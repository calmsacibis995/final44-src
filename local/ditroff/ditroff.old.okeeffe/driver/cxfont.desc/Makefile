DEVDIR	= /usr/local/lib/font

all:
	-if test ! -r R; then mak.sh; fi

install:
	../../bin/devconfig DESC
	cp DESC.out $(DEVDIR)/devcx/DESC.out
	chmod 644 $(DEVDIR)/devcx/DESC.out
	/bin/rm -f *.out
