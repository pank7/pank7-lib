#ifndef __INT_SET
#define __INT_SET

#include        "rbtree.h"

#ifdef  __cplusplus
extern "C" {
#endif

  typedef struct int_set_type {
    int                 size;
    struct rb_root      head;
  } int_set_type;

  int_set_type *
  int_set_new();

  void
  int_set_del(int_set_type *is);

  int
  int_set_empty(int_set_type *is);

  int
  int_set_search(int_set_type *is, int val);

  int
  int_set_insert(int_set_type *is, int val);

  int
  int_set_remove(int_set_type *is, int val);

#ifdef  __cplusplus
}
#endif

#endif  /* __INT_SET */
