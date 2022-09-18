h27505
s 00008/00008/00027
d D 1.2 87/11/18 12:10:52 denise 4 1
c minor rearrangements
e
s 00011/00006/00029
d R 1.2 87/11/18 12:05:58 denise 3 1
c minor corrections
e
s 00010/00005/00030
d R 1.2 87/04/01 16:48:22 jaap 2 1
c minor corrections
e
s 00035/00000/00000
d D 1.1 87/04/01 16:41:36 jaap 1 0
c date and time created 87/04/01 16:41:36 by jaap
e
u
U
t
T
I 1
#
I 4
# %I%	(CWI)	%E%
#
E 4
#   Makefile for the Versatec Harris Emulator
#

OBS = dev.o font.o font2.o graph.o main.o parse.o put.o

#CFLAGS = -g -DDEBUGABLE
CFLAGS = -O
I 4
LIBDIR = /usr/lib
E 4

all:	ndver sort tools

D 4
#
# only on turing do we actually need the driver.
#
install: sort
#	install -c ndver $(DESTDIR)/ndver80
	cd Sort; make $(MFLAGS) install
#	cd Tools; make $(MFLAGS) install
E 4
I 4
install: all
	install -c ndver $(DESTDIR)${LIBDIR}/ndver80
	cd Sort; make $(MFLAGS) DESTDIR=${DESTDIR} install
	cd Tools; make $(MFLAGS) DESTDIR=${DESTDIR} install
E 4

clean:
D 4
	rm -f *.o make.out dnver
E 4
I 4
	rm -f *.o make.out ndver
E 4
	cd Sort; make $(MFLAGS) clean
	cd Tools; make $(MFLAGS) clean

ndver:	$(OBS)
	$(CC) $(CFLAGS) $(OBS) -lm -o ndver

sort:;  cd Sort; make $(MFLAGS) all
tools:; cd Tools; make $(MFLAGS) all


$(OBS):			Makefile
font.o put.o dev.o:	the.h dev.h
font2.o: 		the.h defs.h
main.o parse.o:		the.h
E 1
