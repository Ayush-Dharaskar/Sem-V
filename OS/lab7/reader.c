#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<signal.h>
sem_t mutex, wrt;
int rc=0;


void *write(void*arg)
{
    sem_wait(&wrt);
    printf("Writing\n");
    sem_post(&wrt);
}

void *read (void*arg)
{
    sem_wait(&mutex);
    rc++;
    if(rc == 1)
    {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("Reading\n");

    sem_wait(&mutex);
    rc--;
    if(rc==0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);

}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);

    pthread_t * readers,*writers;

    readers = (pthread_t*)malloc(sizeof(pthread_t)*n);
    writers = (pthread_t*)malloc(sizeof(pthread_t)*m);
    int i=0;
    while(i<n || i<m)
    {
        if(i<n)
        {
            pthread_create(&readers[i],NULL,read,NULL);
        }
        if(i<m)
        {
            pthread_create(&writers[i],NULL,write,NULL);
        }
        i++;
    }
    i=0;
    while(i<n || i<m)
    {
        if(i<n)
        {
            pthread_join(readers[i],NULL);
        }
        if(i<m)
        {
            pthread_join(writers[i],NULL);
        }
        i++;
    }
    return 0;
}