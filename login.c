#define MAX_ATTEMPTS 3

#include "types.h"
#include "stat.h"
#include "user.h"
#include "userdb.h"

int
authenticate(char *name, char *pass){

for(int i = 0; userdb[i].activity;i++){
if(strcmp(userdb[i].username, name) == 0&& strcmp(userdb[i].password, pass) == 0)
return 1;
}
 return 0;
}

void read_input(char *buf, int max){
int i = 0;
char c;
while(i < max - 1){
	if(read(0, &c, 1) <= 0) break;
	if(c =='\n') break;
	if(c == 127 || c == '\b')  {
	if( i > 0) i--;
	if(i > 0 && buf[i-1]=='n') buf[i - 1] = '\0';

	 continue;
}
buf[i++] = c;
}
buf[i] = '\0';
printf(1, "\n");
}

int
main(void)
{
char password[MAX_PASSWORD];
char username[MAX_USERNAME];

int attempts = 0;

while(attempts < MAX_ATTEMPTS) {
printf(1, "Welcome to xv6!\n");
printf(1, "Username (please use: \"admin\"): ");
read_input(username, MAX_USERNAME);
printf(1, "Password: (please use: \"12345\":  ");
read_input(password, MAX_PASSWORD);

if(authenticate(username, password)){
printf(1, "\nWelcome, %s!\n\n", username);
char *argv[] = {"sh", 0};
exec("sh", argv);
printf(1, "exec failed\n");
exit();
}
printf(1, "Login failed. Try again!\n");
attempts++;

}
printf(1,"Attempt limit reached. \n");
exit();
}
