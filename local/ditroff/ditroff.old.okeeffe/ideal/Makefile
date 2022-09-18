BINDIR	= /usr/local
DESTFILE= ideal_p
FILTER	= ditfilt
FILTFILE= ideal_f
DEVDIR	= "/usr/local/lib/font"
IDEALIB	= /usr/local/ideal.lib
CFLAGS	= -O '-DLIBDIR="$(IDEALIB)/"'

SOURCES	= ideal.h ideal.c util.c memut.c bldds.c simul.c exprn.c action.c\
	piece.c opaque.c inter.c opqpoly.c idlex.l idyac.y
OBJECTS	= y.tab.o lex.yy.o ideal.o util.o memut.o bldds.o simul.o exprn.o\
	action.o piece.o opaque.o opqpoly.o inter.o
ADMIXTURE = y.tab.c lex.yy.c ideal.c util.c memut.c bldds.c simul.c exprn.c\
	action.c piece.c opaque.c opqpoly.c inter.c

$(DESTFILE):	$(OBJECTS)
	cc -o $(DESTFILE) $(OBJECTS) -ll -lm
	cd idfilt; make 'DEVDIR=$(DEVDIR)' $(FILTER); cd ..

install:	$(BINDIR)/$(FILTFILE) $(BINDIR)/$(DESTFILE) $(BINDIR)/ideal
	-if test ! -d $(IDEALIB); then mkdir $(IDEALIB); fi
	cp lib/* $(IDEALIB)

$(BINDIR)/$(FILTFILE):	filter
	install -c -s filter $(BINDIR)/$(FILTFILE)

$(BINDIR)/$(DESTFILE):	$(DESTFILE)
	install -c -s $(DESTFILE) $(BINDIR)/$(DESTFILE)

$(BINDIR)/ideal:	ideal
	install -c ideal $(BINDIR)/ideal

ideal:	ideal.sh
	echo "#! /bin/csh -f" > ideal
	echo "set ideal = $(BINDIR)/$(DESTFILE)" >> ideal
	echo "set filter = $(BINDIR)/$(FILTFILE)" >> ideal
	cat ideal.sh >> ideal
	chmod 755 ideal

$(OBJECTS):	ideal.h

ideal.h:	stdas.h

lex.yy.c:	idlex.l
	lex idlex.l

y.tab.c:	idyac.y
	yacc -d idyac.y

list:
	pr $(SOURCES)

lint:
	lint $(ADMIXTURE) -lm

clean:
	/bin/rm -f $(OBJECTS) y.tab.c lex.yy.c make.out ideal $(DESTFILE)
	cd idfilt; make clean
