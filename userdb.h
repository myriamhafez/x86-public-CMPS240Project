#define MAX_USERS 10
#define MAX_USERNAME 20
#define MAX_PASSWORD 30

struct user{
char username[MAX_USERNAME];
char password[MAX_PASSWORD];
int activity;
};

static struct user userdb[]={
{"admin", "12345", 1},
{"myriam.hafez", "12345", 1},
{"", "", 0}
};
