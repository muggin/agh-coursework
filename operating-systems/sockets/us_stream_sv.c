#include "us_stream.h"

#define BACKLOG 3

int main (int argc, char * argv[]) {
	struct sockaddr_un addr;
	int sfd, cfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	
	/* Construct socket */
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
		perror("Socket error.");
	
	/* Remove socket if currently exists */
	if(remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
		perror("Remove error.");
	
	/* Configure address and bind to socket */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
	
	if(bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
		perror("Bind error.");
	
	/* Listen for incoming connections */
	if(listen(sfd, BACKLOG) == -1)
		perror("Listen error.");
	
	while(1) {
		
		/* Accept and handle connections */
		cfd = accept(sfd, NULL, NULL);
		if (cfd == -1)
			perror("Accept error.");
		
		while((numRead = read(cfd, buf, BUF_SIZE)) > 0)
			if(write(STDOUT_FILENO, buf, numRead) != numRead) {
				perror("Partial/failed write.");
				exit(EXIT_FAILURE);
			}
	
		if (numRead == -1)
			perror("Read error.");
		
		if (close(cfd) == -1)
			perror("Close error.");
	}
}