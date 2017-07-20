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
#define SERV_PORT 6666
#define MAXSIZE 1024
#define FDSIZE 1024
#define EPOLLEVENTS 20

int create_sock(){
	int sockfd;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	return sockfd;
}

void add_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void delete_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

void mod_event(int epollfd, int fd, int state){
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void do_read(int epollfd, int fd, int sockfd, char *buff){
	int nread = read(fd, buff, MAXSIZE);
	if(nread == -1){
		perror("read error");
		close(fd);
	}
	else if(nread == 0){
		fprintf(stderr, "server close");
		close(fd);
	}
	else{
		if(fd == STDIN_FILENO)
			add_event(epollfd, sockfd, EPOLLOUT);
		else{
			delete_event(epollfd, sockfd, EPOLLIN);
			add_event(epollfd, STDOUT_FILENO, EPOLLOUT);
		}
	}
}

void do_write(int epollfd, int fd, int sockfd, char *buff){
	char temp[100];
    int count = 0;
	buff[strlen(buff) - 1] = '\0';
	snprintf(temp, sizeof(temp), "%s_%02d\n", buff, count++);
	int nwrite = write(fd, temp, strlen(temp));
	if(nwrite == -1){
		perror("write error");
		close(fd);
	}
	else{
		if(fd == STDOUT_FILENO)
			delete_event(epollfd, fd, EPOLLOUT);
		else
			mod_event(epollfd, fd, EPOLLIN);
	}
	memset(buff, 0, MAXSIZE);
}

void handle_events(int epollfd, struct epoll_event *events, int num, int sockfd, char *buff){
	for(int i = 0; i < num; i++){
		// fd为有事件产生的描述符
		int fd = events[i].data.fd;
		if(events[i].events & EPOLLIN)
			do_read(epollfd, fd, sockfd, buff);
		else if(events[i].events & EPOLLOUT)
			do_write(epollfd, fd, sockfd, buff);
	}
}

void handle_connection(int sockfd){
	struct epoll_event events[EPOLLEVENTS];
	char buff[MAXSIZE];
	int epollfd = epoll_create(FDSIZE);
	add_event(epollfd, STDIN_FILENO, EPOLLIN);
	while(1){
		int ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
		handle_events(epollfd, events, ret, sockfd, buff);
	}
	close(epollfd);
}

int main(){
	struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	handle_connection(sockfd);
	close(sockfd);
	return 0;
}

