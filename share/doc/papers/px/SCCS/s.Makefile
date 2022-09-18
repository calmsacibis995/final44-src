h11707
s 00001/00000/00015
d D 5.4 94/10/09 21:51:43 mckusick 4 3
c set macro package
e
s 00001/00001/00014
d D 5.3 93/06/08 17:49:27 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00008/00005
d D 5.2 90/06/30 15:01:12 bostic 2 1
c new doc makefiles
e
s 00013/00000/00000
d D 5.1 90/06/05 17:22:19 bostic 1 0
c date and time created 90/06/05 17:22:19 by bostic
e
u
U
t
T
I 1
D 2
TROFF=	vtroff -t
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
print: trofftxt
	vpr -t trofftxt
E 2
I 2
DIR=	papers/px
I 4
MACROS=	-ms
E 4
SRCS=	pxin0.n pxin1.n pxin2.n pxin3.n pxin4.n
EXTRA=	fig1.1.n fig1.2.n fig1.3.n fig2.3.raw fig2.4.n fig3.2.n \
	fig3.3.n table2.1.n table2.2.n table2.3.n table3.1.n tmac.p
CLEANFILES+=fig2.3.n
E 2

D 2
troff:
	/usr/ucb/soelim pxin?.n | tbl | ${TROFF}
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS} fig2.3.n
E 3
I 3
paper.ps: ${SRCS} fig2.3.n
E 3
	${SOELIM} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 2

D 2
trofftxt: fig2.3.n
	/usr/ucb/soelim pxin?.n | tbl | /usr/ucb/vtroff -t >trofftxt

E 2
fig2.3.n: fig2.3.raw
	sort fig2.3.raw >fig2.3.n
I 2

.include <bsd.doc.mk>
E 2
E 1
