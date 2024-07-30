/* -*- mode: c-mode; -*- */

/* select.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>

/* select program. */
#define BUFFER_SIZE 32

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int n, nfds;
  char buf[ BUFFER_SIZE ];
  long int ret = EXIT_FAILURE;
  fd_set readfds;
  struct timeval tv;
  /*
   * We will be reading from standard input (file
   * descriptor 0), so we want to know when the
   * user has typed something.
   */
  FD_ZERO(&readfds);
  FD_SET(0, &readfds);
  /* Set the timeout for 10 seconds. */
  bzero((void *) &tv, sizeof(struct timeval));
  tv.tv_sec = 15;
  tv.tv_usec = 0;
  /* Prompt for input. */
  printf("Type a word; if you don't in 10 ");
  printf("seconds I'll use \"WORD\": ");
  fflush(stdout);
  /*
   * Now call select.  We pass NULL for
   * writefds and exceptfds, since we
   * aren't interested in them.
   */
  nfds = select(1, &readfds, NULL, NULL, &tv);
  /*
   * Now we check the results.  If nfds is zero,
   * then we timed out and should assume the
   * default.  Otherwise, if file descriptor 0
   * is set in readfds, that means that it is
   * ready to be read and we can read something
   * from it.
   */
  if(nfds == 0)
    strncpy(buf, "WORD", 5);
  else
    if(FD_ISSET(0, &readfds)) {
      n = read(0, buf, BUFFER_SIZE);
      buf[ n > 0 ? n - 1 : 0 ] = '\0';
    }
  printf("\nThe word is: %s\n", buf);
  /*
   * This is not useful, but since we use this
   * method to return success or failure, just
   * go on.
   */
  ret = EXIT_SUCCESS;
  exit(ret);
}

/* End of select.c file. */
