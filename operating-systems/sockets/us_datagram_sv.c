#include "us_stream.h"

#define BACKLOG 3

int main (int argc, char * argv[]) {
	struct sockaddr_un svaddr, claddr;
	int sfd, j;
	ssize_t numRead;
	socklen_t len;
	char buf[BUF_SIZE];
	
	/* Construct socket */
	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sfd == -1)
		perror("Socket error.");
	
	/* Remove socket if currently exists */
	if(remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
		perror("Remove error.");
	
	/* Configure server address and bind to socket */
	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);
	
	if(bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1)
		perror("Bind error.");
	
	while(1) {
		/* Receive, process and resend datagram */
		len = sizeof(struct sockaddr_un);
		numRead = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
		
		if (numRead == -1)
			perror("Read error.");
		
		printf("Server received %ld bytes from %s\n", (long)numRead, claddr.sun_path);
		
		for(j = 0; j < numRead; j++)
			buf[j] = toupper((unsigned char) buf[j]);
		
		if(sendto(sfd, buf, numRead, 0, (struct sockaddr *) &claddr, len) != numRead)
			perror("Send to error");
	}
}