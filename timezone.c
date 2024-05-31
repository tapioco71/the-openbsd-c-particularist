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
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  time_t now;
  struct tm *tm_val;
  /*
   * get-time-of-the-day.
   */
  if(gettimeofday(&now, NULL) >= 0) {
    if((tm_val = localtime(&now)) != NULL) {
      printf("seconds: %d, ", tm.tm_sec);
      printf("minutes: %d, ", tm.tm_min);
      printf("hours: %d, ", tm.tm_hour);
      printf("day of month: %d, ", tm.tm_mday);
      printf("month: %d, ", tm.tm_mon);
      printf("year: %d, ", tm.tm_year);
      printf("weekday: %d, ", tm.tm_wday);
      printf("day of year: %d\n", tm.tm_yday);
      printf("summer time in effect? %d\n", tm.tm_isdst);
      printf("offset from UTC in seconds: %d\n", tm.tm_gmtoff);
      printf("timezone name: %s\n", tm.tm_zone);
      ret = EXIT_SUCCESS;
    } else
      perror("Could not get local time");
  } else
    perror("Could not get time-of-the-day");
  exit(ret);
}
