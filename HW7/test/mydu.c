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

        switch (filestat.st_mode & S_IFMT)
        {
        case S_IFDIR:
        {
            if (strcmp (".", d_file->d_name) && strcmp ("..", d_file->d_name))
            {
                printf("File: %s\nSize: %d\n\n", abPath, filestat.st_size);

                //Add slack space to the final sum
                int slack=sectorSize-(filestat.st_size%sectorSize);

                totalFilesSize+=filestat.st_size+slack;

                readDir(abPath);
            }
            break;
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

    sectorSize=info.f_bsize; //Setting global variable

    uint64_t usedBytes=(info.f_blocks-info.f_bfree)*info.f_bsize;

    readDir(argv[1]);

    printf("Total blocks: %d\nFree blocks: %d\nSize of block: %d\n\
Size in bytes: %d\nTotal Files size: %d\n",
            info.f_blocks, info.f_bfree, info.f_bsize, usedBytes, totalFilesSize);

    return 0;
}