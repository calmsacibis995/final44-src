h55563
s 00002/00002/00080
d D 8.1 93/06/10 21:47:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00081
d D 7.2 93/05/24 22:50:07 mckusick 2 1
c fix include directives
e
s 00082/00000/00000
d D 7.1 92/12/26 16:46:54 hibler 1 0
c date and time created 92/12/26 16:46:54 by hibler
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 University of Utah.
D 3
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: label.c 1.1 92/12/05$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Derived from routines in ufs/ufs/ufs_disksubr.c.
 */

#include <sys/param.h>
#include <sys/disklabel.h>
D 2
#include <stand/saio.h>
E 2
I 2
#include <stand.att/saio.h>
E 2

/*
 * Attempt to read a disk label from a device using the indicated stategy
 * routine.  Returns NULL on success and an error string on failure.
 */
char *
readdisklabel(io, strat, lp)
	struct iob *io;
	int (*strat)();
	register struct disklabel *lp;
{
	struct iob liob;
	struct disklabel *dlp;
	char *msg = NULL;

	liob.i_adapt = io->i_adapt;
	liob.i_ctlr = io->i_ctlr;
	liob.i_unit = io->i_unit;
	liob.i_part = 2;
	liob.i_boff = 0;
	liob.i_cyloff = 0;
	liob.i_bn = LABELSECTOR;
	liob.i_ma = liob.i_buf;
	liob.i_cc = lp->d_secsize ? lp->d_secsize : DEV_BSIZE;
	if ((*strat)(&liob, F_READ) == -1)
		return ("I/O error");

	for (dlp = (struct disklabel *)liob.i_buf;
	     dlp <= (struct disklabel *)(liob.i_buf+DEV_BSIZE-sizeof(*dlp));
	     dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
		if (dlp->d_magic != DISKMAGIC || dlp->d_magic2 != DISKMAGIC) {
			if (msg == NULL)
				msg = "no disk label";
		} else if (dlp->d_npartitions > MAXPARTITIONS || dkcksum(dlp))
			msg = "disk label corrupted";
		else {
			*lp = *dlp;
			msg = NULL;
			break;
		}
	}
	return (msg);
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
	end = (u_short *)&lp->d_partitions[lp->d_npartitions];
	while (start < end)
		sum ^= *start++;
	return (sum);
}
E 1
