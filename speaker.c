/* -*- mode: c-mode; -*- */
/*
 * speaker program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <dev/isa/spkrio.h>

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
  tone_t tones[ 5 ] = {
    { 440, 100 },
    { 880, 100 },
    { 1660, 100 },
    { 3320, 100 },
    { 6640, 100 }
  };
  /*
   * Call ioctl.
   */
  if((fd = open("/dev/speaker", O_WRONLY, 0)) >= 0) {
    for(i = 0; i < 5; i++) {
      ioctl(fd, SPKRTONE, &tones[ i ]);
    }
    ret = EXIT_SUCCESS;
  } else {
    perror("speaker");
  }
  exit(ret);
}
