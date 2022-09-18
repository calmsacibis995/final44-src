h27031
s 00012/00008/00622
d D 8.4 95/02/14 10:48:25 cgd 89 88
c return types, add a comment or type where necessary.
e
s 00001/00000/00629
d D 8.3 95/01/09 18:22:30 cgd 88 87
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00002/00002/00627
d D 8.2 94/01/04 18:42:11 bostic 87 86
c lint
e
s 00002/00002/00627
d D 8.1 93/07/20 11:36:57 bostic 86 85
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00627
d D 7.26 93/07/20 11:35:00 mckusick 85 83
c fix length adjustment of m_pkthdr.len (from karels@bsdi.com)
e
s 00002/00002/00627
d R 8.1 93/06/10 21:59:37 bostic 84 83
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00011/00617
d D 7.25 92/10/11 10:38:49 bostic 83 82
c make kernel includes standard
e
s 00001/00000/00627
d D 7.24 92/07/12 17:31:24 pendry 82 81
c need to include systm.h
e
s 00002/00002/00625
d D 7.23 92/07/12 17:20:22 pendry 81 80
c MIN -> min, MAX -> max
e
s 00004/00002/00623
d D 7.22 92/02/05 19:34:50 torek 80 79
c cleanups
e
s 00012/00011/00613
d D 7.21 91/12/19 21:59:05 mckusick 79 78
c get sense of waiting right (from torek)
e
s 00134/00000/00490
d D 7.20 91/08/30 12:40:44 sklower 78 77
c add common routine to copy from dev buf to mbufs;
c add routine shared between iso & x.25 for packetize that cleaves an mbuf.
e
s 00005/00008/00485
d D 7.19 91/04/20 16:15:18 karels 77 76
c fix includes
e
s 00010/00012/00483
d D 7.18 90/12/05 17:11:23 mckusick 76 75
c update for new VM
e
s 00003/00001/00492
d D 7.17 90/07/25 15:19:44 karels 75 74
c nit: clear M_PKTHDR on second mbuf of chain in m_pullup (after prepending new)
e
s 00001/00011/00492
d D 7.16 90/06/28 21:23:30 bostic 74 73
c new copyright notice
e
s 00008/00000/00495
d D 7.15 90/05/15 18:01:12 mckusick 73 72
c add failure statistics (from hibler)
e
s 00001/00002/00494
d D 7.14 90/05/15 17:57:03 mckusick 72 71
c fix definition of NCL_INIT (from hibler)
e
s 00000/00001/00496
d D 7.13 90/04/05 15:16:21 sklower 71 70
c remove unneeded (and harmful) header file dir.h
e
s 00002/00000/00495
d D 7.12 89/09/26 16:23:20 sklower 70 69
c fast track m_adj from tail didn't adjust pkthdr.len
e
s 00164/00118/00331
d D 7.11 89/09/04 17:01:02 karels 69 67
c new mbufs
e
s 00000/00006/00453
d D 7.4.1.3 89/02/15 09:40:49 karels 68 62
i 67 66 65 64 63
c update branch
e
s 00010/00005/00439
d D 7.10 88/06/29 17:20:20 bostic 67 66
c install approved copyright notice
e
s 00000/00010/00444
d D 7.9 88/05/26 08:56:36 karels 66 65
c rm unused m_pgfree
e
s 00006/00004/00448
d D 7.8 88/04/09 17:21:19 karels 65 64
c really working m_copydata
e
s 00035/00000/00417
d D 7.7 88/02/27 13:46:54 karels 64 63
c add m_copydata
e
s 00001/00001/00416
d D 7.6 88/02/08 11:05:21 karels 63 61
c update date on copyright
e
s 00009/00003/00412
d D 7.4.1.2 88/02/08 11:04:35 karels 62 60
c update copyright on branch
e
s 00008/00002/00409
d D 7.5 87/12/30 12:01:20 bostic 61 59
c add Berkeley header
e
s 00000/00000/00415
d D 7.4.1.1 87/11/24 14:15:30 karels 60 59
x 56
c branch for tahoe release (no malloc)
e
s 00010/00004/00401
d D 7.4 87/11/23 14:59:02 karels 59 56
c try to make this work when MCLBYTES != CLBYTES !
e
s 00010/00004/00401
d R 7.4 87/11/23 14:57:17 karels 58 56
c try to make this work when MCLBYTES != CLBYTES
e
s 00010/00004/00401
d R 7.4 87/11/23 14:09:00 karels 57 56
c try to make it work when CLBYTES != MCLBYTES
e
s 00000/00004/00405
d D 7.3 87/06/21 18:13:53 mckusick 56 55
c MPG_SPACE is replaced by malloc
e
s 00031/00008/00378
d D 7.2 87/02/02 18:01:48 karels 55 54
c log, not panic, when mbuf map exhausted; more statistics
e
s 00001/00001/00385
d D 7.1 86/06/05 00:15:53 mckusick 54 53
c 4.3BSD release version
e
s 00001/00001/00385
d D 6.10 86/06/01 16:30:13 karels 53 52
c can allocate more clusters later, don't need so many at first
e
s 00001/00001/00385
d D 6.9 85/11/06 18:56:13 karels 52 51
c try to make panic message intelligible
e
s 00057/00030/00329
d D 6.8 85/09/16 20:46:24 karels 51 50
c fix m_adj to work right trimming from tail (there can be 0-length mbufs
c in the chain); make m_pullup use first mbuf if enough room without copying,
c and pullup a bit extra for next-level protocol
e
s 00001/00001/00358
d D 6.7 85/09/05 15:30:50 karels 50 49
c hmm, this tells me something
e
s 00012/00007/00347
d D 6.6 85/06/29 12:19:44 karels 49 48
c cleanups in m_pullup: remove unneeded length test, be careful
c to leave offset pointing in current mbuf [cluster], don't go an extra turn
c around the loop with a zero count
e
s 00007/00001/00347
d D 6.5 85/06/08 14:58:08 mckusick 48 47
c Add copyright
e
s 00039/00018/00309
d D 6.4 85/05/27 20:00:28 karels 47 46
c implement M_WAIT; reduce redundant splimp's
e
s 00009/00009/00318
d D 6.3 84/08/29 20:27:44 bloom 46 45
c Change to includes.  no more ../h
e
s 00001/00003/00326
d D 6.2 84/02/22 08:48:05 karels 45 44
c m_copy replicates type per mbuf (not all headers)
e
s 00000/00000/00329
d D 6.1 83/07/29 06:46:20 sam 44 43
c 4.2 distribution
e
s 00000/00000/00329
d D 1.43 83/05/27 12:50:19 sam 43 42
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00009/00004/00320
d D 1.42 82/12/17 11:49:08 sam 42 41
c sun merge
e
s 00016/00013/00308
d D 1.41 82/12/14 17:10:24 sam 41 40
c typed mbufs
e
s 00001/00001/00320
d D 1.40 82/10/21 23:53:48 root 40 39
c lint
e
s 00001/00000/00320
d D 1.39 82/10/21 20:59:30 root 39 38
c lint
e
s 00000/00001/00320
d D 1.38 82/10/09 05:38:49 wnj 38 37
c fix up header file dependencies 
e
s 00002/00006/00319
d D 1.37 82/10/05 21:57:53 root 37 36
c send(... SOF_OOB) and receive(... SOF_PREVIEW)
e
s 00000/00011/00325
d D 1.36 82/06/20 12:21:41 sam 36 35
c purge COUNT crap now that we have gprof
e
s 00000/00023/00336
d D 1.35 82/06/14 22:16:59 wnj 35 34
c get rid of m_release stuff
e
s 00001/00001/00358
d D 1.34 82/05/19 01:19:39 sam 34 33
c make more lucid
e
s 00006/00009/00353
d D 1.33 82/05/18 21:46:28 sam 33 32
c rethink statistics?
e
s 00010/00009/00352
d D 1.32 82/03/13 12:54:36 sam 32 31
c lint
e
s 00003/00000/00358
d D 1.31 82/03/12 16:03:33 sam 31 30
c keep lint happy
e
s 00011/00011/00347
d D 1.30 82/03/09 20:32:17 root 30 29
c 
e
s 00002/00002/00356
d D 1.29 82/02/08 23:02:38 root 29 28
c bug fix in m_pullup
e
s 00002/00001/00356
d D 1.28 82/01/25 18:38:18 wnj 28 27
c bug fixes (round 1)
e
s 00007/00003/00350
d D 1.27 82/01/24 18:32:10 wnj 27 26
c M_COPYALL len argument to m_copy causes all to be copied
e
s 00002/00000/00351
d D 1.26 82/01/19 06:39:20 wnj 26 25
c closef parameter indicating whether error return
c to complete non-blc
e
s 00034/00003/00317
d D 1.25 81/12/23 14:09:42 root 25 24
c m_pullup
e
s 00001/00000/00319
d D 1.24 81/12/21 11:54:27 root 24 23
c #undef m_more
e
s 00001/00000/00318
d D 1.23 81/12/20 15:28:54 root 23 22
c m_free set to 0
e
s 00000/00004/00318
d D 1.22 81/12/12 18:07:35 root 22 21
c delete prints
e
s 00000/00002/00322
d D 1.21 81/12/12 17:49:34 root 21 20
c almost works
e
s 00001/00000/00323
d D 1.20 81/12/09 21:20:15 wnj 20 19
c cleanup
e
s 00109/00124/00214
d D 1.19 81/12/09 20:53:55 wnj 19 18
c new and cleaner version
e
s 00001/00001/00337
d D 1.18 81/11/30 16:22:51 wnj 18 17
c lint
e
s 00026/00016/00312
d D 1.17 81/11/26 11:58:23 wnj 17 16
c before carry to arpavax
e
s 00011/00005/00317
d D 1.16 81/11/22 10:49:01 wnj 16 15
c fix reserve/release to work in m_hiwat and shift lowat
e
s 00004/00006/00318
d D 1.15 81/11/21 22:13:20 root 15 14
c fix mbuf accounting
e
s 00006/00004/00318
d D 1.14 81/11/21 15:13:22 wnj 14 13
c m_reserve/m_release args scale
e
s 00002/00002/00320
d D 1.13 81/11/20 14:43:11 wnj 13 12
c more lint
e
s 00001/00000/00321
d D 1.12 81/11/20 00:45:57 wnj 12 11
c linted
e
s 00062/00006/00259
d D 1.11 81/11/18 15:45:06 wnj 11 10
c more cleanup
e
s 00022/00020/00243
d D 1.10 81/11/16 14:20:47 wnj 10 9
c lint
e
s 00015/00000/00248
d D 1.9 81/11/14 16:43:39 wnj 9 8
c before header overlay
e
s 00020/00046/00228
d D 1.8 81/11/08 16:55:00 wnj 8 7
c first listing
e
s 00018/00000/00256
d D 1.7 81/11/04 00:28:57 wnj 7 6
c more cleanups, fields in ucb.h
e
s 00055/00035/00201
d D 1.6 81/10/30 15:11:35 wnj 6 5
c page at a time version
e
s 00018/00037/00218
d D 1.5 81/10/29 20:27:01 wnj 5 4
c cleanup of header files
e
s 00002/00002/00253
d D 1.4 81/10/28 19:35:17 wnj 4 3
c mtod with type casts
e
s 00020/00002/00235
d D 1.3 81/10/28 16:37:51 wnj 3 2
c first compiled halfbrid... not working yet
e
s 00003/00001/00234
d D 1.2 81/10/23 10:07:08 wnj 2 1
c first working version with page macros and new snd_copy
e
s 00235/00000/00000
d D 1.1 81/10/22 13:44:41 wnj 1 0
c date and time created 81/10/22 13:44:41 by wnj
e
u
U
f b 
t
T
I 1
D 2
/* mbuf.c 1.6 81/10/21 */
E 2
I 2
D 3
/* %M% %I% %E% */
E 3
I 3
D 4
/* mbuf.c 1.2 81/10/23 */
E 4
I 4
D 10
/* %M% %I% %E% */
E 10
I 10
D 48
/*	%M%	%I%	%E%	*/
E 48
I 48
/*
D 54
 * Copyright (c) 1982 Regents of the University of California.
E 54
I 54
D 62
D 63
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 63
I 63
D 77
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 77
I 77
D 86
 * Copyright (c) 1982, 1986, 1988, 1991 Regents of the University of California.
E 77
E 63
E 54
D 61
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 62
I 62
D 68
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 68
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 68
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 68
E 62
E 61
I 61
 * All rights reserved.
E 86
I 86
 * Copyright (c) 1982, 1986, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 86
 *
D 74
 * Redistribution and use in source and binary forms are permitted
D 67
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 67
I 67
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
E 74
I 74
 * %sccs.include.redist.c%
E 74
E 67
E 61
 *
 *	%W% (Berkeley) %G%
 */
E 48
E 10
E 4
E 3
E 2

I 42
D 69
#include "../machine/pte.h"

E 69
E 42
D 46
#include "../h/param.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
D 42
#include "../h/pte.h"
E 42
#include "../h/cmap.h"
#include "../h/map.h"
I 3
#include "../h/mbuf.h"
E 3
D 5
#include "../bbnnet/net.h"
D 3
#include "../bbnnet/mbuf.h"
E 3
#include "../bbnnet/tcp.h"
#include "../bbnnet/ip.h"
E 5
I 5
D 8
#include "../inet/inet.h"
#include "../inet/inet_systm.h"
D 6
#include "../inet/tcp.h"
E 6
#include "../inet/ip.h"
I 6
#include "../inet/tcp.h"
E 8
I 8
D 10
#include "../net/inet_systm.h"		/* ### */
E 10
I 10
D 17
#include "../net/inet_systm.h"		/* XXX */
E 17
I 17
D 38
#include "../net/in_systm.h"		/* XXX */
E 38
E 17
E 10
E 8
E 6
E 5
#include "../h/vm.h"
I 39
#include "../h/kernel.h"
E 46
I 46
D 83
#include "param.h"
I 82
#include "systm.h"
E 82
D 71
#include "dir.h"
E 71
D 77
#include "user.h"
E 77
#include "proc.h"
D 77
#include "cmap.h"
E 77
I 69
#include "malloc.h"
E 69
#include "map.h"
E 83
I 83
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/malloc.h>
#include <sys/map.h>
E 83
I 69
#define MBTYPES
E 69
D 83
#include "mbuf.h"
D 76
#include "vm.h"
E 76
#include "kernel.h"
I 55
#include "syslog.h"
#include "domain.h"
#include "protosw.h"
I 69
D 76
#include "machine/pte.h"
E 76
I 76
D 77
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
E 77
I 77
#include "vm/vm.h"
E 83
I 83
#include <sys/mbuf.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
#include <sys/domain.h>
#include <sys/protosw.h>

#include <vm/vm.h>
E 83
E 77
E 76
E 69
E 55
E 46
E 39

I 76
D 77
extern vm_map_t mb_map;
struct mbuf *mbutl;
char *mclrefcnt;
E 77
I 77
extern	vm_map_t mb_map;
struct	mbuf *mbutl;
char	*mclrefcnt;
E 77

I 89
void
E 89
E 76
I 19
mbinit()
{
I 47
	int s;
E 47
D 21
	register struct mbuf *m;
	register i;
E 21

I 59
D 69
#if CLBYTES < 4096
#define NCL_INIT	(4096/CLBYTES)
E 69
I 69
D 76
#if MCLBYTES < 4096
E 76
I 76
D 89
#if CLBYTES < 4096
E 76
D 72
#define NCL_INIT	(4096/MCLBYTES)
E 72
I 72
#define NCL_INIT	(4096/CLBYTES)
E 72
E 69
#else
#define NCL_INIT	1
#endif
E 89
E 59
D 36
COUNT(MBINIT);
E 36
D 35
	if (m_reserve(32) == 0)
		goto bad;
E 35
D 42
	if (m_clalloc(4, MPG_MBUFS) == 0)
E 42
I 42
D 47
	if (m_clalloc(4096/CLBYTES, MPG_MBUFS) == 0)
E 47
I 47
	s = splimp();
D 59
	if (m_clalloc(4096/CLBYTES, MPG_MBUFS, M_DONTWAIT) == 0)
E 59
I 59
D 69
	if (m_clalloc(NCL_INIT, MPG_MBUFS, M_DONTWAIT) == 0)
E 69
I 69
D 89
	if (m_clalloc(NCL_INIT, M_DONTWAIT) == 0)
E 89
I 89
	if (m_clalloc(max(4096/CLBYTES, 1), M_DONTWAIT) == 0)
E 89
E 69
E 59
E 47
E 42
		goto bad;
D 42
	if (m_clalloc(32, MPG_CLUSTERS) == 0)
E 42
I 42
D 47
	if (m_clalloc(8*4096/CLBYTES, MPG_CLUSTERS) == 0)
E 47
I 47
D 53
	if (m_clalloc(8*4096/CLBYTES, MPG_CLUSTERS, M_DONTWAIT) == 0)
E 53
I 53
D 59
	if (m_clalloc(4096/CLBYTES, MPG_CLUSTERS, M_DONTWAIT) == 0)
E 59
I 59
D 69
	if (m_clalloc(NCL_INIT, MPG_CLUSTERS, M_DONTWAIT) == 0)
E 59
E 53
E 47
E 42
		goto bad;
E 69
I 47
	splx(s);
E 47
	return;
bad:
	panic("mbinit");
}

I 47
/*
I 69
 * Allocate some number of mbuf clusters
 * and place on cluster free list.
E 69
 * Must be called at splimp.
 */
I 55
/* ARGSUSED */
I 89
int
E 89
E 55
E 47
D 69
caddr_t
D 47
m_clalloc(ncl, how)
E 47
I 47
m_clalloc(ncl, how, canwait)
E 69
I 69
D 79
m_clalloc(ncl, canwait)
E 79
I 79
m_clalloc(ncl, nowait)
E 79
E 69
E 47
	register int ncl;
I 79
	int nowait;
E 79
D 69
	int how;
E 69
{
D 87
	int npg, mbx;
E 87
I 87
	static int logged;
E 87
D 69
	register struct mbuf *m;
E 69
I 69
	register caddr_t p;
E 69
	register int i;
I 55
D 87
	static int logged;
E 87
I 87
	int npg;
E 87
E 55
D 47
	int s;
E 47

D 36
COUNT(M_CLALLOC);
E 36
	npg = ncl * CLSIZE;
I 26
D 47
	s = splimp();		/* careful: rmalloc isn't reentrant */
E 47
E 26
D 40
	mbx = rmalloc(mbmap, npg);
E 40
I 40
D 76
	mbx = rmalloc(mbmap, (long)npg);
E 40
I 26
D 47
	splx(s);
E 26
D 22
printf("ncl %d how %d npg %d mbx %d\n", ncl, how, npg, mbx);
E 22
	if (mbx == 0)
E 47
I 47
	if (mbx == 0) {
E 76
I 76
D 79
	p = (caddr_t)kmem_malloc(mb_map, ctob(npg), canwait);
E 79
I 79
	p = (caddr_t)kmem_malloc(mb_map, ctob(npg), !nowait);
E 79
	if (p == NULL) {
E 76
D 55
		if (canwait == M_WAIT)
D 52
			panic("out of mbuf map");
E 52
I 52
			panic("out of mbufs: map full");
E 55
I 55
		if (logged == 0) {
			logged++;
D 76
			log(LOG_ERR, "mbuf map full\n");
E 76
I 76
			log(LOG_ERR, "mb_map full\n");
E 76
		}
E 55
E 52
E 47
		return (0);
I 47
	}
E 47
D 59
	m = cltom(mbx / CLSIZE);
E 59
I 59
D 69
	m = cltom(mbx * NBPG / MCLBYTES);
E 69
I 69
D 76
	p = cltom(mbx * NBPG / MCLBYTES);
E 69
E 59
D 34
	if (memall(&Mbmap[mbx], ncl * CLSIZE, proc, CSYS) == 0)
E 34
I 34
D 42
	if (memall(&Mbmap[mbx], npg, proc, CSYS) == 0)
E 42
I 42
	if (memall(&Mbmap[mbx], npg, proc, CSYS) == 0) {
D 47
		s = splimp();
E 47
		rmfree(mbmap, (long)npg, (long)mbx);
D 47
		splx(s);
E 47
E 42
E 34
		return (0);
I 42
	}
E 42
D 69
	vmaccess(&Mbmap[mbx], (caddr_t)m, npg);
D 22
printf("m %x &Mbmap[mbx] %x\n", m, &Mbmap[mbx]);
E 22
	switch (how) {
E 69
I 69
	vmaccess(&Mbmap[mbx], p, npg);
E 76
	ncl = ncl * CLBYTES / MCLBYTES;
	for (i = 0; i < ncl; i++) {
		((union mcluster *)p)->mcl_next = mclfree;
		mclfree = (union mcluster *)p;
		p += MCLBYTES;
		mbstat.m_clfree++;
	}
	mbstat.m_clusters += ncl;
	return (1);
}
E 69

D 69
	case MPG_CLUSTERS:
I 59
		ncl = ncl * CLBYTES / MCLBYTES;
E 59
D 47
		s = splimp();
E 47
		for (i = 0; i < ncl; i++) {
			m->m_off = 0;
			m->m_next = mclfree;
			mclfree = m;
D 59
			m += CLBYTES / sizeof (*m);
E 59
I 59
			m += MCLBYTES / sizeof (*m);
E 59
D 33
			nmclfree++;
E 33
I 33
			mbstat.m_clfree++;
E 33
		}
		mbstat.m_clusters += ncl;
D 47
		splx(s);
E 47
		break;
E 69
I 69
/*
 * When MGET failes, ask protocols to free space when short of memory,
 * then re-attempt to allocate an mbuf.
 */
struct mbuf *
m_retry(i, t)
	int i, t;
{
	register struct mbuf *m;
E 69

D 69
	case MPG_MBUFS:
		for (i = ncl * CLBYTES / sizeof (*m); i > 0; i--) {
			m->m_off = 0;
I 23
D 41
			m->m_free = 0;
E 41
I 41
			m->m_type = MT_DATA;
			mbstat.m_mtypes[MT_DATA]++;
E 41
I 33
			mbstat.m_mbufs++;
E 33
E 23
			(void) m_free(m);
			m++;
		}
D 33
		mbstat.m_clusters += ncl;
E 33
I 20
		break;
I 55
D 56

	case MPG_SPACE:
		mbstat.m_space++;
		break;
E 56
E 55
E 20
	}
	return ((caddr_t)m);
E 69
I 69
	m_reclaim();
#define m_retry(i, t)	(struct mbuf *)0
	MGET(m, i, t);
#undef m_retry
	return (m);
E 69
}

D 66
m_pgfree(addr, n)
	caddr_t addr;
	int n;
{

D 36
COUNT(M_PGFREE);
E 36
I 31
#ifdef lint
	addr = addr; n = n;
#endif
E 31
D 22
	printf("m_pgfree %x %d\n", addr, n);
E 22
}

E 66
D 47
m_expand()
E 47
I 47
/*
D 69
 * Must be called at splimp.
E 69
I 69
 * As above; retry an MGETHDR.
E 69
 */
D 69
m_expand(canwait)
	int canwait;
E 69
I 69
struct mbuf *
m_retryhdr(i, t)
	int i, t;
E 69
E 47
{
I 69
	register struct mbuf *m;

	m_reclaim();
#define m_retryhdr(i, t) (struct mbuf *)0
	MGETHDR(m, i, t);
#undef m_retryhdr
	return (m);
}

I 89
void
E 89
m_reclaim()
{
E 69
I 55
	register struct domain *dp;
	register struct protosw *pr;
D 69
	int tries;
E 69
I 69
	int s = splimp();
E 69
E 55

D 36
COUNT(M_EXPAND);
E 36
D 33
	if (mbstat.m_bufs >= mbstat.m_hiwat)
		return (0);
E 33
D 47
	if (m_clalloc(1, MPG_MBUFS) == 0)
E 47
I 47
D 55
	if (m_clalloc(1, MPG_MBUFS, canwait) == 0)
E 47
		goto steal;
	return (1);
steal:
	/* should ask protocols to free code */
	return (0);
E 55
I 55
D 69
	for (tries = 0;; ) {
		if (m_clalloc(1, MPG_MBUFS, canwait))
			return (1);
		if (canwait == 0 || tries++)
			return (0);

		/* ask protocols to free space */
		for (dp = domains; dp; dp = dp->dom_next)
			for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW;
			    pr++)
				if (pr->pr_drain)
					(*pr->pr_drain)();
		mbstat.m_drain++;
	}
E 69
I 69
	for (dp = domains; dp; dp = dp->dom_next)
		for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++)
			if (pr->pr_drain)
				(*pr->pr_drain)();
	splx(s);
	mbstat.m_drain++;
E 69
E 55
}

D 69
/* NEED SOME WAY TO RELEASE SPACE */
D 35

/*
 * Space reservation routines
 */
E 19
I 7
D 14
m_reserve(mbufs)
	int mbufs;
E 14
I 14
D 15
m_reserve(cc)
	int cc;
E 15
I 15
m_reserve(mbufs)
	int mbufs;
E 15
E 14
{
I 14
D 15
	int mbufs = cc / MSIZE;
E 15
E 14

D 8
	if (mbstat.m_lowat + mbufs > NNETPAGES * NMBPG - 32) 
E 8
I 8
D 16
	if (mbstat.m_lowat + mbufs > NMBPAGES * NMBPG - 32) 
E 16
I 16
D 19
/*
	printf("reserve %d\n", mbufs);
*/
E 19
D 17
	if (mbstat.m_lowat + (mbufs>>1) > NMBPAGES * NMBPG - 32) 
E 17
I 17
D 18
	if (mbstat.m_lowat + (mbufs>>1) > (NMBPAGES-32) * CLBYTES) 
E 18
I 18
D 33
	if (mbstat.m_lowat + (mbufs>>1) > (NMBCLUSTERS-32) * CLBYTES) 
E 33
I 33
	if (mbstat.m_mbcommitted + mbufs >
	      (nmbclusters * NMBPCL) * MBUFOVERALLOCFRACTION)
E 33
E 18
E 17
E 16
E 8
		return (0);
D 16
	mbstat.m_lowat += mbufs;
	mbstat.m_hiwat = 2 * mbstat.m_lowat;
E 16
I 16
D 33
	mbstat.m_hiwat += mbufs;
	mbstat.m_lowat = mbstat.m_hiwat >> 1;
E 33
I 33
	mbstat.m_mbcommitted += mbufs;
E 33
E 16
I 10
	return (1);
E 10
}

D 14
m_release(mbufs)
	int mbufs;
E 14
I 14
D 15
m_release(cc)
	int cc;
E 15
I 15
m_release(mbufs)
	int mbufs;
E 15
E 14
{
I 14
D 15
	int mbufs = cc / MSIZE;
E 15
E 14

D 16
	mbstat.m_lowat -= mbufs;
	mbstat.m_hiwat = 2 * mbstat.m_lowat;
E 16
I 16
D 19
/*
	printf("release %d\n", mbufs);
*/
E 19
D 33
	mbstat.m_hiwat -= mbufs;
	mbstat.m_lowat = mbstat.m_hiwat >> 1;
E 33
I 33
	mbstat.m_mbcommitted -= mbufs;
E 33
E 16
}
E 35

E 69
I 19
/*
 * Space allocation routines.
 * These are also available as macros
 * for critical paths.
 */
E 19
E 7
struct mbuf *
D 41
m_get(canwait)
	int canwait;
E 41
I 41
D 79
m_get(canwait, type)
	int canwait, type;
E 79
I 79
m_get(nowait, type)
	int nowait, type;
E 79
E 41
{
	register struct mbuf *m;

D 36
COUNT(M_GET);
E 36
D 41
	MGET(m, canwait);
E 41
I 41
D 79
	MGET(m, canwait, type);
E 79
I 79
	MGET(m, nowait, type);
E 79
E 41
	return (m);
}

struct mbuf *
I 69
D 79
m_gethdr(canwait, type)
	int canwait, type;
E 79
I 79
m_gethdr(nowait, type)
	int nowait, type;
E 79
{
	register struct mbuf *m;

D 79
	MGETHDR(m, canwait, type);
E 79
I 79
	MGETHDR(m, nowait, type);
E 79
	return (m);
}

struct mbuf *
E 69
I 9
D 41
m_getclr(canwait)
	int canwait;
E 41
I 41
D 79
m_getclr(canwait, type)
	int canwait, type;
E 79
I 79
m_getclr(nowait, type)
	int nowait, type;
E 79
E 41
{
	register struct mbuf *m;

D 36
COUNT(M_GETCLR);
E 36
D 10
	m = m_get(m, canwait);
E 10
I 10
D 41
	m = m_get(canwait);
E 41
I 41
D 47
	m = m_get(canwait, type);
E 47
I 47
D 79
	MGET(m, canwait, type);
E 79
I 79
	MGET(m, nowait, type);
E 79
E 47
E 41
E 10
	if (m == 0)
		return (0);
D 37
	m->m_off = MMINOFF;
E 37
	bzero(mtod(m, caddr_t), MLEN);
	return (m);
}

struct mbuf *
E 9
m_free(m)
	struct mbuf *m;
{
	register struct mbuf *n;

D 36
COUNT(M_FREE);
E 36
	MFREE(m, n);
	return (n);
}

I 80
void
E 80
I 47
D 69
/*
 * Get more mbufs; called from MGET macro if mfree list is empty.
 * Must be called at splimp.
 */
E 47
I 10
/*ARGSUSED*/
E 10
struct mbuf *
D 41
m_more(type)
	int type;
E 41
I 41
m_more(canwait, type)
	int canwait, type;
E 41
{
D 10
	int s;
E 10
	register struct mbuf *m;

D 36
COUNT(M_MORE);
E 36
D 47
	if (!m_expand()) {
D 8
		netstat.m_drops++;
E 8
I 8
		mbstat.m_drops++;
E 8
		return (NULL);
E 47
I 47
	while (m_expand(canwait) == 0) {
		if (canwait == M_WAIT) {
I 55
			mbstat.m_wait++;
E 55
			m_want++;
D 50
			sleep((caddr_t)mfree, PZERO - 1);
E 50
I 50
			sleep((caddr_t)&mfree, PZERO - 1);
I 65
			if (mfree)
				break;
E 65
E 50
		} else {
			mbstat.m_drops++;
			return (NULL);
		}
E 47
	}
D 10
#define m_more(x) ((struct mbuf *)panic("m_more"))
	MGET(m, 0);
E 10
I 10
D 41
#define m_more(x) (panic("m_more"), (struct mbuf *)0)
	MGET(m, type);
E 41
I 41
#define m_more(x,y) (panic("m_more"), (struct mbuf *)0)
	MGET(m, canwait, type);
E 41
I 24
#undef m_more
E 24
E 10
	return (m);
}

E 69
D 6
m_freem(m)                      /* free mbuf chain headed by m */
E 6
I 6
m_freem(m)
E 6
	register struct mbuf *m;
{
	register struct mbuf *n;
D 10
	register int s, cnt;
E 10
I 10
D 11
	register int s, i;
E 11
I 11
D 69
	register int s;
E 69
E 11
E 10

D 36
COUNT(M_FREEM);
E 36
	if (m == NULL)
D 10
		return (0);
	cnt = 0;
E 10
I 10
		return;
D 11
	i = 0;
E 11
E 10
D 5
	s = spl_imp();
E 5
I 5
D 69
	s = splimp();
E 69
E 5
	do {
D 6
		MFREE(m, n);
E 6
I 6
D 11
		if (m->m_off > MMAXOFF)
D 10
			cnt += NMBPG;
E 6
		cnt++;
E 10
I 10
			i += NMBPG;
		i++;
E 11
E 10
I 6
		MFREE(m, n);
E 6
	} while (m = n);
D 69
	splx(s);
E 69
D 10
	return (cnt);
E 10
I 10
D 11
	return;
E 11
I 11
}

I 12
D 19
/*ARGSUSED*/
E 12
m_pullup(m, len)
	struct mbuf *m;
	int len;
{

	return (0);
}

E 19
I 19
/*
 * Mbuffer utility routines.
 */
I 47

/*
I 69
 * Lesser-used path for M_PREPEND:
 * allocate new mbuf to prepend to chain,
 * copy junk along.
 */
struct mbuf *
m_prepend(m, len, how)
	register struct mbuf *m;
	int len, how;
{
	struct mbuf *mn;

	MGET(mn, how, m->m_type);
	if (mn == (struct mbuf *)NULL) {
		m_freem(m);
		return ((struct mbuf *)NULL);
	}
	if (m->m_flags & M_PKTHDR) {
		M_COPY_PKTHDR(mn, m);
		m->m_flags &= ~M_PKTHDR;
	}
	mn->m_next = m;
	m = mn;
	if (len < MHLEN)
		MH_ALIGN(m, len);
	m->m_len = len;
	return (m);
}

E 69
I 64
D 72
/*
E 72
E 64
D 69
 * Make a copy of an mbuf chain starting "off" bytes from the beginning,
E 69
I 69
/*
 * Make a copy of an mbuf chain starting "off0" bytes from the beginning,
E 69
 * continuing for "len" bytes.  If len is M_COPYALL, copy to end of mbuf.
D 69
 * Should get M_WAIT/M_DONTWAIT from caller.
E 69
I 69
 * The wait parameter is a choice of M_WAIT/M_DONTWAIT from caller.
E 69
 */
I 73
int MCFail;

E 73
E 47
E 19
struct mbuf *
D 69
m_copy(m, off, len)
E 69
I 69
m_copym(m, off0, len, wait)
E 69
	register struct mbuf *m;
D 69
	int off;
E 69
I 69
	int off0, wait;
E 69
	register int len;
{
	register struct mbuf *n, **np;
D 69
	struct mbuf *top, *p;
E 69
I 69
	register int off = off0;
	struct mbuf *top;
	int copyhdr = 0;
E 69
I 41
D 45
	int type;
E 45
E 41
D 36
COUNT(M_COPY);
E 36

D 69
	if (len == 0)
		return (0);
E 69
	if (off < 0 || len < 0)
D 69
		panic("m_copy");
E 69
I 69
		panic("m_copym");
	if (off == 0 && m->m_flags & M_PKTHDR)
		copyhdr = 1;
E 69
I 41
D 45
	type = m->m_type;
E 45
E 41
	while (off > 0) {
		if (m == 0)
D 69
			panic("m_copy");
E 69
I 69
			panic("m_copym");
E 69
		if (off < m->m_len)
			break;
		off -= m->m_len;
		m = m->m_next;
	}
	np = &top;
	top = 0;
	while (len > 0) {
I 27
		if (m == 0) {
			if (len != M_COPYALL)
D 69
				panic("m_copy");
E 69
I 69
				panic("m_copym");
E 69
			break;
		}
E 27
D 41
		MGET(n, 1);
E 41
I 41
D 45
		MGET(n, M_WAIT, type);
E 45
I 45
D 47
		MGET(n, M_WAIT, m->m_type);
E 47
I 47
D 69
		MGET(n, M_DONTWAIT, m->m_type);
E 69
I 69
		MGET(n, wait, m->m_type);
E 69
E 47
E 45
E 41
		*np = n;
		if (n == 0)
			goto nospace;
I 69
		if (copyhdr) {
			M_COPY_PKTHDR(n, m);
			if (len == M_COPYALL)
				n->m_pkthdr.len -= off0;
			else
				n->m_pkthdr.len = len;
			copyhdr = 0;
		}
E 69
D 27
		if (m == 0)
			panic("m_copy");
E 27
D 81
		n->m_len = MIN(len, m->m_len - off);
E 81
I 81
		n->m_len = min(len, m->m_len - off);
E 81
D 69
		if (m->m_off > MMAXOFF) {
			p = mtod(m, struct mbuf *);
			n->m_off = ((int)p - (int)n) + off;
D 17
			mprefcnt[mtopf(p)]++;
E 17
I 17
			mclrefcnt[mtocl(p)]++;
E 69
I 69
		if (m->m_flags & M_EXT) {
			n->m_data = m->m_data + off;
			mclrefcnt[mtocl(m->m_ext.ext_buf)]++;
			n->m_ext = m->m_ext;
			n->m_flags |= M_EXT;
E 69
E 17
D 37
		} else {
			n->m_off = MMINOFF;
E 37
I 37
		} else
E 37
			bcopy(mtod(m, caddr_t)+off, mtod(n, caddr_t),
			    (unsigned)n->m_len);
D 37
		}
E 37
D 27
		len -= n->m_len;
E 27
I 27
		if (len != M_COPYALL)
			len -= n->m_len;
E 27
		off = 0;
		m = m->m_next;
		np = &n->m_next;
	}
I 73
	if (top == 0)
		MCFail++;
E 73
	return (top);
nospace:
D 22
	printf("m_copy: no space\n");
E 22
	m_freem(top);
I 73
	MCFail++;
E 73
	return (0);
I 64
}

/*
 * Copy data from an mbuf chain starting "off" bytes from the beginning,
 * continuing for "len" bytes, into the indicated buffer.
 */
I 89
void
E 89
D 65
struct mbuf *
E 65
m_copydata(m, off, len, cp)
	register struct mbuf *m;
D 65
	int off;
E 65
I 65
	register int off;
E 65
	register int len;
D 65
	caddr_t *cp;
E 65
I 65
	caddr_t cp;
E 65
{
	register unsigned count;

	if (off < 0 || len < 0)
		panic("m_copydata");
	while (off > 0) {
		if (m == 0)
			panic("m_copydata");
		if (off < m->m_len)
			break;
		off -= m->m_len;
		m = m->m_next;
	}
	while (len > 0) {
		if (m == 0)
			panic("m_copydata");
D 65
		count = MIN(m->m_len, len);
E 65
I 65
D 81
		count = MIN(m->m_len - off, len);
E 81
I 81
		count = min(m->m_len - off, len);
E 81
E 65
		bcopy(mtod(m, caddr_t) + off, cp, count);
		len -= count;
I 65
		cp += count;
E 65
		off = 0;
		m = m->m_next;
	}
E 64
E 11
E 10
}

I 69
/*
 * Concatenate mbuf chain n to m.
 * Both chains must be of the same type (e.g. MT_DATA).
 * Any m_pkthdr is not updated.
 */
I 89
void
E 89
E 69
D 6

mbufinit()                      /* init network buffer mgmt system */
E 6
I 6
D 8
mbufinit()
E 8
I 8
D 19
mbinit()
E 8
E 6
{
	register struct mbuf *m;
	register i;

COUNT(MBUFINIT);
D 8
	m = (struct mbuf *)&netutl[0];  /* ->start of buffer virt mem */
	vmemall(&Netmap[0], 2, proc, CSYS);
	vmaccess(&Netmap[0], m, 2);
E 8
I 8
	m = (struct mbuf *)&mbutl[0];  /* ->start of buffer virt mem */
D 10
	vmemall(&Mbmap[0], 2, proc, CSYS);
	vmaccess(&Mbmap[0], m, 2);
E 10
I 10
	(void) vmemall(&Mbmap[0], 2, proc, CSYS);
	vmaccess(&Mbmap[0], (caddr_t)m, 2);
E 10
E 8
D 17
	for (i=0; i < NMBPG; i++) {
E 17
I 17
	for (i=0; i < CLBYTES / sizeof (struct mbuf); i++) {
E 17
I 2
		m->m_off = 0;
E 2
D 13
		m_free(m);
E 13
I 13
		(void) m_free(m);
E 13
		m++;
	}
D 10
	pg_alloc(3);
E 10
I 10
D 17
	(void) pg_alloc(3);
E 17
I 17
	(void) m_pgalloc(3);
E 17
E 10
D 5
	netcb.n_pages = 4;
	netcb.n_bufs = 32;
	netcb.n_lowat = 16;
	netcb.n_hiwat = 32;
E 5
I 5
	mbstat.m_pages = 4;
	mbstat.m_bufs = 32;
	mbstat.m_lowat = 16;
	mbstat.m_hiwat = 32;
I 6
D 10
	{ int i,j,k,n;
E 10
I 10
	{ int j,k,n;
E 10
	n = 32;
	k = n << 1;
D 8
	if ((i = rmalloc(netmap, n)) == 0)
E 8
I 8
	if ((i = rmalloc(mbmap, n)) == 0)
E 8
D 10
		return (0);
E 10
I 10
		panic("mbinit");
E 10
	j = i<<1;
D 17
	m = pftom(i);
E 17
I 17
	m = cltom(i);
E 17
	/* should use vmemall sometimes */
D 8
	if (memall(&Netmap[j], k, proc, CSYS) == 0) {
E 8
I 8
	if (memall(&Mbmap[j], k, proc, CSYS) == 0) {
E 8
		printf("botch\n");
		return;
	}
D 8
	vmaccess(&Netmap[j], (caddr_t)m, k);
E 8
I 8
	vmaccess(&Mbmap[j], (caddr_t)m, k);
E 8
	for (j=0; j < n; j++) {
		m->m_off = 0;
D 17
		m->m_next = mpfree;
		mpfree = m;
		m += NMBPG;
		nmpfree++;
E 17
I 17
		m->m_next = mclfree;
		mclfree = m;
		m += CLBYTES / sizeof (*m);
		nmclfree++;
E 17
	}
	}
E 6
E 5
}

D 17
pg_alloc(n)
E 17
I 17
m_pgalloc(n)
E 17
	register int n;
{
	register i, j, k;
	register struct mbuf *m;
	int bufs, s;

D 17
COUNT(PG_ALLOC);
E 17
I 17
COUNT(M_PGALLOC);
E 17
	k = n << 1;
D 8
	if ((i = rmalloc(netmap, n)) == 0)
E 8
I 8
	if ((i = rmalloc(mbmap, n)) == 0)
E 8
		return (0);
	j = i<<1;
D 17
	m = pftom(i);
E 17
I 17
	m = cltom(i);
E 17
	/* should use vmemall sometimes */
D 8
	if (memall(&Netmap[j], k, proc, CSYS) == 0)
E 8
I 8
	if (memall(&Mbmap[j], k, proc, CSYS) == 0)
E 8
		return (0);
D 8
	vmaccess(&Netmap[j], (caddr_t)m, k);
E 8
I 8
	vmaccess(&Mbmap[j], (caddr_t)m, k);
E 8
	bufs = n << 3;
D 5
	s = spl_imp();
E 5
I 5
	s = splimp();
E 5
	for (j=0; j < bufs; j++) {
I 2
		m->m_off = 0;
E 2
D 13
		m_free(m);
E 13
I 13
		(void) m_free(m);
E 13
		m++;
	}
	splx(s);
D 5
	netcb.n_pages += n;
E 5
I 5
	mbstat.m_pages += n;
E 5
	return (1);
}

I 17
/*ARGSUSED*/
m_pgfree(addr, n)
	caddr_t addr;
	int n;
{

COUNT(M_PGFREE);
	printf("m_pgfree %x %d\n", addr, n);
}

E 17
m_expand()
{
	register i;
D 6
	register struct ipq *fp;
	register struct ip *q;
	register struct tcb *tp;
E 6
D 10
	register struct mbuf *m, *n;
E 10
	int need, needp, needs;

COUNT(M_EXPAND);
D 5
	needs = need = netcb.n_hiwat - netcb.n_bufs;    /* #bufs to add */
	needp = need >> 3;                              /* #pages to add */
E 5
I 5
	needs = need = mbstat.m_hiwat - mbstat.m_bufs;
	needp = need >> 3;
E 5
D 17
	if (pg_alloc(needp))
E 17
I 17
	if (m_pgalloc(needp))
E 17
		return (1);
D 6
	for (i=0; i < needp; i++, need-=NMBPG)
		if (needp == 1 || pg_alloc(1) == 0)		/* ??? */
E 6
I 6
D 17
	for (i=0; i < needp; i++, need -= NMBPG)
		if (pg_alloc(1) == 0)
E 17
I 17
	for (i=0; i < needp; i++, need -= CLBYTES / sizeof (struct mbuf))
		if (m_pgalloc(1) == 0)
E 17
E 6
			goto steal;
	return (need < needs);
steal:
D 5
	fp = netcb.n_ip_tail;           /* ip reass.q */
	while (need > 0 && fp) {
		q = fp->iqx.ip_next;    /* free mbufs assoc. w/chain */
		while (q != (struct ip *)fp) {
			need -= m_freem(dtom(q));
			q = q->ip_next;
		}
		ip_freef(fp);           /* free header */
		fp = netcb.n_ip_tail;
	}
	tp = netcb.n_tcb_tail;          /* ->tcbs */
	while (need > 0 && tp != NULL) {
		m = tp->t_rcv_unack;
		while (m != NULL) {
			n = m->m_act;
			need -= m_freem(m);
			m = n;
		}
		tp->t_rcv_unack = NULL;
		tp = tp->t_tcb_prev;
	}
E 5
I 5
D 6
#ifdef notdef
	/* free fragments */
	/* free unacks */
#endif
E 5
	return (need < needs);
E 6
I 6
	/* while (not enough) ask protocols to free code */
	;
I 10
	return (0);
E 10
E 6
}

#ifdef notdef
m_relse()
{
D 5
	int free;

E 5
D 6
COUNT(M_RELSE);
E 6
D 5
	free = (netcb.n_bufs - netcb.n_hiwat) >> 3;    /* # excess free pages */
	return;
E 5
I 5

I 6
COUNT(M_RELSE);
E 6
E 5
}
#endif

E 19
D 6
struct mbuf *
E 6
I 6
m_cat(m, n)
	register struct mbuf *m, *n;
{
D 30

E 30
	while (m->m_next)
		m = m->m_next;
D 30
	while (n)
D 28
		if (m->m_off + m->m_len + n->m_len <= MMAXOFF) {
E 28
I 28
		if (m->m_off < MMAXOFF &&
		    m->m_off + m->m_len + n->m_len <= MMAXOFF) {
E 28
D 10
			bcopy(mtod(n, caddr_t), mtod(m, caddr_t) + m->m_len, n->m_len);
E 10
I 10
			bcopy(mtod(n, caddr_t), mtod(m, caddr_t) + m->m_len,
			    (u_int)n->m_len);
E 10
			m->m_len += n->m_len;
			n = m_free(n);
		} else {
E 30
I 30
	while (n) {
D 69
		if (m->m_off >= MMAXOFF ||
		    m->m_off + m->m_len + n->m_len > MMAXOFF) {
E 69
I 69
		if (m->m_flags & M_EXT ||
		    m->m_data + m->m_len + n->m_len >= &m->m_dat[MLEN]) {
E 69
			/* just join the two chains */
E 30
			m->m_next = n;
D 30
			m = n;
			n = m->m_next;
E 30
I 30
			return;
E 30
		}
I 30
		/* splat the data from one into the other */
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t) + m->m_len,
		    (u_int)n->m_len);
		m->m_len += n->m_len;
		n = m_free(n);
	}
E 30
}

I 88
void
E 88
E 6
D 69
m_adj(mp, len)
E 69
I 69
m_adj(mp, req_len)
E 69
	struct mbuf *mp;
I 80
	int req_len;
E 80
D 10
	register len;
E 10
I 10
D 69
	register int len;
E 69
E 10
{
I 69
	register int len = req_len;
E 69
D 51
	register struct mbuf *m, *n;
E 51
I 51
	register struct mbuf *m;
	register count;
E 51

I 6
D 8
/*
	for (m = mp; m; m = m->m_next) {
		printf("a %x %d\n", m, m->m_len);
	}
*/
E 8
E 6
D 36
COUNT(M_ADJ);
E 36
	if ((m = mp) == NULL)
		return;
D 8
	if (len >= 0) {                 /* adjust from top of msg chain */
E 8
I 8
	if (len >= 0) {
I 69
		/*
		 * Trim from head.
		 */
E 69
E 8
		while (m != NULL && len > 0) {
D 8
			if (m->m_len <= len) {          /* free this mbuf */
E 8
I 8
			if (m->m_len <= len) {
E 8
				len -= m->m_len;
				m->m_len = 0;
				m = m->m_next;
D 8
			} else {                        /* adjust mbuf */
E 8
I 8
			} else {
E 8
				m->m_len -= len;
D 69
				m->m_off += len;
				break;
E 69
I 69
				m->m_data += len;
				len = 0;
E 69
			}
		}
I 69
		m = mp;
		if (mp->m_flags & M_PKTHDR)
			m->m_pkthdr.len -= (req_len - len);
E 69
D 8

	} else {                        /* adjust from bottom of msg chain */
E 8
I 8
	} else {
D 51
		/* a 2 pass algorithm might be better */
E 51
I 51
		/*
		 * Trim from tail.  Scan the mbuf chain,
		 * calculating its length and finding the last mbuf.
		 * If the adjustment only affects this mbuf, then just
		 * adjust and return.  Otherwise, rescan and truncate
		 * after the remaining size.
		 */
E 51
E 8
		len = -len;
D 51
		while (len > 0 && m->m_len != 0) {
D 8
			/* find end of chain */
E 8
			while (m != NULL && m->m_len != 0) {
				n = m;
				m = m->m_next;
			}
D 8
			if (n->m_len <= len) {          /* last mbuf */
E 8
I 8
			if (n->m_len <= len) {
E 8
				len -= n->m_len;
				n->m_len = 0;
				m = mp;
D 8
			} else {                        /* adjust length */
E 8
I 8
			} else {
E 8
				n->m_len -= len;
E 51
I 51
		count = 0;
		for (;;) {
			count += m->m_len;
			if (m->m_next == (struct mbuf *)0)
E 51
				break;
I 51
			m = m->m_next;
		}
		if (m->m_len >= len) {
			m->m_len -= len;
I 70
D 85
			if ((mp = m)->m_flags & M_PKTHDR)
				m->m_pkthdr.len -= len;
E 85
I 85
			if (mp->m_flags & M_PKTHDR)
				mp->m_pkthdr.len -= len;
E 85
E 70
			return;
		}
		count -= len;
I 69
		if (count < 0)
			count = 0;
E 69
		/*
		 * Correct length for chain is "count".
		 * Find the mbuf with last data, adjust its length,
		 * and toss data from remaining mbufs on chain.
		 */
D 69
		for (m = mp; m; m = m->m_next) {
E 69
I 69
		m = mp;
		if (m->m_flags & M_PKTHDR)
			m->m_pkthdr.len = count;
		for (; m; m = m->m_next) {
E 69
			if (m->m_len >= count) {
				m->m_len = count;
				break;
E 51
			}
I 51
			count -= m->m_len;
E 51
		}
I 51
		while (m = m->m_next)
			m->m_len = 0;
E 51
	}
I 19
}

I 49
/*
 * Rearange an mbuf chain so that len bytes are contiguous
 * and in the data area of an mbuf (so that mtod and dtom
D 51
 * will work for a structure of size len).
 * Returns the resulting mbuf chain on success,
 * frees it and returns null on failure.
E 51
I 51
 * will work for a structure of size len).  Returns the resulting
 * mbuf chain on success, frees it and returns null on failure.
D 69
 * If there is room, it will add up to MPULL_EXTRA bytes to the
E 69
I 69
 * If there is room, it will add up to max_protohdr-len extra bytes to the
E 69
 * contiguous region in an attempt to avoid being called next time.
E 51
 */
I 73
int MPFail;

E 73
E 49
D 25
/*ARGSUSED*/
m_pullup(m, len)
	struct mbuf *m;
E 25
I 25
struct mbuf *
D 51
m_pullup(m0, len)
	struct mbuf *m0;
E 51
I 51
m_pullup(n, len)
	register struct mbuf *n;
E 51
E 25
	int len;
{
I 25
D 51
	register struct mbuf *m, *n;
D 32
	int cnt;
E 32
I 32
	int count;
E 51
I 51
	register struct mbuf *m;
	register int count;
	int space;
E 51
E 32
E 25

I 29
D 51
	n = m0;
E 29
I 25
	if (len > MLEN)
		goto bad;
D 37
	MGET(m, 0);
E 37
I 37
D 41
	MGET(m, M_DONTWAIT);
E 41
I 41
	MGET(m, M_DONTWAIT, n->m_type);
E 41
E 37
	if (m == 0)
		goto bad;
D 37
	m->m_off = MMINOFF;
E 37
	m->m_len = 0;
E 51
I 51
D 69
	if (n->m_off + len <= MMAXOFF && n->m_next) {
E 69
I 69
	/*
	 * If first mbuf has no cluster, and has room for len bytes
	 * without shifting current data, pullup into it,
	 * otherwise allocate a new mbuf to prepend to the chain.
	 */
	if ((n->m_flags & M_EXT) == 0 &&
	    n->m_data + len < &n->m_dat[MLEN] && n->m_next) {
		if (n->m_len >= len)
			return (n);
E 69
		m = n;
		n = n->m_next;
		len -= m->m_len;
	} else {
D 69
		if (len > MLEN)
E 69
I 69
		if (len > MHLEN)
E 69
			goto bad;
		MGET(m, M_DONTWAIT, n->m_type);
		if (m == 0)
			goto bad;
		m->m_len = 0;
I 69
D 75
		if (n->m_flags & M_PKTHDR)
E 75
I 75
		if (n->m_flags & M_PKTHDR) {
E 75
			M_COPY_PKTHDR(m, n);
I 75
			n->m_flags &= ~M_PKTHDR;
		}
E 75
E 69
	}
D 69
	space = MMAXOFF - m->m_off;
E 69
I 69
	space = &m->m_dat[MLEN] - (m->m_data + m->m_len);
E 69
E 51
D 29
	n = m0;
E 29
	do {
D 32
		cnt = MIN(MLEN - m->m_len, len);
		if (cnt > n->m_len)
			cnt = n->m_len;
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t)+m->m_len, cnt);
		len -= cnt;
		m->m_len += cnt;
		n->m_off += cnt;
		n->m_len -= cnt;
E 32
I 32
D 49
		count = MIN(MLEN - m->m_len, len);
		if (count > n->m_len)
			count = n->m_len;
E 49
I 49
D 51
		count = MIN(n->m_len, len);
E 51
I 51
D 69
		count = MIN(MIN(space - m->m_len, len + MPULL_EXTRA), n->m_len);
E 51
E 49
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t)+m->m_len,
E 69
I 69
		count = min(min(max(len, max_protohdr), space), n->m_len);
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t) + m->m_len,
E 69
		  (unsigned)count);
		len -= count;
		m->m_len += count;
D 49
		n->m_off += count;
E 49
		n->m_len -= count;
I 69
		space -= count;
E 69
E 32
		if (n->m_len)
D 49
			break;
		n = m_free(n);
	} while (n);
E 49
I 49
D 69
			n->m_off += count;
E 69
I 69
			n->m_data += count;
E 69
		else
			n = m_free(n);
D 51
	} while (len && n);
E 49
	if (len) {
E 51
I 51
	} while (len > 0 && n);
	if (len > 0) {
E 51
		(void) m_free(m);
		goto bad;
	}
	m->m_next = n;
	return (m);
bad:
D 29
	m_freem(m0);
E 29
I 29
	m_freem(n);
I 73
	MPFail++;
E 73
E 29
E 25
	return (0);
E 19
D 8
}

/*
 * convert mbuf virtual to physical addr for uballoc
 */
mtophys(m)
	register struct mbuf *m;
{
	register i;
	register unsigned long addr;
	register struct pte *pte;

COUNT(MTOPHYS);
	i = (((int)m & ~PGOFSET) - (int)netutl) >> PGSHIFT;
	pte = &Netmap[i];
	addr = (pte->pg_pfnum << PGSHIFT) | ((int)m & PGOFSET);
	return (addr);
E 8
I 3
D 6
}

m_cat(m, n)
	register struct mbuf *m, *n;
{

	while (m->m_next)
		m = m->m_next;
	while (n)
		if (m->m_off + m->m_len + n->m_len <= MMAXOFF) {
D 4
			bcopy(mtod(n), mtod(m) + m->m_len, n->m_len);
E 4
I 4
			bcopy(mtod(n, caddr_t), mtod(m, caddr_t) + m->m_len, n->m_len);
E 4
			m->m_len += n->m_len;
			n = m_free(n);
		} else {
			m->m_next = n;
			m = n;
			n = m->m_next;
		}
E 6
E 3
}
I 78

/*
 * Partition an mbuf chain in two pieces, returning the tail --
 * all but the first len0 bytes.  In case of failure, it returns NULL and
 * attempts to restore the chain to its original state.
 */
struct mbuf *
m_split(m0, len0, wait)
D 80
register struct mbuf *m0;
int len0;
E 80
I 80
	register struct mbuf *m0;
	int len0, wait;
E 80
{
	register struct mbuf *m, *n;
	unsigned len = len0, remain;

	for (m = m0; m && len > m->m_len; m = m->m_next)
		len -= m->m_len;
	if (m == 0)
		return (0);
	remain = m->m_len - len;
	if (m0->m_flags & M_PKTHDR) {
		MGETHDR(n, wait, m0->m_type);
		if (n == 0)
			return (0);
		n->m_pkthdr.rcvif = m0->m_pkthdr.rcvif;
		n->m_pkthdr.len = m0->m_pkthdr.len - len0;
		m0->m_pkthdr.len = len0;
		if (m->m_flags & M_EXT)
			goto extpacket;
		if (remain > MHLEN) {
			/* m can't be the lead packet */
			MH_ALIGN(n, 0);
			n->m_next = m_split(m, len, wait);
			if (n->m_next == 0) {
				(void) m_free(n);
				return (0);
			} else
				return (n);
		} else
			MH_ALIGN(n, remain);
	} else if (remain == 0) {
		n = m->m_next;
		m->m_next = 0;
		return (n);
	} else {
		MGET(n, wait, m->m_type);
		if (n == 0)
			return (0);
		M_ALIGN(n, remain);
	}
extpacket:
	if (m->m_flags & M_EXT) {
		n->m_flags |= M_EXT;
		n->m_ext = m->m_ext;
		mclrefcnt[mtocl(m->m_ext.ext_buf)]++;
		m->m_ext.ext_size = 0; /* For Accounting XXXXXX danger */
		n->m_data = m->m_data + len;
	} else {
		bcopy(mtod(m, caddr_t) + len, mtod(n, caddr_t), remain);
	}
	n->m_len = remain;
	m->m_len = len;
	n->m_next = m->m_next;
	m->m_next = 0;
	return (n);
}
/*
 * Routine to copy from device local memory into mbufs.
 */
struct mbuf *
m_devget(buf, totlen, off0, ifp, copy)
	char *buf;
	int totlen, off0;
	struct ifnet *ifp;
	void (*copy)();
{
	register struct mbuf *m;
	struct mbuf *top = 0, **mp = &top;
	register int off = off0, len;
	register char *cp;
	char *epkt;

	cp = buf;
	epkt = cp + totlen;
	if (off) {
D 89
		cp += off + 2 * sizeof(u_short);
		totlen -= 2 * sizeof(u_short);
E 89
I 89
		/*
		 * If 'off' is non-zero, packet is trailer-encapsulated,
		 * so we have to skip the type and length fields.
		 */
		cp += off + 2 * sizeof(u_int16_t);
		totlen -= 2 * sizeof(u_int16_t);
E 89
	}
	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m == 0)
		return (0);
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = totlen;
	m->m_len = MHLEN;

	while (totlen > 0) {
		if (top) {
			MGET(m, M_DONTWAIT, MT_DATA);
			if (m == 0) {
				m_freem(top);
				return (0);
			}
			m->m_len = MLEN;
		}
		len = min(totlen, epkt - cp);
		if (len >= MINCLSIZE) {
			MCLGET(m, M_DONTWAIT);
			if (m->m_flags & M_EXT)
				m->m_len = len = min(len, MCLBYTES);
			else
				len = m->m_len;
		} else {
			/*
			 * Place initial small packet/header at end of mbuf.
			 */
			if (len < m->m_len) {
				if (top == 0 && len + max_linkhdr <= m->m_len)
					m->m_data += max_linkhdr;
				m->m_len = len;
			} else
				len = m->m_len;
		}
		if (copy)
			copy(cp, mtod(m, caddr_t), (unsigned)len);
		else
			bcopy(cp, mtod(m, caddr_t), (unsigned)len);
		cp += len;
		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		if (cp == epkt)
			cp = buf;
	}
	return (top);
}
E 78
E 1
