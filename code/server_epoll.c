#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#define IPADDRESS "127.0.0.1"
#define PORT 6666
#define MAXSIZE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100

int sock_bind(const char *ip, int port){
	struct sockaddr_in servaddr;
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1){
		perror("socket error");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &servaddr.sin_addr);
	servaddr.sin_port = htons(port);
	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
		perror("bind error");
		exit(1);
	}
	return listenfd;
}

void delete_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

void modify_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void do_read(int epollfd, int fd, char *buff){
	// 读数据
	int nread = read(fd, buff, MAXSIZE);
	if(nread == -1){
		perror("read error");
		close(fd);
		// 发生错误，从注册的fd中删除此客户fd
		delete_event(epollfd, fd, EPOLLIN);
	}
	else if(nread == 0){
		fprintf(stderr, "client close \n");
		close(fd);
		// 完成读操作，删除客户fd
		delete_event(epollfd, fd, EPOLLIN);
	}
	else{
		printf("read message is : %s \n", buff);
		// 事件由读改为写
		modify_event(epollfd, fd, EPOLLOUT);
	}
}

void do_write(int epollfd, int fd, char *buff){
	int nwrite = write(fd, buff, strlen(buff));
	if(nwrite == -1){
		perror("write error \n");
		close(fd);
		// 发生错误从注册中删除
		delete_event(epollfd, fd, EPOLLIN);
	}
	else
		modify_event(epollfd, fd, EPOLLIN);
	// 写完刷新buff
	memset(buff, 0, MAXSIZE);
}

void add_event(int epollfd, int fd, int state){
	// ev用注册事件，state表示监听的事件，fd是被注册的fd
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	// 调用epoll_ctl注册，函数类型通过EPOLL_CTL_XX来区别
	// 将新的fd注册到epollfd
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}


void handle_accept(int epollfd, int listenfd){
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen = 0;
    memset(&cliaddr, 0, sizeof(struct sockaddr_in));   
	// 接受客户请求并返回客户fd
	int clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
	if(clifd == -1)
		perror("accept error");
	else{
		printf("accept a new client : %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
		// 将客户fd同样注册到epollfd中
		add_event(epollfd, clifd, EPOLLIN);
	}
}

void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buff){
	// 遍历events数组，获得有事件产生的fd及产生的事件 -> 对应操作
	for(int i = 0; i < num; i++){
		int fd = events[i].data.fd;
		// 监听描述符监听到事件产生，执行gaccept操作
		if((fd == listenfd) && (events[i].events & EPOLLIN))
			handle_accept(epollfd, listenfd);
		// 监听到有读事件，执行读操作
		else if(events[i].events & EPOLLIN)
			do_read(epollfd, fd, buff);
		// 执行写操作
		else if(events[i].events & EPOLLOUT)
			do_write(epollfd, fd, buff);
	}
}

void do_epoll(int listenfd){
	// 用户态buff缓冲
	char buff[MAXSIZE];
	struct epoll_event events[EPOLLEVENTS];
	// 创建一个epoll句柄，监听数为PDSIZE
	int epollfd = epoll_create(FDSIZE);
	// 在epollfd中注册监听listenfd
	add_event(epollfd, listenfd, EPOLLIN);
	while(1){
		// 等待事件产生，类似于select()
		// events用于返回事件集合
		// ret需要处理的事件数目，0表示已超时
		int ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
		// 根据返回的事件数和事件类型，派发到具体具体流程
		handle_events(epollfd, events, ret, listenfd, buff);
	}
	close(epollfd);
}

int main(){
	// 创建套接字并绑定地址，返回监听描述符
	int listenfd = sock_bind(IPADDRESS, PORT);
	// 开始监听
	listen(listenfd, LISTENQ);
	// 注册监听描述符并响应用户请求
	do_epoll(listenfd);
	return 0;
}

/* 
 * 创建epoll，返回epollfd
 * 向epoll中注册listenfd
 * 调用epoll_wait阻塞掉
 * 等待回调函数填充events数组
 * 遍历event数组检查fd和请求
 * 分发到对应操作
 * 操作执行后要根据执行结果对fd重新注册、删除或修改
 */
