#include "types.h"
#include "user.h"

int main()
{
    int pid1, pid2, pid3;
    printf(1, "Run 1 CPU to get best results\n");
    printf(1, "Get ticks status via Ctrl+P(procdump())\n");
    if ((pid1 = fork()) > 0) {
        if ((pid2 = fork()) > 0) {
            if ((pid3 = fork()) > 0) {
                    struct pstat p;
                    getpinfo(&p);
                    for (int i = 0; i < NPROC; i++) {
                        if (p.inuse[i]) {
                            printf(1, "%d %d %d\n", p.tickets[i], p.pid[i], p.ticks[i]);
                        }
                    }
                    exit();
                } else if (pid3 == 0) {
                    settickets(10);
                    printf(1, "child3\n");
                    while (1) {
                    }
                    exit();
                }
        } else if (pid2 == 0) {
            settickets(20);
            printf(1, "child2\n");
            while (1) {
            }
            exit();
        }
    } else if (pid1 == 0) {
        settickets(30);
        printf(1, "child1\n");
        while (1) {
        }
        exit();
    }
}