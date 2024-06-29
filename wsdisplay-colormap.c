/* -*- mode: c-mode; -*- */

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
  u_char *nred, *ngreen, *nblue;
  u_char *ored, *ogreen, *oblue;
  u_char *ocmap, ncmap;
  u_int ogmode, ngmode;
  u_int gstate, gtype;
  struct wsdisplay_fbinfo gfbinfo;
  struct wsdisplay_cmap old_gcmap, new_gcmap;

  /* Check arguments count. */
  if(argc == 2) {
    fd = open(argv[ 1 ], O_RDWR | O_EXCL);
    if(fd >= 0) {
      printf("opened %s.\n", argv[ 1 ]);
      if(ioctl(fd, WSDISPLAYIO_GTYPE, &gtype) >= 0) {
	printf("GTYPE: %d\t", gtype);
	if(ioctl(fd, WSDISPLAYIO_GMODE, &ogmode) >= 0) {
	  printf("old GMODE: %d\t", ogmode);
	  ngmode = WSDISPLAYIO_MODE_DUMBFB;
	  if(ioctl(fd, WSDISPLAYIO_SMODE, &ngmode) >= 0) {
	    printf("new GMODE: %d\t", ngmode);
	    if(ioctl(fd, WSDISPLAYIO_GINFO, &gfbinfo) >= 0) {
	      printf("GINFO: %d %d %d %d\n", \
		     gfbinfo.height,	     \
		     gfbinfo.width,	     \
		     gfbinfo.depth,	     \
		     gfbinfo.cmsize);
	      ocmap = calloc(gfbinfo.cmsize * 3, sizeof(u_char));
	      if(ocmap) {
		old_gcmap.red = &ocmap[ gfbinfo.cmsize * 0 ];
		old_gcmap.green = &ocmap[ gfbinfo.cmsize * 1 ];
		old_gcmap.blue = &ocmap[ gfbinfo.cmsize * 2 ];
		old_gcmap.count = gfbinfo.cmsize;
		old_gcmap.index = 0;
		if(ioctl(fd, WSDISPLAYIO_GETCMAP, &old_gcmap) >= 0) {
		  printf("CMAP: %d %d\n", old_gcmap.index, old_gcmap.count);
		}
		if(ioctl(fd, WSDISPLAYIO_SMODE, &ogmode) >= 0) {
		  printf("old mode restored: %d\n", ogmode);
		  ret = EXIT_SUCCESS;
		}
		free(ocmap);
	      } else
		fprintf(stderr, "could not allocate space for old color map.\n");
	    }
	  }
	}
      }
      close(fd);
    } else
      perror("open");
  } else
    fprintf(stderr, "usage: wsdisplay <device>\n");
  exit(ret);
}

/* End of wsdisplay-colormap.c file. */
