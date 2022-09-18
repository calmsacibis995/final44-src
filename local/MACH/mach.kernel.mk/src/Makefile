#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# Copyright (c) 1987 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.10  91/04/05  02:03:52  mbj
# 	Made install program to use machine dependent.
# 
# Revision 2.9  90/09/07  19:02:46  mrt
# 	Changed cleaner rule to clean, as sudirectory config did not
# 	have cleaner rule.  Change courtesy of Zon Williams
# 	[90/09/07            mrt]
# 
# Revision 2.8  89/02/25  19:17:29  gm0w
# 	Changes for cleanup.
# 
# Revision 2.7  89/02/07  22:56:22  mwyoung
# Code cleanup cataclysm.
# 
# Revision 2.6  88/09/01  13:58:19  mwyoung
# 	Use /usr/cs/etc/install explicitly until *that* gets installed
# 	in its proper place.
# 	[88/08/30            mwyoung]
# 	
# 	Change dependencies for ${DDIR}/omerge and ${DDIR}/makesym to
# 	the actual source files, so that they don't get repeatedly
# 	rebuilt.
# 	[88/08/30            mwyoung]
# 
# Revision 2.5  88/07/29  03:20:30  rpd
# Cleaned up some oddities; no important functional changes.
# 
# Revision 2.4  88/07/21  16:33:30  rpd
# Fixed omerge & makesym rules to depend on .x forms, not .csh forms.
# 
# Revision 2.3  88/07/20  22:47:37  rpd
# Added omerge and makesym, utilities needed for RT kernel builds.
# 
# 18-May-88  Mike Accetta (mja) at Carnegie-Mellon University
#	Added rules for new buildconf script.
#	[ V5.1(XF25) ]
#
# 20-Feb-88  Mike Accetta (mja) at Carnegie-Mellon University
#	Added entry for mkskel.install and direct installation rules
#	for the scripts needed when initializing the skeleton area.
#	[ V5.1(XF22) ]
#
# 09-May-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Replaced archive with NEWSRC rule for new archiving mechanism.
#	[ V5.1(XF11) ]
#
#  6-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
#	Removed md... this is a standard Mach utility and not part of
#	the kernel sources proper.
#
# 28-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Removed obsolete references to "as".
#	[ V5.1(F8) ]
#
# 25-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Removed assumption of uk,uk as owner of installed files.
#	[ V5.1(F3) ]
#
# 13-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
#	Added "archive" rule to check-in all modified sources.
#	[ V5.1(F2) ]
#
# 09-Dec-86  Mike Accetta (mja) at Carnegie-Mellon University
#	Created.
#	[ V5.1(F1) ]
#
#

.SUFFIXES: .csh .c .x .install

DESTDIR=
CFLAGS=	-O
DDIR=	${DESTDIR}../bin

BASEDIR=

SUBDIR=	config 
ISUBDIR= config.install

DEFAULT_INSTALL_BINARY	= install -c -s
VAX_INSTALL_BINARY	= /usr/cs/etc/install -q -s
SUN_INSTALL_BINARY	= /usr/cs/etc/install -q -s
SUN3_INSTALL_BINARY	= /usr/cs/etc/install -q -s
SUN4_INSTALL_BINARY	= /usr/cs/etc/install -q -s
IBMRT_INSTALL_BINARY	= /usr/cs/etc/install -q -s
MMAX_INSTALL_BINARY	= /usr/cs/etc/install -q -s
PMAX_INSTALL_BINARY	= /usr/cs/etc/install -q -s
INSTALL_BINARY		= ${${TARGET_MACHINE}_INSTALL_BINARY?${${TARGET_MACHINE}_INSTALL_BINARY}:${DEFAULT_INSTALL_BINARY}}

DEFAULT_INSTALL_SCRIPT	= install -c
VAX_INSTALL_SCRIPT	= /usr/cs/etc/install -q -xc
SUN_INSTALL_SCRIPT	= /usr/cs/etc/install -q -xc
SUN3_INSTALL_SCRIPT	= /usr/cs/etc/install -q -xc
SUN4_INSTALL_SCRIPT	= /usr/cs/etc/install -q -xc
IBMRT_INSTALL_SCRIPT	= /usr/cs/etc/install -q -xc
MMAX_INSTALL_SCRIPT	= /usr/cs/etc/install -q -xc
PMAX_INSTALL_SCRIPT	= /usr/cs/etc/install -q -xc
INSTALL_SCRIPT		= ${${TARGET_MACHINE}_INSTALL_SCRIPT?${${TARGET_MACHINE}_INSTALL_SCRIPT}:${DEFAULT_INSTALL_SCRIPT}}

ALL=	omerge.x makesym.x
IALL=	arch.install check_cond.install doconf.install mkskel.install \
	domerge.install hinstall.install remerge.install prune.install \
	buildconf.install omerge.install makesym.install

all:	${ALL} ${SUBDIR}

install: ${IALL} ${ISUBDIR}

${SUBDIR}: FRC
	cd $@ && $(MAKE)

${ISUBDIR}: FRC
	cd $@ && $(MAKE) DESTDIR=${DESTDIR} install

FRC:

.c.x:
	${CC} ${CFLAGS} -o $*.x $*.c


${DDIR}/omerge: omerge.c
	${CC} ${CFLAGS} -o omerge.x omerge.c
	@$(MAKE) DDIR=${DDIR} omerge.install

${DDIR}/makesym: makesym.c
	${CC} ${CFLAGS} -o makesym.x makesym.c
	@$(MAKE) DDIR=${DDIR} makesym.install

${DDIR}/buildconf: buildconf.csh
	@$(MAKE) DDIR=${DDIR} buildconf.install

${DDIR}/doconf: doconf.csh
	@$(MAKE) DDIR=${DDIR} doconf.install

${DDIR}/hinstall: hinstall.csh
	@$(MAKE) DDIR=${DDIR} hinstall.install

${DDIR}/mkskel: mkskel.csh
	@$(MAKE) DDIR=${DDIR} mkskel.install

${DDIR}/mksysprogs: mksysprogs.csh
	@$(MAKE) DDIR=${DDIR} mksysprogs.install

.csh.install:
	${INSTALL_SCRIPT} $*.csh ${DDIR}/$*

.x.install:
	${INSTALL_BINARY} $*.x ${DDIR}/$*

clean:
	rm -f *.o *.x
	@for i in ${SUBDIR}; do echo "[ $$i ]";(cd $$i; make clean); done


#  Display any newly modified source files (e.g. for archive)

NEWSRC=.

NEWSRC: ${NEWSRC}

${NEWSRC}: Makefile *.csh
	@echo $?
