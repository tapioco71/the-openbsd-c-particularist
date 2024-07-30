/* -*- mode: c-mode; -*- */

/* cputime.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <utmp.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/times.h>

/* cputime program. */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i, temp, prev, succ;
  long int ret = EXIT_FAILURE;
  struct tms before, after;
  /* Get current time. */
  times(&before);
  /* some code. */
  for(i = 1; i < rand(); i++) {
    prev = 1;
    succ = 2;
    do {
      printf("%d\n", prev);
      temp = prev + succ;
      prev = succ;
      succ = temp;
    } while(succ < 1836311903);
  }
  ret = EXIT_SUCCESS;
  /* Get time after computation. */
  times(&after);
  printf("User time: %lld seconds.\n", after.tms_utime - before.tms_utime);
  printf("System time: %lld seconds.\n", after.tms_stime - before.tms_stime);
  exit(ret);
}

/* End of cputime.c file. */
