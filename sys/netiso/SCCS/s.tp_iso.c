h47487
s 00001/00000/00667
d D 8.2 94/09/22 19:11:04 sklower 18 17
c minor fixes from cgd@alpha.bostic.com
e
s 00002/00002/00665
d D 8.1 93/06/10 23:20:31 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00666
d D 7.16 93/05/25 11:51:55 bostic 16 15
c trailing comment after #else or #endif
e
s 00013/00004/00654
d D 7.15 92/11/25 20:07:29 sklower 15 14
c changes sufficient for tuba & idrp; may want to rethink this
e
s 00020/00020/00638
d D 7.14 92/10/11 12:22:02 bostic 14 13
c make kernel includes standard
e
s 00024/00086/00634
d D 7.13 91/10/02 19:43:37 sklower 13 12
c move common mtu estimation to tp_route_to; here determine
c only where the rtentry pointer is found in the npcb, and provide net hdr size
e
s 00004/00004/00716
d D 7.12 91/07/18 20:33:24 sklower 12 11
c this changes reflect getting rid of so_tpcb.
e
s 00009/00005/00711
d D 7.11 91/05/06 19:24:25 bostic 11 10
c new copyright; att/bsd/shared
e
s 00008/00008/00708
d D 7.10 91/04/26 15:01:20 sklower 10 9
c calculate mtu for tp_pcb based on route
e
s 00001/00001/00715
d D 7.9 91/03/12 16:00:35 sklower 9 8
c fix from mostek@cray
e
s 00045/00000/00671
d D 7.8 90/06/28 19:39:39 sklower 8 7
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00000/00001/00671
d D 7.7 90/04/05 11:21:55 sklower 7 6
c cltp_usrreq.c made separate file in conf/files
e
s 00003/00003/00669
d D 7.6 90/01/16 23:23:50 sklower 6 5
c merged with mitre decbit changes; mark version sent to NIST.
e
s 00039/00040/00633
d D 7.5 90/01/16 23:19:02 sklower 5 4
c checkpoint cltp changes before merging in mitre decbit changes
e
s 00012/00007/00661
d D 7.4 89/09/26 23:48:20 sklower 4 3
c avoid redundantly and incorrectly looking up route to get mtu.
e
s 00011/00036/00657
d D 7.3 89/08/29 13:45:08 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00174/00115/00519
d D 7.2 89/04/22 11:55:06 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00634/00000/00000
d D 7.1 88/12/14 15:30:03 sklower 1 0
c date and time created 88/12/14 15:30:03 by sklower
e
u
U
t
T
I 11
/*-
D 17
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 11
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
/* 
 * ARGO TP
D 2
 * $Header: tp_iso.c,v 5.3 88/11/18 17:27:57 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_iso.c,v $
E 2
I 2
 * $Header: /var/src/sys/netiso/RCS/tp_iso.c,v 5.1 89/02/09 16:20:51 hagens Exp $
 * $Source: /var/src/sys/netiso/RCS/tp_iso.c,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
I 4
D 11
 *	%W% (Berkeley) %G%
E 11
E 4
E 3
E 2
 *
 * Here is where you find the iso-dependent code.  We've tried
 * keep all net-level and (primarily) address-family-dependent stuff
 * out of the tp source, and everthing here is reached indirectly
 * through a switch table (struct nl_protosw *) tpcb->tp_nlproto 
 * (see tp_pcb.c). 
 * The routines here are:
 * 		iso_getsufx: gets transport suffix out of an isopcb structure.
 * 		iso_putsufx: put transport suffix into an isopcb structure.
 *		iso_putnetaddr: put a whole net addr into an isopcb.
 *		iso_getnetaddr: get a whole net addr from an isopcb.
I 8
 *		iso_cmpnetaddr: compare a whole net addr from an isopcb.
E 8
 *		iso_recycle_suffix: clear suffix for reuse in isopcb
 * 		tpclnp_ctlinput: handle ER CNLPdu : icmp-like stuff
 * 		tpclnp_mtu: figure out what size tpdu to use
 *		tpclnp_input: take a pkt from clnp, strip off its clnp header, 
 *				give to tp
 *		tpclnp_output_dg: package a pkt for clnp given 2 addresses & some data
 *		tpclnp_output: package a pkt for clnp given an isopcb & some data
 */
D 11

#ifndef lint
D 2
static char *rcsid = "$Header: tp_iso.c,v 5.3 88/11/18 17:27:57 nhall Exp $";
E 2
I 2
static char *rcsid = "$Header: /var/src/sys/netiso/RCS/tp_iso.c,v 5.1 89/02/09 16:20:51 hagens Exp $";
E 2
#endif lint
E 11

#ifdef ISO

D 2
#include "../h/types.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/domain.h"
#include "../h/mbuf.h"
#include "../h/errno.h"
#include "../h/time.h"
E 2
I 2
D 14
#include "param.h"
#include "socket.h"
#include "socketvar.h"
#include "domain.h"
#include "malloc.h"
#include "mbuf.h"
#include "errno.h"
#include "time.h"
#include "protosw.h"
E 14
I 14
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/protosw.h>
I 18
#include <sys/kernel.h>
E 18
E 14

E 2
D 14
#include "../net/if.h"
#include "../net/route.h"
E 14
I 14
#include <net/if.h>
#include <net/route.h>
E 14
D 2
#include "../h/protosw.h"
E 2

D 2
#include "../netiso/tp_param.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/tp_clnp.h"
E 2
I 2
D 14
#include "argo_debug.h"
#include "tp_param.h"
#include "tp_stat.h"
#include "tp_pcb.h"
#include "tp_trace.h"
#include "tp_stat.h"
#include "tp_tpdu.h"
#include "tp_clnp.h"
I 5
#include "cltp_var.h"
E 14
I 14
#include <netiso/argo_debug.h>
#include <netiso/tp_param.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_tpdu.h>
#include <netiso/tp_clnp.h>
#include <netiso/cltp_var.h>
E 14
E 5
E 2

/*
 * CALLED FROM:
 * 	pr_usrreq() on PRU_BIND, PRU_CONNECT, PRU_ACCEPT, and PRU_PEERADDR
D 2
 * FUNCTION, ARGUMENTS, and RETURN VALUE:
 * 	Return a transport suffix from an isopcb structure (inp).
 *  (CAST TO AN INT)
E 2
I 2
 * FUNCTION, ARGUMENTS:
E 2
 * 	The argument (which) takes the value TP_LOCAL or TP_FOREIGN.
 */

D 2
short
iso_getsufx(isop,  which)
E 2
I 2
iso_getsufx(isop, lenp, data_out, which)
E 2
	struct isopcb *isop;
I 2
	u_short *lenp;
	caddr_t data_out;
E 2
	int which;
{
I 2
	register struct sockaddr_iso *addr = 0;

E 2
	switch (which) {
	case TP_LOCAL:
D 2
		return  htons(isop->isop_laddr.siso_tsuffix);
E 2
I 2
		addr = isop->isop_laddr;
		break;
E 2

	case TP_FOREIGN:
D 2
		return  htons(isop->isop_faddr.siso_tsuffix);
E 2
I 2
		addr = isop->isop_faddr;
E 2
	}
I 2
	if (addr)
D 3
		bcopy(TSEL(addr), data_out, (*lenp = addr->siso_tsuffixlen));
E 3
I 3
		bcopy(TSEL(addr), data_out, (*lenp = addr->siso_tlen));
E 3
E 2
}

/* CALLED FROM:
 * 	tp_newsocket(); i.e., when a connection is being established by an
 * 	incoming CR_TPDU.
 *
 * FUNCTION, ARGUMENTS:
 * 	Put a transport suffix (found in name) into an isopcb structure (isop).
 * 	The argument (which) takes the value TP_LOCAL or TP_FOREIGN.
 */
void
D 2
iso_putsufx(isop, name, which)
E 2
I 2
iso_putsufx(isop, sufxloc, sufxlen, which)
E 2
	struct isopcb *isop;
D 2
	struct sockaddr_iso *name;
	int which;
E 2
I 2
	caddr_t sufxloc;
	int sufxlen, which;
E 2
{
I 2
	struct sockaddr_iso **dst, *backup;
	register struct sockaddr_iso *addr;
	struct mbuf *m;
	int len;

E 2
	switch (which) {
I 2
	default:
		return;

E 2
	case TP_LOCAL:
D 2
		isop->isop_lport = ntohs(name->siso_tsuffix);
E 2
I 2
		dst = &isop->isop_laddr;
		backup = &isop->isop_sladdr;
E 2
		break;
I 2

E 2
	case TP_FOREIGN:
D 2
		isop->isop_fport = ntohs(name->siso_tsuffix);
		break;
E 2
I 2
		dst = &isop->isop_faddr;
		backup = &isop->isop_sfaddr;
E 2
	}
I 2
	if ((addr = *dst) == 0) {
		addr = *dst = backup;
		addr->siso_nlen = 0;
D 3
		addr->siso_ssuffixlen = 0;
E 3
I 3
		addr->siso_slen = 0;
		addr->siso_plen = 0;
E 3
		printf("iso_putsufx on un-initialized isopcb\n");
	}
	len = sufxlen + addr->siso_nlen +
D 3
			(sizeof(struct sockaddr_iso) - sizeof(struct iso_addr));
E 3
I 3
			(sizeof(*addr) - sizeof(addr->siso_data));
E 3
	if (addr == backup) {
D 3
		if (len > sizeof(isop->isop_sladdr)) {
E 3
I 3
		if (len > sizeof(*addr)) {
E 3
				m = m_getclr(M_DONTWAIT, MT_SONAME);
				if (m == 0)
					return;
				addr = *dst = mtod(m, struct sockaddr_iso *);
				*addr = *backup;
				m->m_len = len;
		}
D 3
	} else
		dtom(addr)->m_len = len;
E 3
I 3
	}
E 3
	bcopy(sufxloc, TSEL(addr), sufxlen);
D 3
	addr->siso_tsuffixlen = sufxlen;
E 3
I 3
	addr->siso_tlen = sufxlen;
E 3
	addr->siso_len = len;
E 2
}

/*
 * CALLED FROM:
 * 	tp.trans whenever we go into REFWAIT state.
 * FUNCTION and ARGUMENT:
 *	 Called when a ref is frozen, to allow the suffix to be reused. 
 * 	(isop) is the net level pcb.  This really shouldn't have to be
 * 	done in a NET level pcb but... for the internet world that just
 * 	the way it is done in BSD...
 * 	The alternative is to have the port unusable until the reference
 * 	timer goes off.
 */
void
iso_recycle_tsuffix(isop)
	struct isopcb	*isop;
{
D 2
	isop->isop_laddr.siso_tsuffix = isop->isop_faddr.siso_tsuffix = 0;
E 2
I 2
D 3
	isop->isop_laddr->siso_tsuffixlen = isop->isop_faddr->siso_tsuffixlen = 0;
E 3
I 3
	isop->isop_laddr->siso_tlen = isop->isop_faddr->siso_tlen = 0;
E 3
E 2
}

/*
 * CALLED FROM:
 * 	tp_newsocket(); i.e., when a connection is being established by an
 * 	incoming CR_TPDU.
 *
 * FUNCTION and ARGUMENTS:
 * 	Copy a whole net addr from a struct sockaddr (name).
 * 	into an isopcb (isop).
 * 	The argument (which) takes values TP_LOCAL or TP_FOREIGN
 */ 
void
iso_putnetaddr(isop, name, which)
	register struct isopcb	*isop;
	struct sockaddr_iso	*name;
	int which;
{
I 2
	struct sockaddr_iso **sisop, *backup;
	register struct sockaddr_iso *siso;

E 2
	switch (which) {
I 8
	default:
		printf("iso_putnetaddr: should panic\n");
		return;
E 8
	case TP_LOCAL:
D 2
		isop->isop_laddr.siso_family = AF_ISO;
		bcopy((caddr_t)&name->siso_addr,
			(caddr_t)&isop->isop_laddr.siso_addr, sizeof(struct iso_addr));
		IFDEBUG(D_TPISO)
			printf("PUT TP_LOCAL addr\n");
			dump_isoaddr(&isop->isop_laddr);
		ENDDEBUG
E 2
I 2
		sisop = &isop->isop_laddr;
		backup = &isop->isop_sladdr;
E 2
		break;
	case TP_FOREIGN:
D 2
		isop->isop_faddr.siso_family = AF_ISO;
		if( name != (struct sockaddr_iso *)0 ) {
			bcopy((caddr_t)&name->siso_addr, 
				(caddr_t)&isop->isop_faddr.siso_addr, sizeof(struct iso_addr));
		}
		IFDEBUG(D_TPISO)
			printf("PUT TP_FOREIGN addr\n");
			dump_isoaddr(&isop->isop_faddr);
		ENDDEBUG
E 2
I 2
		sisop = &isop->isop_faddr;
		backup = &isop->isop_sfaddr;
E 2
	}
I 2
	siso = ((*sisop == 0) ? (*sisop = backup) : *sisop);
	IFDEBUG(D_TPISO)
		printf("ISO_PUTNETADDR\n");
		dump_isoaddr(isop->isop_faddr);
	ENDDEBUG
	siso->siso_addr = name->siso_addr;
I 8
}

/*
 * CALLED FROM:
 * 	tp_input() when a connection is being established by an
 * 	incoming CR_TPDU, and considered for interception.
 *
 * FUNCTION and ARGUMENTS:
 * 	compare a whole net addr from a struct sockaddr (name),
 * 	with that implicitly stored in an isopcb (isop).
 * 	The argument (which) takes values TP_LOCAL or TP_FOREIGN.
 */ 
iso_cmpnetaddr(isop, name, which)
	register struct isopcb	*isop;
	register struct sockaddr_iso	*name;
	int which;
{
	struct sockaddr_iso **sisop, *backup;
	register struct sockaddr_iso *siso;

	switch (which) {
	default:
		printf("iso_cmpnetaddr: should panic\n");
		return 0;
	case TP_LOCAL:
		sisop = &isop->isop_laddr;
		backup = &isop->isop_sladdr;
		break;
	case TP_FOREIGN:
		sisop = &isop->isop_faddr;
		backup = &isop->isop_sfaddr;
	}
	siso = ((*sisop == 0) ? (*sisop = backup) : *sisop);
	IFDEBUG(D_TPISO)
		printf("ISO_CMPNETADDR\n");
		dump_isoaddr(siso);
	ENDDEBUG
	if (name->siso_tlen && bcmp(TSEL(name), TSEL(siso), name->siso_tlen))
		return (0);
	return (bcmp((caddr_t)name->siso_data,
			 (caddr_t)siso->siso_data, name->siso_nlen) == 0);
E 8
E 2
}

/*
 * CALLED FROM:
 *  pr_usrreq() PRU_SOCKADDR, PRU_ACCEPT, PRU_PEERADDR
 * FUNCTION and ARGUMENTS:
 * 	Copy a whole net addr from an isopcb (isop) into
 * 	a struct sockaddr (name).
 * 	The argument (which) takes values TP_LOCAL or TP_FOREIGN.
 */ 

void
iso_getnetaddr( isop, name, which)
	struct isopcb *isop;
D 2
	struct sockaddr_iso *name;
E 2
I 2
	struct mbuf *name;
E 2
	int which;
{
D 2
	switch (which) {
	case TP_LOCAL:
		bcopy( (caddr_t)&isop->isop_laddr.siso_addr, 
			(caddr_t)&name->siso_addr, sizeof(struct iso_addr));
		break;

	case TP_FOREIGN:
		bcopy( (caddr_t)&isop->isop_faddr.siso_addr, 
			(caddr_t)&name->siso_addr, sizeof(struct iso_addr));
		break;
	}
E 2
I 2
	struct sockaddr_iso *siso =
		(which == TP_LOCAL ? isop->isop_laddr : isop->isop_faddr);
	if (siso)
		bcopy((caddr_t)siso, mtod(name, caddr_t),
				(unsigned)(name->m_len = siso->siso_len));
	else
		name->m_len = 0;
E 2
}
D 13

E 13
/*
I 13
 * NAME: 	tpclnp_mtu()
 *
E 13
 * CALLED FROM:
D 13
 *  tp_input() on incoming CR, CC, and pr_usrreq() for PRU_CONNECT
 * FUNCTION, ARGUMENTS, SIDE EFFECTS and RETURN VALUE:
 * Determine the proper maximum transmission unit, i.e., MTU, to use, given
 * a) the header size for the network protocol and the max transmission
 *	  unit on the subnet interface, determined from the information in (isop),
 * b) the max size negotiated so far (negot)
 * c) the window size used by the tp connection (found in so),
E 13
I 13
 *  tp_route_to() on incoming CR, CC, and pr_usrreq() for PRU_CONNECT
E 13
 *
D 13
 * The result is put in the integer *size in its integer form and in
 * *negot in its logarithmic form.  
E 13
I 13
 * FUNCTION, ARGUMENTS, and RETURN VALUE:
 *
 * Perform subnetwork dependent part of determining MTU information.
 * It appears that setting a double pointer to the rtentry associated with
 * the destination, and returning the header size for the network protocol
 * suffices.
E 13
 * 
D 13
 * The rules are:
 * a) can only negotiate down from the value found in *negot.
 * b) the MTU must be < the windowsize,
 * c) If src and dest are on the same net,
 * 	  we will negotiate the closest size larger than  MTU but really USE 
 *    the actual device mtu - ll hdr sizes.
 *   otherwise we negotiate the closest size smaller than MTU - ll hdr sizes.
E 13
I 13
 * SIDE EFFECTS:
 * Sets tp_routep pointer in pcb.
 *
 * NOTES:
E 13
 */
D 13

void
tpclnp_mtu(so, isop, size, negot )
	struct socket *so;
	struct isopcb *isop;
	int *size;
	u_char *negot;
E 13
I 13
tpclnp_mtu(tpcb)
register struct tp_pcb *tpcb;
E 13
{
D 4
	struct ifnet *ifp;
I 2
	struct iso_ifaddr *ia;
E 4
I 4
D 13
	struct ifnet *ifp = 0;
	struct iso_ifaddr *ia = 0;
E 4
E 2
	register int i;
	int windowsize = so->so_rcv.sb_hiwat;
D 10
	int clnp_size;
E 10
I 10
	int clnp_size, mtu;
E 10
	int sizeismtu = 0;
I 4
	register struct rtentry *rt = isop->isop_route.ro_rt;
E 13
I 13
	struct isopcb			*isop = (struct isopcb *)tpcb->tp_npcb;
E 13
E 4

D 2
	struct ifnet	*iso_routeifp();
E 2
I 2
D 4
	struct iso_ifaddr	*iso_routeifa();
E 2

E 4
	IFDEBUG(D_CONN)
D 13
		printf("tpclnp_mtu(0x%x,0x%x,0x%x,0x%x)\n", so, isop, size, negot);
E 13
I 13
		printf("tpclnp_mtu(tpcb)\n", tpcb);
E 13
	ENDDEBUG
D 13
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "ENTER GET MTU: size negot \n",*size, *negot, 0, 0);
	ENDTRACE
E 13
I 13
	tpcb->tp_routep = &(isop->isop_route.ro_rt);
	if (tpcb->tp_netservice == ISO_CONS)
		return 0;
	else
		return (sizeof(struct clnp_fixed) + sizeof(struct clnp_segment) +
			2 * sizeof(struct iso_addr));
E 13

D 13
	*size = 1 << *negot;

	if( *size > windowsize ) {
		*size = windowsize;
	}

D 2
	if ((ifp = iso_routeifp(&isop->isop_faddr)) == (struct ifnet *)0)
E 2
I 2
D 4
	if  (((ia = iso_routeifa(isop->isop_faddr)) == 0)
	      || (ifp = ia->ia_ifp) == 0)
E 4
I 4
	if (rt == 0 || (rt->rt_flags & RTF_UP == 0) ||
		(ia = (struct iso_ifaddr *)rt->rt_ifa) == 0 ||
	    (ifp = ia->ia_ifp) == 0) {
		IFDEBUG(D_CONN)
			printf("tpclnp_mtu routing abort rt=0x%x ia=0x%x ifp=0x%x\n",
					rt, ia, ifp)
		ENDDEBUG
E 4
E 2
		return;
I 4
	}
E 4

I 10


E 10
	/* TODO - make this indirect off the socket structure to the
	 * network layer to get headersize
	 */
D 2
	clnp_size = clnp_hdrsize(isop->isop_laddr.siso_addr.isoa_len);
E 2
I 2
D 10
	if (isop->isop_laddr)
		clnp_size = clnp_hdrsize(isop->isop_laddr->siso_addr.isoa_len);
	else
		clnp_size = 20;
E 2

	if(*size > ifp->if_mtu - clnp_size) {
		*size = ifp->if_mtu - clnp_size;
E 10
I 10
	clnp_size = sizeof(struct clnp_fixed) + sizeof(struct clnp_segment) +
			2 * sizeof(struct iso_addr);
	mtu = SN_MTU(ifp, rt) - clnp_size;
	if(*size > mtu) {
		*size = mtu;
E 10
		sizeismtu = 1;
	}
D 2
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "GET MTU MID: tpcb size negot i \n",
		*size, *negot, i, 0);
	ENDTRACE

E 2
	/* have to transform size to the log2 of size */
D 9
	for(i=TP_MIN_TPDUSIZE; (i<TP_MAX_TPDUSIZE && ((1<<i) <= *size)) ; i++)
E 9
I 9
	for(i=TP_MIN_TPDUSIZE; (i<=TP_MAX_TPDUSIZE && ((1<<i) <= *size)) ; i++)
E 9
		;
	i--;

I 2
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "GET MTU MID: tpcb size negot i \n",
		*size, *negot, i, 0);
	ENDTRACE

E 2
D 5
	/* are we on the same LAN? if so, negotiate one tpdu size larger,
	 * and actually send the real mtu size
	 */
D 2
	/* PHASE2: replace with iso_on_localnet(&isop->isop_faddr);
	 * or something along those lines
	 */
	if ( iso_netmatch(&isop->isop_laddr, &isop->isop_faddr) && sizeismtu ) {
E 2
I 2
	if (iso_localifa(isop->isop_faddr)) {
E 2
		i++;
	} else {
		*size = 1<<i;
	}
E 5
I 5
	*size = 1<<i;
E 5
	*negot = i;

	IFDEBUG(D_CONN)
		printf("GET MTU RETURNS: ifp %s size 0x%x negot 0x%x\n",
		ifp->if_name,	*size, *negot);
	ENDDEBUG
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "EXIT GET MTU: tpcb size negot \n",
		*size, *negot, 0, 0);
	ENDTRACE
E 13
}

D 13

E 13
/*
 * CALLED FROM:
 *  tp_emit()
 * FUNCTION and ARGUMENTS:
 *  Take a packet(m0) from tp and package it so that clnp will accept it.
 *  This means prepending space for the clnp header and filling in a few
 *  of the fields.
D 13
 *  inp is the isopcb structure; datalen is the length of the data in the
E 13
I 13
 *  isop is the isopcb structure; datalen is the length of the data in the
E 13
 *  mbuf string m0.
 * RETURN VALUE:
 *  whatever (E*) is returned form the net layer output routine.
 */

int
tpclnp_output(isop, m0, datalen, nochksum)
	struct isopcb		*isop;
	struct mbuf 		*m0;
	int 				datalen;
	int					nochksum;
{
I 2
	register struct mbuf *m = m0;
E 2
	IncStat(ts_tpdu_sent);

	IFDEBUG(D_TPISO)
		struct tpdu *hdr = mtod(m0, struct tpdu *);

		printf(
"abt to call clnp_output: datalen 0x%x, hdr.li 0x%x, hdr.dutype 0x%x nocsum x%x dst addr:\n",
			datalen,
			(int)hdr->tpdu_li, (int)hdr->tpdu_type, nochksum);
D 2
		dump_isoaddr(&isop->isop_faddr);
E 2
I 2
		dump_isoaddr(isop->isop_faddr);
E 2
		printf("\nsrc addr:\n");
D 2
		dump_isoaddr(&isop->isop_laddr);
E 2
I 2
		dump_isoaddr(isop->isop_laddr);
E 2
		dump_mbuf(m0, "at tpclnp_output");
	ENDDEBUG
I 2
D 3
	if ((m->m_flags & M_PKTHDR) == 0) {
		IFDEBUG(D_TPISO)
		printf("tpclnp_output: non headered mbuf");
		ENDDEBUG
		MGETHDR(m, M_DONTWAIT, MT_DATA);
		if (m == 0) {
			m_freem(m0);
			return ENOBUFS;
		}
		m->m_next = m0;
		m->m_len = 0;
		m->m_pkthdr.len = datalen;
		m0 = m;
	}
E 3
E 2

	return 
D 2
		clnp_output(m0, isop, datalen, nochksum?CLNP_NO_CKSUM:0 /* flags */);
E 2
I 2
D 3
		clnp_output(m0, isop, /* flags */nochksum ? CLNP_NO_CKSUM : 0);
E 3
I 3
		clnp_output(m0, isop, datalen,  /* flags */nochksum ? CLNP_NO_CKSUM : 0);
E 3
E 2
}

/*
 * CALLED FROM:
 *  tp_error_emit()
 * FUNCTION and ARGUMENTS:
 *  This is a copy of tpclnp_output that takes the addresses
 *  instead of a pcb.  It's used by the tp_error_emit, when we
 *  don't have an iso_pcb with which to call the normal output rtn.
 * RETURN VALUE:
 *  ENOBUFS or
 *  whatever (E*) is returned form the net layer output routine.
 */

int
tpclnp_output_dg(laddr, faddr, m0, datalen, ro, nochksum)
	struct iso_addr		*laddr, *faddr;
	struct mbuf 		*m0;
	int 				datalen;
	struct route 		*ro;
	int					nochksum;
{
	struct isopcb		tmppcb;
D 2
	struct iso_addr		*isoa;
E 2
	int					err;
	int					flags;
I 2
	register struct mbuf *m = m0;
E 2

	IFDEBUG(D_TPISO)
		printf("tpclnp_output_dg  datalen 0x%x m0 0x%x\n", datalen, m0);
	ENDDEBUG

	/*
	 *	Fill in minimal portion of isopcb so that clnp can send the
	 *	packet.
	 */
	bzero((caddr_t)&tmppcb, sizeof(tmppcb));
D 2
	isoa = &(tmppcb.isop_laddr.siso_addr);
	bcopy((caddr_t)laddr, (caddr_t)isoa, sizeof (struct iso_addr));
	isoa = &(tmppcb.isop_faddr.siso_addr);
	bcopy((caddr_t)faddr, (caddr_t)isoa, sizeof (struct iso_addr));
E 2
I 2
	tmppcb.isop_laddr = &tmppcb.isop_sladdr;
	tmppcb.isop_laddr->siso_addr = *laddr;
	tmppcb.isop_faddr = &tmppcb.isop_sfaddr;
	tmppcb.isop_faddr->siso_addr = *faddr;
E 2

	IFDEBUG(D_TPISO)
		printf("tpclnp_output_dg  faddr: \n");
D 2
		dump_isoaddr(&tmppcb.isop_faddr);
E 2
I 2
		dump_isoaddr(&tmppcb.isop_sfaddr);
E 2
		printf("\ntpclnp_output_dg  laddr: \n");
D 2
		dump_isoaddr(&tmppcb.isop_laddr);
E 2
I 2
		dump_isoaddr(&tmppcb.isop_sladdr);
E 2
		printf("\n");
	ENDDEBUG

	/*
	 *	Do not use packet cache since this is a one shot error packet
	 */
	flags = (CLNP_NOCACHE|(nochksum?CLNP_NO_CKSUM:0));

	IncStat(ts_tpdu_sent);

D 2
	err = clnp_output(m0, &tmppcb, datalen, flags);
E 2
I 2
D 3
	if ((m->m_flags & M_PKTHDR) == 0) {
		printf("tpclnp_output: non headered mbuf");
		MGETHDR(m, M_DONTWAIT, MT_DATA);
		if (m == 0) {
			m_freem(m0);
			return ENOBUFS;
		}
		m->m_next = m0;
		m->m_len = 0;
		m->m_pkthdr.len = datalen;
		m0 = m;
	}
	err = clnp_output(m0, &tmppcb, flags);
E 3
I 3
	err = clnp_output(m0, &tmppcb, datalen,  flags);
E 3
E 2
	
	/*
	 *	Free route allocated by clnp (if the route was indeed allocated)
	 */
	if (tmppcb.isop_route.ro_rt)
		RTFREE(tmppcb.isop_route.ro_rt);
	
	return(err);
}
D 2

E 2
I 2
D 5
extern struct sockaddr_iso blank_siso;
E 5
E 2
/*
 * CALLED FROM:
 * 	clnp's input routine, indirectly through the protosw.
 * FUNCTION and ARGUMENTS:
 * Take a packet (m) from clnp, strip off the clnp header and give it to tp
 * No return value.  
 */
ProtoHook
D 5
tpclnp_input(m, faddr, laddr, clnp_len)
	struct mbuf *m;
	struct iso_addr *faddr, *laddr;
E 5
I 5
D 6
tpclnp_input(m, src, dst, clnp_len)
E 6
I 6
tpclnp_input(m, src, dst, clnp_len, ce_bit)
E 6
	register struct mbuf *m;
	struct sockaddr_iso *src, *dst;
E 5
D 6
	int clnp_len;
E 6
I 6
	int clnp_len, ce_bit;
E 6
{
D 5
	struct sockaddr_iso src, dst;
E 5
D 15
	int s = splnet();
E 15
I 2
	struct mbuf *tp_inputprep();
I 5
	int tp_input(), cltp_input(), (*input)() = tp_input;
E 5
E 2

	IncStat(ts_pkt_rcvd);

	IFDEBUG(D_TPINPUT)
		printf("tpclnp_input: m 0x%x clnp_len 0x%x\n", m, clnp_len);
		dump_mbuf(m, "at tpclnp_input");
	ENDDEBUG
	/*
	 * CLNP gives us an mbuf chain WITH the clnp header pulled up,
	 * and the length of the clnp header.
	 * First, strip off the Clnp header. leave the mbuf there for the
	 * pullup that follows.
	 */
D 15

E 15
	m->m_len -= clnp_len;
D 2
	m->m_off += clnp_len;
E 2
I 2
	m->m_data += clnp_len;
E 2
D 15

E 15
I 15
	m->m_pkthdr.len -= clnp_len;
	/* XXXX: should probably be in clnp_input */
	switch (dst->siso_data[dst->siso_nlen - 1]) {
#ifdef TUBA
	case ISOPROTO_TCP:
		return (tuba_tcpinput(m, src, dst));
#endif
	case 0:
		if (m->m_len == 0 && (m = m_pullup(m, 1)) == 0)
			return 0;
		if (*(mtod(m, u_char *)) == ISO10747_IDRP)
			return (idrp_input(m, src, dst));
	}
E 15
D 2
	m = (struct mbuf *)tp_inputprep(m);
E 2
I 2
	m = tp_inputprep(m);
I 5
	if (m == 0)
		return 0;
	if (mtod(m, u_char *)[1] == UD_TPDU_type)
		input = cltp_input;
E 5
E 2

	IFDEBUG(D_TPINPUT)
		dump_mbuf(m, "after tpclnp_input both pullups");
	ENDDEBUG

D 2
	src.siso_family = dst.siso_family = AF_ISO;
	bcopy(faddr, &src.siso_addr, sizeof(struct iso_addr));
	bcopy(laddr, &dst.siso_addr, sizeof(struct iso_addr));
E 2
I 2
D 5
	src = blank_siso; dst = blank_siso;
	bcopy((caddr_t)faddr, (caddr_t)&src.siso_addr, 1 + faddr->isoa_len);
	bcopy((caddr_t)laddr, (caddr_t)&dst.siso_addr, 1 + laddr->isoa_len);
E 2

E 5
	IFDEBUG(D_TPISO)
D 5
		printf("calling tp_input: &src 0x%x  &dst 0x%x, src addr:\n", 
			&src, &dst);
E 5
I 5
		printf("calling %sinput : src 0x%x, dst 0x%x, src addr:\n", 
			(input == tp_input ? "tp_" : "clts_"), src, dst);
		dump_isoaddr(src);
E 5
		printf(" dst addr:\n");
D 5
		dump_isoaddr(&src);
		dump_isoaddr(&dst);
E 5
I 5
		dump_isoaddr(dst);
E 5
	ENDDEBUG

D 2
	(void) tp_input(m, &src, &dst, 0, tpclnp_output_dg);
E 2
I 2
D 5
	(void) tp_input(m, (struct sockaddr *)&src, (struct sockaddr *)&dst,
E 5
I 5
	(void) (*input)(m, (struct sockaddr *)src, (struct sockaddr *)dst,
E 5
D 6
				0, tpclnp_output_dg);
E 6
I 6
				0, tpclnp_output_dg, ce_bit);
E 6
E 2

	IFDEBUG(D_QUENCH)
		{ 
			if(time.tv_usec & 0x4 && time.tv_usec & 0x40) {
				printf("tpclnp_input: FAKING %s\n", 
					tp_stat.ts_pkt_rcvd & 0x1?"QUENCH":"QUENCH2");
				if(tp_stat.ts_pkt_rcvd & 0x1) {
					tpclnp_ctlinput(PRC_QUENCH, &src);
				} else {
					tpclnp_ctlinput(PRC_QUENCH2, &src);
				}
			}
		}
	ENDDEBUG

D 15
	splx(s);
E 15
	return 0;
D 2

discard:
	IFDEBUG(D_TPINPUT)
		printf("tpclnp_input DISCARD\n");
	ENDDEBUG
	IFTRACE(D_TPINPUT)
		tptrace(TPPTmisc, "tpclnp_input DISCARD m",  m,0,0,0);
	ENDTRACE
	m_freem(m);
	IncStat(ts_recv_drop);
	splx(s);

	return 0;
E 2
}

ProtoHook
iso_rtchange()
{
	return 0;
}

/*
 * CALLED FROM:
 *  tpclnp_ctlinput()
 * FUNCTION and ARGUMENTS:
 *  find the tpcb pointer and pass it to tp_quench
 */
void
tpiso_decbit(isop)
	struct isopcb *isop;
{
D 2
	tp_quench( isop->isop_socket->so_tpcb, PRC_QUENCH2 );
E 2
I 2
D 12
	tp_quench((struct tp_pcb *)isop->isop_socket->so_tpcb, PRC_QUENCH2);
E 12
I 12
	tp_quench((struct tp_pcb *)isop->isop_socket->so_pcb, PRC_QUENCH2);
E 12
E 2
}
/*
 * CALLED FROM:
 *  tpclnp_ctlinput()
 * FUNCTION and ARGUMENTS:
 *  find the tpcb pointer and pass it to tp_quench
 */
void
tpiso_quench(isop)
	struct isopcb *isop;
{
D 2
	tp_quench( isop->isop_socket->so_tpcb, PRC_QUENCH );
E 2
I 2
D 12
	tp_quench((struct tp_pcb *)isop->isop_socket->so_tpcb, PRC_QUENCH);
E 12
I 12
	tp_quench((struct tp_pcb *)isop->isop_socket->so_pcb, PRC_QUENCH);
E 12
E 2
}

/*
 * CALLED FROM:
 *  The network layer through the protosw table.
 * FUNCTION and ARGUMENTS:
 *	When clnp an ICMP-like msg this gets called.
 *	It either returns an error status to the user or
 *	it causes all connections on this address to be aborted
 *	by calling the appropriate xx_notify() routine.
 *	(cmd) is the type of ICMP error.   
 * 	(siso) is the address of the guy who sent the ER CLNPDU
 */
ProtoHook
tpclnp_ctlinput(cmd, siso)
	int cmd;
	struct sockaddr_iso *siso;
{
I 2
D 5
	return tpclnp_ctlinput1(cmd, &siso->siso_addr);
}

/*
 *	Entry to ctlinput with argument of an iso_addr rather than a sockaddr
 */
ProtoHook
tpclnp_ctlinput1(cmd, isoa)
	int cmd;
	struct iso_addr	*isoa;
{
E 5
E 2
	extern u_char inetctlerrmap[];
	extern ProtoHook tpiso_abort();
	extern ProtoHook iso_rtchange();
	extern ProtoHook tpiso_reset();
I 2
	void iso_pcbnotify();
E 2

	IFDEBUG(D_TPINPUT)
D 2
		printf("tpclnp_ctlinput: cmd 0x%x addr: ", cmd);
		dump_isoaddr(siso);
		printf("\n");
E 2
I 2
D 5
		printf("tpclnp_ctlinput1: cmd 0x%x addr: %s\n", cmd, 
			clnp_iso_addrp(isoa));
E 5
I 5
		printf("tpclnp_ctlinput1: cmd 0x%x addr: \n", cmd);
		dump_isoaddr(siso);
E 5
E 2
	ENDDEBUG

	if (cmd < 0 || cmd > PRC_NCMDS)
		return 0;
I 5
	if (siso->siso_family != AF_ISO)
		return 0;
E 5
	switch (cmd) {

		case	PRC_QUENCH2:
D 2
			iso_pcbnotify(&tp_isopcb, &siso->siso_addr, 0, tpiso_decbit);
E 2
I 2
D 5
			iso_pcbnotify(&tp_isopcb, isoa, 0, (int (*)())tpiso_decbit);
E 5
I 5
			iso_pcbnotify(&tp_isopcb, siso, 0, (int (*)())tpiso_decbit);
E 5
E 2
			break;

		case	PRC_QUENCH:
D 2
			iso_pcbnotify(&tp_isopcb, &siso->siso_addr, 0, tpiso_quench);
E 2
I 2
D 5
			iso_pcbnotify(&tp_isopcb, isoa, 0, (int (*)())tpiso_quench);
E 5
I 5
			iso_pcbnotify(&tp_isopcb, siso, 0, (int (*)())tpiso_quench);
E 5
E 2
			break;

		case	PRC_TIMXCEED_REASS:
		case	PRC_ROUTEDEAD:
D 2
			iso_pcbnotify(&tp_isopcb, &siso->siso_addr, 0, tpiso_reset);
E 2
I 2
D 5
			iso_pcbnotify(&tp_isopcb, isoa, 0, tpiso_reset);
E 5
I 5
			iso_pcbnotify(&tp_isopcb, siso, 0, tpiso_reset);
E 5
E 2
			break;

		case	PRC_HOSTUNREACH:
		case	PRC_UNREACH_NET:
		case	PRC_IFDOWN:
		case	PRC_HOSTDEAD:
D 2
			iso_pcbnotify(&tp_isopcb, &siso->siso_addr,
E 2
I 2
D 5
			iso_pcbnotify(&tp_isopcb, isoa,
E 5
I 5
			iso_pcbnotify(&tp_isopcb, siso,
E 5
E 2
					(int)inetctlerrmap[cmd], iso_rtchange);
			break;

		default:
		/*
		case	PRC_MSGSIZE:
		case	PRC_UNREACH_HOST:
		case	PRC_UNREACH_PROTOCOL:
		case	PRC_UNREACH_PORT:
		case	PRC_UNREACH_NEEDFRAG:
		case	PRC_UNREACH_SRCFAIL:
		case	PRC_REDIRECT_NET:
		case	PRC_REDIRECT_HOST:
		case	PRC_REDIRECT_TOSNET:
		case	PRC_REDIRECT_TOSHOST:
		case	PRC_TIMXCEED_INTRANS:
		case	PRC_PARAMPROB:
		*/
D 2
		iso_pcbnotify(&tp_isopcb, &siso->siso_addr, 
			(int)inetctlerrmap[cmd], tpiso_abort);
E 2
I 2
D 5
		iso_pcbnotify(&tp_isopcb, isoa, (int)inetctlerrmap[cmd], tpiso_abort);
E 5
I 5
		iso_pcbnotify(&tp_isopcb, siso, (int)inetctlerrmap[cmd], tpiso_abort);
E 5
E 2
		break;
	}
	return 0;
}
I 5
/*
 * XXX - Variant which is called by clnp_er.c with an isoaddr rather
 * than a sockaddr_iso.
 */
E 5

I 5
static struct sockaddr_iso siso = {sizeof(siso), AF_ISO};
tpclnp_ctlinput1(cmd, isoa)
	int cmd;
	struct iso_addr *isoa;
{
	bzero((caddr_t)&siso.siso_addr, sizeof(siso.siso_addr));
	bcopy((caddr_t)isoa, (caddr_t)&siso.siso_addr, isoa->isoa_len);
	tpclnp_ctlinput(cmd, &siso);
}

E 5
/*
 * These next 2 routines are
 * CALLED FROM:
 *	xxx_notify() from tp_ctlinput() when
 *  net level gets some ICMP-equiv. type event.
 * FUNCTION and ARGUMENTS:
 *  Cause the connection to be aborted with some sort of error
 *  reason indicating that the network layer caused the abort.
 *  Fakes an ER TPDU so we can go through the driver.
 *  abort always aborts the TP connection.
 *  reset may or may not, depending on the TP class that's in use.
 */
ProtoHook
tpiso_abort(isop)
	struct isopcb *isop;
{
	struct tp_event e;

	IFDEBUG(D_CONN)
		printf("tpiso_abort 0x%x\n", isop);
	ENDDEBUG
	e.ev_number = ER_TPDU;
	e.ATTR(ER_TPDU).e_reason = ECONNABORTED;
D 12
	return  tp_driver((struct tp_pcb *)isop->isop_socket->so_tpcb, &e);
E 12
I 12
	return  tp_driver((struct tp_pcb *)isop->isop_socket->so_pcb, &e);
E 12
}

ProtoHook
tpiso_reset(isop)
	struct isopcb *isop;
{
	struct tp_event e;

	e.ev_number = T_NETRESET;
D 12
	return tp_driver((struct tp_pcb *)isop->isop_socket->so_tpcb, &e);
E 12
I 12
	return tp_driver((struct tp_pcb *)isop->isop_socket->so_pcb, &e);
E 12

}

I 5
D 7
#include "cltp_usrreq.c"
E 7
E 5
D 16
#endif ISO
E 16
I 16
#endif /* ISO */
E 16
E 1
