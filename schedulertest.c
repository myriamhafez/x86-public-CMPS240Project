#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
int pid;
int i, j;
  
pid = fork();
if(pid == 0){
for(i = 0; i < 1000000; i++){
for(j = 0; j < 1000; j++){
asm volatile("nop");
}
if(i % 100000 == 0)
printf(1, "%d %d\n", getticks(), getpriority());
}
exit();
}
  
sleep(10);
pid = fork();
if(pid == 0){
for(i = 0; i < 100; i++){
sleep(1);
printf(1, "%d %d\n", getticks(), getpriority());
}
exit();
}
  
wait();
wait();
exit();
}
