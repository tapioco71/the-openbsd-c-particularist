/* -*- mode: c-mode; -*- */
/*
 * difftime program.
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

/*
 * Functions prototypes.
 */
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  int fd_wtmp;
  long int ret = EXIT_FAILURE;
  double d;
  struct utmp login_record, logout_record;

  /*
   * Open the /va/run/utmp file.
   */
  if(argc == 2) {
    if((fd_wtmp = open(_PATH_WTMP, O_RDONLY)) >= 0) {
      while(read(fd_wtmp, (void *) &login_record, sizeof(struct utmp)) > 0) {
	if(strncmp((const char *) argv[ 1 ], (const char *) login_record.ut_name, UT_NAMESIZE) != 0) {
	  if(read(fd_wtmp, (void *) &logout_record, sizeof(struct utmp)) > 0) {
	    d = difftime(login_record.ut_time, logout_record.ut_time);
	  }
	}
      }
      printf("user %s last session time: %f\n", d);
      close(fd_wtmp);
    } else
      perror("Could not open /var/log/wtmp");
  } else
    fprintf(stderr, "Usage: difftime name\n");
  exit(ret);
}
