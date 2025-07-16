/* -*- mode: c; -*- */

/* File random2.c. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define GUESSES_COUNT 10

/* Function prototypes. */
int again(void);

/* Main function. */
int main(int argc, char *argv[])
{
  long int nReturnValue = EXIT_FAILURE;
  char c;
  int i;
  uint32_t g, n;

  /* */
  n = arc4random();
  for(i = 0; i < GUESSES_COUNT; i++) {
    printf("Guess #%d: what is the number? ", i + 1);
    scanf("%u", &g);
    if(g < n)
      printf("your guess is lower than the choosen number.\n");
    else if(g > n)
      printf("your guess is higher that the choosen number.\n");
    else {
      printf("Correct the number %u is the choosen one! You it took you %d tries.\n", n, i);
      break;
    }
    if((i + 1) < GUESSES_COUNT)
      if(again() == 0)
	i = GUESSES_COUNT;
  }
  if(i >= GUESSES_COUNT)
    printf("The number to guess was %u\n.", n);
  exit(nReturnValue);
}

int again(void)
{
  char answer[ 4 ];

  /* */
  printf("do you want to continue? ");
  scanf("%s", answer);
  if(strncmp(answer, "yes", 3) == 0)
    return 1;
  else
    return 0;
}

/* End of random2.c file. */
