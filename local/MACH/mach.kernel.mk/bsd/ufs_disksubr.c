/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ufs_disksubr.c,v $
 * Revision 2.2  90/07/03  16:33:18  mrt
 * 	Correction from Mt Xinu for disks without Berkely labels.
 * 	[90/06/22            mrt]
 * 
 * Revision 2.1.1.1  90/05/17  17:49:08  mrt
 * 	Merged mt Xinu 2.6 MSD changes.
 * 	[90/05/17            emg]
 * 
 */
/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ufs_disksubr.c	7.10 (Berkeley) 6/11/88
 */

#include "param.h"
#include "systm.h"
#include "buf.h"
#include "disklabel.h"
#include "syslog.h"

#include "dir.h"
#include "user.h"

#if	sun
#include <sun/dklabel.h>
#include "fs.h"
#endif

/*
 * Seek sort for disks.  We depend on the driver
 * which calls us using b_resid as the current cylinder number.
 *
 * The argument dp structure holds a b_actf activity chain pointer
 * on which we keep two queues, sorted in ascending cylinder order.
 * The first queue holds those requests which are positioned after
 * the current cylinder (in the first request); the second holds
 * requests which came in after their cylinder number was passed.
 * Thus we implement a one way scan, retracting after reaching the
 * end of the drive to the first request on the second queue,
 * at which time it becomes the first queue.
 *
 * A one-way scan is natural because of the way UNIX read-ahead
 * blocks are allocated.
 */

#define	b_cylin	b_resid

disksort(dp, bp)
	register struct buf *dp, *bp;
{
	register struct buf *ap;

	/*
	 * If nothing on the activity queue, then
	 * we become the only thing.
	 */
	ap = dp->b_actf;
	if(ap == NULL) {
		dp->b_actf = bp;
		dp->b_actl = bp;
		bp->av_forw = NULL;
		return;
	}
	/*
	 * If we lie after the first (currently active)
	 * request, then we must locate the second request list
	 * and add ourselves to it.
	 */
	if (bp->b_cylin < ap->b_cylin) {
		while (ap->av_forw) {
			/*
			 * Check for an ``inversion'' in the
			 * normally ascending cylinder numbers,
			 * indicating the start of the second request list.
			 */
			if (ap->av_forw->b_cylin < ap->b_cylin) {
				/*
				 * Search the second request list
				 * for the first request at a larger
				 * cylinder number.  We go before that;
				 * if there is no such request, we go at end.
				 */
				do {
					if (bp->b_cylin < ap->av_forw->b_cylin)
						goto insert;
					if (bp->b_cylin == ap->av_forw->b_cylin &&
					    bp->b_blkno < ap->av_forw->b_blkno)
						goto insert;
					ap = ap->av_forw;
				} while (ap->av_forw);
				goto insert;		/* after last */
			}
			ap = ap->av_forw;
		}
		/*
		 * No inversions... we will go after the last, and
		 * be the first request in the second request list.
		 */
		goto insert;
	}
	/*
	 * Request is at/after the current request...
	 * sort in the first request list.
	 */
	while (ap->av_forw) {
		/*
		 * We want to go after the current request
		 * if there is an inversion after it (i.e. it is
		 * the end of the first request list), or if
		 * the next request is a larger cylinder than our request.
		 */
		if (ap->av_forw->b_cylin < ap->b_cylin ||
		    bp->b_cylin < ap->av_forw->b_cylin ||
		    (bp->b_cylin == ap->av_forw->b_cylin &&
		    bp->b_blkno < ap->av_forw->b_blkno))
			goto insert;
		ap = ap->av_forw;
	}
	/*
	 * Neither a second list nor a larger
	 * request... we go at the end of the first list,
	 * which is the same as the end of the whole schebang.
	 */
insert:
	bp->av_forw = ap->av_forw;
	ap->av_forw = bp;
	if (ap == dp->b_actl)
		dp->b_actl = bp;
}

#define	LABEL_DEBUG	1
#if	LABEL_DEBUG
int	label_debug	= 0;
#endif	/* LABEL_DEBUG */

/*
 * Attempt to read a disk label from a device
 * using the indicated stategy routine.
 * The label must be partly set up before this:
 * secpercyl and anything required in the strategy routine
 * (e.g., sector size) must be filled in before calling us.
 * Returns null on success and an error string on failure.
 */
char *
readdisklabel(dev, strat, lp)
	dev_t dev;
	int (*strat)();
	register struct disklabel *lp;
{
	register struct buf *bp;
	struct disklabel *dlp;
	char *msg = NULL;

	if (lp->d_secperunit == 0)
		lp->d_secperunit = 0x1fffffff;
	lp->d_npartitions = 1;
	if (lp->d_partitions[0].p_size == 0)
		lp->d_partitions[0].p_size = 0x1fffffff;
	lp->d_partitions[0].p_offset = 0;

	bp = geteblk((int)lp->d_secsize);
	bp->b_dev = dev;
	bp->b_blkno = LABELSECTOR;
	bp->b_bcount = lp->d_secsize;
	bp->b_flags = B_BUSY | B_READ;
	bp->b_cylin = LABELSECTOR / lp->d_secpercyl;
	(*strat)(bp);
	if ((bp->b_flags & B_DONE) == 0)	/* strat may be synchronous */
		biowait(bp);
	if (bp->b_flags & B_ERROR) {
		/* u.u_error = 0;		 XXX */
		msg = "I/O error";
		goto done;
	}
	for (dlp = (struct disklabel *)bp->b_un.b_addr;
	    dlp <= (struct disklabel *)(bp->b_un.b_addr+DEV_BSIZE-sizeof(*dlp));
	    dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
#if	LABEL_DEBUG
		if (label_debug)
			printf("\nCheck label %x (%x/%x=>%x) npart %d, sum %x",
				dlp, dlp->d_magic, dlp->d_magic2, DISKMAGIC,
				dlp->d_npartitions, dkcksum(dlp));
#endif	/* LABEL_DEBUG */
		if (dlp->d_magic != DISKMAGIC || dlp->d_magic2 != DISKMAGIC) {
			if (msg == NULL)
				msg = "no disk label";
		} else if (dlp->d_npartitions > MAXPARTITIONS ||
			   dkcksum(dlp) != 0)
			msg = "disk label corrupted";
		else {
			*lp = *dlp;
			msg = NULL;
			break;
		}
#if	LABEL_DEBUG
		if (label_debug)
			printf(": %s", msg);
#endif	/* LABEL_DEBUG */
	}
#if	sun
	if (msg != NULL && check_sun_label((struct dk_label *)bp->b_un.b_addr))
	{
		register struct dk_label *slp =
					(struct dk_label *)bp->b_un.b_addr;
		register int i;

		/*
		 * fill in the Berkeley label with the information from the
		 * Sun label
		 */
		bzero((caddr_t)lp, sizeof(*lp));
		bcopy(slp->dkl_asciilabel, lp->d_typename,
						sizeof(lp->d_typename) - 1);
		lp->d_magic = lp->d_magic2 = DISKMAGIC;
		lp->d_secsize = DEV_BSIZE;
		lp->d_nsectors = slp->dkl_nsect;
		lp->d_ntracks = slp->dkl_nhead;
		lp->d_ncylinders = slp->dkl_ncyl;
		lp->d_secpercyl = lp->d_nsectors * lp->d_ntracks;
		lp->d_secperunit = lp->d_secpercyl * lp->d_ncylinders;
		lp->d_sparespertrack = slp->dkl_apc / lp->d_ntracks;
		lp->d_sparespercyl = slp->dkl_apc;
		lp->d_acylinders = slp->dkl_acyl;
		lp->d_rpm = 3600;
		lp->d_interleave = slp->dkl_intrlv;
 		lp->d_bbsize = BBSIZE;
 		lp->d_sbsize = SBSIZE;
		lp->d_npartitions = MIN(NDKMAP, MAXPARTITIONS);
		for(i = 0; i < lp->d_npartitions; i++) {
			lp->d_partitions[i].p_size = slp->dkl_map[i].dkl_nblk;
			lp->d_partitions[i].p_offset =
				slp->dkl_map[i].dkl_cylno * lp->d_secpercyl;
		}
		lp->d_checksum = 0;
		lp->d_checksum = dkcksum(lp);
		msg = NULL;
	}
#endif	/* sun */
done:
	bp->b_flags = B_INVAL | B_AGE;
	brelse(bp);
	return (msg);
}

#if	sun
/*
 * Verify a Sun disk label.  Return TRUE iff good.
 */

check_sun_label(slp)
	register struct dk_label *slp;
{
	if (slp->dkl_magic != DKL_MAGIC)
		return(0);
	if (cksum_sun_label(slp) != 0)
		return(0);
	return(1);
}

cksum_sun_label(slp)
	struct dk_label *slp;
{
	register short *sp;
	register short count = sizeof(struct dk_label)/sizeof(short);
	short sum = 0;

	sp = (short *)slp;
	while(count--)
		sum ^= *sp++;
	return(sum);
}
#endif	/* sun */

/*
 * Check new disk label for sensibility
 * before setting it.
 */
setdisklabel(olp, nlp, openmask)
	register struct disklabel *olp, *nlp;
	u_long openmask;
{
	register i;
	register struct partition *opp, *npp;

	if (nlp->d_magic != DISKMAGIC || nlp->d_magic2 != DISKMAGIC ||
	    dkcksum(nlp) != 0)
		return (EINVAL);
	while ((i = ffs((long)openmask)) != 0) {
		i--;
		openmask &= ~(1 << i);
		if (nlp->d_npartitions <= i)
			return (EBUSY);
		opp = &olp->d_partitions[i];
		npp = &nlp->d_partitions[i];
		if (npp->p_offset != opp->p_offset || npp->p_size < opp->p_size)
			return (EBUSY);
		/*
		 * Copy internally-set partition information
		 * if new label doesn't include it.		XXX
		 */
		if (npp->p_fstype == FS_UNUSED && opp->p_fstype != FS_UNUSED) {
			npp->p_fstype = opp->p_fstype;
			npp->p_fsize = opp->p_fsize;
			npp->p_frag = opp->p_frag;
			npp->p_cpg = opp->p_cpg;
		}
	}
 	nlp->d_checksum = 0;
 	nlp->d_checksum = dkcksum(nlp);
	*olp = *nlp;
	return (0);
}

/* encoding of disk minor numbers, should be elsewhere... */
#define dkunit(dev)		(minor(dev) >> 3)
#define dkpart(dev)		(minor(dev) & 07)
#define dkminor(unit, part)	(((unit) << 3) | (part))

/*
 * Write disk label back to device after modification.
 */
writedisklabel(dev, strat, lp)
	dev_t dev;
	int (*strat)();
	register struct disklabel *lp;
{
	struct buf *bp;
	struct disklabel *dlp;
	int labelpart;
	int error = 0;

	labelpart = dkpart(dev);
	if (lp->d_partitions[labelpart].p_offset != 0) {
		if (lp->d_partitions[0].p_offset != 0)
			return (EXDEV);			/* not quite right */
		labelpart = 0;
	}
	bp = geteblk((int)lp->d_secsize);
	bp->b_dev = makedev(major(dev), dkminor(dkunit(dev), labelpart));
	bp->b_blkno = LABELSECTOR;
	bp->b_bcount = lp->d_secsize;
	bp->b_flags = B_READ;
	(*strat)(bp);
	biowait(bp);
	if (bp->b_flags & B_ERROR) {
		error = u.u_error;		/* XXX */
		u.u_error = 0;
		goto done;
	}
	for (dlp = (struct disklabel *)bp->b_un.b_addr;
	    dlp <= (struct disklabel *)
	      (bp->b_un.b_addr + lp->d_secsize - sizeof(*dlp));
	    dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
		if (dlp->d_magic == DISKMAGIC && dlp->d_magic2 == DISKMAGIC &&
		    dkcksum(dlp) == 0) {
			*dlp = *lp;
#if	defined(sun)
			/*
			 * Update the Sun label if the BSD label
			 * was found at the canonical offset.
			 */
			if ((caddr_t)dlp == ((caddr_t )bp->b_un.b_addr +
								LABELOFFSET)) {
				register struct dk_label *slp;
				register struct partition *pp;
				register struct dk_map *dm;
				register int i;

				slp = (struct dk_label *)bp->b_un.b_addr;
				slp->dkl_asciilabel[LABELOFFSET - 1] = '\0';
				slp->dkl_nsect = lp->d_nsectors;
				slp->dkl_nhead = lp->d_ntracks;
				slp->dkl_ncyl = lp->d_ncylinders;
				slp->dkl_apc = lp->d_sparespercyl;
				slp->dkl_acyl = lp->d_acylinders;
				slp->dkl_intrlv = lp->d_interleave;
				for(i = 0; i < MIN(NDKMAP, lp->d_npartitions);
				    i++) {
					pp = &lp->d_partitions[i];
					dm = &slp->dkl_map[i];
					dm->dkl_nblk = pp->p_size;
					dm->dkl_cylno = pp->p_offset /
								lp->d_secpercyl;
				}
				for(; i < NDKMAP; i++) {
					dm = &slp->dkl_map[i];
					dm->dkl_nblk = 0;
					dm->dkl_cylno = 0;
				}
				slp->dkl_gap1 = slp->dkl_gap2 = (u_short)-1;
				slp->dkl_bhead = 0;
				slp->dkl_ppart = 0;
				slp->dkl_magic = DKL_MAGIC;
				slp->dkl_cksum = 0;
				slp->dkl_cksum = cksum_sun_label(slp);
			}
#endif	/* sun */
			bp->b_flags = B_WRITE;
			(*strat)(bp);
			biowait(bp);
			if (bp->b_flags & B_ERROR) {
				error = u.u_error;		/* XXX */
				u.u_error = 0;
			}
			goto done;
		}
	}
	error = ESRCH;
done:
	brelse(bp);
	return (error);
}

/*
 * Compute checksum for disk label.
 */
dkcksum(lp)
	register struct disklabel *lp;
{
	register u_short *start, *end;
	register u_short sum = 0;

	start = (u_short *)lp;
#if	LABEL_DEBUG
	if (lp->d_npartitions > MAXPARTITIONS)
		end = (u_short *)&lp->d_partitions[MAXPARTITIONS];
	else
#endif	/* LABEL_DEBUG */
		end = (u_short *)&lp->d_partitions[lp->d_npartitions];
	while (start < end)
		sum ^= *start++;
	return (sum);
}

/*
 * Disk error is the preface to plaintive error messages
 * about failing disk transfers.  It prints messages of the form

hp0g: hard error reading fsbn 12345 of 12344-12347 (hp0 bn %d cn %d tn %d sn %d)

 * if the offset of the error in the transfer and a disk label
 * are both available.  blkdone should be -1 if the position of the error
 * is unknown; the disklabel pointer may be null from drivers that have not
 * been converted to use them.  The message is printed with printf
 * if pri is LOG_PRINTF, otherwise it uses log at the specified priority.
 * The message should be completed (with at least a newline) with printf
 * or addlog, respectively.  There is no trailing space.
 */
diskerr(bp, dname, what, pri, blkdone, lp)
	register struct buf *bp;
	char *dname, *what;
	int pri, blkdone;
	register struct disklabel *lp;
{
	int unit = dkunit(bp->b_dev), part = dkpart(bp->b_dev);
	register int (*pr)(), sn;
	char partname = 'a' + part;
	extern printf(), addlog();

	if (pri != LOG_PRINTF) {
		log(pri, "");
		pr = addlog;
	} else
		pr = printf;
	(*pr)("%s%d%c: %s %sing fsbn ", dname, unit, partname, what,
	    bp->b_flags & B_READ ? "read" : "writ");
	sn = bp->b_blkno;
	if (bp->b_bcount <= DEV_BSIZE)
		(*pr)("%d", sn);
	else {
		if (blkdone >= 0) {
			sn += blkdone;
			(*pr)("%d of ", sn);
		}
		(*pr)("%d-%d", bp->b_blkno,
		    bp->b_blkno + (bp->b_bcount - 1) / DEV_BSIZE);
	}
	if (lp && (blkdone >= 0 || bp->b_bcount <= lp->d_secsize)) {
#ifdef tahoe
		sn *= DEV_BSIZE / lp->d_secsize;		/* XXX */
#endif
		sn += lp->d_partitions[part].p_offset;
		(*pr)(" (%s%d bn %d; cn %d", dname, unit, sn,
		    sn / lp->d_secpercyl);
		sn %= lp->d_secpercyl;
		(*pr)(" tn %d sn %d)", sn / lp->d_ntracks, sn % lp->d_ntracks);
	}
}
