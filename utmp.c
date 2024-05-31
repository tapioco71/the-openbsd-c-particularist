/* -*- mode: c-mode; -*- */
/*
 * group program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <utmp.h>

/*
 * Functions prototypes.
 */
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;
  struct utmp record;
  /*
   * Open the /va/run/utmp file.
   */
  if((fd = open(_PATH_UTMP, O_RDONLY)) >= 0) {
    if(lseek(fd, 0, SEEK_SET) > 0) {
      while(read(1, &record, sizeof(struct utmp)) > 0) {
	printf("line: %.*s, ", record.ut_line);
	printf("name: %.*s, ", record.ut_name);
	printf("name: %.*s, ", record.ut_host);
	printf("time: %s\n", ctime(&record.ut_time));
      }
      ret = EXIT_SUCCESS;
    } else
      perror("utmp seek failed.");
    close(fd);
  } else
    perror("open /var/run/utmp");
  exit(ret);
}
