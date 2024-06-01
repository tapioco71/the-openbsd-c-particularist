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
  struct utmp record;

  /*
   * Open the /va/run/utmp file.
   */
  if(argc == 2) {
    if((fd_wtmp = open(_PATH_WTMP, O_RDONLY)) >= 0) {
      if(lseek(fd_wtmp, -sizeof(struct utmp), SEEK_END) >= 0) {
	do {
	  if(read(fd_wtmp, (void *) &record, sizeof(struct utmp)) > 0) {
	    if(record.ut_name[ 0 ] != '\0') {
	      if(strncmp(record.ut_name, (const char *) argv[ 1 ], UT_NAMESIZE) == 0) {
		printf("login for %s at %s\n", record.ut_name, ctime(&record.ut_time));
		break;
	      }
	    }
	    if(lseek(fd_wtmp, -sizeof(struct utmp), SEEK_CUR) < 0)
	      break;
	  } else
	    break;
	} while(1);
      } else
	perror("Could not seek in /var/log/wtmp");
      close(fd_wtmp);
    } else
      perror("Could not open /var/log/wtmp");
  } else
    fprintf(stderr, "Usage: difftime name\n");
  exit(ret);
}
