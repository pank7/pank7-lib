#include        <stdio.h>
#include        "int_queue.h"

int
main(int argc, char *argv[])
{
  FILE                  *fin = stdin;
  int_queue_type        *iq = NULL;
  int                   val;

  if (argc > 1) {
    fin = fopen(argv[1], "r");
  }
  if (fin == NULL) {
    perror(argv[1]);
    return 1;
  }

  iq = int_queue_new();

  fprintf(stdout, "push front...\n");
  while (fscanf(fin, "%d", &val) != EOF) {
    int_queue_push_front(iq, val);
  }

  fprintf(stdout, "push back...\n");
  while (fscanf(fin, "%d", &val) != EOF) {
    int_queue_push_back(iq, val);
  }

  fprintf(stdout, "queue size: %d\n", iq->size);
  fprintf(stdout, "queue front: %d\n", int_queue_front(iq));
  fprintf(stdout, "queue back: %d\n", int_queue_back(iq));

  fprintf(stdout, "and then pop front 1 time...\n");
  if (!int_queue_empty(iq)) {
    val = int_queue_pop_front(iq);
    fprintf(stdout, "%d\n", val);
  }
  fprintf(stdout, "queue size: %d\n", iq->size);

  fprintf(stdout, "and then pop back 1 time...\n");
  if (!int_queue_empty(iq)) {
    val = int_queue_pop_back(iq);
    fprintf(stdout, "%d\n", val);
  }
  fprintf(stdout, "queue size: %d\n", iq->size);

  int_queue_del(iq);

  fclose(fin);

  return 0;
}
