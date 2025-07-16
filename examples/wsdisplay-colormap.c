/* -*- mode: c; -*- */

/* wsdisplay-colormap.c file. */
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

/* program wsdisplay-colormap.c */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd;
  long int ret = EXIT_FAILURE;
  u_int gmode, gstate, gtype;
  struct wsdisplay_fbinfo gfbinfo;
  struct wsdisplay_screentype gscreentype;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDWR | O_EXCL);
    if(fd >= 0) {
      printf("opened %s.\n", argv[ 1 ]);
      if(ioctl(fd, WSDISPLAYIO_GTYPE, &gtype) >= 0) {
	printf("GTYPE: %d\t", gtype);
	if(ioctl(fd, WSDISPLAYIO_GMODE, &gmode) >= 0) {
	  printf("GMODE: %d\t", gmode);
	  if(ioctl(fd, WSDISPLAYIO_GINFO, &gfbinfo) >= 0) {
	    printf("GINFO: %d %d %d %d\n",   \
		   gfbinfo.height,	     \
		   gfbinfo.width,	     \
		   gfbinfo.depth,	     \
		   gfbinfo.cmsize);
	    if(ioctl(fd, WSDISPLAYIO_GETSCREENTYPE, &gscreentype) >= 0) {
	      printf("SCREENTYPE: %d %d %s %d %d %d %d\n",     \
		     gscreentype.idx,			       \
		     gscreentype.nidx,			       \
		     gscreentype.name,			       \
		     gscreentype.ncols,			       \
		     gscreentype.nrows,			       \
		     gscreentype.fontwidth,		       \
		     gscreentype.fontheight);
	      ret = EXIT_SUCCESS;
	    } else
	      perror("error getting screen type");
	  } else
	    perror("error getting console info");
	} else
	  perror("error getting console mode");
      } else
	perror("error getting console type");
      close(fd);
    } else
      perror("open");
  } else
    fprintf(stderr, "usage: wsdisplay <device>\n");
  exit(ret);
}

/* End of wsdisplay-colormap.c file. */
