/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1988 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	mscpvar.h,v $
 * Revision 2.4  93/05/17  16:20:15  rvb
 * 	Type casts, etc to quiet gcc 2.3.3 warnings
 * 	[93/05/17            rvb]
 * 
 * Revision 2.3  91/05/14  17:45:12  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:20:19  dbg
 * 	Use new copyright.
 * 	[91/04/26            dbg]
 * 
 * Revision 2.1  89/08/03  16:29:07  rwd
 * Created.
 * 
 * 29-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH_KERNEL: use thread_wakeup instead of wakeup.
 *
 */

#ifndef	_VAX_MSCPVAR_H_
#define	_VAX_MSCPVAR_H_

/*
 * MSCP generic driver configuration
 */

/*
 * Enabling MSCP_PARANOIA makes the response code perform various checks
 * on the hardware.  (Right now it verifies only the buffer pointer in
 * mscp_cmdref.)
 *
 * Enabling AVOID_EMULEX_BUG selects an alternative method of identifying
 * transfers in progress, which gets around a rather peculiar bug in the
 * SC41/MS.  Enabling MSCP_PARANOIA instead should work, but will cause
 * `extra' Unibus resets.
 *
 * Either of these flags can simply be included as an `options' line in
 * your configuration file.
 */

/* #define MSCP_PARANOIA */
/* #define AVOID_EMULEX_BUG */

/*
 * Per driver information.
 *
 * md_ndpc sets the maximum unit number allowed in response packets.
 * md_nunits is the number of drives attached to all controllers.
 * md_unitshift is the divisor for converting a minor device number
 * to a unit index for the device queues in md_utab.
 *
 * The routines are called from the generic response dispatcher.
 * The first three (dgram, ctlrdone, and unconf) get passed a pointer
 * to the uba_ctlr and to the packet; the rest get a pointer to the
 * uba_device and to the packet (`um, mp' and `ui, mp' respectively).
 * The routines unconf, online, gotstatus, and ioerr are functions
 * and should return one of the values given below.  In addition,
 * the ioerr and bb routines get a third argument, `bp': a pointer
 * to the buffer describing the transfer in error.
 */
struct mscp_driver {
	int	md_ndpc;		/* number of drives per ctlr */
	int	md_nunits;		/* total number drives (all ctlrs) */
	int	md_unitshift;		/* device number to unit: >> count */
	struct	buf *md_utab;		/* pointer to device queues */
	int	(*md_dgram)();		/* error datagram */
	int	(*md_ctlrdone)();	/* controller operation complete */
	int	(*md_unconf)();		/* response from unconfigured drive */
	int	(*md_online)();		/* drive on line */
	int	(*md_gotstatus)();	/* got unit status */
	int	(*md_replace)();	/* replace done */
	int	(*md_ioerr)();		/* read or write failed */
	int	(*md_bb)();		/* B_BAD io done */
};

/*
 * Return values from functions.
 * MSCP_RESTARTED is peculiar to I/O errors.
 */
#define	MSCP_DONE	0		/* all ok */
#define	MSCP_FAILED	1		/* no go */
#define	MSCP_RESTARTED	2		/* transfer restarted */

/*
 * Ring information, per ring (one each for commands and responses).
 */
struct mscp_ri {
	int	mri_size;		/* ring size */
	int	mri_next;		/* next (expected|free) */
	long	*mri_desc;		/* base address of descriptors */
	struct	mscp *mri_ring;		/* base address of packets */
};

/*
 * Per device information.
 *
 * mi_ip is a pointer to the inverting pointers (things that get `ui's
 * given unit numbers) FOR THIS CONTROLLER (NOT the whole set!).
 *
 * mi_wtab holds a queue of those transfers that were started but have
 * not yet finished.  Other Unibus drivers do not need this as they hand
 * out requests one at a time.  MSCP devices, however, take a slew of
 * requests and pick their own order to execute them.  This means that
 * we have to have a place to move transfers that were given to the
 * controller, so we can tell those apart from those that have not yet
 * been handed out; mi_wtab is that place.
 */
struct mscp_info {
	struct	mscp_driver *mi_md;	/* pointer to driver info */
	struct	uba_ctlr *mi_um;	/* pointer to ctlr */
	struct	uba_device **mi_ip;	/* pointer to inverting pointers */
	struct	mscp_ri mi_cmd;		/* MSCP command ring info */
	struct	mscp_ri mi_rsp;		/* MSCP response ring info */
	short	mi_credits;		/* transfer credits */
	char	mi_wantcmd;		/* waiting for command packet */
	char	mi_wantcredits;		/* waiting for transfer credits */
	struct	buf mi_wtab;		/* transfer wait queue */
#ifdef AVOID_EMULEX_BUG
#define	AEB_MAX_BP	32		/* max pend xfers (power of 2) XXX */
	struct	buf *mi_bp[AEB_MAX_BP];	/* xfer no. to buffer */
	u_int	mi_nextbp;		/* generates unique xfer no's */
	int	mi_ok;			/* for error rate statistics */
#endif AVOID_EMULEX_BUG
};

/*
 * We have run out of credits when mi_credits is <= MSCP_MINCREDITS.
 * It is still possible to issue one command in this case, but it must
 * not be a data transfer.  E.g., `get command status' or `abort command'
 * is legal, while `read' is not.
 */
#define	MSCP_MINCREDITS	1

/*
 * Flags for mscp_getcp().
 */
#define	MSCP_WAIT	1
#define	MSCP_DONTWAIT	0

struct	mscp *mscp_getcp();	/* get a command packet */

/*
 * Unit flags
 */
#define	UNIT_ONLINE	0x01	/* drive is on line */
#define	UNIT_HAVESTATUS	0x02	/* got unit status */
#define	UNIT_REQUEUE	0x04	/* requeue after response */

/*
 * Handle a command ring transition: wake up sleepers for command packets.
 * This is too simple to bother with a function call.
 */
#ifdef	MACH_KERNEL
#define	MSCP_DOCMD(mi) { \
	if ((mi)->mi_wantcmd) { \
		(mi)->mi_wantcmd = 0; \
		thread_wakeup((event_t) &(mi)->mi_wantcmd); \
	} \
}
#else	MACH_KERNEL
#define	MSCP_DOCMD(mi) { \
	if ((mi)->mi_wantcmd) { \
		(mi)->mi_wantcmd = 0; \
		wakeup((caddr_t) &(mi)->mi_wantcmd); \
	} \
}
#endif	MACH_KERNEL

/*
 * The following macro appends a buffer to a drive queue or a drive to
 * a controller queue, given the name of the forward link.  Use as
 * `APPEND(dp, &um->um_tab, b_forw)' or `APPEND(bp, dp, av_forw)',
 * where `bp' is a transfer request, `dp' is a drive queue, and `um_tab'
 * is a controller queue.  (That is, the forward link for controller
 * queues is `b_forw'; for drive queues, it is `av_forw'.)
 */
#define	APPEND(bp, queue, link) { \
	(bp)->link = NULL; \
	if ((queue)->b_actf == NULL) \
		(queue)->b_actf = (bp); \
	else \
		(queue)->b_actl->link = (bp); \
	(queue)->b_actl = (bp); \
}

#endif	/* _VAX_MSCPVAR_H_ */
