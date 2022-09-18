/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	table.h,v $
 * Revision 2.6  89/03/09  22:08:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  17:56:52  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/07/15  16:03:57  mja
 * Made tl_loadavg structure independent of conditionals;  moved
 * UMODE_* bit definitions here from <sys/syscalls.h> since they
 * are now handled through the table() call.
 * 
 * 15-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added TBL_PROCINFO (MACH only).
 *
 * 15-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added TBL_LOADAVG.
 *	[ V5.1(F8) ]
 *
 * 28-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added TBL_MAXUPRC, TBL_AID, and TBL_MODES definitions.
 *	[ V5.1(F1) ]
 *
 *  7-Nov-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added TBL_ARGUMENTS, also for MACH only.
 *
 * 24-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added TBL_UAREA.  For now it only works under MACH virtual
 *	memory.
 *
 * 24-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added TBL_INCLUDE_VERSION and TBL_FSPARAM.
 *
 * 30-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added TBL_U_TTYD.
 *	[V1(1)]
 *
 * 30-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created (V3.06h).
 *
 */

#ifndef	_SYS_TABLE_H_
#define _SYS_TABLE_H_

#define TBL_TTYLOC		0	/* index by device number */
#define TBL_U_TTYD		1	/* index by process ID */
#define TBL_UAREA		2	/* index by process ID */
#define TBL_LOADAVG		3	/* (no index) */
#define TBL_INCLUDE_VERSION	4	/* (no index) */
#define TBL_FSPARAM		5	/* index by device number */
#define TBL_ARGUMENTS		6	/* index by process ID */
#define TBL_MAXUPRC		7	/* index by process ID */
#define TBL_AID			8	/* index by process ID */
#define TBL_MODES		9	/* index by process ID */
#define TBL_PROCINFO		10	/* index by proc table slot */


/*
 *  TBL_FSPARAM data layout
 */

struct tbl_fsparam
{
    long tf_used;		/* free fragments */
    long tf_iused;		/* free inodes */
    long tf_size;		/* total fragments */
    long tf_isize;		/* total inodes */
};


/*
 *  TBL_LOADAVG data layout
 */

struct tbl_loadavg
{
    union {
	    long   l[3];
	    double d[3];
    } tl_avenrun;
    int    tl_lscale;		/* 0 scale when floating point */
};


/*
 *  TBL_MODES bit definitions
 */

#define UMODE_P_GID	01	/* - 4.2 parent GID on inode create */
#define UMODE_NOFOLLOW	02	/* - don't follow symbolic links */
#define UMODE_NONICE	04	/* - don't auto-nice long job */



/*
 *	TBL_PROCINFO data layout
 */
#define PI_COMLEN	19	/* length of command string */
struct tbl_procinfo
{
    int		pi_uid;		/* user ID */
    int		pi_pid;		/* proc ID */
    int		pi_ppid;	/* parent proc ID */
    int		pi_pgrp;	/* proc group ID */
    int		pi_ttyd;	/* controlling terminal number */
    int		pi_status;	/* process status: */
#define PI_EMPTY	0	    /* no process */
#define PI_ACTIVE	1	    /* active process */
#define PI_EXITING	2	    /* exiting */
#define PI_ZOMBIE	3	    /* zombie */
    int		pi_flag;	/* other random flags */
    char	pi_comm[PI_COMLEN+1];
				/* short command name */
};

#endif	_SYS_TABLE_H_
