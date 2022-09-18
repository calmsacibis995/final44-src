h15514
s 00005/00000/01081
d D 8.3 95/05/09 12:08:10 mckusick 32 31
c put in request to unmount all filesystems when rebooting
e
s 00001/00001/01080
d D 8.2 94/01/12 14:29:54 hibler 31 30
c entries_pageable set TRUE for buffer map (set vm_map.c change).
e
s 00002/00002/01079
d D 8.1 93/06/11 15:34:58 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00028/01079
d D 7.19 93/06/10 22:04:18 cgd 29 28
c fix header which i botched
e
s 00029/00003/01078
d D 7.18 93/06/10 21:55:57 cgd 28 27
c update with newer changed from NetBSD
e
s 00004/00000/01077
d D 7.17 93/05/24 15:06:47 mckusick 27 26
c need header files for sysctl
e
s 00027/00000/01050
d D 7.16 93/05/21 18:39:41 mckusick 26 25
c add support for CTL_MACHDEP
e
s 00027/00026/01023
d D 7.15 92/10/11 10:11:01 bostic 25 24
c make kernel includes standard
e
s 00004/00003/01045
d D 7.14 92/07/10 18:00:08 torek 24 23
c ANSIfy syscall arguments
e
s 00015/00024/01033
d D 7.13 92/05/11 16:50:08 bostic 23 22
c fix NPX device handling; memory sizing update; bad argument to grow
c from Pace Willison
e
s 00012/00007/01045
d D 7.12 92/04/20 23:51:11 mckusick 22 21
c add functionality for sigaltstack
e
s 00001/00000/01051
d D 7.11 92/04/14 14:41:54 mckusick 21 20
c null terminate the callout list (from torek)
e
s 00004/00004/01047
d D 7.10 92/03/13 17:07:28 sklower 20 19
c p_regs => p_md.md_regs (checked in for sklower by torek)
e
s 00001/00001/01050
d D 7.9 92/02/19 18:30:01 torek 19 18
c eliminate function pmap_kernel
e
s 00002/00029/01049
d D 7.8 92/02/05 10:51:49 bostic 18 17
c put on a reasonable header
e
s 00003/00001/01075
d D 7.7 92/02/05 10:51:13 william 17 16
c checking in for Bill by TK; don't pause for keystroke on reboot
e
s 00044/00020/01032
d D 7.6 91/11/13 17:45:38 william 16 15
c changes to fix new vm on i386
e
s 00001/00001/01051
d D 7.5 91/07/25 22:44:12 mckusick 15 14
c vm_page_free_count moves to vm_stat.free_count
e
s 00000/00001/01052
d D 7.4 91/06/03 20:38:11 mckusick 14 13
c file table is no longer statically allocated
e
s 00017/00052/01036
d D 7.3 91/05/13 01:11:16 william 13 12
c last whacks, numerious bugs and cleanups, sizing disabled due to
c bug I don't care to chase now, other nicer code withdrawn due to bugs
e
s 00007/00004/01081
d D 7.2 91/05/10 14:24:37 bostic 12 11
c cleanups
e
s 00011/00090/01074
d D 7.1 91/05/09 21:44:54 william 11 10
c changes prior to net2 release
e
s 00014/00016/01150
d D 5.9 91/05/09 18:58:28 william 10 9
c interm version
e
s 00267/00224/00899
d D 5.8 91/05/09 18:57:55 william 9 8
c add in mach vm system
e
s 00093/00089/01030
d D 5.7 91/01/19 12:44:18 william 8 7
c reno changes and kernel reorg
e
s 00000/00000/01119
d D 5.6 91/01/15 12:21:59 bill 7 6
c reno changes
e
s 00005/00002/01114
d D 5.5 90/11/25 16:08:07 bill 6 5
c last changes before merger with reno version. cross fingers.
e
s 00034/00116/01082
d D 5.4 90/11/18 11:30:11 bill 5 4
c fix autoconf, move code to isa.c, remove debugging, drop redundant tlbflushes, macros for tlb et al
e
s 00095/00037/01103
d D 5.3 90/11/14 13:27:19 bill 4 3
c "small" machines, hole mgmt, errors, config crap
e
s 00124/00080/01016
d D 5.2 90/06/23 19:28:38 donahn 3 2
c improvements
e
s 00611/00204/00485
d D 5.1 90/04/24 18:56:36 william 2 1
c 1st Berkeley Release
e
s 00689/00000/00000
d D 1.1 90/03/12 15:48:05 bill 1 0
c date and time created 90/03/12 15:48:05 by bill
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1982,1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
E 4
I 4
D 30
 * Copyright (c) 1982, 1987, 1990 The Regents of the University of California.
E 4
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1982, 1987, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
E 2
 *
D 2
 *	@(#)machdep.c	1.16.1.1 (Berkeley) 11/24/87
E 2
I 2
 * This code is derived from software contributed to Berkeley by
D 4
 * William Jolitz and the University of Utah.
E 4
I 4
 * William Jolitz.
E 4
 *
D 9
 * %sccs.include.386.c%
E 9
I 9
D 16
 * %sccs.include.redist.c%
E 16
I 16
D 18
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
E 18
I 18
D 28
 * %sccs.include.redist.c%
E 28
I 28
D 29
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
E 29
I 29
 * %sccs.include.redist.c%
E 29
E 28
E 18
E 16
E 9
 *
D 16
 *	%W% (Berkeley) %G%
E 16
I 16
D 18
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
 *	@(#)machdep.c	7.4 (Berkeley) 6/3/91
E 18
I 18
D 28
 *	%W% (Berkeley) %G%
E 28
I 28
D 29
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
 *	@(#)machdep.c	7.17 (Berkeley) 5/24/93
E 29
I 29
 *	%W% (Berkeley) %G%
E 29
E 28
E 18
E 16
E 2
 */
D 18

E 18
I 9

E 9
I 3
D 4
/*
 * Copyright (c) 1982,1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)machdep.c	1.16.1.1 (Berkeley) 11/24/87
 */
E 3
I 2

E 4
E 2
D 25
#include "param.h"
#include "systm.h"
D 8
#include "dir.h"
E 8
D 9
#include "user.h"
E 9
I 9
#include "signalvar.h"
E 9
#include "kernel.h"
I 6
D 8
#include "malloc.h"
E 8
E 6
#include "map.h"
D 9
#include "vm.h"
E 9
#include "proc.h"
I 9
#include "user.h"
E 9
#include "buf.h"
#include "reboot.h"
#include "conf.h"
D 8
#include "inode.h"
E 8
#include "file.h"
D 9
#include "text.h"
E 9
#include "clist.h"
#include "callout.h"
D 9
#include "cmap.h"
E 9
I 9
#include "malloc.h"
E 9
#include "mbuf.h"
#include "msgbuf.h"
D 8
#include "quota.h"
I 2
#include "../net/netisr.h"
E 8
I 8
#include "net/netisr.h"
E 25
I 25
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signalvar.h>
#include <sys/kernel.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/reboot.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/clist.h>
#include <sys/callout.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
I 27
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/sysctl.h>
E 27
E 25
I 13

E 13
E 8
E 2
D 11

D 2
#include "../tahoe/cpu.h"
#include "../tahoe/reg.h"
#include "../tahoe/pte.h"
#include "../tahoe/psl.h"
E 2
I 2
D 8
#include "../i386/frame.h"
#include "../i386/reg.h"
#include "../i386/segments.h"
#include "../i386/pte.h"
#include "../i386/psl.h"
I 4
#include "../i386/isa/rtc.h"
E 8
I 8
D 9
#include "machine/frame.h"
E 9
I 9
#define	MAXMEM	64*1024*CLSIZE	/* XXX - from cmap.h */
E 11
D 25
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 25
I 25
#include <net/netisr.h>
E 25
D 11
/*#include "vm/vm_param.h"
#include "vm/vm_map.h"
#include "vm/vm_object.h"
#include "vm/pmap.h"*/
E 11

I 25
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>

E 25
vm_map_t buffer_map;
extern vm_offset_t avail_end;

D 25
#include "machine/cpu.h"
E 9
#include "machine/reg.h"
D 9
#include "machine/segments.h"
#include "machine/pte.h"
E 9
#include "machine/psl.h"
#include "machine/specialreg.h"
#include "i386/isa/rtc.h"
E 25
I 25
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/psl.h>
#include <machine/specialreg.h>
#include <i386/isa/rtc.h>
I 27
#include <i386/i386/cons.h>
E 27
E 25
E 8
E 4
E 2

D 2
#include "../tahoe/mem.h"
#include "../tahoe/mtpr.h"
#include "../tahoe/cp.h"
#include "../tahoevba/vbavar.h"

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
D 2
#include "yc.h"
#if NCY > 0
#include "../tahoevba/cyreg.h"
#endif
E 2
I 2
D 8
int kernmem;
E 8
I 8
int	msgbufmapped;		/* set when safe to use msgbuf */
E 8
E 2

I 13
/*
 * Machine-dependent startup code
 */
E 13
D 12
/*
 * Machine-dependent startup code
 */
E 12
I 2
D 5
extern char Sysbase;
caddr_t sbase = { &Sysbase };
E 5
I 5
D 8
/*extern char Sysbase;
caddr_t sbase = { &Sysbase };*/
E 8
D 9
extern	char	Sysbase[];
E 9
I 9
D 11
#define	SYSTEM	0xfe000000
E 9
E 5
I 4
/* extern struct pte	EMCmap[];
extern char		EMCbase[]; */
E 11
int boothowto = 0, Maxmem = 0;
I 13
long dumplo;
int physmem, maxmem;
E 13
extern int bootdev;
D 11
#ifdef SMALL
extern int forcemaxmem;
#endif
E 11
I 11
D 13
int forcemaxmem;
E 13
I 13
#ifdef SMALL
extern int forcemaxmem;
#endif
E 13
E 11
int biosmem;
E 4

I 4
extern cyloffset;

I 12
D 13
/*
 * cpu_startup: allocate memory for variable-sized tables,
 * initialize cpu, and do autoconfiguration.
 */
E 12
D 9
caddr_t bypasshole(b,t) caddr_t b,t; {

D 5
	if (b <= sbase + 0xa0000 && t > sbase + 0xa0000)
		return(sbase + 0x100000);
E 5
I 5
	if (b <= Sysbase + 0xa0000 && t > Sysbase + 0xa0000)
		return(Sysbase + 0x100000);
E 5
	return(b);
}

E 9
E 4
E 2
D 11
startup(firstaddr)
	int firstaddr;
E 11
I 11
cpu_startup()
E 13
I 13
cpu_startup(firstaddr)
	int firstaddr;
E 13
E 11
{
	register int unixsize;
	register unsigned i;
	register struct pte *pte;
	int mapaddr, j;
	register caddr_t v;
D 11
	int maxbufs, base, residual;
E 11
I 11
D 13
	int firstaddr, maxbufs, base, residual;
E 13
I 13
	int maxbufs, base, residual;
E 13
E 11
I 2
D 9
	extern struct map *useriomap;
E 9
I 9
	extern long Usrptsize;
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
D 11
#ifdef DEBUG
	extern int pmapdebug;
	int opmapdebug = pmapdebug;
#endif
E 11
E 9
D 4
int cmaxmem;
E 4
E 2

D 11
	/*
I 2
	 * Initialize the console before we print anything out.
	 */
	/*cninit();*/
E 11
D 13

E 13
	/*
I 4
D 11
	 * Bounds check memory size information against bios values
	 * use the lesser of the two
	 */
	biosmem = rtcin(RTC_BASELO)+ (rtcin(RTC_BASEHI)<<8);
printf("Maxmem %x howto %x bootdev %x cyloff %x firstaddr %x bios %d %d\n",
		Maxmem, boothowto, bootdev, cyloffset, firstaddr,
biosmem, 
rtcin(RTC_EXTLO) + (rtcin(RTC_EXTHI)<<8)
);
D 9
	maxmem = Maxmem-1;
E 9
I 9
	/*maxmem = Maxmem-1;
E 9

I 8
D 9
/*
E 9
E 8
D 6
#ifdef notdef
E 6
	if(biosmem != 640)
		panic("does not have 640K of base memory");

	biosmem = 1024;
	biosmem += rtcin(RTC_EXTLO) + (rtcin(RTC_EXTHI)<<8);
	biosmem = biosmem/4 - 1 ;
	if (biosmem < maxmem) maxmem=biosmem;
I 8
D 9
*/
E 9
E 8

#ifdef SMALL
if(forcemaxmem && maxmem > forcemaxmem)
	maxmem = forcemaxmem-1;
D 9
#endif
D 6
#endif
E 6
/*
maxmem = 0xA00;*/
E 9
I 9
#endif*/
E 9

	/*
E 11
E 4
E 2
	 * Initialize error message buffer (at end of core).
	 */
D 2
	maxmem -= btoc(sizeof (struct msgbuf));
E 2
I 2
D 9
/* Problem to resolve. AT's have memory that is not contigous, as
I/O address space for video adapters and network cards fall into
a range of 0xa0000 - 0x100000 . Note that the cmap really expects
contigous memory. For the moment, use the bottom of memory for
kernel and run-time configured storage (e.g. valloc), using memory
above 0x100000 for the cmap, and wasting the stuff left over after
valloc-end up to 0xa0000 (640K). Will have to fix this before beta,
and will have to somehow move this out into per bus adapter directory
D 3
(e.g. configurable). For now, punt */
E 3
I 3
(e.g. configurable). For now, punt
E 9

D 9
How about starting cmap normally following valloc space, and then
write a routine than allocs only phys pages in the 0xa0000-0x100000
hole?

I 5
Temporary fix for beta, if we only have 640K, then cmap follows valloc
up to 640K.
E 5
*/
E 3
D 4
	kernmem = 640/4;
	kernmem -= btoc(sizeof (struct msgbuf));
E 4
I 4
	maxmem -= btoc(sizeof (struct msgbuf));
E 4
D 3
/*pg("kern %x, msgbufmap", kernmem);*/
E 3
E 2
	pte = msgbufmap;
E 9
I 9
	/* avail_end was pre-decremented in pmap_bootstrap to compensate */
E 9
	for (i = 0; i < btoc(sizeof (struct msgbuf)); i++)
D 2
		*(int *)pte++ = PG_V | PG_KW | (maxmem + i);
	mtpr(TBIA, 1);
E 2
I 2
D 4
		*(int *)pte++ = PG_V | PG_KW | ctob(kernmem + i);
D 3
/*XXX*/	maxmem = freemem = physmem = 1024/4+kernmem;
	cmaxmem = 1024/4;
E 3
I 3
/*XXX*/	maxmem = freemem = physmem = 2048/4+kernmem;
	cmaxmem = 2048/4;
E 4
I 4
D 9
		*(int *)pte++ = PG_V | PG_KW | ctob(maxmem + i);
E 4

E 9
I 9
D 19
		pmap_enter(pmap_kernel(), msgbufp, avail_end + i * NBPG,
E 19
I 19
		pmap_enter(kernel_pmap, msgbufp, avail_end + i * NBPG,
E 19
			   VM_PROT_ALL, TRUE);
	msgbufmapped = 1;
E 9
D 4
/* unmap particular region being written into, so we can find offending ptr */
/*{ extern char b_uregion[], e_uregion[];
#define	ptidx(s)	((s - sbase)/NBPG)
	pte = Sysmap + ptidx(b_uregion) + 1 ;
	for (i = ptidx(b_uregion) + 1 ; i < ptidx (e_uregion) ; i++)
		*(int *)pte++ = 0 ;
}*/
E 4
I 4
D 11
#ifdef notdef
	/* XXX EMC */
	pte = EMCmap;
	*(int *)pte = PG_V | PG_UW | 0xc0000000;
	printf("EMC at %x\n", EMCbase);
#endif
E 11

D 9
	freemem = physmem = maxmem;

E 4
E 3
	load_cr3(_cr3());

E 9
E 2
#ifdef KDB
	kdb_init();			/* startup kernel debugger */
#endif
	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	printf(version);
	printf("real mem  = %d\n", ctob(physmem));

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
D 2
	v = (caddr_t)(0xc0000000 | (firstaddr * NBPG));
E 2
I 2
D 5
	v = (caddr_t)(sbase + (firstaddr * NBPG));
E 5
I 5
D 9
	v = (caddr_t)(Sysbase + (firstaddr * NBPG));
E 5
	/*v = sbase + (firstaddr * NBPG);*/
E 9
I 9

	/*
	 * Make two passes.  The first pass calculates how much memory is
	 * needed and allocates it.  The second pass assigns virtual
	 * addresses to the various data structures.
	 */
	firstaddr = 0;
again:
	v = (caddr_t)firstaddr;

E 9
D 3
/*pg("vallocs %x", v);*/
E 3
E 2
#define	valloc(name, type, num) \
I 4
D 9
		v = bypasshole (v, v + (int) ((name)+(num))) ; \
E 9
E 4
	    (name) = (type *)v; v = (caddr_t)((name)+(num))
#define	valloclim(name, type, num, lim) \
I 4
D 9
		v = bypasshole (v, v + (int) ((name)+(num))) ; \
E 9
E 4
	    (name) = (type *)v; v = (caddr_t)((lim) = ((name)+(num)))
D 2
#if NCY > 0
	/*
	 * Allocate raw buffers for tapemaster controllers
	 * first, as they need buffers in the first megabyte.
	 */
	valloc(cybuf, char, NCY * CYMAXIO);
#endif
E 2
D 8
	valloclim(inode, struct inode, ninode, inodeNINODE);
E 8
D 14
	valloclim(file, struct file, nfile, fileNFILE);
E 14
D 9
	valloclim(proc, struct proc, nproc, procNPROC);
	valloclim(text, struct text, ntext, textNTEXT);
E 9
	valloc(cfree, struct cblock, nclist);
	valloc(callout, struct callout, ncallout);
D 9
	valloc(swapmap, struct map, nswapmap = nproc * 2);
	valloc(argmap, struct map, ARGMAPSIZE);
	valloc(kernelmap, struct map, nproc);
I 2
D 8
	valloc(useriomap, struct map, nproc);
E 8
E 2
	valloc(mbmap, struct map, nmbclusters/4);
D 8
	valloc(namecache, struct namecache, nchsize);
I 6

E 8
	valloc(kmemmap, struct map, ekmempt - kmempt);
	valloc(kmemusage, struct kmemusage, ekmempt - kmempt);
E 6
D 8
#ifdef QUOTA
	valloclim(quota, struct quota, nquota, quotaNQUOTA);
	valloclim(dquot, struct dquot, ndquot, dquotNDQUOT);
E 8
I 8
	valloc(useriomap, struct map, nproc);
E 9
I 9
	valloc(swapmap, struct map, nswapmap = maxproc * 2);
E 9
#ifdef SYSVSHM
	valloc(shmsegs, struct shmid_ds, shminfo.shmmni);
E 8
#endif
D 8
	
E 8
	/*
	 * Determine how many buffers to allocate.
	 * Use 10% of memory for the first 2 Meg, 5% of the remaining
	 * memory. Insure a minimum of 16 buffers.
	 * We allocate 1/2 as many swap buffer headers as file i/o buffers.
	 */
	if (bufpages == 0)
		if (physmem < (2 * 1024 * 1024))
			bufpages = physmem / 10 / CLSIZE;
		else
			bufpages = ((2 * 1024 * 1024 + physmem) / 20) / CLSIZE;
	if (nbuf == 0) {
		nbuf = bufpages / 2;
		if (nbuf < 16)
			nbuf = 16;
	}
	if (nswbuf == 0) {
		nswbuf = (nbuf / 2) &~ 1;	/* force even */
		if (nswbuf > 256)
			nswbuf = 256;		/* sanity */
	}
	valloc(swbuf, struct buf, nswbuf);
I 9
	valloc(buf, struct buf, nbuf);
E 9

	/*
D 9
	 * Now the amount of virtual memory remaining for buffers
	 * can be calculated, estimating needs for the cmap.
E 9
I 9
	 * End of first pass, size has been calculated so allocate memory
E 9
	 */
D 2
	ncmap = (maxmem*NBPG - ((int)v &~ 0xc0000000)) /
E 2
I 2
D 4
	ncmap = (maxmem*NBPG /* - ((int)(v - sbase))*/) /
E 4
I 4
D 5
	ncmap = (maxmem*NBPG  - ((int)(v - sbase))) /
E 5
I 5
D 9
	ncmap = (maxmem*NBPG  - ((int)(v - Sysbase))) /
E 5
E 4
E 2
		(CLBYTES + sizeof(struct cmap)) + 2;
	maxbufs = ((SYSPTSIZE * NBPG) -
D 2
	    ((int)(v + ncmap * sizeof(struct cmap)) - 0xc0000000)) /
E 2
I 2
D 5
		((int)(v - sbase + ncmap * sizeof(struct cmap)))) /
E 5
I 5
		((int)(v - Sysbase + ncmap * sizeof(struct cmap)))) /
E 5
E 2
		(MAXBSIZE + sizeof(struct buf));
	if (maxbufs < 16)
		panic("sys pt too small");
	if (nbuf > maxbufs) {
		printf("SYSPTSIZE limits number of buffers to %d\n", maxbufs);
		nbuf = maxbufs;
E 9
I 9
	if (firstaddr == 0) {
		size = (vm_size_t)(v - firstaddr);
		firstaddr = (int)kmem_alloc(kernel_map, round_page(size));
		if (firstaddr == 0)
			panic("startup: no room for tables");
		goto again;
E 9
	}
D 9
	if (bufpages > nbuf * (MAXBSIZE / CLBYTES))
		bufpages = nbuf * (MAXBSIZE / CLBYTES);
	valloc(buf, struct buf, nbuf);

E 9
	/*
D 9
	 * Allocate space for core map.
D 2
	 * Allow space for all of phsical memory minus the amount 
E 2
I 2
	 * Allow space for all of physical memory minus the amount 
E 2
	 * dedicated to the system. The amount of physical memory
	 * dedicated to the system is the total virtual memory of
	 * the system thus far, plus core map, buffer pages,
	 * and buffer headers not yet allocated.
	 * Add 2: 1 because the 0th entry is unused, 1 for rounding.
E 9
I 9
	 * End of second pass, addresses have been assigned
E 9
	 */
D 2
	ncmap = (maxmem*NBPG - ((int)(v + bufpages*CLBYTES) &~ 0xc0000000)) /
E 2
I 2
D 9
	/*ncmap = (maxmem*NBPG - ((int)((v - sbase) + bufpages*CLBYTES))) /*/
D 4
	ncmap = (maxmem*NBPG - ((int)(/*(v - sbase)*/ + bufpages*CLBYTES))) /
E 4
I 4
D 5
	ncmap = (maxmem*NBPG - ((int)((v - sbase) + bufpages*CLBYTES))) /
E 5
I 5
	ncmap = (maxmem*NBPG - ((int)((v - Sysbase) + bufpages*CLBYTES))) /
E 5
E 4
E 2
		(CLBYTES + sizeof(struct cmap)) + 2;
	valloclim(cmap, struct cmap, ncmap, ecmap);

E 9
I 9
	if ((vm_size_t)(v - firstaddr) != size)
		panic("startup: table size inconsistency");
E 9
	/*
D 9
	 * Clear space allocated thus far, and make r/w entries
	 * for the space in the kernel map.
	 */
D 2
	unixsize = btoc((int)v &~ 0xc0000000);
E 2
I 2
D 4
	/*unixsize = btoc((int)(v - sbase));*/
E 4
D 5
	unixsize = btoc((int)(v - sbase));
E 5
I 5
	unixsize = btoc((int)(v - Sysbase));
E 5
E 2
	while (firstaddr < unixsize) {
D 2
		*(int *)(&Sysmap[firstaddr]) = PG_V | PG_KW | firstaddr;
E 2
I 2
		*(int *)(&Sysmap[firstaddr]) = PG_V | PG_KW | ctob(firstaddr);
E 2
		clearseg((unsigned)firstaddr);
		firstaddr++;
	}

	/*
E 9
	 * Now allocate buffers proper.  They are different than the above
	 * in that they usually occupy more virtual memory than physical.
	 */
I 4
D 9
	v = bypasshole (v, (caddr_t) ((int)(v + PGOFSET) &~ PGOFSET +
		MAXBSIZE*nbuf));
E 4
	v = (caddr_t) ((int)(v + PGOFSET) &~ PGOFSET);
	valloc(buffers, char, MAXBSIZE * nbuf);
E 9
I 9
	size = MAXBSIZE * nbuf;
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t)&buffers,
D 31
				   &maxaddr, size, FALSE);
E 31
I 31
				   &maxaddr, size, TRUE);
E 31
	minaddr = (vm_offset_t)buffers;
	if (vm_map_find(buffer_map, vm_object_allocate(size), (vm_offset_t)0,
			&minaddr, size, FALSE) != KERN_SUCCESS)
		panic("startup: cannot allocate buffers");
E 9
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
D 4
	mapaddr = firstaddr;
E 4
I 4
D 5
	mapaddr = firstaddr = btoc((unsigned) buffers - (unsigned)sbase);
E 5
I 5
D 9
	mapaddr = firstaddr = btoc((unsigned) buffers - (unsigned)Sysbase);
E 5
E 4
	for (i = 0; i < residual; i++) {
		for (j = 0; j < (base + 1) * CLSIZE; j++) {
D 2
			*(int *)(&Sysmap[mapaddr+j]) = PG_V | PG_KW | firstaddr;
E 2
I 2
			*(int *)(&Sysmap[mapaddr+j]) = PG_V | PG_KW | ctob(firstaddr);
E 2
			clearseg((unsigned)firstaddr);
			firstaddr++;
		}
		mapaddr += MAXBSIZE / NBPG;
E 9
I 9
	for (i = 0; i < nbuf; i++) {
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
		vm_map_pageable(buffer_map, curbuf, curbuf+curbufsize, FALSE);
		vm_map_simplify(buffer_map, curbuf);
E 9
	}
D 9
	for (i = residual; i < nbuf; i++) {
		for (j = 0; j < base * CLSIZE; j++) {
D 2
			*(int *)(&Sysmap[mapaddr+j]) = PG_V | PG_KW | firstaddr;
E 2
I 2
			*(int *)(&Sysmap[mapaddr+j]) = PG_V | PG_KW | ctob(firstaddr);
E 2
			clearseg((unsigned)firstaddr);
			firstaddr++;
		}
		mapaddr += MAXBSIZE / NBPG;
	}
E 9
I 9
	/*
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
E 9

D 2
	unixsize = btoc((int)v &~ 0xc0000000);
E 2
I 2
D 3
	/*unixsize = btoc((int)(v - sbase));*/
E 3
D 5
	unixsize = btoc((int)(v - sbase));
E 5
I 5
D 9
	unixsize = btoc((int)(v - Sysbase));
E 5
E 2
	if (firstaddr >= physmem - 8*UPAGES)
		panic("no memory");
D 2
	mtpr(TBIA, 1);			/* After we just cleared it all! */
E 2
I 2
D 4
	if (firstaddr >= (640/4))
		panic("allocated AT hole!");
E 4
E 2

E 9
	/*
I 9
	 * Finally, allocate mbuf pool.  Since mclrefcnt is an off-size
	 * we use the more space efficient malloc in place of kmem_alloc.
	 */
	mclrefcnt = (char *)malloc(NMBCLUSTERS+CLBYTES/MCLBYTES,
				   M_MBUF, M_NOWAIT);
	bzero(mclrefcnt, NMBCLUSTERS+CLBYTES/MCLBYTES);
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t)&mbutl, &maxaddr,
			       VM_MBUF_SIZE, FALSE);
	/*
E 9
	 * Initialize callouts
	 */
	callfree = callout;
	for (i = 1; i < ncallout; i++)
		callout[i-1].c_next = &callout[i];
I 21
	callout[i-1].c_next = NULL;
E 21

D 9
	/*
	 * Initialize memory allocator and swap
	 * and user page table maps.
	 *
	 * THE USER PAGE TABLE MAP IS CALLED ``kernelmap''
	 * WHICH IS A VERY UNDESCRIPTIVE AND INCONSISTENT NAME.
	 */
E 9
I 9
D 11
#ifdef DEBUG
	pmapdebug = opmapdebug;
#endif
E 11
D 15
	printf("avail mem = %d\n", ptoa(vm_page_free_count));
E 15
I 15
D 16
	printf("avail mem = %d\n", ptoa(vm_stat.free_count));
E 16
I 16
	/*printf("avail mem = %d\n", ptoa(vm_page_free_count));*/
E 16
E 15
	printf("using %d buffers containing %d bytes of memory\n",
		nbuf, bufpages * CLBYTES);
E 9
I 2
D 3
firstaddr = 0x100; maxmem = 0x200;		/*XXX*/
E 3
I 3
D 4
firstaddr = 0x100; maxmem = 0x300;		/*XXX*/
E 4
I 4

I 9
D 13
#ifdef somewhere
E 13
E 9
	/*
D 13
	 *  cmap must not allocate the hole, so toss memory
	 */
	if(firstaddr < 640/4 && maxmem > 1024/4){
		printf("[not using %dK due to hole]\n", 4*(640/4 - firstaddr));
		firstaddr = 0x100;
	}
	if(maxmem < 2048/4-10)
	  printf("WARNING: NOT ENOUGH RAM MEMORY - RUNNING IN DEGRADED MODE\n");

E 4
E 3
E 2
D 9
	meminit(firstaddr, maxmem);
	maxmem = freemem;
	printf("avail mem = %d\n", ctob(maxmem));
	printf("using %d buffers containing %d bytes of memory\n",
		nbuf, bufpages * CLBYTES);
	rminit(kernelmap, (long)USRPTSIZE, (long)1,
	    "usrpt", nproc);
I 2
/*
 * PTEs for mapping user space into kernel for phyio operations.
 * One page is enough to handle 4Mb of simultaneous raw IO operations.
 */
D 3
#define USRIOSIZE	(30)
E 3
I 3
D 4
#undef USRIOSIZE
#define USRIOSIZE 30
E 4
E 3
	rminit(useriomap, (long)USRIOSIZE, (long)1, "usrio", nproc);
E 2
	rminit(mbmap, (long)(nmbclusters * CLSIZE), (long)CLSIZE,
	    "mbclusters", nmbclusters/4);
I 6
	kmeminit();	/* now safe to do malloc/free */
E 6
D 2
	intenable = 1;		/* Enable interrupts from now on */
E 2
I 2
	/*intenable = 1;		/* Enable interrupts from now on */
E 2

E 9
I 9
#endif
E 9
	/*
E 13
	 * Set up CPU-specific registers, cache, etc.
	 */
	initcpu();

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
D 9
	bhinit();
	binit();
E 9
I 9
	bufinit();
E 9

	/*
	 * Configure the system.
	 */
	configure();
}

#ifdef PGINPROF
/*
 * Return the difference (in microseconds)
 * between the  current time and a previous
 * time as represented  by the arguments.
 * If there is a pending clock interrupt
 * which has not been serviced due to high
 * ipl, return error code.
 */
/*ARGSUSED*/
vmtime(otime, olbolt, oicr)
	register int otime, olbolt, oicr;
{

	return (((time.tv_sec-otime)*60 + lbolt-olbolt)*16667);
}
#endif

I 2
struct sigframe {
	int	sf_signum;
	int	sf_code;
	struct	sigcontext *sf_scp;
D 8
	int	(*sf_handler)();
E 8
I 8
	sig_t	sf_handler;
E 8
	int	sf_eax;	
	int	sf_edx;	
	int	sf_ecx;	
D 8
	struct	save87	sf_fsave;	/* fpu coproc */
E 8
I 8
	struct	sigcontext sf_sc;
E 8
} ;

I 10
extern int kstack[];

E 10
E 2
/*
 * Send an interrupt to process.
 *
 * Stack is set up to allow sigcode stored
 * in u. to call routine, followed by kcall
 * to sigreturn routine below.  After sigreturn
 * resets the signal mask, the stack, and the
 * frame pointer, it returns to the user
 * specified pc, psl.
 */
D 2
sendsig(p, sig, mask)
E 2
I 2
D 8
sendsig(p, sig, mask, frmtrp)
E 2
	int (*p)(), sig, mask;
E 8
I 8
D 9
sendsig(catcher, sig, mask, code, frm)
E 9
I 9
void
sendsig(catcher, sig, mask, code)
E 9
	sig_t catcher;
	int sig, mask;
	unsigned code;
E 8
{
D 8
	register struct sigcontext *scp;
E 8
I 8
D 9
	register struct proc *p = u.u_procp;
E 9
I 9
	register struct proc *p = curproc;
E 9
E 8
	register int *regs;
D 2
	register struct sigframe {
		int	sf_signum;
		int	sf_code;
		struct	sigcontext *sf_scp;
		int	(*sf_handler)();
		int	sf_regs[6];		/* r0-r5 */
		struct	sigcontext *sf_scpcopy;
	} *fp;
E 2
I 2
	register struct sigframe *fp;
I 9
D 22
	struct sigacts *ps = p->p_sigacts;
E 22
I 22
	struct sigacts *psp = p->p_sigacts;
E 22
D 10
	int oonstack;
E 10
I 10
	int oonstack, frmtrap;
E 10
E 9
E 2
D 8
	int oonstack;
E 8

I 4
D 8
#include "dbg.h"
dprintf(DSIGNAL,"sendsig %d code %d to pid %d frmtrp %d to locn %x\n",
	sig, u.u_code, u.u_procp->p_pid, frmtrp, p);
E 8
E 4
D 9
	regs = u.u_ar0;
E 9
I 9
D 20
	regs = p->p_regs;
E 20
I 20
	regs = p->p_md.md_regs;
E 20
D 22
        oonstack = ps->ps_onstack;
E 22
I 22
        oonstack = psp->ps_sigstk.ss_flags & SA_ONSTACK;
E 22
I 10
	frmtrap = curpcb->pcb_flags & FM_TRAP;
E 10
E 9
D 8
	oonstack = u.u_onstack;
E 8
I 8
D 13
/*#include "dbg.h"
dprintf(DALLTRAPS|DPAGIN,"s %d %d ", sig, frm);*/
E 13
E 8
	/*
	 * Allocate and validate space for the signal handler
	 * context. Note that if the stack is in P0 space, the
	 * call to grow() is a nop, and the useracc() check
	 * will fail if the process has not already allocated
	 * the space with a `brk'.
	 */
D 9
	if (!u.u_onstack && (u.u_sigonstack & sigmask(sig))) {
E 9
I 9
D 22
        if (!ps->ps_onstack && (ps->ps_sigonstack & sigmask(sig))) {
D 13

E 9
D 8
		scp = (struct sigcontext *)u.u_sigsp - 1;
E 8
I 8
printf("onstack?");
E 13
D 9
		fp = (struct sigframe *)(u.u_sigsp - sizeof(struct sigframe));
E 8
		u.u_onstack = 1;
E 9
I 9
		fp = (struct sigframe *)(ps->ps_sigsp
				- sizeof(struct sigframe));
                ps->ps_onstack = 1;
E 22
I 22
	if ((psp->ps_flags & SAS_ALTSTACK) &&
	    (psp->ps_sigstk.ss_flags & SA_ONSTACK) == 0 &&
	    (psp->ps_sigonstack & sigmask(sig))) {
		fp = (struct sigframe *)(psp->ps_sigstk.ss_base +
		    psp->ps_sigstk.ss_size - sizeof(struct sigframe));
		psp->ps_sigstk.ss_flags |= SA_ONSTACK;
E 22
E 9
D 2
	} else
		scp = (struct sigcontext *)regs[SP] - 1;
E 2
I 2
	} else {
D 8
		if (frmtrp)
			scp = (struct sigcontext *)regs[tESP] - 1;
E 8
I 8
D 9
		if (frm)
E 9
I 9
D 10
		if (code&0x100)
E 10
I 10
		if (frmtrap)
E 10
E 9
			fp = (struct sigframe *)(regs[tESP]
				- sizeof(struct sigframe));
E 8
		else
D 8
			scp = (struct sigcontext *)regs[sESP] - 1;
E 8
I 8
			fp = (struct sigframe *)(regs[sESP]
				- sizeof(struct sigframe));
E 8
	}
E 2
D 8
	fp = (struct sigframe *)scp - 1;
	if ((int)fp <= USRSTACK - ctob(u.u_ssize)) 
		(void) grow((unsigned)fp);
	if (useracc((caddr_t)fp, sizeof (*fp) + sizeof (*scp), B_WRITE) == 0) {
E 8
I 8

D 9
	if ((unsigned)fp <= USRSTACK - ctob(u.u_ssize)) 
E 9
I 9
	if ((unsigned)fp <= USRSTACK - ctob(p->p_vmspace->vm_ssize)) 
E 9
D 23
		(void)grow((unsigned)fp);
E 23
I 23
		(void)grow(p, (unsigned)fp);
E 23

	if (useracc((caddr_t)fp, sizeof (struct sigframe), B_WRITE) == 0) {
D 9
printf("fail %x %x\n", fp, regs[frm?tESP:sESP]);
E 9
I 9
D 10
printf("fail %x %x\n", fp, regs[code&0x100?tESP:sESP]);
E 10
I 10
D 13
printf("fail %x %x\n", fp, regs[frmtrap?tESP:sESP]);
E 13
E 10
E 9
E 8
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
I 3
D 4
printf("sendsig: failed to grow stack %x\n", fp);
E 4
I 4
D 8
printf("sendsig: failed to grow stack down to %x\n", fp);
E 4
E 3
		u.u_signal[SIGILL] = SIG_DFL;
E 8
I 8
		SIGACTION(p, SIGILL) = SIG_DFL;
E 8
		sig = sigmask(SIGILL);
D 8
		u.u_procp->p_sigignore &= ~sig;
		u.u_procp->p_sigcatch &= ~sig;
		u.u_procp->p_sigmask &= ~sig;
		psignal(u.u_procp, SIGILL);
E 8
I 8
		p->p_sigignore &= ~sig;
		p->p_sigcatch &= ~sig;
		p->p_sigmask &= ~sig;
		psignal(p, SIGILL);
D 13
/*dprintf(DALLTRAPS|DPAGIN,"ill ");*/
E 13
E 8
		return;
	}
I 2

E 2
	/* 
	 * Build the argument list for the signal handler.
	 */
	fp->sf_signum = sig;
D 8
	if (sig == SIGILL || sig == SIGFPE) {
E 8
I 8
	fp->sf_code = code;
D 9
	/*if (sig == SIGILL || sig == SIGFPE) {
E 8
		fp->sf_code = u.u_code;
		u.u_code = 0;
	} else
D 8
		fp->sf_code = 0;
E 8
I 8
		fp->sf_code = 0; */
E 9
I 9
D 10

E 9
E 8
I 2
	/* indicate trap occured from system call */
D 8
	if(!frmtrp) fp->sf_code |= 0x80;
E 8
I 8
	/*if(!(code&FRMTRAP)) fp->sf_code |= 0x80;*/
E 8

E 10
E 2
D 8
	fp->sf_scp = scp;
	fp->sf_handler = p;
E 8
I 8
	fp->sf_scp = &fp->sf_sc;
	fp->sf_handler = catcher;
E 8
I 2

	/* save scratch registers */
D 8
	if(frmtrp) {
E 8
I 8
D 9
	if(frm) {
E 9
I 9
D 10
	if(code&0x100) {
E 10
I 10
	if(frmtrap) {
E 10
E 9
E 8
		fp->sf_eax = regs[tEAX];
		fp->sf_edx = regs[tEDX];
		fp->sf_ecx = regs[tECX];
	} else {
		fp->sf_eax = regs[sEAX];
		fp->sf_edx = regs[sEDX];
		fp->sf_ecx = regs[sECX];
	}
D 8
#ifdef notyet
	/* XXX FPU state? */
#endif
E 8
E 2
	/*
D 2
	 * Build the callf argument frame to be used to call sigreturn.
	 */
	fp->sf_scpcopy = scp;
	/*
E 2
	 * Build the signal context to be used by sigreturn.
	 */
D 8
	scp->sc_onstack = oonstack;
	scp->sc_mask = mask;
D 2
	scp->sc_sp = regs[SP];
	scp->sc_fp = regs[FP];
	scp->sc_pc = regs[PC];
	scp->sc_ps = regs[PS];
	regs[SP] = (int)fp;
	regs[PC] = (int)u.u_pcb.pcb_sigc;
E 2
I 2
	if(frmtrp) {
		scp->sc_sp = regs[tESP];
		scp->sc_fp = regs[tEBP];
		scp->sc_pc = regs[tEIP];
		scp->sc_ps = regs[tEFLAGS];
E 8
I 8
D 9
	fp->sf_sc.sc_onstack = u.u_onstack;
E 9
I 9
	fp->sf_sc.sc_onstack = oonstack;
E 9
	fp->sf_sc.sc_mask = mask;
D 9
	if(frm) {
E 9
I 9
D 10
	if(code&0x100) {
E 10
I 10
	if(frmtrap) {
E 10
E 9
		fp->sf_sc.sc_sp = regs[tESP];
		fp->sf_sc.sc_fp = regs[tEBP];
		fp->sf_sc.sc_pc = regs[tEIP];
		fp->sf_sc.sc_ps = regs[tEFLAGS];
E 8
		regs[tESP] = (int)fp;
D 9
		regs[tEIP] = (int)u.u_pcb.pcb_sigc;
E 9
I 9
D 10
		regs[tEIP] = (int)p->p_addr->u_pcb.pcb_sigc;
E 10
I 10
		regs[tEIP] = (int)((struct pcb *)kstack)->pcb_sigc;
E 10
E 9
I 8
D 13
/*dprintf(DALLTRAPS|DPAGIN,"E ");*/
E 13
E 8
	} else {
D 8
		scp->sc_sp = regs[sESP];
		scp->sc_fp = regs[sEBP];
		scp->sc_pc = regs[sEIP];
		scp->sc_ps = regs[sEFLAGS];
E 8
I 8
		fp->sf_sc.sc_sp = regs[sESP];
		fp->sf_sc.sc_fp = regs[sEBP];
		fp->sf_sc.sc_pc = regs[sEIP];
		fp->sf_sc.sc_ps = regs[sEFLAGS];
E 8
		regs[sESP] = (int)fp;
D 9
		regs[sEIP] = (int)u.u_pcb.pcb_sigc;
E 9
I 9
D 10
		regs[sEIP] = (int)p->p_addr->u_pcb.pcb_sigc;
E 10
I 10
		regs[sEIP] = (int)((struct pcb *)kstack)->pcb_sigc;
E 10
E 9
I 8
D 13
/*dprintf(DALLTRAPS|DPAGIN,"e "); */
E 13
E 8
	}
E 2
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
I 24
struct sigreturn_args {
	struct sigcontext *sigcntxp;
};
E 24
D 8
sigreturn()
E 8
I 8
sigreturn(p, uap, retval)
	struct proc *p;
D 24
	struct args {
		struct sigcontext *sigcntxp;
	} *uap;
E 24
I 24
	struct sigreturn_args *uap;
E 24
	int *retval;
E 8
{
D 2
	struct a {
		struct sigcontext *sigcntxp;
	};
E 2
I 2
D 8
	register struct sigframe *fp;
E 8
E 2
	register struct sigcontext *scp;
I 8
	register struct sigframe *fp;
E 8
D 9
	register int *regs = u.u_ar0;
E 9
I 9
D 20
	register int *regs = p->p_regs;
E 20
I 20
	register int *regs = p->p_md.md_regs;
E 20
E 9

I 9

E 9
D 2
	scp = ((struct a *)(u.u_ap))->sigcntxp;
E 2
I 2
	fp = (struct sigframe *) regs[sESP] ;
D 8
	if (useracc((caddr_t)fp, sizeof (*fp), 0) == 0) {
		u.u_error = EINVAL;
		return;
	}
E 8

I 8
	if (useracc((caddr_t)fp, sizeof (*fp), 0) == 0)
		return(EINVAL);

E 8
	/* restore scratch registers */
	regs[sEAX] = fp->sf_eax ;
	regs[sEDX] = fp->sf_edx ;
	regs[sECX] = fp->sf_ecx ;
D 8
#ifdef notyet
	/* XXX FPU state? */
#endif
E 8

	scp = fp->sf_scp;
E 2
D 8
	if (useracc((caddr_t)scp, sizeof (*scp), 0) == 0) {
		u.u_error = EINVAL;
		return;
	}
E 8
I 8
	if (useracc((caddr_t)scp, sizeof (*scp), 0) == 0)
		return(EINVAL);
E 8
D 2
	if ((scp->sc_ps & (PSL_MBZ|PSL_IPL|PSL_IS)) != 0 ||
	    (scp->sc_ps & (PSL_PRVMOD|PSL_CURMOD)) != (PSL_PRVMOD|PSL_CURMOD)) {
E 2
I 2
#ifdef notyet
	if ((scp->sc_ps & PSL_MBZ) != 0 || (scp->sc_ps & PSL_MBO) != PSL_MBO) {
E 2
D 8
		u.u_error = EINVAL;
		return;
E 8
I 8
		return(EINVAL);
E 8
	}
I 2
#endif
E 2
D 8
	u.u_eosys = JUSTRETURN;
E 8
D 9
	u.u_onstack = scp->sc_onstack & 01;
E 9
I 9
D 22
        p->p_sigacts->ps_onstack = scp->sc_onstack & 01;
E 22
I 22
	if (scp->sc_onstack & 01)
		p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
	else
		p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;
E 22
E 9
D 8
	u.u_procp->p_sigmask = scp->sc_mask &~
E 8
I 8
	p->p_sigmask = scp->sc_mask &~
E 8
	    (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
D 2
	regs[FP] = scp->sc_fp;
	regs[SP] = scp->sc_sp;
	regs[PC] = scp->sc_pc;
	regs[PS] = scp->sc_ps;
E 2
I 2
	regs[sEBP] = scp->sc_fp;
	regs[sESP] = scp->sc_sp;
	regs[sEIP] = scp->sc_pc;
	regs[sEFLAGS] = scp->sc_ps;
I 8
	return(EJUSTRETURN);
E 8
E 2
}

D 2
/* XXX - BEGIN 4.2 COMPATIBILITY */
/*
 * Compatibility with 4.2 kcall $139 used by longjmp()
 */
osigcleanup()
{
	register struct sigcontext *scp;
	register int *regs = u.u_ar0;

	scp = (struct sigcontext *)fuword((caddr_t)regs[SP]);
	if ((int)scp == -1)
		return;
	if (useracc((caddr_t)scp, 3 * sizeof (int), 0) == 0)
		return;
	u.u_onstack = scp->sc_onstack & 01;
	u.u_procp->p_sigmask = scp->sc_mask &~
	    (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
	regs[SP] = scp->sc_sp;
}
/* XXX - END 4.2 COMPATIBILITY */

E 2
int	waittime = -1;

boot(arghowto)
	int arghowto;
{
	register long dummy;		/* r12 is reserved */
	register int howto;		/* r11 == how to boot */
	register int devtype;		/* r10 == major of root dev */
	extern char *panicstr;
I 16
extern int cold;
E 16

	howto = arghowto;
I 9
D 13
pg("reboot?" );
E 13
E 9
D 28
	if ((howto&RB_NOSYNC) == 0 && waittime < 0 && bfreelist[0].b_forw) {
E 28
I 28
	if ((howto&RB_NOSYNC) == 0 && waittime < 0) {
E 28
		register struct buf *bp;
		int iter, nbusy;

		waittime = 0;
		(void) splnet();
		printf("syncing disks... ");
		/*
		 * Release inodes held by texts before update.
		 */
		if (panicstr == 0)
D 9
			xumount(NODEV);
E 9
I 9
			vnode_pager_umount(NULL);
E 9
D 8
		update();
E 8
I 8
		sync((struct sigcontext *)0);
I 32
		/*
		 * Unmount filesystems
		 */
		if (panicstr == 0)
			vfs_unmountall();
E 32
E 8

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
		DELAY(10000);			/* wait for printf to finish */
	}
D 2
	mtpr(IPL, 0x1f);			/* extreme priority */
E 2
I 2
	splhigh();
E 2
	devtype = major(rootdev);
D 2
	*(int *)CPBFLG = howto;
E 2
	if (howto&RB_HALT) {
D 2
		printf("halting (in tight loop); hit ~h\n\n");
		mtpr(IPL, 0x1f);
E 2
I 2
		printf("halting (in tight loop); hit reset\n\n");
I 4
D 5
reset_cpu();
E 4
E 2
		for (;;)
			;
E 5
I 5
D 9
		reset_cpu();
E 9
I 9
		splx(0xfffd);	/* all but keyboard XXX */
E 9
		for (;;) ;
E 5
	} else {
		if (howto & RB_DUMP) {
D 9
			doadump();		/* CPBOOT's itsself */
E 9
I 9
			dumpsys();	
E 9
			/*NOTREACHED*/
		}
D 2
		tocons(CPBOOT);
E 2
	}
#ifdef lint
	dummy = 0; dummy = dummy;
	printf("howto %d, devtype %d\n", arghowto, devtype);
#endif
I 16
D 17
pg("pausing (hit any key to reset)");
E 17
I 17
#ifdef	notdef
	pg("pausing (hit any key to reset)");
#endif
E 17
E 16
I 4
D 5
reset_cpu();
E 4
	for (;;)
D 2
		asm("halt");
E 2
I 2
D 4
		asm("hlt");
E 4
I 4
		/*asm("hlt")*/;
E 5
I 5
	reset_cpu();
	for(;;) ;
E 5
E 4
E 2
	/*NOTREACHED*/
}

D 2
struct	cpdcb_o cpcontrol;

/*
 * Send the given comand ('c') to the console processor.
 * Assumed to be one of the last things the OS does before
 *  halting or rebooting.
 */
tocons(c)
{
	register timeout;

	cpcontrol.cp_hdr.cp_unit = CPUNIT;
	cpcontrol.cp_hdr.cp_comm =  (char)c;
	if (c != CPBOOT) 
		cpcontrol.cp_hdr.cp_count = 1;	/* Just for sanity */
	else {
		cpcontrol.cp_hdr.cp_count = 4;
		*(int *)cpcontrol.cp_buf = 0;	/* r11 value for reboot */
	}
	timeout = 100000;				/* Delay loop */
	while (timeout-- && (cnlast->cp_unit&CPDONE) == 0)
		uncache(&cnlast->cp_unit);
	/* give up, force it to listen */
	mtpr(CPMDCB, vtoph((struct proc *)0, (unsigned)&cpcontrol));
}

#if CLSIZE != 1
/*
 * Invalidate single all pte's in a cluster
 */
tbiscl(v)
	unsigned v;
{
	register caddr_t addr;		/* must be first reg var */
	register int i;

	addr = ptob(v);
	for (i = 0; i < CLSIZE; i++) {
		mtpr(TBIS, addr);
		addr += NBPG;
	}
}
#endif

E 2
int	dumpmag = 0x8fca0101;	/* magic number for savecore */
int	dumpsize = 0;		/* also for savecore */
/*
 * Doadump comes here after turning off memory management and
 * getting on the dump stack, either when called above, or by
 * the auto-restart code.
 */
dumpsys()
{

	if (dumpdev == NODEV)
		return;
D 9
#ifdef notdef
E 9
	if ((minor(dumpdev)&07) != 1)
		return;
D 9
#endif
E 9
	dumpsize = physmem;
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
	printf("\n\n");
	DELAY(1000);
D 2
	tocons(CPBOOT);
E 2
}

D 2
/*
 * Bus error 'recovery' code.
 * Print out the buss frame and then give up.
 * (More information from special registers can be printed here.)
 */

/*
 * Frame for bus error
 */
struct buserframe {
	int	which_bus;		/* primary or secondary */
	int	memerreg;		/* memory error register */
	int	trp_pc;			/* trapped pc */
	int	trp_psl;		/* trapped psl */
};

char	*mem_errcd[8] = {
	"Unknown error code 0",
	"Address parity error",		/* APE */
	"Data parity error",		/* DPE */
	"Data check error",		/* DCE */
	"Versabus timeout",		/* VTO */
	"Versabus error",		/* VBE */
	"Non-existent memory",		/* NEM */
	"Unknown error code 7",
};

buserror(v)
	caddr_t v;
{
	register struct buserframe *busef = (struct buserframe *)v;
	register long reg;

	printf("bus error, address %x, psl %x\n",
	    busef->trp_pc, busef->trp_psl);
	reg =  busef->memerreg;
	printf("mear %x %s\n",
	    ((reg&MEAR)>>16)&0xffff, mem_errcd[reg & ERRCD]);
	if (reg&AXE)
		printf("adapter external error\n");
	printf("error master: %s\n", reg&ERM ? "versabus" : "tahoe");
	if (reg&IVV)
		printf("illegal interrupt vector from ipl %d\n", (reg>>2)&7);
	reg = busef->which_bus;
	printf("mcbr %x versabus type %x\n",
	    ((reg&MCBR)>>16)&0xffff, reg & 0xffc3);
	if ((busef->memerreg&IVV) == 0)
		panic("buserror");
}

E 2
microtime(tvp)
	register struct timeval *tvp;
{
	int s = splhigh();

	*tvp = time;
	tvp->tv_usec += tick;
	while (tvp->tv_usec > 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	splx(s);
}

physstrat(bp, strat, prio)
	struct buf *bp;
	int (*strat)(), prio;
{
D 2
	int s;
E 2
I 2
	register int s;
	caddr_t baddr;
E 2

I 2
	/*
	 * vmapbuf clobbers b_addr so we must remember it so that it
	 * can be restored after vunmapbuf.  This is truely rude, we
	 * should really be storing this in a field in the buf struct
	 * but none are available and I didn't want to add one at
	 * this time.  Note that b_addr for dirty page pushes is 
	 * restored in vunmapbuf. (ugh!)
	 */
	baddr = bp->b_un.b_addr;
	vmapbuf(bp);
E 2
	(*strat)(bp);
	/* pageout daemon doesn't wait for pushed pages */
	if (bp->b_flags & B_DIRTY)
		return;
D 2
	s = spl8();
E 2
I 2
	s = splbio();
E 2
	while ((bp->b_flags & B_DONE) == 0)
		sleep((caddr_t)bp, prio);
	splx(s);
I 2
	vunmapbuf(bp);
	bp->b_un.b_addr = baddr;
E 2
}

initcpu()
{
D 9
	register struct proc *p;

	p = &proc[0];
E 9
D 2
#ifndef lint
#define	initkey(which, p, index) \
    which/**/_cache[index] = 1, which/**/_cnt[index] = 1; \
    p->p_/**/which = index;
	initkey(ckey, p, MAXCKEY);
	initkey(dkey, p, MAXDKEY);
#endif
E 2
}

/*
D 12
 * Clear registers on exec
E 12
I 12
D 13
 * Set registers on exec.
 * XXX Should clear registers except sp, pc,
 * but would break init; should be fixed soon.
E 13
I 13
 * Clear registers on exec
E 13
E 12
 */
D 9
setregs(entry)
E 9
I 9
D 16
setregs(p, entry)
	struct proc *p;
E 16
I 16
setregs(p, entry, retval)
	register struct proc *p;
E 16
E 9
	u_long entry;
I 16
	int retval[2];
E 16
{
D 16

E 16
D 9
#ifdef notdef
	/* should pass args to init on the stack */
	for (rp = &u.u_ar0[0]; rp < &u.u_ar0[16];)
		*rp++ = 0;
#endif
D 2
	u.u_ar0[FP] = 0;	/* bottom of the fp chain */
	u.u_ar0[PC] = entry + 2;
E 2
I 2
	u.u_ar0[sEBP] = 0;	/* bottom of the fp chain */
	u.u_ar0[sEIP] = entry;
E 9
I 9
D 20
	p->p_regs[sEBP] = 0;	/* bottom of the fp chain */
	p->p_regs[sEIP] = entry;
E 20
I 20
	p->p_md.md_regs[sEBP] = 0;	/* bottom of the fp chain */
	p->p_md.md_regs[sEIP] = entry;
E 20
E 9
I 8

D 9
	u.u_pcb.pcb_flags = 0;	/* no fp at all */
E 9
I 9
	p->p_addr->u_pcb.pcb_flags = 0;	/* no fp at all */
E 9
	load_cr0(rcr0() | CR0_EM);	/* start emulating */
D 23
#ifdef	NPX
E 23
I 23
#include "npx.h"
#if NNPX > 0
E 23
	npxinit(0x262);
#endif
E 8
}

/*
I 26
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
}

/*
E 26
 * Initialize 386 and configure to run kernel
 */

/*
 * Initialize segments & interrupt table
 */


#define	GNULL_SEL	0	/* Null Descriptor */
#define	GCODE_SEL	1	/* Kernel Code Descriptor */
#define	GDATA_SEL	2	/* Kernel Data Descriptor */
#define	GLDT_SEL	3	/* LDT - eventually one per process */
#define	GTGATE_SEL	4	/* Process task switch gate */
#define	GPANIC_SEL	5	/* Task state to consider panic from */
#define	GPROC0_SEL	6	/* Task state process slot zero and up */
I 9
#define NGDT 	GPROC0_SEL+1
E 9

D 9
union descriptor gdt[GPROC0_SEL];
E 9
I 9
union descriptor gdt[GPROC0_SEL+1];
E 9

/* interrupt descriptor table */
struct gate_descriptor idt[32+16];

/* local descriptor table */
union descriptor ldt[5];
#define	LSYS5CALLS_SEL	0	/* forced by intel BCS */
#define	LSYS5SIGR_SEL	1

#define	L43BSDCALLS_SEL	2	/* notyet */
#define	LUCODE_SEL	3
#define	LUDATA_SEL	4
/* seperate stack, es,fs,gs sels ? */
/* #define	LPOSIXCALLS_SEL	5	/* notyet */

D 9
struct	i386tss	tss;
E 9
I 9
struct	i386tss	tss, panic_tss;
E 9

I 9
D 10
extern int kstack[];
E 10
extern  struct user *proc0paddr;

E 9
/* software prototypes -- in more palitable form */
struct soft_segment_descriptor gdt_segs[] = {
	/* Null Descriptor */
{	0x0,			/* segment base address  */
	0x0,			/* length - all address space */
	0,			/* segment type */
	0,			/* segment descriptor priority level */
	0,			/* segment descriptor present */
	0,0,
	0,			/* default 32 vs 16 bit size */
	0  			/* limit granularity (byte/page units)*/ },
	/* Code Descriptor for kernel */
{	0x0,			/* segment base address  */
	0xfffff,		/* length - all address space */
	SDT_MEMERA,		/* segment type */
	0,			/* segment descriptor priority level */
	1,			/* segment descriptor present */
	0,0,
	1,			/* default 32 vs 16 bit size */
	1  			/* limit granularity (byte/page units)*/ },
	/* Data Descriptor for kernel */
{	0x0,			/* segment base address  */
	0xfffff,		/* length - all address space */
	SDT_MEMRWA,		/* segment type */
	0,			/* segment descriptor priority level */
	1,			/* segment descriptor present */
	0,0,
	1,			/* default 32 vs 16 bit size */
	1  			/* limit granularity (byte/page units)*/ },
	/* LDT Descriptor */
{	(int) ldt,			/* segment base address  */
	sizeof(ldt)-1,		/* length - all address space */
	SDT_SYSLDT,		/* segment type */
	0,			/* segment descriptor priority level */
	1,			/* segment descriptor present */
	0,0,
	0,			/* unused - default 32 vs 16 bit size */
	0  			/* limit granularity (byte/page units)*/ },
	/* Null Descriptor - Placeholder */
{	0x0,			/* segment base address  */
	0x0,			/* length - all address space */
	0,			/* segment type */
	0,			/* segment descriptor priority level */
	0,			/* segment descriptor present */
	0,0,
	0,			/* default 32 vs 16 bit size */
	0  			/* limit granularity (byte/page units)*/ },
	/* Panic Tss Descriptor */
D 9
{	(int) &u,			/* segment base address  */
E 9
I 9
{	(int) &panic_tss,		/* segment base address  */
E 9
	sizeof(tss)-1,		/* length - all address space */
	SDT_SYS386TSS,		/* segment type */
	0,			/* segment descriptor priority level */
	1,			/* segment descriptor present */
	0,0,
	0,			/* unused - default 32 vs 16 bit size */
I 9
	0  			/* limit granularity (byte/page units)*/ },
	/* Proc 0 Tss Descriptor */
{	(int) kstack,			/* segment base address  */
	sizeof(tss)-1,		/* length - all address space */
	SDT_SYS386TSS,		/* segment type */
	0,			/* segment descriptor priority level */
	1,			/* segment descriptor present */
	0,0,
	0,			/* unused - default 32 vs 16 bit size */
E 9
	0  			/* limit granularity (byte/page units)*/ }};

struct soft_segment_descriptor ldt_segs[] = {
	/* Null Descriptor - overwritten by call gate */
{	0x0,			/* segment base address  */
	0x0,			/* length - all address space */
	0,			/* segment type */
	0,			/* segment descriptor priority level */
	0,			/* segment descriptor present */
	0,0,
	0,			/* default 32 vs 16 bit size */
	0  			/* limit granularity (byte/page units)*/ },
	/* Null Descriptor - overwritten by call gate */
{	0x0,			/* segment base address  */
	0x0,			/* length - all address space */
	0,			/* segment type */
	0,			/* segment descriptor priority level */
	0,			/* segment descriptor present */
	0,0,
	0,			/* default 32 vs 16 bit size */
	0  			/* limit granularity (byte/page units)*/ },
	/* Null Descriptor - overwritten by call gate */
{	0x0,			/* segment base address  */
	0x0,			/* length - all address space */
	0,			/* segment type */
	0,			/* segment descriptor priority level */
	0,			/* segment descriptor present */
	0,0,
	0,			/* default 32 vs 16 bit size */
	0  			/* limit granularity (byte/page units)*/ },
	/* Code Descriptor for user */
{	0x0,			/* segment base address  */
	0xfffff,		/* length - all address space */
	SDT_MEMERA,		/* segment type */
	SEL_UPL,		/* segment descriptor priority level */
	1,			/* segment descriptor present */
	0,0,
	1,			/* default 32 vs 16 bit size */
	1  			/* limit granularity (byte/page units)*/ },
	/* Data Descriptor for user */
{	0x0,			/* segment base address  */
	0xfffff,		/* length - all address space */
	SDT_MEMRWA,		/* segment type */
	SEL_UPL,		/* segment descriptor priority level */
	1,			/* segment descriptor present */
	0,0,
	1,			/* default 32 vs 16 bit size */
	1  			/* limit granularity (byte/page units)*/ } };

/* table descriptors - used to load tables by microp */
struct region_descriptor r_gdt = {
	sizeof(gdt)-1,(char *)gdt
};

struct region_descriptor r_idt = {
	sizeof(idt)-1,(char *)idt
};

D 3
setidt(idx, func, typ) char *func; {
E 3
I 3
setidt(idx, func, typ, dpl) char *func; {
E 3
	struct gate_descriptor *ip = idt + idx;

	ip->gd_looffset = (int)func;
	ip->gd_selector = 8;
	ip->gd_stkcpy = 0;
	ip->gd_xx = 0;
	ip->gd_type = typ;
D 3
	ip->gd_dpl = 0;
E 3
I 3
	ip->gd_dpl = dpl;
E 3
	ip->gd_p = 1;
	ip->gd_hioffset = ((int)func)>>16 ;
}

D 9
#define	IDTVEC(name)	X/**/name
E 9
I 9
#define	IDTVEC(name)	__CONCAT(X, name)
E 9
D 5
extern
IDTVEC(div),
IDTVEC(dbg),
IDTVEC(nmi),
IDTVEC(bpt),
IDTVEC(ofl),
IDTVEC(bnd),
IDTVEC(ill),
IDTVEC(dna),
 IDTVEC(dble),		/* XXX needs to be handled by task gate */
IDTVEC(fpusegm),
 IDTVEC(tss),		/* XXX needs to be handled by task gate */
 IDTVEC(missing),	/* XXX needs to be handled by task gate */
 IDTVEC(stk),		/* XXX needs to be handled by task gate */
IDTVEC(prot),
IDTVEC(page),
IDTVEC(rsvd),
IDTVEC(fpu),
IDTVEC(rsvd0),
IDTVEC(rsvd1),
IDTVEC(rsvd2),
IDTVEC(rsvd3),
IDTVEC(rsvd4),
IDTVEC(rsvd5),
IDTVEC(rsvd6),
IDTVEC(rsvd7),
IDTVEC(rsvd8),
IDTVEC(rsvd9),
IDTVEC(rsvd10),
IDTVEC(rsvd11),
IDTVEC(rsvd12),
IDTVEC(rsvd13),
IDTVEC(rsvd14),
IDTVEC(rsvd14),
IDTVEC(intr0),
IDTVEC(intr1),
IDTVEC(intr3),
IDTVEC(intr4),
IDTVEC(intr5),
IDTVEC(intr6),
IDTVEC(intr7),
IDTVEC(intr8),
IDTVEC(intr9),
IDTVEC(intr10),
IDTVEC(intr11),
IDTVEC(intr12),
IDTVEC(intr13),
IDTVEC(intr14),
IDTVEC(intr15),
IDTVEC(syscall);
E 5
I 5
extern	IDTVEC(div), IDTVEC(dbg), IDTVEC(nmi), IDTVEC(bpt), IDTVEC(ofl),
	IDTVEC(bnd), IDTVEC(ill), IDTVEC(dna), IDTVEC(dble), IDTVEC(fpusegm),
	IDTVEC(tss), IDTVEC(missing), IDTVEC(stk), IDTVEC(prot),
	IDTVEC(page), IDTVEC(rsvd), IDTVEC(fpu), IDTVEC(rsvd0),
	IDTVEC(rsvd1), IDTVEC(rsvd2), IDTVEC(rsvd3), IDTVEC(rsvd4),
	IDTVEC(rsvd5), IDTVEC(rsvd6), IDTVEC(rsvd7), IDTVEC(rsvd8),
	IDTVEC(rsvd9), IDTVEC(rsvd10), IDTVEC(rsvd11), IDTVEC(rsvd12),
	IDTVEC(rsvd13), IDTVEC(rsvd14), IDTVEC(rsvd14), IDTVEC(syscall);
E 5

int lcr0(), lcr3(), rcr0(), rcr2();
int _udatasel, _ucodesel, _gsel_tss;

D 4
init386() { extern ssdtosd(), lgdt(), lidt(), lldt(), etext; 
E 4
I 4
init386(first) { extern ssdtosd(), lgdt(), lidt(), lldt(), etext; 
E 4
	int x, *pi;
I 9
	unsigned biosbasemem, biosextmem;
E 9
	struct gate_descriptor *gdp;
I 9
	extern int sigcode,szsigcode;
E 9

I 9
	proc0.p_addr = proc0paddr;
I 13

E 13
D 10
	/*cninit (SYSTEM+0xa0000);*/
E 10
I 10
D 11
	cninit (SYSTEM+0xa0000);
E 11
I 11
	/*
	 * Initialize the console before we print anything out.
	 */

E 11
E 10
D 13
/*pg("init386 first %x &x %x Maxmem %x", first, &x, Maxmem);
pg("init386 PTmap[0] %x PTD[0] %x", *(int *)PTmap, *(int *)PTD);*/
E 13
I 13
	cninit (KERNBASE+0xa0000);
E 13

E 9
	/* make gdt memory segments */
	gdt_segs[GCODE_SEL].ssd_limit = btoc((int) &etext + NBPG);
D 9
	for (x=0; x < 6; x++) ssdtosd(gdt_segs+x, gdt+x);
E 9
I 9
	for (x=0; x < NGDT; x++) ssdtosd(gdt_segs+x, gdt+x);
E 9
	/* make ldt memory segments */
D 5
	ldt_segs[LUCODE_SEL].ssd_limit = btoc((int) &Sysbase);
D 4
	ldt_segs[LUDATA_SEL].ssd_limit = btoc((int) &Sysbase);
E 4
I 4
	/*ldt_segs[LUDATA_SEL].ssd_limit = btoc((int) &Sysbase); */
E 5
I 5
D 9
	ldt_segs[LUCODE_SEL].ssd_limit = btoc((int) Sysbase);
	/*ldt_segs[LUDATA_SEL].ssd_limit = btoc((int) Sysbase); */
E 5
	ldt_segs[LUDATA_SEL].ssd_limit = btoc(0xfffff000);
E 9
I 9
	ldt_segs[LUCODE_SEL].ssd_limit = btoc(UPT_MIN_ADDRESS);
	ldt_segs[LUDATA_SEL].ssd_limit = btoc(UPT_MIN_ADDRESS);
E 9
E 4
D 5
	for (x=0; x < 5; x++) ssdtosd(ldt_segs+x, ldt+x);
E 5
D 13
/* Note. eventually want private ldts per process */
E 13
I 13
	/* Note. eventually want private ldts per process */
E 13
I 5
	for (x=0; x < 5; x++) ssdtosd(ldt_segs+x, ldt+x);
E 5

D 13
/* exceptions */
E 13
I 13
	/* exceptions */
E 13
D 3
	setidt(0, &IDTVEC(div),  SDT_SYS386TGT);
	setidt(1, &IDTVEC(dbg),  SDT_SYS386TGT);
	setidt(2, &IDTVEC(nmi),  SDT_SYS386TGT);
	setidt(3, &IDTVEC(bpt),  SDT_SYS386TGT);
	setidt(4, &IDTVEC(ofl),  SDT_SYS386TGT);
	setidt(5, &IDTVEC(bnd),  SDT_SYS386TGT);
	setidt(6, &IDTVEC(ill),  SDT_SYS386TGT);
	setidt(7, &IDTVEC(dna),  SDT_SYS386TGT);
	setidt(8, &IDTVEC(dble),  SDT_SYS386TGT);
	setidt(9, &IDTVEC(fpusegm),  SDT_SYS386TGT);
	setidt(10, &IDTVEC(tss),  SDT_SYS386TGT);
	setidt(11, &IDTVEC(missing),  SDT_SYS386TGT);
	setidt(12, &IDTVEC(stk),  SDT_SYS386TGT);
	setidt(13, &IDTVEC(prot),  SDT_SYS386TGT);
	setidt(14, &IDTVEC(page),  SDT_SYS386TGT);
	setidt(15, &IDTVEC(rsvd),  SDT_SYS386TGT);
	setidt(16, &IDTVEC(fpu),  SDT_SYS386TGT);
	setidt(17, &IDTVEC(rsvd0),  SDT_SYS386TGT);
	setidt(18, &IDTVEC(rsvd1),  SDT_SYS386TGT);
	setidt(19, &IDTVEC(rsvd2),  SDT_SYS386TGT);
	setidt(20, &IDTVEC(rsvd3),  SDT_SYS386TGT);
	setidt(21, &IDTVEC(rsvd4),  SDT_SYS386TGT);
	setidt(22, &IDTVEC(rsvd5),  SDT_SYS386TGT);
	setidt(23, &IDTVEC(rsvd6),  SDT_SYS386TGT);
	setidt(24, &IDTVEC(rsvd7),  SDT_SYS386TGT);
	setidt(25, &IDTVEC(rsvd8),  SDT_SYS386TGT);
	setidt(26, &IDTVEC(rsvd9),  SDT_SYS386TGT);
	setidt(27, &IDTVEC(rsvd10),  SDT_SYS386TGT);
	setidt(28, &IDTVEC(rsvd11),  SDT_SYS386TGT);
	setidt(29, &IDTVEC(rsvd12),  SDT_SYS386TGT);
	setidt(30, &IDTVEC(rsvd13),  SDT_SYS386TGT);
	setidt(31, &IDTVEC(rsvd14),  SDT_SYS386TGT);
E 3
I 3
	setidt(0, &IDTVEC(div),  SDT_SYS386TGT, SEL_KPL);
	setidt(1, &IDTVEC(dbg),  SDT_SYS386TGT, SEL_KPL);
	setidt(2, &IDTVEC(nmi),  SDT_SYS386TGT, SEL_KPL);
D 5
	  setidt(3, &IDTVEC(bpt),  SDT_SYS386TGT, SEL_UPL);
E 5
I 5
 	setidt(3, &IDTVEC(bpt),  SDT_SYS386TGT, SEL_UPL);
E 5
	setidt(4, &IDTVEC(ofl),  SDT_SYS386TGT, SEL_KPL);
	setidt(5, &IDTVEC(bnd),  SDT_SYS386TGT, SEL_KPL);
	setidt(6, &IDTVEC(ill),  SDT_SYS386TGT, SEL_KPL);
	setidt(7, &IDTVEC(dna),  SDT_SYS386TGT, SEL_KPL);
	setidt(8, &IDTVEC(dble),  SDT_SYS386TGT, SEL_KPL);
	setidt(9, &IDTVEC(fpusegm),  SDT_SYS386TGT, SEL_KPL);
	setidt(10, &IDTVEC(tss),  SDT_SYS386TGT, SEL_KPL);
	setidt(11, &IDTVEC(missing),  SDT_SYS386TGT, SEL_KPL);
	setidt(12, &IDTVEC(stk),  SDT_SYS386TGT, SEL_KPL);
	setidt(13, &IDTVEC(prot),  SDT_SYS386TGT, SEL_KPL);
	setidt(14, &IDTVEC(page),  SDT_SYS386TGT, SEL_KPL);
	setidt(15, &IDTVEC(rsvd),  SDT_SYS386TGT, SEL_KPL);
	setidt(16, &IDTVEC(fpu),  SDT_SYS386TGT, SEL_KPL);
	setidt(17, &IDTVEC(rsvd0),  SDT_SYS386TGT, SEL_KPL);
	setidt(18, &IDTVEC(rsvd1),  SDT_SYS386TGT, SEL_KPL);
	setidt(19, &IDTVEC(rsvd2),  SDT_SYS386TGT, SEL_KPL);
	setidt(20, &IDTVEC(rsvd3),  SDT_SYS386TGT, SEL_KPL);
	setidt(21, &IDTVEC(rsvd4),  SDT_SYS386TGT, SEL_KPL);
	setidt(22, &IDTVEC(rsvd5),  SDT_SYS386TGT, SEL_KPL);
	setidt(23, &IDTVEC(rsvd6),  SDT_SYS386TGT, SEL_KPL);
	setidt(24, &IDTVEC(rsvd7),  SDT_SYS386TGT, SEL_KPL);
	setidt(25, &IDTVEC(rsvd8),  SDT_SYS386TGT, SEL_KPL);
	setidt(26, &IDTVEC(rsvd9),  SDT_SYS386TGT, SEL_KPL);
	setidt(27, &IDTVEC(rsvd10),  SDT_SYS386TGT, SEL_KPL);
	setidt(28, &IDTVEC(rsvd11),  SDT_SYS386TGT, SEL_KPL);
	setidt(29, &IDTVEC(rsvd12),  SDT_SYS386TGT, SEL_KPL);
	setidt(30, &IDTVEC(rsvd13),  SDT_SYS386TGT, SEL_KPL);
	setidt(31, &IDTVEC(rsvd14),  SDT_SYS386TGT, SEL_KPL);
E 3

I 9
D 13
/*pg("isa");*/
E 13
E 9
D 5
/* first icu */
D 3
	setidt(32, &IDTVEC(intr0),  SDT_SYS386IGT);
	setidt(33, &IDTVEC(intr1),  SDT_SYS386IGT);
	setidt(34, &IDTVEC(intr9),  SDT_SYS386IGT); /* note: never happens */
	setidt(35, &IDTVEC(intr3),  SDT_SYS386IGT);
	setidt(36, &IDTVEC(intr4),  SDT_SYS386IGT);
	setidt(37, &IDTVEC(intr5),  SDT_SYS386IGT);
	setidt(38, &IDTVEC(intr6),  SDT_SYS386IGT);
	setidt(39, &IDTVEC(intr7),  SDT_SYS386IGT);
E 3
I 3
	setidt(32, &IDTVEC(intr0),  SDT_SYS386IGT, SEL_KPL);
	setidt(33, &IDTVEC(intr1),  SDT_SYS386IGT, SEL_KPL);
	setidt(34, &IDTVEC(intr9),  SDT_SYS386IGT, SEL_KPL); /* note: never happens */
	setidt(35, &IDTVEC(intr3),  SDT_SYS386IGT, SEL_KPL);
	setidt(36, &IDTVEC(intr4),  SDT_SYS386IGT, SEL_KPL);
	setidt(37, &IDTVEC(intr5),  SDT_SYS386IGT, SEL_KPL);
	setidt(38, &IDTVEC(intr6),  SDT_SYS386IGT, SEL_KPL);
	setidt(39, &IDTVEC(intr7),  SDT_SYS386IGT, SEL_KPL);
E 5
I 5
D 25
#include	"isa.h"
E 25
I 25
#include "isa.h"
E 25
#if	NISA >0
	isa_defaultirq();
#endif
E 5
E 3

I 9
D 13
/*pg("gdt");*/
E 13
E 9
D 5
/* second icu */
D 3
	setidt(40, &IDTVEC(intr8),  SDT_SYS386IGT);
	setidt(41, &IDTVEC(intr9),  SDT_SYS386IGT);
	setidt(42, &IDTVEC(intr10),  SDT_SYS386IGT);
	setidt(43, &IDTVEC(intr11),  SDT_SYS386IGT);
	setidt(44, &IDTVEC(intr12),  SDT_SYS386IGT);
	setidt(45, &IDTVEC(intr13),  SDT_SYS386IGT);
	setidt(46, &IDTVEC(intr14),  SDT_SYS386IGT);
	setidt(47, &IDTVEC(intr15),  SDT_SYS386IGT);
E 3
I 3
	setidt(40, &IDTVEC(intr8),  SDT_SYS386IGT, SEL_KPL);
	setidt(41, &IDTVEC(intr9),  SDT_SYS386IGT, SEL_KPL);
	setidt(42, &IDTVEC(intr10),  SDT_SYS386IGT, SEL_KPL);
	setidt(43, &IDTVEC(intr11),  SDT_SYS386IGT, SEL_KPL);
	setidt(44, &IDTVEC(intr12),  SDT_SYS386IGT, SEL_KPL);
	setidt(45, &IDTVEC(intr13),  SDT_SYS386IGT, SEL_KPL);
	setidt(46, &IDTVEC(intr14),  SDT_SYS386IGT, SEL_KPL);
	setidt(47, &IDTVEC(intr15),  SDT_SYS386IGT, SEL_KPL);
E 3

E 5
	lgdt(gdt, sizeof(gdt)-1);
I 9
D 13
/*pg("idt");*/
E 13
E 9
	lidt(idt, sizeof(idt)-1);
I 9
D 13
/*pg("ldt");*/
E 13
E 9
	lldt(GSEL(GLDT_SEL, SEL_KPL));
I 9
D 13
/*pg("after ldt");*/
E 13
E 9

I 9
D 16
#ifdef notyet
	/* determine amount of memory present so we can scale kernel PT */
	for (i= RAM_BEGIN; i < IOM_BEGIN; i += NBPG)
		if (probemem(i) == 0) break;
	if (i == IOM_BEGIN) {
		if (maxphysmem == 0) maxphysmem = RAM_END;
		for (i= IOM_END; i < maxphysmem; i += NBPG)
			if (probemem(i) == 0) break;
	}
	maxmem = i / NBPG;
I 11
D 13
	if(forcemaxmem && maxmem > forcemaxmem)
		maxmem = forcemaxmem-1;
	cninit (KERNBASE+0xa0000);
E 13
E 11
#else
Maxmem = 8192 *1024 /NBPG;
E 16
I 16
D 23
	/*if (Maxmem > 6*1024/4)
		Maxmem = (1024+384) *1024 /NBPG;*/
E 16
	maxmem = Maxmem;
D 16
#endif
E 16
E 9

I 9
	/* reconcile against BIOS's recorded values in RTC
	 * we trust neither of them, as both can lie!
E 23
I 23
	/*
	 * This memory size stuff is a real mess.  Here is a simple
	 * setup that just believes the BIOS.  After the rest of
	 * the system is a little more stable, we'll come back to
	 * this and deal with issues if incorrect BIOS information,
	 * and when physical memory is > 16 megabytes.
E 23
	 */
	biosbasemem = rtcin(RTC_BASELO)+ (rtcin(RTC_BASEHI)<<8);
	biosextmem = rtcin(RTC_EXTLO)+ (rtcin(RTC_EXTHI)<<8);
D 23
	if (biosbasemem == 0xffff || biosextmem == 0xffff) {
		if (maxmem > 0xffc)
			maxmem = 640/4;
	} else if (biosextmem > 0 && biosbasemem == 640) {
		int totbios = (biosbasemem + 0x60000 + biosextmem)/4;
		if (totbios < maxmem) maxmem = totbios;
	} else	maxmem = 640/4;
I 16
	maxmem = (biosextmem+1024)/4;
E 16
	maxmem = maxmem-1;
D 16
	physmem = maxmem - (0x100 -0xa0);
E 16
I 16
	physmem = maxmem;
	if (maxmem > 1024/4)
		physmem -= (1024 - 640)/4;
printf("bios base %d ext %d maxmem %d physmem %d\n",
	biosbasemem, biosextmem, 4*maxmem, 4*physmem);
E 23
I 23
	Maxmem = btoc ((biosextmem + 1024) * 1024);
	maxmem = Maxmem - 1;
	physmem = btoc (biosbasemem * 1024 + (biosextmem - 1) * 1024);
	printf ("bios %dK+%dK. maxmem %x, physmem %x\n",
		biosbasemem, biosextmem, ctob (maxmem), ctob (physmem));
E 23
E 16
D 10
pg("maxmem %dk", 4*maxmem);
E 10
I 10
D 11
/*pg("maxmem %dk", 4*maxmem);*/
E 11
E 10

I 16
D 23
maxmem=8192/4 -2;
E 23
	vm_set_page_size();
E 16
	/* call pmap initialization to make new kernel address space */
D 11
/*pg("pmap_bootstrap");*/
E 11
	pmap_bootstrap (first, 0);
	/* now running on new page tables, configured,and u/iom is accessible */

E 9
	/* make a initial tss so microp can get interrupt stack on syscall! */
D 9
	u.u_pcb.pcbtss.tss_esp0 = (int) &u + UPAGES*NBPG;
	u.u_pcb.pcbtss.tss_ss0 = GSEL(GDATA_SEL, SEL_KPL) ;
	_gsel_tss = GSEL(GPANIC_SEL, SEL_KPL);
E 9
I 9
D 10
	proc0.p_addr->u_pcb.pcbtss.tss_esp0 = (int) kstack + UPAGES*NBPG;
	proc0.p_addr->u_pcb.pcbtss.tss_ss0 = GSEL(GDATA_SEL, SEL_KPL) ;
E 10
I 10
	proc0.p_addr->u_pcb.pcb_tss.tss_esp0 = (int) kstack + UPAGES*NBPG;
	proc0.p_addr->u_pcb.pcb_tss.tss_ss0 = GSEL(GDATA_SEL, SEL_KPL) ;
E 10
	_gsel_tss = GSEL(GPROC0_SEL, SEL_KPL);
D 11
/*pg("ltr");*/
E 11
E 9
	ltr(_gsel_tss);

	/* make a call gate to reenter kernel with */
	gdp = &ldt[LSYS5CALLS_SEL].gd;
	
	x = (int) &IDTVEC(syscall);
	gdp->gd_looffset = x++;
	gdp->gd_selector = GSEL(GCODE_SEL,SEL_KPL);
	gdp->gd_stkcpy = 0;
	gdp->gd_type = SDT_SYS386CGT;
	gdp->gd_dpl = SEL_UPL;
	gdp->gd_p = 1;
	gdp->gd_hioffset = ((int) &IDTVEC(syscall)) >>16;

	/* transfer to user mode */

	_ucodesel = LSEL(LUCODE_SEL, SEL_UPL);
	_udatasel = LSEL(LUDATA_SEL, SEL_UPL);
I 9

	/* setup proc 0's pcb */
D 11
	bcopy(&sigcode, proc0.p_addr->u_pcb.pcb_sigc, szicode);
E 11
I 11
	bcopy(&sigcode, proc0.p_addr->u_pcb.pcb_sigc, szsigcode);
E 11
	proc0.p_addr->u_pcb.pcb_flags = 0;
	proc0.p_addr->u_pcb.pcb_ptd = IdlePTD;
E 9
D 5

	/* initialize 8259's */
	outb(0xf1,0);
	outb(0x20,0x11);
	outb(0x21,32);
	outb(0x21,4);
	outb(0x21,1);
	outb(0x21,0xff);

	outb(0xa0,0x11);
	outb(0xa1,40);
	outb(0xa1,2);
	outb(0xa1,1);
	outb(0xa1,0xff);

E 5
}
D 13

I 9
/*probemem(i) {
	int val;

	val = *(int *) i;
	*(int *) i = PAT;
	asm("inb $0x84,%al" ::: "ax");
}*/
E 13

extern struct pte	*CMAP1, *CMAP2;
extern caddr_t		CADDR1, CADDR2;
E 9
/*
 * zero out physical memory
 * specified in relocation units (NBPG bytes)
 */
clearseg(n) {
D 9
	extern CMAP1, CADDR1;
E 9

D 9
	CMAP1 = PG_V | PG_KW | ctob(n);
D 8
	load_cr3(_cr3());
E 8
I 8
	load_cr3(u.u_pcb.pcb_cr3);
E 8
	bzero(&CADDR1,NBPG);
E 9
I 9
	*(int *)CMAP2 = PG_V | PG_KW | ctob(n);
D 11
/*printf( " CMAP2 %x * %x CADDR2 %x\n", (int) CMAP2, *(int *) CMAP2, (int)CADDR2);
*/
E 11
	load_cr3(rcr3());
D 11
/*printf("*CADDR2 %x", * (int *) CADDR2);*/
E 11
	bzero(CADDR2,NBPG);
D 11
/*printf("*CADDR2 %x", * (int *) CADDR2);
E 11
	*(int *) CADDR2 = 0;
D 11
printf("*CADDR2 %x", * (int *) CADDR2);*/
E 11
E 9
}

/*
 * copy a page of physical memory
 * specified in relocation units (NBPG bytes)
 */
copyseg(frm, n) {
D 9
	extern CMAP2, CADDR2;
E 9

D 9
	CMAP2 = PG_V | PG_KW | ctob(n);
D 8
	load_cr3(_cr3());
E 8
I 8
	load_cr3(u.u_pcb.pcb_cr3);
E 8
	bcopy(frm, &CADDR2,NBPG);
E 9
I 9
	*(int *)CMAP2 = PG_V | PG_KW | ctob(n);
	load_cr3(rcr3());
	bcopy((void *)frm, (void *)CADDR2, NBPG);
E 9
}

D 5
strayintr(d) {
I 4
static x;
E 4
	/* for some reason, get bursts of intr #7, though not enabled! */
D 4
	/*pg("strayintr %x", d);*/
E 4
I 4
	pg("%d strayintr %x", x++,d);
E 4
}

E 5
D 9
aston() {
	schednetisr(NETISR_AST);
E 9
I 9
/*
 * copy a page of physical memory
 * specified in relocation units (NBPG bytes)
 */
physcopyseg(frm, to) {

	*(int *)CMAP1 = PG_V | PG_KW | ctob(frm);
	*(int *)CMAP2 = PG_V | PG_KW | ctob(to);
	load_cr3(rcr3());
	bcopy(CADDR1, CADDR2, NBPG);
E 9
}

I 9
/*aston() {
	schednetisr(NETISR_AST);
}*/

E 9
I 8
setsoftclock() {
	schednetisr(NETISR_SCLK);
}

E 8
/*
 * insert an element into a queue 
 */
#undef insque
_insque(element, head)
	register struct prochd *element, *head;
{
	element->ph_link = head->ph_link;
	head->ph_link = (struct proc *)element;
	element->ph_rlink = (struct proc *)head;
	((struct prochd *)(element->ph_link))->ph_rlink=(struct proc *)element;
}

/*
 * remove an element from a queue
 */
#undef remque
_remque(element)
	register struct prochd *element;
{
	((struct prochd *)(element->ph_link))->ph_rlink = element->ph_rlink;
	((struct prochd *)(element->ph_rlink))->ph_link = element->ph_link;
	element->ph_rlink = (struct proc *)0;
}

vmunaccess() {}

/*
 * Below written in C to allow access to debugging code
 */
D 9
copyinstr(fromaddr, toaddr, maxlength, lencopied) int *lencopied;
	char *toaddr; {
D 3
	int c;
	char *t = toaddr;
E 3
I 3
	int c,tally;
E 9
I 9
copyinstr(fromaddr, toaddr, maxlength, lencopied) u_int *lencopied, maxlength;
	void *toaddr, *fromaddr; {
D 23
	u_int c,tally;
E 23
I 23
	int c,tally;
E 23
E 9
E 3

D 3
/*printf("\ncpyinstr(%x,%x) %x|", fromaddr, toaddr, *(((int *) &fromaddr) - 1) );*/
	*lencopied = 0;
E 3
I 3
	tally = 0;
E 3
	while (maxlength--) {
		c = fubyte(fromaddr++);
D 3
		if (c == -1) return(EFAULT);
c &= 0xff;
		(*lencopied)++;
E 3
I 3
		if (c == -1) {
			if(lencopied) *lencopied = tally;
			return(EFAULT);
		}
		tally++;
E 3
D 9
		*toaddr++ = (char) c;
E 9
I 9
		*(char *)toaddr++ = (char) c;
E 9
		if (c == 0){
D 3
/* if(*lencopied < 50 && *t > 0) printf("%s|\n", t);*/
return(0);
}
E 3
I 3
			if(lencopied) *lencopied = tally;
			return(0);
		}
E 3
	}
I 3
	if(lencopied) *lencopied = tally;
E 3
D 8
	return(ENOENT);
E 8
I 8
	return(ENAMETOOLONG);
E 8
}

D 9
copyoutstr(fromaddr, toaddr, maxlength, lencopied) int *lencopied;
	u_char *fromaddr; {
E 9
I 9
copyoutstr(fromaddr, toaddr, maxlength, lencopied) u_int *lencopied, maxlength;
	void *fromaddr, *toaddr; {
E 9
	int c;
D 3
	u_char *f = fromaddr;
E 3
I 3
	int tally;
E 3

D 3
/*printf("\ncpyoutstr(%x,%x)%x|", fromaddr, toaddr, maxlength, 
	*(((int *) &fromaddr) - 1) );*/

	*lencopied = 0;
E 3
I 3
	tally = 0;
E 3
	while (maxlength--) {
D 9
		c = subyte(toaddr++,*fromaddr);
E 9
I 9
		c = subyte(toaddr++, *(char *)fromaddr);
E 9
		if (c == -1) return(EFAULT);
D 3
		(*lencopied)++;
E 3
I 3
		tally++;
E 3
D 9
		if (*fromaddr++ == 0){
E 9
I 9
		if (*(char *)fromaddr++ == 0){
E 9
D 3
/*if(*lencopied < 50 && *f < 127) printf("%s|\n", f);*/
E 3
I 3
			if(lencopied) *lencopied = tally;
E 3
			return(0);
D 3
}
E 3
I 3
		}
E 3
	}
I 3
	if(lencopied) *lencopied = tally;
E 3
D 8
	return(ENOENT);
E 8
I 8
	return(ENAMETOOLONG);
E 8
}

D 9
copystr(fromaddr, toaddr, maxlength, lencopied) int *lencopied;
	u_char *fromaddr, *toaddr; {
D 3
	int c;
E 3
I 3
	int tally;
E 9
I 9
copystr(fromaddr, toaddr, maxlength, lencopied) u_int *lencopied, maxlength;
	void *fromaddr, *toaddr; {
	u_int tally;
E 9
E 3

D 3
	*lencopied = 0;
E 3
I 3
	tally = 0;
E 3
	while (maxlength--) {
D 9
		*toaddr = *fromaddr++;
E 9
I 9
		*(u_char *)toaddr = *(u_char *)fromaddr++;
E 9
D 3
		(*lencopied)++;
		if (*toaddr++ == 0)
E 3
I 3
		tally++;
D 9
		if (*toaddr++ == 0) {
E 9
I 9
		if (*(u_char *)toaddr++ == 0) {
E 9
			if(lencopied) *lencopied = tally;
E 3
			return(0);
I 3
		}
E 3
	}
I 3
	if(lencopied) *lencopied = tally;
E 3
D 8
	return(ENOENT);
E 8
I 8
	return(ENAMETOOLONG);
E 8
I 3
D 11
}

/* 
 * ovbcopy - like bcopy, but recognizes overlapping ranges and handles 
 *           them correctly.
 */
I 9
void
E 9
ovbcopy(from, to, bytes)
D 9
	char *from, *to;
	int bytes;			/* num bytes to copy */
E 9
I 9
	void *from, *to;
	u_int bytes;			/* num bytes to copy */
E 9
{
	/* Assume that bcopy copies left-to-right (low addr first). */
	if (from + bytes <= to || to + bytes <= from || to == from)
		bcopy(from, to, bytes);	/* non-overlapping or no-op*/
	else if (from > to)
		bcopy(from, to, bytes);	/* overlapping but OK */
	else {
		/* to > from: overlapping, and must copy right-to-left. */
		from += bytes - 1;
		to += bytes - 1;
		while (bytes-- > 0)
D 9
			*to-- = *from--;
E 9
I 9
			*(u_char *)to-- = *(u_char *)from--;
E 9
	}
E 11
I 4
D 5
}

redstack() { int i;

	if ((u_int)&u+sizeof(u)+100 >= (u_int)&i) pg("redstack");
E 5
E 4
E 3
E 2
}
E 1
