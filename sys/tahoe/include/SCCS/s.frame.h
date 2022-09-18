h62120
s 00009/00001/00012
d D 7.2 91/05/08 14:23:26 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00010
d D 7.1 88/05/21 18:35:12 karels 2 1
c bring up to revision 7 for tahoe release
e
s 00011/00000/00000
d D 1.1 86/01/05 18:46:20 sam 1 0
c date and time created 86/01/05 18:46:20 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 3
/*
E 3
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
E 3
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * Definition of the tahoe call frame.
 */
struct frame {
	int	fr_savpc;		/* saved program counter */
	u_int	fr_mask:16,		/* register save mask */
		fr_removed:16;		/* 4*number of arguments + 4 */
	int	fr_savfp;		/* saved frame pointer */
};
E 1
