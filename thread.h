#include "types.h"
#include "stat.h"
#include "user.h"

int
thread_create(void (*start_routine)(void *, void *), void *arg1, void *arg2)
{
    void *userstk = malloc(PGSIZE);
    return clone(start_routine, arg1, arg2, userstk);
}

int
thread_join()
{
    void *stack = 0;
    if (join(&stack) < 0)
        return -1;
    free(stack);
    return 0;
}

