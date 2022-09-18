h17549
s 00002/00002/00068
d D 8.1 93/06/05 11:14:31 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00069
d D 5.8 90/06/01 16:30:31 bostic 12 11
c new copyright notice
e
s 00003/00003/00077
d D 5.7 89/02/20 17:21:25 karels 11 10
c don't use same buffer for input and output, as that leads to race
e
s 00006/00012/00074
d D 5.6 89/02/18 11:28:28 karels 10 9
c working with dynamic updates, auto-loading timer; tracing additions and fixes
e
s 00010/00005/00076
d D 5.5 88/06/18 13:56:47 bostic 9 8
c install approved copyright notice
e
s 00022/00010/00059
d D 5.4 88/05/31 11:52:10 karels 8 7
c add ability to trace changes only, with timestamp; even up output fields
e
s 00008/00002/00061
d D 5.3 88/02/16 18:51:05 bostic 7 6
c add Berkeley specific headers
e
s 00001/00001/00062
d D 5.2 86/04/20 23:41:52 karels 6 5
c ifp 0 for requests to supply all
e
s 00007/00001/00056
d D 5.1 85/06/04 16:40:22 dist 5 4
c Add copyright
e
s 00001/00000/00056
d D 4.4 84/04/09 15:05:58 karels 4 3
c many cleanups; avoid interface timing out; put it back asap
e
s 00001/00001/00055
d D 4.3 83/05/25 17:51:27 sam 3 2
c protocol change; byte swap those fields which need it;  also add 
c a version stamp to allow future changes
e
s 00011/00005/00045
d D 4.2 83/01/31 14:18:41 sam 2 1
c add stdout tracing of all packets
e
s 00050/00000/00000
d D 4.1 83/01/11 14:35:38 sam 1 0
c date and time created 83/01/11 14:35:38 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
E 8
I 8
D 13
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 8
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 9
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * Routing table management daemon.
 */

/*
 * Trace record format.
 */
struct	iftrace {
D 10
	time_t	ift_stamp;		/* time stamp */
E 10
I 10
	struct	timeval ift_stamp;	/* time stamp */
E 10
	struct	sockaddr ift_who;	/* from/to */
	char	*ift_packet;		/* pointer to packet */
	short	ift_size;		/* size of packet */
	short	ift_metric;		/* metric on associated metric */
};

/*
 * Per interface packet tracing buffers.  An incoming and
 * outgoing circular buffer of packets is maintained, per
 * interface, for debugging.  Buffers are dumped whenever
 * an interface is marked down.
 */
struct	ifdebug {
	struct	iftrace *ifd_records;	/* array of trace records */
	struct	iftrace *ifd_front;	/* next empty trace record */
I 4
	int	ifd_count;		/* number of unprinted records */
E 4
	struct	interface *ifd_if;	/* for locating stuff */
};

/*
 * Packet tracing stuff.
 */
I 2
int	tracepackets;		/* watch packets as they go by */
I 10
int	tracecontents;		/* watch packet contents as they go by */
E 10
E 2
D 8
int	tracing;		/* on/off */
E 8
I 8
int	traceactions;		/* on/off */
int	tracehistory;		/* on/off */
E 8
FILE	*ftrace;		/* output trace file */
I 8
D 10
char	*curtime;		/* current timestamp string */
E 10
E 8
I 2

E 2
#define	TRACE_ACTION(action, route) { \
D 8
	  if (tracing) \
		traceaction(ftrace, "action", route); \
E 8
I 8
	  if (traceactions) \
		traceaction(ftrace, action, route); \
E 8
	}
I 8
#define	TRACE_NEWMETRIC(route, newmetric) { \
	  if (traceactions) \
		tracenewmetric(ftrace, route, newmetric); \
	}
E 8
D 2
#define	TRACE_INPUT(ifp, from, size) { \
E 2
I 2
D 11
#define	TRACE_INPUT(ifp, src, size) { \
E 11
I 11
#define	TRACE_INPUT(ifp, src, pack, size) { \
E 11
E 2
D 8
	  if (tracing) { \
E 8
I 8
	  if (tracehistory) { \
E 8
D 2
		ifp = if_iflookup(from); \
E 2
I 2
		ifp = if_iflookup(src); \
E 2
		if (ifp) \
D 2
			trace(&ifp->int_input, from, packet, size, \
E 2
I 2
D 11
			trace(&ifp->int_input, src, packet, size, \
E 11
I 11
			trace(&ifp->int_input, src, pack, size, \
E 11
E 2
D 3
				ifp->int_metric); \
E 3
I 3
				ntohl(ifp->int_metric)); \
E 3
	  } \
I 2
D 8
	  if (tracepackets) \
		dumppacket(stdout, "from", src, packet, size); \
E 8
I 8
D 10
	  if (tracepackets) { \
		time_t t; \
		t = time(0); \
		dumppacket(stdout, "from", src, packet, size, &t); \
	  } \
E 10
I 10
	  if (tracepackets) \
D 11
		dumppacket(ftrace, "from", src, packet, size, &now); \
E 11
I 11
		dumppacket(ftrace, "from", src, pack, size, &now); \
E 11
E 10
E 8
E 2
	}
D 2
#define	TRACE_OUTPUT(ifp, to, size) { \
E 2
I 2
#define	TRACE_OUTPUT(ifp, dst, size) { \
E 2
D 6
	  if (tracing) \
E 6
I 6
D 8
	  if (tracing && ifp) \
E 8
I 8
	  if (tracehistory && ifp) \
E 8
E 6
D 2
		trace(&ifp->int_output, to, packet, size, ifp->int_metric); \
E 2
I 2
		trace(&ifp->int_output, dst, packet, size, ifp->int_metric); \
D 8
	  if (tracepackets) \
		dumppacket(stdout, "to", dst, packet, size); \
E 8
I 8
D 10
	  if (tracepackets) { \
		time_t t; \
		t = time(0); \
		dumppacket(stdout, "to", dst, packet, size, &t); \
	  } \
E 10
I 10
	  if (tracepackets) \
		dumppacket(ftrace, "to", dst, packet, size, &now); \
E 10
E 8
E 2
	}
E 1
