h44407
s 00002/00002/00009
d D 8.1 93/06/06 22:22:37 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00000/00000
d D 5.1 93/05/21 15:10:05 torek 1 0
c date and time created 93/05/21 15:10:05 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

void	getdev __P((u_long alldevs, int (*match)(struct device *),
		    void (*add)(u_long, struct device *)));
E 1
