#
# Mach Operating System
# Copyright (c) 1993,1991,1990,1989,1988 Carnegie Mellon University
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
#
# HISTORY
# $Log:	template.mk,v $
# Revision 2.2  93/02/05  12:38:59  danner
# 	Created.
# 
# 
# Revision 2.11  93/01/14  18:10:11  danner
# 	Changed CPP definition.
# 
# Revision 2.10  92/04/05  18:29:04  rpd
# 	Modified for cross-compilation technology.
# 	[92/03/27            rpd]
# 
# Revision 2.9  92/02/19  15:07:14  elf
# 	Simplified, condensed history.
# 	[92/02/17            rpd]
# 
#
# Condensed history:
#	gcc support (dbg).
#	Created (mja).

######################################################################
#BEGIN	Machine dependent Makefile fragment for the VAX
######################################################################

LDOBJS_PREFIX = ${ORDERED}

MK_LDFLAGS = -n -e start -T 80000000

vax_init.o : assym.s

gcc_asm.h  : vax/gcc_asm.h
	cp ${vax/gcc_asm.h:P} gcc_asm.h 

OBJSDEPS += gcc_asm.h
######################################################################
#END	Machine dependent Makefile fragment for the VAX
######################################################################
