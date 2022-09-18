h48649
s 00001/00000/00377
d D 8.5 95/02/19 07:50:08 cgd 65 64
c add proto for m_reclaim
e
s 00009/00008/00368
d D 8.4 95/01/09 18:16:08 cgd 64 63
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00003/00374
d D 8.3 94/01/21 20:01:40 bostic 63 62
c copyright typo
e
s 00001/00001/00376
d D 8.2 94/01/11 15:55:26 mckusick 62 61
c clean up include syntax
e
s 00000/00000/00377
d D 8.1 93/06/04 16:47:41 bostic 61 60
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00008/00366
d D 7.19 93/06/04 16:31:09 sklower 60 58
c add function prototype for m_copyback
e
s 00002/00002/00372
d R 8.1 93/06/02 19:54:11 bostic 59 58
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00015/00359
d D 7.18 92/07/11 04:02:10 torek 58 57
c comment within comment gives compiler indigestion (as it should)
e
s 00023/00013/00351
d D 7.17 92/05/11 17:58:43 mckusick 57 56
c add MBUFLOCK to protect statistics updates (from forys@snake.cs.utah.edu)
e
s 00001/00001/00363
d D 7.16 92/05/11 17:55:22 mckusick 56 55
c fix cltom macro (from forys@snake.cs.utah.edu)
e
s 00011/00003/00353
d D 7.15 92/02/05 19:33:57 torek 55 54
c add prototypes
e
s 00005/00006/00351
d D 7.14 90/12/05 15:28:22 mckusick 54 53
c update for new VM
e
s 00001/00011/00356
d D 7.13 90/06/28 21:59:23 bostic 53 52
c new copyright notice
e
s 00014/00030/00353
d D 7.12 89/09/04 14:33:14 sklower 52 50
c (checked in for sklower) move machdep to machparam.h;
c add (temp) m_copy compat macro; hack (temp) mbtypes for datakit (karels)
e
s 00010/00005/00176
d D 7.8.1.3 89/02/14 18:10:28 karels 51 48
c once more, with feeling... update copyright
e
s 00297/00093/00086
d D 7.11 88/08/27 15:43:42 karels 50 49
c new mbufs, working (but should move m_nextpkt to m_pkthdr)
e
s 00001/00001/00178
d D 7.10 88/02/08 10:53:23 karels 49 47
c update copyright dates
e
s 00009/00003/00172
d D 7.8.1.2 88/02/08 10:52:35 karels 48 46
c update copyright on branch
e
s 00008/00002/00171
d D 7.9 87/12/30 11:59:22 bostic 47 45
c add Berkeley header
e
s 00000/00000/00175
d D 7.8.1.1 87/10/06 14:22:50 karels 46 45
x 41 40
c branch version without malloc (for monet and dist)
e
s 00017/00006/00156
d D 7.8 87/07/03 12:15:21 karels 45 41
c fix potential bug when cluster allocation fails;
c add MCLBYTES for larger page sizes
e
s 00017/00006/00156
d R 7.8 87/07/03 12:11:34 karels 44 41
c fix potential bug when cluster allocation fails; 
c add MCLBYTES for larger page sizes
e
s 00017/00006/00156
d R 7.8 87/07/03 11:24:26 karels 43 41
c fix potential bug when cluster allocation fails; 
c add MCLBYTES for larger page sizes
e
s 00014/00005/00157
d R 7.8 87/06/30 18:12:05 karels 42 41
c fix potential bug when cluster allocation fails;
c add MCLBYTES for larger page sizes
e
s 00001/00002/00161
d D 7.7 87/06/21 18:13:26 mckusick 41 40
c MPG_SPACE is replaced by malloc
e
s 00000/00001/00163
d D 7.6 87/06/20 14:26:15 mckusick 40 39
c no more MT_ZOMBIE's
e
s 00008/00005/00156
d D 7.5 87/02/02 18:02:02 karels 39 38
c more statistics
e
s 00004/00000/00157
d D 7.4 86/12/03 22:24:13 karels 38 37
c more mbufs for gateways
e
s 00002/00002/00155
d D 7.3 86/09/11 06:20:02 karels 37 36
x 36
c better fix for MCLGET race, call m_clalloc from MCLALLOC
e
s 00005/00003/00154
d D 7.2 86/09/04 19:16:08 karels 36 34
c need to splimp in MCLGET for calling m_clalloc
e
s 00005/00003/00154
d R 7.2 86/09/04 11:32:46 karels 35 34
c need to call m_clalloc at splimp from MCLALLOC
e
s 00001/00001/00156
d D 7.1 86/06/04 23:24:49 mckusick 34 33
c 4.3BSD release version
e
s 00001/00001/00156
d D 6.12 86/02/21 19:04:54 karels 33 32
c missed arg to m_clalloc
e
s 00029/00005/00128
d D 6.11 86/02/18 16:35:39 karels 32 30
c clean up cluster allocation
e
s 00028/00006/00127
d R 6.11 86/02/18 16:26:31 karels 31 30
c clean up cluster allocation
e
s 00000/00004/00133
d D 6.10 85/12/19 16:18:34 karels 30 29
c rm bbnnet
e
s 00006/00000/00131
d D 6.9 85/09/16 23:32:53 karels 29 28
c pullup a bit extra if wasy
e
s 00002/00002/00129
d D 6.8 85/09/05 15:31:43 karels 28 27
c full sized mbcluster pool; fix wakeup
e
s 00005/00000/00126
d D 6.7 85/08/22 10:00:31 walsh 27 26
c bbn net code currently requires 256 byte mbufs for protocol state
e
s 00001/00001/00125
d D 6.6 85/06/29 12:13:34 karels 26 24
c off by one in MFREE
e
s 00001/00001/00125
d R 6.6 85/06/29 12:09:10 karels 25 24
c off by one in MFREE
e
s 00007/00001/00119
d D 6.5 85/06/08 15:01:09 mckusick 24 23
c Add copyright
e
s 00007/00001/00113
d D 6.4 85/05/05 23:27:34 karels 23 22
c implement M_WAIT
e
s 00001/00000/00113
d D 6.3 85/03/07 22:00:54 karels 22 21
c new type
e
s 00005/00004/00108
d D 6.2 84/08/21 10:16:15 karels 21 20
c add RIGHTS type for mbufs, use m_act correctly for queuing datagrams
c (for sam)
e
s 00000/00000/00112
d D 6.1 83/07/29 06:13:02 sam 20 19
c 4.2 distribution
e
s 00001/00001/00111
d D 4.18 83/03/25 11:51:07 sam 19 18
c make histogram very large so we don't have to change this file again
e
s 00001/00001/00111
d D 4.17 83/01/17 21:14:54 sam 18 16
c more machine independet
e
s 00001/00001/00111
d R 4.17 83/01/17 15:47:30 sam 17 16
c machine independent?
e
s 00028/00011/00084
d D 4.16 82/12/14 17:20:10 sam 16 15
c typed mbufs
e
s 00001/00001/00094
d D 4.15 82/10/20 01:56:58 root 15 14
c lint
e
s 00002/00001/00093
d D 4.14 82/10/05 22:09:04 root 14 13
c MGET sets m_off to MMINOFF
e
s 00001/00007/00093
d D 4.13 82/06/14 22:17:00 wnj 13 12
c get rid of m_mbcommitted
e
s 00020/00011/00080
d D 4.12 82/05/18 21:48:03 sam 12 11
c rethink statistics
e
s 00003/00000/00088
d D 4.11 82/01/24 18:46:12 wnj 11 10
c M_COPYALL
e
s 00001/00001/00087
d D 4.10 81/12/23 14:07:39 root 10 9
c m_pullup declared struct mbuf *
e
s 00004/00002/00084
d D 4.9 81/12/20 15:29:51 root 9 8
c consistency checks on free/alloc
e
s 00010/00004/00076
d D 4.8 81/12/09 20:49:21 wnj 8 7
c pages->clusters
e
s 00003/00003/00077
d D 4.7 81/11/29 22:14:05 wnj 7 6
c lint & wkend editing
e
s 00014/00015/00066
d D 4.6 81/11/26 11:53:47 wnj 6 5
c before carry to arpavax
e
s 00001/00001/00080
d D 4.5 81/11/18 15:46:51 wnj 5 4
c more cleanup
e
s 00001/00001/00080
d D 4.4 81/11/14 16:51:04 wnj 4 3
c just before overlay of ip
e
s 00017/00013/00064
d D 4.3 81/11/08 16:39:18 wnj 3 2
c first listing
e
s 00013/00009/00064
d D 4.2 81/10/29 20:51:46 wnj 2 1
c misc changes
e
s 00073/00000/00000
d D 4.1 81/10/29 17:39:02 wnj 1 0
c date and time created 81/10/29 17:39:02 by wnj
e
u
U
f b 
t
T
I 1
D 12
/* %M% %I% %E% */
E 12
I 12
D 24
/*	%M%	%I%	%E%	*/
E 24
I 24
/*
D 34
 * Copyright (c) 1982 Regents of the University of California.
E 34
I 34
D 48
D 49
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 49
I 49
D 60
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 60
I 60
D 63
 * Copyright (c)
 *	1982, 1986, 1988, 1993  Regents of the University of California.
E 60
E 49
E 34
D 47
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 48
I 48
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 51
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 51
I 51
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 51
E 48
E 47
I 47
 * All rights reserved.
E 63
I 63
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 63
 *
D 53
 * Redistribution and use in source and binary forms are permitted
D 50
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 50
I 50
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 53
I 53
 * %sccs.include.redist.c%
E 53
E 50
E 47
 *
 *	%W% (Berkeley) %G%
 */
E 24
E 12

I 50
#ifndef M_WAITOK
D 62
#include "malloc.h"
E 62
I 62
#include <sys/malloc.h>
E 62
#endif

E 50
/*
D 50
 * Constants related to memory allocator.
E 50
I 50
D 52
 * Constants related to network buffer management.
 * Mbufs are of a single size, MSIZE, which includes overhead.
 * An mbuf may add a single "mbuf cluster" of size MCLBYTES,
 * which has no additional overhead and is used instead of the internal
 * data area; this is done when at least MINCLSIZE of data must be stored.
 * MCLBYTES must be no larger than CLBYTES (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
E 52
I 52
 * Mbufs are of a single size, MSIZE (machine/machparam.h), which
 * includes overhead.  An mbuf may add a single "mbuf cluster" of size
 * MCLBYTES (also in machine/machparam.h), which has no additional overhead
 * and is used instead of the internal data area; this is done when
 * at least MINCLSIZE of data must be stored.
E 52
E 50
 */
I 50
D 52
/* BEGIN SHOULD MOVE TO MACHINE-SPECIFIC FILE (machparam.h) */
E 50
I 27
D 30
#ifdef BBNNET
#define MSIZE		256
#else
E 30
E 27
D 6
#define	PGSIZE		1024
E 6
#define	MSIZE		128			/* size of an mbuf */
I 27
D 30
#endif
E 30
D 50

E 50
I 50
#define	MAPPED_MBUFS
E 50
I 45
#if CLBYTES > 1024
#define	MCLBYTES	1024
#define	MCLSHIFT	10
#define	MCLOFSET	(MCLBYTES - 1)
#else
#define	MCLBYTES	CLBYTES
#define	MCLSHIFT	CLSHIFT
#define	MCLOFSET	CLOFSET
#endif
D 50

E 45
E 27
#define	MMINOFF		12			/* mbuf header length */
#define	MTAIL		4
#define	MMAXOFF		(MSIZE-MTAIL)		/* offset where data ends */
#define	MLEN		(MSIZE-MMINOFF-MTAIL)	/* mbuf data length */
E 50
I 38
#ifdef GATEWAY
#define	NMBCLUSTERS	512
#else
E 38
D 3
#define	NMPAGES		256
E 3
I 3
D 7
#define	NMBPAGES	256
E 7
I 7
#define	NMBCLUSTERS	256
I 38
#endif
E 38
I 12
D 50
#define	NMBPCL		(CLBYTES/MSIZE)		/* # mbufs per cluster */
E 50
I 50
/* END SHOULD MOVE TO MACHINE-SPECIFIC FILE (machparam.h) */
E 52
E 50
E 12
E 7
E 3

I 50
#define	MLEN		(MSIZE - sizeof(struct m_hdr))	/* normal data len */
#define	MHLEN		(MLEN - sizeof(struct pkthdr))	/* data len w/pkthdr */

#define	MINCLSIZE	(MHLEN + MLEN)	/* smallest amount to put in cluster */
#define	M_MAXCOMPRESS	(MHLEN / 2)	/* max amount to copy for compression */

E 50
/*
 * Macros for type conversion
I 50
 * mtod(m,t) -	convert mbuf pointer to data pointer of correct type
 * dtom(x) -	convert data pointer within mbuf to mbuf pointer (XXX)
 * mtocl(x) -	convert pointer within cluster to cluster index #
 * cltom(x) -	convert cluster # to ptr to beginning of cluster
E 50
D 8
 *
 * CONSTANTS HERE ARE A CROCK
E 8
 */
I 50
D 64
#define mtod(m,t)	((t)((m)->m_data))
D 54
#define	dtom(x)		((struct mbuf *)((int)x & ~(MSIZE-1)))
#define	mtocl(x)	(((u_int)x - (u_int)mbutl) >> MCLSHIFT)
#define	cltom(x)	((caddr_t)mbutl[x])
E 54
I 54
#define	dtom(x)		((struct mbuf *)((int)(x) & ~(MSIZE-1)))
#define	mtocl(x)	(((u_int)(x) - (u_int)mbutl) >> MCLSHIFT)
D 56
#define	cltom(x)	((caddr_t)((u_int)mbutl + ((u_int)(x) >> MCLSHIFT)))
E 56
I 56
#define	cltom(x)	((caddr_t)((u_int)mbutl + ((u_int)(x) << MCLSHIFT)))
E 64
I 64
#define	mtod(m,t)	((t)((m)->m_data))
#define	dtom(x)		((struct mbuf *)((long)(x) & ~(MSIZE-1)))
#define	mtocl(x)	(((u_long)(x) - (u_long)mbutl) >> MCLSHIFT)
#define	cltom(x)	((caddr_t)((u_long)mbutl + ((u_long)(x) << MCLSHIFT)))
E 64
E 56
E 54
E 50

D 6
/* network page map number to virtual address, and back */
D 3
#define	pftom(x) ((struct mbuf *)((x << 10) + (int)netutl))
#define	mtopf(x) ((((int)x & ~0x3ff) - (int)netutl) >> 10)
E 3
I 3
#define	pftom(x) ((struct mbuf *)((x << 10) + (int)mbutl))
#define	mtopf(x) ((((int)x & ~0x3ff) - (int)mbutl) >> 10)
E 6
I 6
D 50
/* network cluster number to virtual address, and back */
D 45
#define	cltom(x) ((struct mbuf *)((int)mbutl + ((x) << CLSHIFT)))
#define	mtocl(x) (((int)x - (int)mbutl) >> CLSHIFT)
E 45
I 45
#define	cltom(x) ((struct mbuf *)((int)mbutl + ((x) << MCLSHIFT)))
#define	mtocl(x) (((int)x - (int)mbutl) >> MCLSHIFT)
E 50
I 50
/* header at beginning of each mbuf: */
struct m_hdr {
	struct	mbuf *mh_next;		/* next buffer in chain */
	struct	mbuf *mh_nextpkt;	/* next chain in queue/record */
D 64
	int	mh_len;			/* amount of data in this mbuf */
E 64
	caddr_t	mh_data;		/* location of data */
I 64
	int	mh_len;			/* amount of data in this mbuf */
E 64
	short	mh_type;		/* type of data in this mbuf */
	short	mh_flags;		/* flags; see below */
};
E 50
E 45
E 6
E 3

D 50
/* address in mbuf to mbuf head */
D 6
#define	dtom(x)		((struct mbuf *)((int)x & ~0x7f))
#define	mtoff(x) 	(((int)x & 0x3ff) >> 7)
E 6
I 6
#define	dtom(x)		((struct mbuf *)((int)x & ~(MSIZE-1)))
E 50
I 50
/* record/packet header in first mbuf of chain; valid if M_PKTHDR set */
struct	pkthdr {
D 64
	int	len;		/* total packet length */
	struct	ifnet *rcvif;	/* rcv interface */
E 64
I 64
	struct	ifnet *rcvif;		/* rcv interface */
	int	len;			/* total packet length */
E 64
};
E 50

D 50
/* mbuf head, to typed data */
E 6
#define	mtod(x,t)	((t)((int)(x) + (x)->m_off))
E 50
I 50
/* description of external storage mapped into mbuf, valid if M_EXT set */
struct m_ext {
	caddr_t	ext_buf;		/* start of buffer */
	void	(*ext_free)();		/* free routine if not the usual */
	u_int	ext_size;		/* size of buffer, for ext_free */
};
E 50

struct mbuf {
D 50
	struct	mbuf *m_next;		/* next buffer in chain */
	u_long	m_off;			/* offset of data */
	short	m_len;			/* amount of data in this mbuf */
D 9
	short	m_cnt;			/* reference count */
E 9
I 9
D 16
	short	m_free;			/* is mbuf free? (consistency check) */
E 16
I 16
	short	m_type;			/* mbuf type (0 == free) */
E 16
E 9
	u_char	m_dat[MLEN];		/* data storage */
	struct	mbuf *m_act;		/* link in higher-level mbuf list */
E 50
I 50
	struct	m_hdr m_hdr;
	union {
		struct {
			struct	pkthdr MH_pkthdr;	/* M_PKTHDR set */
			union {
				struct	m_ext MH_ext;	/* M_EXT set */
				char	MH_databuf[MHLEN];
			} MH_dat;
		} MH;
		char	M_databuf[MLEN];		/* !M_PKTHDR, !M_EXT */
	} M_dat;
E 50
};
I 50
#define	m_next		m_hdr.mh_next
#define	m_len		m_hdr.mh_len
#define	m_data		m_hdr.mh_data
#define	m_type		m_hdr.mh_type
#define	m_flags		m_hdr.mh_flags
#define	m_nextpkt	m_hdr.mh_nextpkt
#define	m_act		m_nextpkt
#define	m_pkthdr	M_dat.MH.MH_pkthdr
#define	m_ext		M_dat.MH.MH_dat.MH_ext
#define	m_pktdat	M_dat.MH.MH_dat.MH_databuf
#define	m_dat		M_dat.M_databuf
E 50
D 3
struct	mbuf *mfree, *mpfree;
int	nmpfree;
char	mprefcnt[NMPAGES];
struct	mbuf *m_get(), *m_free(), *m_more();
E 3

I 50
/* mbuf flags */
#define	M_EXT		0x0001	/* has associated external storage */
#define	M_PKTHDR	0x0002	/* start of record */
#define	M_EOR		0x0004	/* end of record */

/* mbuf pkthdr flags, also in m_flags */
#define	M_BCAST		0x0100	/* send/received as link-level broadcast */
#define	M_MCAST		0x0200	/* send/received as link-level multicast */

/* flags copied when copying m_pkthdr */
#define	M_COPYFLAGS	(M_PKTHDR|M_EOR|M_BCAST|M_MCAST)

E 50
I 16
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
D 40
#define	MT_ZOMBIE	9	/* zombie proc status */
E 40
#define	MT_SOOPTS	10	/* socket options */
#define	MT_FTABLE	11	/* fragment reassembly header */
I 21
#define	MT_RIGHTS	12	/* access rights */
I 22
#define	MT_IFADDR	13	/* interface address */
I 50
#define MT_CONTROL	14	/* extra-data protocol message */
#define MT_OOBDATA	15	/* expedited data  */
E 50
E 22
E 21

E 16
I 3
D 8
#define	M_WAIT	1
E 8
I 8
D 50
/* flags to m_get */
#define	M_DONTWAIT	0
#define	M_WAIT		1
E 50
I 50
/* flags to m_get/MGET */
#define	M_DONTWAIT	M_NOWAIT
#define	M_WAIT		M_WAITOK
E 50
E 8

I 8
D 50
/* flags to m_pgalloc */
#define	MPG_MBUFS	0		/* put new mbufs on free list */
#define	MPG_CLUSTERS	1		/* put new clusters on free list */
E 50
I 50
/*
I 57
 * mbuf utility macros:
 *
 *	MBUFLOCK(code)
 * prevents a section of code from from being interrupted by network
 * drivers.
 */
#define	MBUFLOCK(code) \
	{ int ms = splimp(); \
	  { code } \
	  splx(ms); \
	}

/*
E 57
 * mbuf allocation/deallocation macros:
 *
 *	MGET(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain internal data.
 *
 *	MGETHDR(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain a packet header
 * and internal data.
 */
#define	MGET(m, how, type) { \
	MALLOC((m), struct mbuf *, MSIZE, mbtypes[type], (how)); \
	if (m) { \
		(m)->m_type = (type); \
D 57
		mbstat.m_mtypes[type]++; \
E 57
I 57
		MBUFLOCK(mbstat.m_mtypes[type]++;) \
E 57
		(m)->m_next = (struct mbuf *)NULL; \
		(m)->m_nextpkt = (struct mbuf *)NULL; \
		(m)->m_data = (m)->m_dat; \
		(m)->m_flags = 0; \
	} else \
		(m) = m_retry((how), (type)); \
}
E 50
D 41
#define	MPG_SPACE	2		/* don't free; caller wants space */
E 41

I 11
D 50
/* length to m_copy to copy all */
#define	M_COPYALL	1000000000
E 50
I 50
#define	MGETHDR(m, how, type) { \
	MALLOC((m), struct mbuf *, MSIZE, mbtypes[type], (how)); \
	if (m) { \
		(m)->m_type = (type); \
D 57
		mbstat.m_mtypes[type]++; \
E 57
I 57
		MBUFLOCK(mbstat.m_mtypes[type]++;) \
E 57
		(m)->m_next = (struct mbuf *)NULL; \
		(m)->m_nextpkt = (struct mbuf *)NULL; \
		(m)->m_data = (m)->m_pktdat; \
		(m)->m_flags = M_PKTHDR; \
	} else \
		(m) = m_retryhdr((how), (type)); \
}
E 50

I 29
/*
D 50
 * m_pullup will pull up additional length if convenient;
 * should be enough to hold headers of second-level and higher protocols. 
E 50
I 50
 * Mbuf cluster macros.
 * MCLALLOC(caddr_t p, int how) allocates an mbuf cluster.
 * MCLGET adds such clusters to a normal mbuf;
 * the flag M_EXT is set upon success.
 * MCLFREE releases a reference to a cluster allocated by MCLALLOC,
 * freeing the cluster if the reference count has reached 0.
 *
 * Normal mbuf clusters are normally treated as character arrays
 * after allocation, but use the first word of the buffer as a free list
 * pointer while on the free list.
E 50
 */
D 50
#define	MPULL_EXTRA	32
E 50
I 50
union mcluster {
	union	mcluster *mcl_next;
	char	mcl_buf[MCLBYTES];
};
E 50

E 29
E 11
E 8
E 3
D 16
#define	MGET(m, i) \
E 16
I 16
D 50
#define	MGET(m, i, t) \
E 50
I 50
#define	MCLALLOC(p, how) \
E 50
E 16
D 2
	{ int ms = spl_imp(); \
E 2
I 2
D 57
	{ int ms = splimp(); \
E 57
I 57
	MBUFLOCK( \
E 57
E 2
D 50
	  if ((m)=mfree) \
D 2
		{ netcb.n_bufs--; mfree = (m)->m_next; (m)->m_next = 0; } \
E 2
I 2
D 9
		{ mbstat.m_bufs--; mfree = (m)->m_next; (m)->m_next = 0; } \
E 9
I 9
D 16
		{ if ((m)->m_free == 0) panic("mget"); (m)->m_free = 0; \
D 12
		  mbstat.m_bufs--; mfree = (m)->m_next; (m)->m_next = 0; } \
E 12
I 12
D 14
		  mbstat.m_mbfree--; mfree = (m)->m_next; (m)->m_next = 0; } \
E 14
I 14
		  mbstat.m_mbfree--; mfree = (m)->m_next; (m)->m_next = 0; \
E 16
I 16
		{ if ((m)->m_type != MT_FREE) panic("mget"); (m)->m_type = t; \
D 21
		  mbstat.m_mbfree--; mbstat.m_mtypes[t]++; \
E 21
I 21
		  mbstat.m_mtypes[MT_FREE]--; mbstat.m_mtypes[t]++; \
E 21
		  mfree = (m)->m_next; (m)->m_next = 0; \
E 16
		  (m)->m_off = MMINOFF; } \
E 14
E 12
E 9
E 2
	  else \
D 16
		(m) = m_more(i); \
E 16
I 16
		(m) = m_more(i, t); \
E 16
	  splx(ms); }
D 6
#define	MPGET(m, i) \
E 6
I 6
D 32
#define	MCLGET(m, i) \
E 32
I 32
/*
 * Mbuf page cluster macros.
 * MCLALLOC allocates mbuf page clusters.
 * Note that it works only with a count of 1 at the moment.
I 36
 * It must be called at splimp.
E 36
 * MCLGET adds such clusters to a normal mbuf.
D 45
 * m->m_len is set to CLBYTES upon success.
E 45
I 45
 * m->m_len is set to MCLBYTES upon success, and to MLEN on failure.
E 45
 * MCLFREE frees clusters allocated by MCLALLOC.
 */
#define	MCLALLOC(m, i) \
E 32
E 6
D 2
	{ int ms = spl_imp(); \
E 2
I 2
D 36
	{ int ms = splimp(); \
E 50
I 37
	  if (mclfree == 0) \
D 50
		(void)m_clalloc((i), MPG_CLUSTERS, M_DONTWAIT); \
E 37
E 2
D 6
	  if ((m)=mpfree) \
	      { ++mprefcnt[mtopf(m)]; nmpfree--; mpfree = (m)->m_next; } \
E 6
I 6
	  if ((m)=mclfree) \
E 36
I 36
	{ if ((m)=mclfree) \
E 36
D 12
	      { ++mclrefcnt[mtocl(m)]; nmclfree--; mclfree = (m)->m_next; } \
E 12
I 12
	     {++mclrefcnt[mtocl(m)];mbstat.m_clfree--;mclfree = (m)->m_next;} \
E 12
E 6
D 36
	  splx(ms); }
E 36
I 36
	}
E 36
I 32
#define	M_HASCL(m)	((m)->m_off >= MSIZE)
D 45
#define	MTOCL(m)	((struct mbuf *)(mtod((m), int)&~CLOFSET))
E 45
I 45
#define	MTOCL(m)	((struct mbuf *)(mtod((m), int) &~ MCLOFSET))
E 50
I 50
		(void)m_clalloc(1, (how)); \
D 64
	  if ((p) = (caddr_t)mclfree) { \
E 64
I 64
	  if (((p) = (caddr_t)mclfree) != 0) { \
E 64
		++mclrefcnt[mtocl(p)]; \
		mbstat.m_clfree--; \
		mclfree = ((union mcluster *)(p))->mcl_next; \
	  } \
D 57
	  splx(ms); \
	}
E 57
I 57
	)
E 57
E 50
E 45

D 50
#define	MCLGET(m) \
	{ struct mbuf *p; \
I 36
	  int ms = splimp(); \
E 36
D 37
	  if (mclfree == 0) \
D 33
		(void)m_clalloc(1, MPG_CLUSTERS); \
E 33
I 33
		(void)m_clalloc(1, MPG_CLUSTERS, M_DONTWAIT); \
E 37
E 33
	  MCLALLOC(p, 1); \
	  if (p) { \
		(m)->m_off = (int)p - (int)(m); \
D 45
		(m)->m_len = CLBYTES; \
	  } \
E 45
I 45
		(m)->m_len = MCLBYTES; \
	  } else \
		(m)->m_len = MLEN; \
E 50
I 50
#define	MCLGET(m, how) \
	{ MCLALLOC((m)->m_ext.ext_buf, (how)); \
	  if ((m)->m_ext.ext_buf != NULL) { \
		(m)->m_data = (m)->m_ext.ext_buf; \
		(m)->m_flags |= M_EXT; \
		(m)->m_ext.ext_size = MCLBYTES;  \
	  } \
E 50
E 45
I 36
	  splx(ms); \
E 36
	}
D 50
#define	MCLFREE(m) { \
	if (--mclrefcnt[mtocl(m)] == 0) \
	    { (m)->m_next = mclfree;mclfree = (m);mbstat.m_clfree++;} \
	}
E 32
#define	MFREE(m, n) \
E 50
I 50

#define	MCLFREE(p) \
E 50
D 2
	{ int ms = spl_imp(); \
E 2
I 2
D 57
	{ int ms = splimp(); \
E 57
I 57
	MBUFLOCK ( \
E 57
I 9
D 16
	  if ((m)->m_free) panic("mfree"); (m)->m_free = 1; \
E 16
I 16
D 50
	  if ((m)->m_type == MT_FREE) panic("mfree"); \
D 21
	  mbstat.m_mtypes[(m)->m_type]--; (m)->m_type = MT_FREE; \
E 21
I 21
	  mbstat.m_mtypes[(m)->m_type]--; mbstat.m_mtypes[MT_FREE]++; \
	  (m)->m_type = MT_FREE; \
E 21
E 16
E 9
E 2
D 26
	  if ((m)->m_off > MSIZE) { \
E 26
I 26
D 32
	  if ((m)->m_off >= MSIZE) { \
E 26
D 18
		(n) = (struct mbuf *)(mtod(m, int)&~0x3ff); \
E 18
I 18
		(n) = (struct mbuf *)(mtod(m, int)&~CLOFSET); \
E 18
D 6
		if (--mprefcnt[mtopf(n)] == 0) \
		    { (n)->m_next = mpfree; mpfree = (n); nmpfree++; } \
E 6
I 6
		if (--mclrefcnt[mtocl(n)] == 0) \
D 12
		    { (n)->m_next = mclfree; mclfree = (n); nmclfree++; } \
E 12
I 12
		    { (n)->m_next = mclfree;mclfree = (n);mbstat.m_clfree++;} \
E 32
I 32
	  if (M_HASCL(m)) { \
		(n) = MTOCL(m); \
		MCLFREE(n); \
E 50
I 50
	  if (--mclrefcnt[mtocl(p)] == 0) { \
		((union mcluster *)(p))->mcl_next = mclfree; \
		mclfree = (union mcluster *)(p); \
		mbstat.m_clfree++; \
E 50
E 32
E 12
E 6
	  } \
D 50
	  (n) = (m)->m_next; (m)->m_next = mfree; \
D 2
	  (m)->m_off = 0; (m)->m_act = 0; mfree = (m); netcb.n_bufs++; \
E 2
I 2
D 12
	  (m)->m_off = 0; (m)->m_act = 0; mfree = (m); mbstat.m_bufs++; \
E 12
I 12
D 21
	  (m)->m_off = 0; (m)->m_act = 0; mfree = (m); mbstat.m_mbfree++; \
E 21
I 21
	  (m)->m_off = 0; (m)->m_act = 0; mfree = (m); \
E 50
E 21
E 12
E 2
D 23
	  splx(ms); }
E 23
I 23
D 57
	  splx(ms); \
D 50
	  if (m_want) { \
		  m_want = 0; \
D 28
		  wakeup((caddr_t)mfree); \
E 28
I 28
		  wakeup((caddr_t)&mfree); \
E 50
I 50
	}
E 57
I 57
	)
E 57

/*
 * MFREE(struct mbuf *m, struct mbuf *n)
 * Free a single mbuf and associated external storage.
 * Place the successor, if any, in n.
 */
#ifdef notyet
#define	MFREE(m, n) \
D 57
	{ mbstat.m_mtypes[(m)->m_type]--; \
E 57
I 57
	{ MBUFLOCK(mbstat.m_mtypes[(m)->m_type]--;) \
E 57
	  if ((m)->m_flags & M_EXT) { \
		if ((m)->m_ext.ext_free) \
			(*((m)->m_ext.ext_free))((m)->m_ext.ext_buf, \
			    (m)->m_ext.ext_size); \
		else \
			MCLFREE((m)->m_ext.ext_buf); \
E 50
E 28
	  } \
I 50
	  (n) = (m)->m_next; \
	  FREE((m), mbtypes[(m)->m_type]); \
E 50
	}
I 50
#else /* notyet */
#define	MFREE(m, nn) \
D 57
	{ mbstat.m_mtypes[(m)->m_type]--; \
E 57
I 57
	{ MBUFLOCK(mbstat.m_mtypes[(m)->m_type]--;) \
E 57
	  if ((m)->m_flags & M_EXT) { \
		MCLFREE((m)->m_ext.ext_buf); \
	  } \
	  (nn) = (m)->m_next; \
	  FREE((m), mbtypes[(m)->m_type]); \
	}
#endif
E 50
E 23
D 6
#define	NMBPG (PGSIZE/MSIZE)		/* mbufs/page */
E 6

I 12
/*
I 50
 * Copy mbuf pkthdr from from to to.
 * from must have M_PKTHDR set, and to must be empty.
 */
#define	M_COPY_PKTHDR(to, from) { \
	(to)->m_pkthdr = (from)->m_pkthdr; \
	(to)->m_flags = (from)->m_flags & M_COPYFLAGS; \
	(to)->m_data = (to)->m_pktdat; \
}

/*
 * Set the m_data pointer of a newly-allocated mbuf (m_get/MGET) to place
 * an object of the specified size at the end of the mbuf, longword aligned.
 */
#define	M_ALIGN(m, len) \
	{ (m)->m_data += (MLEN - (len)) &~ (sizeof(long) - 1); }
/*
 * As above, for mbufs allocated with m_gethdr/MGETHDR
 * or initialized by M_COPY_PKTHDR.
 */
#define	MH_ALIGN(m, len) \
	{ (m)->m_data += (MHLEN - (len)) &~ (sizeof(long) - 1); }

/*
 * Compute the amount of space available
 * before the current start of data in an mbuf.
 */
#define	M_LEADINGSPACE(m) \
	((m)->m_flags & M_EXT ? /* (m)->m_data - (m)->m_ext.ext_buf */ 0 : \
	    (m)->m_flags & M_PKTHDR ? (m)->m_data - (m)->m_pktdat : \
	    (m)->m_data - (m)->m_dat)

/*
 * Compute the amount of space available
 * after the end of data in an mbuf.
 */
#define	M_TRAILINGSPACE(m) \
	((m)->m_flags & M_EXT ? (m)->m_ext.ext_buf + (m)->m_ext.ext_size - \
	    ((m)->m_data + (m)->m_len) : \
	    &(m)->m_dat[MLEN] - ((m)->m_data + (m)->m_len))

/*
 * Arrange to prepend space of size plen to mbuf m.
 * If a new mbuf must be allocated, how specifies whether to wait.
 * If how is M_DONTWAIT and allocation fails, the original mbuf chain
 * is freed and m is set to NULL.
 */
#define	M_PREPEND(m, plen, how) { \
	if (M_LEADINGSPACE(m) >= (plen)) { \
		(m)->m_data -= (plen); \
		(m)->m_len += (plen); \
	} else \
		(m) = m_prepend((m), (plen), (how)); \
	if ((m) && (m)->m_flags & M_PKTHDR) \
		(m)->m_pkthdr.len += (plen); \
}

/* change mbuf to new type */
#define MCHTYPE(m, t) { \
D 57
	mbstat.m_mtypes[(m)->m_type]--; \
	mbstat.m_mtypes[t]++; \
E 57
I 57
	MBUFLOCK(mbstat.m_mtypes[(m)->m_type]--; mbstat.m_mtypes[t]++;) \
E 57
	(m)->m_type = t;\
}

/* length to m_copy to copy all */
#define	M_COPYALL	1000000000

I 52
/* compatiblity with 4.3 */
#define  m_copy(m, o, l)	m_copym((m), (o), (l), M_DONTWAIT)

E 52
/*
E 50
D 13
 * Mbuf statistics.  Clients can committ hunks of space until we are
 * overcommitted by the fraction represented by MBUFOVERALLOCFRAG.
 * We keep track of the amount of space committed, the number
 * of mbufs and clusters allocated from the free memory pool, and
 * the number of mbufs and clusters on our free lists.
E 13
I 13
 * Mbuf statistics.
E 13
 */
D 13
#define	MBUFOVERALLOCFRACTION	3 / 2		/* don't parenthesize ! */
E 13
E 12
I 2
struct mbstat {
D 3
	short	m_bufs;				/* # free msg buffers */
	short	m_hiwat;			/* # free mbufs allocated */
	short	m_lowat;			/* min. # free mbufs */
	short	m_pages;			/* # pages owned by network */
E 3
I 3
D 12
	short	m_bufs;			/* # free msg buffers */
	short	m_hiwat;		/* # free mbufs allocated */
	short	m_lowat;		/* min. # free mbufs */
D 8
	short	m_pages;		/* # pages owned by network */
E 8
I 8
	short	m_clusters;		/* # pages owned by network */
E 12
I 12
D 13
	short	m_mbcommitted;		/* most we'll allow pool size to get */
E 13
D 16
	short	m_mbufs;		/* mbufs obtained from page pool */
	short	m_mbfree;		/* mbufs on our free list */
	short	m_clusters;		/* clusters obtained from page pool */
	short	m_clfree;		/* free clusters */
E 12
E 8
	short	m_drops;		/* times failed to find space */
E 16
I 16
D 39
	short	m_mbufs;	/* mbufs obtained from page pool */
D 21
	short	m_mbfree;	/* mbufs on our free list */
E 21
	short	m_clusters;	/* clusters obtained from page pool */
	short	m_clfree;	/* free clusters */
	short	m_drops;	/* times failed to find space */
D 19
	short	m_mtypes[32];	/* type specific mbuf allocations */
E 19
I 19
	short	m_mtypes[256];	/* type specific mbuf allocations */
E 39
I 39
	u_long	m_mbufs;	/* mbufs obtained from page pool */
	u_long	m_clusters;	/* clusters obtained from page pool */
D 41
	u_long	m_space;	/* interface pages obtained from page pool */
E 41
I 41
	u_long	m_spare;	/* spare field */
E 41
	u_long	m_clfree;	/* free clusters */
	u_long	m_drops;	/* times failed to find space */
	u_long	m_wait;		/* times waited for space */
	u_long	m_drain;	/* times drained protocols for space */
	u_short	m_mtypes[256];	/* type specific mbuf allocations */
E 39
E 19
E 16
E 3
};

E 2
#ifdef	KERNEL
D 3
extern	struct mbuf netutl[];		/* virtual address of net free mem */
extern	struct pte Netmap[];		/* page tables to map Netutl */
E 3
I 3
D 50
extern	struct mbuf mbutl[];		/* virtual address of net free mem */
extern	struct pte Mbmap[];		/* page tables to map Netutl */
E 50
I 50
D 54
extern	char mbutl[][MCLBYTES];		/* virtual address of mclusters */
extern	struct pte Mbmap[];		/* page tables to map mbutl */
E 54
I 54
extern	struct mbuf *mbutl;		/* virtual address of mclusters */
extern	char *mclrefcnt;		/* cluster reference counts */
E 54
E 50
E 3
I 2
struct	mbstat mbstat;
I 3
D 7
int	nmbpages;
E 7
I 7
D 12
int	nmbclusters;
E 12
I 12
D 15
extern	int nmbclusters;
E 15
I 15
D 57
int	nmbclusters;
E 57
I 57
extern	int nmbclusters;
E 57
E 15
E 12
E 7
D 6
struct	mbuf *mfree, *mpfree;
int	nmpfree;
char	mprefcnt[NMBPAGES];
E 6
I 6
D 50
struct	mbuf *mfree, *mclfree;
D 12
int	nmclfree;
E 12
D 7
char	mclrefcnt[NMBPAGES];
E 7
I 7
D 28
char	mclrefcnt[NMBCLUSTERS];
E 28
I 28
char	mclrefcnt[NMBCLUSTERS + 1];
E 28
I 23
int	m_want;
E 23
E 7
E 6
D 4
struct	mbuf *m_get(), *m_free(), *m_more();
E 4
I 4
D 5
struct	mbuf *m_get(), *m_getclr(), *m_free(), *m_more();
E 5
I 5
D 10
struct	mbuf *m_get(), *m_getclr(), *m_free(), *m_more(), *m_copy();
E 10
I 10
struct	mbuf *m_get(),*m_getclr(),*m_free(),*m_more(),*m_copy(),*m_pullup();
E 10
I 8
caddr_t	m_clalloc();
E 50
I 50
D 52
struct	mbuf *mfree;
E 52
union	mcluster *mclfree;
D 54
char	mclrefcnt[NMBCLUSTERS + CLBYTES/MCLBYTES];
E 54
int	max_linkhdr;			/* largest link-level header */
int	max_protohdr;			/* largest protocol header */
int	max_hdr;			/* largest link+protocol header */
int	max_datalen;			/* MHLEN - max_hdr */
I 60
extern	int mbtypes[];			/* XXX */

struct	mbuf *m_copym __P((struct mbuf *, int, int, int));
struct	mbuf *m_free __P((struct mbuf *));
E 60
D 55
struct	mbuf *m_get(), *m_gethdr(), *m_getclr(), *m_retry(), *m_retryhdr();
D 52
struct	mbuf *m_free(), *m_copy(), *m_pullup(), *m_prepend();
E 52
I 52
struct	mbuf *m_free(), *m_copym(), *m_pullup(), *m_prepend();
E 52
int	m_clalloc();
E 55
I 55
struct	mbuf *m_get __P((int, int));
D 60
struct	mbuf *m_gethdr __P((int, int));
E 60
struct	mbuf *m_getclr __P((int, int));
I 60
struct	mbuf *m_gethdr __P((int, int));
struct	mbuf *m_prepend __P((struct mbuf *, int, int));
struct	mbuf *m_pullup __P((struct mbuf *, int));
E 60
struct	mbuf *m_retry __P((int, int));
struct	mbuf *m_retryhdr __P((int, int));
I 64
void	m_adj __P((struct mbuf *, int));
E 64
D 60
struct	mbuf *m_free __P((struct mbuf *));
void	m_freem __P((struct mbuf *));
struct	mbuf *m_copym __P((struct mbuf *, int, int, int));
struct	mbuf *m_pullup __P((struct mbuf *, int));
struct	mbuf *m_prepend __P((struct mbuf *, int, int));
E 60
int	m_clalloc __P((int, int));
E 55
D 60
extern	int mbtypes[];			/* XXX */
E 60
I 60
void	m_copyback __P((struct mbuf *, int, int, caddr_t));
void	m_freem __P((struct mbuf *));
I 65
void	m_reclaim __P((void));
E 65
E 60

#ifdef MBTYPES
D 52
int mbtypes[] = {
E 52
I 52
int mbtypes[] = {				/* XXX */
E 52
D 58
	M_FREE,		/* MT_FREE	0	/* should be on free list */
	M_MBUF,		/* MT_DATA	1	/* dynamic (data) allocation */
	M_MBUF,		/* MT_HEADER	2	/* packet header */
	M_SOCKET,	/* MT_SOCKET	3	/* socket structure */
	M_PCB,		/* MT_PCB	4	/* protocol control block */
	M_RTABLE,	/* MT_RTABLE	5	/* routing tables */
	M_HTABLE,	/* MT_HTABLE	6	/* IMP host tables */
	0,		/* MT_ATABLE	7	/* address resolution tables */
	M_MBUF,		/* MT_SONAME	8	/* socket name */
E 58
I 58
	M_FREE,		/* MT_FREE	0	   should be on free list */
	M_MBUF,		/* MT_DATA	1	   dynamic (data) allocation */
	M_MBUF,		/* MT_HEADER	2	   packet header */
	M_SOCKET,	/* MT_SOCKET	3	   socket structure */
	M_PCB,		/* MT_PCB	4	   protocol control block */
	M_RTABLE,	/* MT_RTABLE	5	   routing tables */
	M_HTABLE,	/* MT_HTABLE	6	   IMP host tables */
	0,		/* MT_ATABLE	7	   address resolution tables */
	M_MBUF,		/* MT_SONAME	8	   socket name */
E 58
I 52
	0,		/* 		9 */
E 52
D 58
	M_SOOPTS,	/* MT_SOOPTS	10	/* socket options */
	M_FTABLE,	/* MT_FTABLE	11	/* fragment reassembly header */
	M_MBUF,		/* MT_RIGHTS	12	/* access rights */
	M_IFADDR,	/* MT_IFADDR	13	/* interface address */
	M_MBUF,		/* MT_CONTROL	14	/* extra-data protocol message */
	M_MBUF,		/* MT_OOBDATA	15	/* expedited data  */
E 58
I 58
	M_SOOPTS,	/* MT_SOOPTS	10	   socket options */
	M_FTABLE,	/* MT_FTABLE	11	   fragment reassembly header */
	M_MBUF,		/* MT_RIGHTS	12	   access rights */
	M_IFADDR,	/* MT_IFADDR	13	   interface address */
	M_MBUF,		/* MT_CONTROL	14	   extra-data protocol message */
	M_MBUF,		/* MT_OOBDATA	15	   expedited data  */
E 58
I 52
#ifdef DATAKIT
	25, 26, 27, 28, 29, 30, 31, 32		/* datakit ugliness */
#endif
E 52
};
#endif
E 50
E 8
E 5
E 4
E 3
E 2
#endif
D 2
	short	n_bufs;				/* # free msg buffers */
	short	n_hiwat;			/* # free mbufs allocated */
	short	n_lowat;			/* min. # free mbufs */
	short	n_pages;			/* # pages owned by network */
E 2
E 1
