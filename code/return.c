#include <stdio.h>
#include <stdlib.h>

void fun(){
	printf("using exit \n");
	printf("this is the content in buff \n");
	return;
}

int main(){
	fun();
	printf("already return \n");
}