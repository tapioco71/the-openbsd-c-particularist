/* -*- mode: c; -*- */

/* append-char.c file. */
#include <stdio.h>
#include <stdlib.h>

/* append-char program. */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int c;
  long int ret = EXIT_FAILURE;
  FILE *from, *to;


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
	 * Now read characters from from-file until we
	 * hit end-of-file, and put  them onto to-file.
	 */
	while((c = getc(from)) != EOF)
	  putc(c, to);

	/* Now close the output file. */
	fclose(to);
	ret = EXIT_SUCCESS;
      } else
	perror(argv[ 2 ]);

      /* Now close the input file. */
      fclose(from);
    } else
      perror(argv[ 1 ]);
  } else
    fprintf(stderr, "usage: %s from-file to-file\n", *argv);
  exit(ret);
}

/* End of append-char.c file. */
