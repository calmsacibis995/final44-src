DRIVEDIR= .
UTILDIR	= ../bin
BINDIR	= /usr/local
DEVDIR	= "/usr/local/lib/font"
IFONTDIR= "/usr/src/local/imagen/fonts/raster"
VFONTDIR= "/usr/lib/vfont"
TROFF	= troff_p
DITROFF	= ditroff
CFLAGS	= -O '-DFONTDIR=$(DEVDIR)'

SOURCE	= rst.h canon.h dev.h dvar.c dver.c graph.c vsort.c dip.c draw.c

EFILES	= dver.o graph.o
AFILES	= dvar.o graph.o
IFILES	= dip.o draw.o

DRIVERS	= $(DRIVEDIR)/dver $(DRIVEDIR)/dvar $(DRIVEDIR)/vsort $(DRIVEDIR)/dip
UTILS	= $(UTILDIR)/makevfont $(UTILDIR)/makeifont $(UTILDIR)/scalech \
	$(UTILDIR)/doublech $(UTILDIR)/rotate $(UTILDIR)/rst2ch \
	$(UTILDIR)/ch2rst $(UTILDIR)/vft2ch $(UTILDIR)/ch2vft \
	$(UTILDIR)/ch2qms $(UTILDIR)/qms2ch $(UTILDIR)/ch2x $(UTILDIR)/x2ch \
	$(UTILDIR)/devconfig $(UTILDIR)/devundo
PROGS	= ifontinfo vfontinfo dterm $(DITROFF)

nothing:
	@echo "'make driver' installs the drivers in $(DRIVEDIR)"
	@echo "'make utility' installs the utilities in $(UTILDIR)"
	@echo "'make programs' makes a local copy of $(PROGS)"
	@echo "'make install' installs $(PROGS) in $(BINDIR)"

all: programs driver utility
programs: $(PROGS)
driver: $(DRIVERS)
utility: $(UTILS)
install: $(PROGS)
	for i in $(PROGS); do install -s $$i $(BINDIR)/$$i; done

$(DRIVEDIR)/vsort:	vsort.c
	cc $(CFLAGS) -o $(DRIVEDIR)/vsort vsort.c -lm

$(DRIVEDIR)/dver:	$(EFILES)
	cc '-DBITDIR=$(VFONTDIR)' $(CFLAGS) -o $(DRIVEDIR)/dver $(EFILES) -lm

$(DRIVEDIR)/dvar:	$(AFILES)
	cc '-DBITDIR=$(VFONTDIR)' $(CFLAGS) -o $(DRIVEDIR)/dvar $(AFILES) -lm

$(DRIVEDIR)/dip:	$(IFILES)
	cc $(CFLAGS) -o $(DRIVEDIR)/dip $(IFILES) -lm

dterm:	dterm.c
	cc $(CFLAGS) -o dterm dterm.c -lm

ifontinfo:	ifontinfo.c rst.h
	cc '-DBITDIR=$(IFONTDIR)' $(CFLAGS) -o ifontinfo ifontinfo.c

vfontinfo:	vfontinfo.c
	cc '-DBITDIR=$(VFONTDIR)' $(CFLAGS) -o vfontinfo vfontinfo.c

$(DITROFF):	troff.sh
	/bin/rm -f $(DITROFF)
	echo "#! /bin/csh -f" > $(DITROFF)
	echo "set troff = $(BINDIR)/$(TROFF)" >> $(DITROFF)
	echo "set dterm = ($(BINDIR)/dterm -m -c)" >> $(DITROFF)
	cat troff.sh >> $(DITROFF)
	chmod 0755 $(DITROFF)

$(UTILDIR)/makevfont:	makevfont.c
	cc '-DBITDIR=$(VFONTDIR)' $(CFLAGS) -o $(UTILDIR)/makevfont makevfont.c

$(UTILDIR)/makeifont:	makeifont.c rst.h
	cc '-DBITDIR=$(IFONTDIR)' $(CFLAGS) -o $(UTILDIR)/makeifont makeifont.c

$(UTILDIR)/rotate:	rotate.c
	cc $(CFLAGS) -o $(UTILDIR)/rotate rotate.c

$(UTILDIR)/rst2ch:	rst2ch.c rst.h
	cc '-DBITDIR=$(IFONTDIR)' $(CFLAGS) -o $(UTILDIR)/rst2ch rst2ch.c

$(UTILDIR)/ch2rst:	ch2rst.c rst.h
	cc $(CFLAGS) -o $(UTILDIR)/ch2rst ch2rst.c

$(UTILDIR)/vft2ch:	vft2ch.c
	cc '-DBITDIR=$(VFONTDIR)' $(CFLAGS) -o $(UTILDIR)/vft2ch vft2ch.c

$(UTILDIR)/ch2vft:	ch2vft.c
	cc $(CFLAGS) -o $(UTILDIR)/ch2vft ch2vft.c

$(UTILDIR)/qms2ch:	qms2ch.c
	cc '-DBITDIR=$(VFONTDIR)' $(CFLAGS) -o $(UTILDIR)/qms2ch qms2ch.c

$(UTILDIR)/ch2qms:	ch2qms.c
	cc $(CFLAGS) -o $(UTILDIR)/ch2qms ch2qms.c

$(UTILDIR)/x2ch:	x2ch.c xfont.h
	cc '-DBITDIR=$(VFONTDIR)' $(CFLAGS) -o $(UTILDIR)/x2ch x2ch.c

$(UTILDIR)/ch2x:	ch2x.c xfont.h
	cc $(CFLAGS) -o $(UTILDIR)/ch2x ch2x.c

$(UTILDIR)/scalech:	scalech.c
	cc $(CFLAGS) -o $(UTILDIR)/scalech scalech.c

$(UTILDIR)/doublech:	doublech.c
	cc $(CFLAGS) -o $(UTILDIR)/doublech doublech.c

$(UTILDIR)/devconfig:	devconfig.c dev.h
	cc $(CFLAGS) -o $(UTILDIR)/devconfig devconfig.c

$(UTILDIR)/devundo:	devundo.c dev.h
	cc $(CFLAGS) -o $(UTILDIR)/devundo devundo.c

dver.o:	dev.h dver.c

dvar.o:	dev.h dvar.c

dip.o:	dev.h canon.h rst.h dip.c

list:
	lpr -p -Pucbvax $(SOURCE) makefile

clean:
	/bin/rm -f *.o make.out
