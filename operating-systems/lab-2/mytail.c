#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 512

void tail (int file_desc, long position)
{
	ssize_t nread;
	char buf[BUFSIZE];
        
	lseek(file_desc, position, SEEK_END);
	
	while ((nread = read(file_desc, buf, sizeof(buf))) > 0)
        {
                if (write(STDOUT_FILENO, buf, nread) == -1)
                {
                        perror("Blad zapisu!");
                }
        }
}

int main (int argc, char **argv)
{
	long position;
	int file_desc;

	if (argc < 2 || argc > 4)
	{
		fprintf(stdout, "Usage: %s filename [-b | -c] [blocks | bytes]", argv[0]);
	}

	if ((file_desc = open(argv[1], O_RDONLY)) == -1)
	{
		perror("Blad podczas otwierania pliku.");			
	}

	if (argc == 2)
	{
		position = -1 * (lseek(file_desc, 0L, SEEK_END) / 2);
	}

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-b") == 0)
			position = -1 * (BUFSIZE * atol(argv[i + 1]));
		else if (strcmp(argv[i], "-c") == 0)
			position = -1 * atol(argv[i + 1]);	
	}
	
	tail(file_desc, position);
	return 1;
}
