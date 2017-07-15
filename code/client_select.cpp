#include <sys/time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h>

#define DEFAULT_PORT 6666

int main() {
	int connfd = 0;
	int cLen = 0;
	struct sockaddr_in client;
	if(argc < 2){
		printf("Usage : client [server ip address] \n");
		return -1;
	}
	client.sin_family = AF_INET;
	client.sin_port = htons(DEFAULT_PORT);
	client.sin_addr.a_addr = inet_addr[argv[1]];
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	if(connfd < 0){
		perror("socket");
		return -1;
	}
	if(connect(connfd, (struct sockaddr *)&client, sizeof(client)) < 0){
		perror("connect");
		return -1;
	}
	char buff[1024];
	bzero(buff, sizeof(buff));
	recv(connfd, buff, 1024, 0);
	printf("recv : %s \n", buff);
	bzero(buff, sizeof(buff));
	strcpy(buff, "this is client \n");
	send(connfd, buff, 1024, 0);
	while(1){
		bzero(buff, sizeof(buff));
		scanf("%s", buff);
		int p = strlen(buff);
		buff[p] = '\0';
		send(connfd, buff, 1024, 0);
		printf("i have send buff \n");
	}
	close(fd);
	return 0;
}