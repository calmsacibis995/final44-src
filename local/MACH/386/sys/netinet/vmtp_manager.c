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
 * $Log:	vmtp_manager.c,v $
 * Revision 2.3  89/03/09  20:50:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:05:14  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_HOSTID: modified to use vmtp_hostid.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
/*
 * $ Header: vmtp_manager.c,v 2.1 87/08/14 15:44:21 mrt Exp $
 */
 
#include <mach_vmtp.h>

/*
 * 	vmtp_manager.c		5/15/87
 *	Written by Erik Nordmark
 */

/*
 * TODO
 *	Fill out the gaps.
 *	Creating a joining groups: routines in vmtp_group.c has no support for
 *	access keys. Set eid of creator and check this + flag on self management
 *	when joining. What flags are set in the request when creating??
 *
 *	Init: the host can't join the hostgroup since invoking IGMP to do this
 *	will cause sleep to be called which can be a problem, and the init code
 *	runs at splimp so the response will not be received until all the init 
 *	code is finished which is too late. The code here works only when the
 *	manager is called with a singleton coresident entity!!
 *
 *	Not possible to allocate the eid of the manager in initmanager() since
 *	the global variables time and hostid haven't been set when the 
 *	protocols are initialized.
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
#include "vmtp_send.h"
#include "vmtp_cksum.h"
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "esp_cache.h"
#include "vmtp_manager.h"

struct vmtpeid vmtp_alloceid();
struct vmtpeid vmanagereid;		/* Used in responses */

/*
 * The VMTP manager module
 */
vmtp_manager(csr)
	register struct vmtpcsr *csr;
{
	register struct vmtpmreq *vm = (struct vmtpmreq *)&csr->vc_ucb;
	register struct mbuf **mp = NULL;
	register struct mbuf *seg = csr->vc_dataseg;

#ifdef	MANAGER_DEBUG
	printf("vmtp_manager(): csr = 0x%x\n", csr);
	printf("\tvmr_code = 0x%x, vmr_eid = %x:%x:%x\n", vm->vmr_code,
		getve_flags(vm->vmr_eid), getve_tmstamp(vm->vmr_eid),
		vm->vmr_eid.ve_inaddr);

	printf("\tvmr_group = %x:%x:%x, vmr_flags = 0x%x\n",
		getve_flags(vm->vmr_group), getve_tmstamp(vm->vmr_group),
		vm->vmr_group.ve_inaddr, vm->vmr_flags);
	printf("\vmr_arg = 0x%x, vmr_segsize = %d\n", 
		vm->vmr_arg, vm->vmr_segsize);
#endif

#if	VMTP_HOSTID
	if (vmanagereid.ve_inaddr != vmtp_hostid) {
#else	VMTP_HOSTID
	if (vmanagereid.ve_inaddr != ntohl(hostid)) {
#endif	VMTP_HOSTID
#ifdef	MANAGER_DEBUG
		printf("vmtp_manager - setting the manager's entity id\n");
#endif
		vmanagereid = vmtp_alloceid();
		printf("VMTP manager eid = %x:%x:%x\n", 
			getve_flags(vmanagereid),
			getve_tmstamp(vmanagereid), vmanagereid.ve_inaddr);
	}

	switch (vm->vmr_code) {
		case VM_NEWENT:		/* Generate an entity id */
			vm->vmr_eid =  vmtp_alloceid();
			vm->vmr_code = VMTP_OK;
			break;
		case VM_REMENT:
			vm->vmr_code = VMTP_OK;
			break;
		case VM_NEWSERVER:	/* setup as a server */
		case (VM_NEWSERVER | VU_SDA):
			vmtp_initserver(vm, seg, csr->vc_vihdr->vi_multicast);
			break;
		case VM_REMSERVER:
			vmtp_remserver(vm, csr->vc_vihdr->vi_multicast);
			break;
		case VM_NEWGROUP:
			vm->vmr_code = VMTP_OK;
			break;
		case VM_JOINGROUP:
			vmtp_joingroup(vm, csr->vc_vihdr->vi_multicast);
			break;
		case VM_LEAVEGROUP:
			vmtp_leavegroup(vm, csr->vc_vihdr->vi_multicast);
			break;
		case VM_SIGNALENTITY:
			vmtp_signalentity(vm, csr->vc_vihdr->vi_multicast);
			break;
		case VM_PROBE:
			break;
		case VM_FULLPROBE:
			break;
		case VM_PROBEBLOCK:
			vmtp_probeblock(vm, csr->vc_vihdr->vi_multicast);
			break;
		case VM_QUERYENT:
			break;
		case VM_QUERYGROUP:
			break;
	}

	if (seg != NULL) {
		m_freem(seg);
		csr->vc_dataseg = NULL;
	}

	/* Send a response */
	vm->vmr_code &= ~VU_DGM;		/* not idempotent */
	if (vmtp_respdiscarded(vm->vmr_code)) {
		if (mp)
			m_freem(*mp);
		goto noreply;
	}
	if (vmtp_segmentdata(vm->vmr_code) && mp != NULL) {
		csr->vc_txmsk = vmtp_segsizetomsk(vm->vmr_segsize);
		csr->vc_dataseg = *mp;
	} else
		csr->vc_txmsk = 0;
	csr->vc_flags |= VCF_MBUF;
	csr->vc_server = vmanagereid;

	csr->vc_rexmtcnt = 0;
	csr->vc_retrycnt = 0;

	csr->vc_vihdr->vi_addr = csr->vc_hostaddr;
	csr->vc_vihdr->vi_ifp = csr->vc_ifp;
	setvi_fnctcode(csr->vc_vihdr, VMTP_RESP);
	setvi_priority(csr->vc_vihdr, VPR_NORMAL);
	setvi_pgcount(csr->vc_vihdr, 0);
	setvi_control(csr->vc_vihdr, 0);
	vmtp_sendpg(csr, VMTP_RETRANSMIT, 1);		/* Inhibit local */

noreply:
	csr->vc_state = VC_RESPONDED;
	vmtp_starttimer(csr, vts_discardcsr(csr));

} /* vmtp_manager */

static long lasttmstamp;
/*
 * Pick a random entity id with approiate flags
 */
struct vmtpeid vmtp_alloceid()
{
	register struct vmtpeid eid;

#if	VMTP_HOSTID
	eid.ve_inaddr = vmtp_hostid;
#else	VMTP_HOSTID
	eid.ve_inaddr = htonl(hostid);
#ifdef	LITTLE_ENDIAN
	setve_flags(eid, VE_LEE);
#else	
	setve_flags(eid, 0);
#endif
#endif	VMTP_HOSTID

	if (lasttmstamp >= time.tv_sec) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_alloceid(): close allocation\n");
#endif
		++lasttmstamp;
	} else {
		lasttmstamp = time.tv_sec;
	}
	setve_tmstamp(eid, lasttmstamp);
	return eid;
} /* vmtp_alloceid */


/* 
 * Initialize the entity as a server
 */
vmtp_initserver(vm, seg, multicast)
	register struct vmtpmreq *vm;
	register struct mbuf *seg;	/* data segment */
	int multicast;
{
	register struct vmtpcsr *csr;
	register struct vmtpser *ser;
	register int s;

#ifdef	MANAGER_DEBUG
	printf("vmtp_initserver(): called\n");
#endif
	
	csr = vmtp_maptocsr(vm->vmr_eid, vlocalcsrmap);
	if (!csr) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_initserver(): no local csr\n");
#endif
		if (multicast)
			vm->vmr_code = VMTP_RESPDISC;
		else
			vm->vmr_code = VMTP_NONEXIST;
		return;
	}

	if (vmtp_maptoserver(vm->vmr_eid) != NULL) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_initserver(): address in use\n");
#endif
		vm->vmr_code = VMTP_OK;		/* Is already a server */
		return;
	}

#ifdef	MANAGER_DEBUG
	printf("vmtp_initserver(): allocating a ser\n");
#endif

	/* Create a server descriptor and initiate it */
	s = splimp();
	ser = vmtp_newserver(vm->vmr_eid);
	if (ser == NULL) {
		vm->vmr_code = VMTP_BUSY;
		return;
	}
	ser->vs_flags = vm->vmr_flags & 
		(VS_MESGPORT | VS_AUTHREQ | VS_SECUREREQ | VS_MASTERKEY);

	if (vmtp_masterkey(ser) && seg && seg->m_len == sizeof(union vmtpkey)) {
		ser->vs_mencryptqual = vm->vmr_arg;
		ser->vs_mkey = *mtod(seg, union vmtpkey *);
#ifdef	MANAGER_DEBUG
		printf("vmtp_initserver(): eq = %d, key = 0x%x\n",
			vm->vmr_arg, ser->vs_mkey.vk_xor);
#endif
	} else 
		ser->vs_flags &= ~VS_MASTERKEY;
	splx(s);
	vm->vmr_code = VMTP_OK;
} /* vmtp_initserver */

/* 
 * Deregister the entity as a server
 */
vmtp_remserver(vm, multicast)
	register struct vmtpmreq *vm;
	int multicast;
{
	register struct vmtpcsr *csr;
	register struct vmtpser *ser;

#ifdef	MANAGER_DEBUG
	printf("vmtp_remserver(): called\n");
#endif
	
	csr = vmtp_maptocsr(vm->vmr_eid, vlocalcsrmap);
	if (!csr) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_remserver(): no local csr\n");
#endif
		if (multicast)
			vm->vmr_code = VMTP_RESPDISC;
		else
			vm->vmr_code = VMTP_NONEXIST;
		return;
	}

	if ((ser = vmtp_maptoserver(vm->vmr_eid)) == NULL) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_remserver(): address in use\n");
#endif
		vm->vmr_code = VMTP_OK;	/* Wasn't a server */
		return;
	}

#ifdef	MANAGER_DEBUG
	printf("vmtp_remserver(): removing ser\n");
#endif

	vmtp_freeserver(ser);
	vm->vmr_code = VMTP_OK;
} /* vmtp_remserver */


/* 
 * Join an entity group
 */
vmtp_joingroup(vm, multicast)
	register struct vmtpmreq *vm;
	int multicast;
{
	register struct vmtpcsr *csr;
	register int error;

#ifdef	MANAGER_DEBUG
	printf("vmtp_joingroup(): called\n");
#endif
	
	csr = vmtp_maptocsr(vm->vmr_eid, vlocalcsrmap);
	if (!csr) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_joingroup(): no local csr\n");
#endif
		if (multicast)
			vm->vmr_code = VMTP_RESPDISC;
		else
			vm->vmr_code = VMTP_NONEXIST;
		return;
	}

	if (vmtp_isgroupmember(vm->vmr_eid, vm->vmr_group)) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_joingroup(): already member\n");
#endif
		vm->vmr_code = VMTP_OK;	
		return;
	}

#ifdef	MANAGER_DEBUG
	printf("vmtp_joingroup(): adding as a member\n");
#endif
	error = vmtp_addgroupmember(vm->vmr_eid, vm->vmr_group);
	switch (error) {
		case 0:
			vm->vmr_code = VMTP_OK;
			break;
		case ENOBUFS:
			vm->vmr_code = VMTP_BUSY;
			break;
		case EADDRNOTAVAIL:
			vm->vmr_code = VMTP_NOMULTICAST;
			break;
		case EPROTOTYPE:
		case EPROTONOSUPPORT:
			vm->vmr_code = VMTP_NOMULTICAST;
			break;
		case EACCES:
			vm->vmr_code = VMTP_NOPERMISSN;
			break;
		case ETIMEDOUT:
			vm->vmr_code = VMTP_REXMTTIMEO;
			break;
		default :
			vm->vmr_code = VMTP_NOMULTICAST;
			break;
	}

} /* vmtp_joingroup */


/* 
 * Leave a group
 */
vmtp_leavegroup(vm, multicast)
	register struct vmtpmreq *vm;
	int multicast;
{
	register struct vmtpcsr *csr;

#ifdef	MANAGER_DEBUG
	printf("vmtp_leavegroup(): called\n");
#endif
	
	csr = vmtp_maptocsr(vm->vmr_eid, vlocalcsrmap);
	if (!csr) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_leavegroup(): no local csr\n");
#endif
		if (multicast)
			vm->vmr_code = VMTP_RESPDISC;
		else
			vm->vmr_code = VMTP_NONEXIST;
		return;
	}

	if (!vmtp_isgroupmember(vm->vmr_eid, vm->vmr_group)) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_leavegroup(): isn't a member\n");
#endif
		vm->vmr_code = VMTP_OK;	
		return;
	}

#ifdef	MANAGER_DEBUG
	printf("vmtp_leavegroup(): leaving\n");
#endif
	vmtp_removegroupmember(vm->vmr_eid, vm->vmr_group);
	vm->vmr_code = VMTP_OK;
} /* vmtp_leavegroup */


/* 
 * Signal an entity. Very much like vmtp_signal() but more general.
 */
vmtp_signalentity(vm, multicast)
	register struct vmtpmreq *vm;
	int multicast;
{
	register struct vmtpcsr *csr;
	register struct proc *p;

#ifdef	MANAGER_DEBUG
	printf("vmtp_signalentity(): called\n");
#endif
	
	csr = vmtp_maptocsr(vm->vmr_eid, vlocalcsrmap);
	if (!csr) {
#ifdef	MANAGER_DEBUG
		printf("vmtp_signalentity(): no local csr\n");
#endif
		if (multicast)
			vm->vmr_code = VMTP_RESPDISC;
		else
			vm->vmr_code = VMTP_NONEXIST;
		return;
	}

	p = pfind(csr->vc_processid.pi_local);
	if (p == NULL)
		return;
#ifdef	ESP_DEBUG
	printf("vmtp_signalentity(): signaling p = 0x%x, signal = %d\n", 
		p, vm->vmr_arg);
#endif
	psignal(p, vm->vmr_arg);
	vm->vmr_code = VMTP_OK;
} /* vmtp_signalentity */

/*
 * Check if any entity id's exist in the range
 */
vmtp_probeblock(vm, multicast)
	register struct vmtpmreq *vm;
	register int multicast;
{
	register struct vmtpcsr *csr;

#ifdef	MANAGER_DEBUG
	printf("vmtp_probeblock(): called\n");
#endif

#if	VMTP_HOSTID
	if ((vmtp_eidtoinaddr(vm->vmr_eid) != vmtp_hostid)
#else	VMTP_HOSTID
	if ((vmtp_eidtoinaddr(vm->vmr_eid) != hostid)
#endif	VMTP_HOSTID
	    && (getve_tmstamp(vm->vmr_eid) + ESP_PROBEBLOCKSIZE < 0x0fffffff)) {
		if (!multicast) {
#ifdef	MANAGER_DEBUG
			printf("vmtp_probeblock(): BLOCK not used\n");
#endif
			vm->vmr_code = VMTP_NONEXIST;
		} else {
			vm->vmr_code = VMTP_RESPDISC;
		}
	} else {
#ifdef	MANAGER_DEBUG
		printf("vmtp_probeblock(): part of BLOCK could be used\n");
#endif
		vm->vmr_code = VMTP_BUSY;
	}

} /* vmtp_probeblock */


/*
 * Initialize
 */
vmtp_initmanager()
{
	struct vmtpser *ser;
	struct vmtpeid group;

	group.ve_fltm = VMTP_MANAGER_FLTM;
	group.ve_inaddr = VMTP_HOSTGROUP;
	ser = vmtp_newserver(group);
	ser->vs_flags = VS_MESGPORT;
	lasttmstamp = time.tv_sec;		/* init alloceid */
	vmanagereid.ve_inaddr = 0;
} /* vmtp_initmanager */
