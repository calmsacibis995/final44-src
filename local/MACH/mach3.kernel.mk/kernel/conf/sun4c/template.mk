#
# Mach Operating System
# Copyright (c) 1993 Carnegie Mellon University
# All Rights Reserved.
# 
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
# 
# CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
# CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
# ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
# 
# Carnegie Mellon requests users of this software to return to
# 
#  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
#  School of Computer Science
#  Carnegie Mellon University
#  Pittsburgh PA 15213-3890
# 
# any improvements or extensions that they make and grant Carnegie Mellon 
# the rights to redistribute these changes.
#
######################################################################
# HISTORY
# $Log:	template.mk,v $
# Revision 2.3  93/05/14  15:05:54  rvb
# 	Don't define CC_OPT_LEVEL; let user do it
# 
# Revision 2.2  93/02/04  16:48:24  mrt
# 	Changes for compiling under ode.
# 	Added -Xlinker flag for -X to ld.
# 	[93/01/26            berman]
# 
# Revision 2.1.2.3  93/01/24  12:09:14  berman
# 	Changes for gcc.
# 	Changed IDENT to include a -Imachine to get at sun4/scsi.
# 	Created for Sparc (sun4) port.  Updated copyright.
# 	[93/01/12            berman]
# 
# 
######################################################################
#BEGIN	Machine dependent Makefile fragment for the SUN4C
######################################################################

SUN4_CC		= gcc -fno-builtin

IDENT		+= -Dasm=__asm__

INCFLAGS	+= -I../sun4

LD		= /bin/ld
MK_LDFLAGS	= -e _start -N -p -Xlinker -X -T F8004000

LDOBJS_PREFIX	= locore.o

${SOBJS}:	assym.s

#
######################################################################
#END	 Machine dependent Makefile fragment for the SUN4C
######################################################################
