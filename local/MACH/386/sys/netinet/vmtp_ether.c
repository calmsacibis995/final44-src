/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmtp_ether.c,v $
 * Revision 2.3  89/03/09  20:48:15  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:21  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_ether.c,v 2.1 87/08/14 15:43:12 mrt Exp $
 */

/*
 *    vmtp_ether.c
 *    Written by Erik Nordmark
 */
#ifdef	VE_DEBUG
#undef VE_DEBUG		/* turn of except for vmtp_route() */
#define _VE_DEBUG
#endif
/*
 * TODO
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_pcb.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "vmtp_so.h"
#include "vmtp.h"
#include "vmtp_ip.h"
#include "vmtp_var.h"
#include "vmtp_ether.h"
#include "if_ether.h"


#ifdef	VMTP_ETHER

/*
 * Vmtp interface towards ethernet interfaces
 */

/*
 * Interupt driven input routine.
 * Very much the same as ipintr().
 */
vmtpintr()
{
	register struct mbuf *m;
	register struct ether_header *eh;
	register struct vmtp_header *vh;
	register int i, s;

next:
	/*
	 * Get next datagram off input queue and get ethernet header
	 * (including ifnet pointer) in first mbuf.
	 */
#ifdef	VE_DEBUG
	printf("vmtpintr(): queue length = %d\n", vmtpintrq.ifq_len);
#endif
	s = splimp();
	IF_DEQUEUE(&vmtpintrq, m);
	splx(s);
#ifdef	VE_DROP
	m_freem(m);
	return;
#endif
#ifdef	VE_DEBUG
	printf("vmtpintr(): received m = 0x%x\n", m);
#endif
	if (m == 0)
		return;
#ifdef	VE_DEBUG
	printf("vmtpintr(): off = %d, len = %d\n", m->m_off, m->m_len);
#endif
	vmtpstat.vst_etintotal++;

	if ((m->m_off > MMAXOFF || m->m_len < sizeof(struct vmtpiphdr)) &&
	    (m = m_pullup(m, sizeof(struct vmtpiphdr))) == 0) {
#ifdef	VE_DEBUG
		printf("vmtpintr(): pullup failed\n");
#endif
		vmtpstat.vst_ethdrops++;
		goto next;
	}
	vh = mtod(m, struct vmtp_header *);
 	eh = mtod(m, struct ether_header *);

#ifdef	VE_DEBUG
	printf("vmtpintr(): type = 0x%x\n", eh->ether_type);
	printf("vmtpintr(): source = %s\n", ether_sprintf(eh->ether_shost));
	printf("vmtpintr(): dest = %s\n", ether_sprintf(eh->ether_dhost));
#endif
	vh->vh_ifp = *(struct ifnet **)((caddr_t)m + m->m_off + 
			(sizeof(struct vmtp_header) - sizeof(struct ifnet *)));

	if (ether_multicast(eh->ether_dhost))
		vh->vh_multicast = 1;
	else
		vh->vh_multicast = 0;

	for (i = 0; i<6; i++)
		vh->vh_src.va_ether[i] = eh->ether_shost[i];	/* noop ? */
	vh->vh_src.va_type = VAT_ETHER;
	vh->vh_type = eh->ether_type;		/* noop ? */

	vmtp_input(m);

	goto next;
} /* vmtpintr */

static struct sockaddr VMTP_ETHER_AF = { AF_IMPLINK };

/*
 * Send a vmtp packet as a "raw" ethernet packet
 */
vmtp_sendetherpacket(m, secure)
	register struct mbuf *m;
	register int secure;
{
	register struct ether_header *eh;
	register struct vmtp_header *vh;
	register int i;
	register struct ifnet *ifp;
	int error;

#ifdef	VE_DEBUG
	printf("vmtp_sendetherpacket(): m = 0x%x\n", m);
#endif
	/*
	 * Drop difference in size between the headers.
	 * The first mbuf has to contain at least the vmtp_header. (No
	 * problem since it contains the vmtpiphdr.)
	 */
	vh = mtod(m, struct vmtp_header *);
	m->m_len -= sizeof(struct vmtp_header) - sizeof(struct ether_header);
	m->m_off += sizeof(struct vmtp_header) - sizeof(struct ether_header);
	eh = mtod(m, struct ether_header *);

#ifdef	VE_DEBUG
	vmtp_dumpvh(vh, "vh", "vmtp_sendetherpacket");
printf("vmtp_sendetherpacket(): dest = %s\n", ether_sprintf(eh->ether_dhost));
#endif

	ifp = vh->vh_ifp;
	if (ifp == NULL) {
#ifdef	VE_DEBUG
		printf("vmtp_sendetherpacket(): failed: ifp == NULL\n");
#endif
		m_freem(m);
		return -1;
	}
	if (vh->vh_dst.va_type != VAT_ETHER) {
#ifdef	VE_DEBUG
		printf("vmtp_sendetherpacket(): failed: va_type = %d\n",
				vh->vh_dst.va_type);
#endif
		m_freem(m);
		return -1;
	}
#ifdef	VE_DEBUG
	if (vh->vh_dst.va_type != vh->vh_dst.vau_inet.type) {
		printf("vmtp_sendetherpacket(): va_type = %d, va_itype = %d\n",
			vh->vh_dst.va_type, vh->vh_dst.vau_inet.type);
	}
#endif

#ifdef	LITTLE_ENDIAN
	if (secure)
		eh->ether_type = ETHERTYPE_LE_VMTPS;
	else
		eh->ether_type = ETHERTYPE_LE_VMTP;
#else	LITTLE_ENDIAN
	if (secure)
		eh->ether_type = ETHERTYPE_BE_VMTPS;
	else
		eh->ether_type = ETHERTYPE_BE_VMTP;
#endif	LITTLE_ENDIAN
	eh->ether_type = htons((u_short)eh->ether_type);

	for (i = 5; i>=0; i--)
		eh->ether_dhost[i] = vh->vh_dst.va_ether[i];

#ifdef	VE_DEBUG
	printf("vmtp_sendetherpacket(): type = 0x%x, ifp = 0x%x\n", 
		eh->ether_type, ifp);
	printf("vmtp_sendetherpacket(): dest = %s\n", 
		ether_sprintf(eh->ether_dhost));
#endif
	error = (*ifp->if_output)(ifp, m, &VMTP_ETHER_AF);
#ifdef	VE_DEBUG
	if (error)
		printf("vmtp_sendetherpacket(): error = %d\n", error);
#endif
	return error;
} /* vmtp_sendetherpacket */
#ifdef	_VE_DEBUG
#define VE_DEBUG
#endif


/*
 * Find an ethernet address and an interface to use to the destination.
 * Returns NULL if none found.
 * The assumes that the info in the internet routing table and the Ethernet 
 * address resolution table are consistent enough for this to work.
 */
struct ifnet *vmtp_route(dst, desten)
	register struct in_addr dst;
	register u_char *desten;		/* ethernet address */
{
	register struct ifnet *ifp;
	struct route ro;
	register struct arptab *at;

#ifdef	VE_DEBUG
	printf("vmtp_route(): dst = 0x%x, &dst = 0x%x, &desten = 0x%x \n",
		dst.s_addr, &dst, (u_long)desten);
#endif

	ro.ro_dst.sa_family = AF_INET;
	((struct sockaddr_in *)&ro.ro_dst)->sin_addr = dst;
	ro.ro_rt = NULL;
	rtalloc(&ro);

	if (ro.ro_rt == NULL || (ro.ro_rt->rt_flags & RTF_GATEWAY) != 0) {
		if (ro.ro_rt) {
#ifdef	VE_DEBUG
			printf("vmtp_route(): got a gateway\n");
#endif
			RTFREE(ro.ro_rt);
		}
#ifdef	VE_DEBUG
		else
			printf("vmtp_route(): didn't find a route\n");
#endif
		return NULL;
	}

#ifdef	VE_DEBUG
	printf("vmtp_route(): got an ifp\n");
#endif
	ifp = ro.ro_rt->rt_ifp;
	RTFREE(ro.ro_rt);


	at = arptab_look(dst);
	if (at == NULL) {
#ifdef	VE_DEBUG
		printf("vmtp_route(): ethernet address not found\n");
#endif
		return NULL;
	}

#ifdef	VE_DEBUG
	printf("vmtp_route(): ifp = 0x%x, desten = %s\n", 
		ifp, ether_sprintf(at->at_enaddr));
#endif
	bcopy((caddr_t)at->at_enaddr, (caddr_t)desten, sizeof(at->at_enaddr));
	return ifp;
} /* vmtp_route */

#endif	VMTP_ETHER
