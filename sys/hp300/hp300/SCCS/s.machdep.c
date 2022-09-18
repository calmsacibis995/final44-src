h01712
s 00004/00010/01651
d D 8.15 95/05/26 16:04:35 mckusick 52 51
c clean up backtrace code
e
s 00003/00001/01658
d D 8.14 95/05/19 14:01:27 mckusick 51 50
c call sync with curproc, not &proc0
e
s 00047/00001/01612
d D 8.13 95/05/17 14:58:10 mckusick 50 49
c add backtrace function
e
s 00005/00000/01608
d D 8.12 95/05/09 12:10:44 mckusick 49 48
c put in request to unmount all filesystems when rebooting
e
s 00003/00002/01605
d D 8.11 95/01/09 18:28:18 cgd 48 47
c signal handler code is u_long, pull in vm_extern.h and fix grow() args.
e
s 00001/00002/01606
d D 8.10 94/04/20 09:43:44 mckusick 47 46
c lint
e
s 00000/00007/01608
d D 8.9 94/04/18 23:07:09 mckusick 46 45
c ps_code is now passed by postsig, so guess should no longer be necessary
e
s 00007/00000/01608
d D 8.8 94/03/21 16:27:59 hibler 45 44
c don't lose signal handler "code" argument when signal delivery
c is delayed due to being traced
e
s 00005/00002/01603
d D 8.7 94/02/13 10:55:16 hibler 44 43
c make sure we dump the last page of physical memory
e
s 00002/00001/01603
d D 8.6 94/01/12 16:50:37 hibler 43 42
c forgot some of the lint
e
s 00003/00005/01601
d D 8.5 94/01/12 16:33:07 hibler 42 41
c lint, cleanup
e
s 00055/00007/01551
d D 8.4 94/01/12 14:40:46 hibler 41 40
c experimental code for "unmanaged" buffers,
c don't get stuck on stray interrupts,
c entries_pageable set TRUE for buffer map (set vm_map.c change).
e
s 00015/00000/01543
d D 8.3 93/11/14 14:22:58 hibler 40 39
c MAPPEDCOPY code: init the threshhold size
e
s 00001/00001/01542
d D 8.2 93/09/23 16:37:45 bostic 39 38
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/01541
d D 8.1 93/06/10 21:41:08 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/01509
d D 7.37 93/05/20 21:21:02 mckusick 37 36
c add cpu_sysctl
e
s 00033/00022/01476
d D 7.36 93/02/10 19:40:28 mckusick 36 35
c construct string that can be copied out later
e
s 00128/00050/01370
d D 7.35 92/12/28 09:02:29 hibler 35 34
c numerous changes: SHPUX has moved, LED stuff assorted
e
s 00006/00000/01414
d D 7.34 92/12/28 09:01:15 hibler 34 33
c for sklower: CCITT changes
e
s 00027/00027/01387
d D 7.33 92/10/11 09:42:40 bostic 33 32
c make kernel includes standard
e
s 00001/00001/01413
d D 7.32 92/09/24 21:52:02 bostic 32 31
c delete antique code to check bfreelist[0].b_forw (no longer used)
e
s 00026/00029/01388
d D 7.31 92/08/03 13:59:22 hibler 31 30
c expand tweaksigcode in place and make it work correctly
e
s 00004/00003/01413
d D 7.30 92/07/10 22:02:19 torek 30 29
c ANSIfy syscall args
e
s 00005/00034/01411
d D 7.29 92/07/08 01:08:40 mckusick 29 28
c microtime moved to clock.c; lint
e
s 00030/00015/01415
d D 7.28 92/06/05 15:37:11 hibler 28 27
c merge latest Utah hp300 code including 68040 support
e
s 00001/00005/01429
d D 7.27 92/05/04 17:04:24 mckusick 27 26
c delete unneeded header files
e
s 00016/00007/01418
d D 7.26 92/04/20 23:32:12 mckusick 26 25
c add functionality to support sigaltstack
e
s 00001/00000/01424
d D 7.25 92/04/14 14:41:09 mckusick 25 24
c null terminate the callout list (from torek)
e
s 00002/00001/01422
d D 7.24 92/04/03 14:57:59 mckusick 24 23
c update from Chris Torek to add argument pointer at known location
e
s 00002/00002/01421
d D 7.23 92/02/25 16:34:53 mckusick 23 22
c lint
e
s 00003/00003/01420
d D 7.22 92/02/19 18:28:03 torek 22 21
c pmap_kernel() is really kernel_pmap variable
e
s 00005/00005/01418
d D 7.21 92/02/05 17:20:04 mckusick 21 20
c p_regs moves to p_md.md_regs
e
s 00006/00004/01417
d D 7.20 91/11/05 17:01:09 mckusick 20 19
c lint
e
s 00001/00001/01420
d D 7.19 91/08/28 15:49:21 mckusick 19 18
c vm_stat is merged into vmmeter structure
e
s 00001/00001/01420
d D 7.18 91/07/25 22:49:06 mckusick 18 17
c vm_page_free_count moves to vm_stat.free_count
e
s 00004/00000/01417
d D 7.17 91/06/25 22:25:49 sklower 17 16
c arp now runs at splnet() to merge arp and routing tables.
e
s 00000/00001/01417
d D 7.16 91/06/03 20:37:09 mckusick 16 15
c file table is no longer statically allocated
e
s 00001/00001/01417
d D 7.15 91/05/21 13:25:46 karels 15 14
c missing cast
e
s 00007/00005/01411
d D 7.14 91/05/09 17:53:30 karels 14 13
c startup => cpu_startup; remove unused argument; clarify comments
e
s 00042/00029/01374
d D 7.13 91/05/07 09:58:23 hibler 13 12
c new stack adjustment code
c assorted updates from utah
e
s 00020/00018/01383
d D 7.12 91/05/04 19:29:37 karels 12 11
c u. is gone, use p_addr; add proc param to setregs; resume => savectx;
c sigcode no longer in pcb
e
s 00076/00074/01325
d D 7.11 91/04/20 17:32:53 karels 11 10
c new proc struct, sigacts struct; add consinit; bhinit+binit => bufinit;
c no proc array; nproc => maxproc
e
s 00026/00026/01373
d D 7.10 90/12/16 16:36:20 bostic 10 9
c kernel reorg
e
s 00005/00000/01394
d D 7.9 90/12/07 17:10:50 karels 9 8
c define safepri for sleep
e
s 00098/00112/01296
d D 7.8 90/12/05 18:58:22 mckusick 8 7
c update from Mike Hibler for new VM and other machine support
e
s 00010/00010/01398
d D 7.7 90/06/28 17:29:48 karels 7 6
c RETURN => return, remove syscontext.h
e
s 00015/00016/01393
d D 7.6 90/06/22 09:33:18 hibler 6 5
c cleanup
e
s 00005/00004/01404
d D 7.5 90/06/21 22:22:21 mckusick 5 4
c pass back values appropriately
e
s 00022/00020/01386
d D 7.4 90/06/20 09:49:10 karels 4 3
c first cut at new syscall convention
e
s 00032/00021/01374
d D 7.3 90/05/25 15:56:06 mckusick 3 2
c update from Mike Hibler at Utah
e
s 00014/00027/01381
d D 7.2 90/05/16 23:12:13 karels 2 1
c remove old static tables; attempt to convert sigreturn
e
s 01408/00000/00000
d D 7.1 90/05/08 18:09:10 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 38
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 38
I 38
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 38
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 13
 * from: Utah $Hdr: machdep.c 1.51 89/11/28$
E 13
I 13
D 28
 * from: Utah $Hdr: machdep.c 1.63 91/04/24$
E 28
I 28
D 35
 * from: Utah $Hdr: machdep.c 1.68 92/01/20$
E 35
I 35
 * from: Utah $Hdr: machdep.c 1.74 92/12/20$
E 35
E 28
E 13
 *
 *	%W% (Berkeley) %G%
 */

D 10
#include "param.h"
#include "systm.h"
D 6
#include "user.h"
E 6
I 6
D 7
#include "syscontext.h"
E 7
I 7
#include "user.h"
E 7
E 6
#include "kernel.h"
#include "map.h"
D 8
#include "vm.h"
E 8
#include "proc.h"
#include "buf.h"
#include "reboot.h"
#include "conf.h"
D 2
#include "vnode.h"
E 2
#include "file.h"
D 8
#include "text.h"
E 8
#include "clist.h"
#include "callout.h"
D 8
#include "cmap.h"
E 8
#include "malloc.h"
#include "mbuf.h"
#include "msgbuf.h"
E 10
I 10
D 11
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/kernel.h"
#include "sys/map.h"
#include "sys/proc.h"
#include "sys/buf.h"
#include "sys/reboot.h"
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/clist.h"
#include "sys/callout.h"
#include "sys/malloc.h"
#include "sys/mbuf.h"
#include "sys/msgbuf.h"
E 11
I 11
D 33
#include "param.h"
#include "systm.h"
#include "signalvar.h"
#include "kernel.h"
#include "map.h"
#include "proc.h"
#include "buf.h"
#include "reboot.h"
#include "conf.h"
#include "file.h"
#include "clist.h"
#include "callout.h"
#include "malloc.h"
#include "mbuf.h"
#include "msgbuf.h"
I 27
#include "mount.h"
E 27
#include "user.h"
I 24
#include "exec.h"
E 33
I 33
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signalvar.h>
#include <sys/kernel.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/reboot.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/clist.h>
#include <sys/callout.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
I 37
#include <sys/ioctl.h>
#include <sys/tty.h>
E 37
#include <sys/mount.h>
#include <sys/user.h>
#include <sys/exec.h>
I 37
#include <sys/sysctl.h>
E 37
E 33
E 24
E 11
E 10
D 2
#include "../ufs/quota.h"
E 2
#ifdef SYSVSHM
D 10
#include "shm.h"
E 10
I 10
D 11
#include "sys/shm.h"
E 11
I 11
D 33
#include "shm.h"
E 33
I 33
#include <sys/shm.h>
E 33
E 11
E 10
#endif
#ifdef HPUXCOMPAT
D 28
#include "../hpux/hpux.h"
E 28
I 28
D 33
#include "hp/hpux/hpux.h"
E 33
I 33
#include <hp/hpux/hpux.h>
E 33
E 28
#endif

D 10
#include "cpu.h"
#include "reg.h"
D 8
#include "pte.h"
E 8
#include "psl.h"
E 10
I 10
D 33
#include "../include/cpu.h"
#include "../include/reg.h"
#include "../include/psl.h"
E 10
#include "isr.h"
I 11
#include "pte.h"
E 11
D 10
#include "../net/netisr.h"
E 10
I 10
#include "net/netisr.h"
E 33
I 33
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/psl.h>
I 37
#include <hp/dev/cons.h>
E 37
#include <hp300/hp300/isr.h>
#include <hp300/hp300/pte.h>
#include <net/netisr.h>
E 33
E 10

I 8
#define	MAXMEM	64*1024*CLSIZE	/* XXX - from cmap.h */
I 48
#include <vm/vm_extern.h>
E 48
D 10
#include "../vm/vm_param.h"
#include "../vm/pmap.h"
#include "../vm/vm_map.h"
#include "../vm/vm_object.h"
#include "../vm/vm_kern.h"
#include "../vm/vm_page.h"
E 10
I 10
D 27
#include "vm/vm_param.h"
#include "vm/pmap.h"
#include "vm/vm_map.h"
#include "vm/vm_object.h"
E 27
D 33
#include "vm/vm_kern.h"
E 33
I 33
#include <vm/vm_kern.h>
E 33
D 27
#include "vm/vm_page.h"
E 27
I 11

I 36
/* the following is used externally (sysctl_hw) */
char machine[] = "hp300";		/* cpu "architecture" */

E 36
E 11
E 10
vm_map_t buffer_map;
extern vm_offset_t avail_end;

E 8
I 2
D 3
#define	RETURN(value)	{ u.u_error = (value); return; }
E 3
I 3
D 4
#define RETURN(value)   { u.u_error = (value); return; }
E 4
I 4
D 6
#define RETURN(value)   { u.u_error = (value); return (u.u_error); }
E 4
E 3

E 6
E 2
/*
 * Declare these as initialized data so we can patch them.
 */
int	nswbuf = 0;
#ifdef	NBUF
int	nbuf = NBUF;
#else
int	nbuf = 0;
#endif
#ifdef	BUFPAGES
int	bufpages = BUFPAGES;
#else
int	bufpages = 0;
#endif
int	msgbufmapped;		/* set when safe to use msgbuf */
I 13
int	maxmem;			/* max memory per process */
E 13
int	physmem = MAXMEM;	/* max supported memory, changes to actual */
I 9
/*
 * safepri is a safe priority for sleep to set for a spin-wait
 * during autoconfiguration or after a panic.
 */
D 13
int   safepri = PSL_LOWIPL;
E 13
I 13
int	safepri = PSL_LOWIPL;
E 13
E 9

extern	u_int lowram;
I 35
extern	short exframesize[];
E 35

/*
D 11
 * Machine-dependent startup code
E 11
I 11
 * Console initialization: called early on from main,
 * before vm init or startup.  Do enough configuration
 * to choose and initialize a console.
E 11
 */
D 11
startup(firstaddr)
	int firstaddr;
E 11
I 11
consinit()
E 11
{
D 8
	register int unixsize;
E 8
D 11
	register unsigned i;
D 8
	register struct pte *pte;
	int mapaddr, j, n;
E 8
	register caddr_t v;
D 8
	int maxbufs, base, residual;
E 8
I 8
	int base, residual;
E 8
	extern long Usrptsize;
	extern struct map *useriomap;
I 8
#ifdef DEBUG
	extern int pmapdebug;
	int opmapdebug = pmapdebug;
#endif
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
E 11
E 8

	/*
	 * Set cpuspeed immediately since cninit() called routines
D 35
	 * might use delay.
E 35
I 35
	 * might use delay.  Note that we only set it if a custom value
	 * has not already been specified.
E 35
	 */
D 35
	switch (machineid) {
	case HP_320:
	case HP_330:
	case HP_340:
		cpuspeed = MHZ_16;
		break;
	case HP_350:
	case HP_360:
		cpuspeed = MHZ_25;
		break;
	case HP_370:
		cpuspeed = MHZ_33;
		break;
I 3
	case HP_375:
		cpuspeed = MHZ_50;
		break;
I 28
	case HP_380:
		cpuspeed = MHZ_25 * 2;	/* XXX */
		break;
E 35
I 35
	if (cpuspeed == 0) {
		switch (machineid) {
		case HP_320:
		case HP_330:
		case HP_340:
			cpuspeed = MHZ_16;
			break;
		case HP_350:
		case HP_360:
		case HP_380:
			cpuspeed = MHZ_25;
			break;
		case HP_370:
		case HP_433:
			cpuspeed = MHZ_33;
			break;
		case HP_375:
			cpuspeed = MHZ_50;
			break;
		default:	/* assume the fastest */
			cpuspeed = MHZ_50;
			break;
		}
		if (mmutype == MMU_68040)
			cpuspeed *= 2;	/* XXX */
E 35
E 28
E 3
	}
I 8
D 11
#ifndef DEBUG
E 11
E 8
	/*
         * Find what hardware is attached to this machine.
         */
	find_devs();
I 11

E 11
	/*
	 * Initialize the console before we print anything out.
	 */
	cninit();
I 11
}

/*
D 14
 * Machine-dependent startup code
E 14
I 14
 * cpu_startup: allocate memory for variable-sized tables,
 * initialize cpu, and do autoconfiguration.
E 14
 */
D 14
startup(firstaddr)
	int firstaddr;
E 14
I 14
cpu_startup()
E 14
{
	register unsigned i;
D 14
	register caddr_t v;
E 14
I 14
	register caddr_t v, firstaddr;
E 14
	int base, residual;
D 28
	extern long Usrptsize;
	extern struct map *useriomap;
E 28
I 28
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
I 41
#ifdef BUFFERS_UNMANAGED
	vm_offset_t bufmemp;
	caddr_t buffermem;
	int ix;
#endif
E 41
E 28
#ifdef DEBUG
	extern int pmapdebug;
	int opmapdebug = pmapdebug;
I 28

	pmapdebug = 0;
E 28
E 11
I 8
#endif
I 11
D 28
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
E 28

E 11
E 8
	/*
	 * Initialize error message buffer (at end of core).
I 28
	 * avail_end was pre-decremented in pmap_bootstrap to compensate.
E 28
	 */
D 8
	maxmem -= btoc(sizeof (struct msgbuf));
	pte = msgbufmap;
E 8
I 8
D 28
#ifdef DEBUG
	pmapdebug = 0;
#endif
	/* avail_end was pre-decremented in pmap_bootstrap to compensate */
E 28
E 8
	for (i = 0; i < btoc(sizeof (struct msgbuf)); i++)
D 8
		*(int *)pte++ = PG_CI | PG_V | PG_KW | (ctob(maxmem + i));
	TBIAS();
E 8
I 8
D 20
		pmap_enter(pmap_kernel(), msgbufp, avail_end + i * NBPG,
			   VM_PROT_ALL, TRUE);
E 20
I 20
D 22
		pmap_enter(pmap_kernel(), (vm_offset_t)msgbufp,
E 22
I 22
		pmap_enter(kernel_pmap, (vm_offset_t)msgbufp,
E 22
		    avail_end + i * NBPG, VM_PROT_ALL, TRUE);
E 20
E 8
	msgbufmapped = 1;

	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	printf(version);
	identifycpu();
	printf("real mem = %d\n", ctob(physmem));

	/*
	 * Allocate space for system data structures.
	 * The first available real memory address is in "firstaddr".
	 * The first available kernel virtual address is in "v".
	 * As pages of kernel virtual memory are allocated, "v" is incremented.
	 * As pages of memory are allocated and cleared,
	 * "firstaddr" is incremented.
	 * An index into the kernel page table corresponding to the
	 * virtual memory address maintained in "v" is kept in "mapaddr".
	 */
D 8
	v = (caddr_t)((firstaddr * NBPG) - lowram);
	mapaddr = (int)v;
E 8
I 8
	/*
	 * Make two passes.  The first pass calculates how much memory is
	 * needed and allocates it.  The second pass assigns virtual
	 * addresses to the various data structures.
	 */
	firstaddr = 0;
again:
	v = (caddr_t)firstaddr;

E 8
#define	valloc(name, type, num) \
	    (name) = (type *)v; v = (caddr_t)((name)+(num))
#define	valloclim(name, type, num, lim) \
	    (name) = (type *)v; v = (caddr_t)((lim) = ((name)+(num)))
D 2
	valloclim(vnode, struct vnode, nvnode, vnodeNVNODE);
E 2
D 16
	valloclim(file, struct file, nfile, fileNFILE);
E 16
D 11
	valloclim(proc, struct proc, nproc, procNPROC);
E 11
D 8
	valloclim(text, struct text, ntext, textNTEXT);
E 8
	valloc(cfree, struct cblock, nclist);
	valloc(callout, struct callout, ncallout);
D 11
	valloc(swapmap, struct map, nswapmap = nproc * 2);
E 11
I 11
	valloc(swapmap, struct map, nswapmap = maxproc * 2);
E 11
D 8
	valloc(argmap, struct map, ARGMAPSIZE);
	valloc(kernelmap, struct map, nproc);
	valloc(mbmap, struct map, nmbclusters/4);
D 2
	valloc(namecache, struct namecache, nchsize);
E 2
	valloc(kmemmap, struct map, ekmempt - kmempt);
	valloc(kmemusage, struct kmemusage, ekmempt - kmempt);
	valloc(useriomap, struct map, nproc);
E 8
D 2
#ifdef QUOTA
	valloclim(quota, struct quota, nquota, quotaNQUOTA);
	valloclim(dquot, struct dquot, ndquot, dquotNDQUOT);
#endif
E 2
#ifdef SYSVSHM
	valloc(shmsegs, struct shmid_ds, shminfo.shmmni);
#endif
	
	/*
	 * Determine how many buffers to allocate.
	 * Since HPs tend to be long on memory and short on disk speed,
	 * we allocate more buffer space than the BSD standard of
	 * use 10% of memory for the first 2 Meg, 5% of remaining.
	 * We just allocate a flat 10%.  Insure a minimum of 16 buffers.
	 * We allocate 1/2 as many swap buffer headers as file i/o buffers.
	 */
	if (bufpages == 0)
		bufpages = physmem / 10 / CLSIZE;
	if (nbuf == 0) {
		nbuf = bufpages;
		if (nbuf < 16)
			nbuf = 16;
	}
	if (nswbuf == 0) {
		nswbuf = (nbuf / 2) &~ 1;	/* force even */
		if (nswbuf > 256)
			nswbuf = 256;		/* sanity */
	}
	valloc(swbuf, struct buf, nswbuf);
D 8

E 8
I 8
	valloc(buf, struct buf, nbuf);
E 8
	/*
D 8
	 * Now the amount of virtual memory remaining for buffers
	 * can be calculated, estimating needs for the cmap.
E 8
I 8
	 * End of first pass, size has been calculated so allocate memory
E 8
	 */
D 8
	ncmap = (maxmem*NBPG - (firstaddr*NBPG + ((int)v - mapaddr))) /
		(CLBYTES + sizeof(struct cmap)) + 2;
	maxbufs = ((SYSPTSIZE * NBPG) -
		(int)(v + ncmap * sizeof(struct cmap))) /
		(MAXBSIZE + sizeof(struct buf));
	if (maxbufs < 16)
		panic("sys pt too small");
	if (nbuf > maxbufs) {
		printf("SYSPTSIZE limits number of buffers to %d\n", maxbufs);
		nbuf = maxbufs;
E 8
I 8
	if (firstaddr == 0) {
		size = (vm_size_t)(v - firstaddr);
D 15
		firstaddr = (int)kmem_alloc(kernel_map, round_page(size));
E 15
I 15
		firstaddr = (caddr_t) kmem_alloc(kernel_map, round_page(size));
E 15
		if (firstaddr == 0)
			panic("startup: no room for tables");
I 41
#ifdef BUFFERS_UNMANAGED
		buffermem = (caddr_t) kmem_alloc(kernel_map, bufpages*CLBYTES);
		if (buffermem == 0)
			panic("startup: no room for buffers");
#endif
E 41
		goto again;
E 8
	}
D 8
	if (bufpages > nbuf * (MAXBSIZE / CLBYTES))
		bufpages = nbuf * (MAXBSIZE / CLBYTES);
	valloc(buf, struct buf, nbuf);

E 8
	/*
D 8
	 * Allocate space for core map.
	 * Allow space for all of physical memory minus the amount 
	 * dedicated to the system. The amount of physical memory
	 * dedicated to the system is the total virtual memory of
	 * the system thus far, plus core map, buffer pages,
	 * and buffer headers not yet allocated.
	 * Add 2: 1 because the 0th entry is unused, 1 for rounding.
E 8
I 8
	 * End of second pass, addresses have been assigned
E 8
	 */
D 8
	ncmap = (maxmem*NBPG - (firstaddr * NBPG +
		((int)(v + bufpages*CLBYTES) - mapaddr))) /
		(CLBYTES + sizeof(struct cmap)) + 2;
	valloclim(cmap, struct cmap, ncmap, ecmap);

E 8
I 8
	if ((vm_size_t)(v - firstaddr) != size)
		panic("startup: table size inconsistency");
E 8
	/*
D 8
	 * Clear space allocated thus far, and make r/w entries
	 * for the space in the kernel map.
	 */
	unixsize = btoc(v);
	mapaddr = btoc(mapaddr);
	while (mapaddr < unixsize) {
		*(int *)(&Sysmap[mapaddr]) = PG_V | PG_KW | ctob(firstaddr);
		clearseg((unsigned)firstaddr);
		firstaddr++;
		mapaddr++;
	}

	/*
E 8
	 * Now allocate buffers proper.  They are different than the above
	 * in that they usually occupy more virtual memory than physical.
	 */
D 8
	v = (caddr_t) ((int)(v + PGOFSET) &~ PGOFSET);
	valloc(buffers, char, MAXBSIZE * nbuf);
E 8
I 8
	size = MAXBSIZE * nbuf;
D 23
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t)&buffers,
E 23
I 23
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t *)&buffers,
E 23
D 41
				   &maxaddr, size, FALSE);
E 41
I 41
				   &maxaddr, size, TRUE);
E 41
	minaddr = (vm_offset_t)buffers;
	if (vm_map_find(buffer_map, vm_object_allocate(size), (vm_offset_t)0,
			&minaddr, size, FALSE) != KERN_SUCCESS)
		panic("startup: cannot allocate buffers");
E 8
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
I 41
#ifdef BUFFERS_UNMANAGED
	bufmemp = (vm_offset_t) buffermem;
#endif
E 41
	for (i = 0; i < nbuf; i++) {
D 8
		n = (i < residual ? base + 1 : base) * CLSIZE;
		for (j = 0; j < n; j++) {
			*(int *)(&Sysmap[mapaddr+j]) =
			    PG_CI | PG_V | PG_KW | ctob(firstaddr);
			clearseg((unsigned)firstaddr);
			firstaddr++;
		}
		mapaddr += MAXBSIZE / NBPG;
E 8
I 8
		vm_size_t curbufsize;
		vm_offset_t curbuf;

		/*
		 * First <residual> buffers get (base+1) physical pages
		 * allocated for them.  The rest get (base) physical pages.
		 *
		 * The rest of each buffer occupies virtual space,
		 * but has no physical memory allocated for it.
		 */
		curbuf = (vm_offset_t)buffers + i * MAXBSIZE;
		curbufsize = CLBYTES * (i < residual ? base+1 : base);
I 41
#ifdef BUFFERS_UNMANAGED
		/*
		 * Move the physical pages over from buffermem.
		 */
		for (ix = 0; ix < curbufsize/CLBYTES; ix++) {
			vm_offset_t pa;

			pa = pmap_extract(kernel_pmap, bufmemp);
			if (pa == 0)
				panic("startup: unmapped buffer");
			pmap_remove(kernel_pmap, bufmemp, bufmemp+CLBYTES);
			pmap_enter(kernel_pmap,
				   (vm_offset_t)(curbuf + ix * CLBYTES),
				   pa, VM_PROT_READ|VM_PROT_WRITE, TRUE);
			bufmemp += CLBYTES;
		}
#else
E 41
		vm_map_pageable(buffer_map, curbuf, curbuf+curbufsize, FALSE);
		vm_map_simplify(buffer_map, curbuf);
I 41
#endif
E 41
E 8
	}
I 41
#ifdef BUFFERS_UNMANAGED
#if 0
E 41
I 8
	/*
I 41
	 * We would like to free the (now empty) original address range
	 * but too many bad things will happen if we try.
	 */
	kmem_free(kernel_map, (vm_offset_t)buffermem, bufpages*CLBYTES);
#endif
#endif
	/*
E 41
	 * Allocate a submap for exec arguments.  This map effectively
	 * limits the number of processes exec'ing at any time.
	 */
	exec_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr,
				 16*NCARGS, TRUE);
	/*
	 * Allocate a submap for physio
	 */
	phys_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr,
				 VM_PHYS_SIZE, TRUE);
E 8

D 8
	unixsize = btoc(v);
	if (firstaddr - Sysmap[0].pg_pfnum >= physmem - 8*UPAGES)
		panic("no memory");
	TBIA();				/* After we just cleared it all! */

E 8
	/*
I 8
	 * Finally, allocate mbuf pool.  Since mclrefcnt is an off-size
	 * we use the more space efficient malloc in place of kmem_alloc.
	 */
	mclrefcnt = (char *)malloc(NMBCLUSTERS+CLBYTES/MCLBYTES,
				   M_MBUF, M_NOWAIT);
	bzero(mclrefcnt, NMBCLUSTERS+CLBYTES/MCLBYTES);
D 23
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t)&mbutl, &maxaddr,
E 23
I 23
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t *)&mbutl, &maxaddr,
E 23
			       VM_MBUF_SIZE, FALSE);
	/*
E 8
	 * Initialize callouts
	 */
	callfree = callout;
	for (i = 1; i < ncallout; i++)
		callout[i-1].c_next = &callout[i];
I 25
	callout[i-1].c_next = NULL;
E 25

D 8
	/*
	 * Initialize memory allocator and swap
	 * and user page table maps.
	 *
	 * THE USER PAGE TABLE MAP IS CALLED ``kernelmap''
	 * WHICH IS A VERY UNDESCRIPTIVE AND INCONSISTENT NAME.
	 */
	meminit(firstaddr, maxmem);
	maxmem = freemem;
	printf("avail mem = %d\n", ctob(maxmem));
E 8
I 8
#ifdef DEBUG
	pmapdebug = opmapdebug;
#endif
D 18
	printf("avail mem = %d\n", ptoa(vm_page_free_count));
E 18
I 18
D 19
	printf("avail mem = %d\n", ptoa(vm_stat.free_count));
E 19
I 19
	printf("avail mem = %d\n", ptoa(cnt.v_free_count));
E 19
E 18
E 8
	printf("using %d buffers containing %d bytes of memory\n",
		nbuf, bufpages * CLBYTES);
D 8
	rminit(kernelmap, (long)&Usrptsize-CLSIZE, (long)1, "usrpt", nproc);
	rminit(useriomap, (long)USRIOSIZE, (long)1, "usrio", nproc);
	rminit(mbmap, (long)(nmbclusters * MCLBYTES / NBPG), (long)CLSIZE,
	    "mbclusters", nmbclusters/4);
	kmeminit();	/* now safe to do malloc/free */

E 8
	/*
	 * Set up CPU-specific registers, cache, etc.
	 */
	initcpu();

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
D 11
	bhinit();
	binit();
E 11
I 11
	bufinit();
E 11

	/*
	 * Configure the system.
	 */
	configure();
}

D 11
#ifdef PGINPROF
E 11
/*
D 11
 * Return the difference (in microseconds)
 * between the  current time and a previous
 * time as represented by the arguments.
 */
/*ARGSUSED*/
vmtime(otime, olbolt, oicr)
	register int otime, olbolt, oicr;
{

	return (((time.tv_sec-otime)*100 + lbolt-olbolt)*10000);
}
#endif

/*
E 11
D 14
 * Clear registers on exec
E 14
I 14
 * Set registers on exec.
 * XXX Should clear registers except sp, pc,
 * but would break init; should be fixed soon.
E 14
 */
D 5
setregs(entry)
E 5
I 5
D 12
setregs(entry, retval)
E 12
I 12
setregs(p, entry, retval)
	register struct proc *p;
E 12
E 5
	u_long entry;
I 5
	int retval[2];
E 5
{
D 11
	u.u_ar0[PC] = entry & ~1;
E 11
I 11
D 12
	register struct proc *p = curproc;
E 12
D 13

E 13
D 21
	p->p_regs[PC] = entry & ~1;
E 21
I 21
D 35
	p->p_md.md_regs[PC] = entry & ~1;
E 35
I 35
	struct frame *frame = (struct frame *)p->p_md.md_regs;

	frame->f_pc = entry & ~1;
E 35
E 21
E 11
#ifdef FPCOPROC
	/* restore a null state frame */
D 12
	u.u_pcb.pcb_fpregs.fpf_null = 0;
	m68881_restore(&u.u_pcb.pcb_fpregs);
E 12
I 12
	p->p_addr->u_pcb.pcb_fpregs.fpf_null = 0;
	m68881_restore(&p->p_addr->u_pcb.pcb_fpregs);
E 12
#endif
#ifdef HPUXCOMPAT
D 11
	if (u.u_procp->p_flag & SHPUX) {
E 11
I 11
D 35
	if (p->p_flag & SHPUX) {
E 35
I 35
	if (p->p_md.md_flags & MDP_HPUX) {
E 35
E 11

D 11
		u.u_ar0[A0] = 0;	/* not 68010 (bit 31), no FPA (30) */
E 11
I 11
D 21
		p->p_regs[A0] = 0;	/* not 68010 (bit 31), no FPA (30) */
E 21
I 21
D 35
		p->p_md.md_regs[A0] = 0; /* not 68010 (bit 31), no FPA (30) */
E 35
I 35
		frame->f_regs[A0] = 0; /* not 68010 (bit 31), no FPA (30) */
E 35
E 21
E 11
D 5
		u.u_r.r_val1 = 0;	/* no float card */
E 5
I 5
		retval[0] = 0;		/* no float card */
E 5
#ifdef FPCOPROC
D 5
		u.u_r.r_val2 = 1;	/* yes 68881 */
E 5
I 5
		retval[1] = 1;		/* yes 68881 */
E 5
#else
D 5
		u.u_r.r_val2 = 0;	/* no 68881 */
E 5
I 5
		retval[1] = 0;		/* no 68881 */
E 5
#endif
	}
	/*
I 31
	 * XXX This doesn't have much to do with setting registers but
	 * I didn't want to muck up kern_exec.c with this code, so I
	 * stuck it here.
	 *
E 31
	 * Ensure we perform the right action on traps type 1 and 2:
	 * If our parent is an HPUX process and we are being traced, turn
	 * on HPUX style interpretation.  Else if we were using the HPUX
	 * style interpretation, revert to the BSD interpretation.
	 *
D 31
	 * XXX This doesn't have much to do with setting registers but
	 * I didn't want to muck up kern_exec.c with this code, so I
	 * stuck it here.
E 31
I 31
	 * Note that we do this by changing the trap instruction in the
	 * global "sigcode" array which then gets copied out to the user's
	 * sigcode in the stack.  Since we are changing it in the global
	 * array we must always reset it, even for non-HPUX processes.
	 *
	 * Note also that implementing it in this way creates a potential
	 * race where we could have tweaked it for process A which then
	 * blocks in the copyout to the stack and process B comes along
	 * and untweaks it causing A to wind up with the wrong setting
	 * when the copyout continues.  However, since we have already
	 * copied something out to this user stack page (thereby faulting
	 * it in), this scenerio is extremely unlikely.
E 31
	 */
D 11
	if ((u.u_procp->p_pptr->p_flag & SHPUX) &&
	    (u.u_procp->p_flag & STRC)) {
E 11
I 11
D 31
	if ((p->p_pptr->p_flag & SHPUX) &&
	    (p->p_flag & STRC)) {
E 11
		tweaksigcode(1);
D 12
		u.u_pcb.pcb_flags |= PCB_HPUXTRACE;
	} else if (u.u_pcb.pcb_flags & PCB_HPUXTRACE) {
E 12
I 12
		p->p_addr->u_pcb.pcb_flags |= PCB_HPUXTRACE;
	} else if (p->p_addr->u_pcb.pcb_flags & PCB_HPUXTRACE) {
E 12
		tweaksigcode(0);
D 12
		u.u_pcb.pcb_flags &= ~PCB_HPUXTRACE;
E 12
I 12
		p->p_addr->u_pcb.pcb_flags &= ~PCB_HPUXTRACE;
E 31
I 31
	{
		extern short sigcodetrap[];

D 35
		if ((p->p_pptr->p_flag & SHPUX) && (p->p_flag & STRC)) {
			p->p_addr->u_pcb.pcb_flags |= PCB_HPUXTRACE;
E 35
I 35
		if ((p->p_pptr->p_md.md_flags & MDP_HPUX) &&
D 39
		    (p->p_flag & STRC)) {
E 39
I 39
		    (p->p_flag & P_TRACED)) {
E 39
			p->p_md.md_flags |= MDP_HPUXTRACE;
E 35
			*sigcodetrap = 0x4E42;
		} else {
D 35
			p->p_addr->u_pcb.pcb_flags &= ~PCB_HPUXTRACE;
E 35
I 35
			p->p_md.md_flags &= ~MDP_HPUXTRACE;
E 35
			*sigcodetrap = 0x4E41;
		}
E 31
E 12
	}
#endif
}

I 37
/*
 * Info for CTL_HW
 */
E 37
I 36
D 47
extern	char machine[];
E 47
char	cpu_model[120];
D 47
extern	char ostype[], osrelease[], version[];
E 47
I 47
extern	char version[];
E 47

E 36
identifycpu()
{
I 36
	char *t, *mc;
	int len;
E 36
I 11

E 11
D 36
	printf("HP9000/");
E 36
	switch (machineid) {
	case HP_320:
D 36
		printf("320 (16.67Mhz");
E 36
I 36
		t = "320 (16.67MHz";
E 36
		break;
	case HP_330:
D 36
		printf("318/319/330 (16.67Mhz");
E 36
I 36
		t = "318/319/330 (16.67MHz";
E 36
		break;
	case HP_340:
D 36
		printf("340 (16.67Mhz");
E 36
I 36
		t = "340 (16.67MHz";
E 36
		break;
	case HP_350:
D 36
		printf("350 (25Mhz");
E 36
I 36
		t = "350 (25MHz";
E 36
		break;
	case HP_360:
D 36
		printf("360 (25Mhz");
E 36
I 36
		t = "360 (25MHz";
E 36
		break;
	case HP_370:
D 36
		printf("370 (33.33Mhz");
E 36
I 36
		t = "370 (33.33MHz";
E 36
		break;
I 3
	case HP_375:
D 36
		printf("345/375 (50Mhz");
E 36
I 36
		t = "345/375 (50MHz";
E 36
		break;
I 28
	case HP_380:
D 36
		printf("380/425 (25Mhz)");
E 36
I 36
		t = "380/425 (25MHz";
E 36
		break;
I 35
	case HP_433:
D 36
		printf("433 (33Mhz)");
E 36
I 36
		t = "433 (33MHz";
E 36
		break;
E 35
E 28
E 3
	default:
		printf("\nunknown machine type %d\n", machineid);
		panic("startup");
	}
D 28
	printf(" MC680%s CPU", mmutype == MMU_68030 ? "30" : "20");
E 28
I 28
D 36
	printf(" MC680%s CPU",
	       mmutype == MMU_68040 ? "40" :
E 36
I 36
	mc = (mmutype == MMU_68040 ? "40" :
E 36
	       (mmutype == MMU_68030 ? "30" : "20"));
I 36
	sprintf(cpu_model, "HP9000/%s MC680%s CPU", t, mc);
E 36
E 28
	switch (mmutype) {
I 28
	case MMU_68040:
E 28
	case MMU_68030:
D 36
		printf("+MMU");
E 36
I 36
		strcat(cpu_model, "+MMU");
E 36
		break;
	case MMU_68851:
D 36
		printf(", MC68851 MMU");
E 36
I 36
		strcat(cpu_model, ", MC68851 MMU");
E 36
		break;
	case MMU_HP:
D 36
		printf(", HP MMU");
E 36
I 36
		strcat(cpu_model, ", HP MMU");
E 36
		break;
	default:
D 36
		printf("\nunknown MMU type %d\n", mmutype);
E 36
I 36
		printf("%s\nunknown MMU type %d\n", cpu_model, mmutype);
E 36
		panic("startup");
	}
I 36
	len = strlen(cpu_model);
E 36
D 28
	if (mmutype == MMU_68030)
E 28
I 28
	if (mmutype == MMU_68040)
D 36
		printf("+FPU, 4k on-chip physical I/D caches");
E 36
I 36
		len += sprintf(cpu_model + len,
		    "+FPU, 4k on-chip physical I/D caches");
E 36
	else if (mmutype == MMU_68030)
E 28
D 36
		printf(", %sMhz MC68882 FPU",
E 36
I 36
		len += sprintf(cpu_model + len, ", %sMHz MC68882 FPU",
E 36
		       machineid == HP_340 ? "16.67" :
D 3
		       (machineid == HP_360 ? "25" : "33.33"));
E 3
I 3
		       (machineid == HP_360 ? "25" :
			(machineid == HP_370 ? "33.33" : "50")));
E 3
	else
D 36
		printf(", %sMhz MC68881 FPU",
E 36
I 36
		len += sprintf(cpu_model + len, ", %sMHz MC68881 FPU",
E 36
		       machineid == HP_350 ? "20" : "16.67");
	switch (ectype) {
	case EC_VIRT:
D 36
		printf(", %dK virtual-address cache",
E 36
I 36
		sprintf(cpu_model + len, ", %dK virtual-address cache",
E 36
		       machineid == HP_320 ? 16 : 32);
		break;
	case EC_PHYS:
D 3
		printf(", 64K physical-address cache");
E 3
I 3
D 36
		printf(", %dK physical-address cache",
E 36
I 36
		sprintf(cpu_model + len, ", %dK physical-address cache",
E 36
		       machineid == HP_370 ? 64 : 32);
E 3
		break;
	}
D 36
	printf(")\n");
E 36
I 36
	strcat(cpu_model, ")");
	printf("%s\n", cpu_model);
E 36
	/*
	 * Now that we have told the user what they have,
	 * let them know if that machine type isn't configured.
	 */
	switch (machineid) {
	case -1:		/* keep compilers happy */
#if !defined(HP320) && !defined(HP350)
	case HP_320:
	case HP_350:
#endif
#ifndef HP330
	case HP_330:
#endif
#if !defined(HP360) && !defined(HP370)
	case HP_340:
	case HP_360:
	case HP_370:
#endif
I 28
#if !defined(HP380)
	case HP_380:
I 35
	case HP_433:
E 35
#endif
E 28
		panic("CPU type not configured");
	default:
		break;
	}
I 37
}

/*
 * machine dependent system variables.
 */
cpu_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
	int *name;
	u_int namelen;
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
	struct proc *p;
{

	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case CPU_CONSDEV:
		return (sysctl_rdstruct(oldp, oldlenp, newp, &cn_tty->t_dev,
		    sizeof cn_tty->t_dev));
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
E 37
}
D 31

#ifdef HPUXCOMPAT
tweaksigcode(ishpux)
{
	static short *sigtrap = NULL;
I 12
	extern short sigcode[], esigcode[];
E 12

	/* locate trap instruction in pcb_sigc */
	if (sigtrap == NULL) {
D 12
		register struct pcb *pcp = &u.u_pcb;

		sigtrap = &pcp->pcb_sigc[sizeof(pcp->pcb_sigc)/sizeof(short)];
		while (--sigtrap >= pcp->pcb_sigc)
E 12
I 12
		sigtrap = esigcode;
		while (--sigtrap >= sigcode)
E 12
			if ((*sigtrap & 0xFFF0) == 0x4E40)
				break;
D 12
		if (sigtrap < pcp->pcb_sigc)
E 12
I 12
		if (sigtrap < sigcode)
E 12
			panic("bogus sigcode\n");
	}
	*sigtrap = ishpux ? 0x4E42 : 0x4E41;
}
#endif
E 31

I 35
#ifdef USELEDS
#include <hp300/hp300/led.h>

int inledcontrol = 0;	/* 1 if we are in ledcontrol already, cheap mutex */
char *ledaddr;

/*
 * Map the LED page and setup the KVA to access it.
 */
ledinit()
{
	extern caddr_t ledbase;

	pmap_enter(kernel_pmap, (vm_offset_t)ledbase, (vm_offset_t)LED_ADDR,
		   VM_PROT_READ|VM_PROT_WRITE, TRUE);
	ledaddr = (char *) ((int)ledbase | (LED_ADDR & PGOFSET));
}

/*
 * Do lights:
 *	`ons' is a mask of LEDs to turn on,
 *	`offs' is a mask of LEDs to turn off,
 *	`togs' is a mask of LEDs to toggle.
 * Note we don't use splclock/splx for mutual exclusion.
 * They are expensive and we really don't need to be that precise.
 * Besides we would like to be able to profile this routine.
 */
ledcontrol(ons, offs, togs)
	register int ons, offs, togs;
{
	static char currentleds;
	register char leds;

	inledcontrol = 1;
	leds = currentleds;
	if (ons)
		leds |= ons;
	if (offs)
		leds &= ~offs;
	if (togs)
		leds ^= togs;
	currentleds = leds;
	*ledaddr = ~leds;
	inledcontrol = 0;
}
#endif

E 35
#define SS_RTEFRAME	1
#define SS_FPSTATE	2
#define SS_USERREGS	4

struct sigstate {
	int	ss_flags;		/* which of the following are valid */
	struct	frame ss_frame;		/* original exception frame */
	struct	fpframe ss_fpstate;	/* 68881/68882 state info */
};

/*
 * WARNING: code in locore.s assumes the layout shown for sf_signum
 * thru sf_handler so... don't screw with them!
 */
struct sigframe {
	int	sf_signum;		/* signo for handler */
	int	sf_code;		/* additional info for handler */
	struct	sigcontext *sf_scp;	/* context ptr for handler */
	sig_t	sf_handler;		/* handler addr for u_sigc */
	struct	sigstate sf_state;	/* state of the hardware */
	struct	sigcontext sf_sc;	/* actual context */
};

#ifdef HPUXCOMPAT
struct	hpuxsigcontext {
	int	hsc_syscall;
	char	hsc_action;
	char	hsc_pad1;
	char	hsc_pad2;
	char	hsc_onstack;
	int	hsc_mask;
	int	hsc_sp;
	short	hsc_ps;
	int	hsc_pc;
/* the rest aren't part of the context but are included for our convenience */
	short	hsc_pad;
	u_int	hsc_magic;		/* XXX sigreturn: cookie */
	struct	sigcontext *hsc_realsc;	/* XXX sigreturn: ptr to BSD context */
};

/*
 * For an HP-UX process, a partial hpuxsigframe follows the normal sigframe.
 * Tremendous waste of space, but some HP-UX applications (e.g. LCL) need it.
 */
struct hpuxsigframe {
	int	hsf_signum;
	int	hsf_code;
	struct	sigcontext *hsf_scp;
	struct	hpuxsigcontext hsf_sc;
	int	hsf_regs[15];
};
#endif

#ifdef DEBUG
int sigdebug = 0;
int sigpid = 0;
#define SDB_FOLLOW	0x01
#define SDB_KSTACK	0x02
#define SDB_FPSTATE	0x04
#endif

/*
 * Send an interrupt to process.
 */
I 11
void
E 11
sendsig(catcher, sig, mask, code)
	sig_t catcher;
	int sig, mask;
D 48
	unsigned code;
E 48
I 48
	u_long code;
E 48
{
D 11
	register struct proc *p = u.u_procp;
E 11
I 11
	register struct proc *p = curproc;
E 11
	register struct sigframe *fp, *kfp;
	register struct frame *frame;
I 11
D 26
	register struct sigacts *ps = p->p_sigacts;
E 26
I 26
	register struct sigacts *psp = p->p_sigacts;
E 26
E 11
	register short ft;
	int oonstack, fsize;
I 13
D 35
	extern short exframesize[];
E 35
E 13
I 12
	extern char sigcode[], esigcode[];
E 12

D 11
	frame = (struct frame *)u.u_ar0;
E 11
I 11
D 21
	frame = (struct frame *)p->p_regs;
E 21
I 21
	frame = (struct frame *)p->p_md.md_regs;
E 21
E 11
	ft = frame->f_format;
D 11
	oonstack = u.u_onstack;
E 11
I 11
D 26
	oonstack = ps->ps_onstack;
E 26
I 26
	oonstack = psp->ps_sigstk.ss_flags & SA_ONSTACK;
E 26
E 11
	/*
	 * Allocate and validate space for the signal handler
	 * context. Note that if the stack is in P0 space, the
	 * call to grow() is a nop, and the useracc() check
	 * will fail if the process has not already allocated
	 * the space with a `brk'.
	 */
#ifdef HPUXCOMPAT
D 35
	if (p->p_flag & SHPUX)
E 35
I 35
	if (p->p_md.md_flags & MDP_HPUX)
E 35
		fsize = sizeof(struct sigframe) + sizeof(struct hpuxsigframe);
	else
#endif
	fsize = sizeof(struct sigframe);
D 11
	if (!u.u_onstack && (u.u_sigonstack & sigmask(sig))) {
		fp = (struct sigframe *)(u.u_sigsp - fsize);
		u.u_onstack = 1;
E 11
I 11
D 26
	if (!ps->ps_onstack && (ps->ps_sigonstack & sigmask(sig))) {
		fp = (struct sigframe *)(ps->ps_sigsp - fsize);
		ps->ps_onstack = 1;
E 26
I 26
	if ((psp->ps_flags & SAS_ALTSTACK) &&
	    (psp->ps_sigstk.ss_flags & SA_ONSTACK) == 0 &&
	    (psp->ps_sigonstack & sigmask(sig))) {
		fp = (struct sigframe *)(psp->ps_sigstk.ss_base +
D 28
		    psp->ps_sigstk.ss_size - fsize);
E 28
I 28
					 psp->ps_sigstk.ss_size - fsize);
E 28
		psp->ps_sigstk.ss_flags |= SA_ONSTACK;
E 26
E 11
	} else
		fp = (struct sigframe *)(frame->f_regs[SP] - fsize);
D 11
	if ((unsigned)fp <= USRSTACK - ctob(u.u_ssize)) 
		(void)grow((unsigned)fp);
E 11
I 11
	if ((unsigned)fp <= USRSTACK - ctob(p->p_vmspace->vm_ssize)) 
D 48
		(void)grow(p, (unsigned)fp);
E 48
I 48
		(void)grow(p, (vm_offset_t)fp);
E 48
E 11
#ifdef DEBUG
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
D 6
		printf("sendsig: pid %d, sig %d ssp %x usp %x scp %x ft %d\n",
E 6
I 6
		printf("sendsig(%d): sig %d ssp %x usp %x scp %x ft %d\n",
E 6
		       p->p_pid, sig, &oonstack, fp, &fp->sf_sc, ft);
#endif
	if (useracc((caddr_t)fp, fsize, B_WRITE) == 0) {
#ifdef DEBUG
		if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
D 6
			printf("sendsig: pid %d, useracc failed on sig %d\n",
E 6
I 6
			printf("sendsig(%d): useracc failed on sig %d\n",
E 6
			       p->p_pid, sig);
#endif
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
		SIGACTION(p, SIGILL) = SIG_DFL;
		sig = sigmask(SIGILL);
		p->p_sigignore &= ~sig;
		p->p_sigcatch &= ~sig;
		p->p_sigmask &= ~sig;
		psignal(p, SIGILL);
		return;
	}
	kfp = (struct sigframe *)malloc((u_long)fsize, M_TEMP, M_WAITOK);
	/* 
	 * Build the argument list for the signal handler.
	 */
	kfp->sf_signum = sig;
I 45
D 46
	/*
	 * If sendsig call was delayed due to process being traced,
	 * code will always be zero.  Look in ps_code to see if trapsignal
	 * stashed something there.
	 */
	if (code == 0 && (code = psp->ps_code))
		psp->ps_code = 0;
E 46
E 45
	kfp->sf_code = code;
	kfp->sf_scp = &fp->sf_sc;
	kfp->sf_handler = catcher;
	/*
	 * Save necessary hardware state.  Currently this includes:
	 *	- general registers
	 *	- original exception frame (if not a "normal" frame)
	 *	- FP coprocessor state
	 */
	kfp->sf_state.ss_flags = SS_USERREGS;
	bcopy((caddr_t)frame->f_regs,
	      (caddr_t)kfp->sf_state.ss_frame.f_regs, sizeof frame->f_regs);
D 28
	if (ft >= FMT9) {
E 28
I 28
	if (ft >= FMT7) {
E 28
#ifdef DEBUG
D 28
		if (ft != FMT9 && ft != FMTA && ft != FMTB)
E 28
I 28
D 35
		if (ft != FMT9 && ft != FMTA && ft != FMTB
#if defined(HP380)
		    && mmutype != MMU_68040 || mmutype==MMU_68040 && ft != FMT7
#endif
		    )
E 35
I 35
		if (ft > 15 || exframesize[ft] < 0)
E 35
E 28
			panic("sendsig: bogus frame type");
#endif
		kfp->sf_state.ss_flags |= SS_RTEFRAME;
		kfp->sf_state.ss_frame.f_format = frame->f_format;
		kfp->sf_state.ss_frame.f_vector = frame->f_vector;
		bcopy((caddr_t)&frame->F_u,
D 13
		      (caddr_t)&kfp->sf_state.ss_frame.F_u,
		      (ft == FMT9) ? FMT9SIZE :
		      (ft == FMTA) ? FMTASIZE : FMTBSIZE);
E 13
I 13
		      (caddr_t)&kfp->sf_state.ss_frame.F_u, exframesize[ft]);
E 13
		/*
D 13
		 * Gag!  Leave an indicator that we need to clean up the
		 * kernel stack.  We do this by setting the "pad word"
		 * above the hardware stack frame.  "bexit" in locore
		 * will then know that it must compress the kernel stack
		 * and create a normal four word stack frame.
E 13
I 13
		 * Leave an indicator that we need to clean up the kernel
		 * stack.  We do this by setting the "pad word" above the
		 * hardware stack frame to the amount the stack must be
		 * adjusted by.
		 *
		 * N.B. we increment rather than just set f_stackadj in
		 * case we are called from syscall when processing a
		 * sigreturn.  In that case, f_stackadj may be non-zero.
E 13
		 */
D 13
		frame->f_stackadj = -1;
E 13
I 13
		frame->f_stackadj += exframesize[ft];
		frame->f_format = frame->f_vector = 0;
E 13
#ifdef DEBUG
		if (sigdebug & SDB_FOLLOW)
D 6
			printf("sendsig: pid %d, copy out %d of frame %d\n",
E 6
I 6
			printf("sendsig(%d): copy out %d of frame %d\n",
E 6
D 13
			       p->p_pid,
			       (ft == FMT9) ? FMT9SIZE :
			       (ft == FMTA) ? FMTASIZE : FMTBSIZE, ft);
E 13
I 13
			       p->p_pid, exframesize[ft], ft);
E 13
#endif
	}
#ifdef FPCOPROC
	kfp->sf_state.ss_flags |= SS_FPSTATE;
	m68881_save(&kfp->sf_state.ss_fpstate);
#ifdef DEBUG
	if ((sigdebug & SDB_FPSTATE) && *(char *)&kfp->sf_state.ss_fpstate)
D 6
		printf("sendsig: pid %d, copy out FP state (%x) to %x\n",
E 6
I 6
		printf("sendsig(%d): copy out FP state (%x) to %x\n",
E 6
		       p->p_pid, *(u_int *)&kfp->sf_state.ss_fpstate,
		       &kfp->sf_state.ss_fpstate);
#endif
#endif
	/*
	 * Build the signal context to be used by sigreturn.
	 */
	kfp->sf_sc.sc_onstack = oonstack;
	kfp->sf_sc.sc_mask = mask;
	kfp->sf_sc.sc_sp = frame->f_regs[SP];
	kfp->sf_sc.sc_fp = frame->f_regs[A6];
	kfp->sf_sc.sc_ap = (int)&fp->sf_state;
	kfp->sf_sc.sc_pc = frame->f_pc;
	kfp->sf_sc.sc_ps = frame->f_sr;
#ifdef HPUXCOMPAT
	/*
	 * Create an HP-UX style sigcontext structure and associated goo
	 */
D 35
	if (p->p_flag & SHPUX) {
E 35
I 35
	if (p->p_md.md_flags & MDP_HPUX) {
E 35
		register struct hpuxsigframe *hkfp;

		hkfp = (struct hpuxsigframe *)&kfp[1];
		hkfp->hsf_signum = bsdtohpuxsig(kfp->sf_signum);
		hkfp->hsf_code = kfp->sf_code;
		hkfp->hsf_scp = (struct sigcontext *)
			&((struct hpuxsigframe *)(&fp[1]))->hsf_sc;
		hkfp->hsf_sc.hsc_syscall = 0;		/* XXX */
		hkfp->hsf_sc.hsc_action = 0;		/* XXX */
		hkfp->hsf_sc.hsc_pad1 = hkfp->hsf_sc.hsc_pad2 = 0;
		hkfp->hsf_sc.hsc_onstack = kfp->sf_sc.sc_onstack;
		hkfp->hsf_sc.hsc_mask = kfp->sf_sc.sc_mask;
		hkfp->hsf_sc.hsc_sp = kfp->sf_sc.sc_sp;
		hkfp->hsf_sc.hsc_ps = kfp->sf_sc.sc_ps;
		hkfp->hsf_sc.hsc_pc = kfp->sf_sc.sc_pc;
		hkfp->hsf_sc.hsc_pad = 0;
		hkfp->hsf_sc.hsc_magic = 0xdeadbeef;
		hkfp->hsf_sc.hsc_realsc = kfp->sf_scp;
		bcopy((caddr_t)frame->f_regs, (caddr_t)hkfp->hsf_regs,
		      sizeof (hkfp->hsf_regs));

		kfp->sf_signum = hkfp->hsf_signum;
		kfp->sf_scp = hkfp->hsf_scp;
	}
#endif
	(void) copyout((caddr_t)kfp, (caddr_t)fp, fsize);
	frame->f_regs[SP] = (int)fp;
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
D 6
		printf("sendsig: pid %d, scp %x, fp %x, sc_ap %x\n",
		       p->p_pid, kfp->sf_scp, fp, kfp->sf_sc.sc_ap);
E 6
I 6
		printf("sendsig(%d): sig %d scp %x fp %x sc_sp %x sc_ap %x\n",
		       p->p_pid, sig, kfp->sf_scp, fp,
		       kfp->sf_sc.sc_sp, kfp->sf_sc.sc_ap);
E 6
#endif
	/*
D 8
	 * User PC is set to signal trampoline code.  The catch is that
	 * it must be set to reference the pcb via the user space address
	 * NOT via u.  Assumption: u-area is at USRSTACK.
E 8
I 8
	 * Signal trampoline code is at base of user stack.
E 8
	 */
D 8
	frame->f_pc = (int)((struct user *)USRSTACK)->u_pcb.pcb_sigc;
E 8
I 8
D 12
	frame->f_pc = USRSTACK - sizeof(u.u_pcb.pcb_sigc);
E 12
I 12
D 24
	frame->f_pc = USRSTACK - (esigcode - sigcode);
E 24
I 24
	frame->f_pc = (int)PS_STRINGS - (esigcode - sigcode);
E 24
E 12
E 8
#ifdef DEBUG
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
D 6
		printf("sendsig: pid %d, sig %d, returns\n",
E 6
I 6
		printf("sendsig(%d): sig %d returns\n",
E 6
		       p->p_pid, sig);
#endif
	free((caddr_t)kfp, M_TEMP);
}

/*
 * System call to cleanup state after a signal
 * has been taken.  Reset signal mask and
 * stack state from context left by sendsig (above).
 * Return to previous pc and psl as specified by
 * context left by sendsig. Check carefully to
 * make sure that the user has not modified the
 * psl to gain improper priviledges or to cause
 * a machine fault.
 */
I 30
struct sigreturn_args {
	struct sigcontext *sigcntxp;
};
E 30
D 4
sigreturn()
{
	struct a {
E 4
I 4
/* ARGSUSED */
sigreturn(p, uap, retval)
	struct proc *p;
D 30
	struct args {
E 4
		struct sigcontext *sigcntxp;
D 4
	};
E 4
I 4
	} *uap;
E 30
I 30
	struct sigreturn_args *uap;
E 30
	int *retval;
{
E 4
	register struct sigcontext *scp;
	register struct frame *frame;
	register int rf;
	struct sigcontext tsigc;
	struct sigstate tstate;
	int flags;
I 13
D 35
	extern short exframesize[];
E 35
E 13

D 4
	scp = ((struct a *)(u.u_ap))->sigcntxp;
E 4
I 4
	scp = uap->sigcntxp;
E 4
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
D 4
		printf("sigreturn: pid %d, scp %x\n", u.u_procp->p_pid, scp);
E 4
I 4
		printf("sigreturn: pid %d, scp %x\n", p->p_pid, scp);
E 4
#endif
D 2
	if ((int)scp & 1) {
		u.u_error = EINVAL;
		return;
	}
E 2
I 2
	if ((int)scp & 1)
D 7
		RETURN (EINVAL);
E 7
I 7
		return (EINVAL);
E 7
E 2
#ifdef HPUXCOMPAT
	/*
	 * Grab context as an HP-UX style context and determine if it
	 * was one that we contructed in sendsig.
	 */
D 4
	if (u.u_procp->p_flag & SHPUX) {
E 4
I 4
D 35
	if (p->p_flag & SHPUX) {
E 35
I 35
	if (p->p_md.md_flags & MDP_HPUX) {
E 35
E 4
		struct hpuxsigcontext *hscp = (struct hpuxsigcontext *)scp;
		struct hpuxsigcontext htsigc;

		if (useracc((caddr_t)hscp, sizeof (*hscp), B_WRITE) == 0 ||
		    copyin((caddr_t)hscp, (caddr_t)&htsigc, sizeof htsigc))
D 2
			return;
E 2
I 2
D 4
			RETURN (0);
E 4
I 4
D 7
			RETURN (EINVAL);
E 7
I 7
			return (EINVAL);
E 7
E 4
E 2
		/*
		 * If not generated by sendsig or we cannot restore the
		 * BSD-style sigcontext, just restore what we can -- state
		 * will be lost, but them's the breaks.
		 */
		hscp = &htsigc;
		if (hscp->hsc_magic != 0xdeadbeef ||
		    (scp = hscp->hsc_realsc) == 0 ||
		    useracc((caddr_t)scp, sizeof (*scp), B_WRITE) == 0 ||
		    copyin((caddr_t)scp, (caddr_t)&tsigc, sizeof tsigc)) {
D 2
			u.u_eosys = JUSTRETURN;
E 2
D 11
			u.u_onstack = hscp->hsc_onstack & 01;
E 11
I 11
D 26
			p->p_sigacts->ps_onstack = hscp->hsc_onstack & 01;
E 26
I 26
			if (hscp->hsc_onstack & 01)
				p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
			else
				p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;
E 26
E 11
D 4
			u.u_procp->p_sigmask = hscp->hsc_mask &~ sigcantmask;
E 4
I 4
			p->p_sigmask = hscp->hsc_mask &~ sigcantmask;
E 4
D 11
			frame = (struct frame *) u.u_ar0;
E 11
I 11
D 21
			frame = (struct frame *) p->p_regs;
E 21
I 21
			frame = (struct frame *) p->p_md.md_regs;
E 21
E 11
			frame->f_regs[SP] = hscp->hsc_sp;
			frame->f_pc = hscp->hsc_pc;
			frame->f_sr = hscp->hsc_ps &~ PSL_USERCLR;
D 2
			return;
E 2
I 2
D 7
			RETURN (EJUSTRETURN);
E 7
I 7
			return (EJUSTRETURN);
E 7
E 2
		}
		/*
		 * Otherwise, overlay BSD context with possibly modified
		 * HP-UX values.
		 */
		tsigc.sc_onstack = hscp->hsc_onstack;
		tsigc.sc_mask = hscp->hsc_mask;
		tsigc.sc_sp = hscp->hsc_sp;
		tsigc.sc_ps = hscp->hsc_ps;
		tsigc.sc_pc = hscp->hsc_pc;
	} else
#endif
	/*
	 * Test and fetch the context structure.
	 * We grab it all at once for speed.
	 */
	if (useracc((caddr_t)scp, sizeof (*scp), B_WRITE) == 0 ||
	    copyin((caddr_t)scp, (caddr_t)&tsigc, sizeof tsigc))
D 2
		return;
E 2
I 2
D 7
		RETURN (EINVAL);
E 7
I 7
		return (EINVAL);
E 7
E 2
	scp = &tsigc;
D 2
	if ((scp->sc_ps & (PSL_MBZ|PSL_IPL|PSL_S)) != 0) {
		u.u_error = EINVAL;
		return;
	}
E 2
I 2
	if ((scp->sc_ps & (PSL_MBZ|PSL_IPL|PSL_S)) != 0)
D 7
		RETURN (EINVAL);
E 7
I 7
		return (EINVAL);
E 7
E 2
	/*
	 * Restore the user supplied information
	 */
D 2
	u.u_eosys = JUSTRETURN;
E 2
D 11
	u.u_onstack = scp->sc_onstack & 01;
E 11
I 11
D 26
	p->p_sigacts->ps_onstack = scp->sc_onstack & 01;
E 26
I 26
	if (scp->sc_onstack & 01)
		p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
	else
		p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;
E 26
E 11
D 4
	u.u_procp->p_sigmask = scp->sc_mask &~ sigcantmask;
E 4
I 4
	p->p_sigmask = scp->sc_mask &~ sigcantmask;
E 4
D 11
	frame = (struct frame *) u.u_ar0;
E 11
I 11
D 21
	frame = (struct frame *) p->p_regs;
E 21
I 21
	frame = (struct frame *) p->p_md.md_regs;
E 21
E 11
	frame->f_regs[SP] = scp->sc_sp;
	frame->f_regs[A6] = scp->sc_fp;
	frame->f_pc = scp->sc_pc;
	frame->f_sr = scp->sc_ps;
	/*
	 * Grab pointer to hardware state information.
	 * If zero, the user is probably doing a longjmp.
	 */
	if ((rf = scp->sc_ap) == 0)
D 2
		return;
E 2
I 2
D 4
		RETURN (JUSTRETURN);
E 4
I 4
D 7
		RETURN (EJUSTRETURN);
E 7
I 7
		return (EJUSTRETURN);
E 7
E 4
E 2
	/*
	 * See if there is anything to do before we go to the
	 * expense of copying in close to 1/2K of data
	 */
	flags = fuword((caddr_t)rf);
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
D 6
		printf("sigreturn: pid %d, sc_ap %x, flags %x\n",
E 6
I 6
		printf("sigreturn(%d): sc_ap %x flags %x\n",
E 6
D 4
		       u.u_procp->p_pid, rf, flags);
E 4
I 4
		       p->p_pid, rf, flags);
E 4
#endif
I 13
	/*
	 * fuword failed (bogus sc_ap value).
	 */
	if (flags == -1)
		return (EINVAL);
E 13
	if (flags == 0 || copyin((caddr_t)rf, (caddr_t)&tstate, sizeof tstate))
D 2
		return;
E 2
I 2
D 4
		RETURN (JUSTRETURN);
E 4
I 4
D 7
		RETURN (EJUSTRETURN);
E 7
I 7
		return (EJUSTRETURN);
E 7
E 4
E 2
#ifdef DEBUG
D 4
	if ((sigdebug & SDB_KSTACK) && u.u_procp->p_pid == sigpid)
E 4
I 4
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
E 4
D 6
		printf("sigreturn: pid %d, ssp %x usp %x scp %x ft %d\n",
E 6
I 6
		printf("sigreturn(%d): ssp %x usp %x scp %x ft %d\n",
E 6
D 4
		       u.u_procp->p_pid, &flags, scp->sc_sp,
		       ((struct a *)(u.u_ap))->sigcntxp,
E 4
I 4
		       p->p_pid, &flags, scp->sc_sp, uap->sigcntxp,
E 4
		       (flags&SS_RTEFRAME) ? tstate.ss_frame.f_format : -1);
#endif
	/*
	 * Restore most of the users registers except for A6 and SP
	 * which were handled above.
	 */
	if (flags & SS_USERREGS)
		bcopy((caddr_t)tstate.ss_frame.f_regs,
		      (caddr_t)frame->f_regs, sizeof(frame->f_regs)-2*NBPW);
	/*
	 * Restore long stack frames.  Note that we do not copy
	 * back the saved SR or PC, they were picked up above from
	 * the sigcontext structure.
	 */
	if (flags & SS_RTEFRAME) {
		register int sz;
		
		/* grab frame type and validate */
		sz = tstate.ss_frame.f_format;
D 13
		if (sz == FMT9)
			sz = FMT9SIZE;
		else if (sz == FMTA)
			sz = FMTASIZE;
		else if (sz == FMTB) {
			sz = FMTBSIZE;
			/* no k-stack adjustment necessary */
			frame->f_stackadj = 0;
D 2
		} else {
			u.u_error = EINVAL;
			return;
		}
E 2
I 2
		} else
E 13
I 13
		if (sz > 15 || (sz = exframesize[sz]) < 0)
E 13
D 7
			RETURN (EINVAL);
E 7
I 7
			return (EINVAL);
I 13
		frame->f_stackadj -= sz;
E 13
E 7
E 2
		frame->f_format = tstate.ss_frame.f_format;
		frame->f_vector = tstate.ss_frame.f_vector;
		bcopy((caddr_t)&tstate.ss_frame.F_u, (caddr_t)&frame->F_u, sz);
#ifdef DEBUG
		if (sigdebug & SDB_FOLLOW)
D 6
			printf("sigreturn: copy in %d of frame type %d\n",
			       sz, tstate.ss_frame.f_format);
E 6
I 6
			printf("sigreturn(%d): copy in %d of frame type %d\n",
			       p->p_pid, sz, tstate.ss_frame.f_format);
E 6
#endif
	}
#ifdef FPCOPROC
	/*
	 * Finally we restore the original FP context
	 */
	if (flags & SS_FPSTATE)
		m68881_restore(&tstate.ss_fpstate);
#ifdef DEBUG
	if ((sigdebug & SDB_FPSTATE) && *(char *)&tstate.ss_fpstate)
D 6
		printf("sigreturn: pid %d, copied in FP state (%x) at %x\n",
E 6
I 6
		printf("sigreturn(%d): copied in FP state (%x) at %x\n",
E 6
D 4
		       u.u_procp->p_pid, *(u_int *)&tstate.ss_fpstate,
E 4
I 4
		       p->p_pid, *(u_int *)&tstate.ss_fpstate,
E 4
		       &tstate.ss_fpstate);
#endif
#endif
#ifdef DEBUG
	if ((sigdebug & SDB_FOLLOW) ||
D 4
	    ((sigdebug & SDB_KSTACK) && u.u_procp->p_pid == sigpid))
E 4
I 4
	    ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid))
E 4
D 6
		printf("sigreturn: pid %d, returns\n", u.u_procp->p_pid);
E 6
I 6
		printf("sigreturn(%d): returns\n", p->p_pid);
E 6
#endif
I 2
D 4
	RETURN (JUSTRETURN);
E 4
I 4
D 7
	RETURN (EJUSTRETURN);
E 7
I 7
	return (EJUSTRETURN);
E 7
E 4
E 2
}

int	waittime = -1;

boot(howto)
	register int howto;
{
I 51
	struct proc *p = curproc;	/* XXX */

E 51
	/* take a snap shot before clobbering any registers */
D 8
	resume((u_int)pcbb(u.u_procp));
E 8
I 8
D 11
	if (u.u_procp)
		resume((u_int)pcbb(u.u_procp));
E 11
I 11
D 41
	if (curproc)
E 41
I 41
	if (curproc && curproc->p_addr)
E 41
D 12
		resume((u_int)pcbb(curproc));
E 12
I 12
		savectx(curproc->p_addr, 0);
E 12
E 11
E 8

	boothowto = howto;
D 32
	if ((howto&RB_NOSYNC) == 0 && waittime < 0 && bfreelist[0].b_forw) {
E 32
I 32
	if ((howto&RB_NOSYNC) == 0 && waittime < 0) {
E 32
		register struct buf *bp;
		int iter, nbusy;

		waittime = 0;
		(void) spl0();
		printf("syncing disks... ");
		/*
		 * Release vnodes held by texts before sync.
		 */
		if (panicstr == 0)
D 8
			xumount(NULL);
E 8
I 8
			vnode_pager_umount(NULL);
I 11
#ifdef notdef
E 11
E 8
D 41
#include "fd.h"
#if NFD > 0
		fdshutdown();
E 41
I 41
#include "vn.h"
#if NVN > 0
		vnshutdown();
E 41
#endif
D 11
		sync((struct sigcontext *)0);
E 11
I 11
#endif
D 51
		sync(&proc0, (void *)NULL, (int *)NULL);
E 51
I 51
		sync(p, (void *)NULL, (int *)NULL);
E 51
I 49
		/*
		 * Unmount filesystems
		 */
		if (panicstr == 0)
			vfs_unmountall();
E 49
E 11

		for (iter = 0; iter < 20; iter++) {
			nbusy = 0;
			for (bp = &buf[nbuf]; --bp >= buf; )
				if ((bp->b_flags & (B_BUSY|B_INVAL)) == B_BUSY)
					nbusy++;
			if (nbusy == 0)
				break;
			printf("%d ", nbusy);
			DELAY(40000 * iter);
		}
		if (nbusy)
			printf("giving up\n");
		else
			printf("done\n");
		/*
		 * If we've been adjusting the clock, the todr
		 * will be out of synch; adjust it now.
		 */
		resettodr();
	}
	splhigh();			/* extreme priority */
	if (howto&RB_HALT) {
		printf("halted\n\n");
		asm("	stop	#0x2700");
	} else {
		if (howto & RB_DUMP)
			dumpsys();
		doboot();
		/*NOTREACHED*/
	}
	/*NOTREACHED*/
}

int	dumpmag = 0x8fca0101;	/* magic number for savecore */
int	dumpsize = 0;		/* also for savecore */
I 13
long	dumplo = 0;
E 13

dumpconf()
{
	int nblks;

D 44
	dumpsize = physmem;
E 44
I 44
	/*
	 * XXX include the final RAM page which is not included in physmem.
	 */
	dumpsize = physmem + 1;
E 44
	if (dumpdev != NODEV && bdevsw[major(dumpdev)].d_psize) {
		nblks = (*bdevsw[major(dumpdev)].d_psize)(dumpdev);
		if (dumpsize > btoc(dbtob(nblks - dumplo)))
			dumpsize = btoc(dbtob(nblks - dumplo));
		else if (dumplo == 0)
D 44
			dumplo = nblks - btodb(ctob(physmem));
E 44
I 44
			dumplo = nblks - btodb(ctob(dumpsize));
E 44
	}
	/*
	 * Don't dump on the first CLBYTES (why CLBYTES?)
	 * in case the dump device includes a disk label.
	 */
	if (dumplo < btodb(CLBYTES))
		dumplo = btodb(CLBYTES);
}

/*
 * Doadump comes here after turning off memory management and
 * getting on the dump stack, either when called above, or by
 * the auto-restart code.
 */
dumpsys()
{

	msgbufmapped = 0;
	if (dumpdev == NODEV)
		return;
	/*
	 * For dumps during autoconfiguration,
	 * if dump device has already configured...
	 */
	if (dumpsize == 0)
		dumpconf();
	if (dumplo < 0)
		return;
	printf("\ndumping to dev %x, offset %d\n", dumpdev, dumplo);
	printf("dump ");
	switch ((*bdevsw[major(dumpdev)].d_dump)(dumpdev)) {

	case ENXIO:
		printf("device bad\n");
		break;

	case EFAULT:
		printf("device not ready\n");
		break;

	case EINVAL:
		printf("area improper\n");
		break;

	case EIO:
		printf("i/o error\n");
		break;

	default:
		printf("succeeded\n");
		break;
	}
}

D 29
/*
 * Return the best possible estimate of the time in the timeval
 * to which tvp points.  We do this by returning the current time
 * plus the amount of time since the last clock interrupt (clock.c:clkread).
 *
 * Check that this time is no less than any previously-reported time,
 * which could happen around the time of a clock adjustment.  Just for fun,
 * we guarantee that the time will be greater than the value obtained by a
 * previous call.
 */
microtime(tvp)
	register struct timeval *tvp;
{
	int s = splhigh();
	static struct timeval lasttime;

	*tvp = time;
	tvp->tv_usec += clkread();
	while (tvp->tv_usec > 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	if (tvp->tv_sec == lasttime.tv_sec &&
	    tvp->tv_usec <= lasttime.tv_usec &&
	    (tvp->tv_usec = lasttime.tv_usec + 1) > 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	lasttime = *tvp;
	splx(s);
}

E 29
initcpu()
{
I 40
#ifdef MAPPEDCOPY
	extern u_int mappedcopysize;

	/*
	 * Initialize lower bound for doing copyin/copyout using
	 * page mapping (if not already set).  We don't do this on
	 * VAC machines as it loses big time.
	 */
	if (mappedcopysize == 0) {
		if (ectype == EC_VIRT)
			mappedcopysize = (u_int) -1;
		else
			mappedcopysize = NBPG;
	}
#endif
E 40
	parityenable();
I 35
#ifdef USELEDS
	ledinit();
#endif
E 35
}

D 13
straytrap(addr)
	register int addr;
E 13
I 13
straytrap(pc, evec)
	int pc;
	u_short evec;
E 13
{
D 13
	printf("stray trap, addr 0x%x\n", addr);
E 13
I 13
	printf("unexpected trap (vector offset %x) from %x\n",
	       evec & 0xFFF, pc);
E 13
}

int	*nofault;

badaddr(addr)
	register caddr_t addr;
{
	register int i;
	label_t	faultbuf;

#ifdef lint
	i = *addr; if (i) return(0);
#endif
	nofault = (int *) &faultbuf;
	if (setjmp((label_t *)nofault)) {
		nofault = (int *) 0;
		return(1);
	}
	i = *(volatile short *)addr;
	nofault = (int *) 0;
	return(0);
}

badbaddr(addr)
	register caddr_t addr;
{
	register int i;
	label_t	faultbuf;

#ifdef lint
	i = *addr; if (i) return(0);
#endif
	nofault = (int *) &faultbuf;
	if (setjmp((label_t *)nofault)) {
		nofault = (int *) 0;
		return(1);
	}
	i = *(volatile char *)addr;
	nofault = (int *) 0;
	return(0);
}

netintr()
{
#ifdef INET
I 17
	if (netisr & (1 << NETISR_ARP)) {
		netisr &= ~(1 << NETISR_ARP);
		arpintr();
	}
E 17
	if (netisr & (1 << NETISR_IP)) {
		netisr &= ~(1 << NETISR_IP);
		ipintr();
	}
#endif
#ifdef NS
	if (netisr & (1 << NETISR_NS)) {
		netisr &= ~(1 << NETISR_NS);
		nsintr();
	}
#endif
#ifdef ISO
	if (netisr & (1 << NETISR_ISO)) {
		netisr &= ~(1 << NETISR_ISO);
		clnlintr();
	}
#endif
I 34
#ifdef CCITT
	if (netisr & (1 << NETISR_CCITT)) {
		netisr &= ~(1 << NETISR_CCITT);
		ccittintr();
	}
#endif
E 34
}

D 3
#ifdef DEBUG
int panicbutton = 1;	/* non-zero if panic buttons are enabled */
int crashandburn = 0;
int candbdelay = 50;	/* give em half a second */

candbtimer()
{
	crashandburn = 0;
}
#endif

E 3
intrhand(sr)
	int sr;
{
	register struct isr *isr;
	register int found = 0;
	register int ipl;
	extern struct isr isrqueue[];
I 41
	static int straycount;
E 41

	ipl = (sr >> 8) & 7;
	switch (ipl) {

	case 3:
	case 4:
	case 5:
		ipl = ISRIPL(ipl);
		isr = isrqueue[ipl].isr_forw;
		for (; isr != &isrqueue[ipl]; isr = isr->isr_forw) {
			if ((isr->isr_intr)(isr->isr_arg)) {
				found++;
				break;
			}
		}
D 41
		if (found == 0)
E 41
I 41
		if (found)
			straycount = 0;
		else if (++straycount > 50)
			panic("intrhand: stray interrupt");
		else
E 41
			printf("stray interrupt, sr 0x%x\n", sr);
		break;

	case 0:
	case 1:
	case 2:
	case 6:
	case 7:
D 41
		printf("intrhand: unexpected sr 0x%x\n", sr);
E 41
I 41
		if (++straycount > 50)
			panic("intrhand: unexpected sr");
		else
			printf("intrhand: unexpected sr 0x%x\n", sr);
E 41
		break;
	}
}

I 3
#if defined(DEBUG) && !defined(PANICBUTTON)
#define PANICBUTTON
#endif

#ifdef PANICBUTTON
int panicbutton = 1;	/* non-zero if panic buttons are enabled */
int crashandburn = 0;
int candbdelay = 50;	/* give em half a second */

D 29
candbtimer()
E 29
I 29
void
candbtimer(arg)
	void *arg;
E 29
{
I 29

E 29
	crashandburn = 0;
}
#endif

E 3
/*
 * Level 7 interrupts can be caused by the keyboard or parity errors.
 */
nmihand(frame)
	struct frame frame;
{
	if (kbdnmi()) {
D 3
#ifdef DEBUG
E 3
I 3
#ifdef PANICBUTTON
E 3
D 13
		printf("Got a keyboard NMI\n");
E 13
I 13
		static int innmihand = 0;

		/*
		 * Attempt to reduce the window of vulnerability for recursive
		 * NMIs (e.g. someone holding down the keyboard reset button).
		 */
		if (innmihand == 0) {
			innmihand = 1;
			printf("Got a keyboard NMI\n");
			innmihand = 0;
		}
E 13
D 3
		if (panicbutton && !panicstr) {
E 3
I 3
		if (panicbutton) {
E 3
			if (crashandburn) {
D 3
#ifdef BELLS
				panicstr = "Yow!!";
#endif
				panic("forced crash");
E 3
I 3
				crashandburn = 0;
				panic(panicstr ?
				      "forced crash, nosync" : "forced crash");
E 3
			}
			crashandburn++;
D 29
			timeout(candbtimer, (caddr_t)0, candbdelay);
E 29
I 29
			timeout(candbtimer, (void *)0, candbdelay);
E 29
		}
#endif
		return;
	}
	if (parityerror(&frame))
		return;
	/* panic?? */
	printf("unexpected level 7 interrupt ignored\n");
}

/*
 * Parity error section.  Contains magic.
 */
D 13
#define PARREG		((volatile short *)IOV(0x5B0000))
E 13
I 13
#define PARREG		((volatile short *)IIOV(0x5B0000))
E 13
static int gotparmem = 0;
#ifdef DEBUG
int ignorekperr = 0;	/* ignore kernel parity errors */
#endif

/*
 * Enable parity detection
 */
parityenable()
{
	label_t	faultbuf;

	nofault = (int *) &faultbuf;
	if (setjmp((label_t *)nofault)) {
		nofault = (int *) 0;
#ifdef DEBUG
		printf("No parity memory\n");
#endif
		return;
	}
	*PARREG = 1;
	nofault = (int *) 0;
	gotparmem = 1;
#ifdef DEBUG
	printf("Parity detection enabled\n");
#endif
}

/*
 * Determine if level 7 interrupt was caused by a parity error
 * and deal with it if it was.  Returns 1 if it was a parity error.
 */
parityerror(fp)
	struct frame *fp;
{
	if (!gotparmem)
		return(0);
	*PARREG = 0;
	DELAY(10);
	*PARREG = 1;
	if (panicstr) {
		printf("parity error after panic ignored\n");
		return(1);
	}
	if (!findparerror())
		printf("WARNING: transient parity error ignored\n");
	else if (USERMODE(fp->f_sr)) {
D 11
		printf("pid %d: parity error\n", u.u_procp->p_pid);
E 11
I 11
		printf("pid %d: parity error\n", curproc->p_pid);
E 11
		uprintf("sorry, pid %d killed due to memory parity error\n",
D 11
			u.u_procp->p_pid);
		psignal(u.u_procp, SIGKILL);
E 11
I 11
			curproc->p_pid);
		psignal(curproc, SIGKILL);
E 11
#ifdef DEBUG
	} else if (ignorekperr) {
		printf("WARNING: kernel parity error ignored\n");
#endif
	} else {
D 35
		regdump(fp->f_regs, 128);
E 35
I 35
		regdump(fp, 128);
E 35
		panic("kernel parity error");
	}
	return(1);
}

/*
 * Yuk!  There has got to be a better way to do this!
 * Searching all of memory with interrupts blocked can lead to disaster.
 */
findparerror()
{
	static label_t parcatch;
	static int looking = 0;
D 42
	volatile struct pte opte;
E 42
	volatile int pg, o, s;
	register volatile int *ip;
	register int i;
	int found;

#ifdef lint
D 42
	ip = &found;
E 42
	i = o = pg = 0; if (i) return(0);
#endif
	/*
	 * If looking is true we are searching for a known parity error
	 * and it has just occured.  All we do is return to the higher
	 * level invocation.
	 */
	if (looking)
		longjmp(&parcatch);
	s = splhigh();
	/*
	 * If setjmp returns true, the parity error we were searching
	 * for has just occured (longjmp above) at the current pg+o
	 */
	if (setjmp(&parcatch)) {
		printf("Parity error at 0x%x\n", ctob(pg)|o);
		found = 1;
		goto done;
	}
	/*
	 * If we get here, a parity error has occured for the first time
	 * and we need to find it.  We turn off any external caches and
	 * loop thru memory, testing every longword til a fault occurs and
	 * we regain control at setjmp above.  Note that because of the
	 * setjmp, pg and o need to be volatile or their values will be lost.
	 */
	looking = 1;
	ecacheoff();
D 8
	opte = mmap[0];
E 8
	for (pg = btoc(lowram); pg < btoc(lowram)+physmem; pg++) {
D 8
		*(u_int *)mmap = PG_RO|PG_CI|PG_V;
		mmap[0].pg_pfnum = pg;
		TBIS(vmmap);
		ip = (int *)vmmap;
E 8
I 8
D 20
		pmap_enter(pmap_kernel(), vmmap, ctob(pg), VM_PROT_READ, TRUE);
E 20
I 20
D 22
		pmap_enter(pmap_kernel(), (vm_offset_t)vmmap, ctob(pg),
E 22
I 22
		pmap_enter(kernel_pmap, (vm_offset_t)vmmap, ctob(pg),
E 22
		    VM_PROT_READ, TRUE);
I 42
		ip = (int *)vmmap;
E 42
E 20
E 8
		for (o = 0; o < NBPG; o += sizeof(int))
D 8
			i = *ip++;
E 8
I 8
D 42
			i = *(int *)(&vmmap[o]);
E 42
I 42
			i = *ip++;
E 42
E 8
	}
	/*
	 * Getting here implies no fault was found.  Should never happen.
	 */
	printf("Couldn't locate parity error\n");
	found = 0;
done:
	looking = 0;
D 8
	mmap[0] = opte;
	TBIS(vmmap);
E 8
I 8
D 20
	pmap_remove(pmap_kernel(), vmmap, &vmmap[NBPG]);
E 20
I 20
D 22
	pmap_remove(pmap_kernel(), (vm_offset_t)vmmap,
E 22
I 22
D 42
	pmap_remove(kernel_pmap, (vm_offset_t)vmmap,
E 22
	    (vm_offset_t)&vmmap[NBPG]);
E 42
I 42
	pmap_remove(kernel_pmap, (vm_offset_t)vmmap, (vm_offset_t)&vmmap[NBPG]);
E 42
E 20
E 8
	ecacheon();
	splx(s);
	return(found);
}

D 35
regdump(rp, sbytes)
  int *rp; /* must not be register */
  int sbytes;
E 35
I 35
regdump(fp, sbytes)
	struct frame *fp; /* must not be register */
	int sbytes;
E 35
{
	static int doingdump = 0;
	register int i;
	int s;
	extern char *hexstr();

	if (doingdump)
		return;
	s = splhigh();
	doingdump = 1;
D 11
	printf("pid = %d, pc = %s, ", u.u_procp->p_pid, hexstr(rp[PC], 8));
E 11
I 11
D 35
	printf("pid = %d, pc = %s, ", curproc->p_pid, hexstr(rp[PC], 8));
E 11
	printf("ps = %s, ", hexstr(rp[PS], 4));
E 35
I 35
	printf("pid = %d, pc = %s, ",
	       curproc ? curproc->p_pid : -1, hexstr(fp->f_pc, 8));
	printf("ps = %s, ", hexstr(fp->f_sr, 4));
E 35
	printf("sfc = %s, ", hexstr(getsfc(), 4));
	printf("dfc = %s\n", hexstr(getdfc(), 4));
D 8
	printf("p0 = %x@%s, ",
	       u.u_pcb.pcb_p0lr, hexstr((int)u.u_pcb.pcb_p0br, 8));
	printf("p1 = %x@%s\n\n",
	       u.u_pcb.pcb_p1lr, hexstr((int)u.u_pcb.pcb_p1br, 8));
E 8
	printf("Registers:\n     ");
	for (i = 0; i < 8; i++)
		printf("        %d", i);
	printf("\ndreg:");
	for (i = 0; i < 8; i++)
D 35
		printf(" %s", hexstr(rp[i], 8));
E 35
I 35
		printf(" %s", hexstr(fp->f_regs[i], 8));
E 35
	printf("\nareg:");
	for (i = 0; i < 8; i++)
D 35
		printf(" %s", hexstr(rp[i+8], 8));
E 35
I 35
		printf(" %s", hexstr(fp->f_regs[i+8], 8));
E 35
	if (sbytes > 0) {
D 35
		if (rp[PS] & PSL_S) {
E 35
I 35
		if (fp->f_sr & PSL_S) {
E 35
			printf("\n\nKernel stack (%s):",
D 35
			       hexstr((int)(((int *)&rp)-1), 8));
			dumpmem(((int *)&rp)-1, sbytes, 0);
E 35
I 35
			       hexstr((int)(((int *)&fp)-1), 8));
			dumpmem(((int *)&fp)-1, sbytes, 0);
E 35
		} else {
D 35
			printf("\n\nUser stack (%s):", hexstr(rp[SP], 8));
			dumpmem((int *)rp[SP], sbytes, 1);
E 35
I 35
			printf("\n\nUser stack (%s):", hexstr(fp->f_regs[SP], 8));
			dumpmem((int *)fp->f_regs[SP], sbytes, 1);
E 35
		}
	}
	doingdump = 0;
	splx(s);
}

D 12
#define KSADDR	((int *)&(((char *)&u)[(UPAGES-1)*NBPG]))
E 12
I 12
extern char kstack[];
#define KSADDR	((int *)&(kstack[(UPAGES-1)*NBPG]))
E 12

dumpmem(ptr, sz, ustack)
D 12
 register int *ptr;
 int sz;
E 12
I 12
	register int *ptr;
D 43
	int sz;
E 43
I 43
	int sz, ustack;
E 43
E 12
{
	register int i, val;
	extern char *hexstr();

	for (i = 0; i < sz; i++) {
		if ((i & 7) == 0)
			printf("\n%s: ", hexstr((int)ptr, 6));
		else
			printf(" ");
		if (ustack == 1) {
			if ((val = fuword(ptr++)) == -1)
				break;
		} else {
D 12
			if (ustack == 0 && (ptr < KSADDR || ptr > KSADDR+(NBPG/4-1)))
E 12
I 12
			if (ustack == 0 &&
			    (ptr < KSADDR || ptr > KSADDR+(NBPG/4-1)))
E 12
				break;
			val = *ptr++;
		}
		printf("%s", hexstr(val, 8));
	}
	printf("\n");
}

char *
hexstr(val, len)
D 3
 register int val;
E 3
I 3
	register int val;
I 43
	int len;
E 43
E 3
{
	static char nbuf[9];
	register int x, i;

	if (len > 8)
		return("");
	nbuf[len] = '\0';
	for (i = len-1; i >= 0; --i) {
		x = val & 0xF;
		if (x > 9)
			nbuf[i] = x - 10 + 'A';
		else
			nbuf[i] = x + '0';
		val >>= 4;
	}
	return(nbuf);
}
I 35

#ifdef DEBUG
char oflowmsg[] = "k-stack overflow";
char uflowmsg[] = "k-stack underflow";

badkstack(oflow, fr)
	int oflow;
	struct frame fr;
{
	extern char kstackatbase[];

	printf("%s: sp should be %x\n", 
	       oflow ? oflowmsg : uflowmsg,
	       kstackatbase - (exframesize[fr.f_format] + 8));
	regdump(&fr, 0);
	panic(oflow ? oflowmsg : uflowmsg);
}
D 50
#endif
E 50
I 50

/*
 * print a primitive backtrace for the requested process.
 */
D 52
#define MAXARGS 4

E 52
backtrace(p)
	struct proc *p;
{
	long fix, arg, pc, *lfp;
	caddr_t fp;
	char *fmt;
	int i;

	if (p != curproc) {
		pc = *((long *)(p->p_addr->u_pcb.pcb_regs[11] + fix));
		fp = (caddr_t)p->p_addr->u_pcb.pcb_regs[10];
		fix = ((caddr_t)p->p_addr - kstack);
	} else {
		/*
		 * Have to grab current frame pointer; start with function
		 * that called backtrace.
		 */
		asm("movl a6, %0" : "=r" (fp));
		lfp = (long *)fp;
		pc = lfp[1];
		fp = (caddr_t)lfp[0];
		fix = 0;
	}

	printf("Process %s\n", p->p_comm);
	while (fp > kstack) {
		fp += fix;
D 52
		printf("Function: 0x%x(", pc);
E 52
I 52
		if (kernacc(fp, 6 * sizeof(*lfp), B_READ) == 0)
			return;
E 52
		lfp = (long *)fp;
D 52
		fmt = ", ";
		for (i = 0; i < MAXARGS; i++) {
			arg = lfp[i + 2];
			if (i == MAXARGS - 1)
				fmt = ")\n";
			printf("0x%x%s", arg, fmt);
		}
E 52
I 52
		printf("Function: 0x%x(0x%x, 0x%x, 0x%x, 0x%x)\n",
		    pc, lfp[2], lfp[3], lfp[4], lfp[5]);
E 52
		pc = lfp[1];
		fp = (caddr_t)lfp[0];
	}
}
#endif /* DEBUG */
E 50
E 35
E 1
