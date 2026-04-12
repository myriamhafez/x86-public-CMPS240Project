#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int
wildcard(char *pattern, char *name){
if(*pattern == '\0') return *name== '\0';

if(*pattern == '*'){

do{
if(wildcard(pattern+1, name)) return 1;
}
while(*name++ != '\0');
}

if(*pattern == *name) return wildcard(pattern+1, name+1);

return 0;
}


char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path, char *pattern)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
	 if(de.inum == 0)
        continue;
	if(pattern && !wildcard(pattern, de.name)){
	 continue;
	}
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;
  if(argc < 2){
    ls(".", 0);
    exit();
  }
  for(i=1; i<argc; i++){
	if(strchr(argv[i], '*')) ls(".", argv[i]);
	else
   	 ls(argv[i], 0);
	}
  exit();
}
