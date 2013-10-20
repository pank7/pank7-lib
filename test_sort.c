#include        <stdio.h>
#include        <stdlib.h>
#include        "sort.h"

#define ARRAY_LEN       16

int
cmp_int(const void *left, const void *right)
{
  return *(int *)left - *(int *)right;
}

int
main(int argc, char *argv[])
{
  int           array[ARRAY_LEN];
  int           i = 0;

  srandomdev();

  for (i = 0; i < ARRAY_LEN; ++i) {
    array[i] = (int)(random() % (ARRAY_LEN * 2));
    fprintf(stdout, "%d ", array[i]);
  }
  fprintf(stdout, "\n");

  sort(array, ARRAY_LEN, sizeof(int), cmp_int, NULL);

  for (i = 0; i < ARRAY_LEN; ++i) {
    fprintf(stdout, "%d ", array[i]);
  }
  fprintf(stdout, "\n");

  return 0;
}
