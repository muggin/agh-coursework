/*
 * copy1.c
 * 
 * based on: 
 *
 * Miscellaneous examples for Chap. 2
 * AUP2, Chap. 2
 *
 * modified by WTA
 */

/*[copy-with-bug]*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define BUFSIZE 512

size_t readall(int fd, void *buf, size_t nbyte)
{
	ssize_t nread = 0, n;
	
	do 
	{
        	if ((n = read(fd, &((char *)buf)[nread], nbyte - nread)) <= 0) 
		{
			if (n == 0)
				return nread;
         		if (errno == EINTR)
                               	 continue;
		        else
                                return -1;
                }
                nread += n;
        } while (nread < nbyte);
        return nread;
}

size_t writeall(int fd, const void *buf, size_t nbyte)
{
        ssize_t nwritten = 0, n;

        do 
	{
                if ((n = write(fd, &((const char *)buf)[nwritten], nbyte - nwritten)) == -1) 
		{
                        if (errno == EINTR)
                                continue;
                        else
                                return -1;
                }
                nwritten += n;
        } while (nwritten < nbyte);
        return nwritten;
}

void copy(char *from, char *to)  /* has a bug */
{
	int fromfd = -1, tofd = -1;
	ssize_t nread;
	char buf[BUFSIZE];
	
	if ((fromfd = open(from, O_RDONLY)) == -1)
	{
		perror("Blad otwarcia pliku wejsciowego.");
	}

	if ((tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
	{
		perror("Blad otwarcia pliku wyjsciowego.");
	}

	while ((nread = readall(fromfd, buf, sizeof(buf))) > 0)
	{
		if (writeall(tofd, buf, nread) == -1)
		{
			perror("Blad zapisu!");
		}
	}

        close(fromfd);
	close(tofd);
	return;
}

int main(int argc, char **argv){
	if (argc != 3)
	{
		fprintf(stderr,"usage: %s from_pathname to_pathname\n", argv[0]);
		return 1;
	}
	copy(argv[1], argv[2]);
	return 0;
}
