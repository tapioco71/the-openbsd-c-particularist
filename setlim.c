/* -*- mode: c; -*- */

/* File setlim.c. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

/* setlim program. */

/* Functions protitypes. */
long int setlim(int, rlim_t);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  bool ok = false;
  char *bad;
  int limit;
  long int ret = EXIT_FAILURE;
  rlim_t value;

  /* Checks arguments. */
  if(argc == 3) {
    ok = true;
    if(strncmp(argv[ 1 ], "cpu", 3) == 0)
      limit = RLIMIT_CPU;
    else if(strncmp(argv[ 1 ], "filesize", 8) == 0)
      limit = RLIMIT_FSIZE;
    else if(strncmp(argv[ 1 ], "data", 4) == 0)
      limit = RLIMIT_DATA;
    else if(strncmp(argv[ 1 ], "stack", 5) == 0)
      limit = RLIMIT_STACK;
    else if(strncmp(argv[ 1 ], "core", 4) == 0)
      limit = RLIMIT_CORE;
    else if(strncmp(argv[ 1 ], "rss", 3) == 0)
      limit = RLIMIT_RSS;
    else if(strncmp(argv[ 1 ], "memorylock", 10) == 0)
      limit = RLIMIT_MEMLOCK;
    else if(strncmp(argv[ 1 ], "nproc", 5) == 0)
      limit = RLIMIT_NPROC;
    else if(strncmp(argv[ 1 ], "openfiles", 9) == 0)
      limit = RLIMIT_NOFILE;
    else {
      ok = false;
      perror("unknown limit");
    }
    if(ok == true) {
      if(strncmp(argv[ 2 ], "infinity", 8) == 0)
	value = RLIM_INFINITY;
      else {
	value = (rlim_t) strtoul(argv[ 2 ], &bad, 0);
	if(*bad != '\0') {
	  ok = false;
	}
      }
      if(ok == true) {
	printf("set limit: %s(%d)\tto value: %lld\n",	\
	       argv[ 1 ],				\
	       limit,					\
	       value);
	if(setlim(limit, value) == EXIT_SUCCESS)
	  ret = EXIT_SUCCESS;
	else
	  perror("error setting limit");
      } else
	perror("bad numerical value for limit");
    }
  } else
    fprintf(stderr, "usage: setlim <limit> <value>\n");
  exit(ret);
}

long int setlim(int lim, rlim_t val)
{
  long int ret = EXIT_FAILURE;
  struct rlimit rlim;

  /*
   * Get the current limits so  we
   * will know the maximum value.
   */
  bzero(&rlim, sizeof(struct rlimit));
  if(getrlimit(lim, &rlim) >= 0) {
    printf("current limit: %lld\tmaximum limit: %lld\n",	\
	   rlim.rlim_cur,					\
	   rlim.rlim_max);

    /* Now change the current limit. */
    rlim.rlim_cur = val;
    if(setrlimit(lim, &rlim) >= 0)
      ret = EXIT_SUCCESS;
  }
  return ret;
}

/* End of setlim.c file. */
