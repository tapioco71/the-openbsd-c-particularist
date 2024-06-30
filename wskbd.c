/* -*- mode: c-mode; -*- */

/* wskbd.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <dev/wscons/wsconsio.h>

#define FOREVER for(;;)

/* program wskbd.c */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDWR | O_EXCL);
    if(fd >= 0) {
      printf("opened %s.\n", argv[ 1 ]);
      if(ioctl(fd, WSKBDIO_BELL) >= 0) {
	ret = EXIT_SUCCESS;
      } else
	perror("error playing bell");
      close(fd);
    } else
      perror("open");
  } else
    fprintf(stderr, "usage: wskbd <device>\n");
  exit(ret);
}

/* End of wskbd.c file. */
