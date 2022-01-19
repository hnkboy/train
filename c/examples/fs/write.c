#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include <string.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <stdbool.h>


#define handle_debug(format, ...) \
               do { printf("[%s]  " \
                           format \
                           "\n", __func__, ##__VA_ARGS__); } while (0)
                                                           
                                                   
pthread_mutex_t mutex;
int fd = -1;
volatile bool finished = false;
unsigned long writebytes = 0;
#define handle_error_en(en, msg) \
	   do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
	   do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct thread_info {    /* Used as argument to thread_start() */
   pthread_t thread_id;        /* ID returned by pthread_create() */
   int       thread_num;       /* Application-defined thread # */
   char     *argv_string;      /* From command-line argument */
};

static void *
write_start(void *arg)
{
    int rc = 0;
	struct thread_info *tinfo = arg;
	char *uargv, *p;
	char *buf = malloc(1024*1024);	
	memset(buf,0,1024*1024);

    //printf("new thread \n");
    //rc = pthread_mutex_lock(&mutex);
    //printf("lock rc = %d \n", rc);
    //rc = pthread_mutex_unlock(&mutex);
    //printf("unlock rc = %d \n", rc);
	
	printf("Thread %d: top of stack near %p; argv_string=%s\n",
		   tinfo->thread_num, &p, tinfo->argv_string);

	uargv = strdup(tinfo->argv_string);
	if (uargv == NULL)
	   handle_error("strdup");

	for (p = uargv; *p != '\0'; p++)
	   *p = toupper(*p);

	off_t offset = (1024*1024)*(tinfo->thread_num - 1);
	int writed = 0;
	int wantlen = 0;
	while(!finished){
		if (writed == 1024*1024){
			writed = 0;
			offset = (1024*1024)*(tinfo->thread_num - 1);
		}
		offset += writed; 		
    //pthread_mutex_lock(&mutex);
		lseek(fd, offset, SEEK_SET);
	    wantlen =  1024*1024 - writed;
		rc = write(fd, buf, wantlen);
    //pthread_mutex_unlock(&mutex);
		if (rc < 0){
	   		perror("write error");
		}
		else {
			__atomic_add_fetch(&writebytes, rc, __ATOMIC_SEQ_CST);
			writed += rc;
			//handle_debug("thread %d, rc = %d,writebytes %lu, writed %d, offset %d. wantlen =%d",tinfo->thread_num,rc,writebytes, writed, offset, wantlen);	
		}	
		handle_debug("writen %d",rc + offset);
		
	}
    return uargv;
}


/**
 *  功能描述:
 *  @param param1
 *
 *  @return
 */
int hali_timer_openfd(int iwaits)
{

	struct timespec starttime, stintervaltime;
	struct itimerspec stnewvalue;
    int itimerfd = -1;

    /* timerfd */
   	itimerfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    if (itimerfd < 0)
    {
        perror("timerfd_open()");
        return itimerfd;
    }
	starttime.tv_sec = iwaits;
    starttime.tv_nsec = 0;                                //相当于立即到达超时时间
    stintervaltime.tv_sec = iwaits;                       //首次超时后，每一秒超时一次
    stintervaltime.tv_nsec = 0;
    stnewvalue.it_value = starttime;
    stnewvalue.it_interval = stintervaltime;
	/*设置超时时间，且为相对时间*/
    if (timerfd_settime(itimerfd, 0, &stnewvalue, NULL) < 0)
    {
        perror("work timerfd_settime()");
        return itimerfd;
    }

    return itimerfd;
}

int main(int argn, char* argc[]){
    char *path = NULL;
    int rc = 0;
	int s, tnum, opt, num_threads;
	struct thread_info *tinfo;
	void *res;
    pthread_attr_t attr;
	int epfd = -1;
	int timefd = -1;

	int iret = -1;
    struct epoll_event event;

    if (argn < 2){
        handle_debug("need write path");
        exit(EXIT_SUCCESS);
        //perror("test");
    }
    path = argc[1];
	num_threads = atoi(argc[2]);
    handle_debug("argc[1]: %s %s threads %d \n", path, path,num_threads);
    fd = open(path, O_CREAT|O_SYNC|O_RDWR);
    if (fd < 0){
        handle_debug("open error fd=%d, errno=%d",fd,errno);
        exit(EXIT_FAILURE);
    }
	epfd = epoll_create(1);
    rc = pthread_attr_init(&attr);
    if (rc < 0)
        perror("pthread_attr_init");
    rc = pthread_mutex_init(&mutex, NULL);
    if (rc < 0)
        perror("pthread_mutex_init");
	
    tinfo = calloc(num_threads, sizeof(struct thread_info));
    if (tinfo == NULL)
		handle_error("calloc");
	
    handle_debug("start threads fd=%d",fd);
    rc = open(path, O_CREAT|O_SYNC);
	for (tnum = 0; tnum < num_threads; tnum++) {
		tinfo[tnum].thread_num = tnum + 1;
		//tinfo[tnum].argv_string = argv[optind + tnum];
		tinfo[tnum].argv_string = "test";
		s = pthread_create(&tinfo[tnum].thread_id, &attr, &write_start, &tinfo[tnum]);
        if (s != 0)
			handle_error_en(s, "pthread_create");		
	}

    timefd = hali_timer_openfd(1);
	if (timefd < 0)
		handle_error_en(timefd, "timer_openfd");
	event.events=EPOLLIN;
    event.data.fd = timefd;
	iret = epoll_ctl(epfd, EPOLL_CTL_ADD, timefd, &event);
	if (iret < 0)
		handle_error_en(iret, "epoll_ctl");

    for( ; ; )
    {
		int n_events;
        n_events = epoll_wait(epfd, &event, 10, -1);
        if (event.events & EPOLLIN)
        {
			if(event.data.fd == timefd)
			{
				uint64_t ui64data;
				uint64_t mbytes;
				uint64_t kbytes;
				uint64_t zero = 0x0;
        		handle_debug("epoll event fd=%d",event.data.fd);
				read(timefd, &ui64data,sizeof(ui64data));
				mbytes = __atomic_load_n(&writebytes, __ATOMIC_SEQ_CST)/(1024*1024);
				if(mbytes <= 0){
					kbytes = __atomic_load_n(&writebytes, __ATOMIC_SEQ_CST)/(1024);
					handle_debug("write %lu KB/s",kbytes);	
				}else{
					handle_debug("write %lu MB/s",mbytes);
				}
				__atomic_and_fetch(&writebytes, zero, __ATOMIC_SEQ_CST);
			}
        }
		if (!n_events) {
			/* timed out (idle) */
			continue;
		}
		n_events = errno;
		if (n_events == EINTR) {
        	handle_debug("epoll errno=EINTR");
			finished  = true;
			/*在epoll_wait阻塞期间，signal信号会打断该阻塞，使其返回-1并将errno设置成EINTR*/
			break;
		}
    }



	s = pthread_attr_destroy(&attr);
	if (s != 0)
		handle_error_en(s, "pthread_attr_destroy");
	for (tnum = 0; tnum < num_threads; tnum++) {
		pthread_join(tinfo[tnum].thread_id, &res);
		if (s != 0)
        	handle_error_en(s, "pthread_join");
        printf("Joined with thread %d; returned value was %s\n",
                       tinfo[tnum].thread_num, (char *) res);
        free(res);      /* Free memory allocated by thread */
	}
	free(tinfo);
    return 0;
}
