/* -*- mode: c-mode; -*- */

/* File blocks.c. */
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

/* program blocks. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i, diskfd;
  long int ret;
  struct disklabel label;
  uint8_t *sector;

  /* Check arguments. */
  if(argc == 2) {
    if(pledge("stdio disklabel unveil rpath wpath", NULL) >= 0) {
      if(unveil(argv[ 1 ], "rw") >= 0) {
	if((diskfd = open(argv[ 1 ], O_RDWR)) >= 0) {
	  if(ioctl(diskfd, DIOCGDINFO, &label) >= 0) {
	    if(lseek(diskfd, 0, SEEK_SET) >= 0) {
	      if((sector = (uint8_t *) malloc(sizeof(uint8_t) * label.d_secsize)) != NULL) {
		if(read(diskfd, sector, label.d_secsize) >= 0) {
		  for(i = 0; i < label.d_secsize; i++) {
		    if((i % 16) == 0) {
		      printf("\n0x%0.4x: ", i);
		    } else {
		      printf("%0.2x ", sector[ i ]);
		    }
		  }
		  printf("\n\n");
		  ret = EXIT_SUCCESS;
		} else
		  perror("read");
		free(sector);
	      } else
		perror("malloc");
	    } else
	      perror("lseek");
	  } else
	    perror("ioctl");
	  close(diskfd);
	} else
	  perror("open");
      } else
	perror("unveil");
    } else
      perror("pledge");
  } else
    fprintf(stderr, "usage: disklabel <device>\n");
  exit(ret);
}

/* End of disklabel2.c file. */
