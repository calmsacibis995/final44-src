h24514
s 00002/00002/00059
d D 8.1 93/06/06 14:09:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00054
d D 5.2 93/05/11 11:53:05 bostic 2 1
c put in correct SCCS header, copyright
e
s 00060/00000/00000
d D 5.1 93/05/11 11:52:33 bostic 1 0
c date and time created 93/05/11 11:52:33 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1985 Regents of the University of California.
E 2
I 2
/*-
D 3
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

D 2
#ifdef sgi
#ident "$Revision: 1.3 $"
E 2
#ifndef lint
D 2
static char sccsid[] = "@(#)cksum.c	2.6 (Berkeley) 6/1/90";
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
#endif /* not lint */
D 2
#endif /* sgi */
E 2
I 2

#ifdef sgi
#ident "$Revision: 1.3 $"
#endif
E 2

#include <sys/types.h>

/*
 *			I N _ C K S U M
 *
 * Checksum routine for Internet Protocol family headers (C Version)
 *
 * There is no profit in a specialized version of the checksum
 * function for any machine where int's are 32 bits and shorts are 16.
 *
 * All timed packets are smaller than 32K shorts, so there is no need to
 * worry about carries except at the end.
 */
int
in_cksum(addr, len)
	u_short *addr;
	int len;
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 )
		sum += (*(u_char *)w) << 8;

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}
E 1
