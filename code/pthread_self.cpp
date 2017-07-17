// g++ -o pthread pthreadself.cpp -lpthread
#include <stdio.h>
#include <pthread.h>

void *say_hello(void *args){
	printf("hello from thread. i = %d, tid = %ld\n", *((int *)args), pthread_self());
	pthread_exit((void *)1);
}

int main() {
	pthread_t tid;
	int para = 10;
	int iRet = pthread_create(&tid, NULL, say_hello, &para);
	if(iRet){
		printf("pthread create error : iRet = %d\n", iRet);
		return iRet;
	}
	void *retval;
	iRet = pthread_join(tid, &retval);
	if(iRet){
		printf("pthread join error : iRet = %d\n", iRet);
		return iRet;
	}
	printf("retval = %ld\n", (long)retval);
	return 0;
}
