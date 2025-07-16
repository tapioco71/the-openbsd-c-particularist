/* -*- mode: c; -*- */

/* sigaction.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/* sigaction program. */

/* Functions prototypes. */
void handler(int);
int main(int, char *[]);
/* Global variables. */
struct sigaction sa = {
  handler,
  SIGUSR1,
  SA_SIGINFO
};

struct sigaction sb = {
  SIG_IGN,
  SIGUSR2,
};

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  /* Setup signal handler for this process. */
  if(sigaction(SIGUSR1, &sa, NULL) >= 0) {
    if(sigaction(SIGUSR2, &sb, NULL) >= 0) {
      ret = EXIT_SUCCESS;
      pause();
    } else
      perror("Could not setup SIGUSR2");
  } else
    perror("Could not setup SIGUSR1");
  exit(ret);
}

void handler(int si)
{
  /* Saving the current errno value. */
  int save_errno = errno;
  /* Handler code. */
  printf("Entering handler.\n");
  /* ... */
  printf("Signal passed to handler: %d\n", si);
  printf("Exiting handler.\n");
  /* Restore the old errno value. */
  errno = save_errno;
}

/* End of sigaction.c file. */
