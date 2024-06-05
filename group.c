/* -*- mode: c-mode; -*- */

/* group.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h>

/* group program. */

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  struct group *grp;
  char **members;
  /* Open the group database file. */
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

/* End of group.c file. */
