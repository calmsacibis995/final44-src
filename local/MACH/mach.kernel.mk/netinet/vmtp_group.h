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
 * $Log:	vmtp_group.h,v $
 * Revision 2.3  89/03/09  20:48:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:40  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
/*
 * $ Header: vmtp_group.h,v 2.1 87/08/14 15:43:23 mrt Exp $
 */

/*
 * 	vmtp_group.h		2/16/87
 *	Written by Erik Nordmark
 */

struct vmtpgroup {
	struct vmtpgroup  *vg_next;
	struct vmtpeid 	  vg_eid;
	struct vmtpmember *vg_members;
	u_short 	  vg_flags;
};

/*
 * Flags for groups 
 */
#define VGF_NONE	0
#define VGF_OPEN	0x1	/* any entity can add itself */
#define VGF_MANAGER	0x2	/* all members are managers */
#define VGF_DEALLEMPTY	0x4	/* deallocate group when no members left */

#define vgf_open(f)	((f) & VGF_OPEN)
#define vgf_manager(f) 	((f) & VGF_MANAGER)
#define vgf_deallempty(f) ((f) & VGF_DEALLEMPTY)

struct vmtpmember {
	struct vmtpmember *vm_next;
	struct vmtpeid    vm_eid;
	u_short		  vm_flags;
};

/*
 * Flags for members 
 */
#define VMF_NONE	0
#define VMF_MANAGER	0x1	/* authorized to add new members et.c. */

#define vmf_manager(f)	((f) & VMF_MANAGER)

/*
 * Default values for IGMP calls
 */
#define VG_LOOPBACK	1	/* since vmtp_invoke has no loopback to local */
				/* members right now */
#define VG_PRIVATE	0	/* host groups are not created private */

/*
 * One of these per IGMP host group
 */
struct vmtphostgroup {
	struct vmtphostgroup 	*vh_next;	/* next in linked list */
	struct in_addr		vh_hostgroup;
	struct socket 		*vh_socket;

};

#ifdef	KERNEL
u_long vmtp_groupeidtoinaddr();
struct vmtpeid vmtp_firstgroupmember();
struct vmtpgroup *vmtp_maptogroup();
struct socket *vmtp_findhostgroupsocket();

struct vmtpgroup *vg_groupmap[VMTP_HASHMAPSIZE];
struct vmtphostgroup *vg_hostgroups;

#endif	KERNEL

