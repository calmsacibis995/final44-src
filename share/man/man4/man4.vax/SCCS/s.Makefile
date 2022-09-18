h46745
s 00000/00000/00020
d D 8.1 93/06/05 13:49:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00024/00009
d D 5.4 90/05/11 13:56:29 bostic 4 3
c first pass for new make
e
s 00007/00021/00026
d D 5.3 89/03/06 11:02:13 bostic 3 2
c move man pages into source tree
e
s 00010/00005/00037
d D 5.2 88/07/09 11:38:54 bostic 2 1
c install approved copyright notice
e
s 00042/00000/00000
d D 5.1 87/12/12 18:18:52 bostic 1 0
c date and time created 87/12/12 18:18:52 by bostic
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 3
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
E 2
#
E 4
#	%W% (Berkeley) %G%
D 4
#
D 3
MDIR=	/usr/man/cat4/vax
SRCS=	acc.4 ad.4 autoconf.4 cons.4 crl.4 css.4 ct.4 ddn.4 de.4 dh.4 dhu.4 \
	dmc.4 dmf.4 dmz.4 dn.4 dz.4 ec.4 en.4 ex.4 fl.4 hdh.4 hk.4 hp.4 \
	ht.4 hy.4 ik.4 il.4 intro.4 ix.4 kg.4 lp.4 mem.4 mt.4 mtio.4 np.4 \
	pcl.4 ps.4 qe.4 rx.4 tb.4 tm.4 tmscp.4 ts.4 tu.4 uda.4 up.4 ut.4 \
	uu.4 va.4 vp.4 vv.4
E 3
I 3
MDIR=	${DESTDIR}/usr/man/cat4/vax
E 3
OBJS=	acc.0 ad.0 autoconf.0 cons.0 crl.0 css.0 ct.0 ddn.0 de.0 dh.0 dhu.0 \
E 4
I 4

MAN4=	acc.0 ad.0 autoconf.0 cons.0 crl.0 css.0 ct.0 ddn.0 de.0 dh.0 dhu.0 \
E 4
	dmc.0 dmf.0 dmz.0 dn.0 dz.0 ec.0 en.0 ex.0 fl.0 hdh.0 hk.0 hp.0 \
	ht.0 hy.0 ik.0 il.0 intro.0 ix.0 kg.0 lp.0 mem.0 mt.0 mtio.0 np.0 \
	pcl.0 ps.0 qe.0 rx.0 tb.0 tm.0 tmscp.0 ts.0 tu.0 uda.0 up.0 ut.0 \
	uu.0 va.0 vp.0 vv.0
I 4
MLINKS=	mem.4 kmem.4
MANSUBDIR=/vax
E 4
D 3
LINKS=	kmem.0
E 3

D 3
.SUFFIXES: .4 .0
E 3
I 3
D 4
all clean depend lint tags:
E 4
I 4
all: ${MAN4}
E 4
E 3

I 4
clean depend lint tags:

E 4
D 3
.4.0:
	${DESTDIR}/usr/man/manroff $*.4 > $*.0

all: ${OBJS}

clean: FRC
E 3
I 3
cleandir:
E 3
D 4
	rm -f ${OBJS}
E 4
I 4
	rm -f ${MAN4}
E 4

D 3
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/mem.0 ${DESTDIR}${MDIR}/kmem.0

FRC:
E 3
I 3
D 4
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/kmem.0; ln ${MDIR}/mem.0 ${MDIR}/kmem.0
E 4
I 4
install: maninstall

.include <bsd.prog.mk>
E 4
E 3
E 1
