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
 * $Log:	vmtp_buf.c,v $
 * Revision 2.3  89/03/09  20:47:50  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:02:56  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_buf.c,v 2.1 87/08/14 15:42:59 mrt Exp $
 */

/*
 * 	vmtp_buf.c		2/19/87
 *	Written by Erik Nordmark
 */

/*
 * A simple buffer manager that uses mbufs for storing smaller records
 *
 * Currently used for server descriptors, group records and group member records
 */

#if	MACH_VMTP
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


/*
 * Initialize the buffer manager
 */
vmtp_initbuf()
{
	vb_freegroup = NULL;
	vb_freemember = NULL;
	vb_freeser = NULL;
	vb_freesynq = NULL;
	vb_freehostgr = NULL;
} /* vmtp_initbuf */

/*
 * Allocate a group record
 */
struct vmtpgroup *vmtp_allocgroup()
{
	struct vmtpgroup *g;
	struct vmtppool *pool;
	struct mbuf *m;
	int i,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_allocgroup(): called\n");
#endif
	s = splimp();

	if ((g = vb_freegroup) == NULL) {
		m = m_get(M_DONTWAIT, MT_DATA);	
		if (m == NULL) {
			splx(s);
			return(NULL);
		}
		m->m_len = sizeof(struct vmtppool);
		pool = mtod(m, struct vmtppool *);
		pool->vp_used = 0;
		pool->vp_type = VP_GROUP;
		for (i = 0; i < VP_MAXGROUPS; i++) {
			pool->vp_groups[i].vg_next = g;
			g = &(pool->vp_groups[i]);
		}
		vb_freegroup = g;
	}
	vb_freegroup = g->vg_next;
	mtod(dtom(g), struct vmtppool *)->vp_used++;	
				/* incr used count for this pool/mbuf */
	splx(s);
	return g;
} /* vmtp_allocgroup */


/*
 * Allocate a member record
 */
struct vmtpmember *vmtp_allocmember()
{
	struct vmtpmember *mem;
	struct vmtppool *pool;
	struct mbuf *m;
	int i,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_allocmember(): called\n");
#endif
	s = splimp();

	if ((mem = vb_freemember) == NULL) {
		m = m_get(M_DONTWAIT, MT_DATA);	
		if (m == NULL) {
			splx(s);
			return(NULL);
		}
		m->m_len = sizeof(struct vmtppool);
		pool = mtod(m, struct vmtppool *);
		pool->vp_used = 0;
		pool->vp_type = VP_MEMBER;
		for (i = 0; i < VP_MAXMEMBERS; i++) {
			pool->vp_members[i].vm_next = mem;
			mem = &(pool->vp_members[i]);
		}
		vb_freemember = mem;
	}
	vb_freemember = mem->vm_next;
	mtod(dtom(mem), struct vmtppool *)->vp_used++;	
				/* incr used count for this pool/mbuf */
	splx(s);
	return mem;
} /* vmtp_allocmember */


/*
 * Allocate a server descriptor
 */
struct vmtpser *vmtp_allocser()
{
	struct vmtpser *ser;
	struct vmtppool *pool;
	struct mbuf *m;
	int i,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_allocser(): called\n");
#endif
	s = splimp();

	if ((ser = vb_freeser) == NULL) {
		m = m_get(M_DONTWAIT, MT_PCB);	
		if (m == NULL) {
			splx(s);
			return(NULL);
		}
		m->m_len = sizeof(struct vmtppool);
		pool = mtod(m, struct vmtppool *);
		pool->vp_used = 0;
		pool->vp_type = VP_SER;
#ifdef	VMTP_DEBUG
		printf("vmtp_allocser(): pool = 0x%x\n", pool);
#endif
		for (i = 0; i < VP_MAXSERS; i++) {
			pool->vp_sers[i].vs_next = ser;
			ser = &(pool->vp_sers[i]);
		}
		vb_freeser = ser;
	}
	vb_freeser = ser->vs_next;
	mtod(dtom(ser), struct vmtppool *)->vp_used++;	
				/* incr used count for this pool/mbuf */
	splx(s);
	return ser;
} /* vmtp_allocser */


/*
 * Allocate a synch queue head.
 * Note: vq_qhead is used as a next pointer !
 */
struct vmtpsynq *vmtp_allocsynq()
{
	struct vmtpsynq *synq;
	struct vmtppool *pool;
	struct mbuf *m;
	int i,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_allocsynq(): called\n");
#endif
	s = splimp();

	if ((synq = vb_freesynq) == NULL) {
		m = m_get(M_DONTWAIT, MT_PCB);	
		if (m == NULL) {
			splx(s);
			return(NULL);
		}
		m->m_len = sizeof(struct vmtppool);
		pool = mtod(m, struct vmtppool *);
		pool->vp_used = 0;
		pool->vp_type = VP_SYNQ;
		for (i = 0; i < VP_MAXSYNQS; i++) {
			pool->vp_synqs[i].vq_qhead = synq;
			synq = &(pool->vp_synqs[i]);
		}
		vb_freesynq = synq;
	}
	vb_freesynq = synq->vq_qhead;
	mtod(dtom(synq), struct vmtppool *)->vp_used++;	
				/* incr used count for this pool/mbuf */
	splx(s);
	return synq;
} /* vmtp_allocsynq */

/*
 * Allocate a hostgroup record.
 */
struct vmtphostgroup *vmtp_allochostgroup()
{
	struct vmtphostgroup *hostgroup;
	struct vmtppool *pool;
	struct mbuf *m;
	int i,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_allochostgroup(): called\n");
#endif
	s = splimp();

	if ((hostgroup = vb_freehostgr) == NULL) {
		m = m_get(M_DONTWAIT, MT_PCB);	
		if (m == NULL) {
			splx(s);
			return(NULL);
		}
		m->m_len = sizeof(struct vmtppool);
		pool = mtod(m, struct vmtppool *);
		pool->vp_used = 0;
		pool->vp_type = VP_HOSTGR;
		for (i = 0; i < VP_MAXHOSTGRS; i++) {
			pool->vp_hostgrs[i].vh_next = hostgroup;
			hostgroup = &(pool->vp_hostgrs[i]);
		}
		vb_freehostgr = hostgroup;
	}
	vb_freehostgr = hostgroup->vh_next;
	mtod(dtom(hostgroup), struct vmtppool *)->vp_used++;	
				/* incr used count for this pool/mbuf */
	splx(s);
	return hostgroup;
} /* vmtp_allochostgroup */


/*
 * Deallocate a group.
 * Free the mbuf if the used count becomes zero.
 */
vmtp_deallocgroup(g)
	struct vmtpgroup *g;
{
	struct vmtppool *pool;
	struct vmtpgroup **a_g;
	struct mbuf *m;
	int s,i;

#ifdef	VMTP_DEBUG
	printf("vmtp_deallocgroup(): g = 0x%x\n", g);
#endif
	s = splimp();

	pool = mtod(dtom(g), struct vmtppool *);
		/* decr used count for this pool/mbuf */
	g->vg_next = vb_freegroup;
	vb_freegroup = g;
	if (--pool->vp_used == 0)  {
		/* remove all records in that mbuf from the free list */
		m = dtom(pool);
		for(i = 0, a_g = &(vb_freegroup); *a_g != NULL; /* nop */)
			if (dtom(*a_g) == m) {
				*a_g = (*a_g)->vg_next;
				i++;
			} else {
				a_g = &(*a_g)->vg_next;
			}
		if (i != VP_MAXGROUPS)
			panic("vmtp_deallocgroup");
		m_free(m); 
	}
	splx(s);
} /* vmtp_deallocgroup */


/*
 * Deallocate a member.
 * Free the mbuf if the used count becomes zero.
 */
vmtp_deallocmember(mem)
	struct vmtpmember *mem;
{
	struct vmtppool *pool;
	struct vmtpmember **a_mem;
	struct mbuf *m;
	int s,i;

#ifdef	VMTP_DEBUG
	printf("vmtp_deallocmember(): mem = 0x%x\n", mem);
#endif
	s = splimp();

	pool = mtod(dtom(mem), struct vmtppool *);
		/* decr used count for this pool/mbuf */
	mem->vm_next = vb_freemember;
	vb_freemember = mem;
	if (--pool->vp_used == 0)  {
		/* remove all records in that mbuf from the free list */
		m = dtom(pool);
		for(i = 0, a_mem = &(vb_freemember); *a_mem != NULL; /* nop */)
			if (dtom(*a_mem) == m) {
				*a_mem = (*a_mem)->vm_next;
				i++;
			} else {
				a_mem = &(*a_mem)->vm_next;
			}
		if (i != VP_MAXMEMBERS)
			panic("vmtp_deallocmember");
		m_free(m);
	}
	splx(s);
} /* vmtp_deallocmember */


/*
 * Deallocate a ser.
 * Free the mbuf if the used count becomes zero.
 */
vmtp_deallocser(ser)
	struct vmtpser *ser;
{
	struct vmtppool *pool;
	struct vmtpser **a_ser;
	struct mbuf *m;
	int s,i;

#ifdef	VMTP_DEBUG
	printf("vmtp_deallocser(): ser = 0x%x\n", ser);
#endif
	s = splimp();

	pool = mtod(dtom(ser), struct vmtppool *);
		/* decr used count for this pool/mbuf */
#ifdef	VMTP_DEBUG
	printf("vmtp_deallocser(): pool = 0x%x\n", pool);
#endif
	ser->vs_next = vb_freeser;
	vb_freeser = ser;
	if (--pool->vp_used == 0)  {
		/* remove all records in that mbuf from the free list */
		m = dtom(pool);
		for(i = 0, a_ser = &(vb_freeser); *a_ser != NULL; /* nop */)
			if (dtom(*a_ser) == m) {
				*a_ser = (*a_ser)->vs_next;
				i++;
			} else {
				a_ser = &(*a_ser)->vs_next;
			}
#ifdef	VMTP_DEBUG
		printf("vmtp_deallocser(): i = %d, MAX = %d\n", i, VP_MAXSERS);
#endif
		if (i != VP_MAXSERS)
			panic("vmtp_deallocser");
		m_free(m);
	}
	splx(s);
} /* vmtp_deallocser */


/*
 * Deallocate a synq.
 * Free the mbuf if the used count becomes zero.
 * Note: vq_qhead is used as a next pointer !
 */
vmtp_deallocsynq(synq)
	struct vmtpsynq *synq;
{
	struct vmtppool *pool;
	struct vmtpsynq **a_synq;
	struct mbuf *m;
	int s,i;

#ifdef	VMTP_DEBUG
	printf("vmtp_deallocsynq(): synq = 0x%x\n", synq);
#endif
	s = splimp();

	pool = mtod(dtom(synq), struct vmtppool *);
		/* decr used count for this pool/mbuf */
	synq->vq_qhead = vb_freesynq;
	vb_freesynq = synq;
	if (--pool->vp_used == 0)  {
		/* remove all records in that mbuf from the free list */
		m = dtom(pool);
		for(i = 0, a_synq = &(vb_freesynq); *a_synq != NULL; /* nop */)
			if (dtom(*a_synq) == m) {
				*a_synq = (*a_synq)->vq_qhead;
				i++;
			} else {
				a_synq = &(*a_synq)->vq_qhead;
			}
		if (i != VP_MAXSYNQS)
			panic("vmtp_deallocsynq");
		m_free(m);
	}
	splx(s);
} /* vmtp_deallocsynq */

/*
 * Deallocate a hostgroup record.
 * Free the mbuf if the used count becomes zero.
 */
vmtp_deallochostgroup(hostgr)
	struct vmtphostgroup *hostgr;
{
	struct vmtppool *pool;
	struct vmtphostgroup **a_hostgr;
	struct mbuf *m;
	int s,i;

#ifdef	VMTP_DEBUG
	printf("vmtp_deallochostgroup(): hostgr = 0x%x\n", hostgr);
#endif
	s = splimp();

	pool = mtod(dtom(hostgr), struct vmtppool *);
		/* decr used count for this pool/mbuf */
	hostgr->vh_next = vb_freehostgr;
	vb_freehostgr = hostgr;
	if (--pool->vp_used == 0)  {
		/* remove all records in that mbuf from the free list */
		m = dtom(pool);
		for(i = 0, a_hostgr = &(vb_freehostgr); *a_hostgr != NULL; /* nop */)
			if (dtom(*a_hostgr) == m) {
				*a_hostgr = (*a_hostgr)->vh_next;
				i++;
			} else {
				a_hostgr = &(*a_hostgr)->vh_next;
			}
		if (i != VP_MAXHOSTGRS)
			panic("vmtp_deallochostgroup");
		m_free(m);
	}
	splx(s);
} /* vmtp_deallochostgroup */

#define csrtopool(csr) ((struct vmtplpool *)((((u_long)csr)>>CLSHIFT)<<CLSHIFT))


/*
 * Allocate a client state record
 */
struct vmtpcsr *vmtp_alloccsr()
{
	struct vmtpcsr *csr;
	struct vmtplpool *pool;
	struct mbuf *m;
	int i,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_alloccsr(): called\n");
#endif
	s = splimp();

	if ((csr = vb_freecsr) == NULL) {
		m = m_get(M_DONTWAIT, MT_PCB);	
		if (m == NULL) {
			splx(s);
			return(NULL);
		}
		MCLGET(m);
		if (m->m_len != CLBYTES) {
			m_free(m);
			splx(s);
			return(NULL);
		}
		m->m_len = sizeof(struct vmtplpool);
		pool = mtod(m, struct vmtplpool *);
		pool->vpl_used = 0;
		pool->vpl_type = VPL_CSR;
		pool->vpl_mbuf = m;
		for (i = 0; i < VPL_MAXCSRS; i++) {
			pool->vpl_csrs[i].vc_next = csr;
			csr = &(pool->vpl_csrs[i]);
		}
		vb_freecsr = csr;
	}
	vb_freecsr = csr->vc_next;
	csrtopool(csr)->vpl_used++;	/* incr used count for this pool/mbuf */
	splx(s);
	return csr;
} /* vmtp_alloccsr */

/*
 * Allocate a response buffer (subset of a csr)
 */
struct vmtpcsr *vmtp_allocrb()
{
	struct vmtpcsr *rb;
	struct vmtplpool *pool;
	struct mbuf *m;
	int i,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_allocrb(): called\n");
#endif
	s = splimp();

	if ((rb = vb_freerb) == NULL) {
		m = m_get(M_DONTWAIT, MT_PCB);	
		if (m == NULL) {
			splx(s);
			return(NULL);
		}
		MCLGET(m);
		if (m->m_len != CLBYTES) {
			m_free(m);
			splx(s);
			return(NULL);
		}
		m->m_len = sizeof(struct vmtplpool);
		pool = mtod(m, struct vmtplpool *);
		pool->vpl_used = 0;
		pool->vpl_type = VPL_RB;
		pool->vpl_mbuf = m;
		for (i = 0; i < VPL_MAXRBS; i++) {
			pool->vpl_rbs[i].vc_next = rb;
			rb = &(pool->vpl_rbs[i]);
		}
		vb_freerb = rb;
	}
	vb_freerb = rb->vc_next;
	csrtopool(rb)->vpl_used++;	/* incr used count for this pool/mbuf */
	splx(s);
	return rb;
} /* vmtp_allocrb */


/*
 * Deallocate a client state record.
 * Free the mbuf (and the cluster) if the used count becomes zero.
 */
vmtp_dealloccsr(csr)
	struct vmtpcsr *csr;
{
	struct vmtplpool *pool;
	struct vmtpcsr **a_csr;
	struct mbuf *m;
	int s,i;

#ifdef	VMTP_DEBUG
	printf("vmtp_dealloccsr(): csr = 0x%x\n", csr);
#endif
	s = splimp();

	pool = csrtopool(csr);
		/* decr used count for this pool/mbuf */
	csr->vc_next = vb_freecsr;
	vb_freecsr = csr;
	if (--pool->vpl_used == 0)  {
		/* remove all records in that mbuf from the free list */
		m = pool->vpl_mbuf;
		for(i = 0, a_csr = &(vb_freecsr); *a_csr != NULL; /* nop */)
			if (csrtopool(*a_csr) == pool){
				*a_csr = (*a_csr)->vc_next;
				i++;
			} else {
				a_csr = &(*a_csr)->vc_next;
			}
		if (i != VPL_MAXCSRS) {
#ifdef	VMTP_DEBUG
		printf("vmtp_dealloccsr(): i = %d, MAX = %d\n", i, VPL_MAXCSRS);
#endif
			panic("vmtp_dealloccsr");
		}
		m_free(m);
	}
	splx(s);
} /* vmtp_dealloccsr */

/*
 * Deallocate a response buffer.
 * Free the mbuf (and the cluster) if the used count becomes zero.
 */
vmtp_deallocrb(rb)
	struct vmtpcsr *rb;
{
	struct vmtplpool *pool;
	struct vmtpcsr **a_rb;
	struct mbuf *m;
	int s,i;

#ifdef	VMTP_DEBUG
	printf("vmtp_deallocrb(): rb = 0x%x\n", rb);
#endif
	s = splimp();

	pool = csrtopool(rb);
		/* decr used count for this pool/mbuf */
#ifdef	VMTP_DEBUG
	printf("vmtp_deallocrb(): pool = 0x%x\n", pool);
#endif
	rb->vc_next = vb_freerb;
	vb_freerb = rb;
	if (--pool->vpl_used == 0)  {
		/* remove all records in that mbuf from the free list */
		m = pool->vpl_mbuf;
		for(i = 0, a_rb = &(vb_freerb); *a_rb != NULL; /* nop */)
			if (csrtopool(*a_rb) == pool){
				*a_rb = (*a_rb)->vc_next;
				i++;
			} else {
				a_rb = &(*a_rb)->vc_next;
			}
		if (i != VPL_MAXRBS) {
#ifdef	VMTP_DEBUG
		printf("vmtp_deallocrb(): i = %d, MAX = %d\n", i, VPL_MAXRBS);
#endif
			panic("vmtp_deallocrb");
		}
		m_free(m);
	}
	splx(s);
} /* vmtp_deallocrb */


#endif	MACH_VMTP
