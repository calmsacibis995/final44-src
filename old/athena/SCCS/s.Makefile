h45407
s 00003/00002/00028
d D 5.2 89/05/11 14:35:19 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00030/00000/00000
d D 5.1 89/02/03 22:02:33 kfall 1 0
c date and time created 89/02/03 22:02:33 by kfall
e
u
U
t
T
I 1
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
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
#
#	%W% (Berkeley) %G%
#
DESTDIR=

SUBDIR=	kdestroy kinit klist ksrvtgt ksu

all clean cleandir depend install lint tags: FRC
D 2
	-for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 2
I 2
	@-for i in ${SUBDIR}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done
E 2

${SUBDIR}: FRC
	cd $@; make ${MFLAGS} DESTDIR=${DESTDIR}

FRC:
E 1
