#include <stdio.h>    // printf
#include <stdlib.h>    // exit
#include <unistd.h>
#include <fcntl.h>    // open
#include <sys/select.h>

#define FILE_NAME    "/dev/globalmem"

int main(int args, char *argv[])
{
    int fd;
    fd_set rd_fd_set,wr_fd_set;    

    printf("\r\nstart.");

    // open file
    fd=open(FILE_NAME,O_RDONLY|O_NONBLOCK);
    if( fd<0 )    
    {
        printf("\r\nopen file err");
        exit(-1);
    }
    
        
    while(1)
    {
        FD_ZERO(&rd_fd_set);
        FD_ZERO(&wr_fd_set);
        FD_SET(fd,&rd_fd_set);
        FD_SET(fd,&wr_fd_set);
        
        select(fd+1,&rd_fd_set,&wr_fd_set,NULL,NULL);
        if( FD_ISSET(fd,&rd_fd_set) )
            printf("\r\nPoll monitor:can be read");
        if( FD_ISSET(fd,&wr_fd_set) )
            printf("\r\nPoll monitor:can be write");        
    }
    close(fd);
    exit(0);
}
