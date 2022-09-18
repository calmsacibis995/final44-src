h28267
s 00000/00000/00010
d D 8.1 93/06/06 15:12:36 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 90/06/29 11:38:21 bostic 1 0
c date and time created 90/06/29 11:38:21 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

FILES=	how_pc how_pi how_pix how_pxp
NOOBJ=	noobj

install:
	install -c -o bin -g bin -m 444 ${FILES} \
	    ${DESTDIR}/usr/libdata/pascal

.include <bsd.prog.mk>
E 1
