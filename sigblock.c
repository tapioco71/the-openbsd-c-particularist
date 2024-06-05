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

void timeout(int sig)
{
  /*
   * Ignore the signal for the duration of this
   * routine.
   */
  if(sig == SIGALRM) {
    /* Restore the action of the alarm signal. */
    if(sigaction(SIGALRM, &sa, NULL) >= 0) {
      /*
       * We would perform any timeout-related
       * functions here; in this case there
       * are none.
       */
      ;
      /*
       * Return to the main routine at setjmp
       * and make setjmp return 1.
       */
      ;
      longjmp(env, 1);
    }
  }
}

/* End of timeout.c file. */
