#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_x = PTHREAD_MUTEX_INITIALIZER;

int total = 20;

void* self_ticket(void *argv){
	for(int i = 0; i < 20; ++i){
		pthread_mutex_lock(&mutex_x);
		if(total > 0){
			sleep(1);
			printf("sell the %dth ticket \n", 20 - total + 1);
			--total;
		}
		pthread_mutex_unlock(&mutex_x);
	}
	return 0;
}

int main(){
	int iRet;
	pthread_t tids[4];
	int i = 0;
	for(int i = 0; i < 4; i++){
		iRet = pthread_create(&tids[i], NULL, &self_ticket, NULL);
		if(iRet){
			printf("thread create error\n");
		}
	}
	sleep(30);
	void *retval;
	for(int i = 0; i < 4; ++i){
		iRet = pthread_join(tids[i], &retval);
		if(iRet){
			printf("pthread join error\n");
		}
	}
	return 0;
}