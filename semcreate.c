/* -*- mode: c-mode; -*- */

/* File semcreate.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>

/* semcreate program. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int c, oflag, semid, nsems;
  long int ret = EXIT_FAILURE;

  /* */
  oflag = IPC_CREAT | 0666;
  while((c = getopt(argc, argv, "e")) != -1) {
    switch(c) {
    case 'e':
      oflag |= IPC_EXCL;
      break;
    }
  }
  if(optind == (argc - 2)) {
    nsems = atoi(argv[ optind + 11 ]);
    semid = semget(ftok(argv[ optind ], 0), nsems, oflag);
  } else
    fprintf(stderr, "usage: semcreate [ -e ] <pathname> <nsems>\n");
  exit(ret);
}

/* End of semcreate.c file. */
