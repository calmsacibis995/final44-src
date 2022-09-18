h32091
s 00001/00001/00019
d D 5.5 91/01/31 11:28:14 bostic 5 4
c move lint into the pcc directory
e
s 00001/00001/00019
d D 5.4 90/06/19 15:01:47 bostic 4 3
c OBJS depends on pcclocal.h
e
s 00003/00003/00017
d D 5.3 90/06/18 11:58:04 bostic 3 2
c move localdefs.h to pcc/mip
e
s 00004/00004/00016
d D 5.2 90/06/17 15:04:29 bostic 2 1
c pcc moved
e
s 00020/00000/00000
d D 5.1 90/06/05 14:33:25 bostic 1 0
c date and time created 90/06/05 14:33:25 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
MIP=	${.CURDIR}/../../../libexec/mip
PCC=	${.CURDIR}/../../../libexec/pcc
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

PROG=	lintpass2
SRCS=	hash.c lpass2.c
CFLAGS+=-I${MIP} -I. -I${.CURDIR}/../lpass1
BINDIR=	/usr/libexec
D 3
.PATH:	${.CURDIR}/../lpass1
E 3
I 3
.PATH:	${.CURDIR}/../lpass1 ${MIP}
CLEANFILES+=pcclocal.h
E 3
NOMAN=	noman

.include <bsd.prog.mk>

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

D 4
.depend: pcclocal.h
E 4
I 4
${OBJS} .depend: pcclocal.h
E 4
E 1
