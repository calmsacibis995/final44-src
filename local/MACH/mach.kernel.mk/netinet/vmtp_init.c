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
 * $Log:	vmtp_init.c,v $
 * Revision 2.3  89/03/09  20:49:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:04:37  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *	Disabled periodic ESP probe on all remote csr's.
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_init.c,v 2.1 87/08/14 15:44:01 mrt Exp $
 */

/*
 * 	vmtp_init.c	0.1	10/19/86
 *	Written by Erik Nordmark and Joyo Wijaya
 */

#if	MACH_VMTP

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>

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
#include "esp.h"
#include "esp_var.h"

#ifdef	VMTP_ETHER
#include "vmtp_ether.h"
#include "if_ether.h"
#endif


/*
 * Initialize the maps, the timeout queue, and the statistics.
 */
vmtp_init()
{
	int i;

#ifdef	VMTPDEBUG
	printf("vmtp_init()\n");
#endif
	for (i=0; i<VMTP_HASHMAPSIZE; i++)
		vservermap[i] = NULL;
	for (i=0; i<VMTP_HASHMAPSIZE; i++)
		vlocalcsrmap[i] = NULL;
	for (i=0; i<VMTP_HASHMAPSIZE; i++)
		vremotecsrmap[i] = NULL;

	vtimeoqueue.vq_chead = vtimeoqueue.vq_ctail = &vtimeoqueue.vq_queue;
	vtimeoqueue.vq_type = VQ_TIMEOUT;
	vtimeoqueue.vq_qhead = NULL;

	vmtpstat.vst_badsum = 0;
	vmtpstat.vst_badencrsum = 0;
	vmtpstat.vst_iphdrops = 0;	
	vmtpstat.vst_ipintotal = 0;
	vmtpstat.vst_ipouttotal = 0;
	vmtpstat.vst_ethdrops = 0;	
	vmtpstat.vst_etintotal = 0;
	vmtpstat.vst_etouttotal = 0;

	vmtp_initgroup();
	vmtp_initbuf();

	vmtp_timeout();

	esp_initcache();
/* DPJ	esp_hdlestimeo();*/

	vmtp_initmanager();

#ifdef	VMTP_ETHER
	vmtpintrq.ifq_maxlen = IFQ_MAXLEN;
#endif
	{
	struct vmtpcsr *csr;

	if ((caddr_t)(&csr->vc_verifyint) + sizeof(int) - (caddr_t)csr 
	    != VMTP_RBSIZE) {
		printf("\n\n ********* VMTP size problems *************\n\n");
		printf("true size for rb = %d\n", 
				(caddr_t)&csr->vc_verifyint + sizeof(int)
				 - (caddr_t)csr);
		printf("VMTP_RBSIZE = %d\n", VMTP_RBSIZE);
	}

	if (sizeof(struct av3auth) + sizeof(struct vmtpiphdr) > MLEN ||
	    VMTP_RBSIZE > MLEN) {
		printf("\n\n ********* VMTP size problems *************\n\n");
		printf("sizeof vmtpiphdr = %d\n", sizeof(struct vmtpiphdr));
		printf("sizeof vmtpcsr = %d\n", sizeof(struct vmtpcsr));
		printf("sizeof av2auth = %d\n", sizeof(struct av2auth));
		printf("sizeof av3auth = %d\n", sizeof(struct av3auth));
		printf("size for rb = %d\n", VMTP_RBSIZE);
	}
	}


} /* vmtp_init */


#endif	MACH_VMTP

