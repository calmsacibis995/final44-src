h24646
s 00002/00002/00050
d D 8.1 93/06/11 15:48:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00051
d D 5.4 91/01/18 14:32:20 william 5 4
c fixed just which copyright notice is included.
e
s 00027/00027/00025
d D 5.3 91/01/15 15:21:41 william 4 3
c trivia, reno changes, and kernel reorg
e
s 00026/00026/00026
d D 5.2 90/11/14 16:49:34 bill 3 2
c correct types (*sigh*)
e
s 00012/00000/00040
d D 5.1 90/04/24 18:52:47 william 2 1
c 1st Berkeley Release
e
s 00040/00000/00000
d D 1.1 90/03/12 15:48:29 bill 1 0
c date and time created 90/03/12 15:48:29 by bill
e
u
U
t
T
I 2
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 5
 * %sccs.include.noredist.c%
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * Intel 386 Context Data Type
 */

D 4

E 4
struct i386tss {
D 3
	int	tss_link;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_esp0; 	/* kernel stack pointer priviledge level 0 */
E 3
I 3
D 4
	long	tss_link;	/* actually 16 bits: top 16 bits must be zero */
	long	tss_esp0; 	/* kernel stack pointer priviledge level 0 */
E 4
I 4
	int	tss_link;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_esp0; 	/* kernel stack pointer priviledge level 0 */
E 4
E 3
#define	tss_ksp	tss_esp0
D 3
	int	tss_ss0;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_esp1; 	/* kernel stack pointer priviledge level 1 */
	int	tss_ss1;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_esp2; 	/* kernel stack pointer priviledge level 2 */
	int	tss_ss2;	/* actually 16 bits: top 16 bits must be zero */
	struct  ptd *tss_cr3; 	/* page table directory */
E 3
I 3
D 4
	long	tss_ss0;	/* actually 16 bits: top 16 bits must be zero */
	long	tss_esp1; 	/* kernel stack pointer priviledge level 1 */
	long	tss_ss1;	/* actually 16 bits: top 16 bits must be zero */
	long	tss_esp2; 	/* kernel stack pointer priviledge level 2 */
	long	tss_ss2;	/* actually 16 bits: top 16 bits must be zero */
	long	tss_cr3; 	/* page table directory physical address */
E 4
I 4
	int	tss_ss0;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_esp1; 	/* kernel stack pointer priviledge level 1 */
	int	tss_ss1;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_esp2; 	/* kernel stack pointer priviledge level 2 */
	int	tss_ss2;	/* actually 16 bits: top 16 bits must be zero */
	/* struct  ptd *tss_cr3; 	/* page table directory */
	int	tss_cr3; 	/* page table directory */
E 4
E 3
#define	tss_ptd	tss_cr3
D 3
	int	tss_eip; 	/* program counter */
E 3
I 3
D 4
	long	tss_eip; 	/* program counter */
E 4
I 4
	int	tss_eip; 	/* program counter */
E 4
E 3
#define	tss_pc	tss_eip
D 3
	int	tss_eflags; 	/* program status longword */
E 3
I 3
D 4
	long	tss_eflags; 	/* program status longword */
E 4
I 4
	int	tss_eflags; 	/* program status longword */
E 4
E 3
#define	tss_psl	tss_eflags
D 3
	int	tss_eax; 
	int	tss_ecx; 
	int	tss_edx; 
	int	tss_ebx; 
	int	tss_esp; 	/* user stack pointer */
E 3
I 3
D 4
	long	tss_eax; 
	long	tss_ecx; 
	long	tss_edx; 
	long	tss_ebx; 
	long	tss_esp; 	/* user stack pointer */
E 4
I 4
	int	tss_eax; 
	int	tss_ecx; 
	int	tss_edx; 
	int	tss_ebx; 
	int	tss_esp; 	/* user stack pointer */
E 4
E 3
#define	tss_usp	tss_esp
D 3
	int	tss_ebp; 	/* user frame pointer */
E 3
I 3
D 4
	long	tss_ebp; 	/* user frame pointer */
E 4
I 4
	int	tss_ebp; 	/* user frame pointer */
E 4
E 3
#define	tss_fp	tss_ebp
D 3
	int	tss_esi; 
	int	tss_edi; 
	int	tss_es;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_cs;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_ss;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_ds;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_fs;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_gs;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_ldt;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_ioopt;	/* options & io offset bitmap: currently zero */
E 3
I 3
D 4
	long	tss_esi; 
	long	tss_edi; 
	long	tss_es;		/* actually 16 bits: top 16 bits must be zero */
	long	tss_cs;		/* actually 16 bits: top 16 bits must be zero */
	long	tss_ss;		/* actually 16 bits: top 16 bits must be zero */
	long	tss_ds;		/* actually 16 bits: top 16 bits must be zero */
	long	tss_fs;		/* actually 16 bits: top 16 bits must be zero */
	long	tss_gs;		/* actually 16 bits: top 16 bits must be zero */
	long	tss_ldt;	/* actually 16 bits: top 16 bits must be zero */
	long	tss_ioopt;	/* options & io offset bitmap: currently zero */
E 4
I 4
	int	tss_esi; 
	int	tss_edi; 
	int	tss_es;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_cs;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_ss;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_ds;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_fs;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_gs;		/* actually 16 bits: top 16 bits must be zero */
	int	tss_ldt;	/* actually 16 bits: top 16 bits must be zero */
	int	tss_ioopt;	/* options & io offset bitmap: currently zero */
E 4
E 3
				/* XXX unimplemented .. i/o permission bitmap */
};
E 1
