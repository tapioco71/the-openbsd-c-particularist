#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n;
  FILE *from, *to;
  char buf[ BUFSIZ ];
  /*
   * Check our arguments.
   */
  if(argc != 3) {
    fprintf(stderr, "Usage: %s from-file to-file\n", *argv);
    exit(1);
  }
  /*
   * Open the from-file for reading.
   */
  if((from = fopen(argv[ 1 ], "r")) == NULL) {
    perror(argv[ 1 ]);
    exit(1);
  }
  /*
   * Open the to-file for appending.  If to-file does
   * not exist, fopen will create it.
   */
  if((to = fopen(argv[ 2 ], "a")) == NULL) {
    perror(argv[ 2 ]);
    exit(1);
  }
  /*
   * Now read a buffer-full at a time from from-file
   * and write it to the to-file.
   */
  while((n = fread(buf, sizeof(char), BUFSIZ, from)) > 0)
    fwrite(buf, sizeof(char), n, to);
  /*
   * Now close the files.
   */
  fclose(to);
  fclose(from);
  exit(0);
}
