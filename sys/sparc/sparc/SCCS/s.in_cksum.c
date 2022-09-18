h00874
s 00002/00002/00071
d D 8.1 93/06/11 15:16:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00071
d D 7.4 93/04/20 23:12:00 torek 4 3
c spelling
e
s 00005/00004/00068
d D 7.3 92/10/11 12:57:11 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00067
d D 7.2 92/07/21 16:54:25 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00067/00000/00000
d D 7.1 92/07/13 00:44:33 torek 1 0
c date and time created 92/07/13 00:44:33 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: in_cksum.c,v 1.6 92/06/17 05:22:04 torek Exp $
E 4
I 4
 * from: $Header: in_cksum.c,v 1.7 92/11/26 03:04:52 torek Exp $
E 4
 */

D 3
#include "param.h"
#include "mbuf.h"
#include "netinet/in.h"
#include "netinet/in_systm.h"
E 3
I 3
#include <sys/param.h>
#include <sys/mbuf.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
E 3

/*
 * Checksum routine for Internet Protocol family headers.
 * This routine is very heavily used in the network
 * code and should be modified for each CPU to be as fast as possible.
 * In particular, it should not be this one.
 */
int
in_cksum(m, len)
	register struct mbuf *m;
	register int len;
{
	register int sum = 0, i, oddbyte = 0, v = 0;
	register u_char *cp;

	/* we assume < 2^16 bytes being summed */
	while (len) {
		while ((i = m->m_len) == 0)
			m = m->m_next;
		if (i > len)
			i = len;
		len -= i;
		cp = mtod(m, u_char *);
		if (oddbyte) {
			sum += v + *cp++;
			i--;
		}
		if (((int)cp & 1) == 0) {
			while ((i -= 2) >= 0) {
				sum += *(u_short *)cp;
				cp += 2;
			}
		} else {
			while ((i -= 2) >= 0) {
				sum += *cp++ << 8;
				sum += *cp++;
			}
		}
		if ((oddbyte = i & 1) != 0)
			v = *cp << 8;
		m = m->m_next;
	}
	if (oddbyte)
		sum += v;
	sum = (sum >> 16) + (sum & 0xffff); /* add in accumulated carries */
	sum += sum >> 16;		/* add potential last carry */
	return (0xffff & ~sum);
}
E 1
