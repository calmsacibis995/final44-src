h01209
s 00002/00002/00087
d D 8.2 94/01/21 19:49:17 bostic 2 1
c copyright typo
e
s 00089/00000/00000
d D 8.1 93/10/30 22:02:04 torek 1 0
c date and time created 93/10/30 22:02:04 by torek
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
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: bt_subr.c,v 1.1 93/10/12 15:28:39 torek Exp $
 */

#include <sys/param.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/fbio.h>

#include <sparc/sbus/btreg.h>
#include <sparc/sbus/btvar.h>

/*
 * Common code for dealing with Brooktree video DACs.
 * (Contains some software-only code as well, since the colormap
 * ioctls are shared between the cgthree and cgsix drivers.)
 */

/*
 * Implement an FBIOGETCMAP-like ioctl.
 */
int
bt_getcmap(p, cm, cmsize)
	register struct fbcmap *p;
	union bt_cmap *cm;
	int cmsize;
{
	register u_int i, start, count;
	register u_char *cp;

	start = p->index;
	count = p->count;
	if (start >= cmsize || start + count > cmsize)
		return (EINVAL);
	if (!useracc(p->red, count, B_WRITE) ||
	    !useracc(p->green, count, B_WRITE) ||
	    !useracc(p->blue, count, B_WRITE))
		return (EFAULT);
	for (cp = &cm->cm_map[start][0], i = 0; i < count; cp += 3, i++) {
		p->red[i] = cp[0];
		p->green[i] = cp[1];
		p->blue[i] = cp[2];
	}
	return (0);
}

/*
 * Implement the software portion of an FBIOPUTCMAP-like ioctl.
 */
int
bt_putcmap(p, cm, cmsize)
	register struct fbcmap *p;
	union bt_cmap *cm;
	int cmsize;
{
	register u_int i, start, count;
	register u_char *cp;

	start = p->index;
	count = p->count;
	if (start >= cmsize || start + count > cmsize)
		return (EINVAL);
	if (!useracc(p->red, count, B_READ) ||
	    !useracc(p->green, count, B_READ) ||
	    !useracc(p->blue, count, B_READ))
		return (EFAULT);
	for (cp = &cm->cm_map[start][0], i = 0; i < count; cp += 3, i++) {
		cp[0] = p->red[i];
		cp[1] = p->green[i];
		cp[2] = p->blue[i];
	}
	return (0);
}
E 1
