#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <errno.h>
#include <sys/socket.h>

#define SV_SOCK_PATH "/tmp/us_datagram"
#define BUF_SIZE 20

