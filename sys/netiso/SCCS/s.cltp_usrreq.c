h55242
s 00002/00002/00377
d D 8.1 93/06/10 23:18:55 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00016/00363
d D 7.9 92/10/11 12:21:41 bostic 9 8
c make kernel includes standard
e
s 00000/00001/00379
d D 7.8 91/07/18 18:46:36 sklower 8 7
c remove extraneous line
e
s 00008/00009/00372
d D 7.7 91/07/18 18:41:30 sklower 7 6
c make this not depend on tp_iso.c
e
s 00000/00001/00381
d D 7.6 91/06/27 22:31:40 sklower 6 5
c make compile under both new and old vm systems
e
s 00001/00011/00381
d D 7.5 90/06/28 21:44:01 bostic 5 4
c new copyright notice
e
s 00004/00001/00388
d D 7.4 90/05/14 16:05:07 sklower 4 3
c new conventions for obtaining freeing ancillary data
e
s 00003/00007/00386
d D 7.3 90/04/05 11:02:12 sklower 3 2
c access rights made special case of control info
e
s 00018/00009/00375
d D 7.2 90/01/16 23:15:21 sklower 2 1
c checkpoint for initial shipment to NIST
e
s 00384/00000/00000
d D 7.1 89/11/15 19:41:06 sklower 1 0
c date and time created 89/11/15 19:41:06 by sklower
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 5
 * Redistribution and use in source and binary forms are permitted
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

#ifndef CLTPOVAL_SRC /* XXX -- till files gets changed */
D 9
#include "param.h"
D 6
#include "user.h"
E 6
#include "malloc.h"
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
#include "stat.h"
E 9
I 9
#include <sys/param.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/stat.h>
E 9

D 9
#include "../net/if.h"
#include "../net/route.h"
E 9
I 9
#include <net/if.h>
#include <net/route.h>
E 9

D 9
#include "argo_debug.h"
#include "iso.h"
#include "iso_pcb.h"
#include "iso_var.h"
#include "clnp.h"
#include "cltp_var.h"
E 9
I 9
#include <netiso/argo_debug.h>
#include <netiso/iso.h>
#include <netiso/iso_pcb.h>
#include <netiso/iso_var.h>
#include <netiso/clnp.h>
#include <netiso/cltp_var.h>
E 9
#endif

/*
 * CLTP protocol implementation.
 * Per ISO 8602, December, 1987.
 */
cltp_init()
{

	cltb.isop_next = cltb.isop_prev = &cltb;
}

int cltp_cksum = 1;


/* ARGUSED */
cltp_input(m0, srcsa, dstsa, cons_channel, output)
	struct mbuf *m0;
	struct sockaddr *srcsa, *dstsa;
	u_int cons_channel;
	int (*output)();
{
	register struct isopcb *isop;
	register struct mbuf *m = m0;
	register u_char *up = mtod(m, u_char *);
	register struct sockaddr_iso *src = (struct sockaddr_iso *)srcsa;
	int len, hdrlen = *up + 1, dlen = 0;
	u_char *uplim = up + hdrlen;
	caddr_t dtsap;

	for (len = 0; m; m = m->m_next)
		len += m->m_len;
	up += 2; /* skip header */
	while (up < uplim) switch (*up) { /* process options */
	case CLTPOVAL_SRC:
		src->siso_tlen = up[1];
		src->siso_len = up[1] + TSEL(src) - (caddr_t)src;
		if (src->siso_len < sizeof(*src))
			src->siso_len = sizeof(*src);
		else if (src->siso_len > sizeof(*src)) {
			MGET(m, M_DONTWAIT, MT_SONAME);
			if (m == 0)
				goto bad;
			m->m_len = src->siso_len;
			src = mtod(m, struct sockaddr_iso *);
			bcopy((caddr_t)srcsa, (caddr_t)src, srcsa->sa_len);
		}
		bcopy((caddr_t)up + 2, TSEL(src), up[1]);
		up += 2 + src->siso_tlen;
		continue;
	
	case CLTPOVAL_DST:
		dtsap = 2 + (caddr_t)up;
		dlen = up[1];
		up += 2 + dlen;
		continue;

	case CLTPOVAL_CSM:
D 2
		if (iso_check_csum(m0, len))
E 2
I 2
		if (iso_check_csum(m0, len)) {
			cltpstat.cltps_badsum++;
E 2
			goto bad;
I 2
		}
E 2
		up += 4;
I 2
		continue;
E 2

	default:
		printf("clts: unknown option (%x)\n", up[0]);
I 2
		cltpstat.cltps_hdrops++;
E 2
		goto bad;
	}
	if (dlen == 0 || src->siso_tlen == 0)
		goto bad;
	for (isop = cltb.isop_next;; isop = isop->isop_next) {
D 2
		if (isop == &cltb)
E 2
I 2
		if (isop == &cltb) {
			cltpstat.cltps_noport++;
E 2
			goto bad;
I 2
		}
E 2
		if (isop->isop_laddr &&
		    bcmp(TSEL(isop->isop_laddr), dtsap, dlen) == 0)
			break;
	}
	m = m0;
D 2
	m->m_len += hdrlen;
E 2
I 2
	m->m_len -= hdrlen;
	m->m_data += hdrlen;
E 2
	if (sbappendaddr(&isop->isop_socket->so_rcv, (struct sockaddr *)src,
	    m, (struct mbuf *)0) == 0)
		goto bad;
I 2
	cltpstat.cltps_ipackets++;
E 2
	sorwakeup(isop->isop_socket);
	m0 = 0;
bad:
	if (src != (struct sockaddr_iso *)srcsa)
		m_freem(dtom(src));
	if (m0)
		m_freem(m0);
D 2
	return;
E 2
I 2
	return 0;
E 2
}

/*
 * Notify a cltp user of an asynchronous error;
 * just wake up so that he can collect error status.
 */
cltp_notify(isop)
	register struct isopcb *isop;
{

	sorwakeup(isop->isop_socket);
	sowwakeup(isop->isop_socket);
}

cltp_ctlinput(cmd, sa)
	int cmd;
	struct sockaddr *sa;
{
	extern u_char inetctlerrmap[];
	struct sockaddr_iso *siso;
	int iso_rtchange();

	if ((unsigned)cmd > PRC_NCMDS)
		return;
	if (sa->sa_family != AF_ISO && sa->sa_family != AF_CCITT)
		return;
	siso = (struct sockaddr_iso *)sa;
	if (siso == 0 || siso->siso_nlen == 0)
		return;

	switch (cmd) {
	case PRC_ROUTEDEAD:
	case PRC_REDIRECT_NET:
	case PRC_REDIRECT_HOST:
	case PRC_REDIRECT_TOSNET:
	case PRC_REDIRECT_TOSHOST:
		iso_pcbnotify(&cltb, siso,
				(int)inetctlerrmap[cmd], iso_rtchange);
		break;

	default:
		if (inetctlerrmap[cmd] == 0)
			return;		/* XXX */
		iso_pcbnotify(&cltb, siso, (int)inetctlerrmap[cmd],
			cltp_notify);
	}
}

cltp_output(isop, m)
	register struct isopcb *isop;
	register struct mbuf *m;
{
	register int len;
	register struct sockaddr_iso *siso;
	int hdrlen, error = 0, docsum;
	register u_char *up;

	if (isop->isop_laddr == 0 || isop->isop_faddr == 0) {
		error = ENOTCONN;
		goto bad;
	}
	/*
	 * Calculate data length and get a mbuf for CLTP header.
	 */
	hdrlen = 2 + 2 + isop->isop_laddr->siso_tlen
		   + 2 + isop->isop_faddr->siso_tlen;
	if (docsum = /*isop->isop_flags & CLNP_NO_CKSUM*/ cltp_cksum)
		hdrlen += 4;
	M_PREPEND(m, hdrlen, M_WAIT);
	len = m->m_pkthdr.len;
	/*
	 * Fill in mbuf with extended CLTP header
	 */
	up = mtod(m, u_char *);
D 2
	up[0] = UD_TPDU_type;
	up[1] = hdrlen - 1;
	up[2] = CLTPOVAL_DST;
E 2
I 2
	up[0] = hdrlen - 1;
	up[1] = UD_TPDU_type;
	up[2] = CLTPOVAL_SRC;
E 2
	up[3] = (siso = isop->isop_laddr)->siso_tlen;
	up += 4;
	bcopy(TSEL(siso), (caddr_t)up, siso->siso_tlen);
	up += siso->siso_tlen;
D 2
	up[0] = CLTPOVAL_SRC;
E 2
I 2
	up[0] = CLTPOVAL_DST;
E 2
	up[1] = (siso = isop->isop_faddr)->siso_tlen;
	up += 2;
	bcopy(TSEL(siso), (caddr_t)up, siso->siso_tlen);
	/*
	 * Stuff checksum and output datagram.
	 */
	if (docsum) {
		up += siso->siso_tlen;
		up[0] = CLTPOVAL_CSM;
		up[1] = 2;
D 2
		iso_gen_cksum(m, 2 + up - mtod(m, u_char *), len);
E 2
I 2
		iso_gen_csum(m, 2 + up - mtod(m, u_char *), len);
E 2
	}
I 2
	cltpstat.cltps_opackets++;
E 2
	return (tpclnp_output(isop, m, len, !docsum));
bad:
	m_freem(m);
	return (error);
}

D 7
#ifndef TP_LOCAL
/* XXXX should go in iso.h maybe? from tp_param.h, in any case */
#define		TP_LOCAL				22
#define		TP_FOREIGN				33
#endif

E 7
u_long	cltp_sendspace = 9216;		/* really max datagram size */
u_long	cltp_recvspace = 40 * (1024 + sizeof(struct sockaddr_iso));
					/* 40 1K datagrams */


/*ARGSUSED*/
D 3
cltp_usrreq(so, req, m, nam, rights, control)
E 3
I 3
cltp_usrreq(so, req, m, nam, control)
E 3
	struct socket *so;
	int req;
D 3
	struct mbuf *m, *nam, *rights, *control;
E 3
I 3
	struct mbuf *m, *nam, *control;
E 3
{
D 7
	struct isopcb *isop = sotoisopcb(so);
E 7
I 7
	register struct isopcb *isop = sotoisopcb(so);
D 8
	register struct sockaddr_iso *siso;
E 8
E 7
	int s, error = 0;

	if (req == PRU_CONTROL)
		return (iso_control(so, (int)m, (caddr_t)nam,
D 3
			(struct ifnet *)rights));
	if (rights && rights->m_len) {
		error = EINVAL;
		goto release;
	}
E 3
I 3
			(struct ifnet *)control));
E 3
D 4
	if (isop == NULL && req != PRU_ATTACH) {
E 4
I 4
	if ((isop == NULL && req != PRU_ATTACH) ||
	    (control && control->m_len)) {
E 4
		error = EINVAL;
		goto release;
	}
	switch (req) {

	case PRU_ATTACH:
		if (isop != NULL) {
			error = EINVAL;
			break;
		}
		error = iso_pcballoc(so, &cltb);
		if (error)
			break;
		error = soreserve(so, cltp_sendspace, cltp_recvspace);
		if (error)
			break;
		break;

	case PRU_DETACH:
		iso_pcbdetach(isop);
		break;

	case PRU_BIND:
		error = iso_pcbbind(isop, nam);
		break;

	case PRU_LISTEN:
		error = EOPNOTSUPP;
		break;

	case PRU_CONNECT:
		if (isop->isop_faddr) {
			error = EISCONN;
			break;
		}
		error = iso_pcbconnect(isop, nam);
		if (error == 0)
			soisconnected(so);
		break;

	case PRU_CONNECT2:
		error = EOPNOTSUPP;
		break;

	case PRU_ACCEPT:
		error = EOPNOTSUPP;
		break;

	case PRU_DISCONNECT:
		if (isop->isop_faddr == 0) {
			error = ENOTCONN;
			break;
		}
		iso_pcbdisconnect(isop);
		so->so_state &= ~SS_ISCONNECTED;		/* XXX */
		break;

	case PRU_SHUTDOWN:
		socantsendmore(so);
		break;

	case PRU_SEND:
		if (nam) {
			if (isop->isop_faddr) {
				error = EISCONN;
				break;
			}
			/*
			 * Must block input while temporarily connected.
			 */
			s = splnet();
			error = iso_pcbconnect(isop, nam);
			if (error) {
				splx(s);
				break;
			}
		} else {
			if (isop->isop_faddr == 0) {
				error = ENOTCONN;
				break;
			}
		}
		error = cltp_output(isop, m);
		m = 0;
		if (nam) {
			iso_pcbdisconnect(isop);
			splx(s);
		}
		break;

	case PRU_ABORT:
		soisdisconnected(so);
		iso_pcbdetach(isop);
		break;

	case PRU_SOCKADDR:
D 7
		iso_getnetaddr(isop, nam, TP_LOCAL);
E 7
I 7
		if (isop->isop_laddr)
			bcopy((caddr_t)isop->isop_laddr, mtod(m, caddr_t),
				nam->m_len = isop->isop_laddr->siso_len);
E 7
		break;

	case PRU_PEERADDR:
D 7
		iso_getnetaddr(isop, nam, TP_FOREIGN);
E 7
I 7
		if (isop->isop_faddr)
			bcopy((caddr_t)isop->isop_faddr, mtod(m, caddr_t),
				nam->m_len = isop->isop_faddr->siso_len);
E 7
		break;

	case PRU_SENSE:
		/*
		 * stat: don't bother with a blocksize.
		 */
		return (0);

	case PRU_SENDOOB:
	case PRU_FASTTIMO:
	case PRU_SLOWTIMO:
	case PRU_PROTORCV:
	case PRU_PROTOSEND:
		error =  EOPNOTSUPP;
		break;

	case PRU_RCVD:
	case PRU_RCVOOB:
		return (EOPNOTSUPP);	/* do not free mbuf's */

	default:
		panic("cltp_usrreq");
	}
release:
I 4
	if (control != NULL)
		m_freem(control);
E 4
	if (m != NULL)
		m_freem(m);
	return (error);
}
E 1
