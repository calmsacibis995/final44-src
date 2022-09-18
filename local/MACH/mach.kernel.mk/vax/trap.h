/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	trap.h,v $
 * Revision 2.5  89/03/09  22:22:17  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  10:49:03  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/24  03:02:21  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  19:02:25  mwyoung]
 * 
 *
 * 25-Jun-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added a new trap code for KDB entry to avoid conflict with trace
 *	trap from user mode.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)trap.h	7.1 (Berkeley) 6/5/86
 */

#include <mach_kdb.h>

/*
 * Trap type values
 */

/* The first three constant values are known to the real world <signal.h> */
#define T_RESADFLT	0		/* reserved addressing fault */
#define T_PRIVINFLT	1		/* privileged instruction fault */
#define T_RESOPFLT	2		/* reserved operand fault */
/* End of known constants */
#define T_BPTFLT	3		/* bpt instruction fault */
#define T_XFCFLT	4		/* xfc instruction fault */
#define T_SYSCALL	5		/* chmk instruction (syscall trap) */
#define T_ARITHTRAP	6		/* arithmetic trap */
#define T_ASTFLT	7		/* software level 2 trap (ast deliv) */
#define T_SEGFLT	8		/* segmentation fault */
#define T_PROTFLT	9		/* protection fault */
#define T_TRCTRAP	10		/* trace trap */
#define T_COMPATFLT	11		/* compatibility mode fault */
#define T_PAGEFLT	12		/* page fault */
#define T_TABLEFLT	13		/* page table fault */
#define T_READ_FAULT	14		/* read fault */
#define T_WRITE_FAULT	15		/* write fault */
#if	MACH_KDB
#define T_KDB_ENTRY	16		/* force entry to kernel debugger */
#endif	MACH_KDB
