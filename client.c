/* -*- mode: c-mode; -*- */

/* File client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <resolv.h>
#include <sys/socket.h>

/* client program. */
#define FOREVER for(;;)

/* Functions prototypes. */
long int client(struct sockaddr_in *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int res;
  long int ret;
  char address[ 10 ] = "127.0.0.1";
  struct sockaddr_in sa;
  /* */
  sa.sin_family = AF_INET;
  sa.sin_port = htons(1024);
  res = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);
  ret = client(&addr);
  exit(ret);
}

/*
 * client -- the client function.
 */
long int client(struct sockaddr_in *sa)
{
  int sockfd;
  long int ret = EXIT_FAILURE;
  /* */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
    printf("Created socket: %d\n", sockfd);
    if(connect(sockfd, (struct sockaddr *) &sa, sizeof(sa)) >= 0) {
      if(shutdown(sockfd, SHUT_RDWR) >= 0) {
	;
	ret = EXIT_SUCCESS;
      } else
	perror("shutdown");
    } else
      perror("connect");
    close(sockfd);
  } else
    perror("socket");
  return ret;
}

/* End of client.c file. */
