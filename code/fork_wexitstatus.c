#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid = fork();
	if(pid < 0){
		perror("fork error\n");
		return 0;
	}
	else if(pid > 0){
		printf("parent process \n");
		int status = -1;
		pid_t pr = wait(&status);
		if(WIFEXITED(status)){
			printf("the child process %d exit normallly \n", pr);
			printf("the return code is %d \n", WEXITSTATUS(status));
		}
		else {
			printf("the child process %d exit abnormally \n", pr);
		}
	}
	else if(pid == 0){
		printf("sub-process, pid : %u, ppid : %u \n", getpid(), getppid());
		exit(3);
	}
	return 0;
}