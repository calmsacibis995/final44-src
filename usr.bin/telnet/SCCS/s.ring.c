h24337
s 00002/00002/00334
d D 8.2 95/05/30 20:57:10 dab 20 19
c code cleanup, change b*() calls to mem*() calls
e
s 00002/00002/00334
d D 8.1 93/06/06 16:33:12 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00330
d D 5.4 93/05/20 10:49:32 dab 18 16
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00006/00006/00330
d R 5.4 93/05/20 10:37:23 dab 17 16
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00003/00003/00333
d D 5.3 92/12/18 14:06:53 dab 16 15
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00080/00031/00256
d D 5.2 91/03/01 01:32:00 dab 15 14
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00000/00000/00287
d D 5.1 90/09/14 10:42:06 borman 14 13
c Bump the sccs id to 5.1
e
s 00004/00000/00283
d D 1.13 90/06/28 12:57:06 borman 13 12
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00282
d D 1.12 90/06/01 17:45:34 bostic 12 11
c new copyright notice
e
s 00001/00001/00292
d D 1.11 89/08/21 14:58:43 borman 11 10
c Add support for LINEMODE option
e
s 00010/00005/00283
d D 1.10 88/06/29 20:15:23 bostic 10 9
c install approved copyright notice
e
s 00000/00000/00288
d D 1.9 88/06/27 22:19:13 minshall 9 8
c Fix up lint errors.
e
s 00016/00000/00272
d D 1.8 88/03/08 10:30:54 bostic 8 7
c add Berkeley specific copyright
e
s 00072/00030/00200
d D 1.7 88/01/07 15:26:48 minshall 7 6
c Make SYNCH work (ie: urgent (ie: ring markers)).
e
s 00003/00000/00227
d D 1.6 87/11/23 20:38:04 minshall 6 5
c Fixes from Dave Borman.
e
s 00006/00000/00221
d D 1.5 87/10/27 15:58:45 minshall 5 4
c Reset ring pointers when the ring empties out.
e
s 00047/00091/00174
d D 1.4 87/10/23 11:57:27 minshall 4 3
c Make the ring buffer a two-state buffer (supplier and consumer)
c rather than a three-state buffer (supplier, sender, and acker).
e
s 00012/00000/00253
d D 1.3 87/10/10 17:45:05 minshall 3 2
c Add ring_sent_acked() for simpletons.
e
s 00044/00006/00209
d D 1.2 87/10/10 14:27:28 minshall 2 1
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00215/00000/00000
d D 1.1 87/10/10 12:39:06 minshall 1 0
c date and time created 87/10/10 12:39:06 by minshall
e
u
U
t
T
I 1
/*
I 8
D 19
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 10
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
E 8
D 4
 * This defines a structure for a receive or send ring buffer.
E 4
I 4
 * This defines a structure for a ring buffer.
E 4
 *
D 4
 * The circular buffer actually has three parts:
E 4
I 4
 * The circular buffer has two parts:
E 4
 *(((
D 4
 *	full, sent, not acked:	[ack, send)
 *	full, not sent:		[send, add)
 *	empty:			[add, ack)
E 4
I 4
 *	full:	[consume, supply)
 *	empty:	[supply, consume)
E 4
 *]]]
 *
D 4
 * Any given byte will go through "empty" -> "send" -> "ack" -> "empty"
 * as data is moved through it.  The transition from "ack" to "empty"
 * may occur instantaneously (as in the case of sending data up to another
 * process).
E 4
 */

#include	<stdio.h>
#include	<errno.h>

#ifdef	size_t
#undef	size_t
#endif

#include	<sys/types.h>
I 13
#ifndef	FILIO_H
E 13
#include	<sys/ioctl.h>
I 13
#endif
E 13
#include	<sys/socket.h>

#include	"ring.h"
#include	"general.h"

/* Internal macros */

D 2
#if	!defined(min)
#define	min(a,b)	(((a)<(b))? (a):(b))
#endif	/* !defined(min) */
E 2
I 2
#if	!defined(MIN)
#define	MIN(a,b)	(((a)<(b))? (a):(b))
#endif	/* !defined(MIN) */
E 2

D 2
#define	ring_subtract(d,a,b)	((((int)(a))-((int)(b)) >= 0)? (a)-(b): (((a)-(b))+(d)->size))
E 2
I 2
D 11
#define	ring_subtract(d,a,b)	((((int)(a))-((int)(b)) >= 0)? \
E 11
I 11
#define	ring_subtract(d,a,b)	(((a)-(b) >= 0)? \
E 11
					(a)-(b): (((a)-(b))+(d)->size))
E 2

#define	ring_increment(d,a,c)	(((a)+(c) < (d)->top)? \
					(a)+(c) : (((a)+(c))-(d)->size))

I 7
#define	ring_decrement(d,a,c)	(((a)-(c) >= (d)->bottom)? \
					(a)-(c) : (((a)-(c))-(d)->size))
E 7

I 7

E 7
/*
 * The following is a clock, used to determine full, empty, etc.
 *
 * There is some trickiness here.  Since the ring buffers are initialized
 * to ZERO on allocation, we need to make sure, when interpreting the
D 4
 * clock, that when the times are EQUAL, then the buffer is FULL, all
 * bytes have been SENT, no bytes are waiting to be ACKED, etc.
E 4
I 4
 * clock, that when the times are EQUAL, then the buffer is FULL.
E 4
 */
static u_long ring_clock = 0;


D 4
#define	ring_add_all(d) (((d)->ack == (d)->add) && \
				((d)->acktime >= (d)->addtime))
#define	ring_send_all(d) (((d)->add == (d)->send) && \
				((d)->addtime > (d)->sendtime))
#define	ring_ack_all(d) (((d)->send == (d)->ack) && \
				((d)->sendtime > (d)->acktime))
E 4
I 4
#define	ring_empty(d) (((d)->consume == (d)->supply) && \
				((d)->consumetime >= (d)->supplytime))
#define	ring_full(d) (((d)->supply == (d)->consume) && \
				((d)->supplytime > (d)->consumetime))
E 4





/* Buffer state transition routines */

I 2
D 15
ring_init(ring, buffer, count)
E 15
I 15
    ring_init(ring, buffer, count)
E 15
Ring *ring;
D 15
char *buffer;
int count;
E 15
I 15
    unsigned char *buffer;
    int count;
E 15
{
    memset((char *)ring, 0, sizeof *ring);
E 2

I 2
    ring->size = count;

D 4
    ring->add = ring->send = ring->ack = ring->bottom = buffer;
E 4
I 4
    ring->supply = ring->consume = ring->bottom = buffer;
E 4

    ring->top = ring->bottom+ring->size;

I 15
D 16
#if	defined(ENCRYPT)
E 16
I 16
D 18
#if	defined(ENCRYPTION)
E 18
I 18
#ifdef	ENCRYPTION
E 18
E 16
    ring->clearto = 0;
D 18
#endif
E 18
I 18
#endif	/* ENCRYPTION */
E 18

E 15
    return 1;
}

I 7
/* Mark routines */

E 7
E 2
/*
I 7
 * Mark the most recently supplied byte.
 */

D 15
void
E 15
I 15
    void
E 15
ring_mark(ring)
D 15
Ring *ring;
E 15
I 15
    Ring *ring;
E 15
{
    ring->mark = ring_decrement(ring, ring->supply, 1);
}

/*
 * Is the ring pointing to the mark?
 */

D 15
int
E 15
I 15
    int
E 15
ring_at_mark(ring)
D 15
Ring *ring;
E 15
I 15
    Ring *ring;
E 15
{
    if (ring->mark == ring->consume) {
	return 1;
    } else {
	return 0;
    }
}

/*
 * Clear any mark set on the ring.
 */

D 15
void
E 15
I 15
    void
E 15
ring_clear_mark(ring)
D 15
Ring *ring;
E 15
I 15
    Ring *ring;
E 15
{
    ring->mark = 0;
}

/*
E 7
 * Add characters from current segment to ring buffer.
 */
D 15
void
E 15
I 15
    void
E 15
D 4
ring_added(ring, count)
E 4
I 4
ring_supplied(ring, count)
E 4
D 15
Ring *ring;
int count;
E 15
I 15
    Ring *ring;
    int count;
E 15
{
D 4
    ring->add = ring_increment(ring, ring->add, count);
    ring->addtime = ++ring_clock;
E 4
I 4
    ring->supply = ring_increment(ring, ring->supply, count);
    ring->supplytime = ++ring_clock;
E 4
}

/*
D 4
 * We have just sent "c" bytes.
E 4
I 4
 * We have just consumed "c" bytes.
E 4
 */
D 15
void
E 15
I 15
    void
E 15
D 4
ring_sent(ring, count)
E 4
I 4
ring_consumed(ring, count)
E 4
D 15
Ring *ring;
int count;
E 15
I 15
    Ring *ring;
    int count;
E 15
{
I 6
    if (count == 0)	/* don't update anything */
	return;

I 7
    if (ring->mark &&
		(ring_subtract(ring, ring->mark, ring->consume) < count)) {
	ring->mark = 0;
    }
I 15
D 16
#if	defined(ENCRYPT)
E 16
I 16
D 18
#if	defined(ENCRYPTION)
E 18
I 18
#ifdef	ENCRYPTION
E 18
E 16
    if (ring->consume < ring->clearto &&
		ring->clearto <= ring->consume + count)
	ring->clearto = 0;
    else if (ring->consume + count > ring->top &&
		ring->bottom <= ring->clearto &&
		ring->bottom + ((ring->consume + count) - ring->top))
	ring->clearto = 0;
D 18
#endif
E 18
I 18
#endif	/* ENCRYPTION */
E 18
E 15
E 7
E 6
D 4
    ring->send = ring_increment(ring, ring->send, count);
    ring->sendtime = ++ring_clock;
E 4
I 4
    ring->consume = ring_increment(ring, ring->consume, count);
    ring->consumetime = ++ring_clock;
I 5
    /*
     * Try to encourage "ring_empty_consecutive()" to be large.
     */
    if (ring_empty(ring)) {
	ring->consume = ring->supply = ring->bottom;
    }
E 5
E 4
}

D 4
/*
 * We have just received an "ack" for "c" bytes.
 */
void
ring_acked(ring, count)
Ring *ring;
int count;
{
    ring->ack = ring_increment(ring, ring->ack, count);
    ring->acktime = ++ring_clock;
}
E 4

I 3
D 4
/*
 * We just sent and acked some data.
 */
void
ring_sent_acked(ring, count)
Ring *ring;
int count;
{
    ring_sent(ring, count);
    ring_acked(ring, count);
}
E 4

E 3
D 4

E 4
/* Buffer state query routines */


D 4
/* Number of bytes that may be added */
E 4
I 4
/* Number of bytes that may be supplied */
E 4
D 15
int
E 15
I 15
    int
E 15
ring_empty_count(ring)
D 15
Ring *ring;
E 15
I 15
    Ring *ring;
E 15
{
D 4
    if (ring_add_all(ring)) {	/* if empty */
E 4
I 4
    if (ring_empty(ring)) {	/* if empty */
E 4
	    return ring->size;
    } else {
D 4
	return ring_subtract(ring, ring->ack, ring->add);
E 4
I 4
	return ring_subtract(ring, ring->consume, ring->supply);
E 4
    }
}

D 4
/* number of CONSECUTIVE bytes that may be added */
E 4
I 4
/* number of CONSECUTIVE bytes that may be supplied */
E 4
D 15
int
E 15
I 15
    int
E 15
ring_empty_consecutive(ring)
D 15
Ring *ring;
E 15
I 15
    Ring *ring;
E 15
{
D 4
    if ((ring->ack < ring->add) || ring_add_all(ring)) {
				    /*
				     * if ack is "below" add, or empty, then
				     * return distance to the top
				     */
	return ring_subtract(ring, ring->top, ring->add);
E 4
I 4
    if ((ring->consume < ring->supply) || ring_empty(ring)) {
			    /*
			     * if consume is "below" supply, or empty, then
			     * return distance to the top
			     */
	return ring_subtract(ring, ring->top, ring->supply);
E 4
    } else {
				    /*
				     * else, return what we may.
				     */
D 4
	return ring_subtract(ring, ring->ack, ring->add);
E 4
I 4
	return ring_subtract(ring, ring->consume, ring->supply);
E 4
    }
}

D 4
/* number of bytes that are available for sending */
E 4
I 4
D 7
/* number of bytes that are available for consuming */
E 7
I 7
/* Return the number of bytes that are available for consuming
 * (but don't give more than enough to get to cross over set mark)
 */

E 7
E 4
D 15
int
E 15
I 15
    int
E 15
D 4
ring_unsent_count(ring)
E 4
I 4
ring_full_count(ring)
E 4
D 15
Ring *ring;
E 15
I 15
    Ring *ring;
E 15
{
D 4
    if (ring_send_all(ring)) {
	return ring->size;	/* nothing sent, but full */
E 4
I 4
D 7
    if (ring_full(ring)) {
	return ring->size;	/* nothing consumed, but full */
E 7
I 7
    if ((ring->mark == 0) || (ring->mark == ring->consume)) {
	if (ring_full(ring)) {
	    return ring->size;	/* nothing consumed, but full */
	} else {
	    return ring_subtract(ring, ring->supply, ring->consume);
	}
E 7
E 4
    } else {
D 4
	return ring_subtract(ring, ring->add, ring->send);
E 4
I 4
D 7
	return ring_subtract(ring, ring->supply, ring->consume);
E 7
I 7
	return ring_subtract(ring, ring->mark, ring->consume);
E 7
E 4
    }
}

D 4
/* number of CONSECUTIVE bytes available for sending */
E 4
I 4
D 7
/* number of CONSECUTIVE bytes available for consuming */
E 7
I 7
/*
 * Return the number of CONSECUTIVE bytes available for consuming.
 * However, don't return more than enough to cross over set mark.
 */
E 7
E 4
D 15
int
E 15
I 15
    int
E 15
D 4
ring_unsent_consecutive(ring)
E 4
I 4
ring_full_consecutive(ring)
E 4
D 15
Ring *ring;
E 15
I 15
    Ring *ring;
E 15
{
D 4
    if ((ring->add < ring->send) || ring_send_all(ring)) {
	return ring_subtract(ring, ring->top, ring->send);
E 4
I 4
D 7
    if ((ring->supply < ring->consume) || ring_full(ring)) {
	return ring_subtract(ring, ring->top, ring->consume);
E 7
I 7
    if ((ring->mark == 0) || (ring->mark == ring->consume)) {
	if ((ring->supply < ring->consume) || ring_full(ring)) {
	    return ring_subtract(ring, ring->top, ring->consume);
	} else {
	    return ring_subtract(ring, ring->supply, ring->consume);
	}
E 7
E 4
    } else {
D 4
	return ring_subtract(ring, ring->add, ring->send);
E 4
I 4
D 7
	return ring_subtract(ring, ring->supply, ring->consume);
E 7
I 7
	if (ring->mark < ring->consume) {
	    return ring_subtract(ring, ring->top, ring->consume);
	} else {	/* Else, distance to mark */
	    return ring_subtract(ring, ring->mark, ring->consume);
	}
E 7
E 4
    }
}

D 4
/* number of bytes awaiting acking */
int
ring_unacked_count(ring)
Ring *ring;
{
    if (ring_ack_all(ring)) {
	    return ring->size;	/* last operation was a send - nothing done */
    } else {
	return ring_subtract(ring, ring->send, ring->ack);
    }
}


E 4
/*
D 4
 * Move data into the "add" portion of of the ring buffer.
E 4
I 4
 * Move data into the "supply" portion of of the ring buffer.
E 4
 */
D 15
void
E 15
I 15
    void
E 15
D 4
ring_add_data(ring, buffer, count)
E 4
I 4
ring_supply_data(ring, buffer, count)
E 4
D 15
Ring *ring;
char *buffer;
int count;
E 15
I 15
    Ring *ring;
    unsigned char *buffer;
    int count;
E 15
{
    int i;

    while (count) {
D 2
	i = min(count, ring_empty_consecutive(ring));
E 2
I 2
	i = MIN(count, ring_empty_consecutive(ring));
E 2
D 4
	memcpy(ring->add, buffer, i);
	ring_added(ring, i);
E 4
I 4
D 20
	memcpy(ring->supply, buffer, i);
E 20
I 20
	memmove(ring->supply, buffer, i);
E 20
	ring_supplied(ring, i);
E 4
	count -= i;
	buffer += i;
    }
}

I 13
#ifdef notdef
E 13

/*
D 4
 * Move data from the "send" portion of the ring buffer
E 4
I 4
 * Move data from the "consume" portion of the ring buffer
E 4
 */
D 15
void
E 15
I 15
    void
E 15
D 4
ring_send_data(ring, buffer, count)
E 4
I 4
ring_consume_data(ring, buffer, count)
E 4
D 15
Ring *ring;
char *buffer;
int count;
E 15
I 15
    Ring *ring;
    unsigned char *buffer;
    int count;
E 15
{
    int i;

    while (count) {
D 2
	i = min(count, ring_unsent_consecutive(ring));
E 2
I 2
D 4
	i = MIN(count, ring_unsent_consecutive(ring));
E 2
	memcpy(buffer, ring->send, i);
	ring_sent(ring, i);
E 4
I 4
	i = MIN(count, ring_full_consecutive(ring));
D 20
	memcpy(buffer, ring->consume, i);
E 20
I 20
	memmove(buffer, ring->consume, i);
E 20
	ring_consumed(ring, i);
E 4
	count -= i;
	buffer += i;
    }
I 15
}
#endif

D 16
#if	defined(ENCRYPT)
E 16
I 16
D 18
#if	defined(ENCRYPTION)
E 18
I 18
#ifdef	ENCRYPTION
E 18
E 16
    void
ring_encrypt(ring, encryptor)
    Ring *ring;
    void (*encryptor)();
{
    unsigned char *s, *c;

    if (ring_empty(ring) || ring->clearto == ring->supply)
	return;

    if (!(c = ring->clearto))
	c = ring->consume;

    s = ring->supply;

    if (s <= c) {
	(*encryptor)(c, ring->top - c);
	(*encryptor)(ring->bottom, s - ring->bottom);
    } else
	(*encryptor)(c, s - c);

    ring->clearto = ring->supply;
}

    void
ring_clearto(ring)
    Ring *ring;
{
    if (!ring_empty(ring))
	ring->clearto = ring->supply;
    else
	ring->clearto = 0;
E 15
I 2
D 7
}

/* Mark routines */

/* XXX do something here */
void
ring_mark(ring)
Ring *ring;
{
}

int
ring_at_mark(ring)
Ring *ring;
{
    return 0;
}

void
ring_clear_mark(ring)
Ring *ring;
{
E 7
E 2
}
I 13
D 18
#endif
E 18
I 18
#endif	/* ENCRYPTION */
E 18
E 13
E 1
