#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void tree(char *path){
  int fd;
  struct dirent de;
  struct stat st;
  char fileName[512];
  char *p;

  if((fd = open(path, 0)) < 0){
    printf("cannot open %s\n", path);
    return;
  }

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;

    char name[DIRSIZ+1];
    memmove(name, de.name, DIRSIZ);
    name[DIRSIZ] = 0;

    if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
      continue;

    strcpy(fileName, path);
    p = fileName + strlen(fileName);
    *p++ = '/';

    memmove(p, name, strlen(name));
    p[strlen(name)] = 0;

    if(stat(fileName, &st) < 0)
      continue;

    printf("%s\n", fileName);

    if(st.type == T_DIR)
      tree(fileName);
  }

  close(fd);
}

int main(int argc, char *argv[]){
  printf("tree getting started\n");

  if(argc < 2)
    tree(".");
  else
    tree(argv[1]);

  exit();
}
