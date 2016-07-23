#include<pthread.h>
#include<stdio.h>


pthread_mutex_t mutex;

int a = 0;

void *acc(void *arg)
{
   pthread_mutex_lock(&mutex);
    a++;
    printf("自增 a is %d\n",a);
    pthread_mutex_unlock(&mutex);
}

void *abb(void *arg)
{
    pthread_mutex_lock(&mutex);
    a--;
    printf("自减 a is %d\n",a);
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t tid1,tid2;

    pthread_mutex_init(&mutex,NULL);


    pthread_create(&tid1,NULL,acc,NULL);
    pthread_create(&tid2,NULL,abb,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
     return 0;
}



