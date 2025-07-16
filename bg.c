/* -*- mode: c; -*- */

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
void handler(int);
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
  struct sigaction signal = {
    handler,
    SIGTTOU,
    SA_SIGINFO
  };

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
    pgrp = getpgrp();
    printf("Child remains in foreground for 5 seconds.\n");
    sleep(5);

    if(sigaction(SIGTTOU, &signal, NULL) >= 0) {
      /* Send background write request to the child. */
      if(killpg(pgrp, SIGTTOU) >= 0) {
	printf("Parent waiting 10 seconds before kills its child.\n");
	sleep(10);
	if(killpg(pgrp, SIGKILL) >= 0) {
	  printf("Parent kills its child.\n");
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
  } else
    perror("fork");
  exit(ret);
}

void handler(int sig)
{
  printf("Received SIGTTOU.\n");
}

/* End of bg.c file. */
