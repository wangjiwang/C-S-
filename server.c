#include <time.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 4096
#define LISTENQ 1024


int main(int argc, char ** argv)
{
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    //创建TCP套接字
    listenfd = socket(AF_INET,SOCK_STREAM,0);

    //填写一个网际套接字地址结构并调用bind函数，服务器的端口我们设置为9500
    //IP地址我们指定为127.0.0.1（这个要根据你自己的IP地址指定）
    bzero(&servaddr ,sizeof(servaddr ));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(9500);//端口的设置

    //bind函数把一个本地的协议地址赋予一个套接字。
    //第二个参数是一个指向特定于协议的地址结构的指针，第三个参数是该地址结构的长度
    bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr ));

    //调用listen函数把该套接字转换成监听套接字
    //第二个参数是指定这个监听描述符上排队的最大客户连接数
    listen(listenfd,LISTENQ);

    //调用accept函数
    //第一个参数叫监听套接字描述符，由socket创建，随后作用与bind和listen的第一个参数描述符
    //accept函数成功返回时，返回一个已连接套接字描述符
    //注意！监听套接字描述符与已连接套接字描述符是不一样的
    //一个服务器通常仅仅创建一个监听套接字，它在该服务的生命周期内一直存在。
    //内核会为每个与服务器成功连接的客户创建一个新的套接字，即已连接套接字
    //当服务器完成对某个客户的服务时，相应的连接套接字就被关闭掉
    for(;;){
        connfd = accept(listenfd ,(struct sockaddr*)NULL,NULL);

        ticks = time (NULL);
        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        write(connfd,buff,strlen(buff));

        close(connfd);
        }
    return 0;
}
