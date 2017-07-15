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

int main(int argc, char *argv[]) {
    int keyboard;
	int ret, i;
	char c;
	fd_set readfd;
	struct timeval timeout;
	// 打开键盘文件返回键盘文件描述符
	keyboard = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	assert(keyboard > 0);

	while(1) {
		// 设置超时信息
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		// 对readdf清零
		FD_ZERO(&readfd);
		// 对resdfd标记keyboard的位置为1
		FD_SET(keyboard, &readfd);
		// 设置select函数参数并调用
		ret = select(keyboard + 1, &readfd, NULL, NULL, &timeout);
		if(ret == -1)
			perror("select error");
		else if(ret) {
			// 判断fd是否在readfd集合中
			if(FD_ISSET(keyboard, &readfd)) {
				// 开始读取键盘输入
				i = read(keyboard, &c, 1);
				if('\n' == c)
					continue;
				printf("The time is %c\n", c);
				if('q' == c)
					break; 
			}
			// 超过5秒没有输入显示超时
			else if(ret == 0)
				printf("time out\n");
		}
	}
    return 0;
}

