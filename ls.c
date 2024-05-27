/* -*- mode: c-mode; -*- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
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
    while((ch = getopt(argc, argv, "asl:")) != -1) {
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
      if(stat(*++argv, &st_buf) >= 0) {
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
	perror(*argv);
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
  /*
   * At this point we know the file exists,
   * so this won't fail.
   */
  stat(newname, &st_buf);
  if((flags & 0x04) != 0)
    /*
     * print size in kbytes.
     */
    printf("%5d ", (st_buf.st_size + S_BLKSIZE - 1) / S_BLKSIZE);


}

void usage(void)
{
  printf("Usage: ls [-asl] dir\n");
}

/* End of file listfiles1.c */
