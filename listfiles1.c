/* -*- mode: c-mode; -*- */
/*
 * Reading directory entries.
 */
#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function prototypes.
 */
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  FILE *fp;
  struct dirent dir;
  long int ret = EXIT_FAILURE;
  /*
   * Open the current directory.
   */
  if((fp = fopen(".", "r")) != NULL) {
    /*
     * Read directory entries.  Since we're reading
     * entries one at a time, we use the fread routine,
     * which buffers them internally.  Don't use the
     * low-level read to do things this way, since
     * at a time is very inefficient.
     */
    while(fread((char *) &dir, sizeof(dir), 1, fp) != EOF) {
      /*
       * mark deleted file.
       */
      if(dir.d_fileno == 0)
	printf(" DELETED ");
      /*
       * Make sure we print no more that DIRSIZ
       * characters.
       */
      printf("%.*s\n", DIRSIZ(dir), dir.d_name);
    }
    fclose(fp);
    ret = EXIT_SUCCESS;
  } else {
    perror("current directory");
  }
  exit(ret);
}

/* End of file listfiles1.c */
