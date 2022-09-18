/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * 17-May-90  Robert Baron (rvb) at Carnegie-Mellon University
 *	kdb(0, 0, 0) is now a no-no
 *
 * HISTORY
 * $Log:	debug.c,v $
 * Revision 2.9.1.1  90/05/17  18:18:03  rvb
 * 	kdb(0, 0, 0) is now a no-no
 * 
 * Revision 2.9  89/09/09  15:24:11  rvb
 * 	i386: conditionalize for MACH_KDB == 0
 * 	[89/09/09            rvb]
 * 
 * Revision 2.8  89/07/14  15:39:19  rvb
 * 	Well, only call panic iff a debugger function is NOT defined.
 * 	[89/07/11            rvb]
 * 
 * Revision 2.7  89/05/30  10:37:23  rvb
 * 	Simpler strategy to get to the debugger for mips.
 * 	[89/05/16            af]
 * 
 * Revision 2.6  89/02/25  18:00:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/01/23  22:19:08  af
 * 	Hook for Mips, incomplete.
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: define Debugger to call kdb
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  88/12/20  13:50:09  rpd
 * 	ibmrt: Debugger is always in ca/machdep.c.
 * 	[88/12/08  10:40:54  rpd]
 * 
 *
 * Revision 2.3  88/12/19  02:42:45  mwyoung
 * 	Corrected include file references.
 * 	[88/11/22            mwyoung]
 * 	
 * 	Get into the debugger through panic() if there's no good
 * 	alternative.
 * 	[88/11/17  00:23:33  mwyoung]
 * 	
 * 	Remove sun3 breakpoint code.
 * 	[88/11/13            mwyoung]
 * 
 * Revision 2.2  88/10/18  03:18:23  mwyoung
 * 	Emit a breakpoint instruction on the Sun3.
 * 	[88/10/11            mwyoung]
 * 
 */

#ifndef	ibmrt
#include <mach_kdb.h>
int	Debugger_should_panic = 1;

void		Debugger(message)
	char		*message;
{
#ifdef	lint
	message++;
#endif	lint

#ifdef	vax
	asm("bpt");
#endif	vax
#if	defined(i386) && MACH_KDB > 0
	Bpt();
#endif	defined(i386) && MACH_KDB > 0
#ifdef	mips
	gimmeabreak();
#endif	mips
#if	!(defined(vax)) && !(defined(i386)) && !(defined(mips))
	if (Debugger_should_panic)
		panic(message);
#endif	alles
}

#endif	!ibmrt
