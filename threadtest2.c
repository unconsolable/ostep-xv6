#include "types.h"
#include "user.h"
#include "ticketlock.h"

lock_t lk;
int ans = 0;

void func(void *arg1, void *arg2)
{
    for (int i = 0; i < 1000000; i++) {
        lock_acquire(&lk);
        ans++;
        lock_release(&lk);
    }
    exit();
}

int main()
{
    lock_init(&lk);
    thread_create(func, 0, 0);
    for (int i = 0; i < 1000000; i++) {
        lock_acquire(&lk);
        ans++;
        lock_release(&lk);
    }
    thread_join();
    printf(1, "ans=%d\n", ans);
    exit();
}