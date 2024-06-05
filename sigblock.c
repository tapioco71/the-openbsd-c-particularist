/* -*- mode: c-mode; -*- */

/* timeout.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>

/* sigblock.c program. */
#define FOREVER for(;;)

/* Global variables. */
struct sigaction signals = {
  handler,
};

/* Functions prototypes. */
void handler(int, siginfo_t *, void *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  /* Setup signal set for this process. */
  if(sigfillset(&signals.sa_mask) >= 0) {
    printf("Current signal mask set: 0x%8x\n", signals.sa_mask);
    ret = EXIT_SUCCESS;
  }
  exit(ret);
}

void handler(int sig, siginfo_t *mask, void *d)
{
  ;
}

/* End of timeout.c file. */
