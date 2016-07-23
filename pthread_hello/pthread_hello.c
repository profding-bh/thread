#include<stdio.h>
#include<pthread.h>
#include<string.h>

void * func(void *arg)
{
    printf("hello\n");
    return NULL;
}


int main()
{
    pthread_t tid[5];

    int i;
    for(i = 0; i< 5;++i){
        pthread_create(&tid[i],NULL,func,NULL);
    }
    //sleep(1);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    pthread_join(tid[4],NULL);
    return 0;
}
