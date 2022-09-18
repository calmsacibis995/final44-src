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
 * Revision 1.5  89/07/17  10:38:39  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 		Declare trap_type[] for use by kdb.
 * 	[89/07/11            rvb]
 * 
 * Revision 1.4  89/03/09  20:04:28  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:27:02  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *	BUT SOME of the 386 types conflict with OLDER TYPES --
 *	WHAT SHOULD WE DO
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


/*
 * I386 Trap type values
 */

#define T_DIVERR	0	/* divide by 0 eprror		*/
#define T_SGLSTP	1	/* single step			*/
#define T_NMIFLT	2	/* NMI				*/
#define T_BPTFLT	3	/* breakpoint fault		*/
#define T_INTOFLT	4	/* INTO overflow fault		*/
#define T_BOUNDFLT	5	/* BOUND instruction fault	*/
#define T_INVOPFLT	6	/* invalid opcode fault		*/
#define T_NOEXTFLT	7	/* extension not available fault*/
#define T_DBLFLT	8	/* double fault			*/
#define T_EXTOVRFLT	9	/* extension overrun fault	*/
#define T_INVTSSFLT	10	/* invalid TSS fault		*/
#define T_SEGNPFLT	11	/* segment not present fault	*/
#define T_STKFLT	12	/* stack fault			*/
#define T_GPFLT		13	/* general protection fault	*/
#define T_PGFLT		14	/* page fault			*/
#define T_EXTERRFLT	16	/* extension error fault	*/
#define T_ENDPERR	33	/* emulated extension error flt	*/
#define T_ENOEXTFLT	32	/* emulated ext not present	*/

/*
 * Trap type values
 */

/* The first three constant values are known to the real world <signal.h> */
/* Well, I wonder what we do? */
/*#define	T_RESADFLT	0		/* reserved addressing fault */
/*#define	T_PRIVINFLT	1		/* privileged instruction fault */
/*#define	T_RESOPFLT	2		/* reserved operand fault */
/* End of known constants */
#define T_READ_FAULT	14		/* read fault */
#define T_WRITE_FAULT	15		/* write fault */
#define T_KDB_ENTRY	16		/* force entry to kernel debugger */

/* 
 * List of printable strings for trap types.  TRAP_TYPES is the number 
 * of elements in the array.  It may be smaller than the list of trap 
 * types given above.
 */
extern char *trap_type[];
extern int TRAP_TYPES;
