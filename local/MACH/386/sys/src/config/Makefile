#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.8.1.1  90/02/01  13:38:02  rvb
# 	Use -lcs for CS library.
# 	Fix install.
# 	[90/01/22            rvb]
# 
# Revision 2.8  89/05/30  10:41:37  rvb
# 	Made explicit the depend on libcs.a (for fopenp).
# 	[89/04/20            af]
# 
# Revision 2.7  89/02/25  19:17:50  gm0w
# 	Changes for cleanup.
# 
# Revision 2.6  89/02/07  22:56:09  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.5  89/01/23  22:21:19  af
# 	Added def of CMU for those who do not have the light yet.
# 	[89/01/16  17:42:42  af]
# 
# Revision 2.4  88/09/01  13:53:35  mwyoung
# 	Use /usr/cs/etc/install until it's placed correctly.
# 	[88/08/30            mwyoung]
# 
# Revision 2.3  88/07/29  03:20:45  rpd
# Cleaned up some oddities; no real functional changes.
# 
# 24-Mar-88  Mike Accetta (mja) at Carnegie-Mellon University
#	Added DESTDIR, DDIR and SRCS macros and parameterized
#	installation rules so that they can optionally be used to build
#	and install a new version if the sources are newer than the
#	currently installed binary.
#	[ V5.1(XF22) ]
#
# 09-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Add ${CFILES} to "depend" rule.
#	[ V5.1(XF21) ]
#
# 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
#	Mod config.x rule to take $P (for parallel make).
#
# 09-Dec-86  Mike Accetta (mja) at Carnegie-Mellon University
#	Install in bin/config with the other kernel maintenance
#	programs.
#
# 31-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
#	Build config.x instead of config.  Make install move config.x to
#	config (../../conf/config is a symbolic link to here).
#
# 19-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
#	Added -q to install and moved destination from /etc to conf.
#

#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.3 (Berkeley) 2/18/86
#
#

CFILES_SRC =	main.c mkioconf.c mkmakefile.c \
		mkglue.c mkheaders.c mkswapconf.c
CFILES=	y.tab.c lex.yy.c ${CFILES_SRC}
SRCS=${CFILES_SRC} config.h config.y config.l

OBJS=	y.tab.o main.o lex.yy.o mkioconf.o mkmakefile.o \
	mkglue.o mkheaders.o mkswapconf.o

DDIR=../../bin

CFLAGS=-O -DCMU
LDFLAGS=-ll -lcs

config.x:$P ${OBJS}
	${CC} ${OBJS} -o config.x ${LDFLAGS}

lex.yy.c: config.l
	lex config.l

y.tab.h y.tab.c: config.y
	yacc -d config.y

clean:
	rm -f ${OBJS} lex.yy.c y.tab.c y.tab.h config.x

${DDIR}/config: ${SRCS}
	@$(MAKE) DDIR=${DDIR} install

install: config.x
	install -c -s config.x ${DDIR}/config

lint: ${CFILES}
	lint ${CFILES}


depend: ${CFILES}
	grep '^#include' ${CFILES} | grep -v '<' | \
	sed -e 's/:[^"]*"\([^"]*\)".*/: \1/' \
	    -e 's/\.c/.o/' \
	    -e 's,../[a-zA-Z]*/,,' | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' > makedep
	echo '$$r makedep' >>eddep
	echo '/^# DO NOT DELETE THIS LINE/+1,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep

# DO NOT DELETE THIS LINE -- make depend uses it

y.tab.o: config.h
lex.yy.o: y.tab.h config.h
main.o: y.tab.h config.h
mkioconf.o: y.tab.h config.h
mkmakefile.o: y.tab.h config.h
mkglue.o: config.h y.tab.h
mkheaders.o: config.h y.tab.h
mkswapconf.o: config.h
