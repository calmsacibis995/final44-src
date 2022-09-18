#	@(#)Makefile	8.1 (Berkeley) 6/1/93

PROG=	kprop
SRCS=	kprop.c
CFLAGS+=-DCRYPT -DDEBUG -DKERBEROS
CFLAGS+=-I/csrg/src/kerberosIV/include
CFLAGS+=-I${.CURDIR}/../include
CFLAGS+=-I${.CURDIR}/../../include
CFLAGS+=-I${.CURDIR}/../../compat
CFLAGS+=-I/usr/sww/include
.PATH:	${.CURDIR}/../../usr.bin/rlogin
DPADD=	${LIBKRB} ${LIBDES}
LDADD=  -L${.CURDIR}/../krb/obj -lkrb
LDADD+= -L${.CURDIR}/../des/obj -ldes
LDADD+= -L/usr/sww/bin -lresolv
LDADD+= -L${.CURDIR}/../../compat/obj -lcompat
.if	${MACHINE} == "snake"
LDADD+= -lndbm
.endif
LDADD= -lkrb -ldes
NOMAN=	noman

.include <bsd.prog.mk>
