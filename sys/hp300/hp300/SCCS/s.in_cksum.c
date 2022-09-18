h08423
s 00002/00002/00070
d D 8.1 93/06/10 21:40:46 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/00072
d D 7.5 93/06/03 16:40:22 sklower 5 4
c get rid of unnecessary includes
e
s 00005/00004/00070
d D 7.4 92/10/11 09:42:34 bostic 4 3
c make kernel includes standard
e
s 00004/00004/00070
d D 7.3 90/12/16 16:36:12 bostic 3 2
c kernel reorg
e
s 00001/00001/00073
d D 7.2 90/11/03 11:42:23 mckusick 2 1
c update identifier from Utah
e
s 00074/00000/00000
d D 7.1 90/05/08 18:09:09 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1988, 1990 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: in_cksum.c 1.6 89/08/24$
E 2
I 2
 * from: Utah $Hdr: in_cksum.c 1.1 90/07/09$
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * in_cksum - checksum routine for the Internet Protocol family.
 */

D 3
#include "param.h"
#include "mbuf.h"
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 3
I 3
D 4
#include "sys/param.h"
#include "sys/mbuf.h"
#include "netinet/in.h"
#include "netinet/in_systm.h"
E 4
I 4
#include <sys/param.h>
#include <sys/mbuf.h>

D 5
#include <netinet/in.h>
#include <netinet/in_systm.h>
E 4
E 3

E 5
extern int oc_cksum();

/*
 * Checksum routine for the Internet Protocol family.
 *
 * This isn't as bad as it looks.  For ip headers the "while" isn't
 * executed and we just drop through to the return statement at the
 * end.  For the usual tcp or udp packet (a single header mbuf
 * chained onto a cluster of data, we make exactly one trip through
 * the while (for the header mbuf) and never do the hairy code
 * inside the "if".  If fact, if m_copydata & sb_compact are doing
 * their job, we should never do the hairy code inside the "if".
 */
in_cksum(m, len)
	register struct mbuf *m;
	register int len;
{
	register int sum = 0;
	register int i;

	while (len > m->m_len) {
		sum = oc_cksum(mtod(m, u_char *), i = m->m_len, sum);
		m = m->m_next;
		len -= i;
		if (i & 1) {
			/*
			 * ouch - we ended on an odd byte with more
			 * to do.  This xfer is obviously not interested
			 * in performance so finish things slowly.
			 */
			register u_char *cp;

			while (len > m->m_len) {
				cp = mtod(m, u_char *);
				if (i & 1) {
					i = m->m_len - 1;
					--len;
					sum += *cp++;
				} else
					i = m->m_len;

				sum = oc_cksum(cp, i, sum);
				m = m->m_next;
				len -= i;
			}
			if (i & 1) {
				cp =  mtod(m, u_char *);
				sum += *cp++;
				return (0xffff & ~oc_cksum(cp, len - 1, sum));
			}
		}
	}
	return (0xffff & ~oc_cksum(mtod(m, u_char *), len, sum));
}
E 1
