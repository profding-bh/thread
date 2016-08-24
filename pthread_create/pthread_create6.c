#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<errno.h>

pthread_t ntid;

pthread_t ntidB;

void printids(const char *s)
{

    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %u tid %u (0x%x)\n",s,(unsigned int )pid,(unsigned int )tid,
            (unsigned int)tid);
}

void *thr_fn2(void *arg){
    
	sleep(3);// 让
	char *thread_name = (char *)arg;
	char logname[100]= "线程名字:";
    printids(strcat(logname,thread_name));
    return  ((void *)0);
}


/* Append SRC onto DEST.  */
//extern char *strcat (char *__restrict __dest, const char *__restrict __src)
//     __THROW __nonnull ((1, 2)); 
// strcat返回的就是__dest


void *thr_fn(void *arg){

	sleep(1);// 让
	char *thread_name = (char *)arg;
	char logname[100]= "线程名字:";
	
	printf("logname: %p\n",logname);

	char *p = strcat(logname,thread_name);
	
	printf("p:%p\n",p);// p 和 logname是一样的。

    printids(p);


	extern   int errno;
    errno = 0; 
    errno = pthread_create(&ntidB,NULL,thr_fn2,"B"); // 看到没有子线程里面又可以创建新的子线程。
    if(0 != errno){
         printf("can't create thread B :%s \n",strerror(errno));
    }
    return  ((void *)0);
}

int main(){

	extern   int errno;
    errno = 0; 
    errno = pthread_create(&ntid,NULL,thr_fn,"A");
    if(0 != errno){
         printf("can't create thread A:%s \n",strerror(errno));
    }
    printids("main thread:");
     
	pthread_exit(NULL);

	printf("我会执行吗\n");// 主线程不会执行这句代码
    return 0;// 结束整个进程。
}
