/* -*- mode: c-mode; -*- */

/* stopproc.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/proc.h>
#include <sys/wait.h>

/* stopproc program. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char * argv[])
{
  int pgrp;
  int status;
  long int ret = EXIT_FAILURE;
  pid_t pid;
  struct sigaction signal = {
    SIG_IGN,
    SIGKILL,
  };
  /* fork */
  if((pid = fork()) == 0) {

    /* Child execute code if pid == 0. */
    printf("Child executed!\n");
    FOREVER {
      ;
    }
    _exit(EXIT_SUCCESS);
  } else {

    /* Parent executes otherwise. */
    if(sigaction(SIGKILL, &signal) >= 0) {
      pgrp = getpgrp();
      printf("Parent waiting 5 seconds before kill its child.\n");
      sleep(5);
      if(killpg(pgrp, SIGKILL) >= 0) {
	printf("Parent killed its child.\n");
	while(wait(&status) != pid)
	  ;
	printf("Child killed!\n");
	ret = EXIT_SUCCESS;
      } else
	perror("killpg");
    } else
      perror("sigaction");
  exit(ret);
}

/* End of stopproc.c file. */
