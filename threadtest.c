#include "types.h"
#include "user.h"

int ans;

void thread2(void *arg1, void *arg2)
{
    ans = (int)arg1 + (int)arg2;
    exit();
}

void thread1(void *arg1, void *arg2)
{
    thread_create(thread2, arg1, arg2);
    thread_join();
    exit();
}

int main()
{
    int pid;
    if ((pid = fork()) > 0) {
        thread_create(thread1, (void *)1, (void *)2);
        wait();
        printf(1, "ans = %d\n", ans);
        thread_join();
        exit();
    } else if (!pid){
        thread_create(thread1, (void *)4, (void *)5);
        thread_join();
        printf(1, "ans = %d\n", ans);
        exit();
    }
    exit();
}