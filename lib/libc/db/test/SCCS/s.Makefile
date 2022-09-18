h34952
s 00005/00002/00012
d D 8.9 94/02/21 17:41:42 bostic 13 12
c add strerror.c for portability
c set -D__DBINTERFACE_PRIVATE so it will compile elsewhere
e
s 00001/00001/00013
d D 8.8 94/02/21 17:24:14 bostic 12 11
c add INC macro, so user's can point a -I flag
e
s 00002/00009/00012
d D 8.7 94/01/02 12:12:15 bostic 11 10
c integrate latest version into 4.4BSD-Lite
e
s 00005/00002/00016
d D 8.6 93/12/19 13:14:31 bostic 10 9
c checkpoint for 1.73, 
e
s 00001/00001/00017
d D 8.5 93/09/07 13:23:17 bostic 9 8
c need PORT directory, too, to pick up <sys/XXX.h>
e
s 00011/00005/00007
d D 8.4 93/09/07 11:46:23 bostic 8 7
c add in recno as an example of local compilation of an access method
e
s 00003/00000/00009
d D 8.3 93/09/06 11:38:59 bostic 7 6
c add a make clean
e
s 00005/00017/00004
d D 8.2 93/09/06 11:38:25 bostic 6 5
c put in an old-style Makefile
e
s 00000/00000/00021
d D 8.1 93/06/04 15:31:46 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00000/00017
d D 5.4 93/01/11 22:16:27 bostic 4 3
c add hash SRCS
e
s 00002/00001/00015
d D 5.3 93/01/10 13:06:05 bostic 3 2
c add -DSTATISTICS
e
s 00002/00002/00014
d D 5.2 92/11/13 17:11:13 bostic 2 1
c use obj
e
s 00016/00000/00000
d D 5.1 92/08/26 12:59:22 bostic 1 0
c date and time created 92/08/26 12:59:22 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	dbtest
D 6
SRCS=	dbtest.c
#SRCS+=	rec_close.c rec_delete.c rec_get.c rec_open.c rec_put.c \
#	rec_search.c rec_seq.c rec_utils.c
D 2
#.PATH:	../recno
E 2
I 2
#.PATH:	${.CURDIR}/../recno
E 2
#SRCS+=	bt_close.c bt_conv.c bt_debug.c bt_delete.c bt_get.c bt_open.c \
#	bt_overflow.c bt_put.c bt_search.c bt_seq.c bt_split.c bt_stack.c \
#	bt_utils.c
D 2
#.PATH:	../btree
E 2
I 2
#.PATH:	${.CURDIR}/../btree
I 4
#SRCS+=	hash.c hash_bigkey.c hash_buf.c hash_func.c hash_log2.c \
#	hash_page.c hsearch.c ndbm.c
#.PATH:	${.CURDIR}/../hash
E 4
E 2
D 3
CFLAGS=	-g -DDEBUG
E 3
I 3
#LDADD=	/usr/src/lib/libc/obj/libc.a
E 6
I 6
D 8
OBJS=	dbtest.o #strerror.o
CFLAGS=	-O -DDEBUG -DSTATISTICS
LIB=	../PORT/bsd.44/libdb.a
E 8
I 8
D 11
OBJS1=	dbtest.o #strerror.o
#OBJS2=	rec_close.o rec_delete.o rec_get.o rec_open.o rec_put.o \
#	rec_search.o rec_seq.o rec_utils.o
#VPATH=	../recno
OBJS=	${OBJS1} ${OBJS2} ${OBJS3}
E 11
I 11
D 13
OBJS=	dbtest.o
E 13
I 13
OBJS=	dbtest.o strerror.o
E 13
E 11
E 8
E 6
I 4

I 8
D 11
PDIR=	../PORT/bsd.44
D 9
CFLAGS=	-O -DDEBUG -DSTATISTICS -I${PDIR}/include #-I../recno
E 9
I 9
D 10
CFLAGS=	-O -DDEBUG -DSTATISTICS -I${PDIR}/include -I${PDIR} #-I../recno
E 10
I 10

E 11
# Add -DSTATISTICS to CFLAGS to get btree statistical use info.
# Note, the db library has to be compiled for statistics as well.
D 11
CFLAGS=	-O -DDEBUG -I${PDIR}/include -I${PDIR} #-I../recno
E 10
E 9
LIB=	${PDIR}/libdb.a
E 11
I 11
D 12
CFLAGS=	-O -DDEBUG
E 12
I 12
D 13
CFLAGS=	-O -DDEBUG ${INC}
E 13
I 13
CFLAGS=	-D__DBINTERFACE_PRIVATE -DDEBUG -O ${INC}
E 13
E 12
E 11

E 8
E 4
D 6
CFLAGS=	-g -DDEBUG -DSTATISTICS
E 3
NOMAN=	noman

NOINCLUDE=1
.include <bsd.prog.mk>
E 6
I 6
dbtest: ${OBJS} ${LIB}
D 8
	${CC} -o $@ ${OBJS} ${LIB}
E 8
I 8
D 10
	${CC} -o $@ ${OBJS} ${LIB} ${LIB}
E 10
I 10
	${CC} -o $@ ${OBJS} ${LIB}
I 13

strerror.o: ../PORT/clib/strerror.c
	${CC} -c ../PORT/clib/strerror.c
E 13
E 10
E 8
I 7

clean:
D 8
	rm -f ${OBJS} ${PROG} t1 t2 t3
E 8
I 8
	rm -f gmon.out ${OBJS} ${PROG} t1 t2 t3
E 8
E 7
E 6
E 1
