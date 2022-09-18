h58419
s 00001/00000/01039
d D 8.3 95/03/20 12:31:17 sklower 27 26
c when esis_shoutput is constructing a packet that overflows the first mbuf,
c the EXTEND_PACKET macro did not set m_len on the new mbuf, which confused esis-insert_addr.
e
s 00004/00002/01035
d D 8.2 95/02/09 10:42:41 cgd 26 25
c casts to quiet compiler.
e
s 00002/00002/01035
d D 8.1 93/06/10 23:19:10 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/01034
d D 7.24 93/06/04 17:02:26 sklower 24 23
c fix #endif something to #endif /* something */
e
s 00002/00001/01035
d D 7.23 93/04/06 15:18:26 sklower 23 22
c shut up complaints about 1st arg to timeout; declare esis_config() and snpac_age() as returning void
e
s 00022/00023/01014
d D 7.22 92/10/11 12:21:43 bostic 22 21
c make kernel includes standard
e
s 00003/00003/01034
d D 7.21 92/02/20 14:20:54 sklower 21 20
c minor typo-level changes for consistency with new header files
e
s 00002/00002/01035
d D 7.20 92/01/07 14:25:14 sklower 20 19
c changes required by nov 92 version of socketvar.h
e
s 00003/00004/01034
d D 7.19 91/06/27 19:54:23 sklower 19 18
c common version for new and old vm
e
s 00009/00004/01029
d D 7.18 91/05/06 19:23:54 bostic 18 17
c new copyright; att/bsd/shared
e
s 00007/00002/01026
d D 7.17 91/05/02 18:54:20 sklower 17 16
c don't call x.25 output devices . . .
e
s 00001/00001/01027
d D 7.16 91/01/09 15:41:24 sklower 16 15
c changes to support esis and isis over eon
e
s 00004/00001/01024
d D 7.15 90/07/24 18:12:14 sklower 15 14
c wisconsin fixes
e
s 00016/00000/01009
d D 7.14 90/06/25 17:27:00 sklower 14 13
c add suggested es_config_timer option to ISH's
e
s 00008/00010/01001
d D 7.13 90/06/25 13:40:45 sklower 13 12
c isis_input() may be called when there are no listeners;
c so must free packet anyway.  Also, must remember more than sockbuf 
c when avoiding copying.
e
s 00005/00005/01006
d D 7.12 90/06/25 10:38:46 sklower 12 11
c forgot one critical line from isis_init();
c may eventually remove clnl_protox[] since the elements are picked out
e
s 00001/00000/01010
d D 7.11 90/06/22 17:21:42 mckusick 11 10
c need systm.h included for insque
e
s 00008/00003/01002
d D 7.10 90/06/22 16:09:54 sklower 10 9
c somehow lost change to esct.
e
s 00195/00041/00810
d D 7.9 90/06/22 15:39:21 sklower 9 8
c merge in UW isis changes; my merge is untested, but SCCS id's
c must be assigned before I leave today :-(
e
s 00155/00076/00696
d D 7.8 90/06/20 19:02:31 sklower 8 7
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00023/00020/00749
d D 7.7 90/06/09 17:39:41 sklower 7 6
c change snpa cache to fold in to routing table; this doesn't work yet;
c but checkpoint anyhow
e
s 00005/00005/00764
d D 7.6 90/04/05 11:13:39 sklower 6 5
c make rights special case of ancillary data; if_output now called with rtentry ptr.
e
s 00069/00082/00700
d D 7.5 90/01/25 18:26:13 sklower 5 4
c fixbugs in ishinput, rdinput processing, checkpoint for release
c to NIST
e
s 00002/00001/00780
d D 7.4 89/08/29 13:44:10 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00001/00781
d D 7.3 89/05/05 00:27:41 mckusick 3 2
c get rid of unneeded include's
e
s 00171/00167/00611
d D 7.2 89/04/22 11:53:45 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00778/00000/00000
d D 7.1 88/12/14 15:29:33 sklower 1 0
c date and time created 88/12/14 15:29:33 by sklower
e
u
U
t
T
I 18
/*-
D 25
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 18
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
I 4
D 18
/*	%W% (Berkeley) %G% */
E 4
#ifndef lint
static char *rcsid = "$Header: esis.c,v 4.10 88/09/15 18:57:03 hagens Exp $";
#endif
E 18

#ifdef ISO

D 2
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
#include "../h/kernel.h"
E 2
I 2
D 22
#include "types.h"
#include "param.h"
I 11
#include "systm.h"
E 11
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
D 3
#include "dir.h"
E 3
D 19
#include "user.h"
E 19
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
E 22
I 22
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/kernel.h>
E 22
D 19
#include "kernel.h"
E 19
E 2

D 22
#include "../net/if.h"
I 8
#include "../net/if_dl.h"
E 8
#include "../net/route.h"
I 9
#include "../net/raw_cb.h"
E 22
I 22
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <net/raw_cb.h>
E 22
E 9

D 2
#include "../netiso/iso.h"
#include "../netiso/iso_pcb.h"
#include "../netiso/iso_var.h"
#include "../netiso/iso_snpac.h"
#include "../netiso/clnl.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
#include "../netiso/esis.h"
E 2
I 2
D 22
#include "iso.h"
#include "iso_pcb.h"
#include "iso_var.h"
#include "iso_snpac.h"
#include "clnl.h"
#include "clnp.h"
#include "clnp_stat.h"
D 4
#include "argo_debug.h"
E 4
#include "esis.h"
I 4
#include "argo_debug.h"
I 19
#include "kernel.h"
E 22
I 22
#include <netiso/iso.h>
#include <netiso/iso_pcb.h>
#include <netiso/iso_var.h>
#include <netiso/iso_snpac.h>
#include <netiso/clnl.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/esis.h>
#include <netiso/argo_debug.h>
E 22
E 19
E 4
E 2

/*
 *	Global variables to esis implementation
 *
 *	esis_holding_time - the holding time (sec) parameter for outgoing pdus
 *	esis_config_time  - the frequency (sec) that hellos are generated
I 9
 *	esis_esconfig_time - suggested es configuration time placed in the
 *						ish.
E 9
 *
 */
D 9
struct isopcb	esis_pcb;
E 9
I 9
struct rawcb	esis_pcb;
I 19
D 23
int				esis_config(), snpac_age();
E 23
I 23
void				esis_config(), snpac_age();
E 23
E 19
E 9
int				esis_sendspace = 2048;
int				esis_recvspace = 2048;
short			esis_holding_time = ESIS_HT;
short			esis_config_time = ESIS_CONFIG;
I 9
short			esis_esconfig_time = ESIS_CONFIG;
E 9
extern int		iso_systype;
I 9
struct sockaddr_dl	esis_dl = { sizeof(esis_dl), AF_LINK };
E 9
D 8
extern struct snpa_cache	all_es, all_is;
E 8
I 8
extern char		all_es_snpa[], all_is_snpa[];
E 8

D 2
#define EXTEND_PACKET(m, mhdr, len, cp)\
E 2
I 2
#define EXTEND_PACKET(m, mhdr, cp)\
E 2
	if (((m)->m_next = m_getclr(M_DONTWAIT, MT_HEADER)) == NULL) {\
		esis_stat.es_nomem++;\
		m_freem(mhdr);\
		return;\
	} else {\
D 2
		(m)->m_len = (len);\
E 2
		(m) = (m)->m_next;\
D 2
		(len) = 0;\
E 2
		(cp) = mtod((m), caddr_t);\
I 27
		(m)->m_len = 0;\
E 27
	}
/*
 * FUNCTION:		esis_init
 *
 * PURPOSE:			Initialize the kernel portion of esis protocol
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
esis_init()
{
	extern struct clnl_protosw clnl_protox[256];
D 12
	int esis_input();
D 9
	int snpac_age();
E 9
	int	esis_config();
I 9
	int snpac_age();
E 12
I 12
	int	esis_input(), isis_input();
D 19
	int	esis_config(), snpac_age();
E 19
E 12
E 9
#ifdef	ISO_X25ESIS
D 12
	x25esis_input();
E 12
I 12
	int	x25esis_input();
E 12
D 24
#endif	ISO_X25ESIS
E 24
I 24
#endif	/* ISO_X25ESIS */
E 24

D 9
	esis_pcb.isop_next = esis_pcb.isop_prev = &esis_pcb;
E 9
I 9
	esis_pcb.rcb_next = esis_pcb.rcb_prev = &esis_pcb;
	llinfo_llc.lc_next = llinfo_llc.lc_prev = &llinfo_llc;
E 9

D 12
	clnl_protox[ISO9542_ESIS].clnl_input = esis_input;
E 12
I 8
D 9
	llinfo_llc.lc_next = llinfo_llc.lc_prev = &llinfo_llc;
E 9
E 8
	timeout(snpac_age, (caddr_t)0, hz);
	timeout(esis_config, (caddr_t)0, hz);

I 12
	clnl_protox[ISO9542_ESIS].clnl_input = esis_input;
	clnl_protox[ISO10589_ISIS].clnl_input = isis_input;
E 12
#ifdef	ISO_X25ESIS
	clnl_protox[ISO9542X25_ESIS].clnl_input = x25esis_input;
D 24
#endif	ISO_X25ESIS
E 24
I 24
#endif	/* ISO_X25ESIS */
E 24
}

/*
 * FUNCTION:		esis_usrreq
 *
 * PURPOSE:			Handle user level esis requests
 *
 * RETURNS:			0 or appropriate errno
 *
 * SIDE EFFECTS:	
 *
D 9
 * NOTES:			This is here only so esis gets initialized.
E 9
 */
I 2
/*ARGSUSED*/
E 2
D 6
esis_usrreq(so, req, m, nam, rights)
E 6
I 6
esis_usrreq(so, req, m, nam, control)
E 6
struct socket	*so;		/* socket: used only to get to this code */
int				req;		/* request */
struct mbuf		*m;			/* data for request */
struct mbuf		*nam;		/* optional name */
D 6
struct mbuf		*rights;	/* optional rights */
E 6
I 6
struct mbuf		*control;	/* optional control */
E 6
{
I 9
	struct rawcb *rp = sotorawcb(so);
	int error = 0;

D 19
	if (suser(u.u_cred, &u.u_acflag)) {
E 19
I 19
	if ((so->so_state & SS_PRIV) == 0) {
E 19
		error = EACCES;
		goto release;
	}
	if (rp == NULL && req != PRU_ATTACH) {
		error = EINVAL;
		goto release;
	}

	switch (req) {
	case PRU_ATTACH:
		if (rp != NULL) {
			error = EINVAL;
			break;
		}
		MALLOC(rp, struct rawcb *, sizeof(*rp), M_PCB, M_WAITOK);
		if (so->so_pcb = (caddr_t)rp) {
			bzero(so->so_pcb, sizeof(*rp));
			insque(rp, &esis_pcb);
I 15
			rp->rcb_socket = so;
E 15
			error = soreserve(so, esis_sendspace, esis_recvspace);
		} else
			error = ENOBUFS;
		break;

	case PRU_SEND:
		if (nam == NULL) {
			error = EINVAL;
			break;
		}
		/* error checking here */
		error = isis_output(mtod(nam,struct sockaddr_dl *), m);
		m = NULL;
		break;

	case PRU_DETACH:
		raw_detach(rp);
		break;

	case PRU_SHUTDOWN:
		socantsendmore(so);
		break;

	case PRU_ABORT:
		soisdisconnected(so);
		raw_detach(rp);
		break;

	case PRU_SENSE:
		return (0);

	default:
		return (EOPNOTSUPP);
	}
release:
E 9
	if (m != NULL)
		m_freem(m);

D 9
	return(EOPNOTSUPP);
E 9
I 9
	return (error);
E 9
}

/*
 * FUNCTION:		esis_input
 *
 * PURPOSE:			Process an incoming esis packet
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
esis_input(m0, shp)
struct mbuf		*m0;		/* ptr to first mbuf of pkt */
struct snpa_hdr	*shp;	/* subnetwork header */
{
D 2
	struct isopcb		*isop;
E 2
D 9
	struct esis_fixed	*pdu = mtod(m0, struct esis_fixed *);
E 9
I 9
	register struct esis_fixed	*pdu = mtod(m0, struct esis_fixed *);
E 9
I 2
	register int type;
E 2

D 9
	IFDEBUG(D_ESISINPUT)
		int i;

		printf("esis_input: pdu on ifp x%x (%s%d): from:", shp->snh_ifp, 
			shp->snh_ifp->if_name, shp->snh_ifp->if_unit);
		for (i=0; i<6; i++)
			printf("%x%c", shp->snh_shost[i]&0xff, (i<5) ? ':' : ' ');
		printf(" to:");
		for (i=0; i<6; i++)
			printf("%x%c", shp->snh_dhost[i]&0xff, (i<5) ? ':' : ' ');
		printf("\n");
	ENDDEBUG

E 9
	/*
	 *	check checksum if necessary
	 */
D 2
	if (ESIS_CKSUM_REQUIRED(pdu) && iso_check_csum(m0, pdu->esis_hdr_len)) {
E 2
I 2
	if (ESIS_CKSUM_REQUIRED(pdu) && iso_check_csum(m0, (int)pdu->esis_hdr_len)) {
E 2
		esis_stat.es_badcsum++;
		goto bad;
	}

	/* check version */
	if (pdu->esis_vers != ESIS_VERSION) {
		esis_stat.es_badvers++;
		goto bad;
	}
D 9

E 9
D 2
	switch(pdu->esis_type) {
E 2
I 2
	type = pdu->esis_type & 0x1f;
	switch (type) {
E 2
		case ESIS_ESH:
			esis_eshinput(m0, shp);
D 9
			return;
E 9
I 9
			break;
E 9

		case ESIS_ISH:
			esis_ishinput(m0, shp);
D 9
			return;
E 9
I 9
			break;
E 9

		case ESIS_RD:
			esis_rdinput(m0, shp);
D 9
			return;
E 9
I 9
			break;
E 9

D 9
		default: {
E 9
I 9
		default:
E 9
			esis_stat.es_badtype++;
D 9
			goto bad;
		}
E 9
	}

bad:
D 9
	m_freem(m0);
E 9
I 9
	if (esis_pcb.rcb_next != &esis_pcb)
		isis_input(m0, shp);
	else
		m_freem(m0);
E 9
}

/*
 * FUNCTION:		esis_rdoutput
 *
 * PURPOSE:			Transmit a redirect pdu
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Assumes there is enough space for fixed part of header,
 *					DA, BSNPA and NET in first mbuf.
 */
D 8
esis_rdoutput(inbound_shp, inbound_m, inbound_oidx, rd_dstnsap, nhop_sc)
E 8
I 8
esis_rdoutput(inbound_shp, inbound_m, inbound_oidx, rd_dstnsap, rt)
E 8
struct snpa_hdr		*inbound_shp;	/* snpa hdr from incoming packet */
struct mbuf			*inbound_m;		/* incoming pkt itself */
struct clnp_optidx	*inbound_oidx;	/* clnp options assoc with incoming pkt */
struct iso_addr		*rd_dstnsap;	/* ultimate destination of pkt */
D 8
struct snpa_cache	*nhop_sc;		/* snpa cache info regarding next hop of
E 8
I 8
struct rtentry		*rt;			/* snpa cache info regarding next hop of
E 8
										pkt */
{
	struct mbuf			*m, *m0;
	caddr_t				cp;
	struct esis_fixed	*pdu;
	int					len, total_len = 0;
	struct sockaddr_iso	siso;
	struct ifnet 		*ifp = inbound_shp->snh_ifp;
I 8
	struct sockaddr_dl *sdl;
	struct iso_addr *rd_gwnsap;
E 8

I 8
	if (rt->rt_flags & RTF_GATEWAY) {
		rd_gwnsap = &((struct sockaddr_iso *)rt->rt_gateway)->siso_addr;
		rt = rtalloc1(rt->rt_gateway, 0);
	} else
		rd_gwnsap = &((struct sockaddr_iso *)rt_key(rt))->siso_addr;
	if (rt == 0 || (sdl = (struct sockaddr_dl *)rt->rt_gateway) == 0 ||
		sdl->sdl_family != AF_LINK) {
		/* maybe we should have a function that you
		   could put in the iso_ifaddr structure
		   which could translate iso_addrs into snpa's
		   where there is a known mapping for that address type */
		esis_stat.es_badtype++;
		return;
	}
E 8
	esis_stat.es_rdsent++;
D 8

E 8
	IFDEBUG(D_ESISOUTPUT)
D 2
		int	i;
E 2
		printf("esis_rdoutput: ifp x%x (%s%d), ht %d, m x%x, oidx x%x\n",
			ifp, ifp->if_name, ifp->if_unit, esis_holding_time, inbound_m,
			inbound_oidx);
		printf("\tdestination: %s\n", clnp_iso_addrp(rd_dstnsap));
D 8
		printf("\tredirected toward:%s\n", clnp_iso_addrp(&nhop_sc->sc_nsap));
E 8
I 8
		printf("\tredirected toward:%s\n", clnp_iso_addrp(rd_gwnsap));
E 8
	ENDDEBUG

D 2
	if ((m0 = m = m_getclr(M_DONTWAIT, MT_HEADER)) == NULL) {
E 2
I 2
	if ((m0 = m = m_gethdr(M_DONTWAIT, MT_HEADER)) == NULL) {
E 2
		esis_stat.es_nomem++;
		return;
	}
I 2
	bzero(mtod(m, caddr_t), MHLEN);
E 2

	pdu = mtod(m, struct esis_fixed *);
D 2
	cp = (caddr_t)pdu + sizeof(struct esis_fixed);
E 2
I 2
	cp = (caddr_t)(pdu + 1); /*pointer arith.; 1st byte after header */
E 2
	len = sizeof(struct esis_fixed);

	/*
	 *	Build fixed part of header
	 */
	pdu->esis_proto_id = ISO9542_ESIS;
	pdu->esis_vers = ESIS_VERSION;
	pdu->esis_type = ESIS_RD;
	HTOC(pdu->esis_ht_msb, pdu->esis_ht_lsb, esis_holding_time);

	/* Insert destination address */
D 2
	(void) esis_insert_addr(&cp, &len, rd_dstnsap, MLEN - len);
E 2
I 2
D 7
	(void) esis_insert_addr(&cp, &len, rd_dstnsap, m);
E 7
I 7
	(void) esis_insert_addr(&cp, &len, rd_dstnsap, m, 0);
E 7
E 2

	/* Insert the snpa of better next hop */
D 8
	*cp++ = nhop_sc->sc_len;
D 2
	bcopy(nhop_sc->sc_snpa, cp, nhop_sc->sc_len);
E 2
I 2
	bcopy((caddr_t)nhop_sc->sc_snpa, cp, nhop_sc->sc_len);
E 2
	len += (nhop_sc->sc_len + 1);
E 8
I 8
	*cp++ = sdl->sdl_alen;
	bcopy(LLADDR(sdl), cp, sdl->sdl_alen);
	cp += sdl->sdl_alen;
	len += (sdl->sdl_alen + 1);
E 8

	/* 
	 *	If the next hop is not the destination, then it ought to be
	 *	an IS and it should be inserted next. Else, set the
	 *	NETL to 0
	 */
	/* PHASE2 use mask from ifp of outgoing interface */
D 8
	if (!iso_addrmatch1(rd_dstnsap, &nhop_sc->sc_nsap)) {
E 8
I 8
	if (!iso_addrmatch1(rd_dstnsap, rd_gwnsap)) {
		/* this should not happen: 
E 8
		if ((nhop_sc->sc_flags & SNPA_IS) == 0) {
D 8
			/* this should not happen */
E 8
			printf("esis_rdoutput: next hop is not dst and not an IS\n");
			m_freem(m0);
			return;
D 8
		}
D 2
		(void) esis_insert_addr(&cp, &len, &nhop_sc->sc_nsap, MLEN - len);
E 2
I 2
D 7
		(void) esis_insert_addr(&cp, &len, &nhop_sc->sc_nsap, m);
E 7
I 7
		(void) esis_insert_addr(&cp, &len, &nhop_sc->sc_nsap, m, 0);
E 8
I 8
		} */
		(void) esis_insert_addr(&cp, &len, rd_gwnsap, m, 0);
E 8
E 7
E 2
	} else {
		*cp++ = 0;	/* NETL */
		len++;
	}
I 2
	m->m_len = len;
E 2

	/*
	 *	PHASE2
	 *	If redirect is to an IS, add an address mask. The mask to be
	 *	used should be the mask present in the routing entry used to
	 *	forward the original data packet.
	 */
	
	/*
	 *	Copy Qos, priority, or security options present in original npdu
	 */
	if (inbound_oidx) {
D 8
		/* THIS CODE IS CURRENTLY UNTESTED */
E 8
I 8
		/* THIS CODE IS CURRENTLY (mostly) UNTESTED */
E 8
		int optlen = 0;
		if (inbound_oidx->cni_qos_formatp)
			optlen += (inbound_oidx->cni_qos_len + 2);
		if (inbound_oidx->cni_priorp)	/* priority option is 1 byte long */
			optlen += 3;
		if (inbound_oidx->cni_securep)
			optlen += (inbound_oidx->cni_secure_len + 2);
D 2
		if (MLEN-len < optlen) {
			total_len += len;
			EXTEND_PACKET(m, m0, len, cp);
E 2
I 2
		if (M_TRAILINGSPACE(m) < optlen) {
			EXTEND_PACKET(m, m0, cp);
			m->m_len = 0;
E 2
			/* assumes MLEN > optlen */
		}
		/* assume MLEN-len > optlen */
		/* 
		 *	When copying options, copy from ptr - 2 in order to grab
		 *	the option code and length
		 */
		if (inbound_oidx->cni_qos_formatp) {
D 2
			bcopy(inbound_m + inbound_oidx->cni_qos_formatp - 2, cp, 
				inbound_oidx->cni_qos_len + 2);
E 2
I 2
D 8
			bcopy((caddr_t)(inbound_m + inbound_oidx->cni_qos_formatp - 2), cp, 
				(unsigned)(inbound_oidx->cni_qos_len + 2));
E 2
			len += inbound_oidx->cni_qos_len + 2;
E 8
I 8
			bcopy(mtod(inbound_m, caddr_t) + inbound_oidx->cni_qos_formatp - 2,
				cp, (unsigned)(inbound_oidx->cni_qos_len + 2));
			cp += inbound_oidx->cni_qos_len + 2;
E 8
		}
		if (inbound_oidx->cni_priorp) {
D 2
			bcopy(inbound_m + inbound_oidx->cni_priorp - 2, cp, 3);
E 2
I 2
D 8
			bcopy((caddr_t)(inbound_m + inbound_oidx->cni_priorp - 2), cp, 3);
E 2
			len += 3;
E 8
I 8
			bcopy(mtod(inbound_m, caddr_t) + inbound_oidx->cni_priorp - 2,
					cp, 3);
			cp += 3;
E 8
		}
		if (inbound_oidx->cni_securep) {
D 2
			bcopy(inbound_m + inbound_oidx->cni_securep - 2, cp, 
				inbound_oidx->cni_secure_len + 2);
E 2
I 2
D 8
			bcopy((caddr_t)(inbound_m + inbound_oidx->cni_securep - 2), cp, 
E 8
I 8
			bcopy(mtod(inbound_m, caddr_t) + inbound_oidx->cni_securep - 2, cp, 
E 8
				(unsigned)(inbound_oidx->cni_secure_len + 2));
E 2
D 8
			len += inbound_oidx->cni_secure_len + 2;
E 8
I 8
			cp += inbound_oidx->cni_secure_len + 2;
E 8
		}
I 2
		m->m_len += optlen;
I 8
		len += optlen;
E 8
E 2
	}

D 2
	m->m_len = len;
	total_len += len;
	pdu->esis_hdr_len = total_len;
E 2
I 2
	pdu->esis_hdr_len = m0->m_pkthdr.len = len;
E 2
	iso_gen_csum(m0, ESIS_CKSUM_OFF, (int)pdu->esis_hdr_len);

I 2
	bzero((caddr_t)&siso, sizeof(siso));
D 9
	siso.siso_len = 12;
E 9
E 2
	siso.siso_family = AF_ISO;
D 2
	siso.siso_addr.isoa_afi = AFI_SNA;
	siso.siso_addr.isoa_len = 6 + 1;	/* should be taken from snpa_hdr */
E 2
I 2
	siso.siso_data[0] = AFI_SNA;
	siso.siso_nlen = 6 + 1;	/* should be taken from snpa_hdr */
E 2
										/* +1 is for AFI */
D 2
	bcopy(inbound_shp->snh_shost, siso.siso_addr.sna_idi, 6);
E 2
I 2
	bcopy(inbound_shp->snh_shost, siso.siso_data + 1, 6);
E 2
D 6
	(ifp->if_output)(ifp, m0, &siso);
E 6
I 6
D 21
	(ifp->if_output)(ifp, m0, &siso, 0);
E 21
I 21
	(ifp->if_output)(ifp, m0, (struct sockaddr *)&siso, 0);
E 21
E 6
}

/*
D 2
 * FUNCTION:		esis_extract_addr
 *
 * PURPOSE:			Remove an addr from a buffer, and stuff in iso_addr
 *
 * RETURNS:			true if the address was complete, else false
 *
 * SIDE EFFECTS:	Increment buf and decrement len according to the
 *					size of the iso_addr
 *
 * NOTES:			
 */
esis_extract_addr(buf, isoa, len)
caddr_t			*buf;		/* ptr to buffer to put address into */
struct iso_addr	*isoa;		/* ptr to address */
int				*len;		/* ptr to length of buffer */
{
	caddr_t		bp = *buf;

	if (*len <= 0)
		return(0);

	bzero((caddr_t)isoa, sizeof (struct iso_addr));
	isoa->isoa_len = *bp++;
	*len -= 1;
	if (isoa->isoa_len > *len)
		return(0);	/* too big */
	bcopy(bp, (caddr_t)isoa, isoa->isoa_len);
	*len -= isoa->isoa_len;
	bp += isoa->isoa_len;
	*buf = bp;

	return(1);
}

/*
E 2
 * FUNCTION:		esis_insert_addr
 *
 * PURPOSE:			Insert an iso_addr into a buffer
 *
 * RETURNS:			true if buffer was big enough, else false
 *
 * SIDE EFFECTS:	Increment buf & len according to size of iso_addr
 *
 * NOTES:			Plus 1 here is for length byte
 */
D 2
esis_insert_addr(buf, len, isoa, remaining)
E 2
I 2
D 7
esis_insert_addr(buf, len, isoa, m)
E 2
caddr_t			*buf;		/* ptr to buffer to put address into */
E 7
I 7
esis_insert_addr(buf, len, isoa, m, nsellen)
D 8
register caddr_t	*buf;		/* ptr to buffer to put address into */
E 7
int				*len;		/* ptr to length of buffer so far */
struct iso_addr	*isoa;		/* ptr to address */
D 2
int				remaining;	/* length of buffer */
E 2
I 2
register struct mbuf	*m;	/* determine if there remains space */
I 7
int				nsellen;
E 8
I 8
register caddr_t			*buf;		/* ptr to buffer to put address into */
int							*len;		/* ptr to length of buffer so far */
register struct iso_addr	*isoa;		/* ptr to address */
register struct mbuf		*m;			/* determine if there remains space */
int							nsellen;
E 8
E 7
E 2
{
D 2
	caddr_t		bp = *buf;
E 2
I 2
D 7
	register int newlen = isoa->isoa_len + 1;
E 7
I 7
D 8
	register int newlen = isoa->isoa_len + 1 + nsellen;
E 8
I 8
	register int newlen, result = 0;
E 8
E 7
E 2

D 2
	if ((isoa->isoa_len+1) > remaining)
E 2
I 2
D 8
	if (newlen > M_TRAILINGSPACE(m))
E 2
		return(0);
D 2
	*bp++ = isoa->isoa_len;
	*len += 1;
	bcopy((caddr_t)isoa, bp, isoa->isoa_len);
	bp += isoa->isoa_len;
	*len += isoa->isoa_len;
	*buf = bp;
E 2
I 2
	bcopy((caddr_t)isoa, *buf, newlen);
I 7
	if (nsellen)
		*(u_char *)*buf += nsellen;
E 7
	*len += newlen;
	*buf += newlen;
	m->m_len += newlen;
E 2
	return(1);
E 8
I 8
	isoa->isoa_len -= nsellen;
	newlen = isoa->isoa_len + 1;
	if (newlen <=  M_TRAILINGSPACE(m)) {
		bcopy((caddr_t)isoa, *buf, newlen);
		*len += newlen;
		*buf += newlen;
		m->m_len += newlen;
		result = 1;
	}
	isoa->isoa_len += nsellen;
	return (result);
E 8
}

I 5
#define ESIS_EXTRACT_ADDR(d, b) { d = (struct iso_addr *)(b); b += (1 + *b); \
	    if (b > buflim) {esis_stat.es_toosmall++; goto bad;}}
#define ESIS_NEXT_OPTION(b)	{ b += (2 + b[1]); \
	    if (b > buflim) {esis_stat.es_toosmall++; goto bad;}}
D 6
int ESHonly;
E 6
I 6
D 10
int ESHonly = 1;
E 10
I 10
int ESHonly = 0;
E 10
E 6
E 5
/*
 
/*
 * FUNCTION:		esis_eshinput
 *
 * PURPOSE:			Process an incoming ESH pdu
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
esis_eshinput(m, shp)
struct mbuf		*m;	/* esh pdu */
struct snpa_hdr	*shp;	/* subnetwork header */
{
D 7
	struct esis_fixed	*pdu = mtod(m, struct esis_fixed *);
E 7
I 7
	struct	esis_fixed	*pdu = mtod(m, struct esis_fixed *);
E 7
	u_short				ht;		/* holding time */
D 2
	struct iso_addr		nsap;
	int					naddr;
	caddr_t				buf = (caddr_t)pdu + sizeof(struct esis_fixed);
E 2
I 2
D 7
	struct iso_addr		*nsap;
E 7
I 7
	struct	iso_addr	*nsap;
E 7
D 5
	int					naddr = 0;
E 5
I 5
	int					naddr;
E 5
	u_char				*buf = (u_char *)(pdu + 1);
E 2
D 5
	int					len = pdu->esis_hdr_len - sizeof(struct esis_fixed);
I 2
	int					optlen, new_entry;
E 5
I 5
	u_char				*buflim = pdu->esis_hdr_len + (u_char *)pdu;
I 7
D 8
	struct	rtentry *rt;
E 7
	int					new_entry;
E 8
I 8
	int					new_entry = 0;
E 8
E 5
E 2

	esis_stat.es_eshrcvd++;

	CTOH(pdu->esis_ht_msb, pdu->esis_ht_lsb, ht);

D 5
	if (len > 0) {
		naddr = *buf++;
		len--;
	} else
E 5
I 5
	naddr = *buf++;
	if (buf >= buflim)
E 5
		goto bad;
D 8

	IFDEBUG(D_ESISINPUT)
		printf("esis_eshinput: esh: ht %d, naddr %d\n", ht, naddr);
	ENDDEBUG

	while (naddr-- > 0) {
E 8
I 8
	if (naddr == 1) {
E 8
D 2
		if (esis_extract_addr(&buf, &nsap, &len)) {
			int new_entry = (snpac_look(&nsap) == NULL);
E 2
I 2
D 5
		nsap = (struct iso_addr *)buf;
		if ((len -=  (optlen = *buf++)) >= 0) {
			buf += optlen;
			new_entry = (snpac_look(nsap) == NULL);
E 5
I 5
		ESIS_EXTRACT_ADDR(nsap, buf);
D 7
		new_entry = (snpac_look(nsap) == NULL);
E 5
E 2

E 7
I 7
D 8
		new_entry = snpac_add(shp->snh_ifp, nsap, shp->snh_shost, SNPA_ES, ht);
E 8
I 8
		new_entry = snpac_add(shp->snh_ifp,
								 nsap, shp->snh_shost, SNPA_ES, ht, 0);
	} else {
		int nsellength = 0, nlen = 0;
		{
		/* See if we want to compress out multiple nsaps differing
		   only by nsel */
			register struct ifaddr *ifa = shp->snh_ifp->if_addrlist;
			for (; ifa; ifa = ifa->ifa_next)
				if (ifa->ifa_addr->sa_family == AF_ISO) {
					nsellength = ((struct iso_ifaddr *)ifa)->ia_addr.siso_tlen;
					break;
			}
		}
E 8
E 7
D 5
			IFDEBUG(D_ESISINPUT)
				printf("esis_eshinput: nsap %s is %s\n", 
D 2
					clnp_iso_addrp(&nsap), new_entry ? "new" : "old");
E 2
I 2
					clnp_iso_addrp(nsap), new_entry ? "new" : "old");
E 2
			ENDDEBUG
E 5
I 5
		IFDEBUG(D_ESISINPUT)
D 8
			printf("esis_eshinput: nsap %s is %s\n", 
				clnp_iso_addrp(nsap), new_entry ? "new" : "old");
E 8
I 8
			printf("esis_eshinput: esh: ht %d, naddr %d nsellength %d\n",
					ht, naddr, nsellength);
E 8
		ENDDEBUG
E 5
D 7

D 2
			snpac_add(shp->snh_ifp, &nsap, shp->snh_shost, 6, SNPA_ES, ht);
E 2
I 2
D 5
			snpac_add(shp->snh_ifp, nsap, shp->snh_shost, 6, SNPA_ES, ht);
E 2
			if (new_entry)
				esis_shoutput(shp->snh_ifp, 
					iso_systype & SNPA_ES ? ESIS_ESH : ESIS_ISH,
					esis_holding_time, shp->snh_shost, 6);
		} else {
I 2
bad:
E 2
			esis_stat.es_toosmall++;
			break;
		}
E 5
I 5
		snpac_add(shp->snh_ifp, nsap, shp->snh_shost, 6, SNPA_ES, ht);
E 7
D 8
		if (new_entry)
			esis_shoutput(shp->snh_ifp, 
				iso_systype & SNPA_ES ? ESIS_ESH : ESIS_ISH,
				esis_holding_time, shp->snh_shost, 6);
E 8
I 8
		while (naddr-- > 0) {
			struct iso_addr *nsap2; u_char *buf2;
			ESIS_EXTRACT_ADDR(nsap, buf);
			/* see if there is at least one more nsap in ESH differing
			   only by nsel */
			if (nsellength != 0) for (buf2 = buf; buf2 < buflim;) {
				ESIS_EXTRACT_ADDR(nsap2, buf2);
				IFDEBUG(D_ESISINPUT)
					printf("esis_eshinput: comparing %s ", 
						clnp_iso_addrp(nsap));
					printf("and %s\n", clnp_iso_addrp(nsap2));
				ENDDEBUG
				if (Bcmp(nsap->isoa_genaddr, nsap2->isoa_genaddr,
						 nsap->isoa_len - nsellength) == 0) {
					nlen = nsellength;
					break;
				}
			}
			new_entry |= snpac_add(shp->snh_ifp,
									nsap, shp->snh_shost, SNPA_ES, ht, nlen);
			nlen = 0;
		}
E 8
E 5
	}
I 8
	IFDEBUG(D_ESISINPUT)
		printf("esis_eshinput: nsap %s is %s\n", 
			clnp_iso_addrp(nsap), new_entry ? "new" : "old");
	ENDDEBUG
	if (new_entry && (iso_systype & SNPA_IS))
		esis_shoutput(shp->snh_ifp, ESIS_ISH, esis_holding_time,
						shp->snh_shost, 6, (struct iso_addr *)0);
E 8
D 5

E 5
I 5
bad:
E 5
D 2
bad:
E 2
D 9
	m_freem(m);
E 9
I 5
	return;
E 5
}

/*
 * FUNCTION:		esis_ishinput
 *
 * PURPOSE:			process an incoming ISH pdu
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
esis_ishinput(m, shp)
struct mbuf		*m;	/* esh pdu */
struct snpa_hdr	*shp;	/* subnetwork header */
{
	struct esis_fixed	*pdu = mtod(m, struct esis_fixed *);
D 5
	u_short				ht;		/* holding time */
D 2
	struct iso_addr		nsap;
E 2
I 2
	struct iso_addr		*nsap;
E 2
	caddr_t				buf = (caddr_t)pdu + sizeof(struct esis_fixed);
	int					len = pdu->esis_hdr_len - sizeof(struct esis_fixed);
I 2
	int					optlen, new_entry;
E 5
I 5
D 10
	u_short				ht;					/* holding time */
E 10
I 10
	u_short				ht, newct;			/* holding time */
E 10
	struct iso_addr		*nsap; 				/* Network Entity Title */
	register u_char		*buf = (u_char *) (pdu + 1);
	register u_char		*buflim = pdu->esis_hdr_len + (u_char *)pdu;
	int					new_entry;
E 5
E 2

	esis_stat.es_ishrcvd++;
	CTOH(pdu->esis_ht_msb, pdu->esis_ht_lsb, ht);

	IFDEBUG(D_ESISINPUT)
		printf("esis_ishinput: ish: ht %d\n", ht);
	ENDDEBUG
D 5

D 2
	if (esis_extract_addr(&buf, &nsap, &len)) {
		int new_entry = (snpac_look(&nsap) == NULL);
E 2
I 2
	nsap = (struct iso_addr *)buf;
	if ((len -=  (optlen = *buf++)) < 0)
E 5
I 5
	if (ESHonly)
E 5
		goto bad;
D 5
	buf += optlen;
E 5
E 2

D 2
		IFDEBUG(D_ESISINPUT)
			printf("esis_ishinput: nsap %s is %s\n", 
				clnp_iso_addrp(&nsap), new_entry ? "new" : "old");
		ENDDEBUG

		snpac_add(shp->snh_ifp, &nsap, shp->snh_shost, 6, SNPA_IS, ht);
		if (new_entry)
			esis_shoutput(shp->snh_ifp, 
				iso_systype & SNPA_ES ? ESIS_ESH : ESIS_ISH,
				esis_holding_time, shp->snh_shost, 6);
	} else {
		esis_stat.es_toosmall++;
E 2
I 2
D 5
	/* process options */
	while (len > 0) {
		switch (*buf++) {
E 5
I 5
	ESIS_EXTRACT_ADDR(nsap, buf);

	while (buf < buflim) {
		switch (*buf) {
E 5
		case ESISOVAL_ESCT:
I 15
			if (iso_systype & SNPA_IS)
				break;
E 15
D 5
			if (*buf != 2)
E 5
I 5
			if (buf[1] != 2)
E 5
				goto bad;
D 5
			CTOH(buf[0], buf[1], esis_config_time);
E 5
I 5
D 10
			CTOH(buf[2], buf[3], esis_config_time);
E 10
I 10
			CTOH(buf[2], buf[3], newct);
			if (esis_config_time != newct) {
				untimeout(esis_config,0);
				esis_config_time = newct;
				esis_config();
			}
E 10
			break;
		
		default:
			printf("Unknown ISH option: %x\n", *buf);
E 5
		}
D 5
		if ((len -=  (optlen = *buf)) < 0) {
	bad:
			esis_stat.es_toosmall++;
			m_freem(m);
			return;
		}
		buf += 1 + optlen;
E 5
I 5
		ESIS_NEXT_OPTION(buf);
E 5
E 2
	}
I 2
D 7
	new_entry = (snpac_look(nsap) == NULL);

E 7
I 7
D 8
	new_entry = snpac_add(shp->snh_ifp, nsap, shp->snh_shost, SNPA_IS, ht);
E 8
I 8
	new_entry = snpac_add(shp->snh_ifp, nsap, shp->snh_shost, SNPA_IS, ht, 0);
E 8
E 7
	IFDEBUG(D_ESISINPUT)
		printf("esis_ishinput: nsap %s is %s\n", 
			clnp_iso_addrp(nsap), new_entry ? "new" : "old");
	ENDDEBUG

D 7
	snpac_add(shp->snh_ifp, nsap, shp->snh_shost, 6, SNPA_IS, ht);
E 7
	if (new_entry)
		esis_shoutput(shp->snh_ifp, 
			iso_systype & SNPA_ES ? ESIS_ESH : ESIS_ISH,
D 8
			esis_holding_time, shp->snh_shost, 6);
E 8
I 8
			esis_holding_time, shp->snh_shost, 6, (struct iso_addr *)0);
E 8
I 5
bad:
E 5
E 2
D 9
	m_freem(m);
E 9
I 5
	return;
E 5
}

/*
 * FUNCTION:		esis_rdinput
 *
 * PURPOSE:			Process an incoming RD pdu
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
esis_rdinput(m0, shp)
struct mbuf		*m0;	/* esh pdu */
struct snpa_hdr	*shp;	/* subnetwork header */
{
	struct esis_fixed	*pdu = mtod(m0, struct esis_fixed *);
	u_short				ht;		/* holding time */
D 2
	struct iso_addr		da;
	caddr_t				bsnpa;
	int					bsnpalen;
	struct iso_addr		net;
	int					netl;
	caddr_t				buf = (caddr_t)pdu + sizeof(struct esis_fixed);
E 2
I 2
D 5
	register struct iso_addr *da, *net = 0, *netmask = 0, *snpamask = 0;
	u_char				*buf = (u_char *)(pdu + 1);
E 2
	int					len = pdu->esis_hdr_len - sizeof(struct esis_fixed);
I 2
	int					optlen, bsnpalen;
	caddr_t				bsnpa;
E 5
I 5
	struct iso_addr		*da, *net = 0, *netmask = 0, *snpamask = 0;
	register struct iso_addr *bsnpa;
	register u_char		*buf = (u_char *)(pdu + 1);
	register u_char		*buflim = pdu->esis_hdr_len + (u_char *)pdu;
E 5
E 2

	esis_stat.es_rdrcvd++;

	/* intermediate systems ignore redirects */
	if (iso_systype & SNPA_IS)
D 9
		goto bad;
E 9
I 9
		return;
E 9
I 5
	if (ESHonly)
D 9
		goto bad;
E 9
I 9
		return;
E 9
E 5

	CTOH(pdu->esis_ht_msb, pdu->esis_ht_lsb, ht);
I 2
D 5
	if (len <= 0)
E 5
I 5
	if (buf >= buflim)
E 5
D 9
		goto bad;
E 9
I 9
		return;
E 9
E 2

	/* Extract DA */
D 2
	if (!esis_extract_addr(&buf, &da, &len)) {
		esis_stat.es_toosmall++;
E 2
I 2
D 5
	da = (struct iso_addr *)buf;
	if ((len -=  (optlen = *buf++)) <= 0)
E 2
		goto bad;
D 2
	}
	
E 2
I 2
	buf += optlen;
E 5
I 5
	ESIS_EXTRACT_ADDR(da, buf);
E 5

E 2
	/* Extract better snpa */
D 2
	bsnpalen = *buf++;
	if (bsnpalen > len) {
		esis_stat.es_toosmall++;
E 2
I 2
D 5
	if ((len -=  (bsnpalen = *buf++)) < 0)
E 2
		goto bad;
D 2
	} else {
		bsnpa = buf;
		buf += bsnpalen;
		len -= bsnpalen;
	}

E 2
I 2
	bsnpa = (caddr_t)buf;
	buf += optlen;
	
E 5
I 5
	ESIS_EXTRACT_ADDR(bsnpa, buf);

E 5
E 2
	/* Extract NET if present */
D 2
	if ((netl = *buf) > 0) {
		if (!esis_extract_addr(&buf, &net, &len)) {
			esis_stat.es_toosmall++;
E 2
I 2
D 5
	if (len) {
		net = (struct iso_addr *)buf;
		if ((len -=  (optlen = *buf++)) < 0)
E 2
			goto bad;
I 2
		buf += optlen;
E 5
I 5
	if (buf < buflim) {
D 8
		ESIS_EXTRACT_ADDR(net, buf);
E 8
I 8
		if (*buf == 0)
			buf++; /* no NET present, skip NETL anyway */
		else
			ESIS_EXTRACT_ADDR(net, buf);
E 8
E 5
	}

	/* process options */
D 5
	while (len > 0) {
		switch (*buf++) {
E 5
I 5
	while (buf < buflim) {
		switch (*buf) {
E 5
		case ESISOVAL_SNPAMASK:
			if (snpamask) /* duplicate */
D 9
				goto bad;
E 9
I 9
				return;
E 9
D 5
			snpamask = (struct iso_addr *)buf;
E 5
I 5
			snpamask = (struct iso_addr *)(buf + 1);
E 5
			break;

		case ESISOVAL_NETMASK:
			if (netmask) /* duplicate */
D 9
				goto bad;
E 9
I 9
				return;
E 9
D 5
			netmask = (struct iso_addr *)buf;
E 5
I 5
			netmask = (struct iso_addr *)(buf + 1);
			break;

		default:
			printf("Unknown option in ESIS RD (0x%x)\n", buf[-1]);
E 5
E 2
		}
I 2
D 5
		if ((len -=  (optlen = *buf)) < 0)
			goto bad;
		buf += 1 + optlen;
E 5
I 5
		ESIS_NEXT_OPTION(buf);
E 5
E 2
	}

	IFDEBUG(D_ESISINPUT)
D 2
		printf("esis_rdinput: rd: ht %d, da %s\n", ht, clnp_iso_addrp(&da));
		if (netl)
			printf("\t: net %s\n", clnp_iso_addrp(&net));
E 2
I 2
		printf("esis_rdinput: rd: ht %d, da %s\n", ht, clnp_iso_addrp(da));
		if (net)
			printf("\t: net %s\n", clnp_iso_addrp(net));
E 2
	ENDDEBUG
D 2

E 2
	/*
	 *	If netl is zero, then redirect is to an ES. We need to add an entry
	 *	to the snpa cache for (destination, better snpa).
	 *	If netl is not zero, then the redirect is to an IS. In this
	 *	case, add an snpa cache entry for (net, better snpa).
	 *
	 *	If the redirect is to an IS, add a route entry towards that
	 *	IS.
	 */
D 2
	if (netl == 0) {
E 2
I 2
D 5
	if ((net == 0) || (snpamask)) {
E 5
I 5
	if (net == 0 || net->isoa_len == 0 || snpamask) {
E 5
E 2
		/* redirect to an ES */
D 2
		snpac_add(shp->snh_ifp, &da, bsnpa, bsnpalen, SNPA_ES, ht);
E 2
I 2
D 5
		snpac_add(shp->snh_ifp, da, bsnpa, bsnpalen, SNPA_ES, ht);
E 5
I 5
		snpac_add(shp->snh_ifp, da,
D 7
				bsnpa->isoa_genaddr, bsnpa->isoa_len, SNPA_ES, ht);
E 7
I 7
D 8
				bsnpa->isoa_genaddr, SNPA_ES, ht);
E 8
I 8
				bsnpa->isoa_genaddr, SNPA_ES, ht, 0);
E 8
E 7
E 5
E 2
	} else {
D 2
		snpac_add(shp->snh_ifp, &net, bsnpa, bsnpalen, SNPA_IS, ht);
		snpac_addrt(&da, &net);
E 2
I 2
D 5
		struct iso_addr bsnpa_ia;

		snpac_add(shp->snh_ifp, net, bsnpa, bsnpalen, SNPA_IS, ht);
		bcopy(bsnpa, bsnpa_ia.isoa_genaddr, bsnpa_ia.isoa_len = 1 + bsnpalen);
		bsnpa_ia.isoa_genaddr[0] = AFI_SNA;
		snpac_addrt(da, &bsnpa_ia, net, netmask);
E 5
I 5
		snpac_add(shp->snh_ifp, net,
D 7
				bsnpa->isoa_genaddr, bsnpa->isoa_len, SNPA_IS, ht);
E 7
I 7
D 8
				bsnpa->isoa_genaddr, SNPA_IS, ht);
E 8
I 8
				bsnpa->isoa_genaddr, SNPA_IS, ht, 0);
E 8
E 7
		snpac_addrt(shp->snh_ifp, da, net, netmask);
E 5
E 2
	}
D 9
bad:
	m_freem(m0);
E 9
I 9
bad: ;    /* Needed by ESIS_NEXT_OPTION */
E 9
}

/*
 * FUNCTION:		esis_config
 *
 * PURPOSE:			Report configuration
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Called every esis_config_time seconds
 */
I 23
void
E 23
esis_config()
{
	register struct ifnet	*ifp;

	timeout(esis_config, (caddr_t)0, hz * esis_config_time);

	/* 
	 *	Report configuration for each interface that 
	 *	- is UP
D 17
	 *	- is not loopback
E 17
I 17
	 *	- has BROADCAST capability
E 17
D 9
	 *	- has broadcast capabilities
E 9
	 *	- has an ISO address
	 */
I 17
	/* Todo: a better way would be to construct the esh or ish
	 * once and copy it out for all devices, possibly calling
	 * a method in the iso_ifaddr structure to encapsulate and
	 * transmit it.  This could work to advantage for non-broadcast media
	 */
E 17
	
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if ((ifp->if_flags & IFF_UP) &&
D 9
			(ifp->if_flags & IFF_BROADCAST) &&
E 9
D 17
			((ifp->if_flags & IFF_LOOPBACK) == 0)) {
E 17
I 17
		    (ifp->if_flags & IFF_BROADCAST)) {
E 17
			/* search for an ISO address family */
			struct ifaddr	*ia;

			for (ia = ifp->if_addrlist; ia; ia = ia->ifa_next) {
D 2
				if (ia->ifa_addr.sa_family == AF_ISO) {
E 2
I 2
				if (ia->ifa_addr->sa_family == AF_ISO) {
E 2
					esis_shoutput(ifp, 
						iso_systype & SNPA_ES ? ESIS_ESH : ESIS_ISH,
						esis_holding_time,
D 2
						iso_systype & SNPA_ES ? all_is.sc_snpa : 
						all_es.sc_snpa, 6);
E 2
I 2
D 8
						(caddr_t)(iso_systype & SNPA_ES ? all_is.sc_snpa : 
						all_es.sc_snpa), 6);
E 8
I 8
						(caddr_t)(iso_systype & SNPA_ES ? all_is_snpa : 
						all_es_snpa), 6, (struct iso_addr *)0);
E 8
E 2
					break;
				}
			}
		}
	}
}

/*
 * FUNCTION:		esis_shoutput
 *
 * PURPOSE:			Transmit an esh or ish pdu
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
D 8
esis_shoutput(ifp, type, ht, sn_addr, sn_len)
E 8
I 8
esis_shoutput(ifp, type, ht, sn_addr, sn_len, isoa)
E 8
struct ifnet	*ifp;
int				type;
short			ht;
caddr_t 		sn_addr;
int				sn_len;
I 8
struct	iso_addr *isoa;
E 8
{
	struct mbuf			*m, *m0;
	caddr_t				cp, naddrp;
	int					naddr = 0;
	struct esis_fixed	*pdu;
D 8
	struct ifaddr		*ifa;
E 8
I 8
	struct iso_ifaddr	*ia;
E 8
D 2
	int					len, total_len = 0;
E 2
I 2
	int					len;
E 2
	struct sockaddr_iso	siso;

	if (type == ESIS_ESH)
		esis_stat.es_eshsent++;
	else if (type == ESIS_ISH) 
		esis_stat.es_ishsent++;
	else {
		printf("esis_shoutput: bad pdu type\n");
		return;
	}

	IFDEBUG(D_ESISOUTPUT)
		int	i;
		printf("esis_shoutput: ifp x%x (%s%d), %s, ht %d, to: [%d] ",
			ifp, ifp->if_name, ifp->if_unit, type == ESIS_ESH ? "esh" : "ish",
			ht, sn_len);
		for (i=0; i<sn_len; i++)
			printf("%x%c", *(sn_addr+i), i < (sn_len-1) ? ':' : ' ');
		printf("\n");
	ENDDEBUG

D 2
	if ((m0 = m = m_getclr(M_DONTWAIT, MT_HEADER)) == NULL) {
E 2
I 2
	if ((m0 = m = m_gethdr(M_DONTWAIT, MT_HEADER)) == NULL) {
E 2
		esis_stat.es_nomem++;
		return;
	}
I 2
	bzero(mtod(m, caddr_t), MHLEN);
E 2

	pdu = mtod(m, struct esis_fixed *);
D 2
	naddrp = cp = (caddr_t)pdu + sizeof(struct esis_fixed);
E 2
I 2
	naddrp = cp = (caddr_t)(pdu + 1);
E 2
	len = sizeof(struct esis_fixed);

	/*
	 *	Build fixed part of header
	 */
	pdu->esis_proto_id = ISO9542_ESIS;
	pdu->esis_vers = ESIS_VERSION;
	pdu->esis_type = type;
	HTOC(pdu->esis_ht_msb, pdu->esis_ht_lsb, ht);

	if (type == ESIS_ESH) {
		cp++;
		len++;
	}

I 2
	m->m_len = len;
E 2
D 8
	for (ifa = ifp->if_addrlist; ifa; ifa=ifa->ifa_next) {
D 2
		if (ifa->ifa_addr.sa_family == AF_ISO) {
E 2
I 2
		if (ifa->ifa_addr->sa_family == AF_ISO) {
I 7
			register struct iso_ifaddr *ia = (struct iso_ifaddr *)ifa;
			int nsellen = (type == ESIS_ESH ? ia->ia_addr.siso_tlen : 0); 
E 7
E 2
			IFDEBUG(D_ESISOUTPUT)
D 7
				printf("esis_shoutput: adding nsap %s\n", 
					clnp_iso_addrp(&IA_SIS(ifa)->siso_addr));
E 7
I 7
				printf("esis_shoutput: adding NET %s\n", 
					clnp_iso_addrp(&ia->ia_addr.siso_addr));
E 7
			ENDDEBUG
D 2
			if (!esis_insert_addr(&cp, &len, &IA_SIS(ifa)->siso_addr, 
				MLEN - len)) {
				total_len += len;
				EXTEND_PACKET(m, m0, len, cp);
				(void) esis_insert_addr(&cp, &len, &IA_SIS(ifa)->siso_addr, 
					MLEN - len);
E 2
I 2
D 7
			if (!esis_insert_addr(&cp, &len, &IA_SIS(ifa)->siso_addr, m)) {
E 7
I 7
			if (!esis_insert_addr(&cp, &len,
								  &ia->ia_addr.siso_addr, m, nsellen)) {
E 7
				EXTEND_PACKET(m, m0, cp);
D 7
				(void) esis_insert_addr(&cp, &len, &IA_SIS(ifa)->siso_addr, m);
E 7
I 7
				(void) esis_insert_addr(&cp, &len, &ia->ia_addr.siso_addr, m,
										nsellen);
E 7
E 2
			}
			naddr++;
			if (type == ESIS_ISH)
				break;
E 8
I 8
	if (isoa) {
		/*
		 * Here we are responding to a clnp packet sent to an NSAP
		 * that is ours which was sent to the MAC addr all_es's.
		 * It is possible that we did not specifically advertise this
		 * NSAP, even though it is ours, so we will respond
		 * directly to the sender that we are here.  If we do have
		 * multiple NSEL's we'll tack them on so he can compress them out.
		 */
		(void) esis_insert_addr(&cp, &len, isoa, m, 0);
		naddr = 1;
	}
	for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
		int nsellen = (type == ESIS_ISH ? ia->ia_addr.siso_tlen : 0); 
		int n = ia->ia_addr.siso_nlen;
		register struct iso_ifaddr *ia2;

		if (type == ESIS_ISH && naddr > 0)
			break;
		for (ia2 = iso_ifaddr; ia2 != ia; ia2 = ia2->ia_next)
			if (Bcmp(ia->ia_addr.siso_data, ia2->ia_addr.siso_data, n) == 0)
					break;
		if (ia2 != ia)
			continue;	/* Means we have previously copied this nsap */
		if (isoa && Bcmp(ia->ia_addr.siso_data, isoa->isoa_genaddr, n) == 0) {
			isoa = 0;
			continue;	/* Ditto */
E 8
		}
I 8
		IFDEBUG(D_ESISOUTPUT)
			printf("esis_shoutput: adding NSAP %s\n", 
				clnp_iso_addrp(&ia->ia_addr.siso_addr));
		ENDDEBUG
		if (!esis_insert_addr(&cp, &len,
							  &ia->ia_addr.siso_addr, m, nsellen)) {
			EXTEND_PACKET(m, m0, cp);
			(void) esis_insert_addr(&cp, &len, &ia->ia_addr.siso_addr, m,
									nsellen);
		}
		naddr++;
E 8
	}

	if (type == ESIS_ESH)
		*naddrp = naddr;
I 14
	else {
		/* add suggested es config timer option to ISH */
		if (M_TRAILINGSPACE(m) < 4) {
			printf("esis_shoutput: extending packet\n");
			EXTEND_PACKET(m, m0, cp);
		}
		*cp++ = ESISOVAL_ESCT;
		*cp++ = 2;
		HTOC(*cp, *(cp+1), esis_esconfig_time);
		len += 4;
		m->m_len += 4;
		IFDEBUG(D_ESISOUTPUT)
			printf("m0 0x%x, m 0x%x, data 0x%x, len %d, cp 0x%x\n",
			m0, m, m->m_data, m->m_len, cp);
		ENDDEBUG
	}
E 14

D 2
	m->m_len = len;
	total_len += len;
	pdu->esis_hdr_len = total_len;
E 2
I 2
	m0->m_pkthdr.len = len;
	pdu->esis_hdr_len = len;
E 2
	iso_gen_csum(m0, ESIS_CKSUM_OFF, (int)pdu->esis_hdr_len);

I 2
	bzero((caddr_t)&siso, sizeof(siso));
E 2
	siso.siso_family = AF_ISO;
D 2
	siso.siso_addr.isoa_afi = AFI_SNA;
	siso.siso_addr.isoa_len = sn_len + 1;
	bcopy(sn_addr, siso.siso_addr.sna_idi, sn_len);
E 2
I 2
	siso.siso_data[0] = AFI_SNA;
	siso.siso_nlen = sn_len + 1;
D 9
	siso.siso_len  = sn_len + 6;
E 9
	bcopy(sn_addr, siso.siso_data + 1, (unsigned)sn_len);
E 2
D 6
	(ifp->if_output)(ifp, m0, &siso);
E 6
I 6
D 21
	(ifp->if_output)(ifp, m0, &siso, 0);
E 21
I 21
	(ifp->if_output)(ifp, m0, (struct sockaddr *)&siso, 0);
E 21
E 6
}
I 9

/*
 * FUNCTION:		isis_input
 *
 * PURPOSE:			Process an incoming isis packet
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
isis_input(m0, shp)
struct mbuf		*m0;		/* ptr to first mbuf of pkt */
struct snpa_hdr	*shp;	/* subnetwork header */
{
	register int type;
D 13
	struct rawcb *rp;
E 13
I 13
	register struct rawcb *rp, *first_rp = 0;
E 13
	struct ifnet *ifp = shp->snh_ifp;
D 13
	struct sockbuf *sb = 0;
E 13
	char workbuf[16];
	struct mbuf *mm;

	IFDEBUG(D_ISISINPUT)
		int i;

		printf("isis_input: pkt on ifp x%x (%s%d): from:", ifp, 
			ifp->if_name, ifp->if_unit);
		for (i=0; i<6; i++)
			printf("%x%c", shp->snh_shost[i]&0xff, (i<5) ? ':' : ' ');
		printf(" to:");
		for (i=0; i<6; i++)
			printf("%x%c", shp->snh_dhost[i]&0xff, (i<5) ? ':' : ' ');
		printf("\n");
	ENDDEBUG
	esis_dl.sdl_alen = ifp->if_addrlen;
	esis_dl.sdl_index = ifp->if_index;
	bcopy(shp->snh_shost, (caddr_t)esis_dl.sdl_data, esis_dl.sdl_alen);
	for (rp = esis_pcb.rcb_next; rp != &esis_pcb; rp = rp->rcb_next) {
D 13
		if (sb == 0) {
			sb = &rp->rcb_socket->so_rcv;
E 13
I 13
		if (first_rp == 0) {
			first_rp = rp;
E 13
			continue;
		}
		if (mm = m_copy(m0, 0, M_COPYALL)) { /*can't block at interrupt level */
			if (sbappendaddr(&rp->rcb_socket->so_rcv,
D 20
							  &esis_dl, mm, (struct mbuf *)0) != 0)
E 20
I 20
D 26
							  &esis_dl, mm, (struct mbuf *)0) != 0) {
E 26
I 26
							  (struct sockaddr *)&esis_dl, mm,
							  (struct mbuf *)0) != 0) {
E 26
E 20
				sorwakeup(rp->rcb_socket);
D 20
			else {
E 20
I 20
			 } else {
E 20
				IFDEBUG(D_ISISINPUT)
					printf("Error in sbappenaddr, mm = 0x%x\n", mm);
				ENDDEBUG
				m_freem(mm);
			}
		}
	}
D 13
	if (sb) {
		if (sbappendaddr(&rp->rcb_socket->so_rcv,
							  &esis_dl, mm, (struct mbuf *)0) != 0)
			sorwakeup(rp->rcb_socket);
		else
			m_freem(m0);
E 13
I 13
	if (first_rp && sbappendaddr(&first_rp->rcb_socket->so_rcv,
D 15
							  &esis_dl, mm, (struct mbuf *)0) != 0) {
E 15
I 15
D 26
							  &esis_dl, m0, (struct mbuf *)0) != 0) {
E 26
I 26
							  (struct sockaddr *)&esis_dl, m0,
							  (struct mbuf *)0) != 0) {
E 26
E 15
		sorwakeup(first_rp->rcb_socket);
		return;
E 13
	}
I 13
	m_freem(m0);
E 13
}

isis_output(sdl, m)
register struct sockaddr_dl	*sdl;
struct mbuf *m;
{
	register struct ifnet *ifp;
	struct ifaddr *ifa, *ifa_ifwithnet();
	struct sockaddr_iso siso;
	int error = 0;
	unsigned sn_len;

D 21
	ifa = ifa_ifwithnet(sdl);	/* extract ifp from sockaddr_dl */
E 21
I 21
	ifa = ifa_ifwithnet((struct sockaddr *)sdl);	/* get ifp from sdl */
E 21
	if (ifa == 0) {
		IFDEBUG(D_ISISOUTPUT)
			printf("isis_output: interface not found\n");
		ENDDEBUG
		error = EINVAL;
		goto release;
	}
	ifp = ifa->ifa_ifp;
D 16
	sn_len = ifp->if_addrlen;
E 16
I 16
	sn_len = sdl->sdl_alen;
E 16
	IFDEBUG(D_ISISOUTPUT)
		u_char *cp = (u_char *)LLADDR(sdl), *cplim = cp + sn_len;
		printf("isis_output: ifp 0x%x (%s%d), to: ",
			ifp, ifp->if_name, ifp->if_unit);
		while (cp < cplim) {
			printf("%x", *cp++);
			printf("%c", (cp < cplim) ? ':' : ' ');
		}
		printf("\n");
	ENDDEBUG
	bzero((caddr_t)&siso, sizeof(siso));
	siso.siso_family = AF_ISO; /* This convention may be useful for X.25 */
	siso.siso_data[0] = AFI_SNA;
	siso.siso_nlen = sn_len + 1;
	bcopy(LLADDR(sdl), siso.siso_data + 1, sn_len);
	error = (ifp->if_output)(ifp, m, (struct sockaddr *)&siso, 0);
	if (error) {
		IFDEBUG(D_ISISOUTPUT)
			printf("isis_output: error from ether_output is %d\n", error);
		ENDDEBUG
	}
	return (error);

release:
	if (m != NULL)
		m_freem(m);
	return(error);
}

E 9

/*
 * FUNCTION:		esis_ctlinput
 *
 * PURPOSE:			Handle the PRC_IFDOWN transition
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Calls snpac_flush for interface specified.
 *					The loop through iso_ifaddr is stupid because
 *					back in if_down, we knew the ifp...
 */
esis_ctlinput(req, siso)
int						req;		/* request: we handle only PRC_IFDOWN */
struct sockaddr_iso		*siso;		/* address of ifp */
{
	register struct iso_ifaddr *ia;	/* scan through interface addresses */

D 2
	for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
		if (iso_addrmatch(IA_SIS(ia), siso))
			snpac_flushifp(ia->ia_ifp);
	}
E 2
I 2
	if (req == PRC_IFDOWN)
		for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
			if (iso_addrmatch(IA_SIS(ia), siso))
				snpac_flushifp(ia->ia_ifp);
		}
E 2
}

D 24
#endif	ISO
E 24
I 24
#endif	/* ISO */
E 24
E 1
