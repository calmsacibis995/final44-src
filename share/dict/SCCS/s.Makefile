h47300
s 00000/00000/00012
d D 8.1 93/06/05 13:00:17 bostic 3 1
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00001/00011
d D 5.1.1.1 91/05/07 17:05:38 bostic 2 1
c branch for the 2nd network distribution
e
s 00012/00000/00000
d D 5.1 90/06/19 17:40:52 bostic 1 0
c date and time created 90/06/19 17:40:52 by bostic
e
u
U
f b 
t
T
I 1
#	%W% (Berkeley) %G%

D 2
FILES=	README connectives propernames web2 web2a words
E 2
I 2
# Missing: connectives, words

FILES=	README propernames web2 web2a
E 2
NOOBJ=	noobj

all clean cleandir depend lint tags:

install:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}/dict

.include <bsd.prog.mk>
E 1
