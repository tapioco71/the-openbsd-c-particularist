/* -*- mode: c-mode; -*- */
/*
 * speaker program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/ttycom.h>


/*
 * Functions prototypes.
 */
void prompt(void);
long int more(char *);
int main(int, char *[]);

/*
 * The main function.
 */

int main(int argc, char *argv[])
{
  int fd, i;
  long int ret = EXIT_FAILURE;
  struct termios old_tos, new_tos;
  /*
   * Check arguments count.
   */
  if(argc >= 2) {
    if((fd = open("/dev/tty", O_RDWR | O_NOCTTY)) >= 0) {
      /*
       * Retrieve terminal informations.
       */
      if(ioctl(fd, TIOCGETA, &old_tos) >= 0) {
	memcpy((void *) &new_tos, (void *) &old_tos, sizeof(struct termios));
	new_tos.c_iflag &= ~IGNBRK;             /* not ignore BREAK. */
	new_tos.c_lflag &= ~ECHO;               /* disable ECHO. */
	new_tos.c_lflag &= ~ISIG;               /* disable signals: INTR, QUIT, DSUSP, SUSP. */
	if(ioctl(fd, TIOCSETA, &new_tos) >= 0) {
	  /*
	   * printout files.
	   */
	  while(--argc)
	    if(more(*++argv) == EXIT_FAILURE)
	      break;
	  /*
	   * Reset the terminal configuration.
	   */
	  if(ioctl(fd, TIOCSETA, &old_tos) >= 0)
	    ret = EXIT_SUCCESS;
	  else
	    perror("pager");
	} else
	  perror("pager");
      } else
	perror("pager");
      close(fd);
    } else
      perror("pager");
  } else
    fprintf(stderr, "Usage: %s file [ file1 ... ]\n", *argv);
  exit(ret);
}

long int more(char *name)
{
  long int ret = EXIT_FAILURE;
  /*
   * Check arguments.
   */
  if(name) {
    FILE *fp;
    int line;
    char line_buf[ BUFSIZ ];
    /*
     * Open the file to print.
     */
    if((fp = fopen(name, "r")) != NULL) {
      for(;;) {
	line = 1;
	while(line < 24) {
	  /*
	   * If end-of-file, let them hit a key one
	   * more time and then go back.
	   */
	  if(gets(linebuf, BUFSIZ, fp) != NULL) {
	    fwrite(linebuf, 1, strlen(linebuf), stdout);
	    line++;
	  } else {
	    fclose(fp);
	    prompt();
	    return ret;
	  }
	}
	prompt();
      }
    }
  }
  return ret;
}

void prompt(void)
{
  int answer;
  //
  printf("Type any character for next page: ");
  answer = getchar();
  putchar('\n');
}
