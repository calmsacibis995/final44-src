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
 * $Log:	esp_subr.c,v $
 * Revision 2.3  89/03/09  20:42:25  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:21  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_subr.c,v 2.1 87/08/18 16:31:06 mrt Exp $
 */

/*
 * 	esp_subr.c		2/26/87
 *	Written by Erik Nordmark
 */

/*
 * TODO
 *
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
#include "esp_cache.h"

/* 
 * Send a (delayed) probe
 * Is called by using timeout() routine
 */
esp_delayedprobe(csr)
	struct vmtpcsr *csr;
{
	esp_sendprq(csr, csr->vc_vihdr);
	vmtp_starttimer(csr, ET_RETRANSMIT);
} /* esp_delayedprobe */


/* 
 * Encryption
 */
esp_encrypt(m, off, len, encryptqual, key)
	register struct mbuf *m;
	register int off,len;
	register int encryptqual;
	union vmtpkey key;
{
#ifdef	ESP_DEBUG
	printf("esp_encrypt(): m = 0x%x, off = %d, len = %d, qual = %d\n",
		m, off, len, encryptqual);
#endif
	switch (encryptqual) {
		case ENCRYPT_XOR: 
			esp_xorcrypt(m, key.vk_xor, off, len);
			break;
		case ENCRYPT_DESCBC: 
#ifdef	ESP_DEBUG
			printf("esp_encrypt(): DES not supported\n");
#endif
			return -1;
		default:
#ifdef	ESP_DEBUG
			printf("esp_encrypt(): BAD encryption qual: %d\n",
				encryptqual);
#endif
			return -1;
	}
	return 0;
} /* esp_encrypt */

/* 
 * Decryption
 */
esp_decrypt(m, off, len, encryptqual, key)
	register struct mbuf *m;
	register int off,len;
	register int encryptqual;
	union vmtpkey key;
{
#ifdef	ESP_DEBUG
	printf("esp_decrypt(): m = 0x%x, off = %d, len = %d, qual = %d\n",
		m, off, len, encryptqual);
#endif
	switch (encryptqual) {
		case ENCRYPT_XOR: 
			esp_xorcrypt(m, key.vk_xor, off, len);
			break;
		case ENCRYPT_DESCBC: 
#ifdef	ESP_DEBUG
			printf("esp_decrypt(): DES not supported\n");
#endif
			return -1;
		default:
#ifdef	ESP_DEBUG
			printf("esp_decrypt(): BAD encryption qual: %d\n",
				encryptqual);
#endif
			return -1;
	}
	return 0;

} /* esp_decrypt */


/*
 * Something that does xor encryption in a rather inefficient way
 */
esp_xorcrypt(m, key, off, len)
	register struct mbuf *m;
	register u_long key;
	int off;
	register int len;
{
	register u_long *word, *maxword;
	register int count;

#ifdef	ESP_DEBUG
	printf("esp_xorcrypt(): key = 0x%x, off = %d, len = %d\n",
		key, off, len);
#endif

	while (m && m->m_len <= off) {
		off -= m->m_len;
		m = m->m_next;
	}
		
	if (!m) 
		panic("esp_xorcrypt");

	count = MIN(m->m_len - off, len);
	word = (u_long *)(mtod(m, char *) + off);
	maxword = word + (count>>2);


	while (1) {
#ifdef	ESP_DEBUG
		printf("esp_xorcrypt():  key = 0x%x, off = %d, len = %d\n", 
		key, off, len);
#endif

#ifdef	ESP_DEBUG
	printf("esp_xorcrypt():  word = 0x%x, maxword = 0x%x, count = %d\n", 
		word, maxword, count);
#endif

		while (word < maxword-1) {
			*(word++) = *word ^ key;
			*(word++) = *word ^ key;
		}
		if (word < maxword)
			*(word++) = *word ^ key;

		switch (count & 0x3) {
			case 0: break;
			case 1: 
			{
				*word = *word ^ (key & 0xffffff00);
				key = (key >> 24) | (key << 8);
				break;
			}
			case 2: 
			{
				*word = *word ^ (key & 0xffff0000);
				key = (key >> 16) | (key << 16);
				break;
			}
			case 3: 
			{
				*word = *word ^ (key & 0xff000000);
				key = (key >> 8) | (key << 24);
				break;
			}
		}
		len -= count;
		m = m->m_next;
		if (!len || !m)
			break;

		count = MIN(m->m_len, len);
		word = mtod(m, u_long *);
		maxword = word + count/4;
	}
	if (len) {
		printf("esp_xorcrypt: out of data\n");
	}

} /* esp_xorcrypt */

/* 
 * When multicasting is used several remote csr's may exist for the same
 * client. When a prp is received to info has to reach all of them!
 */
esp_copyinfo(csr)
	register struct vmtpcsr *csr;
{
	register struct vmtpcsr *csr1;

#ifdef	ESP_DEBUG
	printf("esp_copyinfo(): csr = 0x%x\n", csr);
	vmtp_dumpeid(&csr->vc_server, "server", "esp_copyinfo");
#endif

	while ((csr1 = vmtp_nextcsr(csr)) != NULL) {
		/* Ignore if any of the m_copies fail! */
		m_freem(csr1->vc_principal);
		m_freem(csr1->vc_password);
		m_freem(csr1->vc_authenticator);
		bcopy((caddr_t)&csr->vc_mtu, (caddr_t)&csr1->vc_mtu,
			(caddr_t)&csr->vc_key + sizeof(union vmtpkey) - 
			(caddr_t)&csr->vc_mtu);
		if (csr->vc_principal)
			csr1->vc_principal = m_copy(csr->vc_principal, 0, 
							M_COPYALL);
		if (csr->vc_password)
			csr1->vc_password = m_copy(csr->vc_password, 0, 
							M_COPYALL);
		if (csr->vc_authenticator)
			csr1->vc_authenticator = m_copy(csr->vc_authenticator, 
							0, M_COPYALL);
		csr = csr1;
	}
} /* esp_copyinfo */



