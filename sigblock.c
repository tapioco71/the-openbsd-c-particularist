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
#include <sys/signal.h>

/* sigblock.c program. */
#define FOREVER for(;;)

/* Functions prototypes. */
void handler(int, siginfo_t *, void *);
int main(int, char *[]);

/* Global variables. */
struct sigaction signals;
jmp_buf env;

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  /* Setup signal set for this process. */
  signals.sa_sigaction = handler;
  if(sigfillset(&signals.sa_mask) >= 0) {
    if(sigdelset(&signals.sa_mask, SIGUSR1) >= 0) {
      printf("Current signal mask set: 0x%8x\n", signals.sa_mask);
      /*
       * Blocking all signals but SIGUSR1.
       * Use # `kill -s SIGUSR1 pid` to terminate the
       * process.
       */
      if(sigprocmask(SIG_BLOCK, &signals.sa_mask, NULL) >= 0) {
	if(setjmp(env) == 0) {
	  FOREVER {
	    ;
	  }
	} else
	  ret = EXIT_SUCCESS;
      }
    }
  }
  exit(ret);
}

void handler(int sig, siginfo_t *mask, void *d)
{
  longjmp(env, 1);
}

/* End of sigblock.c file. */
