/* -*- mode: c; -*- */

/* utmp.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <utmp.h>

/* utmp program. */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;
  struct utmp record;
  /* Open the /va/run/utmp file. */
  if((fd = open(_PATH_UTMP, O_RDONLY)) >= 0) {
    while(read(fd, (void *) &record, sizeof(struct utmp)) > 0) {
      if(record.ut_name[ 0 ] != '\0') {
	printf("line: %.*s, ", UT_LINESIZE, record.ut_line);
	printf("name: %.*s, ", UT_NAMESIZE, record.ut_name);
	printf("name: %.*s, ", UT_HOSTSIZE, record.ut_host);
	printf("time: %s", ctime(&record.ut_time));
      }
    }
    ret = EXIT_SUCCESS;
    close(fd);
  } else
    perror("open /var/run/utmp");
  exit(ret);
}

/* End of utmp.c file. */
