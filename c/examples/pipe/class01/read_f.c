#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{

    // 从管道读取数据

    // 打开管道，以只读的方式读取管道
    int fd = open("test", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(0);
    }

    // 读数据
    while (1)
    {
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));

        if (len == 0)
        {
            printf("写端断开连接。。。。。。。。\n");
            break;
        }
        printf("收到的数据是：%s", buf);
    }
    close(fd);
    return 0;
}


