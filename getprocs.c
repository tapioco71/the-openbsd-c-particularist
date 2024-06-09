/* -*- mode: c-mode; -*- */

/* getprocs.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <kvm.h>
#include <sys/sysctl.h>

/* getprocs program. */
#define TRUE  1
#define FALSE 0

/* Functions prototypes. */
struct kinfo_proc *getprocs(int *, int);
long int showinfo(int);
int main(int, char *[]);

/* Main function. */
int main(int argc, char * argv[])
{
  long int ret = EXIT_FAILURE;

  /* Check arguments. */
  if(argc == 1) {
    exit(showinfo(FALSE));
  } else if((argc == 2) && \
	    (!strncmp(argv[1], "-t", 3) || \
	     !strncmp(argv[1], "--threads", 10))) {
    exit(showinfo(TRUE));
  } else {
    printf( "Usage:\n" ) ;
    printf( "      list [-h] [-t]\n\n" ) ;
    printf( "Options:\n" ) ;
    printf( "      -h, --help            Print this information\n" ) ;
    printf( "      -t, --threads         Show threads\n\n" ) ;
    ret = EXIT_SUCCESS;
  }
  exit(ret);
}

/*
 * getprocs -- retrieve the list of processes.
 */
struct kinfo_proc *getprocs(int *count, int threads)
{
  struct kinfo_proc *procbase = NULL ;
  unsigned int maxslp ;
  size_t size = sizeof(maxslp) ;
  int maxslp_mib[] = { CTL_VM, VM_MAXSLP } ;
  int mib[6] = {
    CTL_KERN,
    KERN_PROC,
    threads ? KERN_PROC_KTHREAD | KERN_PROC_SHOW_THREADS : KERN_PROC_KTHREAD,
    0,
    sizeof(struct kinfo_proc),
    0
  };

  /* */
  if(sysctl(maxslp_mib, 2, &maxslp, &size, NULL, 0) == -1) {
    perror("list");
    return NULL;
  }

 retry:
  if(sysctl(mib, 6, NULL, &size, NULL, 0 ) == -1) {
    perror("list") ;
    return NULL;
  }
  size = 5 * size / 4;           /* extra slop */
  procbase = (struct kinfo_proc *) malloc(size);
  if(procbase == NULL) {
      perror("list") ;
      return NULL;
  }
  mib[5] = (int) (size / sizeof(struct kinfo_proc));
  if(sysctl(mib, 6, procbase, &size, NULL, 0)) {
    if(errno == ENOMEM) {
      free(procbase);
      goto retry;
    }
    perror("list") ;
    return NULL;
  }
  *count = (int) (size / sizeof(struct kinfo_proc));
  return procbase;
}

/*
 * showinfo -- show informations about threads.
 */
int showinfo(int threads)
{
  struct kinfo_proc * list, * proc ;
  int count, i ;
  /* */
  if((list = getprocs(&count, threads)) == NULL) {
    return EXIT_FAILURE;
  }
  proc = list ;
  if(threads) {
    for(i = 0; i < count; ++i, ++proc) {
      if(proc -> p_tid != -1) {
	printf("%s: pid: %d (tid: %d)\n",	\
	       proc -> p_comm,			\
	       proc -> p_pid,			\
	       proc -> p_tid);
      }
    }
  } else {
    for(i = 0; i < count; ++i, ++proc) {
      printf("%s: pid: %d\n",			\
	     proc -> p_comm,			\
	     proc->p_pid ) ;
    }
  }
  return EXIT_SUCCESS;
}
