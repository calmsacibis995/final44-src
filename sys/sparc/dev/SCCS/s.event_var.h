h13626
s 00002/00002/00059
d D 8.1 93/06/11 15:08:15 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00059
d D 7.3 93/04/20 05:48:46 torek 3 2
c spelling
e
s 00005/00000/00056
d D 7.2 92/07/21 16:37:57 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00056/00000/00000
d D 7.1 92/07/13 00:41:28 torek 1 0
c date and time created 92/07/13 00:41:28 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: event_var.h,v 1.4 92/06/17 05:35:45 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: event_var.h,v 1.5 92/11/26 01:11:51 torek Exp $ (LBL)
E 3
 */

/*
 * Internal `Firm_event' interface for the keyboard and mouse drivers.
 * The drivers are expected not to place events in the queue above spltty(),
 * i.e., are expected to run off serial ports.
 */

/* EV_QSIZE should be a power of two so that `%' is fast */
#define	EV_QSIZE	256	/* may need tuning; this uses 2k */

struct evvar {
	u_int	ev_get;		/* get (read) index (modified synchronously) */
	volatile u_int ev_put;	/* put (write) index (modified by interrupt) */
	struct	selinfo ev_sel;	/* process selecting */
	struct	proc *ev_io;	/* process that opened queue (can get SIGIO) */
	char	ev_wanted;	/* wake up on input ready */
	char	ev_async;	/* send SIGIO on input ready */
	struct	firm_event *ev_q;/* circular buffer (queue) of events */
};

#define	splev()	spltty()

#define	EV_WAKEUP(ev) { \
	selwakeup(&(ev)->ev_sel); \
	if ((ev)->ev_wanted) { \
		(ev)->ev_wanted = 0; \
		wakeup((caddr_t)(ev)); \
	} \
	if ((ev)->ev_async) \
		psignal((ev)->ev_io, SIGIO); \
}

void	ev_init __P((struct evvar *));
void	ev_fini __P((struct evvar *));
int	ev_read __P((struct evvar *, struct uio *, int));
int	ev_select __P((struct evvar *, int, struct proc *));

/*
 * PEVENT is set just above PSOCK, which is just above TTIPRI, on the
 * theory that mouse and keyboard `user' input should be quick.
 */
#define	PEVENT	23
E 1
