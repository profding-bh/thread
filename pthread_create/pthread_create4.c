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



int main(){

extern    int errno;
    errno = 0; // 在使用之前，先初始化为0
    errno = pthread_create(&ntid,NULL,thr_fn,NULL);
    if(0 != errno){
         printf("can't create thread:%s \n",strerror(errno));
    }
    printids("main thread:");
     
	//  进程先退出，新线程也会立即退出，系统清除所有资源。
    //  所以，新线程 根本没有机会打印输出 new thread:
 
    return 0;// 结束整个进程。
}
