/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	nfs.h,v $
 * Revision 2.9  90/07/03  16:46:30  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:10:41  mrt]
 * 
 * Revision 2.8  89/08/02  08:04:11  jsb
 * 	Eliminated MACH conditionals. Declare nfs zones.
 * 	[89/07/31  16:21:36  jsb]
 * 
 * Revision 2.7  89/06/03  15:36:35  jsb
 * 	Eliminated offlist field in nfsrdok and added pad field to nfsrddirres
 * 	to support afs/nfs_gateway.c.
 * 	[89/05/26  22:48:38  jsb]
 * 
 * Revision 2.6  89/05/01  18:01:08  rpd
 * 	Added offlist field to nfsrdok struct for afs gateway support.
 * 	[89/05/01  13:59:48  jsb]
 * 
 * Revision 2.5  89/04/22  15:25:30  gm0w
 * 	Removed FIFO code.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  20:53:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:09:06  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  00:54:46  jsb
 * 	MACH: Add kalloc_size and kalloc_base fields to struct nfsrddirres to
 * 	make rfs_rddirfree work.
 * 	[89/01/17  14:07:48  jsb]
 * 
 */
/* @(#)nfs.h	1.2 87/09/11 3.2/4.3NFSSRC */
/*      @(#)nfs.h 1.1 86/09/25 SMI      */

#ifndef	__NFS_HEADER__
#define __NFS_HEADER__

#ifdef	KERNEL
#include <kern/zalloc.h>
#endif

/* Maximum size of data portion of a remote request */
#define NFS_MAXDATA	8192
#define NFS_MAXNAMLEN	255
#define NFS_MAXPATHLEN	1024

/*
 * Rpc retransmission parameters
 */
#if	PROTO
#define NFS_TIMEO	14	/* initial timeout in tenths of a sec. */
#define NFS_RETRIES	6	/* times to retry request */
#else	PROTO
#define NFS_TIMEO	7	/* initial timeout in tenths of a sec. */
#define NFS_RETRIES	3	/* times to retry request */
#endif	PROTO
/*
 * maximum transfer size for different interfaces
 */
#define ECTSIZE	4096
#define IETSIZE	8192

/*
 * Error status
 * Should include all possible net errors.
 * For now we just cast errno into an enum nfsstat.
 */
enum nfsstat {
	NFS_OK = 0,			/* no error */
	NFSERR_PERM=EPERM,		/* Not owner */
	NFSERR_NOENT=ENOENT,		/* No such file or directory */
	NFSERR_IO=EIO,			/* I/O error */
	NFSERR_NXIO=ENXIO,		/* No such device or address */
	NFSERR_ACCES=EACCES,		/* Permission denied */
	NFSERR_EXIST=EEXIST,		/* File exists */
	NFSERR_NODEV=ENODEV,		/* No such device */
	NFSERR_NOTDIR=ENOTDIR,		/* Not a directory */
	NFSERR_ISDIR=EISDIR,		/* Is a directory */
	NFSERR_FBIG=EFBIG,		/* File too large */
	NFSERR_NOSPC=ENOSPC,		/* No space left on device */
	NFSERR_ROFS=EROFS,		/* Read-only file system */
	NFSERR_NAMETOOLONG=ENAMETOOLONG,/* File name too long */
	NFSERR_NOTEMPTY=ENOTEMPTY,	/* Directory not empty */
	NFSERR_DQUOT=EDQUOT,		/* Disc quota exceeded */
	NFSERR_STALE=ESTALE,		/* Stale NFS file handle */
	NFSERR_WFLUSH			/* write cache flushed */
};
#define puterrno(error)		((enum nfsstat)error)
#define geterrno(status)	((int)status)

/*
 * File types
 */
enum nfsftype {
	NFNON,
	NFREG,		/* regular file */
	NFDIR,		/* directory */
	NFBLK,		/* block special */
	NFCHR,		/* character special */
	NFLNK		/* symbolic link */
};

/*
 * Size of an fhandle in bytes
 */
#define NFS_FHSIZE	32

/*
 * File access handle
 * This structure is the Sun server representation of a file.
 * It is handed out by a server for the client to use in further
 * file transactions.
 */

#ifdef	NFSSERVER
/*
 * This struct is only used to find the size of the data field in the 
 * fhandle structure below.
 */
struct fhsize {
	fsid_t	f1;
	u_short	f2;
	char	f3[4];
};
#define NFS_FHMAXDATA	(NFS_FHSIZE - sizeof(struct fhsize) + 4)

struct svcfh {
	fsid_t	fh_fsid;		/* filesystem id */
	u_short	fh_len;			/* file number */
	char	fh_data[NFS_FHMAXDATA];	/* Pad struct to NFS_FHSIZE */
};

typedef struct svcfh fhandle_t;
#else
/*
 * This is the client view of an fhandle
 */
typedef struct {
	char	fh_data[NFS_FHSIZE];	/* opaque data */
} fhandle_t;
#endif


/*
 * Arguments to remote write and writecache
 */
struct nfswriteargs {
	fhandle_t	wa_fhandle;	/* handle for file */
	u_long		wa_begoff;	/* beginning byte offset in file */
	u_long		wa_offset;      /* current byte offset in file */
	u_long		wa_totcount;    /* total write count (to this offset)*/
	u_long		wa_count;	/* size of this write */
	char		*wa_data;	/* data to write (up to NFS_MAXDATA) */
};


/*
 * File attributes
 */
struct nfsfattr {
	enum nfsftype	na_type;	/* file type */
	u_long		na_mode;	/* protection mode bits */
	u_long		na_nlink;	/* # hard links */
	u_long		na_uid;		/* owner user id */
	u_long		na_gid;		/* owner group id */
	u_long		na_size;	/* file size in bytes */
	u_long		na_blocksize;	/* prefered block size */
	u_long		na_rdev;	/* special device # */
	u_long		na_blocks;	/* Kb of disk used by file */
	u_long		na_fsid;	/* device # */
	u_long		na_nodeid;	/* inode # */
	struct timeval	na_atime;	/* time of last access */
	struct timeval	na_mtime;	/* time of last modification */
	struct timeval	na_ctime;	/* time of last change */
};

/*
 * Arguments to remote read
 */
struct nfsreadargs {
	fhandle_t	ra_fhandle;	/* handle for file */
	u_long		ra_offset;	/* byte offset in file */
	u_long		ra_count;	/* immediate read count */
	u_long		ra_totcount;	/* total read count (from this offset)*/
};

/*
 * Status OK portion of remote read reply
 */
struct nfsrrok {
	struct nfsfattr	rrok_attr;	/* attributes, need for pagin*/
	u_long		rrok_count;	/* bytes of data */
	char		*rrok_data;	/* data (up to NFS_MAXDATA bytes) */
	struct buf	*rrok_bp;	/* buffer pointer for bread */
	struct vnode	*rrok_vp;	/* vnode assoc. with buffer */
};

/*
 * Reply from remote read
 */
struct nfsrdresult {
	enum nfsstat	rr_status;		/* status of read */
	union {
		struct nfsrrok	rr_ok_u;	/* attributes, need for pagin*/
	} rr_u;
	u_int		rr_kalloc_size;
};
#define rr_ok		rr_u.rr_ok_u
#define rr_attr		rr_u.rr_ok_u.rrok_attr
#define rr_count	rr_u.rr_ok_u.rrok_count
#define rr_data		rr_u.rr_ok_u.rrok_data
#define rr_bp		rr_u.rr_ok_u.rrok_bp
#define rr_vp		rr_u.rr_ok_u.rrok_vp


/*
 * File attributes which can be set
 */
struct nfssattr {
	u_long		sa_mode;	/* protection mode bits */
	u_long		sa_uid;		/* owner user id */
	u_long		sa_gid;		/* owner group id */
	u_long		sa_size;	/* file size in bytes */
	struct timeval	sa_atime;	/* time of last access */
	struct timeval	sa_mtime;	/* time of last modification */
};


/*
 * Reply status with file attributes
 */
struct nfsattrstat {
	enum nfsstat	ns_status;		/* reply status */
	union {
		struct nfsfattr ns_attr_u;	/* NFS_OK: file attributes */
	} ns_u;
};
#define ns_attr	ns_u.ns_attr_u


/*
 * NFS_OK part of read sym link reply union
 */
struct nfssrok {
	u_long	srok_count;	/* size of string */
	char	*srok_data;	/* string (up to NFS_MAXPATHLEN bytes) */
};

/*
 * Result of reading symbolic link
 */
struct nfsrdlnres {
	enum nfsstat	rl_status;		/* status of symlink read */
	union {
		struct nfssrok	rl_srok_u;	/* name of linked to */
	} rl_u;
};
#define rl_srok		rl_u.rl_srok_u
#define rl_count	rl_u.rl_srok_u.srok_count
#define rl_data		rl_u.rl_srok_u.srok_data


/*
 * Arguments to readdir
 */
struct nfsrddirargs {
	fhandle_t rda_fh;	/* directory handle */
	u_long rda_offset;	/* offset in directory (opaque) */
	u_long rda_count;	/* number of directory bytes to read */
};

/*
 * NFS_OK part of readdir result
 */
struct nfsrdok {
	u_long	rdok_offset;		/* next offset (opaque) */
	u_long	rdok_size;		/* size in bytes of entries */
	bool_t	rdok_eof;		/* true if last entry is in result*/
	struct direct *rdok_entries;	/* variable number of entries */
};

/*
 * Readdir result
 */
struct nfsrddirres {
	u_long		rd_bufsize;	/* size of client request (not xdr'ed)*/
	enum nfsstat	rd_status;
	union {
		struct nfsrdok rd_rdok_u;
	} rd_u;
#if	MACH_AFS
	u_int		rd_pad;		/* for afs/nfs_gateway offset list */
#endif	MACH_AFS
	u_int		rd_kalloc_size;
	caddr_t		rd_kalloc_base;
};

#define rd_rdok		rd_u.rd_rdok_u
#define rd_offset	rd_u.rd_rdok_u.rdok_offset
#define rd_size		rd_u.rd_rdok_u.rdok_size
#define rd_eof		rd_u.rd_rdok_u.rdok_eof
#define rd_entries	rd_u.rd_rdok_u.rdok_entries

/*
 * Arguments for directory operations
 */
struct nfsdiropargs {
	fhandle_t	da_fhandle;	/* directory file handle */
	char		*da_name;	/* name (up to NFS_MAXNAMLEN bytes) */
};

/*
 * NFS_OK part of directory operation result
 */
struct  nfsdrok {
	fhandle_t	drok_fhandle;	/* result file handle */
	struct nfsfattr	drok_attr;	/* result file attributes */
};

/*
 * Results from directory operation 
 */
struct  nfsdiropres {
	enum nfsstat	dr_status;	/* result status */
	union {
		struct  nfsdrok	dr_drok_u;	/* NFS_OK result */
	} dr_u;
};
#define dr_drok		dr_u.dr_drok_u
#define dr_fhandle	dr_u.dr_drok_u.drok_fhandle
#define dr_attr		dr_u.dr_drok_u.drok_attr

/*
 * arguments to setattr
 */
struct nfssaargs {
	fhandle_t	saa_fh;		/* fhandle of file to be set */
	struct nfssattr	saa_sa;		/* new attributes */
};

/*
 * arguments to create and mkdir
 */
struct nfscreatargs {
	struct nfsdiropargs	ca_da;	/* file name to create and parent dir */
	struct nfssattr		ca_sa;	/* initial attributes */
};

/*
 * arguments to link
 */
struct nfslinkargs {
	fhandle_t		la_from;	/* old file */
	struct nfsdiropargs	la_to;		/* new file and parent dir */
};

/*
 * arguments to rename
 */
struct nfsrnmargs {
	struct nfsdiropargs rna_from;	/* old file and parent dir */
	struct nfsdiropargs rna_to;	/* new file and parent dir */
};

/*
 * arguments to symlink
 */
struct nfsslargs {
	struct nfsdiropargs	sla_from;	/* old file and parent dir */
	char			*sla_tnm;	/* new name */
	struct nfssattr		sla_sa;		/* attributes */
};

/*
 * NFS_OK part of statfs operation
 */
struct nfsstatfsok {
	u_long fsok_tsize;	/* preferred transfer size in bytes */
	u_long fsok_bsize;	/* fundamental file system block size */
	u_long fsok_blocks;	/* total blocks in file system */
	u_long fsok_bfree;	/* free blocks in fs */
	u_long fsok_bavail;	/* free blocks avail to non-superuser */
};

/*
 * Results of statfs operation
 */
struct nfsstatfs {
	enum nfsstat	fs_status;	/* result status */
	union {
		struct	nfsstatfsok fs_fsok_u;	/* NFS_OK result */
	} fs_u;
};
#define fs_fsok		fs_u.fs_fsok_u
#define fs_tsize	fs_u.fs_fsok_u.fsok_tsize
#define fs_bsize	fs_u.fs_fsok_u.fsok_bsize
#define fs_blocks	fs_u.fs_fsok_u.fsok_blocks
#define fs_bfree	fs_u.fs_fsok_u.fsok_bfree
#define fs_bavail	fs_u.fs_fsok_u.fsok_bavail

/*
 * XDR routines for handling structures defined above
 */
bool_t xdr_attrstat();
bool_t xdr_creatargs();
bool_t xdr_diropargs();
bool_t xdr_diropres();
bool_t xdr_drok();
bool_t xdr_fattr();
bool_t xdr_fhandle();
bool_t xdr_linkargs();
bool_t xdr_rddirargs();
bool_t xdr_putrddirres();
bool_t xdr_getrddirres();
bool_t xdr_rdlnres();
bool_t xdr_rdresult();
bool_t xdr_readargs();
bool_t xdr_rnmargs();
bool_t xdr_rrok();
bool_t xdr_saargs();
bool_t xdr_sattr();
bool_t xdr_slargs();
bool_t xdr_srok();
bool_t xdr_timeval();
bool_t xdr_writeargs();
bool_t xdr_statfs();

/*
 * Remote file service routines
 */
#define RFS_NULL	0
#define RFS_GETATTR	1
#define RFS_SETATTR	2
#define RFS_ROOT	3
#define RFS_LOOKUP	4
#define RFS_READLINK	5
#define RFS_READ	6
#define RFS_WRITECACHE	7
#define RFS_WRITE	8
#define RFS_CREATE	9
#define RFS_REMOVE	10
#define RFS_RENAME	11
#define RFS_LINK	12
#define RFS_SYMLINK	13
#define RFS_MKDIR	14
#define RFS_RMDIR	15
#define RFS_READDIR	16
#define RFS_STATFS	17
#define RFS_NPROC	18

/*
 * remote file service numbers
 */
#define NFS_PROGRAM	((u_long)100003)
#define NFS_VERSION	((u_long)2)
#define NFS_PORT	2049

#ifdef	KERNEL
extern zone_t nfs_attrstat_zone;
extern zone_t nfs_diropres_zone;
extern zone_t nfs_mntinfo_zone;
extern zone_t nfs_name_zone;
extern zone_t nfs_path_zone;
extern zone_t nfs_rnode_zone;
#endif

#endif	!__NFS_HEADER__
