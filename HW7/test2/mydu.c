#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

//The amount of bytes of all files found
uint64_t totalFilesSize=0;

//Size for a sector in the fs
unsigned int sectorSize=0;

void readDir(char *path) {
    DIR *directory;
    struct dirent *d_file;  // a file in *directory

    directory = opendir (path);

    while ((d_file = readdir (directory)) != 0)
    {
        struct stat filestat;
        char *abPath=malloc(1024);
        memset(abPath, 0, 1024);
        strcpy(abPath, path);
        strcat(abPath, "/");
        strcat(abPath, d_file->d_name);

        lstat (abPath, &filestat);

        if(S_ISDIR(filestat.st_mode))
        {
            if (strcmp (".", d_file->d_name) && strcmp ("..", d_file->d_name))
            {
                printf("%d\t%s\n", filestat.st_size, abPath);

                totalFilesSize+=filestat.st_blocks;

                readDir(abPath);
            }
            
        }


        free(abPath);
    }

    closedir (directory);
}

int main (int argc, char **argv) {

    if(argc!=2) {
        printf("Error: Missing required parameter.\n");
        return -1;
    }

    struct statvfs info;
    statvfs (argv[1], &info);

    readDir(argv[1]);
    return 0;
}