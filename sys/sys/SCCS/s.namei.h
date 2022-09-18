h36810
s 00002/00000/00164
d D 8.5 95/01/09 18:16:11 cgd 42 41
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00004/00004/00160
d D 8.4 94/08/20 16:50:16 mckusick 41 40
c use new queue.h data structures
e
s 00002/00000/00162
d D 8.3 94/07/28 03:39:29 pendry 40 39
c changes for whiteouts and union filesystem
e
s 00003/00003/00159
d D 8.2 94/01/04 16:16:37 bostic 39 38
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00160
d D 8.1 93/06/02 19:54:35 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00158
d D 7.21 92/07/25 16:28:50 mckusick 37 36
c eliminate embedded comments
e
s 00002/00002/00160
d D 7.20 92/07/20 01:08:05 mckusick 36 35
c new hashing scheme
e
s 00001/00000/00161
d D 7.19 92/07/12 23:47:49 pendry 35 34
c allow lower layers to consume more of the pathname
e
s 00037/00051/00124
d D 7.18 92/02/04 00:27:50 mckusick 34 33
c reorganize and clean up John Heideman's layout
e
s 00059/00025/00116
d D 7.17 92/01/22 15:42:03 heideman 33 32
c works with lookup converted
e
s 00001/00001/00140
d D 7.16 92/01/13 15:21:29 mckusick 32 31
c REMOTE gone; RDONLY added
e
s 00050/00043/00091
d D 7.15 91/05/15 19:17:10 mckusick 31 30
c namei/lookup split apart; eliminate direct structure
e
s 00002/00007/00132
d D 7.14 91/03/17 15:34:02 karels 30 29
c more-or-less working with new proc & user structs
e
s 00023/00012/00116
d D 7.13 91/02/21 22:54:58 mckusick 29 28
c fixes for multiple calls to namei (for rename in NFS)
e
s 00003/00003/00125
d D 7.12 91/02/05 17:03:25 bostic 28 27
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00000/00002/00128
d D 7.11 91/01/10 23:30:06 mckusick 27 26
c rdir and cdir move into file descriptor structure
e
s 00001/00011/00129
d D 7.10 90/06/28 21:59:59 bostic 26 25
c new copyright notice
e
s 00009/00007/00131
d D 7.9 90/05/03 16:56:45 mckusick 25 24
c add REMOTE and HASBUF for NFS
e
s 00004/00004/00134
d D 7.8 90/04/10 20:40:10 mckusick 24 23
c the name cache is now dynamically allocated
e
s 00001/00001/00137
d D 7.7 89/12/30 22:18:23 mckusick 23 21
c eliminate unintended overlap, #define ni_segflg => ni_uioseg
e
s 00008/00001/00100
d D 7.3.1.1 89/09/04 14:36:37 karels 22 18
c branch for osi alpha release (pre-vnode, but has NAMEI macro)
e
s 00009/00011/00129
d D 7.6 89/08/25 21:46:21 mckusick 21 20
c reorganize for clarity; capability fields in the vnode cache
e
s 00002/00000/00138
d D 7.5 89/06/06 19:35:03 mckusick 20 19
c add selectors for newly used fields
e
s 00057/00020/00081
d D 7.4 89/05/09 16:36:24 mckusick 19 18
c merge in vnodes
e
s 00014/00003/00087
d D 7.3 89/01/20 09:22:37 bostic 18 17
c add Berkeley specific copyright
e
s 00002/00000/00088
d D 7.2 88/01/05 16:42:37 bostic 17 16
c protect applications that include user.h from KERNEL #ifdef's.
e
s 00001/00001/00087
d D 7.1 86/06/04 23:25:43 mckusick 16 15
c 4.3BSD release version
e
s 00002/00000/00086
d D 6.12 86/03/28 11:47:22 mckusick 15 14
c ifdef KERNEL for kernel variables
e
s 00007/00005/00079
d D 6.11 86/02/20 21:03:30 karels 14 12
c rename nch to avoid name conflict
e
s 00008/00006/00078
d R 6.11 86/02/20 17:45:39 karels 13 12
c rename nch to avoid name collision 
e
s 00007/00001/00077
d D 6.10 85/06/08 15:02:36 mckusick 12 11
c Add copyright
e
s 00000/00001/00078
d D 6.9 85/03/07 19:55:51 karels 11 10
c garbage
e
s 00001/00000/00078
d D 6.8 85/02/15 16:24:30 mckusick 10 9
c add ni_endoff for shrinking directories (from kre)
e
s 00001/00001/00077
d D 6.7 84/08/28 17:29:23 bloom 9 8
c Change include paths.  No more ../h
e
s 00010/00004/00068
d D 6.6 84/07/08 16:03:20 mckusick 8 7
c comments; add provision for returning pathname buffers
e
s 00030/00007/00042
d D 6.5 84/07/08 15:47:45 mckusick 7 6
c rework `namei' interface to eliminate global variables
e
s 00011/00009/00038
d D 6.4 84/06/27 20:46:06 sam 6 5
c revise to hold soft references so . and .. can be held in cache
e
s 00013/00001/00034
d D 6.3 84/01/04 16:26:30 mckusick 5 4
c add namei statistics structure so that `vmstat' can summarize it
e
s 00019/00000/00016
d D 6.2 84/01/03 23:43:21 mckusick 4 3
c add system wide cacheing of path names in namei() (from kre)
e
s 00000/00000/00016
d D 6.1 83/07/29 06:13:18 sam 3 2
c 4.2 distribution
e
s 00006/00000/00010
d D 4.2 82/11/13 23:08:28 sam 2 1
c merge 4.1b and 4.1c
e
s 00010/00000/00000
d D 4.1 82/09/04 09:27:39 root 1 0
c date and time created 82/09/04 09:27:39 by root
e
u
U
f b 
t
T
I 1
D 12
/*	%M%	%I%	%E%	*/
E 12
I 12
/*
D 16
 * Copyright (c) 1982 Regents of the University of California.
E 16
I 16
D 18
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 16
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
D 19
 * Copyright (c) 1982, 1986 The Regents of the University of California.
E 19
I 19
D 31
 * Copyright (c) 1985, 1989 Regents of the University of California.
E 31
I 31
D 38
 * Copyright (c) 1985, 1989, 1991 Regents of the University of California.
E 31
E 19
 * All rights reserved.
E 38
I 38
 * Copyright (c) 1985, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 38
 *
D 26
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 18
 *
 *	%W% (Berkeley) %G%
 */
E 12

I 33
D 34
/* NEEDSWORK: function defns need update */

E 34
E 33
D 7
struct namidata {
	int	ni_offset;
	int	ni_count;
	struct	inode *ni_pdir;
	struct	direct ni_dent;
E 7
I 7
D 28
#ifndef _NAMEI_
#define	_NAMEI_
E 28
I 28
D 39
#ifndef _NAMEI_H_
#define	_NAMEI_H_
E 39
I 39
#ifndef _SYS_NAMEI_H_
#define	_SYS_NAMEI_H_
E 39
E 28

I 41
#include <sys/queue.h>

E 41
I 33
D 34

struct componentname {
	u_long cn_nameiop;	/* in */
	u_long cn_flags;	/* in */
	long cn_namelen;	/* in */
	char *cn_nameptr;	/* in */
	u_long cn_hash;		/* in */
	char *cn_pnbuf;		/* in */
	struct ucred *cn_cred;	/* in */
	struct proc *cn_proc;	/* in */
	/*
	 * Side effects.
	 */
	struct ufs_specific {		/* saved info for new dir entry */
		off_t	ufs_endoff;	/* end of useful directory contents */
		long	ufs_offset;	/* offset of free space in directory */
		long	ufs_count;	/* size of free slot in directory */
		ino_t	ufs_ino;	/* inode number of found directory */
		u_long	ufs_reclen;	/* size of found directory entry */
	} cn_ufs;
};

E 34
E 33
D 30
#ifdef KERNEL
I 19
#include "../ufs/dir.h"
E 19
D 9
#include "../h/uio.h"
E 9
I 9
#include "uio.h"
E 9
#else
#include <sys/uio.h>
I 19
#include <ufs/dir.h>
E 19
#endif
E 30
I 30
D 31
#include <ufs/dir.h>		/* XXX */
E 30

E 31
I 8
/*
 * Encapsulation of namei parameters.
D 31
 * One of these is located in the u. area to
 * minimize space allocated on the kernel stack.
E 31
 */
E 8
struct nameidata {
I 19
D 31
		/* arguments to namei and related context: */
E 31
I 31
	/*
D 34
	 * Arguments to namei.
E 34
I 34
	 * Arguments to namei/lookup.
E 34
	 */
E 31
E 19
	caddr_t	ni_dirp;		/* pathname pointer */
I 19
	enum	uio_seg ni_segflg;	/* location of pathname */
E 19
I 8
D 29
	short	ni_nameiop;		/* see below */
E 29
I 29
D 33
	u_long	ni_nameiop;		/* see below */
E 33
I 33
D 34
        u_long	ni_nameiop;		/* see below.  NEEDSWORK: here for compatibility */
E 34
I 34
D 37
     /* u_long	ni_nameiop;		/* namei operation */
     /* u_long	ni_flags;		/* flags to namei */
     /* struct	proc *ni_proc;		/* process requesting lookup */
E 37
I 37
     /* u_long	ni_nameiop;		   namei operation */
     /* u_long	ni_flags;		   flags to namei */
     /* struct	proc *ni_proc;		   process requesting lookup */
E 37
E 34
E 33
I 31
	/*
	 * Arguments to lookup.
	 */
E 31
E 29
D 19
	short	ni_error;		/* error return if any */
I 10
	off_t	ni_endoff;		/* end of useful stuff in directory */
E 10
E 8
	struct	inode *ni_pdir;		/* inode of parent directory of dirp */
D 8
	struct	iovec ni_iovec;
	struct	uio ni_uio;
E 8
I 8
D 11
	struct	buf *ni_pathbp;		/* unresolved pathname */
E 11
	struct	iovec ni_iovec;		/* MUST be pointed to by ni_iov */
	struct	uio ni_uio;		/* directory I/O parameters */
E 19
I 19
D 27
	struct	vnode *ni_cdir;		/* current directory */
	struct	vnode *ni_rdir;		/* root directory, if not normal root */
E 27
D 33
	struct	ucred *ni_cred;		/* credentials */
E 33
I 33
D 37
     /* struct	ucred *ni_cred;		/* credentials */
E 37
I 37
     /* struct	ucred *ni_cred;		   credentials */
E 37
E 33
I 29
D 31
	struct	vnode *ni_startdir;	/* alternate starting directory */
E 29

		/* shared between namei, lookup routines and commit routines: */
	caddr_t	ni_pnbuf;		/* pathname buffer */
E 31
I 31
	struct	vnode *ni_startdir;	/* starting directory */
	struct	vnode *ni_rootdir;	/* logical root directory */
	/*
D 33
	 * Results
E 33
I 33
	 * Results: returned from/manipulated by lookup
E 33
	 */
	struct	vnode *ni_vp;		/* vnode of result */
	struct	vnode *ni_dvp;		/* vnode of intermediate directory */
	/*
D 34
	 * Shared between namei, lookup routines, and commit routines.
E 34
I 34
	 * Shared between namei and lookup/commit routines.
E 34
	 */
D 33
	char	*ni_pnbuf;		/* pathname buffer */
E 33
I 33
D 34
     /* char	*ni_pnbuf;		/* pathname buffer */
E 34
E 33
	long	ni_pathlen;		/* remaining chars in path */
E 31
D 33
	char	*ni_ptr;		/* current location in pathname */
I 31
	long	ni_namelen;		/* length of current component */
E 33
I 33
D 34
     /* char	*ni_ptr;		/* current location in pathname */
     /* long	ni_namelen;		/* length of current component */
E 34
E 33
E 31
	char	*ni_next;		/* next location in pathname */
D 31
	u_int	ni_pathlen;		/* remaining chars in path */
E 31
I 21
D 33
	u_long	ni_hash;		/* hash value of current component */
E 33
I 33
D 34
     /* u_long	ni_hash;		/* hash value of current component */
E 33
E 21
D 31
	short	ni_namelen;		/* length of current component */
	short	ni_loopcnt;		/* count of symlinks encountered */
	char	ni_makeentry;		/* 1 => add entry to name cache */
	char	ni_isdotdot;		/* 1 => current component name is .. */

		/* results: */
	struct	vnode *ni_vp;		/* vnode of result */
	struct	vnode *ni_dvp;		/* vnode of intermediate directory */
I 21
	struct	direct ni_dent;		/* final component name */
E 21

		/* side effects: */
E 19
E 8
D 21
	struct	direct ni_dent;		/* current directory entry */
I 19

E 21
	/* BEGIN UFS SPECIFIC */
	off_t	ni_endoff;		/* end of useful directory contents */
	struct ndirinfo {		/* saved info for new dir entry */
		struct	iovec nd_iovec;		/* pointed to by ni_iov */
		struct	uio nd_uio;		/* directory I/O parameters */
D 21
		u_long	nd_hash;		/* hash value of nd_dent */
E 21
	} ni_nd;
	/* END UFS SPECIFIC */
E 31
I 31
	u_char	ni_loopcnt;		/* count of symlinks encountered */
D 33
	u_char	ni_makeentry;		/* 1 => add entry to name cache */
	u_char	ni_isdotdot;		/* 1 => current component name is .. */
	u_char	ni_more;		/* 1 => symlink needs interpretation */
E 33
I 33
     /* u_char	ni_makeentry;		/* 1 => add entry to name cache */
     /* u_char	ni_isdotdot;		/* 1 => current component name is .. */
     /* u_char	ni_more;		/* 1 => symlink needs interpretation */
E 34
I 34
	u_long	ni_loopcnt;		/* count of symlinks encountered */
E 34
E 33
	/*
D 33
	 * Side effects.
E 33
I 33
D 34
	 * Lookup params.
E 34
I 34
	 * Lookup parameters: this structure describes the subset of
	 * information from the nameidata structure that is passed
	 * through the VOP interface.
E 34
E 33
	 */
D 33
	struct ufs_specific {		/* saved info for new dir entry */
		off_t	ufs_endoff;	/* end of useful directory contents */
		long	ufs_offset;	/* offset of free space in directory */
		long	ufs_count;	/* size of free slot in directory */
		ino_t	ufs_ino;	/* inode number of found directory */
		u_long	ufs_reclen;	/* size of found directory entry */
	} ni_ufs;
E 33
I 33
D 34
	struct componentname ni_cnd;
E 34
I 34
	struct componentname {
		/*
		 * Arguments to lookup.
		 */
		u_long	cn_nameiop;	/* namei operation */
		u_long	cn_flags;	/* flags to namei */
		struct	proc *cn_proc;	/* process requesting lookup */
		struct	ucred *cn_cred;	/* credentials */
		/*
		 * Shared between lookup and commit routines.
		 */
		char	*cn_pnbuf;	/* pathname buffer */
		char	*cn_nameptr;	/* pointer to looked up name */
		long	cn_namelen;	/* length of looked up component */
		u_long	cn_hash;	/* hash value of looked up name */
I 35
		long	cn_consume;	/* chars to consume in lookup() */
E 35
	} ni_cnd;
E 34
E 33
E 31
E 19
D 8
	short	ni_error;		/* error return if any */
	short	ni_nameiop;		/* see below */
E 8
E 7
};
I 33
D 34
/*
 * Backwards compatibility.
 */
/* #define ni_nameiop	ni_cnd.cn_nameiop */
#define ni_cred		ni_cnd.cn_cred
#define ni_pnbuf	ni_cnd.cn_pnbuf
#define ni_namelen	ni_cnd.cn_namelen
#define ni_ptr		ni_cnd.cn_nameptr
#define ni_hash		ni_cnd.cn_hash
#define ni_flags	ni_cnd.cn_flags
#define ni_ufs		ni_cnd.cn_ufs
E 34
E 33

D 7
enum nami_op { NAMI_LOOKUP, NAMI_CREATE, NAMI_DELETE };
E 7
I 7
D 19
#define	ni_base		ni_iovec.iov_base
#define	ni_count	ni_iovec.iov_len
#define	ni_iov		ni_uio.uio_iov
#define	ni_iovcnt	ni_uio.uio_iovcnt
#define	ni_offset	ni_uio.uio_offset
#define	ni_segflg	ni_uio.uio_segflg
#define	ni_resid	ni_uio.uio_resid
E 19
I 19
D 31
#define	ni_base		ni_nd.nd_iovec.iov_base
#define	ni_count	ni_nd.nd_iovec.iov_len
D 23
#define	ni_segflg	ni_nd.nd_uio.uio_segflg
E 23
I 23
#define	ni_uioseg	ni_nd.nd_uio.uio_segflg
E 23
#define	ni_iov		ni_nd.nd_uio.uio_iov
#define	ni_iovcnt	ni_nd.nd_uio.uio_iovcnt
#define	ni_offset	ni_nd.nd_uio.uio_offset
#define	ni_resid	ni_nd.nd_uio.uio_resid
I 20
#define	ni_rw		ni_nd.nd_uio.uio_rw
#define	ni_uio		ni_nd.nd_uio
E 20
D 21
#define ni_hash		ni_nd.nd_hash
E 21
E 19
E 7
I 2

E 31
I 17
#ifdef KERNEL
E 17
D 7
/* this is temporary until the namei interface changes */
E 7
I 7
/*
D 14
 * namei opertions
E 14
I 14
D 29
 * namei operations and modifiers
E 29
I 29
 * namei operations
E 29
E 14
 */
E 7
#define	LOOKUP		0	/* perform name lookup only */
#define	CREATE		1	/* setup for file creation */
#define	DELETE		2	/* setup for file deletion */
D 19
#define	LOCKPARENT	0x10	/* see the top of namei */
E 19
I 19
#define	RENAME		3	/* setup for file renaming */
D 29
#define	OPFLAG		3	/* mask for operation */
D 25
#define	LOCKLEAF	0x04	/* lock inode on return */
#define	LOCKPARENT	0x08	/* want parent vnode returned locked */
#define	WANTPARENT	0x10	/* want parent vnode returned unlocked */
E 19
I 4
#define NOCACHE		0x20	/* name must not be left in cache */
I 7
#define FOLLOW		0x40	/* follow symbolic links */
#define	NOFOLLOW	0x0	/* don't follow symbolic links (pseudo) */
I 19
#define	NOMOUNT		0x80	/* don't cross mount points */
E 25
I 25
#define	LOCKLEAF	0x004	/* lock inode on return */
#define	LOCKPARENT	0x008	/* want parent vnode returned locked */
#define	WANTPARENT	0x010	/* want parent vnode returned unlocked */
#define	NOCACHE		0x020	/* name must not be left in cache */
#define	FOLLOW		0x040	/* follow symbolic links */
#define	NOFOLLOW	0x000	/* do not follow symbolic links (pseudo) */
#define	NOCROSSMOUNT	0x080	/* do not cross mount points */
#define	REMOTE		0x100	/* lookup for remote filesystem servers */
#define	HASBUF		0x200	/* has preallocated pathname buffer */
E 29
I 29
#define	OPMASK		3	/* mask for operation */
/*
D 33
 * namei operational modifiers
E 33
I 33
 * namei operational modifier flags, stored in ni_cnd.flags
E 33
 */
#define	LOCKLEAF	0x0004	/* lock inode on return */
#define	LOCKPARENT	0x0008	/* want parent vnode returned locked */
#define	WANTPARENT	0x0010	/* want parent vnode returned unlocked */
#define	NOCACHE		0x0020	/* name must not be left in cache */
#define	FOLLOW		0x0040	/* follow symbolic links */
#define	NOFOLLOW	0x0000	/* do not follow symbolic links (pseudo) */
#define	MODMASK		0x00fc	/* mask of operational modifiers */
/*
D 31
 * namei parameter descriptors
E 31
I 31
 * Namei parameter descriptors.
 *
 * SAVENAME may be set by either the callers of namei or by VOP_LOOKUP.
 * If the caller of namei sets the flag (for example execve wants to
 * know the name of the program that is being executed), then it must
 * free the buffer. If VOP_LOOKUP sets the flag, then the buffer must
 * be freed by either the commit routine or the VOP_ABORT routine.
 * SAVESTART is set only by the callers of namei. It implies SAVENAME
 * plus the addition of saving the parent directory that contains the
 * name in ni_startdir. It allows repeated calls to lookup for the
 * name being sought. The caller is responsible for releasing the
 * buffer and for vrele'ing ni_startdir.
E 31
 */
D 33
#define	NOCROSSMOUNT	0x0100	/* do not cross mount points */
D 32
#define	REMOTE		0x0200	/* lookup for remote filesystem servers */
E 32
I 32
#define	RDONLY		0x0200	/* lookup with read-only semantics */
E 32
D 31
#define	HASBUF		0x0400	/* has preallocated pathname buffer */
#define	STARTDIR	0x0800	/* has alternate starting directory */
#define	SAVESTARTDIR	0x1000	/* do not vrele alternate starting directory */
E 31
I 31
#define	HASBUF		0x0400	/* has allocated pathname buffer */
#define	SAVENAME	0x0800	/* save pathanme buffer */
#define	SAVESTART	0x1000	/* save starting directory */
E 31
#define PARAMASK	0xff00	/* mask of parameter descriptors */
E 33
I 33
#define	NOCROSSMOUNT	0x00100	/* do not cross mount points */
#define	RDONLY		0x00200	/* lookup with read-only semantics */
#define	HASBUF		0x00400	/* has allocated pathname buffer */
#define	SAVENAME	0x00800	/* save pathanme buffer */
#define	SAVESTART	0x01000	/* save starting directory */
D 34
/* new: */
E 34
#define ISDOTDOT	0x02000	/* current component name is .. */
#define MAKEENTRY	0x04000	/* entry is to be added to name cache */
#define ISLASTCN	0x08000	/* this is last component of pathname */
#define ISSYMLINK	0x10000	/* symlink needs interpretation */
I 40
#define	ISWHITEOUT	0x20000	/* found whiteout */
#define	DOWHITEOUT	0x40000	/* do whiteouts */
E 40
#define PARAMASK	0xfff00	/* mask of parameter descriptors */
I 34
/*
 * Initialization of an nameidata structure.
 */
#define NDINIT(ndp, op, flags, segflg, namep, p) { \
	(ndp)->ni_cnd.cn_nameiop = op; \
	(ndp)->ni_cnd.cn_flags = flags; \
	(ndp)->ni_segflg = segflg; \
	(ndp)->ni_dirp = namep; \
	(ndp)->ni_cnd.cn_proc = p; \
}
E 34
E 33
E 29
E 25
E 19
I 17
#endif
E 17
E 7

/*
 * This structure describes the elements in the cache of recent
D 24
 * names looked up by namei.
E 24
I 24
 * names looked up by namei. NCHNAMLEN is sized to make structure
 * size a power of two to optimize malloc's. Minimum reasonable
 * size is 15.
E 24
 */
I 19

D 24
#define	NCHNAMLEN	15	/* maximum name segment length we bother with */
E 24
I 24
#define	NCHNAMLEN	31	/* maximum name segment length we bother with */
E 24

E 19
D 5
#define	NCHNAMLEN	11	/* maximum name segment length we bother with */
E 5
I 5
D 6
#define	NCHNAMLEN	15	/* maximum name segment length we bother with */
E 6
E 5
D 14
struct	nch {
D 6
	struct	nch	*nc_forw, *nc_back;	/* hash chain, MUST BE FIRST */
	struct	nch	*nc_nxt, **nc_prev;	/* LRU chain */
	struct	inode	*nc_ip;			/* inode the name refers to */
	ino_t		 nc_ino;		/* ino of parent of name */
	dev_t		 nc_dev;		/* dev of parent of name */
	dev_t		 nc_idev;		/* dev of the name ref'd */
	char		 nc_nlen;		/* length of name */
	char		 nc_name[NCHNAMLEN];	/* segment name */
E 6
I 6
	struct	nch *nc_forw, *nc_back;	/* hash chain, MUST BE FIRST */
	struct	nch *nc_nxt, **nc_prev;	/* LRU chain */
E 14
I 14
struct	namecache {
D 36
	struct	namecache *nc_forw;	/* hash chain, MUST BE FIRST */
	struct	namecache *nc_back;	/* hash chain, MUST BE FIRST */
E 36
I 36
D 41
	struct	namecache *nc_forw;	/* hash chain */
	struct	namecache **nc_back;	/* hash chain */
E 36
	struct	namecache *nc_nxt;	/* LRU chain */
	struct	namecache **nc_prev;	/* LRU chain */
E 41
I 41
	LIST_ENTRY(namecache) nc_hash;	/* hash chain */
	TAILQ_ENTRY(namecache) nc_lru;	/* LRU chain */
E 41
I 21
	struct	vnode *nc_dvp;		/* vnode of parent of name */
	u_long	nc_dvpid;		/* capability number of nc_dvp */
E 21
E 14
D 19
	struct	inode *nc_ip;		/* inode the name refers to */
	ino_t	nc_ino;			/* ino of parent of name */
	dev_t	nc_dev;			/* dev of parent of name */
	dev_t	nc_idev;		/* dev of the name ref'd */
	long	nc_id;			/* referenced inode's id */
E 19
I 19
	struct	vnode *nc_vp;		/* vnode the name refers to */
D 21
	struct	vnode *nc_dp;		/* vnode of parent of name */
E 21
I 21
	u_long	nc_vpid;		/* capability number of nc_vp */
E 21
E 19
	char	nc_nlen;		/* length of name */
D 19
#define	NCHNAMLEN	15	/* maximum name segment length we bother with */
E 19
	char	nc_name[NCHNAMLEN];	/* segment name */
I 19
D 21
	struct	ucred *nc_cred;		/* ??? credentials */
E 21
E 19
E 6
};
I 19

D 21
#define ANYCRED ((struct ucred *) -1)
#define NOCRED  ((struct ucred *) 0)

E 21
E 19
I 15
#ifdef KERNEL
E 15
D 14
struct	nch *nch;
E 14
I 14
D 24
struct	namecache *namecache;
E 14
int	nchsize;
E 24
I 21
u_long	nextvnodeid;
I 30
D 34
int	namei __P((struct nameidata *ndp, struct proc *p));
I 31
int	lookup __P((struct nameidata *ndp, struct proc *p));
E 34
I 34
int	namei __P((struct nameidata *ndp));
int	lookup __P((struct nameidata *ndp));
I 42
int	relookup __P((struct vnode *dvp, struct vnode **vpp,
	    struct componentname *cnp));
E 42
E 34
E 31
E 30
E 21
I 15
#endif
E 15
I 5

/*
 * Stats on usefulness of namei caches.
 */
struct	nchstats {
D 21
	long	ncs_goodhits;		/* hits that we can reall use */
E 21
I 21
	long	ncs_goodhits;		/* hits that we can really use */
	long	ncs_neghits;		/* negative hits that we can use */
E 21
	long	ncs_badhits;		/* hits we must drop */
I 6
	long	ncs_falsehits;		/* hits with id mismatch */
E 6
	long	ncs_miss;		/* misses */
	long	ncs_long;		/* long names that ignore cache */
	long	ncs_pass2;		/* names found with passes == 2 */
	long	ncs_2passes;		/* number of times we attempt it */
};
I 7
D 21
D 22
#endif
E 22
I 22

#define	NAMEI(ndp, nameiop, segflg, dirp) \
	ndp->ni_nameiop = nameiop, \
	ndp->ni_segflg = segflg, \
	ndp->ni_dirp = dirp, \
	namei(ndp);

#endif /* !_NAMEI_ */
E 22
E 21
I 21
D 28
#endif /* _NAMEI_ */
E 28
I 28
D 39
#endif /* !_NAMEI_H_ */
E 39
I 39
#endif /* !_SYS_NAMEI_H_ */
E 39
E 28
E 21
E 7
E 5
E 4
E 2
E 1
