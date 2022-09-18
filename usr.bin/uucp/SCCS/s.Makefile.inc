h46254
s 00000/00000/00021
d D 8.1 93/06/06 22:05:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00021/00000/00000
d D 5.1 91/03/02 13:17:33 bostic 1 0
c date and time created 91/03/02 13:17:33 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

BINDIR?=	/usr/bin
BINOWN?=	uucp
BINGRP?=	daemon

ETC=    	${DESTDIR}/etc
LIBDIR=		${DESTDIR}/usr/lib/uucp
PUBDIR= 	${DESTDIR}/var/spool/uucppublic

AUDIT=		${SPOOL}/AUDIT
CORRUPT=	${SPOOL}/CORRUPT
LCK=		${SPOOL}/LCK
LOG=		${SPOOL}/LOG
SPOOL=  	${DESTDIR}/var/spool/uucp
STST=		${SPOOL}/STST
XQTDIR=		${SPOOL}/XTMP

LIBUU=		${.CURDIR}/../libuu/obj/libuu.a
LIBACU=		${.CURDIR}/../libacu/obj/libacu.a
CFLAGS+=	-DUSE_OLD_TTY
E 1
