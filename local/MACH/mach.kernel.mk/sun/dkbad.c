/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dkbad.c,v $
 * Revision 2.3  89/03/09  21:30:09  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:28:12  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-89  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Fixed #include's as part of cleanup.
 *
 */
/*	dkbad.c	1.1	86/02/03	*/

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
		if (bblk < 0)
			break;
	}
	return (-1);
}
#endif
