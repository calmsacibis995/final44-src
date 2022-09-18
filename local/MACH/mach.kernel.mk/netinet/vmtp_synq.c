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
 * $Log:	vmtp_synq.c,v $
 * Revision 2.4  89/03/09  20:51:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:06:15  gm0w
 * 	Updated copyright.  CMUCS -> MACH.
 * 	[89/02/12            gm0w]
 * 
 * 01-Oct-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	CMUCS: in vmtp_queuerequest, there may be requests
 *	already received but waiting for a response, even if
 *	there are no outstanding non-received requests. Be careful
 *	when setting the vs_cnext pointer in that case.
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
 * $ Header: vmtp_synq.c,v 2.2 88/06/08 16:20:15 mwyoung Exp $
 */

/*
 * 	vmtp_synq.c	0.1	2/5/87
 *	Routines relating to the synchronization queue
 *	Written by Erik Nordmark
 */

/*
 * TODO
 */

#if	MACH_VMTP

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


/*
 * vmtp_synqenq -  insert csr at the tail of the queue 
 *
 * Must be called at splimp
 */
vmtp_synqenq(csr,queue)
	register struct vmtpcsr *csr;
	register struct vmtpsynq *queue;
{
#ifdef	VMTP_DEBUG
	printf("vmtp_synqenq(): csr = 0x%x, queue = 0x%x\n",csr,queue);
#endif
	csr->vc_qprev = queue->vq_ctail;
	csr->vc_qnext = &queue->vq_queue;
	csr->vc_qhead = queue;
	queue->vq_ctail->vq_next = &csr->vc_queue;
	queue->vq_ctail = &csr->vc_queue;
} /* vmtp_synqenq */


/*
 * vmtp_synqdeq - dequeue a csr from the queue it's in.
 *
 * The csr has to point to a synch queue. Must be called at splimp.
 */
struct vmtpsynq*
vmtp_synqdeq(csr)
	register struct vmtpcsr *csr;
{
	register struct vmtpsynq *queue;

#ifdef	VMTP_DEBUG
	printf("vmtp_synqdeq(): csr = 0x%x\n",csr);
#endif

	queue = csr->vc_qhead;
	if (!queue) {
#ifdef	VMTP_DEBUG
		printf("vmtp_synqdeq(): csr->vc_qhead == NULL!\n");
#endif
		panic("vmtp_synqdeq");
	}


#ifdef	VMTP_DEBUG
	printf("vmtp_synqdeq(): queue type = %d\n", queue->vq_type);
#endif
	
	csr->vc_qnext->vq_prev = csr->vc_qprev;
	csr->vc_qprev->vq_next = csr->vc_qnext;

	csr->vc_qprev = csr->vc_qnext = NULL;
	csr->vc_qhead = NULL;
} /* vmtp_synqdeq */

/*
 * VMTP start timer routine. 
 * Insert csr into csr timeout queue.
 * The queue is a delta list.  That is,
 * the time left before timeout of a csr is relative to the
 * csr that will timeout before him.
 */
vmtp_starttimer(csr, tleft)
	register struct vmtpcsr *csr;
	register u_short tleft;
{
	register struct vmtpsynqovl	*qelt;
	register int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_starttimer(): csr = 0x%x, time = %d\n", csr, tleft);
#endif


	s = splimp();

	if (csr->vc_qhead) {
		/* already queued */
#ifdef	VMTP_DEBUG 
	printf("vmtp_starttimer(): already queued, qhead = 0x%x, type = %d\n",
			csr->vc_qhead, csr->vc_qhead->vq_type);
#endif	
		panic("vmtp_starttimer: already queued");
	}
	
	for (qelt = vtimeoqueue.vq_chead;
	     qelt != &vtimeoqueue.vq_queue 
	     && ((struct vmtpcsr *)qelt)->vc_tleft < tleft;
	     qelt = qelt->vq_next)
		tleft -= ((struct vmtpcsr *)qelt)->vc_tleft;

	/* insert before qelt */
	csr->vc_tleft = tleft;
	csr->vc_qhead = &vtimeoqueue;
	csr->vc_qnext = qelt;
	csr->vc_qprev = qelt->vq_prev;
	qelt->vq_prev->vq_next = &csr->vc_queue;
	qelt->vq_prev = &csr->vc_queue;
	if (qelt != &vtimeoqueue.vq_queue)
		((struct vmtpcsr *)qelt)->vc_tleft -= csr->vc_tleft;

	splx(s);
} /* vmtp_starttimer */

/*
 * VMTP stop timer routine. Remove csr from the timeout queue.
 * 
 * If it's not in the queue return 0; else non-zero
 * Must be called at splimp!
 */
vmtp_stoptimer(csr)
	register struct vmtpcsr *csr;

{
#ifdef	VMTP_DEBUG
	printf("vmtp_stoptimer(): csr = 0x%x\n", csr);
#endif

	if (csr->vc_qhead != &vtimeoqueue) {
#ifdef	VMTP_DEBUG
		printf("vmtp_stoptimer(): can't stop!, qhead = 0x%x\n",
			csr->vc_qhead);
#endif

		return 0;
	}
	
	if (csr->vc_qnext != &vtimeoqueue.vq_queue) {
		((struct vmtpcsr *)csr->vc_qnext)->vc_tleft += csr->vc_tleft;
	}

	vmtp_synqdeq(csr);
	return 1;
} /* vmtp_stoptimer */

/*
 * Deliver a request to server by inserting a remote csr into the server
 * queue. 
 */
vmtp_queuerequest(csr, ser)
	register struct vmtpcsr	*csr;
	register struct vmtpser	*ser;
{
	register int s;
#ifdef	VMTP_DEBUG
	printf("vmtp_queuerequest() csr = 0x%x, ser = 0x%x\n", csr, ser);
#endif

	s = splimp();
	vmtp_synqenq(csr, &ser->vs_queue);
	if (ser->vs_cnext == &ser->vs_queue.vq_queue) {
#ifdef	MACH
		ser->vs_cnext = &csr->vc_queue;
#else	MACH
		ser->vs_cnext = ser->vs_chead;
#endif	MACH
		ser->vs_flags |= VS_REQQUEUED;
	}
	splx(s);
	
} /* vmtp_queuerequest */

/*
 * Retrive the next request from the servers queue - if none return NULL
 * Only advance the vs_cnext pointer.
 */
struct vmtpcsr *
vmtp_retrievereq(ser)
	register struct vmtpser *ser;
{
	register struct vmtpcsr *csr;
	register int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_retrievereq(): ser = 0x%x\n", ser);
#endif

	s = splimp();

	if (ser->vs_cnext == &ser->vs_queue.vq_queue) {
		splx(s);
		return NULL;
	}
	csr = (struct vmtpcsr *)ser->vs_cnext;
	ser->vs_cnext = csr->vc_qnext;

	if (ser->vs_cnext == &ser->vs_queue.vq_queue) {
		ser->vs_flags &= ~VS_REQQUEUED;
	}

	splx(s);

	return csr;
} /* vmtp_retrievereq */


/*
 * Remove a csr from the servers queue.
 * Return NULL if it isn't on the queue.
 */
struct vmtpcsr *vmtp_dequeuereq(ser, client)
	register struct vmtpser *ser;
	struct vmtpeid client;
{
	register struct vmtpsynqovl *qelt;
	register int s = splimp();
	
#ifdef	VMTP_DEBUG
	printf("vmtp_dequeuereq(): ser = 0x%x\n", ser);
	vmtp_dumpeid(&client, "client", "vmtp_dequeuereq");
#endif
	for (qelt = ser->vs_chead; qelt != ser->vs_cnext; qelt = qelt->vq_next)
#define csr 	((struct vmtpcsr *)qelt)
		if (vmtp_sameeid(csr->vc_client, client)) {
			vmtp_synqdeq(csr);
			splx(s);
			return csr;
#undef csr
		}
	splx(s);
	return NULL;
} /* vmtp_dequeuereq */

/*
 * Check if the csr has been received on the ser i.e. if it's before the
 * vs_cnext pointer into the queue.
 */
vmtp_isreceived(csr, ser)
	register struct vmtpcsr *csr;
	register struct vmtpser *ser;
{
	register struct vmtpsynqovl *qelt;
	register int s = splimp();
	
#ifdef	VMTP_DEBUG
	printf("vmtp_isreceived(): csr = 0x%x, ser = 0x%x\n", csr, ser);
#endif
	if (csr->vc_qhead == NULL) {
		splx(s);
		return 0;
	}
	
	for (qelt = ser->vs_chead; qelt != ser->vs_cnext; qelt = qelt->vq_next)
		if (qelt == &csr->vc_queue) {
			splx(s);
			return 1;
		}
			
	splx(s);
	return 0; 
} /* vmtp_isreceived */

/*
 * Called every 20 msec.  It checks the vtimeoqueue for any csr that times out
 * or decrements the time left of the csr.
 */
vmtp_timeout()
{
	register struct vmtpsynqovl *qelt;
	register int s = splimp();

	if ((qelt = vtimeoqueue.vq_chead) == &vtimeoqueue.vq_queue) {
		goto done;
	}

#define csr  	((struct vmtpcsr *)qelt)

	csr->vc_tleft--;
	while (qelt != &vtimeoqueue.vq_queue && csr->vc_tleft == 0) {
		/* 
		 * Stop the timer. Inline version of vmtp_stoptimer
		 */
		if (csr->vc_qhead != &vtimeoqueue) {
#ifdef	VMTP_DEBUG
			printf("vmtp_timeout(): inconsistent, qhead = 0x%x\n",
				csr->vc_qhead);
#endif
			panic("vmtp_timeout");
		}
		vmtp_synqdeq(csr);
		splx(s);
				/* allow access during timeout processing! */
		/* Handle the timeout */
		(csr->vc_hdltimeo)(csr);
		s = splimp();
		qelt = vtimeoqueue.vq_chead;
	}

#undef csr
done:
	splx(s);
	timeout(vmtp_timeout, (caddr_t)0, hz/VMTP_TIMEOFREQ);
} /* vmtp_timeout */

#endif	MACH_VMTP
