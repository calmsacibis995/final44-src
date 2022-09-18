h61166
s 00000/00000/00138
d D 8.1 93/06/08 11:22:13 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00137
d D 5.11 93/05/03 15:56:02 hibler 11 10
c missing backslash
e
s 00001/00002/00137
d D 5.10 92/07/18 10:58:06 bostic 10 9
c make install test conditional
e
s 00001/00001/00138
d D 5.9 91/02/28 18:56:45 bostic 9 8
c get rid of the "portability" sugar
e
s 00000/00001/00139
d D 5.8 91/02/15 11:29:45 bostic 8 7
c don't need to defined OBJS
e
s 00016/00034/00124
d D 5.7 90/06/24 14:54:32 bostic 7 6
c cleanups, don't define TZ_DIR and NOSOLAR here, tzfile.h has them.
e
s 00001/00001/00157
d D 5.6 90/06/01 16:34:35 bostic 6 5
c man page in the right palce
e
s 00025/00015/00133
d D 5.5 90/05/11 13:54:47 bostic 5 4
c first pass for new make
e
s 00001/00001/00147
d D 5.4 89/05/10 22:44:30 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00008/00014/00140
d D 5.3 89/03/17 16:53:01 bostic 3 2
c more cleanup
e
s 00046/00137/00108
d D 5.2 89/03/16 20:48:57 bostic 2 1
c make it work for us
e
s 00245/00000/00000
d D 5.1 89/03/16 17:29:32 bostic 1 0
c date and time created 89/03/16 17:29:32 by bostic
e
u
U
t
T
I 1
D 5
# @(#)Makefile	4.31
E 5
I 5
#	%W% (Berkeley) %G%
E 5

# Change the line below for your time zone (after finding the zone you want in
# the time zone files, or adding it to a time zone file).
# Alternately, if you discover you've got the wrong time zone, you can just
#	zic -l rightzone

D 2
LOCALTIME=	Factory
E 2
I 2
LOCALTIME=	US/Pacific
E 2

# If you want something other than Eastern United States time as a template
# for handling POSIX-style time zone environment variables,
# change the line below (after finding the zone you want in the
# time zone files, or adding it to a time zone file).
# Alternately, if you discover you've got the wrong time zone, you can just
#	zic -p rightzone

D 2
POSIXRULES=	US/Eastern
E 2
I 2
POSIXRULES=	US/Pacific
E 2

# Use an absolute path name for TZDIR unless you're just testing the software.

D 2
TZDIR=		/etc/zoneinfo
E 2
I 2
D 4
TZDIR=	${DESTDIR}/etc/zoneinfo
E 4
I 4
TZDIR=	${DESTDIR}/usr/share/zoneinfo
E 4
E 2

# If you always want time values interpreted as "seconds since the epoch
# (not counting leap seconds)", use
# 	REDO=		posix_only
# below.  If you always want right time values interpreted as "seconds since
# the epoch" (counting leap seconds)", use
#	REDO=		right_only
# below.  If you want both sets of data available, with leap seconds not
# counted normally, use
#	REDO=		posix_right
# below.  If you want both sets of data available, with leap seconds counted
# normally, use
#	REDO=		right_posix
# below.

D 2
REDO=		posix_right
E 2
I 2
REDO=		right_only
E 2

D 2
# You may want to change this define if you're just testing the software.
# Alternatively, you can put these functions in /lib/libc.a, removing
# the old "ctime.o".  This is the
# ideal solution if you are able.  Build libz.a, extract the files, and
# then add them to libc.a.

TZLIB=		/usr/lib/libz.a

E 2
# If you're running on a System V-style system and don't want lint grief,
# add
#	-DUSG
# to the end of the "CFLAGS=" line.
#
# If you're running on a system where "strchr" is known as "index",
# (for example, a 4.[012]BSD system), add
#	-Dstrchr=index
# to the end of the "CFLAGS=" line.
#
# If you're running on a system with a "mkdir" function, feel free to add
#	-Demkdir=mkdir
# to the end of the "CFLAGS=" line
#
# If you want to use System V compatibility code, add
#	-DUSG_COMPAT
# to the end of the "CFLAGS=" line.
#
# If your system has a "GMT offset" field in its "struct tm"s
# (or if you decide to add such a field in your system's "time.h" file),
# add the name to a define such as
#	-DTM_GMTOFF=tm_gmtoff
# or
#	-DTM_GMTOFF=_tm_gmtoff
# to the end of the "CFLAGS=" line.
#
# If your system has a "GMT offset" field in its "struct tm"s
# (or if you decide to add such a field in your system's "time.h" file),
# add the name to a define such as
#	-DTM_ZONE=tm_zone
# or
#	-DTM_ZONE=_tm_zone
# to the end of the "CFLAGS=" line.
#
# If you want code inspired by certain emerging standards, add
#	-DSTD_INSPIRED
# to the end of the "CFLAGS=" line.
#
# If you want Source Code Control System ID's left out of object modules, add
#	-DNOID
# to the end of the "CFLAGS=" line.
#
# If you'll never want to handle solar-time-based time zones, add
#	-DNOSOLAR
# to the end of the "CFLAGS=" line
# (and comment out the "SDATA=" line below).
#
# If you want to allocate state structures in localtime, add
#	-DALL_STATE
# to the end of the "CFLAGS=" line.
#
# If you want an "altzone" variable (a la System V Release 3.1), add
#	-DALTZONE
# to the end of the "CFLAGS=" line.
#
# If you want a "gtime" function (a la MACH), add
#	-DCMUCS
# to the end of the "CFLAGS=" line

D 2
CFLAGS=
E 2
I 2
D 5
VPATH=	data
E 5
I 5
.PATH:	${.CURDIR}/datfiles
E 5
D 7
CFLAGS=	-Demkdir=mkdir -DTM_GMTOFF=tm_gmtoff -DTM_ZONE=tm_zone -DNOSOLAR \
	-DTZDIR=\"$(TZDIR)\"
MAN=	tzfile.0
E 7
I 7
D 9
CFLAGS=	-Demkdir=mkdir -DTM_GMTOFF=tm_gmtoff -DTM_ZONE=tm_zone
E 9
I 9
CFLAGS=	-DTM_GMTOFF=tm_gmtoff -DTM_ZONE=tm_zone
E 9
PROG=	zic
MAN5=	tzfile.0
E 7
E 2

D 2
# LINTFLAGS is set for SunOS 4.0.
# If you're using System V, you'll want to comment out the "LINTFLAGS=" line.
E 2
I 2
D 3
TZCOBJS=	zic.o scheck.o ialloc.o
TZDOBJS=	zdump.o ialloc.o
SRCS=	zic.c zdump.c scheck.c ialloc.c
E 3
I 3
D 5
OBJS=	zic.o scheck.o ialloc.o
E 5
SRCS=	zic.c scheck.c ialloc.c
I 5
D 8
OBJS=	${SRCS:.c=.o}
E 8
E 5

E 3
YDATA=	africa antarctica asia australasia europe northamerica \
	southamerica pacificnew etcetera factory
NDATA=	systemv
#SDATA=	solar87 solar88 solar89
D 7
TDATA=	$(YDATA) $(NDATA) $(SDATA)
DATA=	$(YDATA) $(NDATA) $(SDATA) leapseconds
E 7
I 7
TDATA=	${YDATA} ${NDATA} ${SDATA}
DATA=	${YDATA} ${NDATA} ${SDATA} leapseconds
E 7
USNO=	usno1988 usno1989
E 2

D 2
LINT=		lint
LINTFLAGS=	-hbaxc
E 2
I 2
D 3
all: zic zdump
E 3
I 3
D 5
all: zic
E 5
I 5
D 7
all: zic ${MAN}
E 5
E 3
E 2

D 2
SHAR=		shar
E 2
I 2
D 3
zic: $(TZCOBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(TZCOBJS) -o $@
E 3
I 3
D 5
zic: $(OBJS)
E 5
I 5
zic: $(OBJS) ${MAN}
E 5
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $@
E 3
E 2

D 2
################################################################################
E 2
I 2
D 3
zdump: $(TZDOBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(TZDOBJS) -o $@

E 3
posix_only: $(TDATA)
E 7
I 7
posix_only: ${TDATA}
E 7
D 5
	./zic -d $(TZDIR) -L /dev/null $(TDATA)
E 5
I 5
	(cd ${.CURDIR}/datfiles; \
D 7
	    ../obj/zic -d $(TZDIR) -L /dev/null $(TDATA))
E 7
I 7
	    ../obj/zic -d ${TZDIR} -L /dev/null ${TDATA})
E 7
E 5
E 2

D 2
CC=		cc -DTZDIR=\"$(TZDIR)\"
E 2
I 2
D 7
right_only: leapseconds $(TDATA)
E 7
I 7
right_only: leapseconds ${TDATA}
E 7
D 5
	./zic -d $(TZDIR) -L leapseconds $(TDATA)
E 5
I 5
	(cd ${.CURDIR}/datfiles; \
D 7
	    ../obj/zic -d $(TZDIR) -L leapseconds $(TDATA))
E 7
I 7
	    ../obj/zic -d ${TZDIR} -L leapseconds ${TDATA})
E 7
E 5
E 2

D 2
TZCSRCS=	zic.c localtime.c asctime.c \
		scheck.c ialloc.c emkdir.c getopt.c link.c
TZCOBJS=	zic.o localtime.o asctime.o \
		scheck.o ialloc.o emkdir.o getopt.o link.o
TZDSRCS=	zdump.c localtime.c asctime.c \
		ialloc.c getopt.c link.c
TZDOBJS=	zdump.o localtime.o asctime.o \
		ialloc.o getopt.o link.o
DATESRCS=	date.c localtime.c getopt.c logwtmp.c
DATEOBJS=	date.o localtime.o getopt.o logwtmp.o
LIBSRCS=	localtime.c asctime.c difftime.c
LIBOBJS=	localtime.o asctime.o difftime.o
HEADERS=	tzfile.h nonstd.h stdio.h stdlib.h time.h
NONLIBSRCS=	zic.c zdump.c scheck.c ialloc.c emkdir.c getopt.c link.c
NEWUCBSRCS=	date.c logwtmp.c
SOURCES=	$(HEADERS) $(LIBSRCS) $(NONLIBSRCS) $(NEWUCBSRCS)
DOCS=		Patchlevel.h \
		README Theory \
		date.1 newctime.3 tzfile.5 zic.8 zdump.8 \
		Makefile
YDATA=		africa antarctica asia australasia \
		europe northamerica southamerica pacificnew etcetera factory
NDATA=		systemv
SDATA=		solar87 solar88 solar89
TDATA=		$(YDATA) $(NDATA) $(SDATA)
DATA=		$(YDATA) $(NDATA) $(SDATA) leapseconds
USNO=		usno1988 usno1989
ENCHILADA=	$(DOCS) $(SOURCES) $(DATA) $(USNO)
E 2
I 2
D 7
other_two: leapseconds $(TDATA)
E 7
I 7
other_two: leapseconds ${TDATA}
E 7
D 5
	./zic -d $(TZDIR)/posix -L /dev/null $(TDATA)
	./zic -d $(TZDIR)/right -L leapseconds $(TDATA)
E 5
I 5
D 11
	(cd ${.CURDIR}/datfiles;
E 11
I 11
	(cd ${.CURDIR}/datfiles; \
E 11
D 7
	    ../obj/zic -d $(TZDIR)/posix -L /dev/null $(TDATA))
E 7
I 7
	    ../obj/zic -d ${TZDIR}/posix -L /dev/null ${TDATA})
E 7
	(cd ${.CURDIR}/datfiles; \
D 7
	    ../obj/zic -d $(TZDIR)/right -L leapseconds $(TDATA))
E 7
I 7
	    ../obj/zic -d ${TZDIR}/right -L leapseconds ${TDATA})
E 7
E 5
E 2

D 2
all:		REDID_BINARIES zdump date $(TZLIB)
E 2
I 2
posix_right: posix_only other_two
E 2

D 2
# We want to use system's logwtmp in preference to ours if available.
E 2
I 2
right_posix: right_only other_two
E 2

D 2
date:		$(DATEOBJS)
		ar r ,lib.a logwtmp.o
		-ranlib ,lib.a
		$(CC) $(CFLAGS) date.o localtime.o getopt.o -lc ,lib.a -o $@
		rm -f ,lib.a
E 2
I 2
D 3
install: install1 ${MAN} $(DATA) $(REDO)
E 3
I 3
D 7
install: ${MAN} $(DATA) $(REDO)
E 7
I 7
install: maninstall ${DATA} ${REDO}
E 7
E 3
D 5
	./zic -d $(TZDIR) -l $(LOCALTIME) -p $(POSIXRULES)
	install -c -o bin -g bin -m 444 tzfile.0 ${DESTDIR}/usr/man/man5
	chown -R bin.bin $(TZDIR)
	chmod 775 $(TZDIR)
E 5
I 5
D 10
	(cd ${.CURDIR}/datfiles; \
D 7
	    ../obj/zic -d $(TZDIR) -p $(POSIXRULES))
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 tzfile.0 \
D 6
	    ${DESTDIR}/usr/man/cat5
E 6
I 6
	    ${DESTDIR}/usr/share/man/cat5
E 7
I 7
	    ../obj/zic -d ${TZDIR} -p ${POSIXRULES})
E 10
I 10
	(cd ${.CURDIR}/datfiles && ../obj/zic -d ${TZDIR} -p ${POSIXRULES})
E 10
E 7
E 6
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${TZDIR}/${LOCALTIME} ${DESTDIR}/etc/localtime
D 7
	chown -R ${BINOWN}.${BINGRP} $(TZDIR)
	chmod -R a-w $(TZDIR)
E 5
E 2

D 2
REDID_BINARIES:	zic $(DATA) $(REDO)
		./zic -d $(TZDIR) -l $(LOCALTIME) -p $(POSIXRULES)
		touch $@
E 2
I 2
D 3
install1:
	-mkdir $(TZDIR)
E 2

E 3
D 2
posix_only:	zic $(TDATA)
		./zic -d $(TZDIR) -L /dev/null $(TDATA)

right_only:	zic leapseconds $(TDATA)
		./zic -d $(TZDIR) -L leapseconds $(TDATA)

other_two:	zic leapseconds $(TDATA)
		./zic -d $(TZDIR)/posix -L /dev/null $(TDATA)
		./zic -d $(TZDIR)/right -L leapseconds $(TDATA)

posix_right:	posix_only other_two

right_posix:	right_only other_two

zdump:		$(TZDOBJS)
		$(CC) $(CFLAGS) $(LFLAGS) $(TZDOBJS) -o $@

# The "ar d" command below ensures that obsolete object files are eliminated
# from the library.

$(TZLIB):	$(LIBOBJS)
		ar ru $@ $(LIBOBJS)
		-ar d $@ timemk.o ctime.o
		-ranlib $@

zic:		$(TZCOBJS)
		$(CC) $(CFLAGS) $(LFLAGS) $(TZCOBJS) -o $@

SHARS:		SHAR1.Z SHAR2.Z SHAR3.Z SHAR4.Z SHAR5.Z SHAR6.Z SHAR7.Z

SHAR1.Z:	$(DOCS)
		$(SHAR) $(DOCS) | compress > $@

SHAR2.Z:	$(HEADERS) $(LIBSRCS)
		$(SHAR) $(HEADERS) $(LIBSRCS) | compress > $@

SHAR3.Z:	$(NONLIBSRCS)
		$(SHAR) $(NONLIBSRCS) | compress > $@

SHAR4.Z:	$(YDATA) $(NDATA) leapseconds
		$(SHAR) $(YDATA) $(NDATA) leapseconds | compress > $@

SHAR5.Z:	$(SDATA)
		$(SHAR) $(SDATA) | compress > $@

SHAR6.Z:	$(USNO)
		$(SHAR) $(USNO) | compress > $@

SHAR7.Z:	$(NEWUCBSRCS)
		$(SHAR) $(NEWUCBSRCS) | compress > $@

sure:		$(SOURCES)
		for i in "$(TZCSRCS)" "$(TZDSRCS)" "$(DATESRCS)" "$(LIBSRCS)"; \
		do $(LINT) $(LINTFLAGS) $(CFLAGS) -DTZDIR=\"$(TZDIR)\" $$i ; \
		done

# "/usr/5bin/lint -p" can dump core on SunOS 4.0, so no -p below. . .

SURE:		sure $(ENCHILADA)
		make sure LINT=/usr/5bin/lint LINTFLAGS=-DUSG
		make sure LINT=gcc LINTFLAGS="-c -O -ansi -pedantic -Wall"
		rm -f zic zdump *.o
		spell $(ENCHILADA)

E 2
clean:
D 2
		rm -f core *.o *.out REDID_BINARIES zdump zic date SHAR* ,*
E 2
I 2
D 3
	rm -f core *.o zdump zic
E 3
I 3
	rm -f core *.o zic
E 3
E 2

D 2
CLEAN:		clean
		sccs clean
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend
E 2

D 2
names:
		@echo $(ENCHILADA)
E 2
I 2
depend: $(SRCS)
D 5
	mkdep $(CFLAGS) $(SRCS)
E 5
I 5
	mkdep ${CFLAGS} ${.ALLSRC}
E 5
E 2

D 2
asctime.o:	nonstd.h stdio.h time.h tzfile.h
difftime.o:	nonstd.h time.h
emkdir.o:	nonstd.h stdio.h stdlib.h
ialloc.o:	nonstd.h stdlib.h
link.o:		nonstd.h stdio.h
localtime.o:	nonstd.h stdio.h stdlib.h time.h tzfile.h
scheck.o:	nonstd.h stdio.h stdlib.h
zic.o:		nonstd.h stdio.h stdlib.h time.h tzfile.h

.KEEP_STATE:
E 2
I 2
D 5
lint:
E 5
I 5
lint tags:
E 7
I 7
	chown -R ${BINOWN}.${BINGRP} ${TZDIR}
	chmod -R a-w ${TZDIR}
E 7

.include <bsd.prog.mk>
E 5
E 2
E 1
