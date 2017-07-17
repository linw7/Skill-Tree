#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid, pr;
	pid = fork();
	if(pid < 0)
		printf("fork error \n");
	else if(pid == 0){
		printf("sub-process will sleep for 10 seconds \n");
		sleep(10);
		exit(0);
	}
	else if(pid > 0){
		do{
			pr = waitpid(pid, NULL, WNOHANG);
			if(pr == 0){
				printf("no child exited \n");
				sleep(1);
			}
		}while(pr == 0);
		if(pr == pid)
			printf("successful get child %d \n", pr);
		else 
			printf("some error occured \n");
	}
	return 0;
}