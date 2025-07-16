/* -*- mode: c; -*- */

/* find-word.h file. */
#ifndef __FIND_WORD_H
#define __FIND_WORD_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "list.h"

#define FOREVER for(;;)
#define MAXINT 20
#define DEFAULT_DICTIONARY_PATH "/usr/share/dict/words"
#define min(a, b) ((a) < (b) ? (a) : (b))

/* Types. */

/* Functions prototype. */
void lowerize(char *, size_t);
void printArray(char *, void *, size_t);
size_t factorial(size_t);
size_t binomial(size_t, size_t);
void combinations(size_t *, size_t, size_t, size_t **);
long int getCombString(char *, char *, size_t *, size_t);
size_t **allocateCombs(size_t, size_t);
long int deallocateCombs(size_t **);
char *intersect(char *, char *, size_t);
bool cmp(void *, ...);
int main(int, char *[]);

#endif /* __FIND_WORD_H */

/* End if find-word.h file. */
