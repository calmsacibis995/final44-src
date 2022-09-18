h34443
s 00002/00002/00068
d D 8.1 93/06/05 10:48:20 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00069
d D 5.6 90/06/01 16:15:42 bostic 7 6
c new copyright notice
e
s 00017/00006/00063
d D 5.5 88/09/19 21:00:55 bostic 6 5
c add Berkeley specific copyright notice
e
s 00004/00004/00065
d D 5.4 85/09/17 21:42:16 sklower 5 4
c latest changes from nesheim@cornell:
c use syslog instead of perror, ignore remote requests unless specifically asked,
c handle requests from net 0.
e
s 00010/00001/00059
d D 5.3 85/08/16 22:35:15 sklower 4 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00012/00001/00059
d R 5.3 85/08/16 21:49:33 sklower 3 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00000/00000/00060
d D 5.2 85/08/16 20:44:23 sklower 2 1
c status as of 4.3 alpha tape
e
s 00060/00000/00000
d D 5.1 85/08/16 20:23:00 sklower 1 0
c date and time created 85/08/16 20:23:00 by sklower
e
u
U
t
T
I 1
D 4
/*	trace.h	1.0 4/16/85	*/
E 4
I 4
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 8
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
E 6
 *
D 6
 *	%W% (Berkeley) %G%";
E 6
I 6
 * This file includes significant work done at Cornell University by
 * Bill Nesheim.  That work included by permission.
E 6
 *
D 6
 * Includes material written at Cornell University by Bill Nesheim,
 * by permission of the author.
E 6
I 6
D 7
 * Redistribution and use in source and binary forms are permitted
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
E 6
 */
E 4

/*
 * Xerox Routing Information Protocol.
 */

/*
 * Trace record format.
 */
struct	iftrace {
	time_t	ift_stamp;		/* time stamp */
	struct	sockaddr ift_who;	/* from/to */
	char	*ift_packet;		/* pointer to packet */
	short	ift_size;		/* size of packet */
	short	ift_metric;		/* metric  */
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
	int	ifd_count;		/* number of unprinted records */
	struct	interface *ifd_if;	/* for locating stuff */
};

/*
 * Packet tracing stuff.
 */
int	tracepackets;		/* watch packets as they go by */
int	tracing;		/* on/off */
FILE	*ftrace;		/* output trace file */

#define	TRACE_ACTION(action, route) { \
	  if (tracing) \
		traceaction(ftrace, "action", route); \
	}
#define	TRACE_INPUT(ifp, src, size) { \
	  if (tracing) { \
		ifp = if_iflookup(src); \
		if (ifp) \
			trace(&ifp->int_input, src, &packet[sizeof(struct idp)], size, \
				ntohl(ifp->int_metric)); \
	  } \
D 5
	  if (tracepackets) \
		dumppacket(stdout, "from", src, &packet[sizeof(struct idp)], size); \
E 5
I 5
	  if (tracepackets && ftrace) \
		dumppacket(ftrace, "from", src, &packet[sizeof(struct idp)], size); \
E 5
	}
#define	TRACE_OUTPUT(ifp, dst, size) { \
	  if (tracing) { \
		ifp = if_iflookup(dst); \
		if (ifp) \
		    trace(&ifp->int_output, dst, &packet[sizeof(struct idp)], size, ifp->int_metric); \
	  } \
D 5
	  if (tracepackets) \
		dumppacket(stdout, "to", dst, &packet[sizeof(struct idp)], size); \
E 5
I 5
	  if (tracepackets && ftrace) \
		dumppacket(ftrace, "to", dst, &packet[sizeof(struct idp)], size); \
E 5
	}
E 1
