#
# @(#)Makefile 1.11 88/02/08
#
######################################################################
# HISTORY
# $Log:	Makefile,v $
# Revision 2.3  89/07/12  12:24:33  jjc
# 	    Modified for CMU CS make.
# 	[88/11/14            jjc]
# 
#
######################################################################

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

# All the real work gets done in ./$(ARCH)
# Also, that's where the targets wind up
#if	CMU
all boot lint install install_h:
	rm -f mon
	ln -s include/mon mon
	rm -f include/machine
	ln -s $(ARCH) include/machine
	cd $(ARCH); $(MAKE) $(MFLAGS) $@
	rm -f boot/sizecheck
#else	CMU
#all boot lint install install_h:
#	cd $(ARCH); $(MAKE) $(MFLAGS) $@
#	rm -f boot/sizecheck
#endpif	CMU

#if	CMU
#
#	Need the following dependencies to force make to try to make
#	the boot program.  Otherwise, make will always think that
#	`boot' is up to date because there is a subdirectory here
#	named "boot".
#
boot:	FRC

FRC:

#endif	CMU

clean:
	cd $(ARCH); $(MAKE) $(MFLAGS) clean
	cd lib; $(MAKE) $(MFLAGS) clean
	cd boot; $(MAKE) $(MFLAGS) clean

#if	CMU
.EXPORT: ARCH MACH
#else	CMU
#.DEFAULT:
#	sccs get -G$@ $@
#endif	CMU
