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

#define MAXLINE 1024
#define DEFAULT_PORT 6666
#define max(a, b) (a > b) ? a : b

static void handle_connection(int sockfd);

int main(int argc, char const *argv[])
{
	int connfd = 0;
	int cLen = 0;
	struct sockaddr_in client;
	if(argc < 2){
		printf("Usage : Server IP address \n");
		return -1;
	}
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	client.sin_family = AF_INET;
	client.sin_port = htons(DEFAULT_PORT);
	client.sin_addr.s_addr = inet_addr(argv[1]);
	if(connfd < 0){
		perror("socket");
		return -1;
	}
	if(connect(connfd, (struct sockaddr *)&client, sizeof(client)) < 0){
		perror("connect");
		return -2;
	}
	handle_connection(connfd);
	return 0;
}

static void handle_connection(int sockfd){
	char sendline[MAXLINE], recvline[MAXLINE];
	int maxfd, stdineof;
	struct pollfd pfds[2];
	int n;
	pfds[0].fd = sockfd;
	pfds[0].events = POLLIN;
	pfds[1].fd = STDIN_FILENO;
	pfds[1].events = POLLIN;
	while(1){
		poll(pfds, 2 , -1);
		if(pfds[0].revents & POLLIN){
			n = read(sockfd, recvline, MAXLINE);
			if(n == 0){
				fprintf(stderr, "client : server is closed \n");
				close(sockfd);
			}
			write(STDOUT_FILENO, recvline, n);
		}
		if(pfds[1].revents & POLLIN){
			n = read(STDIN_FILENO, sendline, MAXLINE);
			if(n == 0){
				shutdown(sockfd, SHUT_WR);
				continue;
			}
			write(sockfd, sendline, n);
		}
	}
}
