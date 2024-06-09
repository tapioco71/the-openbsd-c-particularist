/* -*- mode: c-mode; -*- */

/* stopproc.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/proc.h>

/* stopproc program. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char * argv[])
{
  int status;
  long int ret = EXIT_FAILURE;
  pid_t pid;
  struct pgrp *pgrp = NULL;

  /* fork */
  if((pid = fork()) >= 0) {

    /* Child execute code if pid == 0. */
    printf("Child executed!\n");
    _exit(EXIT_SUCCESS);
  } else {

    /* Parent executes otherwise. */
    printf("Parent waiting.\n");
    while(wait(&status) != pid)
      ;
    printf("Parent waited for child to finish.\n");
  }
  exit(EXIT_SUCCESS);
}

/* End of stopproc.c file. */
