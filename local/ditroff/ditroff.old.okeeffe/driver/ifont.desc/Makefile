DEVDIR	= /usr/local/lib/font

all:
	-if test ! -r R; then mak.sh; fi

install:
	../../bin/devconfig DESC
	cp DESC.out $(DEVDIR)/devip/DESC.out
	chmod 644 $(DEVDIR)/devip/DESC.out
	/bin/rm -f *.out
