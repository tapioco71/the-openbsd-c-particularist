/* -*- mode: c; -*- */

/* File arguments2.c. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main (int argc, char *argv[])
{
  int c;
  int digit_optind = 0;
  int aopt = 0, bopt = 0;
  int nReturnValue = EXIT_FAILURE;
  char *copt = 0, *dopt = 0;
  const char options[] = "abc:d:h012";

  /* */
  while ((c = getopt(argc, argv, options)) != -1) {
    int this_option_optind = optind ? optind : 1;
    switch(c) {
    case '0':
    case '1':
    case '2':
      if(digit_optind != 0 && digit_optind != this_option_optind) {
	printf ("digits occur in two different argv-elements.\n");
      }
      digit_optind = this_option_optind;
      printf ("option %c\n", c);
      nReturnValue = EXIT_SUCCESS;
      break;
      
    case 'a':
      printf ("option a\n");
      aopt = 1;
      break;
      
    case 'b':
      printf ("option b\n");
      bopt = 1;
      break;
      
    case 'c':
      printf ("option c with value '%s'\n", optarg);
      copt = optarg;
      break;
      
    case 'd':
      printf ("option d with value '%s'\n", optarg);
      dopt = optarg;
      break;

    case 'h':
      printf("%s [-abcd argument] ...\n", argv[ 0 ]);
      printf("%s [ -h ]\n", argv[ 0 ]);
      exit(nReturnValue);
      break;
      
    case '?':
      break;
      
    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
    }
  }
  if(optind < argc) {
    printf ("non-option ARGV-elements: ");
    while (optind < argc) {
      printf ("%s ", argv[optind++]);
    }
    printf ("\n");
  }
  exit(nReturnValue);
}

/* End of arguments2.c file. */
