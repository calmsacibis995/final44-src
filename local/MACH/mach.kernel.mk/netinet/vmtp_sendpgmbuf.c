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
 * $Log:	vmtp_sendpgmbuf.c,v $
 * Revision 2.3  89/03/09  20:50:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:05:40  gm0w
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
 * $ Header: vmtp_sendpgmbuf.c,v 2.1 87/08/14 15:44:38 mrt Exp $
 */
 
#include <mach_vmtp.h>

#define VMTP_INVOKE	1

/*
 * 	vmtp_sendpgmbuf.c
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
#include "vmtp_cksum.h"
#include "vmtp_send.h"

#if	VMTP_INVOKE
/*
 * copyin that is valid for kernel space also.
 */
#define COPYIN(error,from,to,len) {					\
		if ((((caddr_t)(from)) >= ((caddr_t)VM_MIN_KERNEL_ADDRESS)) &&		\
			    (((caddr_t)(from)) <= ((caddr_t)VM_MAX_KERNEL_ADDRESS))) {	\
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
 * Duplicate a cluster in a new mbuf.
 */
#define MCLDUP(from,to,off) {					\
	struct mbuf *p = mtod((from), struct mbuf *);		\
	(to)->m_off = ((int)p - (int)(to)) + (off);		\
	if (mtocl(p) > 290) {					\
		printf("from=0x%x, to=0x%x, off=0x%x, p=0x%x\n",\
			(from),(to),(off),p);			\
		panic("MCLDUP: out of mclrefcnt");		\
	}							\
	mclrefcnt[mtocl(p)]++;					\
}


/*
 * vmtp_sendpgmbuf:
 * Send a packet group from an mbuf chain:
 * if first transmission the create the mbuf chain by copying in data from 
 *	memory as the packets are sent.
 * if it's a retransmission just send from the mbuf chain. 
 */

vmtp_sendpgmbuf(csr, txmsk, dlvrmsk, retransflag, mtu, maxmask)
	register struct vmtpcsr *csr;
	u_long 			txmsk;
	u_long 			dlvrmsk;
	u_short 		retransflag;
	int			mtu;	/* in blocks: either 1 or 2 */
	u_long			maxmask;
{
	register struct vmtpiphdr *vi;
	u_long 			packettxmsk = 1;
	register struct mbuf 	*m;
	register struct mbuf 	**a_dataseg;
	register caddr_t 	segptr = csr->vc_segptr;
	register int 		segsize = csr->vc_segsize;
	register int 		len;
	int 			error;
	int 			pos;
	int 			skiplen;	


#if	VMTP_DEBUG
	printf("vmtp_sendpgmbuf(): txmsk = 0x%x, dlvrmsk = 0x%x segsize = %d\n",
		txmsk, dlvrmsk, segsize);
#endif
	if (vmtp_retransmit(retransflag))
		return vmtp_sendpgmbufre(csr, txmsk, dlvrmsk, mtu, maxmask);

	/* first transmission */
	
	a_dataseg = &(csr->vc_dataseg);
	*a_dataseg = NULL;

	if (txmsk != dlvrmsk) {
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpgmbuf(): bad parameters: txmsk != dlvrmsk\n");
		return EINVAL; /* *** OR SOMTHING */
#else
		panic("vmtp_sendpgmbuf(): bad parameters");
#endif
	}


	while (txmsk  && (segsize > 0)) {

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgmbuf(): segptr = 0x%x, segsize = 0x%x, txmsk = 0x%x\n", 
	(int)segptr, segsize, txmsk);
#endif

		skiplen = 0;
		while (!(txmsk & 0x01) && (skiplen < segsize)) {
			txmsk >>= 1;
			packettxmsk <<= 1;
			skiplen += VMTP_BLKSIZE;
		}
		segptr = (caddr_t)((int)segptr + skiplen);
		segsize -= skiplen;

		if (segsize < 0) {
			/* assume it's ok - receivers problem */
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpgmbuf(): txmsk 'bigger then' segsize\n");
#endif
			return 0;
		}

		if ((txmsk & maxmask) == maxmask) {
			/* (at least) this packet contigious in memory */
			m = vmtp_copyvihdr(csr->vc_vihdr);
			if (!m) {
#ifdef	VMTPDEBUG
			printf("vmtp_sendpgmbuf(): ENOBUFS for vi header\n");
#endif
				error = ENOBUFS;
				goto release;
			}
			vi = mtod(m, struct vmtpiphdr *);
			vi->vi_dlvrmsk = packettxmsk * maxmask;	
			len = MIN(mtu * VMTP_BLKSIZE, segsize);
			MGET(m->m_next, M_WAIT, MT_DATA);
			if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgmbuf(): ENOBUFS for segment\n");
#endif	
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}

		        MCLGET(m->m_next);
			if (m->m_next->m_len != CLBYTES) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpgmbuf(): ENOBUFS for segment\n");
#endif
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgmbuf(): copyin segptr = 0x%x,segsize = %d,txmsk = 0x%x\n",
	 (int)segptr, segsize, txmsk);
#endif
			COPYIN(error,segptr, mtod(m->m_next,caddr_t),len);
			if (error) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpgmbuf(): copyin failed: len = %d\n", 
				len);
#endif
				m_freem(m);
				goto release;
			}
			m->m_next->m_len = len;

		/* get a copy to be saved */
			MGET(*a_dataseg, M_WAIT, MT_DATA);
			if (!*a_dataseg) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgmbuf(): ENOBUFS for dataseg\n");
#endif	
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}
			MCLDUP(m->m_next, *a_dataseg, 0);
			(*a_dataseg)->m_len = len;
			a_dataseg = &((*a_dataseg)->m_next);


			if (txmsk == maxmask) {
				/* last packet in group */
				goto sendlast;
			}

			if (error = vmtp_sendpacket(csr, vi,
					len+sizeof(struct vmtpiphdr), 
					csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
			printf("vmtp_sendpgmbuf(): sendpacket() failed\n");
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
				panic("vmtp_sendpgmbuf");
			m = vmtp_copyvihdr(csr->vc_vihdr);
			if (!m) {
#ifdef	VMTPDEBUG
			printf("vmtp_sendpgmbuf(): ENOBUFS - vi header\n");
#endif
				error = ENOBUFS;
				goto release;
			}
			vi = mtod(m, struct vmtpiphdr *);
			vi->vi_dlvrmsk = packettxmsk;
			len = MIN(VMTP_BLKSIZE, segsize);
			MGET(m->m_next, M_WAIT, MT_DATA);
			if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgmbuf(): ENOBUFS for segment\n");
#endif
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}

			if (len > MLEN) {
			        MCLGET(m->m_next);
				if (m->m_next->m_len != CLBYTES) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpgmbuf(): ENOBUFS for segment\n");
#endif
					m_freem(m);
					error = ENOBUFS;
					goto release;
				}
			}

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgmbuf(): copyin segptr = 0x%x,segsize = %d,txmsk = 0x%x\n",
	 (int)segptr, segsize, txmsk);
#endif
			COPYIN(error,segptr, mtod(m->m_next,caddr_t),len);
			if (error) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpgmbuf(): copyin failed: len = %d\n", 
				len);
#endif
				m_freem(m);
				goto release;
			}
			m->m_next->m_len = len;

		/* get a copy to be saved */
			*a_dataseg = m_copy(m->m_next, 0, len);
			if (!*a_dataseg) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgmbuf(): ENOBUFS for dataseg\n");
#endif
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}


			segptr = (caddr_t)((int)segptr + len);
			segsize -=len;
			txmsk >>= 1;
			packettxmsk <<= 1;

			if (txmsk == 0 || segsize == 0) {
				/* send last - vi_dlvrmsk already set! */
				goto sendlast;
			}

			/* find the next block */

			skiplen = 0;
			while (!(txmsk & 0x01) && (skiplen < segsize)) {
				txmsk >>= 1;
				packettxmsk <<= 1;
				skiplen += VMTP_BLKSIZE;
			}
			segptr = (caddr_t)((int)segptr + skiplen);
			segsize -= skiplen;

			if (segsize < 0) {
				/* There wasn't another one - bad txmsk! */
				 /* send the first block anyway! */
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpgmbuf(): txmsk 'bigger then' segsize\n");
#endif
				segsize = 0; 
			}

			vi->vi_dlvrmsk |= packettxmsk;

			len = MIN(VMTP_BLKSIZE, segsize);

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgmbuf(): copyin segptr = 0x%x,segsize = %d,txmsk = 0x%x\n",
	 (int)segptr, segsize, txmsk);
#endif
			COPYIN(error,segptr, mtod(m->m_next,caddr_t),len);
			if (error) {
#ifdef	VMTPDEBUG
	    		printf("vmtp_sendpgmbuf(): copyin failed: len = %d\n", 
				len);
#endif
				m_freem(m);
				goto release;
			}
			m->m_next->m_len += len;

		/* 
		 * Update the copy - since the data must be in a cluster, the
		 * previous m_copy did a mcldup so we can just increase the
 		 * length here! 
		 */
			(*a_dataseg)->m_len += len;
			a_dataseg = &((*a_dataseg)->m_next);

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
			printf("vmtp_sendpgmbuf(): sendpacket() failed\n");
#endif
				goto release;
			}
		
			segptr = (caddr_t)((int)segptr + len - VMTP_BLKSIZE);
			segsize -=len - VMTP_BLKSIZE;
			txmsk >>= 1;
			packettxmsk <<= 1;
	
		} /* end if-else */

	} /* end while */
#ifdef	VMTP_DEBUG
	printf("vmtp_sendpgmbuf(): FALLING THROUGH - no segment???\n");
	return 0;
#else
	panic("vmtp_sendpgmbuf()");
#endif

sendlast:

#ifdef	VMTPDEBUG
	printf("vmtp_sendpgmbuf(): sending the LAST packet\n");
#endif
	andvi_control(vi, ~VCTL_CPG);
	vmtp_padlength(m, len);
	if (error = vmtp_sendpacket(csr, vi, len + sizeof(struct vmtpiphdr), 
				csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
		printf("vmtp_sendpgmbuf(): sendpacket() failed\n");
#endif
		goto release;
	}
	return 0;

release:

#ifdef	VMTPDEBUG
		printf("vmtp_sendpgmbuf(): Error return - dataseg freed\n");
#endif
	m_freem(csr->vc_dataseg);
	csr->vc_dataseg = NULL;

	return error;		
			
} /* vmtp_sendpgmbuf */

/* *** */

/*
 * A bit mask operation: move the n-most 1's from 'from' to 'to'
 */
#define move_nmost_ones(from, to, n) 				\
	{ 							\
		register u_long mask;				\
		register int count = (n);			\
								\
		for (mask = 1; mask && count; mask <<= 1) {	\
			if (from & mask) {			\
				from &= ~mask;			\
				to |= mask;			\
				count--;			\
			}					\
		}						\
	}	


/*
 * vmtp_sendpgmbufre:
 * retransmit from a list of mbufs.
 */
vmtp_sendpgmbufre(csr, txmsk, dlvrmsk, mtu, maxmask)
	struct vmtpcsr 		*csr;
	u_long 			txmsk;
	u_long 			dlvrmsk;
	int			mtu;	/* in blocks: either 1 or 2 */
	u_long			maxmask;
{
	register struct vmtpiphdr *vi;
	register u_long		efftxmsk;	
			/* effective transmit mask w.r.t. dlvrmsk i.e. w.r.t. 
			 * what's in the mbuf chain.
			 */				
	register struct mbuf 	*m;
	register struct mbuf    *dataseg = csr->vc_dataseg;
	int	 		len;
	int			curroff = 0;
	int 			offset;
	int 			error;

#ifdef	VMTP_DEBUG
	printf("vmtp_sendpgmbufre(): called\n");
#endif

	/* just to make sure that efftxmsk and txmsk will be equivalent */
	txmsk &= dlvrmsk;

	/* 
	 * compute the effective txmsk - dlvrmsk reflects what blocks there are
 	 * in dataseg!
	 */
	{
		register u_long mask = VMTP_MAXSEGMASK;
					/* highest bit in mask */
		efftxmsk = 0;
		for(; mask; mask >>= 1) {
			if (mask & dlvrmsk) {
				efftxmsk <<= 1;
				if (mask & txmsk)
					efftxmsk |= 1;
			}
		}
	}


	while (efftxmsk  && dataseg) {

#ifdef	VMTP_DEBUG
printf("vmtp_sendpgmbufre(): txmsk = 0x%x, dataseg = 0x%x, efftxmsk = 0x%x\n",
	txmsk, dataseg, efftxmsk);
#endif

		while (!(efftxmsk & maxmask) && dataseg) {
			efftxmsk >>= mtu;
			curroff += mtu * VMTP_BLKSIZE;
			while (dataseg && dataseg->m_len <= curroff) {
				curroff -= dataseg->m_len;
				dataseg = dataseg->m_next;
			}
		}

		if (!dataseg) {
			/* ran out of mbufs */
			/* assume it's ok - receivers problem */
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpgmbufre(): txmsk 'longer then' dataseg\n");
#endif
			return 0;
		}

		if ((efftxmsk & maxmask) == maxmask) {
			/* this packet contigious in the mbuf chain */
			m = vmtp_copyvihdr(csr->vc_vihdr);
			if (!m) {
#ifdef	VMTPDEBUG
			printf("vmtp_sendpgmbufre(): ENOBUFS for vi header\n");
#endif
				error = ENOBUFS;
				goto release;
			}
		    	vi = mtod(m, struct vmtpiphdr *);
			vi->vi_dlvrmsk = 0;
			len = MIN(mtu*VMTP_BLKSIZE, m_length(dataseg)-curroff);
			move_nmost_ones(txmsk,vi->vi_dlvrmsk, mtu);
			m->m_next = m_copy(dataseg, curroff, len);
			if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgmbufre(): ENOBUFS for segment\n");
#endif	
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}
#ifdef	VMTP_DEBUG
			vmtp_dumpmbuf(dataseg,"dataseg","vmtp_sendpgmbufre():");
#endif
			if (efftxmsk == maxmask) {
				/* last packet in group */
				goto sendlast;
			}

			if (error = vmtp_sendpacket(csr, vi,
					len+sizeof(struct vmtpiphdr),
					csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
			printf("vmtp_sendpgmbufre(): sendpacket() failed\n");
#endif
				goto release;
			}
			/* skip the packet that we just sent */
			efftxmsk >>= mtu;
			curroff += mtu * VMTP_BLKSIZE;
			while (dataseg && dataseg->m_len <= curroff) {
				curroff -= dataseg->m_len;
				dataseg = dataseg->m_next;
			}

		} /*end of sending a contigious packet */

		else { 
			/* 
			 * Take this block and then find the next one
			 * Will never be used when mtu is 1
			 */
			if (mtu == 1)
				panic("vmtp_sendpgmbufre");
			m = vmtp_copyvihdr(csr->vc_vihdr);
			if (!m) {
#ifdef	VMTPDEBUG
			printf("vmtp_sendpgmbufre(): ENOBUFS - vi header\n");
#endif
				error = ENOBUFS;
				goto release;
			}

			vi = mtod(m, struct vmtpiphdr *);
			vi->vi_dlvrmsk = 0;
			offset = curroff + (efftxmsk & 1) ? 0 : VMTP_BLKSIZE;
			len = MIN(VMTP_BLKSIZE, m_length(dataseg)-offset);
#ifdef	VMTP_DEBUG
			vmtp_dumpmbuf(dataseg,"dataseg","vmtp_sendpgmbufre():");
#endif
			m->m_next = m_copy(dataseg, offset, len);
			if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgmbufre(): ENOBUFS for segment\n");
#endif
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}

			if ((efftxmsk >> mtu) == 0 || !dataseg) {
				/* send last */
				move_nmost_ones(txmsk, vi->vi_dlvrmsk, 1);
				goto sendlast;
			}

			/* skip the block we just copied */
			efftxmsk >>= mtu;
			curroff += mtu * VMTP_BLKSIZE;
			while (dataseg && dataseg->m_len <= curroff) {
				curroff -= dataseg->m_len;
				dataseg = dataseg->m_next;
			}


			/* find the next block */

			while (!(efftxmsk & maxmask) && dataseg) {
				efftxmsk >>= mtu;
				curroff += mtu * VMTP_BLKSIZE;
				while (dataseg && dataseg->m_len <= curroff) {
					curroff -= dataseg->m_len;
					dataseg = dataseg->m_next;
				}
			}

			if (!dataseg) {
				/* There wasn't another one - bad txmsk! */
				 /* send the first block anyway! */
#ifdef	VMTP_DEBUG
		printf("vmtp_sendpgmbufre(): txmsk 'longer then' dataseg\n");
#endif
				move_nmost_ones(txmsk, vi->vi_dlvrmsk, 1);
				goto sendlast;
			}

			move_nmost_ones(txmsk, vi->vi_dlvrmsk, mtu);

			offset = curroff + (efftxmsk & 1) ? 0 : VMTP_BLKSIZE;
			len = MIN(VMTP_BLKSIZE, m_length(dataseg)-offset);

#ifdef	VMTP_DEBUG
			vmtp_dumpmbuf(dataseg,"dataseg","vmtp_sendpgmbufre():");
#endif

			if (m->m_next)
				while (m->m_next->m_next)
					m = m->m_next;

			m->m_next = m_copy(dataseg, offset, len);
			if (!m->m_next) {
#ifdef	VMTPDEBUG
		    	printf("vmtp_sendpgmbufre(): ENOBUFS for segment\n");
#endif
				m_freem(m);
				error = ENOBUFS;
				goto release;
			}

			/* include previous block in len */
			len += VMTP_BLKSIZE;
			if ((efftxmsk >> mtu) == 0) {
				/* last packet in group */
				goto sendlast;
			}

			if (error = vmtp_sendpacket(csr, vi, 
					len+sizeof(struct vmtpiphdr), 
					csr->vc_encryptqual)) {
#ifdef	VMTPDEBUG
			printf("vmtp_sendpgmbufre(): sendpacket() failed\n");
#endif
				goto release;
			}
		
			if (efftxmsk & 1) {
				/* there might be another block in this mbuf! */
				efftxmsk &= ~1;
			} else {
				/* next mbuf */
				efftxmsk >>= mtu;
				curroff += mtu * VMTP_BLKSIZE;
				while (dataseg && dataseg->m_len <= curroff) {
					curroff -= dataseg->m_len;
					dataseg = dataseg->m_next;
				}
			}
	
		} /* end if-else */
	} /* end while */
#ifdef	VMTP_DEBUG
	printf("vmtp_sendpgmbufre(): falling through\n");
#endif

sendlast:

#ifdef	VMTPDEBUG
	printf("vmtp_sendpgmbufre(): sending the LAST packet\n");
#endif
	andvi_control(vi, ~VCTL_CPG);
	vmtp_padlength(m, len);
	if (error = vmtp_sendpacket(csr, vi, len + sizeof(struct vmtpiphdr), 
				csr->vc_encryptqual)) {

#ifdef	VMTPDEBUG
		printf("vmtp_sendpgmbufre(): sendpacket() failed\n");
#endif
		goto release;
	}
	return 0;

release:

#ifdef	VMTPDEBUG
		printf("vmtp_sendpgmbufre(): Error return\n");
#endif

	return error;		

} /* vmtp_sendpgmbufre */

#endif	MACH_VMTP
