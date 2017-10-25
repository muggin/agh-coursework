#include "us_stream.h"

int main (int argc, char * argv[]) {
	struct sockaddr_un svaddr, claddr;
	int sfd, j;
	size_t msgLen;
	ssize_t numRead;
	socklen_t len;
	char buf[BUF_SIZE];
	
	/* Construct socket */
	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sfd == -1)
		perror("Socket error.");
	
	/* Configure address and bind to client socket */
	memset(&claddr, 0, sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;
	snprintf(claddr.sun_path, sizeof(claddr.sun_path), "/tmp/ud_ucase_cl.%ld", (long) getpid());
	if(bind(sfd, (struct sockaddr *) &claddr, sizeof(struct sockaddr_un)) == -1)
		perror("Bind error.");
	
	/* Configure  server address */
	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);
		
	for(j = 1; j < argc; j++) {
		
		/* Send, receive and print processed command-line arguments */
		msgLen = strlen(argv[j]);
		if(sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) != msgLen)
			perror("Send to error.");
		
		numRead = recvfrom(sfd, buf, BUF_SIZE, 0, NULL, NULL);
		if(numRead == -1)
			perror("Read error.");
		
		printf("Server response: %s\n", buf);
	}
		
	remove(claddr.sun_path);
	exit(EXIT_SUCCESS);	
}