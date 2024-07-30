/* -*- mode: c-mode; -*- */

/* wsmux.c file. */
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

/* program wsmux.c */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  int i;
  long int ret = EXIT_FAILURE;
  struct wsmux_device_list mdevices;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDWR | O_EXCL);
    if(fd >= 0) {
      if(ioctl(fd, WSMUXIO_LIST_DEVICES, &mdevices) >= 0) {
	printf("opened %s.\n", argv[ 1 ]);
	for(i = 0; i < mdevices.ndevices; i++) {
	  printf("LIST_DEVICES: %d %d\n",		\
		 mdevices.devices[ i ].type,		\
		 mdevices.devices[ i ].idx);
	}
      } else
	perror("error retrieving devices list");
      close(fd);
    } else
      fprintf(stderr, "error open device %s.\n", argv[ 1 ]);
  } else
    fprintf(stderr, "usage: wsmux <device>\n");
  exit(ret);
}

/* End of wsmux.c file. */
