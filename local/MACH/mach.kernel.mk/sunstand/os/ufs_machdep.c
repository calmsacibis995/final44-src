/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ufs_machdep.c,v $
 * Revision 2.2  89/07/12  01:14:34  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static        char sccsid[] = "@(#)ufs_machdep.c 1.6 88/02/08 Copyr 1986 Sun Micro";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */



#include <machine/pte.h>

#include <sys/param.h>
#include "boot/systm.h"
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include "boot/seg.h"
#include <sys/vm.h>

/*
 * Machine dependent handling of the buffer cache.
 */

/*
 * Expand or contract the actual memory allocated to a buffer.
 * If no memory is available, release buffer and take error exit
 */
/*ARGSUSED*/
allocbuf(tp, size)
	register struct buf *tp;
	int size;
{
#ifdef lint
	tp = tp;
	size = size;
#endif lint
	return (1);
}

/*
 * Release space associated with a buffer.
 */
bfree(bp)
	struct buf *bp;
{

	bp->b_bcount = 0;
}
