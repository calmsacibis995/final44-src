h30381
s 00002/00003/00043
d D 5.3 90/06/18 13:56:07 bostic 3 2
c don't use yacc temporary
e
s 00007/00010/00039
d D 5.2 90/06/18 11:46:00 bostic 2 1
c localdefs.h -> pcc/mip, use .IMPSRC instead of specifying
e
s 00049/00000/00000
d D 5.1 90/06/17 14:27:38 bostic 1 0
c date and time created 90/06/17 14:27:38 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%
#
# 'sccom' is a C compiler that does single precision computations in
# single precision rather than double precision.
#

PROG=	sccom
MIP=	${.CURDIR}/../mip
CCOM=	${.CURDIR}/../ccom.vax
CFLAGS+=-DONEPASS -DSPRECC -I. -I${.CURDIR} -I${CCOM} -I${MIP}
SRCS=	allo.c code.c common.c local.c local2.c match.c optim.c order.c \
	pftn.c reader.c rel.c scan.c stab.c table.c trees.c xdefs.c
OBJS+=	cgram.o rodata.o
NOMAN=	noman
.PATH:	${CCOM} ${MIP}
D 3
CLEANFILES+=cgram.c gram.in rodata.c pcctokens pcclocal.h
E 3
I 3
CLEANFILES+=cgram.c rodata.c pcctokens pcclocal.h
E 3

cgram.o: cgram.c
	${CC} ${CFLAGS} -c cgram.c

rodata.c cgram.c: ${MIP}/cgram.y pcctokens
D 3
	cat pcctokens ${MIP}/cgram.y > gram.in
	${YACC} gram.in
E 3
I 3
	cat pcctokens ${MIP}/cgram.y | ${YACC} /dev/stdin
E 3
	yyfix rodata.c
	mv y.tab.c cgram.c

D 2
common.o: ${MIP}/common.c
	${CC} ${CFLAGS} -DPASS1COMMON -c ${.ALLSRC}
E 2
I 2
common.o:
	${CC} ${CFLAGS} -DPASS1COMMON -c ${.IMPSRC}
E 2

D 2
rodata.o: rodata.c
	${CC} ${CFLAGS} -c -R rodata.c
E 2
I 2
rodata.o table.o:
	${CC} ${CFLAGS} -c -R ${.IMPSRC}
E 2

D 2
table.o: ${CCOM}/${.PREFIX}.c
	${CC} ${CFLAGS} -c -R ${CCOM}/${.PREFIX}.c

pcclocal.h: ${.CURDIR}/../ccom.vax/localdefs.h /usr/include/pcc.h
E 2
I 2
pcclocal.h: localdefs.h /usr/include/pcc.h
E 2
	cat ${.ALLSRC} | \
	    egrep '^#[ 	]*(define[ 	][ 	]*PCC(F|T|TM|OM)?_|ifdef|ifndef|endif)' | \
	    sed -e 's/PCC[A-Z]*_//' > ${.TARGET}

D 2
pcctokens: ${.CURDIR}/../ccom.vax/localdefs.h /usr/include/pcc.h
E 2
I 2
pcctokens: localdefs.h /usr/include/pcc.h
E 2
	cat ${.ALLSRC} | \
	    egrep '^#[ 	]*define[ 	][ 	]*PCC_' | \
	    sed -e 's/^#[ 	]*define[ 	][ 	]*PCC_/%term	/' > \
	    ${.TARGET}

D 2
.depend: pcclocal.h pcctokens
E 2
I 2
${OBJS} .depend: pcclocal.h pcctokens
E 2

.include <bsd.prog.mk>
E 1
