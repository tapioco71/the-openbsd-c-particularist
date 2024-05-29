/* -*- mode: c-mode; -*- */
/*
 * speaker program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/ttycom.h>


/*
 * Functions prototypes.
 */

int main(int, char *[]);

/*
 * The main function.
 */

int main(int argc, char *argv[])
{
  int fd, i;
  long int ret = EXIT_FAILURE;
  struct winsize ws;
  /*
   * Call ioctl.
   */
  if((fd = open("/dev/tty00", O_RDONLY)) >= 0) {
    ioctl(fd, TIOCGWINSZ, &ws);
    if((ws.ws_row == 0) && (ws.ws_col == 0)) {
      perror("winsize");
    } else {
      printf("terminal number of rows: %d\n", ws.ws_row);
      printf("terminal number of columns: %d\n", ws.ws_col);
      printf("terminal x pixels size: %d\n", ws.ws_xpixel);
      printf("terminal y pixels size: %d\n", ws.ws_ypixel);
      close(fd);
      ret = EXIT_SUCCESS;
    }
    return ret;
  }
