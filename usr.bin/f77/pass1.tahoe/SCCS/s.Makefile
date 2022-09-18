h55041
s 00018/00042/00008
d D 5.3 90/06/17 18:48:38 bostic 3 2
c pmake style make, reorg the directories
e
s 00009/00074/00041
d D 5.2 89/05/10 22:22:48 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00115/00000/00000
d D 5.1 87/12/12 17:40:43 bostic 1 0
c date and time created 87/12/12 17:40:43 by bostic
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
CFLAGS=	-O -DHERE=TAHOE -DTARGET=TAHOE -DFAMILY=PCC -DUCBVAXASM \
	-DUCBPASS2 -I$(INCLDIR)/usr/include -I../include
LIBC=	/lib/libc.a
SRCS=	bb.c conv.c data.c equiv.c error.c exec.c expr.c fmt.c gram.c init.c \
E 3
I 3
#	%W% (Berkeley) %G%

PROG=	f77pass1
CFLAGS+=-DHERE=TAHOE -DTARGET=TAHOE -DFAMILY=PCC -DUCBVAXASM -DUCBPASS2 \
	-I. -I${.CURDIR} -I${.CURDIR}/../include.tahoe
SRCS=	bb.c conv.c data.c equiv.c error.c exec.c expr.c fmt.c init.c \
E 3
	intr.c io.c lex.c main.c misc.c optcse.c optim.c optloop.c paramset.c \
	proc.c put.c putpcc.c regalloc.c setfmt.c stab.c tahoe.c tahoex.c
D 3
OBJS=	bb.o conv.o data.o equiv.o error.o exec.o expr.o fmt.o gram.o init.o \
	intr.o io.o lex.o main.o misc.o optcse.o optim.o optloop.o paramset.o \
	proc.o put.o putpcc.o regalloc.o setfmt.o stab.o tahoe.o tahoex.o
E 3
I 3
OBJS+=	gram.o
BINDIR=	/usr/libexec
NOMAN=	noman
CLEANFILES+=gram.c gram.in y.tab.c tokdefs.h
E 3

D 3
all: f77pass1

f77pass1: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}

gram.c:	gram.head gram.dcl gram.expr gram.exec gram.io tokdefs.h
	( sed <tokdefs.h "s/#define/%token/"; \
		cat gram.head gram.dcl gram.expr gram.exec gram.io ) >gram.in
E 3
I 3
gram.c: gram.head gram.dcl gram.expr gram.exec gram.io tokdefs.h
	(sed < tokdefs.h "s/#define/%token/"; cd ${.CURDIR}; \
	    cat gram.head gram.dcl gram.expr gram.exec gram.io) > gram.in
E 3
	${YACC} gram.in
	mv y.tab.c gram.c

D 3
gram.head: defs.h data.h
E 3
I 3
tokdefs.h: ${.CURDIR}/tokens
	(cd ${.CURDIR}; grep -n . < tokens | \
	    sed "s/\([^:]*\):\(.*\)/#define \2 \1/") > tokdefs.h
E 3

D 3
tokdefs.h: tokens
	grep -n . <tokens | sed "s/\([^:]*\):\(.*\)/#define \2 \1/" >tokdefs.h
E 3
I 3
.include <bsd.prog.mk>
E 3

D 2
clean: FRC
E 2
I 2
D 3
clean:
E 2
	rm -f ${OBJS} core f77pass1 gram.c gram.in

D 2
depend: ${SRCS} FRC
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 2
	mkdep ${CFLAGS} ${SRCS}

D 2
install: FRC
	install -s -o bin -g bin -m 755 f77pass1 ${DESTDIR}/usr/lib/f77pass1
E 2
I 2
install: ${MAN}
	install -s -o bin -g bin -m 755 f77pass1 ${DESTDIR}/usr/libexec
E 2

D 2
lint: ${SRCS} FRC
E 2
I 2
lint: ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: ${SRCS} FRC
E 2
I 2
tags: ${SRCS}
E 2
	ctags ${SRCS}
E 3
I 3
.depend: tokdefs.h
E 3
D 2

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

bb.o: bb.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
bb.o: ../include/defines.h ../include/machdefs.h optim.h
conv.o: conv.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
conv.o: ../include/defines.h ../include/machdefs.h conv.h
data.o: data.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
data.o: ../include/defines.h ../include/machdefs.h data.h
equiv.o: equiv.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
equiv.o: ../include/defines.h ../include/machdefs.h /usr/include/a.out.h
equiv.o: /usr/include/sys/exec.h /usr/include/stab.h
error.o: error.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
error.o: ../include/defines.h ../include/machdefs.h
exec.o: exec.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
exec.o: ../include/defines.h ../include/machdefs.h optim.h
expr.o: expr.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
expr.o: ../include/defines.h ../include/machdefs.h
fmt.o: fmt.c format.h
gram.o: gram.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
gram.o: ../include/defines.h ../include/machdefs.h data.h /usr/include/a.out.h
gram.o: /usr/include/sys/exec.h /usr/include/stab.h
init.o: init.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
init.o: ../include/defines.h ../include/machdefs.h io.h /usr/include/sys/file.h
intr.o: intr.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
intr.o: ../include/defines.h ../include/machdefs.h
io.o: io.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
io.o: ../include/defines.h ../include/machdefs.h io.h
lex.o: lex.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
lex.o: ../include/defines.h ../include/machdefs.h tokdefs.h
main.o: main.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
main.o: ../include/defines.h ../include/machdefs.h /usr/include/signal.h
main.o: /usr/include/machine/trap.h /usr/include/a.out.h
main.o: /usr/include/sys/exec.h /usr/include/stab.h
misc.o: misc.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
misc.o: ../include/defines.h ../include/machdefs.h
optcse.o: optcse.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
optcse.o: ../include/defines.h ../include/machdefs.h optim.h
optim.o: optim.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
optim.o: ../include/defines.h ../include/machdefs.h optim.h
optloop.o: optloop.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
optloop.o: ../include/defines.h ../include/machdefs.h optim.h
paramset.o: paramset.c defs.h /usr/include/stdio.h /usr/include/ctype.h
paramset.o: ftypes.h ../include/defines.h ../include/machdefs.h data.h
proc.o: proc.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
proc.o: ../include/defines.h ../include/machdefs.h /usr/include/a.out.h
proc.o: /usr/include/sys/exec.h /usr/include/stab.h
put.o: put.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
put.o: ../include/defines.h ../include/machdefs.h /usr/include/pcc.h
putpcc.o: putpcc.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
putpcc.o: ../include/defines.h ../include/machdefs.h /usr/include/pcc.h
regalloc.o: regalloc.c defs.h /usr/include/stdio.h /usr/include/ctype.h
regalloc.o: ftypes.h ../include/defines.h ../include/machdefs.h optim.h
setfmt.o: setfmt.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
setfmt.o: ../include/defines.h ../include/machdefs.h format.h
stab.o: stab.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
stab.o: ../include/defines.h ../include/machdefs.h /usr/include/sys/types.h
stab.o: /usr/include/a.out.h /usr/include/sys/exec.h /usr/include/stab.h
tahoe.o: tahoe.c defs.h /usr/include/stdio.h /usr/include/ctype.h ftypes.h
tahoe.o: ../include/defines.h ../include/machdefs.h /usr/include/a.out.h
tahoe.o: /usr/include/sys/exec.h /usr/include/stab.h /usr/include/pcc.h
tahoex.o: tahoex.c /usr/include/stdio.h ../include/defines.h
tahoex.o: ../include/machdefs.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
