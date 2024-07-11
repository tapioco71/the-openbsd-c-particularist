/* -*- mode: c-mode; -*- */

/* find-word.h file. */
#ifndef _FIND_WORD_H
#define _FIND_WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define FOREVER for(;;)
#define MAXINT 20
#define DEFAULT_DICTIONARY_PATH "/usr/share/dict/words"

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
int main(int, char *[]);

#endif /* _FIND_WORD_H */

/* End if find-word.h file. */
