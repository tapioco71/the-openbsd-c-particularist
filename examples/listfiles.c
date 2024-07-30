/* -*- mode: c-mode; -*- */

/* listfiles.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>

/* listfiles program. */
/* Function prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  DIR *dp;
  struct dirent *dir;
  long int ret = EXIT_FAILURE;
  /* Open the current directory. */
  if((dp = opendir(".")) != NULL) {
    /*
     * Read directory entries.  Since we're reading
     * entries one at a time, we use the readdir routine,
     * which buffers them internally.  Don't use the
     * low-level read to do things this way, since
     * at a time is very inefficient.
     */
    while((dir = readdir(dp)) != NULL) {
      /* mark deleted file. */
      if(dir -> d_fileno == 0)
	printf(" DELETED ");
      /*
       * Make sure we print no more that DIRSIZ
       * characters.
       */
      printf("%.*s\n", DIRSIZ(dir), dir -> d_name);
    }
    closedir(dp);
    ret = EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Could not read current directory\n");
  }
  exit(ret);
}

/* End of listfiles.c file. */
