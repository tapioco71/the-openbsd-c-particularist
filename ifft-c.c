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
  double complex x[] = {
    1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0
  };

  if(idft_(x, 10) == true) {
    for(i = 0; i < 10; i++)
      printf("%f\n", x[ i ]);
    ret = EXIT_SUCCESS;
  }
}

/* End of ifft-c.c file. */

