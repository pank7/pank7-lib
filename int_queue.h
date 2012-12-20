#ifndef __INT_QUEUE
#define __INT_QUEUE

#include        "list.h"

#ifdef  __cplusplus
extern "C" {
#endif

  typedef struct int_queue_type {
    int         size;
    list_head   head;
  } int_queue_type;

  int_queue_type *
  int_queue_new();

  void
  int_queue_del(int_queue_type *iq);

  int
  int_queue_empty(int_queue_type *iq);

  int
  int_queue_front(int_queue_type *iq);

  int
  int_queue_back(int_queue_type *iq);

  int
  int_queue_push_front(int_queue_type *iq, int val);

  int
  int_queue_pop_front(int_queue_type *iq);

  int
  int_queue_push_back(int_queue_type *iq, int val);

  int
  int_queue_pop_back(int_queue_type *iq);

#ifdef  __cplusplus
}
#endif

#endif  /* __INT_QUEUE */
