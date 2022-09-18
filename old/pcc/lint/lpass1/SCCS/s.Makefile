h29166
s 00001/00001/00037
d D 5.5 91/01/31 11:27:47 bostic 5 4
c move lint into the pcc directory
e
s 00002/00001/00036
d D 5.4 90/07/01 10:47:55 bostic 4 3
c clean mip files
e
s 00003/00004/00034
d D 5.3 90/06/18 11:55:24 bostic 3 2
c move localdefs.h to pcc/mip
e
s 00009/00007/00029
d D 5.2 90/06/17 15:03:20 bostic 2 1
c pcc moved
e
s 00036/00000/00000
d D 5.1 90/06/05 14:33:20 bostic 1 0
c date and time created 90/06/05 14:33:20 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
PCC=	${.CURDIR}/../../../libexec/pcc
MIP=	${.CURDIR}/../../../libexec/mip
E 2
I 2
D 5
MIP=	${.CURDIR}/../../../libexec/pcc/mip
E 5
I 5
MIP=	${.CURDIR}/../../mip
E 5
D 3
CCOM=	${.CURDIR}/../../../libexec/pcc/ccom.vax
E 3
E 2

PROG=	lintpass1
CFLAGS+=-I${MIP} -I. -I${.CURDIR}
D 3
.PATH:	${.CURDIR}/.. ${MIP}
E 3
I 3
D 4
.PATH:	${MIP}
E 4
E 3
SRCS=	cgram.c common.c hash.c lint.c optim.c pftn.c rel.c rodata.c scan.c \
	trees.c xdefs.c
I 4
.PATH:	${MIP}
E 4
BINDIR=	/usr/libexec
MAN1=	lint.0
I 4
CLEANFILES=cgram.c gram.in pcclocal.h pcctokens rodata.c
E 4

.include <bsd.prog.mk>

rodata.o:
	$(CC) -c ${CFLAGS} -R ${.IMPSRC}

common.o:
	${CC} -c ${CFLAGS} -DPASS1COMMON ${.IMPSRC}

rodata.c cgram.c: pcclocal.h pcctokens
	cat pcctokens ${MIP}/cgram.y > gram.in
	${YACC} gram.in
	yyfix rodata.c yylhs yylen yydefred yydgoto yysindex yyrindex yygindex \
	    yytable yycheck
	mv y.tab.c cgram.c

D 2
pcclocal.h: ${PCC}/localdefs.h /usr/include/pcc.h
	cat /usr/include/pcc.h ${PCC}/localdefs.h | \
E 2
I 2
D 3
pcclocal.h: ${CCOM}/localdefs.h /usr/include/pcc.h
E 3
I 3
pcclocal.h: localdefs.h /usr/include/pcc.h
E 3
	cat ${.ALLSRC} | \
E 2
	   egrep '^#[ 	]*(define[ 	][ 	]*PCC(F|T|TM|OM)?_|ifdef|ifndef|endif)' | \
	   sed -e 's/PCC[A-Z]*_//' > ${.TARGET}

D 2
pcctokens: ${PCC}/localdefs.h /usr/include/pcc.h
	cat /usr/include/pcc.h ${PCC}/localdefs.h | \
	    egrep '^#[ 	]*define[ 	][ 	]*PCC_' | sed -e 's/^#[ 	]*define[ 	][ 	]*PCC_/%term	/' > ${.TARGET}
E 2
I 2
D 3
pcctokens: ${CCOM}/localdefs.h /usr/include/pcc.h
E 3
I 3
pcctokens: localdefs.h /usr/include/pcc.h
E 3
	cat ${.ALLSRC} | \
	    egrep '^#[ 	]*define[ 	][ 	]*PCC_' | \
	    sed -e 's/^#[ 	]*define[ 	][ 	]*PCC_/%term	/' > \
	    ${.TARGET}
E 2
E 1
