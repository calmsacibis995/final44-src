h53069
s 00002/00002/00025
d D 8.1 93/06/11 15:12:23 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00025
d D 7.3 93/04/20 18:54:34 torek 3 2
c spelling
e
s 00005/00000/00022
d D 7.2 92/07/21 16:41:34 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00022/00000/00000
d D 7.1 92/07/13 00:43:04 torek 1 0
c date and time created 92/07/13 00:43:04 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: proc.h,v 1.5 92/06/17 06:10:23 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: proc.h,v 1.6 92/11/26 02:04:41 torek Exp $ (LBL)
E 3
 */

/*
 * Machine-dependent part of the proc structure for SPARC.
 */
struct mdproc {
	struct	trapframe *md_tf;	/* trap/syscall registers */
	struct	fpstate *md_fpstate;	/* fpu state, if any; always resident */
};
E 1
