#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

int pfd[2];
int pid;
size_t nread;
char buf[100];

pipe(pfd);
char * str ="Ur beautiful pipe example";
pid = fork();

if(pid == 0) {
	close(pfd[1]);
	nread = read(pfd[0],buf, sizeof(buf));	
    (nread != 0) ? printf("%s (%ld bytes)\n",buf,(long)nread) : printf("No data\n");
	printf("MAX_BUFFOR_SIZE: %ld\n",  fpathconf(pfd[0], _PC_PIPE_BUF));
}
else if (pid > 0) {
	close(pfd[0]);
	write(pfd[1], str, strlen(str));
}


return 0;
}
