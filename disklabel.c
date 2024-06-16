/* -*- mode: c-mode; -*- */

/* File disklabel.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/dkio.h>
#include <sys/disklabel.h>

/* program disklabel. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int diskfd;
  long int ret;
  struct disklabel label;

  /* Check arguments. */
  if(argc == 2) {
    if(pledge("stdio disklabel unveil rpath wpath", NULL) >= 0) {
      if(unveil(argv[ 1 ], "rw") >= 0) {
	if((diskfd = open(argv[ 1 ], O_RDWR)) >= 0) {
	  if(ioctl(diskfd, DIOCGPDINFO, &label) >= 0) {
	    printf("magic number: 0x%0.8x\n", label.d_magic);
	    printf("drive type: 0x%0.4x\n", label.d_type);
	    printf("drive subtype: 0x%0.4x\n", label.d_subtype);
	    printf("type name: %s\n", label.d_typename);
	    printf("pack name: %s\n", label.d_packname);
	    printf("bytes per sector: 0x%0.8x\n", label.d_secsize);
	    printf("sectors per track: 0x%0.8x\n", label.d_nsectors);
	    printf("tracks per cylinder: 0x%0.8x\n", label.d_ntracks);
	    printf("data cylinders per unit: 0x%0.8x\n", label.d_ncylinders);
	    printf("data sectors per cylinder: 0x%0.8x\n", label.d_secpercyl);
	    printf("data sectors per unit: 0x%0.8x\n", label.d_secperunit);
	    ret = EXIT_SUCCESS;
	  } else
	    perror("ioctl");
	  close(diskfd);
	} else
	  perror("open");
      } else
	perror("nveil");
    } else
      perror("pledge");
  } else
    fprintf(stderr, "usage: disklabel <device>\n");
  exit(ret);
}

/* End of disklabel.c file. */
