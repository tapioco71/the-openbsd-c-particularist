/* -*- mode: c-mode; -*- */

/* File client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* client program. */
#define FOREVER for(;;)

/* Functions prototypes. */
long int server(struct sockaddr_in *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int res;
  long int ret;
  struct sockaddr_in sa;
  /* */
  sa.sin_family = AF_INET;
  sa.sin_port = htons(1024);
  res = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);
  ret = server(&sa);
  exit(ret);
}

/*
 * client -- the client function.
 */
long int server(struct sockaddr_in *sa)
{
  int sockfd;
  long int ret = EXIT_FAILURE;
  char *buff[ BUFSIZ ];
  /* */
  if(sa) {
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
      if(bind(sockfd, (struct sockaddr *) sa, sizeof(struct sockaddr_in)) >= 0) {
	FOREVER {
	  printf("Waiting to accept a connection...\n");
	  if(accept(sockfd, (struct sockaddr *) sa, sizeof(struct sockaddr_in)) >= 0) {
	    printf("Accepted connection from %s\n", sa -> sin_addr);
	    ret = EXIT_SUCCESS;
	  } else
	    perror("connect");
	}
      } else
	perror("bind");
    } else
      perror("socket");
  } else
    fprintf(stderr, "NULL address passed.\n");
  return ret;
}

/* End of client.c file. */
