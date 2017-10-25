#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define BUFSIZE 100
int main (int argc, char **argv)
{
	
	int fd1, fd2, fd3;
	char bufor[BUFSIZE];
	ssize_t read1, write1, read2, write2;
	
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s [filename]", argv[0]);
		return -1;
	}
	
	if ((fd1 = open(argv[0], O_RDONLY)) == -1)
	{
		perror("Blad podczas otwierania pliku.");
	}

	if ((fd2 = open(argv[0], O_RDONLY)) == -1)
	{
		perror("Blad podczas otwierania pliku.");
	}

	if ((fd3 = open(argv[0], O_RDWR)) == -1)
	{
		perror("Blad podczas otwierania pliku.");
	}
		
	fprintf(stdout, "Cwiczenie 1\nWrite: \nWskaznik 1: %lld \nWskaznik 2: %lld.\n", lseek(fd1, 0L, SEEK_CUR), lseek(fd2, 0L, SEEK_CUR));
	write1 = write(fd1, bufor, BUFSIZE);

	read1 = read(fd2, bufor, BUFSIZE);
	fprintf(stdout, "Read: \nWskaznik 1: %lld \nWskaznik 2: %lld.\n", lseek(fd1, 0L, SEEK_CUR), lseek(fd2, 0L, SEEK_CUR));

	fprintf(stdout, "Cwiczenie 2\nStart:\nWskaznik 3: %lld \n", lseek(fd3, 0L, SEEK_CUR));
	write2 = write(fd3, bufor, BUFSIZE);
	read2 = read(fd3, bufor, BUFSIZE);
	fprintf(stdout, "Read/Write: \nWskaznik 3: %lld \n", lseek(fd3, 0L, SEEK_CUR));
	
	fprintf(stdout, "%ld, %ld, %ld, %ld", write1, read1, write2, read2);
	return 1;
}
