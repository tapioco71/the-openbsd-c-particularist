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
  int i, temp, prev, succ;
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
    if(succ < 1836311903) {
      printf("%d\n", prev);
      temp = prev + succ;
      prev = succ;
      succ = temp;
    } else
      break;
  }
  ret = EXIT_SUCCESS;
  /*
   * Get time after computation.
   */
  times(&after);
  printf("User time: %ld seconds.\n", after.tms_utime - before.tms_utime);
  printf("System time: %ld seconds.\n", after.tms_stime - before.tms_stime);
  exit(ret);
}
