/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	xyvar.h,v $
 * Revision 2.4  90/07/03  16:49:50  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:16:09  mrt]
 * 
 * Revision 2.3  89/03/09  21:50:13  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:59:53  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)xyvar.h 1.1 86/09/25 SMI	*/

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */
#ifndef	XYVAR_H_
#define XYVAR_H_

/*
 * Structure definitions for Xylogics 450 disk driver.
 */
#include <sundev/xycreg.h>
#include <sundev/xyreg.h>
#include <sundev/xycom.h>

/*
 * Structure needed to execute a command.  Contains controller & iopb ptrs
 * and some error recovery information.  The link is used to identify
 * chained iopbs.
 */
struct xycmdblock {
	struct	xyctlr *c;		/* ptr to controller */
	struct	xyiopb *iopb;		/* ptr to IOPB */
	struct	xycmdblock *next;	/* next iopb in ctlr chain */
	u_char	retries;		/* retry count */
	u_char	restores;		/* restore count */
	u_char	resets;			/* reset count */
	u_char	slave;			/* current drive no. */
	u_short	cmd;			/* current command */
	u_short	flags;			/* state information */
	caddr_t	baddr;			/* physical buffer address */
	daddr_t	blkno;			/* current block */
	daddr_t altblkno;		/* alternate block (forwarding) */
	u_short	nsect;			/* sector count active */
	short	device;			/* current minor device */
};

/*
 * Data per unit
 */
struct xyunit {
	char			un_attached;	/* unit has been attached */
	char			un_present;	/* unit is present */
	char			un_mode;	/* operating mode */
	u_char			un_drtype;	/* drive type */
	struct	buf		*un_rtab;	/* for physio */
	int			un_ltick;	/* last time active */
	struct	mb_device	*un_md;		/* generic unit */
	struct	mb_ctlr		*un_mc;		/* generic controller */
	struct	dkbad		*un_bad;	/* bad sector info */
	int			un_errsect;	/* sector in error */
	struct	xyerror		*un_errptr;	/* ptr to last error */
	u_short			un_errcmd;	/* command in error */
	struct	xycmdblock	un_cmd;		/* current command info */
	struct	disklabel	un_label;	/* disk label */
	u_long			un_openpart;	/* partitions open */
	u_long			un_copenpart;	/* raw partitions open */
	u_long			un_bopenpart;	/* block partitions open */
	u_char			un_state;	/* software state */
	u_char			un_wlabel;	/* write-enable label flag */
};

/*
 * Data per controller
 */
struct xyctlr {
	struct	xyunit *c_units[XYUNPERC];	/* units on controller */
	struct	xydevice *c_io;			/* ptr to I/O space data */
	struct	xycmdblock *c_chain;		/* ptr to iopb chain */
	char	c_present;			/* controller is present */
	char	c_addrlen;			/* 20/24 bit addressing */
	int	c_wantint;			/* controller is busy */
	struct	xycmdblock c_cmd;		/* used for special commands */
};

#endif	XYVAR_H_

