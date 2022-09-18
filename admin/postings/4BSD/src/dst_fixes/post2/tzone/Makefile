# @(#)Makefile	1.1 Makefile 3/4/87

DESTDIR=

# If you want something other than Eastern United States time used on your
# system, change the line below (after finding the zone you want in the
# time zone files, or adding it to a time zone file).
# Alternately, if you discover you've got the wrong time zone, you can just
#	zic -l rightzone

LOCALTIME=	US/Pacific

# If you want code inspired by certain emerging standards, add
#	-DSTD_INSPIRED
# to the end of the "CFLAGS=" line.
#
# If you want to handle solar-time-based time zones, remove the
# "#define NOSOLAR" from the include file usr/include/tzfile.h.
# (and add solar87 to the DATA= line below).

CFLAGS= -O

# LINTFLAGS is set for 4.[123]BSD systems.
# If you're using System V, you'll want to comment out the "LINTFLAGS=" line.

LINTFLAGS=	-phbaaxc

# BUNDLE was set to "bundle" in the original, "shar" is more universal

BUNDLE=		shar

################################################################################

CC=		cc

TZCSRCS=	zic.c scheck.c ialloc.c
TZCOBJS=	zic.o scheck.o ialloc.o
TZDSRCS=	zdump.c ialloc.c
TZDOBJS=	zdump.o ialloc.o
DOCS=		Theory README Makefile newctime.3 tzfile.5 zic.8 zdump.8
SOURCES=	zic.c zdump.c scheck.c ialloc.c
DATA=		asia australasia europe etcetera northamerica \
		pacificnew systemv
ENCHILADA=	$(DOCS) $(SOURCES) $(DATA)

all:		zdump zic

install:	zic $(DATA)
		./zic -d ${DESTDIR}/etc/zoneinfo -l $(LOCALTIME) $(DATA)

zdump:		$(TZDOBJS)
		$(CC) $(CFLAGS) $(LFLAGS) $(TZDOBJS) -o $@

zic:		$(TZCOBJS)
		$(CC) $(CFLAGS) $(LFLAGS) $(TZCOBJS) -o $@

BUNDLES:	BUNDLE1 BUNDLE2 BUNDLE3

BUNDLE1:	$(DOCS)
		$(BUNDLE) $(DOCS) > $@

BUNDLE2:	$(SOURCES)
		$(BUNDLE) $(SOURCES) > $@

BUNDLE3:	$(DATA)
		$(BUNDLE) $(DATA) > $@

$(ENCHILADA):
		sccs get $(REL) $(REV) $@

sure:		$(TZCSRCS) $(TZDSRCS)
		lint $(LINTFLAGS) $(CFLAGS) $(TZCSRCS)
		lint $(LINTFLAGS) $(CFLAGS) $(TZDSRCS)

clean:
		rm -f core *.o *.out REDID_BINARIES zdump zic BUNDLE* \#*

CLEAN:		clean
		sccs clean

listing:	$(ENCHILADA)
		pr $(ENCHILADA) | lpr

