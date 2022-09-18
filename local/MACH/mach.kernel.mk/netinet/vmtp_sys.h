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
 * $Log:	vmtp_sys.h,v $
 * Revision 2.4  89/07/11  13:37:51  jjc
 * 	Changed "#ifdef sun3" into "if defined(sun3) || defined(sun4)".
 * 	[89/05/06            jjc]
 * 
 * Revision 2.3  89/03/09  20:51:15  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:06:22  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
/*
 * $ Header: vmtp_sys.h,v 2.1 87/08/14 15:45:05 mrt Exp $
 */

/*
 * 	vmtp_sys.h	0.1	11/21/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

#ifndef	VMTP_SYSH
#define VMTP_SYSH

#if	defined(sun3) || defined(sun4)
#define SYS_invoke		176	/* from sys/init_sysent.c */
#define SYS_recvreq		177 
#define SYS_sendreply		178
#define SYS_forward		179
#define SYS_probeentity		180
#define SYS_getreply		181
#else	defined(sun3) || defined(sun4)
#define SYS_invoke		162	/* from sys/init_sysent.c */
#define SYS_recvreq		163 
#define SYS_sendreply		164
#define SYS_forward		165
#define SYS_probeentity		166
#define SYS_getreply		167
#endif	defined(sun3) || defined(sun4)

/*
 * Note: the return value (ll below) is the length of the segment actually 
 * received whereas the parameter l is the maximum length. ll<0 implies 
 * there was a Unix related error e.g. bad socket, socket not bound or
 * out of buffer space. VMTP reply codes can be found in the mcb. So if
 * an invocation times out the return value will not signal an error but
 * the reply code in the mcb will. This avoids creating a lot of new Unix 
 * error codes or doing a bad mapping from vmtp errors to the existing ones.\
 */


/*
 * Invoke a message transaction:
 * 	ll = invoke(s, func, m, d, l)
 *		int 		s;
 *		int		func;   request and/or response
 *		struct vmtpmcb 	*m;
 *		char		*d;	segment pointer
 *		int		l;	maximum segment size
 */
#define invoke(s, m, d, l)	syscall(SYS_invoke, s, m, d, l)

/* 
 * Receive next request:
 *	ll = recvreq(s, m, d, l)
 *		int 		s;
 *		struct vmtpmcb 	*m;
 *		char		*d;	segment pointer
 *		int		l;	maximum segment size
 */
#define recvreq(s, m, d, l) syscall(SYS_recvreq, s, m, d, l)

/*
 * Send a response:
 * 	sendreply(s, m, d)
 *		int 		s;
 *		struct vmtpmcb 	*m;
 *		char		*d;	segment pointer
 */
#define sendreply(s, m, d) syscall(SYS_sendreply, s, m, d)

/*
 * Forward a transaction
 *	forward(s, m, new, d)
 *		int		s;
 *		struct vmtpmcb	*m;
 *		struct vmtpeid	new;	the new server
 *		char		*d;	segment pointer
 */
#define forward(s, m, new, d) syscall(SYS_forward, s, m, new, d)

/*
 * Probe an entity
 *	probeentity(s, d)
 *		int		s;
 *		struct espprobedata *d;
 */
#define probeentity(s, d) syscall(SYS_probeentity, s, d)

/*
 * Get next reply (if any)
 *	ll = getreply(s, m, d, l, t)
 *		int 		s;
 *		struct vmtpmcb 	*m;
 *		char		*d;	segment pointer
 *		int		l;	maximum segment size
 *		int		t: 	timeout in millisecs
 */
#define getreply(s, m, d, l, t) syscall(SYS_getreply, s, m, d, l, t)


/*
 * Get the destination server for the current transaction with
 * client 'eid'.
 *	getdestserver(s, eidp)
 *		int 		s;
 *		struct vmtpeid 	*eidp;
 */
#define getdestserver(s, eidp) ioctl(s, SIOCVMTPGETDEST, eidp)

/*
 * Get the entity that has on orphaned request. Should be checked after the
 * signal SIGURG has been received (for servers that care about orphans).
 *	getorphan(s, eidp)
 *		int 		s;
 *		struct vmtpeid 	*eidp;
 */
#define getorphan(s, eidp) ioctl(s, SIOCVMTPGETORPHAN, eidp)

/*
 * Check if there are requests queued for the server.
 *	requestsqueued(s, resultp)
 *		int		s;
 *		int		*resultp;
 */
#define requestsqueued(s, resultp) ioctl(s, SIOCVMTPREQWAITING, resultp)

#endif	VMTP_SYSH

