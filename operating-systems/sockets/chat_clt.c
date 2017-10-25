/*
** client.c -- chat client (stream server)
*/
#include "chat_clt.h"

int main(int argc, char *argv[])
{
	int sock_fd;
	char * nickname;
	struct hostent * host_ent;
	struct sockaddr_in sv_addr;

	if (argc != 3) {
	    fprintf(stderr,"usage: ./client hostname nickname\n");
	    exit(EXIT_FAILURE);
	}
	
	/* Process command-line input */
	if ((host_ent = gethostbyname(argv[1])) == NULL) { 
	    perror("gethostbyname");
	    exit(EXIT_FAILURE);
	}
	
	/* Setup chat client and connect to chat server */
	setup_client(&sock_fd, &sv_addr, host_ent);
	connect_server(sock_fd, &sv_addr);
	
	/* Run chat client */
	run_chat(sock_fd, argv[2]);

	wait(NULL);
	return 0;
}

void setup_client(int * sock_fd, struct sockaddr_in * sv_addr, struct hostent * host_ent) {
	if ((*sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	    perror("socket");
	    exit(EXIT_FAILURE);
	}

	sv_addr->sin_family = AF_INET;
	sv_addr->sin_port = htons(PORT);
	sv_addr->sin_addr = *((struct in_addr *) host_ent->h_addr);
	memset(sv_addr->sin_zero, '\0', sizeof(sv_addr->sin_zero));
}

void connect_server(int sock_fd, struct sockaddr_in * sv_addr) {
	if (connect(sock_fd, (struct sockaddr *)sv_addr, sizeof(*sv_addr)) == -1) {
	    perror("connect");
	    exit(EXIT_FAILURE);
	}
}

void run_chat(int sock_fd, char * nickname) {
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
			handle_out(sock_fd, nickname);
			break;
		default:
			printf("New process for writing created (pid: %d).\n", write_pid);
			break;
	}
	sleep(10);
	close(sock_fd);
	
}

void handle_inc(int sock_fd) {
	int numRead;
	char buf[MAXDATASIZE];
	char msg_start;
	
	while((numRead = read(sock_fd, buf, MAXDATASIZE)) > 0) {
		printf("%sServer: ", INC_COLOR);
		fflush(NULL);
		if(write(STDOUT_FILENO, buf, numRead) != numRead) {
			perror("Partial/failed write.");
			exit(EXIT_FAILURE);
		}
		printf("%s", RST_COLOR);
		fflush(NULL);
	}
}

void handle_out(int sock_fd, char * nickname) {
	int numRead;
	char buf[MAXDATASIZE];
	
	while((numRead = read(STDIN_FILENO, buf, MAXDATASIZE)) > 0) {
		if(write(sock_fd, buf, numRead) != numRead) {
			perror("Partial/failed write.");
			exit(EXIT_FAILURE);
		}
	}
}
