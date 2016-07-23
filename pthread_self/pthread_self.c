#include<stdio.h>
#include<pthread.h>

void *startfun(void *data)
{

    printf("线程ID %u\n",(unsigned int)pthread_self());
    return NULL;
}

int main()
{
    pthread_t tha;

    void *ret;
    pthread_create(&tha,NULL,startfun,NULL);
    pthread_join(tha,&ret);


    printf("主线程ID %u\n，子线程返回 %d\n",(unsigned int)pthread_self(),(int) ret);
    return 0;
}
