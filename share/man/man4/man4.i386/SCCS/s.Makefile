h27457
s 00000/00000/00016
d D 8.1 93/06/05 13:39:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00016/00000/00000
d D 5.1 91/02/12 22:49:26 bostic 1 0
c date and time created 91/02/12 22:49:26 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

MAN4=	mem.0
MLINKS=	mem.4 kmem.4
MANSUBDIR=/i386

all: ${MAN4}

clean depend lint tags:

cleandir:
	rm -f ${MAN4}

install: maninstall

.include <bsd.prog.mk>
E 1
