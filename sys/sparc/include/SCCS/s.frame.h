h32876
s 00002/00002/00039
d D 8.1 93/06/11 15:12:00 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00039
d D 7.3 93/04/20 18:48:52 torek 3 2
c spelling
e
s 00005/00000/00036
d D 7.2 92/07/21 16:41:29 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00036/00000/00000
d D 7.1 92/07/13 00:43:01 torek 1 0
c date and time created 92/07/13 00:43:01 by torek
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
 * from: $Header: frame.h,v 1.4 92/06/17 06:10:17 torek Exp $
E 3
I 3
 * from: $Header: frame.h,v 1.5 92/11/26 02:04:35 torek Exp $
E 3
 */

/*
 * Sparc stack frame format.
 *
 * Note that the contents of each stack frame may be held only in
 * machine register windows.  In order to get an accurate picture
 * of the frame, you must first force the kernel to write any such
 * windows to the stack.
 */
struct frame {
	int	fr_local[8];	/* space to save locals (%l0..%l7) */
	int	fr_arg[6];	/* space to save arguments (%i0..%i5) */
	struct	frame *fr_fp;	/* space to save frame pointer (%i6) */
	int	fr_pc;		/* space to save return pc (%i7) */
	/*
	 * SunOS reserves another 8 words here; this is pointless
	 * but we do it for compatibility.
	 */
	int	fr_xxx;		/* `structure return pointer' (unused) */
	int	fr_argd[6];	/* `arg dump area' (lunacy) */
	int	fr_argx[1];	/* arg extension (args 7..n; variable size) */
};
E 1
