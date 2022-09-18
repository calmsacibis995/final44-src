h54411
s 00002/00002/00057
d D 8.1 93/06/05 10:47:51 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00058
d D 5.6 90/06/01 16:14:53 bostic 7 6
c new copyright notice
e
s 00017/00006/00052
d D 5.5 88/09/19 21:00:50 bostic 6 5
c add Berkeley specific copyright notice
e
s 00006/00003/00052
d D 5.4 86/02/14 18:28:28 sklower 5 4
c 1.) Fixes from Nesheim viz pt to pt timeouts;
c 2.) Getting rid of ns_netof, to make common for Gould, CCI
e
s 00011/00001/00044
d D 5.3 85/08/16 22:35:11 sklower 4 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00014/00001/00044
d R 5.3 85/08/16 21:49:18 sklower 3 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00000/00000/00045
d D 5.2 85/08/16 20:43:59 sklower 2 1
c status as of 4.3 alpha tape
e
s 00045/00000/00000
d D 5.1 85/08/16 20:22:45 sklower 1 0
c date and time created 85/08/16 20:22:45 by sklower
e
u
U
t
T
I 1
D 4
/*	protocol.h	1.0 4/12/85 */
E 4
I 4
/*
D 6
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 8
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1985, 1993
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
 * Xerox Routing Information Protocol
 *
 */

struct netinfo {
D 5
	u_short  rip_dst[2];		/* destination net */
	u_short	rip_metric;		/* cost of route */
E 5
I 5
	union ns_net	rip_dst;		/* destination net */
	u_short		rip_metric;		/* cost of route */
E 5
};

struct rip {
	u_short	rip_cmd;		/* request/response */
	struct netinfo rip_nets[1];	/* variable length */
};
 
/*
 * Packet types.
 */
#define	RIPCMD_REQUEST		1	/* want info */
#define	RIPCMD_RESPONSE		2	/* responding to request */

#define	RIPCMD_MAX		3
#ifdef RIPCMDS
char *ripcmds[RIPCMD_MAX] =
  { "#0", "REQUEST", "RESPONSE" };
#endif

#define	HOPCNT_INFINITY		16		/* per Xerox NS */
D 5
#define 	DSTNETS_ALL		0xffffffff	/* per Xerox NS */
E 5
I 5
#define	DSTNETS_ALL		0xffffffff	/* per Xerox NS */
E 5
#define	MAXPACKETSIZE		512		/* max broadcast size */
I 5

extern union ns_net ns_anynet;
extern union ns_net ns_zeronet;
E 5

/*
 * Timer values used in managing the routing table.
 * Every update forces an entry's timer to be reset.  After
 * EXPIRE_TIME without updates, the entry is marked invalid,
 * but held onto until GARBAGE_TIME so that others may
 * see it "be deleted".
 */
#define	TIMER_RATE		30	/* alarm clocks every 30 seconds */

#define	SUPPLY_INTERVAL		30	/* time to supply tables */

#define	EXPIRE_TIME		180	/* time to mark entry invalid */
#define	GARBAGE_TIME		240	/* time to garbage collect */
E 1
