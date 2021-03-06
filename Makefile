TARGETS 	= test_list.out test_rbtree.out hello_world.out \
		  test_int_stack.out test_int_set.out test_int_queue.out \
		  test_sort.out libpank7.a
OBJECTS		= rbtree.o test_list.o test_rbtree.o int_stack.o \
		  int_set.o int_queue.o test_int_stack.o test_int_queue.o \
		  test_int_set.o sort.o

CC		= clang
#CFLAGS		= -Wall -O3 -c
CFLAGS		= -Wall -g -c
OFLAGS		= -L.
AR		= ar
RANLIB		= ranlib
AWK		= gawk

.PHONY: all clean tags

%.o: %.c
	${CC} ${CFLAGS} $^ -o $@

all: ${TARGETS}

clean:
	rm -rf ${TARGETS} ${OBJECTS} *.o

tags:
	ctags -R

libpank7.a: sort.o rbtree.o int_stack.o int_queue.o int_set.o
	${AR} rvS $@ $^
	${RANLIB} $@

hello_world.out: hello_world.o
	${CC} ${OFLAGS} $^ -o $@

test_list.out: test_list.o
	${CC} ${OFLAGS} $^ -o $@

run_test_list: test_list.out
	${AWK} 'BEGIN{srand(systime()); for (i = 0; i < 5; ++i) print int(1000 * rand())}' | ./$^

test_int_stack.out: test_int_stack.o libpank7.a
	${CC} ${OFLAGS} test_int_stack.o -o $@ -lpank7

test_int_queue.out: test_int_queue.o libpank7.a
	${CC} ${OFLAGS} test_int_queue.o -o $@ -lpank7

test_rbtree.out: test_rbtree.o libpank7.a
	${CC} ${OFLAGS} test_rbtree.o -o $@ -lpank7

test_int_set.out: test_int_set.o libpank7.a
	${CC} ${OFLAGS} test_int_set.o -o $@ -lpank7

test_sort.out: test_sort.o libpank7.a
	${CC} ${OFLAGS} test_sort.o -o $@ -lpank7
