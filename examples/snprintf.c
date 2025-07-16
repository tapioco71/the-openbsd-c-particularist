/* -*- mode: c; -*- */

/* snprintf.c file. */
#include <stdio.h>
#include <stdlib.h>

/* snprintf test program. */
#define MAXLENGTH 16

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char divina[ MAXLENGTH + 1 ];
  char commedia[] = "Nel mezzo del cammin di nostra vita mi ritrovai per una selva oscura...";
  long int ret = EXIT_FAILURE;

  snprintf(divina, MAXLENGTH, "%s", commedia);
  printf("Source string: %s\n", commedia);
  printf("Destination string: %s\n", divina);
  exit(EXIT_SUCCESS);
}

/* End of snprintf.c file. */
