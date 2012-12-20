#ifndef SORT_H
#define SORT_H

#include        <unistd.h>
#include        <stdlib.h>
#include        <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
  void
  sort (void *base, unsigned int *index, size_t num, size_t size,
        int (*cmp) (const void *, const void *),
        void (*swap) (void *, void *, int size));
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /* SORT_H */
