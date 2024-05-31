/* -*- mode: c-mode; -*- */
/*
 * group program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h>

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
  struct group *grp;
  char **members;
  /*
   * Open the group database file.
   */
  setgrent();
  do {
    grp = getgrent();
    if(grp) {
      printf("group name: %s, ", grp -> gr_name);
      printf("group password: %s, ", grp -> gr_passwd);
      printf("group id: %d\n", grp -> gr_gid);
      printf("group members: ");
      members = grp -> gr_mem;
      while(*members) {
	printf("%s", *members++);
	if(*members)
	  printf(", ");
      }
      printf("\n");
    }
  } while(grp);
  endgrent();
  ret = EXIT_SUCCESS;
  exit(ret);
}
