#include        "sort.h"
/*
 * A fast, small, non-recursive O(nlog n) sort for the Linux kernel
 *
 * Jan 23 2005  Matt Mackall <mpm@selenic.com>
 */

static void
u32_swap (void *a, void *b, int size)
{
  unsigned int t = *(unsigned int *)a;
  *(unsigned int *)a = *(unsigned int *)b;
  *(unsigned int *)b = t;
}

static void
generic_swap (void *a, void *b, int size)
{
  char t;

  do {
    t = *(char *)a;
    *(char *)a++ = *(char *)b;
    *(char *)b++ = t;
  } while (--size > 0);
}

/**
 * sort - sort an array of elements
 * @base: pointer to data to sort
 * @num: number of elements
 * @size: size of each element
 * @cmp: pointer to comparison function
 * @swap: pointer to swap function or NULL
 *
 * This function does a heapsort on the given array. You may provide a
 * swap function optimized to your element type.
 *
 * Sorting time is O(n log n) both on average and worst-case. While
 * qsort is about 20% faster on average, it suffers from exploitable
 * O(n*n) worst-case behavior and extra memory requirements that make
 * it less suitable for kernel use.
 */
void
sort (void *base, unsigned int *index, size_t num, size_t size,
      int (*cmp) (const void *, const void *),
      void (*swap) (void *, void *, int size))
{
  /* pre-scale counters for performance */
  // ssize_t i = (num/2 - 1) * size, n = num * size, c, r;
  long i = (num / 2 - 1) * size, idxi = (num / 2 - 1) * sizeof(unsigned int);
  long n = num * size, idxn = num * sizeof(unsigned int), idxc, idxr, c, r;
  void *idx = (void *)index;

  if (!swap)
    swap = (size == 4 ? u32_swap : generic_swap);

  /* heapify */
  for ( ; i >= 0; i -= size, idxi -= sizeof(unsigned int)) {
    for (r = i, idxr = idxi; r * 2 + size < n; r = c, idxr = idxc) {
      c = r * 2 + size;
      idxc = idxr * 2 + sizeof(unsigned int);
      if (c < n - size && cmp (base + c, base + c + size) < 0) {
        c += size;
        idxc += sizeof(unsigned int);
      }
      if (cmp (base + r, base + c) >= 0)
        break;
      swap (base + r, base + c, size);
      generic_swap (idx + idxr, idx + idxc, sizeof(unsigned int));
    }
  }

  /* sort */
  for (i = n - size, idxi = idxn - sizeof(unsigned int); i > 0;
       i -= size, idxi -= sizeof(unsigned int)) {
    swap (base, base + i, size);
    generic_swap (idx, idx + idxi, sizeof(unsigned int));
    for (r = 0, idxr = 0; r * 2 + size < i; r = c, idxr = idxc) {
      c = r * 2 + size;
      idxc = idxr * 2 + sizeof(unsigned int);
      if (c < i - size && cmp (base + c, base + c + size) < 0) {
        c += size;
        idxc += sizeof(unsigned int);
      }
      if (cmp (base + r, base + c) >= 0)
        break;
      swap (base + r, base + c, size);
      generic_swap (idx + idxr, idx + idxc, sizeof(unsigned int));
    }
  }
}
