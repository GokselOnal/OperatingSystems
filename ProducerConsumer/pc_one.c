#include <sys/time.h>
#include <stdio.h>
#include <pthread.h> 
#include <errno.h>

pthread_mutex_t region_mutex = PTHREAD_MUTEX_INITIALIZER;

int b;  /* buffer size = 1; */
 
main()  
{
  pthread_t producer_thread; 
  pthread_t consumer_thread; 
  void *producer();
  void *consumer();
  
  pthread_create(&consumer_thread,NULL,consumer,NULL);
  pthread_create(&producer_thread,NULL,producer,NULL);
  pthread_join(consumer_thread,NULL);
  printf("done!\n");
}

void add_buffer(int i){
  b = i;
  printf("put %d -",i);
}

int get_buffer(){
  return b ;
}
 
void *producer()
{
 int i = 0;
 printf("I'm a producer\n");
 //while (1) {
for( ; i < 12; ){
   pthread_mutex_lock(&region_mutex);
   add_buffer(i);
   pthread_mutex_unlock(&region_mutex);
   i = i + 1;
   sleep(1);
 }
 pthread_exit(NULL);
}

void *consumer()
{
 int i,v;
 printf("I'm a consumer\n");
 for (i=0;i<10;i++) {
   pthread_mutex_lock(&region_mutex);
   v = get_buffer();
   pthread_mutex_unlock(&region_mutex);
   printf("got %d  ",v);
   sleep(1);
 }
 pthread_exit(NULL);

}

