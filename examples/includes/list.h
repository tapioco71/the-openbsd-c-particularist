/* -*- mode: c-mode; -*- */

/* list.h file. */
#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* Types. */
struct tagList {
  void *l_data;
  struct tagList *l_next;
};

typedef struct tagList list_t;

/* Types. */

/* Functions prototype. */
list_t *push(void *, list_t **);
void *pop(list_t **);
bool unique(void *, list_t *, bool (*cmp)(void *, ...));

#endif /* __LIST_H */

/* End if list.h file. */
