/* -*- mode: c-mode; -*- */

/* File irc-client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* irc-client program. */
#define FOREVER for(;;)

/* Global variables. */
uint16_t ircports[] = {
  6660, 6661, 6662, 6663, 6664, 6665, 6666, 6667, 0
}
uint16_t sslircports[] = {
  6697, 0
}

/* Functions prototypes. */
long int client(struct sockaddr_in *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char servername[ BUFSIZ ];
  char portname[ BUFSIZ ];
  int res;
  long int ret;
  struct sockaddr_in serveraddress;
  struct hostent *host;

  /* Check parameters */
  switch(argc) {
  case 2:
    strncpy(servername, argv[ 1 ], BUFSIZ);
    portname[ 0 ] = '\0';
    break;

  case 3:
    strncpy(servername, argv[ 1 ], BUFSIZ);
    strncpy(portname, argv[ 2 ], BUFSIZ);
    break;

  default:
    fprintf(stderr, "usage: irc-client <server-name> [ <port> ]\n");
    exit(EXIT_FAILURE);
    break;
  }
  if((host = gethostbyname(servername)) != NULL) {
    printf("Address for %s: 0x%0.8x\n", serveraddress, host -> h_addr_list[ 0 ]);
    ret = EXIT_SUCCESS;
  } else
    perror("gethostbyname");

  /*
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);
  res = inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
  ret = client(&servaddr);
  */
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
      if(connect(sockfd,				\
		 (struct sockaddr *) sa,		\
		 sizeof(struct sockaddr_in)) >= 0) {
	printf("Connected to 0x%0.8x, port 0x%0.4x\n",	\
	       sa -> sin_addr,				\
	       ntohs(sa -> sin_port));
	if(recv(sockfd, (void *) buff, BUFSIZ, MSG_WAITALL) >= 0) {
	  printf("Received data from server: %s\n", buff);
	  ret = EXIT_SUCCESS;
	} else
	  perror("recv");
      } else
	perror("connect");
      close(sockfd);
    } else
      perror("socket");
  } else
    fprintf(stderr, "NULL address passed.\n");
  return ret;
}

/* End of irc-client.c file. */
