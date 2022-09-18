h22258
s 00000/00002/00235
d D 8.3 93/11/11 13:48:17 torek 7 6
c need <machine/instr.h> even ifndef DIAGNOSTIC
e
s 00007/00002/00230
d D 8.2 93/09/27 14:02:52 torek 6 5
c 1.21: rm bogus stray interrupt time assignment (from dab@berserkly.cray.com)
c 1.22: trap table is protected (at least without kgdb)
e
s 00002/00002/00230
d D 8.1 93/06/11 15:16:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00229
d D 7.4 93/04/20 23:12:52 torek 4 3
c ctlreg.h moves; fix copyright spelling
e
s 00008/00008/00224
d D 7.3 92/10/11 12:57:11 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00227
d D 7.2 92/07/21 16:54:26 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00227/00000/00000
d D 7.1 92/07/13 00:44:35 torek 1 0
c date and time created 92/07/13 00:44:35 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: intr.c,v 1.18 92/07/09 00:47:43 torek Exp $ (LBL)
E 4
I 4
D 6
 * from: $Header: intr.c,v 1.20 92/11/26 03:04:53 torek Exp $ (LBL)
E 6
I 6
 * from: $Header: intr.c,v 1.22 93/09/26 19:48:06 torek Exp $ (LBL)
E 6
E 4
 */

D 3
#include "sys/param.h"
#include "sys/kernel.h"
E 3
I 3
#include <sys/param.h>
#include <sys/kernel.h>
E 3

I 6
#include <vm/vm.h>

E 6
D 3
#include "net/netisr.h"
E 3
I 3
#include <net/netisr.h>
E 3

D 3
#include "machine/cpu.h"
E 3
I 3
#include <machine/cpu.h>
I 4
#include <machine/ctlreg.h>
E 4
E 3
D 7
#ifdef DIAGNOSTIC
E 7
D 3
#include "machine/instr.h"
E 3
I 3
#include <machine/instr.h>
E 3
D 7
#endif
E 7
D 3
#include "machine/trap.h"
E 3
I 3
#include <machine/trap.h>
E 3

D 3
#include "clockreg.h"
#include "ctlreg.h"
E 3
I 3
#include <sparc/sparc/clockreg.h>
D 4
#include <sparc/sparc/ctlreg.h>
E 4
E 3

/*
 * Stray interrupt handler.  Clear it if possible.
 * If not, and if we get 10 interrupts in 10 seconds, panic.
 */
void
strayintr(fp)
	struct clockframe *fp;
{
	static int straytime, nstray;
	int timesince;

	printf("stray interrupt ipl %x pc=%x npc=%x psr=%b\n",
	    fp->ipl, fp->pc, fp->npc, fp->psr, PSR_BITS);
	timesince = time.tv_sec - straytime;
D 6
	straytime = time.tv_sec;
E 6
	if (timesince <= 10) {
		if (++nstray > 9)
			panic("crazy interrupts");
	} else {
		straytime = time.tv_sec;
		nstray = 1;
	}
}

extern int clockintr();		/* level 10 (clock) interrupt code */
static struct intrhand level10 = { clockintr };

extern int statintr();		/* level 14 (statclock) interrupt code */
static struct intrhand level14 = { statintr };

/*
 * Level 1 software interrupt (could also be Sbus level 1 interrupt).
 * Three possible reasons:
 *	ROM console input needed
 *	Network software interrupt
 *	Soft clock interrupt
 */
int
soft01intr(fp)
	void *fp;
{
	extern int rom_console_input;

	if (rom_console_input && cnrom())
		cnrint();
	if (sir.sir_any) {
		/*
		 * XXX	this is bogus: should just have a list of
		 *	routines to call, a la timeouts.  Mods to
		 *	netisr are not atomic and must be protected (gah).
		 */
		if (sir.sir_which[SIR_NET]) {
			int n, s;

			s = splhigh();
			n = netisr;
			netisr = 0;
			splx(s);
			sir.sir_which[SIR_NET] = 0;
#ifdef INET
			if (n & (1 << NETISR_ARP))
				arpintr();
			if (n & (1 << NETISR_IP))
				ipintr();
#endif
#ifdef NS
			if (n & (1 << NETISR_NS))
				nsintr();
#endif
#ifdef ISO
			if (n & (1 << NETISR_ISO))
				clnlintr();
#endif
		}
		if (sir.sir_which[SIR_CLOCK]) {
			sir.sir_which[SIR_CLOCK] = 0;
			softclock();
		}
	}
	return (1);
}

static struct intrhand level01 = { soft01intr };

/*
 * Level 15 interrupts are special, and not vectored here.
 * Only `prewired' interrupts appear here; boot-time configured devices
 * are attached via intr_establish() below.
 */
struct intrhand *intrhand[15] = {
	NULL,			/*  0 = error */
	&level01,		/*  1 = software level 1 + Sbus */
	NULL,	 		/*  2 = Sbus level 2 */
	NULL,			/*  3 = SCSI + DMA + Sbus level 3 */
	NULL,			/*  4 = software level 4 (tty softint) */
	NULL,			/*  5 = Ethernet + Sbus level 4 */
	NULL,			/*  6 = software level 6 (not used) */
	NULL,			/*  7 = video + Sbus level 5 */
	NULL,			/*  8 = Sbus level 6 */
	NULL,			/*  9 = Sbus level 7 */
	&level10,		/* 10 = counter 0 = clock */
	NULL,			/* 11 = floppy */
	NULL,			/* 12 = zs hardware interrupt */
	NULL,			/* 13 = audio chip */
	&level14,		/* 14 = counter 1 = profiling timer */
};

static int fastvec;		/* marks fast vectors (see below) */
#ifdef DIAGNOSTIC
extern int sparc_interrupt[];
#endif

/*
 * Attach an interrupt handler to the vector chain for the given level.
 * This is not possible if it has been taken away as a fast vector.
 */
void
intr_establish(level, ih)
	int level;
	struct intrhand *ih;
{
	register struct intrhand **p, *q;
#ifdef DIAGNOSTIC
	register struct trapvec *tv;
	register int displ;
#endif
	int s;

	s = splhigh();
	if (fastvec & (1 << level))
		panic("intr_establish: level %d interrupt tied to fast vector",
		    level);
#ifdef DIAGNOSTIC
	/* double check for legal hardware interrupt */
	if (level != 1 && level != 4 && level != 6) {
		tv = &trapbase[T_L1INT - 1 + level];
		displ = &sparc_interrupt[0] - &tv->tv_instr[1];
		/* has to be `mov level,%l3; ba _sparc_interrupt; rdpsr %l0' */
		if (tv->tv_instr[0] != I_MOVi(I_L3, level) ||
		    tv->tv_instr[1] != I_BA(0, displ) ||
		    tv->tv_instr[2] != I_RDPSR(I_L0))
			panic("intr_establish(%d, %x)\n%x %x %x != %x %x %x",
			    level, ih,
			    tv->tv_instr[0], tv->tv_instr[1], tv->tv_instr[2],
			    I_MOVi(I_L3, level), I_BA(0, displ), I_RDPSR(I_L0));
	}
#endif
	/*
	 * This is O(N^2) for long chains, but chains are never long
	 * and we do want to preserve order.
	 */
	for (p = &intrhand[level]; (q = *p) != NULL; p = &q->ih_next)
		continue;
	*p = ih;
	ih->ih_next = NULL;
	splx(s);
}

/*
 * Like intr_establish, but wires a fast trap vector.  Only one such fast
 * trap is legal for any interrupt, and it must be a hardware interrupt.
 */
void
intr_fasttrap(level, vec)
	int level;
	void (*vec) __P((void));
{
	register struct trapvec *tv;
	register u_long hi22, lo10;
#ifdef DIAGNOSTIC
	register int displ;	/* suspenders, belt, and buttons too */
#endif
	int s;

	tv = &trapbase[T_L1INT - 1 + level];
	hi22 = ((u_long)vec) >> 10;
	lo10 = ((u_long)vec) & 0x3ff;
	s = splhigh();
	if ((fastvec & (1 << level)) != 0 || intrhand[level] != NULL)
		panic("intr_fasttrap: already handling level %d interrupts",
		    level);
#ifdef DIAGNOSTIC
	displ = &sparc_interrupt[0] - &tv->tv_instr[1];
	/* has to be `mov level,%l3; ba _sparc_interrupt; rdpsr %l0' */
	if (tv->tv_instr[0] != I_MOVi(I_L3, level) ||
	    tv->tv_instr[1] != I_BA(0, displ) ||
	    tv->tv_instr[2] != I_RDPSR(I_L0))
		panic("intr_fasttrap(%d, %x)\n%x %x %x != %x %x %x",
		    level, vec,
		    tv->tv_instr[0], tv->tv_instr[1], tv->tv_instr[2],
		    I_MOVi(I_L3, level), I_BA(0, displ), I_RDPSR(I_L0));
#endif
I 6
	/* kernel text is write protected -- let us in for a moment */
	pmap_changeprot(kernel_pmap, (vm_offset_t)tv,
	    VM_PROT_READ|VM_PROT_WRITE, 1);
E 6
	tv->tv_instr[0] = I_SETHI(I_L3, hi22);	/* sethi %hi(vec),%l3 */
	tv->tv_instr[1] = I_JMPLri(I_G0, I_L3, lo10);/* jmpl %l3+%lo(vec),%g0 */
	tv->tv_instr[2] = I_RDPSR(I_L0);	/* mov %psr, %l0 */
I 6
	pmap_changeprot(kernel_pmap, (vm_offset_t)tv, VM_PROT_READ, 1);
E 6
	fastvec |= 1 << level;
	splx(s);
}
E 1
