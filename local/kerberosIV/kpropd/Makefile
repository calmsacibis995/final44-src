#
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh
#
#	@(#)Makefile	8.1 (Berkeley) 6/1/93
#
PROG=	kpropd
SRCS=	kpropd.c
CFLAGS+=-DCRYPT -DKERBEROS
CFLAGS+=-I${.CURDIR}/../kprop
CFLAGS+=-I/csrg/src/kerberosIV/include
CFLAGS+=-I${.CURDIR}/../include
CFLAGS+=-I${.CURDIR}/../../include
CFLAGS+=-I${.CURDIR}/../../compat
CFLAGS+=-I/usr/sww/include
DPADD=	${LIBKDB} ${LIBKRB} ${LIBDES} ${LIBCOMPAT}
LDADD=	-L${.CURDIR}/../kdb/obj -lkdb
LDADD+= -L${.CURDIR}/../krb/obj -lkrb
LDADD+= -L${.CURDIR}/../des/obj -ldes
LDADD+= -L/usr/sww/bin -lresolv
LDADD+= -L${.CURDIR}/../../compat/obj -lcompat
BINDIR=	${KRBUSR}/libexec
NOMAN=  noman

LDADD= -lkrb -ldes
BINDIR= /usr/libexec

.include <bsd.prog.mk>
