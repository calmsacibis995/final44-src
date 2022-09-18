/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sc_conf.c,v $
 * Revision 2.5  90/07/03  16:48:49  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:15:05  mrt]
 * 
 * Revision 2.4  89/03/09  21:44:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:53:53  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.2  88/12/07  17:19:29  mikeg
 * 	Entered new version of this file from SunOS 3.5 into
 * 	the RCS kernel souurce tree.  Also commented out
 * 	the include for "se.h".
 * 	[88/12/01  12:02:46  mikeg]
 * 
 * 14-Aug-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Upgraded to SunOS 3.5 with some help from Jon Hale at Mt. Xinu.
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)sc_conf.c 1.1 87/12/21 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <si.h>
#include <sc.h>
/*#include <se.h>	We are not using this driver presently. */
#include <sd.h>
#include <st.h>
#include <sf.h>

#if	((NSC > 0) || (NSI > 0) || (NSE > 0))

#include <sys/types.h>
#include <sys/buf.h>

#include <sun/dkio.h>
#include <sundev/screg.h>
#include <sundev/sireg.h>
#include <sundev/scsi.h>

/* generic scsi debug flag */
short scsi_debug = 0;

/* scsi disconnect/reconnect global enable flag */
short scsi_disre_enable = 1;

/*
 * If host adaptors exist, declare structures for them.
 */
#if	NSI > 0
#ifdef	MACH
/*
 *	In Mach, this might be dynamically allocated so just make
 *	an external declaration instead of statically allocating
 *	space.
 */
struct	scsi_ctlr sictlrs[];		/* per controller structs */
#else	MACH
struct	scsi_ctlr sictlrs[NSI];		/* per controller structs */
#endif	MACH
struct	mb_ctlr *siinfo[NSI];
#endif	NSI

#if	NSC > 0
struct	scsi_ctlr scctlrs[NSC];
struct	mb_ctlr *scinfo[NSC];
#endif	NSC

/*
 * If disks exist, declare unit structures for them.
 */
#if	NSD > 0
struct	scsi_unit sdunits[NSD];
struct scsi_disk sdisk[NSD];
int nsdisk = NSD;
#endif	NSD

/*
 * Same thing for tapes.
 */
#if	NST > 0
struct	scsi_unit stunits[NST];
struct scsi_tape stape[NST];
int nstape = NST;
#endif	NST

/*
 * Same thing for floppy disks.
 */
#if	NSF > 0
struct	scsi_unit sfunits[NSF];
struct scsi_floppy sfloppy[NSF];
int nsfloppy = NSF;
#endif	NSF

struct	mb_device *sdinfo[NSD + NST + NSF];


/*
 * Device specific subroutines.
 * Indexed by "flag" from the configuration file,
 * which is in mc_flag.
 * Disk is 0, tape is 1.
 */
#if	NSD > 0
int	sdattach(), sdstart(), sdmkcdb(), sdintr(), sdunitptr();
#endif	NSD > 0

#if	NST > 0
int	stattach(), ststart(), stmkcdb(), stintr(), stunitptr();
#endif	NST > 0

#if	NSF > 0
int	sfattach(), sfstart(), sfmkcdb(), sfintr(), sfunitptr();
#endif	NSF > 0

struct	scsi_unit_subr scsi_unit_subr[] = {
#if	NSD > 0
	{ sdattach, sdstart, sdmkcdb, sdintr, sdunitptr, "sd", },
#else
	{ (int (*)())0, (int (*)())0, (int (*)())0, (int (*)())0, (int (*)())0,
	(char *)0},
#endif	NSD > 0

#if	NST > 0
	{ stattach, ststart, stmkcdb, stintr, stunitptr, "st", },
#else
	{ (int (*)())0, (int (*)())0, (int (*)())0, (int (*)())0, (int (*)())0,
	(char *)0},
#endif	NST > 0

#if	NSF > 0
	{ sfattach, sfstart, sfmkcdb, sfintr, sfunitptr, "sf", },
#else
	{ (int (*)())0, (int (*)())0, (int (*)())0, (int (*)())0, (int (*)())0,
	(char *)0},
#endif	NSF > 0
};

/*
 * Number of SCSI device driver types.
 */
int scsi_ntype = sizeof scsi_unit_subr / sizeof (struct scsi_unit_subr);

#endif	((NSC > 0) || (NSI > 0) || (NSE > 0))
