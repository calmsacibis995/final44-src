/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dkbad.c,v $
 * Revision 2.3  89/03/09  22:14:32  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:18:16  gm0w
 * 	Changes for cleanup.
 * 
 *  7-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed include of cs_generic.h so that this file can be
 *	compiled for standalone use.
 *
 * 23-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Forced include of "param.h" to find "../h" version.
 *
 */ 
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)dkbad.c	7.1 (Berkeley) 6/5/86
 */

#ifndef	NOBADSECT
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/dkbad.h>

/*
 * Search the bad sector table looking for
 * the specified sector.  Return index if found.
 * Return -1 if not found.
 */

isbad(bt, cyl, trk, sec)
	register struct dkbad *bt;
{
	register int i;
	register long blk, bblk;

	blk = ((long)cyl << 16) + (trk << 8) + sec;
	for (i = 0; i < 126; i++) {
		bblk = ((long)bt->bt_bad[i].bt_cyl << 16) + bt->bt_bad[i].bt_trksec;
		if (blk == bblk)
			return (i);
		if (blk < bblk || bblk < 0)
			break;
	}
	return (-1);
}
#endif
