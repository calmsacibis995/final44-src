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
 * $Log:	esp_hdlprp.c,v $
 * Revision 2.3  89/03/09  20:41:27  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:27  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_hdlprp.c,v 2.1 87/08/18 16:30:34 mrt Exp $
 */

/*
 * 	esp_hdlprp.c		2/26/87
 *	Written by Erik Nordmark
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
#include "vmtp_send.h"
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "vmtp_cksum.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "esp_cache.h"

/* 
 * Handle probe responses
 */
esp_hdlprp(ei)
	register struct espiphdr *ei;
{
	register struct vmtpcsr *csr;
	struct vmtpser *ser;
	struct mbuf *m = dtom(ei);
	struct vmtpsce *sc;
	int recvtime;
	int modify_transid = 0;	/* set when transid can be changed */
	int s;

#ifdef	ESP_DEBUG
	printf("esp_hdlprp(): ei = 0x%x\n", ei);
#endif
#ifndef	ESP_DEBUG
	printf("#");
#endif
	s  = splimp();

	csr = vmtp_maptocsr(ei->ei_probedent, vremotecsrmap);

	if (csr == NULL) {
		splx(s);
#ifdef	ESP_DEBUG
		printf("esp_hdlprp(): no client - discarding\n");
#endif
		m_freem(m);		
		return;
	}
	if (!esp_securedomain(geteip_authdomain(ei)) && 
	    (ei->ei_tmstamp != csr->vc_tmstamp)) {
#ifdef	ESP_DEBUG
		printf("esp_hdlprp(): old response - discarding\n");
		printf("\tei: 0x%x, csr: 0x%x\n", ei->ei_tmstamp, 
			csr->vc_tmstamp);
#endif	
		splx(s);
		m_freem(m);		
		return;
	}
	
	if (!esp_authdomainserved(geteip_authdomain(ei)) ||
	    !esp_authversionserved(geteip_authversion(ei))) {
		splx(s);
#ifdef	ESP_DEBUG
	printf("esp_hdlprp(): BAD authentification version or domain\n");
	printf("\tdomain = %d, version = %d\n", geteip_authdomain(ei),
		geteip_authversion(ei));
#endif
		m_freem(m);		
		return;
	}


	if (csr->vc_state == VC_AWAITPROBE && 
	    !esp_notifyprobing(getei_control(ei))) {
		/*
		 * The probing entity/server is waiting for this response.
		 * Make sure that it's the right kind of response i.e.
 		 * secure domain if server requires security.
		 */
		ser = vmtp_maptoserver(ei->ei_probingent);
		if (ser) {
			if (vmtp_securityreq(ser) && 
			    !esp_securedomain(geteip_authdomain(ei))) {
#ifdef	ESP_DEBUG
				printf("esp_hdlprp(): response not secure!!\n");
#endif
				splx(s);
				m_freem(m);
				return;
			}
		}
		if (!vmtp_stoptimer(csr)) {
			splx(s);
#ifdef	ESP_DEBUG
			printf("esp_hdlprp():stoptimer FAILED!\n");
#endif
			m_freem(m);		
			return;
		}
		splx(s);

	}


	esp_time(recvtime);
	csr->vc_probecode = ei->ei_code;

	switch (ei->ei_code & 0x00ffffff) {
		case VMTP_OK: 
			break;

		case VMTP_BUSY:
			/*
			 * Drop this packet and retransmit when timing out
			 */
			csr->vc_mtu = mtutoblocks(ei->eip_mtu);
			if (csr->vc_mtu <= 0)
				csr->vc_mtu = VMTP_MAXBLKPACKET;
			csr->vc_inpktgap = getei_inpktgap(ei);
			csr->vc_hostaddr = ei->ei_src;
			csr->vc_ifp = ei->ei_ifp;
			csr->vc_roundtrip = recvtime - ei->ei_tmstamp;

			if (vcf_group(csr))
				esp_copyinfo(csr);

			if (csr->vc_state == VC_AWAITPROBE &&
			    !esp_notifyprobing(getei_control(ei))) 
				vmtp_starttimer(csr, vts_retransmit(csr)); 
			else
				splx(s);
			m_freem(m);
			return;
		case VMTP_NONEXIST:
		case VMTP_NOPERMISSN:
		case VMTP_PROERROR:
		case VMTP_MIGRATED:
		default:
		{
#ifdef	ESP_DEBUG
			printf("esp_hdlprp(): BAD return code\n");
#endif
			if (esp_findentry(ei->ei_probedent)) 
				esp_removeentry(ei->ei_probedent);

			if (esp_notifyprobing(getei_control(ei))) {
				if (vmtp_stoptimer(csr)) {
					splx(s);
#ifdef	ESP_DEBUG
				printf("esp_hdlprp():waking up the probing\n");
#endif
					csr->vc_action = VCA_DELIVER;
					wakeup(csr);
				}
				else {
					splx(s);
#ifdef	ESP_DEBUG
	printf("esp_hdlprp(): stoptimer FAILED: can't wake up the probing\n");
#endif
				}
			} else if (csr->vc_state == VC_AWAITPROBE) {
				vmtp_starttimer(csr, vts_discardcsr(csr));
			} 
			m_freem(m);
			return;
		}
	}

	/* update info in csr */
	/* compute roundtrip delay */

	csr->vc_mtu = mtutoblocks(ei->eip_mtu);
	if (csr->vc_mtu <= 0)
		csr->vc_mtu = VMTP_MAXBLKPACKET;
	csr->vc_inpktgap = getei_inpktgap(ei);
	csr->vc_hostaddr = ei->ei_src;
	csr->vc_ifp = ei->ei_ifp;
	csr->vc_roundtrip = recvtime - ei->ei_tmstamp;

	if (csr->vc_state != VC_RECVREQ &&  csr->vc_state != VC_PROCESSING && 
	    vmtp_stoptimer(csr)) {
#ifdef	ESP_DEBUG
		printf("esp_hdlprp(): timer stopped\n");
#endif
		modify_transid = 1;
	}
		

	switch (geteip_authversion(ei)) {
		case 1: 
		{
			struct av1 *auth = &(ei->eip_authent.au_av1);

			if (modify_transid)
				csr->vc_transid = ei->ei_transid;
			csr->vc_processid = auth->ai_processid;
			csr->vc_principalid = auth->ai_principalid;
			csr->vc_effprincipalid = auth->ai_effprincipalid;
			break;
		}
		case 2: 
		{
			if (esp_saveversion2(&m, csr, ei, modify_transid)) {
#ifdef	ESP_DEBUG
				printf("esp_hdlprp():saveversion2 FAILED!\n");
#endif
				if (modify_transid)
					vmtp_starttimer(csr, vts_discardcsr(csr));
				splx(s);
				m_freem(m);
				return;
			}
			ei = mtod(m, struct espiphdr *);
			break;
		}
		case 3: 
		{
			if (esp_saveversion3(&m, csr, ei, modify_transid)) {
#ifdef	ESP_DEBUG
				printf("esp_hdlprp():saveversion3 FAILED!\n");
#endif
				if (modify_transid)
					vmtp_starttimer(csr, vts_discardcsr(csr));
				splx(s);
				m_freem(m);
				return;
			}
			ei = mtod(m, struct espiphdr *);
			break;
		}
	}	

	/* update info in server cache */

	if ((sc = esp_findentry(ei->ei_probedent)) == NULL)
		if (!vmtp_groupeid(ei->ei_probedent))
			sc = esp_allocentry(ei->ei_probedent);
	if (sc) {
		sc->ve_hostaddr = ei->ei_src;	
		sc->ve_ifp = ei->ei_ifp;
		sc->ve_gap = getei_inpktgap(ei);
		sc->ve_roundtrip = csr->vc_roundtrip;
		sc->ve_mtu = csr->vc_mtu;
		sc->ve_principalid = csr->vc_principalid;
		sc->ve_flags |= VEF_HOSTADDR | VEF_PRINCIPAL;
	}

#ifdef	ESP_DEBUG
	printf("esp_hdlprp(): dispatching on state et.c\n");
#endif
	csr->vc_verifyint = 0;

	if (vcf_group(csr))
		esp_copyinfo(csr);

	if (modify_transid)
		vmtp_starttimer(csr, vts_discardcsr(csr));

	if (esp_notifyprobing(getei_control(ei))) {
		if (vmtp_stoptimer(csr)) {
			splx(s);
#ifdef	ESP_DEBUG
			printf("esp_hdlprp(): A user was waiting for this\n");
#endif
			csr->vc_action = VCA_DELIVER;
			wakeup(csr);
		}
		else {
			splx(s);
#ifdef	ESP_DEBUG
	printf("esp_hdlprp(): stoptimer FAILED: can't wake up the probing\n");
#endif
		}
	}
	else if (csr->vc_state == VC_AWAITPROBE) {

#ifdef	ESP_DEBUG
		printf("esp_hdlprp(): server was waiting for this\n");
#endif
		csr->vc_state = VC_AWAITREQ;
		vmtp_starttimer(csr, vts_discardcsr(csr));
	}
	m_freem(m);
} /* esp_hdlprp */


/*
 * Store the information in the authenticator into the csr
 */
esp_saveversion2(a_m, csr, ei, modify_transid)
	struct mbuf **a_m;
	struct vmtpcsr *csr;
	struct espiphdr *ei;
	int modify_transid;
{
	struct av2 *auth = &(ei->eip_authent.au_av2);
	struct av2auth *ap;

#ifdef	ESP_DEBUG
	printf("esp_saveversion2(): called\n");
#endif
	if (ei->ei_len != sizeof(struct esphdr) 
	    + auth->ai_authsize + VMTP_CKSUMLEN) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion2(): BAD LENGTH: %d != %d\n", 
		    ei->ei_len,
		    sizeof(struct esphdr) + auth->ai_authsize + VMTP_CKSUMLEN);
#endif	
		return -1;
	}

	if ((*a_m)->m_len < sizeof(struct espiphdr) + sizeof(struct av2auth)) {
		*a_m = m_pullup(*a_m, 
			sizeof(struct espiphdr) + sizeof(struct av2auth));
		if (!*a_m) {
#ifdef	ESP_DEBUG
			printf("esp_saveversion2(): pullup FAILED!!\n");
#endif
			return -1;					
		}
		ei = mtod(*a_m, struct espiphdr *);
		auth = &(ei->eip_authent.au_av2);
	}
	ap = eitoav2auth(ei);

	if (ap->av2a_pwdlen) {
		if (csr->vc_password)
			m_freem(csr->vc_password);

		csr->vc_password = m_copy(*a_m, av2a_passwordoff(ap),
					   ap->av2a_pwdlen);
		if (!csr->vc_password) {
#ifdef	ESP_DEBUG
			printf("esp_saveversion2(): m_copy password FAILED!!\n");
#endif
			return -1;
		}
	} else 
		csr->vc_password = NULL;

	if (ap->av2a_princlen) {
		if (csr->vc_principal)
			m_freem(csr->vc_principal);

		csr->vc_principal = m_copy(*a_m, av2a_principaloff(ap),
					   ap->av2a_princlen);
		if (!csr->vc_principal) {
#ifdef	ESP_DEBUG
			printf("esp_saveversion2(): m_copy principal FAILED!!\n");
#endif
			return -1;
		}
	} else 
		csr->vc_principal = NULL;
						
	if (modify_transid)
		csr->vc_transid = ei->ei_transid;
	csr->vc_processid = auth->ai_processid;
	csr->vc_principalid = auth->ai_principalid;
	csr->vc_timelimit = ap->av2a_timelimit;
	return 0;
} /* esp_saveversion2 */

/*
 * Store the information in the authenticator into the csr
 */
esp_saveversion3(a_m, csr, ei, modify_transid)
	struct mbuf **a_m;
	struct vmtpcsr *csr;
	struct espiphdr *ei;
	int modify_transid;
{
	struct av3 *auth = &(ei->eip_authent.au_av3);
	struct av3auth *ap;
	union vmtpkey key;
	struct mbuf *n;
	int length;

#ifdef	ESP_DEBUG
	printf("esp_saveversion3(): called\n");
#endif
	if (ei->ei_len != sizeof(struct esphdr) 
	    + auth->ai_authsize + VMTP_CKSUMLEN) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): BAD LENGTH: %d != %d\n", 
		    ei->ei_len,
	 	    sizeof(struct esphdr) + auth->ai_authsize + VMTP_CKSUMLEN);
#endif	
		return -1;
	}

	if (auth->ai_encryptqual == ENCRYPT_NONE) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): encryption qual == 0!\n");
#endif
		return -1;
	}

	length = auth->ai_authsize;


	if ((*a_m)->m_len < sizeof(struct espiphdr) + sizeof(struct av3auth)) {
		*a_m = m_pullup(*a_m, 
			sizeof(struct espiphdr) + sizeof(struct av3auth));
		if (!*a_m) {
#ifdef	ESP_DEBUG
			printf("esp_saveversion3(): pullup FAILED!!\n");
#endif
			return -1;					
		}
		ei = mtod(*a_m, struct espiphdr *);
		auth = &(ei->eip_authent.au_av3);
	}
	ap = eitoav3auth(ei);

	if (esp_decryptauth(*a_m, ap, auth->ai_encryptqual, length) < 0) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): decryptauth failed!\n");
#endif
		return -1;
	}

	/*
	 * Decrypt the response data
	 */
	if (ap->av3a_keylen != sizeof(union vmtpkey)) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): bad key length\n");
#endif
		return -1;
	}

	n = m_copy(*a_m, av3a_keyoff(ap), ap->av3a_keylen);
	if (!n) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): m_copy key FAILED!!\n");
#endif
		return -1;
	}

	key = *(mtod(n, union vmtpkey *));
	m_freem(n);

#ifdef	ESP_DEBUG
	printf("esp_saveversion3(): encrypted RESPONSE DATA\n");
	printf("\tai_cksum = 0x%x, ai_transid = 0x%x\n", 
		auth->ai_cksum, auth->ai_transid);
	printf("\tai_tmstamp = 0x%x, ai_reserved = 0x%x\n",
		auth->ai_tmstamp, auth->ai_reserved);
#endif
	if (esp_decrypt(*a_m, av3aresp_off, 16, auth->ai_encryptqual, key)) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): BAD encryptqual\n");
#endif
		return -1;
	}
	
#ifdef	ESP_DEBUG
	printf("esp_saveversion3(): RESPONSE DATA\n");
	printf("\tai_cksum = 0x%x, ai_transid = 0x%x\n", 
		auth->ai_cksum, auth->ai_transid);
	printf("\tai_tmstamp = 0x%x, ai_reserved = 0x%x\n",
		auth->ai_tmstamp, auth->ai_reserved);
#endif

	if (auth->ai_cksum != vmtp_cksum(*a_m, av3aresp_off + 4, 12)) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): BAD cksum for response data\n");
		printf("\treceived: 0x%x, computed: 0x%x\n", auth->ai_cksum,
			vmtp_cksum(*a_m, av3aresp_off + 4, 12));
#endif
		return -1;
	}

	if (auth->ai_tmstamp != csr->vc_tmstamp) {
#ifdef	ESP_DEBUG
		printf("esp_saveversion3(): BAD timetamp\n");
		printf("\treceived: 0x%x, computed: 0x%x\n", auth->ai_tmstamp,
			csr->vc_tmstamp);
#endif
		return -1;
	}

	if (ap->av3a_princlen) {
		if (csr->vc_principal)
			m_freem(csr->vc_principal);

		csr->vc_principal = m_copy(*a_m, av3a_principaloff(ap),
					   ap->av3a_princlen);
		if (!csr->vc_principal) {
#ifdef	ESP_DEBUG
			printf("esp_saveversion3(): m_copy principal FAILED!!\n");
#endif
			return -1;
		}
	} else 
		csr->vc_principal = NULL;

	if (modify_transid)
		csr->vc_transid = auth->ai_transid;
	csr->vc_encryptqual = auth->ai_encryptqual;
	csr->vc_timelimit = ap->av3a_timelimit;
	csr->vc_processid = ap->av3a_processid;
	csr->vc_principalid = ap->av3a_principalid;
	csr->vc_key = key;


#ifdef	ESP_DEBUG
	printf("esp_saveversion3(): done!\n");
#endif
						
	return 0;
} /* esp_saveversion3 */

