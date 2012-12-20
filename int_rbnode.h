#ifndef __INT_RB_NODE
#define __INT_RB_NODE

#include        "rbtree.h"

#ifdef  __cplusplus
extern "C" {
#endif

  typedef struct int_rbnode_type {
    int                 val;
    struct rb_node      hook;
  } int_rbnode_type;

  int_rbnode_type *
  int_rbnode_new()
  {
    int_rbnode_type    *isn = NULL;

    isn = (int_rbnode_type *)malloc(sizeof(int_rbnode_type));
    isn->val = 0;
    RB_CLEAR_NODE(&isn->hook);

    return isn;
  }

  void
  int_rbnode_del(int_rbnode_type *isn)
  {
    free((void *)isn);
  }

#ifdef  __cplusplus
}
#endif

#endif  /* __INT_RB_NODE */
