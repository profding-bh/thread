#include<stdio.h>
#include<pthread.h>

void *fun(void *arg)
{
    int i;
    for(i = 0;i<10;i++){
        printf("i is %d\n",i);
    }
    printf("xxxx\n");
    pthread_exit((void *) 112);
    printf("yyyyyy\n");
    return NULL;
}

int main()
{

    pthread_t  tid;

    void *ret;
    pthread_create(&tid,NULL,fun,NULL);
    pthread_join(tid,&ret);

    printf("子线程的返回值 %d\n",(int)ret);
    return 0;
}
