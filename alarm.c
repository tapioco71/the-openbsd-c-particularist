/* -*- mode: c-mode; -*- */
/*
 * alarm.c program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define FOREVER for(;;)

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
  SIGALRM,
  SA_SIGINFO
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
  if(sigaction(SIGALRM, &sa, NULL) >= 0) {
    alarm(15);
    ret = EXIT_SUCCESS;
    FOREVER {
      printf("Waiting!\n");
      pause(5);
    }
  } else
    perror("Could not setup SIGINT");
  exit(ret);
}

void handler(int si)
{
  /*
   * Handler code
   */
  if(si == SIGALRM)
    printf("Alarm received.\n");
}

/* End of file alarm.c */
