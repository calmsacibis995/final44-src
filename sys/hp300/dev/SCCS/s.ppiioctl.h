h30467
s 00002/00002/00034
d D 8.1 93/06/10 21:33:53 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00036
d D 7.3 92/10/11 09:24:06 bostic 3 2
c make kernel includes standard
e
s 00000/00004/00036
d D 7.2 90/12/16 16:36:53 bostic 2 1
c kernel reorg
e
s 00040/00000/00000
d D 7.1 90/11/03 13:23:32 mckusick 1 0
c from Utah
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _IOCTL_
D 2
#ifdef KERNEL
#include "ioctl.h"
#else
E 2
#include <sys/ioctl.h>
D 2
#endif
E 2
#endif

struct ppiparam {
	int	burst;	/* chars to send/recv in one call */
	int	timo;	/* timeout: -1 blocking, 0 non-blocking, >0 msec */
	int	delay;	/* delay between polls (msec) */
};

#define PPI_BLOCK	-1
#define PPI_NOBLOCK	0

/* default values */
#define	PPI_BURST	1024
#define PPI_TIMO	PPI_BLOCK
#define PPI_DELAY	10

/* limits */
#define	PPI_BURST_MIN	1
#define	PPI_BURST_MAX	1024
#define PPI_DELAY_MIN	0
#define PPI_DELAY_MAX	30000

#define PPIIOCSPARAM	_IOW('P', 0x1, struct ppiparam)
#define PPIIOCGPARAM	_IOR('P', 0x2, struct ppiparam)
#define PPIIOCSSEC	_IOW('P', 0x3, int)
E 1
