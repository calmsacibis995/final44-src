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
 * $Log:	esp_probe.c,v $
 * Revision 2.4  89/03/09  20:41:59  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:56:58  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 09-Aug-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	gcc bug work around.
 *
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_HOSTID: modified to not byte-swap IP addresses.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_probe.c,v 2.2 88/08/09 17:45:30 rvb Exp $
 */

/*
 * 	esp_probe.c		2/26/87
 *	Written by Erik Nordmark
 */

/*
 * TODO
 * 	Protection when local csr is found! Also check that probing is 
 *	involved in transaction i.e. either client or server of the probed!
 *	Release some of the checks - possible to get the principal id for
 *	everyone (used by secure protocol).
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
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "esp_cache.h"
#include "esp_probe.h"

#ifdef	VMTP_ETHER
#include "vmtp_ether.h"
#endif

/*
 * Probe a remote entity. Called from vmtp_usrreq when the request is
 * PRU_VERIFY
 */
esp_probe(csr, m)
	struct vmtpcsr *csr;
	struct mbuf *m;
{
	struct espprobedata *data = mtod(m, struct espprobedata *); 
	struct vmtpeid probing,probed;
	struct vmtpser *ser;
	struct vmtpcsr *csr1;	/* used for timeouts and retransmissions */
	struct espiphdr *ei; 
	struct vmtpsce *sc;
	u_long probe;		/* type of probe: FULL or MIN */
	int error = 0;
	u_char ipttl;

#ifdef	ESP_DEBUG
	printf("esp_probe(): called\n");
#endif

	if (m == NULL) {
#ifdef	ESP_DEBUG
		printf("esp_probe(): m == NULL\n");
#endif
		return EINVAL;
	}

	if (csr == NULL) {
#ifdef	ESP_DEBUG
		printf("esp_probe(): no client address\n");
#endif
		return EADDRNOTAVAIL;
	}

	if (vmtp_emptyeid(data->es_probedent))
		data->es_probedent = csr->vc_client;

	probing = csr->vc_client;
	probed = data->es_probedent;
	ipttl = csr->vc_ipttl;

	/* check if local entity */
	csr = vmtp_maptocsr(probed, vlocalcsrmap);
	if (csr) {
		/*
		 * Check if invoker has right to access the info 
		 */
		if (!esp_accessright(csr, probing, data->es_request)) {
			data->es_code = VMTP_NOPERMISSN;
			return 0;
		}

		error = esp_putprobedata(csr, data);
		if (error)
			return error;
		data->es_request |= EPR_NEW;		
		data->es_code = VMTP_OK;
		data->es_inpktgap = VMTP_INPKTGAP;
		data->es_hostaddr.va_type = VAT_INET;
		data->es_hostaddr.va_inet = vmtp_eidtoinaddr(probed);
		data->es_mtu = vmtp_mtu(csr);
		return 0;
	}

	probe = 0;	/* type of probe not determined yet */

	if (!esp_newinfo(data->es_request)) {
		u_short r = data->es_request;
		
		ser = vmtp_maptoserver(probing);
		if (ser == NULL) {
			if (data->es_request != EPR_COMM && 
			    data->es_request != 0)
				data->es_request |= EPR_NEW;
			goto send;
		}

		/*
		 * Check if a probe request has to be sent
		 */
		if (esp_processinfo(r) || esp_principalinfo(r))
			if (! vmtp_authreq(ser) && ! vmtp_securityreq(ser))
				data->es_request |= EPR_NEW;		
	
		if (esp_encryptinfo(r) && !vmtp_securityreq(ser)) {
			data->es_code = VMTP_NOPERMISSN;
			return 0;
		}
		if (esp_effprincinfo(r)) {
			data->es_request |= EPR_NEW;
			probe = ESP_MINPROBE;
		}			
		if (esp_pwdinfo(r) || 
		    (esp_principalinfo(r) && data->es_length)) {
			data->es_request |= EPR_NEW;		
			data->es_request &= ~EPR_EFFP;		
			probe = ESP_FULLPROBE;
		}			
	} else {
		u_short r = data->es_request;

		if (esp_pwdinfo(r) || 
		    (esp_principalinfo(r) && data->es_length)) {
			data->es_request |= EPR_NEW;		
			data->es_request &= ~EPR_EFFP;		
			probe = ESP_FULLPROBE;
		}			
	}
send:
	if (probe == 0)
		probe = ESP_MINPROBE;			

	/* find a remote csr for the probed entity */

	csr = vmtp_maptocsr(probed, vremotecsrmap);
	if (csr == NULL) {
#ifdef	ESP_DEBUG
		printf("esp_probe(): allocating a remote csr\n");
#endif

		csr = vmtp_newcsr(probed, vremotecsrmap);
		if (csr == NULL) {
#ifdef	ESP_DEBUG
			printf("esp_probe(): csr allocation failed\n");
#endif
			return ENOBUFS;
		}
		csr->vc_mtu = VMTP_MAXBLKPACKET;
		csr->vc_inpktgap = VMTP_INPKTGAP;
		csr->vc_roundtrip = VTS_ROUNDTRIP * 20; 	/* in ms */
		csr->vc_encryptqual = ENCRYPT_NONE;

		csr1 = csr;	/* can use this csr for everything */
		data->es_request |= EPR_NEW;		
	} else if (!esp_newinfo(data->es_request)) {
		/*
		 * check if authorized to get info
		 */
		if (!esp_accessright(csr, probing, data->es_request)) 
			data->es_code = VMTP_NOPERMISSN;
		else {
			error = esp_putprobedata(csr, data);
			data->es_code = VMTP_OK;
		}
		return error;
	} else {
		struct mbuf *m;

#ifdef	ESP_DEBUG
		printf("esp_probe(): copying the existing csr\n");
#endif

		csr1 = vmtp_alloccsr();
		if (!csr1) {
#ifdef	ESP_DEBUG
			printf("esp_probe(): alloccsr failed!\n");
#endif
			return ENOBUFS;
		}
		bcopy((caddr_t)csr, (caddr_t)csr1, sizeof(struct vmtpcsr));
		csr1->vc_qhead = NULL;
		csr1->vc_next = NULL;
		csr1->vc_qnext = csr1->vc_qprev = NULL;
		m = vmtp_copyvihdr(csr->vc_vihdr);
		if (!m) {
#ifdef	ESP_DEBUG
			printf("esp_probe(): vmtp_copyvihdr failed!\n");
#endif
			vmtp_dealloccsr(csr1);
			return ENOBUFS;
		}
		csr1->vc_vihdr = mtod(m, struct vmtpiphdr *);
	}
		
	if ((sc = esp_findentry(probed)) != NULL) {
		csr1->vc_hostaddr = sc->ve_hostaddr;
		csr1->vc_ifp = sc->ve_ifp;
		csr1->vc_inpktgap = sc->ve_gap;
		csr1->vc_roundtrip = sc->ve_roundtrip;
		csr1->vc_mtu = sc->ve_mtu;
	} else {
#ifdef	VMTP_ETHER
		if (ipttl == 1) {
			struct vmtpeid eid;

			eid.ve_inaddr = VMTP_HOSTGROUP;
			vmtp_setmulticastaddr(csr1->vc_hostaddr, eid);
		} else
#endif	VMTP_ETHER
		{
			csr1->vc_hostaddr.va_type = VAT_INET;
#if	VMTP_HOSTID
			csr1->vc_hostaddr.va_inet = VMTP_HOSTGROUP;
#else	VMTP_HOSTID
			csr1->vc_hostaddr.va_inet = htonl(VMTP_HOSTGROUP);
#endif	VMTP_HOSTID
		}
	}
			
				
	ei = (struct espiphdr *)csr1->vc_vihdr;
	ei->ei_probingent = probing;
	ei->ei_probedent = probed;
	ei->ei_transid = 0;
	esp_time(ei->ei_tmstamp);
	seteiq_authversion(ei, 1);
	seteiq_authdomain(ei, 1);	

	csr1->vc_hdltimeo = esp_hdltimeo;
	csr1->vc_state = VC_AWAITPROBE;
	csr->vc_tmstamp = ei->ei_tmstamp;
	csr->vc_action = VCA_NOOP;	/* since sleeping on this one */

	setei_control(ei, ECTL_NPE);
	ei->ei_code = probe;
	ei->ei_addr = csr1->vc_hostaddr;
	ei->ei_ifp = csr1->vc_ifp;
	esp_sendprq(csr1, ei);
	vmtp_starttimer(csr1, ET_RETRANSMIT);

	while (csr->vc_action != VCA_DELIVER)
		sleep(csr, PZERO+1);

#ifdef	ESP_DEBUG
	printf("esp_probe(): awoken!\n");
#endif
	csr1->vc_state = VC_AWAITREQ;
	data->es_code = csr->vc_probecode;
	if (vmtp_ok(data->es_code)) {
		/*
		 * check if authorized to get info
		 */
		if (!esp_accessright(csr, probing, data->es_request)) 
			data->es_code = VMTP_NOPERMISSN;
		else 
			error = esp_putprobedata(csr, data);
		csr->vc_hdltimeo = vmtp_hdlrcsrtimeo;
		vmtp_starttimer(csr, vts_discardcsr(csr));
	} else {
#ifdef	ESP_DEBUG
	printf("esp_probe(): response code = 0x%x\n", data->es_code);
#endif
		vmtp_freecsr(csr, vremotecsrmap);		
	}

	if (csr != csr1) {
		vmtp_stoptimer(csr1);
#ifdef	ESP_DEBUG
		printf("esp_probe(): freeing temporary csr\n");
#endif
		if (vcf_mbuf(csr1)) {
			m_freem(csr1->vc_dataseg);
		}
		m_free(dtom(csr1->vc_vihdr));
		vmtp_dealloccsr(csr1);
	}
	return error;

} /* esp_probe */

/*
 * Copy data from the csr to the espprobedata and copy the strings to
 * user address space if deemed necessery.
 */
esp_putprobedata(csr, data)
	struct vmtpcsr *csr;
	struct espprobedata *data;
{
	struct mbuf *m;
	int error;
	caddr_t	addr = data->es_data;
	int space = data->es_length;
	int zero = 0;		/* for zero-termination of strings */
	int len;
#ifdef	__GNU__
	int i;
#endif	__GNU__

#ifdef	ESP_DEBUG
	printf("esp_putprobedata(): called\n");
#endif
	data->es_inpktgap = csr->vc_inpktgap;
	data->es_mtu = csr->vc_mtu * VMTP_BLKSIZE + sizeof(struct vmtpiphdr); 	
	data->es_transid = csr->vc_transid;
	data->es_hostaddr = csr->vc_hostaddr;
	data->es_roundtrip = csr->vc_roundtrip;
	if (esp_processinfo(data->es_request))
		data->es_processid = csr->vc_processid;
	if (esp_principalinfo(data->es_request))
		data->es_principalid = csr->vc_principalid;
	if (esp_effprincinfo(data->es_request))
		data->es_effprincipalid = csr->vc_effprincipalid;
	if (esp_timelimitinfo(data->es_request))
		data->es_timelimit = csr->vc_timelimit;
	if (data->es_length && esp_principalinfo(data->es_request)) {
		data->es_princlen = m_length(csr->vc_principal);
		for (m = csr->vc_principal; m != NULL; m = m->m_next) {
#ifdef	__GNU__
			i = m->m_len;
			len = MIN(space, i);
#else	__GNU__
			len = MIN(space, m->m_len);
#endif	__GNU__
			error = sockresults(m, addr, len);
			if (error)
				return error;
			addr += len;
			space -= len;
		}
		if (space) {
			error = copyout( &zero, addr, (u_int)1);
			addr++;
		} else
			error = copyout( &zero, addr-1, (u_int)1);
		if (error)
			return error;
	}
	if (data->es_length && esp_pwdinfo(data->es_request)) {
		data->es_pwdlen = m_length(csr->vc_password);
		for (m = csr->vc_password; m != NULL; m = m->m_next) {
#ifdef	__GNU__
			i = m->m_len;
			len = MIN(space, i);
#else	__GNU__
			len = MIN(space, m->m_len);
#endif	__GNU__
			error = sockresults(m, addr, len);
			if (error)
				return error;
			addr += len;
			space -= len;
		}
		if (space) {
			error = copyout( &zero, addr, (u_int)1);
			addr++;
		} else
			error = copyout( &zero, addr-1, (u_int)1);
		if (error)
			return error;
	}

	if (esp_encryptinfo(data->es_request)) {
		data->es_encryptqual = csr->vc_encryptqual;
		data->es_key = csr->vc_key;
	}
#ifdef	ESP_DEBUG
	printf("esp_putprobedata(): results: %d, %d, %d\n",
		data->es_mtu, data->es_inpktgap, data->es_transid);
#endif
	return 0;
} /* esp_putprobedata */

/*
 * Check if the entity has a right to get the requested information
 * Returns zero if not.
 */
esp_accessright(csr, entity, req)
	struct vmtpcsr *csr;
	struct vmtpeid entity;
	u_short req;
{
	struct vmtpser *ser;
	struct vmtpcsr *localcsr;

#ifdef	ESP_DEBUG
	printf("esp_accessright(): called\n");
#endif

	if (vmtp_sameeid(csr->vc_client, entity))
		return 1;

	if (vmtp_sameeid(csr->vc_server, entity) || (vcf_group(csr) &&
	    vmtp_isgroupmember(entity, csr->vc_origserver))) {
		/*
		 * The server is probing the client in the current transaction
		 */
		ser = vmtp_maptoserver(entity);
		if (ser == NULL) 
			return !(esp_pwdinfo(req) || esp_encryptinfo(req));

		if (esp_encryptinfo(req) && !vmtp_securityreq(ser))
			return 0;
		if (esp_pwdinfo(req) && !(vmtp_securityreq(ser) || 
		    vmtp_authreq(ser)))
			return 0;
		return 1;
	}

	localcsr = vmtp_maptocsr(entity, vlocalcsrmap);
	if (vmtp_sameeid(localcsr->vc_server, csr->vc_server) || 
	    vcf_group(localcsr)) {
		/*
		 * The client is probing the server.
		 */
		if (esp_pwdinfo(req) || esp_encryptinfo(req))
			return 0;
		return 1;
	}
	/* 
	 * Probed by a random entity
	 * Leave the check to the other end.
 	 */

	return (!esp_pwdinfo(req) && !esp_encryptinfo(req));

} /* esp_accessright */
#endif	MACH_VMTP





