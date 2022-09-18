h29712
s 00000/00000/00010
d D 8.1 93/06/11 15:28:57 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 91/05/03 18:31:37 bostic 1 0
c date and time created 91/05/03 18:31:37 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	ftp
SRCS=	cmds.c cmdtab.c ftp.c glob.c main.c ruserpass.c domacro.c
CFLAGS+=-DLETS_GET_SMALL
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../usr.bin/ftp

.include <bsd.prog.mk>
E 1
