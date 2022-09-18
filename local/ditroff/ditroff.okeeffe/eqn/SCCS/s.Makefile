h02861
s 00008/00008/00021
d D 2.2 87/04/01 15:17:22 jaap 4 3
c Updates from bwk, see README for details
e
s 00007/00008/00022
d D 2.1 87/04/01 13:31:51 jaap 3 2
c saving it before munging it
e
s 00002/00002/00028
d D 1.2 85/03/12 01:24:05 jaap 2 1
c Changed DESTDIR to know about ..../.code
e
s 00030/00000/00000
d D 1.1 85/03/01 15:26:33 jaap 1 0
c date and time created 85/03/01 15:26:33 by jaap
e
u
U
t
T
I 1
D 3

E 3
#
#	%M%	(CWI)	%I%	%E%
#
D 3
CFLAGS= -O
E 3
I 3
D 4
CFLAGS=
E 4
I 4
CFLAGS= -O
E 4
E 3
YFLAGS= -d
DESTDIR=
D 2
BINDIR=/usr/local
E 2
I 2
D 3
BINDIR=/usr/local/.code
E 3
I 3
BINDIR=/usr/local
E 3
E 2
D 4
OBJECTS= diacrit.o eqnbox.o font.o fromto.o funny.o glob.o integral.o \
D 3
 io.o lex.o lookup.o mark.o matrix.o move.o over.o paren.o \
 pile.o shift.o size.o sqrt.o text.o e.o
E 3
I 3
 input.o main.o lex.o lookup.o mark.o matrix.o move.o over.o paren.o \
 pile.o shift.o size.o sqrt.o text.o eqn.o
E 4
I 4
OBJECTS= diacrit.o eqnbox.o font.o fromto.o funny.o glob.o input.o \
 integral.o lex.o lookup.o main.o mark.o matrix.o move.o over.o paren.o \
 pile.o shift.o size.o sqrt.o text.o eqn.o tuning.o
E 4
E 3

D 3
all:	dieqn
E 3
I 3
all:	dieqn ${FILES}
E 3

dieqn:	${OBJECTS}
D 3
	cc -n -o dieqn ${CFLAGS} ${OBJECTS}
E 3
I 3
	cc -o dieqn ${CFLAGS} ${OBJECTS}
E 3

D 3
y.tab.h:	e.o
E 3
I 3
y.tab.h:	eqn.o
E 3

D 4
e.def:	y.tab.h
	-cmp -s y.tab.h e.def || cp y.tab.h e.def
E 4
I 4
prevy.tab.h:	y.tab.h
	-cmp -s y.tab.h prevy.tab.h || cp y.tab.h prevy.tab.h
E 4

D 4
${OBJECTS}:	e.h e.def
E 4
I 4
${OBJECTS}:	e.h prevy.tab.h
E 4

install: all
D 2
	install -s dieqn ${DESTDIR}${BINNDIR}/dieqn
E 2
I 2
	install -s dieqn ${DESTDIR}${BINDIR}/dieqn
E 2
	install -c -m 644 dieqn.1 ${DESTDIR}/usr/man/manl/dieqn.1

clean:
D 4
	rm -f dieqn *.o make.out y.tab.h e.def
E 4
I 4
	rm -f dieqn *.o make.out y.tab.h prevy.tab.h
E 4
E 1
