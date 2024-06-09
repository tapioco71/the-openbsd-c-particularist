/* -*- mode: c-mode; -*- */

/* getproc.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/proc.h>

/* getproc program. */
#define FOREVER for(;;)

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char * argv[])
{
  int status;
  long int ret = EXIT_FAILURE;
  pid_t pid;
  struct process *proc = NULL;

  /* fork */
  if((pid = fork()) >= 0) {

    /* Child execute code if pid == 0. */
    /* Gets the process pgrp. */
    if((proc = prfind(pid)) != NULL) {
      printf("Adress 0x%8.0x\n", proc);
      _exit(EXIT_SUCCESS);
    } else {
      perror("prfind");
      _exit(EXIT_FAILURE);
    }
  } else {

    /* Parent executes otherwise. */
    while(wait(&status) != pid)
      ;
  }
  exit(EXIT_SUCCESS);
}

/*
 * getprocs -- retrieve the list of processes.
 */
struct kinfo_proc *getprocs(int *count, int threads)
{
  struct kinfo_proc *procbase = NULL ;
  unsigned int maxslp ;
  size_t size = sizeof(maxslp) ;
  int maxslp_mib[] = {
    CTL_VM,
    VM_MAXSLP
  };
  int mib[ 6 ] = {
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
long int showinfo(int threads)
{
  struct kinfo_proc *list, *proc;
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
