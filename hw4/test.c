#include <pthread.h>
#include <stdio.h>


void* say(void *arg){
  printf("Hello, world!");
  return NULL;
}

int main(){
  pthread_t threads[2];
  int tn;
  for(tn=0;tn<2;++tn){
    pthread_create(&threads,NULL, say,NULL);
  }
  for(tn=0;tn<2;++tn){
    pthread_join(threads[tn], NULL);
  }
  return 0;
}
