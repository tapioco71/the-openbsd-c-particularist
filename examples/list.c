/* -*- mode: c-mode; -*- */

/* File list.c */
#include "list.h"

list_t *push(void *d, list_t **l)
{
  list_t *ret = *l, *temp;

  if(d) {
    temp = (list_t *) calloc(1, sizeof(list_t));
    if(temp) {
      temp -> l_next = *l;
      temp -> l_data = d;
      ret = temp;
    }
  }
  return ret;
}

void *pop(list_t **l)
{
  void *ret = NULL;
  list_t *temp = *l;

  if(temp) {
    if(temp -> l_next) {
      while(temp -> l_next -> l_next)
	temp = temp -> l_next;
      ret = temp -> l_next -> l_data;
      free(temp -> l_next);
      temp -> l_next = NULL;
    } else {
      ret = temp -> l_data;
      free(temp);
      *l = NULL;
    }
  }
  return ret;
}

bool unique(void *d, list_t *l, bool (*cmp)(void *, ...))
{
  bool ret = true;
  list_t *p;

  if(d) {
    if(cmp) {
      p = l;
      while(p) {
	if(cmp(d, p -> l_data) == true) {
	  ret = false;
	  break;
	} else
	  p = p -> l_next;
      }
    }
  }
  return ret;
}

/* End of list.c file. */
