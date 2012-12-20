#ifndef __INT_LIST_NODE
#define __INT_LIST_NODE

#include        "list.h"

#ifdef  __cplusplus
extern "C" {
#endif

  typedef struct int_listnode_type {
    int           val;
    list_head     hook;
  } int_listnode_type;

  int_listnode_type *
  int_listnode_new()
  {
    int_listnode_type         *in = NULL;

    in = (int_listnode_type *)malloc(sizeof(int_listnode_type));
    in->val = 0;
    INIT_LIST_HEAD(&in->hook);

    return in;
  }

  void
  int_listnode_del(int_listnode_type *in)
  {
    free((void *)in);
  }

#ifdef  __cplusplus
}
#endif

#endif  /* __INT_LIST_NODE */
