#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "ticketlock.h"

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

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

void lock_init(lock_t *lk)
{
  lk->ticket = 0;
  lk->turn = 0;
}

// acquire a ticket lock via exchange-and-add, compare-and-swap
void lock_acquire(lock_t *lk)
{
  uint myturn = xaddl(&lk->ticket);
  // load lk->turn MUST be atomic
  // cmpxchg can be replaced by a atomic load instr
  uint lkturn = cmpxchg(&lk->turn, myturn, myturn);
  while (lkturn != myturn)
    lkturn = cmpxchg(&lk->turn, myturn, myturn); // spin
  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen after the lock is acquired.
  __sync_synchronize();
}
// release a ticket lock via exchange-and-add
void lock_release(lock_t *lk)
{
  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen after the lock is acquired.
  __sync_synchronize();
  xaddl(&lk->turn);
}