BINDIR  = /usr/local
DESTFILE= grap
YFLAGS = -d -D
CFLAGS =

OFILES = main.o input.o print.o frame.o for.o coord.o ticks.o \
	 plot.o label.o misc.o
CFILES = main.c input.c print.c frame.c for.c coord.c ticks.c \
	 plot.c label.c misc.c
SRCFILES = grap.y grapl.l grap.h $(CFILES)

grap:	grap.o grapl.o $(OFILES) grap.h 
	cc -o grap grap.o grapl.o $(OFILES) -lm

$(OFILES):	grap.h

grap.o:		grap.h

y.tab.h:	grap.o

grap.0:		grap.1
		nroff -man grap.1 > grap.0

install:	$(BINDIR)/$(DESTFILE)
		cp grap.defines /usr/local/lib
		cp grap.0 /usr/local/man/cat1

$(BINDIR)/$(DESTFILE):	grap
	install -c -s grap $(BINDIR)/$(DESTFILE)

clean:
	/bin/rm -f *.o grap grap.0 make.out y.tab.h
