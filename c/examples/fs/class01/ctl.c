#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
typedef enum {
	COMMAND_SET_SPEED,
	COMMAND_INVAILD
}arg_command_t;
arg_command_t command = COMMAND_INVAILD;  
int main(int argc, char *argv[]){
    static const char options[] = "s:v";
    char c;
    char *exec_name = argv[0];
    printf("argc: %d\n",argc);
	char speed[1024];
	char recvbuf[1024];
	memset(speed, 0, sizeof(speed));
	memset(recvbuf, 0, sizeof(recvbuf));
   	while ((c = getopt(argc, argv, options)) != EOF) {
        switch (c) {
        case 's':
            //printf("optind: %d", optind);
            //printf("optarg: %s\n", optarg);
			command  = COMMAND_SET_SPEED;
			memcpy(speed, optarg, optind);
            break;
        case 'v':
            printf("version: 0.0.0.1\n");
            break;
        default: /* '?' */
            fprintf(stderr, "Try '%s -h' for usage\n", exec_name);
            exit(1);
        }
    }
    int write_fd = open("/var/write.pipe", O_WRONLY|O_NONBLOCK);
   	//int read_fd = open("/var/read.pipe", O_RDONLY);
    //if ((write_fd == -1) || (read_fd == -1))
    if (write_fd == -1 )
    {
        perror("open");
        exit(0);
    }
	if (COMMAND_SET_SPEED == command)
	{	
        write(write_fd, speed, strlen(speed));
		/*
		int len = read(read_fd, recvbuf, sizeof(recvbuf));
        if (len == 0)
        {
            printf("send command error\n");
        }
		else{
        	printf("send command success\n");
		}*/
	}
	
    close(write_fd);
    //close(read_fd);

    return 0;
}
