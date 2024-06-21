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
 * executeServerCommand - fullfill a server request.
 */
long int executeServerCommand(int fd, command_t command)
{
  char buff[ BUFSIZ ];
  long int ret = EXIT_FAILURE;
  size_t i;

  /* Check arguments. */
  if(fd >= 0) {
    printf("Command name: %s, ", command.c_name);
    printf("Parameter: %s\n", command.c_parameters[ 0 ]);
    if(strncmp(command.c_name, "PING", 4) == 0) {
      snprintf(buff, BUFSIZ, "PONG :%s", command.c_parameters[ 0 ]);
      printf("%s\n", buff);
      sendCommand(fd, buff);
      ret = EXIT_SUCCESS;
    }
    for(i = 0; command.c_parameters[ i ] != NULL; i++)
      free(command.c_parameters[ i ]);
    free(command.c_parameters);
  }
  return ret;
}
/*
 * decodeServerAnswer - decode the server answer.
 */
long int decodeServerAnswer(char *buff, answer_t *answer)
{
  char temp[ PARAMETERLENGTH ];
  long int ret = EXIT_FAILURE;

  /* Check arguments. */
  if(buff) {
    if(answer) {
      bzero(answer, sizeof(answer_t));
      if(buff[ 0 ] == ':') {
	answer -> a_type = 0;
	strncpy(&answer -> a_message[ 0 ], &buff[ 0 ], MESSAGELENGTH);
	ret = EXIT_SUCCESS;
      } else if(((buff[ 0 ] >= 'a') && (buff[ 0 ] <= 'z')) ||
		((buff[ 0 ] >= 'A') && (buff[ 0 ] <= 'Z'))) {
	answer -> a_type = 1;
	sscanf(&buff[ 0 ], "%s :%s", &answer -> a_command.c_name, temp);
	answer -> a_command.c_parameters = (char **) malloc(sizeof(char) * 2);
	answer -> a_command.c_parameters[ 0 ] = (char *) malloc(sizeof(char) * PARAMETERLENGTH);
	answer -> a_command.c_parameters[ 1 ] = NULL;
	strncpy(answer -> a_command.c_parameters[ 0 ], temp, PARAMETERLENGTH);
	ret = EXIT_SUCCESS;
      }
    }
  }
  return ret;
}

/*
 * sendCommand -- send a command string to server.
 */
long int sendCommand(int fd, char *cmd)
{
  char command[ BUFSIZ ];
  long int ret = EXIT_FAILURE;

  /* Check argument. */
  if(fd >= 0) {
    if(cmd) {

#ifdef DEBUG
      printf("Client sending command string: \"%s\"\n", cmd);
#endif

      bzero(command, BUFSIZ);
      snprintf(command, BUFSIZ, "%s\n\r", cmd);
      if(write(fd, command, strlen(command)) >= 0)
	ret = EXIT_SUCCESS;
      else
	perror("write");
    }
  }
  return ret;
}

/*
 * getServerAnswer -- receive the server answer.
 */
long int getServerAnswer(int fd, char *buff, size_t length)
{
  bool bRead;
  size_t position, stop;
  long int ret = EXIT_FAILURE;

  /* Check arguments. */
  if(fd >= 0) {
    if(buff) {
      if(length > 0) {
	bRead = true;
	position = 0;
	bzero(buff, length);
	do {
	  if(read(fd, &buff[ position ], 1) >= 0) {
	    if(buff[ position ] == '\r')
	      stop = position;
	    if((buff[ position ] == '\n') || (buff[ position ] == '\0')) {
	      buff[ stop ] = '\0';
	      ret = EXIT_SUCCESS;
	      bRead = false;
	    } else {
	      if(position < length) {
		++position;
	      } else {
		bRead = false;
	      }
	    }
	  } else
	    bRead = false;
	} while(bRead);
      }
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
	       sa -> sin_addr.s_addr,			\
	       ntohs(sa -> sin_port));
	bRun = true;
	while(bRun) {
	  switch(state) {
	  case IDLE:
	    state = END;
	    printf("Idle state.\n");
	    //state = START_REGISTRATION;
	    state = SEND_NICK;
	    break;

	  case SEND_NICK:
	    {
	      answer_t answer;

	      /* */
	      state = END;
	      printf("Send nick state.\n");
	      bzero(buff, BUFSIZ);
	      snprintf(buff, BUFSIZ, "NICK %s", nickname);
	      if(sendCommand(sockfd, buff) == EXIT_SUCCESS) {
		if(getServerAnswer(sockfd, buff, BUFSIZ) == EXIT_SUCCESS) {
		  printf("Server answer: %s\n", buff);
		  if(decodeServerAnswer(buff, &answer) == EXIT_SUCCESS) {
		    switch(answer.a_type) {
		    case 0:
		      printf("%s", answer.a_message);
		      break;

		    case 1:
		      executeServerCommand(sockfd, answer.a_command);
		      break;
		    }
		    state = SEND_USER;
		  }
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
	    {
	      int start = 0;
	      int end = 0;
	      int position = 0;
	      long int s;
	      answer_t answer;

	      /* */
	      state = END;
	      bzero(buff, BUFSIZ);
	      snprintf(buff, BUFSIZ, "USER %s 0 * :%s", username, realname);
	      if(sendCommand(sockfd, buff) == EXIT_SUCCESS) {
		state = REPL;
	      } else {
		strncpy(error, "USER command failed.", BUFSIZ);
		state = ERROR;
	      }
	    }
	    break;

	  case REPL:
	    {
	      answer_t answer;

	      /* */
	      bzero(buff, BUFSIZ);
	      state = ERROR;
	      if(getServerAnswer(sockfd, buff, BUFSIZ) == EXIT_SUCCESS) {
		if(decodeServerAnswer(buff, &answer) == EXIT_SUCCESS) {
		  switch(answer.a_type) {
		  case 0:
		    printf("%s\n", answer.a_message);
		    break;

		  case 1:
		    executeServerCommand(sockfd, answer.a_command);
		    break;
		  }
		  state = REPL;
		}
	      }
	    }
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
