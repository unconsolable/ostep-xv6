#ifndef _TICKETLOCK_H_
#define _TICKETLOCK_H_

typedef struct lock_t
{
  unsigned int ticket;
  unsigned int turn;
} lock_t;

#endif