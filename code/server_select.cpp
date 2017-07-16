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
#include <iostream>

using namespace std;

int main() {
	// servfd监听描述符，acceptfd连接描述符
	int servfd, acceptfd;
	struct sockaddr_in my_addr;
	// 创建套接字（IPv4 + TCP）
	if((servfd == socket(AF_INET, SOCK_STREAM, 0) == -1)) {
		perror("socket");
		return -1;
	}
	printf("socket ok \n");
	// 设置sockaddr_in结构的类型，端口号，IP地址
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(6666);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// 对my_addr清零
	bzero(&(my_addr.sin_zero), 0);
	// 将套接字描述符和sockaddr_in结构绑定
	if(bind(servfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		return -2;
	}
	printf("bind ok\n");
	
	int maxsock = servfd;
	fd_set client_fdset;
	struct timeval tv;
	int client_sockfd[5];
	bzero((void *)client_sockfd, sizeof(client_sockfd));
	int conn_amount = 0;
	char buffer[1024];
	int ret = 0;

	while(1){
		// 将fd_set集合置零并重设fd位，设置超时时间
		FD_ZERO(&client_fdset);
		FD_SET(servfd, &client_fdset);
		tv.tv_sec = 30;
		tv.tv_usec = 0;
		// 把已连上的client描述符加入集合中
		for(int i = 0; i < 5; ++i){
			if(client_sockfd[i] != 0)
				FD_SET(client_sockfd[i], &client_fdset);
		}
		// 调用select函数并检查是否正确
		ret = select(maxsock + 1, &client_fdset, NULL, NULL, &tv);
		if(ret < 0){
			perror("select error \n");
			break;
		} 
		else if(ret == 0){
			printf("timeout \n");
			continue;
		}
		// 遍历每一个已连上的client的fd，查看是否有数据，conn_amount初始为0
		for(int i = 0; i < conn_amount; ++i) {
			if(FD_ISSET(client_sockfd[i], &client_fdset)){
				printf("start recv from client[%d] : \n", i);
				ret = recv(client_sockfd[i], buffer, 1024, 0);
				// 无数据可读则关闭连接且在集合中清理掉
				if(ret <= 0){
					printf("client[%d] close\n", i);
					close(client_sockfd[i]);
					FD_CLR(client_sockfd[i], &client_fdset);
					client_sockfd[i] = 0;
				} 
				// 有数据可读
				else 
					printf("recv from client[%d] : %s\n", i, buffer);
			}
		}
		// 检查是否有新连接
		if(FD_ISSET(servfd, &client_fdset)){
			struct sockaddr_in client_addr;
			size_t size = sizeof(struct sockaddr_in);
			// 服务器接收新连接并返回连接描述符sock_client
			int sock_client = accept(servfd, (struct sockaddr *)(&client_addr), (unsigned int *)(&size));
			if(sock_client < 0){
				perror("accept error \n");
				continue;
			}
			// 已连接数小于5接受新连接
			if(conn_amount < 5){
				client_sockfd[conn_amount++] = sock_client;
				bzero(buffer, 1024);
				// 建立起连接向客户机发送消息
				strcpy(buffer, "this is server ! welcome \n ");
				send(sock_client, buffer, 1024, 0);
				// 打印客户机信息，IP + port
				printf("new connection client[%d] %s : %d \n", conn_amount, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
				bzero(buffer, sizeof(buffer));
				// 开始调用recv接收用户输入数据
				ret = recv(sock_client, buffer, 1024, 0);
				if(ret < 0){
					perror("recv error \n");
					close(servfd);
					return -1;
				}
				printf("recv : %s \n", buffer);
				// 检查新建立连接的描述符是否比当前最大的更大并更新（select第一个参数）
				if(sock_client > maxsock) {
					maxsock = sock_client;
				}
			}
			// 超过最大连接
			else{
				printf("max connections, quit \n");
				break;
			}
		}
	}
	// 关掉已连上的fd和自身fd
	for(int i = 0; i < 5; ++i){
		if(client_sockfd[i] != 0)
			close(client_sockfd[i]);
	}
	close(servfd);
	return 0;
}
