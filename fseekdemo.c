/* -*- mode: c; -*- */

/* fseekdemo.c file. */
#include <stdio.h>
#include <stdlib.h>

/* fseekdemo program. */
/* structure and type definition. */
struct tagRecord {
  int uid;
  char login[ 9 ];
};

typedef struct tagRecord record_t;

/* Global variables. */
record_t records[ 5 ] = {
  { 1, "user1" },
  { 2, "user2" },
  { 3, "user3" },
  { 4, "user4" },
  { 5, "user5" }
};

/* Function prototypes. */
int putRecord(FILE *, int, record_t *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i;
  long int ret = EXIT_FAILURE;
  FILE *fp;

  /* Open the data file for writing. */
  if((fp = fopen("datafile.dat", "w")) != NULL) {

    /* For each user, going backwards... */
    for(i = 4; i >= 0; i--) {
      printf("writing record #%d\n", i);

      /*
       * Output the record.  Notice we pass the address
       * of the structure.
       */
      if(putRecord(fp, i, &records[ i ]) == EXIT_FAILURE) {
	perror("Could not write record.\n");
	break;
      }
    }
    if(i == 0)
      ret = EXIT_SUCCESS;
    fclose(fp);
  } else
    perror("Could not open datafile.dat for writing.\n");
  exit(ret);
}

int putRecord(FILE *fp, int i, record_t *r)
{
  int ret = EXIT_FAILURE;
  /*
   * Seek to the i-th position from the beginning
   * of the file.
   */
  if(fp) {
    if(r) {
      if(fseek(fp, (long) (i * sizeof(record_t)), SEEK_SET) == 0)
	/*
	 * Write the record.  We want to write  one
	 * object the size of a record structure.
	 */
	if(fwrite((char *) r, sizeof(record_t), 1, fp) == 1)
	  ret = EXIT_SUCCESS;
    }
  }
  return ret;
}

/* End of fseekdemo.c file. */
