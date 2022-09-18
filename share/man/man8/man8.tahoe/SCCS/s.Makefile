h26399
s 00000/00000/00015
d D 8.1 93/06/05 13:57:14 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00015/00000/00000
d D 5.1 91/03/22 14:14:57 bostic 1 0
c date and time created 91/03/22 14:14:57 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

MAN8=	MAKEDEV.0
MANSUBDIR=/tahoe

all: ${MAN8}

clean depend lint tags:

cleandir:
	rm -f ${MAN8}

install: maninstall

.include <bsd.prog.mk>
E 1
