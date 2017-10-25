#include "us_stream.h"

int main (int argc, char * argv[]) {
	struct sockaddr_un addr;
	int sfd, cfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	
	/* Construct socket */
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
		perror("Socket error.");
	
	/* Configure address */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
	
	/* Open connection with server */
	if(connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
		perror("Connect error.");
		
	/* Send stdin stream to server */
	while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
		if(write(sfd, buf, numRead) != numRead) {
			perror("Partial/failed write.");
			exit(EXIT_FAILURE);
		}
	
	if (numRead == -1)
		perror("Read error.");
		
	exit(EXIT_SUCCESS);	
}