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
 * $Log:	pmap_prot.c,v $
 * Revision 2.4  89/03/09  20:58:42  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:14:21  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:01:06  jsb
 * 	Include file references.
 * 	[89/01/17  14:30:41  jsb]
 * 
 *
 *  3-Nov-87  Peter King (king) at NeXT, Inc.
 *	Changed struct pmap to struct portmap.
 *
 */ 

/* @(#)pmap_prot.c	1.2 87/09/18 3.2/4.3NFSSRC */
/* @(#)pmap_prot.c	1.2 86/10/28 NFSSRC */
#ifndef	lint
static char sccsid[] = "@(#)pmap_prot.c 1.1 86/09/24 Copyr 1984 Sun Micro";
#endif

/*
 * pmap_prot.c
 * Protocol for the local binder service, or pmap.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#ifdef	KERNEL
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/pmap_prot.h>
#else
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/pmap_prot.h>
#endif

bool_t
xdr_pmap(xdrs, regs)
	XDR *xdrs;
	struct portmap *regs;
{

	if (xdr_u_long(xdrs, &regs->pm_prog) && 
		xdr_u_long(xdrs, &regs->pm_vers) && 
		xdr_u_long(xdrs, &regs->pm_prot))
		return (xdr_u_long(xdrs, &regs->pm_port));
	return (FALSE);
}
