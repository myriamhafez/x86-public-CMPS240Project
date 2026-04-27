#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void tree(char *path, char *fileName){
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

if(de.name == fileName)

 printf(1, "%s found \n", fileName);

 else
      tree(fileName);
 }

  close(fd);
}

int main(int argc, char *argv[]){
  if(argc != 2)
    printf(1, "please use find <filename> format.");
  else
    tree(argv[1]);
  exit();
}
