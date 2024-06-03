/* -*- mode: c-mode; -*- */
/*
 * sigaction program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/*
 * Functions prototypes.
 */
void handler(int);
int main(int, char *[]);
/*
 * Global variables.
 */
struct sigaction sa = {
  handler,
  SIGUSR1,
  SA_SGINFO | SA_DFL
};

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  /*
   * setup signal handler for this process.
   */
  if(sigaction(SIGUSR1, &sa, NULL) >= 0) {
    ret = EXIT_SUCCESS;
  }
  exit(ret);
}

void handler(in si)
{
  int save_errno = errno;
  /*
   *
   */
  errno = save_errno;
}

/* End of file sigaction.c */
