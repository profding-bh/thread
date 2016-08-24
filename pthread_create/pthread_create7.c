#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


/* code snippet 1:

void* thrd_start_routine(void* v)
{
    sleep(10);
    printf("created thread\n");
}

int main()
{
        pthread_t thrdid;
                
        pthread_create(&thrdid, NULL, &thrd_start_routine, NULL);
        
        sleep(5);
        printf("main thread\n");        
        return  0;// 程序return,间接调用了exit（）函数。一个线程调用exit函数，会导致整个进程的退出。
}
*/


// code snippet 2:
/* 
在主线程退出时，要想系统并不回收进程的所有资源，可以调用pthread_exit()；然后等其他线程终止退出。
void* thrd_start_routine(void* v)
{
    sleep(10);
    printf("created thread\n");
}

int main()
{
        pthread_t thrdid;
                
        pthread_create(&thrdid, NULL, &thrd_start_routine, NULL);
        
        sleep(5);
        printf("main thread\n");    
		pthread_exit(NULL);// 主线程退出之后，过了5s：输出：created thread
		printf("main exit\n");  
        return  0;
}
*/

// code snippet 3:
// 验证：一个线程调用exit函数，会导致整个进程的退出。系统回收所有的资源，当然所有的线程都退出了。

/*
void* thrd_start_routine(void* v)
{
    printf("created thread\n");
	exit(1); //一个线程调用exit函数，会导致整个进程的退出。
}

int main()
{
        pthread_t thrdid;
                
        pthread_create(&thrdid, NULL, &thrd_start_routine, NULL);
        
        sleep(1);
        printf("main thread\n");   // 主线程还没有结束 
        return  0;
}
*/
// code snippet 4:

/*
编写程序完成如下功能：

1）有一int型全局变量g_Flag初始值为0；

2） 在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1

3） 在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2

4） 线程序1需要在线程2退出后才能退出

5） 主线程在检测到g_Flag从1变为2，或者从2变为1的时候退出

*/
int  g_Flag = 0; 

pthread_t thrdid1,thrdid2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;


void* thrd_start_routine(void* v)
{
	pthread_detach(pthread_self());

	pthread_mutex_lock(&mutex);
	if(g_Flag == 2)
		pthread_cond_signal(&cond);
    printf("This is  thread 1\n");
	g_Flag = 1;
	pthread_mutex_unlock(&mutex);


	pthread_join(thrdid2,NULL);// wait for thread 2;
	printf("thread 1 exit\n");
}

void* thrd_start_routine2(void* v)
{
	pthread_detach(pthread_self());

	pthread_mutex_lock(&mutex);
	if(g_Flag == 1)
		pthread_cond_signal(&cond);
    printf("This is  thread 2\n");
	g_Flag = 2;
	pthread_mutex_unlock(&mutex);

	printf("thread 2 exit\n");
}


int main()
{       
        pthread_create(&thrdid1, NULL, &thrd_start_routine, NULL);
        pthread_create(&thrdid2, NULL, &thrd_start_routine2, NULL);

		pthread_cond_wait(&cond,&mutex);

     	printf("init thread exit\n");
		pthread_exit(NULL);
		
        return  0;
}



/* Mutex initializers.  */

#if __PTHREAD_MUTEX_HAVE_ELISION == 1 /* 64bit layout.  */

#define __PTHREAD_SPINS 0, 0 // 逗号运算符

#elif __PTHREAD_MUTEX_HAVE_ELISION == 2 /* 32bit layout.  */

#define __PTHREAD_SPINS { 0, 0 }

#else

#define __PTHREAD_SPINS 0  // 既不是32位，也不是64位。

#endif



#ifdef __PTHREAD_MUTEX_HAVE_PREV

# define PTHREAD_MUTEX_INITIALIZER  { { 0, 0, 0, 0, 0, __PTHREAD_SPINS, { 0, 0 } } }

#else


# define PTHREAD_MUTEX_INITIALIZER { { 0, 0, 0, 0, 0, { __PTHREAD_SPINS } } }

#endif


/* Conditional variable handling.  */

#define PTHREAD_COND_INITIALIZER { { 0, 0, 0, 0, 0, (void *) 0, 0, 0 } }



/* Wait for condition variable COND to be signaled or broadcast.
   MUTEX is assumed to be locked before.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
//extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
//			      pthread_mutex_t *__restrict __mutex)
//   __nonnull ((1, 2));










