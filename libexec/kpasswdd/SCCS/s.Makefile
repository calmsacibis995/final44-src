h03620
s 00000/00000/00011
d D 8.1 93/06/04 18:50:25 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.1 91/01/15 18:13:49 bostic 4 3
c needs CRYPT now
e
s 00001/00001/00010
d D 1.3 90/06/22 20:42:57 kfall 3 2
c add libkdb to DPADD
e
s 00005/00006/00006
d D 1.2 90/06/22 15:39:06 kfall 2 1
c moved location into /usr/src/libexec
e
s 00012/00000/00000
d D 1.1 90/05/14 14:39:26 kfall 1 0
c date and time created 90/05/14 14:39:26 by kfall
e
u
U
t
T
I 1
D 2
BINDIR=	/usr/libexec
E 2
I 2
#	%W% (Berkeley) %G%

E 2
PROG=	kpasswdd
SRCS=	kpasswdd.c des_rw.c
D 2
MAN8=	kpasswdd.0
E 2
I 2
D 4
CFLAGS+=-DKERBEROS -I${.CURDIR}/../../usr.bin/passwd
E 4
I 4
CFLAGS+=-DCRYPT -DKERBEROS -I${.CURDIR}/../../usr.bin/passwd
E 4
E 2
D 3
DPADD=	${LIBKRB} ${LIBDES}
E 3
I 3
DPADD=	${LIBKDB} ${LIBKRB} ${LIBDES}
E 3
D 2
CFLAGS+=-DKERBEROS -I../kpasswd
E 2
LDADD=	-lkdb -lkrb -ldes
D 2
BINOWN=	bin
BINMODE=755
.PATH:  ${.CURDIR}/../../usr.bin/rlogin
E 2
I 2
.PATH:	${.CURDIR}/../../usr.bin/rlogin
MAN8=	kpasswdd.0
E 2

.include <bsd.prog.mk>
E 1
