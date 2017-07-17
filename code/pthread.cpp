// g++ -o pthread pthread.cpp -lpthread
#include <stdio.h>
#include <pthread.h>

void *say_hello(void *args){
	printf("hello from thread. \n");
	pthread_exit((void *)1);
}

int main() {
	pthread_t tid;
	int iRet = pthread_create(&tid, NULL, say_hello, NULL);
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
