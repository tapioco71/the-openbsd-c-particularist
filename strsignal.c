/* -*- mode: c-mode; -*- */

/* File strsignal.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

/* strsignal program. */
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
  for(i = SIGHUP; i <= SIGTHR; i++)
    printf("Signal %d = %s\n", i, strsignal(i));
  ret = EXIT_SUCCESS;
  exit(ret);
}

/* End of strsignal.c file. */
