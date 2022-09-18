h41891
s 00001/00001/00013
d D 8.2 94/02/16 17:59:10 bostic 3 2
c Add a cgsix man page; From: Craig Leres <leres@ee.lbl.gov>
e
s 00000/00000/00014
d D 8.1 93/06/05 13:41:00 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00000/00000
d D 5.1 93/02/17 06:36:26 torek 1 0
c date and time created 93/02/17 06:36:26 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
MAN4=	bwtwo.0 cgthree.0 le.0 mem.0 openprom.0
E 3
I 3
MAN4=	bwtwo.0 cgsix.0 cgthree.0 le.0 mem.0 openprom.0
E 3
MLINKS=	mem.4 kmem.4
MANSUBDIR=/sparc

all: ${MAN4}

clean depend lint tags:

cleandir:
	rm -f ${MAN4}

.include <bsd.prog.mk>
E 1
