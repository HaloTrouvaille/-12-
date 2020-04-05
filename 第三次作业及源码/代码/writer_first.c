#include "stdio.h"
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>

#define N_WRITER 3 //写者数目
#define N_READER 6 //读者数目
#define W_SLEEP 1 //控制写频率
#define R_SLEEP  0.5 //控制读频率

pthread_t wid[N_WRITER],rid[N_READER];
int data = 0;
int readerCnt = 0, writerCnt = 0;
pthread_mutex_t sem_read;
pthread_mutex_t sem_write;
pthread_mutex_t mutex_write;
pthread_mutex_t mutex_read;
 
void write()
{
    int rd = rand()%1000;
    printf("write data : %d\n",rd);
    data = rd;
}
void read()
{
    printf("read data : %d\n",data);
}
void * writer(void * in)
{
        sem_wait(&sem_write);
        {
            writerCnt++;
            if(writerCnt == 1){
                
                pthread_mutex_lock(&mutex_read);
            }
        }
        sem_post(&sem_write);
        
        
        pthread_mutex_lock(&mutex_write);
        {
            printf("writer%d  begins to write\n",pthread_self());
            write();
            printf("writer%d  finishes writing\n",pthread_self());        
        }
        pthread_mutex_unlock(&mutex_write);
        
        sem_wait(&sem_write);
        {
            writerCnt--;
            if(writerCnt == 0){
                
                pthread_mutex_unlock(&mutex_read);
            }
        }
        sem_post(&sem_write);
        sleep(W_SLEEP);

    pthread_exit((void *) 0);
}


void * reader (void * in)
{

            pthread_mutex_lock(&mutex_read);
            {
                sem_wait(&sem_read);
                {
                    readerCnt++;
                    if(readerCnt == 1){
                        pthread_mutex_lock(&mutex_write);
                    }
                }
                sem_post(&sem_read);
            }
            pthread_mutex_unlock(&mutex_read);
        printf("reader%d  begins to read\n",pthread_self());
        read();
        printf("reader%d  finishes reading\n",pthread_self());
        sem_wait(&sem_read);
        {
            readerCnt--;
            if(readerCnt == 0){
                pthread_mutex_unlock(&mutex_write);
            }
        }
        sem_post(&sem_read);
        
        sleep(R_SLEEP);

    pthread_exit((void *) 0);
}
 
int main()
{
    
    pthread_mutex_init(&mutex_write,NULL);
    pthread_mutex_init(&mutex_read,NULL);
    sem_init(&sem_write,0,1);
    sem_init(&sem_read,0,1);
    int i = 0;
    for(i = 0; i < N_READER; i++)
    {
        pthread_create(&rid[i],NULL,reader,NULL);
    }
    for(i = 0; i < N_WRITER; i++)
    {
        pthread_create(&wid[i],NULL,writer,NULL);
    }
    sleep(1);    
    return 0;
}
