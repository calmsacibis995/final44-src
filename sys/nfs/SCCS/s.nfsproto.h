h02082
s 00335/00154/00080
d D 8.2 95/03/30 11:27:00 mckusick 14 13
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00002/00002/00232
d D 8.1 93/06/10 23:39:56 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00232
d D 7.11 92/09/30 16:07:54 mckusick 12 11
c September update from Rick Macklem to add accept protocol to NQMFS
e
s 00109/00017/00124
d D 7.10 92/09/16 18:05:52 mckusick 11 9
c update from Rick Macklem
e
s 00012/00000/00141
d R 7.10 92/02/06 17:33:25 mckusick 10 9
c add RPC format of directories
e
s 00012/00004/00129
d D 7.9 92/01/14 12:41:04 mckusick 9 8
c update from Rick Macklem (including leases)
e
s 00001/00011/00132
d D 7.8 90/06/28 21:54:12 bostic 8 7
c new copyright notice
e
s 00002/00001/00141
d D 7.7 90/06/21 11:14:50 mckusick 7 6
c "update from Rick Macklem"
e
s 00005/00002/00137
d D 7.6 90/05/18 14:49:43 mckusick 6 5
c "nfs_mknod update from Rick Macklem"
e
s 00002/00000/00137
d D 7.5 90/05/14 11:35:20 mckusick 5 4
c "update from Rick Macklem adding TCP support to NFS"
e
s 00002/00001/00135
d D 7.4 90/02/17 14:46:54 mckusick 4 3
c get rid of dependencies on ../ufs/inode.h
e
s 00001/00002/00135
d D 7.3 89/12/20 12:30:45 mckusick 3 2
c "December update from Rick Macklem"
e
s 00040/00000/00097
d D 7.2 89/08/30 20:30:16 macklem 2 1
c first buffer cache implementation; name cache usage; code cleanups
e
s 00097/00000/00000
d D 7.1 89/07/05 11:32:29 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */

I 14
#ifndef _NFS_NFSPROTO_H_
#define _NFS_NFSPROTO_H_


E 14
/*
D 14
 * nfs definitions as per the version 2 specs
E 14
I 14
 * nfs definitions as per the Version 2 and 3 specs
E 14
 */

/*
D 14
 * Constants as defined in the Sun NFS Version 2 spec.
E 14
I 14
 * Constants as defined in the Sun NFS Version 2 and 3 specs.
E 14
D 3
 * "Network File System Protocol Specification" in the
 * Manual "Networking on the Sun Workstation", Part #800-1324-03, Rev B
E 3
I 3
 * "NFS: Network File System Protocol Specification" RFC1094
I 14
 * and in the "NFS: Network File System Version 3 Protocol
 * Specification"
E 14
E 3
 */

#define NFS_PORT	2049
#define	NFS_PROG	100003
#define NFS_VER2	2
D 7
#define	NFS_MAXDATA	8192
E 7
I 7
D 14
#define	NFS_MAXDGRAMDATA 8192
E 14
I 14
#define	NFS_VER3	3
#define NFS_V2MAXDATA	8192
#define	NFS_MAXDGRAMDATA 16384
E 14
#define	NFS_MAXDATA	32768
E 7
#define	NFS_MAXPATHLEN	1024
#define	NFS_MAXNAMLEN	255
D 14
#define	NFS_FHSIZE	32
E 14
I 5
#define	NFS_MAXPKTHDR	404
D 14
#define NFS_MAXPACKET	(NFS_MAXPKTHDR+NFS_MAXDATA)
E 14
I 14
#define NFS_MAXPACKET	(NFS_MAXPKTHDR + NFS_MAXDATA)
E 14
E 5
D 9
#define	NFS_NPROCS	18
E 9
I 9
#define	NFS_MINPACKET	20
E 9
I 6
#define	NFS_FABLKSIZE	512	/* Size in bytes of a block wrt fa_blocks */
E 6

D 14
/* Stat numbers for rpc returns */
#define	NFS_OK		0
#define	NFSERR_PERM	1
#define	NFSERR_NOENT	2
#define	NFSERR_IO	5
#define	NFSERR_NXIO	6
#define	NFSERR_ACCES	13
#define	NFSERR_EXIST	17
#define	NFSERR_NODEV	19
#define	NFSERR_NOTDIR	20
#define	NFSERR_ISDIR	21
#define	NFSERR_FBIG	27
#define	NFSERR_NOSPC	28
#define	NFSERR_ROFS	30
D 9
#define	NFSERR_NAMETOOLONG	63
E 9
I 9
#define	NFSERR_NAMETOL	63
E 9
#define	NFSERR_NOTEMPTY	66
#define	NFSERR_DQUOT	69
#define	NFSERR_STALE	70
#define	NFSERR_WFLUSH	99
E 14
I 14
/* Stat numbers for rpc returns (version 2 and 3) */
#define	NFS_OK			0
#define	NFSERR_PERM		1
#define	NFSERR_NOENT		2
#define	NFSERR_IO		5
#define	NFSERR_NXIO		6
#define	NFSERR_ACCES		13
#define	NFSERR_EXIST		17
#define	NFSERR_XDEV		18	/* Version 3 only */
#define	NFSERR_NODEV		19
#define	NFSERR_NOTDIR		20
#define	NFSERR_ISDIR		21
#define	NFSERR_INVAL		22	/* Version 3 only */
#define	NFSERR_FBIG		27
#define	NFSERR_NOSPC		28
#define	NFSERR_ROFS		30
#define	NFSERR_MLINK		31	/* Version 3 only */
#define	NFSERR_NAMETOL		63
#define	NFSERR_NOTEMPTY		66
#define	NFSERR_DQUOT		69
#define	NFSERR_STALE		70
#define	NFSERR_REMOTE		71	/* Version 3 only */
#define	NFSERR_WFLUSH		99	/* Version 2 only */
#define	NFSERR_BADHANDLE	10001	/* The rest Version 3 only */
#define	NFSERR_NOT_SYNC		10002
#define	NFSERR_BAD_COOKIE	10003
#define	NFSERR_NOTSUPP		10004
#define	NFSERR_TOOSMALL		10005
#define	NFSERR_SERVERFAULT	10006
#define	NFSERR_BADTYPE		10007
#define	NFSERR_JUKEBOX		10008
#define NFSERR_TRYLATER		NFSERR_JUKEBOX
#define	NFSERR_STALEWRITEVERF	30001	/* Fake return for nfs_commit() */
E 14

I 14
#define NFSERR_RETVOID		0x20000000 /* Return void, not error */
#define NFSERR_AUTHERR		0x40000000 /* Mark an authentication error */
#define NFSERR_RETERR		0x80000000 /* Mark an error return for V3 */

E 14
/* Sizes in bytes of various nfs rpc components */
D 14
#define	NFSX_FH		32
E 14
#define	NFSX_UNSIGNED	4
D 11
#define	NFSX_FATTR	68
#define	NFSX_SATTR	32
E 11
I 11
D 14
#define	NFSX_NFSFATTR	68
#define	NFSX_NQFATTR	92
#define	NFSX_NFSSATTR	32
#define	NFSX_NQSATTR	44
E 11
#define	NFSX_COOKIE	4
D 11
#define NFSX_STATFS	20
E 11
I 11
#define NFSX_NFSSTATFS	20
#define	NFSX_NQSTATFS	28
#define	NFSX_FATTR(isnq)	((isnq) ? NFSX_NQFATTR : NFSX_NFSFATTR)
#define	NFSX_SATTR(isnq)	((isnq) ? NFSX_NQSATTR : NFSX_NFSSATTR)
#define	NFSX_STATFS(isnq)	((isnq) ? NFSX_NQSTATFS : NFSX_NFSSTATFS)
E 14
E 11

D 14
/* nfs rpc procedure numbers */
E 14
I 14
/* specific to NFS Version 2 */
#define	NFSX_V2FH	32
#define	NFSX_V2FATTR	68
#define	NFSX_V2SATTR	32
#define	NFSX_V2COOKIE	4
#define NFSX_V2STATFS	20

/* specific to NFS Version 3 */
#define NFSX_V3FH		(sizeof (fhandle_t)) /* size this server uses */
#define	NFSX_V3FHMAX		64	/* max. allowed by protocol */
#define NFSX_V3FATTR		84
#define NFSX_V3SATTR		60	/* max. all fields filled in */
#define NFSX_V3SRVSATTR		(sizeof (struct nfsv3_sattr))
#define NFSX_V3POSTOPATTR	(NFSX_V3FATTR + NFSX_UNSIGNED)
#define NFSX_V3WCCDATA		(NFSX_V3POSTOPATTR + 8 * NFSX_UNSIGNED)
#define NFSX_V3COOKIEVERF 	8
#define NFSX_V3WRITEVERF 	8
#define NFSX_V3CREATEVERF	8
#define NFSX_V3STATFS		52
#define NFSX_V3FSINFO		48
#define NFSX_V3PATHCONF		24

/* variants for both versions */
#define NFSX_FH(v3)		((v3) ? (NFSX_V3FHMAX + NFSX_UNSIGNED) : \
					NFSX_V2FH)
#define NFSX_SRVFH(v3)		((v3) ? NFSX_V3FH : NFSX_V2FH)
#define	NFSX_FATTR(v3)		((v3) ? NFSX_V3FATTR : NFSX_V2FATTR)
#define NFSX_PREOPATTR(v3)	((v3) ? (7 * NFSX_UNSIGNED) : 0)
#define NFSX_POSTOPATTR(v3)	((v3) ? (NFSX_V3FATTR + NFSX_UNSIGNED) : 0)
#define NFSX_POSTOPORFATTR(v3)	((v3) ? (NFSX_V3FATTR + NFSX_UNSIGNED) : \
					NFSX_V2FATTR)
#define NFSX_WCCDATA(v3)	((v3) ? NFSX_V3WCCDATA : 0)
#define NFSX_WCCORFATTR(v3)	((v3) ? NFSX_V3WCCDATA : NFSX_V2FATTR)
#define	NFSX_SATTR(v3)		((v3) ? NFSX_V3SATTR : NFSX_V2SATTR)
#define	NFSX_COOKIEVERF(v3)	((v3) ? NFSX_V3COOKIEVERF : 0)
#define	NFSX_WRITEVERF(v3)	((v3) ? NFSX_V3WRITEVERF : 0)
#define NFSX_READDIR(v3)	((v3) ? (5 * NFSX_UNSIGNED) : \
					(2 * NFSX_UNSIGNED))
#define	NFSX_STATFS(v3)		((v3) ? NFSX_V3STATFS : NFSX_V2STATFS)

/* nfs rpc procedure numbers (before version mapping) */
E 14
#define	NFSPROC_NULL		0
#define	NFSPROC_GETATTR		1
#define	NFSPROC_SETATTR		2
D 9
#define	NFSPROC_ROOT		3		/* Obsolete */
E 9
I 9
D 14
#define	NFSPROC_NOOP		3
#define	NFSPROC_ROOT		NFSPROC_NOOP	/* Obsolete */
E 9
#define	NFSPROC_LOOKUP		4
E 14
I 14
#define	NFSPROC_LOOKUP		3
#define	NFSPROC_ACCESS		4
E 14
#define	NFSPROC_READLINK	5
#define	NFSPROC_READ		6
D 9
#define	NFSPROC_WRITECACHE	7		/* Obsolete */
E 9
I 9
D 14
#define	NFSPROC_WRITECACHE	NFSPROC_NOOP	/* Obsolete */
E 9
#define	NFSPROC_WRITE		8
#define	NFSPROC_CREATE		9
#define	NFSPROC_REMOVE		10
#define	NFSPROC_RENAME		11
#define	NFSPROC_LINK		12
#define	NFSPROC_SYMLINK		13
#define	NFSPROC_MKDIR		14
#define	NFSPROC_RMDIR		15
E 14
I 14
#define	NFSPROC_WRITE		7
#define	NFSPROC_CREATE		8
#define	NFSPROC_MKDIR		9
#define	NFSPROC_SYMLINK		10
#define	NFSPROC_MKNOD		11
#define	NFSPROC_REMOVE		12
#define	NFSPROC_RMDIR		13
#define	NFSPROC_RENAME		14
#define	NFSPROC_LINK		15
E 14
#define	NFSPROC_READDIR		16
D 14
#define	NFSPROC_STATFS		17
E 14
I 14
#define	NFSPROC_READDIRPLUS	17
#define	NFSPROC_FSSTAT		18
#define	NFSPROC_FSINFO		19
#define	NFSPROC_PATHCONF	20
#define	NFSPROC_COMMIT		21
E 14

I 9
D 14
/* NQ nfs numbers */
#define	NQNFSPROC_READDIRLOOK	18
#define	NQNFSPROC_GETLEASE	19
#define	NQNFSPROC_VACATED	20
#define	NQNFSPROC_EVICTED	21
I 12
#define	NQNFSPROC_ACCESS	22
E 14
I 14
/* And leasing (nqnfs) procedure numbers (must be last) */
#define	NQNFSPROC_GETLEASE	22
#define	NQNFSPROC_VACATED	23
#define	NQNFSPROC_EVICTED	24
E 14
E 12

D 12
#define	NFS_NPROCS		22
E 12
I 12
D 14
#define	NFS_NPROCS		23
E 14
I 14
#define NFSPROC_NOOP		25
#define	NFS_NPROCS		26

/* Actual Version 2 procedure numbers */
#define	NFSV2PROC_NULL		0
#define	NFSV2PROC_GETATTR	1
#define	NFSV2PROC_SETATTR	2
#define	NFSV2PROC_NOOP		3
#define	NFSV2PROC_ROOT		NFSV2PROC_NOOP	/* Obsolete */
#define	NFSV2PROC_LOOKUP	4
#define	NFSV2PROC_READLINK	5
#define	NFSV2PROC_READ		6
#define	NFSV2PROC_WRITECACHE	NFSV2PROC_NOOP	/* Obsolete */
#define	NFSV2PROC_WRITE		8
#define	NFSV2PROC_CREATE	9
#define	NFSV2PROC_REMOVE	10
#define	NFSV2PROC_RENAME	11
#define	NFSV2PROC_LINK		12
#define	NFSV2PROC_SYMLINK	13
#define	NFSV2PROC_MKDIR		14
#define	NFSV2PROC_RMDIR		15
#define	NFSV2PROC_READDIR	16
#define	NFSV2PROC_STATFS	17

/*
 * Constants used by the Version 3 protocol for various RPCs
 */
#define NFSV3SATTRTIME_DONTCHANGE	0
#define NFSV3SATTRTIME_TOSERVER		1
#define NFSV3SATTRTIME_TOCLIENT		2

#define NFSV3ACCESS_READ		0x01
#define NFSV3ACCESS_LOOKUP		0x02
#define NFSV3ACCESS_MODIFY		0x04
#define NFSV3ACCESS_EXTEND		0x08
#define NFSV3ACCESS_DELETE		0x10
#define NFSV3ACCESS_EXECUTE		0x20

#define NFSV3WRITE_UNSTABLE		0
#define NFSV3WRITE_DATASYNC		1
#define NFSV3WRITE_FILESYNC		2

#define NFSV3CREATE_UNCHECKED		0
#define NFSV3CREATE_GUARDED		1
#define NFSV3CREATE_EXCLUSIVE		2

#define NFSV3FSINFO_LINK		0x01
#define NFSV3FSINFO_SYMLINK		0x02
#define NFSV3FSINFO_HOMOGENEOUS		0x08
#define NFSV3FSINFO_CANSETTIME		0x10

E 14
E 12
E 9
/* Conversion macros */
D 4
#define	vtonfs_mode(t,m) txdr_unsigned(MAKEIMODE(t,m))
E 4
I 4
D 14
extern int		vttoif_tab[];
D 6
#define	vtonfs_mode(t,m) txdr_unsigned((int)(vttoif_tab[(int)(t)] | (m)))
E 6
I 6
#define	vtonfs_mode(t,m) \
E 14
I 14
#define	vtonfsv2_mode(t,m) \
E 14
		txdr_unsigned(((t) == VFIFO) ? MAKEIMODE(VCHR, (m)) : \
				MAKEIMODE((t), (m)))
E 6
E 4
D 14
#define	nfstov_mode(a)	(fxdr_unsigned(u_short, (a))&07777)
#define	vtonfs_type(a)	txdr_unsigned(nfs_type[((long)(a))])
D 6
#define	nfstov_type(a)	v_type[fxdr_unsigned(u_long, (a))]
E 6
I 6
#define	nfstov_type(a)	ntov_type[fxdr_unsigned(u_long,(a))&0x7]
E 14
I 14
#define vtonfsv3_mode(m)	txdr_unsigned((m) & 07777)
#define	nfstov_mode(a)		(fxdr_unsigned(u_short, (a))&07777)
#define	vtonfsv2_type(a)	txdr_unsigned(nfsv2_type[((long)(a))])
#define	vtonfsv3_type(a)	txdr_unsigned(nfsv3_type[((long)(a))])
#define	nfsv2tov_type(a)	nv2tov_type[fxdr_unsigned(u_long,(a))&0x7]
#define	nfsv3tov_type(a)	nv3tov_type[fxdr_unsigned(u_long,(a))&0x7]
E 14
E 6

/* File types */
D 14
typedef enum { NFNON=0, NFREG=1, NFDIR=2, NFBLK=3, NFCHR=4, NFLNK=5 } nfstype;
E 14
I 14
typedef enum { NFNON=0, NFREG=1, NFDIR=2, NFBLK=3, NFCHR=4, NFLNK=5,
	NFSOCK=6, NFFIFO=7 } nfstype;
E 14
I 2

/* Structs for common parts of the rpc's */
I 14
/*
 * File Handle (32 bytes for version 2), variable up to 64 for version 3.
 * File Handles of up to NFS_SMALLFH in size are stored directly in the
 * nfs node, whereas larger ones are malloc'd. (This never happens when
 * NFS_SMALLFH is set to 64.)
 * NFS_SMALLFH should be in the range of 32 to 64 and be divisible by 4.
 */
#ifndef NFS_SMALLFH
#define NFS_SMALLFH	64
#endif
union nfsfh {
	fhandle_t	fh_generic;
	u_char		fh_bytes[NFS_SMALLFH];
};
typedef union nfsfh nfsfh_t;

E 14
struct nfsv2_time {
D 11
	u_long	tv_sec;
	u_long	tv_usec;
E 11
I 11
D 14
	u_long	nfs_sec;
	u_long	nfs_usec;
E 14
I 14
	u_long	nfsv2_sec;
	u_long	nfsv2_usec;
E 14
E 11
};
I 14
typedef struct nfsv2_time	nfstime2;
E 14

I 11
D 14
struct nqnfs_time {
	u_long	nq_sec;
	u_long	nq_nsec;
E 14
I 14
struct nfsv3_time {
	u_long	nfsv3_sec;
	u_long	nfsv3_nsec;
E 14
};
I 14
typedef struct nfsv3_time	nfstime3;
E 14

/*
I 14
 * Quads are defined as arrays of 2 longs to ensure dense packing for the
 * protocol and to facilitate xdr conversion.
 */
struct nfs_uquad {
	u_long	nfsuquad[2];
};
typedef	struct nfs_uquad	nfsuint64;

/*
 * Used to convert between two u_longs and a u_quad_t.
 */
union nfs_quadconvert {
	u_long		lval[2];
	u_quad_t	qval;
};
typedef union nfs_quadconvert	nfsquad_t;

/*
 * NFS Version 3 special file number.
 */
struct nfsv3_spec {
	u_long	specdata1;
	u_long	specdata2;
};
typedef	struct nfsv3_spec	nfsv3spec;

/*
E 14
 * File attributes and setable attributes. These structures cover both
D 14
 * NFS version 2 and the NQNFS protocol. Note that the union is only
 * used to that one pointer can refer to both variants. These structures
E 14
I 14
 * NFS version 2 and the version 3 protocol. Note that the union is only
 * used so that one pointer can refer to both variants. These structures
E 14
 * go out on the wire and must be densely packed, so no quad data types
 * are used. (all fields are longs or u_longs or structures of same)
D 14
 * NB: You can't do sizeof(struct nfsv2_fattr), you must use the
 *     NFSX_FATTR(isnq) macro.
E 14
I 14
 * NB: You can't do sizeof(struct nfs_fattr), you must use the
 *     NFSX_FATTR(v3) macro.
E 14
 */
E 11
D 14
struct nfsv2_fattr {
E 14
I 14
struct nfs_fattr {
E 14
	u_long	fa_type;
	u_long	fa_mode;
	u_long	fa_nlink;
	u_long	fa_uid;
	u_long	fa_gid;
D 11
	u_long	fa_size;
	u_long	fa_blocksize;
	u_long	fa_rdev;
	u_long	fa_blocks;
	u_long	fa_fsid;
	u_long	fa_fileid;
	struct nfsv2_time fa_atime;
	struct nfsv2_time fa_mtime;
	struct nfsv2_time fa_ctime;
E 11
I 11
	union {
		struct {
D 14
			u_long	nfsfa_size;
			u_long	nfsfa_blocksize;
			u_long	nfsfa_rdev;
			u_long	nfsfa_blocks;
			u_long	nfsfa_fsid;
			u_long	nfsfa_fileid;
			struct nfsv2_time nfsfa_atime;
			struct nfsv2_time nfsfa_mtime;
			struct nfsv2_time nfsfa_ctime;
E 14
I 14
			u_long		nfsv2fa_size;
			u_long		nfsv2fa_blocksize;
			u_long		nfsv2fa_rdev;
			u_long		nfsv2fa_blocks;
			u_long		nfsv2fa_fsid;
			u_long		nfsv2fa_fileid;
			nfstime2	nfsv2fa_atime;
			nfstime2	nfsv2fa_mtime;
			nfstime2	nfsv2fa_ctime;
E 14
		} fa_nfsv2;
		struct {
D 14
			struct {
				u_long	nqfa_qsize[2];
			} nqfa_size;
			u_long	nqfa_blocksize;
			u_long	nqfa_rdev;
			struct {
				u_long	nqfa_qbytes[2];
			} nqfa_bytes;
			u_long	nqfa_fsid;
			u_long	nqfa_fileid;
			struct nqnfs_time nqfa_atime;
			struct nqnfs_time nqfa_mtime;
			struct nqnfs_time nqfa_ctime;
			u_long	nqfa_flags;
			u_long	nqfa_gen;
			struct {
				u_long	nqfa_qfilerev[2];
			} nqfa_filerev;
		} fa_nqnfs;
E 14
I 14
			nfsuint64	nfsv3fa_size;
			nfsuint64	nfsv3fa_used;
			nfsv3spec	nfsv3fa_rdev;
			nfsuint64	nfsv3fa_fsid;
			nfsuint64	nfsv3fa_fileid;
			nfstime3	nfsv3fa_atime;
			nfstime3	nfsv3fa_mtime;
			nfstime3	nfsv3fa_ctime;
		} fa_nfsv3;
E 14
	} fa_un;
E 11
};

I 11
/* and some ugly defines for accessing union components */
D 14
#define	fa_nfssize		fa_un.fa_nfsv2.nfsfa_size
#define	fa_nfsblocksize		fa_un.fa_nfsv2.nfsfa_blocksize
#define	fa_nfsrdev		fa_un.fa_nfsv2.nfsfa_rdev
#define	fa_nfsblocks		fa_un.fa_nfsv2.nfsfa_blocks
#define	fa_nfsfsid		fa_un.fa_nfsv2.nfsfa_fsid
#define	fa_nfsfileid		fa_un.fa_nfsv2.nfsfa_fileid
#define	fa_nfsatime		fa_un.fa_nfsv2.nfsfa_atime
#define	fa_nfsmtime		fa_un.fa_nfsv2.nfsfa_mtime
#define	fa_nfsctime		fa_un.fa_nfsv2.nfsfa_ctime
#define	fa_nqsize		fa_un.fa_nqnfs.nqfa_size
#define	fa_nqblocksize		fa_un.fa_nqnfs.nqfa_blocksize
#define	fa_nqrdev		fa_un.fa_nqnfs.nqfa_rdev
#define	fa_nqbytes		fa_un.fa_nqnfs.nqfa_bytes
#define	fa_nqfsid		fa_un.fa_nqnfs.nqfa_fsid
#define	fa_nqfileid		fa_un.fa_nqnfs.nqfa_fileid
#define	fa_nqatime		fa_un.fa_nqnfs.nqfa_atime
#define	fa_nqmtime		fa_un.fa_nqnfs.nqfa_mtime
#define	fa_nqctime		fa_un.fa_nqnfs.nqfa_ctime
#define	fa_nqflags		fa_un.fa_nqnfs.nqfa_flags
#define	fa_nqgen		fa_un.fa_nqnfs.nqfa_gen
#define	fa_nqfilerev		fa_un.fa_nqnfs.nqfa_filerev
E 14
I 14
#define	fa2_size		fa_un.fa_nfsv2.nfsv2fa_size
#define	fa2_blocksize		fa_un.fa_nfsv2.nfsv2fa_blocksize
#define	fa2_rdev		fa_un.fa_nfsv2.nfsv2fa_rdev
#define	fa2_blocks		fa_un.fa_nfsv2.nfsv2fa_blocks
#define	fa2_fsid		fa_un.fa_nfsv2.nfsv2fa_fsid
#define	fa2_fileid		fa_un.fa_nfsv2.nfsv2fa_fileid
#define	fa2_atime		fa_un.fa_nfsv2.nfsv2fa_atime
#define	fa2_mtime		fa_un.fa_nfsv2.nfsv2fa_mtime
#define	fa2_ctime		fa_un.fa_nfsv2.nfsv2fa_ctime
#define	fa3_size		fa_un.fa_nfsv3.nfsv3fa_size
#define	fa3_used		fa_un.fa_nfsv3.nfsv3fa_used
#define	fa3_rdev		fa_un.fa_nfsv3.nfsv3fa_rdev
#define	fa3_fsid		fa_un.fa_nfsv3.nfsv3fa_fsid
#define	fa3_fileid		fa_un.fa_nfsv3.nfsv3fa_fileid
#define	fa3_atime		fa_un.fa_nfsv3.nfsv3fa_atime
#define	fa3_mtime		fa_un.fa_nfsv3.nfsv3fa_mtime
#define	fa3_ctime		fa_un.fa_nfsv3.nfsv3fa_ctime
E 14

E 11
struct nfsv2_sattr {
D 14
	u_long	sa_mode;
	u_long	sa_uid;
	u_long	sa_gid;
E 14
I 14
	u_long		sa_mode;
	u_long		sa_uid;
	u_long		sa_gid;
	u_long		sa_size;
	nfstime2	sa_atime;
	nfstime2	sa_mtime;
};

/*
 * NFS Version 3 sattr structure for the new node creation case.
 */
struct nfsv3_sattr {
	u_long		sa_modetrue;
	u_long		sa_mode;
	u_long		sa_uidtrue;
	u_long		sa_uid;
	u_long		sa_gidtrue;
	u_long		sa_gid;
	u_long		sa_sizefalse;
	u_long		sa_atimetype;
	nfstime3	sa_atime;
	u_long		sa_mtimetype;
	nfstime3	sa_mtime;
};

struct nfs_statfs {
E 14
D 11
	u_long	sa_size;
	struct nfsv2_time sa_atime;
	struct nfsv2_time sa_mtime;
E 11
I 11
	union {
		struct {
D 14
			u_long	nfssa_size;
			struct nfsv2_time nfssa_atime;
			struct nfsv2_time nfssa_mtime;
		} sa_nfsv2;
E 14
I 14
			u_long		nfsv2sf_tsize;
			u_long		nfsv2sf_bsize;
			u_long		nfsv2sf_blocks;
			u_long		nfsv2sf_bfree;
			u_long		nfsv2sf_bavail;
		} sf_nfsv2;
E 14
		struct {
D 14
			struct {
				u_long	nqsa_qsize[2];
			} nqsa_size;
			struct nqnfs_time nqsa_atime;
			struct nqnfs_time nqsa_mtime;
			u_long	nqsa_flags;
			u_long	nqsa_rdev;
		} sa_nqnfs;
	} sa_un;
E 14
I 14
			nfsuint64	nfsv3sf_tbytes;
			nfsuint64	nfsv3sf_fbytes;
			nfsuint64	nfsv3sf_abytes;
			nfsuint64	nfsv3sf_tfiles;
			nfsuint64	nfsv3sf_ffiles;
			nfsuint64	nfsv3sf_afiles;
			u_long		nfsv3sf_invarsec;
		} sf_nfsv3;
	} sf_un;
E 14
E 11
};

I 11
D 14
/* and some ugly defines for accessing the unions */
#define	sa_nfssize		sa_un.sa_nfsv2.nfssa_size
#define	sa_nfsatime		sa_un.sa_nfsv2.nfssa_atime
#define	sa_nfsmtime		sa_un.sa_nfsv2.nfssa_mtime
#define	sa_nqsize		sa_un.sa_nqnfs.nqsa_size
#define	sa_nqatime		sa_un.sa_nqnfs.nqsa_atime
#define	sa_nqmtime		sa_un.sa_nqnfs.nqsa_mtime
#define	sa_nqflags		sa_un.sa_nqnfs.nqsa_flags
#define	sa_nqrdev		sa_un.sa_nqnfs.nqsa_rdev
E 14
I 14
#define sf_tsize	sf_un.sf_nfsv2.nfsv2sf_tsize
#define sf_bsize	sf_un.sf_nfsv2.nfsv2sf_bsize
#define sf_blocks	sf_un.sf_nfsv2.nfsv2sf_blocks
#define sf_bfree	sf_un.sf_nfsv2.nfsv2sf_bfree
#define sf_bavail	sf_un.sf_nfsv2.nfsv2sf_bavail
#define sf_tbytes	sf_un.sf_nfsv3.nfsv3sf_tbytes
#define sf_fbytes	sf_un.sf_nfsv3.nfsv3sf_fbytes
#define sf_abytes	sf_un.sf_nfsv3.nfsv3sf_abytes
#define sf_tfiles	sf_un.sf_nfsv3.nfsv3sf_tfiles
#define sf_ffiles	sf_un.sf_nfsv3.nfsv3sf_ffiles
#define sf_afiles	sf_un.sf_nfsv3.nfsv3sf_afiles
#define sf_invarsec	sf_un.sf_nfsv3.nfsv3sf_invarsec
E 14

E 11
D 14
struct nfsv2_statfs {
	u_long	sf_tsize;
	u_long	sf_bsize;
	u_long	sf_blocks;
	u_long	sf_bfree;
	u_long	sf_bavail;
I 11
	u_long	sf_files;	/* Nqnfs only */
	u_long	sf_ffree;	/* ditto      */
E 14
I 14
struct nfsv3_fsinfo {
	u_long		fs_rtmax;
	u_long		fs_rtpref;
	u_long		fs_rtmult;
	u_long		fs_wtmax;
	u_long		fs_wtpref;
	u_long		fs_wtmult;
	u_long		fs_dtpref;
	nfsuint64	fs_maxfilesize;
	nfstime3	fs_timedelta;
	u_long		fs_properties;
E 14
E 11
};
I 14

struct nfsv3_pathconf {
	u_long		pc_linkmax;
	u_long		pc_namemax;
	u_long		pc_notrunc;
	u_long		pc_chownrestricted;
	u_long		pc_caseinsensitive;
	u_long		pc_casepreserving;
};

#endif
E 14
E 2
E 1
