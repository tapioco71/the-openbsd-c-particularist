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

/* Functions prototypes. */
void timeout(int);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  sigset_t s;
  long int ret = EXIT_FAILURE;
  /* Setup signal set for this process. */
  if(sigfillset(&s) >= 0) {
    printf("Current signal mask set: 0x%x8\n", s);
    ret = EXIT_SUCCESS;
  }
  exit(ret);
}

/* End of timeout.c file. */
