#include <stdio.h>
#include <stdlib.h>

struct tagRecord {
  int uid;
  char login[ 9 ];
};

typedef struct tagRecord tRecord;

tRecord records[ 5 ] = {
  { 1, "user1" },
  { 2, "user2" },
  { 3, "user3" },
  { 4, "user4" },
  { 5, "user5" }
};
