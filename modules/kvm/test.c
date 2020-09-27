#include <stdio.h>    // printf
#include <stdlib.h>    // exit
#include <unistd.h>
#include <fcntl.h>    // open
#include <sys/select.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <linux/kvm.h>
#define FILE_NAME    "/dev/kvm"
/*需要用root权限运行*/
int main(int args, char *argv[])
{
    int fd;
	int ret = 0; 
    fd_set rd_fd_set,wr_fd_set;    
    int f;
    printf("\r\nstart.\n");

    // open file
    fd=open(FILE_NAME,O_RDWR|O_CLOEXEC);
    if( fd<0 )    
    {
        printf("\r\nopen file err");
        exit(-1);
    }

    f = fcntl(fd, F_GETFD);
    assert(f != -1);
    f = fcntl(fd, F_SETFD, f | FD_CLOEXEC);
    assert(f != -1);
	
    ret = ioctl(fd, KVM_GET_API_VERSION, ret);
    printf("kvm-version:%d \n",ret);
	
    close(fd);
    exit(0);
}
