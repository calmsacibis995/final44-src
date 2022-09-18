h31465
s 00002/00002/00184
d D 8.1 93/06/10 22:52:52 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00013/00173
d D 7.6 92/10/11 11:49:48 bostic 6 5
c make kernel includes standard
e
s 00001/00001/00185
d D 7.5 91/05/29 19:17:45 sklower 5 4
c no more %lx in kernel printf
e
s 00001/00001/00185
d D 7.4 91/05/25 15:27:41 bostic 4 3
c delete obsolete printf formats (%X -> %lx)
e
s 00012/00012/00174
d D 7.3 90/08/30 18:48:20 sklower 3 2
c this version compiles; completely untested
e
s 00013/00001/00173
d D 7.2 90/05/11 15:21:48 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00174/00000/00000
d D 7.1 90/05/11 11:19:33 sklower 1 0
c date and time created 90/05/11 11:19:33 by sklower
e
u
U
t
T
I 1
D 2
/* Copyright (c) University of British Columbia, 1984 */
E 2
I 2
/*
 * Copyright (c) University of British Columbia, 1984
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 3
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/errno.h"
#include "../h/time.h"
#include "../h/kernel.h"
E 3
I 3
D 6
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "domain.h"
#include "socket.h"
#include "protosw.h"
#include "errno.h"
#include "time.h"
#include "kernel.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 6
E 3

D 6
#include "../net/if.h"
E 6
I 6
#include <net/if.h>
E 6

D 3
#include "../netccitt/hdlc.h"
#include "../netccitt/hd_var.h"
#include "../netccitt/x25.h"
E 3
I 3
D 6
#include "hdlc.h"
#include "hd_var.h"
#include "x25.h"
E 6
I 6
#include <netccitt/hdlc.h>
#include <netccitt/hd_var.h>
#include <netccitt/x25.h>
E 6
E 3

#ifdef HDLCDEBUG
#define NTRACE		32

struct	hdlctrace {
	struct	hdcb *ht_hdp;
	short	ht_dir;
	struct	mbuf *ht_frame;
	struct	timeval ht_time;
} hdtrace[NTRACE];

int	lasttracelogged, freezetrace;
#endif

hd_trace (hdp, direction, frame)
struct hdcb *hdp;
register struct Hdlc_frame *frame;
{
	register char *s;
	register int nr, pf, ns, i;
	struct Hdlc_iframe *iframe = (struct Hdlc_iframe *) frame;

#ifdef HDLCDEBUG
	hd_savetrace (hdp, direction, frame);
#endif
	if (hdp -> hd_xcp -> xc_ltrace) {
		if (direction == RX)
			printf ("F-In:  ");
		else if (direction == 2)
				printf ("F-Xmt: ");
			else
				printf ("F-Out:   ");

		nr = iframe -> nr;
		pf = iframe -> pf;
		ns = iframe -> ns;

		switch (hd_decode (hdp, frame)) {
		case SABM: 
			printf ("SABM   : PF=%d\n", pf);
			break;

		case DISC: 
			printf ("DISC   : PF=%d\n", pf);
			break;

		case DM: 
			printf ("DM     : PF=%d\n", pf);
			break;

		case FRMR: 
			{
			register struct Frmr_frame *f = (struct Frmr_frame *)frame;

			printf ("FRMR   : PF=%d, TEXT=", pf);
			for (s = (char *) frame, i = 0; i < 5; ++i, ++s)
				printf ("%x ", (int) * s & 0xff);
			printf ("\n");
			printf ("control=%x v(s)=%d v(r)=%d w%d x%d y%d z%d\n",
				f->frmr_control, f->frmr_ns, f->frmr_nr,
				f->frmr_w, f->frmr_x, f->frmr_y, f->frmr_z);
			break;
			}

		case UA: 
			printf ("UA     : PF=%d\n", pf);
			break;

		case RR: 
			printf ("RR     : N(R)=%d, PF=%d\n", nr, pf);
			break;

		case RNR: 
			printf ("RNR    : N(R)=%d, PF=%d\n", nr, pf);
			break;

		case REJ: 
			printf ("REJ    : N(R)=%d, PF=%d\n", nr, pf);
			break;

		case IFRAME: 
			{
			register struct mbuf *m;
			register int len = 0;

			for(m = dtom (frame); m; m = m -> m_next)
				len += m -> m_len;
			len -= HDHEADERLN;
			printf ("IFRAME : N(R)=%d, PF=%d, N(S)=%d, DATA(%d)=",
				nr, pf, ns, len);
			for (s = (char *)iframe->i_field, i = 0; i < 3; ++i, ++s)
				printf ("%x ", (int) *s & 0xff);
			printf ("\n");
			break;
			}

		default: 
			printf ("ILLEGAL: ");
			for (s = (char *) frame, i = 0; i < 5; ++i, ++s)
				printf ("%x ", (int) *s & 0xff);
			printf ("\n");
		}

	}
}

#ifdef HDLCDEBUG
static
hd_savetrace (hdp, dir, frame)
struct hdcb *hdp;
struct Hdlc_frame *frame;
{
	register struct hdlctrace *htp;
	register struct mbuf *m;

	if (freezetrace)
		return;
	htp = &hdtrace[lasttracelogged];
	lasttracelogged = (lasttracelogged + 1) % NTRACE;
	if (m = htp->ht_frame)
		m_freem (m);
	m = dtom (frame);
	htp->ht_frame = m_copy (m, 0, m->m_len);
	htp->ht_hdp = hdp;
	htp->ht_dir = dir;
	htp->ht_time = time;
}

hd_dumptrace (hdp)
struct hdcb *hdp;
{
	register int i, ltrace;
	register struct hdlctrace *htp;

	freezetrace = 1;
	hd_status (hdp);
	printf ("retransmit queue:");
	for (i = 0; i < 8; i++)
D 4
		printf (" %X", hdp -> hd_retxq[i]);
E 4
I 4
D 5
		printf (" %lx", hdp -> hd_retxq[i]);
E 5
I 5
		printf (" %x", hdp -> hd_retxq[i]);
E 5
E 4
	printf ("\n");
	ltrace = hdp -> hd_xcp -> xc_ltrace;
	hdp -> hd_xcp -> xc_ltrace = 1;
	for (i = 0; i < NTRACE; i++) {
		htp = &hdtrace[(lasttracelogged + i) % NTRACE];
		if (htp->ht_hdp != hdp || htp->ht_frame == 0)
			continue;
		printf ("%d/%d	", htp->ht_time.tv_sec & 0xff,
			htp->ht_time.tv_usec / 10000);
		hd_trace (htp->ht_hdp, htp->ht_dir,
			mtod (htp->ht_frame, struct Hdlc_frame *));
		m_freem (htp->ht_frame);
		htp->ht_frame = 0;
	}
	hdp -> hd_xcp -> xc_ltrace = ltrace;
	freezetrace = 0;
}
#endif
E 1
