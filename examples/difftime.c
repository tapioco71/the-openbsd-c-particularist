/* -*- mode: c-mode; -*- */

/* difftime.c file. */
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

/* difftime program. */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd_wtmp;
  long int ret = EXIT_FAILURE;
  double d;
  off_t lp = 0;
  struct utmp tmp_record, login_record, logout_record;
  /* Open the /va/run/utmp file. */
  if(argc == 2) {
    if((fd_wtmp = open(_PATH_WTMP, O_RDONLY)) >= 0) {
      bzero((void *) &login_record, sizeof(struct utmp));
      while(read(fd_wtmp,			\
		 (void *) &tmp_record,		\
		 sizeof(struct utmp)) > 0) {
	if(tmp_record.ut_name[ 0 ] != '\0') {
	  if(strncmp((const char *) argv[ 1 ],		\
		     (const char *) tmp_record.ut_name, \
		     UT_NAMESIZE) == 0) {
	    lp = lseek(fd_wtmp, 0, SEEK_CUR);
	    memcpy((void *) &login_record, \
		   (void *) &tmp_record,   \
		   sizeof(struct utmp));
	  }
	}
      }
      if(lp >= 0) {
	if(login_record.ut_name[ 0 ] != '\0') {
	  printf("Found login name: %s in position %d.\n", \
		 argv[ 1 ],				   \
		 lp);
	  if(lseek(fd_wtmp, lp, SEEK_SET) >= 0) {
	    bzero((void *) &logout_record, sizeof(struct utmp));
	    while(read(fd_wtmp,				\
		       (void *) &tmp_record,		\
		       sizeof(struct utmp)) > 0) {
	      if(tmp_record.ut_name[ 0 ] == '\0') {
		if(strncmp((const char *) tmp_record.ut_line,	\
			   (const char *) login_record.ut_line, \
			   UT_LINESIZE) == 0) {
		  printf("found the corresponding logout entry for %s...\n", \
			 argv[ 1 ]);
		  memcpy((void *) &logout_record,	\
			 (void *) &tmp_record,		\
			 sizeof(struct utmp));
		  break;
		}
	      }
	    }
	    d = difftime(logout_record.ut_time, login_record.ut_time);
	    printf("user %s last session time: %f s.\n", argv[ 1 ], d);
	  } else
	    perror("Could not seek in /var/log/wtmp");
	} else
	  fprintf(stderr, "no such login: %s\n", argv[ 1 ]);
      } else
	perror("Could not seek in /var/log/wtmp");
      close(fd_wtmp);
    } else
      perror("Could not open /var/log/wtmp");
  } else
    fprintf(stderr, "Usage: difftime name\n");
  exit(ret);
}

/* End of difftime.c file. */
