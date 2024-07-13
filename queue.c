/* -*- mode: c-mode; -*- */

/* File queue.c */
#include "queue.h"

long int initialize(queue_t *q, size_t n)
{
  long int ret = EXIT_FAILURE;
  size_t i;

  if(q) {
    if(n > 0) {
      q -> q_data = calloc(n, sizeof(void *));
      if(q -> q_data) {
	for(i = 0; i < n; i++)
	  q -> q_data[ i ] = NULL;
	q -> q_dimension = n;
	q -> q_start = 0;
	q -> q_end = 0;
	q -> q_empty = true;
	q -> q_full = false;
	ret = EXIT_SUCCESS;
      }
    }
  }
  return ret;
}

long int destroy(queue_t *q)
{
  long int ret = EXIT_FAILURE;
  size_t i;

  if(q) {
    if(q -> q_data) {
      free(q -> q_data);
      q -> q_dimension = 0;
      q -> q_start = 0;
      q -> q_end = 0;
      q -> q_empty = false;
      q -> q_full = false;
      ret = EXIT_SUCCESS;
    }
  }
  return ret;
}

void *push(void *d, queue_t *q)
{
  size_t i;
  void *ret = NULL;

  if(d) {
    if(q) {
      if(q -> q_full == false) {
	q -> q_empty = false;
	q -> q_data[ q -> q_end++ ] = d;
	q -> q_end = q -> q_end % q -> q_dimension;
	if(q -> q_end == q -> q_start)
	  q -> q_full = true;
	ret = d;
      }
    }
  }
  return ret;
}

void *pop(queue_t *q)
{
  void *ret = NULL;

  if(q) {
    if(q -> q_empty == false) {
      q -> q_full = false;
      ret = q -> q_data[ q -> q_start++ ];
      q -> q_start = q -> q_start % q -> q_dimension;
      if(q -> q_start == q -> q_end)
	q -> q_empty = true;
    }
  }
  return ret;
}

bool empty(queue_t *q)
{
  bool ret = false;

  if(q) {
    ret = q -> q_empty;
  }
  return ret;
}

bool full(queue_t *q)
{
  bool ret = false;

  if(q) {
    ret = q -> q_full;
  }
  return ret;
}

bool unique(void *d, queue_t *q, bool (*cmp)(void *p, ...))
{
  size_t i;
  bool ret = true;

  if(d) {
    if(q) {
      if(cmp) {
	if(empty(q) == false) {
	  for(i = q -> q_start; i != q -> q_end; i++) {
	    i = (i % q -> q_dimension);
	    if(cmp(d, q -> q_data[ i ]) == true) {
	      ret = false;
	      break;
	    }
	  }
	}
      }
    }
  }
  return ret;
}

/* End of queue.c file. */
