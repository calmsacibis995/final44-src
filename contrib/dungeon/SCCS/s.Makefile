h54993
s 00026/00069/00006
d D 5.2 90/06/25 00:55:14 bostic 2 1
c checkpoint for June tape -- still doesn't work
e
s 00075/00000/00000
d D 5.1 88/10/20 18:37:46 bostic 1 0
c from UUNET; patches 1-3 applied
e
u
U
t
T
I 1
D 2
# Makefile for creating dungeon
# Edit BIN DDIR and FFLAGS suitable for your system
.c.o:
	cc -c $(CFLAGS) $*.c
.F.o:
	f77 -c $(FFLAGS) $*.F
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
CFLAGS = -O # -i
#
# f77 compiler flags for Vax (and other large address machines)
#
FFLAGS = -O -q # -Ddebug
# f77 compiler flags for pdp (64K split I/D)
#FFLAGS = -O -q -I2 -L1 -i -DPDP # -Ddebug
E 2
I 2
FFLAGS=	-g -Ddebug -DNOCC -q # -g -Ddebug
OBJS=	actors.o ballop.o clockr.o demons.o dgame.o dinit.o dmain.o \
	dso1.o dso2.o dso3.o dso4.o dso5.o dso6.o dso7.o dsub.o \
	dverb1.o dverb2.o gdt.o lightp.o nobjs.o np.o np1.o np2.o \
	np3.o nrooms.o objcts.o rooms.o rtim.o sobjs.o sverbs.o \
	verbs.o villns.o
MAN=	dungeon.0
E 2

D 2
# Directory path for main program - default /usr/games
BIN = /usr/games
# Directory path for data files - default is /usr/games/lib/dunlib
DDIR = \'/usr/games/lib/dunlib
DCDIR =\"/usr/games/lib/dunlib
# Directory path for man page - default /usr/manl/man6
MDIR = /usr/manl/man6
# userid for wizard - allows invoking game debugging tool - default 0
WIZDEF = -DWIZARDID=20
E 2
I 2
all: dungeon
E 2

D 2
OBJS =  actors.o ballop.o clockr.o demons.o\
	dgame.o dinit.o dmain.o dso1.o dso2.o\
	dso3.o dso4.o dso5.o dso6.o dso7.o\
	dsub.o dverb1.o dverb2.o gdt.o lightp.o\
	nobjs.o np.o np1.o np2.o np3.o nrooms.o objcts.o\
	rooms.o rtim.o sobjs.o sverbs.o verbs.o villns.o
E 2
I 2
dungeon: ${OBJS}
	f77 -g -o $@ ${OBJS} rand.o ecvt.o
clean:
	rm -f ${OBJS} core dungeon
E 2

D 2
PDPOBJS = cinit.o cio.o lex.o
LISTEN = listen.o
SPEAK = cspeak.o speak.o
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend
E 2

D 2
vax:	dungeon dtext.dat
pdp:	dungpdp speak listen dtext.dat
E 2
I 2
depend lint tags:
E 2

D 2
dungeon: $(OBJS)
	f77 -s -o dungeon $(OBJS)

dungpdp: $(OBJS) $(PDPOBJS)
	f77 -i -s -o dungpdp $(OBJS) $(PDPOBJS)

speak:	$(SPEAK)
	f77 -i -s -o speak $(SPEAK)
	
speak.o: speak.F
	f77 $(FFLAGS) -DDDIR=$(DDIR) -c speak.F

listen:	$(LISTEN)
	cc $(CFLAGS) -o listen $(LISTEN)

listen.o: listen.c
	cc $(CFLAGS) -DCINDEXFILE=$(DCDIR)/dindx.dat\" -c listen.c

dinit.o: dinit.F
	f77 $(FFLAGS) -DDDIR=$(DDIR) $(WIZDEF) -c dinit.F

install-vax: vax
	cp dungeon $(BIN)
	-mkdir $(DDIR)
	cp dindx.dat dtext.dat $(DDIR)
	cp dungeon.6 $(MDIR)/dungeon.6

install-pdp: pdp
	cp dungeon.sh $(BIN)
	-mkdir $(DDIR)
	cp dindx.dat dtext.dat rtext.dat dungpdp $(DDIR)
	cp dungeon.6 $(MDIR)/dungeon.6

dtext.dat: 
	./maketxt.sh

E 2
I 2
install: ${MAN}
	-[ -d ${DESTDIR}/usr/games/lib/dunlib ] || mkdir ${DESTDIR}/usr/games/lib/dunlib
	chmod 700 ${DESTDIR}/usr/games/lib/dunlib
	chown games.bin ${DESTDIR}/usr/games/lib/dunlib
	install -s -o games -g bin -m 4700 dungeon ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f dungeon; ln -s dm dungeon; chown games.bin dungeon)
	install -c -o bin -g bin -m 444 dindx.dat dtext.dat ${DESTDIR}/usr/games/lib/dunlib
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
	rm -f ${DESTDIR}/usr/man/cat6/zork.0
	ln ${DESTDIR}/usr/man/cat6/dungeon.0 ${DESTDIR}/usr/man/cat6/zork.0
E 2
E 1
