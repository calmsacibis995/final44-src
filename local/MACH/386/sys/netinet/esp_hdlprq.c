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
 * $Log:	esp_hdlprq.c,v $
 * Revision 2.3  89/03/09  20:41:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:33  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_HOSTID: modified to use vmtp_hostid.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_hdlprq.c,v 2.1 87/08/18 16:30:38 mrt Exp $
 */

/*
 * 	esp_hdlprq.c		2/26/87
 *	Written by Erik Nordmark
 */

/*
 * TODO
 *	Is it necessery to remap the entity id to the csr before doing the 
 *	wakeup? The csr might have been freed by PRU_DETACH/PRU_SHUTDOWN.
 */

#if	MACH_VMTP

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
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
#include "vmtp_cksum.h"
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "esp_cache.h"
#include "vmtp_ether.h"

/* 
 * Handle probe requests
 */
esp_hdlprq(ei)
	register struct espiphdr *ei;
{
	register struct vmtpcsr *csr;
	struct mbuf *m = dtom(ei);
	struct vmtpsce *sc;
	u_long encryptqual;
	u_long code;	/* response code */
	u_long control = getei_control(ei);
	int wakeupfl = 0;
	int length;
	int s;

#ifdef	ESP_DEBUG
	printf("esp_hdlprq(): ei = 0x%x\n", ei);
#endif
#ifndef	ESP_DEBUG
	printf("!");
#endif

	if (ei->ei_len != sizeof(struct esphdr)+VMTP_CKSUMLEN) {
#ifdef	ESP_DEBUG
		printf("esp_hdlprq(): BAD LENGTH: %d\n", ei->ei_len);
#endif	
		m_freem(m);
		return;
	}

	if (esp_probeblock(ei->ei_code)) {
		/* 
		 * Determine if conflicting with locally assigned eid's.
 		 * Somewhat conservative.
		 */
#if	VMTP_HOSTID
		if ((vmtp_eidtoinaddr(ei->ei_probedent) != vmtp_hostid)
#else	VMTP_HOSTID
		if ((vmtp_eidtoinaddr(ei->ei_probedent) != hostid)
#endif	VMTP_HOSTID
		    && (getve_tmstamp(ei->ei_probedent) + ESP_PROBEBLOCKSIZE <
		      0xfffffff)) {
			if (!ei->ei_multicast) {
#ifdef	ESP_DEBUG
				printf("esp_hdlprq(): BLOCK not used\n");
#endif
				seteip_authversion(ei, geteiq_authversion(ei));
				seteip_authdomain(ei, geteiq_authdomain(ei));
				ei->eip_mtu = VMTP_MAXBLKPACKET * VMTP_BLKSIZE 
						+ sizeof(struct espiphdr);
				setei_inpktgap(ei, VMTP_INPKTGAP);
				setei_control(ei,control & ~ECTL_SOP);
				ei->ei_code = VMTP_NONEXIST;
				esp_sendprp(NULL, ei, 0, ENCRYPT_NONE);
				return;
			} else {
				m_freem(m);
				return;
			}
		} else {
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): part of BLOCK could be used\n");
#endif
			seteip_authversion(ei, geteiq_authversion(ei));
			seteip_authdomain(ei, geteiq_authdomain(ei));
			ei->eip_mtu = VMTP_MAXBLKPACKET * VMTP_BLKSIZE 
						+ sizeof(struct espiphdr);;
			setei_inpktgap(ei, VMTP_INPKTGAP);
			setei_control(ei, control & ~ECTL_SOP);
			ei->ei_code = VMTP_BUSY;
			esp_sendprp(NULL, ei, 0, ENCRYPT_NONE);
			return;
		}
	}

	if (!esp_authdomainserved(geteiq_authdomain(ei)) ||
	    !esp_authversionserved(geteiq_authversion(ei))) {
#ifdef	ESP_DEBUG
	printf("esp_hdlprp(): BAD authentification version or domain\n");
#endif
		m_freem(m);		
		return;
	}


	s = splimp();
	csr = vmtp_maptocsr(ei->ei_probedent, vlocalcsrmap);

	if (csr == NULL && vmtp_groupeid(ei->ei_probedent)) {
#ifdef	ESP_DEBUG
		printf("esp_hdlprq(): probing a group\n");
#endif
		csr = vmtp_maptocsr(vmtp_firstgroupmember(ei->ei_probedent),
				    vlocalcsrmap);
	}

	if (csr == NULL) {
		if (ei->ei_multicast) {
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): multicast - discarding\n");
#endif
			splx(s);
			m_freem(m);
			return;
		}
		splx(s);
#ifdef	ESP_DEBUG
		printf("esp_hdlprq(): NONEXIST entity\n");
#endif
		seteip_authversion(ei, geteiq_authversion(ei));
		seteip_authdomain(ei, geteiq_authdomain(ei));
		ei->eip_mtu = VMTP_MAXBLKPACKET * VMTP_BLKSIZE 
				+ sizeof(struct espiphdr);;
		setei_inpktgap(ei, VMTP_INPKTGAP);
		setei_control(ei, control & ~ECTL_SOP);
		ei->ei_code = VMTP_NONEXIST;
		esp_sendprp(NULL, ei, 0, ENCRYPT_NONE);
		return;
	}

	/* 
	 * Test if permission.
	 * Note that a client can only use authversion 1 when probing its
	 * server.
	 */

	if ((geteiq_authversion(ei) == 2 
	     && !vmtp_sameeid(csr->vc_server, ei->ei_probingent)
	     && !vcf_group(csr)) ||
	    (!vmtp_securepacket(ei->ei_type) 
	     && esp_securedomain(geteiq_authdomain(ei)) 
	     && geteiq_authversion(ei) != 3)) {
		/*
		 * Send a non-encypted response
		 */
		splx(s);
#ifdef	ESP_DEBUG
		printf("esp_hdlprq(): no permission!\n");
#endif
		seteip_authversion(ei, geteiq_authversion(ei));
		seteip_authdomain(ei, geteiq_authdomain(ei));
		ei->eip_mtu = vmtp_mtu(csr);	
		setei_inpktgap(ei, VMTP_INPKTGAP);
		setei_control(ei, control & ~ECTL_SOP);
		ei->ei_code = VMTP_NOPERMISSN;
		esp_sendprp(NULL, ei, 0, ENCRYPT_NONE);
		return;
	}

	if (csr->vc_state == VC_AWAITRESP && 
	    esp_signalprobe(control) &&
	    !vmtp_datagram(csr->vc_code)) {
		/* 
		 * Stop the timer. Later the vmtp module will be told
		 * to retransmit the request
		 */
		if (!vmtp_stoptimer(csr)) {
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): stoptimer FAILED!\n");
#endif
			m_freem(m);
			splx(s);
			return;
		}
		wakeupfl++;
		splx(s);
	}

	encryptqual = csr->vc_encryptqual;
	length = 0;

	/* record info in server cache unless prober is a group */

	if (!vcf_group(csr) && !vmtp_groupeid(ei->ei_probingent)) {
		if ((sc = esp_findentry(ei->ei_probingent)) == NULL) { 
			sc = esp_allocentry(ei->ei_probingent);
			sc->ve_roundtrip = VTC_ROUNDTRIP * 20;	
		}

		sc->ve_hostaddr = ei->ei_src;	
		sc->ve_ifp = ei->ei_ifp;
		sc->ve_flags |= VEF_HOSTADDR;
		sc->ve_gap = getei_inpktgap(ei);
		sc->ve_mtu = mtutoblocks(ei->eiq_mtu);
		if (sc->ve_mtu <= 0)
			sc->ve_mtu = VMTP_MAXBLKPACKET;


		/*
 		 * Can't update the information in the csr unless this is the 
		 * same server as the one in the csr i.e. not a multicasted 
		 * request.
		 */
		if (vmtp_sameeid(ei->ei_probingent, csr->vc_server)) {
			csr->vc_hostaddr = ei->ei_src;
			csr->vc_ifp = ei->ei_ifp;
			csr->vc_inpktgap = getei_inpktgap(ei);
			csr->vc_mtu = sc->ve_mtu;
		}
	}

	/* build a probe response packet according to the code */

	seteip_authversion(ei, geteiq_authversion(ei));
	seteip_authdomain(ei, geteiq_authdomain(ei));
	ei->eip_mtu = vmtp_mtu(csr);	
	setei_inpktgap(ei, VMTP_INPKTGAP);

	code = 0;

	switch (ei->ei_code & 0x00ffffff) {
		case ESP_MINPROBE:
		{
			struct av1 *auth = &(ei->eip_authent.au_av1);

#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): MINPROBE\n");
#endif
			/*
			 * If this is part of secure communication sendpacket
			 * will encrypt the response automatically.
			 */
			ei->ei_transid = csr->vc_transid;

			auth->ai_processid = csr->vc_processid;
			auth->ai_principalid = csr->vc_principalid;
			auth->ai_effprincipalid = csr->vc_effprincipalid;
			break;
		}
		case ESP_FULLPROBE:
		{
		    int len1, len2;
		    struct mbuf *n;

		    /*
		     * Different information depending on the domain
		     */

		    if (!esp_securedomain(geteiq_authdomain(ei))) { 
			struct av2 *auth = &(ei->eip_authent.au_av2);
			struct av2auth *ap;
	
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): FULLPROBE - not secure\n");
#endif
			auth->ai_processid = csr->vc_processid;
			auth->ai_principalid = csr->vc_principalid;
			auth->ai_reserved = 0;

			/*
			 * Don't want to deal with cluster case below.
			 * The request packet is not in a cluster since
			 * it's short.
			 */
			if (m->m_off > MMAXOFF || m->m_len + m->m_off +
			    sizeof(struct av2auth) - MMINOFF > MLEN) {
				n = m_get(M_DONTWAIT, MT_DATA);
				if (!n) {
#ifdef	ESP_DEBUG
					printf("esp_hdlprq(): m_get failed!\n");
#endif
					goto failed;	
				}
				n->m_len = sizeof(struct av2auth);
				m->m_next = n;
				ap = mtod(n, struct av2auth *);
			} else {
				/* pad the header mbuf */
				m->m_len += sizeof(struct av2auth);
				ap = eitoav2auth(ei);
			}
			if (csr->vc_password) {
				n = m_copy(csr->vc_password, 0, M_COPYALL);
				if (!n) {
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): m_copy password failed!\n");
#endif
					m_adj(m, -sizeof(struct av2auth));
					goto failed;	
				}
				len1 = m_length(n);
				m_cat(m, n);
			} else 
				len1 = 0;

			if (csr->vc_principal) {
				n = m_copy(csr->vc_principal, 0, M_COPYALL);
				if (!n) {
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): m_copy principal failed!\n");
#endif
				    	m_adj(m, -sizeof(struct av2auth)-len1);
					goto failed;	
				}
				len2 = m_length(n);
				m_cat(m, n);
			} else
				len2 = 0;
			ap->av2a_timelimit = csr->vc_timelimit;
			ap->av2a_pwdlen = len1;
			ap->av2a_princlen = len2;
			length = len1 + len2 + sizeof(struct av2auth);					auth->ai_authsize = length;
				
		    } else {
			struct av3 *auth = &(ei->eip_authent.au_av3);

#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): FULLPROBE - secure\n");
#endif
			/* 
			 * The first probe - make sure it is sent
			 * unencrypted!
			 */
			encryptqual = 0;

			ei->ei_transid = 0;

			/* get the encrypted authenticator */

			if (csr->vc_authenticator) {
				n = m_copy(csr->vc_authenticator, 0, M_COPYALL);
				if (!n) {
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): m_copy authenticator failed!\n");
#endif
						goto failed;
				}
				len1 = m_length(n);
				m_cat(m, n);
			} else 
				len1 = 0;
			auth->ai_transid = csr->vc_transid;
			auth->ai_tmstamp = ei->ei_tmstamp;
			ei->ei_tmstamp =0;
			auth->ai_reserved = 0;
			auth->ai_cksum = vmtp_cksum(m, av3aresp_off + 4, 12);
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): RESPONSE DATA\n");
			printf("\tai_cksum = 0x%x, ai_transid = 0x%x\n", 
				auth->ai_cksum, auth->ai_transid);
			printf("\tai_tmstamp = 0x%x, ai_reserved = 0x%x\n",
				auth->ai_tmstamp, auth->ai_reserved);
#endif
			esp_encrypt(m, av3aresp_off, 16, csr->vc_encryptqual,
					csr->vc_key);
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): encrypted RESPONSE DATA\n");
			printf("\tai_cksum = 0x%x, ai_transid = 0x%x\n", 
				auth->ai_cksum, auth->ai_transid);
			printf("\tai_tmstamp = 0x%x, ai_reserved = 0x%x\n",
				auth->ai_tmstamp, auth->ai_reserved);
#endif
			auth->ai_encryptqual = csr->vc_encryptqual;
			auth->ai_authsize = length = len1;
		    } 
		    if (length) {
			code = VU_SDA;
		    }		
		    break;
		}
		default:
		{
#ifdef	ESP_DEBUG
			printf("esp_hdlprq(): BAD code: 0x%x\n", ei->ei_code);
#endif
			splx(s);
			m_freem(m);
			return;
		}
	}

	setei_control(ei, control & ~ECTL_SOP);
	ei->ei_code = VMTP_OK | code;

	if (!wakeupfl)
		splx(s);
#ifdef	ESP_DEBUG
	printf("esp_hdlprq(): length = %d, m_len = %d\n", length, 
		m_length(dtom(ei)));
#endif
	esp_sendprp(csr, ei, length, encryptqual);		/* frees m */


	if (wakeupfl) {
		/* 
		 * Signal the vmtp module to retransmit the request
		 */
		s = splimp();
#ifdef	ESP_DEBUG
		printf("esp_hdlprq():waking up client for retransmission\n");
#endif
		if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
			csr->vc_txmsk =  vmtp_usrdlvrmskset(csr->vc_code) 
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}
		csr->vc_rexmtcnt = 0;
		csr->vc_tleft = vtc_awaitresp(csr);	/* timer value */
		csr->vc_action = VCA_RETRANS;
		splx(s);
		wakeup(csr);			
		return;
	}
	return;

failed:
	setei_control(ei, control & ~ECTL_SOP);
	code = VMTP_BUSY;
	if (!wakeupfl)
		splx(s);
	esp_sendprp(csr, ei, length, encryptqual);		/* frees m */
	if (wakeupfl) {
		/*
		 * Timer was stopped but can't wake the guy up.
		 * Restart the timer and rely on retransmission
		 */
		vmtp_starttimer(csr,vtc_awaitresp(csr));
	}
	return;

} /* esp_hdlprq */


#endif	MACH_VMTP
