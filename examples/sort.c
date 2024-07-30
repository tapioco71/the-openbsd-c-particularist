/* -*- mode: c-mode; -*- */

/* File sort.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *array[] = { "XX", "YYY", "Z" };

#define N (sizeof(array) / sizeof(array[ 0 ]))

/* Functions prototypes. */
int cmp(const void *, const void *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  size_t i;

  /* */
  qsort(array, N, sizeof(array[0]), cmp);
  for(i = 0; i < N; i++)
    printf("%s\n", array[i]);
  ret = EXIT_SUCCESS;
  exit(ret);
}

/*
 * cmp -- comparing elements function.
 */
int cmp(const void *a, const void *b)
{
  /*
   * a and b point to elements of the array.
   * Cast and dereference to obtain the actual elements,
   * which are also pointers in this case.
   */
  size_t lena = strlen(*(const char **)a);
  size_t lenb = strlen(*(const char **)b);

  /*
   * Do not subtract the lengths. The difference between values
   * cannot be represented by an int.
   */
  return lena < lenb ? -1 : lena > lenb;
}

/* End of sort.c file. */
