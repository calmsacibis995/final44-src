h62554
s 00000/00000/00015
d D 8.1 93/06/11 14:49:26 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00015/00000/00000
d D 5.1 93/06/11 14:49:16 bostic 1 0
c date and time created 93/06/11 14:49:16 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

SUBDIR=	boggle mkdict mkindex

beforeinstall:
	mkdict/obj/mkdict < /usr/share/dict/words > \
	    ${DESTDIR}/usr/share/games/boggle/dictionary
	mkindex/obj/mkindex < ${DESTDIR}/usr/share/games/boggle/dictionary > \
	    ${DESTDIR}/usr/share/games/boggle/dictindex
	chown ${BINOWN}.${BINGRP} ${DESTDIR}/usr/share/games/boggle/dictionary
	chmod 444 ${DESTDIR}/usr/share/games/boggle/dictionary
	chown ${BINOWN}.${BINGRP} ${DESTDIR}/usr/share/games/boggle/dictindex
	chmod 444 ${DESTDIR}/usr/share/games/boggle/dictindex
	
.include <bsd.subdir.mk>
E 1
