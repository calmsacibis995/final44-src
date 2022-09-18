h48813
s 00001/00001/00710
d D 8.4 95/05/02 00:02:13 mckusick 30 29
c spelling error in comment
e
s 00003/00002/00708
d D 8.3 95/02/09 10:44:02 cgd 29 28
c casts to quiet compiler.
e
s 00001/00001/00709
d D 8.2 95/01/09 17:51:56 cgd 28 27
c 64-bit changes
e
s 00002/00002/00708
d D 8.1 93/06/10 23:19:54 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00709
d D 7.24 93/06/04 17:01:45 sklower 26 25
c fix #endif something to #endif /* something */
e
s 00003/00001/00707
d D 7.23 93/04/06 15:25:23 sklower 25 24
c arg to timeout require a  void (*) (void)
e
s 00008/00003/00700
d D 7.22 93/02/12 14:55:48 sklower 24 23
c fixes from MITRE
e
s 00020/00021/00683
d D 7.21 92/10/11 12:21:54 bostic 23 22
c make kernel includes standard
e
s 00001/00001/00703
d D 7.20 92/08/14 12:52:25 sklower 22 21
c fix typo cpp+) instaed of cpp++)
e
s 00034/00001/00670
d D 7.19 92/07/06 15:27:50 sklower 21 20
c use multicast conventions
e
s 00017/00020/00654
d D 7.18 92/05/27 16:21:41 sklower 20 19
c fix various reported bugs (like double freeing)
e
s 00003/00003/00671
d D 7.17 92/02/20 14:20:52 sklower 19 18
c minor typo-level changes for consistency with new header files
e
s 00004/00001/00670
d D 7.16 91/08/28 12:20:24 sklower 18 17
c mark esis entries according to if_type and index, so that netstat will work
e
s 00007/00043/00664
d D 7.15 91/06/27 19:32:19 sklower 17 16
c now, take advantage that work is being done in the routing layer
e
s 00021/00017/00686
d D 7.14 91/06/27 19:22:47 sklower 16 14
c this fixes a bug in snpac_free (freeing an entry and depending on
c it for the next pointer), and also compiles on both new and old vm systems;
c it does not make use of recent changes to the routing layer, and should be
c the version for the Networking 2 tape
e
s 00020/00055/00648
d R 7.14 91/06/27 16:57:47 sklower 15 14
c new conventions for how to age llinfo; let routing layer do
c gateway route lookups, minor tweaks since dst & gateway sockaddrs stored
c separately from rtentry.
e
s 00009/00005/00694
d D 7.13 91/05/06 19:24:10 bostic 14 13
c new copyright; att/bsd/shared
e
s 00015/00004/00684
d D 7.12 91/04/26 14:52:01 sklower 13 12
c make routes start off with default mtu inherited from if
e
s 00008/00007/00680
d D 7.11 91/03/12 15:22:19 sklower 12 11
c args to log() wrong; need syslog.h to define LOG_DEBUG
e
s 00002/00000/00685
d D 7.10 91/01/09 15:43:17 sklower 11 10
c changes requested by wisconsin to support IS-IS.
e
s 00008/00001/00677
d D 7.9 90/06/22 15:39:38 sklower 10 9
c merge in UW isis changes; my merge is untested, but SCCS id's
c must be assigned before I leave today :-(
e
s 00151/00104/00527
d D 7.8 90/06/20 19:02:57 sklower 9 8
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00221/00408/00410
d D 7.7 90/06/09 17:39:16 sklower 8 7
c change snpa cache to fold in to routing table; this doesn't work yet;
c but checkpoint anyhow
e
s 00005/00005/00813
d D 7.6 90/01/25 18:26:17 sklower 7 6
c fixbugs in ishinput, rdinput processing, checkpoint for release
c to NIST
e
s 00002/00001/00816
d D 7.5 89/08/29 13:44:36 sklower 6 5
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00001/00817
d D 7.4 89/05/05 00:27:52 mckusick 5 4
c get rid of unneeded include's
e
s 00003/00002/00815
d D 7.3 89/04/26 19:17:37 mckusick 4 2
c use new form of suser()
e
s 00001/00001/00816
d R 7.3 89/04/26 18:51:54 mckusick 3 2
c use new form of suser()
e
s 00133/00103/00684
d D 7.2 89/04/22 11:54:26 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00787/00000/00000
d D 7.1 88/12/14 15:29:49 sklower 1 0
c date and time created 88/12/14 15:29:49 by sklower
e
u
U
f b 
t
T
I 14
/*-
D 27
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 14
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
/* $Header: iso_snpac.c,v 1.8 88/09/19 13:51:36 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/iso_snpac.c,v $ */
I 6
D 14
/*	%W% (Berkeley) %G% */
E 6

#ifndef lint
static char *rcsid = "$Header: iso_snpac.c,v 1.8 88/09/19 13:51:36 hagens Exp $";
#endif lint
E 14

#ifdef ISO

D 2
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
#include "../h/ioctl.h"
#include "../h/time.h"
#include "../h/kernel.h"
E 2
I 2
D 23
#include "types.h"
#include "param.h"
I 8
#include "systm.h"
E 8
I 4
D 5
#include "../ufs/dir.h"
E 5
D 16
#include "user.h"
E 16
E 4
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
#include "ioctl.h"
D 4
#include "time.h"
E 4
D 16
#include "kernel.h"
E 16
I 12
#include "syslog.h"
E 23
I 23
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>
E 23
E 12
E 2

D 23
#include "../net/if.h"
I 8
#include "../net/if_dl.h"
E 8
#include "../net/route.h"
E 23
I 23
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
E 23

D 2
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
#include "../netiso/iso_snpac.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
#include "../netiso/esis.h"
E 2
I 2
D 23
#include "iso.h"
#include "iso_var.h"
#include "iso_snpac.h"
#include "clnp.h"
#include "clnp_stat.h"
D 6
#include "argo_debug.h"
E 6
#include "esis.h"
I 6
#include "argo_debug.h"
E 23
I 23
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_snpac.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/esis.h>
#include <netiso/argo_debug.h>
E 23
E 6
E 2

D 9
#define	SNPAC_BSIZ	20		/* bucket size */
#define	SNPAC_NB	13		/* number of buckets */
#define	SNPAC_SIZE	(SNPAC_BSIZ * SNPAC_NB)
struct	snpa_cache	iso_snpac[SNPAC_SIZE];
D 2
int					iso_snpac_size = SNPAC_SIZE;/* for iso_map command */
E 2
I 2
u_int				iso_snpac_size = SNPAC_SIZE;/* for iso_map command */
E 9
E 2
int 				iso_systype = SNPA_ES;	/* default to be an ES */
I 10
extern short	esis_holding_time, esis_config_time, esis_esconfig_time;
D 16
extern int esis_config();
E 16
I 16
extern struct	timeval time;
D 25
extern int esis_config(), hz;
E 25
I 25
extern void esis_config();
extern int hz;
E 25
static void snpac_fixdstandmask();
E 16
E 10
D 2
static struct iso_addr	zero_isoa;
E 2

I 2
struct sockaddr_iso blank_siso = {sizeof(blank_siso), AF_ISO};
extern u_long iso_hashchar();
static struct sockaddr_iso
	dst	= {sizeof(dst), AF_ISO},
	gte	= {sizeof(dst), AF_ISO},
	src	= {sizeof(dst), AF_ISO},
	msk	= {sizeof(dst), AF_ISO},
D 20
	zmk = {1};
E 20
I 20
	zmk = {0};
E 20
#define zsi blank_siso
#define zero_isoa	zsi.siso_addr
D 16
#define zap_isoaddr(a, b) (bzero((caddr_t)&a.siso_addr, sizeof(*r)), \
	   ((r = b) && bcopy((caddr_t)r, (caddr_t)&a.siso_addr, 1 + (r)->isoa_len)))
E 16
I 16
#define zap_isoaddr(a, b) {Bzero(&a.siso_addr, sizeof(*r)); r = b; \
	   Bcopy(r, &a.siso_addr, 1 + (r)->isoa_len);}
E 16
#define S(x) ((struct sockaddr *)&(x))

E 2
D 8
#define	SNPAC_HASH(addr) \
D 2
	(((u_long) iso_hashchar(addr, addr->isoa_len)) % SNPAC_NB)
E 2
I 2
	(((u_long) iso_hashchar((caddr_t)addr, (int)addr->isoa_len)) % SNPAC_NB)
E 8
I 8
static struct sockaddr_dl blank_dl = {sizeof(blank_dl), AF_LINK};
static struct sockaddr_dl gte_dl;
#define zap_linkaddr(a, b, c, i) \
	(*a = blank_dl, bcopy(b, a->sdl_data, a->sdl_alen = c), a->sdl_index = i)
E 8
E 2

D 8
#define	SNPAC_LOOK(sc,addr) { \
	register n; \
	sc = &iso_snpac[SNPAC_HASH(addr) * SNPAC_BSIZ]; \
	for (n = 0 ; n < SNPAC_BSIZ ; n++,sc++) \
		if ((sc->sc_flags & SNPA_VALID) && \
			(iso_addrmatch1(&sc->sc_nsap, addr))) \
			break; \
	if (n >= SNPAC_BSIZ) \
		sc = 0; \
}

struct snpa_cache	*snpac_new();

E 8
/*
 *	We only keep track of a single IS at a time.
 */
D 8
struct snpa_cache	*known_is;
E 8
I 8
struct rtentry	*known_is;
E 8

/*
 *	Addresses taken from NBS agreements, December 1987.
 *
 *	These addresses assume on-the-wire transmission of least significant
 *	bit first. This is the method used by 802.3. When these
 *	addresses are passed to the token ring driver, (802.5), they
D 30
 *	must be bit-swaped because 802.5 transmission order is MSb first.
E 30
I 30
 *	must be bit-swapped because 802.5 transmission order is MSb first.
E 30
 *
 *	Furthermore, according to IBM Austin, these addresses are not
 *	true token ring multicast addresses. More work is necessary
 *	to get multicast to work right on token ring.
 *
 *	Currently, the token ring driver does not handle multicast, so
 *	these addresses are converted into the broadcast address in
 *	lan_output() That means that if these multicast addresses change
 *	the token ring driver must be altered.
 */
D 9
struct snpa_cache	all_es = {
	{ { 0x0 },							/* sc_nsap */
	6,									/* sc_len */
	{ 0x09, 0x00, 0x2b, 0x00, 0x00, 0x04 }, /* sc_snpa */
	SNPA_VALID,							/* sc_flags */
	0	}								/* sc_ht */ 
};
struct snpa_cache	all_is = {
	{ { 0x0 },							/* sc_nsap */
	6,									/* sc_len */
	{ 0x09, 0x00, 0x2b, 0x00, 0x00, 0x05 }, /* sc_snpa */
	SNPA_VALID,							/* sc_flags */
	0	}								/* sc_ht */ 
};
I 8
char all_es_snpa[] = { 0x09, 0x00, 0x2b, 0x00, 0x00, 0x04 }; /* sc_snpa */
char all_is_snpa[] = { 0x09, 0x00, 0x2b, 0x00, 0x00, 0x05 }; /* sc_snpa */
E 9
I 9
char all_es_snpa[] = { 0x09, 0x00, 0x2b, 0x00, 0x00, 0x04 };
char all_is_snpa[] = { 0x09, 0x00, 0x2b, 0x00, 0x00, 0x05 };
I 11
char all_l1is_snpa[] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x14};
char all_l2is_snpa[] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x15};
E 11
E 9
E 8

I 8
union sockunion {
	struct sockaddr_iso siso;
	struct sockaddr_dl	sdl;
	struct sockaddr		sa;
};
E 8

/*
I 8
 * FUNCTION:		llc_rtrequest
 *
 * PURPOSE:			Manage routing table entries specific to LLC for ISO.
 *
 * NOTES:			This does a lot of obscure magic;
 */
llc_rtrequest(req, rt, sa)
int req;
register struct rtentry *rt;
struct sockaddr *sa;
{
	register union sockunion *gate = (union sockunion *)rt->rt_gateway;
	register struct llinfo_llc *lc = (struct llinfo_llc *)rt->rt_llinfo, *lc2;
	struct rtentry *rt2;
	struct ifnet *ifp = rt->rt_ifp;
	int addrlen = ifp->if_addrlen;
I 9
D 17
	static struct rtentry *recursing = 0;
E 17
I 13
#define LLC_SIZE 3 /* XXXXXX do this right later */
E 13
E 9

D 9
	if (lc == 0)
		panic("llc_rtrequest 1");
	switch (req) {
	case RTM_RESOLVE:
		if (gate->sdl.sdl_family == AF_LINK) {
			/* We have just cloned a route to a host presumed to be on
			   our local net */
			gate->sdl.sdl_alen = 0;
E 9
I 9
	IFDEBUG (D_SNPA)
		printf("llc_rtrequest(%d, %x, %x)\n", req, rt, sa);
	ENDDEBUG
D 17
	if (rt->rt_flags & RTF_GATEWAY) {
		if (recursing) {
D 12
			log("llc_rtrequest: gateway route points to same type %x %x\n",
E 12
I 12
			log(LOG_DEBUG, "llc_rtrequest: gateway route points to same type %x %x\n",
E 12
				recursing, rt);
		} else switch (req) {
		case RTM_RESOLVE:
		case RTM_ADD:
			recursing = rt;
			rt->rt_llinfo = (caddr_t)rtalloc1(&gate->sa, 1);
			recursing = 0;
I 13
			if (rt->rt_rmx.rmx_mtu == 0) {
				rt->rt_rmx.rmx_mtu =
				    ((rt2 = (struct rtentry *)rt->rt_llinfo) &&
					    (rt2->rt_rmx.rmx_mtu)) ?
				    rt2->rt_rmx.rmx_mtu :
				    rt->rt_ifp->if_mtu - LLC_SIZE;
			}
E 13
			return;

		case RTM_DELETE:
			if (lc)
				RTFREE((struct rtentry *)lc);
			rt->rt_llinfo = 0;
E 9
		}
D 9
		/* Fall Through */
E 9
I 9
	} else switch (req) {
E 17
I 17
	if (rt->rt_flags & RTF_GATEWAY)
		return;
	else switch (req) {
E 17
E 9
	case RTM_ADD:
D 9
		lc->lc_rt = rt;
E 9
I 9
		/*
		 * Case 1: This route may come from a route to iface with mask
		 * or from a default route.
		 */
E 9
		if (rt->rt_flags & RTF_CLONING) {
I 21
			iso_setmcasts(ifp, req);
E 21
D 9
			/*
			 * Case 1: This route may come from a route to iface with mask
			 * or from a default IS.
			 */
			rt->rt_gateway = ifp->if_addrlist->ifa_addr;
		} else if ((rt->rt_flags & RTF_GATEWAY == 0) &&
				   gate->sdl.sdl_family == AF_LINK) {
			/*
			 * Case 2:  This route may come from ESIS or a manual route
			 * add with a LL address.
			 */
			insque(lc, &llinfo_llc);
			if (gate->sdl.sdl_alen == sizeof(struct esis_req) + addrlen) {
				gate->sdl.sdl_alen -= sizeof(struct esis_req);
				bcopy(addrlen + LLADDR(&gate->sdl),
					  (caddr_t)&lc->lc_er, sizeof(lc->lc_er));
			} else if (gate->sdl.sdl_alen == addrlen)
				lc->lc_flags = (SNPA_ES | SNPA_VALID | SNPA_PERM);
		} else {
			/*
			 * Case 3:  Told to add route via a gateway;
			 * try to provoke LL route to exist for gateway by cloning.
			 */
			if (gate->siso.siso_family == AF_ISO &&
				(rt->rt_flags & RTF_GATEWAY) &&
				(rt2 = rtalloc1(&gate->sa, 1)) &&
					(lc2 = (struct llinfo_llc *)rt2->rt_llinfo)) {
				lc->lc_rtgate = rt2;
				rt2->rt_use++;
				if (lc2->lc_rtgate == 0) {
					lc->lc_prev = lc->lc_next = lc;
					lc2->lc_rtgate = rt;
					rt->rt_use++;
				} else {
					if (lc2->lc_rtgate->rt_llinfo == 0)
						panic("llc_rtrequest 2");
					insque(lc, lc2->lc_rtgate->rt_llinfo);
E 9
I 9
D 17
			register struct ifaddr *ifa;
			register struct sockaddr *sa;
			for (ifa = ifp->if_addrlist; ifa; ifa->ifa_next)
				if ((sa = ifa->ifa_addr)->sa_family == AF_LINK) {
					if (sa->sa_len > gate->sa.sa_len)
D 12
						log("llc_rtrequest: cloning address too small\n");
E 12
I 12
						log(LOG_DEBUG, "llc_rtrequest: cloning address too small\n");
E 12
					else {
						Bcopy(sa, gate, gate->sa.sa_len);
						gate->sdl.sdl_alen = 0;
					}
D 13
					return;
E 13
I 13
					break;
E 13
E 9
				}
D 9
			}
E 9
I 9
			if (ifa == 0)
D 12
				log("llc_rtrequest: can't find LL ifaddr for iface\n");
E 12
I 12
				log(LOG_DEBUG, "llc_rtrequest: can't find LL ifaddr for iface\n");
E 12
D 13
			return;
E 13
I 13
			break;
E 17
I 17
D 29
			rt_setgate(rt, rt_key(rt), &blank_dl);
E 29
I 29
			rt_setgate(rt, rt_key(rt),
			    (struct sockaddr *)&blank_dl);
E 29
			return;
E 17
E 13
E 9
		}
I 17
		if (lc != 0)
			return; /* happens on a route change */
E 17
I 9
		/* FALLTHROUGH */
	case RTM_RESOLVE:
		/*
		 * Case 2:  This route may come from cloning, or a manual route
		 * add with a LL address.
		 */
		if (gate->sdl.sdl_family != AF_LINK) {
D 12
			log("llc_rtrequest: got non-link non-gateway route\n");
E 12
I 12
			log(LOG_DEBUG, "llc_rtrequest: got non-link non-gateway route\n");
E 12
D 13
			return;
E 13
I 13
			break;
E 13
		}
D 17
		if (lc != 0)
D 12
			log("llc_rtrequest: losing old rt_llinfo\n");
E 12
I 12
D 16
			log(LOG_DEBUG, "llc_rtrequest: losing old rt_llinfo\n");
E 16
I 16
			return; /* happens on a route change */
E 17
E 16
E 12
		R_Malloc(lc, struct llinfo_llc *, sizeof (*lc));
		rt->rt_llinfo = (caddr_t)lc;
		if (lc == 0) {
D 12
			log("llc_rtrequest: malloc failed\n");
E 12
I 12
			log(LOG_DEBUG, "llc_rtrequest: malloc failed\n");
E 12
D 13
			return;
E 13
I 13
			break;
E 13
		}
		Bzero(lc, sizeof(*lc));
		lc->lc_rt = rt;
		rt->rt_flags |= RTF_LLINFO;
		insque(lc, &llinfo_llc);
		if (gate->sdl.sdl_alen == sizeof(struct esis_req) + addrlen) {
			gate->sdl.sdl_alen -= sizeof(struct esis_req);
			bcopy(addrlen + LLADDR(&gate->sdl),
				  (caddr_t)&lc->lc_er, sizeof(lc->lc_er));
		} else if (gate->sdl.sdl_alen == addrlen)
			lc->lc_flags = (SNPA_ES | SNPA_VALID | SNPA_PERM);
E 9
		break;
	case RTM_DELETE:
D 9
		if (rt->rt_flags & RTF_GATEWAY) {
			if (rt2 = lc->lc_rtgate) {
				if ((lc2 = (struct llinfo_llc *)rt2->rt_llinfo) &&
				    (lc2->lc_rtgate == rt)) {
						rt->rt_use--;
						lc2->lc_rtgate = (lc->lc_next != lc->lc_prev) ?
						   lc->lc_next->lc_rt : 0;
					}
					RTFREE(rt2);
			}
		} else {
			if ((rt2 = lc->lc_rtgate) &&
			    (lc2 == (struct llinfo_llc *)rt2->rt_llinfo)) {
					struct llinfo_llc *head = lc2;
					do {
						rt->rt_use--;
						lc2->lc_rtgate = 0;
						lc2 = lc2->lc_next;
					} while (lc2 != head);
			}
		}
		if (lc->lc_next)
			remque(lc);
E 9
I 9
D 21
		if (lc == 0 || (rt->rt_flags & RTF_CLONING))
E 21
I 21
		if (rt->rt_flags & RTF_CLONING)
			iso_setmcasts(ifp, req);
		if (lc == 0)
E 21
			return;
		remque(lc);
		Free(lc);
		rt->rt_llinfo = 0;
		rt->rt_flags &= ~RTF_LLINFO;
E 9
		break;
I 13
	}
	if (rt->rt_rmx.rmx_mtu == 0) {
			rt->rt_rmx.rmx_mtu = rt->rt_ifp->if_mtu - LLC_SIZE;
E 13
	}
I 21
}
/*
 * FUNCTION:		iso_setmcasts
 *
 * PURPOSE:			Enable/Disable ESIS/ISIS multicast reception on interfaces.
 *
 * NOTES:			This also does a lot of obscure magic;
 */
iso_setmcasts(ifp, req)
	struct	ifnet *ifp;
	int		req;
{
	static char *addrlist[] =
		{ all_es_snpa, all_is_snpa, all_l1is_snpa, all_l2is_snpa, 0};
	struct ifreq ifr;
	register caddr_t *cpp;
	int		doreset = 0;

	bzero((caddr_t)&ifr, sizeof(ifr));
D 22
	for (cpp = (caddr_t *)addrlist; *cpp; cpp+) {
E 22
I 22
	for (cpp = (caddr_t *)addrlist; *cpp; cpp++) {
E 22
		bcopy(*cpp, (caddr_t)ifr.ifr_addr.sa_data, 6);
		if (req == RTM_ADD)
			if (ether_addmulti(&ifr, (struct arpcom *)ifp) == ENETRESET)
				doreset++;
		else
D 24
			if (ether_addmulti(&ifr, (struct arpcom *)ifp) == ENETRESET)
E 24
I 24
			if (ether_delmulti(&ifr, (struct arpcom *)ifp) == ENETRESET)
E 24
				doreset++;
	}
D 24
	if (doreset)
		(*ifp->if_reset)(ifp->if_unit);
E 24
I 24
	if (doreset) {
		if (ifp->if_reset)
			(*ifp->if_reset)(ifp->if_unit);
		else
			printf("iso_setmcasts: %s%d needs reseting to receive iso mcasts\n",
					ifp->if_name, ifp->if_unit);
	}
E 24
E 21
}
/*
E 8
 * FUNCTION:		iso_snparesolve
 *
 * PURPOSE:			Resolve an iso address into snpa address
 *
 * RETURNS:			0 if addr is resolved
 *					errno if addr is unknown
 *
 * SIDE EFFECTS:	
 *
D 8
 * NOTES:			If an entry is found that matches the address, that 
 *					snpa is returned. If no entry is found, but an IS is
 *					known, then the address of the IS is returned. If
 *					neither an address is found that matches or an IS is
 *					known, then the multi-cast address for "all ES" for
 *					this interface is returned.
E 8
I 8
 * NOTES:			Now that we have folded the snpa cache into the routing
 *					table, we know there is no snpa address known for this
 *					destination.  If we know of a default IS, then the address
 *					of the IS is returned.  If no IS is known, then return the
 *					multi-cast address for "all ES" for this interface.
E 8
 *
 *					NB: the last case described above constitutes the
 *					query configuration function 9542, sec 6.5
 *					A mechanism is needed to prevent this function from
 *					being invoked if the system is an IS.
 */
D 2
iso_snparesolve(ifp, dst, snpa, snpa_len)
E 2
I 2
iso_snparesolve(ifp, dest, snpa, snpa_len)
E 2
D 8
struct ifnet 		*ifp;	/* outgoing interface */
D 2
struct sockaddr_iso *dst;	/* destination */
E 2
I 2
struct sockaddr_iso *dest;	/* destination */
E 2
char				*snpa;	/* RESULT: snpa to be used */
int					*snpa_len;	/* RESULT: length of snpa */
E 8
I 8
struct	ifnet *ifp;			/* outgoing interface */
struct	sockaddr_iso *dest;	/* destination */
caddr_t	snpa;				/* RESULT: snpa to be used */
int		*snpa_len;			/* RESULT: length of snpa */
E 8
{
D 8
	extern struct ifnet 	loif;		/* loopback interface */
	struct snpa_cache		*sc;		/* ptr to snpa table entry */
	struct iso_addr			*destiso;	/* destination iso addr */
E 8
I 8
	struct	llinfo_llc *sc;	/* ptr to snpa table entry */
	caddr_t	found_snpa;
	int 	addrlen;
E 8
D 2
	int						s;
E 2

D 2
 	destiso = &dst->siso_addr;
E 2
I 2
D 8
 	destiso = &dest->siso_addr;
E 2

E 8
	/*
	 *	This hack allows us to send esis packets that have the destination snpa
	 *	addresss embedded in the destination nsap address 
	 */
D 2
	if (destiso->isoa_afi == AFI_SNA) {
E 2
I 2
D 8
	if (destiso->isoa_genaddr[0] == AFI_SNA) {
E 8
I 8
	if (dest->siso_data[0] == AFI_SNA) {
E 8
E 2
		/*
		 *	This is a subnetwork address. Return it immediately
		 */
		IFDEBUG(D_SNPA)
			printf("iso_snparesolve: return SN address\n");
		ENDDEBUG
D 8

		*snpa_len = destiso->isoa_len - 1;	/* subtract size of AFI */
D 2
		bcopy((caddr_t) destiso->sna_idi, (caddr_t)snpa, *snpa_len);
E 2
I 2
		bcopy((caddr_t) destiso->isoa_genaddr + 1, (caddr_t)snpa,
			  (unsigned)*snpa_len);
E 2
		return (0);
	}

	IFDEBUG(D_SNPA)
		printf("iso_snparesolve: resolving %s\n", clnp_iso_addrp(destiso));
	ENDDEBUG

E 8
I 8
		addrlen = dest->siso_nlen - 1;	/* subtract size of AFI */
		found_snpa = (caddr_t) dest->siso_data + 1;
E 8
	/* 
D 8
	 *	packet is not for us, check cache for an entry 
E 8
I 8
	 * If we are an IS, we can't do much with the packet;
	 *	Check if we know about an IS.
E 8
	 */
D 2
	s = splimp();
E 2
D 8
	SNPAC_LOOK(sc, destiso);
	if (sc == 0) {			/* not found */
		/* If we are an IS, we can't do much with the packet */
		if (iso_systype == SNPA_IS)
			goto bad;

		/*
		 *	Check if we know about an IS
E 8
I 8
	} else if (iso_systype != SNPA_IS && known_is != 0 &&
				(sc = (struct llinfo_llc *)known_is->rt_llinfo) &&
				 (sc->lc_flags & SNPA_VALID)) {
		register struct sockaddr_dl *sdl =
			(struct sockaddr_dl *)(known_is->rt_gateway);
		found_snpa = LLADDR(sdl);
		addrlen = sdl->sdl_alen;
	} else if (ifp->if_flags & IFF_BROADCAST) {
		/* 
		 *	no IS, no match. Return "all es" multicast address for this
		 *	interface, as per Query Configuration Function (9542 sec 6.5)
		 *
		 *	Note: there is a potential problem here. If the destination
		 *	is on the subnet and it does not respond with a ESH, but
		 *	does send back a TP CC, a connection could be established
		 *	where we always transmit the CLNP packet to "all es"
E 8
		 */
D 8
		if ((known_is) && (known_is->sc_flags & SNPA_VALID)) {
			sc = known_is;
		} else if (ifp->if_flags & IFF_BROADCAST) {
			/* 
			 *	no IS, no match. Return "all es" multicast address for this
			 *	interface, as per Query Configuration Function (9542 sec 6.5)
			 *
			 *	Note: there is a potential problem here. If the destination
			 *	is on the subnet and it does not respond with a ESH, but
			 *	does send back a TP CC, a connection could be established
			 *	where we always transmit the CLNP packet to "all es"
			 */
			sc = &all_es;
		} else {
			goto bad;
		}
	}

	bcopy((caddr_t)sc->sc_snpa, (caddr_t)snpa, sc->sc_len);
	*snpa_len = sc->sc_len;
E 8
I 8
		addrlen = ifp->if_addrlen;
		found_snpa = (caddr_t)all_es_snpa;
	} else
		return (ENETUNREACH);
	bcopy(found_snpa, snpa, *snpa_len = addrlen);
E 8
D 2
	splx(s);
E 2
	return (0);
D 8

bad:
D 2
	splx(s);
E 2
	return(ENETUNREACH);
E 8
}


/*
D 8
 * FUNCTION:		snpac_look
 *
 * PURPOSE:			Look up an entry in the snpa cache
 *
 * RETURNS:			Pointer to snpa_cache structure, or null
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			This is simply SNPAC_LOOK as a procedure.
 */
struct snpa_cache *
snpac_look(isoa)
struct iso_addr *isoa;	/* destination nsap */
{
	struct snpa_cache	*sc;
	int 				s = splimp();

	SNPAC_LOOK(sc, isoa);

	splx(s);
	return(sc);
}

/*
 * FUNCTION:		iso_8208snparesolve
 *
 * PURPOSE:			Find the X.121 address that corresponds to an NSAP addr
 *
 * RETURNS:			0 or unix errno
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			This ought to invoke the 8208 ES-IS function
 */
D 2
iso_8208snparesolve(dst, snpa, snpa_len)
struct sockaddr_iso *dst;	/* destination */
E 2
I 2
iso_8208snparesolve(dest, snpa, snpa_len)
struct sockaddr_iso *dest;	/* destination */
E 2
char				*snpa;	/* RESULT: snpa to be used */
int					*snpa_len;	/* RESULT: length of snpa */
{
	struct snpa_cache		*sc;		/* ptr to snpa table entry */
	struct iso_addr			*destiso;	/* destination iso addr */
	int						s;
	int						err = 0;

D 2
 	destiso = &dst->siso_addr;
E 2
I 2
 	destiso = &dest->siso_addr;
E 2

	s = splimp();
	SNPAC_LOOK(sc, destiso);
	if (sc) {
		bcopy((caddr_t)sc->sc_snpa, (caddr_t)snpa, sc->sc_len);
		*snpa_len = sc->sc_len;
	} else {
		err = ENETUNREACH;
	}
	splx(s);
	return (err);
}

/*
 * FUNCTION:		iso_8208snpaadd
 *
 * PURPOSE:			Add an entry to the snpa cache
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			used by cons
 */
iso_8208snpaadd(ifp, nsap, snpa, snpalen, ht)
struct ifnet		*ifp;		/* interface info is related to */
struct iso_addr		*nsap;		/* nsap to add */
caddr_t				snpa;		/* translation */
int					snpalen;	/* length in bytes */
short				ht;			/* holding time (in seconds) */
{
D 2
	snpac_add(ifp, nsap, snpa, snpalen, SNPA_ES, ht);
E 2
I 2
	snpac_add(ifp, nsap, snpa, snpalen, SNPA_ES, (u_short)ht);
E 2
}

/*
 * FUNCTION:		iso_8208snpadelete
 *
 * PURPOSE:			Delete an entry from the snpa cache
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			used by CONS
 */
iso_8208snpadelete(nsap)
struct iso_addr	*nsap;
{
	struct snpa_cache	*sc = snpac_look(nsap);

	if (sc != NULL)
		snpac_free(sc);
}

/*
 * FUNCTION:		snpac_new
 *
 * PURPOSE:			create a new entry in the iso address to ethernet
 *					address table
 *
 * RETURNS:			pointer to newest entry
 *
 * SIDE EFFECTS:	times out old entries if no new entries are found
 *
 * NOTES:			If the bucket is full, then timeout the oldest entry
 *					(ie. the one with the youngest holding time)
 */
struct snpa_cache *
snpac_new(isoa)
struct iso_addr *isoa;		/* iso address to enter into table */
{
	register struct snpa_cache	*sc;
	register int 				n;
	int							smallest_ht = 1000000;
	struct snpa_cache			*maybe;

	sc = &iso_snpac[SNPAC_HASH(isoa) * SNPAC_BSIZ];
	for (n = 0 ; n < SNPAC_BSIZ ; n++,sc++) {

		IFDEBUG (D_IOCTL)
			printf("snpac_new: sc x%x ", sc);

			if (sc->sc_flags & SNPA_VALID) {
				int i;

				printf("(valid) %s ", clnp_iso_addrp(&sc->sc_nsap));
				for (i=0; i<sc->sc_len; i++)
					printf("%x%c", sc->sc_snpa[i], i < (sc->sc_len-1) ? ':' 
						: '\n');
			} else {
				printf("invalid\n");
			}
		ENDDEBUG

		if (sc->sc_flags & SNPA_VALID) {
			if (sc->sc_ht < smallest_ht) {
				smallest_ht = sc->sc_ht;
				maybe = sc;
			}
		} else {
			return sc; /* found unused slot */
		}
	}
	snpac_free(maybe);
	return maybe;
}
D 2

E 2
/*
E 8
 * FUNCTION:		snpac_free
 *
 * PURPOSE:			free an entry in the iso address map table
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			If there is a route entry associated with cache
 *					entry, then delete that as well
 */
D 8
snpac_free(sc)
register struct snpa_cache *sc;		/* entry to free */
E 8
I 8
snpac_free(lc)
register struct llinfo_llc *lc;		/* entry to free */
E 8
{
D 2
	int s = splimp();
E 2
I 2
D 8
	register struct rtentry *rt;
E 8
I 8
	register struct rtentry *rt = lc->lc_rt;
E 8
	register struct iso_addr *r;
E 2

D 8
	if (known_is == sc) {
D 2
		snpac_rtrequest(SIOCDELRT, &zero_isoa, &known_is->sc_nsap, 
			RTF_DYNAMIC|RTF_GATEWAY);
E 2
		known_is = NULL;
	}
D 2
	if (sc->sc_da.isoa_len > 0) {
		snpac_rtrequest(SIOCDELRT, &sc->sc_da, &known_is->sc_nsap, 
			RTF_DYNAMIC|RTF_GATEWAY);
E 2
I 2
	if (sc->sc_rt) {
		zap_isoaddr(dst, (&(sc->sc_da)));
		rt = rtalloc1((struct sockaddr *)&dst, 0);
		if ((sc->sc_rt == rt) && (rt->rt_flags & RTF_UP)
			&& (rt->rt_flags & (RTF_DYNAMIC | RTF_MODIFIED))) {
E 8
I 8
	if (known_is == rt)
		known_is = 0;
	if (rt && (rt->rt_flags & RTF_UP) &&
		(rt->rt_flags & (RTF_DYNAMIC | RTF_MODIFIED))) {
E 8
			RTFREE(rt);
			rtrequest(RTM_DELETE, rt_key(rt), rt->rt_gateway, rt_mask(rt),
						rt->rt_flags, (struct rtentry **)0);
D 8
		}
E 8
		RTFREE(rt);
E 2
	}
D 8
	bzero((caddr_t)sc, sizeof(struct snpa_cache));
E 8
D 2

	splx(s);
E 2
}

/*
 * FUNCTION:		snpac_add
 *
 * PURPOSE:			Add an entry to the snpa cache
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			If entry already exists, then update holding time.
 */
D 8
snpac_add(ifp, nsap, snpa, snpalen, type, ht)
E 8
I 8
D 9
snpac_add(ifp, nsap, snpa, type, ht)
E 9
I 9
snpac_add(ifp, nsap, snpa, type, ht, nsellength)
E 9
E 8
struct ifnet		*ifp;		/* interface info is related to */
struct iso_addr		*nsap;		/* nsap to add */
caddr_t				snpa;		/* translation */
D 2
int					snpalen;	/* length in bytes */
E 2
I 2
D 8
int					snpalen;	/* translation length */
E 8
E 2
char				type;		/* SNPA_IS or SNPA_ES */
D 2
short				ht;			/* holding time (in seconds) */
E 2
I 2
u_short				ht;			/* holding time (in seconds) */
I 9
int					nsellength;	/* nsaps may differ only in trailing bytes */
E 9
E 2
{
D 8
	struct snpa_cache	*sc;
E 8
I 8
	register struct	llinfo_llc *lc;
D 9
	struct	rtentry *rt;
E 9
I 9
	register struct rtentry *rt;
	struct	rtentry *mrt = 0;
E 9
	register struct	iso_addr *r; /* for zap_isoaddr macro */
	int		snpalen = min(ifp->if_addrlen, MAX_SNPALEN);
D 18
	int		new_entry = 0, index = ifp->if_index;
E 18
I 18
D 19
	int		new_entry = 0, index = ifp->if_index, if_type = ifp->if_type;
E 19
I 19
	int		new_entry = 0, index = ifp->if_index, iftype = ifp->if_type;
E 19
E 18
E 8
D 2
	int					s = splimp();
E 2

I 9
	IFDEBUG(D_SNPA)
		printf("snpac_add(%x, %x, %x, %x, %x, %x)\n",
			ifp, nsap, snpa, type, ht, nsellength);
	ENDDEBUG
E 9
D 8
	SNPAC_LOOK(sc, nsap);
	if (sc == NULL) {
		sc = snpac_new(nsap);
		sc->sc_nsap = *nsap;
E 8
I 8
	zap_isoaddr(dst, nsap);
	rt = rtalloc1(S(dst), 0);
I 9
	IFDEBUG(D_SNPA)
		printf("snpac_add: rtalloc1 returns %x\n", rt);
	ENDDEBUG
E 9
	if (rt == 0) {
I 9
		struct sockaddr *netmask;
		int flags;
		add:
		if (nsellength) {
			netmask = S(msk); flags = RTF_UP;
			snpac_fixdstandmask(nsellength);
		} else {
			netmask = 0; flags = RTF_UP | RTF_HOST;
		}
E 9
		new_entry = 1;
		zap_linkaddr((&gte_dl), snpa, snpalen, index);
I 18
D 19
		gte_dl.sdl_type = if_type;
E 19
I 19
		gte_dl.sdl_type = iftype;
E 19
E 18
D 9
		if (rtrequest(RTM_ADD, S(dst), S(gte_dl), (struct sockaddr *)0,
						RTF_UP | RTF_HOST, &rt) || rt == 0)
E 9
I 9
		if (rtrequest(RTM_ADD, S(dst), S(gte_dl), netmask, flags, &mrt) ||
			mrt == 0)
E 9
			return (0);
I 9
		rt = mrt;
		rt->rt_refcnt--;
E 9
	} else {
		register struct sockaddr_dl *sdl = (struct sockaddr_dl *)rt->rt_gateway;
I 9
		rt->rt_refcnt--;
		if ((rt->rt_flags & RTF_LLINFO) == 0)
			goto add;
		if (nsellength && (rt->rt_flags & RTF_HOST)) {
			if (rt->rt_refcnt == 0) {
				rtrequest(RTM_DELETE, S(dst), (struct sockaddr *)0,
D 29
					(struct sockaddr *)0, 0, (struct rtentry *)0);
E 29
I 29
					(struct sockaddr *)0, 0, (struct rtentry **)0);
E 29
				rt = 0;
				goto add;
			} else {
				static struct iso_addr nsap2; register char *cp;
				nsap2 = *nsap;
				cp = nsap2.isoa_genaddr + nsap->isoa_len - nsellength;
				while (cp < (char *)(1 + &nsap2))
					*cp++ = 0;
				(void) snpac_add(ifp, &nsap2, snpa, type, ht, nsellength);
			}
		}
E 9
		if (sdl->sdl_family != AF_LINK || sdl->sdl_alen == 0) {
			int old_sdl_len = sdl->sdl_len;
D 9
			if (old_sdl_len < sizeof(*sdl))
E 9
I 9
			if (old_sdl_len < sizeof(*sdl)) {
D 12
				log("snpac_add: cant make room for lladdr\n");
E 12
I 12
				log(LOG_DEBUG, "snpac_add: cant make room for lladdr\n");
E 12
E 9
				return (0);
I 9
			}
E 9
			zap_linkaddr(sdl, snpa, snpalen, index);
			sdl->sdl_len = old_sdl_len;
I 18
D 19
			sdl->sdl_type = if_type;
E 19
I 19
			sdl->sdl_type = iftype;
E 19
E 18
			new_entry = 1;
		}
E 8
	}
D 8

	sc->sc_ht = ht;

	sc->sc_len = min(snpalen, MAX_SNPALEN);
D 2
	bcopy(snpa, sc->sc_snpa, sc->sc_len);
E 2
I 2
	bcopy(snpa, (caddr_t)sc->sc_snpa, sc->sc_len);
E 2
	sc->sc_flags = SNPA_VALID | type;
	sc->sc_ifp = ifp;

E 8
I 8
D 9
	lc = (struct llinfo_llc *)rt->rt_llinfo;
	lc->lc_ht = ht;
E 9
I 9
	if ((lc = (struct llinfo_llc *)rt->rt_llinfo) == 0)
		panic("snpac_rtrequest");
D 16
	rt->rt_idle = ht;
E 16
I 16
	rt->rt_rmx.rmx_expire = ht + time.tv_sec;
E 16
E 9
	lc->lc_flags = SNPA_VALID | type;
E 8
D 20
	if (type & SNPA_IS)
E 20
I 20
	if ((type & SNPA_IS) && !(iso_systype & SNPA_IS))
E 20
D 8
		snpac_logdefis(sc);
E 8
I 8
		snpac_logdefis(rt);
I 9
	return (new_entry);
E 9
E 8
D 2

	splx(s);
E 2
}

I 9
D 16
static snpac_fixdstandmask(nsellength)
E 16
I 16
static void
snpac_fixdstandmask(nsellength)
E 16
{
	register char *cp = msk.siso_data, *cplim;

	cplim = cp + (dst.siso_nlen -= nsellength);
	msk.siso_len = cplim - (char *)&msk;
	msk.siso_nlen = 0;
	while (cp < cplim)
		*cp++ = -1;
	while (cp < (char *)msk.siso_pad)
		*cp++ = 0;
	for (cp = dst.siso_data + dst.siso_nlen; cp < (char *)dst.siso_pad; )
		*cp++ = 0;
}

E 9
/*
 * FUNCTION:		snpac_ioctl
 *
D 8
 * PURPOSE:			handle ioctls to change the iso address map
 *
 * RETURNS:			unix error code
 *
 * SIDE EFFECTS:	changes the snpa_cache table declared above.
 *
 * NOTES:			
 */
snpac_ioctl(cmd, data)
int		cmd;		/* ioctl to process */
caddr_t	data;	/* data for the cmd */
{
	register struct snpa_req	*rq = (struct snpa_req *)data;
	register struct snpa_cache	*sc;
	register struct iso_addr	*isoa;
	int							s;
I 2
	char						*type;
E 2

D 2
	/* look up this address in table */
	isoa = &rq->sr_isoa;
E 2
I 2
	switch(cmd) {
		case SIOCSISOMAP: type = "set"; break;
		case SIOCDISOMAP: type = "delete"; break;
		case SIOCGISOMAP: type = "get"; break;
		default: return(snpac_systype(cmd, data));
	}
E 2

	/* sanity check */
	if (rq->sr_len > MAX_SNPALEN)
		return(EINVAL);

	IFDEBUG (D_IOCTL)
		int i;

D 2
		printf("snpac_ioctl: ");
		switch(cmd) {
			case SIOCSISOMAP: printf("set"); break;
			case SIOCDISOMAP: printf("delete"); break;
			case SIOCGISOMAP: printf("get"); break;
		}
		printf(" %s to ", clnp_iso_addrp(isoa));
E 2
I 2
		printf("snpac_ioctl: %s %s to ", type, clnp_iso_addrp(isoa));
E 2
		for (i=0; i<rq->sr_len; i++)
			printf("%x%c", rq->sr_snpa[i], i < (rq->sr_len-1) ? ':' : '\n');
	ENDDEBUG

D 2
	s = splimp();
E 2
I 2
	/* look up this address in table */
	isoa = &rq->sr_isoa;

E 2
	SNPAC_LOOK(sc, isoa);
	if (sc == NULL) {	 /* not found */
		if (cmd != SIOCSISOMAP)
			return(ENXIO);
	}

	switch(cmd) {
		case SIOCSISOMAP:	/* set entry */
D 2
			snpac_add(NULL, isoa, rq->sr_snpa, rq->sr_len, 
				rq->sr_flags & (SNPA_ES|SNPA_IS|SNPA_PERM), rq->sr_ht);
E 2
I 2
			snpac_add((struct ifnet *)NULL, isoa, (caddr_t)rq->sr_snpa,
					  (int)rq->sr_len,
					  (char)(rq->sr_flags & (SNPA_ES|SNPA_IS|SNPA_PERM)),
					  rq->sr_ht);
E 2
			break;
		
		case SIOCDISOMAP:	/* delete entry */
			snpac_free(sc);
			break;
		
		case SIOCGISOMAP:	/* get entry */
D 2
			bcopy((caddr_t)&sc->sc_sr, rq, sizeof(struct snpa_req));
E 2
I 2
			bcopy((caddr_t)&sc->sc_sr, (caddr_t)rq, sizeof(struct snpa_req));
E 2
			break;
	}
D 2
	splx(s);
E 2
	return(0);
}

/*
 * FUNCTION:		iso_tryloopback
 *
 * PURPOSE:			Attempt to use the software loopback interface for pkt
 *
 * RETURNS:			0		if packet was sent successfully
 *					errno	if there was a problem sending the packet
 *							Ie. the return value of looutput
 *					-1 		if software loopback is not appropriate
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
D 2
iso_tryloopback(m, dst)
E 2
I 2
iso_tryloopback(m, dest)
E 2
struct mbuf			*m;		/* pkt */
D 2
struct sockaddr_iso *dst;	/* destination */
E 2
I 2
struct sockaddr_iso *dest;	/* destination */
E 2
{
	struct iso_addr			*destiso;	/* destination iso addr */

D 2
 	destiso = &dst->siso_addr;
E 2
I 2
 	destiso = &dest->siso_addr;
E 2

	if (clnp_ours(destiso)) {
		IFDEBUG(D_SNPA)
			printf("iso_tryloopback: local destination\n"); 
		ENDDEBUG
		if (loif.if_flags & IFF_UP) {
			IFDEBUG(D_SNPA)
				printf("iso_tryloopback: calling looutput\n"); 
			ENDDEBUG
D 2
			return (looutput(&loif, m, (struct sockaddr *)dst));
E 2
I 2
			return (looutput(&loif, m, (struct sockaddr *)dest));
E 2
		}
	}
	return (-1);
}

/*
 * FUNCTION:		snpac_systype
 *
E 8
 * PURPOSE:			Set/Get the system type and esis parameters
 *
 * RETURNS:			0 on success, or unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
D 8
snpac_systype (cmd, data)
E 8
I 8
D 16
snpac_ioctl (cmd, data)
E 16
I 16
snpac_ioctl (so, cmd, data)
struct socket *so;
E 16
E 8
D 28
int		cmd;	/* ioctl to process */
E 28
I 28
u_long	cmd;	/* ioctl to process */
E 28
caddr_t	data;	/* data for the cmd */
{
	register struct systype_req *rq = (struct systype_req *)data;
D 10
	extern short	esis_holding_time, esis_config_time;
E 10

D 9
	IFDEBUG (D_IOCTL)
E 9
I 9
	IFDEBUG(D_IOCTL)
E 9
		if (cmd == SIOCSSTYPE)
D 8
			printf("snpac_systype: cmd set, type x%x, ht %d, ct %d\n",
E 8
I 8
			printf("snpac_ioctl: cmd set, type x%x, ht %d, ct %d\n",
E 8
				rq->sr_type, rq->sr_holdt, rq->sr_configt);
		else
D 8
			printf("snpac_systype: cmd get\n");
E 8
I 8
			printf("snpac_ioctl: cmd get\n");
E 8
	ENDDEBUG

	if (cmd == SIOCSSTYPE) {
D 4
		if (!suser())
E 4
I 4
D 16
		if (suser(u.u_cred, &u.u_acflag))
E 4
			return(EACCES);
E 16
I 16
		if ((so->so_state & SS_PRIV) == 0)
			return (EPERM);
E 16
		if ((rq->sr_type & (SNPA_ES|SNPA_IS)) == (SNPA_ES|SNPA_IS))
			return(EINVAL);
		if (rq->sr_type & SNPA_ES) {
			iso_systype = SNPA_ES;
		} else if (rq->sr_type & SNPA_IS) {
			iso_systype = SNPA_IS;
		} else {
			return(EINVAL);
		}
		esis_holding_time = rq->sr_holdt;
		esis_config_time = rq->sr_configt;
I 10
		if (esis_esconfig_time != rq->sr_esconfigt) {
			untimeout(esis_config, (caddr_t)0);
			esis_esconfig_time = rq->sr_esconfigt;
			esis_config();
		}
E 10
	} else if (cmd == SIOCGSTYPE) {
		rq->sr_type = iso_systype;
		rq->sr_holdt = esis_holding_time;
		rq->sr_configt = esis_config_time;
I 10
		rq->sr_esconfigt = esis_esconfig_time;
E 10
	} else {
D 8
		return(EINVAL);
E 8
I 8
		return (EINVAL);
E 8
	}
D 8
	return(0);
E 8
I 8
	return (0);
E 8
}

/*
 * FUNCTION:		snpac_logdefis
 *
 * PURPOSE:			Mark the IS passed as the default IS
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
snpac_logdefis(sc)
D 2
struct snpa_cache	*sc;
E 2
I 2
D 8
register struct snpa_cache	*sc;
E 8
I 8
register struct rtentry *sc;
E 8
E 2
{
D 2
	if (known_is) {
		snpac_rtrequest(SIOCDELRT, &zero_isoa, &known_is->sc_nsap, 
			RTF_DYNAMIC|RTF_GATEWAY);
E 2
I 2
	register struct iso_addr *r;
I 8
	register struct sockaddr_dl *sdl = (struct sockaddr_dl *)sc->rt_gateway;
E 8
D 20
	register struct rtentry *rt = rtalloc1((struct sockaddr *)&zsi, 0);
E 20
I 20
	register struct rtentry *rt;
E 20
I 8

D 20
	zap_linkaddr((&gte_dl), LLADDR(sdl), sdl->sdl_alen, sdl->sdl_index);
I 18
	gte_dl.sdl_type = sc->rt_ifp->if_type;
E 18
E 8
	if (known_is == 0)
		known_is = sc;
	if (known_is != sc) {
D 8
		if (known_is->sc_rt) {
			rtfree(known_is->sc_rt);
			known_is->sc_rt = 0;
		}
E 8
I 8
		rtfree(known_is);
E 8
		known_is = sc;
E 2
	}
D 2
	known_is = sc;
	snpac_rtrequest(SIOCADDRT, &zero_isoa, &sc->sc_nsap, 
		RTF_DYNAMIC|RTF_GATEWAY);
E 2
I 2
	if (rt == 0) {
D 8
		zap_isoaddr(dst, &(sc->sc_nsap));
		rtrequest(RTM_ADD, S(zsi), S(dst), S(zmk),
						RTF_DYNAMIC|RTF_GATEWAY, &sc->sc_rt);
E 8
I 8
		rtrequest(RTM_ADD, S(zsi), S(gte_dl), S(zmk),
						RTF_DYNAMIC|RTF_GATEWAY|RTF_CLONING, 0);
E 20
I 20
	if (known_is == sc || !(sc->rt_flags & RTF_HOST))
E 20
E 8
		return;
I 20
	if (known_is) {
		RTFREE(known_is);
E 20
	}
I 9
D 20
	rt->rt_refcnt--;
E 9
	if (rt->rt_flags & (RTF_DYNAMIC | RTF_MODIFIED)) {
D 8
		((struct sockaddr_iso *)rt->rt_gateway)->siso_addr = sc->sc_nsap;
		known_is = sc;
		sc->sc_rt = rt;
E 8
I 8
		*((struct sockaddr_dl *)rt->rt_gateway) = gte_dl;
E 20
I 20
	known_is = sc;
	sc->rt_refcnt++;
	rt = rtalloc1((struct sockaddr *)&zsi, 0);
	if (rt == 0)
		rtrequest(RTM_ADD, S(zsi), rt_key(sc), S(zmk),
						RTF_DYNAMIC|RTF_GATEWAY, 0);
	else {
		if ((rt->rt_flags & RTF_DYNAMIC) && 
		    (rt->rt_flags & RTF_GATEWAY) && rt_mask(rt)->sa_len == 0)
			rt_setgate(rt, rt_key(rt), rt_key(sc));
E 20
E 8
	}
E 2
}

/*
 * FUNCTION:		snpac_age
 *
 * PURPOSE:			Time out snpac entries
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			When encountering an entry for the first time, snpac_age
 *					may delete up to SNPAC_AGE too many seconds. Ie.
 *					if the entry is added a moment before snpac_age is
 *					called, the entry will immediately have SNPAC_AGE
 *					seconds taken off the holding time, even though
 *					it has only been held a brief moment.
 *
 *					The proper way to do this is set an expiry timeval
 *					equal to current time + holding time. Then snpac_age
 *					would time out entries where expiry date is older
 *					than the current time.
 */
I 25
void
E 25
snpac_age()
{
D 8
	register struct snpa_cache	*sc;
	register int 				i;
E 8
I 8
D 16
	register struct llinfo_llc	*lc;
E 16
I 16
	register struct	llinfo_llc *lc, *nlc;
	register struct	rtentry *rt;
E 16
E 8

	timeout(snpac_age, (caddr_t)0, SNPAC_AGE * hz);

D 8
	sc = &iso_snpac[0];
	for (i=0; i<SNPAC_SIZE; i++, sc++) {
		if (((sc->sc_flags & SNPA_PERM) == 0) && (sc->sc_flags & SNPA_VALID)) {
			sc->sc_ht -= SNPAC_AGE;
			if (sc->sc_ht > 0)
E 8
I 8
D 16
	for (lc = llinfo_llc.lc_next; lc != & llinfo_llc; lc = lc->lc_next) {
E 16
I 16
	for (lc = llinfo_llc.lc_next; lc != & llinfo_llc; lc = nlc) {
		nlc = lc->lc_next;
E 16
D 20
		if (((lc->lc_flags & SNPA_PERM) == 0) && (lc->lc_flags & SNPA_VALID)) {
E 20
I 20
		if (lc->lc_flags & SNPA_VALID) {
E 20
D 9
			lc->lc_ht -= SNPAC_AGE;
			if (lc->lc_ht > 0)
E 9
I 9
D 16
			lc->lc_rt->rt_idle -= SNPAC_AGE;
			if (lc->lc_rt->rt_idle > 0)
E 9
E 8
				continue;
			else
E 16
I 16
			rt = lc->lc_rt;
			if (rt->rt_rmx.rmx_expire && rt->rt_rmx.rmx_expire < time.tv_sec)
E 16
D 8
				snpac_free(sc);
E 8
I 8
				snpac_free(lc);
I 16
D 20
			else
				continue;
E 20
E 16
E 8
		}
	}
}

/*
 * FUNCTION:		snpac_ownmulti
 *
 * PURPOSE:			Determine if the snpa address is a multicast address
 *					of the same type as the system.
 *
 * RETURNS:			true or false
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Used by interface drivers when not in eavesdrop mode 
 *					as interm kludge until
 *					real multicast addresses can be configured
 */
snpac_ownmulti(snpa, len)
D 8
char	*snpa;
int		len;
E 8
I 8
caddr_t	snpa;
u_int	len;
E 8
{
D 2
	return (((iso_systype & SNPA_ES) && (!bcmp(snpa, all_es.sc_snpa, len)))
		|| ((iso_systype & SNPA_IS) && (!bcmp(snpa, all_is.sc_snpa, len))));
E 2
I 2
	return (((iso_systype & SNPA_ES) &&
D 8
			 (!bcmp((caddr_t)snpa, (caddr_t)all_es.sc_snpa, (unsigned)len))) ||
E 8
I 8
			 (!bcmp(snpa, (caddr_t)all_es_snpa, len))) ||
E 8
			((iso_systype & SNPA_IS) &&
D 8
			 (!bcmp((caddr_t)snpa, (caddr_t)all_is.sc_snpa, (unsigned)len))));
E 8
I 8
			 (!bcmp(snpa, (caddr_t)all_is_snpa, len))));
E 8
E 2
}

/*
 * FUNCTION:		snpac_flushifp
 *
 * PURPOSE:			Flush entries associated with specific ifp
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
snpac_flushifp(ifp)
struct ifnet	*ifp;
{
D 8
	register struct snpa_cache	*sc;
	register int 				i;
E 8
I 8
	register struct llinfo_llc	*lc;
E 8

D 8
	sc = &iso_snpac[0];
	for (i=0; i<SNPAC_SIZE; i++, sc++) {
		if ((sc->sc_ifp == ifp) && (sc->sc_flags & SNPA_VALID)) {
			snpac_free(sc);
		}
E 8
I 8
	for (lc = llinfo_llc.lc_next; lc != & llinfo_llc; lc = lc->lc_next) {
		if (lc->lc_rt->rt_ifp == ifp && (lc->lc_flags & SNPA_VALID))
			snpac_free(lc);
E 8
	}
}

/*
 * FUNCTION:		snpac_rtrequest
 *
 * PURPOSE:			Make a routing request
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			In the future, this should make a request of a user
 *					level routing daemon.
 */
D 2
snpac_rtrequest(req, dst, gateway, flags)
E 2
I 2
snpac_rtrequest(req, host, gateway, netmask, flags, ret_nrt)
E 2
int				req;
D 2
struct iso_addr	*dst;
E 2
I 2
struct iso_addr	*host;
E 2
struct iso_addr	*gateway;
I 2
struct iso_addr	*netmask;
E 2
short			flags;
I 2
struct rtentry	**ret_nrt;
E 2
{
D 2
	struct rtentry	rte;
	struct iso_addr	*isoa;
E 2
I 2
	register struct iso_addr *r;
E 2

	IFDEBUG(D_SNPA)
		printf("snpac_rtrequest: ");
D 2
		if (req == SIOCADDRT)
E 2
I 2
		if (req == RTM_ADD)
E 2
			printf("add");
D 2
		else if (req == SIOCDELRT)
E 2
I 2
		else if (req == RTM_DELETE)
E 2
			printf("delete");
		else 
			printf("unknown command");
D 2
		printf(" dst: %s\n", clnp_iso_addrp(dst));
E 2
I 2
		printf(" dst: %s\n", clnp_iso_addrp(host));
E 2
		printf("\tgateway: %s\n", clnp_iso_addrp(gateway));
	ENDDEBUG

D 2
	bzero((caddr_t)&rte, sizeof(struct rtentry));
	rte.rt_dst.sa_family = rte.rt_gateway.sa_family = AF_ISO;
	isoa = &((struct sockaddr_iso *)&rte.rt_dst)->siso_addr;
	*isoa = *dst;
	isoa = &((struct sockaddr_iso *)&rte.rt_gateway)->siso_addr;
	*isoa = *gateway;
	rte.rt_flags = RTF_UP|flags;
E 2

D 2
	rtrequest(req, &rte);
E 2
I 2
	zap_isoaddr(dst, host);
	zap_isoaddr(gte, gateway);
D 9
	zap_isoaddr(msk, netmask);
E 9
I 9
	if (netmask) {
		zap_isoaddr(msk, netmask);
		msk.siso_nlen = 0;
		msk.siso_len = msk.siso_pad - (u_char *)&msk;
	}
E 9

	rtrequest(req, S(dst), S(gte), (netmask ? S(msk) : (struct sockaddr *)0),
		flags, ret_nrt);
E 2
}

D 2

E 2
/*
 * FUNCTION:		snpac_addrt
 *
 * PURPOSE:			Associate a routing entry with an snpac entry
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			If a cache entry exists for gateway, then
 *					make a routing entry (host, gateway) and associate
 *					with gateway.
 *
 *					If a route already exists and is different, first delete
 *					it.
 *
 *					This could be made more efficient by checking 
 *					the existing route before adding a new one.
 */
D 2
snpac_addrt(host, gateway)
struct iso_addr	*host;
struct iso_addr	*gateway;
E 2
I 2
D 7
snpac_addrt(host, gateway, source, netmask)
struct iso_addr	*host, *gateway, *source, *netmask;
E 7
I 7
snpac_addrt(ifp, host, gateway, netmask)
struct ifnet *ifp;
struct iso_addr	*host, *gateway, *netmask;
E 7
E 2
{
D 2
	struct snpa_cache	*sc;
	int					s;
E 2
I 2
D 8
	register struct snpa_cache	*sc;
E 8
	register struct iso_addr *r;
E 2

D 2
	s = splimp();
E 2
D 8
	SNPAC_LOOK(sc, gateway);
	if (sc != NULL) {
D 2
		snpac_rtrequest(SIOCDELRT, &sc->sc_da, gateway, 
			RTF_DYNAMIC|RTF_GATEWAY);
		snpac_rtrequest(SIOCADDRT, host, gateway, RTF_DYNAMIC|RTF_GATEWAY);
		bcopy(host, &sc->sc_da, sizeof(struct iso_addr));
E 2
I 2
		bcopy((caddr_t)host, (caddr_t)&sc->sc_da, sizeof(struct iso_addr));
		zap_isoaddr(dst, host);
		zap_isoaddr(gte, gateway);
D 7
		zap_isoaddr(src, source);
E 7
		zap_isoaddr(msk, netmask);
		if (netmask) {
D 7
			rtredirect(S(dst), S(gte), S(msk), RTF_DONE, S(src), &sc->sc_rt);
E 7
I 7
			rtredirect(S(dst), S(gte), S(msk), RTF_DONE, S(gte), &sc->sc_rt);
E 7
		} else
			rtredirect(S(dst), S(gte), (struct sockaddr *)0,
D 7
									RTF_DONE | RTF_HOST, S(src), &sc->sc_rt);
E 7
I 7
									RTF_DONE | RTF_HOST, S(gte), &sc->sc_rt);
E 7
E 2
	}
E 8
I 8
	zap_isoaddr(dst, host);
	zap_isoaddr(gte, gateway);
D 9
	zap_isoaddr(msk, netmask);
E 9
	if (netmask) {
I 9
		zap_isoaddr(msk, netmask);
		msk.siso_nlen = 0;
		msk.siso_len = msk.siso_pad - (u_char *)&msk;
E 9
		rtredirect(S(dst), S(gte), S(msk), RTF_DONE, S(gte), 0);
	} else
		rtredirect(S(dst), S(gte), (struct sockaddr *)0,
							RTF_DONE | RTF_HOST, S(gte), 0);
E 8
D 2
	s = splx(s);
E 2
}
D 26
#endif	ISO
E 26
I 26
#endif	/* ISO */
E 26
E 1
