#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int compare(char *f1, char *f2){
struct dirent de;
struct stat st1;
struct stat st2;


int fd1 = open(f1, O_RDONLY);
int fd2 = open(f2, O_RDONLY);

if(fd1 < 0){
printf(1,"cannot open %s\n", f1);
return;
}

if(fd2 < 0){
printf(1,"cannot open %s\n", f2);
return;
}

  if(fstat(fd1, &st1) < 0){
    printf(1, "cannot stat %s\n", f1);
    close(fd1);
    return;
  }
  if(fstat(fd2, &st2) < 0){
    printf(1, "cannot stat %s\n", f2);
    close(fd2);
    return;
  }
struct fileID1{
st1.st_dev;
st1.st_ino;
}
struct fileID2{ 
st2.st_dev;
st2.st_ino;
}

if(fileID1 == fileID2){
printf(1, "comparing same file. No differences exist.\n");
return;
}

}
