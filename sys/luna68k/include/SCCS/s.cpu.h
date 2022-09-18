h51626
s 00001/00000/00187
d D 8.6 95/05/17 21:32:33 mckusick 11 10
c add definition for ability to produce a backtrace
e
s 00001/00000/00186
d D 8.5 94/01/05 09:50:16 mckusick 10 9
c add cpu_swapin (nothing needed)
e
s 00004/00004/00182
d D 8.4 93/12/10 17:45:09 mckusick 9 8
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00001/00001/00185
d D 8.3 93/12/06 20:38:48 akito 8 7
c sync up to hp300/include/cpu.h  8.2 (Berkeley) 9/23/93
e
s 00001/00001/00185
d D 8.2 93/09/23 16:43:17 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00184
d D 8.1 93/06/10 22:22:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00001/00174
d D 7.5 93/05/25 13:12:47 akito 5 4
c added CTL_MACHDEP support
e
s 00008/00000/00167
d D 7.4 93/05/12 04:09:53 akito 4 3
c LUNA-II (68040 based LUNA) support
e
s 00003/00006/00164
d D 7.3 93/01/02 13:37:23 akito 3 2
c sync up to hp300/include/cpu.h  7.13
e
s 00025/00024/00145
d D 7.2 92/07/23 16:12:02 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00169/00000/00000
d D 7.1 92/06/15 06:28:17 fujita 1 0
c date and time created 92/06/15 06:28:17 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 6
 * Copyright (c) 1982, 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: cpu.h 1.16 91/03/25$
D 3
 * OMRON: $Id: cpu.h,v 1.2 92/06/14 06:27:54 moti Exp $
E 3
I 3
D 5
 * from: hp300/include/cpu.h	7.13 (Berkeley) 12/27/92
E 5
I 5
D 8
 * from: hp300/include/cpu.h	7.14 (Berkeley) 5/20/93
E 8
I 8
 * from: hp300/include/cpu.h	8.2 (Berkeley) 9/23/93
E 8
E 5
E 3
 *
I 2
D 3
 * from: hp300/include/cpu.h   7.12 (Berkeley) 7/8/92
 *
E 3
E 2
 *	%W% (Berkeley) %G%
 */

/*
D 3
 * Exported definitions unique to luna/68k cpu support, taken from:
 * hp300/68k.
E 3
I 3
 * Exported definitions unique to luna/68k cpu support,
 * taken from hp300/68k.
E 3
 */

/*
 * definitions of cpu-dependent requirements
 * referenced in generic code
 */
#define	COPY_SIGCODE		/* copy sigcode above user stack in exec */

D 2
/*
 * function vs. inline configuration;
 * these are defined to get generic functions
 * rather than inline or machine-dependent implementations
 */
#define	NEED_MINMAX		/* need {,i,l,ul}{min,max} functions */
#undef	NEED_FFS		/* don't need ffs function */
#undef	NEED_BCMP		/* don't need bcmp function */
#undef	NEED_STRLEN		/* don't need strlen function */

E 2
D 9
#define	cpu_exec(p)	/* nothing */
#define	cpu_wait(p)	/* nothing */
#define cpu_setstack(p, ap) \
	(p)->p_md.md_regs[SP] = ap
E 9
I 9
#define	cpu_exec(p)			/* nothing */
I 10
#define	cpu_swapin(p)			/* nothing */
E 10
#define	cpu_wait(p)			/* nothing */
#define cpu_setstack(p, ap)		(p)->p_md.md_regs[SP] = ap
#define cpu_set_init_frame(p, fp)	(p)->p_md.md_regs = fp
I 11
#define	BACKTRACE(p)			/* not implemented */
E 11
E 9

/*
D 2
 * Arguments to hardclock, softclock and gatherstats
 * encapsulate the previous machine state in an opaque
 * clockframe; for 68k, use just what the hardware
 * leaves on the stack.
E 2
I 2
 * Arguments to hardclock and gatherstats encapsulate the previous
 * machine state in an opaque clockframe.  One the 68k, we use
 * what the hardware pushes on an interrupt (but we pad the sr to a
 * longword boundary).
E 2
 */
D 2
typedef struct intrframe {
	char	*pc;
	int	ps;
} clockframe;
E 2
I 2
struct clockframe {
D 3
	u_short	pad;		/* pad to get stack aligned */
E 3
	u_short	sr;		/* sr at time of interrupt */
	u_long	pc;		/* pc at time of interrupt */
	u_short	vo;		/* vector offset (4-word frame) */
};
E 2

D 2
#define	CLKF_USERMODE(framep)	(((framep)->ps & PSL_S) == 0)
#define	CLKF_BASEPRI(framep)	(((framep)->ps & PSL_IPL7) == 0)
E 2
I 2
#define	CLKF_USERMODE(framep)	(((framep)->sr & PSL_S) == 0)
#define	CLKF_BASEPRI(framep)	(((framep)->sr & PSL_IPL) == 0)
E 2
#define	CLKF_PC(framep)		((framep)->pc)
I 2
#if 0
/* We would like to do it this way... */
#define	CLKF_INTR(framep)	(((framep)->sr & PSL_M) == 0)
#else
/* but until we start using PSL_M, we have to do this instead */
#define	CLKF_INTR(framep)	(0)	/* XXX */
#endif
E 2


/*
 * Preempt the current process if in interrupt from user mode,
 * or after the current trap/syscall if in system mode.
 */
#define	need_resched()	{ want_resched++; aston(); }

/*
D 2
 * Give a profiling tick to the current process from the softclock
 * interrupt.  On 68k, request an ast to send us through trap(),
 * marking the proc as needing a profiling tick.
E 2
I 2
 * Give a profiling tick to the current process when the user profiling
 * buffer pages are invalid.  On the 68k, request an ast to send us
 * through trap, marking the proc as needing a profiling tick.
E 2
 */
D 2
#define	profile_tick(p, framep)	{ (p)->p_flag |= SOWEUPC; aston(); }
E 2
I 2
D 7
#define	need_proftick(p)	{ (p)->p_flag |= SOWEUPC; aston(); }
E 7
I 7
#define	need_proftick(p)	{ (p)->p_flag |= P_OWEUPC; aston(); }
E 7
E 2

/*
 * Notify the current process (p) that it has a signal pending,
 * process as soon as possible.
 */
#define	signotify(p)	aston()

#define aston() (astpending++)

int	astpending;		/* need to trap before returning to user mode */
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
I 5

/*
 * CTL_MACHDEP definitions.
 */
#define	CPU_CONSDEV		1	/* dev_t: console terminal device */
#define	CPU_MAXID		2	/* number of valid machdep ids */

#define CTL_MACHDEP_NAMES { \
	{ 0, 0 }, \
	{ "console_device", CTLTYPE_STRUCT }, \
}
E 5

I 4
#ifdef KERNEL
extern	int mmutype, machineid;
#endif

/* values for machineid */
#define	LUNA_I		1	/* 20Mhz 68030 */
#define	LUNA_II		2	/* 25Mhz 68040 */

E 4
/* values for mmutype (assigned for quick testing) */
#define	MMU_68040	-2	/* 68040 on-chip MMU */
#define	MMU_68030	-1	/* 68030 on-chip subset of 68851 */

/* values for cpuspeed (not really related to clock speed due to caches) */
#define	MHZ_8		1
#define	MHZ_16		2
#define	MHZ_25		3
#define	MHZ_33		4
#define	MHZ_50		6

/*
 * 68851 and 68030 MMU
 */
#define	PMMU_LVLMASK	0x0007
#define	PMMU_INV	0x0400
#define	PMMU_WP		0x0800
#define	PMMU_ALV	0x1000
#define	PMMU_SO		0x2000
#define	PMMU_LV		0x4000
#define	PMMU_BE		0x8000
#define	PMMU_FAULT	(PMMU_WP|PMMU_INV)

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

/* 680X0 function codes */
#define	FC_USERD	1	/* user data space */
#define	FC_USERP	2	/* user program space */
#define	FC_PURGE	3	/* HPMMU: clear TLB entries */
#define	FC_SUPERD	5	/* supervisor data space */
#define	FC_SUPERP	6	/* supervisor program space */
#define	FC_CPU		7	/* CPU space */

/* fields in the 68020 cache control register */
#define	IC_ENABLE	0x0001	/* enable instruction cache */
#define	IC_FREEZE	0x0002	/* freeze instruction cache */
#define	IC_CE		0x0004	/* clear instruction cache entry */
#define	IC_CLR		0x0008	/* clear entire instruction cache */

/* additional fields in the 68030 cache control register */
#define	IC_BE		0x0010	/* instruction burst enable */
#define	DC_ENABLE	0x0100	/* data cache enable */
#define	DC_FREEZE	0x0200	/* data cache freeze */
#define	DC_CE		0x0400	/* clear data cache entry */
#define	DC_CLR		0x0800	/* clear entire data cache */
#define	DC_BE		0x1000	/* data burst enable */
#define	DC_WA		0x2000	/* write allocate */

#define	CACHE_ON	(DC_WA|DC_BE|DC_CLR|DC_ENABLE|IC_BE|IC_CLR|IC_ENABLE)
#define	CACHE_OFF	(DC_CLR|IC_CLR)
#define	CACHE_CLR	(CACHE_ON)
#define	IC_CLEAR	(DC_WA|DC_BE|DC_ENABLE|IC_BE|IC_CLR|IC_ENABLE)
#define	DC_CLEAR	(DC_WA|DC_BE|DC_CLR|DC_ENABLE|IC_BE|IC_ENABLE)

/* 68040 cache control register */
#define	IC4_ENABLE	0x8000		/* instruction cache enable bit */
#define	DC4_ENABLE	0x80000000	/* data cache enable bit */

#define	CACHE4_ON	(IC4_ENABLE|DC4_ENABLE)
#define	CACHE4_OFF	(0)
E 1
