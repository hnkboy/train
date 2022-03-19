#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024
int main()
{
	char *buf = calloc(1,SIZE); 
	int fd = open("./tt",O_CREAT|O_SYNC|O_RDWR);
	while(1){
		int rc = write(fd,buf,SIZE);
		if (rc < 0)
			printf("write error \n");
	}
	return 0;
}
