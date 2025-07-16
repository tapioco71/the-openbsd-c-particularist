/* -*- mode: c; -*- */

/* File norm2-c.c. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/* Functions prototypes. */
double norm2_(double [], size_t);

/* Main function. */
int main(int argc, char *argv[])
{
  double values[] = {
    1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0
  };

  /* Computes the two norm of a vector. */
  printf("2 norm: %lf\n", norm2_(values, 10));
  exit(EXIT_SUCCESS);
}
