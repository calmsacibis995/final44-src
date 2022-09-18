h27453
s 00000/00000/00010
d D 8.1 93/06/04 17:41:31 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 90/06/05 09:42:58 bostic 1 0
c date and time created 90/06/05 09:42:58 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=resolv
CFLAGS+=-DDEBUG -DLIBC_SCCS

.PATH:	${.CURDIR}/../libc/net

SRCS=gethostnamadr.c res_mkquery.c res_query.c res_send.c

.include <bsd.lib.mk>
E 1
