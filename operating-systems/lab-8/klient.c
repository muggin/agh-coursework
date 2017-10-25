#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "semman.h"

void enterShop(int cid) {
	printf("Customer %d is trying to come inside the barbershop... \n", customerid);
	semdec(semid, SEM_SHOP, IPC_NOWAIT);
	printf("Customer %d is inside the barbershop...\n", customerid);

}
int main () {

	int customerid = getpid();
	int semid = semget(1111, 3, 0755);
	if (semid == -1) {
		perror("Creating semaphore array.");
		exit(EXIT_FAILURE);
	}

	printf("Customer %d is thinking about getting a haircut...\n", customerid); 
		printf("Customer %d is trying to sit on the sofa...\n", customerid);
	semdec(semid, SEM_SOFA, 0);
	printf("Customer %d is sitting on the sofa...\n", customerid);
	printf("Customer %d is trying to sit on the chair...\n", customerid);
	seminc(semid, SEM_SOFA, 0);
	semdec(semid, SEM_CHAIRS, 0);
	printf("Customer %d is getting a haircut...\n", customerid);
	seminc(semid, SEM_CHAIRS, 0);
	seminc(semid, SEM_SHOP, 0);
	printf("Customer %d is leaving the shop...\n", customerid);
	return 0;
}

