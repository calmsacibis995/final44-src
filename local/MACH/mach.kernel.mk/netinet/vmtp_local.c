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
 * $Log:	vmtp_local.c,v $
 * Revision 2.3  89/03/09  20:49:59  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:05:07  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_local.c,v 2.1 87/08/14 15:44:17 mrt Exp $
 */

/*
 * 	vmtp_local.c
 *	Written by Erik Nordmark
 */

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
#include "vmtp_cksum.h"
#include "vmtp_send.h"
#include "esp.h"

struct mbuf *m_copypartial();


/*
 * Send a packet group to a local entity.
 * Should only be callled when there is a segment to send.
 */
vmtp_sendlocalpg(csr, retransflag)
	register struct vmtpcsr *csr;
	u_short retransflag;
{
	register struct vmtpiphdr *vi;
	u_long 			txmsk;
	u_long 			dlvrmsk;
	struct mbuf 		*m, *mm;
	register caddr_t 	segptr;
	register int 		len;
	int			continious = 1;
	int 			error;


#ifdef	LOCAL_DEBUG
	printf("vmtp_sendlocalpg(): csr = 0x%x, retransflag = %d\n", csr,
		retransflag);
#endif
	txmsk = csr->vc_txmsk;
	if (vmtp_usrdlvrmskset(csr->vc_code)) {
		dlvrmsk =  csr->vc_usrdlvrmsk;
		continious = 0;
	} else {
		dlvrmsk = vmtp_segsizetomsk(csr->vc_segsize);
		if (txmsk != dlvrmsk)
			continious = 0;
	}
	txmsk &= dlvrmsk;

	if (!vcf_mbuf(csr)) {
#ifdef	LOCAL_DEBUG
		printf("vmtp_sendlocalpg(): not vcf_mbuf\n");
#endif
		error = getsegment(&m, csr->vc_segptr, csr->vc_segsize,
				continious ? (u_long)0 :txmsk);
		if (error) {
#ifdef	LOCAL_DEBUG
			printf("vmtp_sendlocalpg(): getsegment failed: %d\n",
				error);
#endif
			return error;
		}
	} else {
#ifdef	LOCAL_DEBUG
		printf("vmtp_sendlocalpg(): MBUF\n");
#endif
		if (!vmtp_retransmit(retransflag)) {
#ifdef	LOCAL_DEBUG
			printf("vmtp_sendlocalpg(): first transmission\n");
#endif
			error = getsegment(&m, csr->vc_segptr, csr->vc_segsize,
				continious ? (u_long)0 :txmsk);
			if (error) {
#ifdef	LOCAL_DEBUG
			printf("vmtp_sendlocalpg(): getsegment failed: %d\n",
				error);
#endif
				return error;
			}
			csr->vc_dataseg = m;
		} else
			if (txmsk != dlvrmsk)
				panic("vmtp_sendlocalpg");

		if (txmsk = dlvrmsk) {
#ifdef	LOCAL_DEBUG
			printf("vmtp_sendlocalpg(): copy the whole segment\n");
#endif
			m = m_copy(csr->vc_dataseg, 0, M_COPYALL);
			if (!m) {
#ifdef	LOCAL_DEBUG
				printf("vmtp_sendlocalpg(): m_copy failed\n");
#endif
				return ENOBUFS;
			}
		} else {
			u_long efftxmsk;
			u_long mask = VMTP_MAXSEGMASK;
					/* highest bit in mask */
#ifdef	LOCAL_DEBUG
			printf("vmtp_sendlocalpg(): partial copy\n");
#endif
			/* 
			 * compute the effective txmsk - dlvrmsk reflects 
		 	 * what blocks there are in dataseg!
			 */
			efftxmsk = 0;
			for(; mask; mask >>= 1) {
				if (mask & dlvrmsk) {
					efftxmsk <<= 1;
					if (mask & txmsk)
						efftxmsk |= 1;
				}
			}
			m = m_copypartial(csr->vc_dataseg, efftxmsk);
			if (!m) {
#ifdef	LOCAL_DEBUG
			printf("vmtp_sendlocalpg(): m_copypartial failed\n");
#endif
				return ENOBUFS;
			}
		}
	}

	/* get the vihdr and set info in it */
	mm = vmtp_copyvihdr(csr->vc_vihdr);
	if (!mm) {
#ifdef	LOCAL_DEBUG
	    	printf("vmtp_sendlocalpg(): ENOBUFS for vi header\n");
#endif
		m_freem(m);
		return(ENOBUFS);
	}
	mm->m_next = m;
	vi = mtod(mm, struct vmtpiphdr *);
	vi->vi_dlvrmsk = txmsk;
	setvi_control(vi, getvi_control(vi) & ~VCTL_CPG);
	/* don't have to pad the length since no checksumming is done */
	len = sizeof(struct vmtpiphdr) + m_length(m);
#ifdef	LOCAL_DEBUG
printf("vmtp_sendlocalpg(): len = %d, vc_segsize = %d, dlvrmsk = 0x%x\n",
		len, csr->vc_segsize, dlvrmsk);
#endif

	return vmtp_sendlocalpacket(csr, vi, len, csr->vc_encryptqual);
} /* vmtp_sendlocalpg */

/* 
 * Send a local packet.
 * Set up the info in the ip header that the receiver uses
 */
vmtp_sendlocalpacket(csr, vi, len, encryptqual)
	register struct vmtpcsr *csr;
	register struct vmtpiphdr *vi;
	int len;			
	u_long encryptqual;
{
	register struct mbuf *m = dtom(vi);
	register struct vmtp_header *vh;
	register int vlen;		

#ifdef	LOCAL_DEBUG
	printf("vmtp_sendlocalpacket(0x%x, 0x%x, %d, %d)\n", (u_long)csr,
		(u_long)vi, len, encryptqual);
#endif
	len += VMTP_CKSUMLEN;
	vlen = len - sizeof(struct vmtp_header);
	vh = (struct vmtp_header *)vi;

	/*
	 * Put VMTP length in extended header
	 */
	vh->vh_len = vlen;
	vh->vh_ttl = 1;	

#ifdef	LITTLE_ENDIAN
	if (csr && (encryptqual != ENCRYPT_NONE)) 
		vh->vh_type = IPPROTO_VMTPS;
	else
		vh->vh_type = IPPROTO_VMTP;

#else
	if (csr && (encryptqual != ENCRYPT_NONE)) 
		vh->vh_type = IPPROTO_VMTPS2;
	else
		vh->vh_type = IPPROTO_VMTP2;

#endif	LITTLE_ENDIAN
		
	vmtp_handle[getvi_fnctcode(vi)](vi);
	return 0;
} /* vmtp_sendlocalpacket */

/*
 * Get a partial copy of a mbuf chain copying the blocks specified
 * in the mask.
 */
struct mbuf *
m_copypartial(dataseg, mask)
	register struct mbuf *dataseg;
	register u_long mask;
{
	struct mbuf *m;
	register struct mbuf **a_m;
	register int curroff = 0;

#ifdef	LOCAL_DEBUG
	printf("m_copypartial(): dataseg = 0x%x, mask = 0x%x\n", dataseg, mask);
#endif
	a_m = &m;
	while (mask  && dataseg) {
#ifdef	LOCAL_DEBUG
		printf("m_copypartial(): curroff = %d, mask = 0x%x\n",
			curroff, mask);
#endif

		while (!(mask & 1) && dataseg) {
			mask >>= 1;
			curroff += VMTP_BLKSIZE;
			while (dataseg && dataseg->m_len <= curroff) {
				curroff -= dataseg->m_len;
				dataseg = dataseg->m_next;
			}
		}

		if (!dataseg) {
			/* ran out of mbufs */
#ifdef	LOCAL_DEBUG
		printf("m_copypartial(): mask 'longer then' dataseg\n");
#endif
			m_freem(m);			
			return NULL;
		}

		*a_m = m_copy(dataseg, curroff, VMTP_BLKSIZE);
		if (!*a_m) {
#ifdef	LOCAL_DEBUG
		    	printf("m_copypartial(): ENOBUFS for segment\n");
#endif	
			m_freem(m);
			return NULL;
		}

		/* skip the block that we just copied */
		mask >>= 1;
		curroff += VMTP_BLKSIZE;
		while (dataseg && dataseg->m_len <= curroff) {
			curroff -= dataseg->m_len;
			dataseg = dataseg->m_next;
		}
		while (*a_m)
			a_m = &(*a_m)->m_next;
	}

	return m;
} /* m_copypartial */


/*
 * Copies the segment into a mbuf chain: if it's shorter then MLEN one mbuf
 * is allocated else a sufficient number of clusters are allocated and linked 
 * together with a possible non-cluster mbuf at the end.
 * 
 * The mask determines what parts of the segment to copy in chunks 
 * of VMTP_BLKSIZE. If the mask is zero the whole segment is copied.
 */
getsegment(a_m, segptr, seglen, mask)
	struct mbuf 	**a_m;
	register caddr_t segptr;
	register int	seglen;
	u_long		mask;
{
	register struct mbuf 	*m = NULL;
	int		error;
	int blocklen, skiplen, spaceused;

#ifdef	LOCAL_DEBUG
	printf("getsegment(): ");
	printf("segptr = 0x%x, seglen = %d, mask = 0x%x\n",
		(int)segptr, seglen, mask);
#endif

	if (!mask) {
		while (seglen > 0) {
#ifdef	LOCAL_DEBUG
		printf("getsegment w/o mask: segptr = 0x%x, seglen = 0x%x\n", 
			(int)segptr, seglen);
#endif

			blocklen = MIN(seglen,CLBYTES);
			seglen -= blocklen;

			/* The first mbuf in the possible sequence */
			if (m == NULL) {
				MGET(m, M_WAIT, MT_DATA);
				if (m == NULL) {
					error = ENOBUFS;
					goto release;
				}
				*a_m = m;
			} else {
				MGET(m->m_next, M_WAIT, MT_DATA);
				if (m->m_next == NULL) {
					error = ENOBUFS;
					goto release;
				}
				m = m->m_next;
			}

			if (blocklen > MLEN) {
				/* get a cluster */
				MCLGET(m);
				if (m->m_len != CLBYTES) {
					error = ENOBUFS;
					goto release;
				}
			} 
	
	    		m->m_len = blocklen;

			error = copyin(segptr, mtod(m,caddr_t), blocklen);
			if (error) 
				goto release;
			
			segptr = (caddr_t)((int)segptr + blocklen);
		}

#ifdef	LOCAL_DEBUG
	printf("getsegment w/o mask done: segptr = 0x%x, seglen = 0x%x\n", 
		(int)segptr, seglen);
#endif
		return 0;
	} else {

		spaceused = 0;		/* in the current cluster */
		while (mask  && seglen > 0) {

#ifdef	LOCAL_DEBUG
printf("getsegment with mask: segptr = 0x%x, seglen = 0x%x, spaceused = %d\n", 
	(int)segptr, seglen, spaceused);
#endif

			skiplen = 0;
			while (!(mask & 0x01) && (skiplen < seglen)) {
				mask >>= 1;
				skiplen += VMTP_BLKSIZE;
			}
			segptr = (caddr_t)((int)segptr + skiplen);
			seglen -= skiplen;

			if (seglen < 0) {
#ifdef	LOCAL_DEBUG
			printf("getsegment(): mask 'bigger then' seglen\n");
#endif
				error = EINVAL;
				goto release;
			}

			blocklen = 0;
			while ((mask & 0x1) && (blocklen < CLBYTES-spaceused)) {
				mask >>= 1;
				blocklen += VMTP_BLKSIZE;
			}

			blocklen = MIN(blocklen,seglen);

			/* The first mbuf in the list */		
			if (m == NULL) {
				MGET(m, M_WAIT, MT_DATA);
				if (m == NULL) {
					error = ENOBUFS;
					goto release;
				}
				m->m_len = 0;
				*a_m = m;
			} else if (!spaceused) {
				MGET(m->m_next, M_WAIT, MT_DATA);
				if (m->m_next == NULL) {
					error = ENOBUFS;
					goto release;
				}
				m = m->m_next;
				m->m_len = 0;
			}

			if ((blocklen > MLEN) && !spaceused) { 	
			/* blocklen can be <= MLEN only for the last block */
				/* get a cluster */
				MCLGET(m);
				if (m->m_len != CLBYTES) {
					error = ENOBUFS;
					goto release;
				}
				m->m_len = 0;
			}

			error = copyin(segptr, (caddr_t)(mtod(m,int)+spaceused),
					blocklen);
			if (error) 
				goto release;

    			m->m_len += blocklen;
			spaceused += blocklen + CLBYTES;
			spaceused %= CLBYTES;

			segptr = (caddr_t)((int)segptr + blocklen);
			seglen -= blocklen;
		}

		if (mask) {
#ifdef	LOCAL_DEBUG
			printf("getsegment(): mask 'bigger then' seglen\n");
#endif
			goto release;
		}

#ifdef	LOCAL_DEBUG
	printf("getsegment with mask done: segptr = 0x%x, seglen = 0x%x\n", 
		(int)segptr, seglen);
#endif

	return 0;
	}


release:
	
#ifdef	LOCAL_DEBUG
	printf("getsegment: releasing mbufs due to error\n");
#endif
	
	m_freem(*a_m);
	return error;


} /* getsegment */		


