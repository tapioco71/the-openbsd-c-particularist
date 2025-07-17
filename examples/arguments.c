/* -*- mode: c; -*- */

/* File arguments.c. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Function prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int nReturnValue = EXIT_SUCCESS;
  char *p;
  int i;

  /* */
  printf("You provided %d options:\n", argc);
  for(i = 0; i < argc; i++)
    printf("option #%d: %s\n", i, argv[ i ]);
  exit(nReturnValue);
}

/* End of arguments.c file. */
