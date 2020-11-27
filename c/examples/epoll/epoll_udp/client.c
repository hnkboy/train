#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#define PORT 7777
#define MAX_LINE 2048

int max(int a , int b)
{
	return a > b ? a : b;
}


int main(int argc , char **argv)
{
	/*声明套接字和链接服务器地址*/
    int sockfd;
    struct sockaddr_in servaddr;

    /*判断是否为合法输入*/
    if(argc != 2)
    {
        perror("usage:tcpcli <IPaddress>");
        exit(1);
    }//if

    /*(1) 创建套接字*/
    if((sockfd = socket(AF_INET , SOCK_DGRAM , 0)) == -1)
    {
        perror("socket error");
        exit(1);
    }//if
	//int opt=SO_REUSEADDR;
    //setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    /*(2) 设置链接服务器地址结构*/
    bzero(&servaddr , sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
	//servaddr.sin_addr = htonl(INADDR_LOOPBACK)
    if(inet_pton(AF_INET , argv[1] , &servaddr.sin_addr) < 0)
    {
        printf("inet_pton error for %s\n",argv[1]);
        exit(1);
    }

	sendto (sockfd, "Hi! I'm UDP client!1\n", 22, 0, 
		    (struct sockaddr *)&servaddr, sizeof(servaddr));
		
	sendto (sockfd, "Hi! I'm UDP client!2\n", 22, 0, 
		    (struct sockaddr *)&servaddr, sizeof(servaddr));
				sendto (sockfd, "Hi! I'm UDP client!3\n", 22, 0, 
		    (struct sockaddr *)&servaddr, sizeof(servaddr));
				sendto (sockfd, "Hi! I'm UDP client!4\n", 22, 0, 
		    (struct sockaddr *)&servaddr, sizeof(servaddr));
	/*调用消息处理函数*/
	exit(0);
}
