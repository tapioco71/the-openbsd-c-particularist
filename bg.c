/* -*- mode: c-mode; -*- */

/* bg.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/queue.h>
#include <sys/signal.h>
#include <sys/proc.h>
#include <sys/wait.h>

/* bg program. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char * argv[])
{
  int n;
  int pgrp;
  int status;
  long int ret = EXIT_FAILURE;
  pid_t pid;
  struct sigaction signal = {
    SIG_IGN,
    SIGQUIT,
  };
  /* fork */
  if((pid = fork()) == 0) {

    /* Child execute code if pid == 0. */
    printf("Child executed!\n");
    n = 1;
    FOREVER {
      printf("Client output: %d\n", n++);
      sleep(1);
    }
    _exit(EXIT_SUCCESS);
  } else {

    /* Parent executes otherwise. */
    if(sigaction(SIGQUIT, &signal, NULL) >= 0) {
      pgrp = getpgrp();
      printf("Child remains in foreground for 5 seconds.\n");
      sleep(5);
      if(killpg(pgrp, SIGCONT) >= 0) {
	printf("Parent waiting 5 seconds before make its child quit.\n");
	sleep(10);
	if(killpg(pgrp, SIGQUIT) >= 0) {
	  printf("Parent make its child quit.\n");
	  while(wait(&status) != pid)
	    ;
	  printf("Child quitted!\n");
	  ret = EXIT_SUCCESS;
	} else
	  perror("killpg");
      } else
	perror("killpg");
    } else
      perror("sigaction");
  }
  exit(ret);
}

/* End of bg.c file. */
