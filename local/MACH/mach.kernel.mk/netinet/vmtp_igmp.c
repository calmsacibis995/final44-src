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
 * $Log:	vmtp_igmp.c,v $
 * Revision 2.3  89/03/09  20:49:23  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:04:29  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_igmp.c,v 2.1 87/08/14 15:43:57 mrt Exp $
 */

/*
 * 	vmtp_igmp.c		2/16/87
 *	Written by Erik Nordmark
 */

/* 
 * The interface towards IGMP and internet host groups.
 * Note that IGMP no longer requires the name of the interface in the requests.
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
#include "igmp.h"
#include "igmp_user.h"

/*
 * Find a host group socket in the list
 */
struct socket *
vmtp_findhostgroupsocket(group)
	struct vmtpeid group;
{
	struct vmtphostgroup *vh = vg_hostgroups;
	struct in_addr hostgroup;
	int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_findhostgroupsocket(): called\n");
	vmtp_dumpeid(&group, "group", "vmtp_findhostgroupsocket()");
#endif

	s = splimp();
	hostgroup.s_addr = vmtp_groupeidtoinaddr(group);
	while (vh) {
		if (vh->vh_hostgroup.s_addr == hostgroup.s_addr) {
			splx(s);
			return vh->vh_socket;
		}
		vh = vh->vh_next;
	}
	splx(s);
	return NULL;
} /* vmtp_findhostgroupsocket */

/*
 * Create a socket for a host group
 */
vmtp_createhostgroupsocket(a_groupsocket, group)
	struct socket **a_groupsocket;
	struct vmtpeid group;
{
	int error, s;
	struct vmtphostgroup *vh;

#ifdef	VMTP_DEBUG
	printf("vmtp_createhostgroupsocket(): called\n");
	vmtp_dumpeid(&group, "group", "vmtp_createhostgroupsocket()");
#endif
	
	error = socreate(AF_INET, a_groupsocket, SOCK_DGRAM, IPPROTO_IGMP);
	if (error) 
		return error;
	vh = vmtp_allochostgroup();
	if (!vh) {
		soclose(*a_groupsocket);
		return ENOBUFS;
		}
	vh->vh_socket = *a_groupsocket;
	vh->vh_hostgroup.s_addr = vmtp_groupeidtoinaddr(group);
	s = splimp();
	vh->vh_next = vg_hostgroups;
	vg_hostgroups = vh;
	splx(s);

	return 0;
} /* vmtp_createhostgroupsocket */

/* 
 * Leave the group that has been joined on an IGMP socket and
 * close the socket
 */
vmtp_closehostgroupsocket(groupsocket, group)
	struct socket *groupsocket;
	struct vmtpeid group;
{
	struct vmtphostgroup **a_vh, *vh;
	struct in_addr hostgroup;
	int s;

#ifdef	VMTP_DEBUG
	printf("vmtp_closehostgroupsocket(): groupsocket = 0x%x\n",groupsocket);
	vmtp_dumpeid(&group, "group", "vmtp_closehostgroupsocket()");
#endif

	s = splimp();
	hostgroup.s_addr = vmtp_groupeidtoinaddr(group);
	for (a_vh = &vg_hostgroups; *a_vh != NULL; a_vh = &(*a_vh)->vh_next) {
		if ((*a_vh)->vh_hostgroup.s_addr == hostgroup.s_addr)
			break;
	}
	if (!*a_vh) {
		splx(s);
		return 0;
	}
	vh = *a_vh;
	if (groupsocket) {
		if (vh->vh_socket != groupsocket)
			panic("vmtp_closehostgroupsocket");
	} else
		groupsocket = vh->vh_socket;

	*a_vh = (*a_vh)->vh_next;
	splx(s);

	vmtp_deallochostgroup(vh);
#ifdef	VMTP_DEBUG
	printf("vmtp_closehostgroupsocket(): closing groupsocket = 0x%x\n",
		groupsocket);
#endif
	return soclose(groupsocket);
} /* vmtp_closehostgroupsocket */

/*
 * Create a host group using IGMP
 */
vmtp_createhostgroup(groupsocket, a_hostgroup)
	struct socket *groupsocket;
	struct in_addr *a_hostgroup;
{
	struct igmpreqargs req;
	int dummy;

#ifdef	VMTP_DEBUG
	printf("vmtp_createhostgroup(): socket = 0x%x\n", groupsocket);
#endif
	if (!groupsocket)
		panic("vmtp_createhostgroup");
	
	req.type = IGMP_CREATE_GROUP_REQUEST;
	req.code = VG_PRIVATE;
	req.loopback = VG_LOOPBACK;
	req.key1 = 0;
	req.key2 = 0;
#ifdef	VMTP_DEBUG
	printf("vmtp_createhostgroup(): groupaddr = 0x%x, ifr_name = %s\n",
		req.groupaddr.s_addr, req.ifr_name);
#endif
	(*groupsocket->so_proto->pr_usrreq)(groupsocket,PRU_CONTROL, 
		(struct mbuf *)0, (struct mbuf *)&req,( struct mbuf *)0);
	switch (req.code) {
		case IGMP_REQUEST_GRANTED: 
			(*a_hostgroup).s_addr = req.groupaddr.s_addr;
			return 0;
		case IGMP_NO_RESOURCES:	return ENOBUFS;
		case IGMP_INVALID_ACCESS_KEY: {
		printf("vmtp_createhostgroup: IGMP requires access key\n"); 
			return EACCES; 
		}
		case IGMP_INVALID_GROUP_ADDRESS: {
		printf("vmtp_createhostgroup: invalid group address\n"); 
			return EINVAL; 
		}
		case IGMP_NO_RESPONSE: {
		printf("vmtp_createhostgroup: IGMP agent not responding\n"); 
			return ETIMEDOUT; 
		}
		default: {
		printf("vmtp_createhostgroup: bad reply code from IGMP: %d\n",
				req.code); 
			return ENOBUFS; 
		}
	}
} /* vmtp_createhostgroup */

/*
 * Join a host group using IGMP
 */
vmtp_joinhostgroup(groupsocket, hostgroup)
	struct socket *groupsocket;
	struct in_addr hostgroup;
{
	struct igmpreqargs req;
	int dummy;

#ifdef	VMTP_DEBUG
	printf("vmtp_joinhostgroup(): socket = 0x%x, hostgroup = 0x%x\n",
		groupsocket, hostgroup.s_addr);
#endif
	if (!groupsocket)
		panic("vmtp_joinhostgroup");

	req.type = IGMP_JOIN_GROUP_REQUEST;
	req.code = 0;
	req.loopback = VG_LOOPBACK;
	req.groupaddr.s_addr = hostgroup.s_addr;
	req.key1 = 0;
	req.key2 = 0;
#ifdef	VMTP_DEBUG
	printf("vmtp_joinhostgroup(): groupaddr = 0x%x, ifr_name = %s\n",
		req.groupaddr.s_addr, req.ifr_name);
#endif
	(*groupsocket->so_proto->pr_usrreq)(groupsocket,PRU_CONTROL, 
		(struct mbuf *)0, (struct mbuf *)&req,( struct mbuf *)0);
	switch (req.code) {
		case IGMP_REQUEST_GRANTED: return 0;
		case IGMP_NO_RESOURCES:	return ENOBUFS;
		case IGMP_INVALID_ACCESS_KEY: {
		printf("vmtp_joinhostgroup: IGMP requires access key\n"); 
			return EACCES; 
		}
		case IGMP_INVALID_GROUP_ADDRESS: {
			printf("vmtp_joinhostgroup: invalid group address\n"); 
			return EINVAL; 
		}
		case IGMP_NO_RESPONSE: {
		printf("vmtp_joinhostgroup: IGMP agent not responding\n"); 
			return ETIMEDOUT; 
		}
		default: {
		printf("vmtp_joinhostgroup: bad reply code from IGMP: %d\n",
				req.code); 
			return ENOBUFS; 
		}
	}
} /* vmtp_joinhostgroup */

/*
 * Leave a host group using IGMP
 */
vmtp_leavehostgroup(groupsocket, hostgroup)
	struct socket *groupsocket;
	struct in_addr hostgroup;
{
	struct igmpreqargs req;
	int dummy;

#ifdef	VMTP_DEBUG
	printf("vmtp_leavehostgroup(): socket = 0x%x, hostgroup = 0x%x\n",
		groupsocket, hostgroup.s_addr);
#endif
	if (!groupsocket)
		panic("vmtp_leavehostgroup");

	req.type = IGMP_LEAVE_GROUP_REQUEST;
	req.code = 0;
	req.loopback = 0;
	req.groupaddr.s_addr = hostgroup.s_addr;
	req.key1 = 0;
	req.key2 = 0;
#ifdef	VMTP_DEBUG
	printf("vmtp_leavehostgroup(): groupaddr = 0x%x, ifr_name = %s\n",
		req.groupaddr.s_addr, req.ifr_name);
#endif
	(*groupsocket->so_proto->pr_usrreq)(groupsocket,PRU_CONTROL, 
		(struct mbuf *)0, (struct mbuf *)&req,( struct mbuf *)0);
	switch (req.code) {
		case IGMP_REQUEST_GRANTED: return 0;
		case IGMP_NO_RESOURCES:	return ENOBUFS;
		case IGMP_INVALID_ACCESS_KEY: {
		printf("vmtp_leavehostgroup: IGMP requires access key\n"); 
			return EACCES; 
		}
		case IGMP_INVALID_GROUP_ADDRESS: {
			printf("vmtp_leavehostgroup: invalid group address\n"); 
			return EINVAL; 
		}
		case IGMP_NO_RESPONSE: {
		printf("vmtp_leavehostgroup: IGMP agent not responding\n"); 
			return ETIMEDOUT; 
		}
		default: {
		printf("vmtp_leavehostgroup: bad reply code from IGMP: %d\n",
				req.code); 
			return ENOBUFS; 
		}
	}
} /* vmtp_leavehostgroup */

#endif	MACH_VMTP

