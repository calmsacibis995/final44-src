h12071
s 00002/00002/00144
d D 7.3 91/06/27 23:49:14 sklower 3 2
c make compile under newvm system (change types.h to param.h)
e
s 00002/00002/00144
d D 7.2 90/12/16 16:36:32 bostic 2 1
c kernel reorg
e
s 00146/00000/00000
d D 7.1 90/05/08 18:09:12 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1985, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "types.h"
#include "mbuf.h"
E 2
I 2
D 3
#include "sys/types.h"
#include "sys/mbuf.h"
E 3
I 3
#include "param.h"
#include "mbuf.h"
E 3
E 2


/*
 * Checksum routine for Network Systems Protocol Packets (SUN Version).
 *
 * This routine is very heavily used in the network
 * code and should be modified for each CPU to be as fast as possible.
 */

u_short
ns_cksum(m, len)
	register struct mbuf *m;
	register int len;
{
	register u_short *w;		/* on sun, known to be a4 */
	register int sum = 0;		/* on sun, known to be d6 */
	register int low = 0;		/* on sun, known to be d5 */
	register int mlen = low;	/* want 0, shuts lint up about low */
	register int zero = mlen;	/* handy for fold */
	register int sumH = mlen;	/* handy for fold2 */
#undef ADD
#define ADD asm("addw a4@+,d6; addxw d3,d6; rolw #1,d6")
#define FOLD asm("movw d6,d5; swap d6; addw d6,d5; addxw d3,d5;  movl d5,d6");
#define ADDH asm("movb a4@+,d5; addl d5,d2; addl d2,d2")
#define ADDL asm("movb a4@+,d5; addl d5,d6; addl d6,d6")
#define FOLDH asm("movw d2,d5; swap d2; addw d2,d5; addxw d3,d5; movl d5,d2");

	for (;;) {
		/*
		 * Each trip around loop adds in
		 * word from one mbuf segment.
		 */
		w = mtod(m, u_short *);
		if (mlen == -1) {
			/*
			 * There is a byte left from the last segment;
			 * ones-complement add it into the checksum.
			 */
			low = *(u_char *)w;
			asm("addw d5,d6; addxw d3,d6; rolw #1,d6");
			w = (u_short *)((char *)w + 1);
			mlen = m->m_len - 1;
			len--;
		} else
			mlen = m->m_len;
		m = m->m_next;
		if (len < mlen)
			mlen = len;
		len -= mlen;
		/*
		 *
		 * We can do a 16 bit ones complement sum using
		 * 32 bit arithmetic registers for adding,
		 * with carries from the low added
		 * into the high (by normal carry-chaining)
		 * so long as we fold back before 16 carries have occured.
		 *
		 */
#ifndef OKTOODDWORD
		if (((int) w & 1)==0) goto easycase;
		while ((mlen -= 32) >= 0) {
			ADDH; ADDL; ADDH; ADDL; ADDH; ADDL; ADDH; ADDL;
			ADDH; ADDL; ADDH; ADDL; ADDH; ADDL; ADDH; ADDL;
			FOLD;
			FOLDH;
			ADDH; ADDL; ADDH; ADDL; ADDH; ADDL; ADDH; ADDL;
			ADDH; ADDL; ADDH; ADDL; ADDH; ADDL; ADDH; ADDL;
			FOLD;
			FOLDH;
		}
		mlen += 32;
		while ((mlen -= 8) >= 0) {
			ADDH; ADDL; ADDH; ADDL; ADDH; ADDL; ADDH; ADDL;
			FOLD;
			FOLDH;
		}
		mlen += 8;
		while ((mlen -= 2) >= 0) {
			ADDH; ADDL;
		}
		FOLDH;
		sum = (sumH << 8) + sum;
		FOLD;
		sumH = 0;
		goto commoncase;
easycase:
#endif
		/* In this sequence there will be no carries out of
		 * the lower 16 bits.
		 */
		while ((mlen -= 32) >= 0) {
			ADD; ADD; ADD; ADD; ADD; ADD; ADD; ADD;
			ADD; ADD; ADD; ADD; ADD; ADD; ADD; ADD;
		}
		mlen += 32;
		while ((mlen -= 8) >= 0) {
			ADD; ADD; ADD; ADD;
		}
		mlen += 8;
		while ((mlen -= 2) >= 0) {
			ADD;
		}
commoncase:
		if (mlen == -1) {
			/*sum += *(u_char *)w << 8; FOLD*/
			low = *(u_char *)w << 8;
			asm("addw d5,d6; addxw d3,d6");
		}
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
				printf("idpcksum: out of data\n");
				goto done;
			}
			if (m->m_len)
				break;
			m = m->m_next;
		}
	}
done:
	/*
	 * sum has already been kept to low sixteen bits.
	 * just examine result and exit.
	 */
	
	if(sum==0xffff) sum = 0;
	return (sum);
}
E 1
