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
 * $Log:	esp_key.c,v $
 * Revision 2.3  89/03/09  20:41:47  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:45  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_key.c,v 2.1 87/08/18 16:30:44 mrt Exp $
 */

/*
 * 	esp_key.c		5/21/87
 *	Written by Erik Nordmark
 */

/*
 * TODO
 *	Handle secure groups - need masterkey in the group descriptor!!
 *
 *	Remove old stuff from getmasterkey and remove getxormasterkey.
 *
 *	Handle case where encryption qualifiers doesn't match - how?
 */


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
#include "esp_key.h"



/*
 * Init the key storage
 */
esp_initkeyst()
{
	int i;

	for (i = 0; i <  ESP_KEYSTSIZE; i++) {
		ekeystorage[i].ek_flags = EKF_NONE;
	}
} /* esp_initkeyst */

/*
 * Decrypt the authenticator
 */
esp_decryptauth(m, ap, encryptqual, length)
	struct mbuf *m;
	struct av3auth *ap;
	int encryptqual;
	int length;
{
	struct vmtpser *ser;
#ifdef	KEY_DEBUG
	printf("esp_decryptauth(): m = 0x%x, ap = 0x%x, eq = %d\n",
		m, ap, encryptqual);
#endif

	/*
	 * Have to scan all the SERs until someone with key the correctly 
	 * decrypts the authenticator is found.
	 */
	for (ser = vmtp_nextserver(NULL); ser != NULL; 
	    ser = vmtp_nextserver(ser)) {
		/* 
		 * Check flag VS_MASTERKEY in the SER and if set extract the 
		 * master key.
		 */
		if (vmtp_masterkey(ser) && encryptqual == ser->vs_mencryptqual){
#ifdef	KEY_DEBUG
			printf("esp_decryptauth(): key = 0x%x\n",
				ser->vs_mkey.vk_xor);
#endif
		} else {
#ifdef	KEY_DEBUG
			printf("esp_decryptauth(): no key in ser\n");
#endif
			continue;
		}
		/*
		 * Try decrypting the authenticator with this masterkey
		 */
		if (esp_decrypt(m, av3a_off, length, encryptqual,ser->vs_mkey)){
#ifdef	KEY_DEBUG
			printf("esp_decryptauth(): BAD encryption qual\n");
#endif
			return -1;
		}
		/* 
		 * Check the checksum
		 */
		if (ap->av3a_cksum == vmtp_cksum(m, av3a_off + sizeof(u_long),
					length - sizeof(u_long))) 
			return 0;
#ifdef	KEY_DEBUG
		printf("esp_decryptauth(): bad checksum!!\n");
		printf("\treceived: 0x%x, computed: 0x%x\n", 
				ap->av3a_cksum,
				vmtp_cksum(m, av3a_off + sizeof(u_long),
					length - sizeof(u_long)));
#endif
	}
#ifdef	KEY_DEBUG
	printf("esp_decryptauth(): no key succeeded!!\n");
#endif
	return -1;
} /* esp_decryptauth */


/* 
 * Fetch authenticators and keys from the key storage and put them in the csr. 
 */
esp_getauthenticator(csr, serverp)
	register struct vmtpcsr *csr;
	struct princid serverp;
{
	register struct espkeyst *ek;
	register int i;
	int error = 1;		/* Default if key not found! */
	int s = splimp();

#ifdef	KEY_DEBUG
	printf("esp_getauthenticator(): csr = 0x%x\n", csr);
	printf("esp_getauthenticator(): principal = 0x%x:0x%x\n",
		serverp.pc_host.s_addr, serverp.pc_local);
#endif

	if (csr->vc_authenticator) 
		m_free(csr->vc_authenticator);

	for (i = 0; i < ESP_KEYSTSIZE; i++) {
		ek = &ekeystorage[i];
		if (!ekf_used(ek) ||
		    csr->vc_principalid.pc_local != ek->ek_clientp.pc_local ||
		    csr->vc_principalid.pc_host.s_addr != 
						ek->ek_clientp.pc_host.s_addr ||
		    serverp.pc_local != ek->ek_serverp.pc_local ||
		    serverp.pc_host.s_addr != ek->ek_serverp.pc_host.s_addr) 
			continue;

		/* Found !! */
#ifdef	KEY_DEBUG
		printf("esp_getauthenticator(): found in entry %d\n", i);
#endif
		csr->vc_authenticator = m_copy(ek->ek_authenticator, 0, 
						M_COPYALL);
		if (csr->vc_authenticator == NULL) {
			error = ENOBUFS;
			break;
		}
		
		ek->ek_flags &= ~EKF_HALFDEAD;
		csr->vc_encryptqual = ek->ek_encryptqual;
		csr->vc_key = ek->ek_key;
		csr->vc_timelimit = ek->ek_timelimit;
#ifdef	KEY_DEBUG
	printf("esp_getauthenticator(): key = 0x%x\n", csr->vc_key.vk_xor);
#endif
		splx(s);
		return 0;
	}
	splx(s);
	csr->vc_encryptqual = ENCRYPT_NONE;
	return error;
} /* esp_getautheticator */


/*
 * Place a key and authenticator in the key storage
 */
esp_setkey(clientp, va)
	struct princid	clientp;
	register struct vmtpauth *va;
{
	struct princid	serverp;
	register struct espkeyst *ek;
	register int i;
	int retry;
	int error;

	serverp.pc_local = va->va_serverp.pc_local;
	serverp.pc_host = va->va_serverp.pc_host;

#ifdef	KEY_DEBUG
	printf("esp_setkey(): clientp = 0x%x:0x%x, serverp = 0x%x:0x%x\n",
	    	clientp.pc_host, clientp.pc_local, serverp.pc_host, 
		serverp.pc_local);
#endif
	/* Make sure no old key is there */
	esp_remkey(clientp, serverp);

	for (retry = 0; ; retry++) {
		for (i = 0; i < ESP_KEYSTSIZE; i++) {
			ek = &ekeystorage[i];
			if (ekf_used(ek) && ~ekf_halfdead(ek)) {
				ek->ek_flags |= EKF_HALFDEAD;
				continue;
			}
#ifdef	KEY_DEBUG
			printf("esp_setkey(): grabbing entry %d\n", i);
#endif
			/* Aquire this entry */
			ek->ek_flags = EKF_USED;
			m_freem(ek->ek_authenticator);
			ek->ek_authenticator = NULL;
		
			error = sockargs(&ek->ek_authenticator, va->va_auth, 
					 va->va_authlen, MT_PCB);
			if (error) {
				ek->ek_flags = EKF_NONE;
				return error;
			}
			ek->ek_clientp = clientp;
			ek->ek_serverp = va->va_serverp;
			ek->ek_encryptqual = va->va_encryptqual;
			ek->ek_timelimit = va->va_timelimit;
			ek->ek_key = va->va_key;
#ifdef	KEY_DEBUG
	printf("esp_setkey(): clientp = 0x%x:%d, serverp = 0x%x:%d\n", 
		clientp.pc_host.s_addr, clientp.pc_local,
		va->va_serverp.pc_host.s_addr, va->va_serverp.pc_local);
	printf("esp_setkey(): key = 0x%x, eq = %d\n", ek->ek_key.vk_xor,
		ek->ek_encryptqual);
#endif
			return 0;	
		}
		if (retry)
			panic("esp_setkey");
	}
} /* esp_setkey */


/*
 * Remove a key from the key storage
 */
esp_remkey(clientp, serverp)
	struct princid	clientp, serverp;
{
	register struct espkeyst *ek;
	register int i;

#ifdef	KEY_DEBUG
	printf("esp_remkey(): clientp = 0x%x:0x%x, serverp = 0x%x:0x%x\n",
	    	clientp.pc_host, clientp.pc_local, serverp.pc_host, 
		serverp.pc_local);
#endif
	for (i = 0; i < ESP_KEYSTSIZE; i++) {
		ek = &ekeystorage[i];
		if (!ekf_used(ek) ||
		    clientp.pc_local != ek->ek_clientp.pc_local ||
		    clientp.pc_host.s_addr != ek->ek_clientp.pc_host.s_addr ||
		    serverp.pc_local != ek->ek_serverp.pc_local ||
		    serverp.pc_host.s_addr != ek->ek_serverp.pc_host.s_addr) 
			continue;
#ifdef	KEY_DEBUG
		printf("esp_remkey(): found in entry %d\n", i);
#endif
		m_freem(ek->ek_authenticator);
		ek->ek_authenticator = NULL;
		ek->ek_flags &= ~EKF_USED;
		break;
	}
} /* esp_remkey */


