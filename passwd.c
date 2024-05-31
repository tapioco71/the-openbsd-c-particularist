/* -*- mode: c-mode; -*- */
/*
 * passwd program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

/*
 * Functions prototypes.
 */
int main(int, char *[]);

/*
 * The main function.
 */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  struct passwd *pw;
  /*
   * Open the password database file.
   */
  setpwent();
  do {
    pw = getpwent();
    if(pw) {
      printf("user name: %s, ", pw -> pw_name);
      printf("user id: %d, ", pw -> pw_uid);
      printf("group id: %d\n", pw -> pw_gid);
    }
  } while(pw);
  ret = EXIT_SUCCESS;

  /*
   * Close the password database.
   */
  endpwent();
  exit(ret);
}
