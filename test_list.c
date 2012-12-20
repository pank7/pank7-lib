#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <errno.h>
#include        "list.h"

typedef struct
{
  int           number;
  list_head     hook;
} data_type;

int
main(int argc, char *argv[])
{
  LIST_HEAD(list);
  int                   tmp = -1;
  FILE                  *fin = stdin;
  data_type             *data = NULL, *n = NULL;

  if (argc > 1) {
    fin = fopen(argv[1], "r");
  }
  if (fin == NULL) {
    perror(argv[1]);
    exit(1);
  }

  while (fscanf(fin, "%d", &tmp) != EOF) {
    data = (data_type *)malloc(sizeof(data_type));
    INIT_LIST_HEAD(&data->hook);
    data->number = tmp;
    list_add_tail(&data->hook, &list);
  }

  list_for_each_entry_reverse(data, &list, hook) {
    fprintf(stdout, "%d\n", data->number);
  }

  list_for_each_entry_safe(data, n, &list, hook) {
    list_del(&data->hook);
    free((void *)data);
  }

  fclose(fin);

  return 0;
}
