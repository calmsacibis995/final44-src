h13588
s 00007/00004/00190
d D 8.3 95/02/14 10:54:20 cgd 38 37
c return types.  use NULL instead of (void *)0.
e
s 00015/00007/00179
d D 8.2 93/10/18 22:26:00 mckusick 37 36
c fixes an splnet() that attempts to lower ipl from splimp();
c get the right types for pf{fast,slow}timo (from Torek)
e
s 00002/00002/00184
d D 8.1 93/06/10 21:59:33 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00184
d D 7.16 93/04/27 15:19:28 mckusick 35 34
c sysctl.h needs vm/vm.h
e
s 00001/00001/00183
d D 7.15 93/04/17 22:03:43 mckusick 34 33
c too agressive on the mib counting
e
s 00002/00002/00182
d D 7.14 93/03/04 17:59:07 bostic 33 32
c change buffer lengths of sysctl(2) to be size_t's
e
s 00002/00001/00182
d D 7.13 93/03/02 18:23:59 mckusick 32 31
c add proc parameter to net_sysctl
e
s 00037/00000/00146
d D 7.12 93/02/04 01:12:53 mckusick 31 30
c add framework for net_sysctl
e
s 00000/00003/00146
d D 7.11 92/11/18 19:35:37 torek 30 29
c rm dregs of RMP (it was deprecated some time ago)
e
s 00007/00008/00142
d D 7.10 92/10/11 10:38:46 bostic 29 28
c make kernel includes standard
e
s 00005/00003/00145
d D 7.9 91/03/04 11:07:36 bostic 28 27
c replace /**/ with __CONCAT() macro
e
s 00003/00000/00145
d D 7.8 90/11/29 17:15:30 sklower 27 26
c add ccitt domain (x.25)
e
s 00001/00011/00144
d D 7.7 90/06/28 21:23:14 bostic 26 25
c new copyright notice
e
s 00003/00000/00152
d D 7.6 90/05/15 17:42:30 mckusick 25 24
c add RMP support for hp300
e
s 00001/00001/00151
d D 7.5 90/03/31 14:46:01 karels 24 23
c add third arg to ctlinput routines
e
s 00010/00001/00142
d D 7.4 89/04/08 17:48:48 karels 23 22
c add iso, route domains (sklower); compute packet size constants dynamically
e
s 00010/00005/00133
d D 7.3 88/06/29 17:20:23 bostic 22 21
c install approved copyright notice
e
s 00008/00002/00130
d D 7.2 87/12/30 12:06:38 bostic 21 20
c add Berkeley header
e
s 00001/00001/00131
d D 7.1 86/06/05 00:15:41 mckusick 20 19
c 4.3BSD release version
e
s 00001/00000/00131
d D 6.10 86/05/29 18:28:25 karels 19 18
c call null_init to zap those null function pointers
e
s 00001/00004/00130
d D 6.9 86/01/08 14:22:09 karels 18 17
c rm bbnnet, pup
e
s 00004/00004/00130
d D 6.8 85/09/16 20:51:18 karels 17 16
c INET || BBNNET; ctlinput now takes sockaddr as arg
e
s 00002/00001/00132
d D 6.7 85/09/04 09:38:36 karels 16 15
c need to check type in pffindproto
e
s 00007/00001/00126
d D 6.6 85/06/08 14:57:46 mckusick 15 14
c Add copyright
e
s 00009/00004/00118
d D 6.5 85/06/02 23:25:47 karels 14 13
c allow raw sockets of any protocol if a wildcard raw entry is found
e
s 00003/00000/00119
d D 6.4 85/04/27 12:09:06 sklower 13 12
c add ifdefs for NS protocol.
e
s 00006/00006/00113
d D 6.3 84/08/29 20:27:40 bloom 12 11
c Change to includes.  no more ../h
e
s 00004/00001/00115
d D 6.2 84/08/21 10:41:55 karels 11 10
c change datagram queuing to use m_act properly; type mbufs with rights;
c change protocol family number in protosw to pointer to domain (for sam)
e
s 00000/00000/00116
d D 6.1 83/07/29 06:46:14 sam 10 9
c 4.2 distribution
e
s 00001/00001/00115
d D 5.9 83/03/15 10:20:26 sam 9 8
c boundary condition
e
s 00001/00001/00115
d D 5.8 83/02/10 18:42:02 sam 8 7
c groups set members are shorts, not ints; hz no longer in systm.h
e
s 00002/00001/00114
d D 5.7 82/12/30 15:46:20 sam 7 6
c include imp stuff differently
e
s 00011/00012/00104
d D 5.6 82/11/13 22:51:13 sam 6 5
c merge of 4.1b and 4.1c
e
s 00109/00015/00007
d D 5.5 82/11/02 11:33:03 root 5 4
c domain searching routines, &c
e
s 00000/00001/00022
d D 5.4 82/10/10 15:34:40 root 4 3
c put headers for vax in separate directories
e
s 00001/00002/00022
d D 5.3 82/09/04 09:16:08 root 3 2
c s/cdomain/domain/
e
s 00005/00000/00019
d D 5.2 82/07/24 18:10:44 root 2 1
c merge with calder
e
s 00019/00000/00000
d D 5.1 82/07/15 20:22:10 root 1 0
c date and time created 82/07/15 20:22:10 by root
e
u
U
f i 
t
T
I 1
D 15
/*	%M%	%I%	%E%	*/
E 15
I 15
/*
D 20
 * Copyright (c) 1982 Regents of the University of California.
E 20
I 20
D 36
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 20
D 21
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 21
I 21
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
 *
D 26
 * Redistribution and use in source and binary forms are permitted
D 22
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 22
I 22
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 22
E 21
 *
 *	%W% (Berkeley) %G%
 */
E 15

I 28
D 29
#include <sys/cdefs.h>
E 28
D 12
#include "../h/param.h"
D 5
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/reg.h"
#include "../h/inode.h"
#include "../h/proc.h"
D 3
#include "../h/clock.h"
E 3
D 4
#include "../h/mtpr.h"
E 4
#include "../h/timeb.h"
#include "../h/times.h"
#include "../h/reboot.h"
#include "../h/fs.h"
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/mount.h"
E 5
I 5
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/domain.h"
I 6
D 8
#include <time.h>
E 8
I 8
#include "../h/time.h"
E 8
#include "../h/kernel.h"
E 12
I 12
#include "param.h"
#include "socket.h"
#include "protosw.h"
#include "domain.h"
I 23
#include "mbuf.h"
E 23
#include "time.h"
#include "kernel.h"
E 29
I 29
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/domain.h>
#include <sys/mbuf.h>
#include <sys/time.h>
#include <sys/kernel.h>
I 37
#include <sys/systm.h>
E 37
I 35
#include <sys/proc.h>
#include <vm/vm.h>
E 35
I 31
#include <sys/sysctl.h>
E 31
E 29
E 12
E 6
E 5

I 37
void	pffasttimo __P((void *));
void	pfslowtimo __P((void *));

E 37
I 2
D 3
cdomain()
E 3
I 3
D 5
domain()
E 5
I 5
#define	ADDDOMAIN(x)	{ \
D 28
	extern struct domain x/**/domain; \
	x/**/domain.dom_next = domains; \
	domains = &x/**/domain; \
E 28
I 28
	extern struct domain __CONCAT(x,domain); \
	__CONCAT(x,domain.dom_next) = domains; \
	domains = &__CONCAT(x,domain); \
E 28
}

I 38
void
E 38
domaininit()
E 5
E 3
{
I 6
	register struct domain *dp;
	register struct protosw *pr;
E 6

I 28
#undef unix
E 28
I 6
#ifndef lint
E 6
D 5
	/* return a descriptor for the domain */
E 5
I 5
	ADDDOMAIN(unix);
I 23
	ADDDOMAIN(route);
E 23
D 17
#ifdef INET
E 17
I 17
D 18
#if defined(INET) || defined(BBNNET)
E 18
I 18
#ifdef INET
E 18
E 17
	ADDDOMAIN(inet);
#endif
I 13
#ifdef NS
	ADDDOMAIN(ns);
D 18
#endif
E 13
#ifdef PUP
	ADDDOMAIN(pup);
E 18
#endif
I 23
#ifdef ISO
	ADDDOMAIN(iso);
#endif
I 25
D 30
#ifdef RMP
	ADDDOMAIN(rmp);
#endif
E 30
I 27
#ifdef CCITT
	ADDDOMAIN(ccitt);
#endif
E 27
E 25
E 23
D 7
#ifdef IMP
E 7
I 7
#include "imp.h"
#if NIMP > 0
E 7
	ADDDOMAIN(imp);
#endif
D 6
	pfinit();
}
E 6
I 6
#endif
E 6

D 6
/*
 * Operations applying to the sets of protocols
 * defined by the available communications domains.
 */
pfinit()
{
	register struct domain *dp;
	register struct protosw *pr;

E 6
D 11
	for (dp = domains; dp; dp = dp->dom_next)
E 11
I 11
	for (dp = domains; dp; dp = dp->dom_next) {
		if (dp->dom_init)
			(*dp->dom_init)();
E 11
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_init)
				(*pr->pr_init)();
I 11
	}
I 19
D 23
	null_init();
E 23
I 23

if (max_linkhdr < 16)		/* XXX */
max_linkhdr = 16;
	max_hdr = max_linkhdr + max_protohdr;
	max_datalen = MHLEN - max_hdr;
E 23
E 19
E 11
I 6
D 37
	pffasttimo();
	pfslowtimo();
E 37
I 37
D 38
	timeout(pffasttimo, (void *)0, 1);
	timeout(pfslowtimo, (void *)0, 1);
E 38
I 38
	timeout(pffasttimo, NULL, 1);
	timeout(pfslowtimo, NULL, 1);
E 38
E 37
E 6
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
D 9
		if (pr->pr_type == type)
E 9
I 9
		if (pr->pr_type && pr->pr_type == type)
E 9
			return (pr);
	return (0);
}

struct protosw *
D 14
pffindproto(family, protocol)
	int family, protocol;
E 14
I 14
pffindproto(family, protocol, type)
	int family, protocol, type;
E 14
{
	register struct domain *dp;
	register struct protosw *pr;
I 14
	struct protosw *maybe = 0;
E 14

	if (family == 0)
		return (0);
	for (dp = domains; dp; dp = dp->dom_next)
		if (dp->dom_family == family)
			goto found;
	return (0);
found:
D 6
	for (pr = dp->dom_protosw; pr <= dp->dom_protoswNPROTOSW; pr++)
E 6
I 6
D 14
	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
E 14
I 14
	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++) {
E 14
E 6
D 16
		if (pr->pr_protocol == protocol)
E 16
I 16
		if ((pr->pr_protocol == protocol) && (pr->pr_type == type))
E 16
			return (pr);
I 16

E 16
D 14
	return (0);
E 14
I 14
		if (type == SOCK_RAW && pr->pr_type == SOCK_RAW &&
		    pr->pr_protocol == 0 && maybe == (struct protosw *)0)
			maybe = pr;
	}
	return (maybe);
I 31
}

I 38
int
E 38
D 32
net_sysctl(name, namelen, oldp, oldlenp, newp, newlen)
E 32
I 32
net_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
E 32
	int *name;
	u_int namelen;
	void *oldp;
D 33
	u_int *oldlenp;
E 33
I 33
	size_t *oldlenp;
E 33
	void *newp;
D 33
	u_int newlen;
E 33
I 33
	size_t newlen;
E 33
I 32
	struct proc *p;
E 32
{
	register struct domain *dp;
	register struct protosw *pr;
	int family, protocol;

	/*
	 * All sysctl names at this level are nonterminal;
	 * next two components are protocol family and protocol number,
	 * then at least one addition component.
	 */
D 34
	if (namelen <= 3)
E 34
I 34
	if (namelen < 3)
E 34
		return (EISDIR);		/* overloaded */
	family = name[0];
	protocol = name[1];

	if (family == 0)
		return (0);
	for (dp = domains; dp; dp = dp->dom_next)
		if (dp->dom_family == family)
			goto found;
	return (ENOPROTOOPT);
found:
	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
		if (pr->pr_protocol == protocol && pr->pr_sysctl)
			return ((*pr->pr_sysctl)(name + 2, namelen - 2,
			    oldp, oldlenp, newp, newlen));
	return (ENOPROTOOPT);
E 31
E 14
}

I 38
void
E 38
D 17
pfctlinput(cmd, arg)
E 17
I 17
pfctlinput(cmd, sa)
E 17
	int cmd;
D 17
	caddr_t arg;
E 17
I 17
	struct sockaddr *sa;
E 17
{
	register struct domain *dp;
	register struct protosw *pr;

	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_ctlinput)
D 17
				(*pr->pr_ctlinput)(cmd, arg);
E 17
I 17
D 24
				(*pr->pr_ctlinput)(cmd, sa);
E 24
I 24
D 37
				(*pr->pr_ctlinput)(cmd, sa, (caddr_t) 0);
E 37
I 37
				(*pr->pr_ctlinput)(cmd, sa, (caddr_t)0);
E 37
E 24
E 17
}

D 37
pfslowtimo()
E 37
I 37
void
pfslowtimo(arg)
	void *arg;
E 37
{
	register struct domain *dp;
	register struct protosw *pr;

	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_slowtimo)
				(*pr->pr_slowtimo)();
I 6
D 37
	timeout(pfslowtimo, (caddr_t)0, hz/2);
E 37
I 37
D 38
	timeout(pfslowtimo, (void *)0, hz/2);
E 38
I 38
	timeout(pfslowtimo, NULL, hz/2);
E 38
E 37
E 6
}

D 37
pffasttimo()
E 37
I 37
void
pffasttimo(arg)
	void *arg;
E 37
{
	register struct domain *dp;
	register struct protosw *pr;

	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_fasttimo)
				(*pr->pr_fasttimo)();
I 6
D 37
	timeout(pffasttimo, (caddr_t)0, hz/5);
E 37
I 37
D 38
	timeout(pffasttimo, (void *)0, hz/5);
E 38
I 38
	timeout(pffasttimo, NULL, hz/5);
E 38
E 37
E 6
E 5
}
E 2
E 1
