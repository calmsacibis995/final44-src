h35536
s 00002/00002/00035
d D 8.1 93/06/10 22:29:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00037/00000/00000
d D 7.1 92/12/13 03:50:21 akito 1 0
c date and time created 92/12/13 03:50:21 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * rcvbuf.h -- receive buffer control structure definition
 *	by A.Fujita, Dec-12-1992
 */

#define	RBUF_SIZE	128

struct rcvbuf {
	u_char	*rb_push;
	u_char	*rb_pop;
	u_char	 rb_buf[RBUF_SIZE+4];
};

#define RBUF_INIT(n)	rcvbuf[n].rb_pop = rcvbuf[n].rb_push = &rcvbuf[n].rb_buf[RBUF_SIZE]

#define PUSH_RBUF(n, c)	*(--rcvbuf[n].rb_push) = c ; \
			if (rcvbuf[n].rb_push == rcvbuf[n].rb_buf) \
				rcvbuf[n].rb_push = &rcvbuf[n].rb_buf[RBUF_SIZE]

#define POP_RBUF(n, c)	c= *(--rcvbuf[n].rb_pop); \
			if (rcvbuf[n].rb_pop == rcvbuf[n].rb_buf) \
				rcvbuf[n].rb_pop = &rcvbuf[n].rb_buf[RBUF_SIZE]

#define RBUF_EMPTY(n)	(rcvbuf[n].rb_push == rcvbuf[n].rb_pop ? 1: 0)
E 1
