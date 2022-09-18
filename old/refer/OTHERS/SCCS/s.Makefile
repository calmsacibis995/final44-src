h37602
s 00005/00005/00014
d D 5.7 92/07/20 21:05:30 bostic 7 6
c install into /usr/old
e
s 00006/00006/00013
d D 5.6 91/11/14 16:09:27 cael 6 5
c commented out install of Ind* files for now
e
s 00002/00002/00017
d D 5.5 91/11/14 10:20:38 bostic 5 4
c look in /usr/old/libexec for mkey and inv
e
s 00000/00004/00019
d D 5.4 90/07/01 10:31:09 bostic 4 3
c don't need these targets
e
s 00002/00002/00021
d D 5.3 90/06/19 17:58:27 bostic 3 2
c install man page for roffbib
e
s 00005/00001/00018
d D 5.2 90/06/19 17:37:20 bostic 2 1
c install papers; do runinv stuff in the Makefile
e
s 00019/00000/00000
d D 5.1 90/05/11 14:25:54 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
MAN=	roffbib.0
E 3
I 3
MAN1=	roffbib.0
E 3

D 4
all OTHERS: ${MAN}

clean cleandir depend lint tags:

E 4
D 3
install:
E 3
I 3
beforeinstall:
E 3
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/indxbib.sh ${DESTDIR}${BINDIR}/indxbib
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/roffbib.sh ${DESTDIR}${BINDIR}/roffbib
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
D 6
	    ${.CURDIR}/tmac.bib ${DESTDIR}/usr/share/tmac
D 2
	sh ${.CURDIR}/runinv ${DESTDIR}/usr/share/dict/papers
E 2
I 2
	(cd ${.CURDIR}/../papers; \
	    install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    INDEX Rbstjissue Rv7man ${DESTDIR}/usr/share/dict/papers)
D 5
	-/usr/libexec/mkey /usr/share/dict/papers/R* | (cd /var/db; \
	    /usr/libexec/inv -v -h997 -n Ind; chmod 444 Ind*)
E 5
I 5
	-/usr/old/libexec/mkey /usr/share/dict/papers/R* | (cd /var/db; \
	    /usr/old/libexec/inv -v -h997 -n Ind; chmod 444 Ind*)
E 6
I 6
	    ${.CURDIR}/tmac.bib ${DESTDIR}/usr/old/lib/tmac
D 7
#	(cd ${.CURDIR}/../papers; \
#	    install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
#	    INDEX Rbstjissue Rv7man ${DESTDIR}/usr/old/dict/papers)
#	-/usr/old/libexec/mkey /usr/old/dict/papers/R* | (cd /var/db; \
#	    /usr/old/libexec/inv -v -h997 -n Ind; chmod 444 Ind*)
E 7
I 7
	(cd ${.CURDIR}/../papers; \
	    install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    INDEX Rbstjissue Rv7man ${DESTDIR}/usr/old/dict/papers)
	-(cd /usr/old/dict/papers && /usr/old/libexec/mkey R* | \
	    /usr/old/libexec/inv -v -h997 -n Ind; chmod 444 Ind*)
E 7
E 6
E 5
E 2

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
