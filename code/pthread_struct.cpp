// g++ -o pthread pthread_struct.cpp -lpthread
#include <stdio.h>
#include <pthread.h>
#include <string.h>

struct arg_type{
	int a;
	char b[100];
};
void *say_hello(void *args){
	struct arg_type temp = *((struct arg_type *)args);
	printf("hello from thread. a = %d, b = %s\n", temp.a, temp.b );
	pthread_exit((void *)1);
}

int main() {
	pthread_t tid;
	struct arg_type args;
	args.a = 10;
	char temp[100] = "say_hello";
	strncpy(args.b, temp, sizeof(temp));
	int iRet = pthread_create(&tid, NULL, say_hello, &args);
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
