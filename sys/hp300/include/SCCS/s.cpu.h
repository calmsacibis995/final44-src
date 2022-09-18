h11058
s 00001/00000/00279
d D 8.5 95/05/17 21:31:30 mckusick 19 18
c add definition for ability to produce a backtrace
e
s 00001/00000/00278
d D 8.4 94/01/05 09:48:21 mckusick 18 17
c add cpu_swapin (nothing needed)
e
s 00004/00004/00274
d D 8.3 93/12/10 17:36:46 mckusick 17 16
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00001/00001/00277
d D 8.2 93/09/23 16:42:38 bostic 16 15
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00276
d D 8.1 93/06/10 21:44:33 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00000/00269
d D 7.14 93/05/20 21:21:33 mckusick 14 13
c add CTL_MACHDEP definitions
e
s 00002/00003/00267
d D 7.13 92/12/27 09:25:19 hibler 13 12
c account for new stack alignment, type for hp433
e
s 00004/00004/00266
d D 7.12 92/07/08 01:05:53 torek 12 11
c fixup comments to reflect that softclock no longer gets a frame ptr
e
s 00023/00024/00247
d D 7.11 92/07/08 01:04:16 torek 11 10
c changes to pass clock frame by reference rather than value;
c profile_tick => need_proftick; cleanups for libkern
e
s 00023/00000/00248
d D 7.10 92/06/05 15:29:19 hibler 10 9
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00247
d D 7.9 92/02/17 17:34:55 mckusick 9 8
c pc is a char *
e
s 00002/00000/00246
d D 7.8 92/02/05 17:15:41 mckusick 8 7
c add cpu_setstack
e
s 00001/00000/00245
d D 7.7 91/06/27 18:01:47 karels 7 6
c add cpu_wait()
e
s 00049/00016/00196
d D 7.6 91/05/07 10:04:48 hibler 6 5
c DIO-II support
e
s 00011/00009/00201
d D 7.5 91/05/06 11:29:02 karels 5 4
c psl.h is already included by machine/param.h; add signotify();
c do ast's here, global rather than per-process
e
s 00080/00000/00130
d D 7.4 91/04/20 16:51:24 karels 4 3
c add intrframe and macros, definitions of generic functions needed
c add need_resched, profile_tick
e
s 00079/00074/00051
d D 7.3 90/12/05 19:30:14 mckusick 3 2
c update from Mike Hibler for new VM and other machine support
e
s 00002/00000/00123
d D 7.2 90/05/25 15:49:37 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00123/00000/00000
d D 7.1 90/05/08 17:51:15 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 15
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 6
 * from: Utah $Hdr: cpu.h 1.13 89/06/23$
E 6
I 6
 * from: Utah $Hdr: cpu.h 1.16 91/03/25$
E 6
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 5
#ifdef notyet
#include "../hp300/psl.h"
#else
#include "machine/psl.h"
#endif

E 5
/*
 * Exported definitions unique to hp300/68k cpu support.
 */

/*
 * definitions of cpu-dependent requirements
 * referenced in generic code
 */
#define	COPY_SIGCODE		/* copy sigcode above user stack in exec */

D 11
/*
 * function vs. inline configuration;
 * these are defined to get generic functions
 * rather than inline or machine-dependent implementations
 */
#define	NEED_MINMAX		/* need {,i,l,ul}{min,max} functions */
#undef	NEED_FFS		/* don't need ffs function */
#undef	NEED_BCMP		/* don't need bcmp function */
#undef	NEED_STRLEN		/* don't need strlen function */

E 11
D 17
#define	cpu_exec(p)	/* nothing */
I 7
#define	cpu_wait(p)	/* nothing */
I 8
#define cpu_setstack(p, ap) \
	(p)->p_md.md_regs[SP] = ap
E 17
I 17
#define	cpu_exec(p)			/* nothing */
I 18
#define	cpu_swapin(p)			/* nothing */
E 18
#define	cpu_wait(p)			/* nothing */
#define cpu_setstack(p, ap)		(p)->p_md.md_regs[SP] = ap
#define cpu_set_init_frame(p, fp)	(p)->p_md.md_regs = fp
I 19
#define BACKTRACE(p)			backtrace(p)
E 19
E 17
E 8
E 7

/*
D 11
 * Arguments to hardclock, softclock and gatherstats
 * encapsulate the previous machine state in an opaque
 * clockframe; for hp300, use just what the hardware
 * leaves on the stack.
E 11
I 11
D 12
 * Arguments to hardclock, softclock and gatherstats encapsulate the
 * previous machine state in an opaque clockframe.  One the hp300, we
 * use what the hardware pushes on an interrupt (but we pad the sr to
 * a longword boundary).
E 12
I 12
 * Arguments to hardclock and gatherstats encapsulate the previous
 * machine state in an opaque clockframe.  One the hp300, we use
D 13
 * what the hardware pushes on an interrupt (but we pad the sr to a
 * longword boundary).
E 13
I 13
 * what the hardware pushes on an interrupt (frame format 0).
E 13
E 12
E 11
 */
D 11
typedef struct intrframe {
D 9
	int	pc;
E 9
I 9
	char	*pc;
E 9
	int	ps;
} clockframe;
E 11
I 11
struct clockframe {
D 13
	u_short	pad;		/* pad to get stack aligned */
E 13
	u_short	sr;		/* sr at time of interrupt */
	u_long	pc;		/* pc at time of interrupt */
	u_short	vo;		/* vector offset (4-word frame) */
};
E 11

D 5
#define	CLKF_USERMODE(framep)	USERMODE((framep)->ps)
#define	CLKF_BASEPRI(framep)	BASEPRI((framep)->ps)
E 5
I 5
D 11
#define	CLKF_USERMODE(framep)	(((framep)->ps & PSL_S) == 0)
#define	CLKF_BASEPRI(framep)	(((framep)->ps & PSL_IPL7) == 0)
E 11
I 11
#define	CLKF_USERMODE(framep)	(((framep)->sr & PSL_S) == 0)
#define	CLKF_BASEPRI(framep)	(((framep)->sr & PSL_IPL) == 0)
E 11
E 5
#define	CLKF_PC(framep)		((framep)->pc)
I 11
#if 0
/* We would like to do it this way... */
#define	CLKF_INTR(framep)	(((framep)->sr & PSL_M) == 0)
#else
/* but until we start using PSL_M, we have to do this instead */
#define	CLKF_INTR(framep)	(0)	/* XXX */
#endif
E 11


/*
 * Preempt the current process if in interrupt from user mode,
 * or after the current trap/syscall if in system mode.
 */
#define	need_resched()	{ want_resched++; aston(); }

D 5

E 5
/*
D 11
 * Give a profiling tick to the current process from the softclock
 * interrupt.  On hp300, request an ast to send us through trap(),
 * marking the proc as needing a profiling tick.
E 11
I 11
 * Give a profiling tick to the current process when the user profiling
 * buffer pages are invalid.  On the hp300, request an ast to send us
 * through trap, marking the proc as needing a profiling tick.
E 11
 */
D 11
#define	profile_tick(p, framep)	{ (p)->p_flag |= SOWEUPC; aston(); }
E 11
I 11
D 16
#define	need_proftick(p)	{ (p)->p_flag |= SOWEUPC; aston(); }
E 16
I 16
#define	need_proftick(p)	{ (p)->p_flag |= P_OWEUPC; aston(); }
E 16
E 11

I 5
/*
 * Notify the current process (p) that it has a signal pending,
 * process as soon as possible.
 */
#define	signotify(p)	aston()

#define aston() (astpending++)

int	astpending;		/* need to trap before returning to user mode */
E 5
int	want_resched;		/* resched() was called */


/*
 * simulated software interrupt register
 */
extern unsigned char ssir;

#define SIR_NET		0x1
#define SIR_CLOCK	0x2

#define siroff(x)	ssir &= ~(x)
#define setsoftnet()	ssir |= SIR_NET
#define setsoftclock()	ssir |= SIR_CLOCK

I 14
/*
 * CTL_MACHDEP definitions.
 */
#define	CPU_CONSDEV		1	/* dev_t: console terminal device */
#define	CPU_MAXID		2	/* number of valid machdep ids */
E 14

I 14
#define CTL_MACHDEP_NAMES { \
	{ 0, 0 }, \
	{ "console_device", CTLTYPE_STRUCT }, \
}
E 14

/*
 * The rest of this should probably be moved to ../hp300/hp300cpu.h,
 * although some of it could probably be put into generic 68k headers.
 */

E 4
/* values for machineid */
D 3
#define HP_320		0	/* 16Mhz 68020+HP MMU+16K external cache */
#define HP_330		1	/* 16Mhz 68020+68851 MMU */
#define HP_350		2	/* 25Mhz 68020+HP MMU+32K external cache */
#define HP_360		3	/* 25Mhz 68030 */
#define HP_370		4	/* 33Mhz 68030+64K external cache */
#define HP_340		5	/* 16Mhz 68030 */
I 2
#define HP_375		6	/* 50Mhz 68030+32K external cache */
E 3
I 3
#define	HP_320		0	/* 16Mhz 68020+HP MMU+16K external cache */
#define	HP_330		1	/* 16Mhz 68020+68851 MMU */
#define	HP_350		2	/* 25Mhz 68020+HP MMU+32K external cache */
#define	HP_360		3	/* 25Mhz 68030 */
#define	HP_370		4	/* 33Mhz 68030+64K external cache */
#define	HP_340		5	/* 16Mhz 68030 */
#define	HP_375		6	/* 50Mhz 68030+32K external cache */
I 10
#define	HP_380		7	/* 25Mhz 68040 */
I 13
#define HP_433		8	/* 33Mhz 68040 */
E 13
E 10
E 3
E 2

/* values for mmutype (assigned for quick testing) */
I 10
#define	MMU_68040	-2	/* 68040 on-chip MMU */
E 10
D 3
#define MMU_68030	-1	/* 68030 on-chip subset of 68851 */
#define MMU_HP		0	/* HP proprietary */
#define MMU_68851	1	/* Motorola 68851 */
E 3
I 3
#define	MMU_68030	-1	/* 68030 on-chip subset of 68851 */
#define	MMU_HP		0	/* HP proprietary */
#define	MMU_68851	1	/* Motorola 68851 */
E 3

/* values for ectype */
D 3
#define EC_PHYS		-1	/* external physical address cache */
#define EC_NONE		0	/* no external cache */
#define EC_VIRT		1	/* external virtual address cache */
E 3
I 3
#define	EC_PHYS		-1	/* external physical address cache */
#define	EC_NONE		0	/* no external cache */
#define	EC_VIRT		1	/* external virtual address cache */
E 3

/* values for cpuspeed (not really related to clock speed due to caches) */
D 3
#define MHZ_8		1
#define MHZ_16		2
#define MHZ_25		3
#define MHZ_33		4
I 2
#define MHZ_50		6
E 3
I 3
#define	MHZ_8		1
#define	MHZ_16		2
#define	MHZ_25		3
#define	MHZ_33		4
#define	MHZ_50		6
E 3
E 2

#ifdef KERNEL
extern	int machineid, mmutype, ectype;
D 3
extern	int IObase;
E 3
I 3
D 6
extern	unsigned long DIObase;
E 6
I 6
extern	char *intiobase, *intiolimit;
E 6
E 3

/* what is this supposed to do? i.e. how is it different than startrtclock? */
#define	enablertclock()

#endif

/* physical memory sections */
D 3
#define ROMBASE		(0x00000000)
#define IOBASE		(0x00200000)
#define IOTOP		(0x01000000)
#define MAXADDR		(0xFFFFF000)
E 3
I 3
#define	ROMBASE		(0x00000000)
D 6
#define	IOBASE		(0x00200000)
#define	IOTOP		(0x01000000)
E 6
I 6
#define	INTIOBASE	(0x00400000)
#define	INTIOTOP	(0x00600000)
#define	EXTIOBASE	(0x00600000)
#define	EXTIOTOP	(0x20000000)
E 6
#define	MAXADDR		(0xFFFFF000)
E 3

D 3
/* IO space stuff */
#define EXTIOBASE	(0x00600000)
E 3
I 3
D 6
/* DIO space stuff */
#define	INTERNALHPIB	(0x00478000)
#define	EXTIOBASE	(0x00600000)
E 3
#define	IOCARDSIZE	(0x10000)
#define	IOMAPSIZE	(btoc(IOTOP-IOBASE))
#define	IOP(x)		((x) - IOBASE)
D 3
#define	IOV(x)		(((x) - IOBASE) + (int)&IObase)
#define UNIOV(x)	((x) - (int)&IObase + IOBASE)
E 3
I 3
#define	IOV(x)		(((x) - IOBASE) + DIObase)
#define	UNIOV(x)	((x) - DIObase + IOBASE)
E 6
I 6
/*
 * Internal IO space:
 *
 * Ranges from 0x400000 to 0x600000 (IIOMAPSIZE).
 *
 * Internal IO space is mapped in the kernel from ``intiobase'' to
 * ``intiolimit'' (defined in locore.s).  Since it is always mapped,
 * conversion between physical and kernel virtual addresses is easy.
 */
#define	ISIIOVA(va) \
	((char *)(va) >= intiobase && (char *)(va) < intiolimit)
#define	IIOV(pa)	((int)(pa)-INTIOBASE+(int)intiobase)
#define	IIOP(va)	((int)(va)-(int)intiobase+INTIOBASE)
#define	IIOPOFF(pa)	((int)(pa)-INTIOBASE)
#define	IIOMAPSIZE	btoc(INTIOTOP-INTIOBASE)	/* 2mb */
E 6
E 3

D 6
/* DIO II uncached address space */
E 6
I 6
/*
 * External IO space:
 *
 * DIO ranges from select codes 0-63 at physical addresses given by:
 *	0x600000 + (sc - 32) * 0x10000
 * DIO cards are addressed in the range 0-31 [0x600000-0x800000) for
 * their control space and the remaining areas, [0x200000-0x400000) and
 * [0x800000-0x1000000), are for additional space required by a card;
 * e.g. a display framebuffer.
 *
 * DIO-II ranges from select codes 132-255 at physical addresses given by:
 *	0x1000000 + (sc - 132) * 0x400000
 * The address range of DIO-II space is thus [0x1000000-0x20000000).
 *
 * DIO/DIO-II space is too large to map in its entirety, instead devices
 * are mapped into kernel virtual address space allocated from a range
 * of EIOMAPSIZE pages (vmparam.h) starting at ``extiobase''.
 */
#define	DIOBASE		(0x600000)
#define	DIOTOP		(0x1000000)
#define	DIOCSIZE	(0x10000)
E 6
D 3
#define DIOIIBASE	(0x01000000)
#define DIOIITOP	(0x20000000)
#define DIOIICSIZE	(0x00400000)
E 3
I 3
#define	DIOIIBASE	(0x01000000)
#define	DIOIITOP	(0x20000000)
#define	DIOIICSIZE	(0x00400000)
E 3

D 3
/* offsets for longword read/write */
#define	MMUSSTP		IOP(0x5F4000)
#define	MMUUSTP		IOP(0x5F4004)
#define	MMUTBINVAL	IOP(0x5F4008)
#define	MMUSTAT		IOP(0x5F400C)
E 3
I 3
D 6
/* base/offsets for longword read/write (for locore.s) */
#define	MMUBASE		IOP(0x5F4000)
E 6
I 6
/*
 * HP MMU
 */
#define	MMUBASE		IIOPOFF(0x5F4000)
E 6
#define	MMUSSTP		0x0
#define	MMUUSTP		0x4
#define	MMUTBINVAL	0x8
#define	MMUSTAT		0xC
E 3
#define	MMUCMD		MMUSTAT

D 3
#define MMU_UMEN	0x0001	/* enable user mapping */
#define MMU_SMEN	0x0002	/* enable supervisor mapping */
#define MMU_CEN		0x0004	/* enable data cache */
#define MMU_BERR	0x0008	/* bus error */
#define MMU_IEN		0x0020	/* enable instruction cache */
#define MMU_FPE		0x0040	/* enable 68881 FP coprocessor */
#define MMU_WPF		0x2000	/* write protect fault */
#define MMU_PF		0x4000	/* page fault */
#define MMU_PTF		0x8000	/* page table fault */
E 3
I 3
#define	MMU_UMEN	0x0001	/* enable user mapping */
#define	MMU_SMEN	0x0002	/* enable supervisor mapping */
#define	MMU_CEN		0x0004	/* enable data cache */
#define	MMU_BERR	0x0008	/* bus error */
#define	MMU_IEN		0x0020	/* enable instruction cache */
#define	MMU_FPE		0x0040	/* enable 68881 FP coprocessor */
#define	MMU_WPF		0x2000	/* write protect fault */
#define	MMU_PF		0x4000	/* page fault */
#define	MMU_PTF		0x8000	/* page table fault */
E 3

D 3
#define MMU_FAULT	(MMU_PTF|MMU_PF|MMU_WPF|MMU_BERR)
#define MMU_ENAB	(MMU_UMEN|MMU_SMEN|MMU_IEN|MMU_FPE)
E 3
I 3
#define	MMU_FAULT	(MMU_PTF|MMU_PF|MMU_WPF|MMU_BERR)
#define	MMU_ENAB	(MMU_UMEN|MMU_SMEN|MMU_IEN|MMU_FPE)
E 3

I 6
/*
 * 68851 and 68030 MMU
 */
E 6
D 3
#define PMMU_LVLMASK	0x0007
#define PMMU_INV	0x0400
#define PMMU_WP		0x0800
#define PMMU_ALV	0x1000
#define PMMU_SO		0x2000
#define PMMU_LV		0x4000
#define PMMU_BE		0x8000
E 3
I 3
#define	PMMU_LVLMASK	0x0007
#define	PMMU_INV	0x0400
#define	PMMU_WP		0x0800
#define	PMMU_ALV	0x1000
#define	PMMU_SO		0x2000
#define	PMMU_LV		0x4000
#define	PMMU_BE		0x8000
E 3
D 6

E 6
D 3
#define PMMU_FAULT	(PMMU_WP|PMMU_INV)
E 3
I 3
#define	PMMU_FAULT	(PMMU_WP|PMMU_INV)
E 3

I 10
/*
 * 68040 MMU
 */
#define	MMU4_RES	0x001
#define	MMU4_TTR	0x002
#define	MMU4_WP		0x004
#define	MMU4_MOD	0x010
#define	MMU4_CMMASK	0x060
#define	MMU4_SUP	0x080
#define	MMU4_U0		0x100
#define	MMU4_U1		0x200
#define	MMU4_GLB	0x400
#define	MMU4_BE		0x800

E 10
D 3
/* function code for user data space */
#define	FC_USERD	1
/* methinks the following is used to selectively clear TLB entries */
#define FC_PURGE	3
E 3
I 3
/* 680X0 function codes */
#define	FC_USERD	1	/* user data space */
#define	FC_USERP	2	/* user program space */
#define	FC_PURGE	3	/* HPMMU: clear TLB entries */
#define	FC_SUPERD	5	/* supervisor data space */
#define	FC_SUPERP	6	/* supervisor program space */
#define	FC_CPU		7	/* CPU space */
E 3

/* fields in the 68020 cache control register */
D 3
#define IC_ENABLE	0x0001	/* enable instruction cache */
#define IC_FREEZE	0x0002	/* freeze instruction cache */
#define IC_CE		0x0004	/* clear instruction cache entry */
#define IC_CLR		0x0008	/* clear entire instruction cache */
E 3
I 3
#define	IC_ENABLE	0x0001	/* enable instruction cache */
#define	IC_FREEZE	0x0002	/* freeze instruction cache */
#define	IC_CE		0x0004	/* clear instruction cache entry */
#define	IC_CLR		0x0008	/* clear entire instruction cache */
E 3

/* additional fields in the 68030 cache control register */
D 3
#define IC_BE		0x0010	/* instruction burst enable */
#define DC_ENABLE	0x0100	/* data cache enable */
#define DC_FREEZE	0x0200	/* data cache freeze */
#define DC_CE		0x0400	/* clear data cache entry */
#define DC_CLR		0x0800	/* clear entire data cache */
#define DC_BE		0x1000	/* data burst enable */
#define DC_WA		0x2000	/* write allocate */
E 3
I 3
#define	IC_BE		0x0010	/* instruction burst enable */
#define	DC_ENABLE	0x0100	/* data cache enable */
#define	DC_FREEZE	0x0200	/* data cache freeze */
#define	DC_CE		0x0400	/* clear data cache entry */
#define	DC_CLR		0x0800	/* clear entire data cache */
#define	DC_BE		0x1000	/* data burst enable */
#define	DC_WA		0x2000	/* write allocate */
E 3

D 3
#define CACHE_ON	(DC_WA|DC_BE|DC_CLR|DC_ENABLE|IC_BE|IC_CLR|IC_ENABLE)
#define CACHE_OFF	(DC_CLR|IC_CLR)
#define CACHE_CLR	(CACHE_ON)
#define IC_CLEAR	(DC_WA|DC_BE|DC_ENABLE|IC_BE|IC_CLR|IC_ENABLE)
#define DC_CLEAR	(DC_WA|DC_BE|DC_CLR|DC_ENABLE|IC_BE|IC_ENABLE)
E 3
I 3
#define	CACHE_ON	(DC_WA|DC_BE|DC_CLR|DC_ENABLE|IC_BE|IC_CLR|IC_ENABLE)
#define	CACHE_OFF	(DC_CLR|IC_CLR)
#define	CACHE_CLR	(CACHE_ON)
#define	IC_CLEAR	(DC_WA|DC_BE|DC_ENABLE|IC_BE|IC_CLR|IC_ENABLE)
#define	DC_CLEAR	(DC_WA|DC_BE|DC_CLR|DC_ENABLE|IC_BE|IC_ENABLE)
I 10

/* 68040 cache control register */
#define	IC4_ENABLE	0x8000		/* instruction cache enable bit */
#define	DC4_ENABLE	0x80000000	/* data cache enable bit */

#define	CACHE4_ON	(IC4_ENABLE|DC4_ENABLE)
#define	CACHE4_OFF	(0)
E 10
E 3
E 1
