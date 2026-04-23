#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void  tree(char *path){
int fd;
struct dirent de;
struct stat st;
char fileName[512];
char *p;

fd = open(".", 0);

while(read(fd, &de, sizeof(de))){
if(de.inum == 0) continue;

if(strcmp(de.name, ".") || strcmp(de.name, "..")) continue;

strcpy(fileName, path);
p = fileName + strlen(path);
*p++ = '/';
memmove(p, de.name, DIRSIZ);
p[DIRSIZ] =0;

if(stat(fileName, &st) <0) continue;

printf("%s\n", fileName);

if(st.type == T_DIR) return tree(fileName);

}
close(fd);
}
int main(int argc, char *argv[]){
printf("%s", "tree getting started");
if(argc < 2)
tree(".");
else
tree(argv[1]);
exit();
}
