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
 * $Log:	vmtp_sendpg.c,v $
 * Revision 2.3  89/03/09  20:50:26  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:05:33  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 11-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_INVOKE: fixed all calls to copyin() so that they will
 *	work with a source in kernel space.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
/*
 * $ Header: vmtp_sendpg.c,v 2.1 87/08/14 15:44:32 mrt Exp $
 */
 
#include <mach_vmtp.h>

#define VMTP_INVOKE	1

/*
 * 	vmtp_sendpg.c
 *	Written by Joyo Wijaya and Erik Nordmark
 */

/* 
 * Assumes: 
 *	VMTP_BLKSIZE > MLEN 
 *		and
 * 	VMTP_MAXBLKPACKET * VMTP_BLKSIZE <= CLBYTES i.e. the datasegment part 
 *	of a packet can fit into one cluster.
 *
 * Variants:
 *	VMTP_NOCKSM - the checksum is not computed and a the checksum 
 *	field is set to zero.
 */

#define CLMASK		(CLBYTES-1)	/* masking out address within cluster */


#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <mach/machine/vm_param.h>

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
#include "esp.h"

#if	VMTP_INVOKE
/*
 * copyin that is valid for kernel space also.
 */
#define COPYIN(error,from,to,len) {					\
		if ((((caddr_t)(from)) >= ((caddr_t)VM_MIN_KERNEL_ADDRESS)) &&		\
			    (((caddr_t)(from)) <= ((caddr_t)VM_MAX_KERNEL_ADDRESS))){ \
			bcopy((caddr_t)(from), (caddr_t)(to), (len));	\
			error = 0;					\
		} else {						\
			error = copyin((caddr_t)(from), (caddr_t)(to), (len));	\
		}							\
}
#else	VMTP_INVOKE
#define COPYIN(error,from,to,len) {					\
	error = copyin((caddr_t)(from), (caddr_t)(to), (len));		\
}
#endif	VMTP_INVOKE


/*
 * Send a packet group.  The vc_vihdr in csr has to be valid.
 * The data segment to be transmitted is pointed by vc_dataseg.
 * The transmission mask vc_txmsk determines which blocks of the segment
 * data will be transmitted and the retransflag specifies if it's the first
 * transmission or a retransmission. This is currently only used in 
 * vmtp_sendpgmbuf that does the copyin of the segment during the first 
 * transmission and reuses that mbuf chain for retransmissions. (For 
 * non-idempotent replies).
 *
 * Note: For the first transmission vc_segment is always a segptr and 
 *	 vc_flags (VCF_MBUF) indicates wether to put a copy of the segment into
 *	 an mbuf chain or not.

 */
vmtp_sendpg(csr, retransflag, inhiblocal)
	register struct vmtpcsr *csr;
	int retransflag;
	int inhiblocal;
{
	register struct vmtpiphdr *vi;
	register u_long 	txmsk;
	register u_long 	packettxmsk;
	u_long 			dlvrmsk;
	register struct mbuf 	*m;
	register caddr_t 	segptr;
	register int 		segsize;
	register int 		len;
	int			mtu;	/* in blocks: either 1 or 2 */
	u_long			maxmask; 
	int 			error;

#ifdef	VMTP_DEBUG
	printf("vmtp_sendpg(0x%x)\n", (u_long)csr);
#endif

	/*
	 * If any data segment to be transmitted then pack each packet
	 * with csr->vc_mtu blocks of data and send; otherwise, just 
	 * send the packet header.
	 */

	if (!csr->vc_vihdr) {
#ifdef	VMTPDEBUG
		printf("vmtp_sendpg(): csr without a vc_vihdr\n");
		return EOPNOTSUPP;
#else
		panic("vmtp_sendpg(): csr without a vc_vihdr\n");
#endif
	}

	if (csr->vc_txmsk == 0 ||  vmtp_respdiscarded(csr->vc_code) || 
	    !vmtp_segmentdata(csr->vc_code)) {
		/*
		 * No data segment to be transmitted.
		 */
		m = vmtp_copyvihdr(csr->vc_vihdr);
		if (!m) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpg(): ENOBUFS for vi header\n");
#endif
			return(ENOBUFS);
		}
		vi = mtod(m, struct vmtpiphdr *);
		vi->vi_dlvrmsk = 0;
		andvi_control(vi, ~VCTL_CPG);
		/* 
		 * No need to pad lenth here - header always multiple 
		 * of 4 bytes!
		 */
		if (vmtp_localaddr(vi->vi_src) && !inhiblocal) {
			vmtp_sendlocalpacket(csr, vi, sizeof(struct vmtpiphdr),
				csr->vc_encryptqual);
			return 0;
		}
		if (error = vmtp_sendpacket(csr, vi, sizeof(struct vmtpiphdr),
				csr->vc_encryptqual)){
#ifdef	VMTPDEBUG
			printf("vmtp_sendpg(): (2) failed: %d\n", error);
#endif
		}
		return(error);
	}	

	
	/*
	 * Data segment need to be transmitted.
	 */

	vi = csr->vc_vihdr;	
	if (vmtp_localaddr(vi->vi_src) && !inhiblocal) {
		vmtp_sendlocalpg(csr, retransflag);
		return;
	}
	orvi_control(vi, VCTL_CPG);		/* except for last packet */

	txmsk = csr->vc_txmsk;
	dlvrmsk = vmtp_usrdlvrmskset(csr->vc_code) ? csr->vc_usrdlvrmsk :
		vmtp_segsizetomsk(csr->vc_segsize);	
	mtu = csr->vc_mtu;
	if (mtu <= 0) {
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpg(): mtu is ZERO: can't send\n");
#endif
		m_freem(m);
		return -1;
	}		
	if (mtu >= 2) {
		mtu = 2;
		maxmask = 0x3;
	} else
		maxmask = 0x1;

#ifdef	ESP_DEBUG
	printf("vmtp_sendpg(): mtu = %d, maxmask = %d\n", mtu, maxmask);
#endif

	if (vcf_mbuf(csr)) 
		return vmtp_sendpgmbuf(csr, txmsk, dlvrmsk, retransflag, 
				mtu, maxmask);

	if (vmtp_usrdlvrmskset(csr->vc_code) || txmsk != dlvrmsk)
		return vmtp_sendpgnoncont(csr, txmsk, mtu, maxmask);

	/* 
	 * vmtp_sendpgcont(): the packet group is in user space memory and
	 * it's contigious.
	 *
	 * Copy a packet into memory at a time and send it with the prepended
	 * vmtpip header.
	 *
	 * Checksums:
	 *	The checksum is kept in the vmtpip header for short packets,
	 *	but packets with datasegments use this word for their first
 	 *	datasegment word since the checksum is located after the data 
	 *	segment. The motivation for this rather akward constuct is to
	 * 	avoid allocating a separate mbuf for just the checksum when
	 *	full size packets are sent.
 	 */


	segptr = csr->vc_segptr;
	if (vmtp_datagram(csr->vc_code))
		csr->vc_segptr = NULL;
	segsize = csr->vc_segsize;
	packettxmsk = maxmask;

#ifdef	VMTP_DEBUG
	printf("vmtp_sendpg(): txmsk = 0x%x, dlvrmsk = 0x%x segsize = %d\n",
		txmsk, dlvrmsk, segsize);
#endif

	while (segsize) {
#ifdef	VMTPDEBUG
	printf("vmtp_sendpg(): segptr = %d, segsize = %d, txmsk = 0x%x\n",
		segptr, segsize, txmsk);
#endif
		m = vmtp_copyvihdr(csr->vc_vihdr);
		if (!m) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpg(): ENOBUFS for vi header\n");
#endif
			return(ENOBUFS);
		}
		vi = mtod(m, struct vmtpiphdr *);
		vi->vi_dlvrmsk = packettxmsk;
		len = MIN(mtu * VMTP_BLKSIZE, segsize);
		MGET(m->m_next, M_WAIT, MT_DATA);
		if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpg(): ENOBUFS for segment\n");
#endif
			m_freem(m);
			return(ENOBUFS);
		}

		if (len>MLEN) {
		        MCLGET(m->m_next);
			if (m->m_next->m_len != CLBYTES) {
#ifdef	VMTPDEBUG
		    		printf("vmtp_sendpg(): ENOBUFS for segment\n");
#endif
				m_freem(m);
				return(ENOBUFS);
			}
		}

		COPYIN(error,segptr, mtod(m->m_next,caddr_t),len);
		if (error) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpg(): copyin failed: len = %d\n", len);
#endif
			m_freem(m);
			goto release;
		}
		m->m_next->m_len = len;
	
		if (!(txmsk & ~maxmask)) {
			/* no more 1's in txmsk - last packet in group */
			if (mtu == 2 && len <= VMTP_BLKSIZE) {
				/* 
				 * Pick rightmost bit of the two bits set in
				 * vi_dlvrmsk
				 */ 
				vi->vi_dlvrmsk &= vi->vi_dlvrmsk>>1;
			}

#ifdef	VMTPDEBUG
			printf("vmtp_sendpg(): sending the LAST packet\n");
#endif
			andvi_control(vi, ~VCTL_CPG);
			vmtp_padlength(m, len);
			if (error = vmtp_sendpacket(csr, vi,	
					len+sizeof(struct vmtpiphdr),
					csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
				printf("vmtp_sendpg(): sendpacket() failed\n");
#endif
				goto release;
			}
			return 0;
		}

		if (error = vmtp_sendpacket(csr,vi,len+sizeof(struct vmtpiphdr),
						csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
				printf("vmtp_sendpg(): sendpacket() failed\n");
#endif
				goto release;
		}
		
		segptr = (caddr_t)((int)segptr + len);
		segsize -=len;
		txmsk >>= mtu;
		packettxmsk <<= mtu;
	} /* while (segsize) */
#ifdef	VMTP_DEBUG
	printf("vmtp_sendpg(): FALLING THROUGH - no segment???\n");
	return 0;
#else
	panic("vmtp_sendpg");
#endif

release:

#ifdef	VMTPDEBUG
		printf("vmtp_sendpg(): Error return\n");
#endif

	return error;
} /* vmtp_sendpg */

/* *** */

/*
 * vmtp_sendpgnoncont:
 * Send from non-contigious memory:
 * Copyin a segment and send it. The segment is not contigious in memory either
 * because it's a partial retranmission or because the user delivery mask is 
 * set and both of these cases are reflected in txmsk.
 */
vmtp_sendpgnoncont(csr, txmsk, mtu, maxmask)
	register struct vmtpcsr *csr;
	u_long 			txmsk;
	int			mtu;		/* in blocks: either 1 or 2 */
	u_long			maxmask; 
{
	register struct vmtpiphdr *vi;
	u_long 			packettxmsk = 1;
	register struct mbuf 	*m;
	register caddr_t 	segptr = csr->vc_segptr;
	register int 		segsize = csr->vc_segsize;
	register int 		len, len0;
	int 			error;

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgncont(): txmsk = 0x%x segsize = %d mtu = %d maxmask = %d\n",
		txmsk, segsize, mtu, maxmask);
#endif

	while (txmsk  && (segsize > 0)) {

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgnoncont(): segptr = 0x%x, segsize = 0x%x, txmsk = 0x%x\n",
	 (int)segptr, segsize, txmsk);
#endif

		while (!(txmsk & 0x01) && (segsize > 0)) {
			txmsk >>= 1;
			packettxmsk <<= 1;
			segptr = (caddr_t)((int)segptr + VMTP_BLKSIZE);
			segsize -= VMTP_BLKSIZE;
		}

		if (segsize < 0) {
			/* assume it's ok - receivers problem */
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpgnoncont(): txmsk 'bigger then' segsize\n");
#endif
			return 0;
		}

		if ((txmsk & maxmask) == maxmask) {
			/* (at least) this packet contigious in memory */
			m = vmtp_copyvihdr(csr->vc_vihdr);
			if (!m) {
#ifdef	VMTPDEBUG
			printf("vmtp_sendpgnoncont(): ENOBUFS for vi header\n");
#endif
				return(ENOBUFS);
			}
			vi = mtod(m, struct vmtpiphdr *);
			vi->vi_dlvrmsk = packettxmsk * maxmask;	
			len = MIN(mtu * VMTP_BLKSIZE, segsize);
			MGET(m->m_next, M_WAIT, MT_DATA);
			if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgnoncont(): ENOBUFS for segment\n");
#endif	
				m_freem(m);
				return(ENOBUFS);
			}

		        MCLGET(m->m_next);
			if (m->m_next->m_len != CLBYTES) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpgnoncont(): ENOBUFS for segment\n");
#endif
				m_freem(m);
				return(ENOBUFS);
			}

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgnoncont(): copyin segptr = 0x%x,segsize = %d,txmsk = 0x%x\n",
	 (int)segptr, segsize, txmsk);
#endif
			COPYIN(error,segptr, mtod(m->m_next,caddr_t),len);
			if (error) {
#ifdef	VMTPDEBUG
    		printf("vmtp_sendpgnoncont(): copyin failed: len = %d\n", len);
#endif
				m_freem(m);
				goto release;
			}
			m->m_next->m_len = len;

			if (txmsk == maxmask) {
				/* last packet in group */
				goto sendlast;
			}

			if (error = vmtp_sendpacket(csr, vi,
				len+sizeof(struct vmtpiphdr),
					csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
			printf("vmtp_sendpgnoncont(): sendpacket() failed\n");
#endif
				goto release;
			}
			segptr = (caddr_t)((int)segptr + len);
			segsize -=len;
			txmsk >>= mtu;
			packettxmsk <<= mtu;
		} /*end of sending a contigious packet */


		else { 
			/* 
			 * Copyin this block and then find the next one
			 * Will never be used when mtu is 1
			 */
			if (mtu == 1)
				panic("vmtp_sendpgnoncont");
			m = vmtp_copyvihdr(csr->vc_vihdr);
			if (!m) {
#ifdef	VMTPDEBUG
			printf("vmtp_sendpgnoncont(): ENOBUFS - vi header\n");
#endif
				return(ENOBUFS);
			}
			vi = mtod(m, struct vmtpiphdr *);
			vi->vi_dlvrmsk = packettxmsk;
			len = MIN(VMTP_BLKSIZE, segsize);
			MGET(m->m_next, M_WAIT, MT_DATA);
			if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgnoncont(): ENOBUFS for segment\n");
#endif
				m_freem(m);
				return(ENOBUFS);
			}

			if (len>MLEN) {
			        MCLGET(m->m_next);
				if (m->m_next->m_len != CLBYTES) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpgnoncont(): ENOBUFS for segment\n");
#endif
					m_freem(m);
					return(ENOBUFS);
				}
			}
#ifdef	VMTP_DEBUG
printf("vmtp_sendpgnoncont(): copyin segptr = 0x%x,segsize = %d,txmsk = 0x%x\n",
	 (int)segptr, segsize, txmsk);
#endif

			COPYIN(error,segptr, mtod(m->m_next,caddr_t),len);
			if (error) {
#ifdef	VMTPDEBUG
    		printf("vmtp_sendpgnoncont(): copyin failed: len = %d\n", len);
#endif
				m_freem(m);
				goto release;
			}
			m->m_next->m_len = len;

			segptr = (caddr_t)((int)segptr + len);
			segsize -=len;
			txmsk >>= 1;
			packettxmsk <<= 1;

			if (txmsk == 0 || segsize == 0) {
				/* send last - vi_dlvrmsk already set! */
				goto sendlast;
			}

			/* find the next block */

			while (!(txmsk & 0x01) && (segsize > 0)) {
				txmsk >>= 1;
				packettxmsk <<= 1;
				segptr = (caddr_t)((int)segptr + VMTP_BLKSIZE);
				segsize -= VMTP_BLKSIZE;
			}

			if (segsize < 0) {
				/* There wasn't another one - bad txmsk! */
				 /* send the first block anyway! */
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpgnoncont(): txmsk 'bigger then' segsize\n");
#endif
				segsize = 0; 
			}

			vi->vi_dlvrmsk |= packettxmsk;

			len = MIN(VMTP_BLKSIZE, segsize);

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgnoncont(): copyin segptr = 0x%x,segsize = %d,txmsk = 0x%x\n",
	 (int)segptr, segsize, txmsk);
#endif

			COPYIN(error,segptr, mtod(m->m_next,caddr_t),len);
			if (error) {
#ifdef	VMTPDEBUG
    		printf("vmtp_sendpgnoncont(): copyin failed: len = %d\n", len);
#endif
				m_freem(m);
				goto release;
			}
			m->m_next->m_len += len;

			/* include previous block in len */
			len += VMTP_BLKSIZE;

			if (txmsk == 1) {
				/* last packet in group */
				goto sendlast;
			}

			if (error = vmtp_sendpacket(csr, vi, 
					len+sizeof(struct vmtpiphdr),
					csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
			printf("vmtp_sendpgnoncont(): sendpacket() failed\n");
#endif
				goto release;
			}
		
			segptr = (caddr_t)((int)segptr + len- VMTP_BLKSIZE);
			segsize -=len - VMTP_BLKSIZE;
			txmsk >>= 1;
			packettxmsk <<= 1;
	
		} /* end if-else */

	} /* end while */
#ifdef	VMTP_DEBUG
	printf("vmtp_sendpgnoncont(): FALLING THROUGH - no segment???\n");
	return 0;
#else
	panic("vmtp_sendpgnoncont()");
#endif

sendlast:

#ifdef	VMTPDEBUG
	printf("vmtp_sendpgnoncont(): sending the LAST packet\n");
#endif
	andvi_control(vi, ~VCTL_CPG);
	vmtp_padlength(m, len);
	if (error = vmtp_sendpacket(csr, vi, len + sizeof(struct vmtpiphdr),
				csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
		printf("vmtp_sendpgnoncont(): sendpacket() failed\n");
#endif
		goto release;
	}
	return 0;

release:

#ifdef	VMTPDEBUG
		printf("vmtp_sendpgnoncont(): Error return\n");
#endif

	return error;		
			
} /* vmtp_sendpgnoncont */

				
/*
 * Compute checksum and do optional encryption on the packet and send it.
 *
 * len is supposed to be the length of the packet excluding the checksum field,
 * which is appended by this routine and including the vmtp_header.
 */
vmtp_sendpacket(csr, vi, len, encryptqual)
	register struct vmtpcsr *csr;
	register struct vmtpiphdr *vi;
	int len;			
	u_long encryptqual;
{
	register struct mbuf *m = dtom(vi);
	register struct mbuf *n;
	register int vlen;	/* for checksum calculation and encryption */

#ifdef	VMTP_DEBUG
	printf("vmtp_sendpacket(0x%x, 0x%x, %d, %d)\n", (u_long)csr,
		(u_long)vi, len, encryptqual);
#endif
	len += VMTP_CKSUMLEN;
	vlen = len - sizeof(struct vmtp_header);
	setvi_length(vi, vlen - VH_DELTALEN);

#ifdef	VMTPDEBUG
	vmtp_dumpvi(vi,"vi", "vmtp_sendpacket");
	printf("vmtp_sendpacket(): len for checksum = %d\n", vlen);
#endif

#ifdef	VMTP_NOCKSM
#define vmtp_cksum(x, y, z) 0
#endif	VMTP_NOCKSM

	n = m;
	while (n->m_next)
		n = n->m_next;
	if (n->m_off <= MMAXOFF) 
		if (n->m_off + n->m_len <= MLEN - VMTP_CKSUMLEN)
			/* cksum fits in current mbuf */
			n->m_len += VMTP_CKSUMLEN;
		else {
			/* allocate a new mbuf */
			MGET(n->m_next, M_WAIT, MT_DATA);
			if(!n->m_next) {
#ifdef	VMTP_DEBUG
			printf("vmtp_sendpacket(): no mbuf for checksum!\n");
#endif
				m_freem(m);
				return ENOBUFS;
			}
			n = n->m_next;
			n->m_len = VMTP_CKSUMLEN;
		}
	else /* it's a cluster! */
		if ((n->m_off & CLMASK) == 0 &&
		     n->m_len <= CLBYTES - VMTP_CKSUMLEN)
			/* cksum fits in cluster (for sure) */
			n->m_len += VMTP_CKSUMLEN;
		else {
			/* allocate a new mbuf */
			MGET(n->m_next, M_WAIT, MT_DATA);
			if(!n->m_next) {
#ifdef	VMTP_DEBUG
			printf("vmtp_sendpacket(): no mbuf for checksum!\n");
#endif
				m_freem(m);
				return ENOBUFS;
			}
			n = n->m_next;
			n->m_len = VMTP_CKSUMLEN;
		}

	*vh_checksum(n) = vmtp_cksum(m, sizeof(struct vmtp_header),
					vlen-VMTP_CKSUMLEN);

#ifdef	VMTPDEBUG
	printf("vmtp_sendpacket(): sent cksum = 0x%x\n", vmtp_cksum(m,vlen));
#endif

#ifdef	VMTP_NOCKSM
#undef vmtp_cksum
#endif	VMTP_NOCKSM

	/*
	 * Encrypt the packet if necessery
	 */
	if (csr && (encryptqual != ENCRYPT_NONE)) {
#ifdef	ESP_DEBUG
		printf("vmtp_sendpacket(): encrypting\n");
#endif
#ifdef	LITTLE_ENDIAN
		vi->vi_type = IPPROTO_VMTPS;
#else
		vi->vi_type = IPPROTO_VMTPS2;
#endif	LITTLE_ENDIAN
		if (esp_encrypt(m, 
			sizeof(struct vmtp_header) + sizeof(struct vmtpeid),
			vlen - sizeof(struct vmtpeid),
			encryptqual, csr->vc_key)) {
#ifdef	ESP_DEBUG
			printf("vmtp_sendpacket(): BAD encryption qual: %d\n",
				encryptqual);
#endif
				m_freem(m);
				return -1;
		}
	} else {
#ifdef	LITTLE_ENDIAN
		vi->vi_type = IPPROTO_VMTP;
#else
		vi->vi_type = IPPROTO_VMTP2;
#endif	LITTLE_ENDIAN
	}	
		
	vi->vi_len = len;
#ifdef	VMTP_ETHER
	if (vi->vi_addr.va_type == VAT_ETHER) 
		return vmtp_sendetherpacket(m, (encryptqual != ENCRYPT_NONE));
#endif	VMTP_ETHER

	if (csr == NULL) {
		vi->vi_ttl = VMTPIP_TTL;
		return(vmtp_sendippacket(m,(encryptqual != ENCRYPT_NONE),NULL));
	} else {
		vi->vi_ttl = csr->vc_ipttl;
		return(vmtp_sendippacket(m, (encryptqual != ENCRYPT_NONE), 
				&csr->vc_iproute));
	}
} /* vmtp_sendpacket */

