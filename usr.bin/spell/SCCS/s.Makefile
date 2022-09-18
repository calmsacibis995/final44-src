h61957
s 00000/00000/00062
d D 8.1 93/06/06 16:24:57 bostic 18 17
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00060
d D 4.16 92/07/19 18:38:35 bostic 17 16
c add american, british, stop to the install list
e
s 00002/00001/00059
d D 4.15 92/02/16 01:53:44 torek 16 15
c rebuild .depend only when necessary
e
s 00003/00001/00057
d D 4.14 90/06/24 12:59:41 bostic 15 14
c move spellin, spellout to /usr/bin
e
s 00004/00009/00054
d D 4.13 90/06/22 19:02:34 bostic 14 13
c some file rearrangement
e
s 00040/00055/00023
d D 4.12 90/05/11 14:13:33 bostic 13 12
c first pass for new make
e
s 00012/00016/00066
d D 4.11 89/05/11 13:39:11 bostic 12 11
c file reorg, pathnames.h, paths.h
e
s 00012/00024/00066
d D 4.10 88/10/25 15:16:24 bostic 11 10
c add manual page, cleanup
e
s 00001/00001/00089
d D 4.9 87/10/07 09:34:29 bostic 10 9
c fix mkdir line
e
s 00077/00042/00013
d D 4.8 87/06/18 23:33:31 bostic 9 7
c new template
e
s 00002/00000/00053
d D 4.7 87/05/31 21:32:31 bostic 7 6
c added depend label
e
s 00016/00011/00037
d D 4.6 87/03/16 14:21:37 mckusick 6 5
c Add second set of local files for George Bergman
e
s 00010/00010/00038
d D 4.5 87/03/12 12:22:22 mckusick 5 4
c set modes correctly!
e
s 00021/00006/00027
d D 4.4 87/03/12 12:08:05 mckusick 4 3
c update for new file names and installation
e
s 00001/00001/00032
d D 4.3 83/05/25 14:12:46 ralph 3 2
c fixed clean entry
e
s 00008/00006/00025
d D 4.2 83/02/14 13:53:40 shannon 2 1
c don't strip programs until installed
e
s 00031/00000/00000
d D 4.1 82/12/18 15:10:36 sam 1 0
c date and time created 82/12/18 15:10:36 by sam
e
u
U
t
T
I 1
D 9
#	%W%	%G%

E 9
I 9
D 13
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
E 9
I 4
D 6
# The word lists may be extended by adding local words.
E 6
I 6
# The word lists may be extended by adding special words.
E 6
# The set of files containing words to be added are defined
D 6
# by LOCAL below. By default we add commands and library
# function names defined in /usr/man/man[1238n].
E 6
I 6
D 9
# by SPECIAL below. By default we add commands and library
# function names defined in /usr/man/man[1238n]. The word
# lists also may be extended by adding local words. The set
E 9
I 9
# by SPECIAL below.  By default we add commands and library
# function names defined in /usr/man/man[1238n].  The word
# lists also may be extended by adding local words.  The set
E 9
# of files containing words to be added are defined by LOCAL
D 9
# below. Typically these lists reside in /usr/local/dict.
E 9
I 9
# below.  Typically these lists reside in /usr/local/dict.
E 13
I 13
#	%W% (Berkeley) %G%
E 13
E 9
E 6

D 6
LOCAL=special.4bsd
E 6
I 6
D 9
SPECIAL=special.4bsd
LOCAL=
E 9
I 9
D 13
SPECIAL=	special.4bsd
E 9
E 6

E 4
I 2
D 9
CFLAGS= -O
E 9
I 9
CFLAGS=	-O
LIBC=	/lib/libc.a
E 13
I 13
LIBC=	/usr/lib/libc.a
E 13
SRCS=	spell.c spellin.c spellout.c
D 13
OBJS=	spell.o spellin.o spellout.o
I 11
MAN=	spell.0
E 13
I 13
MAN1=	spell.0
MLINKS=	spell.1 spellin.1 spell.1 spellout.1
SPECIAL=${.CURDIR}/special.4bsd
E 13
E 11
E 9

E 2
D 9
all:	spell hlist hlista hlistb hstop spellin spellout
E 9
I 9
D 13
all: spell hlist hlista hlistb hstop spellin spellout
E 13
I 13
all: spell hlist hlista hlistb hstop spellin spellout ${MAN1}
E 13
E 9

D 9
install:	all
	install -s spell $(DESTDIR)/usr/lib
	install -s spellin ${DESTDIR}/usr/bin
	install -s spellout ${DESTDIR}/usr/bin
I 4
	install -c spell.sh $(DESTDIR)/usr/bin/spell
E 4
D 5
	install -c hlista $(DESTDIR)/usr/dict
	install -c hlistb $(DESTDIR)/usr/dict
	install -c hstop $(DESTDIR)/usr/dict
D 4
	install -c spell.sh $(DESTDIR)/usr/bin/spell
E 4
I 4
	install -c words $(DESTDIR)/usr/dict
	install -c american $(DESTDIR)/usr/dict
	install -c british $(DESTDIR)/usr/dict
	install -c stop $(DESTDIR)/usr/dict
	install -c README $(DESTDIR)/usr/dict
E 5
I 5
D 6
	install -m 444 -c hlista $(DESTDIR)/usr/dict
	install -m 444 -c hlistb $(DESTDIR)/usr/dict
	install -m 444 -c hstop $(DESTDIR)/usr/dict
E 6
I 6
	install -m 444 hlista $(DESTDIR)/usr/dict
	install -m 444 hlistb $(DESTDIR)/usr/dict
	install -m 444 hstop $(DESTDIR)/usr/dict
	install -m 444 hlist $(DESTDIR)/usr/dict
E 6
	install -m 444 -c words $(DESTDIR)/usr/dict
	install -m 444 -c american $(DESTDIR)/usr/dict
	install -m 444 -c british $(DESTDIR)/usr/dict
	install -m 444 -c stop $(DESTDIR)/usr/dict
	install -m 444 -c README $(DESTDIR)/usr/dict
E 5
	-mkdir $(DESTDIR)/usr/dict/special
D 5
	install -c special.4bsd $(DESTDIR)/usr/dict/special/4bsd
	install -c special.math $(DESTDIR)/usr/dict/special/math
E 5
I 5
	install -m 444 -c special.4bsd $(DESTDIR)/usr/dict/special/4bsd
	install -m 444 -c special.math $(DESTDIR)/usr/dict/special/math
E 9
I 9
D 11
spell: spell.c
	${CC} ${CFLAGS} spell.c -o $@
E 11
I 11
spell spellin spellout: ${LIBC}
D 13
	${CC} ${CFLAGS} $@.c -o $@
E 13
I 13
	${CC} ${CFLAGS} ${.CURDIR}/${.PREFIX}.c -o ${.TARGET}
E 13
E 11
E 9
E 5
E 4

D 9
clean:	
D 3
	rm -f spell spellin hlista hlistb hlist hstop spellout
E 3
I 3
	rm -f *.o spell spellin hlista hlistb hlist hstop spellout
E 9
I 9
D 11
spellin: spellin.c
	${CC} ${CFLAGS} spellin.c -o $@
E 9
E 3

D 2
spell: spell.c
	cc -s -O spell.c -o spell
spellin: spellin.c
	cc -O -s spellin.c -o spellin
spellout: spellout.c
	cc -O -s spellout.c -o spellout
E 2
I 2
D 9
spell: spell.o
	cc spell.o -o spell
spellin: spellin.o
	cc spellin.o -o spellin
spellout: spellout.o
	cc spellout.o -o spellout
E 9
I 9
spellout: spellout.c
	${CC} ${CFLAGS} spellout.c -o $@
E 9
E 2

E 11
D 12
hlist: /usr/dict/words spellin
E 12
I 12
hlist: spellin
E 12
D 4
	spellin </usr/dict/words >hlist
hlista: american local hlist spellin
	(cat american local)|spellin hlist >hlista
hlistb: british local hlist spellin
	(cat british local)|spellin hlist >hlistb
E 4
I 4
D 9
	spellin <words >hlist
D 6
hlista: american $(LOCAL) hlist spellin
	(cat american $(LOCAL))|spellin hlist >hlista
hlistb: british $(LOCAL) hlist spellin
	(cat british $(LOCAL))|spellin hlist >hlistb
E 6
I 6
hlista: american $(SPECIAL) $(LOCAL) hlist spellin
	(cat american $(SPECIAL) $(LOCAL))|spellin hlist >hlista
hlistb: british $(SPECIAL) $(LOCAL) hlist spellin
	(cat british $(SPECIAL) $(LOCAL))|spellin hlist >hlistb
E 9
I 9
D 13
	spellin < words >hlist
E 13
I 13
D 14
	spellin < ${.CURDIR}/words > hlist
E 14
I 14
	spellin < /usr/share/dict/words > hlist
E 14
E 13

D 13
hlista: american ${SPECIAL} ${LOCAL} hlist spellin
	(cat american ${SPECIAL} ${LOCAL}) | spellin hlist > hlista
E 13
I 13
hlista: american ${SPECIAL} hlist spellin
	(cat ${.CURDIR}/american ${SPECIAL}) | spellin hlist > hlista
E 13

D 13
hlistb: british ${SPECIAL} ${LOCAL} hlist spellin
	(cat british ${SPECIAL} ${LOCAL}) | spellin hlist > hlistb
E 13
I 13
hlistb: british ${SPECIAL} hlist spellin
	(cat ${.CURDIR}/british ${SPECIAL}) | spellin hlist > hlistb
E 13

E 9
E 6
E 4
hstop: stop spellin
D 9
	spellin <stop >hstop
E 9
I 9
D 13
	spellin < stop >hstop
E 13
I 13
	spellin < ${.CURDIR}/stop > hstop
E 13
E 9
I 7

D 9
depend:
E 9
I 9
D 11
clean: FRC
E 11
I 11
clean:
E 11
D 13
	rm -f ${OBJS} core spell spellin hlista hlistb hlist hstop spellout
E 13
I 13
	rm -f a.out Errs errs mklog core spell spellin hlista \
	    hlistb hlist hstop spellout
E 13

D 11
depend: FRC
E 11
I 11
cleandir: clean
D 13
	rm -f ${MAN} tags .depend
E 13
I 13
	rm -f ${MAN1} ${.CURDIR}/tags .depend
E 13

D 16
depend: ${SRCS}
E 16
I 16
depend: .depend
.depend: ${SRCS}
E 16
E 11
D 13
	mkdep -p ${CFLAGS} ${SRCS}
E 13
I 13
	mkdep -p ${CFLAGS:M-[ID]*} ${.ALLSRC}
E 13

I 12
DIR=	${DESTDIR}/usr/share/dict
D 13
FILES=	hlista hlistb hstop hlist american british connectives \
	propernames stop README words web2 web2a
E 12
D 11
install: FRC
E 11
I 11
install: ${MAN}
E 11
D 10
	-mkdir ${DESTDIR}/usr/dict/special > /dev/null 2>&1
E 10
I 10
D 12
	-[ -d ${DESTDIR}/usr/dict/special ] || mkdir ${DESTDIR}/usr/dict/special
E 10
	install -s -o bin -g bin -m 755 spell ${DESTDIR}/usr/lib/spell
	install -s -o bin -g bin -m 755 spellin ${DESTDIR}/usr/bin/spellin
	install -s -o bin -g bin -m 755 spellout ${DESTDIR}/usr/bin/spellout
E 12
I 12
	-[ -d ${DIR}/special ] || mkdir ${DIR}/special
	install -s -o bin -g bin -m 755 spell ${DESTDIR}/usr/libexec/spell
	install -s -o bin -g bin -m 755 spellin ${DESTDIR}/usr/libexec/spellin
	install -s -o bin -g bin -m 755 spellout ${DESTDIR}/usr/libexec/spellout
E 12
	install -c -o bin -g bin -m 755 spell.sh ${DESTDIR}/usr/bin/spell
D 12
	install -o bin -g bin -m 444 hlista ${DESTDIR}/usr/dict/hlista
	install -o bin -g bin -m 444 hlistb ${DESTDIR}/usr/dict/hlistb
	install -o bin -g bin -m 444 hstop ${DESTDIR}/usr/dict/hstop
	install -o bin -g bin -m 444 hlist ${DESTDIR}/usr/dict/hlist
	install -c -o bin -g bin -m 444 words ${DESTDIR}/usr/dict/words
	install -c -o bin -g bin -m 444 american ${DESTDIR}/usr/dict/american
	install -c -o bin -g bin -m 444 british ${DESTDIR}/usr/dict/british
	install -c -o bin -g bin -m 444 stop ${DESTDIR}/usr/dict/stop
	install -c -o bin -g bin -m 444 README ${DESTDIR}/usr/dict/README
	install -c -o bin -g bin -m 444 special.4bsd ${DESTDIR}/usr/dict/special/4bsd
	install -c -o bin -g bin -m 444 special.math ${DESTDIR}/usr/dict/special/math
E 12
I 12
	install -c -o bin -g bin -m 444 ${FILES} ${DIR}
	install -c -o bin -g bin -m 444 special.4bsd ${DIR}/special/4bsd
	install -c -o bin -g bin -m 444 special.math ${DIR}/special/math
E 12
I 11
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
I 12
	cp -p -r papers ${DIR}; chmod 755 ${DIR}/papers/runinv
E 12
	rm -f ${DESTDIR}/usr/man/cat1/spellin.0
	rm -f ${DESTDIR}/usr/man/cat1/spellout.0
	ln ${DESTDIR}/usr/man/cat1/spell.0 ${DESTDIR}/usr/man/cat1/spellin.0
	ln ${DESTDIR}/usr/man/cat1/spell.0 ${DESTDIR}/usr/man/cat1/spellout.0
E 13
I 13
D 14
FILES1=	hlist hlista hlistb hstop
FILES2=american british connectives propernames stop README words web2 web2a
E 14
I 14
D 17
FILES=	hlist hlista hlistb hstop
E 17
I 17
FILES=	${.CURDIR}/american ${.CURDIR}/british hlist hlista hlistb hstop \
	${.CURDIR}/stop
E 17
E 14
E 13
E 11

I 13
install: maninstall
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
D 15
	    spell spellin spellout ${DESTDIR}/usr/libexec
E 15
I 15
	    spellin spellout ${DESTDIR}/usr/bin
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    spell ${DESTDIR}/usr/libexec
E 15
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/spell.sh ${DESTDIR}/usr/bin/spell
D 14
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES1} ${DIR}
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${FILES2} ${DIR}
E 14
I 14
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} ${DIR}
E 14
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/special.4bsd \
	    ${DIR}/special/4bsd
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/special.math \
	    ${DIR}/special/math
D 14
	cp -p -r ${.CURDIR}/papers ${DIR}
E 14

E 13
D 11
lint: FRC
E 11
I 11
lint: ${SRCS}
E 11
D 13
	lint ${CFLAGS} spell.c
	lint ${CFLAGS} spellin.c
	lint ${CFLAGS} spellout.c
E 13
I 13
	cd ${.CURDIR}; ${LINT} ${LINTFLAGS} ${CFLAGS} spell.c
	cd ${.CURDIR}; ${LINT} ${LINTFLAGS} ${CFLAGS} spellin.c
	cd ${.CURDIR}; ${LINT} ${LINTFLAGS} ${CFLAGS} spellout.c
E 13

D 11
tags: FRC
E 11
I 11
tags: ${SRCS}
E 11
D 13
	ctags spell.c
	ctags -a spellin.c
	ctags -a spellout.c
	sort -o tags tags
E 13
I 13
	cd ${.CURDIR}; ctags ${SRCS}

D 14
.include <bsd.own.mk>
.include <bsd.man.mk>
E 14
I 14
.include <bsd.prog.mk>
E 14
E 13
D 11

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

spell: spell.c spell.h /usr/include/stdio.h /usr/include/ctype.h
spellin: spellin.c spell.h /usr/include/stdio.h /usr/include/ctype.h
spellout: spellout.c spell.h /usr/include/stdio.h /usr/include/ctype.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 11
E 9
E 7
E 1
