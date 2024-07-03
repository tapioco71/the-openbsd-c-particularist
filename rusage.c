/* -*- mode: c-mode; -*- */

/* File rusage.c. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

/* rusage program. */

/* Functions protitypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  struct rusage usage;

  /* */
  if(getrusage(RUSAGE_SELF, &usage) >= 0) {
    printf("user time used: %ld s\n", (time_t) usage.ru_utime.tv_sec);
    printf("system time used: %ld s\n", (time_t) usage.ru_stime.tv_sec);
    printf("maximum resident set size: %ld kB\n", usage.ru_maxrss);
    printf("integral shared text memory size: %ld kBt\n", usage.ru_ixrss);
    printf("integral unshared data size: %ld kBt\n", usage.ru_idrss);
    printf("integral unshared stack size: %ld kBt\n", usage.ru_isrss);
    printf("page reclaims: %ld\n", usage.ru_minflt);
    printf("page faults: %ld\n", usage.ru_majflt);
    printf("swaps: %ld\n", usage.ru_nswap);
    printf("block input operations: %ld\n", usage.ru_inblock);
    printf("block output operations: %ld\n", usage.ru_oublock);
    printf("messages sent: %ld\n", usage.ru_msgsnd);
    printf("messages received: %ld\n", usage.ru_msgrcv);
    printf("signals received: %ld\n", usage.ru_nsignals);
    printf("voluntary context switches: %ld\n", usage.ru_nvcsw);
    printf("involuntary context switches: %ld\n", usage.ru_nivcsw);
    ret = EXIT_SUCCESS;
  }
  exit(ret);
}
