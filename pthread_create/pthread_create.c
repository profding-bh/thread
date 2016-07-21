#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


/*
 *  需要验证2件事
 *
 *  1)每个线程都有一个errno的副本
 *
 *  2）创建线程时，传递多个参数，通过结构来实现。
 */


struct  param_str{
    int a;
    int b;

};
void *func1(void *arg){

    struct param_str * para = ( struct param_str *)arg;
    //int errno;
    int err;
     printf("参数之和为%d\n",para->a + para->b);
    err = errno;
    printf("thread 1 errno is %d\t,error string is %s\n",err,strerror(err));
    return NULL;
}

void *func2(void *arg){

    struct param_str * para = ( struct param_str *)arg;
    int err;
    printf("8888888888参数之积为%d\n",para->a * para->b);
    err = errno;
    printf("thread 2 errno is %d\t,error string is %s\n",err,strerror(err));
    return NULL;
}


int main(void){

    pthread_t  tid1,tid2;
    pthread_attr_t  tid1_attr,tid2_attr;
    struct  param_str param1,param2;

    int err =  0;
    param1.a = 1;
    param1.b = 2;
    param2.a = 3;
    param2.b = 4;


  //:  int errno;
    errno = pthread_create(&tid1,NULL /*&tid1_attr*/,func1,(void *)&param1);
    if(0 != errno){
         err  = errno;
         char *msg = strerror(err);
         printf("创建线程1失败:主线程 errno is %d\t %s\n",err,msg);
    }
  errno = pthread_create(&tid2, &tid2_attr,func2,(void *)&param2);
    if(0 != errno){
         err  = errno;
         char *msg = strerror(err);
         printf("创建线程2失败:主线程 errno is %d\t %s\n",err,msg);
    }
    while(1){
	}
    return 0;
}



