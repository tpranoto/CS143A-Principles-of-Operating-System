//CS143a HW7
//Timothy Pranoto
//38964311

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int printdir(char* path, char* old) 
{
  struct stat stats;
  lstat(path, &stats);
  int size = stats.st_blocks/2;

    if (S_ISDIR(stats.st_mode)) {
      char newd[strlen(old)];
      if (path[0] == '/') 
	strcpy(newd, path);
      else {
	strcpy(newd, old);
	strcat(newd,  "/");
	strcat(newd, path);
      }
   
      chdir(newd);
      DIR *dir = opendir(newd);
      struct dirent *dp;

      while (dp = readdir(dir))
	if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) 
	  size += printdir(dp->d_name, newd);

      closedir(dir);
      chdir(old);

      if (path[0] == '/')
        printf("%d\t%s\n", size, path);
      else
        printf("%d\t%s/%s\n", size, old, path);
    }
  return size;
}

int main (int argc,char* argv[]) 
{	
  char pwd[100];
  getcwd(pwd);

  if(argc<1)
    printdir(".",pwd);
  else
    printdir(argv[1],pwd);
  return 0;
}
