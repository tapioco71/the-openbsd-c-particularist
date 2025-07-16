/* -*- mode: c; -*- */

/* File mutex.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mutex.h>

/* shm-client program. */
#define FOREVER for(;;)
#define SHMSZ 32

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int counter, i, s;
  long int ret = EXIT_FAILURE;
  struct mutex mtx;
  pid_t pid;

  /* Clear the mutex object. */
  bzero(&mtx, sizeof(struct mutex));

  /* Initialize the mutex object. */
  mtx_init(&mtx, 0);
  pid = fork();
  if(pid == 0) {

    /* Child process. */
    FOREVER {
      s = rand();
      mtx_enter(&mtx);
      for(i = 0; i < s; i++)
	printf("Child counting: %d\n", counter++);
      mtx_leave(&mtx);
      sleep(s);
    }
    ret = EXIT_SUCCESS;
  } else if(pid > 0) {

    /* Parent process. */
    FOREVER {
      s = rand();
      mtx_enter(&mtx);
      for(i = 0; i < s; i++)
	printf("Parent counting: %d\n", counter++);
      mtx_leave(&mtx);
      sleep(s);
    }
    ret = EXIT_SUCCESS;
  } else
    perror("fork");
  exit(ret);
}

/* End of mutex.c file. */
