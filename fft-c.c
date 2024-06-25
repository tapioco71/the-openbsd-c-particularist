/* -*- mode: c-mode; -*- */

/* fft-c.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>
#include <complex.h>
#include <string.h>

bool dft(double complex x[], size_t count)
{
  bool ret = false;
  double complex *temp, wn;
  size_t j, k;

  if(count > 0) {
    if((temp = (double complex *)				\
	calloc(count, sizeof(double complex))) != NULL) {
      for(j = 0; j < count; j++) {
	for(k = 0; k < count; k++) {
	  wn = cexp(-2.0 * M_PI * I / (double) count);
	  temp[ j ] += x[ k ] * cpow(wn, (double) (j * k));
	}
      }
      memcpy(x, temp, sizeof(double complex) * count);
      free(temp);
      ret = true;
    }
  }
  return ret;
}

