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
 * $Log:	group.h,v $
 * Revision 2.3  89/03/09  20:42:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:47  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * group.h
 */

#include "igmproto.h"

#if	IGMPROTO

#include "igmp_var.h"

struct GroupDescriptor {
    u_char		inuse;
    int			confirm_timer;
    struct igmpcb 	pcb;
};

#define GROUP_POOL_SIZE	128	/* total no. of descriptors  */


extern struct GroupDescriptor	GroupDescriptorPool[];

extern struct GroupDescriptor	*InstallGroupDescriptor();
extern struct GroupDescriptor	*AllocGroupDescriptor();

#endif	IGMPROTO
