#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ready = PTHREAD_COND_INITIALIZER;

int x = 10;
int y = 20;

void *func1(void *arg){
	printf("func1 start\n");
	pthread_mutex_lock(&lock);
	while(x < y){
		pthread_cond_wait(&ready, &lock);
	}
	pthread_mutex_unlock(&lock);
	sleep(3);
	printf("func1 end\n");
}

void *func2(void *arg){
	printf("func2 start\n");
	pthread_mutex_lock(&lock);
	x = 20;
	y = 10;
	printf("has change x and y\n");
	pthread_mutex_unlock(&lock);
	if(x > y){
		pthread_cond_signal(&ready);
	}
	printf("func2 end\n");
}

int main(){
	pthread_t tid1, tid2;
	int iRet;
	iRet = pthread_create(&tid1, NULL, func1, NULL);
	if(iRet){
		printf("pthread 1 create error\n");
		return iRet;
	}
	sleep(2);
	iRet = pthread_create(&tid2, NULL, func2, NULL);
	if(iRet){
		printf("pthread 2 create error");
		return iRet;
	}
	sleep(5);
	return 0;
}