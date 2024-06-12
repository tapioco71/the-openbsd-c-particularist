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
long int client(struct sockaddr_in *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int res;
  long int ret;
  struct sockaddr_in sa;
  /* */
  sa.sin_family = AF_INET;
  sa.sin_port = htons(10240);
  res = inet_pton(AF_UNIX, "127.0.0.1", &sa.sin_addr);
  ret = client(&sa);
  exit(ret);
}

/*
 * client -- the client function.
 */
long int client(struct sockaddr_in *sa)
{
  int sockfd;
  long int ret = EXIT_FAILURE;
  char *buff[ BUFSIZ ];
  /* */
  if(sa) {
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
      printf("Created socket: %d\n", sockfd);
      if(connect(sockfd, (struct sockaddr *) &sa, sizeof(struct sockaddr_in)) >= 0) {
	printf("Connected to %d, port %d\n",	\
	       sa -> sin_addr,			\
	       sa -> sin_port);
	if(shutdown(sockfd, SHUT_RDWR) >= 0) {
	  if(recv(sockfd, (void *) buff, BUFSIZ, MSG_WAITALL) >= 0) {
	    printf("Received data from server: %s\n", buff);
	    ret = EXIT_SUCCESS;
	  } else
	    perror("recv");
	} else
	  perror("shutdown");
      } else
	perror("connect");
      close(sockfd);
    } else
      perror("socket");
  } else
    fprintf(stderr, "NULL address passed.\n");
  return ret;
}

/* End of client.c file. */
