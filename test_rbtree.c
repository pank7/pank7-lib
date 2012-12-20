#include        <stdio.h>
#include        <stdlib.h>
#include        "rbtree.h"

typedef struct
{
  int                   number;
  struct rb_node        hook;
} data_type;

data_type *
search(struct rb_root *t, int num);

data_type *
insert(struct rb_root *t, data_type *d);

data_type *
delete(struct rb_root *t, data_type *d);

int
main(int argc, char *argv[])
{
  int                   tmp = -1;
  struct rb_root        tree = RB_ROOT;
  struct rb_node        *node = NULL;
  data_type             *data = NULL, *ret = NULL;
  FILE                  *fin = stdin;

  if (argc > 1) {
    fin = fopen(argv[1], "r");
  }
  if (fin == NULL) {
    perror(argv[1]);
    return 1;
  }

  /* input & build tree */
  while (fscanf(fin, "%d", &tmp) != EOF) {
    data = (data_type *)malloc(sizeof(data_type));
    RB_CLEAR_NODE(&data->hook);
    data->number = tmp;
    ret = insert(&tree, data);
    if (ret != NULL) {
      fprintf(stdout, "this one exists: %d\n", data->number);
      free((void *)data);
    }
  }

  /* search & delete found */
  fprintf(stdout, "search & delete:\n");
  while (fscanf(fin, "%d", &tmp) != EOF) {
    data = search(&tree, tmp);
    if (data == NULL) {
      fprintf(stdout, "not found!\n");
    } else {
      fprintf(stdout, "found: %d!\n", data->number);
      data = delete(&tree, data);
      free((void *)data);
    }
  }

  /* print the rest */
  fprintf(stdout, "the rest:\n");
  node = rb_first(&tree);
  while (node != NULL) {
    data = rb_entry(node, data_type, hook);
    fprintf(stdout, "%d\n", data->number);
    node = rb_next(node);
  }

  /* delete the entire tree */
  while (!RB_EMPTY_ROOT(&tree)) {
    node = tree.rb_node;
    data = rb_entry(node, data_type, hook);
    data = delete(&tree, data);
    free((void *)data);
  }

  fclose(fin);

  return 0;
}

data_type *
search(struct rb_root *t, int num)
{
  struct rb_node        *node = t->rb_node;
  data_type             *data = NULL;

  while(node) {
    data = rb_entry(node, data_type, hook);

    if (num < data->number) {
      node = node->rb_left;
    } else if (num > data->number) {
      node = node->rb_right;
    } else {
      return data;
    }
  }

  return NULL;
}

data_type *
insert(struct rb_root *t, data_type *d)
{
  struct rb_node        **node = &t->rb_node;
  struct rb_node        *parent = NULL;
  data_type             *data = NULL;

  while(*node) {
    parent = *node;
    data = rb_entry(parent, data_type, hook);

    if (d->number < data->number) {
      node = &parent->rb_left;
    } else if (d->number > data->number) {
      node = &parent->rb_right;
    } else {
      return d;
    }
  }

  rb_link_node(&d->hook, parent, node);
  rb_insert_color(&d->hook, t);

  return NULL;
}

data_type *
delete(struct rb_root *t, data_type *d)
{
  rb_erase(&d->hook, t);

  return d;
}
