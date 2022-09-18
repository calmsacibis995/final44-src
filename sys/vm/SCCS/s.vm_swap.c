h61305
s 00007/00001/00394
d D 8.5 94/02/17 09:24:04 hibler 79 78
c return more informative errors, fix a typo in swstrategy (from cgd)
e
s 00002/00002/00393
d D 8.4 94/01/06 22:47:34 mckusick 78 77
c have to init b_vnbufs to NOLIST
e
s 00002/00002/00393
d D 8.3 93/12/30 16:01:16 mckusick 77 76
c convert to use new queue structures
e
s 00146/00005/00249
d D 8.2 93/11/14 13:50:48 hibler 76 75
c support for sequential swap devices (SEQSWAP ifdef)
e
s 00002/00002/00252
d D 8.1 93/07/15 16:59:07 bostic 75 74
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00246
d D 7.30 93/07/15 16:24:22 hibler 74 72
c print a warning if no swap space found, don't use the first CLBYTES 
c of the first swap device
e
s 00002/00002/00250
d R 8.1 93/07/06 13:58:02 bostic 73 72
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00248
d D 7.29 93/07/06 13:57:25 mckusick 72 70
c waste less of the swap map (from Hibler)
e
s 00002/00002/00249
d R 8.1 93/06/11 16:38:39 bostic 71 70
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00004/00244
d D 7.28 93/04/19 18:12:18 torek 70 69
c terminate swap list with NODEV, not 0 (0 is a valid device);
c handle NFS swap
e
s 00002/00000/00246
d D 7.27 92/10/22 13:56:54 hibler 69 68
c have to explicitly set vnode pointer to NOLIST
e
s 00003/00003/00243
d D 7.26 92/10/02 00:21:00 mckusick 68 67
c av_forw/av_back are gone; now use b_actf/b_actb for linking active buffers
e
s 00002/00001/00244
d D 7.25 92/07/12 16:19:54 pendry 67 66
c new include location for specdev.h
e
s 00004/00003/00241
d D 7.24 92/07/10 19:11:45 torek 66 65
c ANSIfy syscall args
e
s 00000/00002/00244
d D 7.23 92/07/03 00:49:36 mckusick 65 64
c delete USES
e
s 00002/00000/00244
d D 7.22 92/05/14 17:24:25 heideman 64 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 16:58:15 heideman 63 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 16:40:46 heideman 62 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 16:30:43 heideman 61 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 15:47:19 heideman 60 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 15:36:49 heideman 59 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 14:42:57 heideman 58 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 12:45:13 heideman 57 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 11:42:15 heideman 56 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/14 10:23:13 heideman 55 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/13 23:00:59 heideman 54 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/13 18:49:38 heideman 53 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/13 18:21:21 heideman 52 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/13 18:11:00 heideman 51 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/13 17:55:37 heideman 50 48
c vnode interface conversion
e
s 00002/00000/00244
d R 7.22 92/05/13 17:54:13 heideman 49 48
c vnode interface conversion
e
s 00006/00002/00238
d D 7.21 92/05/11 17:47:22 mckusick 48 47
c initialize swpa buffers to use proc0 credential (from Leres)
e
s 00015/00011/00225
d D 7.20 92/05/04 17:22:29 bostic 47 46
c new include format; lint
e
s 00003/00007/00233
d D 7.19 92/02/03 23:33:24 mckusick 46 45
c new namei calling convention
e
s 00002/00000/00238
d D 7.18 91/05/06 13:06:06 karels 45 44
c define nswdev, nswap
e
s 00001/00001/00237
d D 7.17 91/04/16 00:22:23 mckusick 44 43
c add proc pointers to appropriate VOP operations
e
s 00061/00008/00177
d D 7.16 91/04/12 18:13:07 karels 43 42
c mv swapinit from main, rm user.h, new proc struct
e
s 00000/00012/00185
d D 7.15 90/12/05 17:55:14 mckusick 42 41
c formerly vm_sw.c; update for new VM
e
s 00001/00011/00196
d D 7.14 90/06/28 21:29:10 bostic 41 40
c new copyright notice
e
s 00009/00009/00198
d D 7.13 90/06/28 17:12:23 karels 40 39
c RETURN => return, remove syscontext.h
e
s 00021/00020/00186
d D 7.12 90/06/21 17:53:50 mckusick 39 37
c new system call convention
e
s 00020/00019/00187
d R 7.12 90/06/21 17:51:30 mckusick 38 37
c new system call convention
e
s 00001/00000/00205
d D 7.11 90/03/27 19:00:11 mckusick 37 36
c break specinfo structure out of vnode.h into specdev.h
e
s 00010/00007/00195
d D 7.10 90/01/13 15:14:50 mckusick 36 35
c have to account for rawread (that does not use a b_vp)
e
s 00010/00003/00192
d D 7.9 90/01/04 22:19:19 mckusick 35 34
c account for I/O's in progress
e
s 00001/00001/00194
d D 7.8 89/12/30 22:23:12 mckusick 34 33
c VREF => VHOLD as buffers hold holdcnts not usecounts
e
s 00005/00000/00190
d D 7.7 89/10/15 21:42:05 mckusick 33 32
c sanity check for unswapon'ed swpa partitions (from Macklem)
e
s 00002/00002/00188
d D 7.6 89/06/27 19:27:03 mckusick 32 31
c update reference counts on vnodes using VREF
e
s 00042/00020/00148
d D 7.5 89/05/09 17:03:37 mckusick 31 30
c merge in vnodes
e
s 00001/00001/00167
d D 7.4 89/04/26 19:21:45 mckusick 30 29
c use new form of suser()
e
s 00000/00017/00168
d D 7.3 88/05/06 17:14:49 bostic 29 28
c remove sw{read,write} for raw{read,write} changes
e
s 00029/00015/00156
d D 7.2 87/04/02 15:49:40 karels 28 26
c working with pack labels
e
s 00044/00015/00156
d D 7.1.1.1 87/04/02 15:41:35 karels 27 26
c add ifdefs for dev_bsize (almost working)
e
s 00001/00001/00170
d D 7.1 86/06/05 00:21:18 mckusick 26 25
c 4.3BSD release version
e
s 00007/00001/00164
d D 6.6 85/06/08 15:17:29 mckusick 25 24
c Add copyright
e
s 00002/00000/00163
d D 6.5 85/05/22 20:07:19 mckusick 24 23
c only allow the super-user to do swapon()
e
s 00002/00006/00161
d D 6.4 85/01/29 16:26:47 bloom 23 22
c check if swapping on default device so swapon won't complain
e
s 00010/00010/00157
d D 6.3 84/08/29 20:30:33 bloom 22 21
c Change to includes.  no more ../h
e
s 00006/00003/00161
d D 6.2 84/07/08 16:17:58 mckusick 21 20
c rework `namei' interface to eliminate global variables
e
s 00000/00000/00164
d D 6.1 83/07/29 06:53:06 sam 20 19
c 4.2 distribution
e
s 00024/00011/00140
d D 4.18 83/05/18 01:58:31 sam 19 18
c changes from sun to do swapping on variable sized devices
e
s 00004/00001/00147
d D 4.17 83/05/10 15:18:36 sam 18 17
c swapon, swapoff, and unmount aren't going to be implemented, 
c so purge the hooks from the system
e
s 00001/00001/00147
d D 4.16 83/02/13 11:18:09 sam 17 16
c increase size of mini root so there's space to build floppy/cassette
e
s 00002/00001/00146
d D 4.15 82/11/13 22:55:08 sam 16 15
c merge of 4.1b and 4.1c
e
s 00002/00001/00145
d D 4.14 82/11/02 11:49:29 root 15 14
c typo
e
s 00006/00003/00140
d D 4.13 82/10/31 13:49:57 root 14 13
c fixes from 68k
e
s 00002/00002/00141
d D 4.12 82/10/22 01:15:12 root 13 12
c lint
e
s 00003/00002/00140
d D 4.11 82/10/21 23:54:47 root 12 11
c lint
e
s 00001/00001/00141
d D 4.10 82/10/21 21:00:44 root 11 10
c lint
e
s 00001/00001/00141
d D 4.9 82/09/06 22:58:51 root 10 9
c 
e
s 00009/00004/00133
d D 4.8 82/08/22 21:14:17 root 9 8
c uio'd
e
s 00011/00000/00126
d D 4.7 82/07/15 20:39:28 root 8 7
c add mini root for new bootstrap style
e
s 00001/00001/00125
d D 4.6 82/06/25 21:31:22 wnj 7 6
c remove spurious i_un.
e
s 00001/00001/00125
d D 4.5 82/03/12 15:53:11 sam 6 5
c missing arg to nami
e
s 00001/00001/00125
d D 4.4 81/03/09 01:54:16 wnj 5 4
c %G% -> %E%
e
s 00009/00003/00117
d D 4.3 81/02/28 17:37:16 wnj 4 3
c rmalloc and related stuff
e
s 00000/00004/00120
d D 4.2 80/11/09 22:56:05 bill 3 2
c minor lint
e
s 00000/00000/00124
d D 4.1 80/11/09 16:54:00 bill 2 1
c stamp for 4bsd
e
s 00124/00000/00000
d D 3.1 80/10/12 22:05:40 bill 1 0
c date and time created 80/10/12 22:05:40 by bill
e
u
U
f b 
t
T
I 1
D 5
/*	%M%	%I%	%G%	*/
E 5
I 5
D 25
/*	%M%	%I%	%E%	*/
E 25
I 25
/*
D 26
 * Copyright (c) 1982 Regents of the University of California.
E 26
I 26
D 31
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 26
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 31
I 31
D 75
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 75
I 75
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 75
E 31
 *
I 31
D 41
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
E 41
I 41
 * %sccs.include.redist.c%
E 41
 *
E 31
 *	%W% (Berkeley) %G%
 */
E 25
E 5

D 22
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/buf.h"
#include "../h/conf.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
#include "../h/map.h"
I 9
#include "../h/uio.h"
I 15
#include "../h/file.h"
E 22
I 22
D 47
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "conf.h"
D 31
#include "dir.h"
E 31
D 39
#include "user.h"
E 39
I 39
D 40
#include "syscontext.h"
E 40
I 40
D 43
#include "user.h"
E 43
I 43
#include "proc.h"
#include "namei.h"
#include "dmap.h"		/* XXX */
E 43
E 40
E 39
D 31
#include "inode.h"
E 31
I 31
#include "vnode.h"
I 37
#include "specdev.h"
E 37
E 31
#include "map.h"
D 31
#include "uio.h"
E 31
#include "file.h"
E 47
I 47
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/namei.h>
#include <sys/dmap.h>		/* XXX */
#include <sys/vnode.h>
D 67
#include <sys/specdev.h>
E 67
#include <sys/map.h>
#include <sys/file.h>
I 67

#include <miscfs/specfs/specdev.h>
E 67
E 47
I 28
D 31
#include "stat.h"
E 31
E 28
I 27
#include "stat.h"
E 27
E 22
I 16
D 21
#include "../h/nami.h"
E 21
E 16
E 15
E 9

D 29
struct	buf rswbuf;
E 29
/*
 * Indirect driver for multi-controller paging.
 */
I 43

I 45
int	nswap, nswdev;
I 76
#ifdef SEQSWAP
int	niswdev;		/* number of interleaved swap devices */
int	niswap;			/* size of interleaved swap area */
#endif
E 76

E 45
/*
 * Set up swap devices.
 * Initialize linked list of free swap
 * headers. These do not actually point
 * to buffers, but rather to pages that
 * are being swapped in and out.
 */
I 47
void
E 47
swapinit()
{
	register int i;
	register struct buf *sp = swbuf;
I 48
	register struct proc *p = &proc0;	/* XXX */
E 48
	struct swdevt *swp;
	int error;

	/*
	 * Count swap devices, and adjust total swap space available.
D 76
	 * Some of this space will not be available until a swapon()
	 * system is issued, usually when the system goes multi-user.
E 76
I 76
	 * Some of the space will not be countable until later (dynamically
	 * configurable devices) and some of the counted space will not be
	 * available until a swapon() system call is issued, both usually
	 * happen when the system goes multi-user.
E 76
I 70
	 *
	 * If using NFS for swap, swdevt[0] will already be bdevvp'd.	XXX
E 70
	 */
I 76
#ifdef SEQSWAP
	nswdev = niswdev = 0;
	nswap = niswap = 0;
	/*
	 * All interleaved devices must come first
	 */
	for (swp = swdevt; swp->sw_dev != NODEV || swp->sw_vp != NULL; swp++) {
		if (swp->sw_flags & SW_SEQUENTIAL)
			break;
		niswdev++;
		if (swp->sw_nblks > niswap)
			niswap = swp->sw_nblks;
	}
	niswap = roundup(niswap, dmmax);
	niswap *= niswdev;
	if (swdevt[0].sw_vp == NULL &&
	    bdevvp(swdevt[0].sw_dev, &swdevt[0].sw_vp))
		panic("swapvp");
	/*
	 * The remainder must be sequential
	 */
	for ( ; swp->sw_dev != NODEV; swp++) {
		if ((swp->sw_flags & SW_SEQUENTIAL) == 0)
			panic("binit: mis-ordered swap devices");
		nswdev++;
		if (swp->sw_nblks > 0) {
			if (swp->sw_nblks % dmmax)
				swp->sw_nblks -= (swp->sw_nblks % dmmax);
			nswap += swp->sw_nblks;
		}
	}
	nswdev += niswdev;
	if (nswdev == 0)
		panic("swapinit");
	nswap += niswap;
#else
E 76
	nswdev = 0;
	nswap = 0;
D 70
	for (swp = swdevt; swp->sw_dev; swp++) {
E 70
I 70
	for (swp = swdevt; swp->sw_dev != NODEV || swp->sw_vp != NULL; swp++) {
E 70
		nswdev++;
		if (swp->sw_nblks > nswap)
			nswap = swp->sw_nblks;
	}
	if (nswdev == 0)
		panic("swapinit");
	if (nswdev > 1)
		nswap = ((nswap + dmmax - 1) / dmmax) * dmmax;
	nswap *= nswdev;
D 70
	if (bdevvp(swdevt[0].sw_dev, &swdevt[0].sw_vp))
E 70
I 70
	if (swdevt[0].sw_vp == NULL &&
	    bdevvp(swdevt[0].sw_dev, &swdevt[0].sw_vp))
E 70
		panic("swapvp");
I 76
#endif
E 76
D 48
	if (error = swfree(&proc0, 0)) {
E 48
I 48
D 74
	if (error = swfree(p, 0)) {
E 74
I 74
	if (nswap == 0)
		printf("WARNING: no swap space found\n");
	else if (error = swfree(p, 0)) {
E 74
E 48
		printf("swfree errno %d\n", error);	/* XXX */
		panic("swapinit swfree 0");
	}

	/*
	 * Now set up swap buffer headers.
	 */
D 68
	bswlist.av_forw = sp;
E 68
I 68
	bswlist.b_actf = sp;
E 68
D 48
	for (i = 0; i < nswbuf - 1; i++, sp++)
E 48
I 48
	for (i = 0; i < nswbuf - 1; i++, sp++) {
E 48
D 68
		sp->av_forw = sp + 1;
E 68
I 68
		sp->b_actf = sp + 1;
E 68
I 48
		sp->b_rcred = sp->b_wcred = p->p_ucred;
I 69
D 77
		sp->b_vnbufs.qe_next = NOLIST;
E 77
I 77
D 78
		sp->b_vnbufs.le_next = NULL;
E 78
I 78
		sp->b_vnbufs.le_next = NOLIST;
E 78
E 77
E 69
	}
	sp->b_rcred = sp->b_wcred = p->p_ucred;
I 69
D 77
	sp->b_vnbufs.qe_next = NOLIST;
E 77
I 77
D 78
	sp->b_vnbufs.le_next = NULL;
E 78
I 78
	sp->b_vnbufs.le_next = NOLIST;
E 78
E 77
E 69
E 48
D 68
	sp->av_forw = NULL;
E 68
I 68
	sp->b_actf = NULL;
E 68
}

I 47
void
E 47
E 43
swstrategy(bp)
	register struct buf *bp;
{
I 64
D 65
	USES_VOP_STRATEGY;
E 65
E 64
D 27
D 28
	int sz, off, seg;
	dev_t dev;
E 28
I 28
	int sz, off, seg, index;
	register struct swdevt *sp;
I 36
	struct vnode *vp;
E 36
E 28
E 27
I 27
	int sz, off, seg, index;
	register struct swdevt *sp;
E 27

I 8
#ifdef GENERIC
	/*
	 * A mini-root gets copied into the front of the swap
	 * and we run over top of the swap area just long
	 * enough for us to do a mkfs and restor of the real
	 * root (sure beats rewriting standalone restor).
	 */
D 17
#define	MINIROOTSIZE	2048
E 17
I 17
#define	MINIROOTSIZE	4096
E 17
	if (rootdev == dumpdev)
		bp->b_blkno += MINIROOTSIZE;
#endif
E 8
D 14
	sz = (bp->b_bcount+511)/512;
E 14
I 14
D 15
	sz = howmany(bp->b_bocunt, DEV_BSIZE);
E 15
I 15
	sz = howmany(bp->b_bcount, DEV_BSIZE);
E 15
E 14
D 19
	off = bp->b_blkno % DMMAX;
	if (bp->b_blkno+sz > nswap || off+sz > DMMAX) {
E 19
I 19
D 43
	if (bp->b_blkno+sz > nswap) {
E 43
I 43
	if (bp->b_blkno + sz > nswap) {
I 79
		bp->b_error = EINVAL;
E 79
E 43
E 19
		bp->b_flags |= B_ERROR;
D 27
D 28
		iodone(bp);
E 28
I 28
		biodone(bp);
E 28
E 27
I 27
		biodone(bp);
E 27
		return;
	}
D 19
	seg = bp->b_blkno / DMMAX;
	dev = swdevt[seg % nswdev].sw_dev;
	seg /= nswdev;
	bp->b_blkno = seg*DMMAX + off;
E 19
I 19
	if (nswdev > 1) {
I 76
#ifdef SEQSWAP
		if (bp->b_blkno < niswap) {
			if (niswdev > 1) {
				off = bp->b_blkno % dmmax;
				if (off+sz > dmmax) {
I 79
					bp->b_error = EINVAL;
E 79
					bp->b_flags |= B_ERROR;
					biodone(bp);
					return;
				}
				seg = bp->b_blkno / dmmax;
				index = seg % niswdev;
				seg /= niswdev;
				bp->b_blkno = seg*dmmax + off;
			} else
				index = 0;
		} else {
			register struct swdevt *swp;

			bp->b_blkno -= niswap;
			for (index = niswdev, swp = &swdevt[niswdev];
			     swp->sw_dev != NODEV;
			     swp++, index++) {
				if (bp->b_blkno < swp->sw_nblks)
					break;
				bp->b_blkno -= swp->sw_nblks;
			}
			if (swp->sw_dev == NODEV ||
			    bp->b_blkno+sz > swp->sw_nblks) {
I 79
				bp->b_error = swp->sw_dev == NODEV ?
					ENODEV : EINVAL;
E 79
				bp->b_flags |= B_ERROR;
				biodone(bp);
				return;
			}
		}
#else
E 76
		off = bp->b_blkno % dmmax;
		if (off+sz > dmmax) {
I 79
			bp->b_error = EINVAL;
E 79
			bp->b_flags |= B_ERROR;
D 27
D 28
			iodone(bp);
E 28
I 28
			biodone(bp);
E 28
E 27
I 27
			biodone(bp);
E 27
			return;
		}
		seg = bp->b_blkno / dmmax;
D 27
D 28
		dev = swdevt[seg % nswdev].sw_dev;
E 28
I 28
		index = seg % nswdev;
E 28
E 27
I 27
		index = seg % nswdev;
E 27
		seg /= nswdev;
		bp->b_blkno = seg*dmmax + off;
I 76
#endif
E 76
	} else
D 27
D 28
		dev = swdevt[0].sw_dev;
E 19
	bp->b_dev = dev;
	if (dev == 0)
E 28
I 28
		index = 0;
	sp = &swdevt[index];
D 36
	bp->b_dev = sp->sw_dev;
D 35
	if (bp->b_dev == 0)
E 35
I 35
	if (bp->b_vp == NULL || bp->b_dev == 0)
E 36
I 36
D 70
	if ((bp->b_dev = sp->sw_dev) == 0)
E 70
I 70
	if ((bp->b_dev = sp->sw_dev) == NODEV)
E 70
E 36
E 35
E 28
E 27
I 27
		index = 0;
	sp = &swdevt[index];
#ifdef SECSIZE
	bp->b_blkno <<= sp->sw_bshift;
	bp->b_blksize = sp->sw_blksize;
#endif SECSIZE
	bp->b_dev = sp->sw_dev;
	if (bp->b_dev == 0)
E 27
		panic("swstrategy");
D 27
D 28
	(*bdevsw[major(dev)].d_strategy)(bp);
E 28
I 28
D 31
	(*bdevsw[major(bp->b_dev)].d_strategy)(bp);
E 31
I 31
D 35
	if (bp->b_vp)
		brelvp(bp);
E 35
I 33
	if (sp->sw_vp == NULL) {
D 79
		bp->b_error |= B_ERROR;
E 79
I 79
		bp->b_error = ENODEV;
		bp->b_flags |= B_ERROR;
E 79
		biodone(bp);
		return;
	}
E 33
D 32
	sp->sw_vp->v_count++;
E 32
I 32
D 34
	VREF(sp->sw_vp);
E 34
I 34
	VHOLD(sp->sw_vp);
I 35
	if ((bp->b_flags & B_READ) == 0) {
D 36
		bp->b_vp->v_numoutput--;
		if ((bp->b_vp->v_flag & VBWAIT) && bp->b_vp->v_numoutput <= 0) {
			bp->b_vp->v_flag &= ~VBWAIT;
			wakeup((caddr_t)&bp->b_vp->v_numoutput);
E 36
I 36
		if (vp = bp->b_vp) {
			vp->v_numoutput--;
			if ((vp->v_flag & VBWAIT) && vp->v_numoutput <= 0) {
				vp->v_flag &= ~VBWAIT;
				wakeup((caddr_t)&vp->v_numoutput);
			}
E 36
		}
		sp->sw_vp->v_numoutput++;
	}
D 36
	brelvp(bp);
E 36
I 36
	if (bp->b_vp != NULL)
		brelvp(bp);
E 36
E 35
E 34
E 32
	bp->b_vp = sp->sw_vp;
	VOP_STRATEGY(bp);
E 31
E 28
E 27
I 27
	(*bdevsw[major(bp->b_dev)].d_strategy)(bp);
E 27
D 29
}

D 9
swread(dev)
E 9
I 9
swread(dev, uio)
	dev_t dev;
	struct uio *uio;
E 9
{

D 9
	physio(swstrategy, &rswbuf, dev, B_READ, minphys);
E 9
I 9
D 13
	physio(swstrategy, &rswbuf, dev, B_READ, minphys, uio);
E 13
I 13
	return (physio(swstrategy, &rswbuf, dev, B_READ, minphys, uio));
E 13
E 9
}

D 9
swwrite(dev)
E 9
I 9
swwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
E 9
{

D 9
	physio(swstrategy, &rswbuf, dev, B_WRITE, minphys);
E 9
I 9
D 13
	physio(swstrategy, &rswbuf, dev, B_WRITE, minphys, uio);
E 13
I 13
	return (physio(swstrategy, &rswbuf, dev, B_WRITE, minphys, uio));
E 29
E 13
E 9
}

/*
 * System call swapon(name) enables swapping on device name,
 * which must be in the swdevsw.  Return EBUSY
 * if already swapping on this device.
 */
I 66
struct swapon_args {
	char	*name;
};
E 66
D 10
vswapon()
E 10
I 10
D 18
oswapon()
E 18
I 18
D 39
swapon()
E 18
E 10
{
I 18
	struct a {
E 39
I 39
/* ARGSUSED */
I 47
int
E 47
swapon(p, uap, retval)
	struct proc *p;
D 66
	struct args {
E 39
		char	*name;
D 21
	};
E 21
I 21
D 39
	} *uap = (struct a *)u.u_ap;
E 39
I 39
	} *uap;
E 66
I 66
	struct swapon_args *uap;
E 66
	int *retval;
{
E 39
E 21
E 18
D 3
	register struct a {
		char	*sname;
	} *uap;
E 3
D 31
	register struct inode *ip;
E 31
I 31
	register struct vnode *vp;
E 31
D 39
	dev_t dev;
E 39
	register struct swdevt *sp;
I 21
D 43
	register struct nameidata *ndp = &u.u_nd;
E 43
I 43
D 46
	register struct nameidata *ndp;
E 46
E 43
I 39
	dev_t dev;
	int error;
I 43
	struct nameidata nd;
E 43
E 39
E 21

I 24
D 30
	if (!suser())
E 30
I 30
D 39
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 30
		return;
E 39
I 39
D 43
	if (error = suser(u.u_cred, &u.u_acflag))
E 43
I 43
	if (error = suser(p->p_ucred, &p->p_acflag))
E 43
D 40
		RETURN (error);
E 40
I 40
		return (error);
I 43
D 46
	ndp = &nd;
E 43
E 40
E 39
E 24
D 3
	uap = (struct a *)u.u_ap;
E 3
D 6
	ip = namei(uchar, 0);
E 6
I 6
D 16
	ip = namei(uchar, 0, 1);
E 16
I 16
D 21
	ip = namei(uchar, LOOKUP, 1);
E 21
I 21
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
D 31
	ip = namei(ndp);
E 21
E 16
E 6
	if (ip == NULL)
E 31
I 31
D 39
	if (u.u_error = namei(ndp))
E 31
		return;
E 39
I 39
D 43
	if (error = namei(ndp))
E 43
I 43
	if (error = namei(ndp, p))
E 46
I 46
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->name, p);
	if (error = namei(&nd))
E 46
E 43
D 40
		RETURN (error);
E 40
I 40
		return (error);
E 40
E 39
D 31
	if ((ip->i_mode&IFMT) != IFBLK) {
E 31
I 31
D 46
	vp = ndp->ni_vp;
E 46
I 46
	vp = nd.ni_vp;
E 46
	if (vp->v_type != VBLK) {
		vrele(vp);
E 31
D 39
		u.u_error = ENOTBLK;
D 31
		iput(ip);
E 31
		return;
E 39
I 39
D 40
		RETURN (ENOTBLK);
E 40
I 40
		return (ENOTBLK);
E 40
E 39
	}
D 7
	dev = (dev_t)ip->i_un.i_rdev;
E 7
I 7
D 31
	dev = (dev_t)ip->i_rdev;
E 7
	iput(ip);
E 31
I 31
	dev = (dev_t)vp->v_rdev;
E 31
	if (major(dev) >= nblkdev) {
I 31
		vrele(vp);
E 31
D 39
		u.u_error = ENXIO;
		return;
E 39
I 39
D 40
		RETURN (ENXIO);
E 40
I 40
		return (ENXIO);
E 40
E 39
	}
D 23
	/*
	 * Search starting at second table entry,
	 * since first (primary swap area) is freed at boot.
	 */
	for (sp = &swdevt[1]; sp->sw_dev; sp++)
E 23
I 23
D 70
	for (sp = &swdevt[0]; sp->sw_dev; sp++)
E 70
I 70
D 76
	for (sp = &swdevt[0]; sp->sw_dev != NODEV; sp++)
E 76
I 76
	for (sp = &swdevt[0]; sp->sw_dev != NODEV; sp++) {
E 76
E 70
E 23
		if (sp->sw_dev == dev) {
D 76
			if (sp->sw_freed) {
E 76
I 76
			if (sp->sw_flags & SW_FREED) {
E 76
I 31
				vrele(vp);
E 31
D 39
				u.u_error = EBUSY;
				return;
E 39
I 39
D 40
				RETURN (EBUSY);
E 40
I 40
				return (EBUSY);
E 40
E 39
			}
D 27
D 28
			swfree(sp - swdevt);
E 28
I 28
D 31
			u.u_error = swfree(sp - swdevt);
E 31
I 31
			sp->sw_vp = vp;
D 39
			if (u.u_error = swfree(sp - swdevt)) {
E 39
I 39
D 43
			if (error = swfree(sp - swdevt)) {
E 43
I 43
			if (error = swfree(p, sp - swdevt)) {
E 43
E 39
				vrele(vp);
D 39
				return;
E 39
I 39
D 40
				RETURN (error);
E 40
I 40
				return (error);
E 40
E 39
			}
E 31
E 28
E 27
I 27
			u.u_error = swfree(sp - swdevt);
E 27
D 39
			return;
E 39
I 39
D 40
			RETURN (0);
E 40
I 40
			return (0);
E 40
E 39
		}
I 76
#ifdef SEQSWAP
		/*
		 * If we have reached a non-freed sequential device without
		 * finding what we are looking for, it is an error.
		 * That is because all interleaved devices must come first
		 * and sequential devices must be freed in order.
		 */
		if ((sp->sw_flags & (SW_SEQUENTIAL|SW_FREED)) == SW_SEQUENTIAL)
			break;
#endif
	}
E 76
I 31
	vrele(vp);
E 31
D 23
	u.u_error = ENODEV;
E 23
I 23
D 39
	u.u_error = EINVAL;
E 39
I 39
D 40
	RETURN (EINVAL);
E 40
I 40
	return (EINVAL);
E 40
E 39
E 23
}

I 27
#ifdef SECSIZE
long	argdbsize;		/* XXX */

#endif SECSIZE
E 27
/*
 * Swfree(index) frees the index'th portion of the swap map.
 * Each of the nswdev devices provides 1/nswdev'th of the swap
D 19
 * space, which is laid out with blocks of DMMAX pages circularly
E 19
I 19
 * space, which is laid out with blocks of dmmax pages circularly
E 19
 * among the devices.
 */
I 47
int
E 47
D 43
swfree(index)
E 43
I 43
swfree(p, index)
	struct proc *p;
E 43
	int index;
{
I 64
D 65
	USES_VOP_OPEN;
E 65
E 64
I 28
	register struct swdevt *sp;
E 28
I 27
	register struct swdevt *sp;
E 27
	register swblk_t vsbase;
D 11
	register int blk;
E 11
I 11
	register long blk;
I 14
D 31
	dev_t dev;
E 31
I 31
	struct vnode *vp;
E 31
I 19
	register swblk_t dvbase;
	register int nblks;
I 28
	int error;
E 28
I 27
	int error;
E 27
E 19
E 14
E 11

I 14
D 27
D 28
	dev = swdevt[index].sw_dev;
	(*bdevsw[major(dev)].d_open)(dev, FREAD|FWRITE);
E 14
	swdevt[index].sw_freed = 1;
D 19
	for (vsbase = index*DMMAX; vsbase < nswap; vsbase += nswdev*DMMAX) {
		blk = nswap - vsbase;
		if (blk > DMMAX)
			blk = DMMAX;
E 19
I 19
	nblks = swdevt[index].sw_nblks;
E 28
I 28
	sp = &swdevt[index];
D 31
	dev = sp->sw_dev;
	if (error = (*bdevsw[major(dev)].d_open)(dev, FREAD|FWRITE, S_IFBLK))
E 31
I 31
	vp = sp->sw_vp;
D 43
	if (error = VOP_OPEN(vp, FREAD|FWRITE, u.u_cred))
E 43
I 43
D 44
	if (error = VOP_OPEN(vp, FREAD|FWRITE, p->p_ucred))
E 44
I 44
	if (error = VOP_OPEN(vp, FREAD|FWRITE, p->p_ucred, p))
E 44
E 43
E 31
		return (error);
D 76
	sp->sw_freed = 1;
E 76
I 76
	sp->sw_flags |= SW_FREED;
E 76
	nblks = sp->sw_nblks;
I 76
	/*
	 * Some devices may not exist til after boot time.
	 * If so, their nblk count will be 0.
	 */
	if (nblks <= 0) {
		int perdev;
		dev_t dev = sp->sw_dev;

		if (bdevsw[major(dev)].d_psize == 0 ||
		    (nblks = (*bdevsw[major(dev)].d_psize)(dev)) == -1) {
			(void) VOP_CLOSE(vp, FREAD|FWRITE, p->p_ucred, p);
			sp->sw_flags &= ~SW_FREED;
			return (ENXIO);
		}
#ifdef SEQSWAP
		if (index < niswdev) {
			perdev = niswap / niswdev;
			if (nblks > perdev)
				nblks = perdev;
		} else {
			if (nblks % dmmax)
				nblks -= (nblks % dmmax);
			nswap += nblks;
		}
#else
		perdev = nswap / nswdev;
		if (nblks > perdev)
			nblks = perdev;
#endif
		sp->sw_nblks = nblks;
	}
	if (nblks == 0) {
		(void) VOP_CLOSE(vp, FREAD|FWRITE, p->p_ucred, p);
		sp->sw_flags &= ~SW_FREED;
		return (0);	/* XXX error? */
	}
#ifdef SEQSWAP
	if (sp->sw_flags & SW_SEQUENTIAL) {
		register struct swdevt *swp;

		blk = niswap;
		for (swp = &swdevt[niswdev]; swp != sp; swp++)
			blk += swp->sw_nblks;
		rmfree(swapmap, nblks, blk);
		return (0);
	}
#endif
E 76
E 28
E 27
I 27
	sp = &swdevt[index];
	dev = sp->sw_dev;
	if (error = (*bdevsw[major(dev)].d_open)(dev, FREAD|FWRITE, S_IFBLK))
		return (error);
	sp->sw_freed = 1;
	nblks = sp->sw_nblks;
E 27
	for (dvbase = 0; dvbase < nblks; dvbase += dmmax) {
		blk = nblks - dvbase;
I 76
#ifdef SEQSWAP
		if ((vsbase = index*dmmax + dvbase*niswdev) >= niswap)
			panic("swfree");
#else
E 76
		if ((vsbase = index*dmmax + dvbase*nswdev) >= nswap)
			panic("swfree");
I 76
#endif
E 76
		if (blk > dmmax)
			blk = dmmax;
E 19
		if (vsbase == 0) {
			/*
D 42
			 * Can't free a block starting at 0 in the swapmap
D 4
			 * but need some space for argmap so use this
E 4
I 4
			 * but need some space for argmap so use 1/2 this
E 4
			 * hunk which needs special treatment anyways.
			 */
D 27
D 28
			argdev = swdevt[0].sw_dev;
E 28
I 28
			argdev = sp->sw_dev;
I 31
			if (argdev_vp)
				vrele(argdev_vp);
D 32
			vp->v_count++;
E 32
I 32
			VREF(vp);
E 32
			argdev_vp = vp;
E 31
E 28
E 27
I 27
			argdev = sp->sw_dev;
#ifdef SECSIZE
			argdbsize = sp->sw_blksize;
			rminit(argmap,
			   ((blk / 2) * DEV_BSIZE - CLBYTES) / argdbsize,
			   CLBYTES / argdbsize, "argmap", ARGMAPSIZE);
#else SECSIZE
E 27
D 4
			mfree(argmap, blk-CLSIZE, vsbase+CLSIZE);
E 4
I 4
D 12
			rminit(argmap, blk/2-CLSIZE, CLSIZE,
E 12
I 12
D 14
			rminit(argmap, (long)(blk/2-CLSIZE), (long)CLSIZE,
E 12
			    "argmap", ARGMAPSIZE);
E 14
I 14
			rminit(argmap, (long)(blk/2-ctod(CLSIZE)),
			    (long)ctod(CLSIZE), "argmap", ARGMAPSIZE);
I 27
#endif SECSIZE
E 27
E 14
			/*
E 42
D 72
			 * First of all chunks... initialize the swapmap
			 * the second half of the hunk.
E 72
I 72
D 74
			 * First of all chunks.
			 * Cannot free a zero-index block in a resource
			 * map so we waste the first block.
E 74
I 74
			 * First of all chunks... initialize the swapmap.
			 * Don't use the first cluster of the device
			 * in case it starts with a label or boot block.
E 74
E 72
			 */
D 12
			rminit(swapmap, blk/2, blk/2, "swap", nswapmap);
E 12
I 12
D 31
			rminit(swapmap, (long)blk/2, (long)blk/2,
E 31
I 31
D 72
			rminit(swapmap, (long)(blk/2), (long)(blk/2),
E 72
I 72
D 74
			rminit(swapmap, (long)(blk - 1), (long)1,
E 72
E 31
			    "swap", nswapmap);
E 74
I 74
			rminit(swapmap, blk - ctod(CLSIZE),
			    vsbase + ctod(CLSIZE), "swap", nswapmap);
E 74
I 28
		} else if (dvbase == 0) {
			/*
			 * Don't use the first cluster of the device
			 * in case it starts with a label or boot block.
			 */
			rmfree(swapmap, blk - ctod(CLSIZE),
			    vsbase + ctod(CLSIZE));
E 28
I 27
		} else if (dvbase == 0) {
			/*
			 * Don't use the first cluster of the device
			 * in case it starts with a label or boot block.
			 */
			rmfree(swapmap, blk - ctod(CLSIZE),
			    vsbase + ctod(CLSIZE));
E 27
E 12
E 4
		} else
D 4
			mfree(swapmap, blk, vsbase);
E 4
I 4
			rmfree(swapmap, blk, vsbase);
E 4
	}
I 28
	return (0);
E 28
I 27
	return (0);
E 27
}
E 1
