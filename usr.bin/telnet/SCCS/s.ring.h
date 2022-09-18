h54989
s 00002/00002/00077
d D 8.1 93/06/06 16:33:16 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00075
d D 5.4 93/05/20 10:49:29 dab 15 13
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00004/00004/00075
d R 5.4 93/05/20 10:37:20 dab 14 13
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00002/00002/00077
d D 5.3 92/12/18 14:06:49 dab 13 12
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00031/00036/00048
d D 5.2 91/03/01 01:32:09 dab 12 11
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00000/00000/00084
d D 5.1 90/09/14 10:42:07 borman 11 10
c Bump the sccs id to 5.1
e
s 00008/00002/00076
d D 1.10 90/06/28 12:57:21 borman 10 9
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00077
d D 1.9 90/06/01 17:45:40 bostic 9 8
c new copyright notice
e
s 00010/00005/00078
d D 1.8 88/06/29 20:15:25 bostic 8 7
c install approved copyright notice
e
s 00021/00000/00062
d D 1.7 88/06/27 22:19:19 minshall 7 6
c Fix up lint errors.
e
s 00014/00000/00048
d D 1.6 88/03/08 10:30:57 bostic 6 5
c add Berkeley specific copyright
e
s 00002/00001/00046
d D 1.5 88/01/07 15:26:50 minshall 5 4
c Make SYNCH work (ie: urgent (ie: ring markers)).
e
s 00014/00024/00033
d D 1.4 87/10/23 11:57:29 minshall 4 3
c Make the ring buffer a two-state buffer (supplier and consumer)
c rather than a three-state buffer (supplier, sender, and acker).
e
s 00002/00001/00055
d D 1.3 87/10/10 17:45:07 minshall 3 2
c Add ring_sent_acked() for simpletons.
e
s 00004/00000/00052
d D 1.2 87/10/10 14:27:30 minshall 2 1
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00052/00000/00000
d D 1.1 87/10/10 12:39:07 minshall 1 0
c date and time created 87/10/10 12:39:07 by minshall
e
u
U
t
T
I 1
/*
I 6
D 16
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
 *
 *	%W% (Berkeley) %G%
 */

I 12
#if defined(P)
# undef P
#endif

#if defined(__STDC__) || defined(LINT_ARGS)
# define	P(x)	x
#else
# define	P(x)	()
#endif

E 12
/*
E 6
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
typedef struct {
D 4
    char	*ack,		/* where you can't add at */
    		*send,		/* where data comes out of */
    		*add,		/* where data comes in to */
E 4
I 4
D 12
    char	*consume,	/* where data comes out of */
    		*supply,	/* where data comes in to */
E 4
		*bottom,	/* lowest address in buffer */
D 5
		*top;		/* highest address+1 in buffer */
E 5
I 5
		*top,		/* highest address+1 in buffer */
		*mark;		/* marker (user defined) */
E 12
I 12
    unsigned char	*consume,	/* where data comes out of */
			*supply,	/* where data comes in to */
			*bottom,	/* lowest address in buffer */
			*top,		/* highest address+1 in buffer */
			*mark;		/* marker (user defined) */
D 13
#if	defined(ENCRYPT)
E 13
I 13
D 15
#if	defined(ENCRYPTION)
E 15
I 15
#ifdef	ENCRYPTION
E 15
E 13
    unsigned char	*clearto;	/* Data to this point is clear text */
    unsigned char	*encryyptedto;	/* Data is encrypted to here */
D 15
#endif
E 15
I 15
#endif	/* ENCRYPTION */
E 15
E 12
E 5
    int		size;		/* size in bytes of buffer */
D 4
    u_long	acktime,	/* the relations between these clocks */
		sendtime,	/* help us keep straight full, empty, etc. */
		addtime;
E 4
I 4
    u_long	consumetime,	/* help us keep straight full, empty, etc. */
		supplytime;
E 4
} Ring;

/* Here are some functions and macros to deal with the ring buffer */

D 12

#if	defined(LINT_ARGS)

E 12
I 2
/* Initialization routine */
extern int
D 12
	ring_init(Ring *ring, char *buffer, int count);
E 12
I 12
	ring_init P((Ring *ring, unsigned char *buffer, int count));
E 12

E 2
/* Data movement routines */
extern void
D 4
	ring_add_data(Ring *ring, char *buffer, int count),
	ring_send_data(Ring *ring, char *buffer, int count);
E 4
I 4
D 10
	ring_supply_data(Ring *ring, char *buffer, int count),
E 10
I 10
D 12
	ring_supply_data(Ring *ring, char *buffer, int count);
E 12
I 12
	ring_supply_data P((Ring *ring, unsigned char *buffer, int count));
E 12
#ifdef notdef
extern void
E 10
D 12
	ring_consume_data(Ring *ring, char *buffer, int count);
E 12
I 12
	ring_consume_data P((Ring *ring, unsigned char *buffer, int count));
E 12
I 10
#endif
E 10
E 4

/* Buffer state transition routines */
extern void
D 4
	ring_added(Ring *ring, int count),
	ring_sent(Ring *ring, int count),
D 3
	ring_acked(Ring *ring, int count);
E 3
I 3
	ring_acked(Ring *ring, int count),
	ring_sent_acked(Ring *ring, int count);
E 4
I 4
D 12
	ring_supplied(Ring *ring, int count),
	ring_consumed(Ring *ring, int count);
E 12
I 12
	ring_supplied P((Ring *ring, int count)),
	ring_consumed P((Ring *ring, int count));
E 12
E 4
E 3

/* Buffer state query routines */
extern int
D 12
	ring_empty_count(Ring *ring),
	ring_empty_consecutive(Ring *ring),
D 4
	ring_unsent_count(Ring *ring),
	ring_unsent_consecutive(Ring *ring),
	ring_unacked_count(Ring *ring);
E 4
I 4
	ring_full_count(Ring *ring),
	ring_full_consecutive(Ring *ring);
E 12
I 12
	ring_empty_count P((Ring *ring)),
	ring_empty_consecutive P((Ring *ring)),
	ring_full_count P((Ring *ring)),
	ring_full_consecutive P((Ring *ring));
E 12
E 4

I 7
D 12
#else /* LINT_ARGS */
extern int
	ring_init();

E 12
I 12
D 13
#if	defined(ENCRYPT)
E 13
I 13
D 15
#if	defined(ENCRYPTION)
E 15
I 15
#ifdef	ENCRYPTION
E 15
E 13
E 12
extern void
D 10
    ring_supply_data(),
E 10
I 10
D 12
    ring_supply_data();
#ifdef notdef
extern void
E 10
    ring_consume_data();
E 12
I 12
	ring_encrypt P((Ring *ring, void (*func)())),
	ring_clearto P((Ring *ring));
E 12
I 10
D 15
#endif
E 15
I 15
#endif	/* ENCRYPTION */
E 15
E 10

extern void
D 12
    ring_supplied(),
    ring_consumed();

extern void
E 12
    ring_clear_mark(),
    ring_mark();
D 12

extern int
    ring_empty_count(),
    ring_empty_consecutive(),
    ring_full_count(),
    ring_full_consecutive();
E 7
#endif	/* defined(LINT_ARGS) */
E 12
E 1
