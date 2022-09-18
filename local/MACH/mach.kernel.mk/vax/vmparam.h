/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmparam.h,v $
 * Revision 2.4  89/03/09  22:23:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  10:50:01  gm0w
 * 	Purged all the berkeley vm defines.
 * 	[89/02/20            rvb]
 * 
 * 30-Sep-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Added definition SIGCODE_SIZE to kernel only clause.
 *
 * 22-Jul-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Move sigcode declaration into KERNEL-only clause, to avoid
 *	polluting user programs (notably adb) with this symbol.
 *
 * 27-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	nsigcode -> sigcode.
 *
 * 27-May-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	MACH: Moved the USRSTACK up to the top of memory
 *	minus sizeof(nsigcode).
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Fixed multiple definition of P1PAGES, for lint.
 *
 *
 */ 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vmparam.h	7.1 (Berkeley) 6/5/86
 */


/*
 * Machine dependent constants for VAX
 */
/*
 * USRTEXT is the start of the user text/data space, while USRSTACK
 * is the top (end) of the user stack.  LOWPAGES and HIGHPAGES are
 * the number of pages from the beginning of the P0 region to the
 * beginning of the text and from the beginning of the P1 region to the
 * beginning of the stack respectively.
 */
#define USRTEXT		0

#ifdef	KERNEL
#ifndef	ASSEMBLER
extern	int sigcode[5];		/* must agree with sigcode declaration in kern_exec*/
#define SIGCODE_SIZE	(sizeof (sigcode))
#endif	ASSEMBLER
#endif	KERNEL

#define USRSTACK	(0x80000000-sizeof(int [5]))	/* must agree with sigcode above */

/*
 * Virtual memory related constants, all in bytes
 */
#ifndef	MAXTSIZ
#define MAXTSIZ		(6*1024*1024)		/* max text size */
#endif
#ifndef	DFLDSIZ
#define DFLDSIZ		(6*1024*1024)		/* initial data size limit */
#endif
#ifndef	MAXDSIZ
#define MAXDSIZ		(16*1024*1024)		/* max data size */
#endif
#ifndef	DFLSSIZ
#define DFLSSIZ		(512*1024)		/* initial stack size limit */
#endif
#ifndef	MAXSSIZ
#define MAXSSIZ		MAXDSIZ			/* max stack size */
#endif

#include <mach/vax/vm_param.h>
