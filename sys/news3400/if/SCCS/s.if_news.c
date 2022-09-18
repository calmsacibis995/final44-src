h04301
s 00002/00002/00213
d D 8.1 93/06/11 14:57:10 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00215
d D 7.5 93/03/09 23:41:24 utashiro 5 4
c 
e
s 00002/00002/00214
d D 7.4 93/01/20 00:28:08 utashiro 4 3
c Fixed wrong headers.
e
s 00014/00014/00202
d D 7.3 92/12/17 02:56:41 utashiro 3 2
c make kernel includes standard
e
s 00001/00001/00215
d D 7.2 92/07/28 17:33:06 bostic 2 1
c update from Kazumasa Utashiro
e
s 00216/00000/00000
d D 7.1 92/06/04 15:59:13 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: if_news.c,v 4.300 91/06/09 06:26:01 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "types.h"
#include "../include/fix_machine_type.h"
#include "../include/pte.h"
E 3
I 3
D 4
#include <sys/types.h"
E 4
I 4
#include <sys/types.h>
E 4
D 5
#include <machine/fix_machine_type.h>
E 5
#include <machine/pte.h>
E 3

D 3
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "map.h"
#include "buf.h"
#include "socket.h"
#include "proc.h"
#include "user.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/socket.h>
#include <sys/proc.h>
#include <sys/user.h>
E 3

D 3
#include "../net/if.h"
#include "../if/if_news.h"
#include "../include/cpu.h"
E 3
I 3
D 4
#include <news3400/net/if.h>
E 4
I 4
#include <net/if.h>
E 4
#include <news3400/if/if_news.h>
#include <machine/cpu.h>
E 3

#if MCLBYTES == CLBYTES && defined(CPU_DOUBLE)
#define	USE_CLUSTER
#endif

/*
 * Routines supporting NEWS network interfaces.
 */
#define btomcl(x)       (((x) + MCLBYTES - 1) >> MCLSHIFT)

/*
 * Init NEWS for interface on uban whose headers of size hlen are to
 * end on a page boundary.  We also allocate page frames in the mbuffer pool
 * for these pages.
 */
if_newsinit(ifn, hlen, nmr)
	register struct ifnews *ifn;
	int hlen, nmr;
{
#ifdef USE_CLUSTER
	register caddr_t cp;
	int ncl;

	if (ifn->ifn_raddr)
		return (1);
	ncl = nmr;
	cp = malloc(btomcl(ctob(2 * ncl)), M_DEVBUF, M_NOWAIT); /*XXX*/
	if (cp == 0)
		return (0);
	ifn->ifn_raddr = cp + 4 - (hlen & 03);
	ifn->ifn_waddr = cp + ncl * MCLBYTES;
#endif /* USE_CLUSTER */
	ifn->ifn_hlen = hlen;
	return (1);
}

/*
 * Pull read data off a interface.
 * Len is length of data, with local net header stripped.
 * Off is non-zero if a trailer protocol was used, and
 * gives the offset of the trailer information.
 * We copy the trailer information and then all the normal
 * data into mbufs.  When large sized units are present
 * on the interface on cluster boundaries we can get them more
 * easily by remapping, and take advantage of this here.
 */
#ifdef NOTDEF /* use m_devget */
struct mbuf *
if_rnewsget(ifn, totlen, off, ifp)
	register struct ifnews *ifn;
	register int totlen, off;
	struct ifnet *ifp;
{
	register struct mbuf **mp, *m;
	struct mbuf *top;
	register int len;
	register caddr_t cp = ifn->ifn_raddr + ifn->ifn_hlen;
	caddr_t epkt = cp + totlen;

#ifdef USE_CLUSTER
	if (totlen >= MHLEN && off == 0) {
		MGETHDR(m, M_DONTWAIT, MT_DATA);
		if (m == 0)
			return (0);
		m->m_pkthdr.rcvif = ifp;
		m->m_pkthdr.len = totlen;
		MCLGET(m, M_DONTWAIT);
		if (m->m_len != MCLBYTES) {
			struct mbuf *n;

			MFREE(m, n);
			goto noncluster;
		}
		pageswap(cp - ifn->ifn_hlen, mtod(m, caddr_t),
		    totlen + ifn->ifn_hlen);
		m->m_len = totlen;
		m->m_data += ifn->ifn_hlen + 4 - (ifn->ifn_hlen & 03);
		return (m);
	}
noncluster:
#endif /* USE_CLUSTER */
	top = 0;
	mp = &top;
	/*
	 * Skip the trailer header (type and trailer length).
	 */
	if (off) {
		off += 2 * sizeof(u_short);
		totlen -= 2 * sizeof(u_short);
		cp += off;
	}
	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m == 0)
		return ((struct mbuf *)NULL);
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = totlen;
	m->m_len = MHLEN;

	while (totlen > 0) {
		if (top) {
			MGET(m, M_DONTWAIT, MT_DATA);
			if (m == 0) {
				m_freem(top);
				return(0);
			}
			m->m_len = MLEN;
		}

		if (totlen >= MINCLSIZE)
			MCLGET(m, M_DONTWAIT);
		if (m->m_flags & M_EXT)
D 2
			m->m_len = MIN(totlen, MCLBYTES);
E 2
I 2
			m->m_len = min(totlen, MCLBYTES);
E 2
		else if (totlen < m->m_len) {
			/*
			 * Place initial small packet/header at end of mbuf.
			 */
			if (top == 0 && totlen + max_linkhdr <= m->m_len)
				m->m_data += max_linkhdr;
			m->m_len = totlen;
		}
		len = m->m_len;
copy:
		bcopy(cp, mtod(m, caddr_t), (unsigned)len);
		cp += len;
nocopy:
		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		if (cp == epkt)
			cp = ifn->ifn_raddr + ifn->ifn_hlen;
	}
	return (top);
}
#endif /* NOTDEF */

/*
 * Map a chain of mbufs onto a network interface
 * in preparation for an i/o operation.
 * The argument chain of mbufs includes the local network header.
 */
if_wnewsput(ifn, m)
	register struct ifnews *ifn;
	register struct mbuf *m;
{
#ifdef CPU_DOUBLE
	register struct mbuf_segment *ms;
	register int n, i;

	ifn->ifn_mbuf = m;
	ms = (struct mbuf_segment *)ifn->ifn_waddr;
	n = 0;
	while (m) {
		ms->ms_physaddr = kvtophys(mtod(m, caddr_t));
		ms->ms_size = m->m_len;
		if ((i = (ms->ms_physaddr & PGOFSET) + ms->ms_size) > NBPG) {
			i -= NBPG;
			ms->ms_size -= i;
			ms++;
			ms->ms_physaddr =
			    kvtophys(mtod(m, caddr_t) + m->m_len - i);
			ms->ms_size = i;
		}
		ms++;
		n += m->m_len;
		m = m->m_next;
	}
	ms->ms_physaddr = 0;
	return (n);
#else /* CPU_DOUBLE */
	register struct mbuf *mp;
	register caddr_t cp;

	cp = ifn->ifn_waddr;
	while (m) {
#ifdef mips
		bxcopy(mtod(m, caddr_t), cp, (unsigned)m->m_len);
#else
		bcopy(mtod(m, caddr_t), cp, (unsigned)m->m_len);
#endif
		cp += m->m_len;
		MFREE(m, mp);
		m = mp;
	}
	return (cp - ifn->ifn_waddr);
#endif /* CPU_DOUBLE */
}
E 1
