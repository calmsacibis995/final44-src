h60097
s 00002/00002/00039
d D 2.4 93/06/07 23:36:23 bostic 4 3
c set up for 4.4BSD
e
s 00001/00001/00040
d D 2.3 93/05/27 14:19:37 bostic 3 2
c add in keywords
e
s 00035/00008/00006
d D 2.2 93/05/27 14:19:15 bostic 2 1
c new version from Dain Samples; checked in by TK
e
s 00014/00000/00000
d D 2.1 88/04/08 14:50:40 mckusick 1 0
c date and time created 88/04/08 14:50:40 by mckusick
e
u
U
t
T
I 1
D 2
#	%W% (Berkeley) %G%
E 2
I 2
D 3
#	@(#)Makefile	2.3 (Berkeley) 5/28/90
E 3
I 3
#	%W% (Berkeley) %G%
E 3
E 2
#
D 2
DESTDIR=
E 2
I 2
# all executables go in DEST_BIN
# all man pages go in DEST_MAN
# the bib libraries go in DEST_LIB
E 2

I 2
# At UCB, the file structures have diverged, resulting in the following
# choice:

# UNIX on VAX machines:
DEST_BASE=/usr/contrib
D 4
DEST_BIN=$(DEST_BASE)
DEST_MAN=/usr/man
E 4
I 4
DEST_BIN=$(DEST_BASE)/bin
DEST_MAN=/usr/contrib/man
E 4

# UNIX on Suns, etc
#DEST_BASE=/usr/local
#DEST_BIN=$(DEST_BASE)/bin
#DEST_MAN=$(DEST_BASE)/man

# the software expects the following to be true
DEST_LIB=$(DEST_BASE)/lib

DESTDIRS=DEST_BASE=$(DEST_BASE) DEST_BIN=$(DEST_BIN) \
	 DEST_MAN=$(DEST_MAN)   DEST_LIB=$(DEST_LIB)

E 2
all:
D 2
	cd src; make ${MFLAGS}
E 2
I 2
	cd src; make ${MFLAGS} $(DESTDIRS)
E 2

D 2
install: all
	cd src; make ${MFLAGS} DESTDIR=${DESTDIR} install
	cd macs; make ${MFLAGS} DESTDIR=${DESTDIR} install
	cd man; make ${MFLAGS} DESTDIR=${DESTDIR} install
E 2
I 2
install: all installsrc installmacs installman
E 2

I 2
installman:
	cd man; make ${MFLAGS} $(DESTDIRS) install

installsrc:
	cd src; make ${MFLAGS} $(DESTDIRS) install

installmacs:
	cd macs; make ${MFLAGS} $(DESTDIRS) install

E 2
clean:
D 2
	cd src; make ${MFLAGS} clean
E 2
I 2
	cd src; make ${MFLAGS} $(DESTDIRS) clean
E 2
E 1
