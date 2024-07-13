/* -*- mode: c-mode; -*- */

/* File queue.h */
#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Types. */
struct tagQueue {
  void **q_data;
  size_t q_dimension;
  size_t q_start;
  size_t q_end;
  bool q_empty;
  bool q_full;
};

typedef struct tagQueue queue_t;

/* Function prototypes. */
long int initialize(queue_t *, size_t);
long int destroy(queue_t *);
void *push(void *, queue_t *);
void *pop(queue_t *);
bool empty(queue_t *);
bool full(queue_t *);
bool unique(void *, queue_t *, bool (*cmp)(void *, ...));

#endif /* __QUEUE_H */

/* End of queue.h file. */
