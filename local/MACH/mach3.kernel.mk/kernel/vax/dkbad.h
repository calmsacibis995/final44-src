/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dkbad.h,v $
 * Revision 2.2  90/08/27  22:13:56  dbg
 * 	Moved from sys to vax directory.
 * 	[90/08/13            dbg]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)dkbad.h	7.1 (Berkeley) 6/4/86
 */

/*
 * Definitions needed to perform bad sector
 * revectoring ala DEC STD 144.
 *
 * The bad sector information is located in the
 * first 5 even numbered sectors of the last
 * track of the disk pack.  There are five
 * identical copies of the information, described
 * by the dkbad structure.
 *
 * Replacement sectors are allocated starting with
 * the first sector before the bad sector information
 * and working backwards towards the beginning of
 * the disk.  A maximum of 126 bad sectors are supported.
 * The position of the bad sector in the bad sector table
 * determines which replacement sector it corresponds to.
 *
 * The bad sector information and replacement sectors
 * are conventionally only accessible through the
 * 'c' file system partition of the disk.  If that
 * partition is used for a file system, the user is
 * responsible for making sure that it does not overlap
 * the bad sector information or any replacement sector.s
 */

struct dkbad {
	long	bt_csn;			/* cartridge serial number */
	u_short	bt_mbz;			/* unused; should be 0 */
	u_short	bt_flag;		/* -1 => alignment cartridge */
	struct bt_bad {
		u_short	bt_cyl;		/* cylinder number of bad sector */
		u_short	bt_trksec;	/* track and sector number */
	} bt_bad[126];
};

#define	ECC	0
#define	SSE	1
#define	BSE	2
#define	CONT	3
