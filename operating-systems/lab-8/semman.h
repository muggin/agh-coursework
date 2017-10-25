#ifndef SEMMAN_H
#define SEMMAN_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEM_SHOP 0
#define SEM_SOFA 1
#define SEM_CHAIRS 2

static struct sembuf buf;

void seminc(int semid, int semnum, int flag) {
	buf.sem_num = semnum;
	buf.sem_op = 1;
	buf.sem_flg = flag;

	if (semop(semid, &buf, 1) == -1) {
		perror("Incrementing semaphore.");
		exit(EXIT_FAILURE);
	}
}

void semdec(int semid, int semnum, int flag) {
	buf.sem_num = semnum;
	buf.sem_op = -1;
	buf.sem_flg = flag;

	if (semop(semid, &buf, 1) == -1) {
		perror("Decrementing semaphore.");
		exit(EXIT_FAILURE);
	}
}
#endif
