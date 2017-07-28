//CS143a HW7
//Timothy Pranoto
//38964311

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>

#define files 200

int cmpfunc (const void * a, const void * b)
{
   return strcasecmp(*(char*const*)a,*(char*const*)b);
}

void printlist(char* fname, struct stat stats){

       printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
       printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
       printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
       printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
       printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
       printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
       printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
       printf( (stats.st_mode & S_IROTH) ? "r" : "-");
       printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
       printf( (stats.st_mode & S_IXOTH) ? "x " : "- ");
       printf("%d ",stats.st_nlink);
          
       printf("%s ",getpwuid(stats.st_uid)->pw_name);
       printf("%s ",getgrgid(stats.st_gid)->gr_name);
       printf("\t%d ",stats.st_size);
        
       
       struct tm * info= localtime(&(stats.st_mtime));
       char *month;
       switch(info->tm_mon){
         case 0:
	   month="Jan";
           break;
	 case 1:
	   month="Feb";
           break;
	 case 2:
	   month="Mar";
           break;
	 case 3:
	   month="Apr";
           break;
         case 4:
	   month="May";
           break;
         case 5:
	   month="Jun";
           break;
	 case 6:
	   month="Jul";
           break;
	 case 7:
	   month="Aug";
           break;
	 case 8:
	   month="Sep";
           break;
	 case 9:
	   month="Oct";
           break;
	 case 10:
	   month="Nov";
           break;
	 case 11:
	   month="Dec";
           break;
       }
       printf("\t%s ",month);
       if((info->tm_mday/10)==0)
	 printf(" %d",info->tm_mday);
       else
	 printf("%d",info->tm_mday);

       if(1900+info->tm_year!=2015)  
         printf("  %d",1900+info->tm_year);
       else
	 printf(" %d:%d",info->tm_hour,info->tm_min);
       printf(" %s\n",fname);
}

void printdir(char *dir)
{
    DIR *dp;
    struct stat stats[files];
    struct stat temp;
    char *fnames[files];
    int total=0,n=0;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }

    while(1){
	struct dirent *entry;
	if((entry = readdir(dp))==NULL)
	  break;
        if(strcmp(".",entry->d_name) !=0 && strcmp("..",entry->d_name)!=0){
          fnames[n]=entry->d_name;
          ++n;
        }
    }
    qsort(fnames,n,sizeof(char *), cmpfunc);
    printf("\n%s:\n",dir);
    int i;
    for(i=0;i<n;++i){
      char path[100];
      strcpy(path,dir);
      strcat(path,"/");
      strcat(path,fnames[i]);

      if(stat(path,&temp)==-1){
        fprintf(stderr," stat failed\n");
	exit(1);
      }
      total+=(temp.st_blocks/2);
      stats[i]=temp;
    }
    
    printf("total %d\n",total);
     
    for(i=0;i<n;++i){
      printlist(fnames[i],stats[i]);
    }
    
    for(i=0;i<n;++i){
      if(S_ISDIR(stats[i].st_mode)){
	char path[100];
	strcpy(path,dir);
        strcat(path,"/");
        strcat(path,fnames[i]);
        printf("\n");
        printdir(path);
      }
    }

    closedir(dp);
}
int main(int argc, char* argv[])
{
    char *topdir, pwd[2]=".";
    if (argc != 2)
        printdir(".");
    else
        printdir(argv[1]);
    return 0;
}
