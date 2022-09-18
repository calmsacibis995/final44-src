h40123
s 00000/00025/00094
d D 8.3 94/08/20 17:10:56 mckusick 61 60
c process group hash tables are now dynamic
e
s 00005/00000/00114
d D 8.2 94/01/21 17:06:28 bostic 60 59
c add USL's copyright notice
e
s 00002/00002/00112
d D 8.1 93/06/16 16:38:44 bostic 59 58
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00113
d D 7.24 93/06/16 16:38:01 mckusick 58 56
c desiredvnodes is int, not long
e
s 00002/00002/00112
d R 8.1 93/06/10 21:15:52 bostic 57 56
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00013/00099
d D 7.23 92/10/11 08:45:36 bostic 56 55
c make kernel includes standard
e
s 00001/00001/00111
d D 7.22 92/07/12 17:09:24 torek 55 54
c smaller tickadj because we have better clocks these days
e
s 00001/00001/00111
d D 7.21 91/11/01 16:44:38 bostic 54 53
c ufs moved down a level
e
s 00009/00010/00103
d D 7.20 91/06/27 17:59:14 karels 53 52
c bump up NPROC, pushing up maxfiles (now both dynamically alloc'ed),
c but without letting other stuff increase as much; more text/vm_object cache
e
s 00001/00001/00112
d D 7.19 91/06/03 19:40:38 mckusick 52 51
c nfile => maxfiles (and default is doubled)
e
s 00000/00006/00113
d D 7.18 91/05/06 11:06:27 karels 51 50
c move copyright to init_main.c
e
s 00001/00003/00118
d D 7.17 91/04/20 16:33:23 karels 50 49
c proc array is gone; rm user.h
e
s 00013/00013/00108
d D 7.16 91/02/15 14:09:25 bostic 49 48
c kernel reorg (checked in by karels)
e
s 00001/00006/00120
d D 7.15 90/12/05 19:53:09 mckusick 48 47
c update for new VM
e
s 00001/00011/00125
d D 7.14 90/06/28 21:13:13 bostic 47 46
c new copyright notice
e
s 00001/00001/00135
d D 7.13 90/05/24 16:40:52 mckusick 46 45
c lint
e
s 00027/00002/00109
d D 7.12 90/05/10 17:22:58 mckusick 45 44
c fine tune NVNODES; merge in support for hp300 from Utah
e
s 00025/00000/00086
d D 7.11 90/05/10 16:54:54 karels 44 43
c proc hashing using pointers; variable size hash table
e
s 00000/00008/00086
d D 7.10 90/04/27 10:16:56 mckusick 43 42
c no more static quota tables
e
s 00001/00004/00093
d D 7.9 90/04/10 19:28:45 mckusick 42 41
c dynamic vnodes/name cache
e
s 00005/00011/00092
d D 7.8 89/10/24 18:32:47 mckusick 41 40
c merge inode and nfsnode tables into a single vnode table
e
s 00005/00000/00098
d D 7.7 89/07/01 19:02:18 mckusick 40 39
c add nnfsnode for NFS
e
s 00001/00000/00097
d D 7.6 89/05/29 12:11:35 mckusick 39 38
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00016/00005/00081
d D 7.5 89/05/09 21:02:41 mckusick 38 37
c new copyright; update include files
e
s 00015/00015/00071
d D 7.4 89/04/25 15:54:37 mckusick 37 36
c ../h => ../sys
e
s 00000/00005/00086
d D 7.3 86/12/06 22:34:53 sam 36 35
c no longer need tahoe bogosity
e
s 00007/00000/00084
d D 7.2 86/10/29 19:37:29 karels 35 34
c tahoe
e
s 00002/00002/00082
d D 7.1 86/06/05 01:47:10 mckusick 34 33
c 4.3BSD release version
e
s 00002/00003/00082
d D 6.13 86/02/23 23:36:19 karels 33 32
c add sccsid; rm unused
e
s 00004/00003/00081
d D 6.12 86/02/20 21:23:16 karels 32 31
c rename nch to avoid name conflict; slow rate of time skew when correcting
e
s 00001/00001/00083
d D 6.11 85/09/18 14:22:59 karels 31 29
c larger clists, so trim
e
s 00001/00001/00083
d R 6.11 85/06/25 13:21:07 karels 30 29
c decrease number of clists with larger clists
e
s 00011/00001/00073
d D 6.10 85/06/08 12:08:32 mckusick 29 28
c Add copyright
e
s 00001/00001/00073
d D 6.9 85/04/17 17:00:27 karels 28 27
c add a few text entries on the low end
e
s 00001/00000/00073
d D 6.8 84/12/20 15:46:18 karels 27 26
c tickadj (for adjtime)
e
s 00002/00002/00071
d D 6.7 84/08/23 16:22:33 mckusick 26 25
c insure that ndquot is at least as big as the inode table
e
s 00000/00001/00073
d D 6.6 84/07/08 15:35:54 sam 25 24
c ufs_nami.c -> ufs_namei.c and nami.h -> namei.h 
e
s 00003/00003/00071
d D 6.5 84/07/02 18:00:31 mckusick 24 23
c resize namei cache to cover the entire inode table
e
s 00002/00007/00072
d D 6.4 84/06/06 23:02:53 sam 23 22
c delete NETSLOP what with inetd
e
s 00003/00002/00076
d D 6.3 84/01/09 15:31:39 mckusick 22 20
c ninodes depends on the size of the namei() cache
e
s 00003/00002/00076
d R 6.3 84/01/09 15:26:15 mckusick 21 20
c ninodes depends on size of namei() cache
e
s 00003/00000/00075
d D 6.2 84/01/03 23:44:30 mckusick 20 19
c add system wide cacheing of path names in namei() (from kre)
e
s 00000/00000/00075
d D 6.1 83/07/29 07:41:23 sam 19 18
c 4.2 distribution
e
s 00007/00004/00068
d D 4.18 83/07/21 01:45:47 sam 18 17
c don't penalize others for our stupidity
e
s 00004/00002/00068
d D 4.17 83/07/21 01:33:14 sam 17 16
c up various tables to account for servers
e
s 00001/00001/00069
d D 4.16 82/11/15 10:16:05 sam 16 15
c temporary, until callout table is allocated at boot time
e
s 00002/00002/00068
d D 4.15 82/11/13 23:09:44 sam 15 14
c merge 4.1b and 4.1c
e
s 00004/00002/00066
d D 4.14 82/09/18 15:12:00 root 14 13
c add tick, drop dstflag
e
s 00009/00000/00059
d D 4.13 82/08/01 19:30:59 sam 13 12
c quota stuff
e
s 00001/00001/00058
d D 4.12 82/04/03 23:40:51 wnj 12 11
c much more generous NFILE
e
s 00001/00001/00058
d D 4.11 81/11/30 16:23:07 wnj 11 10
c lint
e
s 00000/00014/00059
d D 4.10 81/11/14 16:43:45 wnj 10 9
c before header overlay
e
s 00011/00012/00062
d D 4.9 81/11/08 16:56:29 wnj 9 8
c BBNNET->INET, contab XXX, 
e
s 00000/00001/00074
d D 4.8 81/11/07 11:09:42 wnj 8 7
c fixes per shannon
e
s 00004/00003/00071
d D 4.7 81/10/29 20:53:39 wnj 7 6
c s/bbnnet/inet/
e
s 00000/00003/00074
d D 4.6 81/10/29 18:10:32 wnj 6 5
c before inserting beauty header files
e
s 00001/00001/00076
d D 4.5 81/05/15 14:03:39 wnj 5 4
c adjusted NFILE formula
e
s 00020/00001/00057
d D 4.4 81/05/12 17:18:49 root 4 3
c add tcp/ip
e
s 00002/00000/00056
d D 4.3 81/04/28 02:55:11 root 3 2
c add nport
e
s 00001/00001/00055
d D 4.2 81/04/02 23:39:44 root 2 1
c more inodes!
e
s 00056/00000/00000
d D 4.1 81/03/09 01:52:15 wnj 1 0
c date and time created 81/03/09 01:52:15 by wnj
e
u
U
t
T
I 1
D 29
/*	%M%	%I%	%E%	*/
E 29
I 29
/*
D 34
 * Copyright (c) 1980 Regents of the University of California.
E 34
I 34
D 38
 * Copyright (c) 1980, 1986 Regents of the University of California.
E 34
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 38
I 38
D 59
 * Copyright (c) 1980, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 59
I 59
 * Copyright (c) 1980, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 60
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 60
E 59
E 38
I 33
 *
I 38
D 47
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
E 47
I 47
 * %sccs.include.redist.c%
E 47
 *
E 38
 *	%W% (Berkeley) %G%
E 33
 */

D 51
#ifndef lint
char copyright[] =
D 34
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 34
I 34
D 38
"%Z% Copyright (c) 1980, 1986 Regents of the University of California.\n\
E 38
I 38
"%Z% Copyright (c) 1980, 1986, 1989 Regents of the University of California.\n\
E 38
E 34
 All rights reserved.\n";
#endif not lint
E 29

E 51
D 37
#include "../h/param.h"
#include "../h/systm.h"
I 4
D 9
#ifdef BBNNET
D 7
#include "../bbnnet/net.h"
#include "../bbnnet/imp.h"
#include "../bbnnet/ucb.h"
E 7
I 7
#include "../inet/inet.h"
#include "../inet/inet_systm.h"
#include "../inet/imp.h"
E 9
I 9
D 10
#ifdef INET
#include "../net/inet.h"
#include "../net/inet_systm.h"
#include "../net/imp.h"
#endif INET
E 10
E 9
#include "../h/socket.h"
E 7
D 9
#endif BBNNET
E 9
E 4
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/text.h"
#include "../h/inode.h"
#include "../h/file.h"
#include "../h/callout.h"
#include "../h/clist.h"
#include "../h/cmap.h"
I 3
D 9
#include "../h/port.h"
E 9
I 9
#include "../h/mbuf.h"
I 20
D 25
#include "../h/nami.h"
E 25
E 20
I 13
#include "../h/quota.h"
I 14
#include "../h/kernel.h"
E 37
I 37
D 49
#include "../sys/param.h"
#include "../sys/systm.h"
#include "../sys/socket.h"
D 38
#include "../ufs/dir.h"
E 38
#include "../sys/user.h"
#include "../sys/proc.h"
D 48
#include "../sys/text.h"
E 48
I 38
#include "../sys/vnode.h"
E 38
D 41
#include "../ufs/inode.h"
E 41
#include "../sys/file.h"
#include "../sys/callout.h"
#include "../sys/clist.h"
D 48
#include "../sys/cmap.h"
E 48
#include "../sys/mbuf.h"
#include "../ufs/quota.h"
#include "../sys/kernel.h"
E 49
I 49
D 56
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/socket.h"
D 50
#include "sys/user.h"
E 50
#include "sys/proc.h"
#include "sys/vnode.h"
#include "sys/file.h"
#include "sys/callout.h"
#include "sys/clist.h"
#include "sys/mbuf.h"
D 54
#include "ufs/quota.h"
E 54
I 54
#include "ufs/ufs/quota.h"
E 54
#include "sys/kernel.h"
E 56
I 56
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/socket.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/callout.h>
#include <sys/clist.h>
#include <sys/mbuf.h>
#include <sys/kernel.h>

#include <ufs/ufs/quota.h>

E 56
E 49
I 45
#ifdef SYSVSHM
D 56
#include "machine/vmparam.h"
D 49
#include "../sys/shm.h"
E 49
I 49
#include "sys/shm.h"
E 56
I 56
#include <machine/vmparam.h>
#include <sys/shm.h>
E 56
E 49
#endif

E 45
E 37
E 14
E 13
E 9
E 3
/*
 * System parameter formulae.
 *
 * This file is copied into each directory where we compile
 * the kernel; it should be modified there to suit local taste
 * if necessary.
 *
 * Compiled with -DHZ=xx -DTIMEZONE=x -DDST=x -DMAXUSERS=xx
 */

I 35
#ifndef HZ
D 36
#ifdef VAX
E 36
E 35
I 14
#define	HZ 100
I 35
D 36
#endif
#ifdef TAHOE
#define	HZ 60
#endif
E 36
#endif
E 35
E 14
int	hz = HZ;
D 14
int	timezone = TIMEZONE;
int	dstflag = DST;
E 14
I 14
int	tick = 1000000 / HZ;
I 27
D 32
int	tickadj = 1000000 / HZ / 10;
E 32
I 32
D 55
int	tickadj = 240000 / (60 * HZ);		/* can adjust 240ms in 60s */
E 55
I 55
int	tickadj = 30000 / (60 * HZ);		/* can adjust 30ms in 60s */
E 55
E 32
E 27
struct	timezone tz = { TIMEZONE, DST };
E 14
D 53
#define	NPROC (20 + 8 * MAXUSERS)
E 53
I 53
#define	NPROC (20 + 16 * MAXUSERS)
E 53
D 50
int	nproc = NPROC;
E 50
I 50
int	maxproc = NPROC;
E 50
D 17
int	ntext = 24 + MAXUSERS;
E 17
I 17
D 18
/* the +20 here is for all the lousy server processes */
int	ntext = 24 + MAXUSERS + 20;
E 18
I 18
D 23
#ifdef INET
#define	NETSLOP	20			/* for all the lousy servers*/
#else
#define	NETSLOP	0
#endif
E 23
I 22
D 24
#define NCHSIZE (60 + 2 * MAXUSERS)
int	nchsize = NCHSIZE;
E 24
E 22
D 23
int	ntext = 24 + MAXUSERS + NETSLOP;
E 23
I 23
D 28
int	ntext = 24 + MAXUSERS;
E 28
I 28
D 45
int	ntext = 36 + MAXUSERS;
E 28
E 23
E 18
E 17
D 2
int	ninode = NPROC + 16 + MAXUSERS;
E 2
I 2
D 22
int	ninode = (NPROC + 16 + MAXUSERS) + 32;
E 22
I 22
D 24
int	ninode = (NPROC + 16 + MAXUSERS + (2 * NCHSIZE / 3)) + 32;
E 24
I 24
D 41
#define NINODE ((NPROC + 16 + MAXUSERS) + 32)
int	ninode = NINODE;
I 40
#ifndef NFS
E 40
int	nchsize = NINODE * 11 / 10;
I 40
#else
int	nnfsnode = NINODE;
int	nchsize = (2 * NINODE) * 11 / 10;
#endif /* NFS */
E 41
I 41
#define NVNODE ((NPROC + 16 + MAXUSERS) + 32)
E 45
I 45
D 48
#define	NTEXT (36 + MAXUSERS)
int	ntext = NTEXT;
E 48
I 48
D 53
#define NTEXT 100			/* actually the object cache */
E 48
#define NVNODE (NPROC + NTEXT + 300)
E 53
I 53
#define	NTEXT (80 + NPROC / 8)			/* actually the object cache */
#define	NVNODE (NPROC + NTEXT + 100)
E 53
E 45
D 42
int	nvnode = NVNODE;
int	nchsize = NVNODE * 11 / 10;
E 42
I 42
D 46
int	desiredvnodes = NVNODE;
E 46
I 46
D 58
long	desiredvnodes = NVNODE;
E 58
I 58
int	desiredvnodes = NVNODE;
E 58
E 46
E 42
E 41
E 40
E 24
E 22
E 2
D 5
int	nfile = 8 * (NPROC + 16 + MAXUSERS) / 10;
E 5
I 5
D 12
int	nfile = 8 * (NPROC + 16 + MAXUSERS) / 10 + 32;
E 12
I 12
D 17
int	nfile = 16 * (NPROC + 16 + MAXUSERS) / 10 + 32;
E 17
I 17
D 18
/* the +40 here is for 20 server processes */
int	nfile = 16 * (NPROC + 16 + MAXUSERS) / 10 + 32 + 40;
E 18
I 18
D 23
int	nfile = 16 * (NPROC + 16 + MAXUSERS) / 10 + 32 + 2 * NETSLOP;
E 23
I 23
D 52
int	nfile = 16 * (NPROC + 16 + MAXUSERS) / 10 + 32;
E 52
I 52
D 53
int	maxfiles = 3 * (NPROC + 16 + MAXUSERS) + 32;
E 53
I 53
int	maxfiles = 3 * (NPROC + MAXUSERS) + 80;
E 53
E 52
E 23
E 18
E 17
E 12
E 5
D 16
int	ncallout = 16 + MAXUSERS;
E 16
I 16
int	ncallout = 16 + NPROC;
E 16
D 31
int	nclist = 100 + 16 * MAXUSERS;
E 31
I 31
int	nclist = 60 + 12 * MAXUSERS;
E 31
I 3
D 33
int	nport = NPROC / 2;
E 33
I 4
D 9
#ifdef BBNNET
int     nnetpages = NNETPAGES;
E 9
I 9
D 11
int     nmbpages = NMBPAGES;
E 11
I 11
D 53
int     nmbclusters = NMBCLUSTERS;
E 53
I 53
int	nmbclusters = NMBCLUSTERS;
E 53
I 20
D 22
int	nchsize = 60 + 3 * MAXUSERS;
E 22
E 20
I 13
D 15
#if	QUOTA
E 15
I 15
D 43
#ifdef QUOTA
E 15
D 26
int	nquota = (MAXUSERS * 9)/7 + 3;
int	ndquot = (MAXUSERS*NMOUNT)/4 + NPROC;
E 26
I 26
int	nquota = (MAXUSERS * 9) / 7 + 3;
D 41
int	ndquot = NINODE + (MAXUSERS * NMOUNT) / 4;
E 41
I 41
int	ndquot = NVNODE + (MAXUSERS * NMOUNT) / 4;
E 41
E 26
#endif
E 43
I 39
int	fscale = FSCALE;	/* kernel uses `FSCALE', user uses `fscale' */
I 45

/*
D 53
 * Values in support of System V compatible shared memory.
E 53
I 53
 * Values in support of System V compatible shared memory.	XXX
E 53
 */
#ifdef SYSVSHM
#define	SHMMAX	(SHMMAXPGS*NBPG)
D 53
#define SHMMIN	1
#define SHMMNI	32			/* <= SHMMMNI in shm.h */
E 53
I 53
#define	SHMMIN	1
#define	SHMMNI	32			/* <= SHMMMNI in shm.h */
E 53
#define	SHMSEG	8
D 53
#define SHMALL	(SHMMAXPGS/CLSIZE)
E 53
I 53
#define	SHMALL	(SHMMAXPGS/CLSIZE)
E 53

struct	shminfo shminfo = {
	SHMMAX,
	SHMMIN,
	SHMMNI,
	SHMSEG,
	SHMALL
};
#endif
E 45
E 39
E 13
E 11
D 10
#ifdef INET
E 9
D 6
int     nwork = NWORK;
E 6
int     nnetcon = NCON;
int     nhost = NHOST;
D 9
#endif BBNNET
E 9
I 9
#endif INET
E 10
E 9
E 4
E 3

/*
 * These are initialized at bootstrap time
 * to values dependent on memory size
 */
int	nbuf, nswbuf;

/*
 * These have to be allocated somewhere; allocating
D 32
 * them here forces loader errors if this file is omitted.
E 32
I 32
 * them here forces loader errors if this file is omitted
 * (if they've been externed everywhere else; hah!).
E 32
 */
D 50
struct	proc *proc, *procNPROC;
E 50
D 48
struct	text *text, *textNTEXT;
E 48
D 41
struct	inode *inode, *inodeNINODE;
E 41
I 41
D 42
struct	vnode *vnode, *vnodeNVNODE;
E 42
E 41
D 53
struct	file *file, *fileNFILE;
E 53
struct 	callout *callout;
struct	cblock *cfree;
D 4

E 4
struct	buf *buf, *swbuf;
D 33
short	*swsize;
int	*swpf;
E 33
char	*buffers;
D 48
struct	cmap *cmap, *ecmap;
E 48
I 44
D 61

/*
 * Proc/pgrp hashing.
 * Here so that hash table sizes can depend on MAXUSERS/NPROC.
 * Hash size must be a power of two.
 * NOW omission of this file will cause loader errors!
 */

#if NPROC > 1024
#define	PIDHSZ		512
#else
#if NPROC > 512
#define	PIDHSZ		256
#else
#if NPROC > 256
#define	PIDHSZ		128
#else
#define	PIDHSZ		64
#endif
#endif
#endif

struct	proc *pidhash[PIDHSZ];
struct	pgrp *pgrphash[PIDHSZ];
int	pidhashmask = PIDHSZ - 1;
E 61
E 44
I 20
D 32
struct	nch *nch;
E 32
I 32
D 42
struct	namecache *namecache;
E 42
E 32
E 20
I 13
D 15
#if	QUOTA
E 15
I 15
D 43
#ifdef QUOTA
E 15
struct	quota *quota, *quotaNQUOTA;
struct	dquot *dquot, *dquotNDQUOT;
#endif
E 43
E 13
I 4
D 9
#ifdef BBNNET
D 6
struct  pfree *freetab;
struct  work *workfree, *workNWORK;
E 6
struct  ucb *contab, *conNCON;
E 9
I 9
D 10
#ifdef INET
E 9
struct  host *host, *hostNHOST;
D 8
struct  net netcb;
E 8
struct  net_stat netstat;
struct  impstat imp_stat;
D 9
#endif BBNNET
E 9
I 9
#endif INET
E 10
E 9
E 4
E 1
