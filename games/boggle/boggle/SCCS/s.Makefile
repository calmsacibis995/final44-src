h52867
s 00000/00000/00015
d D 8.1 93/06/11 14:45:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00041/00003
d D 5.2 93/06/11 14:43:50 bostic 2 1
c integrate into 4.4BSD
e
s 00044/00000/00000
d D 5.1 93/06/10 11:09:42 bostic 1 0
c date and time created 93/06/10 11:09:42 by bostic
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
# See bog.h for configuration

OBJS=bog.o help.o mach.o prtable.o timer.o word.o

CC=gcc
CFLAGS=-O
LIBS=-lcurses -ltermlib

# DICT is the dictionary that will be used to construct the word list used
# by bog
DICT=/usr/dict/words

bog: $(OBJS)
	$(CC) $(CFLAGS) -s -o bog $(OBJS) $(LIBS)

all: bog mkdict mkindex dict

mkdict: mkdict.c
	$(CC) -s -O -o mkdict mkdict.c

mkindex: mkindex.c
	$(CC) -s -O -o mkindex mkindex.c

showdict: showdict.o word.o
	$(CC) -s -O -o showdict showdict.o word.o
	rm -f showdict.o
E 2
I 2
PROG=	boggle
SRCS=	bog.c help.c mach.c prtable.c timer.c word.c
DPADD=	${LIBCURSES} ${LIBTERM}
LDADD=	-lcurses -ltermlib
HIDEGAME=hidegame
MAN6=	boggle.0
E 2

D 2
dict: mkdict mkindex
	./mkdict < $(DICT) > dict
	./mkindex < dict > dict.ind
E 2
I 2
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/helpfile \
	    ${DESTDIR}/usr/share/games/boggle/helpfile
E 2

D 2
$(OBJS): bog.h

install: all
	@echo "Move dict, dict.ind, and the helpfile to where you specified in bog.h"
	@echo "Move bog.man to where you want the manual page to go"

clean:
	rm -f *.o bog

lint:
	lint -abchx bog.c help.c mach.c prtable.c timer.c word.c

E 2
I 2
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 2
E 1
