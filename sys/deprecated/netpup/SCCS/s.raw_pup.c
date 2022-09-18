h27899
s 00006/00006/00106
d D 6.2 84/08/29 15:33:06 bloom 22 21
c Change includes.  No more ../h
e
s 00000/00000/00112
d D 6.1 83/07/29 07:16:36 sam 21 20
c 4.2 distribution
e
s 00001/00001/00111
d D 4.20 83/06/30 12:11:38 sam 20 19
c checksum needs byte swapping since it's done in kernel
e
s 00034/00009/00078
d D 4.19 83/06/30 01:23:01 sam 19 18
c seems to work?
e
s 00002/00002/00085
d D 4.18 83/06/13 23:03:21 sam 18 17
c lint
e
s 00035/00027/00052
d D 4.17 83/05/30 18:37:09 sam 17 16
c attempt to make it work in agreement with reality
e
s 00004/00002/00075
d D 4.16 83/02/10 22:14:47 sam 16 15
c remove /usr/include dependencies
e
s 00002/00002/00075
d D 4.15 82/10/20 03:14:05 root 15 14
c lint
e
s 00001/00003/00076
d D 4.14 82/10/09 05:45:06 wnj 14 13
c localize header files
e
s 00001/00001/00078
d D 4.13 82/06/26 22:02:27 sam 13 12
c use <errno.h>
e
s 00000/00001/00079
d D 4.12 82/06/20 00:55:02 sam 12 11
c purge COUNT stuff now that we can use gprof
e
s 00028/00015/00052
d D 4.11 82/04/10 23:41:38 sam 11 10
c purge so_addr from socket structure and start cleaning up raw code
e
s 00004/00001/00063
d D 4.10 82/04/04 13:45:36 root 10 9
c byte swap length; call ifp->if_output, not enoutput
e
s 00002/00011/00062
d D 4.9 82/03/28 14:23:23 sam 9 8
c convert interfaces to sockaddr's and add hooks for routing
e
s 00008/00013/00065
d D 4.8 82/03/13 12:52:35 sam 8 7
c lint
e
s 00001/00001/00077
d D 4.7 82/03/10 11:23:29 root 7 6
c fix spelling mistake
e
s 00005/00004/00073
d D 4.6 82/03/05 14:07:09 wnj 6 5
c minor fixes
e
s 00001/00001/00076
d D 4.5 82/03/05 10:20:27 root 5 4
c move location of errno.h
e
s 00007/00072/00070
d D 4.4 82/03/03 11:04:14 sam 4 3
c cleanup raw pup interface
e
s 00007/00007/00135
d D 4.3 82/02/15 11:07:44 root 3 2
c change names to be more "raw"
e
s 00005/00003/00137
d D 4.2 82/02/02 19:45:16 sam 2 1
c bring up to date with raw stuff
e
s 00140/00000/00000
d D 4.1 82/02/02 19:42:41 sam 1 0
c date and time created 82/02/02 19:42:41 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

D 22
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/socketvar.h"
I 16
#include "../h/errno.h"
E 22
I 22
#include "param.h"
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
#include "socketvar.h"
#include "errno.h"
E 22

#include "../net/if.h"
I 19
#include "../net/route.h"
#include "../net/raw_cb.h"
E 19

E 16
D 14
#include "../net/in.h"
#include "../net/in_systm.h"
#include "../net/pup.h"
E 14
I 14
#include "../netpup/pup.h"
E 14
D 19
#include "../net/raw_cb.h"
E 19
I 6
D 16
#include "../net/if.h"
E 6
D 5
#include "/usr/include/errno.h"
E 5
I 5
D 13
#include "../errno.h"
E 13
I 13
#include <errno.h>
E 16
E 13
E 5

/*
 * Raw PUP protocol interface.
 */

I 19
struct	sockaddr_pup pupsrc = { AF_PUP };
struct	sockaddr_pup pupdst = { AF_PUP };
struct	sockproto pupproto = { PF_PUP };
E 19
D 2
static struct sockaddr_pup pupaddr = { AF_PUP };
E 2
I 2
D 4
static struct sockaddr_pup pupsrc = { AF_PUP };
static struct sockaddr_pup pupdst = { AF_PUP };
E 2
static struct sockproto pupproto = { PF_PUP };

/*
 * Setup generic address and protocol structures
 * for raw_input routine, then pass them along with
 * mbuf chain.
 */
D 3
rawpup_input(m)
E 3
I 3
rpup_input(m)
E 3
	struct mbuf *m;
{
	register struct pup_header *pup = mtod(m, struct pup_header *);

COUNT(RAWPUP_INPUT);
	pupproto.sp_protocol = pup->pup_type;
D 2
	pupaddr.spup_addr = pup->pup_daddr;
	raw_input(m, pupproto, pupaddr);
E 2
I 2
	pupdst.spup_addr = pup->pup_daddr;
	pupsrc.spup_addr = pup->pup_saddr;
	raw_input(m, &pupproto, &pupdst, &pupsrc);
E 2
}

E 4
D 9
/*ARGSUSED*/
D 3
rawpup_ctlinput(m)
E 3
I 3
rpup_ctlinput(m)
E 3
	struct mbuf *m;
{
D 3
COUNT(RAWPUP_CTLINPUT);
E 3
I 3
COUNT(RPUP_CTLINPUT);
E 3
}

E 9
/*
I 19
 * Raw PUP input.
 */
rpup_input(m)
	struct mbuf *m;
{
	register struct pup_header *pup = mtod(m, struct pup_header *);

	pupproto.sp_protocol = pup->pup_type;
	bcopy((caddr_t)&pup->pup_dnet, (caddr_t)&pupdst.spup_net,
	    sizeof (struct pupport));
	bcopy((caddr_t)&pup->pup_snet, (caddr_t)&pupsrc.spup_net,
	    sizeof (struct pupport));
	raw_input(m, &pupproto, (struct sockaddr *)&pupsrc,
	  (struct sockaddr *)&pupdst);
}

/*
E 19
 * Encapsulate packet in PUP header which is supplied by the
 * user.  This is done to allow user to specify PUP identifier.
 */
D 3
rawpup_output(m0, so)
E 3
I 3
D 6
rpup_output(m0, so)
E 3
	struct mbuf *m0;
E 6
I 6
rpup_output(m, so)
	register struct mbuf *m;
E 6
	struct socket *so;
{
	register struct rawcb *rp = sotorawcb(so);
	register struct pup_header *pup;
D 11
	int len;
E 11
I 11
	int len, error = 0;
E 11
D 17
	struct mbuf *n;
E 17
I 17
	register struct mbuf *n, *last;
E 17
D 11
	struct sockaddr_pup *spup;
E 11
I 11
	struct sockaddr_pup *dst;
E 11
I 8
D 9
	struct in_addr in;
E 9
E 8
I 4
	struct ifnet *ifp;
I 17
D 19
	u_short *pchecksum;
E 19
I 19
	u_short *pc;
E 19
E 17
E 4

D 3
COUNT(RAWPUP_OUTPUT);
E 3
I 3
D 12
COUNT(RPUP_OUTPUT);
E 12
E 3
	/*
	 * Verify user has supplied necessary space
	 * for the header and check parameters in it.
	 */
	if ((m->m_off > MMAXOFF || m->m_len < sizeof(struct pup_header)) &&
D 6
	    (m = m_pullup(m, sizeof(struct pup_header)) == 0) {
E 6
I 6
D 11
	    (m = m_pullup(m, sizeof(struct pup_header))) == 0)
E 11
I 11
	    (m = m_pullup(m, sizeof(struct pup_header))) == 0) {
D 17
		error = EMSGSIZE;	/* XXX */
E 17
I 17
		error = EINVAL;
E 17
E 11
E 6
		goto bad;
I 11
	}
E 11
	pup = mtod(m, struct pup_header *);
D 11
	if (pup->pup_type == 0)
E 11
I 11
D 17
	if (pup->pup_type == 0) {
		error = EPERM;		/* XXX */
E 17
I 17
	if (pup->pup_type == 0 || (pup->pup_tcontrol &~ PUP_TRACE)) {
		error = EINVAL;
E 17
E 11
		goto bad;
D 11
	if (pup->pup_tcontrol && (pup->pup_tcontrol & ~PUP_TRACE))
E 11
I 11
	}
D 17
	if (pup->pup_tcontrol && (pup->pup_tcontrol & ~PUP_TRACE)) {
		error = EPERM;		/* XXX */
E 17
I 17
	for (len = 0, n = last = m; n; last = n, n = n->m_next)
		len += n->m_len;
	/* assume user leaves space for checksum */
	if ((len & 1) || len < MINPUPSIZ || len > MAXPUPSIZ) {
		error = EMSGSIZE;
E 17
E 11
		goto bad;
I 11
	}
E 11
D 17
	for (len = 0, n = m; n; n = n->m_next)
		len += n->m_len;
	pup->pup_length = len;
I 10
D 15
#if vax || pdp11
E 15
I 15
#if vax || pdp11 || ns16032
E 15
	pup->pup_length = htons(pup->pup_length);
#endif
E 10
D 8
	spup = (struct sockaddr_pup *)&rp->rcb_addr;
	pup->pup_dport = spup->spup_addr;

	/*
	 * Insure proper source address is included.
	 */
E 8
D 6
	spup = (struct sockadrr_pup *)rp->rcb_socket->so_addr;
E 6
I 6
D 7
	spup = (struct sockadrr_pup *)&(rp->rcb_socket->so_addr);
E 7
I 7
D 11
	spup = (struct sockaddr_pup *)&(rp->rcb_socket->so_addr);
E 7
E 6
	pup->pup_sport = spup->spup_addr;
	/* for now, assume user generates PUP checksum. */
I 8
	spup = (struct sockaddr_pup *)&rp->rcb_addr;
	pup->pup_dport = spup->spup_addr;
E 8

E 11
I 11
	/* assume user generates PUP checksum. */
E 17
I 17
D 18
	pup->pup_length = htons(len);
E 18
I 18
	pup->pup_length = htons((u_short)len);
E 18
E 17
	dst = (struct sockaddr_pup *)&rp->rcb_faddr;
D 17
	pup->pup_dport = dst->spup_addr;
E 11
D 4
	if (rp->rcb_pcb == 0)			/* XXX */
		panic("rawpup_output");
E 4
I 4
D 8
	ifp = if_ifonnetof(&rp->rcb_addr);
	if (ifp == 0) {
		ifp = if_gatewayfor(&rp->rcb_addr);
		if (ifp == 0)
			goto bad;
	}
E 4
	return (enoutput((struct ifnet *)rp->rcb_pcb, m, PF_PUP));
E 8
I 8
D 9
	in.s_net = spup->spup_addr.pp_net;
	ifp = if_ifonnetof(in);
E 9
I 9
D 15
	ifp = if_ifonnetof(pup->pup_dnet);
E 15
I 15
	ifp = if_ifonnetof((int)pup->pup_dnet);
E 15
E 9
D 11
	if (ifp == 0)
		goto bad;
D 9
	return (enoutput(ifp, m, PF_PUP));
E 9
I 9
D 10
	return (enoutput(ifp, m, (struct sockaddr *)spup));
E 10
I 10
	return ((*ifp->if_output)(ifp, m, (struct sockaddr *)spup));
E 11
I 11
	if (ifp) {
		if (rp->rcb_flags & RAW_LADDR) {
			register struct sockaddr_pup *src;
E 17
I 17
D 19
	bcopy((caddr_t)dst->spup_net, (caddr_t)pup->pup_dnet,
E 19
I 19
	bcopy((caddr_t)&dst->spup_net, (caddr_t)&pup->pup_dnet,
E 19
	    sizeof (struct pupport));
D 18
	ifp = if_ifonnetof((u_int)pup->pup_dnet);
E 18
I 18
D 19
	ifp = if_ifonnetof((int)(unsigned)pup->pup_dnet);
E 19
I 19
	if (rp->rcb_route.ro_rt == 0)
		ifp = if_ifonnetof(dst->spup_net);
	else {
		rp->rcb_route.ro_rt->rt_use++;
		ifp = rp->rcb_route.ro_rt->rt_ifp;
	}
E 19
E 18
	if (ifp == 0) {
		error = ENETUNREACH;
		goto bad;
	}
	if (rp->rcb_flags & RAW_LADDR) {
		register struct sockaddr_pup *src;
E 17
E 11
E 10
E 9
E 8

I 11
D 17
			src = (struct sockaddr_pup *)&rp->rcb_laddr;
			pup->pup_sport = src->spup_addr;
		} else {
			pup->pup_snet = ifp->if_net;
			pup->pup_shost = ifp->if_host[0];
			/* socket is specified by user */
		}
		return ((*ifp->if_output)(ifp, m, (struct sockaddr *)dst));
E 17
I 17
		src = (struct sockaddr_pup *)&rp->rcb_laddr;
D 19
		bcopy((caddr_t)src->spup_net, (caddr_t)pup->pup_snet,
E 19
I 19
		bcopy((caddr_t)&src->spup_net, (caddr_t)&pup->pup_snet,
E 19
		    sizeof (struct pupport));
	} else {
		pup->pup_snet = ifp->if_net;
		pup->pup_shost = ifp->if_host[0];
		/* socket is specified by user */
E 17
	}
D 17
	error = ENETUNREACH;
E 17
I 17
	/*
	 * Fill in checksum unless user indicates none should be specified.
	 */
D 19
	pchecksum =
	    (u_short *)(mtod(last, caddr_t) + last->m_len - sizeof (short));
	if (*pchecksum != PUP_NOCKSUM)
		*pchecksum = pup_cksum(m, len - sizeof (short));
E 19
I 19
	pc = (u_short *)(mtod(last, caddr_t) + last->m_len - sizeof (short));
	if (*pc != PUP_NOCKSUM)
D 20
		*pc = pup_cksum(m, len - sizeof (short));
E 20
I 20
		*pc = htons((u_short)pup_cksum(m, len - sizeof (short)));
E 20
E 19
	return ((*ifp->if_output)(ifp, m, (struct sockaddr *)dst));
E 17
E 11
bad:
	m_freem(m);
D 11
	return (0);
E 11
I 11
	return (error);
E 11
D 4
}

/*
 * Intercept connects and sends to verify interface
 * exists for destination address.  Disconnects are
 * also looked at to insure pointer is invalidated.
 */
D 3
rawpup_usrreq(so, req, m, addr)
E 3
I 3
rpup_usrreq(so, req, m, addr)
E 3
	struct socket *so;
	int req;
	struct mbuf *m;
	caddr_t addr;
{
	register struct rawcb *rp = sotorawcb(so);

D 3
COUNT(RAWPUP_USRREQ);
E 3
I 3
COUNT(RPUP_USRREQ);
E 3
	if (rp == 0 && req != PRU_ATTACH)
		return (EINVAL);

	switch (req) {

	/*
	 * Verify address has an interface to go with it
	 * and record information for use in output routine.
	 */
	case PRU_SEND:
	case PRU_CONNECT: {
		register struct sockaddr_pup *spup;
		register struct ifnet *ifp;

		spup = (struct sockaddr_pup *)addr;
		ifp = if_ifonnetof(spup->spup_addr);
		if (ifp == 0) {
			ifp = if_gatewayfor(spup->spup_addr);
			if (ifp == 0)
				return (EADDRNOTAVAIL);	/* XXX */
		}
		rp->rcb_pcb = (caddr_t)ifp;
		break;
		}

	case PRU_DISCONNECT:
		rp->rcb_pcb = 0;
		break;
	
	case PRU_CONTROL:
		return (EOPNOTSUPP);
	}
	return (raw_usrreq(so, req, m, addr));
E 4
}
E 1
