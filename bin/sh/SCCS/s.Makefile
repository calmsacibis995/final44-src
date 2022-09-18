h19700
s 00003/00003/00039
d D 8.4 95/05/05 08:30:02 bostic 12 9
c delete printf.o
e
s 00000/00001/00046
d R 8.5 95/05/05 08:25:24 bostic 11 10
c somebody didn't try "make"
e
s 00006/00006/00036
d R 8.4 95/05/04 15:20:56 bostic 10 9
c delete printf.o
e
s 00005/00005/00037
d D 8.3 95/05/04 18:02:10 christos 9 8
c merged netbsd changes
e
s 00003/00010/00039
d D 8.2 95/04/27 14:47:35 bostic 8 7
c J.T. Conklin's changes for signals mean that we don't need all
c of the random signal crap any longer
e
s 00000/00000/00049
d D 8.1 93/06/08 12:50:57 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00048
d D 5.5 93/06/01 23:03:39 bostic 6 4
c don't compile -g by default
e
s 00000/00000/00049
d R 8.1 93/05/31 15:21:28 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00047
d D 5.4 92/10/15 16:25:59 marc 4 3
c clean up y.tab.h
e
s 00003/00003/00045
d D 5.3 92/09/02 11:45:52 bostic 3 2
c don't assume mounted under /usr/src
e
s 00001/00001/00047
d D 5.2 92/07/15 10:36:40 marc 2 1
c remove dirent.c
e
s 00048/00000/00000
d D 5.1 92/06/23 18:13:27 marc 1 0
c date and time created 92/06/23 18:13:27 by marc
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	sh
D 2
SRCS=	alias.c builtins.c cd.c dirent.c echo.c error.c eval.c exec.c expand.c \
E 2
I 2
SRCS=	alias.c builtins.c cd.c echo.c error.c eval.c exec.c expand.c \
E 2
	histedit.c input.c jobs.c mail.c main.c memalloc.c miscbltin.c \
D 3
	mystring.c nodes.c options.c parser.c printf.c redir.c show.c signames.c \
	syntax.c trap.c output.c var.c
E 3
I 3
D 9
	mystring.c nodes.c options.c parser.c printf.c redir.c show.c \
E 9
I 9
D 12
	mystring.c nodes.c options.c parser.c redir.c show.c \
E 9
D 8
	signames.c syntax.c trap.c output.c var.c
E 8
I 8
	syntax.c trap.c output.c var.c
E 12
I 12
	mystring.c nodes.c options.c parser.c redir.c show.c syntax.c \
	trap.c output.c var.c
E 12
E 8
E 3
OBJS+=	init.o arith.o arith_lex.o
D 9
LDADD=	-ll -ledit -ltermcap -lcompat
E 9
I 9
LDADD+=	-ll -ledit -ltermcap
E 9
LFLAGS= -8	# 8-bit lex scanner for arithmetic
D 6
CFLAGS+=-DSHELL -I. -I${.CURDIR} -g
E 6
I 6
CFLAGS+=-DSHELL -I. -I${.CURDIR}
E 6
D 3
.PATH:	${.CURDIR}/bltin /usr/src/usr.bin/printf
E 3
I 3
.PATH:	${.CURDIR}/bltin ${.CURDIR}/../../usr.bin/printf
E 3
CLEANFILES+=\
D 8
	builtins.c builtins.h init.c mkinit mknodes mksignames mksyntax \
D 4
	nodes.c nodes.h signames.c signames.h syntax.c syntax.h token.def
E 4
I 4
	nodes.c nodes.h signames.c signames.h syntax.c syntax.h token.def \
	y.tab.h
E 8
I 8
	builtins.c builtins.h init.c mkinit mknodes mksyntax \
D 12
	nodes.c nodes.h syntax.c syntax.h token.def y.tab.h
E 12
I 12
	nodes.c nodes.h printf.o syntax.c syntax.h token.def y.tab.h
E 12
E 8
E 4

.depend parser.o: token.def
token.def: mktokens
	sh ${.CURDIR}/mktokens

D 9
builtins.h builtins.c: ${.CURDIR}/mkbuiltins ${.CURDIR}/builtins
	cd ${.CURDIR}; sh mkbuiltins
E 9
I 9
builtins.h builtins.c: ${.CURDIR}/mkbuiltins ${.CURDIR}/builtins.def
	cd ${.CURDIR}; sh mkbuiltins ${.OBJDIR}
E 9

init.c: mkinit ${SRCS}
D 9
	./mkinit '${CC} -c ${CFLAGS} init.c' ${.ALLSRC}
E 9
I 9
	./mkinit '${CC} -c ${CFLAGS} init.c' ${.ALLSRC:S/^mkinit$//}
E 9

mkinit: ${.CURDIR}/mkinit.c
	${CC} ${CFLAGS} ${.CURDIR}/mkinit.c -o $@

nodes.c nodes.h: mknodes ${.CURDIR}/nodetypes ${.CURDIR}/nodes.c.pat
	./mknodes ${.CURDIR}/nodetypes ${.CURDIR}/nodes.c.pat

mknodes: ${.CURDIR}/mknodes.c
	${CC} ${CFLAGS} ${.CURDIR}/mknodes.c -o $@
D 8

signames.c signames.h: mksignames
	./mksignames

mksignames: ${.CURDIR}/mksignames.c
	${CC} ${CFLAGS} ${.CURDIR}/mksignames.c -o $@
E 8

syntax.c syntax.h: mksyntax
	./mksyntax

mksyntax: ${.CURDIR}/mksyntax.c ${.CURDIR}/parser.h
	${CC} ${CFLAGS} ${.CURDIR}/mksyntax.c -o $@

.include <bsd.prog.mk>
E 1
