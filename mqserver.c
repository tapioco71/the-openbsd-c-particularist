/* -*- mode: c-mode; -*- */

/* File mqserver.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* mqserver program. */
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
   * We want to let everyone read and
   * write on this message queue, hence
   * we use 0666 as the permissions.
   */
  if((msqid = msgget(key, IPC_CREAT | 0666)) >= 0) {

    /* Receive a message. */
    if(msgrcv(msqid, &rbuf, MSGSZ, 0, 0) >= 0) {

      /* We send a message of type 2. */
      sbuf.mtype = 2;
      snprintf(sbuf.mtext, MSGSZ, "I received your message.");

      /* Send an answer. */
      if(msgsnd(msqid, &sbuf, strnlen(sbuf.mtext, MSGSZ) + 1, 0) >= 0) {
	ret = EXIT_SUCCESS;
      } else
	perror("msgsnd");
    } else
      perror("msgrcv");
  } else
    perror("msgget");

  /* Exit. */
  exit(ret);
}

/* End of mqserver.c file. */
