/* -*- mode: c; -*- */

/* wskbd-leds.c file. */
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

/* program wskbd-leds.c */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;
  u_int i, o_gleds;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDWR | O_EXCL);
    if(fd >= 0) {
      printf("opened %s.\n", argv[ 1 ]);
      if(ioctl(fd, WSKBDIO_GETLEDS, &o_gleds) >= 0) {
	for(i = 1; i <= WSKBD_LED_COMPOSE; i = (i << 1)) {
	  printf("led = %d\n", i);
	  ioctl(fd, WSKBDIO_SETLEDS, &i);
	  sleep(2);
	}
	ioctl(fd, WSKBDIO_SETLEDS, &o_gleds);
      } else
	perror("error getting leds");
      close(fd);
    } else
      perror("open");
  } else
    fprintf(stderr, "usage: wskbd-leds <device>\n");
  exit(ret);
}

/* End of wskbd-leds.c file. */
