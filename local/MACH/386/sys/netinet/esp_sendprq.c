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
 * $Log:	esp_sendprq.c,v $
 * Revision 2.3  89/03/09  20:42:17  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:15  gm0w
 * 	Changes for cleanup.
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $Header: esp_sendprq.c,v 2.3 89/03/09 20:42:17 rpd Exp $
 */

/*
 * 	esp_sendprq.c		2/26/87
 *	Written by Erik Nordmark
 */

#if	MACH_VMTP

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
#include "vmtp_send.h"
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "esp_cache.h"

/* 
 * Send a probe request
 * If a csr is given, a copy of the packet will be sent;
 * otherwise, the given packet will be passed to ip_output()
 * which will free it. Since, in the non-copy case, there might
 * be garbage at the end of the header portion of the packet, the
 * length has to be adjusted before it can be passed to sendpacket
 * for the checksum to get in the right place.
 */
esp_sendprq(csr, ei)
	register struct vmtpcsr *csr;
	register struct espiphdr *ei;
{
	struct mbuf *m;
	u_long encryptqual;
	int error;


#ifdef	ESP_DEBUG
	printf("esp_sendprq(): csr = 0x%x, ei = 0x%x\n", csr, ei);
#endif

	if (csr) {
		/*
		 * Make a copy.
		 */
		m = vmtp_copyvihdr(ei);
		if (m == NULL) {
#ifdef	VMTPDEBUG
			printf("esp_sendprq(): failed to send (ENOBUFS)\n");
#endif
			return(ENOBUFS);
		}
		ei = mtod(m, struct espiphdr *);
		encryptqual = csr->vc_encryptqual;
	} else {
		/*
		 * Adjust the length of the first mbuf and free the rest
		 * Since the mbuf chain was just received m_pullup gurantees
		 * that the first mbuf contains at least the header.
		 */
		m = dtom(ei);
		if (m->m_len < sizeof(struct espiphdr))
			panic("esp_sendprq()");
		m->m_len = sizeof(struct espiphdr);
		m_freem(m->m_next);
		m->m_next = NULL;
		encryptqual = ENCRYPT_NONE;
	}

	setei_fnctcode(ei, VMTP_PROBEREQ);
	setei_inpktgap(ei, VMTP_INPKTGAP);
	setei_priority(ei, VPR_IMPORTANT);
	if (csr)
		if (vcf_forwarding(csr)) {
			ei->ei_addr = csr->vc_clienthost;
			ei->ei_ifp = csr->vc_clientifp;
		} else {
			ei->ei_addr = csr->vc_hostaddr;
			ei->ei_ifp = csr->vc_ifp;
		}
	else {
		ei->ei_addr = ei->ei_src;	/* noop */
	}

	error = vmtp_sendpacket(csr, ei, sizeof(struct espiphdr), 
					encryptqual);
	if (error) {
#ifdef	VMTPDEBUG
		printf("esp_sendprq(): failed to send (%d)\n", error);
#endif
	}
	return(error);


} /* esp_sendprq */

#endif	MACH_VMTP
