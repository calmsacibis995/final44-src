h03040
s 00002/00000/00008
d D 8.2 94/02/21 15:14:32 bostic 5 4
c move __DBINTERFACE_PRIVATE into the Makefile (Makefile.inc)
e
s 00000/00000/00008
d D 8.1 93/06/02 00:23:09 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00002/00005
d D 5.3 91/09/04 15:35:35 bostic 3 2
c add mpool
e
s 00003/00004/00004
d D 5.2 91/09/04 12:55:21 bostic 2 1
c new structure
e
s 00008/00000/00000
d D 5.1 91/02/24 15:16:07 bostic 1 0
c date and time created 91/02/24 15:16:07 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%
#
I 5
CFLAGS+=-D__DBINTERFACE_PRIVATE

E 5
D 2
.PATH: ${.CURDIR}/db

E 2
I 2
D 3
.include "${.CURDIR}/db/db/Makefile.inc"
E 3
E 2
.include "${.CURDIR}/db/btree/Makefile.inc"
I 3
.include "${.CURDIR}/db/db/Makefile.inc"
E 3
.include "${.CURDIR}/db/hash/Makefile.inc"
D 2

MAN3+=	db.0
E 2
I 2
D 3
.include "${.CURDIR}/db/recno/Makefile.inc"
E 3
.include "${.CURDIR}/db/man/Makefile.inc"
I 3
.include "${.CURDIR}/db/mpool/Makefile.inc"
.include "${.CURDIR}/db/recno/Makefile.inc"
E 3
E 2
E 1
