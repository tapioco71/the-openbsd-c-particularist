/* -*- mode: c-mode; -*- */

/* append-buf.c file. */
#include <stdio.h>
#include <stdlib.h>

/* append-buf program. */
/* Functions prototypes. */
int main(int, char *[]);

/* The main function. */
int main(int argc, char *argv[])
{
  int n;
  FILE *from, *to;
  char buf[ BUFSIZ ];
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
	 * Now read a buffer-full at a time from from-file
	 * and write it to the to-file.
	 */
	while((n = fread(buf, sizeof(char), BUFSIZ, from)) > 0)
	  fwrite(buf, sizeof(char), n, to);

	/* Now close the output file. */
	fclose(to);

	/* Signal no errors to the shell. */
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

/* End of append-buf.c file. */
