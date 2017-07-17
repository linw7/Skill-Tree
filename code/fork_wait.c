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
		printf("parent process, i will block in wait \n");
		pid_t pr = wait(NULL);
		printf("parent process, i catch a child process with pid : %u \n", pr);
	}
	else if(pid == 0){
		printf("sub-process, pid : %u, ppid : %u \n", getpid(), getppid());
		sleep(10);
		exit(0);
	}
	return 0;
}