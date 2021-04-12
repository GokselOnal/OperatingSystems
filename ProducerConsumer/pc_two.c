#include <sys/time.h>
#include <stdio.h>
#include <pthread.h> 
#include <errno.h>

int b;  /* buffer size = 1; */
int turn=0;
 
main()  
{
  pthread_t producer_thread; 
  pthread_t consumer_thread; 
  void *producer();
  void *consumer();

  pthread_create(&consumer_thread,NULL,consumer,NULL);
  pthread_create(&producer_thread,NULL,producer,NULL);
  pthread_join(consumer_thread,NULL);
}

void add_buffer(int i){
  b = i;
  printf("put %d -",b);
}

int get_buffer(){
  return b ;
}

void *producer()
{
 int i = 0;
 printf("I'm a producer\n");
 while (1) {
   while (turn == 1) ;
   add_buffer(i);
   turn = 1;
   i = i + 1;
 }
 pthread_exit(NULL);
}

void *consumer()
{
  int i,v;
  printf("I'm a consumer\n");
  for (i=0;i<20;i++) {
    while (turn == 0) ;
    v = get_buffer();
    turn = 0;
    printf("got %d  ",v);
  }
  pthread_exit(NULL);
}
