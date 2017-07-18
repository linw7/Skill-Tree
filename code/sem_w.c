#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>

#define SEM_KRY 4001
#define SHM_KRY 5678

union semun{
	int val;
};

int main(void){
	int shmid = shmget(SHM_KRY, sizeof(int), IPC_CREAT | 0666);
	if(shmid < 0){
		printf("create shm error \n");
		return -1;
	}
	void *shmptr = shmat(shmid, NULL, 0);
	if(shmptr == (void *)-1){
		printf("shmat error : %s \n", strerror(errno));
		return -1;
	}	
	int *data = (int *)shmptr;
	int semid = semget(SEM_KRY, 2, 0666);
	union semun semuni;
	struct sembuf sembuf;
	while(1){
		sembuf.sem_num = 1;
		sembuf.sem_op = -1;
		sembuf.sem_flg = SEM_UNDO;
		semop(semid, &sembuf, 1);
		scanf("%d", data);
		sembuf.sem_num = 0;
		sembuf.sem_op = 1;
		sembuf.sem_flg = SEM_UNDO;
		semop(semid, &sembuf, 1);
	}
	return 0;
}