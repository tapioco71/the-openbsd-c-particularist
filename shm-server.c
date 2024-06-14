/* -*- mode: c-mode; -*- */

/* File shm-server.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* shm-server program. */
#define FOREVER for(;;)
#define SHMSZ 32

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char c;
  char *shm, *s;
  int shmid;
  long int ret = EXIT_FAILURE;
  key_t key;

  /*
   * We'll name our shared memory segment
   * "5678".
   */
  key = 5678;

  /* Create the segment. */
  if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) >= 0) {

    /* Now we attach the segment to our data space. */
    if((shm = shmat(shmid, NULL, 0)) >= 0) {

      /*
       * Now put some things into the memory for the
       * process to read.
       */
      s = shm;
      for(c = 'a'; c <= 'z'; c++)
	*s++ = c;
      *s = '\0';

      /*
       * Finally, we wait until the other process
       * changes the first character of our memory
       * to '*', indicating that it has read what
       * we put there.
       */
      while(*shm != '*')
	sleep(1);
      ret = EXIT_SUCCESS;
    } else
      perror("shmat");
  } else
    perror("shmget");
  exit(ret);
}

/* End of shm-server.c file. */
