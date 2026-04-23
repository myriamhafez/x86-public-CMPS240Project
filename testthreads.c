#include "types.h"
#include "user.h"
#include "x86.h"

#define PGSIZE 4096

typedef struct{
uint next_ticket;
uint now_serving;
} ticket_lock_t;

void ticket_lock_init(ticket_lock_t *lk){
lk->next_ticket = 0;
lk->now_serving = 0;
}

void ticket_lock(ticket_lock_t *lk){
uint my_turn = __sync_fetch_and_add(&lk->next_ticket, 1);
while(lk->now_serving != my_turn)
;
}

void ticket_unlock(ticket_lock_t *lk){
__sync_synchronize();
lk->now_serving++;
}

volatile int counter = 0;
ticket_lock_t lock;
void increment_no_lock(void *arg1, void *arg2) {
int n = (int)arg1;
for(int i = 0; i < n; i++)counter++;
exit();
}

void increment_with_lock(void *arg1, void *arg2){
int n = (int)arg1;
for(int i = 0; i < n; i++) {
ticket_lock(&lock);
counter++;
ticket_unlock(&lock);
} exit();
}

int main(void) {
printf(1, "Thread Test\n");
counter = 0;
printf(1, "Test 1: no lock\n");

void *stack1 = malloc(PGSIZE);
void *stack2 = malloc(PGSIZE);

clone(increment_no_lock, (void*)10000, 0, stack1);
clone(increment_no_lock, (void*)10000, 0, stack2);

void *s;
join(&s); free(s);
join(&s); free(s);

printf(1, "  Result: %d (expected 20000)\n", counter);
printf(1, "  Race?:  %s\n\n", counter != 20000 ? "YES" : "No race this run");

counter = 0;
ticket_lock_init(&lock);
printf(1, "Test 2: ticket lock (expect 20000)\n");

stack1 = malloc(PGSIZE);
stack2 = malloc(PGSIZE);
clone(increment_with_lock, (void*)10000, 0, stack1);
clone(increment_with_lock, (void*)10000, 0, stack2);
join(&s); free(s);
join(&s); free(s);
printf(1, "  Result:  %d\n", counter);
printf(1, "  Correct: %s\n\n", counter == 20000 ? "YES" : "NO");
exit();
}
