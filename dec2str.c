/* -*- mode: c-mode; -*- */

/* File dec2str.c */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <math.h>

/* Prototypes. */
int main(int, char *[]);
long int dec2str(long int, char *, size_t);

/* Main function. */
int main(int argc, char *argv[])
{
  char str[ BUFSIZ ];
  long int n;
  long int ret = EXIT_FAILURE;

  printf("Enter an integer number: ");
  scanf("%ld", &n);
  ret = dec2str(n, str, BUFSIZ);
  if(ret == EXIT_SUCCESS)
    printf("the number is: %s\n", str);
  else
    perror("could not convert decimal using dec2str");
  exit(ret);
}

/*
 * dec2str -- convert a long int decimal to a string.
 *            Returning EXIT_SUCCESS on success and
 *            EXIT_FAILURE otherwise. The string should
 *            be pointed by str. If no room in the string
 *            the routine fails.
 */
long int dec2str(long int n, char *str, size_t l)
{
  char sign = 0;
  long int i, j, k, p, rem;

  if(str) {
    if(l > 0) {
      bzero(str, l);
      i = n;
      j = 0;
      p = 0;
      if(i < 0) {
	sign = '-';
	i = -i;
	p = 1;
	str[ 0 ] = '-';
      }
      do {
	rem = i % 10;
	for(k = j + p; k >= p; k--)
	  str[ k + 1 ] = str[ k ];
	str[ p ] = '0' + rem;
	if((j + p) >= l)
	  return EXIT_FAILURE;
	++j;
	i /= 10;
      } while(i > 0);
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}
