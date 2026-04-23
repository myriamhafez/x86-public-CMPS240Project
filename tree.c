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
    printf(1, "cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(1, "cannot stat %s\n", path);
    close(fd);
    return;
  }

  if(st.type != T_DIR){
    printf(1, "%s is not a directory\n", path);
    close(fd);
    return;
  }

  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(fileName)){
    printf(1, "path too long\n");
    close(fd);
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
    strcpy(p, name);

    if(stat(fileName, &st) < 0){
      printf(1, "cannot stat %s\n", fileName);
      continue;
    }

    printf(1, "	  %s\n", fileName);

    if(st.type == T_DIR)
      tree(fileName);
  }

  close(fd);
}

int main(int argc, char *argv[]){
  if(argc < 2)
    tree(".");
  else
    tree(argv[1]);
  exit();
}
