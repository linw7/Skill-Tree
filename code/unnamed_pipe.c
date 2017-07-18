#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define INPUT 0
#define OUTPUT 1

int main() {
	int fd[2];
	char buff[256];
	pipe(fd);
	pid_t pid = fork();
	if(pid < 0){
		printf("error fork \n");
		exit(1);
	}
	else if(pid == 0){
        printf("in child process ... \n");
		close(fd[INPUT]);
		write(fd[OUTPUT], "hello world", strlen("hello world"));
		exit(0);
	}
	else{
		printf("in parent process ... \n");
		close(fd[OUTPUT]);
		int count = read(fd[INPUT], buff, sizeof(buff));
		printf("%d bytes of data received from child process : %s \n", count, buff);
	}
}
