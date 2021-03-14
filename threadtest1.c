#include "types.h"
#include "user.h"

void thread(void *arg1, void *arg2)
{
    int ticket = (int)arg1;
    settickets(ticket * 100);
    while (1)
    {

    }
}

int main()
{
    for (int i = 1; i < 10; i++) {
        thread_create(thread, (void *)i, 0);
    }
    exit();
}