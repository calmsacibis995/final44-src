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
 * $Log:	vmtp_subr.c,v $
 * Revision 2.4  89/03/09  20:50:59  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:06:06  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.2  88/08/24  02:07:08  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:10:37  mwyoung]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *	Fixed a bug in vmtp_savesegment().
 *	Disabled VMTP-specific checksum, replaced with in_cksum.
 *
 * 05-Jun-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_LOGSTAT: added declaration for vmtpparam.
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
 
#include <mach_vmtp.h>

#define VMTP_LOGSTAT	1

/*
 * $ Header: vmtp_subr.c,v 2.2 88/08/24 02:07:08 mwyoung Exp $
 */

/*
 * 	vmtp_subr.c	0.1	10/26/86
 *	Written by Erik Nordmark and Joyo Wijaya
 *	Some unix specific code is collected at the end of this module.
 */

/*
 * TODO
 *
 */

#ifdef	GROUP_DEBUG
#define VMTP_DEBUG
#define VMTPDEBUG
#endif

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <sys/quota.h>
#include <sys/proc.h>

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
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "vmtp_send.h"
#include "vmtp_cksum.h"
#include "if_ether.h"

/*
 * Create a new VMTP client state record.  Allocate the vmptip header
 * template for the csr.  And insert the csr into the specified map.
 */
struct vmtpcsr *vmtp_newcsr(c, map)
	struct vmtpeid c;
	register struct vmtpcsr **map;
{
	register struct mbuf *m;
	register struct vmtpcsr *csr;
	register int h;
	int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_newcsr(): map = 0x%x\n", map);
	vmtp_dumpeid(&c, "c", "vmtp_newcsr()");
#endif

	csr = vmtp_alloccsr();
	if (csr == NULL)
		return(NULL);
	bzero((caddr_t)csr, sizeof(struct vmtpcsr));
	/*
	 * Allocate header so that the checksum fits in the end of the mbuf
	 * (saves an m_get for messages without segments) and so that at
	 * least an Ethernet header fits in front (saves an m_get in if_output).
	 * vmtp_copyvihdr preserves this when copied!
	 */
	m = m_getclr(M_DONTWAIT, MT_HEADER);	/* obtain header */
	if (m == NULL) {
		vmtp_dealloccsr(csr);
		return(NULL);
	}
	m->m_len = sizeof (struct vmtpiphdr);
	m->m_off = MMAXOFF - VMTP_CKSUMLEN - sizeof(struct vmtpiphdr);
	csr->vc_vihdr = mtod(m, struct vmtpiphdr *);
	setvi_domain(csr->vc_vihdr, 0x1);
	csr->vc_client = c;
	csr->vc_action = VCA_NOOP;
	csr->vc_ipttl = VMTPIP_TTL;

	h = vmtp_hash(&c);		/* insert into map */
	s = splimp();
	csr->vc_next = map[h];
	map[h] = csr;
	splx(s);
	return(csr);
} /* vmtp_newcsr */

/*
 * Find a csr with the given eid
 */
struct vmtpcsr *vmtp_maptocsr(c, map)
	struct vmtpeid	c;
	register struct vmtpcsr **map;
{
	register struct vmtpcsr *curr;

	curr = map[vmtp_hash(&c)];
	while (curr != NULL && !vmtp_sameeid(curr->vc_client, c))
		curr = curr->vc_next;
	return(curr);
} /* vmtp_maptocsr */

/* 
 * Find the next csr with the same client eid
 */
struct vmtpcsr *vmtp_nextcsr(csr)
	register struct vmtpcsr *csr;
{
	register struct vmtpcsr *csr1;

#ifdef	VMTP_DEBUG
	printf("vmtp_nextcsr(): csr = 0x%x\n", csr);
#endif
	for (csr1 = csr->vc_next; csr1; csr1 = csr1->vc_next) {	
		if (vmtp_sameeid(csr->vc_client, csr1->vc_client)) {
#ifdef	VMTP_DEBUG
			printf("vmtp_nextcsr(): returning 0x%x\n", csr1);
#endif
			return csr1;
		}
	}
#ifdef	VMTP_DEBUG
	printf("vmtp_nextcsr(): returning NULL\n");
#endif
	return NULL;
} /* vmtp_nextcsr */

/*
 * Remove a csr from the map and deallocate the csr buffers.
 * Also remove possible additional csr's in the response queue.
 */
vmtp_freecsr(csr, map)
	register struct vmtpcsr	*csr;
	register struct vmtpcsr **map;
{
	register struct vmtpcsr **c;
	int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_freecsr(): csr = 0x%x, map = 0x%x\n", csr, map);
#endif
	if (csr == NULL)
		return;

	if (csr->vc_qhead) {
#ifdef	VMTP_DEBUG
		printf("vmtp_freecsr(): FREEING csr in queue?!\n");
#endif
		panic("vmtp_freecsr");
	}

	s = splimp();
	if (csr->vc_responses) {
		/* remove from response queue */
		vmtp_freerbqueue(csr->vc_responses, map);
		vmtp_deallocsynq(csr->vc_responses);
	}

	for (c = map + vmtp_hash(&csr->vc_client);
	     *c != csr && *c != NULL; c = &((*c)->vc_next));
	if (*c == csr)
		*c = csr->vc_next;
	splx(s);
	if (vcf_mbuf(csr)) {
		m_freem(csr->vc_dataseg);
	}
	m_free(dtom(csr->vc_vihdr));
	vmtp_dealloccsr(csr);
} /* vmtp_freecsr */

/*
 * Remove all additional csr's with the same eid.
 * Works for remote csr's only!
 */
vmtp_csrcleanup(csr)
	register struct vmtpcsr *csr;
{
	register struct vmtpcsr **a_csr, *csr1;
	int s = splimp();

#ifdef	VMTP_DEBUG
	printf("vmtp_csrcleanup(): csr = 0x%x\n", csr);
	vmtp_dumpeid(&csr->vc_client, "vc_client", "vmtp_csrcleanup");
#endif
	a_csr = &csr->vc_next;
	while (*a_csr) {
		if (!vmtp_sameeid(csr->vc_client, (*a_csr)->vc_client)) {
			a_csr = &(*a_csr)->vc_next;
		} else {
#ifdef	VMTP_DEBUG
			printf("vmtp_csrcleanup(): csr1 = 0x%x\n", *a_csr);
			vmtp_dumpeid(&(*a_csr)->vc_server, "vc_server", 
				"vmtp_csrcleanup");
#endif
			csr1 = *a_csr;
			*a_csr = (*a_csr)->vc_next;	/* remove from map */
			if (csr1->vc_qhead) {
				vmtp_synqdeq(csr1);
			}

			if (csr1->vc_responses) {
				panic("vmtp_csrcleanup");
			}

			if (vcf_mbuf(csr1) && csr1->vc_dataseg) {
				m_freem(csr1->vc_dataseg);
			}
			m_free(dtom(csr1->vc_vihdr));
			vmtp_dealloccsr(csr1);
		}
	}
	splx(s);
} /* vmtp_csrcleanup */

/*
 * Free all the csr's in the queue
 */
vmtp_freecsrqueue(q, map)
	register struct vmtpsynq *q;
	register struct vmtpcsr **map;
{
	register struct vmtpsynqovl *qelt;

#ifdef	VMTP_DEBUG
	printf("vmtp_freecsrqueue(): q = 0x%x, head = 0x%x\n", q, &q->vq_queue);
#endif

#define csr ((struct vmtpcsr *)qelt)
	while ((qelt = q->vq_chead) != &q->vq_queue) {
		vmtp_synqdeq(csr);
		vmtp_freecsr(csr, map);
	}
#undef csr
} /* vmtp_freecsrqueue */


/*
 * Create a new VMTP response buffer.  Allocate the vmptip header
 */
struct vmtpcsr *vmtp_newrb()
{
	register struct mbuf *m;
	register struct vmtpcsr *rb;

#ifdef	GROUP_DEBUG
	printf("vmtp_newrb(): called!\n");
#endif

	rb = vmtp_allocrb();
	if (rb == NULL)
		return(NULL);
	bzero((caddr_t)rb, VMTP_RBSIZE);
	/*
	 * Allocate header so that the checksum fits in the end of the mbuf
	 * (saves an m_get for messages without segments) and so that at
	 * least an Ethernet header fits in front (saves an m_get in if_output).
	 * vmtp_copyvihdr preserves this when copied!
	 */
	m = m_getclr(M_DONTWAIT, MT_HEADER);	/* obtain header */
	if (m == NULL) {
		vmtp_deallocrb(rb);
		return(NULL);
	}
	m->m_len = sizeof (struct vmtpiphdr);
	m->m_off = MMAXOFF -VMTP_CKSUMLEN - sizeof(struct vmtpiphdr);
	rb->vc_vihdr = mtod(m, struct vmtpiphdr *);
	rb->vc_action = VCA_NOOP;
	return rb;
} /* vmtp_newrb */


/*
 * Free a response buffer
 */
vmtp_freerb(rb)
	register struct vmtpcsr *rb;
{
	if (rb->vc_responses) 
		panic("vmtp_freerb");

	if (vcf_mbuf(rb)) {
		m_freem(rb->vc_dataseg);
	}
	m_free(dtom(rb->vc_vihdr));
	vmtp_deallocrb(rb);
} /* vmtp_freerb */

/*
 * Free all the rb's in the queue
 */
vmtp_freerbqueue(q)
	register struct vmtpsynq *q;
{
	register struct vmtpsynqovl *qelt;

#ifdef	GROUP_DEBUG
	printf("vmtp_freerbqueue(): q = 0x%x, head = 0x%x\n", q, &q->vq_queue);
#endif

#define rb ((struct vmtpcsr *)qelt)
	while ((qelt = q->vq_chead) != &q->vq_queue) {
		vmtp_synqdeq(rb);
		vmtp_freerb(rb);
	}
#undef rb
} /* vmtp_freerbqueue */


/*
 * Find the reply buffer for this server in the queue.
 * Returns NULL if not found.
 * Caller has to guarantee exlusive access to synch queue.
 */
struct vmtpcsr *vmtp_findrb(rq,server)
	register struct vmtpsynq *rq;
	struct vmtpeid server;
{
	register struct vmtpsynqovl *qelt;
	int s;

#ifdef	GROUP_DEBUG
	printf("vmtp_findrb(): rq = 0x%x\n", rq);
	vmtp_dumpeid(&server, "server", "vmtp_findrb");
#endif
	s = splimp();

#define rb ((struct vmtpcsr *)qelt)
	for (qelt = rq->vq_chead; qelt != &rq->vq_queue; qelt = qelt->vq_next) {
		if (vmtp_sameeid(rb->vc_server, server)) {
			splx(s);
			return rb;
		}
	}
#undef rb
	splx(s);
	return NULL;
} /* vmtp_findrb */

/*
 * Scan the queue of response buffers looking for one with a complete 
 * segment.
 */
struct vmtpcsr* vmtp_scanresponses(rq)
	register struct vmtpsynq *rq;
{
	register struct vmtpsynqovl *qelt;
	int s;

#ifdef	GROUP_DEBUG
	printf("vmtp_scanresponses(): rq = 0x%x\n", rq);
#endif
	if (!rq)
		return NULL;

	s = splimp();
#define rb ((struct vmtpcsr *)qelt)
	for (qelt = rq->vq_chead; qelt != &rq->vq_queue; qelt = qelt->vq_next) {
        	if (rb->vc_state == VC_RECVRESP &&
		    (!vmtp_segmentdata(rb->vc_code) || 
		     rb->vc_dlvrmsk == (vmtp_usrdlvrmskset(rb->vc_code)
				? rb->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(rb->vc_segsize)))) {
			splx(s);
			return rb;
			}
	}
#undef rb
	splx(s);
	return NULL;

} /* vmtp_scanresponses */


/*
 * Create a new VMTP server entity record.
 * Initialize it.
 */
struct vmtpser *vmtp_newserver(s)
	struct vmtpeid s;
{
	struct vmtpser *ser;
	int h,ss;

#ifdef	VMTP_DEBUG
	printf("vmtp_newserver(): called\n");
	vmtp_dumpeid(&s, "s", "vmtp_newserver()");
#endif

	ser = vmtp_allocser();
	if (ser == NULL)
		return (NULL);
	ser->vs_server = s;
	ser->vs_ctail = ser->vs_chead = ser->vs_cnext = &ser->vs_queue.vq_queue;
	ser->vs_qhead = NULL;
	ser->vs_type = VQ_SERVER;

	h = vmtp_hash(&s);
	ss = splimp();
	ser->vs_next = vservermap[h];		/* insert to map */
	vservermap[h] = ser;
	splx(ss);
	return(ser);
} /* vmtp_newserver */


/*
 * Map an eid to the corresponding ser
 */	
struct vmtpser *vmtp_maptoserver(s)
	struct vmtpeid	s;
{
	register struct vmtpser *curr;

#ifdef	VMTPDEBUG
	vmtp_dumpeid(&s, "s", "vmtp_maptoserver(): eid to be mapped");
#endif

	curr = vservermap[vmtp_hash(&s)];
	while (curr != NULL && !vmtp_sameeid(curr->vs_server, s))
		curr = curr->vs_next;
	return(curr);
} /* vmtp_maptoserver */

/* 
 * Find the next ser using the obvious ordering starting at hash bucket 0 and
 * following the next pointers. When called with NULL it returns the first 
 * ser, and in returns NULL when all have been returned.
 */
struct vmtpser *vmtp_nextserver(ser)
	register struct vmtpser *ser;
{
	register int i;

#ifdef	VMTP_DEBUG
	printf("vmtp_nextserver(): ser = 0x%x\n", ser);
#endif
	if (ser == NULL) {
		for (i = 0; i < VMTP_HASHMAPSIZE; i++) 
			if (vservermap[i] != NULL) {
#ifdef	VMTP_DEBUG
				printf("vmtp_nextserver(): first 0x%x\n", 
					vservermap[i]);
#endif
				return vservermap[i];
			}
#ifdef	VMTP_DEBUG
		printf("vmtp_nextserver(): first NULL\n");
#endif
		return NULL;
	}	

	if (ser->vs_next == NULL) {
		i =  vmtp_hash(&ser->vs_server);
		if (++i < VMTP_HASHMAPSIZE) {
			for (; i < VMTP_HASHMAPSIZE; i++) 
				if (vservermap[i] != NULL) {
#ifdef	VMTP_DEBUG
				printf("vmtp_nextserver(): bucket %d 0x%x\n", 
					i, vservermap[i]);
#endif
					return vservermap[i];
				}
		}
#ifdef	VMTP_DEBUG
		printf("vmtp_nextserver(): bucket %d NULL\n", i);
#endif
		return NULL;
	}
#ifdef	VMTP_DEBUG
	printf("vmtp_nextserver(): returning next 0x%x\n", ser->vs_next);
#endif
	return ser->vs_next;

} /* vmtp_nextserver */

/*
 * Remove a ser from the server map and deallocate the server buffers.
 * Also free the csr's that are queued on the ser. This will not cause any
 * problems for duplicate detection since the server entity id is stable,
 * so it won't be reused.
 */
vmtp_freeserver(ser)
	register struct vmtpser	*ser;
{
	register struct vmtpser **s;
	register struct vmtpcsr *csr;
	int ss;

#ifdef	VMTP_DEBUG
	printf("vmtp_freeserver(): ser = 0x%x\n", ser);
#endif
	if (ser == NULL)
		return;

	/* free the csr's that are queued on the ser */
	ss = splimp();
	vmtp_freecsrqueue(&ser->vs_queue, vremotecsrmap);

	for (s = vservermap + vmtp_hash(&ser->vs_server);
	     *s != ser && *s != NULL; s = &((*s)->vs_next));
	if (*s == ser)
		*s = ser->vs_next;
	splx(ss);

 	vmtp_deallocser(ser);
} /* vmtp_freeserver */



/*
 * Save data in the packet vi into the csr buffers.
 */
vmtp_savesegment(csr, vi)
	struct vmtpcsr	*csr;
	struct vmtpiphdr *vi;
{
	register struct mbuf *m = dtom(vi);
	register u_long dlvrmsk = vi->vi_dlvrmsk;
	register u_long currmsk = csr->vc_dlvrmsk;
	register struct mbuf **dblk = &(csr->vc_dataseg);
    	register struct mbuf *m1;	
	register int curroff, skiplen;

#ifdef	VMTP_DEBUG
	printf("vmtp_savesegment(): csr = 0x%x, vi = 0x%x)\n", csr, vi);
	printf("vmtp_savesegment(): vc_dlvrmsk = 0x%x, vi_dlvrmsk = 0x%x\n",
		csr->vc_dlvrmsk, vi->vi_dlvrmsk);
#endif
	
	if ((dlvrmsk & currmsk) == dlvrmsk) {
		m_freem(m);
		return;
	}

	/*
	 * Drop header.
	 *
	 * Note that full size packets (i.e. consisting of 1 or 2 blocks) are
	 * never zero padded.So the only possible zero padding is at the end
	 * of the segment, and is thrown away when the segment is copied to user
	 * space since Putsegment() will only copy out vc_segsize bytes.
	 */
	if (m->m_len >= sizeof(struct vmtpiphdr)) {
		m->m_len -= sizeof (struct vmtpiphdr);
		if (!m->m_len)
			m = m_free(m);
		else
			m->m_off += sizeof (struct vmtpiphdr);
	}
#ifdef	VMTP_DEBUG
	else {
		printf("vmtp_savesegment(): to short vi hdr mbuf!\n");
		return 0;
	}
#else
	else
		panic("vmtp_savesegment(): to short vi hdr mbuf!\n");
#endif

	/* 
	 * Common case - the packet contains two neighboring blocks that are
	 * ``newer'' then the ones already received.
 	 * NOTE: this assumes that at most two bits are set in dlvrmsk !
	 */

	if (dlvrmsk > currmsk 
#if	(VMTP_MAXBLKPACKET == 2)
				&& (dlvrmsk & (dlvrmsk>>1)) > currmsk) 
#endif
									{
		while (*dblk)
			dblk = &((*dblk)->m_next);
		*dblk = m;
		csr->vc_dlvrmsk |= dlvrmsk;
		return 0;
	}


	/* 
	 * Remove blocks already received from the just-arrived packet
	 */

	if (dlvrmsk & currmsk) {
		while (dlvrmsk && currmsk) {
			if (dlvrmsk & currmsk & 0x1) {
				/* first block on packet already received */
				m_adj(m, VMTP_BLKSIZE);
				if (!m)
					panic("vmtp_savesegment: short mbuf 1");
				break;
			} else if (dlvrmsk & 0x1) {
				/* not first, so second! */
				skiplen = VMTP_BLKSIZE;
				m1 = m;
				while (skiplen && m1) 
					if (m->m_len <= skiplen) {
						skiplen -= m->m_len;
						m1 = m1->m_next;
					} else {
						m1->m_off += skiplen;
						m1->m_len -= skiplen;
						break;
					}
				if (!m1)
					panic("vmtp_savesegment: short mbuf 2");
				m_freem(m1->m_next);
				break;
			} else {
				dlvrmsk >>= 1;
				currmsk >>= 1;
			}
		}
		/* restore masks */
		currmsk = csr->vc_dlvrmsk;
		dlvrmsk = vi->vi_dlvrmsk & ~currmsk;
	}
					
	/*
	 * Walk the chain of already-received blocks and stop at the place
	 * where to insert the just-received blocks.  
	 */

	curroff = 0;
	while (dlvrmsk) {
#ifdef	VMTP_DEBUG
		printf("vmtp_savesegment(): dlvrmsk = 0x%x, currmsk = 0x%x\n", 
			dlvrmsk, currmsk);
#endif
		if (dlvrmsk & 0x1) {
			if (curroff) {
				/* split mbuf */
#ifdef	VMTP_DEBUG
		printf("vmtp_savesegment(): splitting already saved\n");
		printf("\t*dblk = 0x%x, curroff = %d, len = %d\n",
			*dblk, curroff, (*dblk)->m_len - curroff);
#endif
				m1 = m_copy(*dblk, curroff, 
					(*dblk)->m_len-curroff);
				if (!m1) {
					goto failed;
				}
				m1->m_next = (*dblk)->m_next;
				(*dblk)->m_len = curroff;
				curroff = 0;
				dblk = &(*dblk)->m_next;
			} else
				m1 = *dblk;
			*dblk = m;
			dlvrmsk >>= 1;
			currmsk >>= 1;
#ifdef	MACH
			/*
			 * Worry about
			 *	currmsk = 1110100
			 *	dlvrmsk =    1000
			 */
			if ((dlvrmsk == 0) || ((currmsk & (dlvrmsk - 1)) == 0)) {
#else	MACH
			if (dlvrmsk <= currmsk) {
#endif	MACH
				/* 
				 * The two blocks in the packet are consequtive
				 * with respect to the blocks received sofar.
				 * The equals case captures when both masks
				 * have become 0.
				 */
#ifdef	VMTP_DEBUG
		printf("vmtp_savesegment(): dlvr (0x%x) <= curr (0x%x)\n", 
			dlvrmsk, currmsk);
#endif
				while (*dblk) 
					dblk = &(*dblk)->m_next;
				*dblk = m1;
				goto done;
			}
			/* Split the incomming packet into two blocks */
#ifdef	VMTP_DEBUG
printf("vmtp_savesegment(): Split the incomming packet into two blocks\n");
#endif
			skiplen = VMTP_BLKSIZE;
			while (skiplen && *dblk) {
				if ((*dblk)->m_len <= skiplen) {
					skiplen -= (*dblk)->m_len;
					dblk = &(*dblk)->m_next;
				} else 
					break;
			}
			if (skiplen) {
				/* split mbuf */
#ifdef	VMTP_DEBUG
		printf("vmtp_savesegment(): splitting the incoming packet\n");
		printf("\t*dblk = 0x%x, skiplen = %d, len = %d\n",
			*dblk, skiplen, (*dblk)->m_len - skiplen);
#endif
				m = m_copy(*dblk, skiplen,
					(*dblk)->m_len - skiplen);
				if (!m) {
					goto failed;
				}
				m->m_next = (*dblk)->m_next;
				(*dblk)->m_len = skiplen;
				dblk = &(*dblk)->m_next;
			} else
				m = *dblk;
			/* m is the 2nd block in the received packet */
			*dblk = m1;
		}
		else if (currmsk & 0x1) {
			/* find where to split if we later have to */
#ifdef	VMTP_DEBUG
	printf("vmtp_savesegment(): find where to split if we later have to\n");
#endif
			skiplen = VMTP_BLKSIZE + curroff;
			while (skiplen && *dblk) {
				if ((*dblk)->m_len <= skiplen) {
					skiplen -= (*dblk)->m_len;
					dblk = &(*dblk)->m_next;
				} else 
					break;
			}
			curroff = skiplen;
			dlvrmsk >>= 1;
			currmsk >>= 1;
		}
		else {
			dlvrmsk >>= 1;
			currmsk >>= 1;
		}
	}
done: 	
	csr->vc_dlvrmsk |= vi->vi_dlvrmsk;
	return 0;

failed:
#ifdef	VMTP_DEBUG
	printf("vmtp_savesegment(): ENOBUFS\n");
#endif
	/* maybe a bit conservative but ... */
	m_freem(m);
	m_freem(m1);
	m_freem(csr->vc_dataseg);
	csr->vc_dataseg = NULL;
	csr->vc_dlvrmsk = 0;
	return ENOBUFS;
} /* vmtp_savesegment */

/*
 * For handling words spanning mbuf boundaries
 */
union {
	u_long	total;
	struct { u_short 	first, second; } h;
	struct { u_char	q1st, q2nd, q3rd, q4th; } q;
} bswc;

/*
 * Byteswap a mbuf chain
 * Only works on little-endians since vmtp_byteswaplong isn't defined for
 * big-endians.
 * When a word crosses an mbuf boundary this algorithm assumes that the first
 * of these mbufs contains at least 3 bytes.
 */
vmtp_byteswap(m, off, len)
	register struct mbuf *m;
	int off,len;
{
	register u_long *word, *maxword;
	struct mbuf *n;
	register int count;

#ifdef	ESP_DEBUG
	printf("vmtp_byteswap(): off = %d, len = %d\n", off, len);
#endif
	if (len & 0x3 != 0) {
		printf("vmtp_byteswap: bad length\n");
		return;
	}


	while (m && len) {
#ifdef	ESP_DEBUG
		printf("vmtp_byteswap():  off = %d, len = %d\n", 
		off, len);
#endif

		while (m && m->m_len <= off) {
			off -= m->m_len;
			m = m->m_next;
		}
		
		if (!m) 	
			panic("vmtp_byteswap");

		count = MIN(m->m_len - off, len);
		word = (u_long *)(mtod(m, char *) + off);
		maxword = word + count/4;

#ifdef	ESP_DEBUG
	printf("vmtp_byteswap():  word = 0x%x, maxword = 0x%x, count = %d\n", 
		word, maxword, count);
#endif

#define oneiteration \
			*word = vmtp_byteswaplong(*word);	\
			word++;

		while (word <= maxword - 8) {
			oneiteration
			oneiteration
			oneiteration
			oneiteration
			oneiteration
			oneiteration
			oneiteration
			oneiteration
		}

		while (word <= maxword - 2) {
			oneiteration
			oneiteration
		}

		if (word < maxword) {
			oneiteration
		}

#undef oneiteration

		switch (count & 0x3) {
			case 0: break;
			case 3: 
			{
				bswc.h.first =				
				    *(u_short *)(mtod(m, caddr_t)+m->m_len-3);
				bswc.q.q3rd = *(mtod(m, caddr_t)+m->m_len-1);
				bswc.q.q4th = *(mtod(n, caddr_t));	
				bswc.total = vmtp_byteswaplong(bswc.total);
				off = 1;
				*(u_short *)(mtod(m, caddr_t)+m->m_len-3) = 
					bswc.h.first;			
				*(mtod(m, caddr_t)+m->m_len-1) = bswc.q.q3rd;
				*(mtod(n, caddr_t)) = bswc.q.q4th;	
				break;
			}
			case 2: 
			{
				bswc.h.first =				
				    *(u_short *)(mtod(m, caddr_t)+m->m_len-2);
				bswc.h.second =				
					*(u_short *)(mtod(n, caddr_t));
				bswc.total = vmtp_byteswaplong(bswc.total);
				*(u_short *)(mtod(m, caddr_t)+m->m_len-2) = 
					bswc.h.first;			
				*(u_short *)(mtod(n, caddr_t)) = 	
					bswc.h.second;			
				off = 2;
				break;
			}
			case 1: 
			{
				bswc.q.q1st = *(mtod(m, caddr_t)+m->m_len-1);
				bswc.q.q2nd = *(mtod(n, caddr_t));	
				bswc.h.second =				
					*(u_short *)(mtod(n, caddr_t)+1);
				bswc.total = vmtp_byteswaplong(bswc.total);
				*(mtod(m, caddr_t)+m->m_len-1) = bswc.q.q1st;
				*(mtod(n, caddr_t)) = bswc.q.q2nd;	
				*(u_short *)(mtod(n, caddr_t)+1) = 	
					bswc.h.second;			
				off = 3;
				break;
			}
		}
		len -= count + off;
		m = m->m_next;

	}
	if (len) {
		printf("vmtp_byteswap: out of data\n");
	}
	
} /* vmtp_byteswap */

#if	1	/* DPJ */
vmtp_cksum(m, off, len)
	register struct mbuf *m;
	int off;
	register int len;
{
	int hold_off;
	int hold_len;
	int ret;

	while (m && m->m_len <= off) {
		off -= m->m_len;
		m = m->m_next;
	}

	if (!m)
		panic("vmtp_cksum");

	hold_off = m->m_off;
	hold_len = m->m_len;
	m->m_off += off;
	m->m_len -= off;

	ret = in_cksum(m,len);

	m->m_off = hold_off;
	m->m_len = hold_len;
	return ret;
}
#else	1	/* DPJ */
/* 
 * Official checksum to use in VMTP. When this implmentation is as efficient
 * as in_cksum it should be used on VMTP packets!
 * Right now used only for checksumming the authenticatior (version 3)
 * This implementation requires that the length of each mbuf is a multiple
 * of 4 bytes!
 */
vmtp_cksum(m, off, len)
	register struct mbuf *m;
	int off;
	register int len;
{
	register int *word;
	register int a1 = 0;
	register int a2 = 0;
	register int  *lastword;
	int len1; 

#ifdef	ESP_DEBUG
	printf("vmtp_cksum(): m = 0x%x, off = %d, len = %d\n", m, off, len);
#endif
	while (m && m->m_len <= off) {
		off -= m->m_len;
		m = m->m_next;
	}

	if (!m)
		panic("vmtp_cksum");

	while (m && len) {
		word = (int *)(mtod(m, caddr_t) + off);

		/* Compute: len1 = MIN(len, m->m_len - off); */
		if ((len1 = m->m_len - off) > len)
			len1 = len;

		if (len1 & 0x3) {
			printf("vmtp_cksum: not word-aligned mbuf boundaries\n");
			return 0;
		}
		len -= len1;
		lastword = word + (len1>>2);
#ifdef	ESP_DEBUG
		printf("vmtp_cksum(): word = 0x%x, lastword = 0x%x, len1 = %d\n",
			word, lastword, len1);
#endif

#define oneiteration \
			a1 += *(word++); \
			a2 += a1; 
#define fiveiterations \
			oneiteration \
			oneiteration \
			oneiteration \
			oneiteration \
			oneiteration 

		if (lastword == word + 15) {
			fiveiterations
			fiveiterations
			fiveiterations

			m = m->m_next;
			off = 0;
			continue;
 		}

		while (lastword >= word + 16) {
			fiveiterations
			fiveiterations
			fiveiterations
			oneiteration

		}
		while (lastword >= word + 2) {
			oneiteration
			oneiteration
		}
		if (lastword != word) {
			oneiteration
		}
#undef oneiteration
#undef fiveiterations
		m = m->m_next;
		off = 0;
	}
	if (len) {
		printf("vmtp_cksum: out of data\n");
		return 0;
	}
	if (a2 == 0)
		a2 =3;
	return a2;
} /* vmtp_cksum */
#endif	1	/* DPJ */


/* Definitely UNIX dependent parts */
 

/*
 * Get the mtu for the interface being used
 * Copy of parts from ip_output().
 */
vmtp_mtu(csr)
	register struct vmtpcsr *csr;
{
	register struct route *ro;
	register struct ifnet *ifp;
	register struct sockaddr_in *dst;

#ifdef	ESP_DEBUG
	printf("vmtp_mtu(): csr = 0x%x\n", csr);
#endif

	if (csr->vc_vihdr->vi_addr.va_type == VAT_ETHER)
		return ETHERMTU;

	ro = &csr->vc_iproute;

	if (ro->ro_rt == 0) 
		rtalloc(ro);


	dst = (struct sockaddr_in *)&ro->ro_dst;
	/*
	 * If there is a cached route,
	 * check that it is to the same destination
	 * and is still up.  If not, free it and try again.
	 */
	if (ro->ro_rt && ((ro->ro_rt->rt_flags & RTF_UP) == 0 ||
	   dst->sin_addr.s_addr != csr->vc_vihdr->vi_addr.va_inet)) {
		RTFREE(ro->ro_rt);
		ro->ro_rt = (struct rtentry *)0;
	}
	if (ro->ro_rt == 0) {
		dst->sin_family = AF_INET;
		dst->sin_addr.s_addr = csr->vc_vihdr->vi_addr.va_inet;
	}

	if (ro->ro_rt == 0 || (ifp = ro->ro_rt->rt_ifp) == 0) {
#ifdef	ESP_DEBUG
		printf("vmtp_mtu(): default\n");
#endif
		return 
#ifndef	ONEBLOCK
			VMTP_MAXBLKPACKET * 
#endif
			VMTP_BLKSIZE + 
			sizeof(struct vmtpiphdr) + VMTP_CKSUMLEN;
					/* default */
	} 
	ro->ro_rt->rt_use++;

#ifdef	ONEBLOCK
	return 	VMTP_BLKSIZE + sizeof(struct vmtpiphdr) + VMTP_CKSUMLEN;
#else
#ifdef	ESP_DEBUG
	printf("vmtp_mtu(): mtu = %d\n", ifp->if_mtu);
#endif
	return ifp->if_mtu;
#endif
} /* vmtp_mtu */

/*
 * Signal the process corresponding to the server
 * The signal that is used for orphaned request and is SIGURG.
 * Cowards call this routine at splimp (changing the vs_flags).
 */		
vmtp_signal(ser, csr)
	register struct vmtpser *ser;
	register struct vmtpcsr *csr;
{
	register struct vmtpcsr *lcsr;
	register struct proc *p;

#ifdef	ESP_DEBUG
	printf("vmtp_signal(): called\n");
	vmtp_dumpeid(&ser->vs_server, "vs_server", "vmtp_signal");
	vmtp_dumpeid(&csr->vc_client, "vc_client", "vmtp_signal");
#endif

	ser->vs_flags |= VS_ORPHAN;
	ser->vs_orphan = csr->vc_client;


	lcsr = vmtp_maptocsr(ser->vs_server, vlocalcsrmap);
	if (lcsr == NULL)
		return;
	p = pfind(lcsr->vc_processid.pi_local);
	if (p == NULL)
		return;
#ifdef	ESP_DEBUG
	printf("vmtp_signal(): signaling p = 0x%x\n", p);
#endif
	psignal(p, SIGURG);

} /* vmtp_signal */

/*
 * Copy a vi header, placing it at the end of the mbuf.
 * This saves an m_get in the if_output() routine for the ethernet header.
 */
struct mbuf *vmtp_copyvihdr(vi)
	register struct vmtpiphdr *vi;
{
	register struct mbuf *m;

	MGET(m, M_DONTWAIT, MT_HEADER);
	if (!m)
		return NULL;
	m->m_len = sizeof(struct vmtpiphdr);
	m->m_off = MMAXOFF - VMTP_CKSUMLEN - sizeof(struct vmtpiphdr);
	bcopy((caddr_t)vi, mtod(m, caddr_t), sizeof(struct vmtpiphdr));
	return m;
} /* vmtp_copyvihdr */

/*
 * The length of an mbuf chain
 */
m_length(m)
	register struct mbuf *m;
{
	register int len = 0;
	
	while (m) {
		len += m->m_len;
		m = m->m_next;
	}
	return len;
}


/*
 * Translate a vmtp response code to an approximate unix error code
 * Note the use on the undefined error code 80 when there no reasonable
 * error code exists. This will just signal the occurens of a  VMTP error
 * and the exact reason can be found in the response code itself.
 */
u_char vmtp_codetounix[VMTP_NUMCODES] = {
	0,		/* VMTP_OK */
	ETIMEDOUT,	/* VMTP_RETRY */
	ETIMEDOUT,	/* VMTP_RETRYALL */
	80,		/* VMTP_BUSY */
	80,		/* VMTP_NONEXIST */
	80,		/* VMTP_MIGRATED */
	EACCES,		/* VMTP_NOPERMISSN */
	80,		/* VMTP_NOTAWAIT */
	80,		/* VMTP_PROERROR */
	80,		/* VMTP_FREQRFSD */
	80,		/* VMTP_BADTID */
	EOPNOTSUPP,	/* VMTP_NOSTREAMING */ 
	80,		/* VMTP_NORUNREC */
	ETIMEDOUT,	/* VMTP_REXMTTIMEO */
	ETIMEDOUT,	/* VMTP_USERTIMEO */
	80,		/* VMTP_RESPDISC */
	EOPNOTSUPP,	/* VMTP_NOSECURITY */
	80,		/* VMTP_BADREPLY */
	EACCES,		/* VMTP_SECUREREQ */
	EOPNOTSUPP,	/* VMTP_NOMULTICAST */
	ETIMEDOUT,	/* VMTP_MANYRETRIES */
	80,		/* VMTP_NOPRINCIPAL */
	80,		/* VMTP_NOKEY */
	80,		/* VMTP_CACHEMISS */
};
	

/*
 * Tables used a little bit of everywhere 
 */

u_long vmtp_sizemap[33] = {
	0x00000000,
	0x00000001,	0x00000003,	0x00000007,	0x0000000f,	
	0x0000001f,	0x0000003f,	0x0000007f,	0x000000ff,
	0x000001ff,	0x000003ff,	0x000007ff,	0x00000fff,
	0x00001fff,	0x00003fff,	0x00007fff,	0x0000ffff,
	0x0001ffff,	0x0003ffff,	0x0007ffff,	0x000fffff,
	0x001fffff,	0x003fffff,	0x007fffff,	0x00ffffff,
	0x01ffffff,	0x03ffffff,	0x07ffffff,	0x0fffffff,
	0x1fffffff,	0x3fffffff,	0x7fffffff,	0xffffffff,
};


#if	VMTP_LOGSTAT
struct vmtpparam vmtpparam = {	5,	/* VT_RECVPGFACTOR */
				100,	/* VTC_AWAITRESP */
				20,	/* VTC_ROUNDTRIP */
				10,	/* VTC_RECEIVEPG */
				10,	/* VTS_RECEIVEPG */
				1000,	/* VTS_ORPHAN */
				10,	/* VTS_ROUNDTRIP */
				6000,	/* VTS_DISCARDCSR */
				20,	/* VTS_RETRANSMIT */
				3	/* VMTP_MAXREXMTCNT */
};
#endif	VMTP_LOGSTAT

