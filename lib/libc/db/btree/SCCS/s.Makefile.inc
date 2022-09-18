h16136
s 00000/00000/00007
d D 8.1 93/06/04 15:21:08 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00005
d D 5.5 92/10/09 16:25:30 bostic 5 4
c add bt_page.c
e
s 00003/00004/00004
d D 5.4 91/09/04 12:47:05 bostic 4 3
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00001/00001/00007
d D 5.3 91/02/12 20:21:00 bostic 3 2
c fix path
e
s 00002/00001/00006
d D 5.2 91/01/23 08:10:55 mao 2 1
c split up modules into smaller files
e
s 00007/00000/00000
d D 5.1 91/01/08 17:04:59 bostic 1 0
c date and time created 91/01/08 17:04:59 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 4
# btree sources

E 4
D 3
.PATH: ${.CURDIR}/btree
E 3
I 3
.PATH: ${.CURDIR}/db/btree
E 3

D 2
SRCS+=	btree.c lrucache.c
E 2
I 2
D 4
SRCS+=	big.c btree.c delete.c insert.c lrucache.c lruhash.c lrutils.c \
	search.c seq.c split.c storage.c updutils.c utils.c
E 4
I 4
SRCS+=	bt_close.c bt_conv.c bt_debug.c bt_delete.c bt_get.c bt_open.c \
D 5
	bt_overflow.c bt_put.c bt_search.c bt_seq.c bt_split.c bt_stack.c \
	bt_utils.c
E 5
I 5
	bt_overflow.c bt_page.c bt_put.c bt_search.c bt_seq.c bt_split.c \
	bt_stack.c bt_utils.c
E 5
E 4
E 2
E 1
