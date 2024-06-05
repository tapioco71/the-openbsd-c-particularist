/* -*- mode: c-mode; -*- */

/* append2.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

/* append2.c program. */

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int n;
  int fromfd, tofd;
  char buf[ BUFSIZ ];
  long ret = EXIT_FAILURE;

  /* Check our arguments. */
  if(argc == 3) {

    /* Open the from-file for reading. */
    if((fromfd = open(argv[ 1 ], O_RDONLY)) >= 0) {
      /*
       * Open the to-file for appending.  If to-file does
       * not exist, open will create it with mode 0644
       * -rw-r--r--.  Note that we specify the mode in octal
       * not decimal.
       */
      if((tofd = open(argv[ 2 ], O_WRONLY | O_CREAT | O_APPEND, 0644)) >= 0) {
	/*
	 * Now read a buffer-full line at a time from from-file
	 * and write it to the to-file.  Note that we only
	 * write the number of characters read  read in,
	 * rather than always writing BUFSIZ characters.
	 */
	while((n = read(fromfd, buf, sizeof(buf))) > 0)
	  if(write(tofd, buf, n) != n) {
	    write(STDERR_FILENO, "Could not write to to-file.\n", 28);
	    break;
	  }
	/* Now close the files. */
	close(tofd);
	if(errno == 0)
	  ret = EXIT_SUCCESS;
      } else {
	write(STDERR_FILENO, argv[ 2 ], strlen(argv[ 2 ]));
      }
      close(fromfd);
    } else {
      write(STDERR_FILENO, argv[ 1 ], strlen(argv[ 1 ]));
    }
  } else {
    write(STDERR_FILENO, "Usage: ", 7);
    write(STDERR_FILENO, *argv, strlen(argv[ 0 ]));
    write(STDERR_FILENO, " from-file to-file\n", 19);
  }
  exit(ret);
}

/* End of append2.c file. */
