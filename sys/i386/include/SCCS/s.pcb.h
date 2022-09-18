h11473
s 00002/00002/00056
d D 8.2 94/01/21 19:45:52 bostic 17 16
c copyright typo
e
s 00000/00000/00058
d D 8.1 93/06/11 15:49:28 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00029/00055
d D 5.13 93/06/11 15:49:22 bostic 15 13
c put the keywords back
e
s 00002/00002/00082
d R 8.1 93/06/11 15:48:09 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00002/00048
d D 5.12 93/06/10 21:57:32 cgd 13 12
c add (bogus) md_coredump stuct, to allow us to compile more
e
s 00002/00002/00048
d D 5.11 92/10/11 10:11:58 bostic 12 11
c make kernel includes standard
e
s 00002/00000/00048
d D 5.10 91/05/12 20:09:39 william 11 10
c ifdef KERNEL'ed the externs
e
s 00023/00023/00025
d D 5.9 91/05/09 18:08:26 william 10 9
c last minute changes, updating present version
e
s 00003/00003/00045
d D 5.8 91/05/09 17:50:28 william 9 8
c interim version
e
s 00001/00000/00047
d D 5.7 91/03/22 21:58:41 william 8 7
c added flag bit to note which kind of entry into kernele
e
s 00001/00001/00046
d D 5.6 91/01/18 14:32:13 william 7 6
c fixed just which copyright notice is included.
e
s 00008/00006/00039
d D 5.5 91/01/15 15:21:36 william 6 5
c trivia, reno changes, and kernel reorg
e
s 00000/00000/00045
d D 5.4 91/01/15 12:22:03 bill 5 4
c reno changes
e
s 00001/00001/00044
d D 5.3 90/11/14 19:48:14 bill 4 3
c name conflict in header files
e
s 00005/00002/00040
d D 5.2 90/11/14 13:37:14 bill 3 2
c fpu->npx, emc additions, bigger sigc if needed, save interrupt mask level,...
e
s 00015/00001/00027
d D 5.1 90/04/24 18:52:19 william 2 1
c 1st Berkeley Release
e
s 00028/00000/00000
d D 1.1 90/03/12 15:48:14 bill 1 0
c date and time created 90/03/12 15:48:14 by bill
e
u
U
t
T
I 2
/*-
D 15
 * Copyright (c) 1990 The Regents of the University of California.
E 15
I 15
D 17
 * Copyright (c) 1993 The Regents of the University of California.
E 15
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 7
 * %sccs.include.noredist.c%
E 7
I 7
D 13
 * %sccs.include.redist.c%
E 13
I 13
D 15
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 13
E 7
 *
D 13
 *	%W% (Berkeley) %G%
E 13
I 13
D 15
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)pcb.h	5.11 (Berkeley) 10/11/92
E 15
I 15
 *	%W% (Berkeley) %G%
E 15
E 13
 */

I 9
D 10

E 10
E 9
E 2
I 1
/*
 * Intel 386 process control block
 */
D 9
#include "tss.h"
D 3
#include "fpu.h"
E 3
I 3
D 4
#include "npx.h"
E 4
I 4
D 6
#include "../i386/npx.h"
E 6
I 6
#include "npx.h"
E 9
I 9
D 12
#include "machine/tss.h"
#include "machine/npx.h"
E 12
I 12
#include <machine/tss.h>
#include <machine/npx.h>
E 12
E 9
E 6
E 4
E 3

struct pcb {
D 10
	struct	i386tss pcbtss;
#define	pcb_ksp	pcbtss.tss_esp0
#define	pcb_ptd	pcbtss.tss_cr3
E 10
I 10
	struct	i386tss pcb_tss;
#define	pcb_ksp	pcb_tss.tss_esp0
#define	pcb_ptd	pcb_tss.tss_cr3
E 10
I 6
#define	pcb_cr3	pcb_ptd
E 6
D 10
#define	pcb_pc	pcbtss.tss_eip
#define	pcb_psl	pcbtss.tss_eflags
#define	pcb_usp	pcbtss.tss_esp
#define	pcb_fp	pcbtss.tss_ebp
E 10
I 10
#define	pcb_pc	pcb_tss.tss_eip
#define	pcb_psl	pcb_tss.tss_eflags
#define	pcb_usp	pcb_tss.tss_esp
#define	pcb_fp	pcb_tss.tss_ebp
#ifdef	notyet
	u_char	pcb_iomap[NPORT/sizeof(u_char)]; /* i/o port bitmap */
#endif
	struct	save87	pcb_savefpu;	/* floating point state for 287/387 */
	struct	emcsts	pcb_saveemc;	/* Cyrix EMC state */
E 10
/*
 * Software pcb (extension)
 */
I 2
D 6
	int	pcb_fpsav;
#define	FP_NEEDSAVE	0x1	/* need save on next context switch */
#define	FP_NEEDRESTORE	0x2	/* need restore on next DNA fault */
I 3
#define	FP_USESEMC	0x4	/* process uses EMC memory-mapped mode */
E 6
I 6
	int	pcb_flags;
D 10
#define	FP_WASUSED	0x1	/* floating point has been used in this proc */
#define	FP_NEEDSSAVE	0x2	/* needs save on next context switch */
#define	FP_NEEDSRESTORE	0x4	/* need restore on next DNA fault */
#define	FP_USESEMC	0x8	/* process uses EMC memory-mapped mode */
I 8
D 9
#define	EX_TRAPSTK	0x10	/* process entered with a trap stack frame */
E 9
E 8
E 6
E 3
E 2
	struct	save87	pcb_savefpu;
I 3
	struct	emcsts	pcb_saveemc;
E 3
	struct	pte	*pcb_p0br;
	struct	pte	*pcb_p1br;
	int	pcb_p0lr;
	int	pcb_p1lr;
	int	pcb_szpt; 	/* number of pages of user page table */
	int	pcb_cmap2;
	int	*pcb_sswap;
D 3
	long	pcb_sigc[5];	/* sigcode actually 19 bytes */
E 3
I 3
D 6
	long	pcb_sigc[8];	/* sigcode actually 19 bytes */
E 6
I 6
	long	pcb_sigc[8];
E 6
	int	pcb_iml;	/* interrupt mask level */
E 10
I 10
#define	FP_WASUSED	0x01	/* floating point has been used in this proc */
#define	FP_NEEDSSAVE	0x02	/* needs save on next context switch */
#define	FP_NEEDSRESTORE	0x04	/* need restore on next DNA fault */
#define	FP_USESEMC	0x08	/* process uses EMC memory-mapped mode */
#define	FM_TRAP		0x10	/* process entered kernel on a trap frame */
	short	pcb_iml;	/* interrupt mask level */
	caddr_t	pcb_onfault;	/* copyin/out fault recovery */
	long	pcb_sigc[8];	/* XXX signal code trampoline */
	int	pcb_cmap2;	/* XXX temporary PTE - will prefault instead */
I 13
};

/*
 * The pcb is augmented with machine-dependent additional data for
 * core dumps. For the i386: ???
 */
struct md_coredump {
        int     pad;		/* XXX? -- cgd */
E 13
E 10
E 3
};
I 10

I 11
#ifdef KERNEL
E 11
struct pcb *curpcb;		/* our current running pcb */
I 11
#endif
E 11
E 10
D 2

E 2
E 1
