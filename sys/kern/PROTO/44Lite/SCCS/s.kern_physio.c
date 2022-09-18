h35587
s 00024/00042/00043
d D 8.1 94/01/21 18:46:05 mckusick 3 2
c update for 4.4BSD-Lite
e
s 00002/00005/00083
d D 1.2 91/06/28 15:47:07 karels 2 1
c not so verbose about the "trade secrets"
e
s 00088/00000/00000
d D 1.1 91/05/11 15:31:09 mckusick 1 0
c date and time created 91/05/11 15:31:09 by mckusick
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
 * All rights reserved.
E 3
I 3
/*-
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 3
 *
 * %sccs.include.redist.c%
 *
D 3
 *	from: @(#)kern_physio.c	7.20 (Berkeley) 5/11/91
E 3
I 3
 *	from: @(#)kern_physio.c	8.1 (Berkeley) 6/10/93
E 3
 */

D 3
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "conf.h"
#include "proc.h"
#include "seg.h"
#include "trace.h"
#include "map.h"
#include "vnode.h"
#include "specdev.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
E 3

D 3
#ifdef HPUXCOMPAT
#include "user.h"
#endif

D 2
static	struct buf *getswbuf();
static	freeswbuf();

E 2
/*
D 2
 * This routine does device I/O for a user process.
E 2
I 2
 * This routine does raw device I/O for a user process.
E 2
 *
D 2
 * If the user has the proper access privilidges, the process is
E 2
I 2
 * If the user has the proper access privileges, the process is
E 2
 * marked 'delayed unlock' and the pages involved in the I/O are
 * faulted and locked. After the completion of the I/O, the pages
 * are unlocked.
 */
physio(strat, bp, dev, rw, mincnt, uio)
	int (*strat)(); 
	register struct buf *bp;
	dev_t dev;
	int rw;
	u_int (*mincnt)();
	struct uio *uio;
E 3
I 3
physio(a1, a2, a3, a4, a5, a6)
	int (*a1)(); 
	struct buf *a2;
	dev_t a3;
	int a4;
	u_int (*a5)();
	struct uio *a6;
E 3
{

	/*
	 * Body deleted.
	 */
	return (EIO);
}

D 3
/*
 * Calculate the maximum size of I/O request that can be requested
 * in a single operation. This limit is necessary to prevent a single
 * process from being able to lock more than a fixed amount of memory
 * in the kernel.
 */
E 3
u_int
D 3
minphys(bp)
	struct buf *bp;
E 3
I 3
minphys(a1)
	struct buf *a1;
E 3
{

	/*
	 * Body deleted.
	 */
D 3
	return;
E 3
I 3
	return (0);
E 3
}

/*
 * Do a read on a device for a user process.
 */
rawread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	return (physio(cdevsw[major(dev)].d_strategy, (struct buf *)NULL,
	    dev, B_READ, minphys, uio));
}

/*
 * Do a write on a device for a user process.
 */
rawwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	return (physio(cdevsw[major(dev)].d_strategy, (struct buf *)NULL,
	    dev, B_WRITE, minphys, uio));
}
E 1
