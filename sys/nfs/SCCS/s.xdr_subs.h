h46635
s 00024/00019/00040
d D 8.3 95/03/30 11:26:18 mckusick 11 10
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00009/00002/00050
d D 8.2 94/12/08 22:55:08 mckusick 10 9
c avoid converting NOVAL (from karels)
e
s 00002/00002/00050
d D 8.1 93/06/10 23:40:06 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00059/00027
d D 7.7 93/05/17 14:10:27 mckusick 8 7
c update from Torek/Macklem for machines requiring quad alignment
e
s 00001/00001/00085
d D 7.6 92/09/16 18:57:32 mckusick 7 6
c fixup in BIG_ENDIAN macro
e
s 00035/00014/00051
d D 7.5 92/09/16 18:19:50 mckusick 6 5
c update from Rick Macklem
e
s 00044/00010/00021
d D 7.4 92/01/14 12:41:03 mckusick 5 4
c update from Rick Macklem (including leases)
e
s 00001/00011/00030
d D 7.3 90/06/28 21:54:25 bostic 4 3
c new copyright notice
e
s 00001/00000/00040
d D 7.2 89/12/20 12:31:10 mckusick 3 1
c "December update from Rick Macklem"
e
s 00000/00000/00040
d R 7.2 89/08/30 20:30:19 macklem 2 1
c first buffer cache implementation; name cache usage; code cleanups
e
s 00040/00000/00000
d D 7.1 89/07/05 11:32:30 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

I 11

#ifndef _NFS_XDR_SUBS_H_
#define _NFS_XDR_SUBS_H_

E 11
/*
 * Macros used for conversion to/from xdr representation by nfs...
 * These use the MACHINE DEPENDENT routines ntohl, htonl
I 3
 * As defined by "XDR: External Data Representation Standard" RFC1014
I 8
 *
 * To simplify the implementation, we use ntohl/htonl even on big-endian
 * machines, and count on them being `#define'd away.  Some of these
 * might be slightly more efficient as quad_t copies on a big-endian,
 * but we cannot count on their alignment anyway.
E 8
E 3
 */
D 5
/* From xdr to machine */
E 5
I 5
D 8
#if BYTE_ORDER == LITTLE_ENDIAN
E 5
#define fxdr_unsigned(t, v)	((t)ntohl((long)(v)))
E 8
I 8

#define	fxdr_unsigned(t, v)	((t)ntohl((long)(v)))
#define	txdr_unsigned(v)	(htonl((long)(v)))

E 8
D 5
#define	fxdr_time(f, t)		{((struct timeval *)(t))->tv_sec=ntohl( \
				((struct timeval *)(f))->tv_sec); \
				((struct timeval *)(t))->tv_usec=ntohl( \
				((struct timeval *)(f))->tv_usec);}
E 5
I 5
D 6
#define	fxdr_time(f, t)	{ \
	((struct timeval *)(t))->tv_sec = \
		ntohl(((struct timeval *)(f))->tv_sec); \
	((struct timeval *)(t))->tv_usec = \
		ntohl(((struct timeval *)(f))->tv_usec); \
E 6
I 6
D 11
#define	fxdr_nfstime(f, t) { \
I 10
	register u_long _nsec; \
E 10
D 8
	(t)->ts_sec = \
		ntohl(((struct nfsv2_time *)(f))->nfs_sec); \
	(t)->ts_nsec = 1000 * \
		ntohl(((struct nfsv2_time *)(f))->nfs_usec); \
E 8
I 8
	(t)->ts_sec = ntohl(((struct nfsv2_time *)(f))->nfs_sec); \
D 10
	(t)->ts_nsec = 1000 * ntohl(((struct nfsv2_time *)(f))->nfs_usec); \
E 10
I 10
	_nsec = ntohl(((struct nfsv2_time *)(f))->nfs_usec); \
	if (_nsec != VNOVAL) \
		_nsec *= 1000; \
	(t)->ts_nsec = _nsec; \
E 11
I 11
#define	fxdr_nfsv2time(f, t) { \
	(t)->ts_sec = ntohl(((struct nfsv2_time *)(f))->nfsv2_sec); \
	if (((struct nfsv2_time *)(f))->nfsv2_usec != 0xffffffff) \
		(t)->ts_nsec = 1000 * ntohl(((struct nfsv2_time *)(f))->nfsv2_usec); \
	else \
		(t)->ts_nsec = 0; \
E 11
E 10
E 8
E 6
}
I 8
D 11
#define	txdr_nfstime(f, t) { \
I 10
	register u_long _nsec = (f)->ts_nsec; \
E 10
	((struct nfsv2_time *)(t))->nfs_sec = htonl((f)->ts_sec); \
D 10
	((struct nfsv2_time *)(t))->nfs_usec = htonl((f)->ts_nsec) / 1000; \
E 10
I 10
	if (_nsec != VNOVAL) \
		_nsec /= 1000; \
	((struct nfsv2_time *)(t))->nfs_usec = htonl(_nsec); \
E 11
I 11
#define	txdr_nfsv2time(f, t) { \
	((struct nfsv2_time *)(t))->nfsv2_sec = htonl((f)->ts_sec); \
	if ((f)->ts_nsec != -1) \
		((struct nfsv2_time *)(t))->nfsv2_usec = htonl((f)->ts_nsec / 1000); \
	else \
		((struct nfsv2_time *)(t))->nfsv2_usec = 0xffffffff; \
E 11
E 10
}
E 8
E 5

I 6
D 11
#define	fxdr_nqtime(f, t) { \
D 8
	(t)->ts_sec = \
		ntohl(((struct nqnfs_time *)(f))->nq_sec); \
	(t)->ts_nsec = \
		ntohl(((struct nqnfs_time *)(f))->nq_nsec); \
E 8
I 8
	(t)->ts_sec = ntohl(((struct nqnfs_time *)(f))->nq_sec); \
	(t)->ts_nsec = ntohl(((struct nqnfs_time *)(f))->nq_nsec); \
E 11
I 11
#define	fxdr_nfsv3time(f, t) { \
	(t)->ts_sec = ntohl(((struct nfsv3_time *)(f))->nfsv3_sec); \
	(t)->ts_nsec = ntohl(((struct nfsv3_time *)(f))->nfsv3_nsec); \
E 11
E 8
}
I 8
D 11
#define	txdr_nqtime(f, t) { \
	((struct nqnfs_time *)(t))->nq_sec = htonl((f)->ts_sec); \
	((struct nqnfs_time *)(t))->nq_nsec = htonl((f)->ts_nsec); \
E 11
I 11
#define	txdr_nfsv3time(f, t) { \
	((struct nfsv3_time *)(t))->nfsv3_sec = htonl((f)->ts_sec); \
	((struct nfsv3_time *)(t))->nfsv3_nsec = htonl((f)->ts_nsec); \
E 11
}
E 8

E 6
D 5
/* from machine to xdr */
E 5
I 5
D 8
/*
 * To handle quad conversions, define a struct of two longs and use
 * ntohl and htonl. Maybe someday there should be ntohq and htonq?
 */
union _hq {
	quad_t	hq;
	struct {
		long val[2];
	} lq;
};
E 8
#define	fxdr_hyper(f, t) { \
D 8
	((union _hq *)(t))->lq.val[1] = ntohl(((union _hq *)(f))->lq.val[0]); \
	((union _hq *)(t))->lq.val[0] = ntohl(((union _hq *)(f))->lq.val[1]); \
E 8
I 8
	((long *)(t))[_QUAD_HIGHWORD] = ntohl(((long *)(f))[0]); \
	((long *)(t))[_QUAD_LOWWORD] = ntohl(((long *)(f))[1]); \
E 8
}
#define	txdr_hyper(f, t) { \
D 8
	((union _hq *)(t))->lq.val[0] = htonl(((union _hq *)(f))->lq.val[1]); \
	((union _hq *)(t))->lq.val[1] = htonl(((union _hq *)(f))->lq.val[0]); \
E 8
I 8
	((long *)(t))[0] = htonl(((long *)(f))[_QUAD_HIGHWORD]); \
	((long *)(t))[1] = htonl(((long *)(f))[_QUAD_LOWWORD]); \
E 8
}
I 11

#endif
E 11
D 8

E 5
#define	txdr_unsigned(v)	(htonl((long)(v)))
D 5
#define	txdr_time(f, t)		{((struct timeval *)(t))->tv_sec=htonl( \
				((struct timeval *)(f))->tv_sec); \
				((struct timeval *)(t))->tv_usec=htonl( \
				((struct timeval *)(f))->tv_usec);}
E 5
I 5
D 6
#define	txdr_time(f, t)	{ \
	((struct timeval *)(t))->tv_sec = \
		htonl(((struct timeval *)(f))->tv_sec); \
	((struct timeval *)(t))->tv_usec = \
		htonl(((struct timeval *)(f))->tv_usec); \
E 6
I 6
#define	txdr_nqtime(f, t) { \
	((struct nqnfs_time *)(t))->nq_sec = \
		htonl((f)->ts_sec); \
	((struct nqnfs_time *)(t))->nq_nsec = \
		htonl((f)->ts_nsec); \
E 6
}
I 6
#define	txdr_nfstime(f, t) { \
	((struct nfsv2_time *)(t))->nfs_sec = \
		htonl((f)->ts_sec); \
	((struct nfsv2_time *)(t))->nfs_usec = \
		htonl((f)->ts_nsec) / 1000; \
}
E 6
#else	/* BIG_ENDIAN */
#define fxdr_unsigned(t, v)	((t)(v))
D 6
#define	fxdr_time(f, t) \
	*((struct timeval *)(t)) = *((struct timeval *)(f))
E 6
I 6
#define	fxdr_nqtime(f, t) \
	*(t) = *((struct timespec *)(f))
#define	fxdr_nfstime(f, t) { \
	(t)->ts_sec = ((struct nfsv2_time *)(f))->nfs_sec; \
	(t)->ts_nsec = ((struct nfsv2_time *)(f))->nfs_usec * 1000; \
}
E 6
#define	fxdr_hyper(f, t) \
	*((quad_t *)(t)) = *((quad_t *)(f))
E 5

I 5
#define	txdr_unsigned(v)	((long)(v))
D 6
#define	txdr_time(f, t) \
	*((struct timeval *)(t)) = *((struct timeval *)(f))
E 6
I 6
#define	txdr_nqtime(f, t) \
D 7
	*(t) = *((struct timespec *)(f))
E 7
I 7
	*(t) = *((struct nqnfs_time *)(f))
E 7
#define	txdr_nfstime(f, t) { \
	((struct nfsv2_time *)(t))->nfs_sec = (f)->ts_sec; \
	((struct nfsv2_time *)(t))->nfs_usec = (f)->ts_nsec / 1000; \
}
E 6
#define	txdr_hyper(f, t) \
	*((quad_t *)(t)) = *((quad_t *)(f))
#endif	/* ENDIAN */
E 8
E 5
E 1
