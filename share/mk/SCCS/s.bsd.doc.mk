h26255
s 00000/00000/00053
d D 8.1 93/08/14 10:01:55 mckusick 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00000/00048
d D 5.11 93/08/03 10:40:41 elan 12 10
c Added 'all' target for subdir makes.
e
s 00000/00000/00048
d R 8.1 93/06/08 11:35:44 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00047
d D 5.10 93/06/05 16:30:22 bostic 10 9
c search groff's tmac directory first
e
s 00001/00001/00047
d D 5.9 93/06/05 13:13:20 bostic 9 8
c look in /usr/old/lib/tmac first
e
s 00005/00000/00043
d D 5.8 93/06/05 12:56:24 bostic 8 7
c add a paper.ps target -- the default 4.4BSD postscript target
e
s 00006/00008/00037
d D 5.7 93/02/27 10:31:33 bostic 7 6
c hack it up, still doesn't work
e
s 00001/00001/00044
d D 5.6 92/11/12 14:54:03 mckusick 6 5
c pic takes no arguments
e
s 00004/00000/00041
d D 5.5 91/11/12 10:47:41 bostic 5 4
c put in obj: stub
e
s 00004/00000/00037
d D 5.4 91/08/07 16:33:20 bostic 4 3
c add manpages
e
s 00003/00003/00034
d D 5.3 91/01/02 22:26:18 karels 3 2
c a bit less CSRG-specific: use "psc" as printer type, ditroff vs. psroff
e
s 00030/00015/00007
d D 5.2 90/06/30 15:13:50 bostic 2 1
c first cut at doc include 
e
s 00022/00000/00000
d D 5.1 90/06/25 16:20:46 bostic 1 0
c date and time created 90/06/25 16:20:46 by bostic
e
u
U
t
T
I 2
#	%W% (Berkeley) %G%
E 2
I 1

D 2
BINDIR=	/usr/share/doc
E 2
I 2
D 3
PRINTER=lz
E 3
I 3
D 7
PRINTER=psc
E 3
E 2

E 7
D 2
MANGRP?=	bin
MANOWN?=	bin
MANMODE?=	444
E 2
I 2
BIB?=		bib
D 3
EQN?=		/usr/local/deqn -P${PRINTER}
E 3
I 3
D 7
EQN?=		deqn -P${PRINTER}
E 3
GREMLIN?=	grn -P${PRINTER}
E 7
I 7
EQN?=		eqn
GREMLIN?=	grn
E 7
GRIND?=		vgrind -f
INDXBIB?=	indxbib
D 6
PIC?=		pic -P${PRINTER}
E 6
I 6
PIC?=		pic
E 6
REFER?=		refer
D 3
ROFF?=		psroff -t ${MACROS} ${PAGES} -P${PRINTER}
E 3
I 3
D 7
ROFF?=		ditroff -t ${MACROS} ${PAGES} -P${PRINTER}
E 7
I 7
D 9
ROFF?=		groff ${MACROS} ${PAGES}
E 9
I 9
D 10
ROFF?=		groff -M/usr/old/lib/tmac ${MACROS} ${PAGES}
E 10
I 10
ROFF?=		groff -M/usr/share/tmac -M/usr/old/lib/tmac ${MACROS} ${PAGES}
E 10
E 9
E 7
E 3
SOELIM?=	soelim
D 7
TBL?=		dtbl -P${PRINTER}
E 7
I 7
TBL?=		tbl
E 7
E 2

D 2
PRINTER=lz
ROFF=	ditroff -P${PRINTER}
TBL=	dtbl -P${PRINTER} ${PAGES}
E 2
I 2
.PATH: ${.CURDIR}
E 2

I 12
.if !target(all)
.MAIN: all
all: paper.ps
.endif

E 12
I 8
.if !target(paper.ps)
paper.ps: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
.endif

E 8
D 2
print:
.if defined(DOTBL)
	${TBL} |
	${ROFF} ${MACROS} -t ${SRCS} | psdit > paper.${PRINTER}
.else
	${ROFF} ${MACROS} -t ${SRCS} | psdit > paper.${PRINTER}
E 2
I 2
.if !target(print)
D 7
print: paper.${PRINTER}
	lpr -P${PRINTER} paper.${PRINTER}
E 7
I 7
print: paper.ps
	lpr -P${PRINTER} paper.ps
E 7
E 2
.endif

I 4
.if !target(manpages)
manpages:
.endif

I 5
.if !target(obj)
obj:
.endif

E 5
E 4
I 2
clean cleandir:
	rm -f paper.* [eE]rrs mklog ${CLEANFILES}

FILES?=	${SRCS}
E 2
install:
D 2
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} \
	    Makefile ${SRCS} ${EXTRA} ${DESTDIR}${BINDIR}/${DIR}
E 2
I 2
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    Makefile ${FILES} ${EXTRA} ${DESTDIR}${BINDIR}/${DIR}

spell: ${SRCS}
	spell ${SRCS} | sort | comm -23 - spell.ok > paper.spell

BINDIR?=	/usr/share/doc
BINGRP?=	bin
BINOWN?=	bin
BINMODE?=	444
E 2
E 1
