h60495
s 00007/00006/00087
d D 1.5 93/07/27 09:18:06 bostic 6 5
c checkpoint; Mike Karels left this checked out.
e
s 00007/00007/00086
d D 1.4 88/03/26 21:10:36 karels 5 3
c fix last fix
e
s 00006/00006/00087
d R 1.4 88/03/26 19:59:34 karels 4 3
c fix last fix
e
s 00010/00020/00083
d D 1.3 88/03/23 10:17:33 karels 3 2
c cleanups
e
s 00001/00001/00102
d D 1.2 87/09/15 12:53:56 edward 2 1
c merged changes from Monet
e
s 00103/00000/00000
d D 1.1 87/09/15 12:17:36 edward 1 0
c date and time created 87/09/15 12:17:36 by edward
e
u
U
t
T
I 1
D 5
#	%W% %G%
E 5
I 5
#	%W% (Berkeley) %G%
E 5
# transcript/src/Makefile.bsd
#
# Copyright (C) 1985 Adobe Systems Incorporated
#
# RCSID: $Header: Makefile.bsd,v 2.1 85/11/24 11:48:44 shore Rel $


D 3
LPROGS = psbanner pscomm psrv pstext
BPROGS = enscript ps4014 ps630 pscat pscatmap psdit psplot psrev psgrind
E 3
I 3
LIBPROGS = psbanner pscatmap pscomm psrv pstext
D 5
BINPROGS = enscript ps4014 ps630 psplot psgrind
LNPROGS = pscat psdit psplot psrev psrev
E 5
I 5
BINPROGS = enscript ps4014 ps630 psgrind
LNPROGS = pscat psdit psplot psrev
E 5
E 3

OBJECTS = psbanner.o pscomm.o psrv.o pstext.o \
	enscript.o ps4014.o ps630.o pscat.o pscatmap.o \
D 5
	psdit.o psplot.o psrev.o \
	psutil.o
E 5
I 5
	psdit.o psplot.o psrev.o psutil.o
E 5

#
# These values are automatically inserted into the appropriate
# variables in config.c when it is created from config.proto.
# They should be set up here for the local site.
#
PSLIBDIR = /usr/local/lib/ps
I 6
BINDIR = /usr/local/bin
E 6
TROFFFONTDIR = /usr/local/lib/ps/troff.font
D 6
DITDIR = /usr/local/lib/font
E 6
I 6
DITDIR = /usr/local/libdata/ditroff_font
E 6
PSTEMPDIR = /tmp

CFLAGS = -O -DBSD

D 3
programs all:	${LPROGS} ${BPROGS}
E 3
I 3
D 5
programs all:	${LIBPROGS} ${BINPROGS}
E 5
I 5
programs all:	${LIBPROGS} ${BINPROGS} ${LNPROGS}
E 5
E 3

enscript: enscript.o psutil.o config.o getopt.o
	cc ${CFLAGS} -o enscript enscript.o psutil.o config.o getopt.o

psgrind: psgrind.o psutil.o config.o
	cc ${CFLAGS} -o psgrind psgrind.o psutil.o config.o

pscat: pscat.o psutil.o config.o getopt.o
	cc ${CFLAGS} -o pscat pscat.o psutil.o config.o getopt.o

psbanner: psbanner.o psutil.o config.o
	cc ${CFLAGS} -o psbanner psbanner.o psutil.o config.o

pscomm: pscomm.o psutil.o config.o
	cc ${CFLAGS} -o pscomm pscomm.o psutil.o config.o

pstext: pstext.o psutil.o config.o
	cc ${CFLAGS} -o pstext pstext.o psutil.o config.o

psplot: psplot.o psutil.o getopt.o config.o
	cc ${CFLAGS} -o psplot psplot.o psutil.o getopt.o config.o

psrv: psrv.o psutil.o config.o
	cc ${CFLAGS} -o psrv psrv.o psutil.o config.o

psrev: psrev.o psutil.o getopt.o config.o
	cc ${CFLAGS} -o psrev psrev.o psutil.o getopt.o config.o

ps630: ps630.o psutil.o config.o getopt.o
	cc ${CFLAGS} -o ps630 ps630.o psutil.o config.o getopt.o

ps4014: ps4014.o psutil.o config.o getopt.o
	cc ${CFLAGS} -o ps4014 ps4014.o psutil.o config.o getopt.o -lm

pscatmap: pscatmap.o psutil.o config.o
	cc ${CFLAGS} -o pscatmap pscatmap.o psutil.o config.o

psdit: psdit.o psutil.o config.o
D 2
	cc ${CFLAGS} -o psdit psdit.o psutil.o config.o 
E 2
I 2
	cc ${CFLAGS} -o psdit psdit.o psutil.o config.o -lm
E 2

${OBJECTS}: transcript.h
pscomm.o psbanner.o pscat.o: psspool.h
pscat.o pscatmap.o: action.h 

config.c: config.proto ../config
	-rm -f - config.c
	sed	-e s,PSLIBDIR,$(PSLIBDIR),g \
		-e s,TROFFFONTDIR,$(TROFFFONTDIR),g \
		-e s,DITDIR,$(DITDIR),g \
		-e s,PSTEMPDIR,$(PSTEMPDIR),g \
		config.proto >config.c

D 3
install: ${LPROGS} ${BPROGS}
	-cd $$PSLIBDIR; rm -f ${LPROGS} ${BPROGS}
	install -c -o $$OWNER -g $$GROUP -s psbanner	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s pscomm	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s psrv	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s pstext	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s enscript	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s ps4014	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s ps630	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s pscat	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s pscatmap	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s psdit	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s psplot	$$PSLIBDIR
	install -c -o $$OWNER -g $$GROUP -s psrev	$$PSLIBDIR
	-cd $$BINDIR ; rm -f ${BPROGS}
	for i in ${BPROGS} ;\
E 3
I 3
install: ${LIBPROGS} ${BINPROGS}
D 6
	install -s -o $$OWNER -g $$GROUP $(LIBPROGS) $$PSLIBDIR
	install -s -o $$OWNER -g $$GROUP $(BINPROGS) $$BINDIR
I 5
	install -s -o $$OWNER -g $$GROUP $(LNPROGS) $$PSLIBDIR
E 5
	-cd $$BINDIR ; rm -f ${LNPROGS}
E 6
I 6
	install -s -o $$OWNER -g $$GROUP $(LIBPROGS) $(PSLIBDIR)
	install -s -o $$OWNER -g $$GROUP $(BINPROGS) $(BINDIR)
	install -s -o $$OWNER -g $$GROUP $(LNPROGS) $(PSLIBDIR)
	-cd $(BINDIR ; rm -f ${LNPROGS}
E 6
	for i in ${LNPROGS} ;\
E 3
D 6
	do ln -s $$PSLIBDIR/$$i $$BINDIR ;\
E 6
I 6
	do ln $(PSLIBDIR)/$$i $(BINDIR) || ln -s $(PSLIBDIR)/$$i $(BINDIR) ;\
E 6
	done

clean:
D 3
	rm -f - *.o config.c ${BPROGS} ${LPROGS} *BAK *CKP .emacs* *~
E 3
I 3
D 5
	rm -f - *.o config.c ${BINPROGS} ${LIBPROGS} *BAK *CKP .emacs* *~
E 5
I 5
	rm -f *.o config.c ${BINPROGS} ${LIBPROGS} ${LNPROGS} .emacs* *~
E 5
E 3

E 1
