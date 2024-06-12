/* -*- mode: c-mode; -*- */

/* File mqclient.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* mqclient program. */
#define MSGSZ 128
#define FOREVER for(;;)

/* Declare the message structure. */
struct tagMessage {
  long mtype;
  char mtext[ MSGSZ ];
};

typedef struct tagMessage message_t;

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  int msqid;
  key_t key;
  message_t sbuf, rbuf;

  /* Create a message queue with "name" 1234. */
  key = 1234;

  /*
   * Get the message queue id for the
   * "name" 1234, which was created by
   * the server.
   */
  if((msqid = msgget(key, 0666)) >= 0) {

    /*
     * We'll send message type 1, the server
     * will send message type 2.
     */
    sbuf.mtype = 1;
    snprintf(sbuf.mtext, MSGSZ, "Did you get this?");

    /* Send message. */
    if(msgsnd(msqid, &sbuf, strnlen(sbuf.mtext, MSGSZ) + 1, 0) >= 0) {

      /* Receive an answer of message type 2. */
      if(msgrcv(msqid, &rbuf, strnlen(rbuf.mtext, MSGSZ) + 1, 2, 0) >= 0) {

	/* Print the answer. */
	printf("%s\n", rbuf.mtext);
	ret = EXIT_SUCCESS;
      } else
	perror("msgrcv");
    } else
      perror("msgsnd");
  } else
    perror("msgget");

  /* Exit. */
  exit(ret);
}

/* End of mqclient.c file. */
