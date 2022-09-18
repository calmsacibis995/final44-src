/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	stubs.c,v $
 * Revision 2.4  91/10/09  16:18:52  af
 * 	Removed that one real routine: strlen.
 * 	[91/10/07            af]
 * 
 * Revision 2.3  91/05/08  13:27:31  dbg
 * 	Added a real routine: strlen.
 * 	[91/03/26            dbg]
 * 
 * Revision 2.2  90/01/11  11:46:35  dbg
 * 	Added freeze_all_processors, thaw_all_processors.
 * 	[89/11/20            dbg]
 * 
 */
#include <cpus.h>


/*
 * Stubs for routines I haven't written yet.
 */
doadump()
{}

turintr()
{}

tuxintr()
{}

crlintr()
{}

int	tu = 0;
int	tudata = 0;

cnrfl()
{}

conxfl()
{}

swapconf()
{}

#if	NCPUS > 1
freeze_all_processors(whichcpu)
	int	whichcpu;
{}

thaw_all_processors()
{}
#endif	NCPUS > 1
