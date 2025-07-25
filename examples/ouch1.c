/* -*- mode: c; -*- */

/* ouch1.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/* ouch1 program. */
#define FOREVER for(;;)

/* Functions prototypes. */
void handler(int);
int main(int, char *[]);
/* Global variables. */
struct sigaction sa = {
  handler,
  SIGINT,
  SA_SIGINFO
};

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  /* Setup signal handler for this process. */
  if(sigaction(SIGINT, &sa, NULL) >= 0) {
    ret = EXIT_SUCCESS;
    FOREVER
      pause();
  } else
    perror("Could not setup SIGINT");
  exit(ret);
}

void handler(int si)
{
  /* Handler code */
  printf("OUCH\n");
}

/* End of ouch1.c file. */
