//CS143a HW3 Part2
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc , char** argv){
  int count;
  if(argc<2)
    count=10;
  else
    count=atoi(argv[1]);

  pid_t pid,pida,pidb;
  int i;
  for(i=0;i<count;++i){
    if((pidb=fork())>0){
      waitpid(pidb);
      if((pida=fork())>0){
        waitpid(pida);  
        if((pid=fork())>0){
          waitpid(pid);
          printf("D");
          fflush(stdout);
	  return;
        }
        else if(pid<0){
          printf("Forking failed!");
          exit(1);
        }
        else{
          printf("C");
          fflush(stdout);
        }
        return;
     }
     else if(pida<0){
       printf("Forking failed!");
       exit(1);
     }
     else{
       printf("B");
       fflush(stdout);
     }
     return;
   }
   else if(pidb<0){
     printf("Forking failed!");
     exit(1);
   }
   else{
     printf("A");
     fflush(stdout);
   } 
  } 
  return 0;
}
