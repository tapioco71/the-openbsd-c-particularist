/* -*- mode: c-mode; -*- */
/*
 * timezone program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

/*
 * Functions prototypes.
 */
char *dst(int);
int main(int, char *[]);
/*
 * Global variables.
 */
char *dstzones[ DST_CAN + 1 ] = {
  "None",
  "USA",
  "Australia",
  "Western Europe",
  "Middle Europe",
  "Eastern Europe",
  "Canada",
  "Unknown"
};

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  struct timeval now;
  struct timezone tz;
  /*
   * get-time-of-the-day.
   */
  if(gettimeofday(&now, &tz) >= 0) {
    printf("time in seconds: %ld, ", now.tv_sec);
    printf("time in microseconds: %ld\n", now.tv_usec);
    printf("date: %s\n", ctime(&now.tv_sec));
    printf("minutes west of Greenwich: %d, ", tz.tz_minuteswest);
    printf("type of DST correction: %s\n", dst(tz.tz_dsttim));
    ret = EXIT_SUCCESS;
  }
  exit(ret);
}

char *dst(int d)
{
  if((d >= DST_NONE) && (d <= DST_CAN))
    return dstzones[ d ];
  else
    return dstzones[ DST_CAN + 1 ];
}
