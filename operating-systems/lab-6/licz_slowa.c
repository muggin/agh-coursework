#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

#define BUF_SIZE 512
int main(int argc, char** argv) {

	int pfd1we[2], pfd1wy[2];
	int pfd2we[2], pfd2wy[2];
	int file_desc;
	int pid1, pid2;
	char buf[BUF_SIZE];
	ssize_t nread;

	file_desc = open(argv[1], O_RDONLY);
	
	if (pipe(pfd1we) == -1 || pipe(pfd1wy) == -1) {
		perror("Pipe 1\n");
		exit(EXIT_FAILURE);
	}

	if (pipe(pfd2we) == -1 || pipe(pfd2wy) == -1) {
		perror("Pipe 2\n");
		exit(EXIT_FAILURE);
	}

	if ((pid1 = fork()) == -1) {
		perror("Fork\n");
		exit(EXIT_FAILURE);
	}

	if ((pid2 = fork()) == -1) {
		perror("Fork\n");
		exit(EXIT_FAILURE);
	}

	/* Fork 1 - WC */
	if (pid1 == 0 & pid2 != 0) {
	
		printf("Proces WC");
		if(dup2(pfd1wy[0], STDIN_FILENO) != 0)
			perror("Dup1");
			
		if(dup2(pfd1we[1], STDOUT_FILENO) != 1)
			perror("Dup2");
		
		if(close(pfd1wy[0]) == -1 || close(pfd1wy[1]) == -1)
			perror("Close3");
		if(close(pfd1we[0]) == -1 || close(pfd1we[1]) == -1)
			perror("Close4");

		execlp("wc", "wc", "-l", NULL);
	}

	if (pid1 != 0 & pid2 == 0) {

		if(dup2(pfd2wy[0], STDIN_FILENO) != 0)
			perror("Dup21");
	
		if(dup2(pfd2we[1], STDOUT_FILENO) != 1)
			perror("Dup22");
		
		if(close(pfd2wy[0]) == -1 || close(pfd2wy[1]) == -1)
			perror("Close");
		if(close(pfd2we[0]) == -1 || close(pfd2we[1]) == -1)
			perror("Close");
		
		execlp("wc", "wc", NULL);
	}


	if (pid1 > 0 & pid2 > 0) {
		
		if (close(pfd1wy[0]) == -1 || close(pfd1we[1]) == -1 ||
			close(pfd2wy[0]) == -1 || close(pfd2we[1]) == -1)
				perror("Close5");

		printf("Proces macierzysty.\n");
		while ((nread = read(file_desc, buf, sizeof(buf))) > 0) {
			if (write(pfd1wy[1], buf, nread) == -1) {
				perror("blad zapisu!");
			}

			if (write(pfd2wy[1], buf, nread) == -1) {
				perror("blad zapisu!");
			}

			if (write(STDOUT_FILENO, buf, nread) == -1) {
				perror("blad zapisu!");
			}
		}

		if (close(pfd1wy[1]) == -1 || close(pfd2wy[1]) || close(file_desc) == -1)
			perror("Close6");
		
		printf("Liczba wszystkich slow:\n ");
		while ((nread = read(pfd1we[0], buf, sizeof(buf))) > 0) {
			if (write(STDOUT_FILENO, buf, nread) == -1) {
				perror("blad zapisu!");
			}	
		}

		while ((nread = read(pfd2we[0], buf, sizeof(buf))) > 0) {
			if (write(STDOUT_FILENO, buf, nread) == -1) {
				perror("blad zapisu!");
			}	
		}
	}

	if (close(pfd1we[0]) == -1 || close(pfd2we[0] == -1))
		perror("Close7");

	return 0;
}
