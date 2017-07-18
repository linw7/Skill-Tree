#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#define TEXT_SZ 2048
struct shared_use_st{
	int written;
	char text[TEXT_SZ];
};

int main(){
	int shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if(shmid == -1){
		fprintf(stderr, "shmget failed \n");
		exit(EXIT_FAILURE);
	}

	void *shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)-1){
		fprintf(stderr, "shmat failed \n");
		exit(EXIT_FAILURE);
	}
	printf("memory attached at : % ld \n", (long)shared_memory);

	struct shared_use_st *shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->written = 0;
	char buffer[TEXT_SZ];
	int running = 1;
	while(running){
		while(shared_stuff->written == 1){
			sleep(1);
			printf("waiting for client \n");
		}
		printf("enter some text \n");
		fgets(buffer, TEXT_SZ, stdin);
		strncpy(shared_stuff->text, buffer, TEXT_SZ);
		shared_stuff->written = 1;
		if(strncmp(buffer, "end", 3) == 0){
			running = 0;
		}
	}

	if(shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed \n");
		exit(EXIT_FAILURE);
	}
	return 0;
}