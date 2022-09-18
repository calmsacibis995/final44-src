h63190
s 00001/00000/00092
d D 8.2 94/01/12 10:02:53 bostic 5 4
c lint
e
s 00002/00002/00090
d D 8.1 93/06/10 21:23:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00086
d D 7.3 92/10/11 08:55:10 bostic 3 2
c make kernel includes standard
e
s 00003/00002/00089
d D 7.2 92/07/12 17:45:26 pendry 2 1
c MIN -> min
e
s 00091/00000/00000
d D 7.1 92/06/05 15:27:00 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1988 University of Utah.
D 4
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 *
 * from: Utah $Hdr: hil_subr.c 1.1 91/11/19$
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "sys/param.h"
I 2
#include "sys/systm.h"
E 2
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/clist.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/clist.h>
E 3

D 3
#include "hilreg.h"
E 3
I 3
#include <hp/dev/hilreg.h>
E 3

/*
 * XXX this file only exists to separate out the AT&T tainted code.
 */

/*
 * This is just a copy of the virgin q_to_b routine with minor
 * optimizations for HIL use.  It is used because we don't have
 * to raise the priority to spltty() for most of the clist manipulations.
 */
hilq_to_b(q, cp, cc)
	register struct clist *q;
	register char *cp;
I 5
	int cc;
E 5
{
	register struct cblock *bp;
	register int nc;
	char *acp;
	int s;
	extern char cwaiting;

	if (cc <= 0)
		return (0);
	s = splhil();
	if (q->c_cc <= 0) {
		q->c_cc = 0;
		q->c_cf = q->c_cl = NULL;
		splx(s);
		return (0);
	}
	acp = cp;

	while (cc) {
		nc = sizeof (struct cblock) - ((int)q->c_cf & CROUND);
D 2
		nc = MIN(nc, cc);
		nc = MIN(nc, q->c_cc);
E 2
I 2
		nc = min(nc, cc);
		nc = min(nc, q->c_cc);
E 2
		(void) bcopy(q->c_cf, cp, (unsigned)nc);
		q->c_cf += nc;
		q->c_cc -= nc;
		cc -= nc;
		cp += nc;
		if (q->c_cc <= 0) {
			bp = (struct cblock *)(q->c_cf - 1);
			bp = (struct cblock *)((int)bp & ~CROUND);
			q->c_cf = q->c_cl = NULL;
			spltty();
			bp->c_next = cfreelist;
			cfreelist = bp;
			cfreecount += CBSIZE;
			if (cwaiting) {
				wakeup(&cwaiting);
				cwaiting = 0;
			}
			break;
		}
		if (((int)q->c_cf & CROUND) == 0) {
			bp = (struct cblock *)(q->c_cf);
			bp--;
			q->c_cf = bp->c_next->c_info;
			spltty();
			bp->c_next = cfreelist;
			cfreelist = bp;
			cfreecount += CBSIZE;
			if (cwaiting) {
				wakeup(&cwaiting);
				cwaiting = 0;
			}
			splhil();
		}
	}
	splx(s);
	return (cp-acp);
}

E 1
