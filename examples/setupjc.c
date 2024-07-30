/* -*- mode: c-mode; -*- */

/* setupjc.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Some general usage macros. */
#define FOREVER for(;;)
#define BUFFER_SIZE 1024
#define ARGS_SIZE 64

/* Global variables. */
int npid;
int npgrp;
int ntermpgrp;

/* Functions prototypes. */
void setup(void);

/* setup function. */
void setup(void)
{
  /* Obtain shell's process id. */
  npid = getpid();

  /*
   * Just use pid for process group.  This is
   * not a requirement, just convenient.  Other
   * ways of picking a process group can be used.
   */
  npgrp = npid;
  ntermpgrp = npid;

  /* Set the shell's process group. */
  if(setpgid(npid, npgrp) >= 0) {
    if(ioctl(1, TIOCSPGRP, &npgrp) >= 0) {
      ;
    } else {
      perror("ioctl");
      exit(EXIT_FAILURE);
    }
  } else {
    perror("getpgid");
    exit(EXIT_FAILURE);
  }
}

/* End of setupjc.c file. */
