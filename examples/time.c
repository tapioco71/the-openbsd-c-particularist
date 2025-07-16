/* -*- mode: c; -*- */

/* time.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

/* time program. */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  struct timeval now;
  /* get-time-of-the-day. */
  if(gettimeofday(&now, NULL) >= 0) {
    printf("time in seconds: %lld, ", now.tv_sec);
    printf("time in microseconds: %ld\n", now.tv_usec);
    printf("date: %s\n", ctime(&now.tv_sec));
    ret = EXIT_SUCCESS;
  }
  exit(ret);
}

/* End of timer.c file. */
