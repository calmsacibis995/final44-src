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
 * $Log:	esp_sendprp.c,v $
 * Revision 2.3  89/03/09  20:42:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:10  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */

#include <mach_vmtp.h>

/*
 * $ Header: esp_sendprp.c,v 2.1 87/08/18 16:31:01 mrt Exp $
 */

/*
 * 	esp_sendprp.c		2/26/87
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
 * Send a probe response. ei is passed to ip_output which will free it.
 * len is the length of the data portion of the packet i.e. without
 * the esp(ip) header.
 */
esp_sendprp(csr, ei, len, encryptqual)
	register struct vmtpcsr *csr;
	register struct espiphdr *ei;
	int len;
	u_long encryptqual;
{
	struct mbuf *m;
	int error;


#ifdef	ESP_DEBUG
	printf("esp_sendprp(): csr = 0x%x, ei = 0x%x, len = %d\n", 
		csr, ei, len);
#endif

	setei_fnctcode(ei, VMTP_PROBERESP);
	setei_inpktgap(ei, VMTP_INPKTGAP);
	setei_priority(ei, VPR_IMPORTANT);
	ei->ei_addr = ei->ei_src;	/* noop */
	if (vmtp_localaddr(ei->ei_addr)) {
		vmtp_sendlocalpacket(csr, ei, sizeof(struct espiphdr)+len,
			encryptqual);
		return 0;
	}
	error = vmtp_sendpacket(csr, ei, sizeof(struct espiphdr)+len, 
					encryptqual);
	if (error) {
#ifdef	VMTPDEBUG
		printf("esp_sendprp(): failed to send (%d)\n", error);
#endif
	}
	return(error);


} /* esp_sendprp */

#endif	MACH_VMTP
