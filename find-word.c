/* -*- mode: c-mode; -*- */

/* find-word.c file. */
#include "find-word.h"

/* find-word program. */

/* Main function. */
int main(int argc, char *argv[])
{
  char ch, dictionary_path[ BUFSIZ ], combstr[ BUFSIZ ];
  char *letters, word[ BUFSIZ ];
  bool found, *combstbl;
  long int ret = EXIT_FAILURE;
  FILE *dict_file;
  size_t i, j, k, m, n;
  size_t combs_count, count, letters_count, chars_count;
  size_t *indices, **combs;

  /* Check our arguments. */
  switch(argc) {
  case 2:
    strncpy(dictionary_path, DEFAULT_DICTIONARY_PATH, BUFSIZ);
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
    lowerize(letters, MAXINT);
    letters_count = strnlen(letters, MAXINT);
    if(letters_count < 21) {

      /* Open system dictionary file. */
      if((dict_file = fopen(dictionary_path, "r")) != NULL) {

	/*
	 * loop starting from same length for words as
	 * the entered sets of characters.
	 */
	for(count = letters_count; count >= 3; count--) {

	  /* computes the number of the character combinations. */
	  combs_count = binomial(letters_count, count);
	  printf("combinations count: %ld\n", combs_count);
	  combs = allocateCombs(combs_count, count);
	  if(combs) {
	    indices = (size_t *) calloc(count, sizeof(size_t));
	    if(indices) {

	      /* generate all character combinations without repetition. */
	      combinations(indices, letters_count, count, combs);
	      for(i = 0; combs[ i ] != NULL; i++) {
		if(getCombString(combstr, letters, combs[ i ], count) == EXIT_SUCCESS)

		  /* reset the file pointer to the start of the file. */
		  fseek(dict_file, 0, SEEK_SET);

		/* loop the dictionary words database. */
		while(fgets(word, BUFSIZ, dict_file) != NULL) {
		  word[ strcspn(word, "\n") ] = '\0';
		  m = strnlen(word, BUFSIZ);

		  /*
		   * if the word has the same length of
		   * the combinations then check for
		   * characters in it.
		   */
		  if(m == count) {
		    combstbl = (bool *) calloc(count, sizeof(bool));
		    if(combstbl) {
		      chars_count = 0;
		      bzero(combstbl, sizeof(bool) * count);

		      /*
		       * looking for characters in word.
		       * Choose the words that contains all
		       * the characters in the combination.
		       */
		      for(k = 0; k < count; k++) {
			for(j = 0; j < count; j++) {
			  if(word[ j ] == combstr[ k ]) {
			    if(combstbl[ j ] == false) {
			      combstbl[ j ] = true;
			      ++chars_count;
			      break;
			    }
			  }
			}
		      }
		      if(chars_count == count)
			printf("word: %s\n", word);
		      free(combstbl);
		    }
		  }
		}
	      }
	      free(indices);
	    }
	    deallocateCombs(combs);
	  }
	}
	fclose(dict_file);
      } else
	fprintf(stderr, "could not open dictionary file: %s\n", dictionary_path);
    } else
      perror("too much letters given: > 20!");
  }
  exit(ret);
}

/*
 * allocateCombs -- allocate combinations arrays.
 */
size_t **allocateCombs(size_t n, size_t k)
{
  size_t **ret;
  size_t i;

  if(n > 0) {
    if(k > 0) {
      ret = calloc(n + 1, sizeof(size_t *));
      if(ret) {
	for(i = 0; i < n; i++) {
	  ret[ i ] = (size_t *) calloc(k, sizeof(size_t));
	  if(!ret[ i ])
	    break;
	}
	ret[ i ] = NULL;
      }
    }
  }
  return ret;
}

/*
 * deallocateCombs -- deallocate combinations arrays.
 */
long int deallocateCombs(size_t **c)
{
  long int ret = EXIT_FAILURE;
  size_t i;

  if(c) {
    for(i = 0; c[ i ] != NULL; i++)
      free(c[ i ]);
    free(c);
    ret = EXIT_SUCCESS;
  }
  return ret;
}

/*
 * lowerize -- tolower every characters in a string.
 */
void lowerize(char *s, size_t l)
{
  char *p = NULL;

  if(s) {
    p = s;
    while((*p != '\0') && ((p - s) <= l)) {
      *p = tolower(*p);
      ++p;
    }
  }
}

/*
 * getCombString -- return the string from characters
 *                  and indices sets.
 */
long int getCombString(char *comb, char *charset, size_t *indices, size_t count)
{
  long int ret = EXIT_FAILURE;
  size_t i;

  if(comb) {
    if(charset) {
      if(indices) {
	if(count > 0) {
	  for(i = 0; i < count; i++)
	    comb[ i ] = charset[ indices[ i ] - 1 ];
	  comb[ i ] = '\0';
	  ret = EXIT_SUCCESS;
	}
      }
    }
  }
  return ret;
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

  /* Set the base combination: 1, 2, 3, ..., n */
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
