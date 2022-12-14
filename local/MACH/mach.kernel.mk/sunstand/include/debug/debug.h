/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	debug.h,v $
 * Revision 2.2  89/07/11  23:24:09  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)debug.h 1.13 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef	_debug_debug_h
#define	_debug_debug_h
/*
 * This file describes the interface between the kernel their debuggers.
 * Actually, the term ``kernel'' here is too restrictive - it actually
 * applies to any standalone program which is to be run under a debugger.
 * The term ``debugger'' here applies to any debugger service which
 * uses this interface.
 *
 * The debugger requires that nobody mess with parts of virtual
 * memory if they expect any debugger services.  These rules
 * apply to all the virtual memory between DEBUGSTART and DEBUGEND:
 *
 *   *	Do not write to these addresses.
 *   *	Do not read from (depend on the contents of) these addresses,
 *	except as documented in the debugvec structure.
 *   *	Do not remap these addresses.
 *   *	Do not change or double-map the pmegs that these addresses
 *	map through.
 *   *	Do not change or double-map the main memory that these
 *	addresses map to.
 *   *	These rules apply in
 *		all map contexts (Sun-3, Sun-4, Sun-386i)
 *		the kernel context 0 (Sun-2)
 *
 * Besides the rules for virtual memory cooperation, the following
 * debugger/debuggee interface is defined:
 *
 *   *	If a debugger is present, it will pass in a '-d' flag
 *	to the program being debugged (although the program being
 *	debugged might want to verify that the debugger is actually
 *	present before taking it as the truth to avoid problems
 *	with users using the wrong flags in the wrong places).
 *	The '-d' flag being passed into the debugger itself will
 *	cause the debugger to prompt for debuggee program name and
 *	allow debugger commands before debuggee is started.
 *   *	The top *dvec->dv_pages tell the number of pages
 *	taken from the end of memory.  If the debuggee is
 *	managing all memory, the amount of usable memory is:
 *	  *romp->v_memorysize  - mmu_ptob(*dvec->dv_pages) [earlier PROMs]
 *	  *romp->v_memoryavail - mmu_ptob(*dvec->dv_pages) [later PROMs]
 *   *	If the debuggee changes the trace exception handler or
 *	the trap exception handler for TRAPBRKNO, it MUST call
 *	(*dvec->dv_scbsync)() after all exception handler changes
 *	are made.  Other exception handlers can be changed
 *	without any special provisions.
 *   *	If the debuggee is going to relocate itself, it is very
 *	desirable to have it call (*dvec->dv_scbsync)() soon
 *	AFTER the relocation to the correct virtual address.
 *   *	The debuggee can call the debugger at any time by
 *	an explicit call using the CALL_DEBUG() macro,
 *	a ``trap #TRAPBRKNO'' (68000), ``t TRAPBRKNO'' (sparc),
 *	``int 3'' (i386), or by jumping to *dvec->dv_trap.
 *   *	The debuggee is expected not to try and trace itself
 *	under the debugger - the only way the trace bit can
 *	be turned on in the debuggee is via the ``rte''
 *	instruction.  This case is detected and handled
 *	correctly by the debugger when single stepping,
 *	except in the case were the rte is returning to
 *	another rte which is returning to user land
 *	(welcome to the real world of 680x0 processors).
 */

#if defined(sun2) || defined(sun3) || defined(sun386)
#define DVEC		DEBUGSTART		/* location of vector table */
#define	TRAPBRKNO	10			/* breakpoint trap no */
#endif sun2 || sun3 || sun386

#ifdef sun4
#define DVEC		(DEBUGSTART + 4096)	/* location of vector table */
#define	TRAPBRKNO	127			/* breakpoint trap no */
#endif sun4

/*
 * The debugger gets a one megabyte virtual address range in which it
 * can reside.  It is hoped that this space is large enough to accommodate
 * the largest kernel debugger that would be needed but not too large to
 * cramp the kernel's virtual address space.  We locate the debugger
 * in the megabyte before the PROM monitor, except on the 386, where we
 * locate it 16 megabytes (minus 20k) in front of the monitor.
 */
#define	DEBUGSIZE	0x100000

#ifndef LOCORE
#include <mon/sunromvec.h>

#ifdef  sun386
#define DEBUGSTART	(MONSTART - 0x1000000 + 0x5000)	/*  16 megs virtual */
#else
#define	DEBUGSTART	(MONSTART - DEBUGSIZE)
#endif
#define	DEBUGEND	(MONSTART)

typedef int (*func_t)();

struct debugvec {
	int	dv_entry;	/* entry point into debugger */
	func_t	dv_trap;	/* function to trap to enter debugger */
	int	*dv_pages;	/* ptr to # of pages stolen */
	func_t	dv_scbsync;	/* function to call after scb is changed */
#ifdef	sun386
	long    *dv_vstart;	/* start of virtual memory (default 0) */
	char    *dv_kbflag;	/* pointer to keyboard state flag */
#endif
};
#define dvec		((struct debugvec *)DVEC)

/*
 * Use the CALL_DEBUG macro to generate a synchronous call to the debugger.
 *
 * Because of a bug in some old versions of /bin/as, using this macro
 * can crash the assembler as doing (*(func_t)DVEC)() generates a call to
 * an absolute address which is not handled correctly by the buggy assemblers.
 */
#if defined (sparc) || defined(sun386)
/* current sparc assemblers cannot handle a call to fixed virtual address */
#define	CALL_DEBUG()	{ func_t callit = (func_t)DVEC; (*callit)(); }
#else
#define	CALL_DEBUG()	(*(func_t)DVEC)()
#endif
#endif !LOCORE

#if	defined(sun386) && !defined(COFF)
#define	COFF	1
#endif

#define	KADBBASE	0xfe000000		/* DEBUGSTART - 0x5000 */

#endif !_debug_debug_h
