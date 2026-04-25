
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void findKeyword(char fileName, char word){
int fd;
char lineBuf[1024];
char wordBuf[512];
int lineNum = 0;
ssize_t bytes;
int word_len = 0;
if((fd = open(fileName, O_RDONLY)) < 0){
printf(1, "failed to open %s\n", fileName);
return;
}

while((bytes = read(fd, lineBuf,sizeof(lineBuf))) > 0){
for(ssize_t i = 0; i < bytes; i++) {
char c = lineBuf[i];

if(c == '\n') lineNum++;
if(c  == ' '){

if(word_len > 0) {
wordBuf[word_len] == '\0';

if(strcmp(word, wordBuf) == 0){
printf(1, "%s found at line %d",word, lineNum );
}
word_len = 0;
} else {
if(word_len < 511){
wordBuf[word_len] = c;
}
}
}


}
}

close(fd);

}

int main(int argc, char argv[]){
if(argc !=  3){
printf(1, "please use format keyword <filename> <word>");
} else {
keyword(argv[2], argv[3]);
}
}
