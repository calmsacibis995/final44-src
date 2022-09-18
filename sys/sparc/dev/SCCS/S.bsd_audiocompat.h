h16609
s 00005/00000/00020
d D 7.2 92/07/21 16:37:53 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00020/00000/00000
d D 7.1 92/07/13 00:41:27 torek 1 0
c date and time created 92/07/13 00:41:27 by torek
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: bsd_audiocompat.h,v 1.1 92/07/02 19:26:52 leres Exp $ (LBL)
 */

/*
 * Some hacks for compatibility across SunOS and 4.4BSD.
 */
#define tsleep(chan, pri, s, t) sleep(chan, pri)
#define __P(args) ()
E 1
