h46330
s 00002/00002/00052
d D 8.1 93/06/11 16:00:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00054/00000/00000
d D 7.1 93/06/11 14:35:13 mckusick 1 0
c date and time created 93/06/11 14:35:13 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/disklabel.h>

char *
getdisklabel(buf, lp)
	const char *buf;
	struct disklabel *lp;
{
	register struct buf *bp;
	struct disklabel *dlp, *elp;
	char *msg = (char *)0;

	elp = (struct disklabel *)(buf + DEV_BSIZE - sizeof(*dlp));
	for (dlp = (struct disklabel *)buf; dlp <= elp;
	    dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
		if (dlp->d_magic != DISKMAGIC || dlp->d_magic2 != DISKMAGIC) {
			if (msg == (char *)0)
				msg = "no disk label";
		} else if (dlp->d_npartitions > MAXPARTITIONS ||
			   dkcksum(dlp) != 0)
			msg = "disk label corrupted";
		else {
			*lp = *dlp;
			msg = (char *)0;
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
