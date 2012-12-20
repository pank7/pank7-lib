#include        <stdio.h>
#include        "int_stack.h"

int
main(int argc, char *argv[])
{
  FILE                  *fin = stdin;
  int_stack_type        *is = NULL;
  int                   i = 0, val;

  if (argc > 1) {
    fin = fopen(argv[1], "r");
  }
  if (fin == NULL) {
    perror(argv[1]);
    return 1;
  }

  is = int_stack_new();

  while (fscanf(fin, "%d", &val) != EOF) {
    int_stack_push(is, val);
  }

  fprintf(stdout, "stack size: %d\n", is->size);
  fprintf(stdout, "stack head: %d\n", int_stack_head(is));
  fprintf(stdout, "and then pop 3 times...\n");

  for (i = 0; i < 3 && !int_stack_empty(is); ++i) {
    val = int_stack_pop(is);
    fprintf(stdout, "%d\n", val);
  }
  
  fprintf(stdout, "stack size: %d\n", is->size);

  int_stack_del(is);

  fclose(fin);

  return 0;
}
