#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

static void *
thread_start(void *arg)
{
    void *uargv = NULL;
	int rc = 0;
	printf("new thread \n");
	rc = pthread_mutex_lock(&mutex);	
	printf("lock rc = %d \n", rc);
	rc = pthread_mutex_unlock(&mutex);	
	printf("unlock rc = %d \n", rc);

   	return uargv;
}


int main(int argn, char* args[])
{
 	pthread_t thread_id;
	pthread_attr_t attr;
	int rc = 0;
	rc = pthread_mutex_init(&mutex, NULL);
	printf("init rc = %d \n", rc);
	rc = pthread_attr_init(&attr);
	printf("attr init rc = %d \n", rc);
    rc = pthread_create(&thread_id, &attr,
                                  &thread_start, NULL);
	printf("create rc = %d \n", rc);
	sleep(3);	

	rc = pthread_mutex_destroy(&mutex);
	
	printf("destroy rc = %d \n", rc);
	return 0;
}
