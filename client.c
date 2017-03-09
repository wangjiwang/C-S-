#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLINE 4096

int main(int argc,char **argv)
{
    int sockfd,n;
    char recvline[MAXLINE+1];
    struct sockaddr_in servaddr;
    if (argc  != 2)
    {
        perror("usage:a.out<IPaddress>");
    }

    //socket函数创建一个网际（AF_INET）字节流（SOCK_STREAM ）套接字
    //该函数返回一个小整数描述符，接下来的所有函数调用就用描述符来标识该套接字
    //如果调用函数函数失败，则返回-1，输出提示信息

    if ( (sockfd = socket(AF_INET,SOCK_STREAM,0) )<0)
    {
        perror("socket error");
    }

    //把服务器的IP地址和端口号填入一个网际套接字地址结构（一个名为servaddr的sockaddr_in结构变量）
    //使用bzero函数清零结构体，把地址族设为AF_INET，端口号设置为9500
    //IP地址为第一个命令行参数的值argv[1]
    //因为网际套接字地址结构的IP地址和端口号必须使用特定格式
    //所以调用htons函数（主机到网络短整数函数）去转换二进制端口号
    //再调用inet_pton 把命令行参数IP地址转换为合适的格式

    bzero (&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9500);//连接服务器端口
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
        perror ("inet_pton error");

    //调用connect函数建立与服务器的TCP连接，所连接的服务器由该函数的第二个参数指向的套接字地址结构指定
    //该函数的第三个参数指定套接字地址结构的长度，我们用sizeof操作符来获取

    if (connect (sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))>0) {
        perror ("connect error ");
    }

    //使用read函数来读取服务器的应答，并用fputs函数输出结果
    //如果数据量大，read函数不能返回服务器的整个应答
    //因此，我们总是把read编写在某个循环中，当返回0（表明传输完成）和返回-1（表明发生错误）时循环结束
    while ((n = read(sockfd,recvline,MAXLINE))>0) {
        recvline[n]=0;
        if (fputs(recvline,stdout)==EOF) {
            perror ("fputs error");
        }
    }
    if (n < 0) {
        perror ("read error");
    }
        printf("服务端ip是127.0.0.1\n");
        printf("服务端监听端口是9500\n");
        printf("服务器发送的文件为wjw.txt\n");

    //exit终止程序运行，关闭该进程所有打开的描述符

    exit(0);
}
