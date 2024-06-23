/* -*- mode: c-mode; -*- */

/* File superblock.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <util.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/dkio.h>
#include <sys/disklabel.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>

/* program superblock. */
#define FOREVER for(;;)

/* Types. */
union tagFS {
  struct fs u_fs;
  char u_pad[ SBSIZE ];
};

typedef union tagFS fsu_t;

/* Functions prototypes. */
long int rdfs(daddr_t, int, void *, int);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i, diskfd;
  long int ret;
  struct disklabel label;
  fsu_t *fsun1;
  struct fs *fs1;

  /* Check arguments. */
  if(argc == 2) {
    if(pledge("stdio disklabel unveil rpath wpath", NULL) >= 0) {
      if(unveil(argv[ 1 ], "rw") >= 0) {
	if((diskfd = opendev(argv[ 1 ], O_RDONLY, 0, NULL)) >= 0) {
	  printf("superblock start sector: %d\n", SBLOCK);
	  printf("superblock size in bytes: %d\n", SBSIZE);
	  printf("superblock struct size: %d\n", sizeof(struct fs));
	  if((fsun1 = calloc(1, sizeof(fsu_t))) != NULL) {
	    if(rdfs(SBLOCK_UFS1 / DEV_BSIZE,				\
		    SBSIZE,						\
		    (char *) fs1,					\
		    diskfd) == EXIT_SUCCESS) {
	      fs1 = &fsun1 -> u_fs;
	      printf("minimum percentage of free blocks: %d%%\n", fs1 -> fs_minfree);
	      printf("magic number: %d\n", fs1 -> fs_magic);
	      ret = EXIT_SUCCESS;
	    } else
	      perror("rdfs");
	    free(fsun1);
	  } else
	    perror("calloc");
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

/*
 * read -- read a block from the file system
 */
long int rdfs(daddr_t bno, int size, void *bf, int fsi)
{
  int n;
  long int ret = EXIT_FAILURE;

  if((n = pread(fsi, bf, size, (off_t) bno * DEV_BSIZE)) == size)
    ret = EXIT_SUCCESS;
  return ret;
}

/* End of superblock.c file. */
