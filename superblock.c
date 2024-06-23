/* -*- mode: c-mode; -*- */

/* File superblock.c. */
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
#include <ufs/ffs/fs.h>
#include <ufs/ufs/inode.h>

/* program superblock. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i, diskfd;
  long int ret;
  struct disklabel label;
  struct fs *superblock;

  /* Check arguments. */
  if(argc == 2) {
    if(pledge("stdio disklabel unveil rpath wpath", NULL) >= 0) {
      if(unveil(argv[ 1 ], "rw") >= 0) {
	if((diskfd = open(argv[ 1 ], O_RDWR)) >= 0) {
	  if(ioctl(diskfd, DIOCGDINFO, &label) >= 0) {
	    if(lseek(diskfd, SBLOCK, SEEK_SET) >= 0) {
	      if((superblock = (uint8_t *) malloc(sizeof(uint8_t) * SBSIZE)) != NULL) {
		if(read(diskfd, superblock, sizeof(uint8_t) * SBSIZE) >= 0) {
		  printf("magic number: %d\n", superblock -> fs_magic);
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

/* End of superblock.c file. */
