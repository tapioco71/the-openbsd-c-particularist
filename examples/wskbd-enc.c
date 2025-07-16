/* -*- mode: c; -*- */

/* wskbd-enc.c file. */
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
#include <dev/wscons/wsksymdef.h>
#include <dev/wscons/wsksymvar.h>

#define FOREVER for(;;)

/* program wskbd-enc.c */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;
  kbd_t o_genc;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDWR | O_EXCL);
    if(fd >= 0) {
      printf("opened %s.\n", argv[ 1 ]);
      if(ioctl(fd, WSKBDIO_GETENCODING, &o_genc) >= 0) {
	printf("GETENCODING: 0x%0.8x\n", KB_ENCODING(o_genc));
      } else
	perror("error getting encoding");
      close(fd);
    } else
      perror("open");
  } else
    fprintf(stderr, "usage: wskbd-enc <device>\n");
  exit(ret);
}

/* End of wskbd-enc.c file. */
