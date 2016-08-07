#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


/*
 *  需要验证2件事
 *
 *  1)每个线程都有一个errno的副本
 *   从3个线程errno地址的不同，我们可以得出结论：每个线程都有一个errno的副本
 *
 *  2）创建线程时，传递多个参数，通过结构来实现。
 */


struct  param_str{
    int a;
    int b;

};


void *func1(void *arg){

	extern int errno;
	printf(" thread 1  errno address is %p\n",&errno);//0x7f6df507b660
    struct param_str * para = ( struct param_str *)arg;
    //int errno;
    int err;
     printf("参数之和为%d\n",para->a + para->b);
    err = errno;
    printf("thread 1 errno is %d\t,error string is %s\n",err,strerror(err));
    return NULL;
}

void *func2(void *arg){
	extern int errno;
	printf(" thread 2  errno address is %p\n",&errno);//0x7f6df487a660
    struct param_str * para = ( struct param_str *)arg;
    int err;
    printf("参数之积为%d\n",para->a * para->b);
    err = errno;
    printf("thread 2 errno is %d\t,error string is %s\n",err,strerror(err));
    return NULL;
}


int main(void){

    pthread_t  tid1,tid2;

    pthread_attr_t  tid1_attr,tid2_attr; //线程属性

	extern int errno;
	
	printf("main thread errno address is %p\n",&errno);//0x7f6df58636a0

    struct  param_str param1,param2;

 
	// initialize params
    param1.a = 1;
    param1.b = 2;

    param2.a = 3; 
    param2.b = 4;

	// initialize  thread attr
	pthread_attr_init(&tid1_attr);
    pthread_attr_init(&tid2_attr);

	// 从这里我们可以得出结论：
	// pthread_create()时，线程属性需要初始化，参数需要初始化。

 
    // errno = pthread_create(&tid1,NULL /*&tid1_attr*/,func1,(void *)&param1);
	errno = 0;
    errno = pthread_create(&tid1,&tid1_attr,func1,(void *)&param1);
    if(0 != errno){
         printf("创建线程1失败:主线程 errno is %d\t %s\n",errno,strerror(errno));
    }

   errno = 0;
   errno = pthread_create(&tid2, &tid2_attr,func2,(void *)&param2);// -->不能创建成功，遗留问题????
// 终于解决这个问题了。
// errno = pthread_create(&tid2, NULL,func2,(void *)&param2);
    if(0 != errno){
         printf("创建线程2失败:主线程 errno is %d\t %s\n",errno,strerror(errno));
    }

	errno = 0;
	errno = pthread_equal(tid1,tid2);
	// strerror在string.h中
	// pthread_equal
    // 不相等 ,返回0（1）
	// 相等,返回 非0
	// 尽管这个函数是反逻辑的 ，但是很合理。
	printf("tid1 and tid2 is equal  %d, %s\n",errno,strerror(errno));



	errno = 0;
	errno = pthread_equal(tid1,tid1);
	printf("tid1 and tid1 is equal  %d, %s\n",errno,strerror(errno));



	// deinitialize thread attr
	pthread_attr_destroy(&tid1_attr);
	pthread_attr_destroy(&tid2_attr);
   
    while(1){
          // 此处暂停，观察。
	}
    return 0;
}



