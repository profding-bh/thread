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

	sleep(1);////使得主线程先退出 
    printids("new thread:");
    return  ((void *)0);
}


/* Terminate calling thread. 

   The registered cleanup handlers are called via exception handling
   so we cannot mark this function with __THROW.*/
// extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));

void *thr_fn2(void *arg){
    printids("跟\n");
    return  ((void *)0);
}


int main(){

extern    int errno;
    errno = 0; // 在使用之前，先初始化为0
    errno = pthread_create(&ntid,NULL,thr_fn,NULL);
    if(0 != errno){
         printf("can't create thread:%s \n",strerror(errno));
    }
    printids("main thread:");
     
	pthread_exit(NULL);
   //如果主线程调用了pthread_exit，那么它退出了，子线程也不会退出。
	printf("我会执行吗\n");// 主线程不会执行这句代码

    thr_fn2(NULL);//不会再有线程，执行这个函数，因为，主线程已经退出了。

/*
  在main函数中，调用pthread_exit只会使主线程退出，而进程并没有退出。
所以，子线程可以继续运行，直到结束。
*/
    return 0;// 结束整个进程。
}
