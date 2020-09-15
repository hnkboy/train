
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sum = 0;
pthread_mutex_t mutex;

void* adder(void *p)
{
    for(int i = 0; i < 1000000; i++)  // 百万次
    {
        sum++;
    }

    return NULL;
}

int main()
{
    pthread_t threads[10];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, adder, NULL);
    }

    for(int i = 0; i < 10; i++)
    {
        pthread_join(threads[i],NULL);
    }

	printf("sum is %d\n", sum);
}
