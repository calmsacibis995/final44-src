h57238
s 00003/00002/00008
d D 8.2 94/05/21 11:55:33 mckusick 5 4
c additional pointer for refer database
e
s 00000/00000/00010
d D 8.1 93/06/08 11:59:32 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 6.3 93/06/05 17:15:57 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00006/00037/00004
d D 6.2 90/06/30 15:07:01 bostic 2 1
c new doc makefiles
e
s 00041/00000/00000
d D 6.1 86/05/23 09:26:30 kjd 1 0
c date and time created 86/05/23 09:26:30 by kjd
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 2
#	%W% (Berkeley) %G%
D 2
#
DOCS = p0 p1 p2 p3 p4 p5 p6 p7
#
#
# Change these to change the way the document is printed out
#
FMT = ditroff
PKG = -msU
PRINTER = -Pdp
FMTOPTIONS =
TBL = dtbl
E 2

D 2
all: sources fmt
E 2
I 2
DIR=	usd/02.learn
SRCS=	p0 p1 p2 p3 p4 p5 p6 p7
D 5
MACROS=	-msU
E 5
I 5
MACROS=	-ms
E 5
E 2

D 2
clean:
	-rm $(FMTDST)
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS}
E 3
I 3
paper.ps: ${SRCS}
E 3
D 5
	${REFER} -p Refs -e ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 5
I 5
	${REFER} -p Refs -p /usr/old/dict/papers/Ind -e ${SRCS} | \
		${TBL} | ${ROFF} > ${.TARGET}
E 5
E 2

D 2
srcs: sources
sources:  $(DOCS)
$(DOCS):
	sccs get $@



docs.raw: $(DOCS)

fmt: $(DOCS)
	refer -p Refs -e $(DOCS) | $(TBL) $(PRINTER) | $(FMT) $(FMTOPTIONS) $(PKG) $(PRINTER)

aps: $(DOCS)
	refer -p Refs -e $(DOCS) | $(TBL) $(PRINTER) | $(FMT) $(FMTOPTIONS) $(PKG) $(PRINTER) | $(LPR)

indexable: $(DOCS)
	refer -p Refs -e $(DOCS) | $(TBL) $(PRINTER) | sed -f ../pre.sed | $(FMT) $(FMTOPTIONS) $(PKG) $(PRINTER) | sed -f ../post.sed >../learn.a

E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
