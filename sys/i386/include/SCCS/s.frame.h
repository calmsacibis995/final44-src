h58340
s 00002/00002/00088
d D 8.1 93/06/11 15:47:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00089
d D 5.2 91/01/18 14:32:08 william 3 2
c fixed just which copyright notice is included.
e
s 00086/00007/00004
d D 5.1 90/04/24 18:52:11 william 2 1
c 1st Berkeley Release
e
s 00011/00000/00000
d D 1.1 90/03/12 15:47:53 bill 1 0
c date and time created 90/03/12 15:47:53 by bill
e
u
U
t
T
I 1
D 2
/*	frame.h	1.1	86/01/05	*/
E 2
I 2
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 3
 * %sccs.include.noredist.c%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
D 2
 * Definition of the tahoe call frame.
E 2
I 2
 * System stack frames.
E 2
 */
D 2
struct frame {
	int	fr_savpc;		/* saved program counter */
	u_int	fr_mask:16,		/* register save mask */
		fr_removed:16;		/* 4*number of arguments + 4 */
	int	fr_savfp;		/* saved frame pointer */
E 2
I 2

/*
 * Exception/Trap Stack Frame
 */

struct trapframe {
	int	tf_es;
	int	tf_ds;
	int	tf_edi;
	int	tf_esi;
	int	tf_ebp;
	int	tf_isp;
	int	tf_ebx;
	int	tf_edx;
	int	tf_ecx;
	int	tf_eax;
	int	tf_trapno;
	/* below portion defined in 386 hardware */
	int	tf_err;
	int	tf_eip;
	int	tf_cs;
	int	tf_eflags;
	/* below only when transitting rings (e.g. user to kernel) */
	int	tf_esp;
	int	tf_ss;
};

/* Interrupt stack frame */

struct intrframe {
	int	if_vec;
	int	if_ppl;
	int	if_es;
	int	if_ds;
	int	if_edi;
	int	if_esi;
	int	if_ebp;
	int	:32;
	int	if_ebx;
	int	if_edx;
	int	if_ecx;
	int	if_eax;
	int	:32;		/* for compat with trap frame - trapno */
	int	:32;		/* for compat with trap frame - err */
	/* below portion defined in 386 hardware */
	int	if_eip;
	int	if_cs;
	int	if_eflags;
	/* below only when transitting rings (e.g. user to kernel) */
	int	if_esp;
	int	if_ss;
};

/*
 * Call Gate/System Call Stack Frame
 */

struct syscframe {
	int	sf_edi;
	int	sf_esi;
	int	sf_ebp;
	int	:32;		/* redundant save of isp */
	int	sf_ebx;
	int	sf_edx;
	int	sf_ecx;
	int	sf_eax;
	int	sf_eflags;
	/* below portion defined in 386 hardware */
/*	int	sf_args[N]; 	/* if call gate copy args enabled!*/
	int	sf_eip;
	int	sf_cs;
	/* below only when transitting rings (e.g. user to kernel) */
	int	sf_esp;
	int	sf_ss;
E 2
};
E 1
