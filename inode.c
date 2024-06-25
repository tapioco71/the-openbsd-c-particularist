/* -*- mode: c-mode; -*- */

/* File inode.c. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <util.h>
#include <fstab.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/dkio.h>
#include <sys/buf.h>
#include <sys/disklabel.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>

/* program inode. */
#define FOREVER for(;;)

/* Types. */
union tagFS {
  struct fs u_fs;
  char u_pad[ SBSIZE ];
};

typedef union tagFS fsu_t;

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char *name, *realdev;
  int i, diskfd;
  long int ret;
  fsu_t fsun1;
  off_t sbtry[] = SBLOCKSEARCH;
  ssize_t n;
  struct fstab *fs;

  /* Check arguments. */
  if(argc == 2) {
    if(pledge("stdio rpath disklabel", NULL) >= 0) {
      if((fs = getfsfile(argv[ 1 ])) != NULL)
	name = fs -> fs_spec;
      else
	name = argv[ 1 ];
      printf("Opening: %s\n", name);
      if((diskfd = opendev(name, O_RDONLY, 0, NULL)) >= 0) {
	for(i = 0; sbtry[ i ] != 1; i++) {
	  n = pread(diskfd, &fsun1.u_fs, SBLOCKSIZE, (off_t) sbtry[ i ]);
	  if(n == SBLOCKSIZE &&						\
	     (fsun1.u_fs.fs_magic == FS_UFS1_MAGIC ||			\
	      (fsun1.u_fs.fs_magic == FS_UFS2_MAGIC &&			\
	       fsun1.u_fs.fs_sblockloc == sbtry[ i ])) &&		\
	     !(fsun1.u_fs.fs_magic == FS_UFS1_MAGIC &&			\
	       sbtry[ i ] == SBLOCK_UFS2) &&				\
	     fsun1.u_fs.fs_bsize <= MAXBSIZE &&				\
	     fsun1.u_fs.fs_bsize >= sizeof(struct fs)) {
	    printf("super-block shift constant: %d\n",	\
		   fsun1.u_fs.fs_fsbtodb);
	    printf("super-block magic number: 0x%0.8x\n",	\
		   fsun1.u_fs.fs_magic);
	    printf("super-block offset: %d\n",	\
		   fsun1.u_fs.fs_sblkno);
	    printf("offset of inode-blocks: %ld\n",	\
		   fsun1.u_fs.fs_iblkno);
	    ret = EXIT_SUCCESS;
	    break;
	  }
	  if(sbtry[ i ] == -1)
	    printf("Could not find superblock for %s\n", argv[ 1 ]);
	}
	close(diskfd);
      } else
	perror("open");
    } else
      perror("pledge");
  } else
    fprintf(stderr, "usage: superblock <fs>\n");
  exit(ret);
}

/* End of inode.c file. */
