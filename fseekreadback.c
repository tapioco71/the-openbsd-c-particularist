#include <stdio.h>
#include <stdlib.h>

struct tagRecord {
  int uid;
  char login[ 9 ];
};

typedef struct tagRecord tRecord;

int positions[ 5 ] = { 3, 0, 2, 1, 4 };
tRecord records[ 5 ];

/*
 * Function prototypes.
 */

int getRecord(FILE *, int, tRecord *);
int main(int, char *[]);

/*
  The main function.
*/

int main(int argc, char *argv[])
{
  int i;
  FILE *fp;
  tRecord rec;

  /*
   * Open the data file for reading.
   */
  if((fp = fopen("datafile.dat", "r")) == NULL) {
    perror("Could not open datafile.dat for reading.\n");
    exit(EXIT_FAILURE);
  }

  /*
   * For each position read back the corresponding user.
   */
  for(i = 0; i < 5; i++) {
    /*
     * Output the record.  Notice we pass the address
     * of the structure.
     */
    if(getRecord(fp, positions[ i ], &rec) == EXIT_FAILURE) {
      perror("Could not read record.\n");
      fclose(fp);
      exit(EXIT_FAILURE);
    }
    printf("uid: %d, login: %s\n", rec.uid, rec.login);
  }
  fclose(fp);
  exit(EXIT_SUCCESS);
}

int getRecord(FILE *fp, int i, tRecord *r)
{
  int ret = EXIT_FAILURE;
  /*
   * Seek to the i-th position from the beginning
   * of the file.
   */
  if(fp)
    if(r) {
      if(fseek(fp, (long) (i * sizeof(tRecord)), SEEK_SET) == 0)
	/*
	 * Write the record.  We want to write  one
	 * object the size of a record structure.
	 */
	if(fread((void *) r, sizeof(tRecord), 1, fp) == 1)
	  ret = EXIT_SUCCESS;
    }
  return ret;
}
