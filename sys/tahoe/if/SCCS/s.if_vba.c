h03612
s 00013/00013/00179
d D 1.4 90/12/16 16:44:00 bostic 4 3
c kernel reorg
e
s 00001/00011/00191
d D 1.3 90/06/28 22:24:36 bostic 3 2
c new copyright notice
e
s 00029/00019/00173
d D 1.2 89/04/22 12:17:04 sklower 2 1
c first working version of BSD/tahoe ex driver; checkpoint other 
c drivers as of first working iso/tp4 connection & before gnodes
e
s 00192/00000/00000
d D 1.1 89/03/09 11:20:06 sklower 1 0
c date and time created 89/03/09 11:20:06 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
D 3
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "buf.h"
#include "cmap.h"
#include "vmmac.h"
#include "socket.h"
E 4
I 4
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/mbuf.h"
#include "sys/buf.h"
#include "sys/cmap.h"
#include "sys/vmmac.h"
#include "sys/socket.h"
E 4

D 4
#include "../tahoe/mtpr.h"
#include "../tahoe/pte.h"
E 4
I 4
#include "../include/mtpr.h"
#include "../include/pte.h"
E 4

D 4
#include "../tahoevba/vbavar.h"
E 4
I 4
#include "../vba/vbavar.h"
E 4

D 4
#include "../net/if.h"
#include "../netinet/in.h"
#include "../netinet/if_ether.h"
E 4
I 4
#include "net/if.h"
#include "netinet/in.h"
#include "netinet/if_ether.h"
E 4

#include "if_vba.h"

D 2
if_vbareserve(ifvba0, n, size)
E 2
I 2
if_vbareserve(ifvba0, n, bufsize, extra, extrasize)
E 2
struct ifvba *ifvba0;
register int n;
D 2
int size;
E 2
I 2
int bufsize;
caddr_t *extra;
int extrasize;
E 2
{
	register caddr_t cp;
	register struct pte *pte;
	register struct ifvba *ifvba = ifvba0;
	struct ifvba *vlim  = ifvba + n;

D 2
	n = roundup(n * size, NBPG);
E 2
I 2
	n = roundup(extrasize + (n * bufsize), NBPG);
E 2
	cp = (caddr_t)malloc((u_long)n, M_DEVBUF, M_NOWAIT);
I 2
	if ((n + kvtophys(cp)) > VB_MAXADDR24) {
		free(cp, M_DEVBUF);
		cp = 0;
	}
E 2
	if (cp == 0) {
D 2
		printf("No memory for device buffer\n");
E 2
I 2
		printf("No memory for device buffer(s)\n");
E 2
		return (0);
	}
	/*
	 * Make raw buffer pages uncacheable.
	 */
	pte = kvtopte(cp);
	for (n = btoc(n); n--; pte++)
		pte->pg_nc = 1;
	mtpr(TBIA, 0);
I 2
	if (extra) {
		*extra = cp;
		cp += extrasize;
	}
E 2
	for (; ifvba < vlim; ifvba++) {
		ifvba->iff_buffer = cp;
		ifvba->iff_physaddr = kvtophys(cp);
D 2
		cp += size;
E 2
I 2
		cp += bufsize;
E 2
	}
	return (1);
}
/*
 * Routine to copy from VERSAbus memory into mbufs.
 *
 * Warning: This makes the fairly safe assumption that
 * mbufs have even lengths.
 */
struct mbuf *
if_vbaget(rxbuf, totlen, off, ifp, flags)
D 2
	u_char *rxbuf;
E 2
I 2
	caddr_t rxbuf;
E 2
	int totlen, off, flags;
	struct ifnet *ifp;
{
D 2
	register u_char *cp;
E 2
I 2
	register caddr_t cp;
E 2
	register struct mbuf *m;
	struct mbuf *top = 0, **mp = &top;
	int len;
D 2
	u_char *packet_end;
E 2
I 2
	caddr_t packet_end;
E 2

	rxbuf += sizeof (struct ether_header);
	cp = rxbuf;
	packet_end = cp + totlen;
	if (off) {
		off += 2 * sizeof(u_short);
		totlen -= 2 *sizeof(u_short);
		cp = rxbuf + off;
	}

	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m == 0)
		return (0);
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = totlen;
	m->m_len = MHLEN;

	while (totlen > 0) {
		if (top) {
			MGET(m, M_DONTWAIT, MT_DATA);
			if (m == 0) {
				m_freem(top);
				return (0);
			}
			m->m_len = MLEN;
		}
		len = min(totlen, (packet_end - cp));
		if (len >= MINCLSIZE) {
			MCLGET(m, M_DONTWAIT);
			if (m->m_flags & M_EXT)
				m->m_len = len = min(len, MCLBYTES);
			else
				len = m->m_len;
		} else {
			/*
			 * Place initial small packet/header at end of mbuf.
			 */
			if (len < m->m_len) {
				if (top == 0 && len + max_linkhdr <= m->m_len)
					m->m_data += max_linkhdr;
				m->m_len = len;
			} else
				len = m->m_len;
		}
		if (flags)
D 2
			if_vba16copy(cp, mtod(m, u_char *), (u_int)len);
E 2
I 2
			if_vba16copy(cp, mtod(m, caddr_t), (u_int)len);
E 2
		else
D 2
			bcopy(cp, mtod(m, u_char *), (u_int)len);
E 2
I 2
			bcopy(cp, mtod(m, caddr_t), (u_int)len);
E 2

		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		cp += len;
		if (cp == packet_end)
			cp = rxbuf;
	}
	return (top);
}

if_vbaput(ifu, m0, flags)
D 2
register u_char *ifu;
register struct mbuf *m0;
E 2
I 2
caddr_t ifu;
struct mbuf *m0;
E 2
{
	register struct mbuf *m = m0;
D 2
	register u_char *cp = ifu;
E 2
I 2
	register caddr_t cp = ifu;
E 2

	while (m) {
		if (flags)
D 2
			if_vba16copy(mtod(m, u_char *), cp, m->m_len);
E 2
I 2
			if_vba16copy(mtod(m, caddr_t), cp, (u_int)m->m_len);
E 2
		else
D 2
			bcopy(mtod(m, u_char *), cp, m->m_len);
E 2
I 2
			bcopy(mtod(m, caddr_t), cp, (u_int)m->m_len);
E 2
		cp += m->m_len;
		MFREE(m, m0);
		m = m0;
	}
	if ((int)cp & 1)
		*cp++ = 0;
	return (cp - ifu);
}

if_vba16copy(from, to, cnt)
D 2
	register u_char *from, *to;
	register u_int cnt;
E 2
I 2
	register caddr_t from, to;
	register unsigned cnt;
E 2
{
	register c;
	register short *f, *t;

	if (((int)from&01) && ((int)to&01)) {
		/* source & dest at odd addresses */
		*to++ = *from++;
		--cnt;
	}
	if (cnt > 1 && (((int)to&01) == 0) && (((int)from&01) == 0)) {
		t = (short *)to;
		f = (short *)from;
		for (c = cnt>>1; c; --c)	/* even address copy */
			*t++ = *f++;
		cnt &= 1;
		if (cnt) {			/* odd len */
D 2
			from = (u_char *)f;
			to = (u_char *)t;
E 2
I 2
			from = (caddr_t)f;
			to = (caddr_t)t;
E 2
			*to = *from;
		}
	}
	while ((int)cnt-- > 0)	/* one of the address(es) must be odd */
		*to++ = *from++;
}
E 1
