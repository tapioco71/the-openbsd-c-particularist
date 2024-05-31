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
  FILE *fp;
  long int ret = EXIT_FAILURE;
  struct utmp record;
  /*
   * Open the /va/run/utmp file.
   */
  if((fp = fopen(_PATH_UTMP, "r")) != NULL) {
    while(fread((char *) &record, sizeof(struct utmp), 1, fp) >= 0) {
      if(record.ut_name[ 0 ] != '\0') {
	printf("line: %.*s, ", record.ut_line);
	printf("name: %.*s, ", record.ut_name);
	printf("name: %.*s, ", record.ut_host);
	printf("time: %s\n", ctime(&record.ut_time));
      }
    }
    ret = EXIT_SUCCESS;
    fclose(fp);
  } else
    perror("open /var/run/utmp");
  exit(ret);
}
