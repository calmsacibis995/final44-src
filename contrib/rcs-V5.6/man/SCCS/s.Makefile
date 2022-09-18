h52908
s 00032/00012/00009
d D 5.2 93/05/26 11:48:52 bostic 2 1
c install in /usr/contrib, formatted
e
s 00021/00000/00000
d D 5.1 93/05/26 11:42:05 bostic 1 0
c date and time created 93/05/26 11:42:05 by bostic
e
u
U
t
T
I 1
# Make RCS man pages.

#	$Id: Makefile,v 5.2 1991/08/19 03:13:55 eggert Exp $

D 2
MANDIR = /usr/man
E 2
I 2
MANDIR = /usr/contrib/man
E 2

install = install -c -m 444

all clean ::

D 2
install ::
	${install} ci.1 ${DESTDIR}${MANDIR}/man1
	${install} co.1 ${DESTDIR}${MANDIR}/man1
	${install} ident.1 ${DESTDIR}${MANDIR}/man1
	${install} merge.1 ${DESTDIR}${MANDIR}/man1
	${install} rcs.1 ${DESTDIR}${MANDIR}/man1
	${install} rcsdiff.1 ${DESTDIR}${MANDIR}/man1
	${install} rcsintro.1 ${DESTDIR}${MANDIR}/man1
	${install} rcsmerge.1 ${DESTDIR}${MANDIR}/man1
	${install} rlog.1 ${DESTDIR}${MANDIR}/man1
	${install} rcsfile.5 ${DESTDIR}${MANDIR}/man5
E 2
I 2
install :: 
	nroff -man ci.1 > ${DESTDIR}${MANDIR}/cat1/ci.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/ci.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/ci.0
	nroff -man co.1 > ${DESTDIR}${MANDIR}/cat1/co.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/co.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/co.0
	nroff -man ident.1 > ${DESTDIR}${MANDIR}/cat1/ident.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/ident.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/ident.0
	nroff -man merge.1 > ${DESTDIR}${MANDIR}/cat1/merge.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/merge.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/merge.0
	nroff -man rcs.1 > ${DESTDIR}${MANDIR}/cat1/rcs.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/rcs.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/rcs.0
	nroff -man rcsdiff.1 > ${DESTDIR}${MANDIR}/cat1/rcsdiff.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/rcsdiff.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/rcsdiff.0
	nroff -man rcsintro.1 > ${DESTDIR}${MANDIR}/cat1/rcsintro.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/rcsintro.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/rcsintro.0
	nroff -man rcsmerge.1 > ${DESTDIR}${MANDIR}/cat1/rcsmerge.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/rcsmerge.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/rcsmerge.0
	nroff -man rlog.1 > ${DESTDIR}${MANDIR}/cat1/rlog.0
	chmod 444 ${DESTDIR}${MANDIR}/cat1/rlog.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat1/rlog.0
	nroff -man rcsfile.5 > ${DESTDIR}${MANDIR}/cat5/rcsfile.0
	chmod 444 ${DESTDIR}${MANDIR}/cat5/rcsfile.0
	chown bin.bin ${DESTDIR}${MANDIR}/cat5/rcsfile.0
E 2
E 1
