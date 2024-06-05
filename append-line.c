/* -*- mode: c-mode; -*- */

/* append-line.c file. */
#include <stdio.h>
#include <stdlib.h>

/* append-line program. */
/* Functions prototype. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  FILE *from, *to;
  char line[ BUFSIZ ];
  /* Check our arguments. */
  if(argc != 3) {
    fprintf(stderr, "Usage: %s from-file to-file\n", *argv);
    exit(1);
  }
  /* Open the from-file for reading. */
  if((from = fopen(argv[ 1 ], "r")) == NULL) {
    perror(argv[ 1 ]);
    exit(1);
  }
  /*
   * Open the to-file for appending.  If to-file does
   * not exist, fopen will create it.
   */
  if((to = fopen(argv[ 2 ], "a")) == NULL) {
    perror(argv[ 2 ]);
    exit(1);
  }
  /*
   * Now read a line at a time from from-file
   * and write it to the to-file.
   */
  while(fgets(line, BUFSIZ, from) != NULL)
    fputs(line, to);
  /* Now close the files. */
  fclose(to);
  fclose(from);
  exit(0);
}

/* End of append-line.c file. */
