h30663
s 00000/00000/00008
d D 8.1 93/06/01 23:07:19 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00007
d D 5.2 93/05/25 17:31:39 bostic 2 1
c don't build profiled KERBEROS libraries
e
s 00007/00000/00000
d D 5.1 90/06/25 11:36:49 bostic 1 0
c date and time created 90/06/25 11:36:49 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=	acl
CFLAGS+=-DDEBUG -DKERBEROS -I${.CURDIR}/../include
SRCS=	acl_files.c

I 2
NOPROFILE=
E 2
.include <bsd.lib.mk>
E 1
