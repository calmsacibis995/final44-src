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
 * $Log:	vmtp_input.c,v $
 * Revision 2.3  89/03/09  20:49:36  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:04:42  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_input.c,v 2.1 87/08/14 15:44:05 mrt Exp $
 */

/*
 * 	vmtp_input.c	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

/*
 * TODO:
 */

/*
 * Variants:
 *	DELAYPROBE - delay the probe request packet 0-10 ms
 */

#define DELAYPROBE

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
#include "vmtp_cksum.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "vmtp_ether.h"

int	vmtp_hdlrq(), vmtp_hdlrp(), vmtp_hdlfrq(), vmtp_hdlfrp();
int	vmtp_hdlrpa(), vmtp_hdlrqa(), esp_hdlprp(), esp_hdlprq();
int 	vmtp_badfnct();

int	(*vmtp_handle[])() =
	{ vmtp_hdlrq,	vmtp_hdlrp,	vmtp_hdlfrq,	vmtp_hdlfrp,
	  vmtp_hdlrpa,	vmtp_hdlrqa,	esp_hdlprp,	esp_hdlprq,	
	  vmtp_badfnct,	vmtp_badfnct,	vmtp_badfnct,	vmtp_badfnct,
	  vmtp_badfnct,	vmtp_badfnct,	vmtp_badfnct,	vmtp_badfnct,
	};


/*
 * VMTP input routine. Assumes that the whole vmtpiphdr has been pulled up
 * by lower level input routines.
 */
vmtp_input(m)
	register struct mbuf *m;
{
	register struct vmtpiphdr *vi = mtod(m, struct vmtpiphdr *);
	register int vlen;
	register u_long cksum;
	register u_long type = vi->vi_type;

#ifdef	VMTPDEBUG
	printf("vmtp_input() m = 0x%x\n", m);
#endif

	if (vmtp_oppositebyteorder(type)) {
#ifdef	VMTPDEBUG
		printf("vmtp_input() byteswapping\n");
#endif
		vmtp_byteswap(m, sizeof(struct vmtp_header), 
				 sizeof(struct vmtpeid));
	}
	vlen = vi->vi_len;
	if (vlen != getvi_length(vi) + VH_DELTALEN) {
#ifdef	VMTP_DEBUG
	printf("vmtp_input(): vh_len = %d, vh_length = %d, should differ %d\n",
		vlen, getvi_length(vi), VH_DELTALEN);
#endif
		m_freem(m);
		return;
	}

	if (vmtp_securepacket(type)) {
		vmtp_inputsecure(m, vi, vlen);
		return;
	} 

	if (vmtp_oppositebyteorder(type))
		vmtp_byteswap(m, 
			sizeof(struct vmtp_header) + sizeof(struct vmtpeid),
			sizeof(struct vmtphdr) - sizeof(struct vmtpeid));
	
	if (!vmtp_domainserved(getvi_domain(vi))) {
#ifdef	VMTP_DEBUG
		printf("vmtp_input(): bad domain: %d\n", getvi_domain(vi));
#endif
		m_freem(m);
		return;
	}

	/*
	 * Checksum extended VMTP header and data.
	 * Skip vmtp_header for checksum computations
	 */

	vmtp_readcksum(m, sizeof(struct vmtp_header), vlen, cksum);
						/* result in cksum */

#ifdef	VMTPDEBUG
	printf("vmtp_input(): cksum in packet = 0x%x, computed = 0x%x\n",
		cksum, 
		vmtp_cksum(m,sizeof(struct vmtp_header), vlen-VMTP_CKSUMLEN));
#endif

	if (cksum != 0 && cksum != 
		vmtp_cksum(m, sizeof(struct vmtp_header), vlen-VMTP_CKSUMLEN)) {
#ifdef	VMTP_DEBUG
		vmtp_dumpvi(vi, "vi", "vmtp_input(): bad checksum");
#endif
		m_freem(m);
		vmtpstat.vst_badsum++;
		return;
	}

	/* 
	 * Drop the checksum
	 */
	m_adj(m, -VMTP_CKSUMLEN);

	vmtp_handle[getvi_fnctcode(vi)](vi);
} /* vmtp_input */

/*
 * Handle decryption of incomming packets
 */
vmtp_inputsecure(m, vi, vlen)
	register struct mbuf *m;
	register struct vmtpiphdr *vi;
	register int vlen;
{
	register struct vmtpcsr *csr;
	register u_long cksum;
	register u_long type = vi->vi_type;

#ifdef	ESP_DEBUG
	printf("vmtp_inputsecure(): called\n");
#endif

	csr = vmtp_maptocsr(vi->vi_client, vlocalcsrmap);
	if (csr != NULL) {
		if (esp_decrypt(m, 
			sizeof(struct vmtp_header) + sizeof(struct vmtpeid),
			vlen - sizeof(struct vmtpeid), csr->vc_encryptqual,
			csr->vc_key)) {
#ifdef	ESP_DEBUG
			printf("vmtp_inputsecure(): BAD encryption qual\n");
#endif
				m_freem(m);
				return;
		}
		if (vmtp_oppositebyteorder(type))
			vmtp_byteswap(m, 
			    sizeof(struct vmtp_header) + sizeof(struct vmtpeid),
			    sizeof(struct vmtphdr) - sizeof(struct vmtpeid));
	
		if (!vmtp_domainserved(getvi_domain(vi))) {
#ifdef	ESP_DEBUG
			printf("vmtp_inputsecure(): bad domain\n");
#endif
			m_freem(m);
			return;
		}


		/*
		 * Checksum extended VMTP header and data.
		 * Skip vmtp_header for checksum computations
		 */

		vmtp_readcksum(m, sizeof(struct vmtp_header), vlen,cksum);
						/* result in cksum */

#ifdef	ESP_DEBUG
		printf("vmtp_inputsecure(): received = 0x%x, computed = 0x%x\n",
			cksum, 
		vmtp_cksum(m,sizeof(struct vmtp_header), vlen-VMTP_CKSUMLEN));
#endif

		if (cksum != 0 && cksum != 
		vmtp_cksum(m, sizeof(struct vmtp_header), vlen-VMTP_CKSUMLEN)) {
#ifdef	ESP_DEBUG
		vmtp_dumpvi(vi, "vi", "vmtp_inputsecure(): bad checksum");
#endif
			m_freem(m);
			vmtpstat.vst_badencrsum++;
			return;
		}

		/* 
		 * Drop the checksum
		 */
		m_adj(m, -VMTP_CKSUMLEN);

		vmtp_handle[getvi_fnctcode(vi)](vi);
		return 0;
	}

	csr = vmtp_maptocsr(vi->vi_client, vremotecsrmap);
	if (csr == NULL) {
		csr = vmtp_newcsr(vi->vi_client, vremotecsrmap);
		if (csr == NULL) {
#ifdef	ESP_DEBUG
			printf("vmtp_inputsecure(): csr allocation failed\n");
#endif

			vmtp_sendrqa(NULL, vi, VMTP_BUSY);
			return;
		}
		/*
		 * Set some initial/default values. 
		 */
		csr->vc_mtu = VMTP_MAXBLKPACKET;
		csr->vc_inpktgap = VMTP_INPKTGAP;
		csr->vc_hostaddr = vi->vi_src;
		csr->vc_ifp = vi->vi_ifp;
		csr->vc_inpktgap = getvi_inpktgap(vi);
		csr->vc_roundtrip = VTS_ROUNDTRIP * 20; 	/* in ms */
		csr->vc_encryptqual = ENCRYPT_NONE;
		csr->vc_hdltimeo = vmtp_hdlrcsrtimeo;
		goto probe;
	} 
	if (csr->vc_encryptqual == ENCRYPT_NONE && 
	    csr->vc_state != VC_AWAITPROBE) {
stopandprobe:
		if (!vmtp_stoptimer(csr)) {
#ifdef	ESP_DEBUG
			printf("vmtp_inputsecure(): stoptimer FAILED!\n");
#endif
			m_freem(m);
			return;
		}
		/*
		 * Set up everything for a probe. Note that the server isn't
		 * known so the probingent field will be empty in the probe.
		 */
probe:
		m_freem(m);
		csr->vc_state = VC_AWAITPROBE;
		csr->vc_dlvrmsk = 0;
		csr->vc_vihdr->vi_addr = csr->vc_hostaddr;
		csr->vc_vihdr->vi_ifp = csr->vc_ifp;
		setvi_fnctcode(csr->vc_vihdr, VMTP_PROBEREQ);
		setvi_priority(csr->vc_vihdr, VPR_IMPORTANT);
		setvi_pgcount(csr->vc_vihdr, 0);

#define ei ((struct espiphdr *)csr->vc_vihdr)			
		seteiq_authdomain(ei, 2);
		seteiq_authversion(ei, 3);
		ei->eiq_mtu = vmtp_mtu(csr);
		esp_time(ei->ei_tmstamp);
		csr->vc_tmstamp = ei->ei_tmstamp;
		setei_control(ei, ECTL_SOP);
		ei->ei_code = ESP_FULLPROBE;
#ifdef	DELAYPROBE
		/*
		 * Can't see if server is a group or DRT bit in control 
		 * field - always delay
		 */
		timeout(esp_delayedprobe, csr, 0);
#else
		esp_sendprq(csr, csr->vc_vihdr);
		vmtp_starttimer(csr, ET_RETRANSMIT);
#endif	DELAYPROBE
		return;
#undef ei
	}
	if (esp_decrypt(m, sizeof(struct vmtp_header) + sizeof(struct vmtpeid),
		     vlen - sizeof(struct vmtpeid), csr->vc_encryptqual,
		     csr->vc_key)) {
#ifdef	ESP_DEBUG
		printf("vmtp_inputsecure(): BAD encryption qual\n");
#endif
			m_freem(m);
			return;
	}

	if (vmtp_oppositebyteorder(type))
		vmtp_byteswap(m, 
			sizeof(struct vmtp_header)+sizeof(struct vmtpeid),
			sizeof(struct vmtphdr) - sizeof(struct vmtpeid));
	
	if (!vmtp_domainserved(getvi_domain(vi))) {
#ifdef	ESP_DEBUG
		printf("vmtp_inputsecure(): bad domain\n");
#endif
		m_freem(m);
		return;
	}

	/*
	 * Checksum extended VMTP header and data.
	 * Skip vmtp_header for checksum computations
	 */

	vmtp_readcksum(m, sizeof(struct vmtp_header), vlen,cksum);
						/* result in cksum */

#ifdef	ESP_DEBUG
	printf("vmtp_inputsecure(): received = 0x%x, computed = 0x%x\n",
		cksum, 
		vmtp_cksum(m,sizeof(struct vmtp_header), vlen-VMTP_CKSUMLEN));
#endif

	if (cksum != 0 && cksum !=
		vmtp_cksum(m, sizeof(struct vmtp_header), vlen-VMTP_CKSUMLEN)) {
#ifdef	ESP_DEBUG
		printf("vmtp_inputsecure(): bad checksum: PROBE\n");
		vmtp_dumpvi(vi, "vi", "vmtp_inputsecure(): bad checksum");
#endif
		goto stopandprobe;
	}


	/* 
	 * Drop the checksum
	 */
	m_adj(m, -VMTP_CKSUMLEN);

	vmtp_handle[getvi_fnctcode(vi)](vi);
	return 0;
} /* vmtp_inputsecure */



/* 
 * Handle packets with bad function code
 */
vmtp_badfnct(vi)
	struct vmtpiphdr *vi;
{
#ifdef	VMTP_DEBUG
	printf("vmtp_input: received packet with unknown function code: 0x%x\n",
		getvi_fnctcode(vi));
#endif
	m_freem(dtom(vi));
} /* vmtp_badfnct */	


