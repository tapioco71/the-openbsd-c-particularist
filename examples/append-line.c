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
  long int ret = EXIT_FAILURE;

  /* Check our arguments. */
  if(argc == 3) {

    /* Open the from-file for reading. */
    if((from = fopen(argv[ 1 ], "r")) != NULL) {

      /*
       * Open the to-file for appending.  If to-file does
       * not exist, fopen will create it.
       */
      if((to = fopen(argv[ 2 ], "a")) != NULL) {

	/*
	 * Now read a line at a time from from-file
	 * and write it to the to-file.
	 */
	while(fgets(line, BUFSIZ, from) != NULL)
	  fputs(line, to);

	/* Now close output file. */
	fclose(to);

	/* Signal no errors to the shell. */
	ret = EXIT_SUCCESS;
      } else
	perror(argv[ 2 ]);

      /* Now close input file. */
      fclose(from);
    } else
      perror(argv[ 1 ]);
  } else
    fprintf(stderr, "usage: %s from-file to-file\n", *argv);
  exit(ret);
}

/* End of append-line.c file. */
