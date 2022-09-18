#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#
# HISTORY
# $Log:	Makefile,v $
# Revision 2.2  89/07/12  00:18:26  jjc
# 	Modified for CMU CS make.
# 	[89/06/07            jjc]
# 
#

#
# @(#)Makefile 1.3 88/02/08
#

#if	CMU
#
#	Trickery to get around fact that $(machine) is "sun" 
#	instead of "sun3" on a Sun 3.
#
ARCH_sun= sun3
ARCH_sun3= sun3
ARCH_sun4= sun4
ARCH=$(ARCH_$(machine))

MACH = $(cputype)
#else	CMU
#m-sun2 = sun2
#m-sun3 = sun3
#m-sun4 = sun4
#
#ARCH = $(m$(TARGET_ARCH))
#
#m-mc68010 = m68k
#m-mc68020 = m68k
#m-sparc = sparc
#m-sunrise = sparc
#
#MACH = $(m$(TARGET_MACH))
#endif	CMU

LIBSA=	libsa.a
LIBXX=	libxx.a

# All the real work gets done in ./$(ARCH)
# Also, that's where the libraries wind up
all $(LIBSA) $(LIBXX) clean lint install install_h:
	cd $(ARCH); $(MAKE) $(MFLAGS) $@
