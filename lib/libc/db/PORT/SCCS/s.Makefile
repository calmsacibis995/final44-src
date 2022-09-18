h21917
s 00002/00001/00102
d D 8.7 94/02/21 18:11:33 bostic 16 15
c delete the library before loading it
c move __DBINTERFACE_PRIVATE into the Makefile (Makefile.inc)
e
s 00003/00003/00100
d D 8.6 94/02/21 16:20:22 bostic 15 14
c move clean after the lib build line
e
s 00002/00001/00101
d D 8.5 94/02/21 15:35:05 bostic 14 13
c add OORG macro
e
s 00003/00003/00099
d D 8.4 94/02/21 15:33:04 bostic 13 12
c minor cleanup
e
s 00074/00014/00028
d D 8.3 93/09/06 10:58:53 bostic 12 11
c rework for separate architecture/os directories a la nvi
e
s 00000/00013/00042
d D 8.2 93/09/06 10:29:43 bostic 11 9
c move MISC information into the README
e
s 00000/00000/00055
d R 8.2 93/06/04 11:58:28 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00055
d D 8.1 93/06/02 00:23:40 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00054
d D 5.8 93/04/29 22:02:56 bostic 8 7
c memmove needs a -D define
e
s 00023/00005/00032
d D 5.7 93/04/29 21:54:37 bostic 7 6
c add memmove, realloc, snprintf
e
s 00001/00001/00036
d D 5.6 93/02/15 17:28:27 bostic 6 5
c typo on mktemp line
e
s 00014/00011/00023
d D 5.5 93/02/14 15:45:27 bostic 5 4
c update for Eric and sendmail
e
s 00006/00006/00028
d D 5.4 93/02/11 11:30:13 bostic 4 3
c typo
e
s 00007/00007/00027
d D 5.3 92/12/04 19:16:36 bostic 3 2
c minor cleanups
e
s 00002/00002/00032
d D 5.2 92/10/20 10:08:34 bostic 2 1
c add bt_page.c
e
s 00034/00000/00000
d D 5.1 92/02/18 11:58:49 bostic 1 0
c date and time created 92/02/18 11:58:49 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

I 5
LIBDB=	libdb.a
E 5
D 12
OBJ1=	bt_close.o bt_conv.o bt_debug.o bt_delete.o bt_get.o bt_open.o \
E 12
I 12
OBJ1=	hash.o hash_bigkey.o hash_buf.o hash_func.o hash_log2.o hash_page.o \
	hsearch.o ndbm.o
OBJ2=	bt_close.o bt_conv.o bt_debug.o bt_delete.o bt_get.o bt_open.o \
E 12
D 2
	bt_overflow.o bt_put.o bt_search.o bt_seq.o bt_split.o bt_stack.o \
	bt_utils.o
E 2
I 2
	bt_overflow.o bt_page.o bt_put.o bt_search.o bt_seq.o bt_split.o \
	bt_stack.o bt_utils.o
E 2
D 12
OBJ2=	db.o
OBJ3=	hash.o hash_bigkey.o hash_buf.o hash_func.o hash_log2.o hash_page.o \
	hsearch.o ndbm.o
E 12
I 12
OBJ3=	db.o
E 12
OBJ4=	mpool.o
OBJ5=	rec_close.o rec_delete.o rec_get.o rec_open.o rec_put.o rec_search.o \
	rec_seq.o rec_utils.o
D 5
# If you need compatibility routines
COMP=	bcopy.o mktemp.o
E 5

D 5
db.a: ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${COMP}
E 5
I 5
D 7
# If you need mktemp or mkstemp, add "mktemp.o" to the COMP list.
COMP=
E 7
I 7
D 11
# If you don't have memmove(3), add memmove.o to the MISC line.
#
# If you don't have mktemp(3) or mkstemp(3), add mktemp.o to the MISC line.
#
# If realloc(3) of a NULL pointer on your system isn't the same as
# a malloc(3) call, add realloc.o to the MISC line.
#
# If you don't have snprintf/vsnprintf(3), add snprintf.o to the MISC line.
# Note, this depends you your having vsprintf(3) -- if you don't, there's
# no workaround other than changing the source code to not use the snprintf
# calls.  If you have to make that change, check to see if your vsprintf
# returns a length or a char *; if it's the latter, set VSPRINTF_CHARSTAR
# in the include/compat.h file.
E 11
MISC=
E 7

I 13
D 15
clean:
	rm -f ${LIBDB} ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${MISC}

E 15
E 13
D 7
${LIBDB}: ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${COMP}
E 7
I 7
${LIBDB}: ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${MISC}
I 16
	rm -f $@
E 16
E 7
E 5
	ar cq $@ \
D 7
	    `lorder ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${COMP} | tsort`
E 7
I 7
	    `lorder ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${MISC} | tsort`
E 7
	ranlib $@
I 15

clean:
	rm -f ${LIBDB} ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${MISC}
E 15

D 12
${OBJ1}:
D 3
	${CC} -c -O -I../btree -I../include ../btree/$*.c
E 3
I 3
D 4
	${CC} -c -O -I. -I../btree -I../include ../btree/$*.c
E 4
I 4
D 5
	${CC} -c -O -I. -I../btree -I../include ../btree/*.c
E 5
I 5
	${CC} -c -O -I. -Iinclude -I../btree ../btree/*.c
E 5
E 4
E 3
${OBJ2}:
D 3
	${CC} -c -O -I../db -I../include ../db/$*.c
E 3
I 3
D 4
	${CC} -c -O -I. -I../db -I../include ../db/$*.c
E 4
I 4
D 5
	${CC} -c -O -I. -I../db -I../include ../db/*.c
E 5
I 5
	${CC} -c -O -I. -Iinclude -I../db ../db/*.c
E 5
E 4
E 3
${OBJ3}:
D 3
	${CC} -c -O -I../hash -I../include ../hash/$*.c
E 3
I 3
D 4
	${CC} -c -O -I. -I../hash -I../include ../hash/$*.c
E 4
I 4
D 5
	${CC} -c -O -I. -I../hash -I../include ../hash/*.c
E 5
I 5
	${CC} -c -O -I. -Iinclude -I../hash ../hash/*.c
E 5
E 4
E 3
${OBJ4}:
D 3
	${CC} -c -O -I../mpool -I../include ../mpool/$*.c
E 3
I 3
D 4
	${CC} -c -O -I. -I../mpool -I../include ../mpool/$*.c
E 4
I 4
D 5
	${CC} -c -O -I. -I../mpool -I../include ../mpool/*.c
E 5
I 5
	${CC} -c -O -I. -Iinclude -I../mpool ../mpool/*.c
E 5
E 4
E 3
${OBJ5}:
D 3
	${CC} -c -O -I../recno -I../include ../recno/$*.c
${COMP}:
	${CC} -c -O -I../port -I../include ../port/$*.c
E 3
I 3
D 4
	${CC} -c -O -I. -I../recno -I../include ../recno/$*.c
E 4
I 4
D 5
	${CC} -c -O -I. -I../recno -I../include ../recno/*.c
E 4
${COMP} X:
D 4
	${CC} -c -O -I. -I../port -I../include ../port/$*.c
E 4
I 4
	${CC} -c -O -I. -I../port -I../include ../port/*.c
E 5
I 5
	${CC} -c -O -I. -Iinclude -I../recno ../recno/*.c
E 12
I 12
D 14
CL=	${CC} -c -O -I. -Iinclude
E 14
I 14
OORG=	-O
D 16
CL=	${CC} -c ${OORG} -I. -Iinclude
E 16
I 16
CL=	${CC} -c -D__DBINTERFACE_PRIVATE ${OORG} -I. -Iinclude
E 16
E 14

hash.o: ../../hash/hash.c
	${CL} -I../../hash ../../hash/hash.c
hash_bigkey.o: ../../hash/hash_bigkey.c
	${CL} -I../../hash ../../hash/hash_bigkey.c
hash_buf.o: ../../hash/hash_buf.c
	${CL} -I../../hash ../../hash/hash_buf.c
hash_func.o: ../../hash/hash_func.c
	${CL} -I../../hash ../../hash/hash_func.c
hash_log2.o: ../../hash/hash_log2.c
	${CL} -I../../hash ../../hash/hash_log2.c
hash_page.o: ../../hash/hash_page.c
	${CL} -I../../hash ../../hash/hash_page.c
hsearch.o: ../../hash/hsearch.c
	${CL} -I../../hash ../../hash/hsearch.c
ndbm.o: ../../hash/ndbm.c
	${CL} -I../../hash ../../hash/ndbm.c

bt_close.o: ../../btree/bt_close.c
	${CL} -I../../btree ../../btree/bt_close.c
bt_conv.o: ../../btree/bt_conv.c
	${CL} -I../../btree ../../btree/bt_conv.c
bt_debug.o: ../../btree/bt_debug.c
	${CL} -I../../btree ../../btree/bt_debug.c
bt_delete.o: ../../btree/bt_delete.c
	${CL} -I../../btree ../../btree/bt_delete.c
bt_get.o: ../../btree/bt_get.c
	${CL} -I../../btree ../../btree/bt_get.c
bt_open.o: ../../btree/bt_open.c
	${CL} -I../../btree ../../btree/bt_open.c
bt_overflow.o: ../../btree/bt_overflow.c
	${CL} -I../../btree ../../btree/bt_overflow.c
bt_page.o: ../../btree/bt_page.c
	${CL} -I../../btree ../../btree/bt_page.c
bt_put.o: ../../btree/bt_put.c
	${CL} -I../../btree ../../btree/bt_put.c
bt_search.o: ../../btree/bt_search.c
	${CL} -I../../btree ../../btree/bt_search.c
bt_seq.o: ../../btree/bt_seq.c
	${CL} -I../../btree ../../btree/bt_seq.c
bt_split.o: ../../btree/bt_split.c
	${CL} -I../../btree ../../btree/bt_split.c
bt_stack.o: ../../btree/bt_stack.c
	${CL} -I../../btree ../../btree/bt_stack.c
bt_utils.o: ../../btree/bt_utils.c
	${CL} -I../../btree ../../btree/bt_utils.c

db.o: ../../db/db.c
	${CL} ../../db/db.c

mpool.o: ../../mpool/mpool.c
	${CL} -I../../mpool ../../mpool/mpool.c

rec_close.o: ../../recno/rec_close.c
	${CL} -I../../recno ../../recno/rec_close.c
rec_delete.o: ../../recno/rec_delete.c
	${CL} -I../../recno ../../recno/rec_delete.c
rec_get.o: ../../recno/rec_get.c
	${CL} -I../../recno ../../recno/rec_get.c
rec_open.o: ../../recno/rec_open.c
	${CL} -I../../recno ../../recno/rec_open.c
rec_put.o: ../../recno/rec_put.c
	${CL} -I../../recno ../../recno/rec_put.c
rec_search.o: ../../recno/rec_search.c
	${CL} -I../../recno ../../recno/rec_search.c
rec_seq.o: ../../recno/rec_seq.c
	${CL} -I../../recno ../../recno/rec_seq.c
rec_utils.o: ../../recno/rec_utils.c
	${CL} -I../../recno ../../recno/rec_utils.c
E 12
E 5
E 4
E 3

I 7
memmove.o:
D 8
	${CC} -c -O -I. -Iinclude clib/memmove.c
E 8
I 8
	${CC} -DMEMMOVE -c -O -I. -Iinclude clib/memmove.c
E 8
E 7
I 5
mktemp.o:
D 6
	${CC} -c -O -I. -Iinclude ../clib/mktemp.c
E 6
I 6
	${CC} -c -O -I. -Iinclude clib/mktemp.c
I 7
realloc.o:
	${CC} -c -O -I. -Iinclude clib/realloc.c
snprintf.o:
	${CC} -c -O -I. -Iinclude clib/snprintf.c
E 7
E 6
D 13

E 5
clean:
D 5
	rm -f db.a ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${COMP}
E 5
I 5
D 7
	rm -f ${LIBDB} ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${COMP}
E 7
I 7
	rm -f ${LIBDB} ${OBJ1} ${OBJ2} ${OBJ3} ${OBJ4} ${OBJ5} ${MISC}
E 13
E 7
E 5
E 1
