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
 * $Log:	param.c,v $
 * Revision 2.11  89/08/28  22:32:28  af
 * 	Changed definition of HZ to 64 for Pmaxen.  This provides
 * 	no rounding errors at all for tick. Needed, along with companion
 * 	fix to adjtime(), to get NTP run smoothly.
 * 	[89/08/26            af]
 * 
 * Revision 2.10  89/07/11  13:29:52  jjc
 * 	[89/07/06  11:59:38  jjc]
 * 
 *	Defined HZ to be 100 for SPARC.
 * 	[89/03/30            jjc]
 * 
 * Revision 2.9  89/05/30  10:37:09  rvb
 * 	The clock on the Pmax is odd.  Made it run at 8ms, so that both
 * 	hz and tick do not suffer from rounding errors.
 * 	[89/04/16            af]
 * 
 * Revision 2.8  89/03/09  19:54:22  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  17:41:56  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  88/11/23  16:36:15  rpd
 * 	Removed tickadj sun conditional.  (From bww.)
 * 	[88/11/23  15:21:23  rpd]
 * 
 * Revision 2.5  88/10/11  10:08:50  rpd
 * 	Changed includes to the new style.
 * 	Added cfreelist, cfreecount declarations.
 * 	Made cfree initialized, so ld won't try
 * 	to pull in cfree() from libc on RTs.
 * 	[88/10/06  07:49:13  rpd]
 * 
 * Revision 2.4  88/08/22  21:28:54  mja
 * 	Raise `tickadj' on the SUN3 to the same ridiculously high
 * 	number as under SunOS.
 * 	[88/08/22  13:30:11  mja]
 * 	
 * 	Initialize `tickadj' based on HZ [bww].
 * 	[88/08/04  13:31:13  mja]
 * 
 *  3-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Remove unused variable declarations.
 *
 * 26-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Made QUOTA a #if-type option.
 *
 *  7-Apr-87  David Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX: 10 HZ clocks.
 *
 * 17-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Removed uses of cmap.h, text.h for MACH.
 *
 *  1-Nov-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	romp: defined HZ to be 64, because this responds better to the
 *	1024 hz hardware clock on the RT.  This avoids serious
 *	round-off error introduced with HZ = 100 which makes the clock
 *	run really fast.
 *
 * 27-Sep-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to include "confdep.h"
 *
 * 21-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Use 50 hz for Sun instead of 100 hz.
 *
 * 10-Jul-86  Supercomputer kernel (mach) at Carnegie-Mellon University
 *	Changed NINODE calculation to *2 from *4.
 *
 * 30-Jun-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Restored size of NINODE to original NINODE*4.
 *
 * 30-Jun-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Increased NINODE by 64 to cover inodes in use by the
 *	vm_object_cache.
 *
 * 26-Jun-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Restore calculation of NINODE now that the inode pager no longer
 *	depends on the inode table to keep track of its paging inodes.
 *
 * 20-Mar-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	If compiling a system with new VM, then increase NINODE by a
 *	factor of 4 (since the new VM code pages out to inodes).
 *
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)param.c	7.1 (Berkeley) 6/5/86
 */

#ifndef	lint
char copyright[] =
"@(#) Copyright (c) 1980, 1986 Regents of the University of California.\n\
 All rights reserved.\n";
#endif	not lint

#include <quota.h>
#include <confdep.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/socket.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/callout.h>
#include <sys/clist.h>
#include <sys/mbuf.h>
#include <sys/quota.h>
#include <sys/kernel.h>
/*
 * System parameter formulae.
 *
 * This file is copied into each directory where we compile
 * the kernel; it should be modified there to suit local taste
 * if necessary.
 *
 * Compiled with -DHZ=xx -DTIMEZONE=x -DDST=x -DMAXUSERS=xx
 */

#ifdef	sparc
#define HZ 100
#endif	sparc
#ifdef	multimax
#define HZ 10
#endif	multimax
#ifdef	sun3
#define HZ 50
#endif	sun3
#ifdef	ibmrt
#define HZ 64
#endif	ibmrt
#ifdef	PMAX
#define	HZ 64
#endif	PMAX

#if !defined(HZ)
#define HZ 100
#endif

int	hz = HZ;
int	tick = 1000000 / HZ;
#if	HZ > 100
int	tickadj = 1;			/* can adjust HZ usecs per second */
#else
int	tickadj = 100 / HZ;		/* can adjust 100 usecs per second */
#endif
struct	timezone tz = { TIMEZONE, DST };
#define NPROC (20 + 8 * MAXUSERS)
int	nproc = NPROC;
#define NINODE (((NPROC + 16 + MAXUSERS) + 32)*2)
int	ninode = NINODE;
int	nchsize = NINODE * 11 / 10;
int	nfile = 16 * (NPROC + 16 + MAXUSERS) / 10 + 32;
int	ncallout = 16 + NPROC;
int	nclist = 60 + 12 * MAXUSERS;
int     nmbclusters = NMBCLUSTERS;
#if	QUOTA
int	nquota = (MAXUSERS * 9) / 7 + 3;
int	ndquot = NINODE + (MAXUSERS * NMOUNT) / 4;
#endif	QUOTA

/*
 * These are initialized at bootstrap time
 * to values dependent on memory size
 */

int	nbuf;


/*
 * These have to be allocated somewhere; allocating
 * them here forces loader errors if this file is omitted
 * (if they've been externed everywhere else; hah!).
 */
struct	proc *proc, *procNPROC;
struct	inode *inode, *inodeNINODE;
struct	file *file, *fileNFILE;
struct 	callout *callout;
struct	cblock *cfree = 0;
struct	cblock *cfreelist = 0;
int	cfreecount = 0;
struct	buf *buf;
char	*buffers;
struct	namecache *namecache;
#if	QUOTA
struct	quota *quota, *quotaNQUOTA;
struct	dquot *dquot, *dquotNDQUOT;
#endif	QUOTA
