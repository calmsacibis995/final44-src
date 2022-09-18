h56086
s 00001/00001/00007
d D 8.2 94/05/16 18:22:36 mckusick 5 4
c update for 4.4BSD manuals
e
s 00000/00000/00008
d D 8.1 93/06/08 13:18:22 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00007
d D 5.3 93/06/05 17:26:36 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00000/00003/00008
d D 5.2 93/06/05 17:26:07 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00011/00000/00000
d D 5.1 90/06/30 15:10:22 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
DIR=	usd/25.trofftut
E 3
I 3
DIR=	usd/22.trofftut
E 3
SRCS=	tt.mac tt00 tt01 tt02 tt03 tt04 tt05 tt06 tt07 tt08 tt09 tt10 \
	tt11 tt12 tt13 tt14 ttack ttcharset ttindex
D 5
MACROS=	-msU
E 5
I 5
MACROS=	-ms
E 5

D 2
paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}

E 2
.include <bsd.doc.mk>
E 1
