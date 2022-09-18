h38439
s 00000/00000/00007
d D 8.1 93/06/04 15:22:41 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00006
d D 5.3 92/08/06 22:34:38 cael 3 2
c added db.3 link (which is referenced in nbdm man page)
e
s 00001/00001/00005
d D 5.2 91/09/12 11:52:06 bostic 2 1
c db.3 -> dbopen.3
e
s 00006/00000/00000
d D 5.1 91/09/04 14:33:20 bostic 1 0
c date and time created 91/09/04 14:33:20 by bostic
e
u
U
t
T
I 1
#       %W% (Berkeley) %G%

.PATH: ${.CURDIR}/db/man

# mpool.3
D 2
MAN3+=	btree.0 db.0 hash.0 recno.0
E 2
I 2
MAN3+=	btree.0 dbopen.0 hash.0 recno.0
I 3
MLINKS+= dbopen.3 db.3
E 3
E 2
E 1
