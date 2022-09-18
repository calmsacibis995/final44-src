h28476
s 00000/00000/00005
d D 8.1 93/06/05 13:03:57 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00004
d D 5.10 92/07/25 11:00:01 bostic 11 10
c add me back in
e
s 00001/00001/00004
d D 5.9 92/07/18 05:26:04 cael 10 8
c added me dir
e
s 00003/00001/00004
d D 5.8.1.1 91/05/07 22:04:56 bostic 9 8
c branch for the 2nd network distribution
e
s 00001/00001/00004
d D 5.8 90/06/30 15:15:53 bostic 8 7
c add doc subdirectory
e
s 00001/00001/00004
d D 5.7 90/06/29 16:45:59 bostic 7 6
c don't install copyright
e
s 00001/00001/00004
d D 5.6 90/06/19 17:41:32 bostic 6 5
c add dict
e
s 00001/00001/00004
d D 5.5 90/06/01 18:10:02 bostic 5 4
c add copyright
e
s 00001/00002/00004
d D 5.4 90/06/01 10:32:48 bostic 4 3
c add mk
e
s 00003/00027/00003
d D 5.3 90/05/11 13:55:54 bostic 3 2
c first pass for new make
e
s 00001/00001/00029
d D 5.2 90/03/24 10:07:15 bostic 2 1
c checkpoing for pmake
e
s 00030/00000/00000
d D 5.1 89/05/28 15:24:55 bostic 1 0
c date and time created 89/05/28 15:24:55 by bostic
e
u
U
f b 
t
T
I 1
D 3
#
# Copyright (c) 1989 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
E 3

D 2
SUBDIR=	man me ms skel termcap zic
E 2
I 2
D 3
SUBDIR=	man me ms skel termcap zoneinfo
E 3
I 3
D 4
# zoneinfo needs conversion
SUBDIR=	man me misc ms skel tabset termcap tmac zoneinfo
E 4
I 4
D 5
SUBDIR=	man me misc mk ms skel tabset termcap tmac zoneinfo
E 5
I 5
D 6
SUBDIR=	copyright man me misc mk ms skel tabset termcap tmac zoneinfo
E 6
I 6
D 7
SUBDIR=	copyright dict man me misc mk ms skel tabset termcap tmac zoneinfo
E 7
I 7
D 8
SUBDIR=	dict man me misc mk ms skel tabset termcap tmac zoneinfo
E 8
I 8
D 9
D 10
SUBDIR=	dict doc man me misc mk ms skel tabset termcap tmac zoneinfo
E 10
I 10
D 11
SUBDIR=	dict doc man misc mk skel tabset termcap tmac zoneinfo
E 11
I 11
SUBDIR=	dict doc man me misc mk skel tabset termcap tmac zoneinfo
E 11
E 10
E 9
I 9
# Missing:  ms

SUBDIR=	dict doc man me misc mk skel tabset termcap tmac zoneinfo
E 9
E 8
E 7
E 6
E 5
E 4
E 3
E 2

D 3
all clean cleandir depend install lint tags: FRC
	@-for i in ${SUBDIR}; do \
		(echo "==> $$i"; \
		    cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} $@); done

${SUBDIR}: FRC
	cd $@; make ${MFLAGS} DESTDIR=${DESTDIR}

FRC:
E 3
I 3
.include <bsd.subdir.mk>
E 3
E 1
