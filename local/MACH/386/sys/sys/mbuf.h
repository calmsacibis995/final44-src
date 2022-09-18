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
 * $Log:	mbuf.h,v $
 * Revision 2.10  89/09/05  20:44:57  jsb
 * 	Fix for null-dereferencing bug in MGET. (Fix from MacMach project.)
 * 	[89/09/05  15:19:19  jsb]
 * 
 * Revision 2.9  89/04/23  13:25:22  gm0w
 * 	Added * before declaration of embutl
 * 	[89/04/19            mrt]
 * 
 * Revision 2.8  89/03/09  22:05:38  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  17:54:41  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/01/23  15:31:19  rvb
 * 	Change lambda variables for MFREE so that \n does not get
 * 	expanded.
 * 	[89/01/23            rvb]
 * 
 * Revision 2.5  89/01/18  01:16:59  jsb
 * 	Added cluster support, necessary for NFS: define MCLBYTES; add type
 * 	support for clusters; new macros for MCLALLOC, MFREE, friends; new
 * 	mb_{space,drain,wait} fields in mbstat.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.4  88/08/24  02:34:59  mwyoung
 * 	Condensed NET_BUGFIX conditional into CMUCS.
 * 	[88/08/22  22:29:49  mwyoung]
 * 	
 * 	Adjusted include file references.
 * 	[88/08/17  02:16:54  mwyoung]
 * 
 * Revision 2.3  88/08/09  17:59:38  rvb
 * Increase nmbclusters allotment for mach.
 * 
 * 18-Nov-86  David Golub (dbg) at Carnegie-Mellon University
 *	Remove all uses of 'pte' from machine-independent code.
 *
 * 15-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	NET_BUGFIX: Installed MCLGET bug fix from UCB.
 *	[ V5.1(F1) ]
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Installed VM changes.
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mbuf.h	7.3 (Berkeley) 9/11/86
 */

#ifndef	_SYS_MBUF_H_
#define _SYS_MBUF_H_

#include <sys/types.h>

/*
 * Constants related to memory allocator.
 */
#define MSIZE		128			/* size of an mbuf */

#define MMINOFF		12			/* mbuf header length */
#define MTAIL		4
#define MMAXOFF		(MSIZE-MTAIL)		/* offset where data ends */
#define MLEN		(MSIZE-MMINOFF-MTAIL)	/* mbuf data length */
#define NMBCLUSTERS	512
#define NMBPCL		(CLBYTES/MSIZE)		/* # mbufs per cluster */
#define MCLBYTES	CLBYTES			/* for uipc_mbuf.c */

/*
 * Macros for type conversion
 */

/* network cluster number to virtual address, and back */
#define cltom(x) ((struct mbuf *)((int)mbutl + ((x) << CLSHIFT)))
#define mtocl(x) (((int)x - (int)mbutl) >> CLSHIFT)

/* address in mbuf to mbuf head */
#define dtom(x)		((struct mbuf *)((int)x & ~(MSIZE-1)))

/* mbuf head, to typed data */
#define mtod(x,t)	((t)((int)(x) + (x)->m_off))

struct mbuf {
	struct	mbuf *m_next;		/* next buffer in chain */
	u_long	m_off;			/* offset of data */
	short	m_len;			/* amount of data in this mbuf */
	short	m_type;			/* mbuf type (0 == free) */
	union {
		u_char	mun_dat[MLEN];	/* data storage */
		struct {
			short	mun_cltype;	/* "cluster" type */
			int	(*mun_clfun)();
			int	mun_clarg;
			int	(*mun_clswp)();
		} mun_cl;
	} m_un;
	struct	mbuf *m_act;		/* link in higher-level mbuf list */
};

#define m_dat	m_un.mun_dat
#define m_cltype m_un.mun_cl.mun_cltype
#define m_clfun	m_un.mun_cl.mun_clfun
#define m_clarg	m_un.mun_cl.mun_clarg
#define m_clswp	m_un.mun_cl.mun_clswp

/* mbuf types */
#define MT_FREE		0	/* should be on free list */
#define MT_DATA		1	/* dynamic (data) allocation */
#define MT_HEADER	2	/* packet header */
#define MT_SOCKET	3	/* socket structure */
#define MT_PCB		4	/* protocol control block */
#define MT_RTABLE	5	/* routing tables */
#define MT_HTABLE	6	/* IMP host tables */
#define MT_ATABLE	7	/* address resolution tables */
#define MT_SONAME	8	/* socket name */
#define MT_ZOMBIE	9	/* zombie proc status */
#define MT_SOOPTS	10	/* socket options */
#define MT_FTABLE	11	/* fragment reassembly header */
#define MT_RIGHTS	12	/* access rights */
#define MT_IFADDR	13	/* interface address */

/* flags to m_get */
#define M_DONTWAIT	0
#define M_WAIT		1

/* flags to m_pgalloc */
#define MPG_MBUFS	0		/* put new mbufs on free list */
#define MPG_CLUSTERS	1		/* put new clusters on free list */
#define MPG_SPACE	2		/* don't free; caller wants space */

/* length to m_copy to copy all */
#define M_COPYALL	1000000000

#define MCL_STATIC	1
#define MCL_LOANED	2

/*
 * m_pullup will pull up additional length if convenient;
 * should be enough to hold headers of second-level and higher protocols. 
 */
#define MPULL_EXTRA	32

/*
 * Mbuf statistics.
 */
struct mbstat {
	short	m_mbufs;	/* mbufs obtained from page pool */
	short	m_clusters;	/* clusters obtained from page pool */
	short	m_clfree;	/* free clusters */
	short	m_drops;	/* times failed to find space */
	short	m_mtypes[256];	/* type specific mbuf allocations */
	short	m_space;
	short	m_drain;
	short	m_wait;
};

#ifdef	KERNEL
#include <kern/macro_help.h>

#define MGET(m, i, t)							\
MACRO_BEGIN								\
	int ms = splimp();						\
	if ((m)=mfree) {						\
		if ((m)->m_type != MT_FREE)				\
			panic("mget");					\
		(m)->m_type = t;					\
		mbstat.m_mtypes[MT_FREE]--; mbstat.m_mtypes[t]++;	\
		mfree = (m)->m_next; (m)->m_next = 0;			\
		(m)->m_off = MMINOFF;					\
	} else								\
		(m) = m_more(i, t);					\
	if (m) (m)->m_cltype = MCL_STATIC; /* XXX Hack */		\
	splx(ms);							\
MACRO_END

/*
 * Mbuf page cluster macros.
 * MCLALLOC allocates mbuf page clusters.
 * Note that it works only with a count of 1 at the moment.
 * MCLGET adds such clusters to a normal mbuf.
 * m->m_len is set to CLBYTES upon success.
 * MCLFREE frees clusters allocated by MCLALLOC.
 */

#define MCLALLOC(m, i)							\
MACRO_BEGIN								\
	int ms = splimp();						\
	if (mclfree == 0)						\
		(void)m_clalloc((i), MPG_CLUSTERS, M_DONTWAIT);		\
	if (mclfree == 0)						\
		panic("MCLALLOC");					\
	if ((m)=mclfree) {						\
		++mclrefcnt[mtocl(m)];					\
		mbstat.m_clfree--;					\
		mclfree = (m)->m_next;					\
	}								\
	splx(ms);							\
MACRO_END

#define M_HASCL(m)	((m)->m_off >= MSIZE)
#define MTOCL(m)	((struct mbuf *)(mtod((m), int)&~CLOFSET))

#define MCLGET(m)							\
MACRO_BEGIN								\
	struct mbuf *p;							\
									\
	MCLALLOC(p, 1);							\
	if (p) {							\
		(m)->m_off = (int)p - (int)(m);				\
		(m)->m_len = CLBYTES;					\
	}								\
MACRO_END

#define MCLFREE(m)							\
MACRO_BEGIN								\
	if (--mclrefcnt[mtocl(m)] == 0) {				\
		(m)->m_next = mclfree;					\
		mclfree = (m);						\
		mbstat.m_clfree++;					\
	}								\
MACRO_END

#define MFREE(m, y)							\
MACRO_BEGIN								\
	int ms = splimp();						\
									\
	if ((m)->m_type == MT_FREE) {					\
		printf("MFREE:m=%x\n",m);				\
		panic("mfree");						\
	}								\
	mbstat.m_mtypes[(m)->m_type]--;					\
	mbstat.m_mtypes[MT_FREE]++;					\
	(m)->m_type = MT_FREE;						\
	if (M_HASCL(m)) {						\
		mclput(m);						\
	}								\
	(y) = (m)->m_next; (m)->m_next = mfree;				\
	(m)->m_off = 0; (m)->m_act = 0; mfree = (m);			\
	splx(ms);							\
	if (m_want) {							\
		m_want = 0;						\
		wakeup((caddr_t)&mfree);				\
	}								\
MACRO_END

extern struct	mbuf *mbutl, *embutl;	/* virtual address of net free mem */
extern struct	mbstat mbstat;
extern int	nmbclusters;
extern struct	mbuf *mfree, *mclfree;
extern char	mclrefcnt[NMBCLUSTERS + 1];
extern int	m_want;

extern struct	mbuf *m_get();
extern struct	mbuf *m_getclr();
extern struct	mbuf *m_free();
extern struct	mbuf *m_more();
extern struct	mbuf *m_copy();
extern struct	mbuf *m_pullup();
extern caddr_t	m_clalloc();
#endif	KERNEL
#endif	_SYS_MBUF_H_
