h04894
s 00002/00002/00308
d D 8.1 93/06/11 15:08:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00308
d D 7.4 93/04/20 05:51:52 torek 4 3
c spelling
e
s 00010/00010/00300
d D 7.3 92/10/11 12:38:57 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00305
d D 7.2 92/07/21 16:38:00 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00305/00000/00000
d D 7.1 92/07/13 00:41:30 torek 1 0
c date and time created 92/07/13 00:41:30 by torek
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
 * from: $Header: ms.c,v 1.4 92/06/17 05:35:50 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: ms.c,v 1.5 92/11/26 01:28:47 torek Exp $ (LBL)
E 4
 */

/*
 * Mouse driver.
 */

D 3
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/ioctl.h"
#include "sys/kernel.h"
#include "sys/proc.h"
#include "sys/syslog.h"
#include "sys/systm.h"
#include "sys/tty.h"
E 3
I 3
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/ioctl.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/syslog.h>
#include <sys/systm.h>
#include <sys/tty.h>
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
 * Mouse state.  A Mouse Systems mouse is a fairly simple device,
 * producing five-byte blobs of the form:
 *
 *	b dx dy dx dy
 *
 * where b is the button state, encoded as 0x80|(~buttons)---there are
 * three buttons (4=left, 2=middle, 1=right)---and dx,dy are X and Y
 * delta values, none of which have are in [0x80..0x87].  (This lets
 * us sync up with the mouse after an error.)
 */
struct ms_softc {
	short	ms_byteno;		/* input byte number, for decode */
	char	ms_mb;			/* mouse button state */
	char	ms_ub;			/* user button state */
	int	ms_dx;			/* delta-x */
	int	ms_dy;			/* delta-y */
	struct	tty *ms_mouse;		/* downlink for output to mouse */
	void	(*ms_open) __P((struct tty *));	/* enable dataflow */
	void	(*ms_close) __P((struct tty *));/* disable dataflow */
	volatile int ms_ready;		/* event queue is ready */
	struct	evvar ms_events;	/* event queue state */
} ms_softc;

/*
 * Attach the mouse serial (down-link) interface.
 * Do we need to set it to 1200 baud, 8 bits?
 * Test by power cycling and not booting SunOS before BSD?
 */
void
ms_serial(tp, iopen, iclose)
	struct tty *tp;
	void (*iopen)(), (*iclose)();
{

	ms_softc.ms_mouse = tp;
	ms_softc.ms_open = iopen;
	ms_softc.ms_close = iclose;
}

void
ms_rint(c)
	register int c;
{
	register struct firm_event *fe;
	register struct ms_softc *ms = &ms_softc;
	register int mb, ub, d, get, put, any;
	static const char to_one[] = { 1, 2, 2, 4, 4, 4, 4 };
	static const int to_id[] = { MS_RIGHT, MS_MIDDLE, 0, MS_LEFT };

	/*
	 * Discard input if not ready.  Drop sync on parity or framing
	 * error; gain sync on button byte.
	 */
	if (ms->ms_ready == 0)
		return;
	if (c & (TTY_FE|TTY_PE)) {
		log(LOG_WARNING,
		    "mouse input parity or framing error (0x%x)\n", c);
		ms->ms_byteno = -1;
		return;
	}
	if ((unsigned)(c - 0x80) < 8)	/* if in 0x80..0x87 */
		ms->ms_byteno = 0;

	/*
	 * Run the decode loop, adding to the current information.
	 * We add, rather than replace, deltas, so that if the event queue
	 * fills, we accumulate data for when it opens up again.
	 */
	switch (ms->ms_byteno) {

	case -1:
		return;

	case 0:
		/* buttons */
		ms->ms_byteno = 1;
		ms->ms_mb = (~c) & 0x7;
		return;

	case 1:
		/* first delta-x */
		ms->ms_byteno = 2;
		ms->ms_dx += (char)c;
		return;

	case 2:
		/* first delta-y */
		ms->ms_byteno = 3;
		ms->ms_dy += (char)c;
		return;

	case 3:
		/* second delta-x */
		ms->ms_byteno = 4;
		ms->ms_dx += (char)c;
		return;

	case 4:
		/* second delta-x */
		ms->ms_byteno = -1;	/* wait for button-byte again */
		ms->ms_dy += (char)c;
		break;

	default:
		panic("ms_rint");
		/* NOTREACHED */
	}

	/*
	 * We have at least one event (mouse button, delta-X, or
	 * delta-Y; possibly all three, and possibly three separate
	 * button events).  Deliver these events until we are out
	 * of changes or out of room.  As events get delivered,
	 * mark them `unchanged'.
	 */
	any = 0;
	get = ms->ms_events.ev_get;
	put = ms->ms_events.ev_put;
	fe = &ms->ms_events.ev_q[put];

	/* NEXT prepares to put the next event, backing off if necessary */
#define	NEXT \
	if ((++put) % EV_QSIZE == get) { \
		put--; \
		goto out; \
	}
	/* ADVANCE completes the `put' of the event */
#define	ADVANCE \
	fe++; \
	if (put >= EV_QSIZE) { \
		put = 0; \
		fe = &ms->ms_events.ev_q[0]; \
	} \
	any = 1

	mb = ms->ms_mb;
	ub = ms->ms_ub;
	while ((d = mb ^ ub) != 0) {
		/*
		 * Mouse button change.  Convert up to three changes
		 * to the `first' change, and drop it into the event queue.
		 */
		NEXT;
		d = to_one[d - 1];		/* from 1..7 to {1,2,4} */
		fe->id = to_id[d - 1];		/* from {1,2,4} to ID */
		fe->value = mb & d ? VKEY_DOWN : VKEY_UP;
		fe->time = time;
		ADVANCE;
		ub ^= d;
	}
	if (ms->ms_dx) {
		NEXT;
		fe->id = LOC_X_DELTA;
		fe->value = ms->ms_dx;
		fe->time = time;
		ADVANCE;
		ms->ms_dx = 0;
	}
	if (ms->ms_dy) {
		NEXT;
		fe->id = LOC_Y_DELTA;
		fe->value = ms->ms_dy;
		fe->time = time;
		ADVANCE;
		ms->ms_dy = 0;
	}
out:
	if (any) {
		ms->ms_ub = ub;
		ms->ms_events.ev_put = put;
		EV_WAKEUP(&ms->ms_events);
	}
}

int
msopen(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{
	int s, error;

	if (ms_softc.ms_events.ev_io)
		return (EBUSY);
	ms_softc.ms_events.ev_io = p;
	ev_init(&ms_softc.ms_events);	/* may cause sleep */
	ms_softc.ms_ready = 1;		/* start accepting events */
	(*ms_softc.ms_open)(ms_softc.ms_mouse);
	return (0);
}

int
msclose(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{

	ms_softc.ms_ready = 0;		/* stop accepting events */
	ev_fini(&ms_softc.ms_events);
	(*ms_softc.ms_close)(ms_softc.ms_mouse);
	ms_softc.ms_events.ev_io = NULL;
	return (0);
}

int
msread(dev, uio, flags)
	dev_t dev;
	struct uio *uio;
	int flags;
{

	return (ev_read(&ms_softc.ms_events, uio, flags));
}

/* this routine should not exist, but is convenient to write here for now */
int
mswrite(dev, uio, flags)
	dev_t dev;
	struct uio *uio;
	int flags;
{

	return (EOPNOTSUPP);
}

int
msioctl(dev, cmd, data, flag, p)
	dev_t dev;
	int cmd;
	register caddr_t data;
	int flag;
	struct proc *p;
{
	int s;

	switch (cmd) {

	case FIONBIO:		/* we will remove this someday (soon???) */
		return (0);

	case FIOASYNC:
		ms_softc.ms_events.ev_async = *(int *)data != 0;
		return (0);

	case TIOCSPGRP:
		if (*(int *)data != ms_softc.ms_events.ev_io->p_pgid)
			return (EPERM);
		return (0);

	case VUIDGFORMAT:
		/* we only do firm_events */
		*(int *)data = VUID_FIRM_EVENT;
		return (0);

	case VUIDSFORMAT:
		if (*(int *)data != VUID_FIRM_EVENT)
			return (EINVAL);
		return (0);
	}
	return (ENOTTY);
}

int
msselect(dev, rw, p)
	dev_t dev;
	int rw;
	struct proc *p;
{

	return (ev_select(&ms_softc.ms_events, rw, p));
}
E 1
