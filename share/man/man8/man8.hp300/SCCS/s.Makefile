h35039
s 00000/00000/00015
d D 8.1 93/06/05 13:56:37 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00014
d D 5.2 91/03/22 14:12:04 bostic 2 1
c add MAKEDEV
e
s 00015/00000/00000
d D 5.1 90/06/29 20:16:17 bostic 1 0
c date and time created 90/06/29 20:16:17 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
MAN8=	crash.0 format.0 rbootd.0
E 2
I 2
MAN8=	MAKEDEV.0 crash.0 format.0
E 2
MANSUBDIR=/hp300

all: ${MAN8}

clean depend lint tags:

cleandir:
	rm -f ${MAN8}

install: maninstall

.include <bsd.prog.mk>
E 1
