#include<pthread.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

#define handle_error_en(en,msg)\
    do{errno = en; perror(msg);exit(EXIT_FAILURE);} while(0)


static int done = 0;
static int cleanup_pop_arg = 0;
static int cnt = 0;


static void
cleanup_handler(void *arg)
{
     printf("Called clean-up handler\n");
     cnt  = 0;// cnt 被清 0
}


static void *
thread_start(void *arg)
{
    time_t start,curr;
    printf("New thread started\n");

    pthread_cleanup_push(cleanup_handler,NULL);


    curr = start = time(NULL);
    while(!done){
         pthread_testcancel(); /* A cancellation point*/
         if(curr < time(NULL)){// 每隔1s，打印cnt
             curr = time(NULL);
             printf("cnt = %d\n",cnt); /* A cancellation point*/
             cnt++;
         }
    }
    pthread_cleanup_pop(cleanup_pop_arg);// pthread_cleanup_pop(0)将不会调用cleanup_handler
    printf("xxxxxxx\n");
    return NULL;
}


int main(int argc,char *argv[])
{
    pthread_t thr;
    int s;
    void *res;


    s = pthread_create(&thr,NULL,thread_start,NULL);
    if(0 != s)
        handle_error_en(s,"pthread_create");

    sleep(2);// allow new thread to run a while

    if(argc > 1){// 2个及2个以上参数
        if(argc > 2) // 3个及3个以上参数
            cleanup_pop_arg = atoi(argv[2]);
        done = 1;
    }else{ // 1个参数
        printf("Cancelling thread\n");
        s = pthread_cancel(thr);// cancel thr
        if(0 != s)
            handle_error_en(s,"pthread_cancel");
    }


    s = pthread_join(thr,&res);
    if(0 != s)
        handle_error_en(s,"pthread_join");
    if(res == PTHREAD_CANCELED)
        printf("Thread was cancelled;cnt = %d \n",cnt);
    else
        printf("Thread terminated normally;cnt = %d\n",cnt);
    exit(EXIT_SUCCESS);
}
