h52326
s 00004/00001/00059
d D 1.5 88/03/04 17:04:58 jaap 5 4
c cleaning up
e
s 00002/00002/00058
d D 1.4 87/04/01 16:36:34 jaap 4 3
c cleanup
e
s 00001/00001/00059
d D 1.3 87/04/01 15:49:48 jaap 3 2
c Just checking in
e
s 00002/00002/00058
d D 1.2 85/03/03 22:39:06 jaap 2 1
c Removed errors, added Versatec support (jaap).
e
s 00060/00000/00000
d D 1.1 85/03/01 17:19:59 jaap 1 0
c date and time created 85/03/01 17:19:59 by jaap
e
u
U
t
T
I 1
#
D 2
#	%M%	(CWI)	%I%	%E%
E 2
I 2
#	Makefile	(CWI)	1.1	85/03/01
E 2
#
# BINDIR is the place where ideal will be installed
BINDIR = /usr/local
# DESTDIR is the destination where we want to move the thing (temporarily)
DESTDIR =
# LIBDIR is the place where we expect the the things we need and is
# is therefore hardwired in. Since it is all local, we use BINDIR as well
D 3
LIBDIR = ${BINDIR}/lib/ideal/lib
E 3
I 3
LIBDIR = ${BINDIR}/lib/ideal/lib/
E 3
CFLAGS = -O -DLIBDIR=\"${LIBDIR}\"

SOURCES = ideal.h ideal.c util.c memut.c bldds.c simul.c exprn.c\
	action.c piece.c opaque.c inter.c opqpoly.c idlex.l idyac.y
OBJECTS = y.tab.o lex.yy.o ideal.o util.o memut.o bldds.o simul.o\
	exprn.o action.o piece.o opaque.o opqpoly.o inter.o
ADMIXTURE = y.tab.c lex.yy.c ideal.c util.c memut.c bldds.c simul.c\
	exprn.c action.c piece.c opaque.c opqpoly.c inter.c

SUBDIR = idfilt lib

all: ideal ideal.sh ${SUBDIR}

${SUBDIR}: /tmp
D 4
	cd $@; make ${MFLAGS}
E 4
I 4
	cd $@; make ${MFLAGS} DESTDIR=${DESTDIR}
E 4

# ideal is a shell file. It needs to know where it can find the real binary
ideal.sh: ideal.cmd
D 2
	sed "s#IDDIR=.*#IDLIB= ${DESTDIR}${LIBDIR}#" < ideal.cmd > ideal.sh
E 2
I 2
D 4
	sed "s#IDDIR=.*#IDDIR=${DESTDIR}${LIBDIR}#" < ideal.cmd > ideal.sh
E 4
I 4
	sed "s#IDDIR=.*#IDDIR=${LIBDIR}#" < ideal.cmd > ideal.sh
E 4
E 2

ideal:	$(OBJECTS)
	cc -o ideal $(OBJECTS) -ll -lm

$(OBJECTS):	ideal.h

ideal.h:	stdas.h

lex.yy.c:	idlex.l
	lex idlex.l

y.tab.c:	idyac.y
	yacc -d idyac.y

D 5
install: all
E 5
I 5
install: all $(LIBDIR)
E 5
	install -s ideal ${DESTDIR}/${LIBDIR}/ideal
	install -m 755 ideal.sh ${DESTDIR}/${BINDIR}/ideal
	install -c -m 644 ideal.1 ${DESTDIR}/usr/man/manl/ideal.1
	cd idfilt; make DESTDIR=${DESTDIR} install
	cd lib; make DESTDIR=${DESTDIR} install

I 5
$(LIBDIR):
	mkdir ${BINDIR}/lib/ideal
	mkdir${BINDIR}/lib/ideal/lib
E 5
list:
	pr $(SOURCES)

lint:
	lint $(ADMIXTURE) -lm

clean:
	rm -f *.o y.tab.c lex.yy.c y.tab.h
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done

E 1
