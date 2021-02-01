#include "pstat.h"

struct stat;
struct rtcdate;
struct lock_t;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int getreadcount(void);
int settickets(int);
int getpinfo(struct pstat *);
int mprotect(void *addr, int len);
int munprotect(void *addr, int len);
int clone(void (*fcn)(void*, void *), void *arg1, void *arg2, void *stack);
int join(void **stack);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int thread_create(void (*start_routine)(void *, void *), void *arg1, void *arg2);
int thread_join();
void lock_init(struct lock_t *);
void lock_acquire(struct lock_t *);
void lock_release(struct lock_t *);
