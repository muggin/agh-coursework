#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define BUFSIZE 512 

void cat (int file_desc)
{
        ssize_t nread;
        char buf[BUFSIZE];
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
int file_desc;

	if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [filename]\n", argv[0] );
		return 1;
	}
	
	if (argc == 2)
	{
		if((file_desc = open(argv[1], O_RDONLY)) == -1)
		{
			perror ("Blad przy otwieraniu pliku.");
		}		
	}
	else 
	{
		file_desc = STDIN_FILENO;
	}

	cat(file_desc);
	return 0;
}
