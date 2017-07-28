//CS143a HW6
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <stdlib.h>

int now[5][5],maxNeed[5][5],avail[5];
int alloc[5]={0, 0, 0, 0, 0};
int maxCla[5], running[5];
int safe =0,count=0,exec,temp;

int main(){
  int process, resource,count1=0,count2=0;

  printf("\nNumber of Processes: ");
  scanf("%d",&process);
  int i;
  for(i=0;i<process;++i){
    running[i]=1;
    ++count;
  }
  
  printf("\nNumber of Resources: ");
  scanf("%d",&resource);
  
  printf("\nNumber of Available resources: ");

  for(i=0;i<resource;++i){
    scanf("%d",&temp);
    maxCla[i]=temp;
  }
  printf("\n");
  printf("\nNumbers of allocated:\n");
  
  int j;
  for(i=0;i<process;++i){
    for(j=0;j<resource;++j){
      scanf("%d",&temp);
      now[i][j]=temp;
    }
  }

  printf("\nNumbers of MaxNeed :\n");
  
  for(i=0;i<process;++i){
    for(j=0;j<resource;++j){
      scanf("%d",&temp);
      maxNeed[i][j]=temp;
    }
  }    
  
  printf("\nAvailable resources:\n");
  for(i=0;i<resource;++i){
    printf(" %d",maxCla[i]);
  }
  printf("\n");
  printf("\nAllocated:\n");
  for(i=0;i<process;++i){
    for(j=0;j<resource;++j){
      printf(" %d",now[i][j]);
    }
    printf("\n");
  }
  
  printf("\nMax Need:\n");
  for(i=0;i<process;++i){
    for(j=0;j<resource;++j){
      printf(" %d", maxNeed[i][j]);
    }
    printf("\n");
  }
  for(i=0;i<process;++i){
    for(j=0;j<resource;++j){
      alloc[j]+=now[i][j];
    }
  }
  
  printf("\nTotal Resources Used:\n");
  for(i=0;i<resource;++i){
    printf(" %d", alloc[i]);
  }
  for(i=0;i<resource;++i){
    avail[i]=maxCla[i]-alloc[i];
  }
  
  printf("\nAvailable Resources Left:\n");
  for(i=0;i<resource;++i){
    printf(" %d",avail[i]);
  }
  printf("\n");
  
  while(count!=0){
    safe=0;
    for(i=0;i<process;++i){
      if(running[i]){
        exec=1;
        for(j=0;j<resource;++j){
          if(maxNeed[i][j]-now[i][j] > avail[j]){
            exec=0;
            break;
          }
        }
        if(exec){
          printf("\nProcess%d is executing\n",i+1);
          running[i]=0;
          --count;
          safe=1;
          for(j=0;j<resource;++j)
            avail[j]+=now[i][j];
          break;
        }
      }
    }
    if(!safe){
      printf("\aThe system is in an unsafe state\n");
      break;
    }
    else{
      printf("Available resources:");
      for(i=0;i<resource;++i)
        printf(" %d",avail[i]);
      printf("\n");
    }
   
  }
  if(safe)
    printf("\nThe system is in a safe state\n");
}
