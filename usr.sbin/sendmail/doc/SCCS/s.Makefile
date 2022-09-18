h20590
s 00001/00001/00004
d D 8.2 95/02/10 08:46:18 eric 8 7
c add changes to the list of subdirectories
e
s 00000/00000/00005
d D 8.1 93/06/07 10:18:58 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00013/00003
d D 5.3 93/06/01 21:04:15 eric 6 5
c new doc scheme
e
s 00009/00037/00007
d D 5.2 93/06/01 20:35:02 eric 5 4
c old changes
e
s 00011/00002/00033
d D 5.1 85/06/07 16:27:15 dist 4 3
c Add copyright
e
s 00000/00000/00035
d D 4.1 83/07/25 20:15:30 eric 3 2
c 4.2 release version
e
s 00007/00002/00028
d D 3.2 83/03/12 22:28:10 eric 2 1
c add usenix.me; be usable in /usr/doc/sendmail
e
s 00030/00000/00000
d D 3.1 83/03/12 22:22:54 eric 1 0
c date and time created 83/03/12 22:22:54 by eric
e
u
U
f b 
f i 
t
T
I 1
D 5
#
D 4
#	Makefile for sendmail documentation
E 4
I 4
#  Sendmail
#  Copyright (c) 1983  Eric P. Allman
#  Berkeley, California
E 4
#
D 4
#	%W%	%Y%	%G%
E 4
I 4
#  Copyright (c) 1983 Regents of the University of California.
#  All rights reserved.  The Berkeley software License Agreement
#  specifies the terms and conditions for redistribution.
#
E 5
#	%W% (Berkeley) %G%
D 5
#
#
#	Makefile for sendmail documentation
E 4
#
E 5

D 2
OBJS=	intro.lpr op.lpr
SRCS=	intro.me  op.me  sendmail.8 syslog.3 syslog.8
E 2
I 2
D 5
OBJS=	intro.lpr op.lpr usenix.lpr
DOCS=	intro.me  op.me  usenix.me
SRCS=	$(DOCS) sendmail.8 syslog.3 syslog.8
E 2
ALL=	$(OBJS) rfc819.lpr rfc821.lpr rfc822.lpr
E 5
I 5
D 6
ALL=	op.ps intro.ps usenix.ps
E 6
I 6
D 8
SUBDIR=	op intro usenix
E 8
I 8
SUBDIR=	op intro usenix changes
E 8
E 6
E 5

D 5
LPR=	lpr
I 2
TROFF=	vtroff
E 2
GET=	sccs get
E 5
I 5
D 6
all: ${ALL}
E 5

D 5
.SUFFIXES: .me .lpr
E 5
I 5
op.ps: op.me
	${PIC} op.me | ${EQN} | ${ROFF} -me > ${.TARGET}
E 5

D 5
.me.lpr:
	nroff -me -Tlp $< > $@
E 5
I 5
intro.ps: intro.me
	${PIC} intro.me | ${ROFF} -me > ${.TARGET}
E 5
I 2

D 5
troff: $(DOCS)
	for i in $(DOCS); do $(TROFF) -me $$i; done
E 5
I 5
usenix.ps: usenix.me
	${ROFF} -me usenix.me > ${.TARGET}
E 5
E 2

D 5
all: $(ALL)

print: $(ALL)
	$(LPR) $(ALL)

sources: $(SRCS)

$(SRCS):
	$(GET) $(REL) SCCS/s.$@

clean:
	rm -f $(OBJS) a.out core
E 5
I 5
.include <bsd.doc.mk>
E 6
I 6
.include <bsd.subdir.mk>
E 6
E 5
E 1
