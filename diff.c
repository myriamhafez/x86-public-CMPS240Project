#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
 
#define MAX_LINE 512
int readline(int fd, char *buf, int max){
int i = 0, n;
char c;
while (i < max - 1){
n = read(fd, &c, 1);
if (n <= 0) break;
buf[i++] = c;
if (c == '\n') break;
}
buf[i] = '\0';
return i;
}
 
void compare(char *f1, char *f2){
struct stat st1, st2;
 
int fd1 = open(f1, O_RDONLY);
int fd2 = open(f2, O_RDONLY);
if(fd1 < 0){
printf(1, "cannot open %s\n", f1);
return;
}
if(fd2 < 0){
printf(1, "cannot open %s\n", f2);
close(fd1);
return;
}
 if(fstat(fd1, &st1) < 0){
printf(1, "cannot stat %s\n", f1);
close(fd1);
close(fd2);
return;
}
if(fstat(fd2, &st2) < 0) {
printf(1, "cannot stat %s\n", f2);
close(fd1);
close(fd2);
return;
}

if(st1.dev == st2.dev && st1.ino == st2.ino) {
printf(1, "diff: comparing same file. No differences exist.\n");
close(fd1);
close(fd2);
return;
}
char line1[MAX_LINE], line2[MAX_LINE];
int linenum = 0;
int differences = 0;
while(1){
int n1 = readline(fd1, line1, MAX_LINE);
int n2 = readline(fd2, line2, MAX_LINE);
linenum++;

if(n1 == 0 && n2 == 0)break;

if(n1 == 0){
printf(1, "%d: only in %s: %s", linenum, f2, line2);
differences++;
continue;
}

if(n2 == 0){
printf(1, "%d: only in %s: %s", linenum, f1, line1);
differences++;
continue;
}

if(strcmp(line1, line2) != 0){
printf(1, "%d > %s", linenum, line1);
printf(1, "%d > %s", linenum, line2);
differences++;
}
}
 
if(differences == 0) printf(1, "No differences found.\n");
 
close(fd1);
close(fd2);
}
 
int main(int argc, char *argv[]) {
if (argc != 3) {
printf(1, "Not enough parameters passed, please enter 2 files.\n");
exit();
}
compare(argv[1], argv[2]);
exit();
}
