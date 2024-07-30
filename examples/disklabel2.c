/* -*- mode: c-mode; -*- */

/* File disklabel2.c. */
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

/* program disklabel2. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i, diskfd;
  long int ret;
  struct disklabel label;

  /* Check arguments. */
  if(argc == 2) {
    if(pledge("stdio disklabel unveil rpath wpath", NULL) >= 0) {
      if(unveil(argv[ 1 ], "rw") >= 0) {
	if((diskfd = open(argv[ 1 ], O_RDWR)) >= 0) {
	  if(ioctl(diskfd, DIOCGDINFO, &label) >= 0) {
	    for(i = 0; i < label.d_npartitions; i++) {
	      printf("\npartion #%d\n", i);
	      printf("partition number of sectors: %u\n",		\
		     (off_t) label.d_partitions[ i ].p_size |		\
		     ((off_t) label.d_partitions[ i ].p_sizeh << 32));
	      printf("partition starting sector: %u\n",			\
		     (off_t) label.d_partitions[ i ].p_offset |		\
		     ((off_t) label.d_partitions[ i ].p_offseth << 32));
	      printf("partition filesystem type: %d\n", \
		     label.d_partitions[ i ].p_fstype);
	      printf("partition encoded filesystem frag/block: %d\n",	\
		     label.d_partitions[ i ].p_fragblock);
	      printf("partition cylinders per group: %d\n",	\
		     label.d_partitions[ i ].p_cpg);
	    }
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

/* End of disklabel2.c file. */
