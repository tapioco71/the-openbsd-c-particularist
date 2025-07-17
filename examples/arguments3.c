/* -*- mode: c; -*- */

/* File arguments3.c. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int c;
  int digit_optind = 0;
  int aopt = 0, bopt = 0;
  int nReturnValue = EXIT_FAILURE;
  char *copt = 0, *dopt = 0;
  static char options[] = "abc:d:f:hv012";
  static struct option long_options[] = {
    /* NAME      ARGUMENT           FLAG  SHORTNAME */
    { "add",     required_argument, NULL, 'a' },
    { "append",  no_argument,       NULL, 'b' },
    { "delete",  required_argument, NULL, 'd' },
    { "verbose", no_argument,       NULL, 'v' },
    { "create",  required_argument, NULL, 'c' },
    { "file",    required_argument, NULL, 'f' },
    { "help",    no_argument,       NULL, 'h' },
    { NULL,      0,                 NULL, 0 }
  };
  int option_index = 0;

  /* */
  while((c = getopt_long(argc, argv, options, long_options, &option_index)) != -1) {
    int this_option_optind = optind ? optind : 1;
    switch(c) {
      
    case 0:
      printf ("option %s", long_options[ option_index ].name);
      if(optarg) {
	printf (" with arg %s", optarg);
      }
      printf ("\n");
      break;
      
    case '0':
    case '1':
    case '2':
      if(digit_optind != 0 && digit_optind != this_option_optind) {
	printf("digits occur in two different argv-elements.\n");
      }
      digit_optind = this_option_optind;
      printf("option %c\n", c);
      nReturnValue = EXIT_SUCCESS;
      break;
      
    case 'a':
      printf("option a\n");
      aopt = 1;
      break;
      
    case 'b':
      printf("option b\n");
      bopt = 1;
      break;
      
    case 'c':
      printf("option c with value '%s'\n", optarg);
      copt = optarg;
      break;

    case 'd':
      printf("option d with value '%s'\n", optarg);
      dopt = optarg;
      break;

    case 'f':
      printf("option f with value '%s'\n", optarg);
      copt = optarg;
      break;
      
    case 'h':
      printf("Usage:\n\n");
      printf("%s [-a|--add] [-b|--append] [-c|--create argument] [-d|--delete argument] [-f|--file argument] [-v|--verbose] ... \n", argv[ 0 ]);
      printf("%s [-h]\n", argv[ 0 ]);
      exit(nReturnValue);
      break;

    case 'v':
      printf("option v\n");
      break;
      
    case '?':
      break;
      
    default:
      printf("?? getopt returned character code 0%o ??\n", c);
      break;
    }
  }
  if(optind < argc) {
    printf("non-option ARGV-elements: ");
    while(optind < argc) {
      printf("%s ", argv[optind++]);
    }
    printf("\n");
  }
  exit(nReturnValue);
}

/* End of arguments3.c file. */
