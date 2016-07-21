#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<errno.h>

pthread_t ntid;


void printids(const char *s)
{

    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %u tid %u (0x%x)\n",s,(unsigned int )pid,(unsigned int )tid,
            (unsigned int)tid);
}


void *thr_fn(void *arg){

    printids("new thread:");
    return  ((void *)0);
}



int main(){

extern    int errno;
    errno = 0;
    errno = pthread_create(&ntid,NULL,thr_fn,NULL);
    if(0 != errno){
         printf("can't create thread:%s \n",strerror(errno));
    }
/*
    int err;
    err = pthread_create(&ntid,NULL,thr_fn,NULL);
    if(0 != err){
         printf("can't create thread:%s \n",strerror(err));
    }
    */
    printids("main thread:");
     sleep(1);

     /*
      *
      * 为什么需要加sleep(1)?
      *
      * 首先这段代码需要处理主线程和子线程之间的竞争问题。
      * 首先是主线程必须休眠，如果主线程不休眠其就可能退出。
      * 这样新线程还没有运行，这个进程就可能已经终止了。如果你
      * 注释了sleep(1);发现整个进程直接退出。
      *
      * */
    return 0;
}
