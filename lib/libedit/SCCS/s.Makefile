h21111
s 00000/00000/00058
d D 8.1 93/06/04 16:50:52 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00036/00020/00022
d D 5.2 92/07/15 10:40:32 marc 2 1
c add test program -- 
e
s 00042/00000/00000
d D 5.1 92/06/22 18:59:34 marc 1 0
c date and time created 92/06/22 18:59:34 by marc
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
SRCS=	chared.c common.c el.c emacs.c hist.c history.c key.c map.c \
	parse.c prompt.c read.c refresh.c search.c sig.c term.c \
	tokenizer.c tty.c vi.c
CLEANFILES+=common.h emacs.h fcns.h help.h vi.h
CFLAGS+=-I. -I${.CURDIR}
E 2
I 2
LIB=	edit

OSRCS=	chared.c common.c el.c emacs.c hist.c key.c map.c parse.c \
	prompt.c read.c refresh.c search.c sig.c term.c tty.c vi.c \
	help.c fcns.c

# For speed and debugging
#SRCS=   ${OSRCS} tokenizer.c history.c
# For protection
SRCS=	editline.c tokenizer.c history.c

CLEANFILES+=common.h emacs.h fcns.h help.h vi.h help.c fcns.c editline.c
CFLAGS+=-I. -I${.CURDIR} 
E 2
CFLAGS+=#-DDEBUG_TTY -DDEBUG_KEY -DDEBUG_READ -DDEBUG -DDEBUG_REFRESH
CFLAGS+=#-DDEBUG_PASTE

I 2
AHDR=vi.h emacs.h common.h 
ASRC=${.CURDIR}/vi.c ${.CURDIR}/emacs.c ${.CURDIR}/common.c

E 2
vi.h: vi.c makelist
D 2
	(cd ${.CURDIR} && sh makelist -h vi.c) > $@
E 2
I 2
	sh ${.CURDIR}/makelist -h ${.CURDIR}/vi.c > ${.TARGET}
E 2

emacs.h: emacs.c makelist
D 2
	(cd ${.CURDIR} && sh makelist -h emacs.c) > $@
E 2
I 2
	sh ${.CURDIR}/makelist -h ${.CURDIR}/emacs.c > ${.TARGET}
E 2

common.h: common.c makelist
D 2
	(cd ${.CURDIR} && sh makelist -h common.c) > $@
E 2
I 2
	sh ${.CURDIR}/makelist -h ${.CURDIR}/common.c > ${.TARGET}
E 2

D 2
AHDR=vi.h emacs.h common.h 
E 2
fcns.h: ${AHDR} makelist
D 2
	sh ${.CURDIR}/makelist -fh ${AHDR} > $@
E 2
I 2
	sh ${.CURDIR}/makelist -fh ${AHDR} > ${.TARGET}
E 2

fcns.c: ${AHDR} fcns.h makelist
D 2
	(cd ${.CURDIR} && sh makelist -fc ${AHDR}) > $@
E 2
I 2
	sh ${.CURDIR}/makelist -fc ${AHDR} > ${.TARGET}
E 2

D 2
ASRC=vi.c emacs.c common.c
E 2
help.c: ${ASRC} makelist 
D 2
	(cd ${.CURDIR} && sh makelist -bc ${ASRC}) > $@
E 2
I 2
	sh ${.CURDIR}/makelist -bc ${ASRC} > ${.TARGET}
E 2

D 2
help.h: makelist
	sh ${.CURDIR}/makelist -bh > $@
E 2
I 2
help.h: ${ASRC} makelist
	sh ${.CURDIR}/makelist -bh ${ASRC} > ${.TARGET}
E 2

D 2
.depend: vi.h emacs.h common.h fcns.h help.h
E 2
I 2
editline.c: ${OSRCS}
	sh ${.CURDIR}/makelist -e ${.ALLSRC:T} > ${.TARGET}
E 2

D 2
beforeinstall:
        -cd ${.CURDIR}; cmp -s histedit.h ${DESTDIR}/usr/include/histedit.h || \
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 histedit.h \
	${DESTDIR}/usr/include
E 2
I 2
.depend: vi.h emacs.h common.h fcns.h help.h help.c
E 2

I 2

test:	libedit.a test.o 
	${CC} ${CFLAGS} ${.ALLSRC} -o ${.TARGET} libedit.a ${LDADD} -ltermcap

beforeinstall:
	-cd ${.CURDIR}; cmp -s histedit.h ${DESTDIR}/usr/include/histedit.h > \
	    /dev/null 2>&1 || \
	    install -c -o ${BINOWN} -g ${BINGRP} -m 444 histedit.h \
	    ${DESTDIR}/usr/include
E 2

.include <bsd.lib.mk>
E 1
