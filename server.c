/* -*- mode: c-mode; -*- */

/* File server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* server program. */
#define SERVER_PORT 10240
#define FOREVER for(;;)

/* Functions prototypes. */
long int server(struct sockaddr_in *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret;
  struct sockaddr_in servaddr;

  /* clear the address structures in memory. */
  bzero(&servaddr, sizeof(struct sockaddr_in));

  /* setup structures. */
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr = htonl(INADR_ANY);
  servaddr.sin_port = htons(SERVER_PORT);
  ret = server(&servaddr);
  exit(ret);
}

/*
 * client -- the client function.
 */
long int server(struct sockaddr_in *sa)
{
  char *buff;
  int listenfd, connfd;
  long int ret = EXIT_FAILURE;
  struct timeval now;
  struct sockaddr_in cliaddr;
  socklen_t cliaddrlen = sizeof(struct sockaddr_in);
  pid_t pid;
  /* */
  if(sa) {
    bzero(&cliaddr, sizeof(struct sockaddr_in));
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
      if(bind(listenfd, (struct sockaddr *) sa, sizeof(struct sockaddr)) >= 0) {
	printf("Waiting to accept a connection...\n");
	if(listen(listenfd, LISTENQ) >= 0) {
	  FOREVER {
	    cliaddrlen = sizeof(cliaddr);
	    if((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &cliaddrlen)) >= 0) {
	      printf("Accepted connection from 0x%8d\n", cliaddr.sin_addr);
	      if((pid = fork()) == 0) {
		close(listenfd);
		if(gettimeofday(&now, NULL) >= 0) {
		  buff = ctime(&now.tv_sec);
		  if(buff) {
		    if(send(sockfd, (void *) buff, strnlen(buff, BUFSIZ), 0) >= 0) {
		      ret = EXIT_SUCCESS;
		      break;
		    } else {
		      perror("send");
		      break;
		    }
		  } else {
		    fprintf(stderr, "empty time string");
		    break;
		  }
		} else {
		  perror("gettimeofday");
		  break;
		}
	      }
	      close(connfd);
	    } else {
	      perror("accept");
	      break;
	    }
	  }
	} else {
	  perror("listen");
	  break;
	}
      } else
	perror("bind");
    } else
      perror("socket");
  } else
    fprintf(stderr, "NULL address passed.\n");
  return ret;
}

/* End of server.c file. */
