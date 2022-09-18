BINDIR	= /usr/local
GREMLIB	= /usr/local/gremlib

gremlin:
	cd gremlin; make

gprint:
	cd gprint; make

install:
	cd gremlin; make install 'BINDIR=$(BINDIR)'
	-if test ! -d $(GREMLIB); then mkdir $(GREMLIB); chmod 755 $(GREMLIB); fi
	cp gremlib/* $(GREMLIB)

clean:
	cd gremlin; make clean
	cd gprint; make clean
