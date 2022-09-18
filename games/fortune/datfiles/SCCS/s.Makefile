h09680
s 00001/00001/00035
d D 8.2 94/04/19 12:12:44 christos 7 6
c update, Makefile workaround no longer needed
e
s 00000/00000/00036
d D 8.1 93/05/31 17:01:14 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00006/00022
d D 5.5 93/05/24 23:08:31 bostic 5 4
c integrate second set of databases
e
s 00001/00001/00027
d D 5.4 92/07/19 12:56:28 bostic 4 3
c /usr/games often isn't in root's path
e
s 00019/00011/00009
d D 5.3 91/11/21 11:15:12 bostic 3 2
c fix scene/obscene creation
e
s 00001/00000/00019
d D 5.2 91/05/06 16:18:11 bostic 2 1
c remove the datfiles on make clean
e
s 00019/00000/00000
d D 5.1 91/04/27 16:02:05 bostic 1 0
c date and time created 91/04/27 16:02:05 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
DATFILES=fortunes.dat startrek.dat zippy.dat fortunes-o.dat
I 2
CLEANFILES+=${DATFILES}
E 3
I 3
D 5
# If TYPE is real, the real obscene fortunes get installed.  If TYPE is
# fake, they don't.  See how easy that was?
E 5
I 5
SRCS=	fortunes fortunes2 startrek zippy
BLDS=	fortunes.dat fortunes2.dat startrek.dat zippy.dat \
	fortunes-o fortunes-o.dat
E 5
E 3
E 2

I 5
# TO INSTALL THE POTENTIALLY OFFENSIVE FORTUNES, UNCOMMENT THE THREE
# LINES AND COMMENT OUT THE FOURTH LINE.

# THE THREE LINES
SRCS+=	fortunes2-o limerick
BLDS+=	fortunes2-o.dat limerick.dat
E 5
D 3
install: ${DATFILES}
E 3
I 3
TYPE=	real
I 5

# THE FOURTH LINE
E 5
#TYPE=	fake

D 5
SRCS=	fortunes startrek zippy
BLDS=	fortunes.dat startrek.dat zippy.dat fortunes-o fortunes-o.dat
E 5
CLEANFILES+=${BLDS}

install: ${SRCS} ${BLDS}
E 3
	(cd ${.CURDIR} && install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
D 3
	    ${DATFILES:R} ${DESTDIR}/usr/share/games/fortune)
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${DATFILES} \
E 3
I 3
	    ${SRCS} ${DESTDIR}/usr/share/games/fortune)
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${BLDS} \
E 3
	    ${DESTDIR}/usr/share/games/fortune

D 3
fortunes-o.dat: ${.TARGET:R}
	${.CURDIR}/../strfile/obj/strfile -rsx \
	    ${.CURDIR}/${.TARGET:R} ${.TARGET}
E 3
I 3
D 5
fortunes.dat startrek.dat zippy.dat:
	${.CURDIR}/../strfile/obj/strfile -rs ${.CURDIR}/${.TARGET:R} ${.TARGET}
E 5
I 5
fortunes.dat fortunes2.dat fortunes2-o.dat limerick.dat startrek.dat zippy.dat:
	${.CURDIR}/../strfile/obj/strfile -rs \
	    ${.CURDIR}/${.TARGET:R} ${.TARGET}
E 5
E 3

D 3
fortunes.dat startrek.dat zippy.dat: ${.TARGET:R}
	${.CURDIR}/../strfile/obj/strfile -rs \
	    ${.CURDIR}/${.TARGET:R} ${.TARGET}
E 3
I 3
fortunes-o.dat: fortunes-o
	${.CURDIR}/../strfile/obj/strfile -rsx fortunes-o ${.TARGET}

fortunes-o: fortunes-o.${TYPE}
D 4
	caesar 13 < ${.CURDIR}/${.ALLSRC} > ${.TARGET}
E 4
I 4
D 7
	/usr/games/caesar 13 < ${.CURDIR}/${.ALLSRC} > ${.TARGET}
E 7
I 7
	/usr/games/caesar 13 < ${.ALLSRC} > ${.TARGET}
E 7
E 4
E 3

.include <bsd.prog.mk>
E 1
