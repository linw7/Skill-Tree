#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ready = PTHREAD_COND_INITIALIZER;

int traveler_cond = 0;

void *traveler_arrive(void *name){
	printf("traveler %s need a taxi now\n", (char *)name);
	pthread_mutex_lock(&lock);
	traveler_cond++;
	pthread_cond_wait(&ready, &lock);
	pthread_mutex_unlock(&lock);
	printf("traveler %s now got a taxi\n", (char *)name);
	pthread_exit((void *)0);
}

void *taxi_arrived(void *name){
	printf("taxi %s arrives\n", (char *)name);
	while(1){
		pthread_mutex_lock(&lock);
		if(traveler_cond > 0){
			pthread_cond_signal(&ready);
			pthread_mutex_unlock(&lock);
			break;
		}
		pthread_mutex_unlock(&lock);
	}
	pthread_exit((void *)0);
}

int main(){
	pthread_t tids[3];
	int iRet = pthread_create(&tids[0], NULL, taxi_arrived, (void *)("Jack"));
	if(iRet){
		printf("pthread_create error : iRet = %d\n", iRet);
		return iRet;
	}
	printf("time passing by\n");
	sleep(1);
	iRet = pthread_create(&tids[1], NULL, traveler_arrive, (void *)("Susan"));
	if(iRet){
		printf("pthread_create error : iRet = %d\n", iRet);
		return iRet;
	}
	printf("time passing by\n");
	sleep(1);
	iRet = pthread_create(&tids[0], NULL, taxi_arrived, (void *)("Mike"));
	if(iRet){
		printf("pthread_create error : iRet = %d\n", iRet);
		return iRet;
	}
	printf("time passing by\n");
	sleep(1);
	void *retval;
	for(int i = 0; i < 3; i++){
		iRet = pthread_join(tids[i], &retval);
		if(iRet){
			printf("pthread_join error : iRet = %d\n", iRet);
			return iRet;
		}
		printf("retval = %ld\n", (long)retval);
	}
	return 0;
}