/* -*- mode: c-mode; -*- */

/* File irc-client.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define FOREVER for(;;)

enum tagIRCNumerics {
  RPL_WELCOME = 1,
  RPL_YOURHOST,
  RPL_CREATED,
  RPL_MYINFO,
  RPL_ISUPPORT,
  RPL_BOUNCE = 10,
  RPL_STATSCOMMANDS = 212,
  RPL_ENDOFSTATS = 219,
  RPL_UMODEIS = 221,
  RPL_STATSUPTIME = 242,
  RPL_LUSERCLIENT = 251,
  RPL_LUSEROP = 252,
  RPL_LUSERUNKNOWN = 253,
  RPL_LUSERCHANNELS = 254
};

enum tagStates {
  IDLE = 0,
  START_REGISTRATION,
  SEND_PASS,
  SEND_NICK,
  CAPABILITY_REQUEST,
  SEND_USER,
  END_REGISTRATION,
  ERROR,
  END
};

typedef enum tagIRCNumerics IRCNumerics_t;
typedef enum tagStates states_t;

/* Functions prototypes. */
long int sendCommand(int, char *);
long int client(struct sockaddr_in *);
int main(int, char *[]);

/* End of irc-client.h file. */
