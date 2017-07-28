//CS143a HW4
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

double ave,sum=0;
int min=INT_MAX, max=INT_MIN;
int size=0,i=0;
double num[1001];
void *calc(void *arg);

int main(int argc, char** argv){
  pthread_t com1,com2,com3;
  int temp;
  FILE * f = stdin;
  if (f==NULL)
  {
    printf("Failed to open file!\n");
    exit(1);
  }
  while (!feof(f))
  {
    fscanf(f,"%d\n",&temp);
    num[size]=temp;
    size++;
  }
  
  if(size==0){
    printf("No numbers found in file!\n");
    exit(2);
  }

  int param=size/4;
  int mod=size%4;
   
  int first=0,second=0,third=0;
    
  if(mod==1){
    ++first;
  }
  else if(mod==2){
    ++first;
    ++second;
  }
  else if(mod==3){
    ++first;
    ++second;
    ++third;
  }

  first+=param;
  second+=first+param;
  third+=second+param;

  pthread_create(&com1,NULL,calc,(void *)first);
  pthread_create(&com2,NULL,calc,(void *)second);
  pthread_create(&com3,NULL,calc,(void *)third);

  pthread_join(com1,NULL);
  pthread_join(com2,NULL);
  pthread_join(com3,NULL);
   
  int k;
  for(k=third;k<size;++k){
    sum+=num[k];
    if(num[k]<min)
      min=num[k];
    if(num[k]>max)
      max=num[k];
  }

  ave=sum/size;
  printf("max:%d\nmin:%d\naverage:%.2f\n", max, min,ave);
  pthread_exit(NULL);
}

void *calc(void *arg){
  int ar=(int )arg;
  int j;
  for(j=i;j<ar;++j){
    sum+=num[j];
    if(num[j]<min)
      min=num[j];
    if(num[j]>max)
      max=num[j];
    ++i;
  }
  pthread_exit(NULL);
}
