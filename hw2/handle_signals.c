//CS143A HW2
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
struct sigaction act;
void sig_handler(int signum,siginfo_t *info,void *ptr)
{
  static int inter=0,quit=0,stop=0;
  if(signum==2){
	printf("I");
	++inter;
  }
  if(signum==3){
	printf("Q");
	++quit;
  }
  if(signum==20){
	printf("S");
	++stop;
	if(stop==3){
	  printf("\nInterrupt: %d\nStop: %d\nQuit: %d\n",inter,stop,quit);
	  exit(0);
	}
  }
}
int main()
{
  setvbuf(stdout,NULL,_IONBF,0);
  memset(&act,0,sizeof(act));

  act.sa_sigaction = sig_handler;
  act.sa_flags =SA_SIGINFO;

  sigaction(SIGINT, &act,NULL);
  sigaction(SIGQUIT,&act,NULL);
  sigaction(SIGTSTP,&act,NULL);


  while(1)
     sleep(1);
}
