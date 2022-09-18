#	@(#)Makefile	8.1 (Berkeley) 6/4/93

PROG=	rkinitd
CFLAGS+=-I${.CURDIR}/../../kerberosIV/include
CFLAGS+=-I${.CURDIR}/../../include
CFLAGS+=-I${.CURDIR}/../../compat
CFLAGS+=-I/usr/sww/include
CFLAGS+=-I/csrg/src/kerberosIV/include
SRCS		= rkinitd.c util.c rpc.c krb.c
MAN8=	rkinitd.0
DPADD=	${LIBRKINIT} ${LIBKRB} ${LIBDES}
LDADD=	-L${.CURDIR}/../../lib/librkinit/obj -lrkinit
LDADD+=	-L${.CURDIR}/../../kerberosIV/krb/obj -lkrb
LDADD+=	-L${.CURDIR}/../../kerberosIV/des/obj -ldes
LDADD+= -L/usr/sww/bin -lresolv
LDADD+=	-L${.CURDIR}/../../compat/obj -lcompat
LDADD=	-L${.CURDIR}/../librkinit/obj -lrkinit
LDADD+=	-lkrb -ldes

.include <bsd.prog.mk>
