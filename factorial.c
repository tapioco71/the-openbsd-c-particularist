#include <stdio.h>
#include <stdlib.h>

/*
 * Function prototypes.
 */
int main(int, char *[]);
unsigned long int factorial(unsigned long int);

/*
 * Main function body.
 */

int main(int argc, char *argv[])
{
  unsigned long int n, m;
  /*
   * Messaging the user to enter the integer
   * number.
   */
  printf("Enter an integer number: ");
  scanf("%lu", &n);
  if(n > 20ul) {
    perror("n must be a positive integer between 0 and 20.\n");
    exit(EXIT_FAILURE);
  }
  m = factorial(n);
  printf("The factorial of %lu is %lu.\n", n, m);
  exit(EXIT_SUCCESS);
}

/*
 * The factorial function which computes
 * n! = 1 * 2 * 3 * ... * n
 */

unsigned long int factorial(unsigned long int n)
{
  /*
   * computes n!
   */
  if((n == 0ul) || (n == 1ul))
    return 1ul;
  else
    return n * factorial(n - 1);
}
