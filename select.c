/* -*- mode: c-mode; -*- */
/*
 * select program.
 */
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

/*
 * Functions prototypes.
 */
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  int n, nfds;
  char buf[ 32 ];
  fd_set readfs;
  struct timeval tv;
  /*
   * We will be reading from standard input (file
   * descriptor 0), so we want to know when the
   * user has typed something.
   */
  FD_ZERO(&readfds);
  FD_SET(0, &readfds);
  /*
   * Set the timeout for 10 seconds.
   */
  bzero((void *) &tv, sizeof(struct timeval));
  tv.tv_sec = 15;
  tv.tv_usec = 0;
  /*
   * Prompt for input.
   */
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
   * Now we check
}
