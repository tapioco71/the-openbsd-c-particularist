/* -*- mode: c-mode; -*- */

/* ifft-c.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>
#include <complex.h>
#include <string.h>

/* Functions prototypes. */
bool idft_(double complex [], size_t);
int main(int, char *[]);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  size_t i;
  double complex x[] = {
    0.0 + I * 0.0,
    1.0 + I * 0.0,
    2.0 + I * 0.0,
    2.0 + I * 0.0,
    1.0 + I * 0.0,
    0.0 + I * 0.0,
    -1.0 + I * 0.0,
    -2.0 + I * 0.0,
    -2.0 + I * 0.0,
    -1.0 + I * 0.0,
    0.0 + I * 0.0
  };

  if(idft_(x, 11) == true) {
    for(i = 0; i < 11; i++) {
      printf("%lf ", creal(x[ i ]));
      if(cimag(x[ i ]) >= 0.0)
	printf(" + ");
      printf("%lf i\n", cimag(x[ i ]));
    }
    ret = EXIT_SUCCESS;
  }
}

/* End of ifft-c.c file. */

