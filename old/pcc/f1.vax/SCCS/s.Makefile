h25418
s 00002/00002/00023
d D 5.3 90/06/28 22:16:59 bostic 3 2
c dependencies go after include
e
s 00006/00006/00019
d D 5.2 90/06/18 11:46:33 bostic 2 1
c localdefs.h -> pcc/mip, use .IMPSRC instead of specifying
e
s 00025/00000/00000
d D 5.1 90/06/17 14:23:22 bostic 1 0
c date and time created 90/06/17 14:23:22 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	f1
MIP=	${.CURDIR}/../mip
CCOM=	${.CURDIR}/../ccom.vax
CFLAGS+=-DFORT -I. -I${.CURDIR} -I${CCOM} -I${MIP}
SRCS=	allo.c common.c fort.c local2.c match.c order.c reader.c table.c
NOMAN=	noman
.PATH:	${MIP} ${CCOM}
CLEANFILES+=pcclocal.h

D 2
table.o: ${CCOM}/table.c
	${CC} ${CFLAGS} -c -R ${CCOM}/table.c
E 2
I 2
table.o:
	${CC} ${CFLAGS} -c -R ${.IMPSRC}
E 2

D 2
common.o: ${MIP}/common.c
	${CC} ${CFLAGS} -DPASS2COMMON -c ${.ALLSRC}
E 2
I 2
common.o:
	${CC} ${CFLAGS} -DPASS2COMMON -c ${.IMPSRC}
E 2

D 2
pcclocal.h: ${.CURDIR}/../ccom.vax/localdefs.h /usr/include/pcc.h
E 2
I 2
pcclocal.h: localdefs.h /usr/include/pcc.h
E 2
	cat ${.ALLSRC} | \
	    egrep '^#[ 	]*(define[ 	][ 	]*PCC(F|T|TM|OM)?_|ifdef|ifndef|endif)' | \
	    sed -e 's/PCC[A-Z]*_//' > ${.TARGET}

D 2
.depend: pcclocal.h
E 2
I 2
D 3
${OBJS} .depend: pcclocal.h
E 2

E 3
.include <bsd.prog.mk>
I 3

${OBJS} .depend: pcclocal.h
E 3
E 1
