/* -*- mode: c-mode; -*- */

/* File shm-client.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* shm-client program. */
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
   * We need to get the segment named
   * "5678", created by the server.
   */
  key = 5678;

  /* Locate the segment. */
  if((shmid = shmget(key, SHMSZ, 0666)) >= 0) {

    /* Now we attach the segment to our data space. */
    if((shm = shmat(shmid, NULL, 0)) >= 0) {

      printf("Server data at 0x%0.8x: ", (size_t) shm);
      /* Now we read what the server put in the memory. */
      for(s = shm; *s != '\0'; s++)
	putchar(*s);
      putchar('\n');

      /*
       * Finally, change the first character of the
       * segment to '*', indicating we have read
       * the segment.
       */
      *shm = '*';
      ret = EXIT_SUCCESS;
    } else
      perror("shmat");
  } else
    perror("shmget");
  exit(ret);
}

/* End of shm-client.c file. */
