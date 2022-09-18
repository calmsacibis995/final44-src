h46942
s 00004/00001/00033
d D 1.4 88/03/04 17:05:32 jaap 4 3
c cleaning up
e
s 00007/00006/00027
d D 1.3 87/04/01 16:38:17 jaap 3 2
c cleanup
e
s 00002/00002/00031
d D 1.2 85/10/25 00:16:26 jaap 2 1
c We should also install grap.defines!
e
s 00033/00000/00000
d D 1.1 85/10/25 00:07:51 jaap 1 0
c date and time created 85/10/25 00:07:51 by jaap
e
u
U
t
T
I 1
#
# grap Makefile %W% (CWI) %E%
#
D 3
DEST =
BIN = /usr/local
CFLAGS = -g
E 3
I 3
DESTDIR =
BINDIR = /usr/local
LIBDIR = ${DESTDIR}/usr/local/lib/grap
CFLAGS = -O
E 3
YFLAGS = -d -D
OFILES = main.o input.o print.o frame.o for.o coord.o ticks.o plot.o label.o misc.o
CFILES = main.c input.c print.c frame.c for.c coord.c ticks.c plot.c label.c misc.c
SRCFILES = grap.y grapl.l grap.h $(CFILES)

D 2
all:	grap
E 2
I 2
all:	grap grap.defines
E 2

grap:	grap.o grapl.o $(OFILES) grap.h 
	$(CC) -o grap $(CFLAGS) grap.o grapl.o $(OFILES) -lm

$(OFILES) grapl.o:	grap.h prevy.tab.h

grap.c:	grap.h grap.y			# grap.o: grap.h
	yacc -d grap.y
	mv y.tab.c grap.c

y.tab.h:	grap.o

prevy.tab.h:	y.tab.h
	-cmp -s y.tab.h prevy.tab.h || cp y.tab.h prevy.tab.h

D 4
install: grap
E 4
I 4
install: grap $(LIBDIR)
E 4
D 3
	install -s grap $(DEST)$(BIN)/grap
D 2
	install -c -m 644 $(DEST)/usr/local/lib/grap
E 2
I 2
	install -c -m 644 grap.defines $(DEST)/usr/local/lib/grap/grap.defines
E 3
I 3
	install -s grap $(DESTDIR)$(BINDIR)/grap
	install -c -m 644 grap.defines $(DESTDIR)${LIBDIR}/grap.defines
I 4

$(LIBDIR):
	mkdir $(LIBDIR)
E 4
E 3
E 2

clean:
D 3
	rm -rf grap *.o y.tab.h
E 3
I 3
	rm -rf grap *.o y.tab.h grap.c
E 3
E 1
