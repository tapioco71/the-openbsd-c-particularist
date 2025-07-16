/* -*- mode: c; -*- */

/* mailer.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Some general usage macros. */
#define FOREVER for(;;)
#define BUFFER_SIZE 1024
#define ARGS_SIZE 64

/* mailer program. */
/* Functions prototypes. */
char *getlogin(void);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char *username;
  int pid, pipefds[ 2 ];
  long int ret = EXIT_SUCCESS;
  FILE *fp;

  /* Get user's name. */
  if((username = getlogin()) != NULL) {

    /*
     * Create the pipe.  This has to be done
     * BEFORE the fork.
     */
    if(pipe(pipefds) >= 0) {
      if((pid = fork()) >= 0) {

	/*
	 * The child process executes  the stuff inside
	 * the if.
	 */
	if(pid == 0) {

	  /*
	   * Make the read  side of the pipe our
	   * standard input.
	   */
	  close(STDIN_FILENO);
	  dup(pipefds[ 0 ]);
	  close(pipefds[ 0 ]);

	  /*
	   * Close the write  side of the pipe;
	   * we'll let our output  go to the screen.
	   */
	  close(pipefds[ 1 ]);

	  /* Execute the command "mutt username". */
	  if(execl("/usr/local/bin/mutt",	\
		   "-s \"ERROR Messages\"",	\
		   "myemail@gmail.com",		\
		   "-a logFile.log",		\
		   NULL) >= 0) {
	  } else {
	    perror("execl");
	  }
	} else {

	  /* The parent executes this code. */
	  /*
	   * Close the read side of the pipe; we
	   * don't need it and the child is not
	   * writing on the pipe anyway.
	   */
	  close(pipefds[ 0 ]);

	  /* Convert the write side of the pipe to stdio. */
	  if((fp = fdopen(pipefds[ 1 ], "w")) != NULL) {

	    /* send a message. close the pipe. */
	    fprintf(fp, "Errors from your porgram.\n");
	    fclose(fp);
	    ret = EXIT_SUCCESS;
	    while(wait(NULL) != pid)
	      ;
	  } else {
	    perror("fdopen");
	  }
	}
      } else {
	perror("fork");
      }
    } else {
      perror("pipe");
    }
  } else {
    fprintf(stderr, "Who are you?\n");
  }
  exit(ret);
}

/* End of mailer.c file. */
