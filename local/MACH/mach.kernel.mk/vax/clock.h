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
 * $Log:	clock.h,v $
 * Revision 2.4  89/03/09  22:12:59  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:11:58  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/10/11  13:01:17  rpd
 * 	Need a common place to define ssc clock structure
 * 	[88/10/08            rvb]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)clock.h	7.1 (Berkeley) 6/5/86
 */

/*
 * VAX clock registers
 */

#define ICCS_RUN	0x00000001
#define ICCS_TRANS	0x00000010
#define ICCS_SS		0x00000020
#define ICCS_IE		0x00000040
#define ICCS_INT	0x00000080
#define ICCS_ERR	0x80000000
	
#define SECDAY		((unsigned)(24*60*60))		/* seconds per day */
#define SECYR		((unsigned)(365*SECDAY))	/* per common year */
/*
 * TODRZERO is the what the TODR should contain when the ``year'' begins.
 * The TODR should always contain a number between 0 and SECYR+SECDAY.
 */
#define TODRZERO	((unsigned)(1<<28))

#define YRREF		1970
#define LEAPYEAR(year)	((year)%4==0)	/* good till time becomes negative */

/*
 * Has the time-of-day clock wrapped around?
 */
#define clkwrap()	(((unsigned)mfpr(TODR) - TODRZERO)/100 > SECYR+SECDAY)

/*
 * Software clock is software interrupt level 8,
 * implemented as mtpr(SIRR, 0x8) in asm.sed.
 */

#if	VAX650 || VAX6200
#ifdef	KERNEL
#ifndef	ASSEMBLER
struct ssclock {
	u_long ssc_r1[64];		/* "filler" */

	u_long ssc_tcr0;		/* Timer 0 Control Register */
	u_long ssc_tir0;		/* Timer 0 u_longerval Register */
	u_long ssc_tnir0;		/* Timer 0 Next u_longerval Register */
	u_long ssc_tivr0;		/* Timer 0 u_longerrupt Vector */

	u_long ssc_tcr1;		/* Timer 1 Control Register */
	u_long ssc_tir1;		/* Timer 1 u_longerval Register */
	u_long ssc_tnir1;		/* Timer 1 Next u_longerval Register */
	u_long ssc_tivr1;		/* Timer 1 u_longerrupt Vector */

};

extern struct ssclock *ssclock;
#endif	ASSEMBLER
#endif	KERNEL
#endif	VAX650 || VAX6200
