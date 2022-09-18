h24316
s 00017/00000/00000
d D 5.1 90/05/11 12:10:17 bostic 1 0
c date and time created 90/05/11 12:10:17 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

.if exists(${.CURDIR}/../Makefile.inc)
.include "${.CURDIR}/../Makefile.inc"
.endif

BINGRP?=	bin
BINOWN?=	bin
BINMODE?=	555

STRIP?=		-s

MANGRP?=	bin
MANOWN?=	bin
MANMODE?=	444

MANDIR?=	/usr/share/man/cat
E 1
