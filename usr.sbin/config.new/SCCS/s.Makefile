h59883
s 00001/00003/00011
d D 8.3 94/05/29 21:32:50 bostic 5 4
c man pages with .new in the don't work
e
s 00003/00001/00011
d D 8.2 94/04/19 17:02:34 mckusick 4 2
c manual page becomes config.new
e
s 00001/00001/00011
d R 8.2 94/04/19 16:52:54 mckusick 3 2
c man page changes names
e
s 00000/00000/00012
d D 8.1 93/06/06 13:55:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00000/00000
d D 5.1 93/01/12 02:18:03 torek 1 0
c date and time created 93/01/12 02:18:03 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	config
SRCS=	files.c gram.y hash.c main.c mkheaders.c mkioconf.c mkmakefile.c \
	mkswap.c pack.c scan.l sem.c util.c
CFLAGS+=-I${.CURDIR} -I.
CLEANFILES=gram.c scan.c y.tab.h
D 4
MAN8=	config.0
E 4
I 4
D 5
MAN8=	config.new.0

MLINKS+=config.new.0 config.0
E 5
I 5
MAN8=	config.0
E 5
E 4

.include <bsd.prog.mk>

.depend: gram.c scan.c
E 1
