#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void *tfn1(void *args){
	printf("the thread. \n");
	return NULL;
}

int main() {
	int iRet;
	pthread_t tid;
	pthread_attr_t attr;
	iRet = pthread_attr_init(&attr);
	if(iRet){
		printf("cant't init attr %s \n", strerror(iRet));
		return iRet;
	}
	iRet = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(iRet){
		printf("can't set attr %s \n", strerror(iRet));
		return iRet;
	}
	iRet = pthread_create(&tid, &attr, tfn1, NULL);
	if(iRet){
		printf("can't create thread %s \n", strerror(iRet));
		return iRet;
	}
	iRet = pthread_join(tid, NULL);
	if(iRet){
		printf("pthread has been detached \n");
		return iRet;
	}
	return 0;
}
