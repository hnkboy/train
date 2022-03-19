#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{

    // 往管道里面写数据

    // 创建之前首先判断管道文件是否存在
    // 使用F_OK宏判断文件访问是否OK

    int ret = access("test", F_OK);
    if (ret == -1)
    {
        printf("管道不存在，创建\n");

        ret = mkfifo("test", 0664);
        if (ret == -1)
        {
            perror("mkfifo");
            exit(0);
        }
    }

    // 打开管道，以只写的方式读取管道
    int fd = open("test", O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(0);
    }

    // 写数据
    for (int i = 0; i < 100; i++)
    {
        char buf[1024];
        sprintf(buf, "hello, %d\n", i);
        printf("写入的数据是%s: ", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);
    return 0;
}

