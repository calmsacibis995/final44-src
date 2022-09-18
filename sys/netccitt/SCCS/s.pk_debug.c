h42900
s 00002/00002/00112
d D 8.1 93/06/10 22:53:46 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00011/00103
d D 7.9 92/10/11 11:49:44 bostic 9 8
c make kernel includes standard
e
s 00002/00001/00112
d D 7.8 91/07/17 11:20:47 sklower 8 7
c useful debugging changes
e
s 00048/00000/00065
d D 7.7 91/05/09 21:18:33 sklower 7 6
c add useful debugging cache for mbufs
e
s 00002/00001/00063
d D 7.6 91/03/12 15:10:36 sklower 6 5
c allow for 2 new packet types (Reject & Diagnostic)
e
s 00004/00004/00060
d D 7.5 91/01/09 15:37:46 sklower 5 4
c get rid of dtom's in kernel
e
s 00001/00001/00063
d D 7.4 90/11/13 14:33:50 sklower 4 3
c use 12 bit channel space
e
s 00012/00010/00052
d D 7.3 90/08/30 18:48:31 sklower 3 2
c this version compiles; completely untested
e
s 00013/00001/00049
d D 7.2 90/05/11 15:22:09 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00050/00000/00000
d D 7.1 90/05/11 11:19:39 sklower 1 0
c date and time created 90/05/11 11:19:39 by sklower
e
u
U
t
T
I 1
D 2
/* Copyright (c) University of British Columbia, 1984 */
E 2
I 2
/*
 * Copyright (c) University of British Columbia, 1984
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 3
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
E 3
I 3
D 9
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
#include "socketvar.h"
#include "errno.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 9
E 3

D 3
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 3
I 3
D 9
#include "../net/if.h"
E 9
I 9
#include <net/if.h>
E 9

D 9
#include "x25.h"
#include "pk.h"
#include "pk_var.h"
E 9
I 9
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 9
E 3

char	*pk_state[] = {
	"Listen",	"Ready",	"Received-Call",
	"Sent-Call",	"Data-Transfer","Received-Clear",
	"Sent-Clear",
};

char   *pk_name[] = {
	"Call",		"Call-Conf",	"Clear",
	"Clear-Conf",	"Data",		"Intr",		"Intr-Conf",
	"Rr",		"Rnr",		"Reset",	"Reset-Conf",
D 6
	"Restart",	"Restart-Conf",	"Invalid"
E 6
I 6
	"Restart",	"Restart-Conf",	"Reject",	"Diagnostic",
	"Invalid"
E 6
};

D 5
pk_trace (xcp, xp, dir)
E 5
I 5
pk_trace (xcp, m, dir)
E 5
struct x25config *xcp;
D 5
struct x25_packet *xp;
E 5
I 5
register struct mbuf *m;
E 5
char *dir;
{
	register char *s;
D 5
	register struct mbuf *m;
E 5
I 5
	struct x25_packet *xp = mtod(m, struct x25_packet *);
E 5
	register int i, len = 0, cnt = 0;

	if (xcp -> xc_ptrace == 0)
		return;

	i = pk_decode (xp) / MAXSTATES;
D 5
	for (m = dtom (xp); m; m = m -> m_next) {
E 5
I 5
	for (; m; m = m -> m_next) {
E 5
		len = len + m -> m_len;
		++cnt;
	}
	printf ("LCN=%d %s:	%s	#=%d, len=%d ",
D 4
		xp -> logical_channel_number, dir, pk_name[i], cnt, len);
E 4
I 4
		LCN(xp), dir, pk_name[i], cnt, len);
E 4
	for (s = (char *) xp, i = 0; i < 5; ++i, ++s)
		printf ("%x ", (int) * s & 0xff);
	printf ("\n");
}
I 7

mbuf_cache(c, m)
register struct mbuf_cache *c;
struct mbuf *m;
{
	register struct mbuf **mp;

	if (c->mbc_size != c->mbc_oldsize) {
		unsigned zero_size, copy_size;
		unsigned new_size = c->mbc_size * sizeof(m);
		caddr_t cache = (caddr_t)c->mbc_cache;

		if (new_size) {
			c->mbc_cache = (struct mbuf **)
				malloc(new_size, M_MBUF, M_NOWAIT);
			if (c->mbc_cache == 0) {
				c->mbc_cache = (struct mbuf **)cache;
				return;
			}
			c->mbc_num %= c->mbc_size;
		} else
			c->mbc_cache = 0;
		if (c->mbc_size < c->mbc_oldsize) {
			register struct mbuf **mplim;
			mp = c->mbc_size + (struct mbuf **)cache;
			mplim = c->mbc_oldsize + (struct mbuf **)cache;
			while (mp < mplim)
				m_freem(*mp++);
			zero_size = 0;
		} else
			zero_size = (c->mbc_size - c->mbc_oldsize) * sizeof(m);
		copy_size = new_size - zero_size;
		c->mbc_oldsize = c->mbc_size;
		if (copy_size)
			bcopy(cache, (caddr_t)c->mbc_cache, copy_size);
		if (cache)
			free(cache, M_MBUF);
		if (zero_size)
			bzero(copy_size + (caddr_t)c->mbc_cache, zero_size);
	}
	if (c->mbc_size == 0)
		return;
	mp = c->mbc_cache + c->mbc_num;
	c->mbc_num = (1 + c->mbc_num) % c->mbc_size;
	if (*mp)
		m_freem(*mp);
D 8
	*mp = m_copym(m, 0, M_COPYALL, M_DONTWAIT);
E 8
I 8
	if (*mp = m_copym(m, 0, M_COPYALL, M_DONTWAIT))
		(*mp)->m_flags |= m->m_flags & 0x08;
E 8
}
E 7
E 1
