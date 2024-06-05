/* -*- mode: c-mode; -*- */

/* sigstack.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/resource.h>
#include <sys/signal.h>

/* sigstack program. */
#define STACKSIZE 10240
#define FOREVER for(;;)

/* Functions prototypes. */
void fn(void);
void handler(int, siginfo_t *, void *);
int main(int, char *[]);

/* Global variables. */
char *stack;                    /* pointer to signal stack base. */
int tooksig = 0;                /* 1 after we take the signal. */
jmp_buf env;

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  struct sigaction signals;
  struct sigaltstack ss;
  struct rlimit limits;
  /* Set stack size limit to 50 kBytes. */
  if(getrlimit(RLIMIT_STACK, &limits) >= 0) {
    if(limits.rlim_cur > (50 * STACKSIZE)) {
      limits.rlim_cur = 50 * STACKSIZE;
    }
    if(setrlimit(RLIMIT_STACK, &limits) >= 0) {
      /*
       * Take illegal instruction and process it with handler,
       * on the interrupt stack.
       */
      signals.sa_mask = 0;
      signals.sa_sigaction = handler;
      signals.sa_flags = SA_ONSTACK;
      if(sigaction(SIGILL, &signals, NULL) >= 0) {
	/*
	 * Allocate memory for the signal stack.  The
	 * kernel assumes the addresses grow in the same
	 * direction as the process stack.
	 */
	if((stack = (char *) malloc(sizeof(char *) * STACKSIZE)) != NULL) {
	  /*
	   * Issue the call to tell the system about the
	   * signal stack.  We pass the end of the signal
	   * stack, no the beginning, since the stack
	   * grows toward higher addresses.
	   */
	  ss.ss_size = STACKSIZE;
	  ss.ss_sp = (void *) stack;
	  if(sigaltstack(&ss, NULL) >= 0) {
	    /* Start using the stack. */
	    ret = EXIT_SUCCESS;
	    fn();
	  } else {
	    fprintf(stderr, "Cannot configure alternate signal stack.\n");
	  }
	} else {
	  fprintf(stderr, "Out of memory!\n");
	}
      } else {
	fprintf(stderr, "Cannot configure SIGILL signal handling.\n");
      }
    } else {
      fprintf(stderr, "Could not set process current stack limit.\n");
    }
  } else {
    fprintf(stderr, "Could not get process current stack limit.\n");
  }
  exit(ret);
}

void handler(int sig, siginfo_t *mask, void *d)
{
  struct rlimit limits;
  /* Increase the stack limit to the maximum. */
  if(getrlimit(RLIMIT_STACK, &limits) >= 0) {
    limits.rlim_cur = limits.rlim_max;
    if(setrlimit(RLIMIT_STACK, &limits) >= 0) {
      tooksig = 1;
      ret = EXIT_SUCCESS;
      return;
    } else
      fprintf(stderr, "Could not set current stack limit.\n");
  } else
    fprintf(stderr, "Could not get current stack limit.\n");
  exit(EXIT_FAILURE);
}

void fn(void)
{
  /* Take up 5 kBytes of space on stack. */
  printf("%s\n", tooksig ? "Now on extended stack." : "On 50 kBytes stack.");
  /* Recurse. */
  fn();
}

/* End of sigstack.c file. */
