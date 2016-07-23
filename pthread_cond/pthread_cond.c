#include<stdio.h>
#include<pthread.h>


#define BUFFER_SIZE 4
#define OVER (-1)


struct producers // 定义生产者条件变量结构
{

    int buffer[BUFFER_SIZE];// 定义缓冲区
    pthread_mutex_t lock;// 访问缓冲区的 互斥锁

    int readpos,writepos;// 读写的位置
    pthread_cond_t notempty;// 缓冲区有数据的标志(包括不满，和满这种特殊状态)
    pthread_cond_t notfull;// 缓冲区未满的标志(包含不满，以及为空这种特殊状态)
};

//
// 初始化缓冲区
void init(struct producers *b ){


    pthread_mutex_init(&b->lock,NULL);
    pthread_cond_init(&b->notempty,NULL);
    pthread_cond_init(&b->notfull,NULL);

    b->readpos = 0;
    b->writepos = 0;
}

// 放入一个整数
void put(struct producers *b,int data)
{
     pthread_mutex_lock(&b->lock);

     // 当缓冲区满的时候，等待
     while((b->writepos + 1)% BUFFER_SIZE == b->readpos){
          pthread_cond_wait(&b->notfull,&b->lock);// 等待不满的信号
          // 在返回之前，pthread_cond_wait需要参数b->lock
          // 只要pthread_cond_wait返回，while循环就会结束，因为
          // 此时，缓冲区处于不满状态，所以while(条件)为假。
     }

     // 向缓冲区写入数据，并且指针后移
    b->buffer[b->writepos] = data;
    b->writepos++;
    if(b->writepos >= BUFFER_SIZE){
         b->writepos = 0;
    }// 从0开始

    pthread_cond_signal(&b->notempty);
    pthread_mutex_unlock(&b->lock);
}

// 从缓冲区读取数据,
int get(struct producers *b){

    int data;
    pthread_mutex_lock(&b->lock);
    // 当缓冲区没有数据时，等待
    while(b->writepos == b->readpos){
        pthread_cond_wait(&b->notempty,&b->lock);// 等待不空的信号
          // 只要pthread_cond_wait返回，while循环就会结束，因为
          // 此时，缓冲区处于 不空状态，所以while(条件)为假。
     }

    data = b->buffer[b->readpos];
    b->readpos++;
    if(b->readpos >= BUFFER_SIZE){
         b->readpos = 0;
    }

    pthread_cond_signal(&b->notfull);// 发送缓冲区未满信号,因为在这之前，
    // 已经读取了信息，所以当然不满。
    pthread_mutex_unlock(&b->lock);
    return data;
}

struct producers buffer;

// 生产者
void *producer(void *data)
{
    int n;
    for(n = 0;n<10;++n){
        printf("Producer: %d-->\n",n);
        put(&buffer,n);
    }
    put(&buffer,OVER);// 这句干嘛？
    return NULL;
}


// 消费者
void *consumer(void *data){


    int d;
    while(1){
         d = get(&buffer);// 获取数据
         if(d == OVER)
         {
              break;
         }
         printf("Consumer: --> %d\n",d);
    }
    return NULL;
}



int main()
{
    pthread_t tha,thb;

    void *retval;

    init(&buffer);

    pthread_create(&tha,NULL,producer,0);
    pthread_create(&thb,NULL,consumer,0);
    pthread_join(tha,&retval);
    pthread_join(thb,&retval);
    return 0;
}
