#include <stdio.h>
#include <stdlib.h>

struct tagRecord {
  int uid;
  char login[ 9 ];
};

typedef struct tagRecord tRecord;

tRecord records[ 5 ] = {
  { 1, "user1" },
  { 2, "user2" },
  { 3, "user3" },
  { 4, "user4" },
  { 5, "user5" }
};

/*
 * Function prototypes.
 */

int putRecord(FILE *, int, tRecord *);
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
   * Open the data file for writing.
   */
  if((fp = fopen("datafile.dat", "w")) == NULL) {
    perror("Could not open datafile.dat for writing.\n");
    exit(EXIT_FAILURE);
  }

  /*
   * For each user, going backwards...
   */
  for(i = 4; i >= 0; i--) {
    /*
     * Output the record.  Notice we pass the address
     * of the structure.
     */
    if(putRecord(fp, i, &records[ i ]) == EXIT_FAILURE) {
      perror("Could not write record.\n");
      fclose(fp);
      exit(EXIT_FAILURE);
    }
  }
  fclose(fp);
  exit(EXIT_SUCCESS);
}

int putRecord(FILE *fp, int i, tRecord *r)
{
  int ret = EXIT_FAILURE;
  /*
   * Seek to the i-th position from the beginning
   * of the file.
   */
  if(fp) {
    if(fseek(fp, (long) (i * sizeof(tRecord)), SEEK_SET) == 0)
      /*
       * Write the record.  We want to write  one
       * object the size of a record structure.
       */
      if(fwrite((char *) r, sizeof(tRecord), 1, fp) == 1)
	ret = EXIT_SUCCESS;
  }
  return ret;
}
