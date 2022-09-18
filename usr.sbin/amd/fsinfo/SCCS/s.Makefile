h50991
s 00000/00000/00030
d D 8.1 93/06/28 07:44:37 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00029
d D 5.4 93/06/28 07:44:32 bostic 5 3
c add a man page
e
s 00000/00000/00030
d R 8.1 93/06/06 11:57:23 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00002/00027
d D 5.3 91/05/12 15:59:54 pendry 3 2
c checkpoint for network tape
e
s 00005/00003/00024
d D 5.2 91/03/17 11:12:45 pendry 2 1
c Fixed yacc and lex rules.  Added CLEANFILES
e
s 00027/00000/00000
d D 5.1 91/03/17 11:02:54 pendry 1 0
c date and time created 91/03/17 11:02:54 by pendry
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	fsinfo
D 5
NOMAN=	true
E 5
I 5
MAN8=	fsinfo.0
E 5
SRCS=	fsinfo.c fsi_gram.c fsi_lex.c \
	fsi_util.c fsi_analyze.c fsi_dict.c \
	wr_atab.c wr_bparam.c wr_dumpset.c \
	wr_exportfs.c wr_fstab.c
I 3
CLEANFILES= \
	fsi_gram.c y.tab.c fsi_gram.h y.tab.h \
	fsi_lex.c lex.yy.c y.output
E 3
I 2
CFLAGS+=-I.
E 2
CFLAGS+=-I${.CURDIR}/../include
D 2
CFLAGS+=-I${.CURDIR}/../rpcx
E 2
CFLAGS+=-I${.CURDIR}/../config
CFLAGS+=-DOS_HDR=\"os-bsd44.h\"

fsi_lex.o fsinfo.o: fsi_gram.h
fsi_gram.c fsi_gram.h: ../fsinfo/fsi_gram.y
	@echo "# expect 2 shift/reduce conflicts"
D 2
	${YACC} -d ../fsinfo/fsi_gram.y
E 2
I 2
	${YACC} -d ${.CURDIR}/fsi_gram.y
E 2
	mv y.tab.c fsi_gram.c
	mv y.tab.h fsi_gram.h

fsi_lex.c: ../fsinfo/fsi_lex.l
D 2
	${LEX} ../fsinfo/fsi_lex.l
E 2
I 2
	${LEX} ${.CURDIR}/fsi_lex.l
E 2
	mv lex.yy.c fsi_lex.c
I 2
D 3

CLEANFILES = fsi_gram.c y.tab.c fsi_gram.h y.tab.h fsi_lex.c lex.yy.c y.output
E 3
E 2

.PATH: ${.CURDIR}/../config
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
