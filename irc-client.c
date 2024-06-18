/* -*- mode: c-mode; -*- */

/* File irc-client.c */
#include "includes/irc-client.h"

/* Global variables. */
char nickname[] = "antani";
char username[] = "blinda";
char realname[] = "la barella";
uint16_t ircports[] = {
  6660, 6661, 6662, 6663, 6664, 6665, 6666, 6667, 0
};
uint16_t sslircports[] = {
  6697, 0
};

/* Main function. */
int main(int argc, char *argv[])
{
  char addressname[ BUFSIZ ];
  char addressstring[ BUFSIZ ];
  char servername[ BUFSIZ ];
  char portname[ BUFSIZ ];
  const char *errstr;
  int i, res;
  long int ret;
  struct sockaddr_in serveraddress;
  struct hostent *host;
  uint16_t port;

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
  if((host = gethostbyname2(servername, AF_INET)) != NULL) {
    if(h_errno == NETDB_SUCCESS) {
      memcpy(addressname, host -> h_addr_list[ 0 ], host -> h_length);
      printf("host %s: ", host -> h_name);
      for(i = 0; i < host -> h_length; i++) {
	if(i == 0)
	  snprintf(addressstring, BUFSIZ, "%u", (uint8_t) addressname[ i ]);
	else
	  snprintf(addressstring, BUFSIZ, "%s.%u", addressstring, (uint8_t) addressname[ i ]);
      }
      printf("%s\n", addressstring);
      if(inet_pton(AF_INET, addressstring, &serveraddress.sin_addr) > 0) {
	port = 0;
	if(portname[ 0 ] != '\0') {
	  if((port = strtonum(portname, 0, 65535, &errstr)) == 0) {
	    perror("strtonum");
	  }
	} else
	  port = htons(ircports[ 7 ]);
	if(port > 0) {
	  printf("server port: %d\n", port);
	  serveraddress.sin_family = AF_INET;
	  serveraddress.sin_port = htons(port);
	  ret = client(&serveraddress);
	} else {
	  fprintf(stderr, "Wrong port specification.\n");
	}
      } else
	perror("inet_pton");
    } else
      fprintf(stderr, "h_errno: %d\n", h_errno);
  } else
    perror("gethostbyname");
  exit(ret);
}

/*
 * sendCommand -- send a command string to server.
 */

long int sendCommand(int fd, char *cmd)
{
  char command[ BUFSIZ ];
  long int ret = EXIT_FAILURE;

  /* Check argument. */
  if(fd > 0) {
    if(cmd) {
      bzero(command, BUFSIZ);
      printf("Send command: %s\n", cmd);
      snprintf(command, BUFSIZ, "%s\n\r", cmd);
      if(write(fd, command, strlen(command)) > 0)
	ret = EXIT_SUCCESS;
    }
  }
  return ret;
}

/*
 * getAnswer -- receive the server answer.
 */

long int getAnswer(int fd, char *answer, size_t length)
{
  int count;
  long int ret = EXIT_FAILURE;

  /* Check arguments. */
  if(answer) {
    if(length > 0) {
      bzero(answer, BUFSIZ);
      if((count = read(fd, answer, length)) > 0) {
	printf("Received data from server: %s\n", answer);
	ret = EXIT_SUCCESS;
      } else
	perror("recv");
    }
  }
  return ret;
}

/*
 * client -- the client function.
 */
long int client(struct sockaddr_in *sa)
{
  bool bRun;
  int sockfd;
  states_t state = IDLE;
  long int ret = EXIT_FAILURE;
  char buff[ BUFSIZ ];
  char error[ BUFSIZ ];

  /* Check function argument. */
  if(sa) {
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
      printf("Created socket: %d\n", sockfd);
      if(connect(sockfd,				\
		 (struct sockaddr *) sa,		\
		 sizeof(struct sockaddr_in)) >= 0) {
	printf("Connected to 0x%0.8x, port 0x%0.4x\n",	\
	       (size_t) sa -> sin_addr.s_addr,			\
	       ntohs(sa -> sin_port));
	bRun = true;
	while(bRun) {
	  switch(state) {
	  case IDLE:
	    printf("Idle state.\n");
	    bzero(error, BUFSIZ);
	    state = START_REGISTRATION;
	    break;

	  case START_REGISTRATION:
	    {
	      int answer;

	      /* */
	      state = END;
	      printf("Registration state.\n");
	      if(sendCommand(sockfd, "CAP LS 302") == EXIT_SUCCESS) {
		if(getAnswer(sockfd, buff, BUFSIZ) == EXIT_SUCCESS) {
		  printf("Server answer: %s\n", buff);
		  if(sscanf(buff, "%d ", &answer) > 0) {
		    snprintf(error, "code %d.", answer);
		    state = ERROR;
		  } else
		    state = SEND_PASS;
		} else {
		  strncpy(error, "answer to CAP command.", BUFSIZ);
		  state = ERROR;
		}
	      } else {
		strncpy(error, "CAP command failed.", BUFSIZ);
		state = ERROR;
	      }
	    }
	    break;

	  case SEND_PASS:
	    printf("Send password state.\n");
	    state = SEND_NICK;
	    break;

	  case SEND_NICK:
	    {
	      char number[ BUFSIZ ];
	      /* */
	      state = END;
	      printf("Send nick state.\n");
	      bzero(buff, BUFSIZ);
	      snprintf(buff, BUFSIZ, "NICK %s", nickname);
	      if(sendCommand(sockfd, buff) == EXIT_SUCCESS) {
		if(getAnswer(sockfd, buff, BUFSIZ) == EXIT_SUCCESS) {
		  printf("Server answer: %s\n", buff);
		  if(strncmp(buff, "PING", 4) == 0) {
		    sscanf(&buff, "PING :%s", number);
		    snprintf(buff, BUFSIZ, "PONG :%s", number);
		    sendCommand(sockfd, buff);
		  }
		  state = SEND_USER;
		} else {
		  strncpy(error, "answer to NICK command.", BUFSIZ);
		  state = ERROR;
		}
	      } else {
		strncpy(error, "NICK command failed.", BUFSIZ);
		state = ERROR;
	      }
	    }
	    break;

	  case SEND_USER:
	    state = END;
	      printf("Send user state.\n");
	      bzero(buff, BUFSIZ);
	      snprintf(buff, BUFSIZ, "USER %s 0 * :%s", username, realname);
	      if(sendCommand(sockfd, buff) == EXIT_SUCCESS) {
		if(getAnswer(sockfd, buff, BUFSIZ) == EXIT_SUCCESS) {
		  printf("Server answer: %s\n", buff);
		  state = END_REGISTRATION;
		} else {
		  strncpy(error, "answer to USER command.", BUFSIZ);
		  state = ERROR;
		}
	      } else {
		strncpy(error, "USER command failed.", BUFSIZ);
		state = ERROR;
	      }
	      break;

	  case CAPABILITY_REQUEST:
	    printf("Capability request state.\n");
	    state = END;
	    break;
	    
	  case END_REGISTRATION:
	    printf("End registration state.\n");
	    state = END;
	    break;

	  case ERROR:
	    fprintf(stderr, "Error: %s\n", error);
	    state = END;
	    break;
	    
	  case END:
	    printf("Exiting state machine.\n");
	    bRun = false;
	    break;
	  }
	}
	

	/*
	bzero(buff, BUFSIZ);
	strncpy(buff, "CAP LS 302\r\n", BUFSIZ);
	if(send(sockfd, buff, strlen(buff), 0) >= 0) {
	  if(recv(sockfd, (void *) buff, BUFSIZ, MSG_WAITALL) >= 0) {
	    printf("Received data from server: %s\n", buff);
	    ret = EXIT_SUCCESS;
	  } else
	    perror("recv");
	} else
	  perror("sendto");
	*/

	
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
