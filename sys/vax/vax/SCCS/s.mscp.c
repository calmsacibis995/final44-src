h58505
s 00008/00008/00887
d D 7.5 90/12/16 17:03:06 bostic 8 7
c kernel reorg
e
s 00001/00011/00894
d D 7.4 90/06/28 22:32:58 bostic 7 6
c new copyright notice
e
s 00017/00003/00888
d D 7.3 88/07/09 13:40:25 bostic 6 5
c install approved copyright notice
e
s 00002/00001/00889
d D 7.2 88/05/31 08:38:30 karels 5 4
c allow null md_lab pointer
e
s 00000/00000/00890
d D 7.1 88/05/27 16:14:24 karels 4 3
c bring up to revision 7 for tahoe release
e
s 00011/00008/00879
d D 1.3 88/05/27 16:09:35 karels 3 2
c new diskerr routine
e
s 00000/00024/00887
d D 1.2 88/05/07 14:20:02 karels 2 1
c vax 8200 support from torek: generalize cpu support, ops, clock ops
e
s 00911/00000/00000
d D 1.1 87/10/23 11:20:03 bostic 1 0
c date and time created 87/10/23 11:20:03 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
 *
 *	%W% (Berkeley) %G%
 */

/*
 * MSCP generic driver routines
 */

D 8
#include "param.h"
#include "buf.h"
#include "errno.h"
#include "dkstat.h"
I 3
#include "ioctl.h"
#include "disklabel.h"
E 3
#include "syslog.h"
E 8
I 8
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/errno.h"
#include "sys/dkstat.h"
#include "sys/ioctl.h"
#include "sys/disklabel.h"
#include "sys/syslog.h"
E 8

D 8
#include "../vaxuba/ubavar.h"
E 8
I 8
#include "../uba/ubavar.h"
E 8

#include "mscp.h"
#include "mscpvar.h"

#define	PCMD	PSWP		/* priority for command packet waits */

/*
 * During transfers, mapping info is saved in the buffer's b_resid.
 */
#define	b_info b_resid

/*
 * Get a command packet.  Second argument is true iff we are
 * to wait if necessary.  Return NULL if none are available and
 * we cannot wait.
 */
struct mscp *
mscp_getcp(mi, canwait)
	register struct mscp_info *mi;
	int canwait;
{
#define	mri	(&mi->mi_cmd)
	register struct mscp *mp;
	register int i;
	int s = spl5();

again:
	/*
	 * Ensure that we have some command credits, and
	 * that the next command packet is free.
	 */
	if (mi->mi_credits <= MSCP_MINCREDITS) {
		if (!canwait) {
			splx(s);
			return (NULL);
		}
		mi->mi_wantcredits = 1;
		sleep((caddr_t) &mi->mi_wantcredits, PCMD);
		goto again;
	}
	i = mri->mri_next;
	if (mri->mri_desc[i] & MSCP_OWN) {
		if (!canwait) {
			splx(s);
			return (NULL);
		}
		mi->mi_wantcmd = 1;
		sleep((caddr_t) &mi->mi_wantcmd, PCMD);
		goto again;
	}
	mi->mi_credits--;
	mri->mri_desc[i] &= ~MSCP_INT;
	mri->mri_next = (mri->mri_next + 1) % mri->mri_size;
	splx(s);
	mp = &mri->mri_ring[i];

	/*
	 * Initialise some often-zero fields.
	 * ARE THE LAST TWO NECESSARY IN GENERAL?  IT SURE WOULD BE
	 * NICE IF DEC SOLD DOCUMENTATION FOR THEIR OWN CONTROLLERS.
	 */
	mp->mscp_msglen = MSCP_MSGLEN;
	mp->mscp_flags = 0;
	mp->mscp_modifier = 0;
	mp->mscp_seq.seq_bytecount = 0;
	mp->mscp_seq.seq_buffer = 0;
	mp->mscp_seq.seq_mapbase = 0;
/*???*/	mp->mscp_sccc.sccc_errlgfl = 0;
/*???*/	mp->mscp_sccc.sccc_copyspd = 0;
	return (mp);
#undef	mri
}

D 2
/*
 * Decode and print an MSCP media ID.  It is made up of five 5-bit
 * `characters' and 7 bits of numeric information.  BITS(i)
 * selects character i's bits; CHAR returns the corresponding
 * character.
 */
mscp_printmedia(id)
	register u_long id;
{
	int c4, c3, c2, c1, c0;
#define	BITS(i)	((id >> ((i) * 5 + 7)) & 0x1f)
#define	CHAR(c)	((c) ? (c) + '@' : ' ')

	c4 = BITS(4);
	c3 = BITS(3);
	c2 = BITS(2);
	c1 = BITS(1);
	c0 = BITS(0);
	printf("%c%c %c%c%c%d", CHAR(c4), CHAR(c3), CHAR(c2),
		CHAR(c1), CHAR(c0), id & 0x7f);
#undef	BITS
#undef	CHAR
}

E 2
#ifdef AVOID_EMULEX_BUG
int	mscp_aeb_xor = 0x8000bb80;
#endif

/*
 * Do a device go.  The driver calls this once it has allocated
 * resources for the transfer.  Save the resource information in
 * bp->b_ubinfo, and finish the MSCP packet.
 *
 * N.B.: If we were blocked for some time, the drive could have gone
 * off line and might still be that way.  We should probably handle
 * such a case by changing this command into an on line request and
 * not dequeuing the transfer after all.
 */
mscp_go(mi, mp, info)
	register struct mscp_info *mi;
	register struct mscp *mp;
	int info;
{
	register struct buf *bp, *dp;

	/*
	 * Now is also the time to move the transfer off the
	 * controller and drive queues, and shuffle the drive
	 * queue on the controller queue.  The idea is to try
	 * to keep as many drives busy as possible---to deal
	 * the controller's credits out to the drives in a `fair
	 * share' arrangement.  (To do this fully would be more
	 * trouble than it is worth, though.)
	 */
	dp = mi->mi_tab->b_actf;
	bp = dp->b_actf;
	dp->b_actf = bp->av_forw;	/* transfer off drive queue */
	mi->mi_tab->b_actf = dp->b_forw;/* drive off ctlr queue */
	APPEND(dp, mi->mi_tab, b_forw);	/* then back again */

	/*
	 * Move the buffer to the I/O wait queue.
	 */
	bp->av_back = mi->mi_wtab.av_back;
	bp->av_forw = &mi->mi_wtab;
	mi->mi_wtab.av_back->av_forw = bp;
	mi->mi_wtab.av_back = bp;

	/*
	 * Save the mapping info, finish the command packet, and give
	 * it to the device.  The device's dgo routine should then
	 * initiate polling.
	 */
	bp->b_info = info;
#ifdef AVOID_EMULEX_BUG
	/*
	 * The Emulex SC41/MS will occasionally zero the lower half word
	 * of the command reference number.  The upper half word remains
	 * intact.  To keep running, we convert the buffer address into
	 * a small but nonzero integer that is unique over all pending
	 * transfers, and store that value in the upper half word.  To
	 * catch occurrances of the bug (so that we can gripe to Emulex),
	 * we also put a nonzero value in the lower word.
	 */
	{
		register u_int i = mi->mi_nextbp;

		do {		/* find a free value */
			if (mi->mi_bp[i] == 0)
				goto found;
			i = (i + 1) % AEB_MAX_BP;
		} while (i != mi->mi_nextbp);
		panic("mscp_go: AEB_MAX_BP too small");
found:
		mi->mi_bp[i++] = bp;
		mi->mi_nextbp = i % AEB_MAX_BP;
		mp->mscp_cmdref = (i << 16) ^ mscp_aeb_xor;
	}
#else
	mp->mscp_cmdref = (long) bp;
#endif
	*mp->mscp_addr |= MSCP_OWN | MSCP_INT;
}

/*
 * Handle a response ring transition.
 */
mscp_dorsp(mi)
	register struct mscp_info *mi;
{
	register struct uba_device *ui;
	register struct buf *bp;
	register struct mscp *mp;
	register int nextrsp;
	struct mscp_driver *md = mi->mi_md;
	char *ctlrname, *drivename;
	int st, error, info;

	ctlrname = md->md_mname;
	drivename = md->md_dname;
	nextrsp = mi->mi_rsp.mri_next;
loop:
	if (mi->mi_rsp.mri_desc[nextrsp] & MSCP_OWN) {
		/*
		 * No more responses.  Remember the next expected
		 * response index.  Check to see if we have some
		 * credits back, and wake up sleepers if so.
		 */
		mi->mi_rsp.mri_next = nextrsp;
		if (mi->mi_wantcredits && mi->mi_credits > MSCP_MINCREDITS) {
			mi->mi_wantcredits = 0;
			wakeup((caddr_t) &mi->mi_wantcredits);
		}
		return;
	}

	/*
	 * Found a response.  Update credit information.  If there is
	 * nothing else to do, jump to `done' to get the next response.
	 */
	mp = &mi->mi_rsp.mri_ring[nextrsp];
	mi->mi_credits += MSCP_CREDITS(mp->mscp_msgtc);
	switch (MSCP_MSGTYPE(mp->mscp_msgtc)) {

	case MSCPT_SEQ:
		break;

	case MSCPT_DATAGRAM:
		(*md->md_dgram)(mi, mp);
		goto done;

	case MSCPT_CREDITS:
		goto done;

	case MSCPT_MAINTENANCE:
	default:
		printf("%s%d: unit %d: unknown message type 0x%x ignored\n",
			ctlrname, mi->mi_ctlr, mp->mscp_unit,
			MSCP_MSGTYPE(mp->mscp_msgtc));
		goto done;
	}

	/*
	 * Controllers are allowed to interrupt as any drive, so we
	 * must check the command before checking for a drive.
	 */
	if (mp->mscp_opcode == (M_OP_SETCTLRC | M_OP_END)) {
		(*md->md_ctlrdone)(mi, mp);
		goto done;
	}

	/*
	 * Find the drive info.  If there is none, and this is an
	 * available attention response, try configuring a new drive.
	 */
	if (mp->mscp_unit > md->md_ndpc) {
		printf("%s%d: unit %d out of range\n",
			ctlrname, mi->mi_ctlr, mp->mscp_unit);
		goto done;
	}
	if ((ui = mi->mi_ip[mp->mscp_unit]) == NULL) {
		if ((*md->md_unconf)(mi, mp) != MSCP_DONE) {
			printf("%s%d: unit %d not configured, ",
				ctlrname, mi->mi_ctlr, mp->mscp_unit);
			if (mp->mscp_opcode == M_OP_AVAILATTN)
				printf("available attn");
			else
				printf("stray response op 0x%x status 0x%x",
					mp->mscp_opcode, mp->mscp_status);
			printf(" ignored\n");
		}
		goto done;
	}

	/*
	 * Handle individual responses.
	 */
	st = mp->mscp_status & M_ST_MASK;
	error = 0;
	switch (mp->mscp_opcode) {

	case M_OP_END:
		/*
		 * The controller presents a bogus END packet when
		 * a read/write command is given with an illegal
		 * block number.  This is contrary to the MSCP
		 * specification (ENDs are to be given only for
		 * invalid commands), but that is the way of it.
		 */
		if (st == M_ST_INVALCMD && mp->mscp_cmdref != 0) {
			printf("%s%d: bad lbn (%d)?\n", drivename,
				ui->ui_unit, mp->mscp_seq.seq_lbn);
			error = EIO;
			goto rwend;
		}
		goto unknown;

	case M_OP_ONLINE | M_OP_END:
		/*
		 * Finished an ON LINE request.  Call the driver to
		 * find out whether it succeeded.  If so, mark it on
		 * line.
		 */
		if (ui->ui_flags & UNIT_ONLINE) {
			printf("%s%d: duplicate ONLINE ignored\n",
				drivename, ui->ui_unit);
			break;
		}
		if ((*md->md_online)(ui, mp) == MSCP_DONE)
			ui->ui_flags |= UNIT_ONLINE;
		break;

	case M_OP_GETUNITST | M_OP_END:
		/*
		 * Got unit status.  Call the driver to find out
		 * whether it succeeded, and if so, mark it.
		 */
		if ((*md->md_gotstatus)(ui, mp) == MSCP_DONE)
			ui->ui_flags |= UNIT_HAVESTATUS;
		break;

	case M_OP_AVAILATTN:
		/*
		 * The drive went offline and we did not notice.
		 * Mark it off line now, to force an on line request
		 * next, so we can make sure it is still the same
		 * drive.
		 *
		 * IF THE UDA DRIVER HAS A COMMAND AWAITING UNIBUS
		 * RESOURCES, THAT COMMAND MAY GO OUT BEFORE THE ON
		 * LINE.  IS IT WORTH FIXING??
		 */
		ui->ui_flags &= ~(UNIT_ONLINE | UNIT_HAVESTATUS);
#ifdef notyet
		(*md->md_offline)(ui, mp);
#endif
		break;

	case M_OP_READ | M_OP_END:
	case M_OP_WRITE | M_OP_END:
		/*
		 * A transfer finished.  Get the buffer, and release its
		 * map registers via ubadone().  If the command finished
		 * with an off line or available status, the drive went
		 * off line (the idiot controller does not tell us until
		 * it comes back *on* line, or until we try to use it).
		 */
		if (mp->mscp_cmdref == 0) {
			/*
			 * No buffer means there is a bug somewhere!
			 */
			printf("%s%d: io done, but no buffer?\n",
				drivename, ui->ui_unit);
			mscp_hexdump(mp);
			break;
		}

rwend:
#ifdef AVOID_EMULEX_BUG
		{
			register u_short *p = (u_short *) &mp->mscp_cmdref;

			/*
			 * Note any errors on the part of the controller.
			 * The lower word should be zero after exclusive
			 * or'ing with mscp_aeb_xor, and the upper should
			 * then be in the range [1..AEB_MAX_BP].
			 */
			mp->mscp_cmdref ^= mscp_aeb_xor;
			p[1]--;
			if (p[1] >= AEB_MAX_BP)
				panic("unrecoverable Emulex screwup");
			if (p[0] == 0)
				mi->mi_ok++;
			else {
				/*
				 * Calculate the expected response,
				 * assuming p[1] is correct.  The
				 * actual response is then the expected
				 * response xor p[0].
				 */
				int sb = ((p[1] + 1) << 16) ^ mscp_aeb_xor;

				log(LOG_WARNING, "\
Emulex SC41/MS screwup: %s%d, got %d correct, then changed 0x%x to 0x%x\n",
					ctlrname, mi->mi_ctlr,
					mi->mi_ok, sb, sb ^ p[0]);
				mi->mi_ok = 0;
			}
			/* convert index back to buffer, and mark free */
			bp = mi->mi_bp[p[1]];
			mi->mi_bp[p[1]] = 0;
		}
#else
		bp = (struct buf *) mp->mscp_cmdref;
#ifdef MSCP_PARANOIA
		{
			register struct buf *q = mi->mi_wtab.av_forw;

			/*
			 * Ensure that this response corresponds to
			 * some outstanding request.  If not, ignore
			 * it entirely.  This will likely cause a
			 * Unibus reset soon, after which the controller
			 * just might behave.
			 */
			while (q != bp && q != &mi->mi_wtab)
				q = q->av_forw;
			if (q != bp) {
				printf("%s%d: bad response packet ignored\n",
					ctlrname, mi->mi_ctlr);
				mscp_hexdump(mp);
				goto out;
			}
		}
#endif MSCP_PARANOIA
#endif AVOID_EMULEX_BUG

		/*
		 * Mark any error-due-to-bad-LBN (via `goto rwend').
		 * WHAT STATUS WILL THESE HAVE?  IT SURE WOULD BE NICE
		 * IF DEC SOLD DOCUMENTATION FOR THEIR OWN CONTROLLERS.
		 */
		if (error) {
			bp->b_flags |= B_ERROR;
			bp->b_error = error;
		}
		if (st == M_ST_OFFLINE || st == M_ST_AVAILABLE) {
			ui->ui_flags &= ~(UNIT_ONLINE | UNIT_HAVESTATUS);
#ifdef notyet
			(*md->md_offline)(ui, mp);
#endif
		}

		/*
		 * Unlink the transfer from the wait queue mi_wtab.
		 * If there are no more transfers on the drive queue
		 * for this drive, and it is a profiled disk, turn
		 * off its busy bit.
		 */
		bp->av_back->av_forw = bp->av_forw;
		bp->av_forw->av_back = bp->av_back;
		if (ui->ui_dk >= 0 && md->md_utab[ui->ui_unit].b_forw == NULL)
			dk_busy &= ~(1 << ui->ui_dk);

		/*
		 * If the transfer has something to do with bad
		 * block forwarding, let the driver handle the
		 * rest.
		 */
		if ((bp->b_flags & B_BAD) != 0 && md->md_bb != NULL) {
			(*md->md_bb)(ui, mp, bp);
			goto out;
		}

		/*
		 * If the transfer failed, give the driver a crack
		 * at fixing things up.
		 */
		if (st != M_ST_SUCCESS) {
			switch ((*md->md_ioerr)(ui, mp, bp)) {

			case MSCP_DONE:		/* fixed */
				break;

			case MSCP_RESTARTED:	/* still working on it */
				goto out;

			case MSCP_FAILED:	/* no luck */
D 3
				harderr(bp, drivename);
E 3
I 3
				diskerr(bp, drivename, "hard error",
D 5
				    LOG_PRINTF, -1, &md->md_lab[ui->ui_unit]);
E 5
I 5
				    LOG_PRINTF, -1, md->md_lab ?
				    &md->md_lab[ui->ui_unit] : md->md_lab);
E 5
E 3
				mscp_printevent(mp);
				bp->b_flags |= B_ERROR;
				bp->b_error = EIO;
				break;
			}
		}

		/*
		 * Set the residual count and mark the transfer as
		 * done.  If the I/O wait queue is now empty, release
		 * the shared BDP, if any.
		 */
		info = bp->b_info;	/* we are about to clobber it */
		bp->b_resid = bp->b_bcount - mp->mscp_seq.seq_bytecount;
		(*md->md_iodone)(mi, bp, info);
out:
		break;
		
	case M_OP_REPLACE | M_OP_END:
		/*
		 * A replace operation finished.  Just let the driver
		 * handle it (if it does replaces).
		 */
		if (md->md_replace == NULL)
			printf("%s%d: bogus REPLACE end\n",
				drivename, ui->ui_unit);
		else
			(*md->md_replace)(ui, mp);
		break;

	default:
		/*
		 * If it is not one of the above, we cannot handle it.
		 * (And we should not have received it, for that matter.)
		 */
unknown:
		printf("%s%d: unknown opcode 0x%x status 0x%x ignored\n",
			mi->mi_md->md_dname, ui->ui_unit,
			mp->mscp_opcode, mp->mscp_status);
		mscp_hexdump(mp);
		break;
	}

	/*
	 * If the drive needs to be put back in the controller queue,
	 * do that now.  (`bp' below ought to be `dp', but they are all
	 * struct buf *.)  Note that b_active was cleared in the driver;
	 * we presume that there is something to be done, hence reassert it.
	 */
	if (ui->ui_flags & UNIT_REQUEUE) {
		bp = &md->md_utab[ui->ui_unit];
if (bp->b_active) panic("mscp_dorsp requeue");
		APPEND(bp, mi->mi_tab, b_forw);
		bp->b_active = 1;
		ui->ui_flags &= ~UNIT_REQUEUE;
	}

done:
	/*
	 * Give back the response packet, and take a look at the next.
	 */
	mp->mscp_msglen = MSCP_MSGLEN;
	mi->mi_rsp.mri_desc[nextrsp] |= MSCP_OWN;
	nextrsp = (nextrsp + 1) % mi->mi_rsp.mri_size;
	goto loop;
}

/*
 * Dump the entire contents of an MSCP packet in hex.  Mainly useful
 * for debugging....
 */
mscp_hexdump(mp)
	register struct mscp *mp;
{
	register long *p = (long *) mp;
	register int i = mp->mscp_msglen;

	if (i > 256)		/* sanity */
		i = 256;
	i /= sizeof (*p);	/* ASSUMES MULTIPLE OF sizeof(long) */
	while (--i >= 0)
		printf("0x%x ", *p++);
	printf("\n");
}

/*
 * Requeue outstanding transfers, e.g., after bus reset.
 * Also requeue any drives that have on line or unit status
 * info pending.
 */
mscp_requeue(mi)
	struct mscp_info *mi;
{
	register struct uba_device *ui;
	register struct mscp_driver *md = mi->mi_md;
	register struct buf *bp, *dp;
	register int unit;
	struct buf *nextbp;

	/*
	 * Clear the controller chain.  Mark everything un-busy; we
	 * will soon fix any that are in fact busy.
	 */
	mi->mi_tab->b_actf = NULL;
	mi->mi_tab->b_active = 0;
	for (unit = 0, dp = md->md_utab; unit < md->md_nunits; unit++, dp++) {
		ui = md->md_dinfo[unit];
		if (ui == NULL || !ui->ui_alive || ui->ui_ctlr != mi->mi_ctlr)
			continue;	/* not ours */
		dp->b_forw = NULL;
		dp->b_active = 0;
	}

	/*
	 * Scan the wait queue, linking buffers onto drive queues.
	 * Note that these must be put at the front of the drive queue,
	 * lest we reorder I/O operations.
	 */
	for (bp = mi->mi_wtab.av_back; bp != &mi->mi_wtab; bp = nextbp) {
		nextbp = bp->av_back;
		dp = &md->md_utab[minor(bp->b_dev) >> md->md_unitshift];
		bp->av_forw = dp->b_actf;
		if (dp->b_actf == NULL)
			dp->b_actl = bp;
		dp->b_actf = bp;
	}
	mi->mi_wtab.av_forw = mi->mi_wtab.av_back = &mi->mi_wtab;

	/*
	 * Scan for drives waiting for on line or status responses,
	 * and for drives with pending transfers.  Put these on the
	 * controller queue, and mark the controller busy.
	 */
	for (unit = 0, dp = md->md_utab; unit < md->md_nunits; unit++, dp++) {
		ui = md->md_dinfo[unit];
		if (ui == NULL || !ui->ui_alive || ui->ui_ctlr != mi->mi_ctlr)
			continue;
		ui->ui_flags &= ~(UNIT_HAVESTATUS | UNIT_ONLINE);
		if ((ui->ui_flags & UNIT_REQUEUE) == 0 && dp->b_actf == NULL)
			continue;
		ui->ui_flags &= ~UNIT_REQUEUE;
		APPEND(dp, mi->mi_tab, b_forw);
		dp->b_active = 1;
		mi->mi_tab->b_active = 1;
	}

#ifdef AVOID_EMULEX_BUG
	/*
	 * ... and clear the index-to-buffer table.
	 */
	for (unit = 0; unit < AEB_MAX_BP; unit++)
		mi->mi_bp[unit] = 0;
#endif
}


/*
 * MSCP error reporting
 */

/*
 * Messages for the various subcodes.
 */
static char unknown_msg[] = "unknown subcode";

/*
 * Subcodes for Success (0)
 */
static char *succ_msgs[] = {
	"normal",		/* 0 */
	"spin down ignored",	/* 1 = Spin-Down Ignored */
	"still connected",	/* 2 = Still Connected */
	unknown_msg,
	"dup. unit #",		/* 4 = Duplicate Unit Number */
	unknown_msg,
	unknown_msg,
	unknown_msg,
	"already online",	/* 8 = Already Online */
	unknown_msg,
	unknown_msg,
	unknown_msg,
	unknown_msg,
	unknown_msg,
	unknown_msg,
	unknown_msg,
	"still online",		/* 16 = Still Online */
};

/*
 * Subcodes for Invalid Command (1)
 */
static char *icmd_msgs[] = {
	"invalid msg length",	/* 0 = Invalid Message Length */
};

/*
 * Subcodes for Command Aborted (2)
 */
/* none known */

/*
 * Subcodes for Unit Offline (3)
 */
static char *offl_msgs[] = {
	"unknown drive",	/* 0 = Unknown, or online to other ctlr */
	"not mounted",		/* 1 = Unmounted, or RUN/STOP at STOP */
	"inoperative",		/* 2 = Unit Inoperative */
	unknown_msg,
	"duplicate",		/* 4 = Duplicate Unit Number */
	unknown_msg,
	unknown_msg,
	unknown_msg,
	"in diagnosis",		/* 8 = Disabled by FS or diagnostic */
};

/*
 * Subcodes for Unit Available (4)
 */
/* none known */

/*
 * Subcodes for Media Format Error (5)
 */
static char *media_fmt_msgs[] = {
	"fct unread - edc",	/* 0 = FCT unreadable */
	"invalid sector header",/* 1 = Invalid Sector Header */
	"not 512 sectors",	/* 2 = Not 512 Byte Sectors */
	"not formatted",	/* 3 = Not Formatted */
	"fct ecc",		/* 4 = FCT ECC */
};

/*
 * Subcodes for Write Protected (6)
 * N.B.:  Code 6 subcodes are 7 bits higher than other subcodes
 * (i.e., bits 12-15).
 */
static char *wrprot_msgs[] = {
	unknown_msg,
	"software",		/* 1 = Software Write Protect */
	"hardware",		/* 2 = Hardware Write Protect */
};

/*
 * Subcodes for Compare Error (7)
 */
/* none known */

/*
 * Subcodes for Data Error (8)
 */
static char *data_msgs[] = {
	"forced error",		/* 0 = Forced Error (software) */
	unknown_msg,
	"header compare",	/* 2 = Header Compare Error */
	"sync timeout",		/* 3 = Sync Timeout Error */
	unknown_msg,
	unknown_msg,
	unknown_msg,
	"uncorrectable ecc",	/* 7 = Uncorrectable ECC */
	"1 symbol ecc",		/* 8 = 1 bit ECC */
	"2 symbol ecc",		/* 9 = 2 bit ECC */
	"3 symbol ecc",		/* 10 = 3 bit ECC */
	"4 symbol ecc",		/* 11 = 4 bit ECC */
	"5 symbol ecc",		/* 12 = 5 bit ECC */
	"6 symbol ecc",		/* 13 = 6 bit ECC */
	"7 symbol ecc",		/* 14 = 7 bit ECC */
	"8 symbol ecc",		/* 15 = 8 bit ECC */
};

/*
 * Subcodes for Host Buffer Access Error (9)
 */
static char *host_buffer_msgs[] = {
	unknown_msg,
	"odd xfer addr",	/* 1 = Odd Transfer Address */
	"odd xfer count",	/* 2 = Odd Transfer Count */
	"non-exist. memory",	/* 3 = Non-Existent Memory */
	"memory parity",	/* 4 = Memory Parity Error */
};

/*
 * Subcodes for Controller Error (10)
 */
static char *cntlr_msgs[] = {
	unknown_msg,
	"serdes overrun",	/* 1 = Serialiser/Deserialiser Overrun */
	"edc",			/* 2 = Error Detection Code? */
	"inconsistant internal data struct",/* 3 = Internal Error */
};

/*
 * Subcodes for Drive Error (11)
 */
static char *drive_msgs[] = {
	unknown_msg,
	"sdi command timeout",	/* 1 = SDI Command Timeout */
	"ctlr detected protocol",/* 2 = Controller Detected Protocol Error */
	"positioner",		/* 3 = Positioner Error */
	"lost rd/wr ready",	/* 4 = Lost R/W Ready Error */
	"drive clock dropout",	/* 5 = Lost Drive Clock */
	"lost recvr ready",	/* 6 = Lost Receiver Ready */
	"drive detected error",	/* 7 = Drive Error */
	"ctlr detected pulse or parity",/* 8 = Pulse or Parity Error */
};

/*
 * The following table correlates message codes with the
 * decoding strings.
 */
struct code_decode {
	char	*cdc_msg;
	int	cdc_nsubcodes;
	char	**cdc_submsgs;
} code_decode[] = {
#define	SC(m)	sizeof (m) / sizeof (m[0]), m
	"success",			SC(succ_msgs),
	"invalid command",		SC(icmd_msgs),
	"command aborted",		0, 0,
	"unit offline",		SC(offl_msgs),
	"unit available",		0, 0,
	"media format error",		SC(media_fmt_msgs),
	"write protected",		SC(wrprot_msgs),
	"compare error",		0, 0,
	"data error",			SC(data_msgs),
	"host buffer access error",	SC(host_buffer_msgs),
	"controller error",		SC(cntlr_msgs),
	"drive error",			SC(drive_msgs),
#undef SC
};

/*
 * Print the decoded error event from an MSCP error datagram.
 */
mscp_printevent(mp)
	struct mscp *mp;
{
	register int event = mp->mscp_event;
	register struct code_decode *cdc;
	int c, sc;
	char *cm, *scm;

	/*
	 * The code is the lower six bits of the event number (aka
	 * status).  If that is 6 (write protect), the subcode is in
	 * bits 12-15; otherwise, it is in bits 5-11.
	 * I WONDER WHAT THE OTHER BITS ARE FOR.  IT SURE WOULD BE
	 * NICE IF DEC SOLD DOCUMENTATION FOR THEIR OWN CONTROLLERS.
	 */
	c = event & M_ST_MASK;
	sc = (c != 6 ? event >> 5 : event >> 12) & 0x7ff;
	if (c >= sizeof code_decode / sizeof code_decode[0])
		cm = "- unknown code", scm = "??";
	else {
		cdc = &code_decode[c];
		cm = cdc->cdc_msg;
		if (sc >= cdc->cdc_nsubcodes)
			scm = unknown_msg;
		else
			scm = cdc->cdc_submsgs[sc];
	}
D 3
	printf("%s (%s) (code %d, subcode %d)\n", cm, scm, c, sc);
E 3
I 3
	printf(" %s (%s) (code %d, subcode %d)\n", cm, scm, c, sc);
E 3
}

/*
 * Print the code and logical block number for an error packet.
 * THIS IS PROBABLY PECULIAR TO DISK DRIVES.  IT SURE WOULD BE
 * NICE IF DEC SOLD DOCUMENTATION FOR THEIR OWN CONTROLLERS.
 */
mscp_decodeerror(name, ctlr, mp)
	char *name;
	int ctlr;
	register struct mscp *mp;
{
	/*
	 * For bad blocks, mp->mscp_erd.erd_hdr identifies a code and
	 * the logical block number.  Code 0 is a regular block; code 6
	 * is a replacement block.  The remaining codes are currently
	 * undefined.  The code is in the upper four bits of the header
	 * (bits 0-27 are the lbn).
	 */
	int issoft = mp->mscp_flags & (M_LF_SUCC | M_LF_CONT);
	static char *codemsg[16] = {
		"lbn", "code 1", "code 2", "code 3",
		"code 4", "code 5", "rbn", "code 7",
		"code 8", "code 9", "code 10", "code 11",
		"code 12", "code 13", "code 14", "code 15"
	};
#define BADCODE(h)	(codemsg[(unsigned)(h) >> 28])
#define BADLBN(h)	((h) & 0xfffffff)

D 3
	printf("%s%d: %s error datagram%s: ", name, ctlr,
E 3
I 3
	printf("%s%d: %s error datagram%s:", name, ctlr,
E 3
		issoft ? "soft" : "hard",
		mp->mscp_flags & M_LF_CONT ? " (continuing)" : "");
	switch (mp->mscp_format & 0377) {

	case M_FM_CTLRERR:	/* controller error */
		break;

	case M_FM_BUSADDR:	/* host memory access error */
D 3
		printf("memory addr 0x%x: ", mp->mscp_erd.erd_busaddr);
E 3
I 3
		printf(" memory addr 0x%x:", mp->mscp_erd.erd_busaddr);
E 3
		break;

	case M_FM_DISKTRN:
D 3
		printf("unit %d: level %d retry %d, %s %d: ",
E 3
I 3
		printf(" unit %d: level %d retry %d, %s %d:",
E 3
			mp->mscp_unit,
			mp->mscp_erd.erd_level, mp->mscp_erd.erd_retry,
			BADCODE(mp->mscp_erd.erd_hdr),
			BADLBN(mp->mscp_erd.erd_hdr));
		break;

	case M_FM_SDI:
D 3
		printf("unit %d: %s %d: ", mp->mscp_unit,
E 3
I 3
		printf(" unit %d: %s %d:", mp->mscp_unit,
E 3
			BADCODE(mp->mscp_erd.erd_hdr),
			BADLBN(mp->mscp_erd.erd_hdr));
		break;

	case M_FM_SMLDSK:
D 3
		printf("unit %d: small disk error, cyl %d: ",
E 3
I 3
		printf(" unit %d: small disk error, cyl %d:",
E 3
			mp->mscp_unit, mp->mscp_erd.erd_sdecyl);
		break;

	default:
D 3
		printf("unit %d: unknown error, format 0x%x: ",
E 3
I 3
		printf(" unit %d: unknown error, format 0x%x:",
E 3
			mp->mscp_unit, mp->mscp_format);
	}
	mscp_printevent(mp);
#undef BADCODE
#undef BADLBN
}
E 1
