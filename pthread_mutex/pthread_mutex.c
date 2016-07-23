#include<stddef.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

#define FALSE 0

#define TRUE 1


/*
 *利用互斥锁实现线程的同步
 *一个线程从共享的缓冲区读取数据，
 * 另一个线程 则向其中写入数据，利用互斥锁来对共享的缓冲区进行访问控制。
 *
 *
 * */
void * readfun(void *arg);
void * writefun(void *arg);


char buffer[256];// 共享的缓冲区


int buffer_has_item = 0;// 缓冲区没有东西

int retflag = FALSE;

pthread_mutex_t mutex;// 互斥锁


int main(void)
{
    pthread_t reader;
    // 初始化互斥锁
    pthread_mutex_init(&mutex,NULL);



    pthread_create(&reader,NULL,readfun,NULL);

    writefun(NULL);


    pthread_mutex_destroy(&mutex);
     return 0;
}


void *readfun(void *arg)
{
    while(1){
        if(retflag){
            return NULL;
        }// return

        pthread_mutex_lock(&mutex);// 加锁

        // 其实buffer_has_item & buffer这2个变量都是需要互斥访问的,
        // 所以需要加锁。
        if(1 == buffer_has_item ){// 如果有东西
             printf("%s\n",buffer);// 消费
             buffer_has_item = 0; // 置空
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// 主线程写数据,读写是严格交替执行
void * writefun(void *arg)
{

    int i = 0;
    while(1){

        if(10 == i){
             retflag = TRUE;
             return NULL;
        }
        pthread_mutex_lock(&mutex);
        if(0 == buffer_has_item){
             sprintf(buffer,"This is %d\n",i++);
             buffer_has_item = 1;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

