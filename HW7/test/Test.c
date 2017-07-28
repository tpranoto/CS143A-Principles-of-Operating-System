#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>
/* limits.h defines "PATH_MAX". */
#include <limits.h>

/* List the files in "dir_name". */

int is_directory_we_want_to_list(const char *parent, char *name) {
  struct stat st_buf;
  if (!strcmp(".", name) || !strcmp("..", name))
    return 0;
  char *path = alloca(strlen(name) + strlen(parent) + 2);
  sprintf(path, "%s/%s", parent, name);
  stat(path, &st_buf);
  return S_ISDIR(st_buf.st_mode);
}

int list(const char *name) {
  DIR *dir = opendir(name);
  struct dirent *ent;
  while (ent = readdir(dir)) {
    char *entry_name = ent->d_name;
    printf("%s\n", entry_name);
    if (is_directory_we_want_to_list(name, entry_name)) {
      // You can consider using alloca instead.
      char *next = malloc(strlen(name) + strlen(entry_name) + 2);
      sprintf(next, "%s/%s", name, entry_name);
      list(next);
      free(next);
    }
  }
  closedir(dir);
}

int main ()
{
    list("/var/www");
    return 0;
}