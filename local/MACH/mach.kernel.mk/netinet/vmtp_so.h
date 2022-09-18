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
 * $Log:	vmtp_so.h,v $
 * Revision 2.4  90/08/30  11:48:47  bohman
 * 	Ioctl changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.3  89/03/09  20:50:53  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:05:59  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 31-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_INVOKE: added support for split invoke call.
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
/*
 * $ Header: vmtp_so.h,v 2.1 87/08/14 15:44:50 mrt Exp $
 */
 
#define VMTP_INVOKE	1

/*
 * 	vmtp_so.h	0.1	11/4/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */


/*
 * VMTP Entity Identifier
 */
struct vmtpeid {
	u_long		ve_fltm;	/* flags and timestmap */
	u_long 		ve_inaddr;	/* internet host address (in host */
					/* byte order) */
};
#define getve_flags(ve) 	((ve).ve_fltm>>28)
#define getve_tmstamp(ve)	((ve).ve_fltm & 0x0fffffff)
#define setve_flags(ve, val) 	{ ve.ve_fltm &= 0x0fffffff; \
				  ve.ve_fltm |= (val)<<28; }
#define setve_tmstamp(ve, val)	{ ve.ve_fltm &= 0xf0000000; \
				  ve.ve_fltm |= (val) & 0x0fffffff; }

/*
 * VMTP entity id flags
 */
#define VE_RAE		0x8		/* remote alias entity */
#define VE_GRP		0x4		/* group entity id */
#define VE_LEE		0x2		/* little-endian entity */
#define VE_UGP		0x2		/* unrestricted grp only if EID_GRP */
#define VE_RES		0x1		/* reserved, should be 0 */

#define vmtp_remotealiasent(eid) ((eid).ve_fltm & (VE_RAE<<28))
#define vmtp_groupeid(eid) ((eid).ve_fltm & (VE_GRP<<28))
#define vmtp_littleendian(eid) ((eid).ve_fltm & (VE_LEE<<28))	
#define vmtp_unrestrictedgrp(eid) ((eid).ve_fltm & (VE_UGP<<28))

#define VMTP_HOSTGROUP 	0xe0000010	/* Class D address temporarely used */
					/* for all vmtp entity groups */
					/* 224.0.0.16 */

#define VMTP_MANAGER_FLTM	0x48000000
#define VMTP_MANAGER_GROUP	{VMTP_MANAGER_FLTM, VMTP_HOSTGROUP}

#define vmtp_tomanager(eid) 			\
	((eid).ve_fltm == VMTP_MANAGER_FLTM && 	\
	 (eid).ve_inaddr == VMTP_HOSTGROUP)


/*
 * VMTP User Control Block
 */
struct vmtpucb {
	u_long		vu_code;	/* see below */
	union {
	    u_long	vuu_longdata[7];	/* user data */
	    struct {
		struct vmtpeid	vuus_coresident;	/* coresident entity */
		u_long		vuus_shortdata[3];	/* user data */
		u_long		vuus_dlvrmsk;	/* user delivery mask */
		u_long		vuus_segsize;	/* data segment size */
	    } vuu_short;
	} vu_u;
};
#define vu_longdata 	vu_u.vuu_longdata
#define vu_coresident	vu_u.vuu_short.vuus_coresident
#define vu_shortdata	vu_u.vuu_short.vuus_shortdata
#define vu_dlvrmsk	vu_u.vuu_short.vuus_dlvrmsk
#define vu_segsize	vu_u.vuu_short.vuus_segsize

/*
 * VMTP user control codes
 */
#define VU_REQ		0x80000000	/* request mcb, else response */
#define VU_SDA		0x40000000	/* segment data followed */
#define VU_WRA		0x20000000	/* write access given */
#define VU_DGM		0x10000000	/* datagram message */
#define VU_CMD		0x08000000	/* conditional message delivery */
#define VU_UDM		0x04000000	/* user delivery mask set */
#define VU_CRE		0x02000000	/* coresident entity field used */
#define VU_MRE		0x01000000	/* multiple responses expected */

#define vmtp_request(code) ((code) & VU_REQ)
#define vmtp_segmentdata(code) ((code) & VU_SDA)
#define vmtp_writeaccess(code) ((code) & VU_WRA)
#define vmtp_datagram(code) ((code) & VU_DGM)
#define vmtp_conditional(code) ((code) & VU_CMD)
#define vmtp_usrdlvrmskset(code) ((code) & VU_UDM)
#define vmtp_coresident(code) ((code) & VU_CRE)
#define vmtp_multipleresp(code) ((code) & VU_MRE)

/*
 * VMTP Message Control Block 
 */
struct vmtpmcb {
	struct vmtpeid	vm_eid;		/* client id, if it's a response */
					/* server id, if it's a request */
#define vm_server	vm_eid
#define vm_client	vm_eid
	struct vmtpucb	vm_ucb;		/* user control block */
};
#define vm_code		vm_ucb.vu_code
#define vm_coresident	vm_ucb.vu_coresident
#define vm_shortdata	vm_ucb.vu_shortdata
#define vm_longdata	vm_ucb.vu_longdata
#define vm_dlvrmsk	vm_ucb.vu_dlvrmsk
#define vm_segsize	vm_ucb.vu_segsize


/*
 * Server descrptor flags that can be specified in initserver()
 */
#define VS_MESGPORT	0x0001	/* request to be handled by a server process */
#define VS_AUTHREQ	0x0002	/* authentication required */
#define VS_SECUREREQ	0x0004	/* security required */
#define VS_MASTERKEY	0x0008	/* masterkey in request/ser */

/*
 * Global process identifier
 */
struct procid {
	struct in_addr	pi_host;	/* host internet address */
	u_long		pi_local;	/* local process identifier */
};

/* 
 * Global principal identifier
 */
struct princid {	
	struct in_addr	pc_host;	/* host internet address */
	u_long		pc_local;	/* local user identifier */
};

/* 
 * Different keys
 */
union vmtpkey {
	u_long	vk_des[2];	/* for qualifier ENCRYPT_DESCBC */
	u_long	vk_xor;		/* for qualifier ENCRYPT_XOR */
};

#if	VMTP_INVOKE
/*
 * Flags for the func argument of invoke().
 */
#define INVOKE_REQ	0x1		/* request part of invoke call */
#define INVOKE_RESP	0x2		/* response part of invoke call */
#endif	VMTP_INVOKE

/*
 * ioctl()'s.
 * GETDEST provides the "GestDestinationServer" operation.
 * GETORPHAN is used by servers after they have been signalled that
 *	one of their requests where orphaned to find out the diseased
 *	parent of the orphan.
 * REQWAITING is used by servers to check if there are any requests on their
 *	request queue.
 */

#ifdef	__STDC__
#define SIOCVMTPGETDEST		_IOWR('v', 2, struct vmtpeid)
#define SIOCVMTPSETKEY		_IOWR('v', 3, struct vmtpauth)
#define SIOCVMTPDELKEY		_IOWR('v', 4, struct vmtpauth)
#define SIOCVMTPGETORPHAN	_IOR('v', 5, struct vmtpeid)
#define SIOCVMTPREQWAITING	_IOR('v', 6, int)
#else
#define SIOCVMTPGETDEST		_IOWR(v, 2, struct vmtpeid)
#define SIOCVMTPSETKEY		_IOWR(v, 3, struct vmtpauth)
#define SIOCVMTPDELKEY		_IOWR(v, 4, struct vmtpauth)
#define SIOCVMTPGETORPHAN	_IOR(v, 5, struct vmtpeid)
#define SIOCVMTPREQWAITING	_IOR(v, 6, int)
#endif

/*
 * Socket options
 * IP_TIMETOLIVE - set time to live on the vmtp/ip packets. If it's 1 and
 *	the option VMTP_ETHER is set vmtp tries to send the packets as
 *	raw vmtp ethernet packets.
 * VMTP_ENCRYTPION - argument length is a char. 1 means encrypted and 0 non-
 *	encrypted packets. Changing this effectively changes between 
 * 	IP_PROTOVMTP and IP_PROTOVMTPS in the socket call.
 */
#define VMTP_ENCRYPTION	3	/* Disjoint from the IP options */


/*
 * Structure used for getting authenticators into the key storage in the kernel
 */
struct vmtpauth {
	struct vmtpeid	va_server;	/* Server entity */
	struct princid	va_serverp;	/* Server principal */
	int		va_timelimit;	/* When to stop using it */
	int		va_encryptqual;	/* Encryption qualifier */
	union vmtpkey	va_key;		/* The key */
	int		va_authlen;	/* Length of the authenticator */
	char		*va_auth;	/* The authenticator */
};
