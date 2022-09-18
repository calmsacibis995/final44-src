#	@(#)Makefile	8.1 (Berkeley) 7/19/93

PROG=	rkinit
CFLAGS+=-I/csrg/src/kerberosIV/include
CFLAGS+=-I${.CURDIR}/../../kerberosIV/include
CFLAGS+=-I${.CURDIR}/../../include
CFLAGS+=-I${.CURDIR}/../../compat
CFLAGS+=-I/usr/sww/include
SRCS=	rkinit.c
DPADD=	${LIBRKINIT} ${LIBKRB} ${LIBDES}
LDADD=	-L${.CURDIR}/../../lib/librkinit/obj -lrkinit
LDADD+=	-L${.CURDIR}/../../kerberosIV/krb/obj -lkrb
LDADD+=	-L${.CURDIR}/../../kerberosIV/des/obj -ldes
LDADD+=	-L${.CURDIR}/../../compat/obj -lcompat
LDADD=	-L${.CURDIR}/../librkinit/obj -lrkinit
LDADD+=	-lkrb -ldes
INSTALLFLAGS=-fschg

.include <bsd.prog.mk>
