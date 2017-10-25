#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "semman.h"

int main () {
	
	int barberid = getpid();
	int semid = semget(1111, 3, 0755);
	if (semid == -1) {
		perror("Creating semaphore array.");
		exit(EXIT_FAILURE);
	}

	printf("Barber %d came to work...\n", barberid);
	
	while(1) {
		printf("Barber %d came to work...\n", barberid);
	
		printf("Barber %d gave a haircut... \n", barberid);
		printf("Barber %d is sleeping...\n", barberid);
		sleep(2);
	}

	return 0;
}
