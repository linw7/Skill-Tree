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
	int servfd, acceptfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	unsigned int sin_size, myport = 6666, lisnum = 10;
	if((servfd == socket(AF_INET, SOCK_STREAM, 0) == -1)) {
		perror("socket");
		return -1;
	}
	printf("socket ok \n");
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(DEFAULT_PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 0);
	if(bind(servfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		return -2;
	}
	printf("bind ok\n");

	fd_set client_fdset;
	int maxsock;
	struct timeval tv;
	int client_sockfd[5];
	bzero((void *)client_sockfd, sizeof(client_sockfd));
	int conn_amount = 0;
	maxsock = servfd;
	char buffer[1024];
	int ret = 0;
	while(1){
		FD_ZERO(&client_fdset);
		FD_SET(servfd, &client_fdset);
		tv.tv_sec = 30;
		tv.tv_usec = 0;
		for(int i = 0; i < 5; ++i){
			if(client_sockfd[i] != 0)
				FD_SET(client_sockfd[i], &client_fdset);
		}
		ret = select(maxsock + 1, &client_fdset, NULL, NULL, &tv);
		if(ret < 0){
			perror("select error \n");
			break;
		} 
		else if(ret == 0){
			printf("timeout \n");
			continue;
		}
		for(int i = 0; i < conn_amount; ++i) {
			if(FD_ISSET(client_sockfd[i], &client_fdset)){
				printf("start recv from client[%d] : \n", i);
				ret = recv(client_sockfd[i], buffer, 1024, 0);
				if(ret <= 0){
					printf("client[%d] close\n", i);
					close(client_sockfd[i]);
					FD_CLR(client_sockfd[i], &client_fdset);
					client_sockfd[i] = 0;
				} 
				else 
					printf("recv from client[%d] : %s\n", i, buffer);
			}
		}
		if(FD_ISSET(servfd, &client_fdset)){
			struct sockaddr_in client_addr;
			size_t size = sizeof(struct sockaddr_in);
			int sock_client = accept(servfd, (struct sockaddr *)(&client_addr), (unsigned int *)(&size));
			if(sock_client < 0){
				perror("accept error \n");
				continue;
			}
			if(conn_amount < 5){
				client_sockfd[conn_amount++] = sock_client;
				bzero(buffer, 1024);
				strcpy(buffer, "this is server ! welcome \n ");
				send(sock_client, buffer, 1024, 0);
				printf("new connection client[%d] %s : %d \n", conn_amount, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
				bzero(buffer, sizeof(buffer));
				ret = recv(sock_client, buffer, 1024, 0);
				if(ret < 0){
					perror("recv error \n");
					close(servfd);
					return -1;
				}
				printf("recv error \n");
				if(sock_client > maxsock)
					maxsock = sock_client;
				else{
					printf("max connections, quit \n");
					break;
				}
			}
		}
	}
	for(int i = 0; i < 5; ++i){
		if(client_sockfd[i] != 0)
			close(client_sockfd[i]);
	}
	close(servfd);
	return 0;
}