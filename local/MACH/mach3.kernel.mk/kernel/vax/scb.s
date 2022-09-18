/*
 * HISTORY
 * $Log:	scb.s,v $
 * Revision 2.3  91/06/19  12:01:40  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:50:19  rvb]
 * 
 * Revision 2.2  91/05/08  13:22:46  dbg
 * 	Adapt for ANSI C.
 * 	[91/04/23            dbg]
 * 
 */
/*
 *	VAX SCB
 */
#include <platforms.h>
#include <uba.h>
#include <bi.h>
#include <mach_mpm.h>

	.set	INTSTK, 1	# handle this interrupt on the interrupt stack
	.set	HALT, 3		# halt for this one

#ifdef	__STDC__
#define	KS(a)	.long	_X ## a
#define	IS(a)	.long	_X ## a+INTSTK
#define	STOP(a)	.long	_X ## a+HALT
#else
#define	KS(a)	.long	_X/**/a
#define	IS(a)	.long	_X/**/a+INTSTK
#define	STOP(a)	.long	_X/**/a+HALT
#endif	/* __STDC__ */

#define	STRAY(no)	.long	_Ystray+INTSTK+((no)*2)
#define	STRAY8(base)	STRAY(base+0x0);STRAY(base+0x4);\
			STRAY(base+0x8);STRAY(base+0xc);\
			STRAY(base+0x10);STRAY(base+0x14);\
			STRAY(base+0x18);STRAY(base+0x1c)

#define	STRAY15(base)	STRAY(base+0x0);STRAY(base+0x4);\
			STRAY(base+0x8);STRAY(base+0xc);\
			STRAY(base+0x10);STRAY(base+0x14);\
			STRAY(base+0x18);STRAY8(base+0x1c)

#define STRAY16(base)	STRAY8(base); STRAY8(base+0x20);

	.globl	_scb
_scb:
/* 000 */	IS(pass_rel);	IS(machcheck);	IS(kspnotval);	STOP(powfail)
/* 010 */	KS(privinflt);	KS(xfcflt);	KS(resopflt);	KS(resadflt)
/* 020 */	KS(protflt);	KS(transflt);	KS(tracep);	KS(bptflt)
/* 030 */	KS(compatflt);	KS(arithtrap);	STRAY(0x038);	STRAY(0x03c)
/* 040 */	KS(syscall);	KS(chme);	KS(chms);	KS(chmu)
/* 050 */	STRAY(0x50);	IS(cmrd);	IS(rxcd);	IS(nmifault)
/* 060 */	KS(wtime);	STRAY(0x064);	STRAY(0x068);	STRAY(0x06c)
/* 070 */	STRAY(0x070);	STRAY(0x074);	IS(ssc0clock);	STRAY(0x07c)
/* 080 */	IS(ipintr);	STRAY(0x084);	KS(astflt);	STRAY(0x08c)
/* 090 */	STRAY(0x090);	STRAY(0x094);	STRAY(0x098);	STRAY(0x09c)
/* 0a0 */	IS(softclock);	STRAY(0x0a4);	STRAY(0x0a8);	STRAY(0x0ac)
/* 0b0 */	STRAY(0x0b0);	STRAY(0x0b4);	STRAY(0x0b8);	IS(kdbintr)
/* 0c0 */	IS(hardclock);	STRAY(0x0c4);	STRAY(0x0c8);	STRAY(0x0cc)
	/* c8 and cc are changed to vax$emulate and vax$emulatefpd */
/* 0d0 */	STRAY(0x0d0);	STRAY(0x0d4);	STRAY(0x0d8);	STRAY(0x0dc)
/* 0e0 */	STRAY(0x0e0);	STRAY(0x0e4);	STRAY(0x0e8);	STRAY(0x0ec)
/* 0f0 */	IS(consdin);	IS(consdout);	IS(cnrint);	IS(cnxint)

/* 100: ipl 14, nexus 0-15 */
#if	MACH_MPM > 0
/* 100 */	STRAY(0x100);	STRAY(0x104);	IS(mpmc0int);	IS(mpmc1int)
/* 110 */	IS(mpmc2int);	IS(mpmc3int);	STRAY(0x118);	STRAY(0x11c)
#else	MACH_MPM > 0
/* 100 */	STRAY(0x100);	STRAY(0x104);	STRAY(0x108);	STRAY(0x10c)
/* 110 */	STRAY(0x110);	STRAY(0x114);	STRAY(0x118);	STRAY(0x11c)
#endif	MACH_MPM > 0
/* 120 */	IS(nbib0);	STRAY(0x124);	STRAY(0x128);	STRAY(0x12c)
/* 130 */	IS(nbib1);	STRAY(0x134);	STRAY(0x138);	STRAY(0x13c)

/* 140: ipl 15, nexus 0-15 */
#if	MACH_MPM > 0
/* 140 */	STRAY(0x140);	STRAY(0x144);	IS(mpm0int);	IS(mpm1int)
/* 150 */	IS(mpm2int);	IS(mpm3int);	STRAY(0x158);	STRAY(0x15c)
#else	MACH_MPM > 0
/* 140 */	STRAY(0x140);	STRAY(0x144);	STRAY(0x148);	STRAY(0x14c)
/* 150 */	STRAY(0x150);	STRAY(0x154);	STRAY(0x158);	STRAY(0x15c)
#endif	MACH_MPM > 0
/* 160 */	STRAY(0x160);	STRAY(0x164);	STRAY(0x168);	STRAY(0x16c)
/* 170 */	STRAY(0x170);	STRAY(0x174);	STRAY(0x178);	STRAY(0x17c)

/* 180: ipl 16, nexus 0-15 */
/* 180 */	STRAY16(0x180)

/* 1c0: ipl 17, nexus 0-15 */
/* 1c0 */	STRAY16(0x1c0)

/* 200 - 2fc */
	.globl	_UNIvec
_UNIvec:	.space 512		/* 750 unibus interrupt vector */
					/* first UBA jump table on 780s */
#if NUBA > 1
/* 300 - 3fc */
	.globl	_UNI1vec
_UNI1vec:	.space 512		/* 750 second unibus vector */
					/* second UBA jump table on 780s */
#endif

#if	NBI > 0
#define	BI_INTR(no)	.long	_Ybi_intr+INTSTK+((no)*2)
#define	BI_INTR8(base)	BI_INTR(base+0x0);BI_INTR(base+0x4);\
			BI_INTR(base+0x8);BI_INTR(base+0xc);\
			BI_INTR(base+0x10);BI_INTR(base+0x14);\
			BI_INTR(base+0x18);BI_INTR(base+0x1c)

#define BI_INTR16(base)	BI_INTR8(base); BI_INTR8(base+0x20);

	.globl	_biscb
_biscb:
	BI_INTR16(0x00)		/* IOA 0 */
#if	NBI > 1
	BI_INTR16(0x40)		/* IOA 1 */
#if	NBI > 2
	BI_INTR16(0x80)		/* IOA 2 */
#if	NBI > 3
	BI_INTR16(0xc0)		/* IOA 3 */
#endif	/*    3 */
#endif	/*    2 */
#endif	/*    1 */

#if	VAX6200
_xmiscb:
	IS(xmi0);	IS(xmi1);	IS(xmi2);	IS(xmi3)
#else
	.space	4*4
#endif	VAX6200
	.space	0x100 - 4*4
#endif	NBI > 0

	.globl	_scb_end
_scb_end:
