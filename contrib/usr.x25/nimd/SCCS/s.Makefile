h60203
s 00007/00023/00002
d D 5.2 93/05/28 13:01:46 bostic 2 1
c new style Makefile
e
s 00025/00000/00000
d D 5.1 93/05/28 13:01:14 bostic 1 0
c date and time created 93/05/28 13:01:14 by bostic
e
u
U
t
T
I 1
D 2
CFLAGS=-DCCITT -c -O
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
nimd:	nim.o ../lib/x25lib.a buf.o commands.o x29.o
	cc nim.o buf.o commands.o x29.o ../lib/x25lib.a -o nimd
E 2
I 2
PROG=	nimd
MAN8=	nimd.0
SRCS=	buf.c commands.c nim.c x29.c
LDADD=	-lx25
CFLAGS= -DCCITT
E 2

D 2
install: nimd
	install -c -m 740 -s nimd /etc/nimd

nim.o:	nim.c buf.h nim.h
	cc ${CFLAGS} nim.c

buf.o:	buf.c buf.h
	cc ${CFLAGS} buf.c

commands.o: commands.c nim.h
	cc ${CFLAGS} commands.c

x29.o:	x29.c nim.h
	cc ${CFLAGS} x29.c

lint:	/tmp
	lint -hbaxu -DCCITT nim.c buf.c x29.c commands.c

clean:
	rm -f core *.o *.CKP .emacs*
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
