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
  int fd_utmp, fd_wtmp;
  long int ret = EXIT_FAILURE;
  struct utmp login_record, logout_record;

  /*
   * Open the /va/run/utmp file.
   */
  if(argc == 2) {
    if((fd_utmp = open(_PATH_UTMP, O_RDONLY)) >= 0) {
      if((fd_wtmp = open(_PATH_WTMP, O_RDONLY)) >= 0) {
	while(read(fd_utmp, (void *) &login_record, sizeof(struct utmp)) > 0) {
	  if(login_record.ut_name[ 0 ] != '\0') {
	    if(strncmp(login_record.ut_name, name, UT_NAMESIZE) == 0)
	      break;
	  }
	}
	while(read(fd_wtmp, (void *) &logout_record, sizeof(struct utmp)) > 0) {
	  if(logout_record.ut_name[ 0 ] != '\0') {
	    if(strncmp(logout_record.ut_name, name, UT_NAMESIZE) == 0)
	      break;
	  }
	}
	if((login_record.ut_name[ 0 ] != '\0') && != (logout_record.ut_name[ 0 ] != '\0')) {
	  printf("%s: time connected %lf seconds.\n", \
		 difftime(login_record.ut_time, login_record.ut_time));
	  ret = EXIT_SUCCESS;
	}
	close(fd_wtmp);
      } else
	perror("Could not open /var/run/wtmp");
      close(fd_utmp);
    } else
      perror("Could no open /var/run/utmp");
  } else
    fprintf(stderr, "Usage: difftime name\n");
  exit(ret);
}
