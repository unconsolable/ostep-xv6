#include "types.h"
#include "user.h"

void thread1(void *arg1, void *arg2)
{
    for (int i = 0; i < 10000; i++) {
        printf(1, "th=%d\n", i);
        void *ptr = malloc(2);
        free(ptr);
    }
    exit();
}

int main()
{
    thread_create(thread1, 0, 0);
    for (int i = 0; i < 10000; i++) {
        printf(1, "ma=%d\n", i);
        void *ptr = malloc(2);
        free(ptr);
    }
    thread_join();
    exit();
}