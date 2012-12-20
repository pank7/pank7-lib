#include        <stdio.h>
#include        "int_set.h"

int
main(int argc, char *argv[])
{
  FILE                  *fin = stdin;
  int_set_type          *is = NULL;
  int                   tmp, ret;

  if (argc > 1) {
    fin = fopen(argv[1], "r");
  }
  if (fin == NULL) {
    perror(argv[1]);
    return 1;
  }

  is = int_set_new();

  while (fscanf(fin, "%d", &tmp) != EOF) {
    ret = int_set_insert(is, tmp);
    if (ret == 0) {
      fprintf(stdout, "this one exists: %d!\n", tmp);
    }
  }

  fprintf(stdout, "set size: %d\n", is->size);
  fprintf(stdout, "search:\n");
  while (fscanf(fin, "%d", &tmp) != EOF) {
    ret = int_set_search(is, tmp);
    if (ret) {
      fprintf(stdout, "found: %d\n", tmp);
    } else {
      fprintf(stdout, "not found: %d\n", tmp);
    }
  }

  fprintf(stdout, "remove:\n");
  while (fscanf(fin, "%d", &tmp) != EOF) {
    ret = int_set_remove(is, tmp);
    if (ret) {
      fprintf(stdout, "removed: %d, set size: %d\n", tmp, is->size);
    } else {
      fprintf(stdout, "not found: %d\n", tmp);
    }
  }

  int_set_del(is);

  fclose(fin);

  return 0;
}
