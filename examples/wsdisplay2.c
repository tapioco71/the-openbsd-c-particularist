/* -*- mode: c; -*- */

/* wsdisplay2.c file. */
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

/* program wsdisplay2.c */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;
  u_int gstate, gtype;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDONLY);
    if(fd >= 0) {
      if(ioctl(fd, WSDISPLAYIO_GVIDEO, &gstate) >= 0) {
	printf("%s display state: %s\n", argv[ 1 ], gstate == 1 ? "on" : "off");
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

/* End of wsdisplay2.c file. */
