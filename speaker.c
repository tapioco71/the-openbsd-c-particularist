/* -*- mode: c; -*- */

/* speaker.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <dev/isa/spkrio.h>

/* speaker program. */

/* Functions prototypes. */
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  int fd, i;
  long int ret = EXIT_FAILURE;
  tone_t tones[ 5 ] = {
    { 440, 200 },
    { 880, 200 },
    { 1660, 200 },
    { 3320, 200 },
    { 6640, 200 }
  };
  /* Call ioctl. */
  if((fd = open("/dev/speaker", O_WRONLY, 0)) >= 0) {
    for(i = 0; i < 5; i++) {
      if(ioctl(fd, SPKRTONE, &tones[ i ]) < 0) {
	perror("speaker");
	break;
      }
    }
    close(fd);
    if(i >= 5)
      ret = EXIT_SUCCESS;
  } else {
    perror("speaker");
  }
  exit(ret);
}

/* End of speaker.c file. */
