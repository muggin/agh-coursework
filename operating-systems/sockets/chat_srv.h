#ifndef CHAT_SRV_H
#define CHAT_SRV_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 33195	// the port users will be connecting to
#define BACKLOG 3	 // how many pending connections queue will hold
#define MAXDATASIZE 100
#define INC_COLOR "\x1B[32m"
#define RST_COLOR "\033[0m"

void server_setup(int * sock_fd, struct sockaddr_in * sv_addr);
void server_listen(int sock_fd);
void run_chat(int sock_fd);
void handle_inc(int sock_fd);
void handle_out(int sock_fd);


#endif