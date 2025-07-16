/* -*- mode: c; -*- */

/* File ondisk-inode.c. */
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
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/dkio.h>
#include <sys/buf.h>
#include <sys/stat.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/dinode.h>

/* program ondisk-inode. */
#define	INOBUFSIZE (128 * 1024)
#define FOREVER for(;;)

/* Types. */
union tagFSU {
  struct fs u_fs;
  char u_pad[ SBSIZE ];
};

typedef union tagFSU fsu_t;

union tagDINODE {
  struct ufs1_dinode u_dinode1;
  struct ufs2_dinode u_dinode2;
  char u_pad[ DEV_BSIZE ];
};

typedef union tagDINODE dinodeu_t;

/* Functions prototypes. */
long int getsuperblock(int, fsu_t *);
long int print(char *, size_t, size_t);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  char *name, *realpath;
  int i, fd;
  long int ret, size;
  dinodeu_t dinode;
  fsu_t sb;
  ssize_t n;
  off_t dblk;
  struct fstab *tab;
  struct stat st;

  /* Check arguments. */
  if(argc == 2) {
    if(pledge("stdio rpath unveil disklabel", NULL) >= 0) {
      if(unveil(argv[ 1 ], "rw") >= 0) {
	tab = getfsfile(argv[ 1 ]);
	if(tab)
	  name = tab -> fs_spec;
	else
	  name = argv[ 1 ];
	fd = opendev(name, O_RDONLY, 0, &realpath);
	if(fd >= 0) {
	  printf("opened %s, real path %s\n", name, realpath);
	  if(getsuperblock(fd, &sb) == EXIT_SUCCESS) {
	    printf("got a superblock!\n");
	    switch(sb.u_fs.fs_magic) {
	    case FS_UFS1_MAGIC:
	      ;
	      ret = EXIT_SUCCESS;
	      break;

	    case FS_UFS2_MAGIC:
	      size = blkroundup(&sb.u_fs, INOBUFSIZE);
	      printf("inode block size: %lld\n", size);
	      dblk = fsbtodb(&sb.u_fs, ino_to_fsba(&sb.u_fs, 0));
	      printf("dinode block number: %lld\n", dblk);
	      n = pread(fd,						\
			dinode.u_pad,					\
			size,						\
			dblk);
	      if(n == DEV_BSIZE) {
		printf("read %lld byte block.\n", n);
		print(dinode.u_pad, DEV_BSIZE, 32);
		ret = EXIT_SUCCESS;
	      } else
		perror("pread");
	      break;
	    }
	  } else
	    fprintf(stderr, "could not get super-block on %s.\n", name);
	  close(fd);
	} else
	  perror("opendev");
      } else
	perror("unveil");
    } else
      perror("pledge");
  } else
    fprintf(stderr, "usage: ondisk-inode <fs>\n");
  exit(ret);
}

long int getsuperblock(int fd, fsu_t *sb)
{
  long int ret = EXIT_FAILURE;
  size_t i;
  ssize_t n;
  off_t sbtry[] = SBLOCKSEARCH;

  /* Check arguments */
  if(fd >= 0) {
    if(sb) {
      for(i = 0; sbtry[ i ] != -1; i++) {
	n = pread(fd, sb ->  u_pad, SBLOCKSIZE, (off_t) sbtry[ i ]);
	if((n == SBLOCKSIZE) &&						\
	   (sb -> u_fs.fs_magic == FS_UFS1_MAGIC ||			\
	    (sb -> u_fs.fs_magic == FS_UFS2_MAGIC &&			\
	     sb -> u_fs.fs_sblockloc == sbtry[ i ])) &&			\
	   !(sb -> u_fs.fs_magic == FS_UFS1_MAGIC &&			\
	     sbtry[ i ] == SBLOCK_UFS2) &&				\
	   sb -> u_fs.fs_bsize <= MAXBSIZE &&				\
	   sb -> u_fs.fs_bsize >= sizeof(struct fs)) {
	  ret = EXIT_SUCCESS;
	  break;
	}
      }
    }
  }
  return ret;
}

long int print(char *block, size_t size, size_t linelength)
{
  long int ret = EXIT_FAILURE;
  size_t i, j;

  /* */
  printf("address: 0x%0.16x\nsize: %lld\nline length: %lld\n", block, size, linelength);
  if(block) {
    if(size > 0) {
      if((linelength > 0) && (linelength < size)) {
	for(i = 0; i < size; i += linelength) {
	  printf("%0.16x: ", i);
	  for(j = 0; j < linelength; j++) {
	    printf("%0.2x ", (uint8_t) block[ i + j ]);
	  }
	  printf("\n");
	}
	ret = EXIT_SUCCESS;
      }
    }
  }
  return ret;
}

/* End of ondisk-inode.c file. */
