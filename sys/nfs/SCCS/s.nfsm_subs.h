h00789
s 00241/00071/00172
d D 8.2 95/03/30 11:26:21 mckusick 21 20
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00002/00002/00241
d D 8.1 93/06/16 17:33:37 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00242
d D 7.17 93/06/16 17:33:18 mckusick 19 18
c missed one change of nfsm_dissecton => nfsm_dissect
e
s 00001/00013/00242
d D 7.16 93/06/16 17:14:44 mckusick 18 16
c fix for trashed TCP/IP connections from Macklem
e
s 00002/00002/00253
d R 8.1 93/06/10 23:39:38 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00254
d D 7.15 93/03/30 15:30:45 mckusick 16 15
c eliminate flags and generation number in times hack
e
s 00032/00014/00224
d D 7.14 92/09/16 17:58:11 mckusick 15 14
c update from Rick Macklem
e
s 00002/00002/00236
d D 7.13 92/06/19 19:25:00 mckusick 14 13
c timeval => timespec in vattr and dinode
e
s 00031/00068/00207
d D 7.12 92/01/14 12:41:07 mckusick 13 12
c update from Rick Macklem (including leases)
e
s 00011/00011/00264
d D 7.11 91/04/16 00:27:22 mckusick 12 11
c u_long p is replaced by u_long tl (so that p can be used for proc pointer)
e
s 00001/00011/00274
d D 7.10 90/06/28 21:53:43 bostic 11 10
c new copyright notice
e
s 00002/00002/00283
d D 7.9 90/06/21 11:14:33 mckusick 10 9
c "update from Rick Macklem"
e
s 00005/00002/00280
d D 7.8 90/05/18 14:48:55 mckusick 9 8
c "nfs_mknod update from Rick Macklem"
e
s 00003/00040/00279
d D 7.7 90/05/14 11:34:38 mckusick 8 7
c "update from Rick Macklem adding TCP support to NFS"
e
s 00002/00002/00317
d D 7.6 90/02/16 15:38:54 mckusick 7 6
c pass indication of idempotency to nfsm_request
e
s 00036/00001/00283
d D 7.5 89/12/20 12:00:40 mckusick 6 5
c "December update from Rick Macklem"
e
s 00021/00032/00263
d D 7.4 89/11/03 15:30:34 mckusick 5 4
c lint
e
s 00001/00001/00294
d D 7.3 89/10/31 16:01:44 mckusick 4 2
c must pass reference to vnode pointer to nfs_loadattrcache so it can be updated
e
s 00000/00000/00295
d R 7.3 89/08/30 20:30:12 macklem 3 2
c first buffer cache implementation; name cache usage; code cleanups
e
s 00001/00001/00294
d D 7.2 89/07/06 17:42:37 mckusick 2 1
c update of July 5th from Rick Macklem
e
s 00295/00000/00000
d D 7.1 89/07/05 11:32:27 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 20
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
 *
 *	%W% (Berkeley) %G%
 */

I 21

#ifndef _NFS_NFSM_SUBS_H_
#define _NFS_NFSM_SUBS_H_


E 21
/*
 * These macros do strange and peculiar things to mbuf chains for
 * the assistance of the nfs code. To attempt to use them for any
 * other purpose will be dangerous. (they make weird assumptions)
 */

/*
 * First define what the actual subs. return
 */
D 5
struct mbuf *nfsm_reqh();
struct vnode *nfs_fhtovp();
E 5
I 5
extern struct mbuf *nfsm_reqh();
D 8
extern struct vnode *nfs_fhtovp();
E 8
E 5

D 8
/*
 * To try and deal with different variants of mbuf.h, I have used the
 * following defs. If M_HASCL is not defined in an older the 4.4bsd mbuf.h,
 * you will have to use a different ifdef
 */
#ifdef M_HASCL
#define	NFSMCLGET(m, w)	MCLGET(m)
#define	NFSMGETHDR(m)	MGET(m, M_WAIT, MT_DATA)
#define	MHLEN		MLEN
#define	NFSMINOFF(m) \
		if (M_HASCL(m)) \
			(m)->m_off = ((int)MTOCL(m))-(int)(m); \
		else \
			(m)->m_off = MMINOFF
#define	NFSMADV(m, s)	(m)->m_off += (s)
#define	NFSMSIZ(m)	((M_HASCL(m))?MCLBYTES:MLEN)
#define	m_nextpkt	m_act
#define	NFSMCOPY(m, o, l, w)	m_copy((m), (o), (l))
#else
E 8
#define	M_HASCL(m)	((m)->m_flags & M_EXT)
D 8
#define	NFSMCLGET	MCLGET
E 8
D 13
#define	NFSMGETHDR(m) \
		MGETHDR(m, M_WAIT, MT_DATA); \
		(m)->m_pkthdr.len = 0; \
		(m)->m_pkthdr.rcvif = (struct ifnet *)0
E 13
#define	NFSMINOFF(m) \
		if (M_HASCL(m)) \
			(m)->m_data = (m)->m_ext.ext_buf; \
I 13
		else if ((m)->m_flags & M_PKTHDR) \
			(m)->m_data = (m)->m_pktdat; \
E 13
		else \
			(m)->m_data = (m)->m_dat
#define	NFSMADV(m, s)	(m)->m_data += (s)
D 2
#define	NFSMSIZ(m)	((M_HASCL(m))?(MCLBYTES-max_hdr): \
E 2
I 2
#define	NFSMSIZ(m)	((M_HASCL(m))?MCLBYTES: \
E 2
				(((m)->m_flags & M_PKTHDR)?MHLEN:MLEN))
D 8
#define	NFSMCOPY	m_copym
#endif
E 8

D 8
#ifndef MCLBYTES
#define	MCLBYTES	CLBYTES
#endif

#ifndef MT_CONTROL
#define	MT_CONTROL	MT_RIGHTS
#endif

E 8
/*
 * Now for the macros that do the simple stuff and call the functions
 * for the hard stuff.
 * These macros use several vars. declared in nfsm_reqhead and these
 * vars. must not be used elsewhere unless you are careful not to corrupt
 * them. The vars. starting with pN and tN (N=1,2,3,..) are temporaries
 * that may be used so long as the value is not expected to retained
 * after a macro.
 * I know, this is kind of dorkey, but it makes the actual op functions
 * fairly clean and deals with the mess caused by the xdr discriminating
 * unions.
 */

I 5
D 13
#ifndef lint
E 13
E 5
#define	nfsm_build(a,c,s) \
D 13
		t1 = NFSMSIZ(mb); \
		if ((s) > (t1-mb->m_len)) { \
E 13
I 13
		{ if ((s) > M_TRAILINGSPACE(mb)) { \
E 13
			MGET(mb2, M_WAIT, MT_DATA); \
			if ((s) > MLEN) \
				panic("build > MLEN"); \
			mb->m_next = mb2; \
			mb = mb2; \
			mb->m_len = 0; \
			bpos = mtod(mb, caddr_t); \
		} \
		(a) = (c)(bpos); \
		mb->m_len += (s); \
D 13
		bpos += (s)
I 5
#else /* lint */
#define	nfsm_build(a,c,s) \
		t1 = NFSMSIZ(mb); \
		if ((s) > (t1-mb->m_len)) { \
			MGET(mb2, M_WAIT, MT_DATA); \
			mb->m_next = mb2; \
			mb = mb2; \
			mb->m_len = 0; \
			bpos = mtod(mb, caddr_t); \
		} \
		(a) = (c)(bpos); \
		mb->m_len += (s); \
		bpos += (s)
#endif /* lint */
E 13
I 13
		bpos += (s); }
E 13
E 5

D 13
#define	nfsm_disect(a,c,s) \
		t1 = mtod(md, caddr_t)+md->m_len-dpos; \
E 13
I 13
D 21
#define	nfsm_dissect(a,c,s) \
E 21
I 21
#define	nfsm_dissect(a, c, s) \
E 21
		{ t1 = mtod(md, caddr_t)+md->m_len-dpos; \
E 13
		if (t1 >= (s)) { \
			(a) = (c)(dpos); \
			dpos += (s); \
D 18
		} else if (error = nfsm_disct(&md, &dpos, (s), t1, TRUE, &cp2)) { \
			m_freem(mrep); \
			goto nfsmout; \
		} else { \
			(a) = (c)cp2; \
D 13
		}
E 13
I 13
		} }
E 13

D 13
#define	nfsm_disecton(a,c,s) \
		t1 = mtod(md, caddr_t)+md->m_len-dpos; \
E 13
I 13
#define	nfsm_dissecton(a,c,s) \
		{ t1 = mtod(md, caddr_t)+md->m_len-dpos; \
E 13
		if (t1 >= (s)) { \
			(a) = (c)(dpos); \
			dpos += (s); \
		} else if (error = nfsm_disct(&md, &dpos, (s), t1, FALSE, &cp2)) { \
E 18
I 18
D 21
		} else if (error = nfsm_disct(&md, &dpos, (s), t1, &cp2)) { \
E 21
I 21
		} else if (t1 = nfsm_disct(&md, &dpos, (s), t1, &cp2)) { \
			error = t1; \
E 21
E 18
			m_freem(mrep); \
			goto nfsmout; \
		} else { \
			(a) = (c)cp2; \
D 13
		}
E 13
I 13
		} }
E 13

D 21
#define nfsm_fhtom(v) \
		nfsm_build(cp,caddr_t,NFSX_FH); \
		bcopy((caddr_t)&(VTONFS(v)->n_fh), cp, NFSX_FH)
E 21
I 21
#define nfsm_fhtom(v, v3) \
	      { if (v3) { \
			t2 = nfsm_rndup(VTONFS(v)->n_fhsize) + NFSX_UNSIGNED; \
			if (t2 <= M_TRAILINGSPACE(mb)) { \
				nfsm_build(tl, u_long *, t2); \
				*tl++ = txdr_unsigned(VTONFS(v)->n_fhsize); \
				*(tl + ((t2>>2) - 2)) = 0; \
				bcopy((caddr_t)VTONFS(v)->n_fhp,(caddr_t)tl, \
					VTONFS(v)->n_fhsize); \
			} else if (t2 = nfsm_strtmbuf(&mb, &bpos, \
				(caddr_t)VTONFS(v)->n_fhp, VTONFS(v)->n_fhsize)) { \
				error = t2; \
				m_freem(mreq); \
				goto nfsmout; \
			} \
		} else { \
			nfsm_build(cp, caddr_t, NFSX_V2FH); \
			bcopy((caddr_t)VTONFS(v)->n_fhp, cp, NFSX_V2FH); \
		} }
E 21

D 21
#define nfsm_srvfhtom(f) \
		nfsm_build(cp,caddr_t,NFSX_FH); \
		bcopy((caddr_t)(f), cp, NFSX_FH)
E 21
I 21
#define nfsm_srvfhtom(f, v3) \
		{ if (v3) { \
			nfsm_build(tl, u_long *, NFSX_UNSIGNED + NFSX_V3FH); \
			*tl++ = txdr_unsigned(NFSX_V3FH); \
			bcopy((caddr_t)(f), (caddr_t)tl, NFSX_V3FH); \
		} else { \
			nfsm_build(cp, caddr_t, NFSX_V2FH); \
			bcopy((caddr_t)(f), cp, NFSX_V2FH); \
		} }
E 21

D 21
#define nfsm_mtofh(d,v) \
		{ struct nfsnode *np; nfsv2fh_t *fhp; \
D 13
		nfsm_disect(fhp,nfsv2fh_t *,NFSX_FH); \
E 13
I 13
		nfsm_dissect(fhp,nfsv2fh_t *,NFSX_FH); \
E 13
		if (error = nfs_nget((d)->v_mount, fhp, &np)) { \
			m_freem(mrep); \
			goto nfsmout; \
E 21
I 21
#define nfsm_srvpostop_fh(f) \
		{ nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED + NFSX_V3FH); \
		*tl++ = nfs_true; \
		*tl++ = txdr_unsigned(NFSX_V3FH); \
		bcopy((caddr_t)(f), (caddr_t)tl, NFSX_V3FH); \
		}

#define nfsm_mtofh(d, v, v3, f) \
		{ struct nfsnode *ttnp; nfsfh_t *ttfhp; int ttfhsize; \
		if (v3) { \
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
			(f) = fxdr_unsigned(int, *tl); \
		} else \
			(f) = 1; \
		if (f) { \
			nfsm_getfh(ttfhp, ttfhsize, (v3)); \
			if (t1 = nfs_nget((d)->v_mount, ttfhp, ttfhsize, \
				&ttnp)) { \
				error = t1; \
				m_freem(mrep); \
				goto nfsmout; \
			} \
			(v) = NFSTOV(ttnp); \
E 21
		} \
D 21
		(v) = NFSTOV(np); \
		nfsm_loadattr(v, (struct vattr *)0); \
E 21
I 21
		if (v3) { \
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
			if (f) \
				(f) = fxdr_unsigned(int, *tl); \
			else if (fxdr_unsigned(int, *tl)) \
				nfsm_adv(NFSX_V3FATTR); \
		} \
		if (f) \
			nfsm_loadattr((v), (struct vattr *)0); \
E 21
D 6
		(v)->v_type = np->n_vattr.va_type; \
E 6
		}

D 21
#define	nfsm_loadattr(v,a) \
D 4
		if (error = nfs_loadattrcache((v), &md, &dpos, (a))) { \
E 4
I 4
D 5
		if (error = nfs_loadattrcache(&(v), &md, &dpos, (a))) { \
E 5
I 5
		{ struct vnode *tvp = (v); \
		if (error = nfs_loadattrcache(&tvp, &md, &dpos, (a))) { \
E 21
I 21
#define nfsm_getfh(f, s, v3) \
		{ if (v3) { \
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
			if (((s) = fxdr_unsigned(int, *tl)) <= 0 || \
				(s) > NFSX_V3FHMAX) { \
				m_freem(mrep); \
				error = EBADRPC; \
				goto nfsmout; \
			} \
		} else \
			(s) = NFSX_V2FH; \
		nfsm_dissect((f), nfsfh_t *, nfsm_rndup(s)); }

#define	nfsm_loadattr(v, a) \
		{ struct vnode *ttvp = (v); \
		if (t1 = nfs_loadattrcache(&ttvp, &md, &dpos, (a))) { \
			error = t1; \
E 21
E 5
E 4
			m_freem(mrep); \
			goto nfsmout; \
D 5
		}
E 5
I 5
		} \
D 21
		(v) = tvp; }
E 21
I 21
		(v) = ttvp; }
E 21
E 5

I 21
#define	nfsm_postop_attr(v, f) \
		{ struct vnode *ttvp = (v); \
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		if ((f) = fxdr_unsigned(int, *tl)) { \
			if (t1 = nfs_loadattrcache(&ttvp, &md, &dpos, \
				(struct vattr *)0)) { \
				error = t1; \
				(f) = 0; \
				m_freem(mrep); \
				goto nfsmout; \
			} \
			(v) = ttvp; \
		} }

/* Used as (f) for nfsm_wcc_data() */
#define NFSV3_WCCRATTR	0
#define NFSV3_WCCCHK	1

#define	nfsm_wcc_data(v, f) \
		{ int ttattrf, ttretf = 0; \
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		if (*tl == nfs_true) { \
			nfsm_dissect(tl, u_long *, 6 * NFSX_UNSIGNED); \
			if (f) \
				ttretf = (VTONFS(v)->n_mtime == \
					fxdr_unsigned(u_long, *(tl + 2))); \
		} \
		nfsm_postop_attr((v), ttattrf); \
		if (f) { \
			(f) = ttretf; \
		} else { \
			(f) = ttattrf; \
		} }

#define nfsm_v3sattr(s, a, u, g) \
		{ (s)->sa_modetrue = nfs_true; \
		(s)->sa_mode = vtonfsv3_mode((a)->va_mode); \
		(s)->sa_uidtrue = nfs_true; \
		(s)->sa_uid = txdr_unsigned(u); \
		(s)->sa_gidtrue = nfs_true; \
		(s)->sa_gid = txdr_unsigned(g); \
		(s)->sa_sizefalse = nfs_false; \
		(s)->sa_atimetype = txdr_unsigned(NFSV3SATTRTIME_TOCLIENT); \
		txdr_nfsv3time(&(a)->va_atime, &(s)->sa_atime); \
		(s)->sa_mtimetype = txdr_unsigned(NFSV3SATTRTIME_TOCLIENT); \
		txdr_nfsv3time(&(a)->va_mtime, &(s)->sa_mtime); \
		}

E 21
#define	nfsm_strsiz(s,m) \
D 12
		nfsm_disect(p,u_long *,NFSX_UNSIGNED); \
		if (((s) = fxdr_unsigned(long,*p)) > (m)) { \
E 12
I 12
D 13
		nfsm_disect(tl,u_long *,NFSX_UNSIGNED); \
E 13
I 13
		{ nfsm_dissect(tl,u_long *,NFSX_UNSIGNED); \
E 13
		if (((s) = fxdr_unsigned(long,*tl)) > (m)) { \
E 12
			m_freem(mrep); \
			error = EBADRPC; \
			goto nfsmout; \
D 13
		}
E 13
I 13
		} }
E 13

#define	nfsm_srvstrsiz(s,m) \
D 12
		nfsm_disect(p,u_long *,NFSX_UNSIGNED); \
		if (((s) = fxdr_unsigned(long,*p)) > (m) || (s) <= 0) { \
E 12
I 12
D 13
		nfsm_disect(tl,u_long *,NFSX_UNSIGNED); \
E 13
I 13
		{ nfsm_dissect(tl,u_long *,NFSX_UNSIGNED); \
E 13
		if (((s) = fxdr_unsigned(long,*tl)) > (m) || (s) <= 0) { \
E 12
			error = EBADRPC; \
			nfsm_reply(0); \
D 13
		}
E 13
I 13
		} }
E 13

I 21
#define	nfsm_srvnamesiz(s) \
		{ nfsm_dissect(tl,u_long *,NFSX_UNSIGNED); \
		if (((s) = fxdr_unsigned(long,*tl)) > NFS_MAXNAMLEN) \
			error = NFSERR_NAMETOL; \
		if ((s) <= 0) \
			error = EBADRPC; \
		if (error) \
			nfsm_reply(0); \
		}

E 21
D 5
#define	nfsm_srvstrsizon(s,m) \
		nfsm_disecton(p,u_long *,NFSX_UNSIGNED); \
		if (((s) = fxdr_unsigned(long,*p)) > (m)) { \
			error = EBADRPC; \
			nfsm_reply(0); \
		}

E 5
#define nfsm_mtouio(p,s) \
		if ((s) > 0 && \
D 21
		   (error = nfsm_mbuftouio(&md,(p),(s),&dpos))) { \
E 21
I 21
		   (t1 = nfsm_mbuftouio(&md,(p),(s),&dpos))) { \
			error = t1; \
E 21
			m_freem(mrep); \
			goto nfsmout; \
		}

#define nfsm_uiotom(p,s) \
D 21
		if (error = nfsm_uiotombuf((p),&mb,(s),&bpos)) { \
E 21
I 21
		if (t1 = nfsm_uiotombuf((p),&mb,(s),&bpos)) { \
			error = t1; \
E 21
			m_freem(mreq); \
			goto nfsmout; \
		}

D 13
#define	nfsm_reqhead(a,c,s) \
		if ((mreq = nfsm_reqh(nfs_prog,nfs_vers,(a),(c),(s),&bpos,&mb,&xid)) == NULL) { \
			error = ENOBUFS; \
			goto nfsmout; \
		}
E 13
I 13
#define	nfsm_reqhead(v,a,s) \
		mb = mreq = nfsm_reqh((v),(a),(s),&bpos)
E 13

D 5
#define	nfsm_vars \
		register u_long *p; \
		register caddr_t cp; \
		register long t1, t2; \
		caddr_t bpos, dpos, cp2; \
		u_long xid; \
		int error = 0; \
		long offs = 0; \
		struct mbuf *mreq, *mrep, *md, *mb, *mb2

E 5
#define nfsm_reqdone	m_freem(mrep); \
		nfsmout: 

#define nfsm_rndup(a)	(((a)+3)&(~0x3))

D 7
#define	nfsm_request(v)	\
		if (error = nfs_request((v), mreq, xid, \
E 7
I 7
D 8
#define	nfsm_request(v, t)	\
		if (error = nfs_request((v), mreq, xid, 5*(t), \
E 8
I 8
D 10
#define	nfsm_request(v, t, p)	\
		if (error = nfs_request((v), mreq, xid, (t), (p), \
E 10
I 10
D 13
#define	nfsm_request(v, t, p, h)	\
		if (error = nfs_request((v), mreq, xid, (t), (p), (h), \
E 10
E 8
E 7
		   (v)->v_mount, &mrep, &md, &dpos)) \
E 13
I 13
#define	nfsm_request(v, t, p, c)	\
		if (error = nfs_request((v), mreq, (t), (p), \
D 21
		   (c), &mrep, &md, &dpos)) \
E 13
			goto nfsmout
E 21
I 21
		   (c), &mrep, &md, &dpos)) { \
			if (error & NFSERR_RETERR) \
				error &= ~NFSERR_RETERR; \
			else \
				goto nfsmout; \
		}
E 21

#define	nfsm_strtom(a,s,m) \
		if ((s) > (m)) { \
			m_freem(mreq); \
			error = ENAMETOOLONG; \
			goto nfsmout; \
		} \
		t2 = nfsm_rndup(s)+NFSX_UNSIGNED; \
D 13
		if(t2<=(NFSMSIZ(mb)-mb->m_len)){ \
E 13
I 13
		if (t2 <= M_TRAILINGSPACE(mb)) { \
E 13
D 12
			nfsm_build(p,u_long *,t2); \
			*p++ = txdr_unsigned(s); \
			*(p+((t2>>2)-2)) = 0; \
			bcopy((caddr_t)(a), (caddr_t)p, (s)); \
E 12
I 12
			nfsm_build(tl,u_long *,t2); \
			*tl++ = txdr_unsigned(s); \
			*(tl+((t2>>2)-2)) = 0; \
			bcopy((caddr_t)(a), (caddr_t)tl, (s)); \
E 12
D 21
		} else if (error = nfsm_strtmbuf(&mb, &bpos, (a), (s))) { \
E 21
I 21
		} else if (t2 = nfsm_strtmbuf(&mb, &bpos, (a), (s))) { \
			error = t2; \
E 21
			m_freem(mreq); \
			goto nfsmout; \
		}

D 8
#define	nfsm_srverr \
		{ \
			m_freem(mrep); \
			return(ENOBUFS); \
		}

E 8
D 5
#define	nfsm_srvars \
		register caddr_t cp; \
		register u_long *p; \
		register long t1, t2; \
		caddr_t bpos; \
		long offs = 0; \
		int error = 0; \
		char *cp2; \
		struct mbuf *mb, *mb2, *mreq

E 5
#define	nfsm_srvdone \
		nfsmout: \
		return(error)

I 6
D 13
#ifndef lint
E 13
E 6
#define	nfsm_reply(s) \
		{ \
I 6
D 13
		*repstat = error; \
E 13
I 13
		nfsd->nd_repstat = error; \
E 13
E 6
D 21
		if (error) \
D 13
			nfs_rephead(0, xid, error, mrq, &mb, &bpos); \
E 13
I 13
		   (void) nfs_rephead(0, nfsd, error, cache, &frev, \
E 21
I 21
		if (error && !(nfsd->nd_flag & ND_NFSV3)) \
		   (void) nfs_rephead(0, nfsd, slp, error, cache, &frev, \
E 21
			mrq, &mb, &bpos); \
E 13
		else \
D 13
			nfs_rephead((s), xid, error, mrq, &mb, &bpos); \
E 13
I 13
D 21
		   (void) nfs_rephead((s), nfsd, error, cache, &frev, \
E 21
I 21
		   (void) nfs_rephead((s), nfsd, slp, error, cache, &frev, \
E 21
			mrq, &mb, &bpos); \
E 13
		m_freem(mrep); \
I 6
		mreq = *mrq; \
E 6
D 5
		mreq = *mrq; \
E 5
D 21
		if (error) \
E 21
I 21
		if (error && (!(nfsd->nd_flag & ND_NFSV3) || \
			error == EBADRPC)) \
E 21
			return(0); \
		}
I 6
D 13
#else	/* lint */
#define	nfsm_reply(s) \
		{ \
		*repstat = error; \
		if (error) \
			nfs_rephead(0, xid, error, mrq, &mb, &bpos); \
		else \
			nfs_rephead((s), xid, error, mrq, &mb, &bpos); \
		m_freem(mrep); \
		mreq = *mrq; \
		mrep = mreq; \
		if (error) \
			return(0); \
		}
#endif	/* lint */
E 13
E 6

I 21
#define	nfsm_writereply(s, v3) \
		{ \
		nfsd->nd_repstat = error; \
		if (error && !(v3)) \
		   (void) nfs_rephead(0, nfsd, slp, error, cache, &frev, \
			&mreq, &mb, &bpos); \
		else \
		   (void) nfs_rephead((s), nfsd, slp, error, cache, &frev, \
			&mreq, &mb, &bpos); \
		}

E 21
#define	nfsm_adv(s) \
D 21
		t1 = mtod(md, caddr_t)+md->m_len-dpos; \
E 21
I 21
		{ t1 = mtod(md, caddr_t)+md->m_len-dpos; \
E 21
		if (t1 >= (s)) { \
			dpos += (s); \
D 21
		} else if (error = nfs_adv(&md, &dpos, (s), t1)) { \
E 21
I 21
		} else if (t1 = nfs_adv(&md, &dpos, (s), t1)) { \
			error = t1; \
E 21
			m_freem(mrep); \
			goto nfsmout; \
D 21
		}
E 21
I 21
		} }
E 21

#define nfsm_srvmtofh(f) \
D 12
		nfsm_disecton(p, u_long *, NFSX_FH); \
		bcopy((caddr_t)p, (caddr_t)f, NFSX_FH)
E 12
I 12
D 13
		nfsm_disecton(tl, u_long *, NFSX_FH); \
E 13
I 13
D 19
		nfsm_dissecton(tl, u_long *, NFSX_FH); \
E 19
I 19
D 21
		nfsm_dissect(tl, u_long *, NFSX_FH); \
E 19
E 13
		bcopy((caddr_t)tl, (caddr_t)f, NFSX_FH)
E 21
I 21
		{ if (nfsd->nd_flag & ND_NFSV3) { \
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
			if (fxdr_unsigned(int, *tl) != NFSX_V3FH) { \
				error = EBADRPC; \
				nfsm_reply(0); \
			} \
		} \
		nfsm_dissect(tl, u_long *, NFSX_V3FH); \
		bcopy((caddr_t)tl, (caddr_t)(f), NFSX_V3FH); \
		if ((nfsd->nd_flag & ND_NFSV3) == 0) \
			nfsm_adv(NFSX_V2FH - NFSX_V3FH); \
		}
E 21
E 12

#define	nfsm_clget \
		if (bp >= be) { \
I 13
			if (mp == mb) \
				mp->m_len += bp-bpos; \
E 13
			MGET(mp, M_WAIT, MT_DATA); \
D 8
			NFSMCLGET(mp, M_WAIT); \
E 8
I 8
			MCLGET(mp, M_WAIT); \
E 8
			mp->m_len = NFSMSIZ(mp); \
D 13
			if (mp3 == NULL) \
				mp3 = mp2 = mp; \
			else { \
				mp2->m_next = mp; \
				mp2 = mp; \
			} \
E 13
I 13
			mp2->m_next = mp; \
			mp2 = mp; \
E 13
			bp = mtod(mp, caddr_t); \
			be = bp+mp->m_len; \
		} \
D 12
		p = (u_long *)bp
E 12
I 12
		tl = (u_long *)bp
E 12
I 6

D 21
#define	nfsm_srvfillattr \
	fp->fa_type = vtonfs_type(vap->va_type); \
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode); \
	fp->fa_nlink = txdr_unsigned(vap->va_nlink); \
	fp->fa_uid = txdr_unsigned(vap->va_uid); \
	fp->fa_gid = txdr_unsigned(vap->va_gid); \
D 15
	fp->fa_size = txdr_unsigned(vap->va_size); \
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize); \
D 9
	fp->fa_rdev = txdr_unsigned(vap->va_rdev); \
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize); \
E 9
I 9
	if (vap->va_type == VFIFO) \
		fp->fa_rdev = 0xffffffff; \
	else \
		fp->fa_rdev = txdr_unsigned(vap->va_rdev); \
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / NFS_FABLKSIZE); \
E 9
	fp->fa_fsid = txdr_unsigned(vap->va_fsid); \
	fp->fa_fileid = txdr_unsigned(vap->va_fileid); \
D 14
	fp->fa_atime.tv_sec = txdr_unsigned(vap->va_atime.tv_sec); \
E 14
I 14
	fp->fa_atime.tv_sec = txdr_unsigned(vap->va_atime.ts_sec); \
E 14
	fp->fa_atime.tv_usec = txdr_unsigned(vap->va_flags); \
	txdr_time(&vap->va_mtime, &fp->fa_mtime); \
D 14
	fp->fa_ctime.tv_sec = txdr_unsigned(vap->va_ctime.tv_sec); \
E 14
I 14
	fp->fa_ctime.tv_sec = txdr_unsigned(vap->va_ctime.ts_sec); \
E 14
	fp->fa_ctime.tv_usec = txdr_unsigned(vap->va_gen)
E 15
I 15
	if (nfsd->nd_nqlflag == NQL_NOVAL) { \
		fp->fa_nfsblocksize = txdr_unsigned(vap->va_blocksize); \
		if (vap->va_type == VFIFO) \
			fp->fa_nfsrdev = 0xffffffff; \
		else \
			fp->fa_nfsrdev = txdr_unsigned(vap->va_rdev); \
		fp->fa_nfsfsid = txdr_unsigned(vap->va_fsid); \
		fp->fa_nfsfileid = txdr_unsigned(vap->va_fileid); \
		fp->fa_nfssize = txdr_unsigned(vap->va_size); \
		fp->fa_nfsblocks = txdr_unsigned(vap->va_bytes / NFS_FABLKSIZE); \
D 16
		fp->fa_nfsatime.nfs_sec = txdr_unsigned(vap->va_atime.ts_sec); \
		fp->fa_nfsatime.nfs_usec = txdr_unsigned(vap->va_flags); \
E 16
I 16
		txdr_nfstime(&vap->va_atime, &fp->fa_nfsatime); \
E 16
		txdr_nfstime(&vap->va_mtime, &fp->fa_nfsmtime); \
		fp->fa_nfsctime.nfs_sec = txdr_unsigned(vap->va_ctime.ts_sec); \
		fp->fa_nfsctime.nfs_usec = txdr_unsigned(vap->va_gen); \
	} else { \
		fp->fa_nqblocksize = txdr_unsigned(vap->va_blocksize); \
		if (vap->va_type == VFIFO) \
			fp->fa_nqrdev = 0xffffffff; \
		else \
			fp->fa_nqrdev = txdr_unsigned(vap->va_rdev); \
		fp->fa_nqfsid = txdr_unsigned(vap->va_fsid); \
		fp->fa_nqfileid = txdr_unsigned(vap->va_fileid); \
		txdr_hyper(&vap->va_size, &fp->fa_nqsize); \
		txdr_hyper(&vap->va_bytes, &fp->fa_nqbytes); \
		txdr_nqtime(&vap->va_atime, &fp->fa_nqatime); \
		txdr_nqtime(&vap->va_mtime, &fp->fa_nqmtime); \
		txdr_nqtime(&vap->va_ctime, &fp->fa_nqctime); \
		fp->fa_nqflags = txdr_unsigned(vap->va_flags); \
		fp->fa_nqgen = txdr_unsigned(vap->va_gen); \
		txdr_hyper(&vap->va_filerev, &fp->fa_nqfilerev); \
	}
E 21
I 21
#define	nfsm_srvfillattr(a, f) \
		nfsm_srvfattr(nfsd, (a), (f))
E 21
E 15
E 6

I 21
#define nfsm_srvwcc_data(br, b, ar, a) \
		nfsm_srvwcc(nfsd, (br), (b), (ar), (a), &mb, &bpos)

#define nfsm_srvpostop_attr(r, a) \
		nfsm_srvpostopattr(nfsd, (r), (a), &mb, &bpos)

#define nfsm_srvsattr(a) \
		{ nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		if (*tl == nfs_true) { \
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
			(a)->va_mode = nfstov_mode(*tl); \
		} \
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		if (*tl == nfs_true) { \
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
			(a)->va_uid = fxdr_unsigned(uid_t, *tl); \
		} \
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		if (*tl == nfs_true) { \
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
			(a)->va_gid = fxdr_unsigned(gid_t, *tl); \
		} \
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		if (*tl == nfs_true) { \
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED); \
			fxdr_hyper(tl, &(a)->va_size); \
		} \
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		switch (fxdr_unsigned(int, *tl)) { \
		case NFSV3SATTRTIME_TOCLIENT: \
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED); \
			fxdr_nfsv3time(tl, &(a)->va_atime); \
			break; \
		case NFSV3SATTRTIME_TOSERVER: \
			(a)->va_atime.ts_sec = time.tv_sec; \
			(a)->va_atime.ts_nsec = time.tv_usec * 1000; \
			break; \
		}; \
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED); \
		switch (fxdr_unsigned(int, *tl)) { \
		case NFSV3SATTRTIME_TOCLIENT: \
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED); \
			fxdr_nfsv3time(tl, &(a)->va_mtime); \
			break; \
		case NFSV3SATTRTIME_TOSERVER: \
			(a)->va_mtime.ts_sec = time.tv_sec; \
			(a)->va_mtime.ts_nsec = time.tv_usec * 1000; \
			break; \
		}; }

#endif
E 21
E 1
