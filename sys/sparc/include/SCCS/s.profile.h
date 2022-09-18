h14801
s 00002/00002/00037
d D 8.1 93/06/11 15:12:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00037
d D 7.3 93/04/20 18:54:35 torek 3 2
c spelling
e
s 00005/00000/00034
d D 7.2 92/07/21 16:41:35 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00034/00000/00000
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
 * from: $Header: profile.h,v 1.7 92/07/09 01:34:21 mccanne Exp $
E 3
I 3
 * from: $Header: profile.h,v 1.8 92/11/26 02:04:41 torek Exp $
E 3
 */

#define MCOUNT \
        asm(".global mcount");\
        asm("mcount:");\
        asm("add %i7, 8, %o0");\
        asm("sethi %hi(__mcount), %o2");\
        asm("jmpl %o2 + %lo(__mcount), %g0");\
        asm("add %o7, 8, %o1");

#define	_MCOUNT_DECL	static void _mcount

#ifdef KERNEL
/*
 * Block interrupts during mcount so that those interrupts can also be
 * counted (as soon as we get done with the current counting).  On the
 * SPARC, we just splhigh/splx as those do not recursively invoke mcount.
 */
#define	MCOUNT_ENTER	s = splhigh()
#define	MCOUNT_EXIT	splx(s)
#endif /* KERNEL */
E 1
