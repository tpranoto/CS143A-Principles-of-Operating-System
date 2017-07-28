//Timothy Pranoto
//38964311

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
  
  while(1){
    char* store[50];
    char command[100];
    printf("prompt> ");
    fflush(stdout);

    fgets(command, sizeof(command),stdin);
    if(feof(stdin))
      exit(0);
    char *pos;
    if((pos=strchr(command, '\n'))!=NULL)
      *pos ='\0';
    char* tok = strtok(command," ");
    
    int i = 0;
    while(tok!=NULL){
      store[i]=tok;
      tok = strtok(NULL," ");
      ++i;
    }
    store[i]=NULL;
    
    pid_t pid;
    int status;

    if((pid=fork())==0&& strncmp(store[0],"quit",4)!=0){
      execvp(store[0],store);
      printf("%s: Command not found.\n",store[0]);
      fflush(stdout);
      
    }
    else if(pid<0){
      perror("fork failed\n");
    }
    else{
      wait(&status);
      if(strncmp(store[0],"quit",4)==0)
        exit(0);
    }
  }
}
