#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void *tfn1(void *args){
	printf("the sub thread sleeping 5 seconds \n");
	sleep(5);
	printf("the thread done \n");
	return NULL;
}

int main() {
	int iRet;
	pthread_t tid;
	pthread_attr_t attr;
	iRet = pthread_create(&tid, NULL, tfn1, NULL);
	if(iRet){
		printf("can't create thread %s \n", strerror(iRet));
		return iRet;
	}
	iRet = pthread_detach(tid);
	if(iRet){
		printf("can't detach thread %s \n", strerror(iRet));
		return iRet;
	}
	printf("hello\n");
	iRet = pthread_join(tid, NULL);
	if(iRet){
		printf("pthread has been detached \n");
		return iRet;
	}
	printf("the main thread sleeping 8 seconds \n");
	sleep(8);
	printf("the main thread done \n");
	return 0;
}
