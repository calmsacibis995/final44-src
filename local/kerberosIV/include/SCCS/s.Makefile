h37543
s 00000/00000/00013
d D 8.1 93/06/01 23:09:12 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00000/00000
d D 5.1 90/06/25 11:37:10 bostic 1 0
c date and time created 90/06/25 11:37:10 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

FILES=	des.h kadm.h kadm_err.h kparse.h krb.h krb_db.h krb_err.h \
	mit-copyright.h
NOOBJ=	noobj

all include clean cleandir depend lint tags:

install:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${FILES} ${DESTDIR}/usr/include/kerberosIV

.include <bsd.prog.mk>
E 1
