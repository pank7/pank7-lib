/*
 * Description:                 Doubly linked list structure, copied from Linux
 *                              kernel source (version 2.6.20.1), Modified.
 *                              Header file.
 * File:                        list.h
 * Author:                      Li Yi <liyi@net.pku.edu.cn>
 * Date & Time:                 Tue Nov 13 12:49:25 2007
 *
 *  <list.h>
 *  Copyright (C) 2012 Li Yi (pAnk7.yArdbird) <liyi84 (AT) gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

#ifdef __cplusplus
extern "C" {
#endif
#if defined(WIN32) && !defined(__cplusplus)
#define inline
#endif

#define LIST_POISON1    ((void *) 0x00100100)
#define LIST_POISON2    ((void *) 0x00200200)
#ifndef NULL
#define NULL            ((void *)0)
#endif /* NULL */

#ifndef offsetof
#ifdef  __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
#endif /* offsetof */

#define container_of(ptr, type, member) ({                                     \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);                   \
        (type *)( (char *)__mptr - offsetof(type,member) );})

  /*
   * Simple doubly linked list implementation.
   *
   * Some of the internal functions ("__xxx") are useful when
   * manipulating whole lists rather than single entries, as
   * sometimes we already know the next/prev entries and we can
   * generate better code by using them directly rather than
   * using the generic single-entry routines.
   */

  typedef struct list_head {
    struct list_head *next, *prev;
  } list_head;

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name)                                                        \
        struct list_head name = LIST_HEAD_INIT(name)

  static inline void INIT_LIST_HEAD(struct list_head *list)
  {
    list->next = list;
    list->prev = list;
  }

  /*
   * Insert a newentry entry between two known consecutive entries.
   *
   * This is only for internal list manipulation where we know
   * the prev/next entries already!
   */
  static inline void __list_add(struct list_head *newentry,
                                struct list_head *prev,
                                struct list_head *next)
  {
    next->prev = newentry;
    newentry->next = next;
    newentry->prev = prev;
    prev->next = newentry;
  }

  /**
   * list_add - add a newentry entry
   * @newentry: newentry entry to be added
   * @head: list head to add it after
   *
   * Insert a newentry entry after the specified head.
   * This is good for implementing stacks.
   */
  static inline void list_add(struct list_head *newentry,
                              struct list_head *head)
  {
    __list_add(newentry, head, head->next);
  }

  /**
   * list_add_tail - add a newentry entry
   * @newentry: newentry entry to be added
   * @head: list head to add it before
   *
   * Insert a newentry entry before the specified head.
   * This is useful for implementing queues.
   */
  static inline void list_add_tail(struct list_head *newentry,
                                   struct list_head *head)
  {
    __list_add(newentry, head->prev, head);
  }

  /*
   * Delete a list entry by making the prev/next entries
   * point to each other.
   *
   * This is only for internal list manipulation where we know
   * the prev/next entries already!
   */
  static inline void __list_del(struct list_head * prev,
                                struct list_head * next)
  {
    next->prev = prev;
    prev->next = next;
  }

  /**
   * list_del - deletes entry from list.
   * @entry: the element to delete from the list.
   * Note: list_empty on entry does not return true after this, the entry is
   * in an undefined state.
   */
  static inline void list_del(struct list_head *entry)
  {
    __list_del(entry->prev, entry->next);
    entry->next = (list_head *)LIST_POISON1;
    entry->prev = (list_head *)LIST_POISON2;
  }

  /**
   * list_replace - replace old entry by newentry one
   * @old : the element to be replaced
   * @newentry : the newentry element to insert
   * Note: if 'old' was empty, it will be overwritten.
   */
  static inline void list_replace(struct list_head *old,
                                  struct list_head *newentry)
  {
    newentry->next = old->next;
    newentry->next->prev = newentry;
    newentry->prev = old->prev;
    newentry->prev->next = newentry;
  }

  static inline void list_replace_init(struct list_head *old,
                                       struct list_head *newentry)
  {
    list_replace(old, newentry);
    INIT_LIST_HEAD(old);
  }

  /**
   * list_del_init - deletes entry from list and reinitialize it.
   * @entry: the element to delete from the list.
   */
  static inline void list_del_init(struct list_head *entry)
  {
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
  }

  /**
   * list_move - delete from one list and add as another's head
   * @list: the entry to move
   * @head: the head that will precede our entry
   */
  static inline void list_move(struct list_head *list, struct list_head *head)
  {
    __list_del(list->prev, list->next);
    list_add(list, head);
  }

  /**
   * list_move_tail - delete from one list and add as another's tail
   * @list: the entry to move
   * @head: the head that will follow our entry
   */
  static inline void list_move_tail(struct list_head *list,
                                    struct list_head *head)
  {
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
  }

  /**
   * list_is_last - tests whether @list is the last entry in list @head
   * @list: the entry to test
   * @head: the head of the list
   */
  static inline int list_is_last(const struct list_head *list,
                                 const struct list_head *head)
  {
    return list->next == head;
  }

  /**
   * list_empty - tests whether a list is empty
   * @head: the list to test.
   */
  static inline int list_empty(const struct list_head *head)
  {
    return head->next == head;
  }

  /**
   * list_empty_careful - tests whether a list is empty and not being modified
   * @head: the list to test
   *
   * Description:
   * tests whether a list is empty _and_ checks that no other CPU might be
   * in the process of modifying either member (next or prev)
   *
   * NOTE: using list_empty_careful() without synchronization
   * can only be safe if the only activity that can happen
   * to the list entry is list_del_init(). Eg. it cannot be used
   * if another CPU could re-list_add() it.
   */
  static inline int list_empty_careful(const struct list_head *head)
  {
    struct list_head *next = head->next;
    return (next == head) && (next == head->prev);
  }

  static inline void __list_splice(struct list_head *list,
                                   struct list_head *head)
  {
    struct list_head *first = list->next;
    struct list_head *last = list->prev;
    struct list_head *at = head->next;

    first->prev = head;
    head->next = first;

    last->next = at;
    at->prev = last;
  }

  /**
   * list_splice - join two lists
   * @list: the newentry list to add.
   * @head: the place to add it in the first list.
   */
  static inline void list_splice(struct list_head *list,
                                 struct list_head *head)
  {
    if (!list_empty(list))
      __list_splice(list, head);
  }

  /**
   * list_splice_init - join two lists and reinitialise the emptied list.
   * @list: the newentry list to add.
   * @head: the place to add it in the first list.
   *
   * The list at @list is reinitialised
   */
  static inline void list_splice_init(struct list_head *list,
                                      struct list_head *head)
  {
    if (!list_empty(list)) {
      __list_splice(list, head);
      INIT_LIST_HEAD(list);
    }
  }

  /**
   * list_entry - get the struct for this entry
   * @ptr: the &struct list_head pointer.
   * @type: the type of the struct this is embedded in.
   * @member: the name of the list_struct within the struct.
   */
#define list_entry(ptr, type, member)                                          \
 container_of(ptr, type, member)

  /**
   * list_for_each - iterate over a list
   * @pos: the &struct list_head to use as a loop cursor.
   * @head: the head for your list.
   */
#define list_for_each(pos, head)                                               \
        for (pos = (head)->next; pos != (head); pos = pos->next)

  /**
   * __list_for_each - iterate over a list
   * @pos: the &struct list_head to use as a loop cursor.
   * @head: the head for your list.
   *
   * This variant differs from list_for_each() in that it's the
   * simplest possible list iteration code, no prefetching is done.
   * Use this for code that knows the list to be very short (empty
   * or 1 entry) most of the time.
   */
#define __list_for_each(pos, head)                                             \
        for (pos = (head)->next; pos != (head); pos = pos->next)

  /**
   * list_for_each_prev - iterate over a list backwards
   * @pos: the &struct list_head to use as a loop cursor.
   * @head: the head for your list.
   */
#define list_for_each_prev(pos, head)                                          \
        for (pos = (head)->prev; pos != (head); pos = pos->prev)

  /**
   * list_for_each_safe - iterate over a list safe against removal of list entry
   * @pos: the &struct list_head to use as a loop cursor.
   * @n:  another &struct list_head to use as temporary storage
   * @head: the head for your list.
   */
#define list_for_each_safe(pos, n, head)                                       \
        for (pos = (head)->next, n = pos->next; pos != (head);                 \
             pos = n, n = pos->next)

  /**
   * list_for_each_entry - iterate over list of given type
   * @pos: the type * to use as a loop cursor.
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   */
#define list_for_each_entry(pos, head, member)                                 \
        for (pos = list_entry((head)->next, typeof(*pos), member);             \
             &pos->member != (head);                                           \
             pos = list_entry(pos->member.next, typeof(*pos), member))

  /**
   * list_for_each_entry_reverse - iterate backwards over list of given type.
   * @pos: the type * to use as a loop cursor.
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   */
#define list_for_each_entry_reverse(pos, head, member)                         \
        for (pos = list_entry((head)->prev, typeof(*pos), member);             \
             &pos->member != (head);                                           \
             pos = list_entry(pos->member.prev, typeof(*pos), member))

  /**
   * list_prepare_entry - prepare a pos entry for use in
   * list_for_each_entry_continue
   * @pos: the type * to use as a start point
   * @head: the head of the list
   * @member: the name of the list_struct within the struct.
   *
   * Prepares a pos entry for use as a start point in
   * list_for_each_entry_continue.
   */
#define list_prepare_entry(pos, head, member)                                  \
        ((pos) ? : list_entry(head, typeof(*pos), member))

  /**
   * list_for_each_entry_continue - continue iteration over list of given type
   * @pos: the type * to use as a loop cursor.
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   *
   * Continue to iterate over list of given type, continuing after
   * the current position.
   */
#define list_for_each_entry_continue(pos, head, member)                        \
        for (pos = list_entry(pos->member.next, typeof(*pos), member);         \
             &pos->member != (head);                                           \
             pos = list_entry(pos->member.next, typeof(*pos), member))

  /**
   * list_for_each_entry_from - iterate over list of given type from the current
   * point
   * @pos: the type * to use as a loop cursor.
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   *
   * Iterate over list of given type, continuing from current position.
   */
#define list_for_each_entry_from(pos, head, member)                            \
        for (; &pos->member != (head);                                         \
             pos = list_entry(pos->member.next, typeof(*pos), member))

  /**
   * list_for_each_entry_safe - iterate over list of given type safe against
   * removal of list entry
   * @pos: the type * to use as a loop cursor.
   * @n:  another type * to use as temporary storage
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   */
#define list_for_each_entry_safe(pos, n, head, member)                         \
        for (pos = list_entry((head)->next, typeof(*pos), member),             \
             n = list_entry(pos->member.next, typeof(*pos), member);           \
             &pos->member != (head);                                           \
             pos = n, n = list_entry(n->member.next, typeof(*n), member))

  /**
   * list_for_each_entry_safe_continue
   * @pos: the type * to use as a loop cursor.
   * @n:  another type * to use as temporary storage
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   *
   * Iterate over list of given type, continuing after current point,
   * safe against removal of list entry.
   */
#define list_for_each_entry_safe_continue(pos, n, head, member)                \
        for (pos = list_entry(pos->member.next, typeof(*pos), member),         \
             n = list_entry(pos->member.next, typeof(*pos), member);           \
             &pos->member != (head);                                           \
             pos = n, n = list_entry(n->member.next, typeof(*n), member))

  /**
   * list_for_each_entry_safe_from
   * @pos: the type * to use as a loop cursor.
   * @n:  another type * to use as temporary storage
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   *
   * Iterate over list of given type from current point, safe against
   * removal of list entry.
   */
#define list_for_each_entry_safe_from(pos, n, head, member)                    \
        for (n = list_entry(pos->member.next, typeof(*pos), member);           \
             &pos->member != (head);                                           \
             pos = n, n = list_entry(n->member.next, typeof(*n), member))

  /**
   * list_for_each_entry_safe_reverse
   * @pos: the type * to use as a loop cursor.
   * @n:  another type * to use as temporary storage
   * @head: the head for your list.
   * @member: the name of the list_struct within the struct.
   *
   * Iterate backwards over list of given type, safe against removal
   * of list entry.
   */
#define list_for_each_entry_safe_reverse(pos, n, head, member)                 \
        for (pos = list_entry((head)->prev, typeof(*pos), member),             \
             n = list_entry(pos->member.prev, typeof(*pos), member);           \
             &pos->member != (head);                                           \
             pos = n, n = list_entry(n->member.prev, typeof(*n), member))

  /*
   * Double linked lists with a single pointer list head.
   * Mostly useful for hash tables where the two pointer list head is
   * too wasteful.
   * You lose the ability to access the tail in O(1).
   */

  typedef struct hlist_head {
    struct hlist_node *first;
  } hlist_head;

  typedef struct hlist_node {
    struct hlist_node *next, **pprev;
  } hlist_node;

#define HLIST_HEAD_INIT { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = { .first = NULL }
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)

  static inline void INIT_HLIST_NODE(struct hlist_node *h)
  {
    h->next = NULL;
    h->pprev = NULL;
  }

  static inline int hlist_unhashed(const struct hlist_node *h)
  {
    return !h->pprev;
  }

  static inline int hlist_empty(const struct hlist_head *h)
  {
    return !h->first;
  }

  static inline void __hlist_del(struct hlist_node *n)
  {
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next)
      next->pprev = pprev;
  }

  static inline void hlist_del(struct hlist_node *n)
  {
    __hlist_del(n);
    n->next = (hlist_node *)LIST_POISON1;
    n->pprev = (hlist_node **)LIST_POISON2;
  }

  static inline void hlist_del_init(struct hlist_node *n)
  {
    if (!hlist_unhashed(n)) {
      __hlist_del(n);
      INIT_HLIST_NODE(n);
    }
  }

  static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
  {
    struct hlist_node *first = h->first;
    n->next = first;
    if (first)
      first->pprev = &n->next;
    h->first = n;
    n->pprev = &h->first;
  }

  /* next must be != NULL */
  static inline void hlist_add_before(struct hlist_node *n,
                                      struct hlist_node *next)
  {
    n->pprev = next->pprev;
    n->next = next;
    next->pprev = &n->next;
    *(n->pprev) = n;
  }

  static inline void hlist_add_after(struct hlist_node *n,
                                     struct hlist_node *next)
  {
    next->next = n->next;
    n->next = next;
    next->pprev = &n->next;

    if(next->next)
      next->next->pprev  = &next->next;
  }

#define hlist_entry(ptr, type, member) container_of(ptr,type,member)

#define hlist_for_each(pos, head)                                              \
        for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head)                                      \
        for (pos = (head)->first; pos && ({ n = pos->next; 1; });              \
             pos = n)

  /**
   * hlist_for_each_entry - iterate over list of given type
   * @tpos: the type * to use as a loop cursor.
   * @pos: the &struct hlist_node to use as a loop cursor.
   * @head: the head for your list.
   * @member: the name of the hlist_node within the struct.
   */
#define hlist_for_each_entry(tpos, pos, head, member)                          \
        for (pos = (head)->first;                                              \
             pos && ({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;});   \
             pos = pos->next)

  /**
   * hlist_for_each_entry_continue - iterate over a hlist continuing after
   * current point
   * @tpos: the type * to use as a loop cursor.
   * @pos: the &struct hlist_node to use as a loop cursor.
   * @member: the name of the hlist_node within the struct.
   */
#define hlist_for_each_entry_continue(tpos, pos, member)                       \
        for (pos = (pos)->next;                                                \
             pos && ({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;});   \
             pos = pos->next)

  /**
   * hlist_for_each_entry_from - iterate over a hlist continuing from current
   * point
   * @tpos: the type * to use as a loop cursor.
   * @pos: the &struct hlist_node to use as a loop cursor.
   * @member: the name of the hlist_node within the struct.
   */
#define hlist_for_each_entry_from(tpos, pos, member)                           \
        for (; pos && ({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \
             pos = pos->next)

  /**
   * hlist_for_each_entry_safe - iterate over list of given type safe against
   * removal of list entry
   * @tpos: the type * to use as a loop cursor.
   * @pos: the &struct hlist_node to use as a loop cursor.
   * @n:  another &struct hlist_node to use as temporary storage
   * @head: the head for your list.
   * @member: the name of the hlist_node within the struct.
   */
#define hlist_for_each_entry_safe(tpos, pos, n, head, member)                  \
        for (pos = (head)->first;                                              \
             pos && ({ n = pos->next; 1; }) &&                                 \
             ({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;});          \
             pos = n)

#ifdef __cplusplus
}
#endif

#endif /* _LINUX_LIST_H */
