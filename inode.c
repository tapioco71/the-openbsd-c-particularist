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
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/dkio.h>
#include <sys/buf.h>
#include <sys/disklabel.h>
#include <sys/stat.h>

/* program inode. */
#define FOREVER for(;;)

/* Types. */

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i, fd;
  long int ret;
  off_t offset;
  ssize_t n;
  struct stat sb;

  /* Check arguments. */
  if(argc == 2) {
    printf("Opening file: %s\n", argv[ 1 ]);
    if((fd = open(argv[ 1 ], O_RDONLY, 0, NULL)) >= 0) {
      if(fstat(fd, &sb) >= 0) {
	printf("inode's device: %lld\n", sb.st_dev);
	printf("inode's number: %lld\n", sb.st_ino);
	printf("inode protection mode: 0x%0.6x\n", sb.st_mode);
	printf("number of hard links: %lld\n", sb.st_nlink);
	printf("user ID of the file's owner: %lld\n", sb.st_uid);
	printf("group ID of the file's group: %lld\n", sb.st_gid);
	printf("device type: %d\n", sb.st_rdev);
	printf("time of last access: %s", ctime(&sb.st_atim.tv_sec));
	printf("time of last data modification: %s", ctime(&sb.st_mtim.tv_sec));
	printf("time of last file status change: %s", ctime(&sb.st_ctim.tv_sec));
	printf("file size in bytes: %lld\n", sb.st_size);
      } else
	perror("stat");
      close(fd);
    } else
      perror("open");
  } else
    fprintf(stderr, "usage: inode <filename>\n");
  exit(ret);
}

/* End of inode.c file. */
