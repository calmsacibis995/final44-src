/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmparam.h,v $
 * Revision 1.4.1.1  90/02/28  15:48:44  rvb
 * 	USRTEXT is 0x10000 [kupfer]
 * 
 * Revision 1.4  89/03/09  20:04:34  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:35:12  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *	A lot of trash could be flushed from this file.
 *
 * 30-Sep-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Added definition SIGCODE_SIZE to kernel only clause.
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
 * Machine dependent constants for I386
 */
/*
 * USRTEXT is the start of the user text/data space, while USRSTACK
 * is the top (end) of the user stack.  LOWPAGES and HIGHPAGES are
 * the number of pages from the beginning of the P0 region to the
 * beginning of the text and from the beginning of the P1 region to the
 * beginning of the stack respectively.
 */
#define USRTEXT		0x10000

#ifdef	KERNEL
#ifndef	ASSEMBLER
extern	int sigcode[5];/* must agree with sigcode declaration in kern_exec*/
#define SIGCODE_SIZE	(sizeof (sigcode))
#endif	ASSEMBLER
#endif	KERNEL

#define USRSTACK	(0xc0000000-sizeof(int [5]))	/* must agree with sigcode above */

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
