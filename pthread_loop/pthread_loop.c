#include<stdio.h>
#include<pthread.h>
#include<string.h>

void * func(void *arg)
{
    int i = *(int *)arg;
    printf("当前计数器的值是%d\n",i);
    return NULL;
}

void * func1(void *arg)
{
    int i = *(int *)arg;
    printf("当前计数器的值是%d\n",i);
    return NULL;
}

void * func2(void *arg)
{
    int i = *(int *)arg;
    printf("当前计数器的值是%d\n",i);
    return NULL;
}
void * func3(void *arg)
{
    int i = *(int *)arg;
    printf("当前计数器的值是%d\n",i);
    return NULL;
}
void * func4(void *arg)
{
    int i = *(int *)arg;
    printf("当前计数器的值是%d\n",i);
    return NULL;
}
int main()
{
    pthread_t tid[5];

    int arg[5] = {0};
    int i;
    for(i = 0; i< 5;++i){
        arg[i] = i;
        switch(i)
        {
            case 0:  pthread_create(&tid[i],NULL,func,(void *)&arg[i]);break;
            case 1:  pthread_create(&tid[i],NULL,func2,(void *)&arg[i]);break;
            case 2:  pthread_create(&tid[i],NULL,func2,(void *)&arg[i]);break;
            case 3:  pthread_create(&tid[i],NULL,func3,(void *)&arg[i]);;break;
            case 4:  pthread_create(&tid[i],NULL,func4,(void *)&arg[i]);break;
        }
    }
    //sleep(1);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    pthread_join(tid[4],NULL);
    return 0;
}
