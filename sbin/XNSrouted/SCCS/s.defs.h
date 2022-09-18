h52127
s 00002/00002/00066
d D 8.1 93/06/05 10:47:21 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00062
d D 5.10 92/02/20 11:59:57 sklower 11 10
c use new kerninfo instead of SIOCGCONF, routing socket instead of
c SIOC{ADD,DEL}RT; edit only, can't test for a while.
e
s 00001/00006/00061
d D 5.9 91/02/26 15:29:56 bostic 10 9
c ANSI fixes
e
s 00001/00011/00066
d D 5.8 90/06/01 16:14:09 bostic 9 8
c new copyright notice
e
s 00000/00001/00077
d D 5.7 90/05/28 12:48:23 bostic 8 7
c sys_errlist -> strerror(3)
e
s 00015/00004/00063
d D 5.6 88/09/19 21:00:42 bostic 7 6
c add Berkeley specific copyright notice
e
s 00006/00002/00061
d D 5.5 86/02/14 18:27:48 sklower 6 5
c 1.) Fixes from Nesheim viz pt to pt timeouts;
c 2.) Getting rid of ns_netof, to make common for Gould, CCI
e
s 00002/00000/00061
d D 5.4 85/09/17 21:42:03 sklower 5 4
c latest changes from nesheim@cornell:
c use syslog instead of perror, ignore remote requests unless specifically asked,
c handle requests from net 0.
e
s 00006/00002/00055
d D 5.3 85/08/16 22:35:04 sklower 4 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00006/00002/00055
d R 5.3 85/08/16 21:48:50 sklower 3 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00006/00002/00051
d D 5.2 85/08/16 20:43:38 sklower 2 1
c status as of 4.3 alpha tape
e
s 00053/00000/00000
d D 5.1 85/08/16 20:22:34 sklower 1 0
c date and time created 85/08/16 20:22:34 by sklower
e
u
U
t
T
I 1
D 4
/*	defs.h		*/

E 4
/*
I 4
D 7
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 12
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
E 7
 *
D 7
 *	%W% (Berkeley) %G%";
E 7
I 7
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
 *
 *	%W% (Berkeley) %G%
E 7
E 4
 */
I 4

E 4
#include <sys/types.h>
#include <sys/socket.h>

#include <net/route.h>
D 2
#include <netxns/xn.h>
#include <netxns/idp.h>
E 2
I 2
#include <netns/ns.h>
#include <netns/idp.h>
D 6
#define xnnet(p) (*(long *)&(p))
E 6
I 6
#if defined(vax) || defined(pdp11)
#define xnnet(x) ((u_long) (x)->rip_dst[1] << 16 | (u_long) (x)->rip_dst[0] )
#else
#define xnnet(x) ((u_long) (x)->rip_dst[0] << 16 | (u_long) (x)->rip_dst[1] )
#endif
E 6
#define	IDPPORT_RIF	1
E 2

#include <stdio.h>
I 5
#include <syslog.h>
E 5

#include "protocol.h"
#include "trace.h"
#include "interface.h"
#include "table.h"
#include "af.h"


/*
 * When we find any interfaces marked down we rescan the
 * kernel every CHECK_INTERVAL seconds to see if they've
 * come up.
 */
D 6
#define	CHECK_INTERVAL	(1*60)
E 6
I 6
#define	CHECK_INTERVAL	(5*60)
E 6

#define equal(a1, a2) \
	(bcmp((caddr_t)(a1), (caddr_t)(a2), sizeof (struct sockaddr)) == 0)
#define	min(a,b)	((a)>(b)?(b):(a))

I 2
struct	sockaddr_ns addr;	/* Daemon's Address */
int	s;			/* Socket to listen on */
E 2
int	kmem;
int	supplier;		/* process should supply updates */
int	install;		/* if 1 call kernel */
int	lookforinterfaces;	/* if 1 probe kernel for new up interfaces */
int	performnlist;		/* if 1 check if /vmunix has changed */
int	externalinterfaces;	/* # of remote and local interfaces */
int	timeval;		/* local idea of time */
I 5
int	noteremoterequests;	/* squawk on requests from non-local nets */
I 11
int	r;			/* Routing socket to install updates with */
struct	sockaddr_ns ns_netmask;	/* Used in installing routes */
E 11
E 5

char	packet[MAXPACKETSIZE+sizeof(struct idp)+1];
struct	rip *msg;

char	**argv0;

D 8
extern	char *sys_errlist[];
E 8
D 10
extern	int errno;

char	*malloc();
int	exit();
int	sendmsg();
E 10
I 10
int	sndmsg();
E 10
int	supply();
D 10
int	timer();
E 10
int	cleanup();
I 11
int	rtioctl();
#define	ADD	1
#define	DELETE	2
#define CHANGE	3
E 11
E 1
