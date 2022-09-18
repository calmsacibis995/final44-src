h14090
s 00000/00000/00014
d D 8.1 93/06/08 11:34:11 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00013
d D 5.4 92/07/11 17:29:45 jak 4 3
c added wide tabset file for vt100-w* termcaps
e
s 00003/00003/00011
d D 5.3 90/10/22 14:43:44 bostic 3 2
c add 9837 for jak
e
s 00002/00001/00012
d D 5.2 90/06/08 14:34:03 bostic 2 1
c don't need obj, use bsd.prog.mk
e
s 00013/00000/00000
d D 5.1 90/05/11 13:54:22 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
FILES=	3101 aa aed512 beehive diablo dtc382 hp700-wy ibm3101 std stdcrt \
	tandem653 teleray vt100 wyse-adds xerox1720 xerox1730 xerox1730-lm \
	zenith29
E 3
I 3
FILES=	3101 9837 aa aed512 beehive diablo dtc382 hp700-wy ibm3101 std \
D 4
	stdcrt tandem653 teleray vt100 wyse-adds xerox1720 xerox1730 \
E 4
I 4
	stdcrt tandem653 teleray vt100 vt100-w wyse-adds xerox1720 xerox1730 \
E 4
	xerox1730-lm zenith29
E 3
I 2
NOOBJ=	noobj
E 2

all clean cleandir depend lint tags:

install:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}/tabset

D 2
.include <bsd.own.mk>
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
