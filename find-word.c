/* -*- mode: c-mode; -*- */

/* find-word.c file. */
#include "find-word.h"

/* find-word program. */

/* Main function. */
int main(int argc, char *argv[])
{
  char ch, dictionary_path[ BUFSIZ ];
  bool found;
  int i, j;
  FILE *dictionary;
  char *letters, word[ BUFSIZ ];
  long int ret = EXIT_FAILURE;
  size_t m, n, count, letters_count, *indices, **perms;

  /* Check our arguments. */
  switch(argc) {
  case 2:
    strncpy(dictionary_path, "/usr/share/dict/words", BUFSIZ);
    letters = argv[ 1 ];
    break;

  case 3:
    strncpy(dictionary_path, argv[ 1 ], BUFSIZ);
    letters = argv[ 2 ];
    break;

  default:
    letters = NULL;
    fprintf(stderr, "usage: find-word <dictionary-file> <letters>, find-word <letters>\n");
    break;
  }
  if(letters) {
    letters_count = strnlen(letters, MAXINT);
    if(letters_count < 21) {

      /* Open system dictionary file. */
      if((dictionary = fopen(dictionary_path, "r")) != NULL) {
	for(count = letters_count; count >= 3; count--) {
	  fseek(dictionary, 0, SEEK_SET);
	  n = binomial(letters_count, count);
	  printf("permutations count: %ld, word length: %ld\n", n, count);
	  perms = calloc(n + 1, sizeof(size_t *));
	  if(perms) {
	    for(i = 0; i < n; i++) {
	      perms[ i ] = (size_t *) calloc(count + 1, sizeof(size_t));
	      if(!perms[ i ])
		break;
	    }
	    if(i == n) {
	      perms[ i ] = NULL;
	      indices = (size_t *) calloc(letters_count, sizeof(char));
	      if(indices) {
		combinations(indices, letters_count, count, perms);
		while(fgets(word, BUFSIZ, dictionary) != NULL) {
		  word[ strnlen(word, BUFSIZ) - 1 ] = '\0';
		  m = strnlen(word, BUFSIZ);
		  for(i = 0; i < m; i++)
		    word[ i ] = tolower(word[ i ]);
		  if(m == count) {
		    for(i = 0; perms[ i ] != NULL; i++) {
		      found = true;
		      for(j = 0; j < count; j++) {
			ch = letters[ perms[ i ][ j ] - 1 ];
			if(strchr(word, ch) == NULL) {
			  found = false;
			  break;
			}
		      }
		      if(found == true)
			printf("word: %s\n", word);
		    }
		  }
		}
		ret = EXIT_SUCCESS;
	      }
	    }
	    for(i = 0; perms[ i ] != NULL; i++) {
	      if(perms[ i ])
		free(perms[ i ]);
	    }
	    free(perms);
	  } else
	    perror("could not store permutations");
	}
	fclose(dictionary);
      } else
	fprintf(stderr, "could not open dictionary file: %s\n", dictionary_path);
    } else
      perror("too much letters given: > 20!");
  } else
    perror("no letters given");
  exit(ret);
}

/*
 * printArray -- print array
 */
void printArray(char *s, void *a, size_t c)
{
  char arg[ BUFSIZ ];
  size_t i;

  /* */
  if(s) {
    if(a) {
      snprintf(arg, BUFSIZ, "%s", s);
      for(i = 0; i < c; i++) {
	if(i == 0)
	  printf("[ ");
	if(strncmp(s, "%c", BUFSIZ) == 0)
	  printf(arg, ((char *) a)[i ]);
	if(strncmp(s, "%d", BUFSIZ) == 0)
	  printf(arg, ((unsigned char *) a)[ i ]);
	else if(strncmp(s, "%ld", BUFSIZ) == 0)
	  printf(arg, ((long *) a)[ i ]);
	if(i < (c - 1))
	  printf(" ");
	else
	  printf(" ]");
      }
    }
  }
}

/*
 * factorial -- compute n!
 */
size_t factorial(size_t n)
{
  if((n == 0) || (n == 1))
    return 1;
  else
    return (n * factorial(n - 1));
}

/*
 * binomial -- return the number of combinations
 *             without repetitions:
 *             c = n! / (k! (n - k)!)
 */
size_t binomial(size_t n, size_t k)
{
  return (factorial(n) / (factorial(k) * factorial(n - k)));
}

/*
 * combinations -- generates the combinations without
 *                 repetitions and with no order.
 */
void combinations(size_t *s, size_t m, size_t n, size_t **c)
{
  size_t i, j;

  /* Set the base combination: 1, 2, 3, ... */
  for (i = 0; i < n; i++)
    s[ i ] = n - i;
  j = 0;
  FOREVER  {
    if(c[ j ])
      memcpy(c[ j++ ], s, sizeof(size_t) * n);

    /*
     * this check is not strictly necessary,
     * but if m is not close to n,
     * it makes the whole thing quite a bit faster
     */
    i = 0;
    if(s[ i ]++ < m)
      continue;

    for(; s[ i ] >= m - i;)
      if(++i >= n)
	return;
    for(s[ i ]++; i; i--)
      s[ i - 1 ] = s[ i ] + 1;
  }
}

/* End of find-word.c file. */
