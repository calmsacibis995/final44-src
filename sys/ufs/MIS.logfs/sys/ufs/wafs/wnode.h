#ifdef CLFS
/*
 * CLFS
 * $Log: wnode.h,v $
 * Revision 1.7  1994/11/15  22:23:37  margo
 * Merge lastrec and lastlen into nextrec field.
 *
 * Revision 1.6  1994/10/04  17:03:12  margo
 * Make 4.4Lite version compile under BSD4.4-Lite.
 *
 * Revision 1.2  1994/09/26  18:52:08  jat
 * Initial WAFS checkin.
 *
 */
#endif
/*
 * Copyright (c) 1982, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1994
 *	The President and Fellows of Harvard University.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$Id: wnode.h,v 1.7 1994/11/15 22:23:37 margo Exp $
 */
#ifndef WNODE_H
#define WNODE_H

/*
 * WAFS log record types.
 */
typedef u_long wafs_type;
typedef	struct timeval	wafs_page_header_t;

struct wafs_header {
	wafs_type	rectype;
	size_t		length;
};

/* The wnode is used to maintain in-memory information about the log. */
struct wnode {
	struct wafs *w_fs;	/* associated file system */
	struct vnode *w_vnode;	/* Vnode */
	off_t	w_lastlsn;	/* last byte written in the log */
				/* The next two fields provide read hints */
	off_t	w_nextrec;	/* offset of the beginning of the next record */
	wafs_type w_type;	/* Type of last record read */
	ino_t	w_ino;		/* inode number */
	off_t	w_head;		/* head of log; place where you write */
	off_t	w_tail;		/* tail of log; oldest live record */
	u_long	w_flag;		/* see below */
	struct	vnode *w_devvp;	/* vnode for block I/O */
	struct	timespec w_atime;	/* Access time */
	struct	timespec w_mtime;	/* Modify time */
	struct	timespec w_ctime;	/* Change time */
	pid_t	w_lockholder;	/* Holding wnode locked */
	pid_t	w_lockwaiter;	/* Waiting on wnode */
	dev_t	w_dev;		/* device where wnode resides */
#ifdef AIX
	int	w_event;	/* for sleep/wakeup */
#endif
};

/*
 * Wnode flag values.
 */
#define	WSYNC	0x1	/* Performing log write */
#define WCHECK	0x2	/* Performing log checkpoint */
#define	WLOCKED	0x4	/* Locking wnode */
#define	WWANT	0x8	/* Waiting on lock */

/*
 * ROOTINO equivalent
 */
#define MASTERLOG 2 /* Used to access "file" containing log */
/*
 * Macros to translate between vnodes and wnodes.
 */
#define	VTOW(vp)	((struct wnode *)(vp)->v_data)
#define	WTOV(wp)	(wp->w_vnode)


#define WAFS_RECTYPE	0x00000111
#define IS_RECTYPE(N)	((N) | WAFS_RECTYPE == WAFS_RECTYPE)

#define	WAFS_NORECORD	0x0
#define	WAFS_RECORD	0x1
#define WAFS_BEGINREC	0x2
#define WAFS_ENDREC	0x3
#define WAFS_CONTINUE	0x4
#define	WAFS_COMMIT	0x5
#define	WAFS_CHECKPOINT	0x6

/*
 * logical_to_physical:  This is the actual computation to derive a physical
 * block number from a WAFS logical block number.  It is used by both bmap
 * and dumpwafs. 
 *	interval_blocks = (WFSP)->wafs_interval << (WFSP)->wafs_sbshift;
 *	boff = (LBN) % (WFSP)->wafs_dsize;
 *	blocks_to_skip = (boff >> interval_shift) + 1 << (WFSP)->wafs_sbshift;
 *	physical = boff + blocks_to_skip + dbtofsb(WFSP, SBLOCK);
 *
 */
#define WAFS_BLOCK_OFF(WFSP, LBN)	((LBN) % (WFSP)->wafs_dsize)

#define	WAFS_INTERVAL_SHIFT(WFSP) \
	((WFSP)->wafs_int_shift + (WFSP)->wafs_sbshift)

#define	WAFS_BLOCKS_SKIP(WFSP, LBN) \
	((WAFS_BLOCK_OFF(WFSP, LBN) >> WAFS_INTERVAL_SHIFT(WFSP)) + 1 \
	<< (WFSP)->wafs_sbshift) \

#define	logical_to_physical(WFSP, LBN) \
	(WAFS_BLOCK_OFF(WFSP, LBN) + WAFS_BLOCKS_SKIP (WFSP, LBN) \
	+ dbtofsb(WFSP, SBLOCK))

#endif
