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
 * $Log:	namei.h,v $
 * Revision 2.7  89/04/22  15:32:09  gm0w
 * 	Removed MACH_VFS changes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.6  89/03/09  22:06:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  17:55:09  gm0w
 * 	Made all CMUCS conditionals true. Made the
 * 	defines for VICE and  MACH_RFS be always true.
 * 	Put macros under #ifdef KERNEL.
 * 	[89/02/13            mrt]
 * 
 * Revision 2.4  89/01/30  22:08:11  rpd
 * 	Made variable declarations use "extern".
 * 	[89/01/25  15:20:32  rpd]
 * 
 * Revision 2.3  89/01/18  01:17:51  jsb
 * 	Vnode support: redefine ni_nbpp for rfs support in vfs_lookup.c.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.2  88/08/24  02:37:23  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:19:05  mwyoung]
 * 
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE: added definition of horrible rmt_saved_data struct.
 *
 * 24-Jul-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added include of "dir.h" to satisfy "struct direct" reference.
 *	Prepended agreement notice.
 *
 * 20-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Added KEEPNAMEBUF flag definition and ni_nbpp() macro.
 *
 * 24-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Updraged to 4.3.
 *
 * 20-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Added OKREMOTE flag defintion.
 *	[V1(1)]
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)namei.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_NAMEI_H_
#define _SYS_NAMEI_H_

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/dir.h>

/*
 * Encapsulation of namei parameters.
 * One of these is located in the u. area to
 * minimize space allocated on the kernel stack.
 */
struct nameidata {
	caddr_t	ni_dirp;		/* pathname pointer */
	short	ni_nameiop;		/* see below */
	short	ni_error;		/* error return if any */
	off_t	ni_endoff;		/* end of useful stuff in directory */
	struct	inode *ni_pdir;		/* inode of parent directory of dirp */
	struct	iovec ni_iovec;		/* MUST be pointed to by ni_iov */
	struct	uio ni_uio;		/* directory I/O parameters */
	struct	direct ni_dent;		/* current directory entry */
};

#define ni_base		ni_iovec.iov_base
#define ni_count	ni_iovec.iov_len
#define ni_iov		ni_uio.uio_iov
#define ni_iovcnt	ni_uio.uio_iovcnt
#define ni_offset	ni_uio.uio_offset
#define ni_segflg	ni_uio.uio_segflg
#define ni_resid	ni_uio.uio_resid

#ifdef	KERNEL
#include <mach_rfs.h>
#include <vice.h>

/*
 * namei operations and modifiers
 */
#define LOOKUP		0	/* perform name lookup only */
#define CREATE		1	/* setup for file creation */
#define DELETE		2	/* setup for file deletion */
#define LOCKPARENT	0x10	/* see the top of namei */
#define NOCACHE		0x20	/* name must not be left in cache */
#define FOLLOW		0x40	/* follow symbolic links */
#define NOFOLLOW	0x0	/* don't follow symbolic links (pseudo) */
#if	MACH_RFS
#define OKREMOTE	0x80	/* allow remote name */
#define KEEPNAMEBUF	0x100	/* keep name buffer in use after return */

/*
 *  When KEEPNAMEBUF is set we need a place to remember the buffer pointer and
 *  this is as good as any since it is not otherwise used by namei().
 *
 *  N.B.  We assume here that the uio_resid field (an int) is at least as wide
 *  as a (struct buf *).
 */
#define ni_nbpp(ndp)	\
	((struct buf **)&((ndp)->ni_resid))

/*
 *  Default namei() definition for routines which do not wish to
 *  handle remote names.
 */

#define namei	cnamei

/*
 *  Cover namei() definition to allow remote name processing.
 */
#define rnamei(ndp)	\
	cnamei((((ndp)->ni_nameiop |= OKREMOTE), ndp))
#endif	MACH_RFS
#endif	KERNEL

/*
 * This structure describes the elements in the cache of recent
 * names looked up by namei.
 */
struct	namecache {
	struct	namecache *nc_forw;	/* hash chain, MUST BE FIRST */
	struct	namecache *nc_back;	/* hash chain, MUST BE FIRST */
	struct	namecache *nc_nxt;	/* LRU chain */
	struct	namecache **nc_prev;	/* LRU chain */
	struct	inode *nc_ip;		/* inode the name refers to */
	ino_t	nc_ino;			/* ino of parent of name */
	dev_t	nc_dev;			/* dev of parent of name */
	dev_t	nc_idev;		/* dev of the name ref'd */
	long	nc_id;			/* referenced inode's id */
	char	nc_nlen;		/* length of name */
#define NCHNAMLEN	15	/* maximum name segment length we bother with */
	char	nc_name[NCHNAMLEN];	/* segment name */
};

#ifdef	KERNEL
extern struct	namecache *namecache;
extern int	nchsize;
#endif	KERNEL

/*
 * Stats on usefulness of namei caches.
 */
struct	nchstats {
	long	ncs_goodhits;		/* hits that we can reall use */
	long	ncs_badhits;		/* hits we must drop */
	long	ncs_falsehits;		/* hits with id mismatch */
	long	ncs_miss;		/* misses */
	long	ncs_long;		/* long names that ignore cache */
	long	ncs_pass2;		/* names found with passes == 2 */
	long	ncs_2passes;		/* number of times we attempt it */
};

#if	!defined(KERNEL) || VICE
/*
 *  Horrible structure to allow communication
 *  between recursive calls of rmt_namei.
 */
struct	rmt_saved_data {
	dev_t	rsd_dev;		/* remote device of previous call */
	struct	nameidata *rsd_nidata;	/* arg/result namei structure */
	struct	buf *rsd_nibuf;		/* buffer containing arg/result path */
};
#endif	!defined(KERNEL) || VICE

#endif	_SYS_NAMEI_H_
