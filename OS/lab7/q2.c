    #include<stdio.h>
    #include<stdlib.h>
    #include<semaphore.h>
    #include<pthread.h>


    int rc=0;
    sem_t mutex,info;

    void *writer(void *arg){
        sem_wait(&info);
        printf("Writing completed\n");
        sem_post(&info);
    }

    void *reader(void *arg){
        sem_wait(&mutex);
        rc++;
        if(rc==1){
            sem_wait(&info);
        }
        sem_post(&mutex);
        printf("Reader reading ...\n");
        sem_wait(&mutex);
        rc--;
        if (rc==0)
            sem_post(&info);
        sem_post(&mutex);

    }

    int main(int argc, const char * argv[]){
        rc=0;
        sem_post(&mutex);
        sem_post(&info);
        pthread_t *readers, *writers;
        int read = abs(atoi(argv[1]));
        int write = abs(atoi(argv[2]));
        readers = (pthread_t *)malloc(sizeof(pthread_t)*read);
        writers = (pthread_t *)malloc(sizeof(pthread_t)*write);
        int i=0;
        while(i<read||i<write){
            if(i<read)
                pthread_create(&readers[i], NULL, &reader, NULL);
            if(i<write)
                pthread_create(&writers[i], NULL, &writer, NULL);
            i++;
        }
        i=0;
        while(i<read||i<write){
            if(i<read)
                pthread_join(readers[i], NULL);
            if(i<write)
                pthread_join(writers[i], NULL);
            i++;
        }
    }