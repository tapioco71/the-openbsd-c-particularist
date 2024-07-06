/* -*- mode: c-mode; -*- */

/* File strerror.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* strerror program. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i;
  long int ret;

  /* */
  ret = EXIT_FAILURE;
  for(i = 0; i <= EPROTO; i++)
    fprintf(stderr, "Error %d = %s\n", i, strerror(i));
  ret = EXIT_SUCCESS;
  exit(ret);
}
