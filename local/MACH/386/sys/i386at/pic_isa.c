/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	pic_isa.c,v $
 * Revision 2.1.1.2  90/11/27  13:45:08  rvb
 * 	Synched 2.5 & 3.0 at I386q (r2.1.1.2) & XMK35 (r2.1)
 * 	[90/11/15            rvb]
 * 
 * 	We don't want to see clock interrupts till clkstart(),
 * 	but we can not turn the interrupt off so we disable them.
 * 	2.5 ONLY!
 * 	[90/11/05            rvb]
 * 
 * Revision 2.1.1.1  90/07/10  11:45:31  rvb
 * 	Created based on pic.c
 * 	[90/06/16            rvb]
 * 
 */

#include <sys/types.h>
#include <i386/ipl.h>
#include <i386/pic.h>


/* These interrupts are always present */
extern intnull(), fpintr(), hardclock(), kdintr();
extern prtnull();

int (*ivect[NINTR])() = {
	/* 00 */	hardclock,	/* always */
	/* 01 */	kdintr,		/* kdintr, ... */
	/* 02 */	intnull,
	/* 03 */	intnull,	/* lnpoll, comintr, ... */

	/* 04 */	intnull,	/* comintr, ... */
	/* 05 */	intnull,	/* comintr, wtintr, ... */
	/* 06 */	intnull,	/* fdintr, ... */
	/* 07 */	prtnull,	/* qdintr, ... */

	/* 08 */	intnull,
	/* 09 */	intnull,	/* ether */
	/* 10 */	intnull,
	/* 11 */	intnull,

	/* 12 */	intnull,
	/* 13 */	fpintr,		/* always */
	/* 14 */	intnull,	/* hdintr, ... */
	/* 15 */	intnull,	/* ??? */
};

u_char intpri[NINTR] = {
#ifdef	MACH_KERNEL
	/* 00 */	SPLHI, 	SPL6,	0,	0,
#else	MACH_KERNEL
	/* 00 */   	0,	SPL6,	0,	0,
#endif	MACH_KERNEL
	/* 04 */	0,	0,	0,	0,
	/* 08 */	0,	0,	0,	0,
	/* 12 */	0,	SPL1,	0,	0,
};
