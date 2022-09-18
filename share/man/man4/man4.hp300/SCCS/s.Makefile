h48583
s 00000/00000/00015
d D 8.1 93/06/18 00:01:32 mckusick 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00014
d D 5.2 93/06/18 00:01:18 mckusick 3 1
c delete rmp.4
e
s 00000/00000/00015
d R 8.1 93/06/05 13:42:33 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00000/00000
d D 5.1 90/06/29 19:05:17 bostic 1 0
c date and time created 90/06/29 19:05:17 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

MAN4=	autoconf.0 cons.0 ct.0 dca.0 dcl.0 dcm.0 dv.0 gb.0 grf.0 hil.0 \
D 3
	intro.0 ite.0 le.0 mem.0 ppi.0 rb.0 rd.0 rmp.0 tc.0
E 3
I 3
	intro.0 ite.0 le.0 mem.0 ppi.0 rb.0 rd.0 tc.0
E 3
MLINKS=	mem.4 kmem.4
MANSUBDIR=/hp300

all: ${MAN4}

clean depend lint tags:

cleandir:
	rm -f ${MAN4}

.include <bsd.prog.mk>
E 1
