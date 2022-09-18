h18850
s 00007/00003/00008
d D 8.3 94/03/27 11:43:23 bostic 6 5
c Jan-Simon Pendry's and my new mount code
e
s 00002/00000/00009
d D 8.2 94/01/12 14:38:30 pendry 5 4
c link with -lcompat to pick up "correct" regex functions
e
s 00000/00000/00009
d D 8.1 93/06/05 11:04:10 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00003/00007
d D 5.3 93/06/04 11:22:21 bostic 3 2
c needs -I/sys for the miscfs directory, put the man pages in
e
s 00000/00001/00010
d D 5.2 93/04/27 18:01:58 bostic 2 1
c daemon(3) now in the C library
e
s 00011/00000/00000
d D 5.1 92/07/13 15:47:59 pendry 1 0
c date and time created 92/07/13 15:47:59 by pendry
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
#CFLAGS+=	-g -DDEBUG
E 3
I 3
D 6
CFLAGS+=-I/sys
E 6
E 3
PROG=	mount_portal
D 6
PTAL=	pt_conf.c pt_exec.c pt_file.c pt_tcp.c
SRCS=	mount_portal.c conf.c activate.c ${PTAL}
E 6
I 6
SRCS=	mount_portal.c activate.c conf.c getmntopts.c pt_conf.c \
	pt_exec.c pt_file.c pt_tcp.c
E 6
D 3
NOMAN=	noman
#MAN8=	mount_portal.0
E 3
I 3
MAN8=	mount_portal.0
I 6

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I/sys -I${MOUNT}
.PATH:	${MOUNT}

E 6
I 5
DPADD=	$(LIBCOMPAT)
LDADD=	-lcompat
E 5
E 3
D 2
LDADD+=	-lutil
E 2

.include <bsd.prog.mk>
E 1
