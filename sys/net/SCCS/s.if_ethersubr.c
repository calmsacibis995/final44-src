h54867
s 00002/00002/00647
d D 8.1 93/06/10 22:44:41 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00645
d D 7.26 93/06/04 17:31:09 bostic 29 28
c prototype everything
e
s 00004/00004/00643
d D 7.25 93/05/24 23:46:22 torek 28 27
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00000/00010/00647
d D 7.24 93/03/22 22:44:20 torek 27 26
c rm RMP (it's been deprecated for a year now!)
e
s 00147/00059/00510
d D 7.23 93/02/25 16:38:43 sklower 26 25
c Husemann's X.25 over 802.2 class 2 addittions
e
s 00027/00026/00542
d D 7.22 92/10/11 11:48:59 bostic 25 24
c make kernel includes standard
e
s 00001/00001/00567
d D 7.21 92/08/14 12:22:54 sklower 24 23
c removing #define of ac broke ISO code, replace argument to bcopy
e
s 00188/00043/00380
d D 7.20 92/07/06 15:28:42 sklower 23 22
c multicast changes from lbl
e
s 00004/00000/00419
d D 7.19 92/05/27 18:06:02 sklower 22 21
c don't accept packets when not config'ed up
e
s 00003/00003/00416
d D 7.18 92/03/26 19:52:25 sklower 21 20
c if we are forwarding to a RTF_REJECTED route, we must free packet.
e
s 00025/00000/00394
d D 7.17 92/02/18 15:50:50 sklower 20 19
c add routine for common ethernet glue (mostly to put link addr
c in ifp link-layer ifa)
e
s 00001/00001/00393
d D 7.16 92/02/07 15:47:15 sklower 19 18
c in ISO specific code, call to ifp->if_output needs fourth arg
e
s 00001/00002/00393
d D 7.15 92/01/30 11:43:26 torek 18 17
c checked in for torek by sklower; Mike agrees to all these changes
e
s 00044/00040/00351
d D 7.14 91/06/25 22:09:24 sklower 17 16
c changes to merge arp and routing table;\ some code moved from
c specific rtrequest routines to general routing layer (e.g. depending
c on pointer to gateway rtentry.)
e
s 00001/00001/00390
d D 7.13 91/04/20 16:39:15 karels 16 15
c ansify
e
s 00001/00001/00390
d D 7.12 91/01/11 17:35:15 bostic 15 14
c need struct ether_header even if INET not defined
e
s 00017/00008/00374
d D 7.11 90/11/20 22:00:18 sklower 14 13
c IFF_SIMPLEX type interfaces won't hear their multicasts;
c rearrange code so that such packets appear to come from that interface
c instead of loopback.
e
s 00001/00011/00381
d D 7.10 90/06/28 21:30:34 bostic 13 12
c new copyright notice
e
s 00004/00004/00388
d D 7.9 90/06/20 19:05:13 sklower 12 11
c changes designed so that ESIS and ARP may use routing table
c instead of private cache; allow RTM_CHANGE to specify new ifp.
e
s 00025/00019/00367
d D 7.8 90/06/09 17:40:21 sklower 11 10
c checkpoint before changes conventions about who allocates llinfo space
e
s 00013/00002/00373
d D 7.7 90/05/10 16:23:44 mckusick 10 9
c merge in support for hp300 from Utah
e
s 00013/00001/00362
d D 7.6 90/04/05 11:42:31 sklower 9 8
c allow direct ethernet addrs for IS-IS
e
s 00015/00007/00348
d D 7.5 89/09/20 17:35:28 sklower 8 6
c put in SNMP counters
e
s 00014/00005/00350
d R 7.5 89/09/20 12:40:01 sklower 7 6
c minor changes in support of SNMP
e
s 00015/00020/00340
d D 7.4 89/08/29 14:52:58 root 6 5
c start routines can't reliably return errors;fix bug in ISO processing;
c check in for ``alpha'' tape.
e
s 00001/00001/00359
d D 7.3 89/04/25 14:25:35 mckusick 5 4
c ../machine => machine
e
s 00046/00030/00314
d D 7.2 89/04/22 12:11:23 sklower 4 3
c checkpoint at first working tp4 connection; before gnodes
e
s 00124/00016/00220
d D 7.1 88/10/12 14:41:20 karels 3 2
c mark state of working kernel before var. length sockaddrs
e
s 00001/00001/00235
d D 1.2 88/08/19 09:49:25 kfall 2 1
c use ifp instead of unit#
e
s 00236/00000/00000
d D 1.1 88/08/18 17:10:42 kfall 1 0
c date and time created 88/08/18 17:10:42 by kfall
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 8
I 8
D 30
 * Copyright (c) 1982, 1989 Regents of the University of California.
E 8
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1982, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
D 13
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
 *
 *	%W% (Berkeley) %G%
 */

D 25
#include "param.h"
#include "systm.h"
I 16
#include "kernel.h"
E 16
#include "malloc.h"
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
#include "ioctl.h"
#include "errno.h"
#include "syslog.h"
I 18
#include "machine/cpu.h"
E 25
I 25
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/syslog.h>
E 25
E 18

D 25
#include "if.h"
#include "netisr.h"
#include "route.h"
I 3
#include "if_llc.h"
I 9
#include "if_dl.h"
I 20
#include "if_types.h"
E 25
I 25
#include <machine/cpu.h>
E 25
E 20
E 9
E 3
D 18

D 5
#include "../machine/mtpr.h"
E 5
I 5
#include "machine/mtpr.h"
E 18
E 5

I 25
#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>
#include <net/if_llc.h>
#include <net/if_dl.h>
#include <net/if_types.h>

E 25
#ifdef INET
D 25
#include "../netinet/in.h"
#include "../netinet/in_var.h"
E 25
I 25
#include <netinet/in.h>
#include <netinet/in_var.h>
E 25
D 15
#include "../netinet/if_ether.h"
E 15
#endif
I 15
D 25
#include "../netinet/if_ether.h"
E 25
I 25
#include <netinet/if_ether.h>
E 25
E 15

#ifdef NS
D 25
#include "../netns/ns.h"
#include "../netns/ns_if.h"
E 25
I 25
#include <netns/ns.h>
#include <netns/ns_if.h>
E 25
#endif

I 4
#ifdef ISO
D 25
#include "../netiso/argo_debug.h"
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
I 11
#include "../netiso/iso_snpac.h"
E 25
I 25
#include <netiso/argo_debug.h>
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_snpac.h>
E 25
E 11
#endif

I 26
#ifdef LLC
#include <netccitt/dll.h>
#include <netccitt/llc_var.h>
#endif

#if defined(LLC) && defined(CCITT)
extern struct ifqueue pkintrq;
#endif

E 26
E 4
u_char	etherbroadcastaddr[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
I 3
extern	struct ifnet loif;
I 17
#define senderr(e) { error = (e); goto bad;}
E 17
E 3

/*
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
 * Use trailer local net encapsulation if enough data in first
 * packet leaves a multiple of 512 bytes of data in remainder.
 * Assumes that ifp is actually pointer to arpcom structure.
 */
I 29
int
E 29
D 4
enoutput(ifp, m0, dst)
E 4
I 4
D 9
ether_output(ifp, m0, dst)
E 9
I 9
D 17
ether_output(ifp, m0, dst, rt)
E 17
I 17
ether_output(ifp, m0, dst, rt0)
E 17
E 9
E 4
	register struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
I 9
D 17
	struct rtentry *rt;
E 17
I 17
	struct rtentry *rt0;
E 17
E 9
{
D 3
	int type, s, error;
E 3
I 3
	short type;
	int s, error = 0;
E 3
 	u_char edst[6];
D 17
	struct in_addr idst;
E 17
	register struct mbuf *m = m0;
I 17
	register struct rtentry *rt;
E 17
I 3
	struct mbuf *mcopy = (struct mbuf *)0;
E 3
	register struct ether_header *eh;
D 3
	register int off;
	int usetrailers;
E 3
I 3
D 8
	int usetrailers, off;
E 8
I 8
D 23
	int usetrailers, off, len = m->m_pkthdr.len;
D 16
	extern struct timeval time;
E 16
E 8
E 3
#define	ac ((struct arpcom *)ifp)
E 23
I 23
	int off, len = m->m_pkthdr.len;
	struct arpcom *ac = (struct arpcom *)ifp;
E 23

D 17
	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		error = ENETDOWN;
		goto bad;
	}
E 17
I 17
	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING))
		senderr(ENETDOWN);
E 17
I 4
D 8
	if (ifp->if_flags & IFF_SIMPLEX && dst->sa_family != AF_UNSPEC &&
	    !bcmp((caddr_t)edst, (caddr_t)etherbroadcastaddr, sizeof (edst)))
		mcopy = m_copy(m, 0, (int)M_COPYALL);
E 8
I 8
	ifp->if_lastchange = time;
I 17
	if (rt = rt0) {
		if ((rt->rt_flags & RTF_UP) == 0) {
			if (rt0 = rt = rtalloc1(dst, 1))
				rt->rt_refcnt--;
			else 
D 21
				return (EHOSTUNREACH);
E 21
I 21
				senderr(EHOSTUNREACH);
E 21
		}
		if (rt->rt_flags & RTF_GATEWAY) {
			if (rt->rt_gwroute == 0)
				goto lookup;
			if (((rt = rt->rt_gwroute)->rt_flags & RTF_UP) == 0) {
				rtfree(rt); rt = rt0;
			lookup: rt->rt_gwroute = rtalloc1(rt->rt_gateway, 1);
				if ((rt = rt->rt_gwroute) == 0)
D 21
					return (EHOSTUNREACH);
E 21
I 21
					senderr(EHOSTUNREACH);
E 21
			}
		}
		if (rt->rt_flags & RTF_REJECT)
			if (rt->rt_rmx.rmx_expire == 0 ||
			    time.tv_sec < rt->rt_rmx.rmx_expire)
D 21
				return (rt == rt0 ? EHOSTDOWN : EHOSTUNREACH);
E 21
I 21
				senderr(rt == rt0 ? EHOSTDOWN : EHOSTUNREACH);
E 21
	}
E 17
E 8
E 4
	switch (dst->sa_family) {

#ifdef INET
	case AF_INET:
D 17
		idst = ((struct sockaddr_in *)dst)->sin_addr;
 		if (!arpresolve(ac, m, &idst, edst, &usetrailers))
E 17
I 17
D 29
		if (!arpresolve(ac, rt, m, (struct sockaddr_in *)dst,
D 23
				edst, &usetrailers))
E 23
I 23
				edst))
E 29
I 29
		if (!arpresolve(ac, rt, m, dst, edst))
E 29
E 23
E 17
			return (0);	/* if not yet resolved */
I 4
D 23
		if ((ifp->if_flags & IFF_SIMPLEX) && (*edst & 1))
E 23
I 23
		/* If broadcasting on a simplex interface, loopback a copy */
		if ((m->m_flags & M_BCAST) && (ifp->if_flags & IFF_SIMPLEX))
E 23
D 10
		    mcopy = m_copy(m, 0, (int)M_COPYALL);
E 10
I 10
			mcopy = m_copy(m, 0, (int)M_COPYALL);
E 10
E 4
		off = m->m_pkthdr.len - m->m_len;
D 23
		if (usetrailers && off > 0 && (off & 0x1ff) == 0 &&
		    (m->m_flags & M_EXT) == 0 &&
		    m->m_data >= m->m_pktdat + 2 * sizeof (u_short)) {
			type = ETHERTYPE_TRAIL + (off>>9);
			m->m_data -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
I 8
			len += 2 * sizeof (u_short);
E 8
			*mtod(m, u_short *) = htons((u_short)ETHERTYPE_IP);
			*(mtod(m, u_short *) + 1) = htons((u_short)m->m_len);
			goto gottrailertype;
		}
E 23
		type = ETHERTYPE_IP;
D 3
		off = 0;
E 3
D 23
		goto gottype;
E 23
I 23
		break;
E 23
#endif
#ifdef NS
	case AF_NS:
		type = ETHERTYPE_NS;
I 3
D 8
		if (!bcmp((caddr_t)edst, (caddr_t)&ns_thishost, sizeof(edst)))
			return(looutput(&loif, m, dst));
E 8
E 3
 		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
D 3
		(caddr_t)edst, sizeof (edst));
		off = 0;
E 3
I 3
		    (caddr_t)edst, sizeof (edst));
I 8
		if (!bcmp((caddr_t)edst, (caddr_t)&ns_thishost, sizeof(edst)))
D 11
			return(looutput(&loif, m, dst));
E 11
I 11
D 14
			return (looutput(&loif, m, dst));
E 14
I 14
			return (looutput(ifp, m, dst, rt));
E 14
E 11
E 8
I 4
D 23
		if ((ifp->if_flags & IFF_SIMPLEX) && (*edst & 1))
E 23
I 23
		/* If broadcasting on a simplex interface, loopback a copy */
		if ((m->m_flags & M_BCAST) && (ifp->if_flags & IFF_SIMPLEX))
E 23
D 10
		    mcopy = m_copy(m, 0, (int)M_COPYALL);
E 10
I 10
			mcopy = m_copy(m, 0, (int)M_COPYALL);
E 10
E 4
E 3
D 23
		goto gottype;
E 23
I 23
		break;
E 23
#endif
I 3
#ifdef	ISO
	case AF_ISO: {
I 4
D 11
		int	len;
E 4
		int	ret;
E 11
I 11
		int	snpalen;
E 11
D 4
		ret = clnp_arpresolve(&us->us_ac.ac_if, m, dst, edst);
		struct llc *l;
		if (ret <= 0) {
			if (ret == -1) {
			/* not resolved */
				IFDEBUG(D_ETHER)
					printf("unoutput: clnp packet dropped\n");
				ENDDEBUG
			}
			return(0);
E 4
I 4
		struct	llc *l;
I 17
		register struct sockaddr_dl *sdl;
E 17

I 9
D 11
		if (rt && rt->rt_gateway &&
		    rt->rt_gateway->sa_family == AF_LINK) {
			register struct sockaddr_dl *sdl;
			sdl = (struct sockaddr_dl *)rt->rt_gateway;
			if (len = sdl->sdl_nlen) {
				bcopy(LLADDR(sdl), (char *)edst, len);
				goto iso_resolved;
E 11
I 11
D 17
	iso_again:
I 12
D 14
		iso_etherout();
E 14
E 12
		if (rt && rt->rt_gateway && (rt->rt_flags & RTF_UP)) {
			if (rt->rt_flags & RTF_GATEWAY) {
D 12
				register struct llinfo_llc *lc =
					(struct llinfo_llc *)rt->rt_llinfo;
				if (lc && lc->lc_rtgate) {
					rt = lc->lc_rtgate;
E 12
I 12
				if (rt->rt_llinfo) {
					rt = (struct rtentry *)rt->rt_llinfo;
E 12
					goto iso_again;
				}
			} else {
				register struct sockaddr_dl *sdl = 
					(struct sockaddr_dl *)rt->rt_gateway;
				if (sdl && sdl->sdl_family == AF_LINK
				    && sdl->sdl_alen > 0) {
					bcopy(LLADDR(sdl), (char *)edst,
								sizeof(edst));
					goto iso_resolved;
				}
E 11
			}
		}
E 9
D 11
		if ((ret = iso_tryloopback(m, (struct sockaddr_iso *)dst)) >= 0)
			return (ret);
		ret = iso_snparesolve(ifp, (struct sockaddr_iso *)dst,
					(char *)edst, &len);
		if (ret > 0) {
			m_freem(m); /* Not Resolved */
			return(ret);
E 4
		}
E 11
I 11
		if ((error = iso_snparesolve(ifp, (struct sockaddr_iso *)dst,
					(char *)edst, &snpalen)) > 0)
E 17
I 17
		if (rt && (sdl = (struct sockaddr_dl *)rt->rt_gateway) &&
		    sdl->sdl_family == AF_LINK && sdl->sdl_alen > 0) {
			bcopy(LLADDR(sdl), (caddr_t)edst, sizeof(edst));
		} else if (error =
			    iso_snparesolve(ifp, (struct sockaddr_iso *)dst,
					    (char *)edst, &snpalen))
E 17
			goto bad; /* Not Resolved */
E 11
I 9
D 17
	iso_resolved:
E 17
I 14
D 23
		if ((ifp->if_flags & IFF_SIMPLEX) && (*edst & 1) &&
E 23
I 23
		/* If broadcasting on a simplex interface, loopback a copy */
		if (*edst & 1)
			m->m_flags |= (M_BCAST|M_MCAST);
		if ((m->m_flags & M_BCAST) && (ifp->if_flags & IFF_SIMPLEX) &&
E 23
		    (mcopy = m_copy(m, 0, (int)M_COPYALL))) {
			M_PREPEND(mcopy, sizeof (*eh), M_DONTWAIT);
			if (mcopy) {
				eh = mtod(mcopy, struct ether_header *);
				bcopy((caddr_t)edst,
				      (caddr_t)eh->ether_dhost, sizeof (edst));
				bcopy((caddr_t)ac->ac_enaddr,
				      (caddr_t)eh->ether_shost, sizeof (edst));
			}
		}
E 14
E 9
		M_PREPEND(m, 3, M_DONTWAIT);
D 4
		if (m == NULL) {
			m_freem(mm);
E 4
I 4
		if (m == NULL)
E 4
D 11
			return(0);
E 11
I 11
			return (0);
E 11
D 4
		}
E 4
		type = m->m_pkthdr.len;
		l = mtod(m, struct llc *);
		l->llc_dsap = l->llc_ssap = LLC_ISO_LSAP;
		l->llc_control = LLC_UI;
I 8
		len += 3;
E 8
		IFDEBUG(D_ETHER)
			int i;
			printf("unoutput: sending pkt to: ");
			for (i=0; i<6; i++)
				printf("%x ", edst[i] & 0xff);
			printf("\n");
		ENDDEBUG
D 23
		} goto gottype;
E 23
I 23
		} break;
E 23
D 28
#endif	ISO
E 28
I 28
#endif /* ISO */
E 28
I 26
#ifdef	LLC
/*	case AF_NSAP: */
	case AF_CCITT: {
		register struct sockaddr_dl *sdl = 
			(struct sockaddr_dl *) rt -> rt_gateway;
E 26
I 10
D 23
#ifdef RMP
	case AF_RMP:
		/*
		 *  This is IEEE 802.3 -- the Ethernet `type' field is
		 *  really a `length' field.
		 */
		type = m->m_len;
 		bcopy((caddr_t)dst->sa_data, (caddr_t)edst, sizeof(edst));
		break;
#endif
E 23

I 26
		if (sdl && sdl->sdl_family == AF_LINK
		    && sdl->sdl_alen > 0) {
			bcopy(LLADDR(sdl), (char *)edst,
				sizeof(edst));
		} else goto bad; /* Not a link interface ? Funny ... */
		if ((ifp->if_flags & IFF_SIMPLEX) && (*edst & 1) &&
		    (mcopy = m_copy(m, 0, (int)M_COPYALL))) {
			M_PREPEND(mcopy, sizeof (*eh), M_DONTWAIT);
			if (mcopy) {
				eh = mtod(mcopy, struct ether_header *);
				bcopy((caddr_t)edst,
				      (caddr_t)eh->ether_dhost, sizeof (edst));
				bcopy((caddr_t)ac->ac_enaddr,
				      (caddr_t)eh->ether_shost, sizeof (edst));
			}
		}
		type = m->m_pkthdr.len;
#ifdef LLC_DEBUG
		{
			int i;
			register struct llc *l = mtod(m, struct llc *);

			printf("ether_output: sending LLC2 pkt to: ");
			for (i=0; i<6; i++)
				printf("%x ", edst[i] & 0xff);
			printf(" len 0x%x dsap 0x%x ssap 0x%x control 0x%x\n", 
			       type & 0xff, l->llc_dsap & 0xff, l->llc_ssap &0xff,
			       l->llc_control & 0xff);

		}
D 28
#endif LLC_DEBUG
E 28
I 28
#endif /* LLC_DEBUG */
E 28
		} break;
D 28
#endif/* LLC */	
E 28
I 28
#endif /* LLC */	
E 28
D 27
#ifdef RMP
	case AF_RMP:
		/*
		 *  This is IEEE 802.3 -- the Ethernet `type' field is
		 *  really a `length' field.
		 */
		type = m->m_len;
 		bcopy((caddr_t)dst->sa_data, (caddr_t)edst, sizeof(edst));
		break;
#endif
E 27

E 26
E 10
E 3
D 4

E 4
	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
 		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
D 23
		goto gottype;
E 23
I 23
		break;
E 23

	default:
		printf("%s%d: can't handle af%d\n", ifp->if_name, ifp->if_unit,
			dst->sa_family);
D 17
		error = EAFNOSUPPORT;
		goto bad;
E 17
I 17
		senderr(EAFNOSUPPORT);
E 17
	}

D 23
gottrailertype:
	/*
	 * Packet to be sent as trailer: move first packet
	 * (control information) to end of chain.
	 */
	while (m->m_next)
		m = m->m_next;
	m->m_next = m0;
	m = m0->m_next;
	m0->m_next = 0;
E 23
D 3
	m0 = m;
E 3

D 23
gottype:
E 23
I 14
	if (mcopy)
		(void) looutput(ifp, mcopy, dst, rt);
E 14
	/*
	 * Add local net header.  If no space in first mbuf,
	 * allocate another.
	 */
	M_PREPEND(m, sizeof (struct ether_header), M_DONTWAIT);
D 17
	if (m == 0) {
		error = ENOBUFS;
		goto bad;
	}
E 17
I 17
	if (m == 0)
		senderr(ENOBUFS);
E 17
	eh = mtod(m, struct ether_header *);
D 3
	eh->ether_type = htons((u_short)type);
E 3
I 3
	type = htons((u_short)type);
	bcopy((caddr_t)&type,(caddr_t)&eh->ether_type,
		sizeof(eh->ether_type));
E 3
 	bcopy((caddr_t)edst, (caddr_t)eh->ether_dhost, sizeof (edst));
 	bcopy((caddr_t)ac->ac_enaddr, (caddr_t)eh->ether_shost,
	    sizeof(eh->ether_shost));
I 14
	s = splimp();
E 14
I 3
D 4
	if (ifp->if_flags & IFF_SIMPLEX && dst->sa_family != AF_UNSPEC &&
	    !bcmp((caddr_t)edst, (caddr_t)etherbroadcastaddr, sizeof (edst)))
		mcopy = m_copy(m, 0, (int)M_COPYALL);
E 3

E 4
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
D 14
	s = splimp();
E 14
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		splx(s);
D 3
		m_freem(m);
		return (ENOBUFS);
E 3
I 3
D 17
		error = ENOBUFS;
		goto bad;
E 17
I 17
		senderr(ENOBUFS);
E 17
E 3
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	if ((ifp->if_flags & IFF_OACTIVE) == 0)
D 2
		(*ifp->if_start)(ifp->if_unit);
E 2
I 2
D 3
		(*ifp->if_start)(ifp);
E 3
I 3
D 6
		error = (*ifp->if_start)(ifp);
E 6
I 6
		(*ifp->if_start)(ifp);
E 6
E 3
E 2
	splx(s);
D 3
	return (0);
E 3
I 3
D 14
	if (mcopy)
		(void) looutput(&loif, mcopy, dst);
E 14
I 8
	ifp->if_obytes += len + sizeof (struct ether_header);
D 23
	if (edst[0] & 1)
E 23
I 23
	if (m->m_flags & M_MCAST)
E 23
		ifp->if_omcasts++;
E 8
	return (error);
E 3

bad:
D 3
	m_freem(m0);
E 3
I 3
D 14
	if (mcopy)
		m_freem(mcopy);
E 14
	if (m)
		m_freem(m);
E 3
	return (error);
}

/*
D 6
 * Pull packet off interface.  Off is nonzero if packet
 * has trailing header; we still have to drop
 * the type and length which are at the front of any trailer data.
E 6
I 6
 * Process a received Ethernet packet;
 * the packet is in the mbuf chain m without
 * the ether header, which is provided separately.
E 6
 */
I 29
void
E 29
D 4
en_doproto(ifp, eh, m)
E 4
I 4
ether_input(ifp, eh, m)
E 4
	struct ifnet *ifp;
	register struct ether_header *eh;
	struct mbuf *m;
{
	register struct ifqueue *inq;
I 3
	register struct llc *l;
I 26
	struct arpcom *ac = (struct arpcom *)ifp;
E 26
E 3
	int s;

I 22
	if ((ifp->if_flags & IFF_UP) == 0) {
		m_freem(m);
		return;
	}
E 22
I 8
	ifp->if_lastchange = time;
	ifp->if_ibytes += m->m_pkthdr.len + sizeof (*eh);
E 8
D 3
	if (bcmp((caddr_t)etherbroadcastaddr, (caddr_t)eh->ether_shost,
E 3
I 3
	if (bcmp((caddr_t)etherbroadcastaddr, (caddr_t)eh->ether_dhost,
E 3
	    sizeof(etherbroadcastaddr)) == 0)
		m->m_flags |= M_BCAST;
I 3
	else if (eh->ether_dhost[0] & 1)
		m->m_flags |= M_MCAST;
I 8
	if (m->m_flags & (M_BCAST|M_MCAST))
		ifp->if_imcasts++;
E 8
E 3

	switch (eh->ether_type) {
#ifdef INET
	case ETHERTYPE_IP:
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;

	case ETHERTYPE_ARP:
D 17
		arpinput((struct arpcom *)ifp, m);
		return;
E 17
I 17
		schednetisr(NETISR_ARP);
		inq = &arpintrq;
		break;
E 17
#endif
#ifdef NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;

#endif
	default:
I 6
D 26
#ifdef	ISO
E 26
I 26
#if defined (ISO) || defined (LLC)
E 26
E 6
D 3
		m_freem(m);
		return;
E 3
I 3
D 4
		if (eh->ether_type > 1500)
E 4
I 4
		if (eh->ether_type > ETHERMTU)
E 4
			goto dropanyway;
		l = mtod(m, struct llc *);
D 26
		switch (l->llc_control) {
		case LLC_UI:
		/* LLC_UI_P forbidden in class 1 service */
		    if ((l->llc_dsap == LLC_ISO_LSAP) &&
			(l->llc_ssap == LLC_ISO_LSAP)) {
D 6
#ifdef	ISO
E 6
				/* LSAP for ISO */
E 26
I 26
		switch (l->llc_dsap) {
#ifdef	ISO
		case LLC_ISO_LSAP: 
			switch (l->llc_control) {
			case LLC_UI:
				/* LLC_UI_P forbidden in class 1 service */
				if ((l->llc_dsap == LLC_ISO_LSAP) &&
				    (l->llc_ssap == LLC_ISO_LSAP)) {
					/* LSAP for ISO */
					if (m->m_pkthdr.len > eh->ether_type)
						m_adj(m, eh->ether_type - m->m_pkthdr.len);
					m->m_data += 3;		/* XXX */
					m->m_len -= 3;		/* XXX */
					m->m_pkthdr.len -= 3;	/* XXX */
					M_PREPEND(m, sizeof *eh, M_DONTWAIT);
					if (m == 0)
						return;
					*mtod(m, struct ether_header *) = *eh;
					IFDEBUG(D_ETHER)
						printf("clnp packet");
					ENDDEBUG
					schednetisr(NETISR_ISO);
					inq = &clnlintrq;
					break;
				}
				goto dropanyway;
				
			case LLC_XID:
			case LLC_XID_P:
				if(m->m_len < 6)
					goto dropanyway;
				l->llc_window = 0;
				l->llc_fid = 9;
				l->llc_class = 1;
				l->llc_dsap = l->llc_ssap = 0;
				/* Fall through to */
			case LLC_TEST:
			case LLC_TEST_P:
			{
				struct sockaddr sa;
				register struct ether_header *eh2;
				int i;
				u_char c = l->llc_dsap;

				l->llc_dsap = l->llc_ssap;
				l->llc_ssap = c;
				if (m->m_flags & (M_BCAST | M_MCAST))
					bcopy((caddr_t)ac->ac_enaddr,
					      (caddr_t)eh->ether_dhost, 6);
				sa.sa_family = AF_UNSPEC;
				sa.sa_len = sizeof(sa);
				eh2 = (struct ether_header *)sa.sa_data;
				for (i = 0; i < 6; i++) {
					eh2->ether_shost[i] = c = eh->ether_dhost[i];
					eh2->ether_dhost[i] = 
						eh->ether_dhost[i] = eh->ether_shost[i];
					eh->ether_shost[i] = c;
				}
				ifp->if_output(ifp, m, &sa, NULL);
				return;
			}
			default:
				m_freem(m);
				return;
			}
			break;
#endif /* ISO */
#ifdef LLC
		case LLC_X25_LSAP:
		{
E 26
I 14
			if (m->m_pkthdr.len > eh->ether_type)
				m_adj(m, eh->ether_type - m->m_pkthdr.len);
E 14
I 6
D 26
			m->m_data += 3;		/* XXX */
			m->m_len -= 3;		/* XXX */
			m->m_pkthdr.len -= 3;	/* XXX */
E 6
D 4
			m->m_data += 3;
			m->m_len -= 3;
			if (m->m_flags & M_PKTHDR)
				m->m_pkthdr.len -= 3;
			DEBUGF(undebug & 0x2, printf("clnp packet\n");)
			schednetisr(NETISR_CLNP);
E 4
I 4
			M_PREPEND(m, sizeof *eh, M_DONTWAIT);
E 26
I 26
			M_PREPEND(m, sizeof(struct sdl_hdr) , M_DONTWAIT);
E 26
			if (m == 0)
				return;
D 26
			*mtod(m, struct ether_header *) = *eh;
			IFDEBUG(D_ETHER)
			    printf("clnp packet");
			ENDDEBUG
			schednetisr(NETISR_ISO);
E 4
			inq = &clnlintrq;
E 26
I 26
			if ( !sdl_sethdrif(ifp, eh->ether_shost, LLC_X25_LSAP,
					    eh->ether_dhost, LLC_X25_LSAP, 6, 
					    mtod(m, struct sdl_hdr *)))
				panic("ETHER cons addr failure");
			mtod(m, struct sdl_hdr *)->sdlhdr_len = eh->ether_type;
#ifdef LLC_DEBUG
				printf("llc packet\n");
D 28
#endif LLC_DEBUG
E 28
I 28
#endif /* LLC_DEBUG */
E 28
			schednetisr(NETISR_CCITT);
			inq = &llcintrq;
E 26
D 6
			if (IF_QFULL(inq)){
D 4
				DEBUGF(undebug & 0x2, printf(" qfull\n");)
E 4
I 4
				IFDEBUG(D_ETHER)
				    printf(" qfull\n");
				ENDDEBUG
E 4
				IF_DROP(inq);
				m_freem(m);
			} else {
				IF_ENQUEUE(inq, m);
D 4
				DEBUGF(undebug & 0x2, printf(" queued\n");)
E 4
I 4
				IFDEBUG(D_ETHER)
				    printf(" queued\n");
				ENDDEBUG
E 4
			}
			return;
#endif	ISO
E 6
I 6
			break;
E 6
D 26
		    }
D 6
		    break;
E 6
I 6
		    goto dropanyway;

E 6
		case LLC_XID:
		case LLC_XID_P:
		    if(m->m_len < 6)
			goto dropanyway;
		    l->llc_window = 0;
		    l->llc_fid = 9;
		    l->llc_class = 1;
		    l->llc_dsap = l->llc_ssap = 0;
		    /* Fall through to */
		case LLC_TEST:
		case LLC_TEST_P:
		{
		    struct sockaddr sa;
		    register struct ether_header *eh2;
		    int i;
		    u_char c = l->llc_dsap;
		    l->llc_dsap = l->llc_ssap;
		    l->llc_ssap = c;
I 4
		    if (m->m_flags & (M_BCAST | M_MCAST))
D 24
			bcopy((caddr_t)ac->ac_enaddr,
E 24
I 24
			bcopy((caddr_t)((struct arpcom *)ifp)->ac_enaddr,
E 24
			      (caddr_t)eh->ether_dhost, 6);
E 4
		    sa.sa_family = AF_UNSPEC;
I 4
		    sa.sa_len = sizeof(sa);
E 4
		    eh2 = (struct ether_header *)sa.sa_data;
		    for (i = 0; i < 6; i++) {
			eh2->ether_shost[i] = c = eh->ether_dhost[i];
			eh2->ether_dhost[i] = 
				eh->ether_dhost[i] = eh->ether_shost[i];
			eh->ether_shost[i] = c;
		    }
D 19
		    ifp->if_output(ifp, m, &sa);
E 19
I 19
		    ifp->if_output(ifp, m, &sa, (struct rtentry *)0);
E 19
		    return;
E 26
		}
I 26
#endif /* LLC */
E 26
		dropanyway:
		default:
D 26
		    m_freem(m);
		    return;
	    }
I 6
#else
E 26
I 26
			m_freem(m);
			return;
		}
#else /* ISO || LLC */
E 26
	    m_freem(m);
	    return;
D 26
#endif	ISO
E 26
I 26
#endif /* ISO || LLC */
E 26
E 6
E 3
	}

	s = splimp();
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
	} else
		IF_ENQUEUE(inq, m);
	splx(s);
}

/*
 * Convert Ethernet address to printable (loggable) representation.
 */
I 4
static char digits[] = "0123456789abcdef";
E 4
char *
ether_sprintf(ap)
	register u_char *ap;
{
	register i;
	static char etherbuf[18];
	register char *cp = etherbuf;
D 4
	static char digits[] = "0123456789abcdef";
E 4

	for (i = 0; i < 6; i++) {
		*cp++ = digits[*ap >> 4];
		*cp++ = digits[*ap++ & 0xf];
		*cp++ = ':';
	}
	*--cp = 0;
	return (etherbuf);
I 20
}

/*
 * Perform common duties while attaching to interface list
 */
I 29
void
E 29
ether_ifattach(ifp)
	register struct ifnet *ifp;
{
	register struct ifaddr *ifa;
	register struct sockaddr_dl *sdl;

	ifp->if_type = IFT_ETHER;
	ifp->if_addrlen = 6;
	ifp->if_hdrlen = 14;
	ifp->if_mtu = ETHERMTU;
	for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
		if ((sdl = (struct sockaddr_dl *)ifa->ifa_addr) &&
		    sdl->sdl_family == AF_LINK) {
			sdl->sdl_type = IFT_ETHER;
			sdl->sdl_alen = ifp->if_addrlen;
			bcopy((caddr_t)((struct arpcom *)ifp)->ac_enaddr,
			      LLADDR(sdl), ifp->if_addrlen);
			break;
		}
E 20
}
I 23

D 26
#ifdef MULTICAST
E 26
u_char	ether_ipmulticast_min[6] = { 0x01, 0x00, 0x5e, 0x00, 0x00, 0x00 };
u_char	ether_ipmulticast_max[6] = { 0x01, 0x00, 0x5e, 0x7f, 0xff, 0xff };
/*
 * Add an Ethernet multicast address or range of addresses to the list for a
 * given interface.
 */
int
ether_addmulti(ifr, ac)
	struct ifreq *ifr;
	register struct arpcom *ac;
{
	register struct ether_multi *enm;
	struct sockaddr_in *sin;
	u_char addrlo[6];
	u_char addrhi[6];
	int s = splimp();

	switch (ifr->ifr_addr.sa_family) {

	case AF_UNSPEC:
		bcopy(ifr->ifr_addr.sa_data, addrlo, 6);
		bcopy(addrlo, addrhi, 6);
		break;

#ifdef INET
	case AF_INET:
		sin = (struct sockaddr_in *)&(ifr->ifr_addr);
		if (sin->sin_addr.s_addr == INADDR_ANY) {
			/*
			 * An IP address of INADDR_ANY means listen to all
			 * of the Ethernet multicast addresses used for IP.
			 * (This is for the sake of IP multicast routers.)
			 */
			bcopy(ether_ipmulticast_min, addrlo, 6);
			bcopy(ether_ipmulticast_max, addrhi, 6);
		}
		else {
			ETHER_MAP_IP_MULTICAST(&sin->sin_addr, addrlo);
			bcopy(addrlo, addrhi, 6);
		}
		break;
#endif

	default:
		splx(s);
		return (EAFNOSUPPORT);
	}

	/*
	 * Verify that we have valid Ethernet multicast addresses.
	 */
	if ((addrlo[0] & 0x01) != 1 || (addrhi[0] & 0x01) != 1) {
		splx(s);
		return (EINVAL);
	}
	/*
	 * See if the address range is already in the list.
	 */
	ETHER_LOOKUP_MULTI(addrlo, addrhi, ac, enm);
	if (enm != NULL) {
		/*
		 * Found it; just increment the reference count.
		 */
		++enm->enm_refcount;
		splx(s);
		return (0);
	}
	/*
	 * New address or range; malloc a new multicast record
	 * and link it into the interface's multicast list.
	 */
	enm = (struct ether_multi *)malloc(sizeof(*enm), M_IFMADDR, M_NOWAIT);
	if (enm == NULL) {
		splx(s);
		return (ENOBUFS);
	}
	bcopy(addrlo, enm->enm_addrlo, 6);
	bcopy(addrhi, enm->enm_addrhi, 6);
	enm->enm_ac = ac;
	enm->enm_refcount = 1;
	enm->enm_next = ac->ac_multiaddrs;
	ac->ac_multiaddrs = enm;
	ac->ac_multicnt++;
	splx(s);
	/*
	 * Return ENETRESET to inform the driver that the list has changed
	 * and its reception filter should be adjusted accordingly.
	 */
	return (ENETRESET);
}

/*
 * Delete a multicast address record.
 */
int
ether_delmulti(ifr, ac)
	struct ifreq *ifr;
	register struct arpcom *ac;
{
	register struct ether_multi *enm;
	register struct ether_multi **p;
	struct sockaddr_in *sin;
	u_char addrlo[6];
	u_char addrhi[6];
	int s = splimp();

	switch (ifr->ifr_addr.sa_family) {

	case AF_UNSPEC:
		bcopy(ifr->ifr_addr.sa_data, addrlo, 6);
		bcopy(addrlo, addrhi, 6);
		break;

#ifdef INET
	case AF_INET:
		sin = (struct sockaddr_in *)&(ifr->ifr_addr);
		if (sin->sin_addr.s_addr == INADDR_ANY) {
			/*
			 * An IP address of INADDR_ANY means stop listening
			 * to the range of Ethernet multicast addresses used
			 * for IP.
			 */
			bcopy(ether_ipmulticast_min, addrlo, 6);
			bcopy(ether_ipmulticast_max, addrhi, 6);
		}
		else {
			ETHER_MAP_IP_MULTICAST(&sin->sin_addr, addrlo);
			bcopy(addrlo, addrhi, 6);
		}
		break;
#endif

	default:
		splx(s);
		return (EAFNOSUPPORT);
	}

	/*
	 * Look up the address in our list.
	 */
	ETHER_LOOKUP_MULTI(addrlo, addrhi, ac, enm);
	if (enm == NULL) {
		splx(s);
		return (ENXIO);
	}
	if (--enm->enm_refcount != 0) {
		/*
		 * Still some claims to this record.
		 */
		splx(s);
		return (0);
	}
	/*
	 * No remaining claims to this record; unlink and free it.
	 */
	for (p = &enm->enm_ac->ac_multiaddrs;
	     *p != enm;
	     p = &(*p)->enm_next)
		continue;
	*p = (*p)->enm_next;
	free(enm, M_IFMADDR);
	ac->ac_multicnt--;
	splx(s);
	/*
	 * Return ENETRESET to inform the driver that the list has changed
	 * and its reception filter should be adjusted accordingly.
	 */
	return (ENETRESET);
}
D 26
#endif
E 26
E 23
I 12
D 14
iso_etherout() {}
E 14
E 12
E 1
