h61617
s 00002/00002/00143
d D 8.1 93/06/11 15:08:12 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00143
d D 7.4 93/04/20 05:48:10 torek 4 3
c spelling
e
s 00008/00008/00137
d D 7.3 92/10/11 12:38:54 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00140
d D 7.2 92/07/21 16:37:56 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00140/00000/00000
d D 7.1 92/07/13 00:41:28 torek 1 0
c date and time created 92/07/13 00:41:28 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: event.c,v 1.4 92/06/17 05:35:45 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: event.c,v 1.5 92/11/26 01:10:44 torek Exp $ (LBL)
E 4
 */

/*
 * Internal `Firm_event' interface for the keyboard and mouse drivers.
 */

D 3
#include "sys/param.h"
#include "sys/fcntl.h"
#include "sys/malloc.h"
#include "sys/proc.h"
#include "sys/systm.h"
#include "sys/vnode.h"
E 3
I 3
#include <sys/param.h>
#include <sys/fcntl.h>
#include <sys/malloc.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/vnode.h>
E 3

D 3
#include "vuid_event.h"
#include "event_var.h"
E 3
I 3
#include <sparc/dev/vuid_event.h>
#include <sparc/dev/event_var.h>
E 3

/*
 * Initialize a firm_event queue.
 */
void
ev_init(ev)
	register struct evvar *ev;
{

	ev->ev_get = ev->ev_put = 0;
	ev->ev_q = malloc((u_long)EV_QSIZE * sizeof(struct firm_event),
	    M_DEVBUF, M_WAITOK);
	bzero((caddr_t)ev->ev_q, EV_QSIZE * sizeof(struct firm_event));
}

/*
 * Tear down a firm_event queue.
 */
void
ev_fini(ev)
	register struct evvar *ev;
{

	free(ev->ev_q, M_DEVBUF);
}

/*
 * User-level interface: read, select.
 * (User cannot write an event queue.)
 */
int
ev_read(ev, uio, flags)
	register struct evvar *ev;
	struct uio *uio;
	int flags;
{
	int s, n, cnt, error;

	/*
	 * Make sure we can return at least 1.
	 */
	if (uio->uio_resid < sizeof(struct firm_event))
		return (EMSGSIZE);	/* ??? */
	s = splev();
	while (ev->ev_get == ev->ev_put) {
		if (flags & IO_NDELAY) {
			splx(s);
			return (EWOULDBLOCK);
		}
		ev->ev_wanted = 1;
		error = tsleep((caddr_t)ev, PEVENT | PCATCH, "firm_event", 0);
		if (error) {
			splx(s);
			return (error);
		}
	}
	/*
	 * Move firm_events from tail end of queue (there is at least one
	 * there).
	 */
	if (ev->ev_put < ev->ev_get)
		cnt = EV_QSIZE - ev->ev_get;	/* events in [get..QSIZE) */
	else
		cnt = ev->ev_put - ev->ev_get;	/* events in [get..put) */
	splx(s);
	n = howmany(uio->uio_resid, sizeof(struct firm_event));
	if (cnt > n)
		cnt = n;
	error = uiomove((caddr_t)&ev->ev_q[ev->ev_get],
	    cnt * sizeof(struct firm_event), uio);
	n -= cnt;
	/*
	 * If we do not wrap to 0, used up all our space, or had an error,
	 * stop.  Otherwise move from front of queue to put index, if there
	 * is anything there to move.
	 */
	if ((ev->ev_get = (ev->ev_get + cnt) % EV_QSIZE) != 0 ||
	    n == 0 || error || (cnt = ev->ev_put) == 0)
		return (error);
	if (cnt > n)
		cnt = n;
	error = uiomove((caddr_t)&ev->ev_q[0],
	    cnt * sizeof(struct firm_event), uio);
	ev->ev_get = cnt;
	return (error);
}

int
ev_select(ev, rw, p)
	register struct evvar *ev;
	int rw;
	struct proc *p;
{
	int s = splev();

	switch (rw) {

	case FREAD:
		/* succeed if there is something to read */
		if (ev->ev_get != ev->ev_put) {
			splx(s);
			return (1);
		}
		selrecord(p, &ev->ev_sel);
		break;

	case FWRITE:
		return (1);	/* always fails => never blocks */
	}
	splx(s);
	return (0);
}
E 1
