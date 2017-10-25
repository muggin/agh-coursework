#ifndef CHAT_CLT_H
#define CHAT_CLT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>


#define PORT 33195 // the port client will be connecting to 
#define MAXDATASIZE 100 // max number of bytes we can get at once 
#define INC_COLOR "\x1B[32m"
#define RST_COLOR "\033[0m"

void setup_client(int * sock_fd, struct sockaddr_in * sv_addr, struct hostent * host_ent);
void connect_server(int sock_fd, struct sockaddr_in * sv_addr);
void run_chat(int sock_fd, char * nickname);
void handle_inc(int sock_fd);
void handle_out(int sock_fd, char * nickname);


#endif