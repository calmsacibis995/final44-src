DEVDIR	= /usr/local/lib/font
FONTS = R I B S M RN XX CN Pi El CW

all: DESC.out

DESC.out: DESC $(FONTS) ../../bin/devconfig
	../../bin/devconfig DESC

install:
	cp DESC.out *.out.ext interpress-fonts $(DEVDIR)/devdp
	chmod 644 $(DEVDIR)/devdp/*

clean:
	/bin/rm -f *.out
