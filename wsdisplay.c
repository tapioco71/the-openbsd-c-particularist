/* -*- mode: c-mode; -*- */

/* wsdisplay.c file. */
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

/* program wsdisplay.c */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;
  u_int gtype;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDONLY | O_EXCL, 0666);
    if(fd >= 0) {
      if(ioctl(fd, WSDISPLAYIO_GTYPE, &gtype) >= 0) {
	printf("type of display for %s: %d\n", argv[ 1 ], gtype);
	ret = EXIT_SUCCESS;
      } else
	perror("ioctl");
      close(fd);
    } else
      perror("open");
  } else
    fprintf(stderr, "usage: wsdisplay <device>\n");
  exit(ret);
}

/* End of wsdisplay.c file. */
