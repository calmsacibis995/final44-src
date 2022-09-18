h44082
s 00002/00002/00038
d D 8.1 93/06/10 21:44:56 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00012/00037
d D 7.7 92/12/27 09:27:11 hibler 7 6
c much goo moved to proc.h
e
s 00008/00000/00041
d D 7.6 92/06/19 23:16:38 mckusick 6 5
c add (unused) md_coredump
e
s 00008/00007/00033
d D 7.5 92/06/05 15:29:21 hibler 5 4
c merge latest Utah hp300 code including 68040 support
e
s 00005/00023/00035
d D 7.4 91/05/04 19:54:38 karels 4 3
c rm sswap, sigcode; ast's now global, not in pcb; need to use
c <machine/frame.h> so user code compiles
e
s 00001/00005/00057
d D 7.3 90/12/16 16:37:24 bostic 3 2
c kernel reorg
e
s 00001/00005/00061
d D 7.2 90/12/05 19:30:19 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00066/00000/00000
d D 7.1 90/05/08 17:51:19 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 8
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: pcb.h 1.13 89/04/23$
E 5
I 5
 * from: Utah $Hdr: pcb.h 1.14 91/03/25$
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 3
#ifdef KERNEL
#include "frame.h"
#else
#include <hp300/frame.h>
#endif
E 3
I 3
D 4
#include <hp300/include/frame.h>
E 4
I 4
#include <machine/frame.h>
E 4
E 3

/*
 * HP300 process control block
 */
struct pcb
{
D 5
	short	pcb_flags;	/* misc. process flags (+0) */
	short	pcb_ps; 	/* processor status word (+2) */
	int	pcb_ustp;	/* user segment table pointer (+4) */
	int	pcb_usp;	/* user stack pointer (+8) */
	int	pcb_regs[12];	/* D0-D7, A0-A7 (+C) */
D 2
	struct pte *pcb_p0br;	/* P0 base register (+3C) */
	int	pcb_p0lr;	/* P0 length register (+40) */
	struct pte *pcb_p1br;	/* P1 base register (+44) */
	int	pcb_p1lr;	/* P1 length register (+48) */
	int	pcb_szpt; 	/* number of pages of user page table (+4C) */
E 2
I 2
D 4
	int	pcb_pad[5];
E 2
	int	pcb_cmap2;	/* temporary copy PTE (+50) */
	int	*pcb_sswap;	/* saved context for swap return (+54) */
	short	pcb_sigc[12];	/* signal trampoline code (+58) */
	caddr_t	pcb_onfault;	/* for copyin/out faults (+70) */
	struct fpframe pcb_fpregs; /* 68881/2 context save area (+74) */
	int	pcb_exec[16];	/* exec structure for core dumps (+1B8) */
	int	pcb_res[2];	/* reserved for future expansion (+1F8) */
E 4
I 4
	int	pcb_cmap2;	/* temporary copy PTE */
E 5
I 5
	short	pcb_flags;	/* misc. process flags */
	short	pcb_ps; 	/* processor status word */
	int	pcb_ustp;	/* user segment table pointer */
	int	pcb_usp;	/* user stack pointer */
	int	pcb_regs[12];	/* D2-D7, A2-A7 */
E 5
	caddr_t	pcb_onfault;	/* for copyin/out faults */
	struct	fpframe pcb_fpregs; /* 68881/2 context save area */
D 7
	int	pcb_exec[16];	/* exec structure for core dumps */
E 7
E 4
};

D 7
/* flags */

D 4
#define	PCB_AST		0x0001	/* async trap pending */
E 4
#define PCB_HPUXMMAP	0x0010	/* VA space is multiple mapped */
#define PCB_HPUXTRACE	0x0020	/* being traced by an HPUX process */
#define PCB_HPUXBIN	0x0040	/* loaded from an HPUX format binary */
				/* note: does NOT imply SHPUX */
I 5
#define PCB_CCBDATA	0x0100	/* copyback caching of data */
#define PCB_CCBSTACK	0x0200	/* copyback caching of stack */
I 6

E 7
/*
 * The pcb is augmented with machine-dependent additional data for
D 7
 * core dumps. For the hp300, there is nothing to add.
E 7
I 7
 * core dumps. For the hp300, this includes an HP-UX exec header
 * which is dumped for HP-UX processes.
E 7
 */
struct md_coredump {
D 7
	long	md_pad[8];
E 7
I 7
	int	md_exec[16];	/* exec structure for HP-UX core dumps */
E 7
};
E 6
E 5
D 4

#define aston() \
	{ \
		u.u_pcb.pcb_flags |= PCB_AST; \
	}

#define astoff() \
	{ \
		u.u_pcb.pcb_flags &= ~PCB_AST; \
	}

#define astpend() \
	(u.u_pcb.pcb_flags & PCB_AST)
E 4
E 1
