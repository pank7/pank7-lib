#include        <stdlib.h>
#include        "int_queue.h"
#include        "int_listnode.h"

int_queue_type *
int_queue_new()
{
  int_queue_type        *iq = NULL;

  iq = (int_queue_type *)malloc(sizeof(int_queue_type));
  iq->size = 0;
  INIT_LIST_HEAD(&iq->head);

  return iq;
}

void
int_queue_del(int_queue_type *iq)
{
  int_listnode_type     *data = NULL, *n = NULL;

  list_for_each_entry_safe(data, n, &iq->head, hook) {
    list_del(&data->hook);
    int_listnode_del((void *)data);
  }

  free((void *)iq);
}

int
int_queue_empty(int_queue_type *iq)
{
  return list_empty(&iq->head);
}

int
int_queue_front(int_queue_type *iq)
{
  int_listnode_type     *data = NULL;

  data = list_entry(iq->head.next, int_listnode_type, hook);

  return data->val;
}

int
int_queue_back(int_queue_type *iq)
{
  int_listnode_type     *data = NULL;

  data = list_entry(iq->head.prev, int_listnode_type, hook);

  return data->val;
}

int
int_queue_push_front(int_queue_type *iq, int val)
{
  int_listnode_type     *data = NULL;

  data = int_listnode_new();
  data->val = val;
  list_add(&data->hook, &iq->head);
  ++iq->size;

  return val;
}

int
int_queue_pop_front(int_queue_type *iq)
{
  int_listnode_type     *data = NULL;
  int                   val;

  data = list_entry(iq->head.next, int_listnode_type, hook);
  val = data->val;
  list_del(iq->head.next);
  int_listnode_del(data);
  --iq->size;

  return val;
}

int
int_queue_push_back(int_queue_type *iq, int val)
{
  int_listnode_type     *data = NULL;

  data = int_listnode_new();
  data->val = val;
  list_add_tail(&data->hook, &iq->head);
  ++iq->size;

  return val;
}

int
int_queue_pop_back(int_queue_type *iq)
{
  int_listnode_type     *data = NULL;
  int                   val;

  data = list_entry(iq->head.prev, int_listnode_type, hook);
  val = data->val;
  list_del(iq->head.prev);
  int_listnode_del(data);
  --iq->size;

  return val;
}
