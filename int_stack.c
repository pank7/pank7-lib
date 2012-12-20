#include        <stdlib.h>
#include        "int_stack.h"
#include        "int_listnode.h"

int_stack_type *
int_stack_new()
{
  int_stack_type        *is = NULL;

  is = (int_stack_type *)malloc(sizeof(int_stack_type));
  is->size = 0;
  INIT_LIST_HEAD(&is->head);

  return is;
}

void
int_stack_del(int_stack_type *is)
{
  int_listnode_type     *data = NULL, *n = NULL;

  list_for_each_entry_safe(data, n, &is->head, hook) {
    list_del(&data->hook);
    int_listnode_del((void *)data);
  }

  free((void *)is);
}

int
int_stack_empty(int_stack_type *is)
{
  return list_empty(&is->head);
}

int
int_stack_head(int_stack_type *is)
{
  int_listnode_type     *data = NULL;

  data = list_entry(is->head.next, int_listnode_type, hook);

  return data->val;
}

int
int_stack_push(int_stack_type *is, int val)
{
  int_listnode_type     *data = NULL;

  data = int_listnode_new();
  data->val = val;
  list_add(&data->hook, &is->head);
  ++is->size;

  return val;
}

int
int_stack_pop(int_stack_type *is)
{
  int_listnode_type     *data = NULL;
  int                   val;

  data = list_entry(is->head.next, int_listnode_type, hook);
  val = data->val;
  list_del(is->head.next);
  int_listnode_del(data);
  --is->size;

  return val;
}

