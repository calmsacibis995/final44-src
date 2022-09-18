h56325
s 00000/00000/00026
d D 8.1 93/06/11 15:30:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00026/00000/00000
d D 5.1 91/05/03 18:56:47 bostic 1 0
c date and time created 91/05/03 18:56:47 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	route
SRCS=	route.c
CFLAGS+=-DLETS_GET_SMALL -I.
NOMAN=	noman
LDFLAGS=-N
CLEANFILES+=keywords.h
BINOWN=	root
BINMODE=4555
.PATH:	${.CURDIR}/../../../../sbin/route

all route depend lint tags: keywords.h

keywords.h: keywords
	sed -e '/^#/d' -e '/^$$/d' \
	    ${.CURDIR}/../../../../sbin/route/keywords > _keywords.tmp
	tr a-z A-Z < _keywords.tmp | paste _keywords.tmp - | \
	    awk '{ \
		if (NF > 1) \
			printf "#define\tK_%s\t%d\n\t{\"%s\", K_%s},\n", \
			    $$2, NR, $$1, $$2 }' \
	    > ${.TARGET}
	rm -f _keywords.tmp

.include <bsd.prog.mk>
E 1
