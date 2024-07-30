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
  struct wskbd_bell_data o_wsbelldata, n_wsbelldata;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDWR | O_EXCL);
    if(fd >= 0) {
      printf("opened %s.\n", argv[ 1 ]);
      if(ioctl(fd, WSKBDIO_BELL) >= 0) {
	if(ioctl(fd, WSKBDIO_GETBELL, &o_wsbelldata) >= 0) {
	  printf("old GETBELL: %d %d %d %d\t",	\
		 o_wsbelldata.which,		\
		 o_wsbelldata.pitch,		\
		 o_wsbelldata.period,		\
		 o_wsbelldata.volume);
	  bzero(&n_wsbelldata, sizeof(struct wskbd_bell_data));
	  n_wsbelldata.which = WSKBD_BELL_DOPITCH;
	  n_wsbelldata.pitch = o_wsbelldata.pitch * 2;
	  if(ioctl(fd, WSKBDIO_SETBELL, &n_wsbelldata) >= 0) {
	    printf("new GETBELL: %d %d %d %d\t",	\
		   n_wsbelldata.which,			\
		   n_wsbelldata.pitch,			\
		   n_wsbelldata.period,			\
		   n_wsbelldata.volume);
	    if(ioctl(fd, WSKBDIO_BELL) >= 0) {
	      sleep(5);
	      if(ioctl(fd, WSKBDIO_SETBELL, &o_wsbelldata) >= 0) {
		printf("restore old GETBELL: %d %d %d %d\n",	\
		       o_wsbelldata.which,			\
		       o_wsbelldata.pitch,			\
		       o_wsbelldata.period,			\
		       o_wsbelldata.volume);
		if(ioctl(fd, WSKBDIO_BELL) >= 0) {
		  sleep(5);
		  ret = EXIT_SUCCESS;
		} else
		  perror("error playing bell");
	      } else
		perror("error setting bell data");
	    } else
	      perror("error playing bell");
	  } else
	    perror("error setting bell data");
	} else
	  perror("error retrieving bell data");
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
