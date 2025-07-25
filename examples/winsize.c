/* -*- mode: c; -*- */

/* winsize.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/ttycom.h>

/* winsize program. */
/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd, i;
  long int ret = EXIT_FAILURE;
  struct winsize ws;

  /* Call ioctl. */
  if((fd = open("/dev/tty", O_RDWR | O_NOCTTY)) >= 0) {
    if(ioctl(fd, TIOCGWINSZ, &ws) >= 0) {
      if((ws.ws_row == 0) && (ws.ws_col == 0))
	printf("Ignoring the winsize structure.\n");
      else {
	printf("terminal number of rows: %d\n", ws.ws_row);
	printf("terminal number of columns: %d\n", ws.ws_col);
	printf("terminal x pixels size: %d\n", ws.ws_xpixel);
	printf("terminal y pixels size: %d\n", ws.ws_ypixel);
      }
      ret = EXIT_SUCCESS;
    } else
      perror("winsize");
    close(fd);
  }
  exit(ret);
}

/* End of winsize.c file. */
