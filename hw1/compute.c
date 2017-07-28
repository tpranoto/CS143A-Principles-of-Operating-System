//CS143A - FALL 2015
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE * f = stdin;
  if (f==NULL)
  {
    printf("Failed to open file!\n");
    exit(1);
  }

  float sum=0;
  int count=0;
  float num;
  float max=0;
  float min=9999999;

  while (!feof(f))
  {
    fscanf(f,"%f\n",&num);
    sum+=num;
    count++;
    if(max<num)
	max=num;
    if(min>num)
	min=num;
  }

  if (count==0)
  {
    printf("No numbers found in file!\n");
    exit(3);
  }

  printf("max: %f\nmin: %f\naverage: %.2f\n", max, min,(sum/count));

  return 0;


}
