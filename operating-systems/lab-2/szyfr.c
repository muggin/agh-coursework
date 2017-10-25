#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define READBUF 1
#define WRITEBUF 12
int randomInt()
{
	return (rand() % 9) + 1; 
}	

char randomChar()
{ 
	return (rand() % 94) + 32;
}

void szyfruj(int input_desc, int output_desc)
{
	char c;
	char buf[WRITEBUF];
	int randomNumber;
	while (read(input_desc, &c, READBUF) == 1)
	{

		randomNumber = randomInt();
		buf[0] = c;
		buf[1] = randomNumber + 48;
		for (int i = 2; i <= randomNumber + 1; i++)
			buf[i] = randomChar();
		write(output_desc, buf, randomNumber + 2);
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
	szyfruj(input_desc, output_desc);
}

