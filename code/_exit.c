#include <stdio.h>
#include <unistd.h>

void fun(){
	printf("using _exit \n");
	printf("this is the content in buff ");
	_exit(0);
}

int main(){
	fun();
	printf("already return \n");
}
