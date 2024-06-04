/* -*- mode: c-mode; -*- */
/*
 * timeout.c program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>

#define FOREVER for(;;)

/*
 * Functions prototypes.
 */
int timeout(int);
int main(int, char *[]);
/*
 * Global variables.
 */
struct sigaction sa = {
  timeout,
  SIGALRM,
  SA_SIGINFO | SA_RESETHAND
};
jmp_buf env;

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  char buff[ BUFSIZ ];
  long int ret = EXIT_FAILURE;
  /*
   * setup signal handler for this process.
   */
  if(sigaction(SIGALRM, &sa, NULL) >= 0) {
    /*
     * The code inside the if gets executed the first
     * time through setjmp, the code inside the else
     * the second time.
     */
    if(setjmp(env) == 0) {
      /*
       * Issue a request for an alarm to be
       * delivered in 15 seconds.
       */
      alarm(15);
      /*
       * Prompt for input.
       */
      printf("Type a word: if you don't in 15 seconds I'll use \"WORD\": ");
      fgets(buff, BUFSIZ, stdin);
      /*
       * Turns off the alarm.
       */
      alarm(0);
      ret = EXIT_SUCCESS;
    } else {
      strncpy(buff, "WORD", BUFSIZ);
    }
    printf("\nThe word is %s.\n", buff);
  } else
    perror("Could not setup SIGINT");
  exit(ret);
}

int timeout(int sig)
{
  /*
   * Ignore the signal for the duration of this
   * routine.
   */
  sigaction(sig, SIG_IGN, NULL);
  /*
   * We would perform any timeout-related
   * functions here; in this case there
   * are none.
   */
  ;
  /*
   * Restore the action of the alarm signal.
   */
  sigaction(SIGALRM, &sa, NULL);
  /*
   * Return to the main routine at setjmp
   * and make setjmp return 1.
   */
  longjmp(env, 1);
}

/* End of file timeout.c */
