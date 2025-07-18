/* -*- mode: c; -*- */

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
  int c, i, oflag, semid, nsems;
  long int ret = EXIT_FAILURE;
  key_t key;

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
    nsems = atoi(argv[ optind + 1 ]);
    printf("Creating %d semaphore%s", nsems, nsems > 1 ? "s.\n" : ".\n");
    if((key = ftok(argv[ optind ], 0)) >= 0) {
      printf("creating key from path %s: %d\n", argv[ optind ], key);
      if((semid = semget(key, nsems, oflag)) >= 0)
	ret = EXIT_SUCCESS;
      else
	perror("semget");
    } else
      perror("ftok");
  } else
    fprintf(stderr, "usage: semcreate [ -e ] <pathname> <nsems>\n");
  exit(ret);
}

/* End of semcreate.c file. */
