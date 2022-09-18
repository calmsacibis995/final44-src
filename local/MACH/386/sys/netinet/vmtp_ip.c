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
 * $Log:	vmtp_ip.c,v $
 * Revision 2.3  89/03/09  20:49:42  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:04:49  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_HOSTID: defined vmtp_hostid.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_ip.c,v 2.1 87/08/14 15:44:09 mrt Exp $
 */

/*
 *    vmtp_ip.c
 *    Written by Erik Nordmark
 */

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
#include <sys/kernel.h>

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

/*
 * Vmtp interface towards IP
 */

#if	VMTP_HOSTID
/*
 * Global variable to hold the local IP address (in network order).
 */
u_long	vmtp_hostid = 0;
#endif	VMTP_HOSTID

/*
 * Vmtp-IP input routine
 * Convert the IP header into a generic vmtp_header 
 */
vmtp_ipinput(m, ifp)
	register struct mbuf *m;
	register struct ifnet *ifp;
{
	register struct vmtp_header *vh;
	register struct ip *ih;
	register u_char proto;
	register u_short len;

#ifdef	VI_DEBUG
	printf("vmtp_ipinput(): received m = 0x%x, ifp = 0x%x\n", m, ifp);
#endif
	if (m == 0)
		return;
#ifdef	VI_DEBUG
	printf("vmtp_ipinput(): off = %d, len = %d\n", m->m_off, m->m_len);
#endif
	ih = mtod(m, struct ip *);
	if (ih->ip_hl > (sizeof (struct ip) >> 2))
		ip_stripoptions(ih, (struct mbuf *)0);
	if (m->m_off > MMAXOFF || m->m_len < sizeof (struct vmtpiphdr)) {
		if ((m = m_pullup(m, sizeof (struct vmtpiphdr))) == 0) {
#ifdef	VI_DEBUG
			printf("vmtp_ipinput(): bad packet header\n");
#endif
			vmtpstat.vst_iphdrops++;
			return;
		}
	}
	vh = mtod(m, struct vmtp_header *);

#ifdef	VI_DEBUG
	printf("vmtp_ipinput(): type = 0x%x ", ih->ip_p);
	printf("source = 0x%x ", ih->ip_src.s_addr);
	printf("dest = 0x%x\n", ih->ip_dst.s_addr);
	printf("len = %d, m_len = %d\n", ih->ip_len, m->m_len);
#endif

	proto = ih->ip_p;
	len = ih->ip_len;
	if (IN_CLASSD(ih->ip_dst.s_addr))
		vh->vh_multicast = 1;
	else
		vh->vh_multicast = 0;
	vh->vh_ifp = ifp;
	vh->vh_src.va_type = VAT_INET;
	vh->vh_src.va_inet = ih->ip_src.s_addr;
	vh->vh_type = proto;
	vh->vh_len = len;
#ifdef	VI_DEBUG
	vmtp_dumpvh(vh, "vh", "vmtp_ipinput");
#endif
	vmtp_input(m);
} /* vmtp_ipinput */

static struct sockaddr VMTP_ETHER_AF = { AF_IMPLINK };

/*
 * Send a vmtp packet as an IP packet
 */
vmtp_sendippacket(m, secure, route)
	register struct mbuf *m;
	register int secure;
	register struct route *route;
{
	register struct ip *ih;
	register struct vmtp_header *vh;
	u_char ttl;
	int error;

#ifdef	VI_DEBUG
	printf("vmtp_sendippacket(): m = 0x%x\n", m);
#endif
	vh = mtod(m, struct vmtp_header *);
	ih = mtod(m, struct ip *);

#ifdef	VI_DEBUG
	vmtp_dumpvh(vh, "vh", "vmtp_sendippacket");
#endif

	if (vh->vh_dst.va_type != VAT_INET) {
#ifdef	VI_DEBUG
		printf("vmtp_sendippacket(): failed: va_type = %d\n",
				vh->vh_dst.va_type);
#endif
		m_freem(m);
		return -1;
	}

#ifdef	VI_DEBUG
	if (vh->vh_dst.va_type != vh->vh_dst.vau_inet.type) {
		printf("vmtp_sendippacket(): va_type = %d, va_itype = %d\n",
			vh->vh_dst.va_type, vh->vh_dst.vau_inet.type);
	}
#endif

	ttl = vh->vh_ttl;
	ih->ip_dst.s_addr = vh->vh_dst.va_inet;

	ih->ip_off = 0;
	ih->ip_len = vh->vh_len;
#if	VMTP_HOSTID
	ih->ip_src.s_addr = vmtp_hostid;
#else	VMTP_HOSTID
	ih->ip_src.s_addr = hostid;
#endif	VMTP_HOSTID
	ih->ip_ttl = ttl;
	ih->ip_tos = 0;

#ifdef	LITTLE_ENDIAN
	if (secure)
		ih->ip_p = IPPROTO_VMTPS;
	else
		ih->ip_p = IPPROTO_VMTP;
#else	LITTLE_ENDIAN
	if (secure)
		ih->ip_p = IPPROTO_VMTPS2;
	else
		ih->ip_p = IPPROTO_VMTP2;
#endif	LITTLE_ENDIAN

#ifdef	VI_DEBUG
	printf("vmtp_sendippacket(): type = %d\n", ih->ip_p);
	printf("vmtp_sendippacket(): dest = 0x%x, src = 0x%x\n", 
		ih->ip_dst.s_addr, ih->ip_src.s_addr);
	printf("vmtp_sendippacket(): len = %d, ttl = %d\n", ih->ip_len, 
		ih->ip_ttl);
#endif

	error = ip_output(m, NULL, route, 0);
#ifdef	VI_DEBUG
	if (error)
		printf("vmtp_sendippacket(): error = %d\n", error);
#endif
	return error;
} /* vmtp_sendippacket */


