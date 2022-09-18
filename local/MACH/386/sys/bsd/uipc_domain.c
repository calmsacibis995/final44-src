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
 * $Log:	uipc_domain.c,v $
 * Revision 2.4.3.2  91/03/30  09:39:15  rvb
 * 	Remove dependence on cpp name concatenation semantics.
 * 	[91/03/29            mbj]
 * 
 * Revision 2.4  89/03/09  19:33:57  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:30:23  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/02/09  04:35:46  mwyoung
 * Code cleanup cataclysm.
 * 
 * 06-May-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	DLI:  Add data-link interface protocol initialization to
 *	domaininit().
 *	[ V5.1(F10) ]
 *
 */ 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)uipc_domain.c	7.1 (Berkeley) 6/5/86
 */

#include <dli.h>

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/domain.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <kern/macro_help.h>

#define ADDDOMAIN(x)				\
MACRO_BEGIN					\
	extern struct domain x;			\
	x.dom_next = domains;			\
	domains = &x;				\
MACRO_END

struct	domain *domains;

domaininit()
{
	register struct domain *dp;
	register struct protosw *pr;

#ifndef	lint
	ADDDOMAIN(unixdomain);
#ifdef	INET
	ADDDOMAIN(inetdomain);
#endif
#ifdef	NS
	ADDDOMAIN(nsdomain);
#endif
#include <imp.h>
#if	NIMP > 0
	ADDDOMAIN(impdomain);
#endif
#if	DLI
	ADDDOMAIN(dlidomain);
#endif	DLI
#endif

	for (dp = domains; dp; dp = dp->dom_next) {
		if (dp->dom_init)
			(*dp->dom_init)();
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_init)
				(*pr->pr_init)();
	}
	null_init();
	pffasttimo();
	pfslowtimo();
}

struct protosw *
pffindtype(family, type)
	int family, type;
{
	register struct domain *dp;
	register struct protosw *pr;

	for (dp = domains; dp; dp = dp->dom_next)
		if (dp->dom_family == family)
			goto found;
	return (0);
found:
	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
		if (pr->pr_type && pr->pr_type == type)
			return (pr);
	return (0);
}

struct protosw *
pffindproto(family, protocol, type)
	int family, protocol, type;
{
	register struct domain *dp;
	register struct protosw *pr;
	struct protosw *maybe = 0;

	if (family == 0)
		return (0);
	for (dp = domains; dp; dp = dp->dom_next)
		if (dp->dom_family == family)
			goto found;
	return (0);
found:
	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++) {
		if ((pr->pr_protocol == protocol) && (pr->pr_type == type))
			return (pr);

		if (type == SOCK_RAW && pr->pr_type == SOCK_RAW &&
		    pr->pr_protocol == 0 && maybe == (struct protosw *)0)
			maybe = pr;
	}
	return (maybe);
}

pfctlinput(cmd, sa)
	int cmd;
	struct sockaddr *sa;
{
	register struct domain *dp;
	register struct protosw *pr;

	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_ctlinput)
				(*pr->pr_ctlinput)(cmd, sa);
}

pfslowtimo()
{
	register struct domain *dp;
	register struct protosw *pr;

	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_slowtimo)
				(*pr->pr_slowtimo)();
	timeout(pfslowtimo, (caddr_t)0, hz/2);
}

pffasttimo()
{
	register struct domain *dp;
	register struct protosw *pr;

	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_fasttimo)
				(*pr->pr_fasttimo)();
	timeout(pffasttimo, (caddr_t)0, hz/5);
}
