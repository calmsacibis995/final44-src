h31256
s 00000/00000/00034
d D 8.1 93/06/06 16:52:33 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00033
d D 5.2 93/05/16 00:19:25 torek 2 1
c make it work when run twice
e
s 00034/00000/00000
d D 5.1 93/05/11 10:04:18 bostic 1 0
c date and time created 93/05/11 10:04:18 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mset
CFLAGS+=-I${.CURDIR} -I.
SRCS+=	astosc.c map3270.c mset.c
MAN1=	mset.0
MAN5=	map3270.0
.PATH:	${.CURDIR}/../api ${.CURDIR}/../ascii

CLEANFILES+=	astosc.OUT astosc.out

# This and the dependency hacks below to make 'depend' target
# work right...

DEPSRCS+=	astosc.OUT map3270.c mset.c

astosc.o: astosc.OUT
astosc.OUT: ${.CURDIR}/../ctlr/hostctlr.h ${.CURDIR}/../ctlr/function.h
astosc.OUT: ${.CURDIR}/../ctlr/${KBD} ${.CURDIR}/../tools/mkastosc/obj/mkastosc
	${.CURDIR}/../tools/mkastosc/obj/mkastosc \
	    ${.CURDIR}/../ctlr/hostctlr.h ${.CURDIR}/../ctlr/function.h \
	    < ${.CURDIR}/../ctlr/${KBD} > ${.TARGET}
D 2
	ln -s astosc.OUT astosc.out
E 2
I 2
	rm -f astosc.out; ln -s astosc.OUT astosc.out
E 2

# astosc.out
${.CURDIR}/../tools/mkastosc/obj/mkastosc:
	cd ${.CURDIR}/../tools/mkastosc; make

depend:	.depend
.depend:${DEPSRCS}
	mkdep ${MKDEP} ${CFLAGS:M-[ID]*} ${.ALLSRC:M*.c}

.include <../../Makefile.inc>
.include <bsd.prog.mk>
E 1
