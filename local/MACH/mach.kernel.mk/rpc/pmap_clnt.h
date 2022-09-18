/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pmap_clnt.h,v $
 * Revision 2.3  89/02/25  19:14:09  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:00:28  jsb
 * 	Include file references.
 * 	[89/01/17  14:33:53  jsb]
 * 
 */
/* @(#)pmap_clnt.h	1.1 87/06/22 3.2/4.3NFSSRC */
/* @(#)pmap_clnt.h	1.2 86/10/28 NFSSRC */
/*	@(#)pmap_clnt.h 1.1 86/09/24 SMI	*/

/*
 * pmap_clnt.h
 * Supplies C routines to get to portmap services.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

/*
 * Usage:
 *	success = pmap_set(program, version, protocol, port);
 *	success = pmap_unset(program, version);
 *	port = pmap_getport(address, program, version, protocol);
 *	head = pmap_getmaps(address);
 *	clnt_stat = pmap_rmtcall(address, program, version, procedure,
 *		xdrargs, argsp, xdrres, resp, tout, port_ptr)
 *		(works for udp only.) 
 * 	clnt_stat = clnt_broadcast(program, version, procedure,
 *		xdrargs, argsp,	xdrres, resp, eachresult)
 *		(like pmap_rmtcall, except the call is broadcasted to all
 *		locally connected nets.  For each valid response received,
 *		the procedure eachresult is called.  Its form is:
 *	done = eachresult(resp, raddr)
 *		bool_t done;
 *		caddr_t resp;
 *		struct sockaddr_in raddr;
 *		where resp points to the results of the call and raddr is the
 *		address if the responder to the broadcast.
 */

extern bool_t		pmap_set();
extern bool_t		pmap_unset();
extern struct pmaplist	*pmap_getmaps();
enum clnt_stat		pmap_rmtcall();
enum clnt_stat		clnt_broadcast();
extern u_short		pmap_getport();
