#include <stdio.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>

int main(){
    int fds[2];
    pipe(fds);
    if(!fork()){
        close(fds[1]); //子进程关闭文件描述符4，但fds[0]为3
        int fd;
        read(fds[0], &fd, sizeof(fd)); //通过fds[0]读出管道内容，写入fd中
        printf("child fd = %d\n", fd); //输出为3
        char buf[128] = {0};
        read(fd, buf, sizeof(buf)); //fds[0]与fd同时为3，读阻塞
        printf("buf = %s\n", buf);
        close(fds[0]); //子进程关闭文件描述符4，但fds[0]为3
        return 0;
    }
    else{
        close(fds[0]); //父进程关闭文件描述符3
        int fd;
        char buf[128] = {0};
        read(fd, buf, sizeof(buf)); //fds[0]与fd同时为3，读阻塞
        fd = open("file", O_RDWR|O_CREAT); //打开文件的描述符为fd = 3
        printf("parent fd = %d\n", fd);
        write(fds[1], &fd, sizeof(fd));  //通过fds[1]写入管道内容
        //write(fd, "fdfd", sizeof(fd));  //向fd写入数据
        //read(fd, buf, sizeof(buf)); //fds[0]与fd同时为3，读阻塞
        wait(NULL); //回收子进程
        close(fds[1]); //父进程关闭文件描述符3
        return 0;
    }
}
