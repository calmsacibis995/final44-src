#
#	"make" makes everything, "make install" installs all but drivers or
#	font width tables and "make widthtables" installs font width tables.
#	DEVDIR must already exist, as should the upper directory paths for
#	the other defined destination directories.  The naming conventions
#	in this makefile create the ditroff system as a separate entity to
#	troff and vtroff.  If you're installing it as a replacement for those
#	programs, the names given below should be changed.
#
#	     we've left out this refer in favor of /usr/bin/refer

#ALL	= tbl eqn troff pic gremlin grn ideal driver fonts
ALL	= tbl eqn troff pic grn ideal driver fonts

TBL	= dtbl
EQN	= deqn
TROFF	= troff_p
DITROFF	= ditroff

DEVDIR	= /usr/local/lib/font
BINDIR	= /usr/local

TMACDIR	= /usr/local/lib/ditmac
IDEALIB	= /usr/local/ideal.lib
GREMLIB	= /usr/local/gremlib

all:	$(ALL)

tbl:	FRC
	cd tbl; make 'DEVDIR="$(DEVDIR)"' TBL=$(TBL)

eqn:	FRC
	cd eqn; make 'DEVDIR="$(DEVDIR)"' EQN=$(EQN)

pic:	FRC
	cd pic; make 'DEVDIR="$(DEVDIR)"'

gremlin:	FRC
	cd gremlin; make gremlin 'GREMLIB="$(GREMLIB)"'

grn:	FRC
	cd grn; make 'DEVDIR="$(DEVDIR)"' 'GREMLIB=$(GREMLIB)'

ideal:	FRC
	cd ideal; make 'DEVDIR="$(DEVDIR)"' 'IDEALIB=$(IDEALIB)'

driver:	FRC
	cd driver; make all 'DEVDIR="$(DEVDIR)"' TROFF=$(TROFF) DITROFF=$(DITROFF) BINDIR=$(BINDIR)

fonts:	FRC
	for fontset in driver/*.desc; do ( cd $$fontset; make ); done

docs:	FRC
	cd docs; make all

troff:	FRC
	cd troff; make 'DEVDIR="$(DEVDIR)"' 'TMACDIR=$(TMACDIR)'

refer:	FRC
	cd refer; make

FRC:

install:
	cd tbl; make install BINDIR=$(BINDIR)
	cd eqn; make install BINDIR=$(BINDIR)
	cd pic; make install BINDIR=$(BINDIR)
#	cd gremlin; make install BINDIR=$(BINDIR) GREMLIB=$(GREMLIB)
	cd grn; make install BINDIR=$(BINDIR)
	cd ideal; make install BINDIR=$(BINDIR) IDEALIB=$(IDEALIB)
	cd driver; make install BINDIR=$(BINDIR) DITROFF=$(DITROFF)
	cd troff; make install BINDIR=$(BINDIR) TROFF=$(TROFF)
	-if test ! -d $(TMACDIR); then mkdir $(TMACDIR); fi
	cp tmac/* $(TMACDIR)
	chmod 444 $(TMACDIR)/*
#	cd refer; make install BINDIR=$(BINDIR)
	cd docs; make install

clean:
	for subdir in docs driver eqn gremlin grn ideal pic refer tbl troff; \
		do (cd $$subdir; make clean); done

###############################################################################
#
# From here on are the device-specific installations.
#    Remove those devices from the "widthtables" entry that you don't have.
#
###############################################################################

#		Imagen		Varian		Versatec	lineprinter/
#								terminals
widthtables:	$(DEVDIR)/devip/DESC.out $(DEVDIR)/devva/DESC.out \
		$(DEVDIR)/devvp/DESC.out $(DEVDIR)/devter/DESC.out \
		$(DEVDIR)/devcx/DESC.out $(DEVDIR)/devdp/DESC.out

$(DEVDIR)/devip/DESC.out: driver/ifont.desc
	-mkdir $(DEVDIR)/devip
	-chmod 755 $(DEVDIR)/devip
	-ln -s $(DEVDIR)/devip $(DEVDIR)/devimagen
	cd driver/ifont.desc; make install DEVDIR=$(DEVDIR)

$(DEVDIR)/devva/DESC.out: driver/vfont.desc
	-mkdir $(DEVDIR)/devva
	-chmod 755 $(DEVDIR)/devva
	-ln -s $(DEVDIR)/devva $(DEVDIR)/devvarian
	cd driver/vfont.desc; make varian DEVDIR=$(DEVDIR)

$(DEVDIR)/devvp/DESC.out: driver/vfont.desc
	-mkdir $(DEVDIR)/devvp
	-chmod 755 $(DEVDIR)/devvp
	-ln -s $(DEVDIR)/devvp $(DEVDIR)/devversatec
	cd driver/vfont.desc; make versatec DEVDIR=$(DEVDIR)

$(DEVDIR)/devter/DESC.out: driver/tfont.desc
	-mkdir $(DEVDIR)/devter
	-chmod 755 $(DEVDIR)/devter
	cd driver/tfont.desc; make install DEVDIR=$(DEVDIR)

$(DEVDIR)/devdp/DESC.out: driver/vfont.desc
	-mkdir $(DEVDIR)/devdp
	-chmod 755 $(DEVDIR)/devdp
	cd driver/vfont.x8044; make DEVDIR=$(DEVDIR)

$(DEVDIR)/devcx/DESC.out: driver/vfont.desc
	-mkdir $(DEVDIR)/devcx
	-chmod 755 $(DEVDIR)/devcx
	cd driver/vfont.cxfont; make DEVDIR=$(DEVDIR)

depend:
