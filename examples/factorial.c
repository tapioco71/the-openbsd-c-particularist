/* -*- mode: c-mode; -*- */

/* factorial.c file. */
#include <stdio.h>
#include <stdlib.h>

/* factorial program. */
/* Function prototypes. */
int main(int, char *[]);
unsigned long int factorial(unsigned long int);

/* Main function. */
int main(int argc, char *argv[])
{
  long int ret = EXIT_FAILURE;
  unsigned long int n, m;

  /*
   * Messaging the user to enter the integer
   * number.
   */
  printf("Enter an integer number: ");
  scanf("%lu", &n);
  if(n <= 20ul) {
    m = factorial(n);
    printf("The factorial of %lu is %lu.\n", n, m);
    ret = EXIT_SUCCESS;
  } else
    perror("n must be a positive integer between 0 and 20");
  exit(ret);
}

/*
 * The factorial function which computes
 * n! = 1 * 2 * 3 * ... * n
 */
unsigned long int factorial(unsigned long int n)
{
  /* computes n! */
  if((n == 0ul) || (n == 1ul))
    return 1ul;
  else
    return (n * factorial(n - 1));
}

/* End of factorial.c file. */
