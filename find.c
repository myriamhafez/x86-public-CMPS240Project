#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void tree(char *path, char *fileName) {
    int fd;
    struct dirent de;
    struct stat st, childSt;
    char buf[512];
    char *p;
    int childFd;

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
  close(fd);
  return;
}

    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
        printf(1, "path too long\n");
        close(fd);
        return;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
            continue;
        if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if (strcmp(de.name, fileName) == 0 || strcmp(fileName, "*") == 0)
            printf(1, "%s\n", buf);
      
        childFd = open(buf, 0);
        if (childFd >= 0) {
            if (fstat(childFd, &childSt) == 0 && childSt.type == T_DIR)
          tree(buf, fileName);
            close(childFd);
        }
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc == 2)
        tree(".", argv[1]);
    else if (argc == 3)
        tree(argv[1], argv[2]);
    else
        printf(1, "usage: find <fileName> || find <dirName> <fileName>\n");

    exit();
}
