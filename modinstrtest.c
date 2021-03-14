#include "types.h"
#include "user.h"

int main()
{
    int *code;
    code = (int *)4096;
    int orig = code[0];
    printf(1, "orig code: %x\n", orig);
    code[0] = 0;
    printf(1, "now code: %x\n", code[0]);
    mprotect(code, 1);
    printf(1, "after protect: %x\n", code[0]);
    // if we mod code[0] here, will segfault
    munprotect(code, 1);
    code[0] = orig;
    printf(1, "after unprotect and mod: %x\n", code[0]);
    exit();
}