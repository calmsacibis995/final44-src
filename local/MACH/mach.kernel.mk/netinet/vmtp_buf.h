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
 * $Log:	vmtp_buf.h,v $
 * Revision 2.3  89/03/09  20:47:56  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:03  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
/*
 * $ Header: vmtp_buf.h,v 2.1 87/08/14 15:43:04 mrt Exp $
 */

/*
 * 	vmtp_buf.h		2/19/87
 *	Written by Erik Nordmark
 */

/*
 * A simple buffer manager that uses mbufs for storing smaller records
 *
 * Currently used for server descriptors, group records, group member records,
 * and the synch queues for the responses.
 *
 * Larger records like csr's and response buffers are stored in mbuf clusters.
 */

#define VP_HEADSIZE	(sizeof(u_short)+sizeof(u_char))
#define VP_MAXGROUPS	(MLEN-VP_HEADSIZE) / sizeof(struct vmtpgroup)
#define VP_MAXMEMBERS	(MLEN-VP_HEADSIZE) / sizeof(struct vmtpmember)
#define VP_MAXSERS	(MLEN-VP_HEADSIZE) / sizeof(struct vmtpser)
#define VP_MAXSYNQS	(MLEN-VP_HEADSIZE) / sizeof(struct vmtpsynq)
#define VP_MAXHOSTGRS	(MLEN-VP_HEADSIZE) / sizeof(struct vmtphostgroup)

struct vmtppool {
	u_short		vp_used;	/* number of slots used */
	u_char		vp_type;
	union {
		struct vmtpgroup   vgroups[VP_MAXGROUPS];
		struct vmtpmember  vmembers[VP_MAXMEMBERS];
		struct vmtpser	   vsers[VP_MAXSERS];
		struct vmtpsynq	   vsynqs[VP_MAXSYNQS];
		struct vmtphostgroup vhostgrs[VP_MAXHOSTGRS];
	} vp_records;
#define vp_groups 	vp_records.vgroups
#define vp_members 	vp_records.vmembers
#define vp_sers 	vp_records.vsers
#define vp_synqs 	vp_records.vsynqs
#define vp_hostgrs	vp_records.vhostgrs
};

#define VPL_HEADSIZE	(sizeof(u_short)+sizeof(u_char)+sizeof(struct mbuf *))
#define VPL_MAXCSRS	(CLBYTES-VPL_HEADSIZE) / sizeof(struct vmtpcsr)
#define VPL_MAXRBS	(CLBYTES-VPL_HEADSIZE) / VMTP_RBSIZE

struct vmtplpool {
	u_short		vpl_used;	/* number of slots used */
	u_char		vpl_type;
	struct mbuf 	*vpl_mbuf;	/* back pointer to mbuf from cluster */
	union {
		struct vmtpcsr   vcsrs[VPL_MAXCSRS];
		struct vmtpcsr   vrbs[VPL_MAXRBS];
	} vpl_records;
#define vpl_csrs 	vpl_records.vcsrs
#define vpl_rbs 	vpl_records.vrbs
};

/*
 * Different types of pools
 */
#define VP_GROUP	1	/* pool contains vmtpgroup records */
#define VP_MEMBER	2	/* pool contains vmtpmember records */
#define VP_SER		3	/* pool contains vmtpser records */
#define VP_SYNQ		4	/* pool contains vmtpsynq records */
#define VP_HOSTGR	5	/* pool contains vmtphostgroup records */
#define VPL_CSR		6	/* large pool for client state records */
#define VPL_RB		7	/* large pool for response buffers */

#ifdef	KERNEL
struct vmtpgroup 	*vmtp_allocgroup();
struct vmtpmember 	*vmtp_allocmember();
struct vmtpser 		*vmtp_allocser();
struct vmtpsynq 	*vmtp_allocsynq();
struct vmtphostgroup	*vmtp_allochostgroup();
struct vmtpcsr		*vmtp_alloccsr();
struct vmtpcsr		*vmtp_allocrb();

struct vmtpgroup 	*vb_freegroup;	/* list of free group records */
struct vmtpmember  	*vb_freemember;	/* list of free member records */
struct vmtpser		*vb_freeser;	/* list of free ser's */
struct vmtpsynq		*vb_freesynq;	/* list of free synq's */
struct vmtphostgroup	*vb_freehostgr;	/* list of free hostgroup records */
struct vmtpcsr		*vb_freecsr;
struct vmtpcsr		*vb_freerb;
#endif	KERNEL
