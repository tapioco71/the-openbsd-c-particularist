/* -*- mode: c-mode; -*- */
/*
 * cputime program.
 */
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

/*
 * Functions prototypes.
 */
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  int temp, prev, succ;
  long int ret = EXIT_FAILURE;
  struct tms before, after;
  /*
   * Get current time.
   */
  times(&before);
  /*
   * some code.
   */
  prev = 1;
  succ = 2;
  for(i = 1; i < rand(); i++) {
    temp = prev + succ;
    prev = succ;
    succ = temp;
  }
  ret = EXIT_SUCCESS;
  /*
   * Get time after computation.
   */
  times(&after);
  printf("User time: %ld seconds.\n", after.tm_utime - before.tm_utime);
  printf("System time: %ld seconds.\n", after.tm_stime - before.tm_stime);
  exit(ret);
}
