h39833
s 00016/00000/00000
d D 5.1 91/04/22 13:34:05 bostic 1 0
c date and time created 91/04/22 13:34:05 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

SRCS=	lrucache.h btree.h big.c btree.c delete.c insert.c lrucache.c \
	lruhash.c lrutils.c search.c seq.c split.c storage.c \
	updutils.c utils.c

OBJS=	big.o btree.o delete.o insert.o lrucache.o \
	lruhash.o lrutils.o search.o seq.o split.o storage.o \
	updutils.o utils.o

#CFLAGS=	-O
CFLAGS=	-g

libbtree.a: $(OBJS)
	ar ru libbtree.a $(OBJS)
	ranlib libbtree.a
E 1
