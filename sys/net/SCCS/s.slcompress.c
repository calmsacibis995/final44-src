h49991
s 00002/00001/00507
d D 8.2 94/04/16 12:18:45 bostic 11 10
c If compressed TCP packets were being received on a SLIP
c link while it was first configured, the system could
c crash if a packet with a compressed connection ID was received.
c BSDI's patch SK110-004
e
s 00002/00002/00506
d D 8.1 93/06/10 22:45:42 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00507
d D 7.9 93/06/04 17:31:04 bostic 9 8
c prototype everything
e
s 00002/00001/00508
d D 7.8 92/10/11 11:49:10 bostic 8 7
c make kernel includes standard
e
s 00013/00011/00496
d D 7.7 91/05/07 12:06:34 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00011/00506
d D 7.6 90/06/28 21:32:37 bostic 6 5
c new copyright notice
e
s 00103/00075/00414
d D 7.5 90/01/20 17:34:18 sam 5 4
c new version from van (beta release)
e
s 00003/00002/00486
d D 7.4 89/07/01 10:08:46 sam 4 3
c must handle alignment for packets w/o data
e
s 00084/00093/00404
d D 7.3 89/06/30 15:12:21 karels 3 2
c new version from van
e
s 00002/00005/00495
d D 7.2 89/06/29 09:05:15 sam 2 1
c checkpoint; should fix previous bug, but see next version
e
s 00500/00000/00000
d D 7.1 89/06/28 11:48:36 sam 1 0
c date and time created 89/06/28 11:48:36 by sam
e
u
U
t
T
I 5
D 7
/*	%M%	%I%	%E%	*/
E 5
I 1
D 3
/*	%M%	%I%	%E%	*/

E 3
/*
I 3
D 5
 *	%W% (Berkeley) %G%
 *
E 3
 *			THIS CODE IS NOT FOR DISTRIBUTION!
 *	KEEP YOUR GRUBBY HANDS OFF UNLESS AUTHORIZED BY VAN JACOBSON TO COPY!
 *			ASK SAM, MIKE, OR BILL ABOUT IT.
D 3
 */

/*
E 3
I 3
 *
E 5
E 3
 * Routines to compress and uncompess tcp packets (for transmission
 * over low speed serial lines.
 *
D 5
 * Copyright (c) 1988, 1989 by Van Jacobson, Lawrence Berkeley Laboratory
E 5
I 5
 * Copyright (c) 1989 Regents of the University of California.
E 7
I 7
/*-
D 10
 * Copyright (c) 1989 The Regents of the University of California.
E 7
E 5
 * All rights reserved.
E 10
I 10
D 11
 * Copyright (c) 1989, 1993
E 11
I 11
 * Copyright (c) 1989, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 10
I 5
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
D 7
 *	Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:
E 7
I 7
 *	%W% (Berkeley) %G%
 */

/*
 * Routines to compress and uncompess tcp packets (for transmission
 * over low speed serial lines.
 *
 * Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:
E 7
 *	- Initial distribution.
I 7
 *
 * static char rcsid[] =
 * "$Header: slcompress.c,v 1.19 89/12/31 08:52:59 van Exp $";
E 7
E 5
 */
D 5

I 3
#include "sl.h"
#if NSL > 0
E 5
E 3
D 7
#ifndef lint
D 3
static char rcsid[] = "$Header: slcompress.c,v 1.7 89/03/19 18:10:19 van Locked $";
E 3
I 3
D 5
static char rcsid[] = "$Header: slcompress.c,v 1.10 89/06/05 08:28:52 van Exp $";
E 5
I 5
static char rcsid[] = "$Header: slcompress.c,v 1.19 89/12/31 08:52:59 van Exp $";
E 5
E 3
#endif
E 7

D 7
#include <sys/types.h>
E 7
#include <sys/param.h>
#include <sys/mbuf.h>
I 8

E 8
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

D 8
#include "slcompress.h"
E 8
I 8
#include <net/slcompress.h>
E 8

D 3
int sls_packets;
int sls_searches;
int sls_misses;
int sls_compressed;
int sls_ipin;
int sls_uncompressedin;
int sls_compressedin;
E 3
I 3
D 5
#ifndef NO_SL_STATS
E 5
I 5
#ifndef SL_NO_STATS
E 5
#define INCR(counter) ++comp->counter;
#else
#define INCR(counter)
#endif
E 3

#define BCMP(p1, p2, n) bcmp((char *)(p1), (char *)(p2), (int)(n))
#define BCOPY(p1, p2, n) bcopy((char *)(p1), (char *)(p2), (int)(n))
I 5
#ifndef KERNEL
#define ovbcopy bcopy
#endif
E 5

D 3
#ifndef KERNEL
extern struct mbuf *m_get();
#undef MGET
#define MGET(m, w, t) ((m) = m_get((w), (t)))
#endif
E 3
D 9

E 9
D 3
#if BSD>=198810
#define m_off m_data
#endif

E 3
void
sl_compress_init(comp)
	struct slcompress *comp;
{
	register u_int i;
	register struct cstate *tstate = comp->tstate;

	bzero((char *)comp, sizeof(*comp));
	for (i = MAX_STATES - 1; i > 0; --i) {
		tstate[i].cs_id = i;
		tstate[i].cs_next = &tstate[i - 1];
	}
	tstate[0].cs_next = &tstate[MAX_STATES - 1];
	tstate[0].cs_id = 0;
	comp->last_cs = &tstate[0];
	comp->last_recv = 255;
	comp->last_xmit = 255;
I 11
	comp->flags = SLF_TOSS;
E 11
}


/* ENCODE encodes a number that is known to be non-zero.  ENCODEZ
 * checks for zero (since zero has to be encoded in the long, 3 byte
 * form).
 */
#define ENCODE(n) { \
	if ((u_short)(n) >= 256) { \
		*cp++ = 0; \
		cp[1] = (n); \
		cp[0] = (n) >> 8; \
		cp += 2; \
	} else { \
		*cp++ = (n); \
	} \
}
#define ENCODEZ(n) { \
	if ((u_short)(n) >= 256 || (u_short)(n) == 0) { \
		*cp++ = 0; \
		cp[1] = (n); \
		cp[0] = (n) >> 8; \
		cp += 2; \
	} else { \
		*cp++ = (n); \
	} \
}

#define DECODEL(f) { \
	if (*cp == 0) {\
		(f) = htonl(ntohl(f) + ((cp[1] << 8) | cp[2])); \
		cp += 3; \
	} else { \
		(f) = htonl(ntohl(f) + (u_long)*cp++); \
	} \
}

#define DECODES(f) { \
	if (*cp == 0) {\
		(f) = htons(ntohs(f) + ((cp[1] << 8) | cp[2])); \
		cp += 3; \
	} else { \
		(f) = htons(ntohs(f) + (u_long)*cp++); \
	} \
}

I 5
#define DECODEU(f) { \
	if (*cp == 0) {\
		(f) = htons((cp[1] << 8) | cp[2]); \
		cp += 3; \
	} else { \
		(f) = htons((u_long)*cp++); \
	} \
}
E 5

I 5
D 9

E 5
u_char
E 9
I 9
u_int
E 9
D 5
sl_compress_tcp(m, ip, comp)
E 5
I 5
sl_compress_tcp(m, ip, comp, compress_cid)
E 5
	struct mbuf *m;
	register struct ip *ip;
	struct slcompress *comp;
I 5
	int compress_cid;
E 5
{
	register struct cstate *cs = comp->last_cs->cs_next;
	register u_int hlen = ip->ip_hl;
	register struct tcphdr *oth;
	register struct tcphdr *th;
	register u_int deltaS, deltaA;
	register u_int changes = 0;
	u_char new_seq[16];
	register u_char *cp = new_seq;

	/*
D 5
	 * Bail if this is an ip fragment or if we don't have
	 * a complete ip & tcp header in the first mbuf.  Otherwise,
	 * check flags to see if this is a packet we might compress 
	 * and, if so, try to locate the connection state.
D 3
	 * since slip links tend to be end nodes, check the tcp ports
	 * first since the inet addresses won't usually change.
E 3
	 * special case the most recently used connection since
	 * it's most likely to be used again & we don't have to
	 * do any reordering if it's used.
E 5
I 5
	 * Bail if this is an IP fragment or if the TCP packet isn't
	 * `compressible' (i.e., ACK isn't set or some other control bit is
	 * set).  (We assume that the caller has already made sure the
	 * packet is IP proto TCP).
E 5
	 */
D 5
	if ((ip->ip_off & 0x3fff) || m->m_len < 40)
E 5
I 5
	if ((ip->ip_off & htons(0x3fff)) || m->m_len < 40)
E 5
		return (TYPE_IP);

	th = (struct tcphdr *)&((int *)ip)[hlen];
	if ((th->th_flags & (TH_SYN|TH_FIN|TH_RST|TH_ACK)) != TH_ACK)
		return (TYPE_IP);
D 5

E 5
I 5
	/*
	 * Packet is compressible -- we're going to send either a
	 * COMPRESSED_TCP or UNCOMPRESSED_TCP packet.  Either way we need
	 * to locate (or create) the connection state.  Special case the
	 * most recently used connection since it's most likely to be used
	 * again & we don't have to do any reordering if it's used.
	 */
E 5
D 3
	++sls_packets;
	if (*(int *)th != ((int *)&cs->cs_ip)[cs->cs_ip.ip_hl] ||
	    ip->ip_src.s_addr != cs->cs_ip.ip_src.s_addr ||
	    ip->ip_dst.s_addr != cs->cs_ip.ip_dst.s_addr) {
E 3
I 3
	INCR(sls_packets)
	if (ip->ip_src.s_addr != cs->cs_ip.ip_src.s_addr ||
	    ip->ip_dst.s_addr != cs->cs_ip.ip_dst.s_addr ||
	    *(int *)th != ((int *)&cs->cs_ip)[cs->cs_ip.ip_hl]) {
E 3
		/*
		 * Wasn't the first -- search for it.
		 *
		 * States are kept in a circularly linked list with
D 5
		 * first_cs pointing to the head of the list.  The
E 5
I 5
		 * last_cs pointing to the end of the list.  The
E 5
		 * list is kept in lru order by moving a state to the
		 * head of the list whenever it is referenced.  Since
		 * the list is short and, empirically, the connection
		 * we want is almost always near the front, we locate
		 * states via linear search.  If we don't find a state
D 5
		 * for the datagram, the oldest state is used.
E 5
I 5
		 * for the datagram, the oldest state is (re-)used.
E 5
		 */
		register struct cstate *lcs;
I 5
		register struct cstate *lastcs = comp->last_cs;
E 5

		do {
			lcs = cs; cs = cs->cs_next;
D 3
			++sls_searches;
E 3
I 3
			INCR(sls_searches)
E 3
D 5
			if (*(int *)th == ((int *)&cs->cs_ip)[cs->cs_ip.ip_hl]
			    && ip->ip_src.s_addr == cs->cs_ip.ip_src.s_addr
			    && ip->ip_dst.s_addr == cs->cs_ip.ip_dst.s_addr)
E 5
I 5
			if (ip->ip_src.s_addr == cs->cs_ip.ip_src.s_addr
			    && ip->ip_dst.s_addr == cs->cs_ip.ip_dst.s_addr
			    && *(int *)th == ((int *)&cs->cs_ip)[cs->cs_ip.ip_hl])
E 5
				goto found;
D 5
		} while (cs != comp->last_cs);
D 3
		++sls_misses;
E 3
I 3
		INCR(sls_misses)
E 5
I 5
		} while (cs != lastcs);
E 5
E 3

		/*
D 5
		 * Didn't find it -- re-use oldest cstate.
		 * Send an uncompressed packet that tells
		 * the other side what connection number
		 * we're using for this conversation.  Note
		 * that since the state list is circular, the
		 * oldest state points to the newest and we only
		 * need to set last_cs to update the lru linkage.
E 5
I 5
		 * Didn't find it -- re-use oldest cstate.  Send an
		 * uncompressed packet that tells the other side what
		 * connection number we're using for this conversation.
		 * Note that since the state list is circular, the oldest
		 * state points to the newest and we only need to set
		 * last_cs to update the lru linkage.
E 5
		 */
I 5
		INCR(sls_misses)
E 5
		comp->last_cs = lcs;
		hlen += th->th_off;
		hlen <<= 2;
		goto uncompressed;

	found:
		/*
		 * Found it -- move to the front on the connection list.
		 */
D 5
		if (comp->last_cs == cs)
E 5
I 5
		if (cs == lastcs)
E 5
			comp->last_cs = lcs;
		else {
			lcs->cs_next = cs->cs_next;
D 5
			cs->cs_next = comp->last_cs->cs_next;
			comp->last_cs->cs_next = cs;
E 5
I 5
			cs->cs_next = lastcs->cs_next;
			lastcs->cs_next = cs;
E 5
		}
	}

	/*
D 5
	 * Make sure that only what we expect to change changed.
E 5
I 5
	 * Make sure that only what we expect to change changed. The first
	 * line of the `if' checks the IP protocol version, header length &
	 * type of service.  The 2nd line checks the "Don't fragment" bit.
	 * The 3rd line checks the time-to-live and protocol (the protocol
	 * check is unnecessary but costless).  The 4th line checks the TCP
	 * header length.  The 5th line checks IP options, if any.  The 6th
	 * line checks TCP options, if any.  If any of these things are
	 * different between the previous & current datagram, we send the
	 * current datagram `uncompressed'.
E 5
	 */
	oth = (struct tcphdr *)&((int *)&cs->cs_ip)[hlen];
	deltaS = hlen;
	hlen += th->th_off;
	hlen <<= 2;

	if (((u_short *)ip)[0] != ((u_short *)&cs->cs_ip)[0] ||
I 5
	    ((u_short *)ip)[3] != ((u_short *)&cs->cs_ip)[3] ||
E 5
	    ((u_short *)ip)[4] != ((u_short *)&cs->cs_ip)[4] ||
	    th->th_off != oth->th_off ||
	    (deltaS > 5 &&
	     BCMP(ip + 1, &cs->cs_ip + 1, (deltaS - 5) << 2)) ||
	    (th->th_off > 5 &&
	     BCMP(th + 1, oth + 1, (th->th_off - 5) << 2)))
		goto uncompressed;

	/*
	 * Figure out which of the changing fields changed.  The
	 * receiver expects changes in the order: urgent, window,
	 * ack, seq (the order minimizes the number of temporaries
	 * needed in this section of code).
	 */
	if (th->th_flags & TH_URG) {
		deltaS = ntohs(th->th_urp);
		ENCODEZ(deltaS);
		changes |= NEW_U;
	} else if (th->th_urp != oth->th_urp)
		/* argh! URG not set but urp changed -- a sensible
		 * implementation should never do this but RFC793
		 * doesn't prohibit the change so we have to deal
D 5
		 * with it.  */
E 5
I 5
		 * with it. */
E 5
		 goto uncompressed;

	if (deltaS = (u_short)(ntohs(th->th_win) - ntohs(oth->th_win))) {
		ENCODE(deltaS);
		changes |= NEW_W;
	}

	if (deltaA = ntohl(th->th_ack) - ntohl(oth->th_ack)) {
		if (deltaA > 0xffff)
			goto uncompressed;
		ENCODE(deltaA);
		changes |= NEW_A;
	}

	if (deltaS = ntohl(th->th_seq) - ntohl(oth->th_seq)) {
		if (deltaS > 0xffff)
			goto uncompressed;
		ENCODE(deltaS);
		changes |= NEW_S;
	}

	switch(changes) {

	case 0:
D 5
		if (ip->ip_len != cs->cs_ip.ip_len && ntohs(ip->ip_len) != hlen)
			break;
E 5
		/*
D 5
		 * Nothing changed and this packet looks like a duplicate
		 * of the last or contains no data -- this is probably a
		 * retransmitted ack or window probe.  Send it
		 * uncompressed in case the other side missed the
		 * compressed version.
		 *
		 * (fall through)
E 5
I 5
		 * Nothing changed. If this packet contains data and the
		 * last one didn't, this is probably a data packet following
		 * an ack (normal on an interactive connection) and we send
		 * it compressed.  Otherwise it's probably a retransmit,
		 * retransmitted ack or window probe.  Send it uncompressed
		 * in case the other side missed the compressed version.
E 5
		 */
I 5
		if (ip->ip_len != cs->cs_ip.ip_len &&
		    ntohs(cs->cs_ip.ip_len) == hlen)
			break;
E 5

I 5
		/* (fall through) */

E 5
	case SPECIAL_I:
	case SPECIAL_D:
		/*
		 * actual changes match one of our special case encodings --
		 * send packet uncompressed.
		 */
		goto uncompressed;

	case NEW_S|NEW_A:
		if (deltaS == deltaA &&
		    deltaS == ntohs(cs->cs_ip.ip_len) - hlen) {
			/* special case for echoed terminal traffic */
			changes = SPECIAL_I;
			cp = new_seq;
		}
		break;

	case NEW_S:
		if (deltaS == ntohs(cs->cs_ip.ip_len) - hlen) {
			/* special case for data xfer */
			changes = SPECIAL_D;
			cp = new_seq;
		}
		break;
	}

	deltaS = ntohs(ip->ip_id) - ntohs(cs->cs_ip.ip_id);
	if (deltaS != 1) {
		ENCODEZ(deltaS);
		changes |= NEW_I;
	}
	if (th->th_flags & TH_PUSH)
		changes |= TCP_PUSH_BIT;
	/*
	 * Grab the cksum before we overwrite it below.  Then update our
	 * state with this packet's header.
	 */
	deltaA = ntohs(th->th_sum);
	BCOPY(ip, &cs->cs_ip, hlen);

	/*
	 * We want to use the original packet as our compressed packet.
	 * (cp - new_seq) is the number of bytes we need for compressed
	 * sequence numbers.  In addition we need one byte for the change
	 * mask, one for the connection id and two for the tcp checksum.
	 * So, (cp - new_seq) + 4 bytes of header are needed.  hlen is how
	 * many bytes of the original packet to toss so subtract the two to
	 * get the new packet size.
	 */
	deltaS = cp - new_seq;
	cp = (u_char *)ip;
D 5
	if (comp->last_xmit != cs->cs_id) {
E 5
I 5
	if (compress_cid == 0 || comp->last_xmit != cs->cs_id) {
E 5
		comp->last_xmit = cs->cs_id;
		hlen -= deltaS + 4;
D 3
		cp += hlen; m->m_len -= hlen; m->m_off += hlen;
D 2
		*cp++ = changes | NEW_C;
E 2
I 2
		*cp++ = TYPE_COMPRESSED_TCP | changes | NEW_C;
E 3
I 3
		cp += hlen;
D 5
		m->m_len -= hlen;
		m->m_data += hlen;
E 5
		*cp++ = changes | NEW_C;
E 3
E 2
		*cp++ = cs->cs_id;
	} else {
		hlen -= deltaS + 3;
D 3
		cp += hlen; m->m_len -= hlen; m->m_off += hlen;
D 2
		*cp++ = changes;
E 2
I 2
		*cp++ = TYPE_COMPRESSED_TCP | changes;
E 3
I 3
		cp += hlen;
D 5
		m->m_len -= hlen;
		m->m_data += hlen;
E 5
		*cp++ = changes;
E 3
E 2
	}
I 5
	m->m_len -= hlen;
	m->m_data += hlen;
E 5
	*cp++ = deltaA >> 8;
	*cp++ = deltaA;
	BCOPY(new_seq, cp, deltaS);
D 3
	++sls_compressed;
E 3
I 3
	INCR(sls_compressed)
E 3
D 2
	/* note: low order version bits used */
	ip = mtod(m, struct ip *);
	ip->ip_v |= (TYPE_COMPRESSED_TCP>>4);
E 2
	return (TYPE_COMPRESSED_TCP);

	/*
	 * Update connection state cs & send uncompressed packet ('uncompressed'
	 * means a regular ip/tcp packet but with the 'conversation id' we hope
	 * to use on future compressed packets in the protocol field).
	 */
uncompressed:
	BCOPY(ip, &cs->cs_ip, hlen);
	ip->ip_p = cs->cs_id;
	comp->last_xmit = cs->cs_id;
D 3
	ip->ip_v = (TYPE_UNCOMPRESSED_TCP>>4);
E 3
	return (TYPE_UNCOMPRESSED_TCP);
}

D 3
int uncdeb ;
E 3

D 3
struct mbuf *
sl_uncompress_tcp(m, type, comp)
	register struct mbuf *m;
	u_char type;
E 3
I 3
int
sl_uncompress_tcp(bufp, len, type, comp)
	u_char **bufp;
	int len;
	u_int type;
E 3
	struct slcompress *comp;
{
	register u_char *cp;
	register u_int hlen, changes;
	register struct tcphdr *th;
	register struct cstate *cs;
	register struct ip *ip;
D 3
	register struct mbuf *m0;
E 3

	switch (type) {

	case TYPE_UNCOMPRESSED_TCP:
D 3
		ip = mtod(m, struct ip *);
		if (ip->ip_p >= MAX_STATES)
			goto bad;
		ip->ip_v = 4;

E 3
I 3
		ip = (struct ip *) *bufp;
D 5
		if (ip->ip_p >= MAX_STATES) {
			INCR(sls_errorin)
			return (0);
		}
E 5
I 5
		if (ip->ip_p >= MAX_STATES)
			goto bad;
E 5
E 3
		cs = &comp->rstate[comp->last_recv = ip->ip_p];
		comp->flags &=~ SLF_TOSS;
		ip->ip_p = IPPROTO_TCP;
		hlen = ip->ip_hl;
		hlen += ((struct tcphdr *)&((int *)ip)[hlen])->th_off;
		hlen <<= 2;
		BCOPY(ip, &cs->cs_ip, hlen);
		cs->cs_ip.ip_sum = 0;
		cs->cs_hlen = hlen;
D 3
		++sls_uncompressedin;
		return (m);
E 3
I 3
		INCR(sls_uncompressedin)
		return (len);
E 3

D 3
	default:
	if(type&TYPE_COMPRESSED_TCP) goto compre;
		++sls_ipin;
		return (m);

E 3
D 5
	case TYPE_ERROR:
		comp->flags |= SLF_TOSS;
E 5
D 3
		return (m);
E 3
I 3
	default:
D 5
		INCR(sls_errorin)
		return (0);
E 5
I 5
		goto bad;
E 5
E 3

	case TYPE_COMPRESSED_TCP:
D 3
compre:
E 3
		break;
	}
	/* We've got a compressed packet. */
D 3
	++sls_compressedin;
	cp = mtod(m, u_char *);
E 3
I 3
	INCR(sls_compressedin)
	cp = *bufp;
E 3
	changes = *cp++;
	if (changes & NEW_C) {
		/* Make sure the state index is in range, then grab the state.
		 * If we have a good state index, clear the 'discard' flag. */
D 3
		if (*cp >= MAX_STATES)
			goto bad;

E 3
I 3
D 5
		if (*cp >= MAX_STATES) {
			INCR(sls_errorin)
			return (0);
		}
E 5
I 5
		if (*cp >= MAX_STATES)
			goto bad;

E 5
E 3
		comp->flags &=~ SLF_TOSS;
		comp->last_recv = *cp++;
	} else {
		/* this packet has an implicit state index.  If we've
		 * had a line error since the last time we got an
		 * explicit state index, we have to toss the packet. */
D 3
		if (comp->flags & SLF_TOSS)
			goto bad;
E 3
I 3
		if (comp->flags & SLF_TOSS) {
			INCR(sls_tossed)
			return (0);
		}
E 3
	}
	cs = &comp->rstate[comp->last_recv];
	hlen = cs->cs_ip.ip_hl << 2;
	th = (struct tcphdr *)&((u_char *)&cs->cs_ip)[hlen];
	th->th_sum = htons((*cp << 8) | cp[1]);
	cp += 2;
	if (changes & TCP_PUSH_BIT)
		th->th_flags |= TH_PUSH;
	else
		th->th_flags &=~ TH_PUSH;

	switch (changes & SPECIALS_MASK) {
	case SPECIAL_I:
		{
		register u_int i = ntohs(cs->cs_ip.ip_len) - cs->cs_hlen;
		th->th_ack = htonl(ntohl(th->th_ack) + i);
		th->th_seq = htonl(ntohl(th->th_seq) + i);
		}
		break;

	case SPECIAL_D:
		th->th_seq = htonl(ntohl(th->th_seq) + ntohs(cs->cs_ip.ip_len)
				   - cs->cs_hlen);
		break;

	default:
		if (changes & NEW_U) {
			th->th_flags |= TH_URG;
D 5
			DECODES(th->th_urp)
E 5
I 5
			DECODEU(th->th_urp)
E 5
		} else
			th->th_flags &=~ TH_URG;
		if (changes & NEW_W)
			DECODES(th->th_win)
		if (changes & NEW_A)
			DECODEL(th->th_ack)
		if (changes & NEW_S)
			DECODEL(th->th_seq)
		break;
	}
	if (changes & NEW_I) {
		DECODES(cs->cs_ip.ip_id)
	} else
		cs->cs_ip.ip_id = htons(ntohs(cs->cs_ip.ip_id) + 1);

	/*
	 * At this point, cp points to the first byte of data in the
D 3
	 * packet (if any).  Toss the compressed header from the
	 * original packet, allocatate a new mbuf for the uncompressed
	 * header (to make sure it's aligned correctly), then chain it
	 * in front of the original.  Set up the ip length & ip checksum then
	 * return the rebuilt packet.
E 3
I 3
	 * packet.  If we're not aligned on a 4-byte boundary, copy the
	 * data down so the ip & tcp headers will be aligned.  Then back up
	 * cp by the tcp/ip header length to make room for the reconstructed
	 * header (we assume the packet we were handed has enough space to
D 5
	 * prepend 128 bytes of header).  Adjust the lenth to account for
E 5
I 5
	 * prepend 128 bytes of header).  Adjust the length to account for
E 5
	 * the new header & fill in the IP total length.
E 3
	 */
D 3
	changes = cp - mtod(m, u_char *);
	m->m_off += changes; m->m_len -= changes;
	changes = cs->cs_hlen;
	for (m0 = m; m0; m0 = m0->m_next)
		changes += m0->m_len;
	cs->cs_ip.ip_len = htons(changes);
E 3
I 3
	len -= (cp - *bufp);
D 5
	if (len < 0) {
E 5
I 5
	if (len < 0)
E 5
		/* we must have dropped some characters (crc should detect
		 * this but the old slip framing won't) */
D 5
		INCR(sls_errorin)
		return (0);
	}
E 5
I 5
		goto bad;

E 5
D 4
	if (len && ((int)cp & ~3) != (int)cp) {
		(void) bcopy((caddr_t)cp, (caddr_t)((int)cp &~ 3), len);
E 4
I 4
	if ((int)cp & 3) {
		if (len > 0)
D 5
			BCOPY(cp, (int)cp &~ 3, len);
E 5
I 5
			(void) ovbcopy(cp, (caddr_t)((int)cp &~ 3), len);
E 5
E 4
		cp = (u_char *)((int)cp &~ 3);
	}
	cp -= cs->cs_hlen;
	len += cs->cs_hlen;
	cs->cs_ip.ip_len = htons(len);
	BCOPY(&cs->cs_ip, cp, cs->cs_hlen);
	*bufp = cp;
E 3

D 3
	/*MGET(m0, M_DONTWAIT, MT_DATA);*/
	MGETHDR(m0, M_DONTWAIT, MT_DATA);		/* XXX! */
	if (! m0)
		goto bad;

	m0->m_next = m;
	m0->m_pkthdr.rcvif = m->m_pkthdr.rcvif ;	/* XXX! */
	m0->m_pkthdr.len = m->m_pkthdr.len;		/* XXX! */
	m = m0;
	m->m_len = cs->cs_hlen;
	ip = mtod(m, struct ip *);
	BCOPY(&cs->cs_ip, ip, cs->cs_hlen);

	ip->ip_sum = in_cksum(m, hlen);
	return (m);

bad:
	m_freem(m);
	return ((struct mbuf *)0);
E 3
I 3
	/* recompute the ip header checksum */
	{
		register u_short *bp = (u_short *)cp;
		for (changes = 0; hlen > 0; hlen -= 2)
			changes += *bp++;
		changes = (changes & 0xffff) + (changes >> 16);
		changes = (changes & 0xffff) + (changes >> 16);
		((struct ip *)cp)->ip_sum = ~ changes;
	}
	return (len);
I 5
bad:
	comp->flags |= SLF_TOSS;
	INCR(sls_errorin)
	return (0);
E 5
E 3
}
I 3
D 5
#endif
E 5
E 3
E 1
