/* -*- mode: c-mode; -*- */

/* File servent.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

/* servent program. */
#define FOREVER for(;;)

/* Function prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i;
  char **alias;
  long int ret = EXIT_FAILURE;
  struct servent *service;

  /* Check the arguments. */
  if(argc == 3) {

    /* Get the specified services from the database. */
    if((service = getservbyname(argv[ 1 ], argv[ 2 ])) != NULL) {
      printf("official service name: %s\n", service -> s_name);
      printf("alias list: ");
      alias = service -> s_aliases;
      while(*alias)
	printf("%s ", *alias++);
      printf("\n");
      printf("port: 0x%0.4x\n", service -> s_port);
      printf("protocol: %s\n", service -> s_proto);
      ret = EXIT_SUCCESS;
    } else
      fprintf(stderr,							\
	      "Service %s with protocol %s not found in services database.\n", \
	      argv[ 1 ],						\
	      argv[ 2 ]);
  } else
    fprintf(stderr, "Usage servent <service name> <protocol name>\n");
  exit(ret);
}

/* End of hostent.c file. */
