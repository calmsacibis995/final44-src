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
 * $Log:	scb.s,v $
 * Revision 2.6  89/03/09  22:21:24  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:28:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/10/11  13:04:19  rpd
 * 		VAX6200: Try ssc timer chip.
 * 	[88/10/08            rvb]
 * 
 * Revision 2.3  88/08/10  10:35:49  rvb
 * Take wtime on kernel stack, so we can get a good stack trace.
 * Besides it really is an exception.
 * 
 * 18-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	NBI:  augmented VAX8800 conditionals to also require this
 *	symbol so that BI support can be omitted more easily without
 *	changing the cpu set.
 *	[ V5.1(XF24) ]
 *
 * 12-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Give the 650's timer a different interrupt.  Restore hardclock
 *	vector at 0xc0 so that all the other VAXen still work! (!@#$%)
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, move ssc timers to dec standard 0x78 and 0c7c
 *
 * 19-Nov-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Cateclysm: CS_GENERIC == TRUE
 *
 *  6-Nov-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Support for VAX650 SSC timers.  Will use vectors D0 and D4.
 *
 * 25-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	VAX 8800 support.
 *
 *  3-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Use same SCB for master and slave processors.
 *
 * 26-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added interprocessor interrupt vector for the BI bus (really the
 *	8200).
 *
 * 24-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	When using Berkeley emulation code, be sure to define the
 *	vectors under CS_GENERIC.
 *
 * 14-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed separate slave console interrupt.  It is handled through
 *	the normal console interrupt system.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 20-Dec-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	MPM is a real device not an option, so the define constant is
 *	NMACH_MPM not MACH_MPM
 *
 * 15-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	MACH_KDB:  Added vector for KDB interrupts at software IPL 0xf.
 *	[V1(1)]
 *
 * 14-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Add entries to scb to catch multiport memory interrupts if 
 *	MACH_MPM
 *
 */
 
#include <cputypes.h>

#include <bi.h>
#include <mach_kdb.h>
#include <emul.h>
#include <mach_mpm.h>	/* note scb.s appears before locore.s in "cat" */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)scb.s	7.1 (Berkeley) 6/5/86
 */

#include <uba.h>

/*
 * System control block
 */
	.set	INTSTK,1	# handle this interrupt on the interrupt stack
	.set	HALT,3		# halt if this interrupt occurs

_scb:	.globl	_scb

#define STRAY(no)	.long	_Ystray+INTSTK+((no)*2)
#define STRAY8(base)	STRAY(base+0x0);STRAY(base+0x4);\
			STRAY(base+0x8);STRAY(base+0xc);\
			STRAY(base+0x10);STRAY(base+0x14);\
			STRAY(base+0x18);STRAY(base+0x1c)

#define STRAY15(base)	STRAY(base+0x0);STRAY(base+0x4);\
			STRAY(base+0x8);STRAY(base+0xc);\
			STRAY(base+0x10);STRAY(base+0x14);\
			STRAY(base+0x18);STRAY8(base+0x1c)

#define STRAY16(base)	STRAY8(base); STRAY8(base+0x20);

#define KS(a)	.long	_X/**/a
#define IS(a)	.long	_X/**/a+INTSTK
#define STOP(a)	.long	_X/**/a+HALT

#if	NBI > 0 
/* 000 */	IS(pass_rel);	IS(machcheck);	IS(kspnotval);	STOP(powfail);
#else	NBI > 0 
/* 000 */	STRAY(0x000);	IS(machcheck);	IS(kspnotval);	STOP(powfail);
#endif	NBI > 0 
/* 010 */	KS(privinflt);	KS(xfcflt);	KS(resopflt);	KS(resadflt);
/* 020 */	KS(protflt);	KS(transflt);	KS(tracep);	KS(bptflt);
/* 030 */	KS(compatflt);	KS(arithtrap);	STRAY(0x038);	STRAY(0x03c);
/* 040 */	KS(syscall);	KS(chme);	KS(chms);	KS(chmu);
#if	NBI > 0 
/* 050 */	IS(bierr);	IS(cmrd);	IS(rxcd);	IS(nmifault);
/* 060 */	KS(wtime);	STRAY(0x064);	STRAY(0x068);	STRAY(0x06c);
#else	NBI > 0 
/* 050 */	STRAY(0x050);	IS(cmrd);	STRAY(0x058);	STRAY(0x05c);
/* 060 */	KS(wtime);	STRAY(0x064);	STRAY(0x068);	STRAY(0x06c);
#endif	NBI > 0 
#if	VAX650 || VAX6200
  	/* on 650 use 78 and 7c for the ssc timer interrupts. */
  	/* 7c (timer 2) is stray for now till we enable it */
/* 070 */	STRAY(0x070);	STRAY(0x074);	IS(ssc0clock);	IS(ssc1clock);
#else	VAX650 || VAX6200
/* 070 */	STRAY(0x070);	STRAY(0x074);	STRAY(0x078);	STRAY(0x07c);
#endif	VAX650 || VAX6200
#if	NBI > 0 
/* 080 */	IS(ipintr);	STRAY(0x084);	KS(astflt);	STRAY(0x08c);
#else	NBI > 0 
/* 080 */	STRAY(0x080);	STRAY(0x084);	KS(astflt);	STRAY(0x08c);
#endif	NBI > 0 
/* 090 */	STRAY(0x090);	STRAY(0x094);	STRAY(0x098);	STRAY(0x09c);
/* 0a0 */	IS(softclock);	STRAY(0x0a4);	STRAY(0x0a8);	STRAY(0x0ac);
#if	MACH_KDB
/* 0b0 */	IS(netintr);	STRAY(0x0b4);	STRAY(0x0b8);	IS(kdbintr);
#else	MACH_KDB
/* 0b0 */	IS(netintr);	STRAY(0x0b4);	STRAY(0x0b8);	STRAY(0x0bc);
#endif	MACH_KDB
#if	NEMUL > 0
#ifdef	notdef
/* This is really a comment, but left to indicate that on uVaxen the scb
 * is patched as shown below.
   0c0 		IS(hardclock);	STRAY(0x0c4);	KS($vax$emulate);
						KS($vax$emulate_fpd);
*/
#endif	notdef
/* 0c0 */	IS(hardclock);	STRAY(0x0c4);	STRAY(0x0c8);	STRAY(0x0cc);
#else	NEMUL > 0
/* 0c0 */	IS(hardclock);	STRAY(0xc4);	KS(emulate);	KS(emulateFPD);
#endif	NEMUL > 0
/* 0d0 */	STRAY(0x0d0);	STRAY(0x0d4);	STRAY(0x0d8);	STRAY(0x0dc);
/* 0e0 */	STRAY(0x0e0);	STRAY(0x0e4);	STRAY(0x0e8);	STRAY(0x0ec);
/* 0f0 */	IS(consdin);	IS(consdout);	IS(cnrint);	IS(cnxint);

/* 100 ipl 0x14, nexus 0-15 */
#if	NMACH_MPM > 0
/* 100 */	STRAY(0x100);	STRAY(0x104);	IS(mpmc0int);	IS(mpmc1int);
/* 110 */	IS(mpmc2int);	IS(mpmc3int);	STRAY(0x118);	STRAY(0x11c);
#else	NMACH_MPM > 0
/* 100 - 120 */	STRAY8(0x100);
#endif	NMACH_MPM > 0
#if	VAX8800 && NBI > 0
/* 120 - 130 */ IS(nbib0);	STRAY(0x124);	STRAY(0x128);	STRAY(0x12c);
/* 130 - 140 */ IS(nbib1);	STRAY(0x134);	STRAY(0x138);	STRAY(0x13c);
#else	VAX8800 && NBI > 0
/* 120 - 140 */ STRAY8(0x120);
#endif	VAX8800 && NBI > 0


/* 140 ipl 0x15, nexus 0-15 */
#if	NMACH_MPM > 0
/* 140 */	STRAY(0x140);	STRAY(0x144);	IS(mpm0int);	IS(mpm1int);
/* 150 */	IS(mpm2int);	IS(mpm3int);	STRAY(0x158);	STRAY(0x15c);
/* 160 - 170 */	STRAY8(0x160);
#else	NMACH_MPM > 0
/* 140 */	STRAY(0x140);	STRAY15(0x144);	/* ipl 0x14, nexus 0-15 */
#endif	NMACH_MPM > 0

/* 180 */	STRAY(0x180);	STRAY15(0x184);	/* ipl 0x16, nexus 0-15 */
/* 1c0 */	STRAY(0x1c0);	STRAY15(0x1c4);	/* ipl 0x17, nexus 0-15 */

	.globl	_UNIvec
_UNIvec:	.space	512		# 750 unibus intr vector
					# 1st UBA jump table on 780's
#if	NUBA > 1
	.globl	_UNI1vec
_UNI1vec:	.space	512		# 750 second unibus intr vector
					# 2nd UBA jump table on 780's
#endif
