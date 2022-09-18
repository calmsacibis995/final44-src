/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	pmap_prot.h,v $
 * Revision 2.4  89/03/09  20:58:47  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:14:27  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:01:29  jsb
 * 	Include file references.
 * 	[89/01/17  14:27:09  jsb]
 * 
 *  3-Nov-87  Peter King (king) at NeXT, Inc.
 *	Changed struct pmap to struct portmap
 *
 */ 
/* @(#)pmap_prot.h	1.1 87/06/22 3.2/4.3NFSSRC */
/* @(#)pmap_prot.h	1.2 86/10/28 NFSSRC */
/*	@(#)pmap_prot.h 1.1 86/09/24 SMI	*/

/*
 * pmap_prot.h
 * Protocol for the local binder service, or pmap.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 *
 * The following procedures are supported by the protocol:
 *
 * PMAPPROC_NULL() returns ()
 * 	takes nothing, returns nothing
 *
 * PMAPPROC_SET(struct pmap) returns (bool_t)
 * 	TRUE is success, FALSE is failure.  Registers the tuple
 *	[prog, vers, prot, port].
 *
 * PMAPPROC_UNSET(struct pmap) returns (bool_t)
 *	TRUE is success, FALSE is failure.  Un-registers pair
 *	[prog, vers].  prot and port are ignored.
 *
 * PMAPPROC_GETPORT(struct pmap) returns (long unsigned).
 *	0 is failure.  Otherwise returns the port number where the pair
 *	[prog, vers] is registered.  It may lie!
 *
 * PMAPPROC_DUMP() RETURNS (struct pmaplist *)
 *
 * PMAPPROC_CALLIT(unsigned, unsigned, unsigned, string<>)
 * 	RETURNS (port, string<>);
 * usage: encapsulatedresults = PMAPPROC_CALLIT(prog, vers, proc, encapsulatedargs);
 * 	Calls the procedure on the local machine.  If it is not registered,
 *	this procedure is quite; ie it does not return error information!!!
 *	This procedure only is supported on rpc/udp and calls via
 *	rpc/udp.  This routine only passes null authentication parameters.
 *	This file has no interface to xdr routines for PMAPPROC_CALLIT.
 *
 * The service supports remote procedure calls on udp/ip or tcp/ip socket 111.
 */

#define PMAPPORT		((u_short)111)
#define PMAPPROG		((u_long)100000)
#define PMAPVERS		((u_long)2)
#define PMAPVERS_PROTO		((u_long)2)
#define PMAPVERS_ORIG		((u_long)1)
#define PMAPPROC_NULL		((u_long)0)
#define PMAPPROC_SET		((u_long)1)
#define PMAPPROC_UNSET		((u_long)2)
#define PMAPPROC_GETPORT	((u_long)3)
#define PMAPPROC_DUMP		((u_long)4)
#define PMAPPROC_CALLIT		((u_long)5)

#ifdef	KERNEL
struct portmap {
	long unsigned pm_prog;
	long unsigned pm_vers;
	long unsigned pm_prot;
	long unsigned pm_port;
};
#else	!KERNEL
struct pmap {
	long unsigned pm_prog;
	long unsigned pm_vers;
	long unsigned pm_prot;
	long unsigned pm_port;
};
#endif	!KERNEL

extern bool_t xdr_pmap();

struct pmaplist {
#ifdef	KERNEL
	struct portmap	pml_map;
#else	!KERNEL
	struct pmap	pml_map;
#endif	!KERNEL
	struct pmaplist *pml_next;
};

#ifndef	KERNEL
extern bool_t xdr_pmaplist();
#endif	/*!KERNEL*/
