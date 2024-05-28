/* -*- mode: c-mode; -*- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

/*
 * Global variables definitions.
 */
char *modes[] = {
  "---",
  "--x",
  "-w-",
  "-wx",
  "r--",
  "r-x",
  "rw-",
  "rwx"
};
/*
 * Function prototypes.
 */
void usage(void);
long int list(char *, uint8_t);
void printout(char *, char *, uint8_t);
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  int ch;
  long int ret = EXIT_FAILURE;
  struct stat st_buf;
  struct dirent *dir;
  DIR *dp;
  uint8_t flags;
  /*
   * Check arguments count.
   */
  flags = 0;
  if(argc < 2) {
    ret = list(".", flags);
  } else {
    /*
     * Process arguments.
     */
    while((ch = getopt(argc, argv, "als")) != -1) {
      switch(ch) {
      case 'a':
	flags |= 0x01;
	break;

      case 's':
	flags |= 0x02;
	break;

      case 'l':
	flags |= 0x04;
	break;

      default:
	usage();
	flags |= 0x08;
	break;
      }
    }
    if((flags & 0x08) == 0) {
      argc -= optind;
      argv += optind;
      if(stat(*argv, &st_buf) >= 0) {
	/*
	 * If it is a directory we list it,
	 * otherwise just print the info about
	 * the file.
	 */
	if((st_buf.st_mode & S_IFMT) == S_IFDIR)
	  ret = list(*argv, flags);
	else {
	  printout(".", *argv, flags);
	  ret = EXIT_SUCCESS;
	}
      } else {
	fprintf(stderr, "ls error.\n");
      }
    }
  }
  exit(ret);
}

/*
 * list -- read a directory  and list the files it
 *         contains.
 */
long int list(char *name, uint8_t flags)
{
  long int ret = EXIT_FAILURE;
  DIR *dp;
  struct dirent *dir;
  /*
   * open the directory.
   */
  if((dp = opendir(name)) != NULL) {
    /*
     * For each entry...
     */
    while((dir = readdir(dp)) != NULL) {
      /*
       * Skip removed file.
       */
      if(dir -> d_fileno == 0)
	continue;
      /*
       * Print it out.
       */
      printout(name, dir -> d_name, flags);
    }
    ret = EXIT_SUCCESS;
  } else
    fprintf(stderr, "%s: cannot open.\n", name);
  return ret;
}

/*
 * printout -- print out the information about
 *             a file.
 */
void printout(char *dir, char *name, uint8_t flags)
{
  int i, j;
  char perms[ 10 ];
  struct stat st_buf;
  char newname[ S_BLKSIZE ];
  /*
   * Make full path name, so
   * we have a legal path.
   */
  snprintf(newname, S_BLKSIZE, "%s/%s", dir, name);
  if((name[ 0 ] != '.') || ((flags & 0x01) != 0)) {
    /*
     * At this point we know the file exists,
     * so this won't fail.
     */
    stat(newname, &st_buf);
    if((flags & 0x04) != 0) {
      /*
       * print size in kbytes.
       */
      if((flags & 02) != 0)
	printf("%5d ", (st_buf.st_size + S_BLKSIZE - 1) / S_BLKSIZE);
      /*
       * Get the file type.  For convenience (and to
       * make this example universal), we ignore the
       * other types which are version-dependent.
       */
      switch(st_buf.st_mode & S_IFMT) {
      case S_IFREG:
	putchar('-');
	break;

      case S_IFDIR:
	putchar('d');
	break;

      case S_IFCHR:
	putchar('c');
	break;

      case S_IFBLK:
	putchar('b');
	break;

      default:
	putchar('?');
	break;
      }
      /*
       * Get each of the three groups of permissions
       * (owner, group, other).  Since they're just
       * bits, we can count in binary and use this
       * as subscript (see the modes array, above).
       */
      *perms = '\0';
      for(i = 2; i >= 0; i--) {
	/*
	 * Since we're subscripting, we don't
	 * read the constants.  Just get a
	 * value between 0 and 7.
	 */
	j = (st_buf.st_mode >> (i * 3)) & 0x07;
	/*
	 * Get the perm bits.
	 */
	strncat(perms, modes[ j ], 4);
      }
      /*
       * Handle special bits which replace the 'x'
       * in places.
       */
      if((st_buf.st_mode & S_ISUID) != 0)
	perms[ 2 ] = 's';
      if((st_buf.st_mode & S_ISGID) != 0)
	perms[ 5 ] = 's';
      if((st_buf.st_mode & S_ISVTX) != 0)
	perms[ 8 ] = 't';
      /*
       * Print permissions, number of links,
       * user and group ids.
       */
      printf("%s%3d %5d/%-5d ", perms, st_buf.st_nlink, st_buf.st_uid, st_buf.st_gid);
      /*
       * Print the size of the file in bytes.
       * and the last modification time.  The
       * ctime routine converts a time to ASCII;
       * it is described in Chapter 7, Telling
       * Time and Timing Things.
       */
      if((flags & 0x02) != 0)
	printf("%7d ", st_buf.st_size);
      printf("%.12s ", ctime(&st_buf.st_mtime) + 4);
      /*
       * Finally, print the file name.
       */
    }
    printf("%s", name);
    putchar('\n');
  }
}

void usage(void)
{
  printf("Usage: ls [-asl] dir\n");
}

/* End of file listfiles1.c */
