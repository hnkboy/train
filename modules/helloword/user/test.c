#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int fd;
	int val = 1;
	fd = open("/dev/xyz", O_RDWR);//根据自己的设备名称
	if (fd < 0)
	{
		printf("can't open!\n");
	}
	return 0;
}

