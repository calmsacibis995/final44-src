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
# Revision 2.6  91/09/23  08:41:43  mja
# 	Add ${ENVIRON_BASE} to PATH and LPATH settings.
# 	[91/09/22  03:36:59  mja]
# 
# Revision 2.5  91/04/02  12:25:31  mbj
# 	LPATH must include /usr/lib and /lib for i386_mach
# 	[90/03/26            rvb]
# 
# Revision 2.4  89/05/01  17:03:11  rpd
# 	Cleaned up, to match mach/Makefile.
# 	[89/05/01  14:52:50  rpd]
# 
# Revision 2.3  89/02/25  18:42:47  gm0w
# 	Changes for cleanup.
# 
# Revision 2.2  89/01/12  07:59:23  rpd
# 	Created.
# 	[89/01/12  04:19:33  rpd]
# 
#

MIG=LPATH=$$LPATH:${ENVIRON_BASE}/usr/mach/lib:${ENVIRON_BASE}/usr/lib:${ENVIRON_BASE}/lib PATH=$$PATH:${ENVIRON_BASE}/usr/mach/bin:${ENVIRON_BASE}/usr/bin mig
MIGOPTS = -I.. -DKERNEL
MIGKERNEL = -DKERNEL_SERVER
MIGUKERNEL = -DKERNEL_USER

MACH_DEBUG_INTERFACE =  mach_debug_server.c

all: $(MACH_DEBUG_INTERFACE)

$(MACH_DEBUG_INTERFACE):	mach_debug.defs
	$(MIG) $(MIGOPTS) $(MIGKERNEL) -server mach_debug_server.c -user /dev/null -header /dev/null mach_debug.defs

clean:
	rm -f $(MACH_DEBUG_INTERFACE)
