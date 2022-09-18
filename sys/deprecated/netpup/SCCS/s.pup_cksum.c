h02719
s 00007/00001/00063
d D 6.3 85/06/08 13:45:11 mckusick 4 3
c Add copyright
e
s 00002/00002/00062
d D 6.2 84/08/28 18:10:36 bloom 3 2
c Change to includes.  No more ../h
e
s 00000/00000/00064
d D 6.1 83/07/29 07:21:02 sam 2 1
c 4.2 distribution
e
s 00064/00000/00000
d D 4.1 83/05/30 18:37:27 sam 1 0
c date and time created 83/05/30 18:37:27 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 4

D 3
#include "../h/types.h"
#include "../h/mbuf.h"
E 3
I 3
#include "types.h"
#include "mbuf.h"
E 3

/*
 * Checksum routine for PUP-I Protocol family (VAX Version).
 */
pup_cksum(m, len)
	register struct mbuf *m;
	register int len;
{
	register u_short *w;
	register int sum = 0;			/* known to be r8 */
	register int mlen = 0;

	for (;;) {
		/*
		 * Each trip around loop adds in
		 * words from one mbuf segment.
		 */
		w = mtod(m, u_short *);
		if (mlen == -1) {
			/*
			 * There is a byte left from the last segment;
			 * add it into the checksum. 
			 */
			sum += *(u_char *)w << 8;
			asm("rotl $1,r8,r8");
			w = (u_short *)((char *)w + 1);
			mlen = m->m_len - 1;
			len--;
		} else
			mlen = m->m_len;
		m = m->m_next;
		if (len < mlen)
			mlen = len;
		len -= mlen;
		while ((mlen -= 2) >= 0) {
			asm("addw2 (r9)+,r8; rotl $1,r8,r8;");
		}
		if (mlen == -1)
			sum += *(u_char *)w;
		if (len == 0)
			break;
		/*
		 * Locate the next block with some data.
		 * If there is a word split across a boundary we
		 * will wrap to the top with mlen == -1 and
		 * then add it in shifted appropriately.
		 */
		for (;;) {
			if (m == 0) {
				printf("pup_cksum: out of data\n");
				goto done;
			}
			if (m->m_len)
				break;
			m = m->m_next;
		}
	}
done:
	return (sum);
}
E 1
