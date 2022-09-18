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
 * $Log:	vmtp_group.c,v $
 * Revision 2.3  89/03/09  20:48:27  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:34  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_HOSTID: modified to not byte-swap IP addresses in eids.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $Header: vmtp_group.c,v 2.3 89/03/09 20:48:27 rpd Exp $
 */

/*
 * 	vmtp_group.c		2/16/87
 *	Written by Erik Nordmark
 */

/* 
 * TODO
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
#include "vmtp_send.h"
#include "vmtp_group.h"
#include "vmtp_buf.h"

/*
 * Map a group entity identifier to an internet address
 */

u_long
vmtp_groupeidtoinaddr(e)
	struct vmtpeid e;
{
#if	VMTP_HOSTID
	return (e.ve_inaddr);
#else	VMTP_HOSTID
	return ntohl(e.ve_inaddr);
#endif	VMTP_HOSTID
} /* vmtp_groupeidtoinaddr */

/* 
 * Add a new (local) member to an entity group. If the group has no member
 * it's created.
 */
vmtp_addgroupmember(e,group)
	struct vmtpeid e, group;
{
	struct vmtpgroup *g;
	register struct vmtpmember  *mem;
	int error, s;
	u_short flags = VMF_NONE;

#ifdef	VMTP_DEBUG
	printf("vmtp_addgroupmember(): called\n");
    	vmtp_dumpeid(&e, "e", "vmtp_addgroupmember()");
	vmtp_dumpeid(&group, "group", "vmtp_addgroupmember()");
#endif
	if ((g = vmtp_maptogroup(group)) == NULL) {
		if (error = vmtp_newgroup(group,VGF_DEALLEMPTY, &g)) 
			return error;
		flags |= VMF_MANAGER;
	}
	mem = vmtp_allocmember();
	if (!mem)
		return ENOBUFS;
	mem->vm_eid = e;
	mem->vm_flags = flags;

	s = splimp();
	mem->vm_next = g->vg_members;
	g->vg_members = mem;
	splx(s);

	return 0;
} /* vmtp_addgroupmember */

/* 
 * Remove a (local) member from an entity group. If the group as a result of 
 * this will have no members the group is remove from the list of local groups.
 */
vmtp_removegroupmember(e,group)
	struct vmtpeid e, group;
{
	register struct vmtpgroup *g;
	register struct vmtpmember *mem, *mem1;
	int error = 0;
	int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_removegroupmember(): called\n");
	vmtp_dumpeid(&e, "e", "vmtp_removegroupmember()");
	vmtp_dumpeid(&group, "group", "vmtp_removegroupmember()");
#endif
	s = splimp();
	g = vmtp_maptogroup(group);
	if (!g) {
		splx(s);
		return 0;
	}

	if ((mem = g->vg_members) && vmtp_sameeid(g->vg_members->vm_eid,e)) {
		g->vg_members = mem->vm_next;
		vmtp_deallocmember(mem);
		if (!g->vg_members && vgf_deallempty(g->vg_flags)) 
			error = vmtp_removegroup(g);
		splx(s);
		return error;
	}

	for (mem = g->vg_members; (mem1 = mem->vm_next) != NULL; mem = mem1)
		if (vmtp_sameeid(mem1->vm_eid, e)) {
			mem->vm_next = mem1->vm_next;
			vmtp_deallocmember(mem1);
			mem1 = mem->vm_next;
			break;
		}
	splx(s);
	return 0;
} /* vmtp_removegroupmember */

/*
 * Get the first member in the group (or any member in fact!)
 * Returns 0 (emptyeid) if group has no members
 */
struct vmtpeid vmtp_firstgroupmember(group)
	struct vmtpeid group;
{
	register struct vmtpgroup *g;
	register struct vmtpeid empty;

#ifdef	VMTP_DEBUG
	printf("vmtp_firstgroupmember(): called\n");
	vmtp_dumpeid(&group, "group", "vmtp_firstgroupmember()");
#endif
	g = vmtp_maptogroup(group);
	if (!g || !g->vg_members) {
		empty.ve_fltm = 0;
		empty.ve_inaddr = 0;
		return empty;
	}
	return g->vg_members->vm_eid;
} /* vmtp_firstgroupmember */

/*
 * Check if a given eid is member in a given group
 */
vmtp_isgroupmember(e,group)
	struct vmtpeid e;
	struct vmtpeid  group;
{
	register struct vmtpgroup *g;
	register struct vmtpmember *mem;

#ifdef	VMTP_DEBUG
	printf("vmtp_isgroupmember(): called\n");
	vmtp_dumpeid(&e, "e", "vmtp_isgroupmember()");
	vmtp_dumpeid(&group, "group", "vmtp_isgroupmember()");
#endif
	g = vmtp_maptogroup(group);
	if (!g)
		return 0;
	mem = g->vg_members;
	while (mem) {
		if (vmtp_sameeid(mem->vm_eid, e))
			return 1;
		mem = mem->vm_next;
	}
	return 0;
} /* vmtp_isgroupmember */

/*
 * Allocate and initialize a new group descriptor
 * Insert it in the group map
 * If there is no socket for the host group create one and join that host group.
 */
vmtp_newgroup(group, flags, a_g)
	struct vmtpeid group;
	u_short flags;
	struct vmtpgroup **a_g;
{
	struct mbuf *m;
	struct socket *so;
	int h,s;

#ifdef	VMTP_DEBUG
	printf("vmtp_newgroup(): called\n");
	vmtp_dumpeid(&group, "group", "vmtp_newgroup()");
#endif

	if ((so = vmtp_findhostgroupsocket(group)) == NULL) {
		int error;

		if (!IN_CLASSD(group.ve_inaddr)) {
#ifdef	VMTP_DEBUG
			printf("vmtp_newgroup(): BAD host group!!\n");
#endif
			return EADDRNOTAVAIL;
		}

#ifdef	VMTP_DEBUG
		printf("vmtp_newgroup(): creating a host group socket\n");
#endif
		error = vmtp_createhostgroupsocket(&so, group);
		switch (error) {
			case 0: break;
			case ENOBUFS: 
			case EPROTOTYPE:
			case EPROTONOSUPPORT: 
			  printf("VMTP: can't use multicating without IGMP\n");
				return error;
			
			default: 
				printf("VMTP: unknown reply code from IGMP\n");
				return error;
			
		}
#ifdef	VMTP_DEBUG
		printf("vmtp_newgroup(): created socket: 0x%x\n", so);
#endif
		error = vmtp_joinhostgroup(so, group.ve_inaddr); 
		switch (error) {
			case 0: break;
			case ENOBUFS: 
				vmtp_closehostgroupsocket(so, group);
				return error;
			default: 
				printf("VMTP: joining hostgroup failed!\n");
				vmtp_closehostgroupsocket(so, group);
				return error;
		}
	}

	*a_g = vmtp_allocgroup();
	if (!*a_g) {
		return ENOBUFS;
	}

	(*a_g)->vg_eid = group;
	(*a_g)->vg_members = NULL;
	(*a_g)->vg_flags = flags;

	s = splimp();
	h = vmtp_hash(&group);		/* insert into map */
	(*a_g)->vg_next = vg_groupmap[h];
	vg_groupmap[h] = *a_g;
	splx(s);
	return 0;
} /* vmtp_newgroup */

/*
 * Find a group descriptor with the given eid
 */
struct vmtpgroup *vmtp_maptogroup(group)
	struct vmtpeid	group;
{
	register struct vmtpgroup *curr;
	register int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_maptogroup(): called\n");
	vmtp_dumpeid(&group, "group", "vmtp_maptogroup()");
#endif
	s = splimp();
	curr = vg_groupmap[vmtp_hash(&group)];
	while (curr != NULL && !vmtp_sameeid(curr->vg_eid, group))
		curr = curr->vg_next;
	splx(s);
	return(curr);
} /* vmtp_maptogroup */


/*
 * Remove a group descriptor from the map and deallocate it.
 * If it is the last group close the group socket.
 */
vmtp_removegroup(g)
	register struct vmtpgroup *g;
{
	register struct vmtpgroup **gp;
	struct vmtpeid group;
	int error, s;
	int i;

#ifdef	VMTP_DEBUG
	printf("vmtp_removegroup(): g = 0x%x\n", g);
#endif
	if (g == NULL)
		return 0;

	s = splimp();
	for (gp = vg_groupmap + vmtp_hash(&g->vg_eid);
	     *gp != g && *gp != NULL; gp = &((*gp)->vg_next));
	if (*gp != g) {
		splx(s);
		return 0;
	}
	*gp = g->vg_next;
	splx(s);

	group = g->vg_eid;
	vmtp_deallocgroup(g);
	
	/*
	 * Check if last member in this host group
	 * If so leave the host group
	 */
	for (i = 0; i<VMTP_HASHMAPSIZE; i++)
		for (g = vg_groupmap[i]; g != NULL; g = g->vg_next) {
			if (g->vg_eid.ve_inaddr == group.ve_inaddr) {
				i = -1;
				break;
			}
		}
	if (i != -1) {
#ifdef	VMTP_DEBUG
		printf("vmtp_removegroup(): closing the socket\n");
#endif
			
		error = vmtp_closehostgroupsocket(NULL, group);
		switch (error) {
			case 0: 
				break;
			case ENOBUFS:
			default: 
		printf("VMTP: closing a host group socket failed: %d!\n",
			error);
				break;
		}
		return error;
	}

	return 0;
} /* vmtp_removegroup */

/*
 * Leave all the groups that this entity is a member of.
 * Used when cleaning up when the entity is removed.
 */
vmtp_leaveallgroups(e)
	struct vmtpeid e;
{
	struct vmtpgroup *g;
	int i, error;
	int s = splimp();

#ifdef	VMTP_DEBUG
	printf("vmtp_leaveallgroups(): called\n");
	vmtp_dumpeid(&e, "e", "vmtp_leaveallgroups()");
#endif

	for (i = 0; i < VMTP_HASHMAPSIZE; i++) 
		for (g = vg_groupmap[i]; g != NULL; g = g->vg_next) {
			error = vmtp_removegroupmember(e, g->vg_eid);
			if (error) {
				splx(s);
				return error;
			}
		}

	splx(s);
} /* vmtp_leaveallgroups */


/* 
 * Initialize the group management module
 */
vmtp_initgroup()
{
	int i;

#ifdef	VMTP_DEBUG
	printf("vmtp_initgroup(): called\n");
#endif
	for (i = 0; i<VMTP_HASHMAPSIZE; i++)
		vg_groupmap[i] = NULL;

	vg_hostgroups = NULL;

} /* vmtp_initgroup */


/*
 * Deliver a request to all the members of a group
 * A new csr is allocated per server in the group and inserted in the 
 * remote csr map.
 */
vmtp_delivertogroup(csr, group)
	register struct vmtpcsr *csr;
	struct vmtpeid group;
{
	register struct vmtpgroup *g;
	register struct vmtpmember *mem;
	register struct vmtpser *ser;
 	register struct mbuf *m1;
	register struct vmtpcsr *csr1;
	struct vmtpeid *server = NULL;
	struct vmtpiphdr *vi = NULL;	/* for request ack */
	int dropcsr;		/* original csr was NOT queued on a server */
	int s; 

#ifdef	VMTP_DEBUG
	printf("vmtp_delivertogroup(): csr = 0x%x\n", csr);
	vmtp_dumpeid(&group, "group", "vmtp_delivertogroup()");
#endif

	s = splimp();

	g = vmtp_maptogroup(group);

	dropcsr = 1;

	for (mem = g->vg_members; mem != NULL; mem = mem->vm_next) {
#ifdef	GROUP_DEBUG
		printf("vmtp_delivertogroup(): looping\n");
		vmtp_dumpeid(&mem->vm_eid, "member", "vmtp_delivertogroup");
#endif
		if (vmtp_sameeid(mem->vm_eid, csr->vc_client))
			continue;	/* to make simple loopback work */

		if ((ser = vmtp_maptoserver(mem->vm_eid)) == NULL)
			panic("vmtp_delivertogroup");
		if (vmtp_conditional(csr->vc_code) && !vmtp_waiting(ser))
			continue;

		if (mem->vm_next == NULL) {
#ifdef	GROUP_DEBUG
			printf("vmtp_delivertogroup(): LAST member\n");
#endif
			if (vi == NULL && 
			    vmtp_acknowledgepg(getvi_control(csr->vc_vihdr))) {
#ifdef	VMTP_DEBUG
			printf("vmtp_delivertogroup(): APG set - VMTP_OK\n");	
#endif
				m1 = vmtp_copyvihdr(csr->vc_vihdr);
				if (m1) {
					vi = mtod(m1, struct vmtpiphdr *);
					vi->vi_server = ser->vs_server;
				}
			}
			vmtp_queuerequest(csr, ser);
			wakeup(ser);
			server = &ser->vs_server;
			dropcsr = 0;
			break;
		}

#ifdef	GROUP_DEBUG
		printf("vmtp_delivertogroup(): copying csr\n");
#endif
		csr1 = vmtp_newcsr(csr->vc_client, vremotecsrmap);
		if (!csr1) 
			continue;
		
		if (csr->vc_dataseg) {
#ifdef	GROUP_DEBUG
			printf("vmtp_delivertogroup(): copying dataseg\n");
#endif
			m1 = m_copy(csr->vc_dataseg, 0 , M_COPYALL);
			if (!m1) {
				m_free(dtom(csr1->vc_vihdr));							vmtp_freecsr(csr1, vremotecsrmap);
				continue;
			}
		}
		bcopy((caddr_t)&csr->vc_state, (caddr_t)&csr1->vc_state,
			(caddr_t)&csr->vc_effprincipalid + 
			sizeof(struct princid) -
			(caddr_t)&csr->vc_state);
		*csr1->vc_vihdr = *csr->vc_vihdr;
		csr1->vc_dataseg = m1;
		if (vi == NULL && 
		    vmtp_acknowledgepg(getvi_control(csr->vc_vihdr))) {
#ifdef	VMTP_DEBUG
			printf("vmtp_delivertogroup(): APG set - VMTP_OK\n");	
#endif
			m1 = vmtp_copyvihdr(csr->vc_vihdr);
			if (m1) {
				vi = mtod(m1, struct vmtpiphdr *);
				vi->vi_server = ser->vs_server;
			}
		}

		vmtp_queuerequest(csr1, ser);
		wakeup(ser);
		server = &ser->vs_server;
	}

	if (dropcsr) {
		/*
		 * Can happen if last server(s) are not awating and CMD is set.
		 * Throw away the csr if at least one server got the request.
		 */
#ifdef	VMTP_DEBUG
		printf("vmtp_delivertogroup(): freeing csr??\n");	
#endif
		if (server) 
			vmtp_freecsr(csr, vremotecsrmap);
		else
			vmtp_starttimer(csr, vts_discardcsr(csr));
	}
	splx(s);

	if (vi != NULL)
		vmtp_sendrqa(NULL, vi, VMTP_OK);
		
} /* vmtp_delivertogroup */

