h02035
s 00002/00002/00660
d D 8.1 93/06/10 23:20:17 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00654
d D 7.13 93/06/05 15:57:59 sklower 13 12
c ip_output takes 5 args now; other miscelleny due to prototypes in header files
e
s 00002/00002/00660
d D 7.12 93/05/25 11:51:49 bostic 12 11
c trailing comment after #else or #endif
e
s 00021/00019/00641
d D 7.11 92/10/11 12:21:58 bostic 11 10
c make kernel includes standard
e
s 00013/00144/00647
d D 7.10 91/10/02 19:43:39 sklower 10 9
c move common mtu estimation to tp_route_to; here determine
c only where the rtentry pointer is found in the npcb, and provide net hdr size
e
s 00001/00001/00790
d D 7.9 91/07/18 20:33:31 sklower 9 8
c this changes reflect getting rid of so_tpcb.
e
s 00019/00015/00772
d D 7.8 91/05/06 19:24:20 bostic 8 7
c new copyright; att/bsd/shared
e
s 00007/00006/00780
d D 7.7 90/11/20 21:54:27 sklower 7 6
c parameters to in_pcbnotify changed
e
s 00034/00000/00752
d D 7.6 90/06/28 19:39:32 sklower 6 5
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00004/00005/00748
d D 7.5 90/01/16 23:29:22 sklower 5 4
c changes to accomodate changes in in_pcbnotify.
e
s 00001/00000/00752
d D 7.4 89/08/29 13:44:57 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00001/00001/00751
d D 7.3 89/04/25 17:19:48 mckusick 3 2
c ../h => (implicitly) ../sys
e
s 00094/00086/00658
d D 7.2 89/04/22 11:54:54 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00744/00000/00000
d D 7.1 88/12/14 15:30:00 sklower 1 0
c date and time created 88/12/14 15:30:00 by sklower
e
u
U
t
T
I 8
/*-
D 14
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 8
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
 * $Header: tp_inet.c,v 5.3 88/11/18 17:27:29 nhall Exp $ 
 * $Source: /usr/argo/sys/netiso/RCS/tp_inet.c,v $
I 4
D 8
 *	%W% (Berkeley) %G% *
E 8
E 4
 *
 * Here is where you find the inet-dependent code.  We've tried
 * keep all net-level and (primarily) address-family-dependent stuff
 * out of the tp source, and everthing here is reached indirectly
 * through a switch table (struct nl_protosw *) tpcb->tp_nlproto 
 * (see tp_pcb.c). 
 * The routines here are:
D 8
 * 		in_getsufx: gets transport suffix out of an inpcb structure.
 * 		in_putsufx: put transport suffix into an inpcb structure.
 *		in_putnetaddr: put a whole net addr into an inpcb.
 *		in_getnetaddr: get a whole net addr from an inpcb.
I 6
 *		in_cmpnetaddr: compare a whole net addr from an isopcb.
E 6
 *		in_recycle_suffix: clear suffix for reuse in inpcb
 *		tpip_mtu: figure out what size tpdu to use
 *		tpip_input: take a pkt from ip, strip off its ip header, give to tp
 *		tpip_output_dg: package a pkt for ip given 2 addresses & some data
 *		tpip_output: package a pkt for ip given an inpcb & some data
E 8
I 8
 * 	in_getsufx: gets transport suffix out of an inpcb structure.
 * 	in_putsufx: put transport suffix into an inpcb structure.
 *	in_putnetaddr: put a whole net addr into an inpcb.
 *	in_getnetaddr: get a whole net addr from an inpcb.
 *	in_cmpnetaddr: compare a whole net addr from an isopcb.
 *	in_recycle_suffix: clear suffix for reuse in inpcb
 *	tpip_mtu: figure out what size tpdu to use
 *	tpip_input: take a pkt from ip, strip off its ip header, give to tp
 *	tpip_output_dg: package a pkt for ip given 2 addresses & some data
 *	tpip_output: package a pkt for ip given an inpcb & some data
E 8
 */
D 8

#ifndef lint
static char *rcsid = "$Header: tp_inet.c,v 5.3 88/11/18 17:27:29 nhall Exp $";
#endif lint
E 8

#ifdef INET

D 2
#include "types.h"
E 2
I 2
D 11
#include "param.h"
E 2
#include "socket.h"
#include "socketvar.h"
#include "mbuf.h"
#include "errno.h"
#include "time.h"
#include "../net/if.h"
D 2
#include "../netiso/tp_param.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_ip.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_tpdu.h"
E 2
I 2
#include "tp_param.h"
#include "argo_debug.h"
#include "tp_stat.h"
#include "tp_ip.h"
#include "tp_pcb.h"
#include "tp_trace.h"
#include "tp_stat.h"
#include "tp_tpdu.h"
E 2
#include "../netinet/in_var.h"
E 11
I 11
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mbuf.h>
#include <sys/errno.h>
#include <sys/time.h>
E 11

I 11
#include <net/if.h>

#include <netiso/tp_param.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_ip.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_tpdu.h>
#include <netinet/in_var.h>

E 11
I 2
#ifndef ISO
D 11
#include "iso_chksum.c"
E 11
I 11
#include <netiso/iso_chksum.c>
E 11
#endif
E 2

/*
 * NAME:			in_getsufx()

 * CALLED FROM: 	pr_usrreq() on PRU_BIND, 
 *					PRU_CONNECT, PRU_ACCEPT, and PRU_PEERADDR
 *
 * FUNCTION, ARGUMENTS, and RETURN VALUE:
 * 	Get a transport suffix from an inpcb structure (inp).
 * 	The argument (which) takes the value TP_LOCAL or TP_FOREIGN.
 *
 * RETURNS:		internet port / transport suffix
 *  			(CAST TO AN INT)
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
D 2

int
in_getsufx(inp,  which)
E 2
I 2
in_getsufx(inp, lenp, data_out, which)
E 2
	struct inpcb *inp;
I 2
	u_short *lenp;
	caddr_t data_out;
E 2
	int which;
{
I 2
	*lenp = sizeof(u_short);
E 2
	switch (which) {
	case TP_LOCAL:
D 2
		return (int) inp->inp_lport;
E 2
I 2
		*(u_short *)data_out = inp->inp_lport;
		return;
E 2

	case TP_FOREIGN:
D 2
		return (int) inp->inp_fport;
E 2
I 2
		*(u_short *)data_out = inp->inp_fport;
E 2
	}
I 2

E 2
}

/*
 * NAME:		in_putsufx()
 *
 * CALLED FROM: tp_newsocket(); i.e., when a connection 
 *		is being established by an incoming CR_TPDU.
 *
 * FUNCTION, ARGUMENTS:
 * 	Put a transport suffix (found in name) into an inpcb structure (inp).
 * 	The argument (which) takes the value TP_LOCAL or TP_FOREIGN.
 *
 * RETURNS:		Nada
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
I 2
/*ARGSUSED*/
E 2
void
D 2
in_putsufx(inp, name, which)
E 2
I 2
in_putsufx(inp, sufxloc, sufxlen, which)
E 2
	struct inpcb *inp;
D 2
	struct sockaddr_in *name;
E 2
I 2
	caddr_t sufxloc;
E 2
	int which;
{
D 2
	switch (which) {
	case TP_LOCAL:
		inp->inp_lport = name->sin_port;
		break;
	case TP_FOREIGN:
		inp->inp_fport = name->sin_port;
		break;
E 2
I 2
	if (which == TP_FOREIGN) {
		bcopy(sufxloc, (caddr_t)&inp->inp_fport, sizeof(inp->inp_fport));
E 2
	}
}

/*
 * NAME:	in_recycle_tsuffix()	
 *
 * CALLED FROM:	tp.trans whenever we go into REFWAIT state.
 *
 * FUNCTION and ARGUMENT:
 *	 Called when a ref is frozen, to allow the suffix to be reused. 
 * 	(inp) is the net level pcb.  
 *
 * RETURNS:			Nada
 *
 * SIDE EFFECTS:	
 *
 * NOTES:	This really shouldn't have to be done in a NET level pcb 
 *	but... for the internet world that just the way it is done in BSD...
 * 	The alternative is to have the port unusable until the reference
 * 	timer goes off.
 */
void
in_recycle_tsuffix(inp)
	struct inpcb	*inp;
{
	inp->inp_fport = inp->inp_lport = 0;
}

/*
 * NAME:	in_putnetaddr()
 *
 * CALLED FROM:
 * 	tp_newsocket(); i.e., when a connection is being established by an
 * 	incoming CR_TPDU.
 *
 * FUNCTION and ARGUMENTS:
 * 	Copy a whole net addr from a struct sockaddr (name).
 * 	into an inpcb (inp).
 * 	The argument (which) takes values TP_LOCAL or TP_FOREIGN
 *
 * RETURNS:		Nada
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */ 
void
in_putnetaddr(inp, name, which)
	register struct inpcb	*inp;
	struct sockaddr_in	*name;
	int which;
{
	switch (which) {
	case TP_LOCAL:
		bcopy((caddr_t)&name->sin_addr, 
			(caddr_t)&inp->inp_laddr, sizeof(struct in_addr));
			/* won't work if the dst address (name) is INADDR_ANY */

		break;
	case TP_FOREIGN:
		if( name != (struct sockaddr_in *)0 ) {
			bcopy((caddr_t)&name->sin_addr, 
				(caddr_t)&inp->inp_faddr, sizeof(struct in_addr));
		}
	}
I 6
}

/*
 * NAME:	in_putnetaddr()
 *
 * CALLED FROM:
 * 	tp_input() when a connection is being established by an
 * 	incoming CR_TPDU, and considered for interception.
 *
 * FUNCTION and ARGUMENTS:
 * 	Compare a whole net addr from a struct sockaddr (name),
 * 	with that implicitly stored in an inpcb (inp).
 * 	The argument (which) takes values TP_LOCAL or TP_FOREIGN
 *
 * RETURNS:		Nada
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */ 
in_cmpnetaddr(inp, name, which)
	register struct inpcb	*inp;
	register struct sockaddr_in	*name;
	int which;
{
	if (which == TP_LOCAL) {
		if (name->sin_port && name->sin_port != inp->inp_lport)
			return 0;
		return (name->sin_addr.s_addr == inp->inp_laddr.s_addr);
	}
	if (name->sin_port && name->sin_port != inp->inp_fport)
		return 0;
	return (name->sin_addr.s_addr == inp->inp_faddr.s_addr);
E 6
}

/*
 * NAME:	in_getnetaddr()
 *
 * CALLED FROM:
 *  pr_usrreq() PRU_SOCKADDR, PRU_ACCEPT, PRU_PEERADDR
 * FUNCTION and ARGUMENTS:
 * 	Copy a whole net addr from an inpcb (inp) into
D 2
 * 	a struct sockaddr (name).
E 2
I 2
 * 	an mbuf (name);
E 2
 * 	The argument (which) takes values TP_LOCAL or TP_FOREIGN.
 *
 * RETURNS:		Nada
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */ 

void
in_getnetaddr( inp, name, which)
I 2
	register struct mbuf *name;
E 2
	struct inpcb *inp;
D 2
	struct sockaddr_in *name;
E 2
	int which;
{
I 2
	register struct sockaddr_in *sin = mtod(name, struct sockaddr_in *);
	bzero((caddr_t)sin, sizeof(*sin));
E 2
	switch (which) {
	case TP_LOCAL:
D 2
		bcopy( (caddr_t)&inp->inp_laddr, (caddr_t)&name->sin_addr, 
				sizeof(struct in_addr));
			/* won't work if the dst address (name) is INADDR_ANY */
E 2
I 2
		sin->sin_addr = inp->inp_laddr;
		sin->sin_port = inp->inp_lport;
E 2
		break;
D 2

E 2
	case TP_FOREIGN:
D 2
		bcopy( (caddr_t)&inp->inp_faddr, (caddr_t)&name->sin_addr, 
				sizeof(struct in_addr));
			/* won't work if the dst address (name) is INADDR_ANY */
E 2
I 2
		sin->sin_addr = inp->inp_faddr;
		sin->sin_port = inp->inp_fport;
E 2
		break;
I 2
	default:
		return;
E 2
	}
I 2
	name->m_len = sin->sin_len = sizeof (*sin);
	sin->sin_family = AF_INET;
E 2
}

/*
 * NAME: 	tpip_mtu()
 *
 * CALLED FROM:
D 10
 *  tp_input() on incoming CR, CC, and pr_usrreq() for PRU_CONNECT
E 10
I 10
 *  tp_route_to() on incoming CR, CC, and pr_usrreq() for PRU_CONNECT
E 10
 *
 * FUNCTION, ARGUMENTS, and RETURN VALUE:
 *
D 10
 * Determine the proper maximum transmission unit, i.e., MTU, to use, given
 * a) the header size for the network protocol and the max transmission
 *	  unit on the subnet interface, determined from the information in (inp),
 * b) the max size negotiated so far (negot)
 * c) the window size used by the tp connection (found in so),
 *
 * The result is put in the integer *size in its integer form and in
 * *negot in its logarithmic form.  
E 10
I 10
 * Perform subnetwork dependent part of determining MTU information.
 * It appears that setting a double pointer to the rtentry associated with
 * the destination, and returning the header size for the network protocol
 * suffices.
E 10
 * 
D 10
 * The rules are:
 * a) can only negotiate down from the value found in *negot.
 * b) the MTU must be < the windowsize,
 * c) If src and dest are on the same net,
 * 	  we will negotiate the closest size larger than  MTU but really USE 
 *    the actual device mtu - ll hdr sizes.
 *   otherwise we negotiate the closest size smaller than MTU - ll hdr sizes.
 * 
E 10
 * SIDE EFFECTS:
D 10
 *	changes the values addressed by the arguments (size) and (negot)
 *  and
 *  when the peer is not on one of our directly connected subnets, it
 *  looks up a route, leaving the route in the inpcb addressed by (inp)
E 10
I 10
 * Sets tp_routep pointer in pcb.
E 10
 *
 * NOTES:
 */

D 10
void
tpip_mtu(so, inp, size, negot)
	struct socket *so;
	struct inpcb *inp;
	int *size;
	u_char *negot;
E 10
I 10
tpip_mtu(tpcb)
register struct tp_pcb *tpcb;
E 10
{
D 10
	register struct ifnet	*ifp;
	struct ifnet			*tpip_route();
	struct in_ifaddr		*ia;
	register int			i;
	int						windowsize = so->so_rcv.sb_hiwat;
E 10
I 10
	struct inpcb			*inp = (struct inpcb *)tpcb->tp_npcb;
E 10

	IFDEBUG(D_CONN)
D 10
		printf("tpip_mtu(0x%x,0x%x,0x%x,0x%x)\n",
			so, inp, size, negot);
		printf("tpip_mtu routing to addr 0x%x\n", inp->inp_faddr);
E 10
I 10
		printf("tpip_mtu(tpcb)\n", tpcb);
		printf("tpip_mtu routing to addr 0x%x\n", inp->inp_faddr.s_addr);
E 10
	ENDDEBUG
D 10
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "ENTER GET MTU: size negot \n",*size, *negot, 0, 0);
	ENDTRACE
E 10
I 10
	tpcb->tp_routep = &(inp->inp_route.ro_rt);
	return (sizeof (struct ip));
E 10

D 10
	*size = 1 << *negot;

	if( *size > windowsize ) {
		*size = windowsize;
	}

	ia = in_iaonnetof(in_netof(inp->inp_faddr));
	if ( ia == (struct in_ifaddr *)0 ) {
		ifp = tpip_route(&inp->inp_faddr);
		if( ifp == (struct ifnet *)0 )
			return ;
	} else
		ifp = ia->ia_ifp;


	/****************************************************************
	 * TODO - make this indirect off the socket structure to the
	 * network layer to get headersize
	 * After all, who knows what lies below the IP layer?
	 * Who knows how big the NL header will be?
	 ***************************************************************/

	if( *size > ifp->if_mtu - sizeof(struct ip)) {
		*size = ifp->if_mtu - sizeof(struct ip);
	}
	for(i=TP_MIN_TPDUSIZE; (i<TP_MAX_TPDUSIZE && ((1<<i)<*size)) ; i++)
		;
	i--;

	if (in_netof(inp->inp_laddr) != in_netof(inp->inp_faddr)) {
		i++;
	} else {
		*size = 1<<i;
	}
	*negot = i;

	IFDEBUG(D_CONN)
		printf("GET MTU RETURNS: ifp %s size 0x%x negot 0x%x\n",
		ifp->if_name,	*size, *negot);
	ENDDEBUG
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "EXIT GET MTU: tpcb size negot \n",
		*size, *negot, 0, 0);
	ENDTRACE

E 10
}

/*
 * NAME:	tpip_output()
 *
 * CALLED FROM:  tp_emit()
 *
 * FUNCTION and ARGUMENTS:
 *  Take a packet(m0) from tp and package it so that ip will accept it.
 *  This means prepending space for the ip header and filling in a few
 *  of the fields.
 *  inp is the inpcb structure; datalen is the length of the data in the
 *  mbuf string m0.
 * RETURNS:			
 *  whatever (E*) is returned form the net layer output routine.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */

int
tpip_output(inp, m0, datalen, nochksum)
	struct inpcb		*inp;
	struct mbuf 		*m0;
	int 				datalen;
	int					nochksum;
{
	return tpip_output_dg( &inp->inp_laddr, &inp->inp_faddr, m0, datalen,
		&inp->inp_route, nochksum);
}

/*
 * NAME:	tpip_output_dg()
 *
 * CALLED FROM:  tp_error_emit()
 *
 * FUNCTION and ARGUMENTS:
 *  This is a copy of tpip_output that takes the addresses
 *  instead of a pcb.  It's used by the tp_error_emit, when we
 *  don't have an in_pcb with which to call the normal output rtn.
 *
 * RETURNS:	 ENOBUFS or  whatever (E*) is 
 *	returned form the net layer output routine.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */

I 2
/*ARGSUSED*/
E 2
int
tpip_output_dg(laddr, faddr, m0, datalen, ro, nochksum)
	struct in_addr		*laddr, *faddr;
	struct mbuf 		*m0;
	int 				datalen;
	struct route 		*ro;
	int					nochksum;
{
	register struct mbuf 	*m;
	register struct ip *ip;
	int 					error;

	IFDEBUG(D_EMIT)
		printf("tpip_output_dg  datalen 0x%x m0 0x%x\n", datalen, m0);
	ENDDEBUG


D 2
	MGET(m, M_DONTWAIT, TPMT_IPHDR);
E 2
I 2
	MGETHDR(m, M_DONTWAIT, TPMT_IPHDR);
E 2
	if (m == 0) {
		error = ENOBUFS;
		goto bad;
	}
D 2
	bzero(mtod(m, caddr_t), MLEN);
E 2
	m->m_next = m0;
D 2
	m->m_off = MMAXOFF - sizeof(struct ip);
E 2
I 2
	MH_ALIGN(m, sizeof(struct ip));
E 2
	m->m_len = sizeof(struct ip);
D 2
	m->m_act = MNULL;
E 2

	ip = mtod(m, struct ip *);
I 2
	bzero((caddr_t)ip, sizeof *ip);
E 2

	ip->ip_p = IPPROTO_TP;
D 2
	ip->ip_len = sizeof(struct ip) + datalen;
E 2
I 2
	m->m_pkthdr.len = ip->ip_len = sizeof(struct ip) + datalen;
E 2
	ip->ip_ttl = MAXTTL;	
		/* don't know why you need to set ttl;
		 * overlay doesn't even make this available
		 */

	ip->ip_src = *laddr;
	ip->ip_dst = *faddr;

	IncStat(ts_tpdu_sent);
	IFDEBUG(D_EMIT)
		dump_mbuf(m, "tpip_output_dg before ip_output\n");
	ENDDEBUG

D 13
	error = ip_output(m, (struct mbuf *)0, ro, IP_ALLOWBROADCAST);
E 13
I 13
	error = ip_output(m, (struct mbuf *)0, ro, IP_ALLOWBROADCAST, NULL);
E 13

	IFDEBUG(D_EMIT)
		printf("tpip_output_dg after ip_output\n");
	ENDDEBUG

	return error;

bad:
	m_freem(m);
	IncStat(ts_send_drop);
	return error;
}

/*
 * NAME:  tpip_input()
 *
 * CALLED FROM:
 * 	ip's input routine, indirectly through the protosw.
 *
 * FUNCTION and ARGUMENTS:
 * Take a packet (m) from ip, strip off the ip header and give it to tp
 *
 * RETURNS:  No return value.  
 * 
 * SIDE EFFECTS:
 *
 * NOTES:
 */
ProtoHook
D 2
tpip_input(m)
E 2
I 2
tpip_input(m, iplen)
E 2
	struct mbuf *m;
I 2
	int iplen;
E 2
{
D 2
	typedef struct {
		struct ip	 tpip_i;
		struct tpdu  tpip_d;
	} tpiphdr;
	register struct tpdu 	*hdr = mtod(m, struct tpdu *);
E 2
	struct sockaddr_in 	src, dst;
	register struct ip 		*ip;
D 2
	int						s = splnet();
E 2
I 2
	int						s = splnet(), hdrlen;
E 2

	IncStat(ts_pkt_rcvd);

D 2
	/* IP layer has already pulled up the IP header */
E 2
I 2
	/*
	 * IP layer has already pulled up the IP header,
	 * but the first byte after the IP header may not be there,
	 * e.g. if you came in via loopback, so you have to do an
	 * m_pullup to before you can even look to see how much you
	 * really need.  The good news is that m_pullup will round
	 * up to almost the next mbuf's worth.
	 */
E 2

D 2
	while( m->m_len < 1 ) {
		struct mbuf *n;
		n = m_free(m);
		if( n == MNULL ) {
			splx(s);
			return 0;
		}
	}
E 2
I 2

	if((m = m_pullup(m, iplen + 1)) == MNULL)
		goto discard;
E 2
	CHANGE_MTYPE(m, TPMT_DATA);
	
	/*
D 2
	 * now pull up the whole tp header : we stripped all leading mbufs
	 * w/o at least one byte, so we know we can read the tpdu_li field.
E 2
I 2
	 * Now pull up the whole tp header:
	 * Unfortunately, there may be IP options to skip past so we
	 * just fetch it as an unsigned char.
E 2
	 */
D 2
	hdr = &(mtod(m, tpiphdr *))->tpip_d;
E 2
I 2
	hdrlen = iplen + 1 + mtod(m, u_char *)[iplen];
E 2

D 2
	if( m->m_len < hdr->tpdu_li + 1 + sizeof(struct ip) ) {
		if((m = m_pullup(m, sizeof(struct ip) + (int)(hdr->tpdu_li)+1))==MNULL){
E 2
I 2
	if( m->m_len < hdrlen ) {
		if((m = m_pullup(m, hdrlen)) == MNULL){
E 2
			IFDEBUG(D_TPINPUT)
				printf("tp_input, pullup 2!\n");
			ENDDEBUG
			goto discard;
		}
	}
	/* 
	 * cannot use tp_inputprep() here 'cause you don't 
	 * have quite the same situation
	 */

	IFDEBUG(D_TPINPUT)
		dump_mbuf(m, "after tpip_input both pullups");
	ENDDEBUG
	/* 
	 * m_pullup may have returned a different mbuf
	 */
D 2
	ip = &(mtod(m, tpiphdr *))->tpip_i;
E 2
I 2
	ip = mtod(m, struct ip *);
E 2

	/*
	 * drop the ip header from the front of the mbuf
	 * this is necessary for the tp checksum
	 */
D 2
	m->m_len -= sizeof(struct ip);
	m->m_off += sizeof(struct ip);
E 2
I 2
	m->m_len -= iplen;
	m->m_data += iplen;
E 2

	src.sin_addr = *(struct in_addr *)&(ip->ip_src);
	src.sin_family  = AF_INET;
I 2
	src.sin_len  = sizeof(src);
E 2
	dst.sin_addr = *(struct in_addr *)&(ip->ip_dst);
	dst.sin_family  = AF_INET; 
I 2
	dst.sin_len  = sizeof(dst);
E 2

D 2
	(void) tp_input(m, &src, &dst, 0, tpip_output_dg);
E 2
I 2
	(void) tp_input(m, (struct sockaddr *)&src, (struct sockaddr *)&dst,
D 5
				0, tpip_output_dg);
E 2
	splx(s);
E 5
I 5
				0, tpip_output_dg, 0);
E 5
	return 0;

discard:
	IFDEBUG(D_TPINPUT)
		printf("tpip_input DISCARD\n");
	ENDDEBUG
	IFTRACE(D_TPINPUT)
		tptrace(TPPTmisc, "tpip_input DISCARD m",  m,0,0,0);
	ENDTRACE
	m_freem(m);
	IncStat(ts_recv_drop);
D 2

E 2
I 2
	splx(s);
E 2
	return 0;
}


D 3
#include "../h/protosw.h"
E 3
I 3
D 11
#include "protosw.h"
E 3
#include "../netinet/ip_icmp.h"
E 11
I 11
#include <sys/protosw.h>
#include <netinet/ip_icmp.h>
E 11

I 2
extern void tp_quench();
E 2
/*
 * NAME:	tpin_quench()
 *
 * CALLED FROM: tpip_ctlinput()
 *
 * FUNCTION and ARGUMENTS:  find the tpcb pointer and pass it to tp_quench
 *
 * RETURNS:	Nada
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */

void
tpin_quench(inp)
	struct inpcb *inp;
{
D 2
	tp_quench( inp->inp_socket->so_tpcb );
E 2
I 2
D 9
	tp_quench((struct tp_pcb *)inp->inp_socket->so_tpcb, PRC_QUENCH);
E 9
I 9
	tp_quench((struct tp_pcb *)inp->inp_socket->so_pcb, PRC_QUENCH);
E 9
E 2
}

/*
 * NAME:	tpip_ctlinput()
 *
 * CALLED FROM:
 *  The network layer through the protosw table.
 *
 * FUNCTION and ARGUMENTS:
 *	When clnp gets an ICMP msg this gets called.
 *	It either returns an error status to the user or
 *	causes all connections on this address to be aborted
 *	by calling the appropriate xx_notify() routine.
 *	(cmd) is the type of ICMP error.   
 * 	(sa) the address of the sender
 *
 * RETURNS:	 Nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
ProtoHook
tpip_ctlinput(cmd, sin)
	int cmd;
	struct sockaddr_in *sin;
{
	extern u_char inetctlerrmap[];
D 13
	extern ProtoHook tpin_abort();
	extern ProtoHook in_rtchange();
E 13
I 7
	extern struct in_addr zeroin_addr;
I 13
	void tp_quench __P((struct inpcb *,int));
	void tpin_abort __P((struct inpcb *,int));
E 13
E 7

	if (sin->sin_family != AF_INET && sin->sin_family != AF_IMPLINK)
		return 0;
	if (sin->sin_addr.s_addr == INADDR_ANY)
		return 0;
	if (cmd < 0 || cmd > PRC_NCMDS)
		return 0;
	switch (cmd) {

		case	PRC_QUENCH:
D 2
			in_pcbnotify(&tp_inpcb, &sin->sin_addr, 0, tp_quench);
E 2
I 2
D 5
			in_pcbnotify(&tp_inpcb, &sin->sin_addr, 
E 5
I 5
D 7
			in_pcbnotify(&tp_inpcb, sin, 
E 5
						0, (int (*)())tp_quench);
E 7
I 7
D 13
			in_pcbnotify(&tp_inpcb, sin, 0,
				zeroin_addr, 0, cmd, (int (*)())tp_quench);
E 13
I 13
			in_pcbnotify(&tp_inpcb, (struct sockaddr *)sin, 0,
				zeroin_addr, 0, cmd, tp_quench);
E 13
E 7
E 2
			break;

		case	PRC_ROUTEDEAD:
		case	PRC_HOSTUNREACH:
		case	PRC_UNREACH_NET:
		case	PRC_IFDOWN:
		case	PRC_HOSTDEAD:
D 5
			in_pcbnotify(&tp_inpcb, &sin->sin_addr, 
E 5
I 5
D 7
			in_pcbnotify(&tp_inpcb, sin, 
E 5
					(int)inetctlerrmap[cmd], in_rtchange);
E 7
I 7
D 13
			in_pcbnotify(&tp_inpcb, sin, 0,
E 13
I 13
			in_pcbnotify(&tp_inpcb, (struct sockaddr *)sin, 0,
E 13
				zeroin_addr, 0, cmd, in_rtchange);
E 7
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
		case	PRC_TIMXCEED_REASS:
		case	PRC_PARAMPROB:
		*/
D 2
		in_pcbnotify(&tp_inpcb, sin, (int)inetctlerrmap[cmd], tpin_abort);
E 2
I 2
D 5
		in_pcbnotify(&tp_inpcb, &sin->sin_addr,
E 5
I 5
D 7
		in_pcbnotify(&tp_inpcb, sin,
E 5
				(int)inetctlerrmap[cmd], tpin_abort);
E 7
I 7
D 13
		in_pcbnotify(&tp_inpcb, sin, 0, zeroin_addr, 0,
				cmd, tpin_abort);
E 13
I 13
		in_pcbnotify(&tp_inpcb, (struct sockaddr *)sin, 0,
			zeroin_addr, 0, cmd, tpin_abort);
E 13
E 7
E 2
	}
	return 0;
}

/*
 * NAME:	tpin_abort()
 *
 * CALLED FROM:
 *	xxx_notify() from tp_ctlinput() when
 *  net level gets some ICMP-equiv. type event.
 *
 * FUNCTION and ARGUMENTS:
 *  Cause the connection to be aborted with some sort of error
 *  reason indicating that the network layer caused the abort.
 *  Fakes an ER TPDU so we can go through the driver.
 *
 * RETURNS:	 Nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */

ProtoHook
tpin_abort(inp)
	struct inpcb *inp;
{
	struct tp_event e;

	e.ev_number = ER_TPDU;
	e.ATTR(ER_TPDU).e_reason = ENETRESET;
D 2
	(void) tp_driver(inp->inp_ppcb, &e);
E 2
I 2
	(void) tp_driver((struct tp_pcb *)inp->inp_ppcb, &e);
E 2
	return 0;
}

#ifdef ARGO_DEBUG
dump_inaddr(addr)
	register struct sockaddr_in *addr;
{
	printf("INET: port 0x%x; addr 0x%x\n", addr->sin_port, addr->sin_addr);
}
D 12
#endif ARGO_DEBUG
D 10

/*
 * NAME:	tpip_route()
 *
 * CALLED FROM: tpip_mtu()
 *
 * FUNCTION and ARGUMENTS:	given a destination addresss,
 *	find the interface that would be used to send something to this address.
 *
 * RETURNS:	 pointer to an ifnet structure
 *
 * SIDE EFFECTS:
 *
 * NOTES:			
 */
struct ifnet *
tpip_route(dst)
	struct in_addr *dst;
{
D 2
	struct	ifnet 		*ifp = (struct ifnet *)0;
	struct	sockaddr_in	*dst_in;
	struct route		iproute;
	struct route		*ro = (struct route *)0;
	struct in_ifaddr	*ia;
E 2
I 2
	struct ifnet 		*ifp = (struct ifnet *)0;
	struct sockaddr_in	insock;
	struct sockaddr_in	*sin = &insock;
	struct rtentry 		*rt;
	struct ifaddr	*ia;
E 2

	IFDEBUG(D_CONN)
		printf("tpip_route: dst is x%x\n", *dst);
	ENDDEBUG

D 2
	ro = &iproute;
	bzero((caddr_t)ro, sizeof (*ro));
	dst_in = (struct sockaddr_in *)&ro->ro_dst;
	dst_in->sin_family = AF_INET;
	dst_in->sin_addr = *dst;
E 2
I 2
	bzero((caddr_t)sin, sizeof (*sin));
	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
	sin->sin_addr = *dst;
E 2

D 2
	ia = (struct in_ifaddr *)ifa_ifwithdstaddr(dst_in);
E 2
I 2
	ia = ifa_ifwithdstaddr((struct sockaddr *)sin);
E 2
	if (ia == 0)
D 2
		ia = in_iaonnetof(in_netof(dst_in));
E 2
I 2
		ia = ifa_ifwithnet((struct sockaddr *)sin);
E 2
	if (ia != 0) {
D 2
		ifp = ia->ia_ifp;
E 2
I 2
		ifp = ia->ifa_ifp;
E 2
		IFDEBUG(D_CONN)
			printf("tpip_route: ifp from ia:0x%x\n", ia);
		ENDDEBUG
	} else {
D 2
		rtalloc(ro);
		if (ro->ro_rt != 0) {
			ifp = ro->ro_rt->rt_ifp;
E 2
I 2
		rt = rtalloc1((struct sockaddr *)sin, 0);
		if (rt != 0) {
			ifp = rt->rt_ifp;
E 2
			IFDEBUG(D_CONN)
D 2
				printf("tpip_route: ifp from route:0x%x ro_rt 0x%x\n", ro,
					ro->ro_rt);
E 2
I 2
				printf("tpip_route: ifp from rentry: 0x%x\n", rt);
E 2
			ENDDEBUG
D 2
			rtfree(ro->ro_rt);
E 2
I 2
			rtfree(rt);
E 2
		}
	}
	IFDEBUG(D_CONN)
		printf("tpip_route: returning 0x%x\n", ifp);
		if (ifp)
			printf("tpip_route: if name %s unit 0x%x, mtu 0x%x\n", 
				ifp->if_name, ifp->if_unit, ifp->if_mtu);
	ENDDEBUG
	return ifp;
}

E 10
#endif INET
E 12
I 12
#endif /* ARGO_DEBUG */
#endif /* INET */
E 12
E 1
