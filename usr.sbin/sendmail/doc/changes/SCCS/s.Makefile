h21754
s 00013/00000/00000
d D 8.1 94/04/13 07:30:38 eric 1 0
c date and time created 94/04/13 07:30:38 by eric
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	smm/09.sendmail
SRCS=	changes.me
MACROS=	-me

all: changes.ps

changes.ps: ${SRCS}
	rm -f ${.TARGET}
	${PIC} ${SRCS} | ${ROFF} > ${.TARGET}

.include <bsd.doc.mk>
E 1
