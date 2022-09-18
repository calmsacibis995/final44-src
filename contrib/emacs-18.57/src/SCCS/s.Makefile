h32407
s 00002/00001/00038
d D 5.2 93/05/24 15:51:19 hibler 2 1
c reflect current state of 4.4
e
s 00039/00000/00000
d D 5.1 93/05/08 09:49:09 hibler 1 0
c date and time created 93/05/08 09:49:09 by hibler
e
u
U
t
T
I 1
CPP = $(CC) -E
MAKE = make  # BSD doesn't have it as a default.
#Note: an alternative is  CPP = /lib/cpp

all: xmakefile doall

doall:
	$(MAKE) $(MAKEOVERRIDES) -f xmakefile ${MFLAGS} all

#This is used in making a distribution.
#Do not use it on development directories!
distclean:
	-rm -f paths.h config.h emacs-* temacs xemacs xmakefile core \
   *~ \#* *.o libXMenu11.a log*

clean:
	-rm -f temacs xemacs xmakefile core \#* *.o libXMenu11.a

xemacs: xmakefile doxemacs

doxemacs:
	$(MAKE) $(MAKEOVERRIDES) -f xmakefile ${MFLAGS} xemacs

temacs: xmakefile dotemacs

dotemacs:
	$(MAKE) $(MAKEOVERRIDES) -f xmakefile ${MFLAGS} temacs

# If you have a problem with cc -E here, changing
# the definition of CPP above may fix it.
xmakefile: ymakefile config.h
	-rm -f xmakefile junk.c
	cp ymakefile junk.c
D 2
	$(CPP) junk.c | sed -e 's/^#.*//' -e 's/^[ \f\t][ \f\t]*$$//' -e 's/^ /	/' | \
E 2
I 2
	$(CPP) -DYMAKEFILE junk.c | \
	sed -e 's/^#.*//' -e 's/^[ 	][ 	]*$$//' -e 's/^ /	/' | \
E 2
	sed -n -e '/^..*$$/p' > xmakefile
	rm -f junk.c

tags:
	etags [a-z]*.h [a-z]*.c ../lisp/[a-z]*.el
E 1
