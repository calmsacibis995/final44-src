#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.2  89/07/12  01:17:24  jjc
# 	     Picked up from SunOS 4.0.
# 	[89/07/03            jjc]
# 
#
#
# @(#)Makefile 1.4 88/02/08 SMI
#
# Makefile for /boot, boot blocks, and related stand-alone programs 

ARCH=	sun4
MACH=	sparc
ARCHDIR=../${MACH}
TARGET_ARCH= -${MACH}

BOOTBLOCKS= bootpr bootxd bootxy

all: $$(ALL)

include ../boot/Makefile.com

install_mdec:
	install bootpr $(DESTDIR)/usr/mdec/rawboot
	install bootpr $(DESTDIR)/usr/mdec/bootsd
	install bootxd $(DESTDIR)/usr/mdec
	install bootxy $(DESTDIR)/usr/mdec
