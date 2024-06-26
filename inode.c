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
#include <ufs/ufs/dinode.h>

/* program inode. */
#define FOREVER for(;;)

/* Types. */
union tagFS {
  struct fs u_fs;
  char u_pad[ SBSIZE ];
};

typedef union tagFS fsu_t;

union tagINode {
  struct ufs1_dinode u_dinode1;
  struct ufs2_dinode u_dinode2;
  char u_pad[ DEV_BSIZE ];
};

typedef union tagINode inodeu_t;

/* Functions prototypes. */
long int print(void *, size_t, size_t);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char *name, *realdev;
  int i, diskfd;
  long int ret;
  fsu_t fsun1;
  inodeu_t inun1;
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
	  n = pread(diskfd,						\
		    fsun1.u_pad,					\
		    SBLOCKSIZE,						\
		    (off_t) sbtry[ i ]);
	  if(n == SBLOCKSIZE &&					\
	     (fsun1.u_fs.fs_magic == FS_UFS1_MAGIC ||			\
	      (fsun1.u_fs.fs_magic == FS_UFS2_MAGIC &&		\
	       fsun1.u_fs.fs_sblockloc == sbtry[ i ])) &&		\
	     !(fsun1.u_fs.fs_magic == FS_UFS1_MAGIC &&		\
	       sbtry[ i ] == SBLOCK_UFS2) &&				\
	     fsun1.u_fs.fs_bsize <= MAXBSIZE &&			\
	     fsun1.u_fs.fs_bsize >= sizeof(struct fs)) {
	    printf("super-block shift constant: %d\n",	\
		   fsun1.u_fs.fs_fsbtodb);
	    printf("super-block magic number: 0x%0.8x\n",	\
		   fsun1.u_fs.fs_magic);
	    printf("super-block offset: %d\n",	\
		   fsun1.u_fs.fs_sblkno);
	    printf("offset of inode-blocks: %ld\n",	\
		   fsun1.u_fs.fs_iblkno);
	    printf("size of basic blocks: %d B\n",	\
		   fsun1.u_fs.fs_bsize);
	    break;
	  }
	}
	if(sbtry[ i ] == -1)
	  printf("Could not find superblock for %s\n", argv[ 1 ]);
	else {
	  n = pread(diskfd,						\
		    inun1.u_pad,					\
		    DEV_BSIZE,						\
		    (off_t) (fsun1.u_fs.fs_iblkno * DEV_BSIZE));
	  if(n == DEV_BSIZE) {
	    if(print(&inun1.u_pad[ 0 ],			\
		     DEV_BSIZE,				\
		     32) == EXIT_SUCCESS) {
	      ret = EXIT_SUCCESS;
	    }
	  } else
	    perror("pread");
	  switch(fsun1.u_fs.fs_magic) {
	  case FS_UFS1_MAGIC:
	    ;
	    break;

	  case FS_UFS2_MAGIC:
	    ;
	    break;
	  }
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

long int print(void *data, size_t size, size_t linelength)
{
  long int ret = EXIT_FAILURE;
  size_t i, j;

  /* */
  if(data) {
    if(size > 0) {
      if(linelength > 0) {
	if(linelength < size) {
	  for(i = 0; i < size; i += linelength) {
	    printf("%0.16x: ", i);
	    for(j = 0; j < linelength; j++) {
	      printf("%0.2x ", ((char *) data)[ i + j ]);
	    }
	    printf("\n");
	  }
	  ret = EXIT_SUCCESS;
	}
      }
    }
  }
  return ret;
}

/* End of inode.c file. */
