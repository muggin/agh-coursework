/*
** server.c -- chat server (stream socket)
*/
#include "chat_srv.h"

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(void)
{
	int sock_fd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct sockaddr_in sv_addr;	// my address information
	struct sockaddr_in cl_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	pid_t new_pid;

	/* Setup chat server and set to listening mode */
	server_setup(&sock_fd, &sv_addr);
	server_listen(sock_fd);
	
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
	
	/* Run chat server */
	sin_size = sizeof(cl_addr);
	while (1) {
		if ((new_fd = accept(sock_fd, (struct sockaddr *)&cl_addr, &sin_size)) == -1) {
			perror("accept");
		}
		
		run_chat(new_fd);
	}
	wait(NULL);
	return 0;
}

void server_setup(int * sock_fd, struct sockaddr_in * sv_addr) {
	char addr_str [INET_ADDRSTRLEN];
	int yes = 1;
	
	if ((*sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(*sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	sv_addr->sin_family = AF_INET;		 // host byte order
	sv_addr->sin_port = htons(MYPORT);	 // short, network byte order
	sv_addr->sin_addr.s_addr = inet_addr("192.168.1.101"); //INADDR_ANY; 
	memset(sv_addr->sin_zero, '\0', sizeof(sv_addr->sin_zero));

	if (bind(*sock_fd, (struct sockaddr *)sv_addr, sizeof(*sv_addr)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	inet_ntop(AF_INET, &sv_addr->sin_addr, addr_str, INET_ADDRSTRLEN);
	printf("Server setup complete.\nServer IPv4 address is: %s\n", addr_str);
	fflush(NULL);
}

void server_listen(int sock_fd) {
	if (listen(sock_fd, BACKLOG) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

void run_chat(int sock_fd) {
	pid_t read_pid, write_pid;
	
	switch(read_pid = fork()) {
		case -1:
			perror("fork (read)");
			exit(EXIT_FAILURE);
		case 0:
			handle_inc(sock_fd);
			break;
		default:
			printf("New process for reading created (pid: %d).\n", read_pid);
			break;
	}
	
	switch(write_pid = fork()) {
		case -1:
			perror("fork (read)");
			exit(EXIT_FAILURE);
		case 0:
			handle_out(sock_fd);
			break;
		default:
			printf("New process for writing created (pid: %d).\n", write_pid);
			break;
	}
	close(sock_fd);
}

void handle_inc(int sock_fd) {
	int numRead;
	char buf[MAXDATASIZE];
	
	while((numRead = read(sock_fd, buf, MAXDATASIZE)) > 0) {
		printf("%sClient: ", INC_COLOR);
		fflush(NULL);
		if(write(STDOUT_FILENO, buf, numRead) != numRead) {
			perror("Partial/failed write.");
			exit(EXIT_FAILURE);
		}
		printf("%s", RST_COLOR);
		fflush(NULL);
	}
}

void handle_out(int sock_fd) {
	int numRead;
	char buf[MAXDATASIZE];
	
	while((numRead = read(STDIN_FILENO, buf, MAXDATASIZE)) > 0) {
		if(write(sock_fd, buf, numRead) != numRead) {
			perror("Partial/failed write.");
			exit(EXIT_FAILURE);
		}
	}
}
