h04764
s 00002/00030/00003
d D 5.7 90/05/11 12:42:43 bostic 7 6
c first pass for new make
e
s 00001/00001/00032
d D 5.6 89/05/08 12:52:59 bostic 6 5
c file system reorg
e
s 00002/00009/00031
d D 5.5 89/01/16 21:14:01 bostic 5 4
c new version from Chris Torek
e
s 00013/00011/00027
d D 5.4 88/10/25 16:37:12 bostic 4 3
c cleanup, add manual page
e
s 00010/00005/00028
d D 5.3 88/07/09 11:22:56 bostic 3 2
c install approved copyright notice
e
s 00010/00007/00023
d D 5.2 88/03/30 16:12:16 bostic 2 1
c clean up scripts; clean out /usr/lib/adb
e
s 00030/00000/00000
d D 5.1 88/03/30 14:27:35 bostic 1 0
c date and time created 88/03/30 14:27:35 by bostic
e
u
U
t
T
I 1
D 7
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 3
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 3
I 3
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
#
E 7
#	%W% (Berkeley) %G%
D 7
#
D 2
DESTDIR= 
E 2
I 2
D 4
SUBDIR=	scripts scripts.${MACHINE} adb.${MACHINE}
E 4
I 4
D 5
MAN=	adb.0
E 4
E 2

D 4
all: FRC
D 2
	cd adb.${MACHINE}; make ${MFLAGS}
E 2
I 2
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS}); done
E 4
I 4
all depend clean lint tags: FRC
E 5
I 5
all depend clean cleandir lint tags: FRC
E 5
	cd adb.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
E 7
E 4
E 2

D 4
depend: FRC
D 2
	cd adb.${MACHINE}; make ${MFLAGS} depend
E 2
I 2
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} depend); done
E 4
I 4
D 5
cleandir: clean
	rm -f ${MAN} tags .depend
	cd adb.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
E 4
E 2

E 5
I 2
D 6
SCRIPTDIR=	/usr/lib/adb
E 6
I 6
D 7
SCRIPTDIR=	/usr/libdata/adb
E 7
I 7
SUBDIR=	adb common_scripts scripts
E 7
E 6
E 2
D 4
install: FRC
D 2
	cd adb.${MACHINE}; make DESTDIR=${DESTDIR} install
	cd scripts; make DESTDIR=${DESTDIR} install
	cd scripts.${MACHINE}; make DESTDIR=${DESTDIR} install
E 2
I 2
	rm -rf ${SCRIPTDIR}
E 4
I 4

D 5
install: ${MAN}
E 5
I 5
D 7
install:
E 5
	rm -rf ${DESTDIR}/${SCRIPTDIR}
E 4
	mkdir ${DESTDIR}/${SCRIPTDIR}
	chown bin.bin ${DESTDIR}/${SCRIPTDIR}
	chmod 755 ${DESTDIR}/${SCRIPTDIR}
D 4
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} install); done
E 2

clean: FRC
D 2
	cd adb.${MACHINE}; make ${MFLAGS} clean
E 2
I 2
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done
E 4
I 4
	cd adb.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
	cd scripts; make ${MFLAGS} DESTDIR=${DESTDIR} $@
	cd scripts.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
D 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 5
E 4
E 2

FRC:
E 7
I 7
.include <bsd.subdir.mk>
E 7
E 1
