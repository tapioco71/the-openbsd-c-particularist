#include <stdio.h>
#include <stdlib.h>

/*
 * Function prototypes.
 */

int main(int, char *[]);
long int factorial(long int);

/*
 * Main function body.
 */

int main(int argc, char *argv[])
{
  long int n, m;
  /*
   * Messaging the user to enter the integer
   * number.
   */
  printf("Enter an integer number: ");
  scanf("%ld", &n);
  if(n > 31ul) {
    perror("n must be a positive integer between 0 and 31.\n");
    exit(EXIT_FAILURE);
  }
  m = factorial(n);
  printf("The factorial of %d is %d.\n", n, m);
  exit(EXIT_SUCCESS);
}

/*
 * The factorial function which computes
 * n! = 1 * 2 * 3 * ... * n
 */

long int factorial(long int n)
{
  /*
   * computes n!
   */
  if((n == 0ul) || (n == 1ul))
    return 1ul;
  else
    return n * factorial(n - 1);
}
