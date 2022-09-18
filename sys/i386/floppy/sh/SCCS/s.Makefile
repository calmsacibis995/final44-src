h57928
s 00000/00000/00049
d D 8.1 93/06/11 15:32:09 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00049/00000/00000
d D 5.1 91/05/03 19:11:41 bostic 1 0
c date and time created 91/05/03 19:11:41 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	sh
SRCS=	builtins.c cd.c dirent.c echo.c error.c eval.c exec.c expand.c \
	input.c jobs.c mail.c main.c memalloc.c miscbltin.c \
	mystring.c nodes.c options.c parser.c redir.c show.c signames.c \
	syntax.c trap.c output.c var.c
OBJS+=	init.o
ORIG=	${.CURDIR}/../../../../bin/sh
CFLAGS+=-DLETS_GET_SMALL -DSHELL -I. -I${ORIG}
NOMAN=	noman
LDFLAGS=-N
.PATH:	${ORIG} ${ORIG}/bltin
CLEANFILES+=\
	builtins.c builtins.h init.c mkinit mknodes mksignames mksyntax \
	nodes.c nodes.h signames.c signames.h syntax.c syntax.h token.def

.depend parser.o: token.def
token.def: mktokens
	sh ${ORIG}/mktokens

builtins.h builtins.c: ${ORIG}/mkbuiltins ${ORIG}/builtins
	cd ${.CURDIR}; sh mkbuiltins

init.c: mkinit ${SRCS}
	./mkinit '${CC} -c ${CFLAGS} init.c' ${.ALLSRC}

mkinit: ${ORIG}/mkinit.c
	${CC} ${CFLAGS} ${ORIG}/mkinit.c -o $@

nodes.c nodes.h: mknodes ${ORIG}/nodetypes ${ORIG}/nodes.c.pat
	./mknodes ${ORIG}/nodetypes ${ORIG}/nodes.c.pat

mknodes: ${ORIG}/mknodes.c
	${CC} ${CFLAGS} ${ORIG}/mknodes.c -o $@

signames.c signames.h: mksignames
	./mksignames

mksignames: ${ORIG}/mksignames.c
	${CC} ${CFLAGS} ${ORIG}/mksignames.c -o $@

syntax.c syntax.h: mksyntax
	./mksyntax

mksyntax: ${ORIG}/mksyntax.c ${ORIG}/parser.h
	${CC} ${CFLAGS} ${ORIG}/mksyntax.c -o $@

.include <bsd.prog.mk>
E 1
