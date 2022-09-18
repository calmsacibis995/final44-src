/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sun.h,v $
 * Revision 2.4  89/03/09  21:35:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:43:00  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 04-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added INKERNEL macro for printstack() and nextframe().
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL and changed pathnames
 *	of include files to be kernel relative in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 */ 
/*	@(#)sun.h 1.1 86/02/03 SMI	*/

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <sys/vmparam.h>
#include <sun3/mmu.h>


#define REG_RN(n)	(n)
#define REG_R0		 0
#define REG_R7		 7
#define REG_AR0		 8
#define REG_AR7		15
#define REG_FP		14
#define REG_SP		15
#define REG_PC		16
#define REG_PS		17
#define REG_SF		18
#define REG_FP0		19
#define REG_FP7		40
#define REG_FPC		43
#define REG_FPS		44
#define REG_FPI		45
#define REG_FPG		46
#define REG_FPF		47

#define REGADDR(r)	(MAXSTOR + (4 * (r)))

#define NREGISTERS	48

#ifdef	REGNAMES
char	*regnames[] = {
	"d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
	"a0", "a1", "a2", "a3", "a4", "a5", "a6", "sp",
	"pc", "ps", "",
	"fp0", "fq0", "fr0", "fp1", "fq1", "fr1", 
	"fp2", "fq2", "fr2", "fp3", "fq3", "fr3", 
	"fp4", "fq4", "fr4", "fp5", "fq5", "fr5", 
	"fp6", "fq6", "fr6", "fp7", "fq7", "fr7",
	"fpc", "fps", "fpi", "fpg", "fpf"
};
#endif

#define U_PAGE	UADDR

#define TXTRNDSIZ	SEGSIZ

#define MAXINT		0x7fffffff
#define MAXSTOR		((NBSG * NSEGMAP) - 1)	/* Mask for virtual addr bits */
#define MAXFILE		0xffffffff
#ifdef	sun3
#define VADDR_MASK	0x0fffffff	/* Sun3: 28 bit virtual addresses */
#else
#define VADDR_MASK	0x00ffffff	/* Sun2: 24 bit virtual addresses */
#endif

#define INSTACK(x)	( (x) >= STKmin && (x) <= STKmax )
int STKmax, STKmin;

#define INKERNEL(addr)	(addr >= KERNELBASE && addr < MONSTART)

#define KVTOPH(x)	(((x) > KERNELBASE)? (x) - KERNELBASE: (x))


struct stackpos {
	 int	k_pc;
	 int	k_fp;
	 int	k_nargs;
	 int	k_entry;
	 int	k_caller;
	 int	k_flags;
	 int	k_regloc[NREGISTERS];
};
#define FR_SAVFP	0
#define FR_SAVPC	4
#define K_CALLTRAMP	1	/* for k_flags: caller is __sigtramp */
#define K_SIGTRAMP	2	/* for k_flags: this is   __sigtramp */
