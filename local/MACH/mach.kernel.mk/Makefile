#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.44  91/10/28  15:08:47  mja
# 	Use "kernel_default" rather than "default" as default build
# 	rule since Makefile-common already defines "default".
# 	[91/10/28  15:08:11  mja]
# 
# Revision 2.43  91/10/28  13:39:18  mja
# 	Added I386_cpu since TARGET_MACHINE on the i386 is I386.
# 	Left AT386 for backwards compatibility for old version of
# 	make.
# 	[91/10/17            mrt]
# 	Add an explicit "default" rule near the top to keep changes in make
# 	files included later from accidentally overriding the default.
# 	[91/10/28  12:33:43  mja]
# 
# Revision 2.42  91/09/26  14:48:41  mja
# 	Always remove KERNEL.* symbolic link before building and
# 	recreate when completed successfully;  always update the
# 	CLEAN.* trigger whenever the corresponding kernel has changed.
# 	[91/09/26  12:53:11  mja]
# 
# Revision 2.41  91/09/25  17:02:59  mja
# 	Move convenience targets to the top of the file so that "kernel" is
# 	used by default to preserve the old default behavior when not using
# 	build.
# 	[91/09/25  17:02:36  mja]
# 
# Revision 2.40  91/09/24  20:07:18  mja
# 	Coalesce make and pmake cases;  move configurations to
# 	Makefile-configs; add release options;  use makepath to create
# 	directories since making them direct dependencies causes make
# 	to include their modification times in its date checks;  make
# 	config build less verbose.
# 	[91/09/23  22:14:24  mja]
# 
# 	Reorganize for use with build(1) and connect to Makefile-
# 	common;  eliminate buildconf rule;  eliminate redundant
# 	${*_cpu} macros;  eliminate duplicate ${*_OUTPUT} macros;  run
# 	config directly from its build directory;  centralize all mkdir
# 	operations in one rule.
# 	[91/09/22  03:26:53  mja]
# 
# Revision 2.39  91/05/24  16:03:17  mbj
# 	Changed MACII -> MAC2 to match Mt. Xinu Mac2 distribution.
# 
# Revision 2.38  91/04/04  10:39:57  mbj
# 	Defined SUN3_OUTPUT.
# 
# Revision 2.37  91/04/03  12:52:54  mbj
# 	add "cases" for luna88k
# 	[91/03/07  11:38:30  rvb]
# 
# Revision 2.36  91/04/02  16:05:06  mbj
# 	Changed ${MACHINE} and ${machine} references to ${TARGET_MACHINE}.
# 	[91/04/02            mbj]
# 
# Revision 2.35  90/09/04  17:14:45  bohman
# 	Changes for mac2.
# 	[90/08/28            bohman]
# 
# Revision 2.34  90/06/12  17:43:16  mja
# 	Add missing src/buildconf.csh dependency for ./bin/buildconf.
# 	[90/06/12            mja]
# 
# Revision 2.33  89/10/03  22:05:56  rpd
# 	Fixed line for buildconf; to cd into "src" instead of "src/config".
# 
# Revision 2.32  89/09/25  22:20:10  mja
# 	Correct bug in using "$$S" instead of "src/config" for cd.
# 	[89/09/22  17:59:33  mja]
# 
# 	Purge SRCSUFFIX.
# 	[89/07/10            bww]
# 
# Revision 2.31.1.1  89/11/10  11:00:47  rvb
# 	Let i386 also be at386 ... for now.
# 	[89/11/09            rvb]
# 
# Revision 2.31  89/08/10  14:20:30  jsb
# 	Added code to save CONFIG in vers.config file.
# 	[89/08/10            gm0w]
# 
# Revision 2.30  89/08/08  21:45:07  jsb
# 	Defined pmax_cpu and PMAX_OUTPUT.
# 	[89/08/03            rvb]
# 
# Revision 2.29  89/07/11  11:25:51  jjc
# 	Defined sun4_cpu and SUN_OUTPUT.
# 	[89/04/15            jjc]
# 
# Revision 2.28  89/06/27  00:22:45  rpd
# 	Added some dependencies.
# 	[89/06/26  23:34:48  rpd]
# 
# Revision 2.27  89/04/22  15:12:18  gm0w
# 	Changed commands to create the "make" script for the build area
# 	into a sed of "conf/make.template".  Moved commands to create
# 	configuration for build into "conf/mkconfig.csh".
# 	[89/04/14            gm0w]
# 
# Revision 2.26  89/04/18  16:41:50  mwyoung
# 	Allow additional flags (e.g., "-p") to be passed to config.
# 	[89/01/05            mwyoung]
# 
# Revision 2.18.3.1  89/03/27  22:55:09  mwyoung
# 	Allow additional flags (e.g., "-p") to be passed to config.
# 	[89/01/05            mwyoung]
# 
# Revision 2.25  89/03/07  00:48:53  rpd
# 	Removed ../sys from the CPATH used in the build directory.
# 
# Revision 2.24  89/02/25  14:12:36  gm0w
# 	Changes for cleanup.
# 
# Revision 2.23  89/02/25  14:07:41  gm0w
# 	Changes for cleanup.
# 
# Revision 2.22  89/01/31  01:19:58  rpd
# 	Support multimax.
# 	[89/01/24            dlb]
# 
# Revision 2.21  89/01/23  22:01:13  af
# 	Changes for MIPS and I386: <foo>_cpu, <FOO>_OUTPUT, and FEATURES_<FOO>
# 	[89/01/09            rvb]
# 
# Revision 2.20  88/12/22  11:52:53  mja
# 	Remove Makefile.top-level before copying to it in case it may
# 	already exist non-writeable.
# 
# Revision 2.19  88/12/20  13:38:27  rpd
# 	Fixed the log (??).
# 	[88/11/26  21:13:27  rpd]
# 
# Revision 2.18  88/10/18  03:13:20  mwyoung
# 	Make it possible to invoke this Makefile using the SOURCE_DIR
# 	technology -- getting Makefile from ".." only worked because
# 	VPATH was being used.
# 	[88/10/10            mwyoung]
# 
# Revision 2.17  88/09/27  17:29:50  rvb
# 	Fixed Log
# 
# Revision 2.16  88/09/27  16:05:59  rvb
# 	Add new pmake target and PMAKE variable and link pmake to make
# 	in the build directory.
# 	[88/09/25            rvb]
# 
# Revision 2.15  88/09/07  15:44:57  rpd
# 	Moved CONFIG macros to Makeconf, so that the user
# 	can easily customize them by modifying Makeconf.
# 	[88/09/07  01:53:58  rpd]
# 	
# 	Removed redundant definition of CONFIG_SUFFIX as empty string.
# 	This allows a definition to go into Makeconf if desired.
# 	[88/09/05  23:46:20  rpd]
# 	
# 	Eliminated a dependency on ${CONFIG}.
# 	Use dependencies to create ${CONFIG}/Makeconf.
# 	[88/09/05  21:41:22  rpd]
# 	
# 	Fixed typo.
# 	[88/09/05  20:51:19  rpd]
# 	
# 	Removed dependencies on directories; they cause to many recompilations.
# 	Put VPATH and OBJECTDIR values into the make script when it is generated.
# 	Moved from NO_SOURCE_DIR to USE_SOURCE_DIR.
# 	[88/09/05  20:30:48  rpd]
# 	
# 	Fixed up some more.  Now VPATH's value isn't wired-in to the script when
# 	it is created.
# 	[88/09/02  18:15:05  rpd]
# 	
# 	Several changes with the following goals:
# 	 1) The object directory can be a subdirectory of the source directory.
# 	 Solution: create an empty Makeconf file in the object directory, so
# 	 that makes in the object directory don't get confused by a Makeconf
# 	 file that might be in the source directory.
# 	
# 	 2) The generated make script in the object directory now properly handles
# 	 passed-in VPATHs with zero, one, or more components.  When possible, it
# 	 tries to use SOURCE_DIR instead of VPATH.
# 	[88/09/02  14:04:08  rpd]
# 
# Revision 2.14  88/09/01  15:52:59  mwyoung
# 	Don't use the '-N' switch, as it turns off OBJECTDIR processing
# 	as well as Makeconf searching.  Sigh.
# 	[88/08/30            mwyoung]
# 
# Revision 2.13  88/08/30  17:22:42  mwyoung
# 	Remove occurances of string "make" from the "./make" script.
# 	[88/08/30            mwyoung]
# 
# Revision 2.12  88/08/30  00:12:25  mwyoung
# 	When building the "make" script in the build directory, don't
# 	precompute the location of the appropriate "make" program.
# 	Computing it at runtime allows for other "make" programs (e.g.,
# 	"pmake") and allows compilation to be done on more than one
# 	different machine.
# 	
# 	Move the machine-specific top-level Makefile into the
# 	machine-specific directory.
# 	[88/08/28            mwyoung]
# 	
# 	Eliminate make dependencies on ${CONFIG}... create the directory
# 	if required in the rules for a particular object.  [Otherwise, the
# 	directory modification time changes, causing things to rebuild.]
# 	[88/08/27            mwyoung]
# 
# Revision 2.11  88/08/25  19:17:44  mwyoung
# 	If the incoming VPATH is simple, pass a value in for SOURCE_DIR
# 	to reduce the number of wasted name lookups.
# 	[88/08/21            mwyoung]
# 	
# 	If the incoming VPATH is simple, pass a value in for SOURCE_DIR
# 	to reduce the number of wasted name lookups.
# 	[88/08/25  19:28:56  mwyoung]
# 
# Revision 2.10  88/08/25  18:39:56  mwyoung
# 	Added some dependencies, so that "make CONFIG=foo config" works
# 	when configuration foo doesn't have a build directory.
# 	[88/08/15  23:14:58  rpd]
# 
# Revision 2.9  88/08/06  17:57:50  rpd
# Changed the generated make script: MAKECONF should be MAKEDIR;
# do more with CPATH now.
# 
# Revision 2.8  88/07/29  03:17:03  rpd
# Removed dependencies upon Makeconf, so that the build directories
# can be subdirectories of the source directory.
# 
# Revision 2.7  88/07/21  16:25:33  rpd
# Include machine-dependent Makefile.  Slight change to config rule,
# to allow the machine-dependent Makefile to specify further actions.
# 
# Revision 2.6  88/07/19  20:40:08  mwyoung
# Always rebuild the config program... it would only get rebuilt if
# the binary didn't exist.
# Attempt to build <sys/features.h> after configuring.  If
# the set of files used to build the features file changes, then
# it will have to be rerun manually because I have no interest
# in figuring out how to get make to do it for me.
# 
# Revision 2.5  88/07/18  16:50:00  mwyoung
# Fix configuration_file-building script.
# 
# Allow "doconf" or "config" targets to be made before
# a full "make" has taken place.
# 
# Revision 2.4  88/07/16  01:04:08  mwyoung
# Resurrect MASTER.local files.
# 
# Revision 2.3  88/07/15  18:19:26  mja
# Created.
# 

#
#	Targets of interest:
#		doconf		Rebuild the configuration file
#		config		Reconfigure
#		kernel		Rebuild just the kernel
#

IBMRT_cpu=ca
SUN_cpu=sun3
PMAX_cpu=mips
AT386_cpu=i386
I386_cpu=i386
cpu=${${TARGET_MACHINE}_cpu?${${TARGET_MACHINE}_cpu}:${target_machine}}

MASTER_DIR=conf
MASTER=${MASTER_DIR}/MASTER
MASTER_CPU=${MASTER}.${cpu}
MASTER_LOCAL=${MASTER_DIR}/MASTER.local
MASTER_CPU_LOCAL=${MASTER}.${cpu}.local
CONFIG_INPUT=${CONFIG}/${CONFIG}
CONFIG_OUTPUT=${CONFIG}/$(${TARGET_MACHINE}_OUTPUT?$($(TARGET_MACHINE)_OUTPUT):Makefile)

IDIR		= /

IOWNER		= sys
IGROUP		= kmem
#  -nostrip should really be part of RELEASE_OPTIONS somehow but this is
#  currently not possible since it is overridden on the command line by build.
IMODE		= 640 -nostrip

#  Do this early to make it less likely that some future rule addition will
#  accidentally supply a new default.
kernel_default: kernel


KPREFIX		= KERNEL${KERNEL_SUFFIX?.${KERNEL_SUFFIX}:}
CPREFIX		= CLEAN${KERNEL_SUFFIX?.${KERNEL_SUFFIX}:}

#
#  Alternate name *_ILINKS prefixes used by Makefile-configs
#
SUPPRESS_ILINKS	= ${${TARGET_MACHINE}_OSUFFIX?:_}
IKPREFIX	= ${IDIR}KERNEL.${${TARGET_MACHINE}_OSUFFIX}
ICPREFIX	= ${IDIR}CLEAN.${${TARGET_MACHINE}_OSUFFIX}
ILKPREFIX	= ${SUPPRESS_ILINKS}${KPREFIX}
ILCPREFIX	= ${SUPPRESS_ILINKS}${CPREFIX}

#
#  Supply optional machine dependent build/release parameters
#
#  *_CONFIGS	- configurations to build with -here
#  *_OSUFFIX	- machine dependent other suffix for links to alternate names
#		  (when a kernel series is not supported on a platform) 
#
-include Makefile-configs

CONFIGS	= $(${TARGET_MACHINE}_CONFIGS?$($(TARGET_MACHINE)_CONFIGS):STD+ANY)

OTHERS	= ${CONFIGS/.*/${KPREFIX}.& ${CPREFIX}.&}

#
#  Convenience targets
#
kernel: ${KPREFIX}.${CONFIG}

doconf:	_doconf_${CONFIG}_

config:	_config_${CONFIG}_

#
#  Standard targets
#
#  These are the names used individually with build, e.g.
#
#	build -ta -fs /{KERNEL,CLEAN}.X.STD+WS
#
#  (CLEAN must follow KERNEL) with -here providing both the KERNEL* and CLEAN*
#  variants automatically based on the contents of the ${CONFIG}
#  macro.  We always remove the symbolic link at the start of the build
#  and recreate it when done to make sure that it exists only when the
#  kernel it points to has been successfully built.
#
KERNEL.%: _rmtop_KERNEL.%_ _all_%_ %/vmunix
	ln -s %/vmunix $@

KERNEL.${KERNEL_SUFFIX}.%: _rmtop_KERNEL.${KERNEL_SUFFIX}.%_  _all_%_ %/vmunix
	ln -s %/vmunix $@

#  These assume that KERNEL.* has already built %/vmunix if possible.
#  We need to touch the CLEAN.* trigger file whenever the kernel changes
#  to make sure that it is at least as new as the kernel, otherwise a release
#  might omit it because it hasn't changed even when the kernel has and the
#  KERNEL.* file would be released without its accompanying trigger.
CLEAN.%: %/vmunix
	echo "" >$@

CLEAN.${KERNEL_SUFFIX}.%: %/vmunix
	echo "" >$@

_rmtop_%_:
	@rm -ef %


MAKE_ARGS=
PMAKE_ARGS= -k -P6 "P=&" all

SOURCE_DIR=..

_all_%_: %/make %/Makeconf _doconf_%_ _config_%_ _make_%_

_cleanconfig_%_:
	@rm -ref ${CLEANFILES?${CLEANFILES}:*%}

_make_%_:	%/make %/Makeconf
	@echo "[ ${PMAKE?p:}making % ]"
	@cd % && USE_SOURCE_DIR=1 ./${PMAKE?p:}make CONFIG=% ${PMAKE?${PMAKE_ARGS}:${MAKE_ARGS}}

_doconf_%_: %/%

_config_%_: %/make \
				%/Makeconf \
				%/Makefile.top-level \
				./src/config/config \
				%/% \
				conf/files \
				conf/files.${cpu} \
				conf/Makefile.template \
				conf/Makefile.${cpu} \
				_configdeps_
	@cd % && \
         ./make CONFIG=% \
		CONFIG_SUFFIX=${CONFIG_SUFFIX} \
		CONFIG_FLAGS=${CONFIG_FLAGS} \
		-f Makefile.top-level \
		make.config

#  Configuration dependencies may be needed for machine dependent rules
#  so include an empty machine independent target for the other cases
#  to keep make happy.
_configdeps_::

./src/config/config: ALWAYS
	@makepath ./src/config/.
	@cd src/config && ${MAKE} _build_prefix_config 

%/Makeconf:
	@makepath ./%/.
	@echo "[ generating $@ ]"
	@-> $@

%/Makefile.top-level: Makefile
	@makepath ./%/.
	@echo "[ generating $@ ]"
	@rm -f $@; cp -p Makefile $@

%/make:	Makefile conf/make.template
	@makepath ./%/.
	@echo "[ generating $@ ]"
	@sed -e 's;@OBJECTDIR@;${OBJECTDIR};g' -e 's;@VPATH@;${VPATH};g' \
	 < conf/make.template > $@.tmp; \
	 chmod +x $@.tmp; \
         mv $@.tmp $@; \
	 rm -f %/pmake; \
	 ln $@ %/pmake

%/%:	${MASTER} ${MASTER_CPU} \
	${MASTER_LOCAL} ${MASTER_CPU_LOCAL} \
	Makefile conf/mkconfig.csh
	@makepath ./%/.
	@echo "[ generating $@ from ${MASTER_DIR}/MASTER{,.${cpu}}{,.local} ]"
	@csh -f conf/mkconfig.csh % ${MASTER} ${MASTER_CPU} ${MASTER_LOCAL} ${MASTER_CPU_LOCAL} >%/%.tmp
	@-if [ -s %/%.tmp ]; then \
	    if [ -f %/% ]; then \
		diff %/% %/%.tmp; \
		mv %/% %/%.old; \
	    fi; \
	    mv %/%.tmp %/%; \
	else \
	    rm -f %/%.tmp; \
	fi

make.config:	../${CONFIG_OUTPUT}${CONFIG_SUFFIX}

../${CONFIG_OUTPUT}${CONFIG_SUFFIX}:	\
		../${CONFIG_INPUT} \
		$(SOURCE_DIR)/conf/files \
		$(SOURCE_DIR)/conf/files.${cpu} \
		$(SOURCE_DIR)/conf/Makefile.template \
		$(SOURCE_DIR)/conf/Makefile.${cpu}
	@makepath ./sys/.
	@echo "[ configuring in ${CONFIG} ]"
	../src/config/config -c $(SOURCE_DIR)/conf ${CONFIG_FLAGS} ${CONFIG}
	@echo ${CONFIG} >vers.config

ALWAYS:

include ../../${MAKETOP}Makefile-common
-include ${cpu}/Makefile.top-level

#  This can be anywhere but fits best here.
_clean_prefix_kernel: _cleanconfig_${CONFIG}_ 

#  This must follow Makefile-common in order to override the more general
#  clean prefix rule that it would provide.
_clean_prefix_KERNEL.%: _cleanconfig_%_ 

_clean_prefix_KERNEL.${KERNEL_SUFFIX}.%: _cleanconfig_%_ 
