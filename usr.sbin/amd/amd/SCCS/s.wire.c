h51369
s 00002/00002/00253
d D 8.1 93/06/06 11:41:46 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00252
d D 5.5 92/06/07 11:10:12 pendry 5 4
c code refresh
e
s 00113/00034/00140
d D 5.4 92/02/09 08:49:15 pendry 4 3
c merge in new release
e
s 00015/00006/00159
d D 5.3 91/05/12 15:56:40 pendry 3 2
c checkpoint for network tape
e
s 00002/00012/00163
d D 5.2 91/03/17 13:34:23 pendry 2 1
c from amd5.3 alpha11
e
s 00175/00000/00000
d D 5.1 91/03/17 12:05:23 pendry 1 0
c date and time created 91/03/17 12:05:23 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: wire.c,v 5.2.1.1 91/03/17 17:42:58 jsp Alpha $
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Imperial College of Science, Technology and Medicine, London, UK.
 * The names of the College and University may not be used to endorse
 * or promote products derived from this software without specific
 * prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: wire.c,v 5.2.1.5 91/05/07 22:14:21 jsp Alpha $
E 4
I 4
 * $Id: wire.c,v 5.2.2.1 1992/02/09 15:09:15 jsp beta $
E 4
 *
E 3
 */

/*
D 4
 * This routine returns the subnet (address&netmask) for the primary network
E 4
I 4
 * This function returns the subnet (address&netmask) for the primary network
E 4
 * interface.  If the resulting address has an entry in the hosts file, the
 * corresponding name is retuned, otherwise the address is returned in
 * standard internet format.
I 4
 * As a side-effect, a list of local IP/net address is recorded for use
 * by the islocalnet() function.
E 4
 *
D 4
 * From: Paul Anderson (23/4/90)
E 4
I 4
 * Derived from original by Paul Anderson (23/4/90)
 * Updates from Dirk Grunwald (11/11/91)
E 4
 */

#include "am.h"

#include <sys/ioctl.h>

#define NO_SUBNET "notknown"

I 4
/*
 * List of locally connected networks
 */
typedef struct addrlist addrlist;
struct addrlist {
	addrlist *ip_next;
	unsigned long ip_addr;
	unsigned long ip_mask;
};
static addrlist *localnets = 0;

E 4
#ifdef SIOCGIFFLAGS
I 4
#ifdef STELLIX
#include <sys/sema.h>
#endif /* STELLIX */
E 4
#include <net/if.h>
#include <netdb.h>

#if defined(IFF_LOCAL_LOOPBACK) && !defined(IFF_LOOPBACK)
#define IFF_LOOPBACK IFF_LOCAL_LOOPBACK
#endif

#define GFBUFLEN 1024
#define clist (ifc.ifc_ifcu.ifcu_req)
#define count (ifc.ifc_len/sizeof(struct ifreq))

char *getwire P((void));
char *getwire()
{
	struct hostent *hp;
	struct netent *np;
	struct ifconf ifc;
	struct ifreq *ifr;
	caddr_t cp, cplim;
	unsigned long address, netmask, subnet;
	char buf[GFBUFLEN], *s;
	int sk = -1;
I 4
	char *netname = 0;
E 4

	/*
	 * Get suitable socket
	 */
	if ((sk = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		goto out;

	/*
	 * Fill in ifconf details
	 */
	ifc.ifc_len = sizeof buf;
	ifc.ifc_buf = buf;

	/*
	 * Get network interface configurations
	 */
	if (ioctl(sk, SIOCGIFCONF, (caddr_t) &ifc) < 0)
		goto out;

	/*
	 * Upper bound on array
	 */
	cplim = buf + ifc.ifc_len;

	/*
	 * This is some magic to cope with both "traditional" and the
	 * new 4.4BSD-style struct sockaddrs.  The new structure has
	 * variable length and a size field to support longer addresses.
	 * AF_LINK is a new definition for 4.4BSD.
	 */
#ifdef AF_LINK
#define max(a, b) ((a) > (b) ? (a) : (b))
D 3
#define size(p) max((p).sa_len, sizeof(p))
E 3
I 3
#define size(ifr) (max((ifr)->ifr_addr.sa_len, sizeof((ifr)->ifr_addr)) + sizeof(ifr->ifr_name))
E 3
#else
D 3
#define size(p) sizeof(p)
E 3
I 3
#define size(ifr) sizeof(*ifr)
E 3
#endif
	/*
	 * Scan the list looking for a suitable interface
	 */
D 3
	for (cp = buf; cp < cplim; cp += sizeof(ifr->ifr_name) + size(ifr->ifr_addr)) {
E 3
I 3
	for (cp = buf; cp < cplim; cp += size(ifr)) {
I 4
		addrlist *al;
E 4
E 3
		ifr = (struct ifreq *) cp;

		if (ifr->ifr_addr.sa_family != AF_INET)
			continue;
		else
			address = ((struct sockaddr_in *) &ifr->ifr_addr)->sin_addr.s_addr;

		/*
		 * Get interface flags
		 */
		if (ioctl(sk, SIOCGIFFLAGS, (caddr_t) ifr) < 0)
D 4
			goto out;
E 4
I 4
			continue;
E 4

		/*
		 * If the interface is a loopback, or its not running
		 * then ignore it.
		 */
		if ((ifr->ifr_flags & IFF_LOOPBACK) != 0)
			continue;
		if ((ifr->ifr_flags & IFF_RUNNING) == 0)
			continue;

		/*
		 * Get the netmask of this interface
		 */
		if (ioctl(sk, SIOCGIFNETMASK, (caddr_t) ifr) < 0)
D 4
			goto out;
E 4
I 4
			continue;
E 4

		netmask = ((struct sockaddr_in *) &ifr->ifr_addr)->sin_addr.s_addr;

D 4
		(void) close(sk);

E 4
		/*
D 4
		 * Figure out the subnet's network address
E 4
I 4
		 * Add interface to local network list
E 4
		 */
D 4
		subnet = address & netmask;
I 3
#ifdef IN_CLASSA
		if (IN_CLASSA(subnet))
			subnet >>= IN_CLASSA_NSHIFT;
		else if (IN_CLASSB(subnet))
			subnet >>= IN_CLASSB_NSHIFT;
		else if (IN_CLASSC(subnet))
			subnet >>= IN_CLASSC_NSHIFT;
#endif
E 3
		/*
		 * Now get a usable name.
		 * First use the network database,
		 * then the host database,
		 * and finally just make a dotted quad.
		 */
		np = getnetbyaddr(subnet, AF_INET);
		if (np)
			s = np->n_name;
		else {
E 4
I 4
		al = ALLOC(addrlist);
		al->ip_addr = address;
		al->ip_mask = netmask;
		al->ip_next = localnets;
		localnets = al;

		if (netname == 0) {
			unsigned long net;
			unsigned long mask;
			unsigned long subnetshift;
			/*
			 * Figure out the subnet's network address
			 */
E 4
I 3
			subnet = address & netmask;
E 3
D 4
			hp = gethostbyaddr((char *) &subnet, 4, AF_INET);
			if (hp)
				s = hp->h_name;
			else
				s = inet_dquad(buf, subnet);
		}
E 4
I 4
		  
#ifdef IN_CLASSA
			subnet = ntohl(subnet); 
E 4

D 4
		return strdup(s);
E 4
I 4
			if (IN_CLASSA(subnet)) {
				mask = IN_CLASSA_NET;
				subnetshift = 8;
			} else if (IN_CLASSB(subnet)) {
				mask = IN_CLASSB_NET;
				subnetshift = 8;
			} else {
				mask = IN_CLASSC_NET;
				subnetshift = 4;
			}

			/*
			 * If there are more bits than the standard mask
			 * would suggest, subnets must be in use.
			 * Guess at the subnet mask, assuming reasonable
			 * width subnet fields.
I 5
			 * XXX: Or-in at least 1 byte's worth of 1s to make
			 * sure the top bits remain set.
E 5
			 */
			while (subnet &~ mask)
D 5
		  		mask = (long)mask >> subnetshift;
E 5
I 5
				mask = (mask >> subnetshift) | 0xff000000;
E 5

			net = subnet & mask;
			while ((mask & 1) == 0)
				mask >>= 1, net >>= 1;

			/*
			 * Now get a usable name.
			 * First use the network database,
			 * then the host database,
			 * and finally just make a dotted quad.
			 */

			np = getnetbyaddr(net, AF_INET);
#else
			/* This is probably very wrong. */
			np = getnetbyaddr(subnet, AF_INET);
#endif /* IN_CLASSA */
			if (np)
				s = np->n_name;
			else {
				subnet = address & netmask;
				hp = gethostbyaddr((char *) &subnet, 4, AF_INET);
				if (hp)
					s = hp->h_name;
				else
					s = inet_dquad(buf, subnet);
			}
			netname = strdup(s);
		}
E 4
	}

out:
	if (sk >= 0)
		(void) close(sk); 
I 4
	if (netname)
		return netname;
E 4
	return strdup(NO_SUBNET);
}

#else

char *getwire P((void));
char *getwire()
{
	return strdup(NO_SUBNET);
}
I 2
D 3
 * %sccs.include.redist.c%
E 3
E 2
#endif /* SIOCGIFFLAGS */
I 4

/*
 * Determine whether a network is on a local network
 * (addr) is in network byte order.
 */
int islocalnet P((unsigned long addr));
int islocalnet(addr)
unsigned long addr;
{
	addrlist *al;

	for (al = localnets; al; al = al->ip_next)
		if (((addr ^ al->ip_addr) & al->ip_mask) == 0)
			return TRUE;

#ifdef DEBUG
	{ char buf[16];
	plog(XLOG_INFO, "%s is on a remote network", inet_dquad(buf, addr));
	}
#endif
	return FALSE;
}
E 4
E 1
