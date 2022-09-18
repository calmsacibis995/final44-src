h55503
s 00002/00002/00010
d D 5.4 91/11/14 09:44:08 bostic 4 3
c add lint
e
s 00003/00000/00009
d D 5.3 91/04/03 12:55:23 bostic 3 2
c install pcc.h from here
e
s 00004/00005/00005
d D 5.2 91/02/28 16:58:51 bostic 2 1
c add cc
e
s 00010/00000/00000
d D 5.1 90/06/17 16:06:28 bostic 1 0
c date and time created 90/06/17 16:06:28 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
.if   (${MACHINE} == "hp300")
.elif (${MACHINE} == "tahoe")
SUBDIR=	c2 ccom f1
.elif (${MACHINE} == "vax")
SUBDIR=	c2 ccom f1 sccom
E 2
I 2
.if	(${MACHINE} == "tahoe")
D 4
SUBDIR=	c2 cc ccom f1
E 4
I 4
SUBDIR=	c2 cc ccom f1 lint
E 4
.elif	(${MACHINE} == "vax")
D 4
SUBDIR=	c2 cc ccom f1 sccom
E 4
I 4
SUBDIR=	c2 cc ccom f1 lint sccom
E 4
E 2
.endif

I 3
afterinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 pcc.h /usr/include

E 3
.include <bsd.subdir.mk>
E 1
