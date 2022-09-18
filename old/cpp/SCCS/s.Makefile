h11024
s 00001/00000/00017
d R 5.3 91/02/01 10:17:00 bostic 11 10
c install in /usr/bin for now
e
s 00002/00004/00015
d D 5.2 90/05/12 19:27:03 bostic 10 9
c yyfix is a real program now
e
s 00012/00039/00007
d D 5.1 90/05/11 13:48:12 bostic 9 8
c first pass for new make
e
s 00002/00001/00044
d D 1.8 90/02/20 11:32:34 bostic 8 7
c yyfix commands are different in the new yacc
e
s 00002/00002/00043
d D 1.7 89/05/10 20:58:41 bostic 7 6
c file system reorg
e
s 00008/00019/00037
d D 1.6 89/03/06 08:44:13 bostic 6 5
c cleanup, add cleandir
e
s 00045/00017/00011
d D 1.5 87/06/06 14:31:47 bostic 5 4
c new template
e
s 00002/00000/00026
d D 1.4 87/05/30 14:18:10 bostic 4 3
c added depend label
e
s 00003/00002/00023
d D 1.3 86/10/15 21:12:12 sam 3 2
c mv :yyfix
e
s 00002/00003/00023
d D 1.2 83/07/02 23:31:27 sam 2 1
c no need for -Dvax
e
s 00026/00000/00000
d D 1.1 82/08/30 10:04:13 rrh 1 0
c date and time created 82/08/30 10:04:13 by rrh
e
u
U
t
T
I 2
D 5
#	%M%	%I%	%E%
E 5
E 2
I 1
D 9
#
D 2
# %Z%%M% %I% %G%
#
E 2
D 5

D 2
CFLAGS=-O -Dunix=1 -Dvax=1 -DFLEXNAMES
E 2
I 2
D 3
CFLAGS=-O -Dunix=1 -DFLEXNAMES
E 3
I 3
YYFIX=	../pcc/pcc.`machine`/:yyfix
E 5
I 5
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
E 5
CFLAGS=	-O -Dunix=1 -DFLEXNAMES
I 5
LIBC=	/lib/libc.a
D 7
YYFIX=	../pcc/pcc.${MACHINE}/:yyfix
E 7
I 7
YYFIX=	../../libexec/pcc/pcc.${MACHINE}/:yyfix
E 7
SRCS=	cpp.c cpy.c rodata.c
OBJS=	cpp.o cpy.o rodata.o
E 9
I 9
#	%W% (Berkeley) %G%
E 9
E 5
E 3
E 2

D 5
cpp :	cpp.o cpy.o rodata.o
	$(CC) $(CFLAGS) -o cpp rodata.o cpp.o cpy.o  
E 5
I 5
D 9
all: cpp
E 9
I 9
PROG=	cpp
CFLAGS+=-Dunix=1 -DFLEXNAMES -I${.CURDIR}
D 10
YYFIX=	${.CURDIR}/../../libexec/pcc/pcc.${MACHINE}/:yyfix
E 10
SRCS=	cpp.c cpy.c rodata.o
D 10
CLEANFILES+=	cpy.c rodata.c
E 10
I 10
CLEANFILES+=cpy.c rodata.c
E 10
NOMAN=	noman
E 9
E 5

D 5
cpy.c : cpy.y
E 5
I 5
D 9
cpp:	${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 9
I 9
rodata.o: cpy.c
	${CC} ${CFLAGS} -R -c ${.PREFIX}.c
E 9

cpy.c: cpy.y
E 5
D 9
	yacc cpy.y
D 3
	../pcc/:yyfix yyexca yyact yypact yypgo yyr1 yyr2 yychk yydef
E 3
I 3
D 8
	${YYFIX} yyexca yyact yypact yypgo yyr1 yyr2 yychk yydef
E 8
I 8
	${YYFIX}  yylhs yylen yydefred yydgoto yysindex yyrindex \
E 9
I 9
	${YACC} ${.ALLSRC}
D 10
	${YYFIX} yylhs yylen yydefred yydgoto yysindex yyrindex \
E 9
	    yygindex yytable yycheck
E 10
I 10
	yyfix rodata.c
E 10
E 8
E 3
	mv y.tab.c cpy.c
D 5
cpy.o :	cpy.c yylex.c
rodata.o : cpy.c
	$(CC) $(CFLAGS) -R -c rodata.c
E 5

D 5
clean :
	rm -f *.s *.o cpy.c rodata.c
E 5
I 5
D 9
cpy.o: cpy.c yylex.c
E 5

D 5
install :
	install -s cpp $(DESTDIR)/lib
E 5
I 5
rodata.o: cpy.c
	${CC} ${CFLAGS} -R -c rodata.c
E 5

I 4
D 5
depend :
E 5
I 5
D 6
clean: FRC
E 6
I 6
clean:
E 6
	rm -f ${OBJS} cpp core cpy.c rodata.c
E 5

E 4
D 5
sources : cpp.c cpy.y yylex.c README
cpp.c cpy.y yylex.c README :
	sccs get $@
E 5
I 5
D 6
depend: ${SRCS} FRC
E 6
I 6
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 6
	mkdep ${CFLAGS} ${SRCS}

D 6
install: FRC
E 6
I 6
install: ${MAN}
E 6
D 7
	install -s -o bin -g bin -m 755 cpp ${DESTDIR}/lib/cpp
E 7
I 7
	install -s -o bin -g bin -m 755 cpp ${DESTDIR}/usr/bin
E 7

D 6
lint: ${SRCS} FRC
E 6
I 6
lint: ${SRCS}
E 6
	lint ${CFLAGS} ${SRCS}

D 6
tags: ${SRCS} FRC
E 6
I 6
tags: ${SRCS}
E 6
	ctags ${SRCS}
E 9
I 9
.include <bsd.prog.mk>
E 9
D 6

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

cpp.o: cpp.c /usr/include/sys/param.h /usr/include/sys/types.h
cpp.o: /usr/include/signal.h /usr/include/machine/machparam.h
cpp.o: /usr/include/stdio.h /usr/include/ctype.h
cpy.o: cpy.c
cpy.o:yylex.c
rodata.o: rodata.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 5
E 1
