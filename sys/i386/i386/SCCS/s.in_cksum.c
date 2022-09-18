h24062
s 00002/00002/00103
d D 8.1 93/06/11 15:34:44 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00100
d D 7.2 92/10/11 10:10:56 bostic 5 4
c make kernel includes standard
e
s 00000/00000/00104
d D 7.1 92/02/05 10:53:30 bostic 4 3
c no changes, yank to version 7.1
e
s 00014/00006/00090
d D 1.3 91/01/19 12:43:07 william 3 2
c kernel reorg
e
s 00000/00000/00096
d D 1.2 91/01/15 12:22:06 bill 2 1
c reno changes
e
s 00096/00000/00000
d D 1.1 90/11/14 13:04:36 bill 1 0
c date and time created 90/11/14 13:04:36 by bill
e
u
U
t
T
I 1
D 3
/*	in_cksum.c	1.2	86/01/05	*/
E 3
I 3
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 * from tahoe:	in_cksum.c	1.2	86/01/05
 *	%W% (Berkeley) %G%
 */
E 3

D 3
#include "../h/types.h"
#include "../h/mbuf.h"
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 3
I 3
D 5
#include "param.h"
#include "sys/mbuf.h"
#include "netinet/in.h"
#include "netinet/in_systm.h"
E 5
I 5
#include <sys/param.h>
#include <sys/mbuf.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
E 5
E 3

/*
 * Checksum routine for Internet Protocol family headers.
 *
 * This routine is very heavily used in the network
 * code and should be modified for each CPU to be as fast as possible.
 * 
D 3
 * This implementation is TAHOE version.
E 3
I 3
 * This implementation is 386 version.
E 3
 */

#undef	ADDCARRY
#define ADDCARRY(sum)  {				\
			if (sum & 0xffff0000) {		\
				sum &= 0xffff;		\
				sum++;			\
			}				\
		}
in_cksum(m, len)
	register struct mbuf *m;
	register int len;
{
	union word {
		char	c[2];
		u_short	s;
	} u;
	register u_short *w;
	register int sum = 0;
	register int mlen = 0;

	for (;m && len; m = m->m_next) {
		if (m->m_len == 0)
			continue;
		w = mtod(m, u_short *);
		if (mlen == -1) {
			/*
			 * The first byte of this mbuf is the continuation
			 * of a word spanning between this mbuf and the
			 * last mbuf.
			 */

			/* u.c[0] is already saved when scanning previous 
			 * mbuf.
			 */
			u.c[1] = *(u_char *)w;
			sum += u.s;
			ADDCARRY(sum);
			w = (u_short *)((char *)w + 1);
			mlen = m->m_len - 1;
			len--;
		} else
			mlen = m->m_len;

		if (len < mlen)
			mlen = len;
		len -= mlen;

		/*
		 * add by words.
		 */
		while ((mlen -= 2) >= 0) {
			if ((int)w & 0x1) {
				/* word is not aligned */
				u.c[0] = *(char *)w;
				u.c[1] = *((char *)w+1);
				sum += u.s;
				w++;
			} else
				sum += *w++;
			ADDCARRY(sum);
		}
		if (mlen == -1)
			/*
			 * This mbuf has odd number of bytes. 
			 * There could be a word split betwen
			 * this mbuf and the next mbuf.
			 * Save the last byte (to prepend to next mbuf).
			 */
			u.c[0] = *(u_char *)w;
	}
	if (len)
		printf("cksum: out of data\n");
	if (mlen == -1) {
		/* The last mbuf has odd # of bytes. Follow the
		   standard (the odd byte is shifted left by 8 bits) */
		u.c[1] = 0;
		sum += u.s;
		ADDCARRY(sum);
	}
	return (~sum & 0xffff);
}
E 1
