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
 * $Log:	agent_var.h,v $
 * Revision 2.4  90/08/30  11:48:11  bohman
 * 	Ioctl changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.3  89/03/09  20:40:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:55:46  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */

#include "multicast_agent.h"

#if	MULTICAST_AGENT

extern struct socket *agentsocket;

struct attachedcell {
    struct attachedcell *next;
    struct ifnet *ifp;
    u_long confirmtimer;
};

struct addrcell {
    struct addrcell *next;
    struct in_addr agentaddr;
    u_long confirmtimer;
};



/* VERY IMPORTANT!  In the struct GroupRecord, the *next and *prev    */
/* fields must come first, in that order, and the groupaddr, key1 and */
/* key2 fields must be contiguous, also in that order, because I do a */
/* single copyout to copy the contents of those fields together.      */

struct GroupRecord {
    struct GroupRecord *next;
    struct GroupRecord *prev;
    struct in_addr groupaddr;
    u_long key1;
    u_long key2;
    struct addrcell *memberlist;
    struct attachedcell *attachednetlist;
    u_char flags;
};


struct memberentry {
    struct in_addr groupaddr;
    u_long key1;
    u_long key2;
};


struct memberupdate {
    struct in_addr agent;
    int length;
    caddr_t bufferptr;
};

#define UPDATE_TTL		60

#define I_BELONG		0x01
#define PERMANENT_GROUP		0x02

#define NON_ZERO_KEY		0x80000000

#ifdef	KERNEL
struct GroupRecord grouprecordhead;
#endif	KERNEL

#define MULTICAST_AGENT_CONFIRM_RESET	240 /* number of 500ms units in 2 min */
#define MULTICAST_AGENT_UPDATE_RESET	240 /* number of 500ms units in 2 min */


struct groupargs {
    struct in_addr groupaddr;
    u_long key1;
    u_long key2;
    u_char returncode;		
    struct in_addr agentaddr;
    struct in_addr netaddr;
};   

#ifdef	__STDC__
#define SIOCADDGROUP		_IOWR('g', 40, struct groupargs)
#define SIOCDELGROUP		_IOWR('g', 41, struct groupargs)

#define SIOCINCRGROUP		_IOWR('g', 42, struct groupargs)
#define SIOCDECRGROUP		_IOWR('g', 43, struct groupargs)

#define SIOCADDAGENT		_IOWR('g', 44, struct groupargs)
#define SIOCDELAGENT		_IOWR('g', 45, struct groupargs)

#define SIOCCONFIRMGROUP	_IOWR('g', 46, struct groupargs)

#define SIOCAGENTINIT		_IO('g', 47)

#define SIOCMEMUPDATE		_IOWR('g', 48, struct memberupdate)
#define SIOCGETMEMBERSHIP	_IOWR('g', 49, struct memberupdate)

#define SIOCADDPERMGROUP	_IOWR('g', 50, struct groupargs)
#define SIOCSETGROUPRANGE	_IOWR('g', 51, struct groupargs)
#else
#define SIOCADDGROUP		_IOWR(g, 40, struct groupargs)
#define SIOCDELGROUP		_IOWR(g, 41, struct groupargs)

#define SIOCINCRGROUP		_IOWR(g, 42, struct groupargs)
#define SIOCDECRGROUP		_IOWR(g, 43, struct groupargs)

#define SIOCADDAGENT		_IOWR(g, 44, struct groupargs)
#define SIOCDELAGENT		_IOWR(g, 45, struct groupargs)

#define SIOCCONFIRMGROUP	_IOWR(g, 46, struct groupargs)

#define SIOCAGENTINIT		_IO(g, 47)

#define SIOCMEMUPDATE		_IOWR(g, 48, struct memberupdate)
#define SIOCGETMEMBERSHIP	_IOWR(g, 49, struct memberupdate)

#define SIOCADDPERMGROUP	_IOWR(g, 50, struct groupargs)
#define SIOCSETGROUPRANGE	_IOWR(g, 51, struct groupargs)
#endif

#endif	MULTICAST_AGENT
