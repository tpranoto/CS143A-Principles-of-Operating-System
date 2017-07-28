//CS143a HW4
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>


int count=0,max=INT_MIN,min=INT_MAX;
double sum=0;
pthread_mutex_t lock;

void * calc(void * arg);

int main(int argc, char** argv){
  pthread_t com1,com2,com3;
  
  pthread_mutex_init(&lock,NULL);
  pthread_create(&com1,NULL,calc,NULL);
  pthread_create(&com2,NULL,calc,NULL);
  pthread_create(&com3,NULL,calc,NULL);
  
  pthread_join(com1,NULL);
  pthread_join(com2,NULL);
  pthread_join(com3,NULL);
  
  FILE *f=stdin;
  if(f==NULL){
    printf("Failed to open file!\n");
    exit(2);
  }
  while(!feof(f)){
    pthread_mutex_lock(&lock);
    int temp;
    if(temp<min)
      min=temp;
    if(temp>max)
      max=temp;
    sum+=temp;
    ++count;
    pthread_mutex_unlock(&lock);
  }

  if(count==0){
    printf("No numbers found in file!\n");
    exit(1);
  }
  printf("max:%d\nmin:%d\naverage:%.2f\n",max,min,(sum/count));

  pthread_mutex_destroy(&lock);
  pthread_exit(NULL);
}

void *calc(void *arg){
  FILE * f= stdin;
  if(f==NULL){
    printf("Failed to open file!\n");
    exit(2);
  }
  while(!feof(f)){
    pthread_mutex_lock(&lock);
    int temp;
    fscanf(f,"%d\n",&temp);
    if(temp<min)
      min=temp;
    if(temp>max)
      max=temp;
    sum+=temp;
    ++count;
    pthread_mutex_unlock(&lock);
  }
  pthread_exit(NULL);
}
