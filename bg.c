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
void handler(int, siginfo_t *, void *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char * argv[])
{
  int n;
  int pgrp;
  int tpgrp;
  int status;
  long int ret = EXIT_FAILURE;
  pid_t pid;
  struct sigaction signals;

  /* fork */
  pid = fork();
  if(pid == 0) {

    /* Child execute code if pid == 0. */
    printf("Child executed!\n");
    n = 1;
    FOREVER {
      printf("Client output: %d\n", n++);
      sleep(1);
    }
    _exit(EXIT_SUCCESS);
  } else if(pid > 0) {

    /* Parent executes otherwise. */
    signals.sa_sigaction = handler;
    if(sigfillset(&signals.sa_mask) >= 0) {
      if(sigdelset(&signals.sa_mask, SIGTTOU) >= 0) {
	pgrp = getpgrp();
	printf("Child remains in foreground for 5 seconds.\n");
	sleep(5);

	/* Send background write request to the child. */
	if(killpg(pgrp, SIGTTOU) >= 0) {
	  printf("Parent waiting 10 seconds before make its child quit.\n");
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
	perror("sigdelset");
    } else
      perror("sigfillset");
  } else
    perror("fork");
  exit(ret);
}

void handler(int sig, siginfo_t *mask, void *d)
{
  ;
}

/* End of bg.c file. */
