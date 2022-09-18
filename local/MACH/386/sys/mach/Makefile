# 
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.7.4.1  90/03/28  08:31:15  rvb
# 	LPATH must include /usr/lib and /lib for i386_mach
# 	[90/03/26            rvb]
# 
# Revision 2.7  89/05/20  11:16:28  mrt
# 	Renamed mach.h to mach_interface.h
# 	[89/05/20  11:07:27  mrt]
# 
# Revision 2.6  89/05/06  02:57:43  rpd
# 	Instead of generate mach_user.c, generate individual files
# 	for each routine in the interface.  (The ones that are used
# 	are included by kern/mach_user_internal.c.)
# 	[89/05/06  02:44:39  rpd]
# 
# Revision 2.5  89/05/01  17:02:34  rpd
# 	Cleaned up.  Now mig mach.defs with -DKERNEL_SERVER directly, instead
# 	of having -DKERNEL imply that, and mig all interfaces with -DKERNEL.
# 	[89/05/01  14:51:37  rpd]
# 
# Revision 2.4  89/04/08  23:40:06  rpd
# 	General cleanup, taking advantage of new Mig features.
# 	[89/04/08  22:51:59  rpd]
# 
# Revision 2.3  89/02/25  18:12:00  gm0w
# 	Changes for cleanup.
# 
# Revision 2.2  89/01/15  16:28:47  rpd
# 	Created from kern/Makefile.
# 	[89/01/15  14:42:16  rpd]
# 
# Revision 2.6  89/01/12  07:43:36  rpd
# 	Moved -I.. from MIGKERNEL to MIGOPTS so it gets used on everything.
# 	[89/01/12  04:37:52  rpd]
# 
# Revision 2.5  88/11/21  16:56:01  rvb
# 	Somehow the mach device interface got left out of "all".
# 	[88/11/10            rvb]
# 
# Revision 2.4  88/07/17  19:33:46  mwyoung
# *** empty log message ***
# 
# Revision 2.2.1.2  88/07/04  15:28:14  mwyoung
# Moved pager_* files to memory_object_* names.
# 
# Revision 2.2.1.1  88/06/28  20:29:15  mwyoung
# Added switches to MiG so that build-dependent options can
# be used.  Removed old obsolete-code-stripping magic.
# 
# 26-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
#	Added switches to MiG so that build-dependent options can
#	be used.  Removed old obsolete-code-stripping magic.
#
# Revision 2.3  88/07/15  16:07:17  mja
# Change MIG definition to include /usr/mach along relevant paths
# since it is not in the default set.
# 
# 28-Mar-88  Douglas Orr (dorr) at Carnegie-Mellon University
#	Added device.defs rules
#
#  9-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
#	Added pager_default interface.
#
#  3-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
#	Added rule for "mach_user_internal.c".
#	Removed old history.
#

######################################################################
#
#	Builds RPC interfaces for kernel functions
#
######################################################################

MIG=LPATH=$$LPATH:/usr/lib:/lib PATH=$$PATH:/usr/bin mig
MIGOPTS = -I.. -DKERNEL
MIGKERNEL = -DKERNEL_SERVER
MIGUKERNEL = -DKERNEL_USER

MACH_INTERFACE =  mach_interface.h mach_server.c mach_user_internal.h
PAGER_INTERFACE = memory_object_user.h memory_object_server.c memory_object_user.c
DEFAULT_PAGER_INTERFACE = memory_object_default.h memory_object_default_server.c memory_object_default_user.c
EXC_INTERFACE = exc.h exc_server.c exc_user.c
DEVICE_INTERFACE = device.h device_server.c device_user.c

all:	${MACH_INTERFACE} ${PAGER_INTERFACE} ${DEFAULT_PAGER_INTERFACE}	\
	${EXC_INTERFACE} ${DEVICE_INTERFACE}

$(MACH_INTERFACE):	mach.defs
	${MIG} ${MIGOPTS} ${MIGKERNEL} -i -server mach_server.c -header mach_interface.h mach.defs
	-egrep 'Routine ' < mach_interface.h | sed -e 's/.*Routine \([a-z_]*\).*/#define \1 \1_EXTERNAL/' > mach_user_internal.h

$(PAGER_INTERFACE):	memory_object.defs
	${MIG} ${MIGOPTS} ${MIGUKERNEL} -header memory_object_user.h -user memory_object_user.c -server memory_object_server.c memory_object.defs

$(DEFAULT_PAGER_INTERFACE):	memory_object_default.defs
	${MIG} ${MIGOPTS} ${MIGUKERNEL} -user memory_object_default_user.c -server memory_object_default_server.c memory_object_default.defs

$(EXC_INTERFACE):	exc.defs
	${MIG} ${MIGOPTS} -user exc_user.c -server exc_server.c exc.defs

$(DEVICE_INTERFACE):	device.defs
	${MIG} ${MIGOPTS} -user device_user.c -server device_server.c device.defs

clean:
	rm -f $(MACH_INTERFACE)
	rm -f $(PAGER_INTERFACE)
	rm -f $(DEFAULT_PAGER_INTERFACE)
	rm -f $(EXC_INTERFACE)
	rm -f $(DEVICE_INTERFACE)
