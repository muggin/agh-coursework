#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "semman.h"

#define BARBERS 3
#define CUSTOMERS 5

#define MAX_SHOP 20
#define MAX_SOFA 4
#define MAX_CHAIRS 3

void getsem(int semid, int semnum) {
	
}
int main () {
	int semid;

	semid = semget(1111, 3, IPC_CREAT|0755);
	if (semid == -1) {
		perror("Creating semaphore array.");
		exit(EXIT_FAILURE);
	}

	if (semctl(semid, SEM_SHOP, SETVAL, (int)MAX_SHOP) == -1) {
		perror("Setting the value of SEM_SHOP");
		exit(EXIT_FAILURE);
	}

	if (semctl(semid, SEM_SOFA, SETVAL, (int)MAX_SOFA) == -1) {
		perror("Setting the value of SEM_SOFA");
		exit(EXIT_FAILURE);
	}

	if (semctl(semid, SEM_CHAIRS, SETVAL, (int)MAX_CHAIRS) == -1) {
		perror("Setting the value of SEM_CHAIRS");
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0; i < BARBERS; i++) {
		int pid = fork();
		if (pid == -1) {
			perror("Creating barbers.");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			execl("./fryzjer", "./fryzjer", NULL);
		}
	}

	for (int i = 0; i < CUSTOMERS; i++) {
		int pid = fork();
		if (pid == -1) {
			perror("Creating customers.");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			execl("./klient", "./klient", NULL);
		}
	}


	return 0;
}

