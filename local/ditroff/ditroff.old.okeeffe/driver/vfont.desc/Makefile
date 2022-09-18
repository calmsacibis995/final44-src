DEVDIR	= /usr/local/lib/font

all:
	-if test ! -r R; then mak.sh; fi

varian:
	cp DESCvar DESC
	../../bin/devconfig DESC
	cp DESC.out $(DEVDIR)/devva/DESC.out
	chmod 644 $(DEVDIR)/devva/DESC.out
	/bin/rm -f *.out DESC

versatec:
	cp DESCver DESC
	../../bin/devconfig DESC
	cp DESC.out $(DEVDIR)/devvp/DESC.out
	chmod 644 $(DEVDIR)/devvp/DESC.out
	/bin/rm -f *.out DESC
