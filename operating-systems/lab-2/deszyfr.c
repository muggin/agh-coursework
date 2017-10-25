#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define READBUF 2
#define WRITEBUF 12

void deszyfruj(int input_desc, int output_desc)
{
	char c;
	char buf[READBUF];
	long skipNumber;

	while (read(input_desc, buf, READBUF) == 2)
	{
		c = buf[0];
		skipNumber = atol(&buf[1]);
		fprintf(stdout, "C: %c, N: %d \n", c, skipNumber);
		write(output_desc, &c, 1);
		lseek(input_desc, skipNumber, SEEK_CUR);
	}
}

int main (int argc, char **argv)
{
	int input_desc, output_desc;
	
	if (argc != 3)
	{
		return -1;
	}

	if ((input_desc = open(argv[1], O_RDONLY)) == -1)
	{
		perror(NULL);
	}

	if ((output_desc = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC)) == -1)
	{
		perror(NULL);
	}

	srand(time(NULL));
	deszyfruj(input_desc, output_desc);
}

