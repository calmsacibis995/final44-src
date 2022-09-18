h15079
s 00000/00000/00080
d D 8.1 93/06/06 16:53:51 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00004/00076
d D 5.2 93/05/15 23:57:37 torek 3 1
c make it work when repeated
e
s 00004/00004/00076
d R 5.2 93/05/15 22:27:51 torek 2 1
c make it work when repeated
e
s 00080/00000/00000
d D 5.1 93/05/11 10:05:10 bostic 1 0
c date and time created 93/05/11 10:05:10 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	tn3270
CFLAGS+=-I${.CURDIR} -I.
LDADD+=	-lcurses -ltermcap -ltelnet
DPADD+=	${LIBCURSES} /usr/lib/libtermcap.a /usr/lib/libtelnet.a
CLEANFILES+= asc_disp.OUT asc_disp.out disp_asc.OUT disp_asc.out TMPfunc.out
.PATH:	${.CURDIR}/../api ${.CURDIR}/../ascii ${.CURDIR}/../ctlr
.PATH:	${.CURDIR}/../general ${.CURDIR}/../sys_curses ${.CURDIR}/../../telnet

MAN1=	tn3270.0

SRCS+=	apilib.c api_bsd.c api_exch.c asc_ebc.c astosc.c dctype.c
SRCS+=	disp_asc.c ebc_disp.c
SRCS+=	map3270.c termin.c
SRCS+=	api.c function.c inbound.c oia.c options.c outbound.c
SRCS+=	genbsubs.c globals.c system.c termout.c
SRCS+=	commands.c main.c network.c ring.c sys_bsd.c telnet.c terminal.c
SRCS+=	tn3270.c utilities.c

# This and the dependency hacks below to make 'depend' target
# work right...

DEPSRCS+= astosc.OUT asc_disp.OUT disp_asc.OUT kbd.OUT
DEPSRCS+= apilib.c api_bsd.c api_exch.c asc_ebc.c dctype.c
DEPSRCS+= ebc_disp.c
DEPSRCS+= map3270.c termin.c
DEPSRCS+= api.c function.c inbound.c oia.c options.c outbound.c
DEPSRCS+= genbsubs.c globals.c system.c termout.c
DEPSRCS+= commands.c main.c network.c ring.c sys_bsd.c telnet.c terminal.c
DEPSRCS+= tn3270.c utilities.c

astosc.o: astosc.OUT
CLEANFILES+= astosc.OUT astosc.out
astosc.OUT: ${.CURDIR}/../ctlr/hostctlr.h ${.CURDIR}/../ctlr/function.h
astosc.OUT: ${.CURDIR}/../ctlr/${KBD} ${.CURDIR}/../tools/mkastosc/obj/mkastosc
	${.CURDIR}/../tools/mkastosc/obj/mkastosc \
	    ${.CURDIR}/../ctlr/hostctlr.h \
	    ${.CURDIR}/../ctlr/function.h < ${.CURDIR}/../ctlr/${KBD} \
	    > ${.TARGET}
D 3
	ln -s astosc.OUT astosc.out
E 3
I 3
	rm -f astosc.out; ln -s astosc.OUT astosc.out
E 3

disp_asc.o: asc_disp.OUT disp_asc.OUT
asc_disp.OUT: ${.CURDIR}/../tools/mkastods/obj/mkastods
	${.CURDIR}/../tools/mkastods/obj/mkastods > ${.TARGET}
D 3
	ln -s asc_disp.OUT asc_disp.out
E 3
I 3
	rm -f asc_disp.out; ln -s asc_disp.OUT asc_disp.out
E 3

disp_asc.OUT: ${.CURDIR}/../tools/mkdstoas/obj/mkdstoas
	${.CURDIR}/../tools/mkdstoas/obj/mkdstoas > ${.TARGET}
D 3
	ln -s disp_asc.OUT disp_asc.out
E 3
I 3
	rm -f disp_asc.out; ln -s disp_asc.OUT disp_asc.out
E 3

inbound.o: kbd.OUT
CLEANFILES += kbd.OUT kbd.out
kbd.OUT: ${.CURDIR}/../ctlr/hostctlr.h ${.CURDIR}/../ctlr/${KBD}
kbd.OUT: ${.CURDIR}/../tools/mkhits/obj/mkhits
	${CC} ${CFLAGS} -E ${.CURDIR}/../ctlr/function.c > TMPfunc.out
	${.CURDIR}/../tools/mkhits/obj/mkhits ${.CURDIR}/../ctlr/hostctlr.h \
	    TMPfunc.out < ${.CURDIR}/../ctlr/${KBD} > ${.TARGET}
D 3
	ln -s kbd.OUT kbd.out
E 3
I 3
	rm -f kbd.out; ln -s kbd.OUT kbd.out
E 3

# astosc.out
# asc_disp.out disp_asc.out
# default.map
# kbd.out

${.CURDIR}/../tools/mkastosc/obj/mkastosc:
	cd ${.CURDIR}/../tools/mkastosc; make
${.CURDIR}/../tools/mkastods/obj/mkastods:
	cd ${.CURDIR}/../tools/mkastods; make
${.CURDIR}/../tools/mkdstoas/obj/mkdstoas:
	cd ${.CURDIR}/../tools/mkdstoas; make
${.CURDIR}/../tools/mkhits/obj/mkhits:
	cd ${.CURDIR}/../tools/mkhits; make

depend: .depend
.depend: ${DEPSRCS}
	mkdep ${MKDEP} ${CFLAGS:M-[ID]*} ${.ALLSRC:M*.c}

.include <../../Makefile.inc>
.include <bsd.prog.mk>
E 1
