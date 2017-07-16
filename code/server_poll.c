#include <sys/time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/wait.h>
#include <poll.h>

#define IPADDRESS "127.0.0.1"
#define PORT 6666
#define MAXLINE 1024
#define LISTENQ 5
#define OPEN_MAX 1000
#define INFTIM -1

int bind_and_listen() {
	int servfd;
	struct sockaddr_in my_addr;
	unsigned int sin_size;
	if((servfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return -1;
	}
	printf("socket ok \n");

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 0);
	if(bind(servfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		return -2;
	}
	printf("bind ok \n");

	if(listen(servfd, LISTENQ) == -1){
		perror("listen");
		return -3;
	}
	printf("listen ok \n");
	return servfd;
}

void do_poll(int listenfd){
	int connfd, sockfd;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	struct pollfd client_fds[OPEN_MAX];
	int max = 0;
	int i;
	int nready;

	client_fds[0].fd = listenfd;
	client_fds[0].events = POLLIN;

	for(int i = 1; i < OPEN_MAX; ++i)
		client_fds[i].fd = -1;
	while(1){
		nready = poll(client_fds, max + 1, INFTIM);
		if(nready == -1){
			perror("poll error");
			exit(1);
		}
		if(client_fds[0].revents & POLLIN){
			client_addr_len = sizeof(client_addr);
			if((connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1){
				if(errno == EINTR)
					continue;
				else{
					perror("accept error");
					exit(1);
				}
			}
			fprintf(stdout, "accept a new client : %s:%d \n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
			for(int i = 1; i < OPEN_MAX; i++){
				if(client_fds[i].fd < 0){
					client_fds[i].fd = connfd;
					break;
				}
			}
			if(i == OPEN_MAX){
				fprintf(stderr, "too many clients. \n");
				exit(1);
			}
			client_fds[i].events = POLLIN;
			max = (i > max ? i : max);
			if(--nready <= 0)
				continue;
		}
        char buff[MAXLINE];
        memset(buff, 0, MAXLINE);
        int readlen = 0;
        for(int i = 1; i <= max; i++){
           	if(client_fds[i].fd < 0)
               	continue;
            if(client_fds[i].revents & POLLIN){
                readlen = read(client_fds[i].fd, buff, MAXLINE);
                if(readlen == 0){
                 	close(client_fds[i].fd);
                    client_fds[i].fd = -1;
                    continue;
                }
                write(STDOUT_FILENO, buff, readlen);
                write(client_fds[i].fd, buff, readlen);
            }
		}
	}
}
int main(int argc, char *argv[]){
	int listenfd = bind_and_listen();
	if(listenfd < 0)
		return 0;
	do_poll(listenfd);
	return 0;
}
