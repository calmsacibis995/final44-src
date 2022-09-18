/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	uipc_mbuf.c,v $
 * Revision 2.11  89/05/30  10:36:37  rvb
 * 	Fixed the DMA problem for mips.
 * 	[89/05/15            af]
 * 
 * Revision 2.10  89/04/23  14:12:03  gm0w
 * 	Fixed declaration of embutl.
 * 	[89/04/23            gm0w]
 * 
 * Revision 2.9  89/03/09  19:34:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/26  11:30:33  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.7  89/02/09  04:35:49  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.6  89/01/31  01:21:04  rpd
 * 	m_clalloc: use entire space allocated.
 * 	[89/01/27            dlb]
 * 
 * Revision 2.5  89/01/23  22:09:56  af
 * 	Changes for Mips.
 * 	Also, Corrected include file references.
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: mbuf initialization for i386
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  89/01/18  00:45:04  jsb
 * 	Vnode support, including addition of m_cpytoc routine.
 * 	[89/01/17            jsb]
 *
 * 13-Jul-88  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Added m_cpytoc routine.
 *
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Don't include "sys/vm.h".
 *
 *  6-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Call kmem_mb_alloc instead of kmem_alloc from m_clalloc.
 *	Temporary hack until mbuf code is fixed to never need to
 *	allocate memory from interrupt level.
 *
 * 22-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 30-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	In m_clalloc, always call kmem_alloc with wait = FALSE -
 *	otherwise, kmem_alloc can sleep with mb_map locked.  m_clalloc's
 *	callers sleep if necessary.
 *
 * 18-Nov-86  David Golub (dbg) at Carnegie-Mellon University
 *	Removed include of cmap.h for MACH.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted under MACH.
 *
 * 20-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Added include of cputypes.h to pick up new MULTIMAX definition.
 *
 * 21-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Temporarily, changed "mbinit" to use NBPG instead of 4096
 *	when allocating mbuf clusters (for SUN - SUN page size is
 *	greater than 4096).
 *
 *  7-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Removed unnecessary include of pte.h
 *
 * 14-Apr-86  David Golub (dbg) at Carnegie-Mellon University
 *	Round up size in m_clalloc to a VM-page multiple, to avoid
 *	wasting space.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use new VM primitives to get more space.
 *
 */
/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *	@(#)uipc_mbuf.c	7.4.1.2 (Berkeley) 2/8/88
 */

#include <cputypes.h>

#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#include <kern/kalloc.h>
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/map.h>
#include <sys/mbuf.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
#include <sys/domain.h>
#include <sys/protosw.h>

struct mbuf *mbutl, *embutl;	/* virtual address of net free mem */
struct	mbstat mbstat;
int	nmbclusters;
struct	mbuf *mfree, *mclfree;
char	mclrefcnt[NMBCLUSTERS + 1];
int	m_want;

mbinit()
{
	int s;
	int initcl;

	if (CLBYTES < 4096)
		initcl = 4096/CLBYTES;
	else
		initcl = 1;
	s = splimp();
	if (m_clalloc(initcl, MPG_MBUFS, M_DONTWAIT) == 0)
		goto bad;
	if (m_clalloc(initcl, MPG_CLUSTERS, M_DONTWAIT) == 0)
		goto bad;
	splx(s);
	return;
bad:
	panic("mbinit");
}

/*
 * Must be called at splimp.
 */
/*
 *	Since m_clalloc can allocate from the mb_map when called from
 *	interrupt level, there are severe constraints on the mb_map:
 *
 *	it may be used only at splimp
 *	it may be used only on the master processor
 *	any calls it makes on the vm routines may NOT sleep.
 *
 *	Uses a hack in vm_kern to allocate memory.
 */
/* ARGSUSED */
caddr_t
m_clalloc(ncl, how, canwait)
	register int ncl;
	int how;
{
	register struct mbuf *m;
	register int i;
	vm_size_t	size;

#ifdef	lint
	canwait++;
#endif	lint

	size = round_page(ncl * CLBYTES);
	m = (struct mbuf *) kmem_mb_alloc(mb_map, size);

	if (m == NULL)
		return(0);

	ncl = size / CLBYTES;

	switch (how) {

	case MPG_CLUSTERS:
		ncl = ncl * CLBYTES / MCLBYTES;
		for (i = 0; i < ncl; i++) {
			m->m_off = 0;
			m->m_next = mclfree;
			mclfree = m;
			m += MCLBYTES / sizeof (*m);
			mbstat.m_clfree++;
		}
		mbstat.m_clusters += ncl;
		break;

	case MPG_MBUFS:
		for (i = ncl * CLBYTES / sizeof (*m); i > 0; i--) {
			m->m_off = 0;
			m->m_type = MT_DATA;
			mbstat.m_mtypes[MT_DATA]++;
			mbstat.m_mbufs++;
			(void) m_free(m);
			m++;
		}
		break;

	case MPG_SPACE:
		mbstat.m_space++;
		break;
	}
	return ((caddr_t)m);
}

m_pgfree(addr, n)
	caddr_t addr;
	int n;
{

#ifdef	lint
	addr = addr; n = n;
#endif
}

/*
 * Must be called at splimp.
 */
m_expand(canwait)
	int canwait;
{
	register struct domain *dp;
	register struct protosw *pr;
	int tries;

	for (tries = 0;; ) {
		if (m_clalloc(1, MPG_MBUFS, canwait))
			return (1);
		if (canwait == 0 || tries++)
			return (0);

		/* ask protocols to free space */
		for (dp = domains; dp; dp = dp->dom_next)
			for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW;
			    pr++)
				if (pr->pr_drain)
					(*pr->pr_drain)();
		mbstat.m_drain++;
	}
}

/* NEED SOME WAY TO RELEASE SPACE */

/*
 * Space allocation routines.
 * These are also available as macros
 * for critical paths.
 */
struct mbuf *
m_get(canwait, type)
	int canwait, type;
{
	register struct mbuf *m;

	MGET(m, canwait, type);
	return (m);
}

struct mbuf *
m_getclr(canwait, type)
	int canwait, type;
{
	register struct mbuf *m;

	MGET(m, canwait, type);
	if (m == 0)
		return (0);
	bzero(mtod(m, caddr_t), MLEN);
	return (m);
}

struct mbuf *
m_free(m)
	struct mbuf *m;
{
	register struct mbuf *n;

	MFREE(m, n);
	return (n);
}

/*
 * Get more mbufs; called from MGET macro if mfree list is empty.
 * Must be called at splimp.
 */
/*ARGSUSED*/
struct mbuf *
m_more(canwait, type)
	int canwait, type;
{
	register struct mbuf *m;

	while (m_expand(canwait) == 0) {
		if (canwait == M_WAIT) {
			mbstat.m_wait++;
			m_want++;
			sleep((caddr_t)&mfree, PZERO - 1);
		} else {
			mbstat.m_drops++;
			return (NULL);
		}
	}
#define m_more(x,y) (panic("m_more"), (struct mbuf *)0)
	MGET(m, canwait, type);
#undef m_more
	return (m);
}

m_freem(m)
	register struct mbuf *m;
{
	register struct mbuf *n;
	register int s;

	if (m == NULL)
		return;
	s = splimp();
	do {
		MFREE(m, n);
	} while (m = n);
	splx(s);
}

/*
 * Mbuffer utility routines.
 */

/*
 * Make a copy of an mbuf chain starting "off" bytes from the beginning,
 * continuing for "len" bytes.  If len is M_COPYALL, copy to end of mbuf.
 * Should get M_WAIT/M_DONTWAIT from caller.
 */
struct mbuf *
m_copy(m, off, len)
	register struct mbuf *m;
	int off;
	register int len;
{
	register struct mbuf *n, **np;
	struct mbuf *top, *p;

	if (len == 0)
		return (0);
	if (off < 0 || len < 0)
		panic("m_copy");
	while (off > 0) {
		if (m == 0)
			panic("m_copy");
		if (off < m->m_len)
			break;
		off -= m->m_len;
		m = m->m_next;
	}
	np = &top;
	top = 0;
	while (len > 0) {
		if (m == 0) {
			if (len != M_COPYALL)
				panic("m_copy");
			break;
		}
		MGET(n, M_DONTWAIT, m->m_type);
		*np = n;
		if (n == 0)
			goto nospace;
		n->m_len = MIN(len, m->m_len - off);
		if (m->m_off > MMAXOFF) {
			p = mtod(m, struct mbuf *);
			n->m_off = ((int)p - (int)n) + off;
			mclrefcnt[mtocl(p)]++;
		} else
			bcopy(mtod(m, caddr_t)+off, mtod(n, caddr_t),
			    (unsigned)n->m_len);
		if (len != M_COPYALL)
			len -= n->m_len;
		off = 0;
		m = m->m_next;
		np = &n->m_next;
	}
	return (top);
nospace:
	m_freem(top);
	return (0);
}

m_cat(m, n)
	register struct mbuf *m, *n;
{
	while (m->m_next)
		m = m->m_next;
	while (n) {
		if (m->m_off >= MMAXOFF ||
		    m->m_off + m->m_len + n->m_len > MMAXOFF) {
			/* just join the two chains */
			m->m_next = n;
			return;
		}
		/* splat the data from one into the other */
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t) + m->m_len,
		    (u_int)n->m_len);
		m->m_len += n->m_len;
		n = m_free(n);
	}
}

m_adj(mp, len)
	struct mbuf *mp;
	register int len;
{
	register struct mbuf *m;
	register count;

	if ((m = mp) == NULL)
		return;
	if (len >= 0) {
		while (m != NULL && len > 0) {
			if (m->m_len <= len) {
				len -= m->m_len;
				m->m_len = 0;
				m = m->m_next;
			} else {
				m->m_len -= len;
				m->m_off += len;
				break;
			}
		}
	} else {
		/*
		 * Trim from tail.  Scan the mbuf chain,
		 * calculating its length and finding the last mbuf.
		 * If the adjustment only affects this mbuf, then just
		 * adjust and return.  Otherwise, rescan and truncate
		 * after the remaining size.
		 */
		len = -len;
		count = 0;
		for (;;) {
			count += m->m_len;
			if (m->m_next == (struct mbuf *)0)
				break;
			m = m->m_next;
		}
		if (m->m_len >= len) {
			m->m_len -= len;
			return;
		}
		count -= len;
		/*
		 * Correct length for chain is "count".
		 * Find the mbuf with last data, adjust its length,
		 * and toss data from remaining mbufs on chain.
		 */
		for (m = mp; m; m = m->m_next) {
			if (m->m_len >= count) {
				m->m_len = count;
				break;
			}
			count -= m->m_len;
		}
		while (m = m->m_next)
			m->m_len = 0;
	}
}

/*
 * Rearange an mbuf chain so that len bytes are contiguous
 * and in the data area of an mbuf (so that mtod and dtom
 * will work for a structure of size len).  Returns the resulting
 * mbuf chain on success, frees it and returns null on failure.
 * If there is room, it will add up to MPULL_EXTRA bytes to the
 * contiguous region in an attempt to avoid being called next time.
 */
struct mbuf *
m_pullup(n, len)
	register struct mbuf *n;
	int len;
{
	register struct mbuf *m;
	register int count;
	int space;

	if (n->m_off + len <= MMAXOFF && n->m_next) {
		m = n;
		n = n->m_next;
		len -= m->m_len;
	} else {
		if (len > MLEN)
			goto bad;
		MGET(m, M_DONTWAIT, n->m_type);
		if (m == 0)
			goto bad;
		m->m_len = 0;
	}
	space = MMAXOFF - m->m_off;
	do {
		count = MIN(MIN(space - m->m_len, len + MPULL_EXTRA), n->m_len);
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t)+m->m_len,
		  (unsigned)count);
		len -= count;
		m->m_len += count;
		n->m_len -= count;
		if (n->m_len)
			n->m_off += count;
		else
			n = m_free(n);
	} while (len > 0 && n);
	if (len > 0) {
		(void) m_free(m);
		goto bad;
	}
	m->m_next = n;
	return (m);
bad:
	m_freem(n);
	return (0);
}

/* Allocate a "funny" mbuf, that is, one whose data is owned by someone else */
struct mbuf *
mclgetx(fun, arg, addr, len, wait)
	int (*fun)(), arg, len, wait;
	caddr_t addr;
{
	register struct mbuf *m;

	MGET(m, wait, MT_DATA);
	if (m == 0)
		return (0);
	m->m_off = (int)addr - (int)m;
	m->m_len = len;
	m->m_cltype = MCL_LOANED;
	m->m_clfun = fun;
	m->m_clarg = arg;
	m->m_clswp = NULL;
	return (m);
}
/* Generic cluster mbuf unallocator -- invoked from within MFREE */
mclput(m)
	register struct mbuf *m;
{

	switch (m->m_cltype) {
	case MCL_STATIC:
		m = MTOCL(m); 
		MCLFREE(m); 
		break;

	case MCL_LOANED:
		(*m->m_clfun)(m->m_clarg);
		break;

	default:
		panic("mclput");
	}
}

/*
 * Copy an mbuf to the contiguous area pointed to by cp.
 * Skip <off> bytes and copy <len> bytes.
 * Returns the number of bytes not transferred.
 * The mbuf is NOT changed.
 */
int
m_cpytoc(m, off, len, cp)
	register struct mbuf *m;
	register int off, len;
	register caddr_t cp;
{
	register int ml;

	if (m == NULL || off < 0 || len < 0 || cp == NULL)
		panic("m_cpytoc");
	while (off && m)
		if (m->m_len <= off) {
			off -= m->m_len;
			m = m->m_next;
			continue;
		} else
			break;
	if (m == NULL)
		return (len);

	ml = imin(len, m->m_len - off);
	bcopy(mtod(m, caddr_t)+off, cp, (u_int)ml);
	cp += ml;
	len -= ml;
	m = m->m_next;

	while (len && m) {
		ml = m->m_len;
		bcopy(mtod(m, caddr_t), cp, (u_int)ml);
		cp += ml;
		len -= ml;
		m = m->m_next;
	}

	return (len);
}
