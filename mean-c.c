/* -*- mode: c-mode; -*- */

/* mean-c.c file. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

double mean(double [], size_t);

double mean(double values[], size_t count)
{
  double ret = 0.;
  size_t i;

  /* Computing the mean for "count" values. */
  for(i = 0; i < count; i++)
    ret += values[ i ];
  return (ret / (double) count);
}

/* End of mean-c.c file. */
