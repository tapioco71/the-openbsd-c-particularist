/* -*- mode: c; -*- */

/* ezshell.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Some general usage macros. */
#define FOREVER for(;;)
#define BUFFER_SIZE 1024
#define ARGS_SIZE 64

/* ezshell program. */
/* Functions prototypes. */
long int execute(char *[]);
void parse(char *, char *[]);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char buff[ BUFFER_SIZE ];
  char *args[ ARGS_SIZE ];
  long int ret = EXIT_SUCCESS;
  /* */
  do {

    /* Prompt for read a command. */
    printf("Command: ");
    if(fgets(buff, BUFFER_SIZE, stdin) != NULL) {

      /* Split the string into arguments. */
      parse(buff, args);
      ret = execute(args);
    } else {
      printf("\n");
      ret = EXIT_FAILURE;
    }
  } while(ret != EXIT_FAILURE);
  exit(ret);
}

/*
 * parse -- split the command in buff into
 *          individual arguments.
 */
void parse(char *buff, char *args[])
{
  while(*buff != '\0') {
    /*
     * Strip whitespace.  Use nulls, so
     * that the previous argument is tewrminated
     * automatically.
     */
    while((*buff == ' ') ||			\
	  (*buff == '\t') ||			\
	  (*buff == '\n'))
      *buff++ = '\0';

    /* Save the argument. */
    *args++ = buff;

    /* Skip over the argument. */
    while((*buff != '\0') &&					\
	  (*buff != ' ') &&					\
	  (*buff != '\t') &&					\
	  (*buff != '\n'))
      buff++;
  }
  *args = '\0';
}

/*
 * execute -- spawn a child process and execute
 *            the program.
 */
long int execute(char *args[])
{
  int pid, status;
  long int ret = EXIT_FAILURE;

  /* Get a child process. */
  if((pid = fork()) >= 0) {
    if(pid == 0) {
      printf("Executing: %s with pid %d\n", *args, pid);
      if(execvp(*args, args) < 0)
	perror("execvp");
      perror(*args);
      ret = EXIT_FAILURE;
    }

    /* The parent executes the wait. */
    while(wait(&status) != pid)
      /* empty ... */
      ;
    ret = EXIT_SUCCESS;
  } else {
    perror("fork");
  }
  return ret;
}

/* End of ezshell.c file. */
