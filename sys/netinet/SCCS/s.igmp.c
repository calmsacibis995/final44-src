h63551
s 00005/00001/00286
d D 8.2 95/05/03 12:56:24 mckusick 9 8
c pass valid mbuf to in_cksum (from mccanne@horse.ee.lbl.gov)
e
s 00002/00002/00285
d D 8.1 93/07/19 13:42:16 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00004/00279
d D 7.5 93/07/19 13:41:51 mckusick 7 5
c bug fix for igmp_input (from mccanne@horse.ee.lbl.gov)
e
s 00002/00002/00281
d R 8.1 93/06/10 23:04:02 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00278
d D 7.4 93/02/12 14:15:22 sklower 5 3
c although MULTICAST is standard, MROUTING isn't, need #ifdef
e
s 00001/00001/00279
d R 7.4 93/02/07 21:14:51 sklower 4 3
c igmp.c now reserves storge for multicast routing socket;
c allows for future variants of ip_mroute.c
e
s 00000/00002/00280
d D 7.3 93/01/08 18:42:43 andrew 3 2
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00013/00013/00269
d D 7.2 92/10/11 12:01:50 bostic 2 1
c make kernel includes standard
e
s 00282/00000/00000
d D 7.1 92/07/08 23:16:01 sklower 1 0
c date and time created 92/07/08 23:16:01 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Stephen Deering.
D 8
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* Internet Group Management Protocol (IGMP) routines. */

D 3
#ifdef MULTICAST
E 3

D 2
#include "param.h"
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
E 2
I 2
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
E 2

D 2
#include "../net/if.h"
#include "../net/route.h"
E 2
I 2
#include <net/if.h>
#include <net/route.h>
E 2

D 2
#include "in.h"
#include "in_var.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "igmp.h"
#include "igmp_var.h"
E 2
I 2
#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/igmp.h>
#include <netinet/igmp_var.h>
E 2

extern struct ifnet loif;

static int igmp_timers_are_running = 0;
static u_long igmp_all_hosts_group;

static void igmp_sendreport __P((struct in_multi *));

void
igmp_init()
{
	/*
	 * To avoid byte-swapping the same value over and over again.
	 */
	igmp_all_hosts_group = htonl(INADDR_ALLHOSTS_GROUP);
}

void
D 7
igmp_input(m, ifp)
E 7
I 7
igmp_input(m, iphlen)
E 7
	register struct mbuf *m;
D 7
	register struct ifnet *ifp;
E 7
I 7
	register int iphlen;
E 7
{
	register struct igmp *igmp;
	register struct ip *ip;
	register int igmplen;
D 7
	register int iphlen;
E 7
I 7
	register struct ifnet *ifp = m->m_pkthdr.rcvif;
E 7
	register int minlen;
	register struct in_multi *inm;
	register struct in_ifaddr *ia;
	struct in_multistep step;

	++igmpstat.igps_rcv_total;

	ip = mtod(m, struct ip *);
D 7
	iphlen = ip->ip_hl << 2;
E 7
	igmplen = ip->ip_len;

	/*
	 * Validate lengths
	 */
	if (igmplen < IGMP_MINLEN) {
		++igmpstat.igps_rcv_tooshort;
		m_freem(m);
		return;
	}
	minlen = iphlen + IGMP_MINLEN;
	if ((m->m_flags & M_EXT || m->m_len < minlen) &&
	    (m = m_pullup(m, minlen)) == 0) {
		++igmpstat.igps_rcv_tooshort;
		return;
	}

	/*
	 * Validate checksum
	 */
	m->m_data += iphlen;
	m->m_len -= iphlen;
	igmp = mtod(m, struct igmp *);
	if (in_cksum(m, igmplen)) {
		++igmpstat.igps_rcv_badsum;
		m_freem(m);
		return;
	}
	m->m_data -= iphlen;
	m->m_len += iphlen;
	ip = mtod(m, struct ip *);

	switch (igmp->igmp_type) {

	case IGMP_HOST_MEMBERSHIP_QUERY:
		++igmpstat.igps_rcv_queries;

		if (ifp == &loif)
			break;

		if (ip->ip_dst.s_addr != igmp_all_hosts_group) {
			++igmpstat.igps_rcv_badqueries;
			m_freem(m);
			return;
		}

		/*
		 * Start the timers in all of our membership records for
		 * the interface on which the query arrived, except those
		 * that are already running and those that belong to the
		 * "all-hosts" group.
		 */
		IN_FIRST_MULTI(step, inm);
		while (inm != NULL) {
			if (inm->inm_ifp == ifp && inm->inm_timer == 0 &&
			    inm->inm_addr.s_addr != igmp_all_hosts_group) {
				inm->inm_timer =
				    IGMP_RANDOM_DELAY(inm->inm_addr);
				igmp_timers_are_running = 1;
			}
			IN_NEXT_MULTI(step, inm);
		}

		break;

	case IGMP_HOST_MEMBERSHIP_REPORT:
		++igmpstat.igps_rcv_reports;

		if (ifp == &loif)
			break;

		if (!IN_MULTICAST(ntohl(igmp->igmp_group.s_addr)) ||
		    igmp->igmp_group.s_addr != ip->ip_dst.s_addr) {
			++igmpstat.igps_rcv_badreports;
			m_freem(m);
			return;
		}

		/*
		 * KLUDGE: if the IP source address of the report has an
		 * unspecified (i.e., zero) subnet number, as is allowed for
		 * a booting host, replace it with the correct subnet number
		 * so that a process-level multicast routing demon can
		 * determine which subnet it arrived from.  This is necessary
		 * to compensate for the lack of any way for a process to
		 * determine the arrival interface of an incoming packet.
		 */
		if ((ntohl(ip->ip_src.s_addr) & IN_CLASSA_NET) == 0) {
			IFP_TO_IA(ifp, ia);
			if (ia) ip->ip_src.s_addr = htonl(ia->ia_subnet);
		}

		/*
		 * If we belong to the group being reported, stop
		 * our timer for that group.
		 */
		IN_LOOKUP_MULTI(igmp->igmp_group, ifp, inm);
		if (inm != NULL) {
			inm->inm_timer = 0;
			++igmpstat.igps_rcv_ourreports;
		}

		break;
	}

	/*
	 * Pass all valid IGMP packets up to any process(es) listening
	 * on a raw IGMP socket.
	 */
	rip_input(m);
}

void
igmp_joingroup(inm)
	struct in_multi *inm;
{
	register int s = splnet();

	if (inm->inm_addr.s_addr == igmp_all_hosts_group ||
	    inm->inm_ifp == &loif)
		inm->inm_timer = 0;
	else {
		igmp_sendreport(inm);
		inm->inm_timer = IGMP_RANDOM_DELAY(inm->inm_addr);
		igmp_timers_are_running = 1;
	}
	splx(s);
}

void
igmp_leavegroup(inm)
	struct in_multi *inm;
{
	/*
	 * No action required on leaving a group.
	 */
}

void
igmp_fasttimo()
{
	register struct in_multi *inm;
	register int s;
	struct in_multistep step;

	/*
	 * Quick check to see if any work needs to be done, in order
	 * to minimize the overhead of fasttimo processing.
	 */
	if (!igmp_timers_are_running)
		return;

	s = splnet();
	igmp_timers_are_running = 0;
	IN_FIRST_MULTI(step, inm);
	while (inm != NULL) {
		if (inm->inm_timer == 0) {
			/* do nothing */
		} else if (--inm->inm_timer == 0) {
			igmp_sendreport(inm);
		} else {
			igmp_timers_are_running = 1;
		}
		IN_NEXT_MULTI(step, inm);
	}
	splx(s);
}

static void
igmp_sendreport(inm)
	register struct in_multi *inm;
{
	register struct mbuf *m;
	register struct igmp *igmp;
	register struct ip *ip;
	register struct ip_moptions *imo;
	struct ip_moptions simo;
D 5
	extern struct socket *ip_mrouter;
E 5

	MGETHDR(m, M_DONTWAIT, MT_HEADER);
	if (m == NULL)
		return;
I 7
	/*
	 * Assume max_linkhdr + sizeof(struct ip) + IGMP_MINLEN
	 * is smaller than mbuf size returned by MGETHDR.
	 */
E 7
	m->m_data += max_linkhdr;
	m->m_len = sizeof(struct ip) + IGMP_MINLEN;
I 7
	m->m_pkthdr.len = sizeof(struct ip) + IGMP_MINLEN;
E 7

	ip = mtod(m, struct ip *);
	ip->ip_tos = 0;
	ip->ip_len = sizeof(struct ip) + IGMP_MINLEN;
	ip->ip_off = 0;
	ip->ip_p = IPPROTO_IGMP;
	ip->ip_src.s_addr = INADDR_ANY;
	ip->ip_dst = inm->inm_addr;

D 9
	igmp = (struct igmp *)(ip + 1);
E 9
I 9
	m->m_data += sizeof(struct ip);
	m->m_len -= sizeof(struct ip);
	igmp = mtod(m, struct igmp *);
E 9
	igmp->igmp_type = IGMP_HOST_MEMBERSHIP_REPORT;
	igmp->igmp_code = 0;
	igmp->igmp_group = inm->inm_addr;
	igmp->igmp_cksum = 0;
	igmp->igmp_cksum = in_cksum(m, IGMP_MINLEN);
I 9
	m->m_data -= sizeof(struct ip);
	m->m_len += sizeof(struct ip);
E 9

	imo = &simo;
	bzero((caddr_t)imo, sizeof(*imo));
	imo->imo_multicast_ifp = inm->inm_ifp;
	imo->imo_multicast_ttl = 1;
	/*
	 * Request loopback of the report if we are acting as a multicast
	 * router, so that the process-level routing demon can hear it.
	 */
I 5
#ifdef MROUTING
    {
	extern struct socket *ip_mrouter;
E 5
	imo->imo_multicast_loop = (ip_mrouter != NULL);
D 5

E 5
I 5
    }
#endif
E 5
	ip_output(m, NULL, NULL, 0, imo);

	++igmpstat.igps_snd_reports;
}
D 3
#endif
E 3
E 1
