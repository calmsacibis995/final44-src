#
# sccsid "%W% (CWI) %E%";
#
DRIVEDIR= .
UTILDIR	= ../bin
DESTDIR	= /usr/local
DEVDIR	= "/usr/local/lib/ditroff/font"
CFLAGS	= -O '-DFONTDIR=$(DEVDIR)'
#Dunno how SPECFILE should be, but let's use /dev/null
DTERMFLAGS	= -O '-DSPECFILE="/usr/local/lib/ditroff/font/devter/specfile"'

SOURCE	= rst.h canon.h dev.h dvar.c dver.c graph.c vsort.c dip.c draw.c

EFILES	= dver.o graph.o
E80FILES = dver80.o graph.o
AFILES	= dvar.o graph.o
IFILES	= dip.o draw.o

DRIVERS	= $(DRIVEDIR)/dver $(DRIVEDIR)/dvar $(DRIVEDIR)/vsort $(DRIVEDIR)/dip
UTILS	= $(UTILDIR)/makevfont $(UTILDIR)/makeifont $(UTILDIR)/scalech \
	$(UTILDIR)/doublech $(UTILDIR)/rotate $(UTILDIR)/rst2ch \
	$(UTILDIR)/ch2rst $(UTILDIR)/vft2ch $(UTILDIR)/ch2vft
PROGS	= $(DESTDIR)/ifontinfo $(DESTDIR)/vfontinfo $(DESTDIR)/dterm

nothing:
	@echo "'make driver' installs the drivers on the local machine in $(DRIVEDIR)'
	@echo "'make utility' puts the utilities in $(UTILDIR)"
	@echo "'make install' installs $(PROGS)"

install: $(PROGS)
driver: $(DRIVERS)
utility: $(UTILS)

$(DRIVEDIR)/dver:	$(EFILES)
	cc $(CFLAGS) -o $(DRIVEDIR)/dver $(EFILES) -lm

$(DRIVEDIR)/dver80:	$(E80FILES)
	cc $(CFLAGS) -o $(DRIVEDIR)/dver80 $(E80FILES) -lm

$(DRIVEDIR)/dvar:	$(AFILES)
	cc $(CFLAGS) -o $(DRIVEDIR)/dvar $(AFILES) -lm

$(DRIVEDIR)/vsort:	vsort.c
	cc $(CFLAGS) -o $(DRIVEDIR)/vsort vsort.c -lm

$(DRIVEDIR)/vsort80:	vsort.c
	cc $(CFLAGS) -DVER80 -o $(DRIVEDIR)/vsort80 vsort.c -lm

$(DRIVEDIR)/dip:	$(IFILES)
	cc $(CFLAGS) -o $(DRIVEDIR)/dip $(IFILES) -lm

$(DESTDIR)/dterm:	dterm
	install -s dterm $(DESTDIR)/dterm

dterm:	dterm.c Makefile
	cc $(DTERMFLAGS) -o dterm dterm.c -lm

$(DESTDIR)/ifontinfo:	ifontinfo
	install -c -s ifontinfo $(DESTDIR)/ifontinfo

ifontinfo:	ifontinfo.c rst.h
	cc $(CFLAGS) -o ifontinfo ifontinfo.c

$(DESTDIR)/vfontinfo:	vfontinfo
	install -c -s vfontinfo $(DESTDIR)/vfontinfo

vfontinfo:	vfontinfo.c
	cc $(CFLAGS) -o vfontinfo vfontinfo.c

$(UTILDIR)/makevfont:	makevfont.o
	cc $(CFLAGS) -o $(UTILDIR)/makevfont makevfont.o

$(UTILDIR)/makeifont:	makeifont.o rst.h
	cc $(CFLAGS) -o $(UTILDIR)/makeifont makeifont.o

$(UTILDIR)/rotate:	rotate.c
	cc $(CFLAGS) -o $(UTILDIR)/rotate rotate.c

$(UTILDIR)/rst2ch:	rst2ch.c rst.h
	cc $(CFLAGS) -o $(UTILDIR)/rst2ch rst2ch.c

$(UTILDIR)/ch2rst:	ch2rst.c rst.h
	cc $(CFLAGS) -o $(UTILDIR)/ch2rst ch2rst.c

$(UTILDIR)/vft2ch:	vft2ch.c
	cc $(CFLAGS) -o $(UTILDIR)/vft2ch vft2ch.c

$(UTILDIR)/ch2vft:	ch2vft.c
	cc $(CFLAGS) -o $(UTILDIR)/ch2vft ch2vft.c

$(UTILDIR)/scalech:	scalech.c
	cc $(CFLAGS) -o $(UTILDIR)/scalech scalech.c

$(UTILDIR)/doublech:	doublech.c
	cc $(CFLAGS) -o $(UTILDIR)/doublech doublech.c

dver80.o:	../dev.h dver.c
	cc $(CFLAGS) -DVER80 -c dver.c
	mv dver.o dver80.o

dver.o:	../dev.h dver.c

dvar.o:	../dev.h dvar.c

dip.o:	dev.h canon.h rst.h dip.c

list:
	lpr -p -Pucbvax $(SOURCE) makefile

clean:
	/bin/rm -f *.o make.out
