h45611
s 00015/00000/00355
d D 8.4 95/05/20 01:19:56 mckusick 48 47
c attempt to avoid spurious simple_lock complaints from interrupt level
e
s 00001/00001/00354
d D 8.3 94/01/04 18:41:14 bostic 47 46
c lint
e
s 00001/00001/00354
d D 8.2 93/11/30 16:07:41 mckusick 46 45
c lint
e
s 00002/00002/00353
d D 8.1 93/06/10 21:57:27 bostic 45 44
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00353
d D 7.38 93/01/21 17:08:02 mckusick 44 43
c NULL is not always a valid kernel address
e
s 00006/00000/00348
d D 7.37 92/12/11 16:07:39 mckusick 43 42
c check bad (modified) addresses on freelist before using them
e
s 00001/00000/00347
d D 7.36 92/10/22 15:43:43 mckusick 42 41
c track allocation sizes
e
s 00008/00007/00339
d D 7.35 92/10/11 10:38:07 bostic 41 40
c make kernel includes standard
e
s 00009/00002/00337
d D 7.34 92/10/09 23:34:05 mckusick 40 38
c use kb_last to reference last element in free chain
e
s 00041/00000/00339
d D 7.33.1.1 92/05/20 15:33:44 mckusick 39 38
c track previous bucket elements that modify things that follow them
e
s 00005/00004/00334
d D 7.33 92/05/20 15:31:52 mckusick 38 37
c if possible, straddle forward pointer across two words
e
s 00014/00008/00324
d D 7.32 92/03/14 20:05:18 ralph 37 36
c fix byte order bug with DIAGNOSTIC, also range check memname[type].
e
s 00034/00031/00298
d D 7.31 92/03/13 17:32:17 mckusick 36 35
c use different values to null out freed structures
e
s 00003/00005/00326
d D 7.30 92/02/15 22:20:36 mckusick 35 34
c more descriptive panic message
e
s 00003/00003/00328
d D 7.29 92/02/05 23:38:18 torek 34 33
c lint
e
s 00001/00001/00330
d D 7.28 91/09/03 11:16:20 mckusick 33 32
c do not panic after modified data found on the freelist
e
s 00051/00014/00280
d D 7.27 91/08/29 23:13:05 mckusick 32 31
c save type when freeing an piece of memory so it can be printed out
c if the piece of memory is found to be modified when it is later reallocated
e
s 00076/00013/00218
d D 7.26 91/08/01 23:10:19 mckusick 31 29
c under DIAGNOSTIC, check for duplicate frees and data modification after freeing
e
s 00006/00000/00231
d D 7.25.1.1 91/05/19 14:36:08 mckusick 30 29
c name resolution checking (need kern/kern_malloc.c 7.25.1.1,
c kern/vfs_lookup.c 7.31.1.1, kern/vfs_syscalls.c 7.70.1.1,
c nfs/nfs_serv.c 7.40.1.1, nfs/nfs_syscalls.c 7.26.1.1,
c ufs/ufs_vnops.c 7.64.1.1, and hp300/hp300/trap.c 7.14.1.1
e
s 00001/00001/00230
d D 7.25 91/05/08 11:56:52 karels 29 28
c update copyright date
e
s 00005/00005/00226
d D 7.24 91/05/04 14:08:41 karels 28 27
c malloc now returns void *
e
s 00002/00005/00229
d D 7.23 91/04/20 15:08:05 karels 27 26
c fix includes
e
s 00008/00002/00226
d D 7.22 91/02/04 18:33:37 karels 26 24
c protect free list from lossage if multiple procs try to fill bucket
e
s 00034/00020/00247
d D 7.12.1.2 90/12/12 16:41:13 sklower 25 14
c update 7.12.1.1 to match 7.20 plus leak-fix from hibler abt 
c info returned while blocked in vmemall
e
s 00013/00033/00215
d D 7.21 90/12/05 16:42:36 mckusick 24 23
c update for new VM
e
s 00003/00002/00245
d D 7.20 90/08/29 14:22:21 mckusick 23 22
c use tsleep to identify the resource being waited for
e
s 00021/00001/00226
d D 7.19 90/07/27 15:16:40 mckusick 22 21
c check for valid free address
e
s 00001/00011/00226
d D 7.18 90/06/28 21:20:16 bostic 21 20
c new copyright notice
e
s 00001/00001/00236
d D 7.17 90/05/15 14:07:27 mckusick 20 19
c fix from Hibler
e
s 00000/00009/00237
d D 7.16 90/04/06 11:44:30 sklower 19 18
c same as 7.14 (7.15 just records debugging code)
e
s 00009/00000/00237
d D 7.15 90/04/06 11:42:59 sklower 18 16
c document debugging code (collect refusal modes)
e
s 00010/00001/00236
d R 7.15 90/04/05 14:17:59 sklower 17 16
c gross hack to distinguish between different malloc failures
e
s 00001/00001/00236
d D 7.14 89/12/19 11:31:30 mckusick 16 13
c return free pages to head of free list
e
s 00000/00000/00237
d R 7.14 89/12/14 09:47:58 sklower 15 13
c phoney delta to see how branches work
e
s 00034/00005/00233
d D 7.12.1.1 89/12/14 09:46:40 sklower 14 12
c Branch delta to check for re-entrancy
e
s 00002/00003/00235
d D 7.13 89/08/17 16:32:11 karels 13 12
c always check malloc type if using the type for stats
e
s 00001/00001/00237
d D 7.12 89/04/25 10:49:12 mckusick 12 11
c ../machine => machine
e
s 00004/00000/00234
d D 7.11 89/04/22 12:26:31 sklower 11 10
c checkpoint for version to be handed to NIST, simple tp4 connection
e
s 00010/00005/00224
d D 7.10 88/06/29 17:15:02 bostic 10 9
c install approved copyright notice
e
s 00019/00014/00210
d D 7.9 88/05/27 16:42:22 karels 9 8
c lint
e
s 00013/00009/00211
d D 7.8 88/02/27 16:18:27 mckusick 8 7
c limit is now enforced as a function of memory use 
c rather than based on number of allocations
e
s 00010/00007/00210
d D 7.7 88/02/18 16:17:03 mckusick 7 6
c correct statistic for `total elements allocated'
e
s 00008/00002/00209
d D 7.6 88/02/06 11:00:10 mckusick 6 5
c change copyright
e
s 00050/00017/00161
d D 7.5 88/02/06 10:55:39 mckusick 5 4
c put in needed sleeps; more detailed statistics
e
s 00003/00002/00175
d D 7.4 87/10/23 14:08:09 kre 4 3
c fix problems with allocation of the last page (or allocation
c of the last cluster after the previous fix)
e
s 00001/00001/00176
d D 7.3 87/10/22 19:47:42 kre 3 2
c base mem allocation at cluster boundary.
e
s 00000/00001/00177
d D 7.2 87/06/22 19:40:57 mckusick 2 1
c one statistic too many
e
s 00178/00000/00000
d D 7.1 87/06/06 13:25:59 mckusick 1 0
c date and time created 87/06/06 13:25:59 by mckusick
e
u
U
f b 
t
T
I 1
/*
D 29
 * Copyright (c) 1987 Regents of the University of California.
E 29
I 29
D 45
 * Copyright (c) 1987, 1991 The Regents of the University of California.
E 29
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 45
I 45
 * Copyright (c) 1987, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 45
 *
D 21
D 25
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 25
I 25
 * %sccs.include.redist.c%
E 25
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 10
E 6
 *
 *	%W% (Berkeley) %G%
 */

D 41
#include "param.h"
D 24
#include "vm.h"
E 24
D 27
#include "cmap.h"
#include "time.h"
E 27
#include "proc.h"
#include "map.h"
#include "kernel.h"
#include "malloc.h"
I 24
D 27
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
E 27
I 27
#include "vm/vm.h"
#include "vm/vm_kern.h"
E 41
I 41
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/map.h>
#include <sys/kernel.h>
#include <sys/malloc.h>

#include <vm/vm.h>
#include <vm/vm_kern.h>
E 41
E 27
E 24

D 12
#include "../machine/pte.h"
E 12
I 12
D 24
#include "machine/pte.h"
E 12

E 24
struct kmembuckets bucket[MINBUCKET + 16];
struct kmemstats kmemstats[M_LAST];
struct kmemusage *kmemusage;
I 25
char *memname[] = INITKMEMNAMES;
E 25
I 24
char *kmembase, *kmemlimit;
E 24
I 23
char *memname[] = INITKMEMNAMES;
E 23
I 5
D 24
long wantkmemmap;
E 24
I 14
long malloc_reentered;
#define IN { if (malloc_reentered) panic("malloc reentered");\
			else malloc_reentered = 1;}
#define OUT (malloc_reentered = 0)
E 14
E 5

I 31
#ifdef DIAGNOSTIC
E 31
I 18
D 19
struct {
	int	nomap;
	int	atlimit;
	int	freemem;
} KFail;

E 19
E 18
/*
I 31
D 36
 * This structure serves two purposes.
 * The first is to provide a set of masks to catch unaligned frees.
 * The second is to provide known text to copy into free objects so
 * that modifications after frees can be detected.
E 36
I 36
 * This structure provides a set of masks to catch unaligned frees.
E 36
 */
D 36
#define WEIRD_ADDR 0xdeadbeef
long addrmask[] = { WEIRD_ADDR,
E 36
I 36
long addrmask[] = { 0,
E 36
	0x00000001, 0x00000003, 0x00000007, 0x0000000f,
	0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
	0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
	0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
};
I 32

/*
I 36
 * The WEIRD_ADDR is used as known text to copy into free objects so
 * that modifications after frees can be detected.
 */
#define WEIRD_ADDR	0xdeadbeef
#define MAX_COPY	32

/*
E 36
 * Normally the first word of the structure is used to hold the list
 * pointer for free objects. However, when running with diagnostics,
 * we use the third and fourth fields, so as to catch modifications
 * in the most commonly trashed first two words.
 */
struct freelist {
	long	spare0;
D 38
	long	spare1;
E 38
	short	type;
D 38
	short	spare2;
E 38
I 38
	long	spare1;
E 38
	caddr_t	next;
};
#else /* !DIAGNOSTIC */
struct freelist {
	caddr_t	next;
};
E 32
#endif /* DIAGNOSTIC */

I 39
struct uselist {
	struct	uselist *next;
	caddr_t	mem;
	long	size;
	long	type;
} *listhd;

E 39
/*
E 31
 * Allocate a block of memory
 */
D 7
qaddr_t malloc(size, type, flags)
E 7
I 7
D 28
qaddr_t
E 28
I 28
void *
E 28
malloc(size, type, flags)
E 7
	unsigned long size;
D 9
	long type, flags;
E 9
I 9
	int type, flags;
E 9
{
	register struct kmembuckets *kbp;
	register struct kmemusage *kup;
I 32
	register struct freelist *freep;
E 32
D 9
	long indx, npg, alloc, allocsize, s;
E 9
I 9
D 47
	long indx, npg, alloc, allocsize;
E 47
I 47
	long indx, npg, allocsize;
E 47
	int s;
E 9
D 25
D 26
	caddr_t va, cp;
E 26
I 26
	caddr_t va, cp, savedlist;
I 31
#ifdef DIAGNOSTIC
D 36
	int i, copysize;
E 36
I 36
	long *end, *lp;
	int copysize;
E 36
I 32
D 37
	short savedtype;
E 37
I 37
	char *savedtype;
I 39
	struct uselist *mlp;
E 39
E 37
E 32
#endif
I 48
#ifdef DEBUG
	extern int simplelockrecurse;
#endif
E 48
E 31
E 26
E 25
I 25
	caddr_t va, cp, rp;
E 25
#ifdef KMEMSTATS
D 5
	register struct kmemstats *ksp;

	ksp = &kmemstats[type];
	if (ksp->ks_inuse >= ksp->ks_limit)
		return (0);
E 5
I 5
	register struct kmemstats *ksp = &kmemstats[type];
I 11
D 13
D 25
#if defined(ISO) || defined(TPIP)
	if (((unsigned int)type) > M_LAST)
E 25
I 25

	if (((unsigned long)type) > M_LAST)
E 25
E 13
I 13

I 30
#ifdef DIAGNOSTIC
E 30
	if (((unsigned long)type) > M_LAST)
E 13
		panic("malloc - bogus type");
I 30
	if (type == M_NAMEI)
		curproc->p_spare[0]++;
E 30
D 13
#endif
E 13
E 11
E 5
D 25
#endif
I 30
#endif
E 30
E 25
I 5
D 38

E 38
E 5
	indx = BUCKETINDX(size);
	kbp = &bucket[indx];
	s = splimp();
I 14
	IN;
E 14
I 5
D 24
again:
E 24
#ifdef KMEMSTATS
D 8
	while (ksp->ks_inuse >= ksp->ks_limit) {
E 8
I 8
	while (ksp->ks_memuse >= ksp->ks_limit) {
E 8
		if (flags & M_NOWAIT) {
I 18
D 19
			KFail.atlimit++;
E 19
E 18
I 14
			OUT;
E 14
			splx(s);
D 28
			return (0);
E 28
I 28
			return ((void *) NULL);
E 28
		}
		if (ksp->ks_limblocks < 65535)
			ksp->ks_limblocks++;
I 14
		OUT;
E 14
D 23
D 25
		sleep((caddr_t)ksp, PSWP+2);
E 25
I 25
		tsleep((caddr_t)ksp, PSWP+2, memname[type], 0);
E 25
E 23
I 23
		tsleep((caddr_t)ksp, PSWP+2, memname[type], 0);
E 23
I 14
		IN;
E 14
	}
I 42
	ksp->ks_size |= 1 << indx;
E 42
#endif
I 31
#ifdef DIAGNOSTIC
D 36
	copysize = 1 << indx < sizeof addrmask ? 1 << indx : sizeof addrmask;
E 36
I 36
	copysize = 1 << indx < MAX_COPY ? 1 << indx : MAX_COPY;
E 36
#endif
I 48
#ifdef DEBUG
	if (flags & M_NOWAIT)
		simplelockrecurse++;
#endif
E 48
E 31
E 5
	if (kbp->kb_next == NULL) {
I 40
		kbp->kb_last = NULL;
E 40
		if (size > MAXALLOCSAVE)
			allocsize = roundup(size, CLBYTES);
		else
			allocsize = 1 << indx;
		npg = clrnd(btoc(allocsize));
D 24
		if ((flags & M_NOWAIT) && freemem < npg) {
E 24
I 24
		va = (caddr_t) kmem_malloc(kmem_map, (vm_size_t)ctob(npg),
					   !(flags & M_NOWAIT));
		if (va == NULL) {
E 24
I 18
D 19
			KFail.freemem++;
E 19
E 18
I 14
			OUT;
E 14
			splx(s);
I 48
#ifdef DEBUG
			if (flags & M_NOWAIT)
				simplelockrecurse--;
#endif
E 48
D 28
			return (0);
E 28
I 28
			return ((void *) NULL);
E 28
		}
D 24
		alloc = rmalloc(kmemmap, npg);
		if (alloc == 0) {
D 5
			splx(s);
			return (0);
E 5
I 5
			if (flags & M_NOWAIT) {
I 18
D 19
				KFail.nomap++;
E 19
E 18
I 14
				OUT;
E 14
				splx(s);
				return (0);
			}
E 24
#ifdef KMEMSTATS
D 24
			if (ksp->ks_mapblocks < 65535)
				ksp->ks_mapblocks++;
#endif
			wantkmemmap++;
I 14
			OUT;
E 14
D 23
D 25
			sleep((caddr_t)&wantkmemmap, PSWP+2);
E 25
I 25
			tsleep((caddr_t)&wantkmemmap, PSWP+2, memname[type], 0);
E 25
E 23
I 23
			tsleep((caddr_t)&wantkmemmap, PSWP+2, memname[type], 0);
E 23
I 14
			IN;
E 14
			goto again;
E 5
		}
I 4
		alloc -= CLSIZE;		/* convert to base 0 */
I 25
		OUT;
E 25
E 4
D 5
		if (vmemall(&kmempt[alloc], npg, &proc[0], CSYS) == 0) {
D 4
			rmfree(kmemmap, npg, alloc);
E 4
I 4
			rmfree(kmemmap, npg, alloc+CLSIZE);
E 4
			splx(s);
			return (0);
		}
E 5
I 5
D 9
		(void) vmemall(&kmempt[alloc], npg, &proc[0], CSYS);
E 9
I 9
		(void) vmemall(&kmempt[alloc], (int)npg, &proc[0], CSYS);
I 25
		IN;
E 25
E 9
E 5
		va = (caddr_t) kmemxtob(alloc);
D 9
		vmaccess(&kmempt[alloc], va, npg);
E 9
I 9
		vmaccess(&kmempt[alloc], va, (int)npg);
E 9
#ifdef KMEMSTATS
E 24
		kbp->kb_total += kbp->kb_elmpercl;
#endif
		kup = btokup(va);
		kup->ku_indx = indx;
		if (allocsize > MAXALLOCSAVE) {
			if (npg > 65535)
				panic("malloc: allocation too large");
			kup->ku_pagecnt = npg;
I 5
#ifdef KMEMSTATS
			ksp->ks_memuse += allocsize;
#endif
E 5
			goto out;
		}
#ifdef KMEMSTATS
		kup->ku_freecnt = kbp->kb_elmpercl;
		kbp->kb_totalfree += kbp->kb_elmpercl;
#endif
I 26
		/*
		 * Just in case we blocked while allocating memory,
		 * and someone else also allocated memory for this
		 * bucket, don't assume the list is still empty.
		 */
		savedlist = kbp->kb_next;
E 26
I 25
		rp = kbp->kb_next; /* returned while blocked in vmemall */
E 25
D 37
		kbp->kb_next = va + (npg * NBPG) - allocsize;
D 5
		for(cp = kbp->kb_next; cp > va; cp -= allocsize)
E 5
I 5
D 14
D 31
		for (cp = kbp->kb_next; cp > va; cp -= allocsize)
E 31
I 31
		for (cp = kbp->kb_next; ; cp -= allocsize) {
E 37
I 37
		kbp->kb_next = cp = va + (npg * NBPG) - allocsize;
		for (;;) {
E 37
I 32
			freep = (struct freelist *)cp;
E 32
#ifdef DIAGNOSTIC
			/*
			 * Copy in known text to detect modification
			 * after freeing.
			 */
D 36
			bcopy(addrmask, cp, copysize);
E 36
I 36
			end = (long *)&cp[copysize];
			for (lp = (long *)cp; lp < end; lp++)
				*lp = WEIRD_ADDR;
E 36
I 32
			freep->type = M_FREE;
E 32
#endif /* DIAGNOSTIC */
			if (cp <= va)
				break;
E 31
E 5
D 32
			*(caddr_t *)cp = cp - allocsize;
E 32
I 32
D 37
			freep->next = cp - allocsize;
E 37
I 37
			cp -= allocsize;
			freep->next = cp;
E 37
E 32
I 31
		}
E 31
D 26
		*(caddr_t *)cp = NULL;
E 26
I 26
D 32
		*(caddr_t *)cp = savedlist;
E 32
I 32
		freep->next = savedlist;
I 40
		if (kbp->kb_last == NULL)
			kbp->kb_last = (caddr_t)freep;
E 40
E 32
E 26
E 14
I 14
		for (cp = kbp->kb_next; cp >= va; cp -= allocsize) {
D 25
			((caddr_t *)cp)[2] = (cp > va ? cp - allocsize : NULL);
E 25
I 25
			((caddr_t *)cp)[2] = (cp > va ? cp - allocsize : rp);
E 25
			if (indx == 7) {
				long *lp = (long *)cp;
				lp[0] = lp[1] = lp[3] = lp[4] = -1;
			}
		}
E 14
	}
	va = kbp->kb_next;
D 14
D 32
	kbp->kb_next = *(caddr_t *)va;
E 32
I 32
	kbp->kb_next = ((struct freelist *)va)->next;
E 32
I 31
#ifdef DIAGNOSTIC
D 32
	*(caddr_t *)va = (char *)WEIRD_ADDR;
E 32
I 32
	freep = (struct freelist *)va;
D 37
	savedtype = freep->type;
E 37
I 37
	savedtype = (unsigned)freep->type < M_LAST ?
		memname[freep->type] : "???";
I 43
D 44
	if (!kernacc(kbp->kb_next, sizeof(struct freelist), 0)) {
E 44
I 44
	if (kbp->kb_next &&
	    !kernacc(kbp->kb_next, sizeof(struct freelist), 0)) {
E 44
		printf("%s of object 0x%x size %d %s %s (invalid addr 0x%x)\n",
			"Data modified on freelist: word 2.5", va, size,
			"previous type", savedtype, kbp->kb_next);
		kbp->kb_next = NULL;
	}
E 43
#if BYTE_ORDER == BIG_ENDIAN
E 37
D 36
	freep->type = ((struct freelist *)addrmask)->type;
	freep->next = ((struct freelist *)addrmask)->next;
E 32
	if (bcmp(addrmask, va, copysize)) {
		copysize >>= 2;
		for (i = 0; i < copysize && addrmask[i] == ((int *)va)[i]; i++)
E 36
I 36
	freep->type = WEIRD_ADDR >> 16;
I 37
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
D 46
	freep->type = WEIRD_ADDR;
E 46
I 46
	freep->type = (short)WEIRD_ADDR;
E 46
#endif
E 37
D 38
	freep->next = (caddr_t)WEIRD_ADDR;
E 38
I 38
	if (((long)(&freep->next)) & 0x2)
		freep->next = (caddr_t)((WEIRD_ADDR >> 16)|(WEIRD_ADDR << 16));
	else
		freep->next = (caddr_t)WEIRD_ADDR;
E 38
	end = (long *)&va[copysize];
	for (lp = (long *)va; lp < end; lp++) {
		if (*lp == WEIRD_ADDR)
E 36
D 34
			/* void */;
E 34
I 34
			continue;
E 34
D 32
		printf("Word %d %s 0x%x of size %d modified (0x%x != 0x%x)\n",
		    i, "of object", va, size, ((int *)va)[i], addrmask[i]);
E 32
I 32
		printf("%s %d of object 0x%x size %d %s %s (0x%x != 0x%x)\n",
D 36
		    "Data modified on freelist: word", i, va, size,
		    "previous type", memname[savedtype], ((int *)va)[i],
		    addrmask[i]);
E 32
D 33
		panic("malloc: data modified on freelist");
E 33
I 33
		/* panic("malloc: data modified on freelist"); */
E 36
I 36
D 37
		    "Data modified on freelist: word", lp - (long *)va,
		    va, size, "previous type", memname[savedtype], *lp,
		    WEIRD_ADDR);
E 37
I 37
			"Data modified on freelist: word", lp - (long *)va,
			va, size, "previous type", savedtype, *lp, WEIRD_ADDR);
I 39
		for (mlp = listhd; mlp; mlp = mlp->next) {
			if (mlp->mem + 128 != va)
				continue;
			printf("previous element 0x%x, size %d, type %s\n",
				mlp->mem, mlp->size, memname[mlp->type]);
		}
E 39
E 37
		break;
E 36
E 33
	}
I 32
	freep->spare0 = 0;
E 32
#endif /* DIAGNOSTIC */
E 31
E 14
I 14
	kbp->kb_next = ((caddr_t *)va)[2];
	if (indx == 7) {
		long *lp = (long *)va;
		if (lp[0] != -1 || lp[1] != -1 || lp[3] != -1 || lp[4] != -1)
			panic("malloc meddled");
	}
E 14
#ifdef KMEMSTATS
	kup = btokup(va);
	if (kup->ku_indx != indx)
		panic("malloc: wrong bucket");
	if (kup->ku_freecnt == 0)
		panic("malloc: lost data");
	kup->ku_freecnt--;
	kbp->kb_totalfree--;
I 5
	ksp->ks_memuse += 1 << indx;
E 5
out:
	kbp->kb_calls++;
	ksp->ks_inuse++;
	ksp->ks_calls++;
D 8
	if (ksp->ks_inuse > ksp->ks_maxused)
		ksp->ks_maxused = ksp->ks_inuse;
E 8
I 8
	if (ksp->ks_memuse > ksp->ks_maxused)
		ksp->ks_maxused = ksp->ks_memuse;
E 8
#else
out:
#endif
I 39
	if (size > 64 && size <= 128) {
		mlp = (struct uselist *)malloc(sizeof(*mlp), M_TEMP, M_WAITOK);
		mlp->type = type;
		mlp->size = size;
		mlp->mem = va;
		mlp->next = listhd;
		listhd = mlp;
	}
E 39
I 14
	OUT;
E 14
	splx(s);
I 48
#ifdef DEBUG
	if (flags & M_NOWAIT)
		simplelockrecurse--;
#endif
E 48
D 28
	return ((qaddr_t)va);
E 28
I 28
	return ((void *) va);
E 28
}

I 25
#ifdef DIAGNOSTIC
long addrmask[] = { 0x00000000,
	0x00000001, 0x00000003, 0x00000007, 0x0000000f,
	0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
	0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
	0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
};
#endif /* DIAGNOSTIC */

E 25
I 22
D 31
#ifdef DIAGNOSTIC
long addrmask[] = { 0x00000000,
	0x00000001, 0x00000003, 0x00000007, 0x0000000f,
	0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
	0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
	0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
};
#endif /* DIAGNOSTIC */

E 31
E 22
/*
 * Free a block of memory allocated by malloc.
 */
D 7
void free(addr, type)
E 7
I 7
void
free(addr, type)
E 7
D 28
	caddr_t addr;
E 28
I 28
	void *addr;
E 28
D 9
	long type;
E 9
I 9
	int type;
E 9
{
	register struct kmembuckets *kbp;
	register struct kmemusage *kup;
I 32
	register struct freelist *freep;
E 32
D 8
	long alloc, s;
E 8
I 8
D 9
	long alloc, size, s;
E 9
I 9
D 31
	long alloc, size;
E 31
I 31
	long size;
E 31
	int s;
I 31
#ifdef DIAGNOSTIC
	caddr_t cp;
D 36
	long alloc, copysize;
E 36
I 36
	long *end, *lp, alloc, copysize;
E 36
#endif
E 31
E 9
E 8
I 5
#ifdef KMEMSTATS
	register struct kmemstats *ksp = &kmemstats[type];
#endif
E 5

	kup = btokup(addr);
I 25
	size = 1 << kup->ku_indx;
#ifdef DIAGNOSTIC
	if (size > NBPG * CLSIZE)
		alloc = addrmask[BUCKETINDX(NBPG * CLSIZE)];
	else
		alloc = addrmask[kup->ku_indx];
	if (((u_long)addr & alloc) != 0) {
		printf("free: unaligned addr 0x%x, size %d, type %d, mask %d\n",
			addr, size, type, alloc);
		panic("free: unaligned addr");
	}
#endif /* DIAGNOSTIC */
E 25
I 22
	size = 1 << kup->ku_indx;
I 31
	kbp = &bucket[kup->ku_indx];
	s = splimp();
I 39
	if (size == 128) {
		struct uselist *mlp, *pmlp;

		mlp = listhd;
		if (mlp->mem == addr)
			listhd = mlp->next;
		else for (pmlp = mlp, mlp = mlp->next ; mlp; mlp = mlp->next) {
			if (mlp->mem == addr) {
				pmlp->next = mlp->next;
				break;
			}
			pmlp = mlp;
		}
		if (mlp == NULL)
			printf("free: lost type %s size %d\n", memname[type],
			    size);
		else
			free(mlp, M_TEMP);
	}
E 39
E 31
#ifdef DIAGNOSTIC
I 31
	/*
	 * Check for returns of data that do not point to the
	 * beginning of the allocation.
	 */
E 31
I 30
	if (type == M_NAMEI)
		curproc->p_spare[0]--;
E 30
	if (size > NBPG * CLSIZE)
		alloc = addrmask[BUCKETINDX(NBPG * CLSIZE)];
	else
		alloc = addrmask[kup->ku_indx];
D 35
	if (((u_long)addr & alloc) != 0) {
		printf("free: unaligned addr 0x%x, size %d, type %d, mask %d\n",
			addr, size, type, alloc);
		panic("free: unaligned addr");
	}
E 35
I 35
	if (((u_long)addr & alloc) != 0)
		panic("free: unaligned addr 0x%x, size %d, type %s, mask %d\n",
			addr, size, memname[type], alloc);
E 35
#endif /* DIAGNOSTIC */
E 22
I 7
D 31
	kbp = &bucket[kup->ku_indx];
E 7
	s = splimp();
E 31
I 14
	IN;
E 14
D 8
	if (1 << kup->ku_indx > MAXALLOCSAVE) {
E 8
I 8
D 22
	size = 1 << kup->ku_indx;
E 22
	if (size > MAXALLOCSAVE) {
E 8
D 24
		alloc = btokmemx(addr);
D 9
		(void) memfree(&kmempt[alloc], kup->ku_pagecnt, 0);
E 9
I 9
D 16
D 25
		(void) memfree(&kmempt[alloc], (int)kup->ku_pagecnt, 0);
E 25
I 25
		(void) memfree(&kmempt[alloc], (int)kup->ku_pagecnt, 1);
E 25
E 16
I 16
		(void) memfree(&kmempt[alloc], (int)kup->ku_pagecnt, 1);
E 16
E 9
D 4
		rmfree(kmemmap, (long)kup->ku_pagecnt, alloc);
E 4
I 4
D 5
		rmfree(kmemmap, (long)kup->ku_pagecnt, alloc+CLSIZE);
E 5
I 5
		rmfree(kmemmap, (long)kup->ku_pagecnt, alloc + CLSIZE);
I 14
		OUT;
E 14
		if (wantkmemmap) {
			wakeup((caddr_t)&wantkmemmap);
			wantkmemmap = 0;
		}
E 24
I 24
		kmem_free(kmem_map, (vm_offset_t)addr, ctob(kup->ku_pagecnt));
E 24
E 5
E 4
#ifdef KMEMSTATS
I 5
D 8
		ksp->ks_memuse -= kup->ku_pagecnt << PGSHIFT;
E 8
I 8
		size = kup->ku_pagecnt << PGSHIFT;
		ksp->ks_memuse -= size;
E 8
E 5
		kup->ku_indx = 0;
		kup->ku_pagecnt = 0;
D 2
		kbp->kb_total -= kbp->kb_elmpercl;
E 2
D 5
		kmemstats[type].ks_inuse--;
E 5
I 5
D 8
		if (ksp->ks_inuse == ksp->ks_limit)
E 8
I 8
		if (ksp->ks_memuse + size >= ksp->ks_limit &&
		    ksp->ks_memuse < ksp->ks_limit)
E 8
			wakeup((caddr_t)ksp);
		ksp->ks_inuse--;
I 7
		kbp->kb_total -= 1;
E 7
E 5
#endif
		splx(s);
		return;
	}
I 32
	freep = (struct freelist *)addr;
E 32
I 31
#ifdef DIAGNOSTIC
	/*
	 * Check for multiple frees. Use a quick check to see if
	 * it looks free before laboriously searching the freelist.
	 */
D 32
	*(caddr_t *)addr = (char *)WEIRD_ADDR;
E 32
D 36
	copysize = size < sizeof addrmask ? size : sizeof addrmask;
E 36
D 32
	if (!bcmp(addrmask, addr, copysize)) {
		for (cp = kbp->kb_next; cp; cp = *(caddr_t *)cp) {
			if (addr == cp) {
				printf("multiply freed item 0x%x\n", addr);
				panic("free: duplicated free");
E 32
I 32
	if (freep->spare0 == WEIRD_ADDR) {
D 36
		freep->type = ((struct freelist *)addrmask)->type;
		freep->next = ((struct freelist *)addrmask)->next;
		if (!bcmp(addrmask, addr, copysize)) {
			for (cp = kbp->kb_next; cp; cp = *(caddr_t *)cp) {
				if (addr == cp) {
					printf("multiply freed item 0x%x\n",
					    addr);
					panic("free: duplicated free");
				}
E 32
			}
E 36
I 36
		for (cp = kbp->kb_next; cp; cp = *(caddr_t *)cp) {
			if (addr != cp)
				continue;
			printf("multiply freed item 0x%x\n", addr);
			panic("free: duplicated free");
E 36
		}
	}
	/*
	 * Copy in known text to detect modification after freeing
D 32
	 * and to make it look free.
E 32
I 32
	 * and to make it look free. Also, save the type being freed
	 * so we can list likely culprit if modification is detected
	 * when the object is reallocated.
E 32
	 */
D 36
	bcopy(addrmask, addr, copysize);
E 36
I 36
	copysize = size < MAX_COPY ? size : MAX_COPY;
	end = (long *)&((caddr_t)addr)[copysize];
	for (lp = (long *)addr; lp < end; lp++)
		*lp = WEIRD_ADDR;
E 36
I 32
	freep->type = type;
E 32
#endif /* DIAGNOSTIC */
E 31
I 14
	if (size == 128) {
		long *lp = (long *)addr;
		lp[0] = lp[1] = lp[3] = lp[4] = -1;
	}
E 14
D 7
	kbp = &bucket[kup->ku_indx];
E 7
#ifdef KMEMSTATS
	kup->ku_freecnt++;
	if (kup->ku_freecnt >= kbp->kb_elmpercl)
		if (kup->ku_freecnt > kbp->kb_elmpercl)
			panic("free: multiple frees");
		else if (kbp->kb_totalfree > kbp->kb_highwat)
			kbp->kb_couldfree++;
	kbp->kb_totalfree++;
D 5
	kmemstats[type].ks_inuse--;
E 5
I 5
D 8
	if (ksp->ks_inuse == ksp->ks_limit)
E 8
I 8
	ksp->ks_memuse -= size;
	if (ksp->ks_memuse + size >= ksp->ks_limit &&
	    ksp->ks_memuse < ksp->ks_limit)
E 8
		wakeup((caddr_t)ksp);
	ksp->ks_inuse--;
D 8
	ksp->ks_memuse -= 1 << kup->ku_indx;
E 8
E 5
#endif
D 14
D 32
	*(caddr_t *)addr = kbp->kb_next;
E 32
I 32
D 40
	freep->next = kbp->kb_next;
E 32
E 14
I 14
	((caddr_t *)addr)[2] = kbp->kb_next;
E 14
	kbp->kb_next = addr;
E 40
I 40
	if (kbp->kb_next == NULL)
		kbp->kb_next = addr;
	else
		((struct freelist *)kbp->kb_last)->next = addr;
	freep->next = NULL;
	kbp->kb_last = addr;
E 40
I 14
	OUT;
E 14
	splx(s);
}

/*
 * Initialize the kernel memory allocator
 */
kmeminit()
{
	register long indx;
I 7
	int npg;
E 7

D 9
	if (!powerof2(MAXALLOCSAVE))
		panic("kmeminit: MAXALLOCSAVE not power of 2");
	if (MAXALLOCSAVE > MINALLOCSIZE * 32768)
		panic("kmeminit: MAXALLOCSAVE too big");
	if (MAXALLOCSAVE < CLBYTES)
		panic("kmeminit: MAXALLOCSAVE too small");
E 9
I 9
#if	((MAXALLOCSAVE & (MAXALLOCSAVE - 1)) != 0)
		ERROR!_kmeminit:_MAXALLOCSAVE_not_power_of_2
#endif
#if	(MAXALLOCSAVE > MINALLOCSIZE * 32768)
		ERROR!_kmeminit:_MAXALLOCSAVE_too_big
#endif
#if	(MAXALLOCSAVE < CLBYTES)
		ERROR!_kmeminit:_MAXALLOCSAVE_too_small
#endif
E 9
D 3
	rminit(kmemmap, ekmempt - kmempt, (long)1,
E 3
I 3
D 7
	rminit(kmemmap, ekmempt - kmempt, (long)CLSIZE,
E 3
		"malloc map", ekmempt - kmempt);
E 7
I 7
D 24
	npg = ekmempt - kmempt;
D 9
	rminit(kmemmap, npg, (long)CLSIZE, "malloc map", npg);
E 9
I 9
	rminit(kmemmap, (long)npg, (long)CLSIZE, "malloc map", npg);
E 24
I 24
	npg = VM_KMEM_SIZE/ NBPG;
	kmemusage = (struct kmemusage *) kmem_alloc(kernel_map,
		(vm_size_t)(npg * sizeof(struct kmemusage)));
D 34
	kmem_map = kmem_suballoc(kernel_map, (vm_offset_t)&kmembase,
		(vm_offset_t)&kmemlimit, (vm_size_t)(npg * NBPG), FALSE);
E 34
I 34
	kmem_map = kmem_suballoc(kernel_map, (vm_offset_t *)&kmembase,
		(vm_offset_t *)&kmemlimit, (vm_size_t)(npg * NBPG), FALSE);
E 34
E 24
E 9
E 7
#ifdef KMEMSTATS
	for (indx = 0; indx < MINBUCKET + 16; indx++) {
		if (1 << indx >= CLBYTES)
			bucket[indx].kb_elmpercl = 1;
		else
			bucket[indx].kb_elmpercl = CLBYTES / (1 << indx);
		bucket[indx].kb_highwat = 5 * bucket[indx].kb_elmpercl;
	}
	for (indx = 0; indx < M_LAST; indx++)
D 5
		kmemstats[indx].ks_limit = 0x7fffffff;
E 5
I 5
D 7
		kmemstats[indx].ks_limit =
			(ekmempt - kmempt) * CLBYTES * 9 / 10;
E 7
I 7
D 20
D 25
		kmemstats[indx].ks_limit = npg * CLBYTES * 8 / 10;
E 25
I 25
		kmemstats[indx].ks_limit = npg * NBPG * 6 / 10;
E 25
E 20
I 20
		kmemstats[indx].ks_limit = npg * NBPG * 6 / 10;
E 20
E 7
E 5
#endif
}
E 1
