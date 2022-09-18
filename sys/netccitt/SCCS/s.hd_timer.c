h60333
s 00002/00002/00119
d D 8.1 93/06/10 22:53:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00013/00108
d D 7.5 92/10/11 11:49:40 bostic 5 4
c make kernel includes standard
e
s 00001/00001/00120
d D 7.4 91/05/29 19:20:12 sklower 4 3
c for LLC2/2, there may be many pkp's to one xcp;
c so stuff pkp in m_pkthdr.rcvif, and change conventions for pk_ctlinput to get pkp
e
s 00012/00012/00109
d D 7.3 90/08/30 18:48:27 sklower 3 2
c this version compiles; completely untested
e
s 00013/00001/00108
d D 7.2 90/05/11 15:21:58 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00109/00000/00000
d D 7.1 90/05/11 11:19:36 sklower 1 0
c date and time created 90/05/11 11:19:36 by sklower
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
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
D 5
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "domain.h"
#include "socket.h"
#include "protosw.h"
#include "errno.h"
#include "time.h"
#include "kernel.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 5
E 3

D 5
#include "../net/if.h"
E 5
I 5
#include <net/if.h>
E 5

D 3
#include "../netccitt/hdlc.h"
#include "../netccitt/hd_var.h"
#include "../netccitt/x25.h"
E 3
I 3
D 5
#include "hdlc.h"
#include "hd_var.h"
#include "x25.h"
E 5
I 5
#include <netccitt/hdlc.h>
#include <netccitt/hd_var.h>
#include <netccitt/x25.h>
E 5
E 3

/*
 * these can be patched with adb if the
 * default values are inappropriate
 */

int	hd_t1 = T1;
int	hd_t3 = T3;
int	hd_n2 = N2;

/*
 *  HDLC TIMER 
 *
 *  This routine is called every 500ms by the kernel. Decrement timer by this
 *  amount - if expired then process the event.
 */

hd_timer ()
{
	register struct hdcb *hdp;
	register int s = splimp ();

	for (hdp = hdcbhead; hdp; hdp = hdp->hd_next) {
		if (hdp->hd_rrtimer && (--hdp->hd_rrtimer == 0)) {
			if (hdp->hd_lasttxnr != hdp->hd_vr)
				hd_writeinternal (hdp, RR, POLLOFF);
		}

		if (!(hdp->hd_timer && --hdp->hd_timer == 0))
			continue;

		switch (hdp->hd_state) {
		case INIT: 
		case DISC_SENT:
			hd_writeinternal (hdp, DISC, POLLON);
			break;

		case ABM: 
			if (hdp->hd_lastrxnr != hdp->hd_vs) {	/* XXX */
				hdp->hd_timeouts++;
				hd_resend_iframe (hdp);
			}
			break;

		case WAIT_SABM: 
			hd_writeinternal (hdp, FRMR, POLLOFF);
			if (++hdp->hd_retxcnt == hd_n2) {
				hdp->hd_retxcnt = 0;
				hd_writeinternal (hdp, SABM, POLLOFF);
				hdp->hd_state = WAIT_UA;
			}
			break;

		case DM_SENT: 
			if (++hdp->hd_retxcnt == hd_n2) {
				/* Notify the packet level. */
D 4
				(void) pk_ctlinput (PRC_LINKDOWN, hdp->hd_xcp);
E 4
I 4
				(void) pk_ctlinput (PRC_LINKDOWN, hdp->hd_pkp);
E 4
				hdp->hd_retxcnt = 0;
				hdp->hd_state = SABM_SENT;
				hd_writeinternal (hdp, SABM, POLLOFF);
			} else
				hd_writeinternal (hdp, DM, POLLOFF);
			break;

		case WAIT_UA: 
			if (++hdp->hd_retxcnt == hd_n2) {
				hdp->hd_retxcnt = 0;
				hd_writeinternal (hdp, DM, POLLOFF);
				hdp->hd_state = DM_SENT;
			} else
				hd_writeinternal (hdp, SABM, POLLOFF);
			break;

		case SABM_SENT: 
			/* Do this indefinitely. */
			hd_writeinternal (hdp, SABM, POLLON);
			break;

		case DISCONNECTED:
			/*
			 * Poll the interface driver flags waiting
			 * for the IFF_UP bit to come on.
			 */
			if (hdp->hd_ifp->if_flags & IFF_UP)
				hdp->hd_state = INIT;

		}
		SET_TIMER (hdp);
	}

	splx (s);
}
E 1
