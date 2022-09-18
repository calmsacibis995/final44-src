/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mbuf.h,v $
 * Revision 2.2  89/07/12  00:13:11  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)mbuf.h 2.16 88/02/08 SMI; from UCB 7.3 9/11/86 */

/*
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	_sys_mbuf_h
#define	_sys_mbuf_h

/*
 * Constants related to memory allocator.
 *
 * Standard 4.3 assumes that the size of a cluster mbuf is PAGESIZE,
 * thus linking (cluster) mbuf size to the system page size.  We
 * choose to break this linkage, instead setting the mbuf cluster
 * size to MCLBYTES, which must be a power of 2 no less than MSIZE.
 * However, when obtaining space from the system, allocation is still
 * performed in units of PAGESIZE.
 *
 * MBPOOLBYTES gives the amount of virtual space to reserve for mbuf
 * storage.  Experience shows that allocation can creep up over half
 * a megabyte, but some machines (notably Sun-2s) can't afford to
 * dedicate that much address space to mbufs.  Thus we case split on
 * the machine type.
 * XXX:	Need better way to handle this problem.
 */
#define	MSIZE		128			/* size of an mbuf */

#define	MMINOFF		12			/* mbuf header length */
#define	MTAIL		4
#define	MMAXOFF		(MSIZE-MTAIL)		/* offset where data ends */
#define	MLEN		(MSIZE-MMINOFF-MTAIL)	/* mbuf data length */
#define	MCLBYTES	1024			/* size of mbuf clusters */

#ifdef	sun2
#define	MBPOOLBYTES	( 512 * 1024)
#else	sun2
#define	MBPOOLBYTES	(1024 * 1024)
#endif	sun2

/*
 * Macros for type conversion
 */

/* bytes to mclusters, rounding up, and back */
#define	btomcl(x)	(((x) + MCLBYTES - 1) / MCLBYTES)
#define	mcltob(x)	((x) * MCLBYTES)

/* mcluster index to mbuf address, and back */
#define	cltom(x) ((struct mbuf *)((int)mbutl + (mcltob(x))))
#define	mtocl(x) (((int)x - (int)mbutl) / MCLBYTES)

/* address in mbuf to mbuf head */
#define	dtom(x)		((struct mbuf *)((int)x & ~(MSIZE-1)))

/* mbuf head, to typed data */
#define	mtod(x,t)	((t)((int)(x) + (x)->m_off))

/*
 * Standard 4.3 supports two kinds of mbufs: normal mbufs, with data
 * residing in the mbuf itself; and cluster mbufs with data stored
 * elsewhere (at a higher address than the corresponding mbuf).
 * The data area for cluster mbufs is allocated as a pool and is
 * managed by the mbuf system itself.  We add another kind of cluster
 * mbuf, whose data area is not part of the mbuf system.  Instead,
 * a routine wishing to use this kind of mbuf must provide a buffer
 * for the storage associated with the mbuf and a pointer to a routine
 * to free the buffer when the mbuf is freed.  The fields in mun_cl
 * below record the necessary bookkeeping information.
 */
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
#define	m_dat		m_un.mun_dat
#define	m_cltype	m_un.mun_cl.mun_cltype
#define	m_clfun		m_un.mun_cl.mun_clfun
#define	m_clarg		m_un.mun_cl.mun_clarg
#define	m_clswp		m_un.mun_cl.mun_clswp

/* mbuf types */
#define	MT_FREE		0	/* should be on free list */
#define	MT_DATA		1	/* dynamic (data) allocation */
#define	MT_HEADER	2	/* packet header */
#define	MT_SOCKET	3	/* socket structure */
#define	MT_PCB		4	/* protocol control block */
#define	MT_RTABLE	5	/* routing tables */
#define	MT_HTABLE	6	/* IMP host tables */
#define	MT_ATABLE	7	/* address resolution tables */
#define	MT_SONAME	8	/* socket name */
#define	MT_ZOMBIE	9	/* zombie proc status */
#define	MT_SOOPTS	10	/* socket options */
#define	MT_FTABLE	11	/* fragment reassembly header */
#define	MT_RIGHTS	12	/* access rights */
#define	MT_IFADDR	13	/* interface address */

/*
 * Values for m_cltype: applicable only for cluster mbufs
 */
#define	MCL_STATIC	1	/* data in mbuf cluster pool */
#define	MCL_LOANED	2	/* data allocated elsewhere and "loaned"
				   to the mbuf */

/* flags to m_get */
#define	M_DONTWAIT	0
#define	M_WAIT		1

/* flags to m_pgalloc */
#define	MPG_MBUFS	0		/* put new mbufs on free list */
#define	MPG_CLUSTERS	1		/* put new clusters on free list */
#define	MPG_SPACE	2		/* don't free; caller wants space */

/* length to m_copy to copy all */
#define	M_COPYALL	1000000000

/*
 * m_pullup will pull up additional length if convenient;
 * should be enough to hold headers of second-level and higher protocols. 
 */
#define	MPULL_EXTRA	32

/*
 * Macros for mbuf manipulation.
 *
 * Standard 4.3 defines some additional macros not given here
 * (MTOCL, MCLFREE), as they are useful only within uipc_mbuf.c
 * or can't cope with the existence of the MCL_LOANED cluster
 * mbuf type.
 *
 * MCLALLOC allocates MCL_STATIC clusters.  Note that it works
 * only with a count of 1 at the moment.  MCLGET connects such clusters
 * to a normal mbuf.  m->m_len is set to MCLBYTES upon success.
 */

#define	MGET(m, i, t) \
	{ int ms = splimp(); \
	  if ((m)=mfree) \
		{ if ((m)->m_type != MT_FREE) panic("mget"); (m)->m_type = t; \
		  mbstat.m_mtypes[MT_FREE]--; mbstat.m_mtypes[t]++; \
		  mfree = (m)->m_next; (m)->m_next = 0; \
		  (m)->m_off = MMINOFF; } \
	  else \
		(m) = m_more(i, t); \
	  (void) splx(ms); }

#define	M_HASCL(m)	((m)->m_off >= MSIZE)

#define	MCLALLOC(m, i) \
	{ int ms = splimp(); \
	  if (mclfree == 0) \
		(void)m_clalloc(1, MPG_CLUSTERS, M_DONTWAIT); \
	  if ((m)=mclfree) \
	     {++mclrefcnt[mtocl(m)];mbstat.m_clfree--;mclfree = (m)->m_next;} \
	  splx(ms); }

/*
 * N.B.: no success/failure indication given.
 * Use mclget if you care.
 */
#define	MCLGET(m) \
	{ struct mbuf *p; \
	  MCLALLOC(p, 1); \
	  if (p) { \
		(m)->m_off = (int)p - (int)(m); \
		(m)->m_len = MCLBYTES; \
		(m)->m_cltype = MCL_STATIC; \
	  } \
	  else \
	  	(m)->m_len = 0; \
	}

#define	MFREE(m, n) \
	{ int ms = splimp(); \
	  if ((m)->m_type == MT_FREE) panic("mfree"); \
	  mbstat.m_mtypes[(m)->m_type]--; mbstat.m_mtypes[MT_FREE]++; \
	  (m)->m_type = MT_FREE; \
	  if (M_HASCL(m)) \
		mclput(m); \
	  (n) = (m)->m_next; (m)->m_next = mfree; \
	  (m)->m_off = 0; (m)->m_act = 0; mfree = (m); \
	  (void) splx(ms); \
	  if (m_want) { \
		  m_want = 0; \
		  wakeup((caddr_t)&mfree); \
	  } \
	}

/*
 * Mbuf statistics.
 */
struct mbstat {
	short	m_mbufs;	/* mbufs obtained from page pool */
	short	m_clusters;	/* clusters obtained from page pool */
	short	m_clfree;	/* free clusters */
	short	m_drops;	/* times failed to find space */
	short	m_mtypes[256];	/* type specific mbuf allocations */
};

#ifdef	KERNEL
extern	struct mbuf mbutl[];		/* virtual address of net free mem */
extern	struct pte Mbmap[];		/* page tables to map mbutl */
struct	mbstat mbstat;
struct	mbuf *mfree, *mclfree;
int	m_want;
struct	mbuf *m_get(),*m_getclr(),*m_free(),*m_more(),*m_copy(),*m_pullup();
struct	mbuf *mclgetx();
caddr_t	m_clalloc();
#endif

#endif	_sys_mbuf_h
