h57098
s 00008/00043/00004
d D 1.3 90/06/30 15:02:36 bostic 3 2
c new doc makefiles
e
s 00010/00006/00037
d D 1.2 86/04/15 13:42:52 mckusick 2 1
c from mis
e
s 00043/00000/00000
d D 1.1 83/02/11 12:34:37 rrh 1 0
c date and time created 83/02/11 12:34:37 by rrh
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1983 Regents of the University of California
#
E 3
#	%W%	(Berkeley)	%G%
D 3
#
MAN = as.man.1
DOC = asdocs0.me asdocs1.me asdocs2.me asdocs3.me asdocs4.me
#
# Change these to change the way the document is printed out;
# the document is written using -me, which always must be present
#
D 2
FMT = vtroff -me
FMTOPTIONS = -t
E 2
I 2
FMT = ditroff
PKG = -me
PRINTER = -Pdp
# FMTOPTIONS = -t
FMTOPTIONS =
E 2
FMTDST = docs.t.out
D 2

E 2
I 2
EQN = deqn
TBL = dtbl
E 2
all: sources fmt
E 3

D 3
clean:
	-rm *.TME $(FMTDST)
E 3
I 3
DIR=	ps1/05.as
SRCS=	asdocs0.me asdocs1.me asdocs2.me asdocs3.me asdocs4.me
EQNCH=	/usr/share/misc/eqnchar
MACROS=	-me
EXTRA=	as.man.1
E 3

D 3
srcs: sources
sources:  $(DOC) $(MAN)
$(DOC) $(MAN):
	sccs get $@
#
# Constructing the assembler documentation:
#	assembler reference manual
#	assembler manual page
#
.SUFFIXES: .me .TME .tbl
E 3
I 3
paper.${PRINTER}: ${SRCS}
	(cat ${EQNCH}; ${SOELIM} ${SRCS} | ${TBL}) | ${EQN} > ${.TARGET}
E 3

D 3
DOCS = asdocs0.me asdocs1.TME asdocs2.TME asdocs3.TME asdocs4.TME

docs.raw: $(DOCS)

fmt: $(DOCS)
D 2
	cat $(DOCS) | $(FMT) $(FMTOPTIONS) > $(FMTDST)
E 2
I 2
	cat $(DOCS) | $(FMT) $(FMTOPTIONS) $(PKG) $(PRINTER)
E 2
	-rm *.TME

.me.TME:
D 2
	soelim $*.me | tbl > $*.tmp
	eqn /usr/pub/eqnchar $*.tmp > $*.TME
E 2
I 2
	soelim $*.me | $(TBL) $(PRINTER) > $*.tmp
	$(EQN) $(PRINTER) /usr/pub/eqnchar $*.tmp > $*.TME
E 2
	rm $*.tmp
E 3
I 3
.include <bsd.doc.mk>
E 3
E 1
