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
 * $Log:	vmtp_manager.h,v $
 * Revision 2.3  89/03/09  20:50:14  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:05:21  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
/*
 * $ Header: vmtp_manager.h,v 2.1 87/08/14 15:44:26 mrt Exp $
 */

/*
 * 	vmtp_manager.h		5/15/87
 *	Written by Erik Nordmark
 *
 * Requests to be sent to the VMTP manager
 */

/*
 * Internal structure of the MCB used for most requests.
 * Overlayed on the UCB part of the MCB.
 */
struct vmtpmreq {
	unsigned long	vmr_code;
	struct vmtpeid	vmr_eid;	/* Corresponds to coresident field */
	struct vmtpeid	vmr_group;
	unsigned short	vmr_flags;
	unsigned short	vmr_res;	/* not used */
	int		vmr_arg;
	int 		vmr_segsize;
};


/*
 * Request codes
 */
#define VM_NEWENT	0x82000006	/* Create an entity id: not an entity */
#define VM_REMENT	0x82000007	/* Remove an entity/client */
#define VM_NEWSERVER	0x8200000E	/* Upgrade a client to a server */
#define VM_NEWSERVERKEY (VM_NEWSERVER | VU_SDA) /* when also seeting the key */
#define VM_REMSERVER	0x8200000F	/* Downgrade a server to a client */
#define VM_NEWGROUP	0x8200000A	/* Create a temporary entity group */
/* #define VM_REMGROUP	0x82000000 */	/* Remove a temporary group */
#define VM_JOINGROUP	0x8200000B	/* Join an existing group */
#define VM_LEAVEGROUP	0x8200000C	/* Leave a group */
#define VM_SIGNALENTITY	0x82000009	/* Signal the entity */


/* Query type operations */
#define VM_PROBE	0x82000001	/* Same as ProbeRequest, version 1 */
#define VM_FULLPROBE	0x82000002	/* Same as ProbeRequest, version 2/3 */
#define VM_PROBEBLOCK	0x82000003	
#define VM_QUERYENT	0x82000008 
#define VM_QUERYGROUP	0x8200000D
/* #define VM_QUERYSERVER	0x82000000 */


/* #define VM_SETKEY	0x82000000 */	/* Set the key for a (client,server) */
				 	/* principal pair */
/* #define VM_DELKEY	0x82000000 */	/* Revoke a key */
/* #define VM_GETKEY	0x82000000 */

/*
 * In VM_NEWSERVERKEY:
 *	arg contains the encryption qualifier.
 *	the segment is a union vmtpkey containing the key.
 */
