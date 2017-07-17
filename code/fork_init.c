#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		perror("fail to fork");
		exit(-1);
	}
	else if(pid == 0){
		printf("sub-process, pid : %u, ppid : %u\n", getpid(), getppid());
	}
	else{
		printf("parent, pid : %u, sub-process pid : %u\n", getpid(), pid);
	}
	return 0;
}
