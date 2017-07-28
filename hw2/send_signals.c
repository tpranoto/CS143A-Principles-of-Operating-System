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
  static int count=0;
  if(signum==2){
	printf("Signals: %d",count);
	exit(0);
  }
  if(signum==SIGUSR1){
	++count;
  	kill(info->si_pid,SIGUSR2);
  }
}

int main()
{
  setvbuf(stdout,NULL,_IONBF,0);
  memset(&act,0,sizeof(act));

  act.sa_sigaction = sig_handler;
  act.sa_flags =SA_SIGINFO;

  sigaction(SIGINT, &act,NULL);
  sigaction(SIGUSR1, &act,NULL);

  while(1)
     sleep(1);
}
