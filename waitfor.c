/* -*- mode: c-mode; -*- */

/* waitfor.c file. */
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

/* waitfor program. */
#define FOREVER for(;;)

/* Functions prototypes. */
void waitfor(void);
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
    SIGQUIT,
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
    if(sigaction(SIGQUIT, &signal, NULL) >= 0) {
      pgrp = getpgrp();
      printf("Parent waiting 5 seconds before make its child quit.\n");
      sleep(5);
      if(killpg(pgrp, SIGQUIT) >= 0) {
	printf("Parent make its child quit.\n");
	while(wait(&status) != pid)
	  ;
	printf("Child quitted!\n");
	ret = EXIT_SUCCESS;
      } else
	perror("killpg");
    } else
      perror("sigaction");
  }
  exit(ret);
}

void waitfor(void)
{
  int pid;
  int status;
  extern struct processlist allprocess;
  struct pgrp grp;

  /* */
  while((pid = wait4(WAIT_MYPGRP, &status, WUNTRACED, NULL)) >= 0) {
    LIST_FOREACH(grp, LIST_HEAD(processlist, allprocess), ps_pid) {
      ;
    }
  }
}

/* End of waitfor.c file. */
