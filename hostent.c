/* -*- mode: c-mode; -*- */

/* File hostent.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

/* hostent program. */
#define FOREVER for(;;)

/* Function prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i;
  char **alias
  long int ret = EXIT_FAILURE;
  struct hostent *host;

  /* Check the arguments. */
  if(argc == 2) {

    /* Get the specified host from the database. */
    if((host = gethostbyname(argv[ 1 ], )) != NULL) {
      printf("official host name: %s\n", host -> h_name);
      printf("alias list: ");
      alias = host -> h_aliases;
      while(*alias)
	printf("%s ", *alias++);
      printf("\n");
      printf("address type: %d\n", host -> h_addrtype);
      printf("addresses: ");
      for(i = 0; i < host -> h_length; i++)
	printf("0x%0.8x ", host -> h_addr_list[ i ]);
      printf("\n");
      ret = EXIT_SUCCESS;
    } else
      fprintf(stderr, "Host %s not found in hosts database.\n");
  } else
    fprintf(stderr, "Usage hostent <hostname>\n");
  exit(ret);
}

/* End of hostent.c file. */
