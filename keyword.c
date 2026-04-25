
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char findKeyword(char fileName, char word){
int fd;
char lineBuf[1024];
int lineNum = 0;
if((fd = open(fileName, O_RDONLY)) < 0){
printf(1, "failed to open %s\n", fileName);
return;
}

FILE *fp = fdopen(fp, "r");
if(!fp) return;

while(fgets(lineBuf, sizeof(lineBuf), fp)){
lineNum++;

char *token = strtok(lineBuf, ",");

while(token != NULL){
if(strcmp(token, word) == 0){
printf(1, "%s found at line %d",word, lineNum );

}
}
}
}

int main(int argc, char argv[]){
if(argc !=  2){
printf("please use format keyword <filename> <word>");
} else {
keyword(argv[1], argv[2]);
}
}
