#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.15  91/09/24  20:08:12  mja
# 	Reorganize to use Makefile-common;  add ${ENVIRON_BASE} to
# 	libcs.a path.
# 	[91/09/22  03:38:22  mja]
# 
# Revision 2.14  91/05/24  16:03:38  mbj
# 	Changed MACII -> MAC2 to match Mt. Xinu Mac2 distribution.
# 
# Revision 2.13  91/04/05  02:05:15  mbj
# 	Made install program to use machine dependent.
# 	Added default LDFLAGS value.
# 
# Revision 2.12  91/04/03  16:52:39  mbj
# 	Added SUN3_LDFLAGS, LUNA88K_LDFLAGS, MACII_LDFLAGS.
# 
# Revision 2.11  91/04/02  16:07:12  mbj
# 	Changed ${MACHINE} reference to ${TARGET_MACHINE}.
# 
# Revision 2.10  91/04/02  12:16:13  mbj
# 	Use -lcs for CS library.
# 	Fix install.
# 	[90/01/22            rvb]
# 
# Revision 2.9  90/09/04  17:04:37  bohman
# 	Changed invocation of 'install', removed '-q', added '-c'.
# 	Made LDFLAGS machine dependent: macmach does not have a libcs.a
# 	instead, those functions are in the default libc.
# 	[90/08/28            bohman]
# 
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

PROGRAMS	= config

OFILES		= $P config.o lex.yy.o main.o mkioconf.o mkmakefile.o \
		  mkglue.o mkheaders.o mkswapconf.o
CFILES		= ${OFILES:.o=.c}

VAX_LIBS	= -ll ${ENVIRON_BASE}/usr/cs/lib/libcs.a
SUN_LIBS	= -ll ${ENVIRON_BASE}/usr/cs/lib/libcs.a
SUN3_LIBS	= -ll ${ENVIRON_BASE}/usr/cs/lib/libcs.a
SUN4_LIBS	= -ll ${ENVIRON_BASE}/usr/cs/lib/libcs.a
IBMRT_LIBS	= -ll ${ENVIRON_BASE}/usr/cs/lib/libcs.a
MMAX_LIBS	= -ll ${ENVIRON_BASE}/usr/cs/lib/libcs.a
PMAX_LIBS	= -ll ${ENVIRON_BASE}/usr/cs/lib/libcs.a
I386_LIBS	= -ll -lcs
AT386_LIBS	= -ll -lcs
LUNA88K_LIBS	= -ll -lcs

LIBS		= ${${TARGET_MACHINE}_LIBS?${${TARGET_MACHINE}_LIBS}:-ll}
CFLAGS		= -DCMU
YFLAGS		= -d
GARBAGE		= Makefile.bak config.c lex.yy.c y.tab.h y.tab.c

# XXX no rule for lex in Makefile-common yet XXX
lex.yy.c: config.l
	lex config.l

y.tab.h: config.y


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

include ../../${MAKETOP}Makefile-common

# DO NOT DELETE THIS LINE -- make depend uses it

config.o: config.h
lex.yy.o: y.tab.h config.h
main.o: y.tab.h config.h
mkioconf.o: y.tab.h config.h
mkmakefile.o: y.tab.h config.h
mkglue.o: config.h y.tab.h
mkheaders.o: config.h y.tab.h
mkswapconf.o: config.h
