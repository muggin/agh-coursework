#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
        int     pfd[2];
        pid_t   pid;
        char    string[] = "Test";
        char    buf[10];

        if(pipe(pfd) == -1) {
			perror("Pipe error.");
			exit(EXIT_FAILURE);
		}
        pid = fork();

        if(pid == 0) {
		close(0);
 		dup(pfd[0]);
		close(pfd[0]);
		close(pfd[1]);
        	read(STDIN_FILENO, buf, sizeof(buf));
                printf("Wypisuje: %s\n", buf);
        } else {
			close(1);
			dup(pfd[1]);
			close(pfd[0]);
			close(pfd[1]);
        	write(STDOUT_FILENO, string, (strlen(string)+1));        
	}

        return 0;
}
