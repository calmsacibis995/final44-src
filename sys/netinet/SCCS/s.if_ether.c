h55024
s 00003/00002/00526
d D 8.2 94/09/26 17:31:01 sklower 55 53
c minor improvements in error messages suggested by R. Stevens
e
s 00001/00001/00527
d R 8.2 94/09/26 16:44:56 sklower 54 53
c improvement suggested by R. Stevens
e
s 00002/00002/00526
d D 8.1 93/06/10 23:03:54 bostic 53 52
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00005/00519
d D 7.28 93/06/04 17:23:31 bostic 52 51
c prototype everything
e
s 00000/00002/00524
d D 7.27 93/01/08 18:42:52 andrew 51 50
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00018/00018/00508
d D 7.26 92/10/11 12:01:48 bostic 50 49
c make kernel includes standard
e
s 00000/00001/00526
d D 7.25 92/07/11 03:23:19 torek 49 48
c delete unused variable mcopy
e
s 00082/00094/00445
d D 7.24 92/07/06 15:08:31 sklower 48 47
c multicast changes from lbl
e
s 00002/00001/00537
d D 7.23 92/06/17 20:25:55 mckusick 47 46
c null pointer bug from Leres
e
s 00000/00002/00538
d D 7.22 92/05/05 17:37:58 sklower 46 45
c since IFF_NOARP doesn't cause the ethernet address to be calculated
c from the IP address any more, it would be insane to ignore arp packets.
e
s 00001/00000/00539
d D 7.21 92/03/15 00:36:10 torek 45 44
c gcc lint
e
s 00003/00002/00536
d D 7.20 92/02/25 12:44:10 sklower 44 43
c don't set cloning flag on proxy arp entries
e
s 00001/00001/00537
d D 7.19 92/01/31 13:02:49 sklower 43 42
c fix arg to arpwhohas to match prototype
e
s 00001/00000/00537
d D 7.18 92/01/30 18:09:30 sklower 42 41
c lint garbage
e
s 00001/00000/00536
d D 7.17 92/01/30 14:10:58 torek 41 40
c lint changes for sparc port (checked in by sklower)
e
s 00002/00002/00534
d D 7.16 91/12/17 16:05:05 sklower 40 39
c enforce cloning bit for route to interface
e
s 00001/00001/00535
d D 7.15 91/10/02 22:43:06 sklower 39 38
c bug pointed out by ralph campbell
e
s 00256/00301/00280
d D 7.14 91/06/25 22:13:55 sklower 38 37
c rewrite to merge arp and routing tables
e
s 00001/00001/00580
d D 7.13 90/10/31 13:56:05 sklower 37 36
c looutput is called with four args for now.
e
s 00001/00011/00580
d D 7.12 90/06/28 21:36:02 bostic 36 35
c new copyright notice
e
s 00006/00005/00585
d D 7.11 90/04/05 11:51:01 sklower 35 34
c if_output wants ptr to rtentry or 0.
e
s 00017/00002/00573
d D 7.10 89/04/22 12:05:58 sklower 34 33
c checkpoint at first working tp4 connection; & before gnodes
e
s 00022/00004/00553
d D 7.9 89/02/17 10:11:12 karels 33 32
c variable length sockaddrs; rename en{_,}* to ether_
e
s 00008/00029/00549
d D 7.8 88/10/12 14:34:59 karels 32 31
c mark state of kernel before variable length sockaddrs (by sklower).
e
s 00010/00005/00568
d D 7.7 88/06/29 17:06:26 bostic 31 30
c install approved copyright notice
e
s 00008/00002/00565
d D 7.6 87/12/07 17:45:03 bostic 30 29
c use Berkeley specific header
e
s 00001/00001/00566
d D 7.5 87/10/30 08:25:31 bostic 29 28
c keep USETRAILERS from SIOCSARP
e
s 00010/00004/00557
d D 7.4 87/10/06 12:10:47 karels 28 25
c don't send trailer replies to IP replies that appear extraneous
c (ps300's loop otherwise!)
e
s 00010/00004/00557
d R 7.4 87/10/06 11:53:41 karels 27 25
c don't send trailer replies to IP replies that appear extraneous
c (ps300's loop otherwise!)
e
s 00006/00002/00529
d D 7.1.1.1 87/02/27 16:07:13 karels 26 23
c minimal fixes to update 4.3 distribution
e
s 00010/00005/00551
d D 7.3 87/01/10 16:37:49 karels 25 24
c use the right type for mask replies!
e
s 00033/00008/00523
d D 7.2 86/12/16 16:16:14 karels 24 23
c block reentrance of arpinput/arptnew with splimp;
c larger tables for gateway (shouldn't use 2-dimensional array!);
c use loopback even if not up yet, for configuration at boot time
c when primary interface doesn't hear itself talk.
e
s 00001/00001/00530
d D 7.1 86/06/05 00:24:24 mckusick 23 22
c 4.3BSD release version
e
s 00001/00001/00530
d D 6.18 86/03/04 13:53:05 karels 22 21
c lint
e
s 00002/00002/00529
d D 6.17 86/02/23 23:23:13 karels 21 20
c lint
e
s 00015/00010/00516
d D 6.16 86/02/18 09:48:26 karels 20 19
c translate my address if necessary (used to work because
c wwe put ourselves into the table when addressed)
e
s 00001/00001/00525
d D 6.15 86/02/12 16:45:16 karels 19 18
c use most recent address rather than least recent (possible
c robustness/security problem)
e
s 00171/00063/00355
d D 6.14 86/01/13 16:52:01 karels 18 17
c separate ARP header from IP-specific portion; break out IP
c portion of the input code; add trailer negotiation
e
s 00005/00003/00413
d D 6.13 85/09/16 22:41:56 karels 17 16
c more buckets; adjust input packets for presence of interface pointer;
c fix logic error if all entries in a bucket are new
e
s 00000/00001/00416
d D 6.12 85/08/26 09:01:49 walsh 16 15
c fix lint error
e
s 00001/00016/00416
d D 6.11 85/08/22 09:37:09 walsh 15 14
c removed old 3 bytes ethernet<->IP address mapping scheme based on oldmap.
e
s 00007/00001/00425
d D 6.10 85/06/08 12:36:22 mckusick 14 13
c Add copyright
e
s 00008/00008/00418
d D 6.9 85/04/24 22:54:37 karels 13 12
c correct the fix for uninitialized variable after dup IP address
e
s 00053/00035/00373
d D 6.8 85/04/16 09:55:59 karels 12 11
c purge struct ether_addr (not portable)
e
s 00013/00013/00395
d D 6.7 85/03/18 17:15:42 karels 11 10
c move net address to protocol layer; keep a copy of IP address
c in arpcom; ETHERPUP_xxTYPE => ETHERTYPE_xx
e
s 00012/00012/00396
d D 6.6 84/08/29 15:35:35 bloom 10 9
c Include file changes.  No more ../h
e
s 00006/00001/00402
d D 6.5 84/07/08 15:39:11 sam 9 8
c checked in for karels; don't return looutput status as mbuf has already 
c been freed (corrects lost mbuf problem)
e
s 00142/00130/00261
d D 6.4 84/03/22 15:11:22 karels 8 7
c new version of ARP (from sun); allows permanent, "published" entries
e
s 00001/00001/00390
d D 6.3 83/12/15 15:27:43 karels 7 6
c len of arp packet doesn't include ethernet header
e
s 00020/00006/00371
d D 6.2 83/08/28 00:35:51 sam 6 4
c insert IFF_NOARP flag and make old address mapping range a 
c patchable constant -- will this keep those cretins quiet?
e
s 00015/00006/00371
d R 6.2 83/08/28 00:21:43 sam 5 4
c listen to IFF_NOARP to silence all those cretins
e
s 00000/00000/00377
d D 6.1 83/07/29 07:10:57 sam 4 3
c 4.2 distribution
e
s 00005/00002/00372
d D 4.3 83/06/13 23:03:10 sam 3 2
c lint
e
s 00034/00022/00340
d D 4.2 83/05/27 13:45:48 sam 2 1
c lint
e
s 00362/00000/00000
d D 4.1 83/03/15 13:19:18 sam 1 0
c date and time created 83/03/15 13:19:18 by sam
e
u
U
f b 
t
T
I 1
D 14
/*	%M%	%I%	%E%	*/
E 14
I 14
/*
D 23
 * Copyright (c) 1982 Regents of the University of California.
E 23
I 23
D 32
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 32
I 32
D 53
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 32
E 23
D 30
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 30
I 30
 * All rights reserved.
E 53
I 53
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 53
 *
D 36
 * Redistribution and use in source and binary forms are permitted
D 31
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 31
I 31
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
E 36
I 36
 * %sccs.include.redist.c%
E 36
E 31
E 30
 *
 *	%W% (Berkeley) %G%
 */
E 14

/*
 * Ethernet address resolution protocol.
I 24
 * TODO:
D 40
 *	run at splnet (add ARP protocol intr.)
 *	link entries onto hash chains, keep free list
E 40
 *	add "inuse/lock" bit (or ref. count) along with valid bit
E 24
 */

D 10
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/time.h"
#include "../h/kernel.h"
I 2
#include "../h/errno.h"
I 8
#include "../h/ioctl.h"
E 10
I 10
D 50
#include "param.h"
#include "systm.h"
I 32
#include "malloc.h"
E 32
#include "mbuf.h"
#include "socket.h"
#include "time.h"
#include "kernel.h"
#include "errno.h"
#include "ioctl.h"
I 18
#include "syslog.h"
E 50
I 50
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>
E 50
E 18
E 10
E 8
E 2

D 50
#include "../net/if.h"
I 38
#include "../net/if_dl.h"
#include "../net/route.h"
E 50
I 50
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
E 50

E 38
D 10
#include "../netinet/in.h"
I 8
#include "../netinet/in_systm.h"
#include "../netinet/ip.h"
E 8
#include "../netinet/if_ether.h"
E 10
I 10
D 50
#include "in.h"
#include "in_systm.h"
I 34
#include "in_var.h"
E 34
#include "ip.h"
#include "if_ether.h"
E 50
I 50
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
E 50
E 10

I 24
D 38
#ifdef GATEWAY
#define	ARPTAB_BSIZ	16		/* bucket size */
#define	ARPTAB_NB	37		/* number of buckets */
#else
E 24
D 8

/*
 * Internet to ethernet address resolution table.
 */
struct	arptab {
	struct	in_addr at_iaddr;	/* internet address */
	u_char	at_enaddr[6];		/* ethernet address */
	struct	mbuf *at_hold;		/* last packet until resolved/timeout */
	u_char	at_timer;		/* minutes since last reference */
	u_char	at_flags;		/* flags */
};
/* at_flags field values */
#define	ATF_INUSE	1		/* entry in use */
#define ATF_COM		2		/* completed entry (enaddr valid) */

E 8
D 17
#define	ARPTAB_BSIZ	5		/* bucket size */
E 17
I 17
#define	ARPTAB_BSIZ	9		/* bucket size */
E 17
#define	ARPTAB_NB	19		/* number of buckets */
I 24
#endif
E 24
#define	ARPTAB_SIZE	(ARPTAB_BSIZ * ARPTAB_NB)
struct	arptab arptab[ARPTAB_SIZE];
I 8
int	arptab_size = ARPTAB_SIZE;	/* for arp command */
E 38
I 38
#define SIN(s) ((struct sockaddr_in *)s)
#define SDL(s) ((struct sockaddr_dl *)s)
#define SRP(s) ((struct sockaddr_inarp *)s)
E 38
E 8

I 18
/*
 * ARP trailer negotiation.  Trailer protocol is not IP specific,
 * but ARP request/response use IP addresses.
 */
#define ETHERTYPE_IPTRAILERS ETHERTYPE_TRAIL

E 18
D 38
#define	ARPTAB_HASH(a) \
D 18
	((short)((((a) >> 16) ^ (a)) & 0x7fff) % ARPTAB_NB)
E 18
I 18
	((u_long)(a) % ARPTAB_NB)
E 38
E 18

D 38
#define	ARPTAB_LOOK(at,addr) { \
	register n; \
	at = &arptab[ARPTAB_HASH(addr) * ARPTAB_BSIZ]; \
	for (n = 0 ; n < ARPTAB_BSIZ ; n++,at++) \
		if (at->at_iaddr.s_addr == addr) \
			break; \
	if (n >= ARPTAB_BSIZ) \
D 18
		at = 0; }
E 18
I 18
		at = 0; \
}
E 18

E 38
D 8
struct	arpcom *arpcom;		/* chain of active ether interfaces */
E 8
D 18
int	arpt_age;		/* aging timer */

E 18
/* timer values */
D 38
#define	ARPT_AGE	(60*1)	/* aging timer, 1 min. */
#define	ARPT_KILLC	20	/* kill completed entry in 20 mins. */
#define	ARPT_KILLI	3	/* kill incomplete entry in 3 minutes */
E 38
I 38
int	arpt_prune = (5*60*1);	/* walk list every 5 minutes */
int	arpt_keep = (20*60);	/* once resolved, good for 20 more minutes */
int	arpt_down = 20;		/* once declared down, don't send for 20 secs */
D 48
#define RTF_USETRAILERS	RTF_PROTO1
#define rt_expire rt_rmx.rmx_expire
E 48
I 48
#define	rt_expire rt_rmx.rmx_expire
E 48
E 38

D 8
u_char	etherbroadcastaddr[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
E 8
I 8
D 12
struct ether_addr etherbroadcastaddr = {{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }};
E 12
I 12
D 32
u_char	etherbroadcastaddr[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
E 32
E 12
E 8
D 48
extern struct ifnet loif;
I 38
extern struct timeval time;
struct llinfo_arp *arplookup(), llinfo_arp = {&llinfo_arp, &llinfo_arp};
struct ifqueue arpintrq = {0, 0, 0, 50};
E 48
I 48
static	void arprequest __P((struct arpcom *, u_long *, u_long *, u_char *));
static	void arptfree __P((struct llinfo_arp *));
I 52
static	void arptimer __P((void *));
E 52
static	struct llinfo_arp *arplookup __P((u_long, int, int));
D 52
static	void arpcatchme __P(());
E 52
I 52
static	void in_arpinput __P((struct mbuf *));
E 52

extern	struct ifnet loif;
extern	struct timeval time;
struct	llinfo_arp llinfo_arp = {&llinfo_arp, &llinfo_arp};
struct	ifqueue arpintrq = {0, 0, 0, 50};
E 48
int	arp_inuse, arp_allocated, arp_intimer;
int	arp_maxtries = 5;
int	useloopback = 1;	/* use loopback interface for local traffic */
int	arpinit_done = 0;
E 38

D 6
#define	OLDMAP	1		/* if LNA > 1023 use old 3COM mapping */
E 6
I 6
/*
D 15
 * Local addresses in the range oldmap to infinity are
 * mapped according to the old mapping scheme.  That is,
 * mapping of Internet to Ethernet addresses is performed
 * by taking the high three bytes of the network interface's
 * address and the low three bytes of the local address part.
 * This only allows boards from the same manufacturer to
 * communicate unless the on-board address is overridden
 * (not possible in many manufacture's hardware).
 *
 * NB: setting oldmap to zero completely disables ARP
 *     (i.e. identical to setting IFF_NOARP with an ioctl).
 */
int	oldmap = 1024;
E 6

/*
E 15
D 8
 * Attach an ethernet interface to the list "arpcom" where
 * arptimer() can find it.  If first time 
 * initialization, start arptimer().
 */
arpattach(ac)
	register struct arpcom *ac;
{
	register struct arpcom *acp;

	for (acp = arpcom; acp != (struct arpcom *)0; acp = acp->ac_ac)
		if (acp == ac)		/* if already on list */
			return;
	ac->ac_ac = arpcom;
	arpcom = ac;
	if (arpcom->ac_ac == 0)		/* very first time */
		arptimer();
}

/*
E 8
D 38
 * Timeout routine.  Age arp_tab entries once a minute.
E 38
I 38
 * Timeout routine.  Age arp_tab entries periodically.
E 38
 */
I 48
D 52
void
E 48
arptimer()
E 52
I 52
/* ARGSUSED */
static void
arptimer(ignored_arg)
	void *ignored_arg;
E 52
{
D 2
	register struct arpcom *ac;
E 2
D 38
	register struct arptab *at;
	register i;
E 38
I 38
	int s = splnet();
	register struct llinfo_arp *la = llinfo_arp.la_next;
E 38

D 2
	timeout(arptimer, 0, hz);
E 2
I 2
D 18
	timeout(arptimer, (caddr_t)0, hz);
E 2
D 8
#ifdef notdef
	if (++arpt_sanity > ARPT_SANITY) {
I 2
		register struct arpcom *ac;

E 2
		/*
		 * Randomize sanity timer based on my host address.
		 * Ask who has my own address;  if someone else replies,
		 * then they are impersonating me.
		 */
		arpt_sanity = arpcom->ac_enaddr[5] & 0x3f;
		for (ac = arpcom; ac != (struct arpcom *)-1; ac = ac->ac_ac)
			arpwhohas(ac, &((struct sockaddr_in *)
			    &ac->ac_if.if_addr)->sin_addr);
	}
#endif
E 8
	if (++arpt_age > ARPT_AGE) {
		arpt_age = 0;
		at = &arptab[0];
		for (i = 0; i < ARPTAB_SIZE; i++, at++) {
D 8
			if (at->at_flags == 0)
E 8
I 8
			if (at->at_flags == 0 || (at->at_flags & ATF_PERM))
E 8
				continue;
			if (++at->at_timer < ((at->at_flags&ATF_COM) ?
			    ARPT_KILLC : ARPT_KILLI))
				continue;
			/* timer has expired, clear entry */
			arptfree(at);
		}
E 18
I 18
D 38
	timeout(arptimer, (caddr_t)0, ARPT_AGE * hz);
	at = &arptab[0];
	for (i = 0; i < ARPTAB_SIZE; i++, at++) {
		if (at->at_flags == 0 || (at->at_flags & ATF_PERM))
			continue;
		if (++at->at_timer < ((at->at_flags&ATF_COM) ?
		    ARPT_KILLC : ARPT_KILLI))
			continue;
		/* timer has expired, clear entry */
		arptfree(at);
E 38
I 38
	timeout(arptimer, (caddr_t)0, arpt_prune * hz);
	while (la != &llinfo_arp) {
		register struct rtentry *rt = la->la_rt;
		la = la->la_next;
		if (rt->rt_expire && rt->rt_expire <= time.tv_sec)
			arptfree(la->la_prev); /* timer has expired, clear */
E 38
E 18
	}
I 38
	splx(s);
E 38
}

/*
I 38
D 48
 * Parallel to llc_rtrequest. 
E 48
I 48
 * Parallel to llc_rtrequest.
E 48
 */
I 48
void
E 48
arp_rtrequest(req, rt, sa)
	int req;
	register struct rtentry *rt;
	struct sockaddr *sa;
{
	register struct sockaddr *gate = rt->rt_gateway;
	register struct llinfo_arp *la = (struct llinfo_arp *)rt->rt_llinfo;
	static struct sockaddr_dl null_sdl = {sizeof(null_sdl), AF_LINK};

	if (!arpinit_done) {
		arpinit_done = 1;
		timeout(arptimer, (caddr_t)0, hz);
	}
	if (rt->rt_flags & RTF_GATEWAY)
		return;
	switch (req) {
I 48

E 48
	case RTM_ADD:
D 48
	case RTM_RESOLVE:
E 48
I 48
		/*
		 * XXX: If this is a manually added route to interface
		 * such as older version of routed or gated might provide,
		 * restore cloning bit.
		 */
E 48
I 40
D 44
		if ((rt->rt_flags & RTF_HOST) == 0) /* Route to IF? XXX*/
			rt->rt_flags |= RTF_CLONING;
E 44
I 44
		if ((rt->rt_flags & RTF_HOST) == 0 &&
		    SIN(rt_mask(rt))->sin_addr.s_addr != 0xffffffff)
D 48
			rt->rt_flags |= RTF_CLONING; /* Route to IF? XXX*/
E 48
I 48
			rt->rt_flags |= RTF_CLONING;
E 48
E 44
E 40
		if (rt->rt_flags & RTF_CLONING) {
			/*
			 * Case 1: This route should come from a route to iface.
			 */
D 52
			rt_setgate(rt, rt_key(rt), &null_sdl);
E 52
I 52
			rt_setgate(rt, rt_key(rt),
					(struct sockaddr *)&null_sdl);
E 52
			gate = rt->rt_gateway;
			SDL(gate)->sdl_type = rt->rt_ifp->if_type;
			SDL(gate)->sdl_index = rt->rt_ifp->if_index;
			rt->rt_expire = time.tv_sec;
			break;
		}
I 48
		/* Announce a new entry if requested. */
		if (rt->rt_flags & RTF_ANNOUNCE)
			arprequest((struct arpcom *)rt->rt_ifp,
			    &SIN(rt_key(rt))->sin_addr.s_addr,
			    &SIN(rt_key(rt))->sin_addr.s_addr,
			    (u_char *)LLADDR(SDL(gate)));
		/*FALLTHROUGH*/
	case RTM_RESOLVE:
E 48
		if (gate->sa_family != AF_LINK ||
		    gate->sa_len < sizeof(null_sdl)) {
			log(LOG_DEBUG, "arp_rtrequest: bad gateway value");
			break;
		}
		SDL(gate)->sdl_type = rt->rt_ifp->if_type;
		SDL(gate)->sdl_index = rt->rt_ifp->if_index;
		if (la != 0)
			break; /* This happens on a route change */
		/*
		 * Case 2:  This route may come from cloning, or a manual route
		 * add with a LL address.
		 */
		R_Malloc(la, struct llinfo_arp *, sizeof(*la));
		rt->rt_llinfo = (caddr_t)la;
		if (la == 0) {
			log(LOG_DEBUG, "arp_rtrequest: malloc failed\n");
			break;
		}
		arp_inuse++, arp_allocated++;
		Bzero(la, sizeof(*la));
		la->la_rt = rt;
		rt->rt_flags |= RTF_LLINFO;
		insque(la, &llinfo_arp);
		if (SIN(rt_key(rt))->sin_addr.s_addr ==
		    (IA_SIN(rt->rt_ifa))->sin_addr.s_addr) {
		    /*
		     * This test used to be
		     *	if (loif.if_flags & IFF_UP)
		     * It allowed local traffic to be forced
		     * through the hardware by configuring the loopback down.
		     * However, it causes problems during network configuration
		     * for boards that can't receive packets they send.
		     * It is now necessary to clear "useloopback" and remove
		     * the route to force traffic out to the hardware.
		     */
			rt->rt_expire = 0;
			Bcopy(((struct arpcom *)rt->rt_ifp)->ac_enaddr,
				LLADDR(SDL(gate)), SDL(gate)->sdl_alen = 6);
			if (useloopback)
				rt->rt_ifp = &loif;
D 48
				
E 48
I 48

E 48
		}
		break;

	case RTM_DELETE:
		if (la == 0)
			break;
		arp_inuse--;
		remque(la);
		rt->rt_llinfo = 0;
		rt->rt_flags &= ~RTF_LLINFO;
		if (la->la_hold)
			m_freem(la->la_hold);
		Free((caddr_t)la);
	}
}

/*
E 38
 * Broadcast an ARP packet, asking who has addr on interface ac.
 */
I 42
void
E 42
arpwhohas(ac, addr)
	register struct arpcom *ac;
D 38
	struct in_addr *addr;
E 38
I 38
D 43
	struct inaddr *addr;
E 43
I 43
D 48
	struct in_addr *addr;
E 48
I 48
	register struct in_addr *addr;
E 48
E 43
E 38
{
I 48
	arprequest(ac, &ac->ac_ipaddr.s_addr, &addr->s_addr, ac->ac_enaddr);
}

/*
 * Broadcast an ARP request. Caller specifies:
 *	- arp header source ip address
 *	- arp header target ip address
 *	- arp header source ethernet address
 */
static void
arprequest(ac, sip, tip, enaddr)
	register struct arpcom *ac;
	register u_long *sip, *tip;
	register u_char *enaddr;
{
E 48
	register struct mbuf *m;
	register struct ether_header *eh;
	register struct ether_arp *ea;
	struct sockaddr sa;

D 32
	if ((m = m_get(M_DONTWAIT, MT_DATA)) == NULL)
E 32
I 32
	if ((m = m_gethdr(M_DONTWAIT, MT_DATA)) == NULL)
E 32
D 2
		return (1);
E 2
I 2
D 3
		return (ENOBUFS);
E 3
I 3
D 8
		return;
E 8
I 8
D 21
		return (1);
E 21
I 21
		return;
E 21
E 8
E 3
E 2
D 7
	m->m_len = sizeof *ea + sizeof *eh;
E 7
I 7
D 32
	m->m_len = sizeof *ea;
E 7
	m->m_off = MMAXOFF - m->m_len;
E 32
I 32
	m->m_len = sizeof(*ea);
	m->m_pkthdr.len = sizeof(*ea);
	MH_ALIGN(m, sizeof(*ea));
E 32
	ea = mtod(m, struct ether_arp *);
	eh = (struct ether_header *)sa.sa_data;
D 2
	bzero((caddr_t)ea, sizeof *ea);
	bcopy(etherbroadcastaddr, eh->ether_dhost, sizeof etherbroadcastaddr);
E 2
I 2
	bzero((caddr_t)ea, sizeof (*ea));
D 8
	bcopy((caddr_t)etherbroadcastaddr, (caddr_t)eh->ether_dhost,
	   sizeof (etherbroadcastaddr));
E 8
I 8
D 12
	eh->ether_dhost = etherbroadcastaddr;
E 12
I 12
	bcopy((caddr_t)etherbroadcastaddr, (caddr_t)eh->ether_dhost,
	    sizeof(eh->ether_dhost));
E 12
E 8
E 2
D 11
	eh->ether_type = ETHERPUP_ARPTYPE;	/* if_output will swap */
E 11
I 11
	eh->ether_type = ETHERTYPE_ARP;		/* if_output will swap */
E 11
	ea->arp_hrd = htons(ARPHRD_ETHER);
D 11
	ea->arp_pro = htons(ETHERPUP_IPTYPE);
E 11
I 11
	ea->arp_pro = htons(ETHERTYPE_IP);
E 11
D 8
	ea->arp_hln = sizeof ea->arp_sha;	/* hardware address length */
	ea->arp_pln = sizeof ea->arp_spa;	/* protocol address length */
E 8
I 8
D 12
	ea->arp_hln = sizeof arp_sha(ea);	/* hardware address length */
	ea->arp_pln = sizeof arp_spa(ea);	/* protocol address length */
E 12
I 12
	ea->arp_hln = sizeof(ea->arp_sha);	/* hardware address length */
	ea->arp_pln = sizeof(ea->arp_spa);	/* protocol address length */
E 12
E 8
	ea->arp_op = htons(ARPOP_REQUEST);
D 2
	bcopy(ac->ac_enaddr, ea->arp_sha, sizeof ea->arp_sha);
E 2
I 2
D 8
	bcopy((caddr_t)ac->ac_enaddr, (caddr_t)ea->arp_sha,
	   sizeof (ea->arp_sha));
E 2
	bcopy((caddr_t)&((struct sockaddr_in *)&ac->ac_if.if_addr)->sin_addr,
D 2
	    ea->arp_spa, sizeof ea->arp_spa);
	bcopy((caddr_t)addr, ea->arp_tpa, sizeof ea->arp_tpa);
E 2
I 2
	   (caddr_t)ea->arp_spa, sizeof (ea->arp_spa));
	bcopy((caddr_t)addr, (caddr_t)ea->arp_tpa, sizeof (ea->arp_tpa));
E 8
I 8
D 12
	arp_sha(ea) = ac->ac_enaddr;
D 11
	arp_spa(ea) = ((struct sockaddr_in *)&ac->ac_if.if_addr)->sin_addr;
E 11
I 11
	arp_spa(ea) = ac->ac_ipaddr;
E 11
	arp_tpa(ea) = *addr;
E 12
I 12
D 48
	bcopy((caddr_t)ac->ac_enaddr, (caddr_t)ea->arp_sha,
	   sizeof(ea->arp_sha));
	bcopy((caddr_t)&ac->ac_ipaddr, (caddr_t)ea->arp_spa,
	   sizeof(ea->arp_spa));
	bcopy((caddr_t)addr, (caddr_t)ea->arp_tpa, sizeof(ea->arp_tpa));
E 48
I 48
	bcopy((caddr_t)enaddr, (caddr_t)ea->arp_sha, sizeof(ea->arp_sha));
	bcopy((caddr_t)sip, (caddr_t)ea->arp_spa, sizeof(ea->arp_spa));
	bcopy((caddr_t)tip, (caddr_t)ea->arp_tpa, sizeof(ea->arp_tpa));
E 48
E 12
E 8
E 2
	sa.sa_family = AF_UNSPEC;
I 33
	sa.sa_len = sizeof(sa);
E 33
D 3
	return ((*ac->ac_if.if_output)(&ac->ac_if, m, &sa));
E 3
I 3
D 8
	(void) (*ac->ac_if.if_output)(&ac->ac_if, m, &sa);
E 8
I 8
D 21
	return ((*ac->ac_if.if_output)(&ac->ac_if, m, &sa));
E 21
I 21
D 35
	(*ac->ac_if.if_output)(&ac->ac_if, m, &sa);
E 35
I 35
	(*ac->ac_if.if_output)(&ac->ac_if, m, &sa, (struct rtentry *)0);
E 35
E 21
E 8
E 3
}

I 26
int	useloopback = 1;	/* use loopback interface for local traffic */

E 26
I 24
D 38
int	useloopback = 1;	/* use loopback interface for local traffic */

E 38
E 24
/*
D 48
 * Resolve an IP address into an ethernet address.  If success, 
E 48
I 48
 * Resolve an IP address into an ethernet address.  If success,
E 48
D 18
 * desten is filled in and 1 is returned.  If there is no entry
 * in arptab, set one up and broadcast a request 
 * for the IP address;  return 0.  Hold onto this mbuf and 
 * resend it once the address is finally resolved.
E 18
I 18
 * desten is filled in.  If there is no entry in arptab,
 * set one up and broadcast a request for the IP address.
 * Hold onto this mbuf and resend it once the address
 * is finally resolved.  A return value of 1 indicates
 * that desten has been filled in and the packet should be sent
 * normally; a 0 return indicates that the packet has been
 * taken over here, either now or for later transmission.
E 18
D 38
 *
 * We do some (conservative) locking here at splimp, since
 * arptab is also altered from input interrupt service (ecintr/ilintr
D 11
 * calls arpinput when ETHERPUP_ARPTYPE packets come in).
E 11
I 11
 * calls arpinput when ETHERTYPE_ARP packets come in).
E 38
E 11
 */
D 18
arpresolve(ac, m, destip, desten)
E 18
I 18
D 38
arpresolve(ac, m, destip, desten, usetrailers)
E 38
I 38
D 48
arpresolve(ac, rt, m, dst, desten, usetrailers)
E 48
I 48
int
arpresolve(ac, rt, m, dst, desten)
E 48
E 38
E 18
	register struct arpcom *ac;
I 38
	register struct rtentry *rt;
E 38
	struct mbuf *m;
D 38
	register struct in_addr *destip;
E 38
I 38
	register struct sockaddr *dst;
E 38
D 8
	register u_char *desten;
E 8
I 8
D 12
	register struct ether_addr *desten;
E 12
I 12
	register u_char *desten;
I 18
D 48
	int *usetrailers;
E 48
E 18
E 12
E 8
{
D 38
	register struct arptab *at;
I 6
D 24
	register struct ifnet *ifp;
E 24
I 8
D 16
	register int i;
E 16
E 8
E 6
D 2
	register i;
E 2
	struct sockaddr_in sin;
E 38
I 38
	register struct llinfo_arp *la;
E 38
I 34
D 48
	register struct in_ifaddr *ia;
E 48
E 34
D 24
	int s, lna;
E 24
I 24
D 38
	u_long lna;
	int s;
E 38
I 38
	struct sockaddr_dl *sdl;
E 38
E 24

I 18
D 48
	*usetrailers = 0;
E 48
E 18
D 11
	lna = in_lnaof(*destip);
	if (lna == INADDR_ANY) {	/* broadcast address */
E 11
I 11
D 32
	if (in_broadcast(*destip)) {	/* broadcast address */
E 32
I 32
	if (m->m_flags & M_BCAST) {	/* broadcast */
E 32
E 11
D 2
		bcopy(etherbroadcastaddr, desten, sizeof etherbroadcastaddr);
E 2
I 2
D 8
		bcopy((caddr_t)etherbroadcastaddr, (caddr_t)desten,
		   sizeof (etherbroadcastaddr));
E 8
I 8
D 12
		*desten = etherbroadcastaddr;
E 12
I 12
		bcopy((caddr_t)etherbroadcastaddr, (caddr_t)desten,
		    sizeof(etherbroadcastaddr));
E 12
E 8
E 2
		return (1);
	}
I 48
D 51
#ifdef MULTICAST
E 51
	if (m->m_flags & M_MCAST) {	/* multicast */
		ETHER_MAP_IP_MULTICAST(&SIN(dst)->sin_addr, desten);
		return(1);
	}
D 51
#endif
E 51
E 48
I 11
D 38
	lna = in_lnaof(*destip);
E 11
D 6
	if (destip->s_addr == ((struct sockaddr_in *)&ac->ac_if.if_addr)->
	    sin_addr.s_addr) {			/* if for us, use lo driver */
E 6
I 6
D 24
	ifp = &ac->ac_if;
E 24
D 20
	/* if for us, then use software loopback driver */
D 11
	if (destip->s_addr ==
D 8
	    ((struct sockaddr_in *)&ifp->if_addr)-> sin_addr.s_addr) {
E 8
I 8
	    ((struct sockaddr_in *)&ifp->if_addr)-> sin_addr.s_addr &&
E 11
I 11
	if (destip->s_addr == ac->ac_ipaddr.s_addr &&
E 11
	    (loif.if_flags & IFF_UP)) {
E 8
E 6
		sin.sin_family = AF_INET;
		sin.sin_addr = *destip;
D 2
		looutput(&loif, m, &sin);
		return (0);
E 2
I 2
D 9
		return (looutput(&loif, m, (struct sockaddr *)&sin));
E 9
I 9
		(void) looutput(&loif, m, (struct sockaddr *)&sin);
		/*
D 18
		 * We really don't want to indicate failure,
		 * but the packet has already been sent and freed.
E 18
I 18
		 * The packet has already been sent and freed.
E 18
		 */
		return (0);
E 20
I 20
	/* if for us, use software loopback driver if up */
D 34
	if (destip->s_addr == ac->ac_ipaddr.s_addr) {
E 34
I 34
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
	    if ((ia->ia_ifp == &ac->ac_if) &&
		(destip->s_addr == ia->ia_addr.sin_addr.s_addr)) {
E 34
D 24
D 26
		if (loif.if_flags & IFF_UP) {
E 26
I 26
		if (useloopback) {
E 26
E 24
I 24
		/*
		 * This test used to be
		 *	if (loif.if_flags & IFF_UP)
		 * It allowed local traffic to be forced
		 * through the hardware by configuring the loopback down.
		 * However, it causes problems during network configuration
		 * for boards that can't receive packets they send.
		 * It is now necessary to clear "useloopback"
		 * to force traffic out to the hardware.
		 */
		if (useloopback) {
E 24
			sin.sin_family = AF_INET;
			sin.sin_addr = *destip;
D 37
			(void) looutput(&loif, m, (struct sockaddr *)&sin);
E 37
I 37
			(void) looutput(&loif, m, (struct sockaddr *)&sin, 0);
E 37
			/*
			 * The packet has already been sent and freed.
			 */
			return (0);
		} else {
			bcopy((caddr_t)ac->ac_enaddr, (caddr_t)desten,
			    sizeof(ac->ac_enaddr));
			return (1);
		}
E 38
I 38
	if (rt)
		la = (struct llinfo_arp *)rt->rt_llinfo;
	else {
D 48
		if (la = arplookup(SIN(dst)->sin_addr.s_addr, 1, 0)) 
E 48
I 48
		if (la = arplookup(SIN(dst)->sin_addr.s_addr, 1, 0))
E 48
			rt = la->la_rt;
E 38
E 20
E 9
E 2
	}
D 6
#ifdef OLDMAP
	if (lna >= 1024) {
E 6
I 6
D 8
	if ((ifp->if_flags & IFF_NOARP) || lna >= oldmap) {
E 6
D 2
		bcopy(ac->ac_enaddr, desten, 3);
E 2
I 2
		bcopy((caddr_t)ac->ac_enaddr, (caddr_t)desten, 3);
E 2
		desten[3] = (lna >> 16) & 0x7f;
		desten[4] = (lna >> 8) & 0xff;
		desten[5] = lna & 0xff;
		return (1);
	}
E 8
D 6
#endif OLDMAP
E 6
D 38
	s = splimp();
	ARPTAB_LOOK(at, destip->s_addr);
	if (at == 0) {			/* not found */
D 8
		at = arptnew(destip);
		at->at_hold = m;
		arpwhohas(ac, destip);
		splx(s);
		return (0);
E 8
I 8
D 15
		if ((ifp->if_flags & IFF_NOARP) || lna >= oldmap) {
E 15
I 15
D 24
		if (ifp->if_flags & IFF_NOARP) {
E 24
I 24
		if (ac->ac_if.if_flags & IFF_NOARP) {
E 24
E 15
D 12
			*desten = ac->ac_enaddr;
			desten->ether_addr_octet[3] = (lna >> 16) & 0x7f;
			desten->ether_addr_octet[4] = (lna >> 8) & 0xff;
			desten->ether_addr_octet[5] = lna & 0xff;
E 12
I 12
			bcopy((caddr_t)ac->ac_enaddr, (caddr_t)desten, 3);
			desten[3] = (lna >> 16) & 0x7f;
			desten[4] = (lna >> 8) & 0xff;
			desten[5] = lna & 0xff;
E 12
			splx(s);
			return (1);
		} else {
			at = arptnew(destip);
I 24
			if (at == 0)
				panic("arpresolve: no free entry");
E 24
			at->at_hold = m;
			arpwhohas(ac, destip);
			splx(s);
			return (0);
		}
E 38
I 38
	if (la == 0 || rt == 0) {
		log(LOG_DEBUG, "arpresolve: can't allocate llinfo");
		m_freem(m);
		return (0);
E 38
E 8
	}
D 38
	at->at_timer = 0;		/* restart the timer */
	if (at->at_flags & ATF_COM) {	/* entry IS complete */
D 2
		bcopy(at->at_enaddr, desten, 6);
E 2
I 2
D 8
		bcopy((caddr_t)at->at_enaddr, (caddr_t)desten, 6);
E 8
I 8
D 12
		*desten = at->at_enaddr;
E 12
I 12
		bcopy((caddr_t)at->at_enaddr, (caddr_t)desten,
		    sizeof(at->at_enaddr));
I 18
		if (at->at_flags & ATF_USETRAILERS)
			*usetrailers = 1;
E 18
E 12
E 8
E 2
		splx(s);
		return (1);
E 38
I 38
	sdl = SDL(rt->rt_gateway);
	/*
	 * Check the address family and length is valid, the address
	 * is resolved; otherwise, try to resolve.
	 */
	if ((rt->rt_expire == 0 || rt->rt_expire > time.tv_sec) &&
	    sdl->sdl_family == AF_LINK && sdl->sdl_alen != 0) {
		bcopy(LLADDR(sdl), desten, sdl->sdl_alen);
D 48
		*usetrailers = rt->rt_flags & RTF_USETRAILERS;
E 48
		return 1;
E 38
	}
	/*
	 * There is an arptab entry, but no ethernet address
	 * response yet.  Replace the held mbuf with this
	 * latest one.
	 */
D 38
	if (at->at_hold)
		m_freem(at->at_hold);
	at->at_hold = m;
	arpwhohas(ac, destip);		/* ask again */
	splx(s);
E 38
I 38
	if (la->la_hold)
		m_freem(la->la_hold);
	la->la_hold = m;
	if (rt->rt_expire) {
		rt->rt_flags &= ~RTF_REJECT;
		if (la->la_asked == 0 || rt->rt_expire != time.tv_sec) {
			rt->rt_expire = time.tv_sec;
			if (la->la_asked++ < arp_maxtries)
				arpwhohas(ac, &(SIN(dst)->sin_addr));
			else {
				rt->rt_flags |= RTF_REJECT;
				rt->rt_expire += arpt_down;
				la->la_asked = 0;
			}

		}
	}
E 38
	return (0);
}

/*
D 8
 * Find my own IP address.  It will either be waiting for us in
 * monitor RAM, or can be obtained via broadcast to the file/boot
 * server (not necessarily using the ARP packet format).
 *
 * Unimplemented at present, return 0 and assume that the host
 * will set his own IP address via the SIOCSIFADDR ioctl.
 */
I 2
/*ARGSUSED*/
E 2
struct in_addr
arpmyaddr(ac)
	register struct arpcom *ac;
{
	static struct in_addr addr;

I 3
#ifdef lint
	ac = ac;
#endif
E 3
	addr.s_addr = 0;
	return (addr);
}

/*
E 8
D 11
 * Called from ecintr/ilintr when ether packet type ETHERPUP_ARP
E 11
I 11
D 38
 * Called from 10 Mb/s Ethernet interrupt handlers
 * when ether packet type ETHERTYPE_ARP
E 11
D 8
 * is received.  Algorithm is exactly that given in RFC 826.
E 8
I 8
D 18
 * is received.  Algorithm is that given in RFC 826.
E 18
I 18
 * is received.  Common length and type checks are done here,
E 38
I 38
 * Common length and type checks are done here,
E 38
 * then the protocol-specific routine is called.
 */
I 48
void
E 48
D 38
arpinput(ac, m)
	struct arpcom *ac;
	struct mbuf *m;
E 38
I 38
arpintr()
E 38
{
I 38
	register struct mbuf *m;
E 38
	register struct arphdr *ar;
I 38
	int s;
E 38

D 38
	if (ac->ac_if.if_flags & IFF_NOARP)
		goto out;
D 32
	IF_ADJ(m);
E 32
	if (m->m_len < sizeof(struct arphdr))
		goto out;
	ar = mtod(m, struct arphdr *);
	if (ntohs(ar->ar_hrd) != ARPHRD_ETHER)
		goto out;
	if (m->m_len < sizeof(struct arphdr) + 2 * ar->ar_hln + 2 * ar->ar_pln)
		goto out;
E 38
I 38
	while (arpintrq.ifq_head) {
		s = splimp();
		IF_DEQUEUE(&arpintrq, m);
		splx(s);
		if (m == 0 || (m->m_flags & M_PKTHDR) == 0)
			panic("arpintr");
		if (m->m_len >= sizeof(struct arphdr) &&
		    (ar = mtod(m, struct arphdr *)) &&
		    ntohs(ar->ar_hrd) == ARPHRD_ETHER &&
		    m->m_len >=
		      sizeof(struct arphdr) + 2 * ar->ar_hln + 2 * ar->ar_pln)
E 38

D 38
	switch (ntohs(ar->ar_pro)) {
E 38
I 38
			    switch (ntohs(ar->ar_pro)) {
E 38

D 38
	case ETHERTYPE_IP:
	case ETHERTYPE_IPTRAILERS:
		in_arpinput(ac, m);
		return;

	default:
		break;
E 38
I 38
			    case ETHERTYPE_IP:
			    case ETHERTYPE_IPTRAILERS:
				    in_arpinput(m);
				    continue;
			    }
		m_freem(m);
E 38
	}
D 38
out:
	m_freem(m);
E 38
}

/*
 * ARP for Internet protocols on 10 Mb/s Ethernet.
 * Algorithm is that given in RFC 826.
E 18
E 8
 * In addition, a sanity check is performed on the sender
 * protocol address, to catch impersonators.
I 18
D 48
 * We also handle negotiations for use of trailer protocol:
 * ARP replies for protocol type ETHERTYPE_TRAIL are sent
 * along with IP replies if we want trailers sent to us,
 * and also send them in response to IP replies.
 * This allows either end to announce the desire to receive
E 48
I 48
 * We no longer handle negotiations for use of trailer protocol:
 * Formerly, ARP replied for protocol type ETHERTYPE_TRAIL sent
 * along with IP replies if we wanted trailers sent to us,
 * and also sent them in response to IP replies.
 * This allowed either end to announce the desire to receive
E 48
 * trailer packets.
D 48
 * We reply to requests for ETHERTYPE_TRAIL protocol as well,
 * but don't normally send requests.
E 48
I 48
 * We no longer reply to requests for ETHERTYPE_TRAIL protocol either,
 * but formerly didn't normally send requests.
E 48
E 18
 */
I 41
D 52
void
E 52
I 52
static void
E 52
E 41
D 18
arpinput(ac, m)
E 18
I 18
D 38
in_arpinput(ac, m)
E 18
	register struct arpcom *ac;
E 38
I 38
in_arpinput(m)
E 38
	struct mbuf *m;
{
	register struct ether_arp *ea;
I 38
	register struct arpcom *ac = (struct arpcom *)m->m_pkthdr.rcvif;
E 38
	struct ether_header *eh;
D 17
	register struct arptab *at = 0;  /* same as "merge" flag */
E 17
I 17
D 38
	register struct arptab *at;  /* same as "merge" flag */
I 34
	register struct in_ifaddr *ia;
	struct in_ifaddr *maybe_ia = 0;
E 38
I 38
D 39
	register struct llinfo_arp *la;
E 39
I 39
	register struct llinfo_arp *la = 0;
E 39
	register struct rtentry *rt;
	struct in_ifaddr *ia, *maybe_ia = 0;
E 38
E 34
I 18
D 49
	struct mbuf *mcopy = 0;
E 49
E 18
E 17
D 38
	struct sockaddr_in sin;
E 38
I 38
	struct sockaddr_dl *sdl;
E 38
	struct sockaddr sa;
D 13
	struct mbuf *mhold;
E 13
D 18
	struct in_addr isaddr,itaddr,myaddr;
E 18
I 18
	struct in_addr isaddr, itaddr, myaddr;
D 24
D 26
	int proto, op;
E 26
I 26
	int proto, op, s;
E 26
E 24
I 24
D 28
	int proto, op, s;
E 28
I 28
D 38
	int proto, op, s, completed = 0;
E 38
I 38
D 48
	int proto, op, completed = 0, sendtrailers;
E 48
I 48
	int op;
E 48
E 38
E 28
E 24
E 18

I 38
D 46
	if (ac->ac_if.if_flags & IFF_NOARP)
		goto out;
E 46
E 38
I 17
D 18
	IF_ADJ(m);
	at = 0;
E 17
	if (m->m_len < sizeof *ea)
		goto out;
I 8
	if (ac->ac_if.if_flags & IFF_NOARP)
		goto out;
E 18
E 8
D 11
	myaddr = ((struct sockaddr_in *)&ac->ac_if.if_addr)->sin_addr;
E 11
I 11
D 34
	myaddr = ac->ac_ipaddr;
E 34
E 11
	ea = mtod(m, struct ether_arp *);
D 11
	if (ntohs(ea->arp_pro) != ETHERPUP_IPTYPE)
E 11
I 11
D 18
	if (ntohs(ea->arp_pro) != ETHERTYPE_IP)
E 11
		goto out;
E 18
I 18
D 48
	proto = ntohs(ea->arp_pro);
E 48
	op = ntohs(ea->arp_op);
E 18
D 8
	isaddr.s_addr = ((struct in_addr *)ea->arp_spa)->s_addr;
	itaddr.s_addr = ((struct in_addr *)ea->arp_tpa)->s_addr;
D 2
	if (!bcmp(ea->arp_sha, ac->ac_enaddr, sizeof ac->ac_enaddr))
E 2
I 2
	if (!bcmp((caddr_t)ea->arp_sha, (caddr_t)ac->ac_enaddr,
E 8
I 8
D 12
	isaddr = arp_spa(ea);
	itaddr = arp_tpa(ea);
	if (!bcmp((caddr_t)&arp_sha(ea), (caddr_t)&ac->ac_enaddr,
E 8
	  sizeof (ac->ac_enaddr)))
E 12
I 12
D 24
	isaddr.s_addr = ((struct in_addr *)ea->arp_spa)->s_addr;
	itaddr.s_addr = ((struct in_addr *)ea->arp_tpa)->s_addr;
E 24
I 24
	bcopy((caddr_t)ea->arp_spa, (caddr_t)&isaddr, sizeof (isaddr));
	bcopy((caddr_t)ea->arp_tpa, (caddr_t)&itaddr, sizeof (itaddr));
I 34
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
		if (ia->ia_ifp == &ac->ac_if) {
			maybe_ia = ia;
			if ((itaddr.s_addr == ia->ia_addr.sin_addr.s_addr) ||
			     (isaddr.s_addr == ia->ia_addr.sin_addr.s_addr))
				break;
		}
	if (maybe_ia == 0)
		goto out;
	myaddr = ia ? ia->ia_addr.sin_addr : maybe_ia->ia_addr.sin_addr;
E 34
E 24
	if (!bcmp((caddr_t)ea->arp_sha, (caddr_t)ac->ac_enaddr,
D 32
	  sizeof (ea->arp_sha)))
E 32
I 32
	    sizeof (ea->arp_sha)))
E 32
E 12
E 2
		goto out;	/* it's from me, ignore it. */
I 18
	if (!bcmp((caddr_t)ea->arp_sha, (caddr_t)etherbroadcastaddr,
	    sizeof (ea->arp_sha))) {
		log(LOG_ERR,
		    "arp: ether address is broadcast for IP address %x!\n",
		    ntohl(isaddr.s_addr));
		goto out;
	}
E 18
	if (isaddr.s_addr == myaddr.s_addr) {
D 18
		printf("duplicate IP address!! sent from ethernet address: ");
D 8
		printf("%x %x %x %x %x %x\n", ea->arp_sha[0], ea->arp_sha[1],
		    ea->arp_sha[2], ea->arp_sha[3],
		    ea->arp_sha[4], ea->arp_sha[5]);
E 8
I 8
D 12
		printf("%x %x %x %x %x %x\n", ea->arp_xsha[0], ea->arp_xsha[1],
			ea->arp_xsha[2], ea->arp_xsha[3],
			ea->arp_xsha[4], ea->arp_xsha[5]);
E 12
I 12
		printf("%x %x %x %x %x %x\n", ea->arp_sha[0], ea->arp_sha[1],
			ea->arp_sha[2], ea->arp_sha[3],
			ea->arp_sha[4], ea->arp_sha[5]);
E 18
I 18
D 33
		log(LOG_ERR, "%s: %s\n",
			"duplicate IP address!! sent from ethernet address",
			ether_sprintf(ea->arp_sha));
E 33
I 33
		log(LOG_ERR,
		   "duplicate IP address %x!! sent from ethernet address: %s\n",
		   ntohl(isaddr.s_addr), ether_sprintf(ea->arp_sha));
E 33
E 18
E 12
		itaddr = myaddr;
E 8
D 12
		if (ntohs(ea->arp_op) == ARPOP_REQUEST)
E 12
I 12
D 18
		if (ntohs(ea->arp_op) == ARPOP_REQUEST) {
			bcopy((caddr_t)ac->ac_enaddr, (caddr_t)ea->arp_sha,
			    sizeof(ea->arp_sha));
E 18
I 18
D 48
		if (op == ARPOP_REQUEST)
E 18
E 12
			goto reply;
I 12
D 18
		}
E 18
E 12
		goto out;
E 48
I 48
		goto reply;
E 48
	}
I 26
	s = splimp();
E 26
I 24
D 38
	s = splimp();
E 24
	ARPTAB_LOOK(at, isaddr.s_addr);
D 8
	if (at) {
D 2
		bcopy(ea->arp_sha, at->at_enaddr, sizeof ea->arp_sha);
E 2
I 2
		bcopy((caddr_t)ea->arp_sha, (caddr_t)at->at_enaddr,
		   sizeof (ea->arp_sha));
E 8
I 8
D 13
	if (at) {		/* XXX ? - can overwrite ATF_PERM */
E 13
I 13
D 19
	if (at && (at->at_flags & ATF_COM) == 0) {
E 19
I 19
	if (at) {
E 19
E 13
D 12
		at->at_enaddr = arp_sha(ea);
E 12
I 12
		bcopy((caddr_t)ea->arp_sha, (caddr_t)at->at_enaddr,
		    sizeof(ea->arp_sha));
I 28
		if ((at->at_flags & ATF_COM) == 0)
			completed = 1;
E 28
E 12
E 8
E 2
		at->at_flags |= ATF_COM;
		if (at->at_hold) {
D 13
			mhold = at->at_hold;
			at->at_hold = 0;
E 13
			sin.sin_family = AF_INET;
			sin.sin_addr = isaddr;
D 35
			(*ac->ac_if.if_output)(&ac->ac_if, 
D 13
			    mhold, (struct sockaddr *)&sin);
E 13
I 13
			    at->at_hold, (struct sockaddr *)&sin);
E 35
I 35
			(*ac->ac_if.if_output)(&ac->ac_if, at->at_hold,
				(struct sockaddr *)&sin, (struct rtentry *)0);
E 35
			at->at_hold = 0;
E 38
I 38
	la = arplookup(isaddr.s_addr, itaddr.s_addr == myaddr.s_addr, 0);
	if (la && (rt = la->la_rt) && (sdl = SDL(rt->rt_gateway))) {
		if (sdl->sdl_alen &&
		    bcmp((caddr_t)ea->arp_sha, LLADDR(sdl), sdl->sdl_alen))
			log(LOG_INFO, "arp info overwritten for %x by %s\n",
D 55
			    isaddr.s_addr, ether_sprintf(ea->arp_sha));
E 55
I 55
			    ntohl(isaddr.s_addr), ether_sprintf(ea->arp_sha));
E 55
D 48
		completed = 1; 
E 48
		bcopy((caddr_t)ea->arp_sha, LLADDR(sdl),
			    sdl->sdl_alen = sizeof(ea->arp_sha));
		if (rt->rt_expire)
			rt->rt_expire = time.tv_sec + arpt_keep;
		rt->rt_flags &= ~RTF_REJECT;
		la->la_asked = 0;
		if (la->la_hold) {
			(*ac->ac_if.if_output)(&ac->ac_if, la->la_hold,
				rt_key(rt), rt);
			la->la_hold = 0;
E 38
E 13
		}
D 8
	}
	if (itaddr.s_addr != myaddr.s_addr)
		goto out;	/* if I am not the target */
	if (at == 0) {		/* ensure we have a table entry */
E 8
I 8
D 13
	} else if (itaddr.s_addr == myaddr.s_addr) {
E 13
I 13
	}
D 38
	if (at == 0 && itaddr.s_addr == myaddr.s_addr) {
E 13
		/* ensure we have a table entry */
E 8
D 25
		at = arptnew(&isaddr);
D 2
		bcopy(ea->arp_sha, at->at_enaddr, sizeof ea->arp_sha);
E 2
I 2
D 8
		bcopy((caddr_t)ea->arp_sha, (caddr_t)at->at_enaddr,
		   sizeof (ea->arp_sha));
E 8
I 8
D 12
		at->at_enaddr = arp_sha(ea);
E 12
I 12
		bcopy((caddr_t)ea->arp_sha, (caddr_t)at->at_enaddr,
		    sizeof(ea->arp_sha));
E 12
E 8
E 2
		at->at_flags |= ATF_COM;
E 25
I 25
		if (at = arptnew(&isaddr)) {
			bcopy((caddr_t)ea->arp_sha, (caddr_t)at->at_enaddr,
			    sizeof(ea->arp_sha));
I 28
			completed = 1;
E 28
			at->at_flags |= ATF_COM;
		}
E 25
	}
I 26
	splx(s);
E 26
I 24
	splx(s);
E 38
E 24
D 18
	if (ntohs(ea->arp_op) != ARPOP_REQUEST)
		goto out;
I 8
	ARPTAB_LOOK(at, itaddr.s_addr);
	if (at == NULL) {
		if (itaddr.s_addr != myaddr.s_addr)
			goto out;	/* if I am not the target */
		at = arptnew(&myaddr);
D 12
		at->at_enaddr = ac->ac_enaddr;
E 12
I 12
		bcopy((caddr_t)ac->ac_enaddr, (caddr_t)at->at_enaddr,
		   sizeof(at->at_enaddr));
E 12
		at->at_flags |= ATF_COM;
	} 
	if (itaddr.s_addr != myaddr.s_addr && (at->at_flags & ATF_PUBL) == 0)
		goto out;
		
E 18
I 12
D 13
	bcopy((caddr_t)at->at_enaddr, (caddr_t)ea->arp_sha,
	    sizeof(ea->arp_sha));
E 13
E 12
E 8
reply:
D 2
	bcopy(ea->arp_sha, ea->arp_tha, sizeof ea->arp_sha);
	bcopy(ea->arp_spa, ea->arp_tpa, sizeof ea->arp_spa);
	bcopy(ac->ac_enaddr, ea->arp_sha, sizeof ea->arp_sha);
	bcopy((caddr_t)&myaddr, ea->arp_spa, sizeof ea->arp_spa);
E 2
I 2
D 8
	bcopy((caddr_t)ea->arp_sha, (caddr_t)ea->arp_tha,
	   sizeof (ea->arp_sha));
	bcopy((caddr_t)ea->arp_spa, (caddr_t)ea->arp_tpa,
	   sizeof (ea->arp_spa));
	bcopy((caddr_t)ac->ac_enaddr, (caddr_t)ea->arp_sha,
	   sizeof (ea->arp_sha));
	bcopy((caddr_t)&myaddr, (caddr_t)ea->arp_spa,
	   sizeof (ea->arp_spa));
E 8
I 8
D 12
	arp_tha(ea) = arp_sha(ea);
	arp_tpa(ea) = arp_spa(ea);
	arp_sha(ea) = at->at_enaddr;
	arp_spa(ea) = itaddr;
E 12
I 12
D 18
	bcopy((caddr_t)ea->arp_sha, (caddr_t)ea->arp_tha,
	    sizeof(ea->arp_sha));
	bcopy((caddr_t)ea->arp_spa, (caddr_t)ea->arp_tpa,
	    sizeof(ea->arp_spa));
I 13
	if (at)		/* done above if at == 0 */
E 18
I 18
D 48
	switch (proto) {

	case ETHERTYPE_IPTRAILERS:
		/* partner says trailers are OK */
D 38
		if (at)
			at->at_flags |= ATF_USETRAILERS;
E 38
I 38
		if (la)
			la->la_rt->rt_flags |= RTF_USETRAILERS;
E 38
		/*
		 * Reply to request iff we want trailers.
		 */
		if (op != ARPOP_REQUEST || ac->ac_if.if_flags & IFF_NOTRAILERS)
			goto out;
		break;

	case ETHERTYPE_IP:
		/*
D 28
		 * Reply if this is an IP request, or if we want to send
		 * a trailer response.
E 28
I 28
		 * Reply if this is an IP request,
		 * or if we want to send a trailer response.
		 * Send the latter only to the IP response
		 * that completes the current ARP entry.
E 28
		 */
D 28
		if (op != ARPOP_REQUEST && ac->ac_if.if_flags & IFF_NOTRAILERS)
E 28
I 28
		if (op != ARPOP_REQUEST &&
		    (completed == 0 || ac->ac_if.if_flags & IFF_NOTRAILERS))
E 28
			goto out;
E 48
I 48
	if (op != ARPOP_REQUEST) {
	out:
		m_freem(m);
		return;
E 48
	}
	if (itaddr.s_addr == myaddr.s_addr) {
		/* I am the target */
		bcopy((caddr_t)ea->arp_sha, (caddr_t)ea->arp_tha,
		    sizeof(ea->arp_sha));
		bcopy((caddr_t)ac->ac_enaddr, (caddr_t)ea->arp_sha,
		    sizeof(ea->arp_sha));
I 38
D 48
		sendtrailers = !(ac->ac_if.if_flags & IFF_NOTRAILERS);
E 48
E 38
	} else {
D 38
		ARPTAB_LOOK(at, itaddr.s_addr);
		if (at == NULL || (at->at_flags & ATF_PUBL) == 0)
E 38
I 38
		la = arplookup(itaddr.s_addr, 0, SIN_PROXY);
		if (la == NULL)
E 38
			goto out;
I 47
		rt = la->la_rt;
E 47
		bcopy((caddr_t)ea->arp_sha, (caddr_t)ea->arp_tha,
		    sizeof(ea->arp_sha));
E 18
D 38
		bcopy((caddr_t)at->at_enaddr, (caddr_t)ea->arp_sha,
		    sizeof(ea->arp_sha));
E 38
I 38
D 47
		sdl = SDL(la->la_rt->rt_gateway);
E 47
I 47
		sdl = SDL(rt->rt_gateway);
E 47
		bcopy(LLADDR(sdl), (caddr_t)ea->arp_sha, sizeof(ea->arp_sha));
D 48
		sendtrailers = rt->rt_flags & RTF_USETRAILERS;
E 48
E 38
I 18
	}

D 48
	bcopy((caddr_t)ea->arp_spa, (caddr_t)ea->arp_tpa,
	    sizeof(ea->arp_spa));
E 18
E 13
	bcopy((caddr_t)&itaddr, (caddr_t)ea->arp_spa,
	    sizeof(ea->arp_spa));
E 12
E 8
E 2
D 18
	ea->arp_op = htons(ARPOP_REPLY);
E 18
I 18
	ea->arp_op = htons(ARPOP_REPLY); 
	/*
	 * If incoming packet was an IP reply,
	 * we are sending a reply for type IPTRAILERS.
	 * If we are sending a reply for type IP
	 * and we want to receive trailers,
	 * send a trailer reply as well.
	 */
	if (op == ARPOP_REPLY)
		ea->arp_pro = htons(ETHERTYPE_IPTRAILERS);
D 38
	else if (proto == ETHERTYPE_IP &&
	    (ac->ac_if.if_flags & IFF_NOTRAILERS) == 0)
E 38
I 38
	else if (proto == ETHERTYPE_IP && sendtrailers)
E 38
D 22
		mcopy = m_copy(m, 0, M_COPYALL);
E 22
I 22
		mcopy = m_copy(m, 0, (int)M_COPYALL);
E 48
I 48
	bcopy((caddr_t)ea->arp_spa, (caddr_t)ea->arp_tpa, sizeof(ea->arp_spa));
	bcopy((caddr_t)&itaddr, (caddr_t)ea->arp_spa, sizeof(ea->arp_spa));
	ea->arp_op = htons(ARPOP_REPLY);
	ea->arp_pro = htons(ETHERTYPE_IP); /* let's be sure! */
E 48
E 22
E 18
	eh = (struct ether_header *)sa.sa_data;
D 2
	bcopy(ea->arp_tha, eh->ether_dhost, sizeof eh->ether_dhost);
E 2
I 2
D 8
	bcopy((caddr_t)ea->arp_tha, (caddr_t)eh->ether_dhost,
	   sizeof (eh->ether_dhost));
E 8
I 8
D 12
	eh->ether_dhost = arp_tha(ea);
E 12
I 12
	bcopy((caddr_t)ea->arp_tha, (caddr_t)eh->ether_dhost,
	    sizeof(eh->ether_dhost));
E 12
E 8
E 2
D 11
	eh->ether_type = ETHERPUP_ARPTYPE;
E 11
I 11
	eh->ether_type = ETHERTYPE_ARP;
E 11
	sa.sa_family = AF_UNSPEC;
I 33
	sa.sa_len = sizeof(sa);
E 33
D 35
	(*ac->ac_if.if_output)(&ac->ac_if, m, &sa);
E 35
I 35
	(*ac->ac_if.if_output)(&ac->ac_if, m, &sa, (struct rtentry *)0);
E 35
I 18
D 48
	if (mcopy) {
		ea = mtod(mcopy, struct ether_arp *);
		ea->arp_pro = htons(ETHERTYPE_IPTRAILERS);
D 35
		(*ac->ac_if.if_output)(&ac->ac_if, mcopy, &sa);
E 35
I 35
		(*ac->ac_if.if_output)(&ac->ac_if,
					mcopy, &sa, (struct rtentry *)0);
E 35
	}
E 48
E 18
	return;
D 48
out:
	m_freem(m);
	return;
E 48
}

/*
D 38
 * Free an arptab entry.
E 38
I 38
 * Free an arp entry.
E 38
 */
I 48
static void
E 48
D 38
arptfree(at)
	register struct arptab *at;
E 38
I 38
arptfree(la)
	register struct llinfo_arp *la;
E 38
{
D 38
	int s = splimp();

	if (at->at_hold)
		m_freem(at->at_hold);
	at->at_hold = 0;
	at->at_timer = at->at_flags = 0;
	at->at_iaddr.s_addr = 0;
	splx(s);
E 38
I 38
	register struct rtentry *rt = la->la_rt;
	register struct sockaddr_dl *sdl;
	if (rt == 0)
		panic("arptfree");
	if (rt->rt_refcnt > 0 && (sdl = SDL(rt->rt_gateway)) &&
	    sdl->sdl_family == AF_LINK) {
		sdl->sdl_alen = 0;
		la->la_asked = 0;
		rt->rt_flags &= ~RTF_REJECT;
		return;
	}
	rtrequest(RTM_DELETE, rt_key(rt), (struct sockaddr *)0, rt_mask(rt),
			0, (struct rtentry **)0);
E 38
}
D 38

E 38
I 38
D 48
int arpdebug = 0;
E 48
E 38
/*
D 38
 * Enter a new address in arptab, pushing out the oldest entry 
 * from the bucket if there is no room.
I 8
 * This always succeeds since no bucket can be completely filled
 * with permanent entries (except from arpioctl when testing whether
D 12
 * another permanent entry).
E 12
I 12
 * another permanent entry will fit).
I 24
 * MUST BE CALLED AT SPLIMP.
E 38
I 38
 * Lookup or enter a new address in arptab.
E 38
E 24
E 12
E 8
 */
D 38
struct arptab *
arptnew(addr)
	struct in_addr *addr;
E 38
I 38
D 48
struct llinfo_arp *
E 48
I 48
static struct llinfo_arp *
E 48
arplookup(addr, create, proxy)
	u_long addr;
I 45
	int create, proxy;
E 45
E 38
{
D 38
	register n;
D 17
	int oldest = 0;
E 17
I 17
	int oldest = -1;
E 17
D 8
	register struct arptab *at, *ato;
E 8
I 8
	register struct arptab *at, *ato = NULL;
	static int first = 1;
E 38
I 38
	register struct rtentry *rt;
	static struct sockaddr_inarp sin = {sizeof(sin), AF_INET };
E 38
E 8

D 8
	ato = at = &arptab[ARPTAB_HASH(addr->s_addr) * ARPTAB_BSIZ];
E 8
I 8
D 38
	if (first) {
		first = 0;
		timeout(arptimer, (caddr_t)0, hz);
E 38
I 38
	sin.sin_addr.s_addr = addr;
	sin.sin_other = proxy ? SIN_PROXY : 0;
	rt = rtalloc1((struct sockaddr *)&sin, create);
	if (rt == 0)
		return (0);
	rt->rt_refcnt--;
D 48
	if ((rt->rt_flags & RTF_GATEWAY) || !(rt->rt_flags & RTF_LLINFO) ||
		rt->rt_gateway->sa_family != AF_LINK) {
		arpcatchme();
		if (arpdebug)
E 48
I 48
	if ((rt->rt_flags & RTF_GATEWAY) || (rt->rt_flags & RTF_LLINFO) == 0 ||
	    rt->rt_gateway->sa_family != AF_LINK) {
		if (create)
E 48
D 55
			log(LOG_DEBUG, "arptnew failed on %x\n", ntohl(addr));
E 55
I 55
			log(LOG_DEBUG,
				"arplookup couldn't create %x\n", ntohl(addr));
E 55
		return (0);
E 38
	}
D 38
	at = &arptab[ARPTAB_HASH(addr->s_addr) * ARPTAB_BSIZ];
E 8
D 12
	for (n = 0 ; n < ARPTAB_BSIZ ; n++,at++) {
E 12
I 12
	for (n = 0; n < ARPTAB_BSIZ; n++,at++) {
E 12
		if (at->at_flags == 0)
			goto out;	 /* found an empty entry */
I 8
		if (at->at_flags & ATF_PERM)
			continue;
E 8
D 25
		if (at->at_timer > oldest) {
E 25
I 25
		if ((int) at->at_timer > oldest) {
E 25
			oldest = at->at_timer;
			ato = at;
		}
	}
I 8
	if (ato == NULL)
D 12
		return(NULL);
E 12
I 12
		return (NULL);
E 12
E 8
	at = ato;
	arptfree(at);
out:
	at->at_iaddr = *addr;
	at->at_flags = ATF_INUSE;
	return (at);
E 38
I 38
	return ((struct llinfo_arp *)rt->rt_llinfo);
E 38
I 8
}

I 38
D 48
arpcatchme(){}

E 48
I 48
int
E 48
E 38
arpioctl(cmd, data)
	int cmd;
	caddr_t data;
{
D 38
	register struct arpreq *ar = (struct arpreq *)data;
	register struct arptab *at;
	register struct sockaddr_in *sin;
	int s;

I 33
	sin = (struct sockaddr_in *)&ar->arp_ha;
#if defined(COMPAT_43) && BYTE_ORDER != BIG_ENDIAN
	if (sin->sin_family == 0 && sin->sin_len < 16)
		sin->sin_family = sin->sin_len;
#endif
	sin->sin_len = sizeof(ar->arp_ha);
	sin = (struct sockaddr_in *)&ar->arp_pa;
#if defined(COMPAT_43) && BYTE_ORDER != BIG_ENDIAN
	if (sin->sin_family == 0 && sin->sin_len < 16)
		sin->sin_family = sin->sin_len;
#endif
	sin->sin_len = sizeof(ar->arp_pa);
E 33
	if (ar->arp_pa.sa_family != AF_INET ||
	    ar->arp_ha.sa_family != AF_UNSPEC)
		return (EAFNOSUPPORT);
D 33
	sin = (struct sockaddr_in *)&ar->arp_pa;
E 33
	s = splimp();
	ARPTAB_LOOK(at, sin->sin_addr.s_addr);
	if (at == NULL) {		/* not found */
		if (cmd != SIOCSARP) {
			splx(s);
			return (ENXIO);
		}
D 11
		if (if_ifwithnet(&ar->arp_pa) == NULL) {
E 11
I 11
		if (ifa_ifwithnet(&ar->arp_pa) == NULL) {
E 11
			splx(s);
			return (ENETUNREACH);
		}
	}
	switch (cmd) {

	case SIOCSARP:		/* set entry */
		if (at == NULL) {
			at = arptnew(&sin->sin_addr);
I 25
			if (at == NULL) {
				splx(s);
				return (EADDRNOTAVAIL);
			}
E 25
			if (ar->arp_flags & ATF_PERM) {
			/* never make all entries in a bucket permanent */
				register struct arptab *tat;
				
				/* try to re-allocate */
				tat = arptnew(&sin->sin_addr);
				if (tat == NULL) {
					arptfree(at);
					splx(s);
					return (EADDRNOTAVAIL);
				}
				arptfree(tat);
			}
		}
D 12
		at->at_enaddr = *(struct ether_addr *)ar->arp_ha.sa_data;
E 12
I 12
		bcopy((caddr_t)ar->arp_ha.sa_data, (caddr_t)at->at_enaddr,
		    sizeof(at->at_enaddr));
E 12
		at->at_flags = ATF_COM | ATF_INUSE |
D 29
			(ar->arp_flags & (ATF_PERM|ATF_PUBL));
E 29
I 29
			(ar->arp_flags & (ATF_PERM|ATF_PUBL|ATF_USETRAILERS));
E 29
		at->at_timer = 0;
		break;

	case SIOCDARP:		/* delete entry */
		arptfree(at);
		break;

	case SIOCGARP:		/* get entry */
I 33
	case OSIOCGARP:
E 33
D 12
		*(struct ether_addr *)ar->arp_ha.sa_data = at->at_enaddr;
E 12
I 12
		bcopy((caddr_t)at->at_enaddr, (caddr_t)ar->arp_ha.sa_data,
		    sizeof(at->at_enaddr));
I 33
#ifdef COMPAT_43
		if (cmd == OSIOCGARP)
			*(u_short *)&ar->arp_ha = ar->arp_ha.sa_family;
#endif
E 33
E 12
		ar->arp_flags = at->at_flags;
		break;
	}
	splx(s);
	return (0);
E 38
I 38
	return (EOPNOTSUPP);
E 38
I 18
D 32
}

/*
 * Convert Ethernet address to printable (loggable) representation.
 */
char *
ether_sprintf(ap)
	register u_char *ap;
{
	register i;
	static char etherbuf[18];
	register char *cp = etherbuf;
	static char digits[] = "0123456789abcdef";

	for (i = 0; i < 6; i++) {
		*cp++ = digits[*ap >> 4];
		*cp++ = digits[*ap++ & 0xf];
		*cp++ = ':';
	}
	*--cp = 0;
	return (etherbuf);
E 32
E 18
E 8
}
E 1
