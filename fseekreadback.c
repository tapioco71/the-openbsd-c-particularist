/* -*- mode: c-mode; -*- */

/* fseekreadback.c file. */
#include <stdio.h>
#include <stdlib.h>

/* fseekreadback program. */
/* structure and type definitions. */
struct tagRecord {
  int uid;
  char login[ 9 ];
};

typedef struct tagRecord record_t;

/* Global variables. */
int positions[ 5 ] = { 3, 0, 2, 1, 4 };
record_t records[ 5 ];

/* Function prototypes. */
int getRecord(FILE *, int, record_t *);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int i;
  long int ret = EXIT_FAILURE;
  FILE *fp;
  record_t rec;

  /* Open the data file for reading. */
  if((fp = fopen("datafile.dat", "r")) != NULL) {
    /* For each position read back the corresponding user. */

    for(i = 0; i < 5; i++) {

      /*
       * Output the record.  Notice we pass the address
       * of the structure.
       */
      if(getRecord(fp, positions[ i ], &rec) != EXIT_FAILURE)
	printf("position: %d, uid: %d, login: %s\n", positions[ i ], rec.uid, rec.login);
      else {
	perror("Could not read record.\n");
	break;
      }
      if(i == 5)
	ret = EXIT_SUCCESS;
    }

    /* Now close the output file. */
    fclose(fp);
  } else
    perror("Could not open datafile.dat for reading.\n");
  exit(ret);
}

int getRecord(FILE *fp, int i, record_t *r)
{
  int ret = EXIT_FAILURE;

  /*
   * Seek to the i-th position from the beginning
   * of the file.
   */
  if(fp) {
    if(r) {
      if(fseek(fp, (long) (i * sizeof(record_t)), SEEK_SET) == 0) {

	/*
	 * Write the record.  We want to write  one
	 * object the size of a record structure.
	 */
	if(fread((void *) r, sizeof(record_t), 1, fp) == 1) {
	  ret = EXIT_SUCCESS;
	}
      }
    }
  }
  return ret;
}

/* End of fseekreadback.c file. */
