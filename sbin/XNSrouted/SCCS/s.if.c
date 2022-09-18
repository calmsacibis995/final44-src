h34912
s 00002/00002/00119
d D 8.1 93/06/05 10:47:25 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00120
d D 5.2 90/06/01 16:14:16 bostic 2 1
c new copyright notice
e
s 00131/00000/00000
d D 5.1 88/09/20 11:29:32 bostic 1 0
c routed/if.c, version 5.1
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 * static char sccsid[] = "@(#)if.c	5.1 (Berkeley) 6/4/85"; (routed/if.c)
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Routing Table Management Daemon
 */
#include "defs.h"

extern	struct interface *ifnet;

/*
 * Find the interface with address addr.
 */
struct interface *
if_ifwithaddr(addr)
	struct sockaddr *addr;
{
	register struct interface *ifp;

#define	same(a1, a2) \
	(bcmp((caddr_t)((a1)->sa_data), (caddr_t)((a2)->sa_data), 14) == 0)
	for (ifp = ifnet; ifp; ifp = ifp->int_next) {
		if (ifp->int_flags & IFF_REMOTE)
			continue;
		if (ifp->int_addr.sa_family != addr->sa_family)
			continue;
		if (same(&ifp->int_addr, addr))
			break;
		if ((ifp->int_flags & IFF_BROADCAST) &&
		    same(&ifp->int_broadaddr, addr))
			break;
	}
	return (ifp);
}

/*
 * Find the point-to-point interface with destination address addr.
 */
struct interface *
if_ifwithdstaddr(addr)
	struct sockaddr *addr;
{
	register struct interface *ifp;

	for (ifp = ifnet; ifp; ifp = ifp->int_next) {
		if ((ifp->int_flags & IFF_POINTOPOINT) == 0)
			continue;
		if (same(&ifp->int_dstaddr, addr))
			break;
	}
	return (ifp);
}

/*
 * Find the interface on the network 
 * of the specified address.
 */
struct interface *
if_ifwithnet(addr)
	register struct sockaddr *addr;
{
	register struct interface *ifp;
	register int af = addr->sa_family;
	register int (*netmatch)();

	if (af >= AF_MAX)
		return (0);
	netmatch = afswitch[af].af_netmatch;
	for (ifp = ifnet; ifp; ifp = ifp->int_next) {
		if (ifp->int_flags & IFF_REMOTE)
			continue;
		if (af != ifp->int_addr.sa_family)
			continue;
		if ((*netmatch)(addr, &ifp->int_addr))
			break;
	}
	return (ifp);
}

/*
 * Find an interface from which the specified address
 * should have come from.  Used for figuring out which
 * interface a packet came in on -- for tracing.
 */
struct interface *
if_iflookup(addr)
	struct sockaddr *addr;
{
	register struct interface *ifp, *maybe;
	register int af = addr->sa_family;
	register int (*netmatch)();

	if (af >= AF_MAX)
		return (0);
	maybe = 0;
	netmatch = afswitch[af].af_netmatch;
	for (ifp = ifnet; ifp; ifp = ifp->int_next) {
		if (ifp->int_addr.sa_family != af)
			continue;
		if (same(&ifp->int_addr, addr))
			break;
		if ((ifp->int_flags & IFF_BROADCAST) &&
		    same(&ifp->int_broadaddr, addr))
			break;
		if (maybe == 0 && (*netmatch)(addr, &ifp->int_addr))
			maybe = ifp;
	}
	if (ifp == 0)
		ifp = maybe;
	return (ifp);
}
E 1
