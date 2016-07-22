#include<stddef.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *print_msg(void *ptr);



int main ()
{
    pthread_t thread1,thread2;

    int i,j;


    void *retval;

    char *msg1 = "This is thread 1\n";
    char *msg2 = "This is thread 2\n";
    pthread_create(&thread1,NULL,print_msg,(void *)msg1);
    pthread_create(&thread2,NULL,print_msg,(void *)msg2);
    pthread_join(thread1,&retval);
    pthread_join(thread2,&retval);

    return 0;
}


void *print_msg(void *ptr)
{
     char *p = (char *)ptr;
    int i;
    for(i = 0;i<10;i++){
         printf("%s\n",p);
    }
}
