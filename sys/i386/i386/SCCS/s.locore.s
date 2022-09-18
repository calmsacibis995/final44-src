h58800
s 00033/00033/01645
d D 8.3 93/09/23 16:42:45 bostic 30 29
c changes for 4.4BSD-Lite requested by USL
e
s 00007/00008/01671
d D 8.2 93/09/21 07:59:02 bostic 29 28
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/01677
d D 8.1 93/06/11 15:35:19 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00627/00532/01052
d D 7.11 93/06/10 21:55:54 cgd 27 26
c update with newer changed from NetBSD
e
s 00005/00005/01579
d D 7.10 92/10/11 10:10:58 bostic 26 25
c make kernel includes standard
e
s 00164/00059/01420
d D 7.9 92/07/14 14:50:46 bostic 25 24
c Changes to deal with the fact that the 386 does not honor read-only pages
c for kernel accesses.  Make subyte and suword check for write permission
c and simulate a page fault if necessary.  copyout requires similar
c treatment, for now, it is in C in trap.c.  Also, check for valid user
c addresses in all of the functions that move data to and from the user
c address space.  Delete functions for moving shorts (fusword, susword),
c which are not used.  Finally, add a push for the environment pointer which
c was missing from the call to exec in icode; from Pace Willisson.
e
s 00016/00000/01463
d D 7.8 92/05/20 16:43:50 bostic 24 23
c Define a processor speed independent DELAY function
c from Pace Willisson (pace@blitz.com)
e
s 00090/00001/01373
d D 7.7 92/05/11 16:55:45 bostic 23 22
c Implement aston, etc, whose absence has prevented preemtive
c scheduling; force interrupt priority to 0 when returning to suer mode.
c update from Pace Willison
e
s 00005/00003/01369
d D 7.6 92/05/11 16:45:40 bostic 22 21
c fix NPX device handling; from Pace Willison
e
s 00002/00035/01370
d D 7.5 92/02/05 10:54:46 bostic 21 20
c put on a reasonable header
e
s 00115/00027/01290
d D 7.4 91/11/13 17:45:41 william 20 19
c changes to fix new vm on i386
e
s 00021/00004/01296
d D 7.3 91/05/13 01:11:18 william 19 18
c last whacks, numerious bugs and cleanups, sizing disabled due to
c bug I don't care to chase now, other nicer code withdrawn due to bugs
e
s 00024/00002/01276
d D 7.2 91/05/09 21:44:57 william 18 17
c changes prior to net2 release
e
s 00004/00001/01274
d D 7.1 91/05/09 18:55:58 william 17 16
c fixed sccs strings
e
s 00065/00090/01210
d D 5.12 91/05/09 18:44:06 william 16 15
c fixes for new system
e
s 00169/00139/01131
d D 5.11 91/05/05 11:43:28 william 15 14
c interim version
e
s 00266/00218/01004
d D 5.10 91/05/02 16:21:36 william 14 13
c interim version
e
s 00055/00098/01167
d D 5.9 91/01/19 13:07:04 william 13 12
c partial cleanup, add coprocessor context switch code,  context cleanup
e
s 00000/00000/01265
d D 5.8 91/01/15 12:21:57 bill 12 11
c reno changes
e
s 00023/00028/01242
d D 5.7 90/12/06 14:20:22 bill 11 10
c working version, prior to cleanup
e
s 00013/00000/01257
d D 5.6 90/11/25 16:08:05 bill 10 9
c last changes before merger with reno version. cross fingers.
e
s 00151/00024/01106
d D 5.5 90/11/18 11:30:09 bill 9 8
c fix autoconf, move code to isa.c, remove debugging, drop redundant tlbflushes, macros for tlb et al
e
s 00004/00002/01126
d D 5.4 90/11/14 15:30:02 bill 8 7
c put in cpu bug workaround
e
s 00150/00051/00978
d D 5.3 90/11/14 13:22:42 bill 7 6
c cr3 into u., primative npx context switches, various minor bugs
e
s 00023/00012/01006
d D 5.2 90/06/23 19:26:54 donahn 6 5
c improve interrupt latency
e
s 00000/00000/01018
d D 5.1 90/04/24 19:12:06 william 5 4
c 1st Berkeley Release
e
s 00126/00216/00892
d D 1.4 90/04/24 18:56:29 william 4 3
c 1st Berkeley Release
e
s 00068/00012/01040
d D 1.3 90/04/15 18:19:31 bill 3 2
c 1st stable locore.s
e
s 00621/00873/00431
d D 1.2 90/04/13 18:25:57 bill 2 1
c baseline version, warts and all!
e
s 01304/00000/00000
d D 1.1 90/03/12 15:48:01 bill 1 0
c date and time created 90/03/12 15:48:01 by bill
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 28
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 28
I 28
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 28
E 4
 *
I 4
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 14
 * %sccs.include.386.c%
E 14
I 14
D 15
 * Copying or redistribution in any form is explicitly forbidden
 * unless prior written permission is obtained from William Jolitz or an
 * authorized representative of the University of California, Berkeley.
E 14
 *
E 4
D 14
 *	%W% (Berkeley) %G%
E 14
I 14
 * Freely redistributable copies of this code will be available in
 * the near future; for more information contact William Jolitz or
 * the Computer Systems Research Group at the University of California,
 * Berkeley.
 *
 * The name of the University may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
E 15
D 17
 *	@(#)locore.s	5.9 (Berkeley) 1/19/91
E 17
I 17
D 20
 * %sccs.include.redist.c%
E 20
I 20
D 21
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 20
 *
D 20
 *	%W% (Berkeley) %G%
E 20
I 20
D 21
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
 *	@(#)locore.s	7.3 (Berkeley) 5/13/91
E 20
E 17
I 15
D 16

E 16
E 15
E 14
 */
I 17

E 17

I 4
/*
 * locore.s:	4BSD machine support for the Intel 386
 *		Preliminary version
 *		Written by William F. Jolitz, 386BSD Project
E 21
I 21
D 27
 *	%W% (Berkeley) %G%
E 27
I 27
 *	from: @(#)locore.s	7.3 (Berkeley) 5/13/91
 *	from NetBSD: Id: locore.s,v 1.12 1993/05/27 16:44:13 cgd Exp
 *
 *      %W% (Berkeley) %G%
E 27
E 21
 */

I 27

/*
 * locore.s:	4BSD machine support for the Intel 386
 *		Preliminary version
 *		Written by William F. Jolitz, 386BSD Project
 */

E 27
I 14
#include "assym.s"
E 14
E 4
D 11
#include "psl.h"
#include "pte.h"
E 11
I 11
D 26
#include "machine/psl.h"
#include "machine/pte.h"
E 26
I 26
D 27
#include <machine/psl.h>
#include <machine/pte.h>
E 27
I 27
#include "machine/psl.h"
#include "machine/pte.h"
E 27
E 26
E 11

D 26
#include "errno.h"
E 26
I 26
D 27
#include <sys/errno.h>
E 27
I 27
#include "errno.h"
E 27
E 26
D 15
#include "cmap.h"
E 15

D 11
#include "../i386/trap.h"
E 11
I 11
D 26
#include "machine/trap.h"
E 26
I 26
D 27
#include <machine/trap.h>
E 27
I 27
#include "machine/trap.h"
E 27
E 26
E 11
D 4
/*#include "cpu.h"*/
/*#include "clock.h"*/
E 4

I 22
D 27
#include "npx.h"
E 27
I 27
#include "machine/specialreg.h"
E 27

I 27
#ifdef cgd_notdef
#include "machine/cputypes.h"
#endif

#define	KDSEL		0x10

E 27
E 22
I 4
/*
 * Note: This version greatly munged to avoid various assembler errors
 * that may be fixed in newer versions of gas. Perhaps newer versions
 * will have more pleasant appearance.
 */
E 4

	.set	IDXSHIFT,10
	.set	SYSTEM,0xFE000000	# virtual address of system start
	/*note: gas copys sign bit (e.g. arithmetic >>), can't do SYSTEM>>22! */
D 14
	.set	SYSPDROFF,0x3F8		# Page dir
E 14
I 14
	.set	SYSPDROFF,0x3F8		# Page dir index of System Base
E 14

D 14
	.set	IOPHYSmem,0xa0000

E 14
I 3
D 4
/* IBM "compatible" nop */
E 4
I 4
D 27
/* IBM "compatible" nop - sensitive macro on "fast" 386 machines */
E 4
D 7
#define	NOP	jmp 7f ; nop ; 7:
E 7
I 7
D 14
#define	NOP	jmp 7f ; nop ; 7: jmp 7f ; nop ; 7:
E 14
I 14
#define	NOP	;
E 27
I 27
#define	NOP	inb $0x84, %al ; inb $0x84, %al 
#define	ALIGN32	.align 2	/* 2^2  = 4 */
E 27
E 14
E 7

E 3
/*
I 14
 * PTmap is recursive pagemap at top of virtual address space.
 * Within PTmap, the page directory can be found (third indirection).
 */
	.set	PDRPDROFF,0x3F7		# Page dir index of Page dir
D 27
	.globl	_PTmap, _PTD, _PTDpde
E 27
I 27
	.globl	_PTmap, _PTD, _PTDpde, _Sysmap
E 27
	.set	_PTmap,0xFDC00000
	.set	_PTD,0xFDFF7000
I 27
	.set	_Sysmap,0xFDFF8000
E 27
	.set	_PTDpde,0xFDFF7000+4*PDRPDROFF

/*
 * APTmap, APTD is the alternate recursive pagemap.
 * It's used when modifying another process's page tables.
 */
	.set	APDRPDROFF,0x3FE		# Page dir index of Page dir
	.globl	_APTmap, _APTD, _APTDpde
	.set	_APTmap,0xFF800000
	.set	_APTD,0xFFBFE000
	.set	_APTDpde,0xFDFF7000+4*APDRPDROFF

/*
E 14
D 15
 * User structure is UPAGES at top of user space.
E 15
I 15
 * Access to each processes kernel stack is via a region of
 * per-process address space (at the beginning), immediatly above
 * the user process stack.
E 15
 */
D 14
	.set	_u,0xFDFFE000
	.globl	_u
	.set	UPDROFF,0x3F7
	.set	UPTEOFF,0x3FE
E 14
I 14
D 15
	.globl	_u, _Upte, _Upde
	.set	_u,0xFDBFE000
	.set	UPDROFF,0x3F6
	.set	UPTEOFF,0x400-UPAGES	# 0x3FE
	.set	_Upte,_PTmap+0xFDBFE*4 
	.set	_Upde,_PTD+UPDROFF*4
E 15
I 15
	.set	_kstack, USRSTACK
	.globl	_kstack
	.set	PPDROFF,0x3F6
	.set	PPTEOFF,0x400-UPAGES	# 0x3FE
E 15
E 14

I 2
#define	ENTRY(name) \
D 4
	.globl _##name; _##name:
E 4
I 4
	.globl _/**/name; _/**/name:
E 4
#define	ALTENTRY(name) \
D 4
	.globl _##name; _##name:
E 2
#ifdef badidea
/*
 * I/O Memory Map is 0xfffa000-0xffffffff (virtual == real)
 */
	.set	_IOmembase,0xFFFA0000
	.globl	_IOmembase
	.set	IOPDROFF,0x3FF
	.set	IOPTEOFF,0x3A0
E 4
I 4
	.globl _/**/name; _/**/name:
E 4

D 4
#endif

E 4
/*
D 14
 * System page table
 * Mbmap and Usrptmap are enlarged by CLSIZE entries
 * as they are managed by resource maps starting with index 1 or CLSIZE.
 */ 
#define	SYSMAP(mname, vname, npte)		\
D 4
_##mname:	.globl	_##mname;		\
E 4
I 4
_/**/mname:	.globl	_/**/mname;		\
E 4
	.space	(npte)*4;			\
D 4
	.set	_##vname,ptes*4096+SYSTEM;	\
	.globl	_##vname;			\
E 4
I 4
D 7
	.set	_/**/vname,ptes*4096+SYSTEM;	\
E 7
I 7
	.set	_/**/vname,ptes*NBPG+SYSTEM;	\
E 7
	.globl	_/**/vname;			\
E 4
	.set	ptes,ptes + npte
#define	ZSYSMAP(mname, vname, npte)		\
D 4
_##mname:	.globl	_##mname;		\
	.set	_##vname,ptes*4096+SYSTEM;	\
	.globl	_##vname;
E 4
I 4
_/**/mname:	.globl	_/**/mname;		\
D 7
	.set	_/**/vname,ptes*4096+SYSTEM;	\
E 7
I 7
	.set	_/**/vname,ptes*NBPG+SYSTEM;	\
E 7
	.globl	_/**/vname;
E 4

	.data
	# assumed to start at data mod 4096
	.set	ptes,0
	SYSMAP(Sysmap,Sysbase,SYSPTSIZE)
	SYSMAP(Forkmap,forkutl,UPAGES)
	SYSMAP(Xswapmap,xswaputl,UPAGES)
	SYSMAP(Xswap2map,xswap2utl,UPAGES)
	SYSMAP(Swapmap,swaputl,UPAGES)
	SYSMAP(Pushmap,pushutl,UPAGES)
	SYSMAP(Vfmap,vfutl,UPAGES)
	SYSMAP(CMAP1,CADDR1,1)
	SYSMAP(CMAP2,CADDR2,1)
	SYSMAP(mmap,vmmap,1)
	SYSMAP(alignmap,alignutl,1)	/* XXX */
	SYSMAP(msgbufmap,msgbuf,MSGBUFPTECNT)
I 7
	/* SYSMAP(EMCmap,EMCbase,1) */
	SYSMAP(Npxmap,npxutl,UPAGES)
	SYSMAP(Swtchmap,Swtchbase,UPAGES)
E 7
	.set mbxxx,(NMBCLUSTERS*MCLBYTES)
	.set mbyyy,(mbxxx>>PGSHIFT)
	.set mbpgs,(mbyyy+CLSIZE)
	SYSMAP(Mbmap,mbutl,mbpgs)
	/*
	 * XXX: NEED way to compute kmem size from maxusers,
	 * device complement
	 */
	SYSMAP(kmempt,kmembase,300*CLSIZE)
#ifdef	GPROF
	SYSMAP(profmap,profbase,600*CLSIZE)
#endif
	.set	atmemsz,0x100000-0xa0000
	.set	atpgs,(atmemsz>>PGSHIFT)
	SYSMAP(ATDevmem,atdevbase,atpgs)
I 2
D 7
#define USRIOSIZE 30
E 7
I 7
D 13
/*#define USRIOSIZE 30*/
E 13
E 7
	SYSMAP(Usriomap,usrio,USRIOSIZE+CLSIZE) /* for PHYSIO */
E 2
	ZSYSMAP(ekmempt,kmemlimit,0)
D 2

E 2
	SYSMAP(Usrptmap,usrpt,USRPTSIZE+CLSIZE)

eSysmap:
	# .set	_Syssize,(eSysmap-_Sysmap)/4
	.set	_Syssize,ptes
	.globl	_Syssize

	/* align on next page boundary */
	# . = . + NBPG - 1 & -NBPG	/* align to page boundry-does not work*/
	# .space (PGSIZE - ((eSysmap-_Sysmap) % PGSIZE)) % PGSIZE
	.set sz,(4*ptes)%NBPG
	# .set rptes,(ptes)%1024
	# .set rptes,1024-rptes
	# .set ptes,ptes+rptes
D 2
	.set Npdes,1
E 2
I 2
D 4
	.set Npdes,3
E 4
I 4
D 7
	.set Npdes,5
E 4
E 2
	.space (NBPG - sz)
E 7
I 7
D 13
	.set Npdes,10
E 13
I 13
	.set Npdes,8
E 13
	# .space (NBPG - sz)
E 7

I 2
D 4
	.globl	_tMap
E 2
	# SYSMAP(Tmap,tmap,1024)
_tMap:
	.space	NBPG
I 2
	.globl	_PDR
E 2
_PDR:
	# SYSMAP(PDR,pdr,1024)
	.space	NBPG

E 4
/*
E 14
 * Initialization
 */
	.data
D 7
	.globl	_cpu
_cpu:	.long	0	# are we 386, 386sx, or 486
E 7
I 7
D 13
	.globl	_cpu, _boothowto, _bootdev, _cyloffset, _Maxmem
E 13
I 13
D 14
	.globl	_cpu, _cold, _boothowto, _bootdev, _cyloffset, _Maxmem
E 14
I 14
D 19
	.globl	_cpu,_cold,_boothowto,_bootdev,_cyloffset,_Maxmem,_atdevbase,_atdevphys
E 19
I 19
	.globl	_cpu,_cold,_boothowto,_bootdev,_cyloffset,_atdevbase,_atdevphys
E 19
E 14
E 13
_cpu:	.long	0		# are we 386, 386sx, or 486
I 13
_cold:	.long	1		# cold till we are not
I 14
_atdevbase:	.long	0	# location of start of iomem in virtual
_atdevphys:	.long	0	# location of device mapping ptes (phys)

	.globl	_IdlePTD, _KPTphys
_IdlePTD:	.long	0
_KPTphys:	.long	0

D 20
	.space 512
E 20
I 20
D 27
pcb:
	.space 8192
E 27
I 27
	.space 512
E 27
E 20
tmpstk:
I 20
D 27
pcb2:
	.space 8192
tmpstk2:
E 27
E 20
E 14
E 13
E 7
	.text
	.globl	start
D 4
start:
E 4
I 4
D 14
start:				# This is assumed to be location zero!
E 4
I 2
	movw	$0x1234,%ax
E 14
I 14
D 20
start:	movw	$0x1234,%ax
E 20
I 20
D 27
 #start:
	.set start,0
	movw	$0x1234,%ax
E 27
I 27
start:	movw	$0x1234,%ax
E 27
E 20
E 14
	movw	%ax,0x472	# warm boot
	jmp	1f
D 7
	.space	0x500	# skip over warm boot shit
1:
D 4
#ifdef notdef
	inb	$0x61,%al
	orb	$3,%al
	outb	%al,$0x61
	movl	$0xffff,%ecx
fooy:	loop	fooy
#endif
E 4
E 2
#ifdef notyet
	# XXX pass parameters on stack
/* count up memory */
E 7
I 7
	.space	0x500		# skip over warm boot shit

I 19
D 27
	/* enable a20! yecchh!! - move this to bootstrap? */
1:	inb	$0x64,%al
	andb	$2,%al
	jnz	1b
	movb	$0xd1,%al
	NOP
	outb	%al,$0x64
	NOP
1:	inb	$0x64,%al
	andb	$2,%al
	jnz	1b
	movb	$0xdf,%al
	NOP
	outb	%al,$0x60

E 27
E 19
D 14
	/* enable a20! yecchh!! */
E 14
I 14
D 16
	/* enable a20! yecchh!! - move this to bootstrap? */
E 14
1:	inb	$0x64,%al
	andb	$2,%al
	jnz	1b
	movb	$0xd1,%al
	NOP
	outb	%al,$0x64
	NOP
1:	inb	$0x64,%al
	andb	$2,%al
	jnz	1b
	movb	$0xdf,%al
	NOP
	outb	%al,$0x60

E 16
D 14
	/* pass parameters on stack (howto, bootdev, unit, cyloffset) */
E 14
I 14
	/*
	 * pass parameters on stack (howto, bootdev, unit, cyloffset)
	 * note: 0(%esp) is return address of boot
	 * ( if we want to hold onto /boot, it's physical %esp up to _end)
	 */
E 14

D 19
	movl	4(%esp),%eax
E 19
I 19
 1:	movl	4(%esp),%eax
E 19
	movl	%eax,_boothowto-SYSTEM
	movl	8(%esp),%eax
	movl	%eax,_bootdev-SYSTEM
	movl	12(%esp),%eax
	movl	%eax, _cyloffset-SYSTEM

I 27
#ifdef cgd_notdef
	/* find out our CPU type. */
        pushfl
        popl    %eax
        movl    %eax, %ecx
        xorl    $0x40000, %eax
        pushl   %eax
        popfl
        pushfl
        popl    %eax
        xorl    %ecx, %eax
        shrl    $18, %eax
        andl    $1, %eax
        push    %ecx
        popfl
      
        cmpl    $0, %eax
        jne     1f
        movl    $CPU_386, _cpu-SYSTEM
	jmp	2f
1:      movl    $CPU_486, _cpu-SYSTEM
2:
#endif

#ifdef garbage
E 27
	/* count up memory */

E 7
D 20
	xorl	%eax,%eax		# start with base memory at 0x0
E 20
I 20
D 27
	xorl	%edx,%edx		# start with base memory at 0x0
E 27
I 27
	xorl	%eax,%eax		# start with base memory at 0x0
E 27
E 20
D 7
	movl	$(0xA0000/NBPG),%ecx	# look every 4K up to 640K
E 7
I 7
	#movl	$ 0xA0000/NBPG,%ecx	# look every 4K up to 640K
	movl	$ 0xA0,%ecx		# look every 4K up to 640K
E 7
D 20
1:	movl	0(%eax),%ebx		# save location to check
	movl	$0xa55a5aa5,0(%eax)	# write test pattern
E 20
I 20
D 27
1:	movl	0(%edx),%ebx		# save location to check
	movl	$0xa55a5aa5,0(%edx)	# write test pattern

	inb	$0x84,%al		# flush write buffer
E 27
I 27
1:	movl	0(%eax),%ebx		# save location to check
	movl	$0xa55a5aa5,0(%eax)	# write test pattern
E 27
E 20
I 14
	/* flush stupid cache here! (with bcopy (0,0,512*1024) ) */
E 14
D 20
	cmpl	$0xa55a5aa5,0(%eax)	# does not check yet for rollover
E 20
I 20
D 27

	cmpl	$0xa55a5aa5,0(%edx)	# does not check yet for rollover
E 27
I 27
	cmpl	$0xa55a5aa5,0(%eax)	# does not check yet for rollover
E 27
E 20
	jne	2f
D 20
	movl	%ebx,0(%eax)		# restore memory
D 4
	addl	$NBPG,%eax
E 4
I 4
	addl	$ NBPG,%eax
E 20
I 20
D 27
	movl	%ebx,0(%edx)		# restore memory
	addl	$ NBPG,%edx
E 27
I 27
	movl	%ebx,0(%eax)		# restore memory
	addl	$ NBPG,%eax
E 27
E 20
E 4
	loop	1b
I 27
2:	shrl	$12,%eax
	movl	%eax,_Maxmem-SYSTEM
E 27
D 7
2:	movl	%eax,_basemem-SYSTEM
E 7
I 7
D 20
2:	shrl	$12,%eax
	movl	%eax,_Maxmem-SYSTEM
E 20
E 7

D 20
	movl	$0x100000,%eax		# next, talley remaining memory
E 20
I 20
D 27
	movl	$0x100000,%edx		# next, talley remaining memory
E 27
I 27
	movl	$0x100000,%eax		# next, talley remaining memory
E 27
E 20
D 7
	movl	$((0xFA0000-0x100000)/NBPG),%ecx
E 7
I 7
	#movl	$((0xFFF000-0x100000)/NBPG),%ecx
	movl	$(0xFFF-0x100),%ecx
E 7
D 20
1:	movl	0(%eax),%ebx		# save location to check
	movl	$0xa55a5aa5,0(%eax)	# write test pattern
	cmpl	$0xa55a5aa5,0(%eax)	# does not check yet for rollover
E 20
I 20
D 27
1:	movl	0(%edx),%ebx		# save location to check
	movl	$0xa55a5aa5,0(%edx)	# write test pattern
	cmpl	$0xa55a5aa5,0(%edx)	# does not check yet for rollover
E 27
I 27
1:	movl	0(%eax),%ebx		# save location to check
	movl	$0xa55a5aa5,0(%eax)	# write test pattern
	cmpl	$0xa55a5aa5,0(%eax)	# does not check yet for rollover
E 27
E 20
	jne	2f
D 20
	movl	%ebx,0(%eax)		# restore memory
D 4
	addl	$NBPG,%eax
E 4
I 4
	addl	$ NBPG,%eax
E 20
I 20
D 27
	movl	%ebx,0(%edx)		# restore memory
	addl	$ NBPG,%edx
E 27
I 27
	movl	%ebx,0(%eax)		# restore memory
	addl	$ NBPG,%eax
E 27
E 20
E 4
	loop	1b
D 7
2:	movl	%eax,_abovemem-SYSTEM
D 2

E 2
#endif notyet
E 7
I 7
D 20
2:	shrl	$12,%eax
	movl	%eax,_Maxmem-SYSTEM
E 20
I 20
D 27
2:	shrl	$12,%edx
	movl	%edx,_Maxmem-SYSTEM
E 27
I 27
2:	shrl	$12,%eax
	movl	%eax,_Maxmem-SYSTEM
#endif
E 27
E 20
E 7
I 2

E 2
D 4
/* clear memory. is this redundant ? */
E 4
I 4
D 14
/* clear memory. */
E 4
	movl	$_edata-SYSTEM,%edi
E 14
I 14
/* find end of kernel image */
E 14
	movl	$_end-SYSTEM,%ecx
D 4
	addl	$NBPG-1,%ecx
E 4
I 4
	addl	$ NBPG-1,%ecx
E 4
	andl	$~(NBPG-1),%ecx
	movl	%ecx,%esi
I 14

/* clear bss and memory for bootstrap pagetables. */
	movl	$_edata-SYSTEM,%edi
E 14
	subl	%edi,%ecx
D 14
	addl	$(UPAGES*NBPG)+NBPG+NBPG+NBPG,%ecx
	#	txt+data+proc zero pt+u.
E 14
I 14
	addl	$(UPAGES+5)*NBPG,%ecx
D 15
	#	kernel bss + page directory + page table + stack
E 15
I 15
/*
 * Virtual address space of kernel:
 *
 *	text | data | bss | page dir | proc0 kernel stack | usr stk map | Sysmap
 *			     0               1       2       3             4
 */
E 15
E 14
D 13
	# any other junk?
D 4
	addl	$NBPG-1,%ecx
E 4
I 4
D 7
	addl	$ NBPG-1,%ecx
E 4
	andl	$~(NBPG-1),%ecx
E 7
I 7
	# addl	$ NBPG-1,%ecx
	# andl	$~(NBPG-1),%ecx
E 7
	# shrl	$2,%ecx	# convert to long word count
E 13
	xorl	%eax,%eax	# pattern
	cld
	rep
	stosb

I 11
D 13
#ifdef notdef
E 11
I 7
	/* pass parameters on stack (howto, bootdev, unit, cyloffset) */

	movl	4(%esp),%eax
	movl	%eax,_boothowto-SYSTEM
	movl	8(%esp),%eax
	movl	%eax,_bootdev-SYSTEM
	movl	12(%esp),%eax
	movl	%eax, _cyloffset-SYSTEM

D 11
#ifdef notdef
E 11

	movl	$0x36000,%edi
	movl	$0x68000,%ecx
	xorl	%eax,%eax	# pattern
	cld
	rep
	stosb

#endif
E 13
I 13
D 14
/* should do all of memory, but some systems don't probe correctly (yet)*/
E 13
	movl	$0x100000,%edi
	movl	$0x200000,%ecx
	xorl	%eax,%eax	# pattern
	cld
	rep
	stosb
E 14
I 14
	movl	%esi,_IdlePTD-SYSTEM /*physical address of Idle Address space */
	movl	$ tmpstk-SYSTEM,%esp	# bootstrap stack end location

#define	fillkpt		\
1:	movl	%eax,0(%ebx)	; \
	addl	$ NBPG,%eax	; /* increment physical address */ \
	addl	$4,%ebx		; /* next pte */ \
	loop	1b		;

E 14
E 7
/*
 * Map Kernel
 * N.B. don't bother with making kernel text RO, as 386
D 4
 * ignores R/W bit on kernel access!
E 4
I 4
 * ignores R/W AND U/S bits on kernel access (only v works) !
I 7
 *
 * First step - build page tables
E 7
E 4
 */
D 4
	# movl	$_Syssize,%ecx		# for this many pte s,
E 4
	movl	%esi,%ecx		# this much memory,
D 4
	shrl	$PGSHIFT,%ecx		# for this many pte s
	movl	$PG_V,%eax		#  having these bits set,
E 4
I 4
	shrl	$ PGSHIFT,%ecx		# for this many pte s
I 14
	addl	$ UPAGES+4,%ecx		# including our early context
E 14
	movl	$ PG_V,%eax		#  having these bits set,
E 4
D 14
	movl	$_Sysmap-SYSTEM,%ebx	#   in the kernel page table,
					#    fill in kernel page table.
1:	movl	%eax,0(%ebx)
D 4
	addl	$NBPG,%eax			# increment physical address
E 4
I 4
	addl	$ NBPG,%eax			# increment physical address
E 4
	addl	$4,%ebx				# next pte
	loop	1b
E 14
I 14
	lea	(4*NBPG)(%esi),%ebx	#   physical address of KPT in proc 0,
	movl	%ebx,_KPTphys-SYSTEM	#    in the kernel page table,
	fillkpt
E 14

D 14
/* temporary double map  virt == real */

	movl	$1024,%ecx		# for this many pte s,
D 4
	movl	$PG_V,%eax		#  having these bits set,
	movl	$_tMap-SYSTEM,%ebx	#   in the temporary page table,
E 4
I 4
	movl	$ PG_V,%eax		#  having these bits set,
D 7
	movl	$_Forkmap-SYSTEM,%ebx	#   in the temporary page table,
E 7
I 7
	movl	$_Sysmap+4096-SYSTEM,%ebx	#   in the temporary page table,
E 7
E 4
					#    fill in kernel page table.
1:	movl	%eax,0(%ebx)
D 4
	addl	$NBPG,%eax			# increment physical address
E 4
I 4
	addl	$ NBPG,%eax			# increment physical address
E 4
	addl	$4,%ebx				# next pte
	loop	1b

E 14
D 4
#ifdef badidea
/* map I/O memory virt == real */

	movl	$(1024-IOPTEOFF),%ecx	# for this many pte s,
	movl	$(_IOmembase|PG_V),%eax	#  having these bits set, (perhaps URW?)
	movl	$_IOMap-SYSTEM,%ebx	#   in the temporary page table,
	addl	$(IOPTEOFF*4),%ebx
					#    fill in kernel page table.
1:	movl	%eax,0(%ebx)
	addl	$NBPG,%eax			# increment physical address
	addl	$4,%ebx				# next pte
	loop	1b
#endif

E 4
/* map I/O memory map */

D 14
	movl	$atpgs,%ecx		# for this many pte s,
	movl	$(IOPHYSmem|PG_V),%eax	#  having these bits set, (perhaps URW?)
	movl	$_ATDevmem-SYSTEM,%ebx	#   in the temporary page table,
					#    fill in kernel page table.
1:	movl	%eax,0(%ebx)
D 4
	addl	$NBPG,%eax			# increment physical address
E 4
I 4
	addl	$ NBPG,%eax			# increment physical address
E 4
	addl	$4,%ebx				# next pte
	loop	1b
E 14
I 14
	movl	$0x100-0xa0,%ecx	# for this many pte s,
D 27
	movl	$(0xa0000|PG_V),%eax	#  having these bits set, (perhaps URW?)
E 27
I 27
	movl	$(0xa0000|PG_V|PG_UW),%eax # having these bits set,(perhaps URW?) XXX 06 Aug 92
E 27
	movl	%ebx,_atdevphys-SYSTEM	#   remember phys addr of ptes
	fillkpt
E 14

D 7
/*# map proc 0's page table*/
E 7
I 7
D 14
/* map proc 0's page table (P1 region) */
E 14
I 14
D 15
 /* map proc 0's _u into sole user page table page (mapping stack & u.) */
E 15
I 15
 /* map proc 0's kernel stack into user page table page */
E 15
E 14

E 7
D 14
	movl	$_Usrptmap-SYSTEM,%ebx	# get pt map address
	lea	(0*NBPG)(%esi),%eax	# physical address of pt in proc 0
D 4
	orl	$PG_V,%eax		#  having these bits set,
E 4
I 4
	orl	$ PG_V,%eax		#  having these bits set,
E 4
	movl	%eax,0(%ebx)

D 7
 /*# map proc 0's _u*/
E 7
I 7
 /* map proc 0's _u */

E 14
E 7
D 4
	movl	$UPAGES,%ecx		# for this many pte s,
E 4
I 4
	movl	$ UPAGES,%ecx		# for this many pte s,
E 4
D 2
	lea	(1*NBPG)(%esi),%eax	# physical address of _u in proc 0
E 2
I 2
D 14
	lea	(2*NBPG)(%esi),%eax	# physical address of _u in proc 0
E 14
I 14
D 15
	lea	(1*NBPG)(%esi),%eax	# physical address of _u in proc 0
E 15
I 15
	lea	(1*NBPG)(%esi),%eax	# physical address in proc 0
E 15
	lea	(SYSTEM)(%eax),%edx
	movl	%edx,_proc0paddr-SYSTEM  # remember VA for 0th process init
E 14
E 2
D 4
	orl	$PG_V|PG_URKW,%eax	#  having these bits set,
E 4
I 4
	orl	$ PG_V|PG_URKW,%eax	#  having these bits set,
E 4
D 14
	lea	(0*NBPG)(%esi),%ebx	# physical address of stack pt in proc 0
E 14
I 14
	lea	(3*NBPG)(%esi),%ebx	# physical address of stack pt in proc 0
E 14
D 15
	addl	$(UPTEOFF*4),%ebx
E 15
I 15
	addl	$(PPTEOFF*4),%ebx
E 15
D 14
					#    fill in proc 0 stack page table.
1:	movl	%eax,0(%ebx)
D 4
	addl	$NBPG,%eax			# increment physical address
E 4
I 4
	addl	$ NBPG,%eax			# increment physical address
E 4
	addl	$4,%ebx				# next pte
	loop	1b
E 14
I 14
	fillkpt
E 14

I 2
D 13
 /*# map proc 0's page directory*/
E 13
I 13
D 14
 /* locate proc 0's page directory*/
E 13
	lea	(1*NBPG)(%esi),%eax	# physical address of ptd in proc 0
	movl	%eax,%edi		# remember ptd physical address
I 7
D 13
#ifdef dubious
E 7
D 4
	orl	$PG_V|PG_URKW,%eax	#  having these bits set,
E 4
I 4
	orl	$ PG_V|PG_URKW,%eax	#  having these bits set,
E 4
	lea	(0*NBPG)(%esi),%ebx	# physical address of stack pt in proc 0
	addl	$(UPTEOFF*4),%ebx
	addl	$(UPAGES*4),%ebx
	movl	%eax,0(%ebx)
I 7
#endif
E 13
E 7

E 14
E 2
/*
 * Construct a page table directory
 * (of page directory elements - pde's)
 */
D 14
					/* kernel pde's */
	movl	$_Sysmap-SYSTEM,%eax	# physical address of kernel page table
E 14
I 14
	/* install a pde for temporary double map of bottom of VA */
	lea	(4*NBPG)(%esi),%eax	# physical address of kernel page table
E 14
D 4
	orl	$PG_V,%eax		# pde entry is valid
	movl	$Npdes,%ecx		# for this many pde s,
D 2
	movl	$_PDR-SYSTEM,%ebx		# address of start of ptd
	# lea	(2*NBPG)(%esi),%ebx	# address of ptd in proc 0 pt
E 2
I 2
	# movl	$_PDR-SYSTEM,%ebx		# address of start of ptd
E 4
I 4
D 27
	orl	$ PG_V,%eax		# pde entry is valid
E 27
I 27
	orl     $ PG_V|PG_UW,%eax	# pde entry is valid XXX 06 Aug 92
E 27
D 14
	movl	$ Npdes,%ecx		# for this many pde s,
E 4
	movl	%edi,%ebx		# phys address of ptd in proc 0
E 2
	addl	$(SYSPDROFF*4), %ebx	# offset of pde for kernel
1:	movl	%eax,0(%ebx)
D 4
	addl	$NBPG,%eax			# increment physical address
E 4
I 4
	addl	$ NBPG,%eax			# increment physical address
E 4
	addl	$4,%ebx				# next pde
	loop	1b
					# install a pde for temporary double map
D 4
	movl	$_tMap-SYSTEM,%eax	# physical address of temp page table
	orl	$PG_V,%eax		# pde entry is valid
D 2
	movl	$_PDR-SYSTEM,%ebx		# address of start of ptd
	# lea	(2*NBPG)(%esi),%ebx	# address of ptd in proc 0 pt
E 2
I 2
	# movl	$_PDR-SYSTEM,%ebx		# address of start of ptd
E 4
I 4
D 7
	movl	$_Forkmap-SYSTEM,%eax	# physical address of temp page table
E 7
I 7
	movl	$_Sysmap+4096-SYSTEM,%eax	# physical address of temp page table
E 14
I 14
	movl	%eax,(%esi)		# which is where temp maps!

	/* kernel pde's */
	movl	$ 3,%ecx		# for this many pde s,
	lea	(SYSPDROFF*4)(%esi), %ebx	# offset of pde for kernel
	fillkpt

	/* install a pde recursively mapping page directory as a page table! */
	movl	%esi,%eax		# phys address of ptd in proc 0
E 14
D 13
	# movl	$_Sysmap-SYSTEM,%eax	# physical address of temp page table
E 13
E 7
D 27
	orl	$ PG_V,%eax		# pde entry is valid
E 27
I 27
	orl	$ PG_V|PG_UW,%eax	# pde entry is valid XXX 06 Aug 92
E 27
E 4
D 14
	movl	%edi,%ebx		# phys address of ptd in proc 0
E 2
	movl	%eax,0(%ebx)			# which is where temp maps!
D 4
#ifdef badidea
					# install a pde for IO memory
	movl	$_IOMap-SYSTEM,%eax	# physical address of temp page table
	orl	$PG_V,%eax		# pde entry is valid
	movl	$_PDR-SYSTEM,%ebx		# address of start of ptd
	# lea	(2*NBPG)(%esi),%ebx	# address of ptd in proc 0 pt
	addl	$(IOPDROFF*4), %ebx	# offset of pde for kernel
	movl	%eax,0(%ebx)			# which is where temp maps!
#endif
E 4
					# install a pde to map _u for proc 0
	lea	(0*NBPG)(%esi),%eax	# physical address of pt in proc 0
E 14
I 14
	movl	%eax, PDRPDROFF*4(%esi)	# which is where PTmap maps!

D 15
	/* install a pde to map _u for proc 0 */
E 15
I 15
	/* install a pde to map kernel stack for proc 0 */
E 15
	lea	(3*NBPG)(%esi),%eax	# physical address of pt in proc 0
E 14
D 4
	orl	$PG_V,%eax		# pde entry is valid
D 2
	movl	$_PDR-SYSTEM,%ebx		# address of start of ptd
	# lea	(2*NBPG)(%esi),%ebx	# address of ptd in proc 0 pt
E 2
I 2
	# movl	$_PDR-SYSTEM,%ebx		# address of start of ptd
E 4
I 4
	orl	$ PG_V,%eax		# pde entry is valid
E 4
D 14
	movl	%edi,%ebx		# phys address of ptd in proc 0
E 2
	addl	$(UPDROFF*4), %ebx	# offset of pde for kernel
	movl	%eax,0(%ebx)		# which is where _u maps!
E 14
I 14
D 15
	movl	%eax,UPDROFF*4(%esi)		# which is where _u maps!
E 15
I 15
	movl	%eax,PPDROFF*4(%esi)	# which is where kernel stack maps!
E 15
E 14

I 6
D 7
#ifdef bug
	movl	$_Sysmap-SYSTEM,%eax	# physical address of kernel page table
	movl	$0x21,%ebx
	shll	$2,%ebx
	addl	%ebx,%eax
	xorl	%ebx,%ebx
	movl	%ebx,0(%eax)		# un validate offending pte
#endif

E 7
E 6
D 4
	# movl	%eax,_PDR-SYSTEM+(1024-16-1)*4
	# movl	$UDOT,%eax
	# shrl	$PGSHIFT+IDXSHF,%eax
	# shll	$2,%eax
	# addl	$_PDR-SYSTEM,%eax
	# orl	$PG_V,%eax

D 2
	movl	$_PDR-SYSTEM,%eax		# address of start of ptd
	# lea	(2*NBPG)(%esi),%eax	# address o ptd in proc 0 pt
E 2
I 2
	# movl	$_PDR-SYSTEM,%eax		# address of start of ptd
E 4
D 14
	movl	%edi,%eax		# phys address of ptd in proc 0
E 14
I 14
	/* load base of page directory, and enable mapping */
	movl	%esi,%eax		# phys address of ptd in proc 0
E 14
I 4
D 8
 # orl $0x80000000,%eax
E 8
I 8
 	orl	$ I386_CR3PAT,%eax
E 8
E 4
E 2
D 6
	movl	%eax,%cr3			# load ptd addr into mmu
	movl	$0x80000001,%eax		# and let s page!
	movl	%eax,%cr0			# NOW!
E 6
I 6
	movl	%eax,%cr3		# load ptd addr into mmu
	movl	%cr0,%eax		# get control word
	orl	$0x80000001,%eax	# and let s page!
	movl	%eax,%cr0		# NOW!
E 6

	pushl	$begin				# jump to high mem!
D 4
	ret
E 4
I 4
D 14
	ret		# jmp $begin does not work
E 4
begin:
D 2
	movl	$_u+UPAGES*NBPG-4,%eax
E 2
I 2
D 4
	# movl	$_u+UPAGES*NBPG-4,%eax
	# movl	$0xfdfffffc,%eax
	movl	$_Sysbase,%eax
E 4
I 4
	movl	$_Sysbase,%eax		# kernel stack just below system
E 4
E 2
	movl	%eax,%esp
E 14
I 14
D 16
	ret		# jmp $begin does not work - generates relative jmp
E 16
I 16
	ret

E 16
begin: /* now running relocated at SYSTEM where the system is linked to run */
D 16
#ifdef notyet
	movl	$0,SYSTEM(%esi)		# destroy temp double map
	movl	%esi,%eax		# phys address of ptd in proc 0
 	orl	$ I386_CR3PAT,%eax
	movl	%eax,%cr3		# load ptd addr into mmu
#endif
E 16

	.globl _Crtat
	movl	_Crtat,%eax
	subl	$0xfe0a0000,%eax
	movl	_atdevphys,%edx	# get pte PA
	subl	_KPTphys,%edx	# remove base of ptes, now have phys offset
	shll	$ PGSHIFT-2,%edx  # corresponding to virt offset
	addl	$ SYSTEM,%edx	# add virtual base
	movl	%edx, _atdevbase
	addl	%eax,%edx
	movl	%edx,_Crtat

	/* set up bootstrap stack */
D 15
	movl	$ _u+UPAGES*NBPG-4*12,%esp	# bootstrap stack end location
E 15
I 15
	movl	$ _kstack+UPAGES*NBPG-4*12,%esp	# bootstrap stack end location
E 15
E 14
I 4
	xorl	%eax,%eax		# mark end of frames
E 4
	movl	%eax,%ebp
D 4
	movl	_Crtat,%eax
	subl	$IOPHYSmem,%eax
E 4
I 4
D 14
	
	movl	_Crtat,%eax		# initialize Crt video ram address
	subl	$ IOPHYSmem,%eax
E 4
	addl	$_atdevbase,%eax
	movl	%eax,_Crtat
E 14
I 14
D 15
	movl	%esi, _u+PCB_CR3
E 15
I 15
	movl	_proc0paddr, %eax
	movl	%esi, PCB_CR3(%eax)
E 15
E 14
D 2
	# call	_init386
E 2
I 2
D 4
	call	_init386
E 4
I 4

I 14
	lea	7*NBPG(%esi),%esi	# skip past stack.
	pushl	%esi
	
E 14
	call	_init386		# wire 386 chip for unix operation
I 20
D 27
	popl	%esi
E 27
E 20
D 14

E 4
/* initialize (slightly) the pcb */
	movl	$_u,%eax		# proc0 u-area
	movl	$_usrpt,%ecx
	movl	%ecx,PCB_P0BR(%eax)	# p0br: SVA of text/data user PT
	xorl	%ecx,%ecx
	movl	%ecx,PCB_P0LR(%eax)	# p0lr: 0 (doesn t really exist)
I 13
	movl	%ecx,PCB_FLAGS(%eax)	# no fp yet.
E 13
	movl	$_usrpt+NBPG,%ecx	# addr of end of PT
D 4
	subl	$P1PAGES*4,%ecx		# backwards size of P1 region
E 4
I 4
	subl	$ P1PAGES*4,%ecx		# backwards size of P1 region
E 4
	movl	%ecx,PCB_P1BR(%eax)	# p1br: P1PAGES from end of PT
D 4
	movl	$P1PAGES-UPAGES,PCB_P1LR(%eax)	# p1lr: vax style
	movl	$CLSIZE,PCB_SZPT(%eax)	# page table size
	#clrw	a1@(PCB_FLAGS)		# clear flags
E 4
I 4
	movl	$ P1PAGES-UPAGES,PCB_P1LR(%eax)	# p1lr: vax style
	movl	$ CLSIZE,PCB_SZPT(%eax)	# page table size
I 6
D 9
	fninit
	pushl	$0x262
	fldcw	0(%esp)
D 7
	popl	%eax
E 6
E 4
#ifdef FPUNOTYET
#endif
E 7
I 7
	popl	%ecx
	fnsave	PCB_SAVEFPU(%eax)
E 9
I 9
D 11
	# fninit
	# pushl	$0x262
	# fldcw	0(%esp)
	# popl	%ecx
	# fnsave	PCB_SAVEFPU(%eax)
E 11
E 9
	movl	%edi,PCB_CR3(%eax)
E 7
	pushl	%edi	# cr3
	movl	%esi,%eax
D 4
	# addl	$(UPAGES*NBPG)+NBPG+NBPG+NBPG,%esi
E 4
	addl	$(UPAGES*NBPG)+NBPG+NBPG+NBPG,%eax
D 4
	shrl	$PGSHIFT,%eax
E 4
I 4
	shrl	$ PGSHIFT,%eax
E 4
	pushl	%eax	# firstaddr

D 4
	pushl	$20		# install sigtrampoline code
E 4
I 4
	pushl	$20		# install signal trampoline code
E 4
	pushl	$_u+PCB_SIGC
	pushl	$sigcode
	call	_bcopy
	addl	$12,%esp

E 14
I 14
	
	movl	$0,_PTD
E 14
E 2
	call 	_main
I 27
	popl	%esi
E 27
I 14
D 20
	popl	%esi
E 20
E 14
D 2
	movw	$0x1234,%ax
	movw	%ax,0x472	# warm boot
E 2
I 2

	.globl	__ucodesel,__udatasel
	movzwl	__ucodesel,%eax
	movzwl	__udatasel,%ecx
	# build outer stack frame
D 4
	pushl	%ecx	# user ss
	# pushl	$0xfdffcffc # user esp
	pushl	$0xfdffd000 # user esp
E 4
I 4
	pushl	%ecx		# user ss
D 15
	pushl	$_u	# user esp
E 4
	pushl	%eax	# user cs
	pushl	$0	# user ip
E 15
I 15
	pushl	$ USRSTACK	# user esp
	pushl	%eax		# user cs
	pushl	$0		# user ip
E 15
	movw	%cx,%ds
	movw	%cx,%es
I 4
D 14
	movw	%ax,%fs		# double map cs to fs
	movw	%cx,%gs		# and ds to gs
E 14
I 14
D 27
	# movw	%ax,%fs		# double map cs to fs
	# movw	%cx,%gs		# and ds to gs
E 27
I 27
	movw	%ax,%fs		# double map cs to fs
	movw	%cx,%gs		# and ds to gs
E 27
E 14
E 4
	lret	# goto user!
D 4
# pushal; pushl %edx; pushl $lr; call _pg; popl %eax ; popl %eax; popal ; .data ; lr: .asciz "lret %x" ; .text
E 4

I 14
	pushl	$lretmsg1	/* "should never get here!" */
	call	_panic
lretmsg1:
	.asciz	"lret: toinit\n"

E 14
D 27
	.globl	__exit
__exit:
I 7
	call _reset_cpu
E 7
E 2
D 4
	lidt	xaxa
	movl	$0,%esp		# segment violation
E 4
I 4
D 13
	lidt	xaxa		# invalidate interrupt descriptor
	movl	$0,%esp		# hardware "freeze" fault
E 4
	ret
xaxa:	.long	0,0
E 13
I 13
	/* NOTREACHED */
E 27
E 13
I 4

E 4
I 2
D 16
	.set	exec,11
E 16
I 16
	.set	exec,59
E 16
	.set	exit,1
	.globl	_icode
D 15
	.globl	_initflags
E 15
	.globl	_szicode
D 16
/* gas fucks up offset -- */
E 16
I 16

E 16
#define	LCALL(x,y)	.byte 0x9a ; .long y; .word x
/*
 * Icode is copied out to process 1 to exec /etc/init.
 * If the exec fails, process 1 exits.
 */
_icode:
I 25
D 27
	pushl	$0 /* environment */

E 27
E 25
D 13
	# pushl	$argv-_icode
E 13
I 13
	# pushl	$argv-_icode	# gas fucks up again
E 13
	movl	$argv,%eax
	subl	$_icode,%eax
	pushl	%eax
E 2

I 2
	# pushl	$init-_icode
	movl	$init,%eax
	subl	$_icode,%eax
	pushl	%eax
	pushl	%eax	# dummy out rta

	movl	%esp,%ebp
	movl	$exec,%eax
	LCALL(0x7,0x0)
	pushl	%eax
	movl	$exit,%eax
	pushl	%eax	# dummy out rta
	LCALL(0x7,0x0)

D 4
# init:	.asciz	"/sbin/init"
E 4
D 11
init:	.asciz	"/etc/init"
E 11
I 11
D 15
init:	.asciz	"/sbin/init"
E 15
I 15
init:
	.asciz	"/sbin/init"
E 15
E 11
	.align	2
D 15
_initflags:
E 15
I 15
argv:
	.long	init+6-_icode		# argv[0] = "init" ("/sbin/init" + 6)
	.long	eicode-_icode		# argv[1] follows icode after copyout
E 15
	.long	0
D 15
argv:	.long	init-_icode
	.long	_initflags-_icode
	.long	0
E 15
I 15
eicode:

E 15
_szicode:
	.long	_szicode-_icode
D 14
sigcode:
E 14
I 14

	.globl	_sigcode,_szsigcode
_sigcode:
E 14
	movl	12(%esp),%eax	# unsure if call will dec stack 1st
	call	%eax
	xorl	%eax,%eax	# smaller movl $103,%eax
	movb	$103,%al	# sigreturn()
	LCALL(0x7,0)		# enter kernel with args on stack
	hlt			# never gets here

I 14
_szsigcode:
	.long	_szsigcode-_sigcode
E 14
E 2
D 4
#ifdef	newway
E 4

I 27
	/*
	 * Support routines for GCC
	 */
E 27
D 4
#define	P(x)	(x-SYSTEM)
#define	PTE(b,o,p) \
		# build a pte pointing to physical p; leave it at loc b+o \	
		movl	p,%eax \
		andl	$0xfffff000,%eax \
		orl	$PG_V,%eax \
		movl	%eax,b(,o,4)

#define	PDE(d, v, p) \
		# build a pde at virtual addr v, pointing to physical pte p \
		movl	v,%edx			\
		andl	$0xffc00000,%edx	\
		shrl	$PGSHIFT+IDXSHFT,%edx	\
		PTE(d, %edx, p)

/* Initialize Sysmap */

	movl	$Syssize,%ecx	# this many pte s
	xorl	%ebx,%ebx	# starting at physical 0
	xorl	%edx,%edx	# starting at virtual XX000000
1:
	PTE(P(SysMap,%edx,%ebx)
	incl	%edx
	addl	$PGSIZE,%edx
	loop 1b

/* Initialize Proc 0 page table  map */
/* Initialize Udot map */

	movl	$UPAGES,%ecx	# this many pte s
	movl	$P(_end),%ebx
	addl	$PGSIZE-1,%ebx
	andl	$PGMASK,%ebx
	xorl	%ebx,%ebx	# starting at physical 0
	movl	$_u,%edx	# starting at virtual _u
1:
	PTE(P(SysMap,%edx,%ebx)
	incl	%edx
	addl	$PGSIZE,%edx
	loop 1b

/* Initialize page table directory */
	zero all entries
	PTD(P(_ptd), 0, P(SysMap))	# bottom double mapped to system
	PTD(P(_ptd), SYSTEM, P(SysMap))	# system location
	PTD(P(_ptd), _u, P(_end))	# udot&ptd

9:
/* clear memory from kernel bss and pages for proc 0 u. and page table */
D 2
	lea	_edata-SYSTEM,r6
	lea	_end-SYSTEM,r5
	bisl3	$SYSTEM,r5,r9			# convert to virtual address
	addl2	$NBPG-1,r9			# roundup to next page
	addl2	$(UPAGES*NBPG)+NBPG+NBPG,r5
1:	clrq	(r6); acbl r5,$8,r6,1b
/* initialize system page table: uba vectors and int stack writeable */
	clrl	r2
	movab	eintstack,r1; bbcc $31,r1,1f;
1:	bisl3	$PG_V|PG_KW,r2,_Sysmap[r2]; aoblss r1,r2,1b
/* make kernel text space read-only */
	movab	_etext+NBPG-1,r1; bbcc $31,r1,1f;
1:	bisl3	$PG_V|PG_URKR,r2,_Sysmap[r2]; aoblss r1,r2,1b
/* make kernel data, bss, read-write */
	bicl3	$SYSTEM,r9,r1; ashl $-PGSHIFT,r1,r1
1:	bisl3	$PG_V|PG_KW,r2,_Sysmap[r2]; aoblss r1,r2,1b
/* now go to mapped mode */
	mtpr	$0,$TBIA; mtpr $1,$MAPEN; jmp *$0f; 0:
/* init mem sizes */
	ashl	$-PGSHIFT,r7,_maxmem
	movl	_maxmem,_physmem
	movl	_maxmem,_freemem
/* setup context for proc[0] == Scheduler */
	bicl3	$SYSTEM|(NBPG-1),r9,r6	# make phys, page boundary
/* setup page table for proc[0] */
	ashl	$-PGSHIFT,r6,r3			# r3 = btoc(r6)
	bisl3	$PG_V|PG_KW,r3,_Usrptmap	# init first upt entry
	incl	r3
	movab	_usrpt,r0
	mtpr	r0,$TBIS
/* init p0br, p0lr */
	mtpr	r0,$P0BR
	mtpr	$0,$P0LR
/* double map the kernel into the virtual user addresses of phys mem */
	mtpr	$_Sysmap,$P0BR
	mtpr	$_Syssize,$P0LR
/* init p1br, p1lr */
	movab	NBPG(r0),r0
	movl	$0x200000-UPAGES,r1
	mtpr	r1,$P1LR
	mnegl	r1,r1
	moval	-4*UPAGES(r0)[r1],r2
	mtpr	r2,$P1BR
/* setup mapping for UPAGES of _u */
	movl	$UPAGES,r2; movab _u+NBPG*UPAGES,r1; addl2 $UPAGES,r3; jbr 2f
1:	decl	r3
	moval	-NBPG(r1),r1;
	bisl3	$PG_V|PG_URKW,r3,-(r0)
	mtpr	r1,$TBIS
2:	sobgeq	r2,1b
/* initialize (slightly) the pcb */
	movab	UPAGES*NBPG(r1),PCB_KSP(r1)
	mnegl	$1,PCB_ESP(r1)
	mnegl	$1,PCB_SSP(r1)
	movl	r1,PCB_USP(r1)
	mfpr	$P0BR,PCB_P0BR(r1)
	mfpr	$P0LR,PCB_P0LR(r1)
	movb	$4,PCB_P0LR+3(r1)		# disable ast
	mfpr	$P1BR,PCB_P1BR(r1)
	mfpr	$P1LR,PCB_P1LR(r1)
	movl	$CLSIZE,PCB_SZPT(r1)		# init u.u_pcb.pcb_szpt
	movl	r9,PCB_R9(r1)
	movl	r10,PCB_R10(r1)
	movl	r11,PCB_R11(r1)
	movab	1f,PCB_PC(r1)			# initial pc
	clrl	PCB_PSL(r1)			# mode(k,k), ipl=0
	ashl	$PGSHIFT,r3,r3
	mtpr	r3,$PCBB			# first pcbb
/* set regs, p0br, p0lr, p1br, p1lr, astlvl, ksp and change to kernel mode */
	ldpctx
	rei
/* put signal trampoline code in u. area */
1:	movab	_u,r0
	movc3	$19,sigcode,PCB_SIGC(r0)
/* save boot device in global _bootdev */
	movl	r10,_bootdev
/* save reboot flags in global _boothowto */
	movl	r11,_boothowto
#ifdef KADB
/* save end of symbol & string table in global _bootesym */
	subl3	$NBPG-1,r9,_bootesym
#endif
/* calculate firstaddr, and call main() */
	bicl3	$SYSTEM,r9,r0; ashl $-PGSHIFT,r0,-(sp)
	addl2	$UPAGES+1,(sp); calls $1,_main
/* proc[1] == /etc/init now running here; run icode */
	pushl	$PSL_CURMOD|PSL_PRVMOD; pushl $0; rei
E 2
I 2
#endif newway
E 2

E 4
D 2
/* signal trampoline code: it is known that this code takes exactly 19 bytes */
/* in ../vax/pcb.h and in the movc3 above */
sigcode:
	calls	$4,8(pc)	# params pushed by sendsig
	movl	sp,ap		# calls frame built by sendsig
	chmk	$103		# cleanup mask and onsigstack
	halt			# sigreturn() does not return!
	.word	0x3f		# registers 0-5
	callg	(ap),*16(ap)	# call the signal handler
	ret			# return to code above
E 2
I 2
	.globl ___udivsi3
I 27
	ALIGN32
E 27
___udivsi3:
	movl 4(%esp),%eax
	xorl %edx,%edx
	divl 8(%esp)
	ret
E 2

D 2
	.set	exec,11
	.set	exit,1
	.globl	_icode
	.globl	_initflags
	.globl	_szicode
/*
 * Icode is copied out to process 1 to exec /etc/init.
 * If the exec fails, process 1 exits.
 */
_icode:
	pushab	b`argv-l0(pc)
l0:	pushab	b`init-l1(pc)
l1:	pushl	$2
	movl	sp,ap
	chmk	$exec
	pushl	r0
	chmk	$exit
E 2
I 2
	.globl ___divsi3
I 27
	ALIGN32
E 27
___divsi3:
	movl 4(%esp),%eax
D 27
	xorl %edx,%edx
E 27
I 27
	#xorl %edx,%edx		/* not needed - cltd sign extends into %edx */
E 27
	cltd
	idivl 8(%esp)
	ret
E 2

I 27
	/*
	 * I/O bus instructions via C
	 */
E 27
D 2
init:	.asciz	"/sbin/init"
	.align	2
_initflags:
	.long	0
argv:	.long	init+6-_icode
	.long	_initflags-_icode
	.long	0
_szicode:
	.long	_szicode-_icode
E 2
I 2
	.globl	_inb
I 27
	ALIGN32
E 27
_inb:	movl	4(%esp),%edx
I 13
D 14
	inb	$0x84,%al	# Compaq SystemPro 
E 14
I 14
D 27
	# inb	$0x84,%al	# Compaq SystemPro 
E 27
E 14
E 13
	subl	%eax,%eax	# clr eax
D 3
	nop
E 3
I 3
	NOP
E 3
	inb	%dx,%al
I 27
	ret


	.globl	_inw
	ALIGN32
_inw:	movl	4(%esp),%edx
	subl	%eax,%eax	# clr eax
E 27
D 3
	nop
E 3
I 3
	NOP
I 27
	inw	%dx,%ax
E 27
E 3
	ret
E 2

I 14

	.globl	_rtcin
I 27
	ALIGN32
E 27
_rtcin:	movl	4(%esp),%eax
	outb	%al,$0x70
	subl	%eax,%eax	# clr eax
	inb	$0x71,%al	# Compaq SystemPro 
	ret

E 14
D 2
/*
 * Primitives
 */ 
E 2
I 2
	.globl	_outb
I 27
	ALIGN32
E 27
_outb:	movl	4(%esp),%edx
D 27
	movl	8(%esp),%eax
E 27
D 3
	nop
E 3
I 3
	NOP
I 27
	movl	8(%esp),%eax
E 27
E 3
	outb	%al,%dx
I 13
D 14
	inb	$0x84,%al
E 14
I 14
D 27
	# inb	$0x84,%al
E 27
E 14
E 13
D 3
	nop
E 3
I 3
	NOP
E 3
	ret
E 2

D 2
#ifdef GPROF
#define	ENTRY(name, regs) \
	.globl _##name; .align 1; _##name: .word regs; jsb mcount
#else
#define	ENTRY(name, regs) \
	.globl _##name; .align 1; _##name: .word regs
#endif GPROF
#define R0 0x01
#define R1 0x02
#define R2 0x04
#define R3 0x08
#define R4 0x10
#define R5 0x20
#define R6 0x40
E 2
I 2
D 27
	#
	# bzero (base,cnt)
	#
E 27
I 27
	.globl	_outw
	ALIGN32
_outw:	movl	4(%esp),%edx
	NOP
	movl	8(%esp),%eax
	outw	%ax,%dx
	NOP
	ret
E 27
E 2

I 27
	/*
	 * void bzero(void *base, u_int cnt)
	 */

E 27
D 2
/*
 * badaddr(addr, len)
 *	see if access addr with a len type instruction causes a machine check
 *	len is length of access (1=byte, 2=short, 4=long)
 */
	.globl	_badaddr
_badaddr:
	.word	0
	movl	$1,r0
	mfpr	$IPL,r1
	mtpr	$HIGH,$IPL
	movl	4(ap),r3
	movl	8(ap),r4
	movab	2f,nofault		# jump to 2f on machcheck
	bbc	$0,r4,1f; tstb	(r3)
1:	bbc	$1,r4,1f; tstw	(r3)
1:	bbc	$2,r4,1f; tstl	(r3)
1:	clrl	r0			# made it w/o machine checks
2:	clrl	nofault
	mtpr	r1,$IPL
E 2
I 2
	.globl _bzero
D 27
	.globl _blkclr
E 27
I 27
	ALIGN32
E 27
_bzero:
D 27
_blkclr:
E 27
	pushl	%edi
	movl	8(%esp),%edi
	movl	12(%esp),%ecx
D 4
	movb	$0x00,%al
E 4
I 4
	xorl	%eax,%eax
	shrl	$2,%ecx	
E 4
	cld
	rep
I 4
	stosl
	movl	12(%esp),%ecx
	andl	$3,%ecx
	rep
E 4
	stosb
	popl	%edi
E 2
	ret

D 2
/*
 * update profiling information for the user
 * addupc(pc, &u.u_prof, ticks)
 */
ENTRY(addupc, 0)
	movl	8(ap),r2		# &u.u_prof
	subl3	8(r2),4(ap),r0		# corrected pc
	blss	9f
	extzv	$1,$31,r0,r0		# logical right shift
	extzv	$1,$31,12(r2),r1	# ditto for scale
	emul	r1,r0,$0,r0
	ashq	$-14,r0,r0
	tstl	r1
	bneq	9f
	bicl2	$1,r0
	cmpl	r0,4(r2)		# length
	bgequ	9f
	addl2	(r2),r0			# base
	probew	$3,$2,(r0)
	beql	8f
	addw2	12(ap),(r0)
9:
E 2
I 2
D 27
	#
I 7
	# fillw (pat,base,cnt)
	#
E 27
I 27
	/*
	 * fillw (pat,base,cnt)
	 */
E 27

	.globl _fillw
I 27
	ALIGN32
E 27
_fillw:
	pushl	%edi
	movl	8(%esp),%eax
	movl	12(%esp),%edi
D 27
	movl	16(%esp),%ecx
E 27
I 27
	movw	%ax, %cx
	rorl	$16, %eax
	movw	%cx, %ax
E 27
D 14
	# xorl	%eax,%eax
E 14
	cld
I 27
	movl	16(%esp),%ecx
	shrl	%ecx
E 27
	rep
I 27
	stosl
	movl	16(%esp),%ecx
	andl	$1, %ecx
	rep
E 27
	stosw
	popl	%edi
	ret

D 27
	#
E 7
	# bcopy (src,dst,cnt)
	# NOTE: does not (yet) handle overlapped copies
	#

	.globl	_bcopy
D 3
	.globl	_copyout
	.globl	_copyin
E 3
_bcopy:
E 27
I 27
	.globl _bcopyb
	ALIGN32
_bcopyb:
E 27
I 3
	pushl	%esi
	pushl	%edi
	movl	12(%esp),%esi
	movl	16(%esp),%edi
	movl	20(%esp),%ecx
D 4
	# shll	$2,%ecx
	# cld
	# rep
	# movsl
	# movl	20(%esp),%ecx
	# andl	$3,%ecx
E 4
I 4
D 27
	shrl	$2,%ecx	
E 27
	cld
E 4
	rep
I 4
D 27
	movsl
	movl	20(%esp),%ecx
	andl	$3,%ecx
	rep
E 27
E 4
	movsb
	popl	%edi
	popl	%esi
	xorl	%eax,%eax
	ret

I 18
D 27
	#
	# ovbcopy (src,dst,cnt)
	# NOTE: does not (yet) work doing words at a time
	#
E 27
I 27
	/*
	 * (ov)bcopy (src,dst,cnt)
	 *  ws@tools.de     (Wolfgang Solfrank, TooLs GmbH) +49-228-985800
	 */
E 27

D 27
	.globl	_ovbcopy
E 27
I 27
	.globl	_bcopy,_ovbcopy
	ALIGN32
E 27
_ovbcopy:
I 27
_bcopy:
E 27
	pushl	%esi
	pushl	%edi
	movl	12(%esp),%esi
	movl	16(%esp),%edi
	movl	20(%esp),%ecx
D 27
	addl	%ecx,%esi	/* copy from end to beginning */
	addl	%ecx,%edi
	decl	%esi
E 27
I 27
	cmpl	%esi,%edi	/* potentially overlapping? */
	jnb	1f
	cld			/* nope, copy forwards. */
	shrl	$2,%ecx		/* copy by words */
	rep
	movsl
	movl	20(%esp),%ecx
	andl	$3,%ecx		/* any bytes left? */
	rep
	movsb
	popl	%edi
	popl	%esi
	xorl	%eax,%eax
	ret
	ALIGN32
1:
	addl	%ecx,%edi	/* copy backwards. */
	addl	%ecx,%esi
	std
	andl	$3,%ecx		/* any fractional bytes? */
E 27
	decl	%edi
D 27
	std			/* decrementing as we go */
E 27
I 27
	decl	%esi
E 27
	rep
	movsb
I 27
	movl	20(%esp),%ecx	/* copy remainder by words */
	shrl	$2,%ecx
	subl	$3,%esi
	subl	$3,%edi
	rep
	movsl
E 27
I 20
	popl	%edi
	popl	%esi
E 20
	xorl	%eax,%eax
	cld
	ret

I 27
#ifdef notdef
	.globl	_copyout
	ALIGN32
_copyout:
	movl	_curpcb, %eax
	movl	$cpyflt, PCB_ONFAULT(%eax) # in case we page/protection violate
	pushl	%esi
	pushl	%edi
	pushl	%ebx
	movl	16(%esp), %esi
	movl	20(%esp), %edi
	movl	24(%esp), %ebx

 				/* first, check to see if "write fault" */
1:	movl	%edi, %eax
#ifdef notyet
	shrl	$IDXSHIFT, %eax	/* fetch pte associated with address */
	andb	$0xfc, %al
	movl	_PTmap(%eax), %eax

	andb	$7, %al		/* if we are the one case that won't trap... */
	cmpb	$5, %al
	jne	2f
				/* ... then simulate the trap! */
	pushl	%edi
	call	_trapwrite	/* trapwrite(addr) */
	popl	%edx

	cmpl	$0, %eax	/* if not ok, return */
	jne	cpyflt
				/* otherwise, continue with reference */
2:
	movl	%edi, %eax	/* calculate remainder this pass */
	andl	$0xfffff000, %eax
	movl	$NBPG, %ecx
	subl	%eax, %ecx
	cmpl	%ecx, %ebx
	jle	3f
	movl	%ebx, %ecx
3:	subl	%ecx, %ebx
	movl	%ecx, %edx
#else
	movl	%ebx, %ecx
	movl	%ebx, %edx
#endif

	shrl	$2,%ecx			/* movem */
	cld
	rep
	movsl
	movl	%edx, %ecx		/* don't depend on ecx here! */
	andl	$3, %ecx
	rep
	movsb

#ifdef notyet
	cmpl	$0, %ebx
	jl	1b
#endif

	popl	%ebx
	popl	%edi
	popl	%esi
	xorl	%eax,%eax
	movl	_curpcb,%edx
	movl	%eax,PCB_ONFAULT(%edx)
	ret

E 27
E 18
D 25
	.globl	_copyout
E 3
_copyout:
I 3
D 16
	movl	$cpyflt,_nofault	# in case we page/protection violate
E 16
I 16
	movl	_curpcb,%eax
	movl	$cpyflt,PCB_ONFAULT(%eax) # in case we page/protection violate
E 16
	pushl	%esi
	pushl	%edi
	movl	12(%esp),%esi
	movl	16(%esp),%edi
	movl	20(%esp),%ecx
D 4
	# shrl	$2,%ecx
E 4
I 4
	shrl	$2,%ecx
E 4
	cld
D 4
	# rep
	# movsl
	# movl	20(%esp),%ecx
	# andl	$3,%ecx
E 4
	rep
I 4
	movsl
	movl	20(%esp),%ecx
	andl	$3,%ecx
	rep
E 4
	movsb
	popl	%edi
	popl	%esi
	xorl	%eax,%eax
D 16
	movl	%eax,_nofault
E 16
I 16
	movl	_curpcb,%edx
	movl	%eax,PCB_ONFAULT(%edx)
E 16
	ret

E 25
	.globl	_copyin
I 27
	ALIGN32
E 27
E 3
_copyin:
I 3
D 16
	movl	$cpyflt,_nofault	# in case we page/protection violate
E 16
I 16
	movl	_curpcb,%eax
	movl	$cpyflt,PCB_ONFAULT(%eax) # in case we page/protection violate
E 16
E 3
	pushl	%esi
	pushl	%edi
I 27
	pushl	%ebx
E 27
	movl	12(%esp),%esi
	movl	16(%esp),%edi
	movl	20(%esp),%ecx
I 27
	shrl	$2,%ecx
	cld
	rep
	movsl
	movl	20(%esp),%ecx
	andl	$3,%ecx
	rep
	movsb
	popl	%ebx
	popl	%edi
	popl	%esi
	xorl	%eax,%eax
	movl	_curpcb,%edx
	movl	%eax,PCB_ONFAULT(%edx)
	ret
E 27
I 25

D 27
	/* if dest >= USRSTACK, return error */
	cmpl	$ USRSTACK, %esi
	jae	cpyflt
E 27
I 27
	ALIGN32
cpyflt:
	popl	%ebx
	popl	%edi
	popl	%esi
	movl	_curpcb,%edx
	movl	$0,PCB_ONFAULT(%edx)
	movl	$ EFAULT,%eax
	ret
#else
	.globl	_copyout
	ALIGN32
_copyout:
	movl	_curpcb,%eax
	movl	$cpyflt,PCB_ONFAULT(%eax) # in case we page/protection violate
	pushl	%esi
	pushl	%edi
	movl	12(%esp),%esi
	movl	16(%esp),%edi
	movl	20(%esp),%ecx
	shrl	$2,%ecx
	cld
	rep
	movsl
	movl	20(%esp),%ecx
	andl	$3,%ecx
	rep
	movsb
	popl	%edi
	popl	%esi
	xorl	%eax,%eax
	movl	_curpcb,%edx
	movl	%eax,PCB_ONFAULT(%edx)
	ret
E 27

D 27
	/* if USRSTACK-dest < len, return error */
	movl	$ USRSTACK, %eax
	subl	%esi, %eax
	cmpl	%ecx, %eax
	jb	cpyflt

E 27
I 27
	.globl	_copyin
	ALIGN32
_copyin:
	movl	_curpcb,%eax
	movl	$cpyflt,PCB_ONFAULT(%eax) # in case we page/protection violate
	pushl	%esi
	pushl	%edi
	movl	12(%esp),%esi
	movl	16(%esp),%edi
	movl	20(%esp),%ecx
E 27
E 25
I 3
D 4
	# shrl	$2,%ecx
E 4
I 4
	shrl	$2,%ecx
E 4
E 3
	cld
I 3
D 4
	# rep
	# movsl
	# movl	20(%esp),%ecx
	# andl	$3,%ecx
E 4
E 3
	rep
I 4
	movsl
	movl	20(%esp),%ecx
	andl	$3,%ecx
	rep
E 4
	movsb
	popl	%edi
	popl	%esi
D 3
	movl	%ecx,%eax
E 3
I 3
	xorl	%eax,%eax
D 16
	movl	%eax,_nofault
E 16
I 16
	movl	_curpcb,%edx
	movl	%eax,PCB_ONFAULT(%edx)
E 16
E 3
E 2
	ret
D 2
8:
	clrl	12(r2)
E 2
I 2

I 27
	ALIGN32
E 27
I 3
cpyflt: popl	%edi
	popl	%esi
D 16
	xorl	%eax,%eax
	movl	%eax,_nofault
E 16
I 16
	movl	_curpcb,%edx
	movl	$0,PCB_ONFAULT(%edx)
E 16
D 4
	movl	$EFAULT,%eax
E 4
I 4
	movl	$ EFAULT,%eax
E 4
	ret

I 27
#endif

E 27
I 7
	# insb(port,addr,cnt)
	.globl	_insb
I 27
	ALIGN32
E 27
_insb:
	pushl	%edi
	movw	8(%esp),%dx
	movl	12(%esp),%edi
	movl	16(%esp),%ecx
	cld
	NOP
	rep
	insb
	NOP
	movl	%edi,%eax
	popl	%edi
	ret
E 7

E 3
	# insw(port,addr,cnt)
	.globl	_insw
I 27
	ALIGN32
E 27
_insw:
	pushl	%edi
	movw	8(%esp),%dx
	movl	12(%esp),%edi
	movl	16(%esp),%ecx
	cld
D 3
	nop
E 3
I 3
	NOP
E 3
	.byte 0x66,0xf2,0x6d	# rep insw
D 3
	nop
E 3
I 3
	NOP
E 3
	movl	%edi,%eax
	popl	%edi
E 2
	ret

D 2
/*
 * Copy a null terminated string from the user address space into
 * the kernel address space.
 *
 * copyinstr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copyinstr, R6)
	movl	12(ap),r6		# r6 = max length
	jlss	8f
	movl	4(ap),r1		# r1 = user address
	bicl3	$~(NBPG*CLSIZE-1),r1,r2	# r2 = bytes on first page
	subl3	r2,$NBPG*CLSIZE,r2
	movl	8(ap),r3		# r3 = kernel address
1:
	cmpl	r6,r2			# r2 = min(bytes on page, length left);
	jgeq	2f
	movl	r6,r2
2:
	prober	$3,r2,(r1)		# bytes accessible?
	jeql	8f
	subl2	r2,r6			# update bytes left count
#ifdef NOSUBSINST
	# fake the locc instr. for processors that don t have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3f
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3f
#endif
	subl2	r2,r1			# back up pointer updated by `locc 
	movc3	r2,(r1),(r3)		# copy in next piece
	movl	$(NBPG*CLSIZE),r2	# check next page
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9f
3:
	tstl	16(ap)			# return length?
	beql	4f
	subl3	r6,12(ap),r6		# actual len = maxlen - unused pages
	subl2	r0,r6			#	- unused on this page
	addl3	$1,r6,*16(ap)		#	+ the null byte
4:
	subl2	r0,r2			# r2 = number of bytes to move
	subl2	r2,r1			# back up pointer updated by `locc 
	incl	r2			# copy null byte as well
	movc3	r2,(r1),(r3)		# copy in last piece
	clrl	r0			# redundant
E 2
I 2
	# outsw(port,addr,cnt)
	.globl	_outsw
I 27
	ALIGN32
E 27
_outsw:
	pushl	%esi
	movw	8(%esp),%dx
	movl	12(%esp),%esi
	movl	16(%esp),%ecx
	cld
D 3
	nop
E 3
I 3
	NOP
E 3
	.byte 0x66,0xf2,0x6f	# rep outsw
D 3
	nop
E 3
I 3
	NOP
E 3
	movl	%esi,%eax
	popl	%esi
E 2
	ret
D 2
8:
	movl	$EFAULT,r0
9:
	tstl	16(ap)
	beql	1f
	subl3	r6,12(ap),*16(ap)
1:
	ret
E 2

D 2
/*
 * Copy a null terminated string from the kernel
 * address space to the user address space.
 *
 * copyoutstr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copyoutstr, R6)
	movl	12(ap),r6		# r6 = max length
	jlss	8b
	movl	4(ap),r1		# r1 = kernel address
	movl	8(ap),r3		# r3 = user address
	bicl3	$~(NBPG*CLSIZE-1),r3,r2	# r2 = bytes on first page
	subl3	r2,$NBPG*CLSIZE,r2
1:
	cmpl	r6,r2			# r2 = min(bytes on page, length left);
	jgeq	2f
	movl	r6,r2
2:
	probew	$3,r2,(r3)		# bytes accessible?
	jeql	8b
	subl2	r2,r6			# update bytes left count
#ifdef NOSUBSINST
	# fake the locc instr. for processors that don t have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3b
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3b
#endif
	subl2	r2,r1			# back up pointer updated by `locc 
	movc3	r2,(r1),(r3)		# copy in next piece
	movl	$(NBPG*CLSIZE),r2	# check next page
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9b
E 2
I 2
D 27
	# lgdt(*gdt, ngdt)
E 27
I 27
	# outsb(port,addr,cnt)
	.globl	_outsb
	ALIGN32
_outsb:
	pushl	%esi
	movw	8(%esp),%dx
	movl	12(%esp),%esi
	movl	16(%esp),%ecx
	cld
	NOP
	rep
	outsb
	NOP
	movl	%esi,%eax
	popl	%esi
	ret

	/*
	 * void lgdt(struct region_descriptor *rdp);
	 */
E 27
	.globl	_lgdt
D 27
	# .globl	_gdt
xxx:	.word 31
	.long 0
E 27
I 27
	ALIGN32
E 27
_lgdt:
I 27
	/* reload the descriptor table */
E 27
	movl	4(%esp),%eax
D 27
	movl	%eax,xxx+2
	movl	8(%esp),%eax
	movw	%ax,xxx
	lgdt	xxx
E 27
I 27
	lgdt	(%eax)
	/* flush the prefetch q */
E 27
	jmp	1f
D 3
	nop
E 3
I 3
D 27
	NOP
E 3
1:	movw	$0x10,%ax
E 27
I 27
	nop
1:
	/* reload "stale" selectors */
	# movw	$KDSEL,%ax
	movw	$0x10,%ax
E 27
	movw	%ax,%ds
	movw	%ax,%es
	movw	%ax,%ss
I 27

	/* reload code selector by turning return into intersegmental return */
E 27
	movl	0(%esp),%eax
	pushl	%eax
I 27
	# movl	$KCSEL,4(%esp)
E 27
	movl	$8,4(%esp)
	lret
E 2

D 2
/*
 * Copy a null terminated string from one point to another in
 * the kernel address space.
 *
 * copystr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copystr, R6)
	movl	12(ap),r6		# r6 = max length
	jlss	8b
	movl	4(ap),r1		# r1 = src address
	movl	8(ap),r3		# r3 = dest address
1:
	movzwl	$65535,r2		# r2 = bytes in first chunk
	cmpl	r6,r2			# r2 = min(bytes in chunk, length left);
	jgeq	2f
	movl	r6,r2
2:
	subl2	r2,r6			# update bytes left count
#ifdef NOSUBSINST
	# fake the locc instr. for processors that don t have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3b
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3b
#endif
	subl2	r2,r1			# back up pointer updated by `locc 
	movc3	r2,(r1),(r3)		# copy in next piece
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9b
E 2
I 2
D 27
	# lidt(*idt, nidt)
E 27
I 27
	/*
	 * void lidt(struct region_descriptor *rdp);
	 */
E 27
	.globl	_lidt
D 4
	# .globl	_idt
E 4
D 27
yyy:	.word	255
D 4
	.long	0 # _idt
E 4
I 4
	.long	0 
E 27
I 27
	ALIGN32
E 27
E 4
_lidt:
	movl	4(%esp),%eax
D 27
	movl	%eax,yyy+2
	movl	8(%esp),%eax
	movw	%ax,yyy
	lidt	yyy
E 27
I 27
	lidt	(%eax)
E 27
	ret
E 2

D 2
/* 
 * Copy specified amount of data from user space into the kernel
 * Copyin(from, to, len)
 *	r1 == from (user source address)
 *	r3 == to (kernel destination address)
 *	r5 == length
 */
	.align	1
JSBENTRY(Copyin, R1|R3|R5)
	cmpl	r5,$(NBPG*CLSIZE)	# probing one page or less ?
	bgtru	1f			# no
	prober	$3,r5,(r1)		# bytes accessible ?
	beql	ersb			# no
	movc3	r5,(r1),(r3)
/*	clrl	r0			# redundant */
	rsb
1:
	blss	ersb			# negative length?
	pushl	r6			# r6 = length
	movl	r5,r6
	bicl3	$~(NBPG*CLSIZE-1),r1,r0	# r0 = bytes on first page
	subl3	r0,$(NBPG*CLSIZE),r0
	addl2	$(NBPG*CLSIZE),r0	# plus one additional full page
	jbr	2f
E 2
I 2
D 27
	# lldt(sel)
E 27
I 27
	/*
	 * void lldt(u_short sel)
	 */
E 27
	.globl	_lldt
I 27
	ALIGN32
E 27
_lldt:
D 27
	movl	4(%esp),%eax
	lldt	%eax
E 27
I 27
	lldt	4(%esp)
E 27
	ret
E 2

D 2
ciloop:
	movc3	r0,(r1),(r3)
	movl	$(2*NBPG*CLSIZE),r0	# next amount to move
2:
	cmpl	r0,r6
	bleq	3f
	movl	r6,r0
3:
	prober	$3,r0,(r1)		# bytes accessible ?
	beql	ersb1			# no
	subl2	r0,r6			# last move?
	bneq	ciloop			# no
E 2
I 2
D 27
	# ltr(sel)
E 27
I 27
	/*
	 * void ltr(u_short sel)
	 */
E 27
	.globl	_ltr
I 27
	ALIGN32
E 27
_ltr:
D 27
	movl	4(%esp),%eax
	ltr	%eax
E 27
I 27
	ltr	4(%esp)
E 27
	ret
E 2

D 2
	movc3	r0,(r1),(r3)
/*	clrl	r0			# redundant */
	movl	(sp)+,r6		# restore r6
	rsb
E 2
I 2
D 27
	# lcr3(cr3)
E 27
I 27
	/*
	 * void lcr3(caddr_t cr3)
	 */
E 27
	.globl	_lcr3
	.globl	_load_cr3
I 27
	ALIGN32
E 27
_load_cr3:
_lcr3:
I 14
	inb	$0x84,%al	# check wristwatch
E 14
	movl	4(%esp),%eax
I 14
D 16
	pushfl
	popl %ecx
	cli
	movl	%esp,%edx
	movl	$tmpstk,%esp
E 16
E 14
I 4
D 7
 # orl $0x80000000,%eax
E 7
I 7
D 8
 	# orl	$0x80000000,%eax
E 8
I 8
 	orl	$ I386_CR3PAT,%eax
I 20
D 27

	movl	$tmpstk2,%edx
	movl	(%edx),%ecx	# touch stack, fault if not there
	movl	%ecx,(%edx)
	movl	%esp,%ecx
	movl	%edx,%esp

E 27
E 20
E 8
E 7
E 4
	movl	%eax,%cr3
I 14
D 16
	movl	(%edx),%eax	# touch stack
	movl	%eax,(%edx)
	movl	%edx,%esp
E 16
E 14
D 19
	movl	%cr3,%eax
E 19
I 19
	inb	$0x84,%al	# check wristwatch
I 20
D 27

	movl	(%ecx),%edx	# touch stack, fault if not there
	movl	%edx,(%ecx)
	movl	%ecx,%esp
E 27
E 20
E 19
I 14
D 16
	pushl %ecx
	popfl		# turns ints on again
E 16
E 14
	ret
E 2

I 15
	# tlbflush()
	.globl	_tlbflush
I 27
	ALIGN32
E 27
_tlbflush:
	inb	$0x84,%al	# check wristwatch
D 16
	pushfl
	popl %ecx
	cli
	movl	%esp,%edx
	movl	$tmpstk,%esp
E 16
	movl	%cr3,%eax
 	orl	$ I386_CR3PAT,%eax
I 20
D 27

	movl	$tmpstk2,%edx
	movl	(%edx),%ecx	# touch stack, fault if not there
	movl	%ecx,(%edx)
	movl	%esp,%ecx
	movl	%edx,%esp

E 27
E 20
	movl	%eax,%cr3
D 16
	movl	(%edx),%eax	# touch stack
	movl	%eax,(%edx)
	movl	%edx,%esp
	movl	%cr3,%eax
	pushl %ecx
	popfl		# turns ints on again
E 16
I 16
	inb	$0x84,%al	# check wristwatch
I 20
D 27

	movl	(%ecx),%edx	# touch stack, fault if not there
	movl	%edx,(%ecx)
	movl	%ecx,%esp
E 27
E 20
E 16
	ret

E 15
D 2
ersb1:
	movl	(sp)+,r6		# restore r6
ersb:
	movl	$EFAULT,r0
	rsb
E 2
I 2
	# lcr0(cr0)
D 13
	.globl	_lcr0
E 13
I 13
	.globl	_lcr0,_load_cr0
I 27
	ALIGN32
E 27
E 13
_lcr0:
I 13
_load_cr0:
E 13
	movl	4(%esp),%eax
	movl	%eax,%cr0
	ret
E 2

D 2
/* 
 * Copy specified amount of data from kernel to the user space
 * Copyout(from, to, len)
 *	r1 == from (kernel source address)
 *	r3 == to (user destination address)
 *	r5 == length
 */
	.align	1
JSBENTRY(Copyout, R1|R3|R5)
	cmpl	r5,$(NBPG*CLSIZE)	# moving one page or less ?
	bgtru	1f			# no
	probew	$3,r5,(r3)		# bytes writeable?
	beql	ersb			# no
	movc3	r5,(r1),(r3)
/*	clrl	r0			# redundant */
	rsb
1:
	blss	ersb			# negative length?
	pushl	r6			# r6 = length
	movl	r5,r6
	bicl3	$~(NBPG*CLSIZE-1),r3,r0	# r0 = bytes on first page
	subl3	r0,$(NBPG*CLSIZE),r0
	addl2	$(NBPG*CLSIZE),r0	# plus one additional full page
	jbr	2f
E 2
I 2
	# rcr0()
	.globl	_rcr0
I 27
	ALIGN32
E 27
_rcr0:
	movl	%cr0,%eax
	ret
E 2

D 2
coloop:
	movc3	r0,(r1),(r3)
	movl	$(2*NBPG*CLSIZE),r0	# next amount to move
2:
	cmpl	r0,r6
	bleq	3f
	movl	r6,r0
3:
	probew	$3,r0,(r3)		# bytes writeable?
	beql	ersb1			# no
	subl2	r0,r6			# last move?
	bneq	coloop			# no
E 2
I 2
	# rcr2()
	.globl	_rcr2
I 27
	ALIGN32
E 27
_rcr2:
	movl	%cr2,%eax
	ret
E 2

D 2
	movc3	r0,(r1),(r3)
/*	clrl	r0			# redundant */
	movl	(sp)+,r6		# restore r6
	rsb
E 2
I 2
	# rcr3()
	.globl	_rcr3
	.globl	__cr3
I 27
	ALIGN32
E 27
__cr3:
_rcr3:
	movl	%cr3,%eax
	ret
E 2

D 2
/*
 * non-local goto s
 */
#ifdef notdef		/* this is now expanded completely inline */
	.align	1
JSBENTRY(Setjmp, R0)
	movl	fp,(r0)+	# current stack frame
	movl	(sp),(r0)	# resuming pc
	clrl	r0
	rsb
#endif
E 2
I 2
	# ssdtosd(*ssdp,*sdp)
	.globl	_ssdtosd
I 27
	ALIGN32
E 27
_ssdtosd:
	pushl	%ebx
	movl	8(%esp),%ecx
	movl	8(%ecx),%ebx
	shll	$16,%ebx
	movl	(%ecx),%edx
	roll	$16,%edx
	movb	%dh,%bl
	movb	%dl,%bh
	rorl	$8,%ebx
	movl	4(%ecx),%eax
	movw	%ax,%dx
	andl	$0xf0000,%eax
	orl	%eax,%ebx
	movl	12(%esp),%ecx
	movl	%edx,(%ecx)
	movl	%ebx,4(%ecx)
	popl	%ebx
	ret
E 2

D 2
#define PCLOC 16	/* location of pc in calls frame */
#define APLOC 8		/* location of ap,fp in calls frame */
	.align	1
JSBENTRY(Longjmp, R0)
	movl	(r0)+,newfp	# must save parameters in memory as all
	movl	(r0),newpc	# registers may be clobbered.
1:
	cmpl	fp,newfp	# are we there yet?
	bgequ	2f		# yes
	moval	1b,PCLOC(fp)	# redirect return pc to us!
	ret			# pop next frame
2:
	beql	3f		# did we miss our frame?
	pushab	4f		# yep ?!?
	calls	$1,_panic
3:
	movl	newpc,r0	# all done, just return to the `setjmp 
	jmp	(r0)		# rsb

	.data
newpc:	.space	4
newfp:	.space	4
4:	.asciz	"longjmp"
	.text
E 2
/*
D 2
 * setjmp that saves all registers as the call frame may not
 * be available to recover them in the usual mannor by longjmp.
 * Called before swapping out the u. area, restored by resume()
 * below.
E 2
I 2
D 4
 * {fu,su},{byte,sword,word}
E 4
I 4
 * {fu,su},{byte,word}
E 4
E 2
 */
I 27
	ALIGN32
E 27
D 2
ENTRY(savectx, 0)
	movl	4(ap),r0
	movq	r6,(r0)+
	movq	r8,(r0)+
	movq	r10,(r0)+
	movq	APLOC(fp),(r0)+	# save ap, fp
	addl3	$8,ap,(r0)+	# save sp
	movl	PCLOC(fp),(r0)	# save pc
	clrl	r0
E 2
I 2
ALTENTRY(fuiword)
ENTRY(fuword)
D 16
	movl	$fusufault,_nofault	# in case we page/protection violate
E 16
I 16
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx)
E 16
	movl	4(%esp),%edx
I 25
D 27

	cmpl	$ USRSTACK - 3, %edx
	jae	fusufault

E 25
I 4
D 14
	.byte	0x65		# use gs
E 14
I 14
	# .byte	0x65		# use gs
E 27
I 27
	.byte	0x65		# use gs
E 27
E 14
E 4
	movl	0(%edx),%eax
D 16
	xorl	%edx,%edx
	movl	%edx,_nofault
E 16
I 16
	movl	$0,PCB_ONFAULT(%ecx)
E 16
E 2
	ret
I 2
	
I 27
	ALIGN32
ENTRY(fusword)
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
	movl	4(%esp),%edx
	.byte	0x65		# use gs
	movzwl	0(%edx),%eax
	movl	$0,PCB_ONFAULT(%ecx)
	ret
	
	ALIGN32
E 27
D 25
ENTRY(fusword)
D 16
	movl	$fusufault,_nofault	# in case we page/protection violate
E 16
I 16
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 16
	movl	4(%esp),%edx
I 4
D 14
	.byte	0x65		# use gs
E 14
I 14
	# .byte	0x65		# use gs
E 14
E 4
	movzwl	0(%edx),%eax
D 16
	xorl	%edx,%edx
	movl	%edx,_nofault
E 16
I 16
	movl	$0,PCB_ONFAULT(%ecx)
E 16
	ret
	
E 25
ALTENTRY(fuibyte)
ENTRY(fubyte)
D 16
	movl	$fusufault,_nofault	# in case we page/protection violate
E 16
I 16
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 16
	movl	4(%esp),%edx
I 25
D 27

	cmpl	$ USRSTACK, %edx
	jae	fusufault

E 25
I 4
D 14
	.byte	0x65		# use gs
E 14
I 14
	# .byte	0x65		# use gs
E 27
I 27
	.byte	0x65		# use gs
E 27
E 14
E 4
	movzbl	0(%edx),%eax
D 16
	xorl	%edx,%edx
	movl	%edx,_nofault
E 16
I 16
	movl	$0,PCB_ONFAULT(%ecx)
E 16
	ret
	
I 27
	ALIGN32
E 27
fusufault:
I 16
	movl	_curpcb,%ecx
E 16
	xorl	%eax,%eax
D 16
	movl	%eax,_nofault
E 16
I 16
	movl	%eax,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 16
	decl	%eax
	ret
E 2

I 25
D 27

/*
 * There is a little bit of duplicated code so we can avoid flushing the
 * prefetch queue in the common case.
 */

E 27
I 27
	ALIGN32
E 27
E 25
D 2
#ifdef KADB
/*
 * C library -- reset, setexit
 *
 *	reset(x)
 * will generate a "return" from
 * the last call to
 *	setexit()
 * by restoring r6 - r12, ap, fp
 * and doing a return.
 * The returned value is x; on the original
 * call the returned value is 0.
 */
ENTRY(setexit, 0)
	movab	setsav,r0
	movq	r6,(r0)+
	movq	r8,(r0)+
	movq	r10,(r0)+
	movq	8(fp),(r0)+		# ap, fp
	movab	4(ap),(r0)+		# sp
	movl	16(fp),(r0)		# pc
	clrl	r0
E 2
I 2
ALTENTRY(suiword)
ENTRY(suword)
D 16
	movl	$fusufault,_nofault	# in case we page/protection violate
E 16
I 16
D 25
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 16
	movl	4(%esp),%edx
	movl	8(%esp),%eax
I 4
D 14
	.byte	0x65		# use gs
E 14
I 14
	# .byte	0x65		# use gs
E 14
E 4
	movl	%eax,0(%edx)
	xorl	%eax,%eax
D 16
	movl	%eax,_nofault
E 16
I 16
	movl	%eax,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 25
I 25
D 27
	movl 4(%esp), %eax /* address */
E 27
I 27
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
	movl	4(%esp),%edx
	movl	8(%esp),%eax
E 27

D 27
	cmpl $ USRSTACK, %eax
	jae return_minus_one
E 27
I 27
#ifdef notdef
	shrl	$IDXSHIFT, %edx	/* fetch pte associated with address */
	andb	$0xfc, %dl
	movl	_PTmap(%edx), %edx
E 27

D 27
	/* check if the destination crosses a page boundary */
	movl %eax, %ecx
	andl $ NBPG - 1, %ecx
	cmpl $ NBPG - 4, %ecx
	ja suword_breakup

	/* make sure the page table is present */
	movl %eax, %ecx
	shrl $ PDRSHIFT, %ecx
	movl _PTD(,%ecx,4), %ecx
	andl $ PG_V, %ecx
	jnz suword_fault

	/* now make sure the page is present with user write permission */
	movl %eax, %ecx
	shrl $ PGSHIFT, %ecx
	movl _PTmap(,%ecx,4), %ecx
	andl $ PG_V | PG_UW, %ecx
	cmpl $ PG_V | PG_UW, %ecx
	jnz suword_fault

	movl 8(%esp), %ecx
	movl %ecx, (%eax)
	xorl %eax, %eax
E 27
I 27
	andb	$7, %dl		/* if we are the one case that won't trap... */
	cmpb	$5 , %edx
	jne	1f
				/* ... then simulate the trap! */
	pushl	%edi
	call	_trapwrite	/* trapwrite(addr) */
	popl	%edx
	cmpl	$0, %eax	/* if not ok, return */
	jne	fusufault
	movl	8(%esp),%eax	/* otherwise, continue with reference */
1:
	movl	4(%esp),%edx
#endif
	.byte	0x65		# use gs
	movl	%eax,0(%edx)
	xorl	%eax,%eax
	movl	%eax,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 27
E 25
E 16
E 2
	ret
I 2
D 25
	
ENTRY(susword)
D 16
	movl	$fusufault,_nofault	# in case we page/protection violate
E 16
I 16
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 16
	movl	4(%esp),%edx
	movl	8(%esp),%eax
D 4
	movl	%eax,0(%edx)
E 4
I 4
D 14
	.byte	0x65		# use gs
E 14
I 14
	# .byte	0x65		# use gs
E 14
	movw	%ax,0(%edx)
E 4
	xorl	%eax,%eax
D 16
	movl	%eax,_nofault
E 16
I 16
	movl	%eax,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 25
I 25
D 27

suword_fault:
	/* 
	 * this is a slow case anyway, so build a frame to make the debugger
	 * more useful
	 */
	pushl %ebp
	movl %esp, %ebp

	pushl %eax
	call _user_write_fault

	leave

	cmpl $0, %eax
	jnz return_minus_one

	movl 4(%esp), %eax
	movl 8(%esp), %ecx
	movl %ecx, (%eax)
	xorl %eax, %eax
E 27
I 27
	
	ALIGN32
ENTRY(susword)
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
	movl	4(%esp),%edx
	movl	8(%esp),%eax
#ifdef notdef
shrl	$IDXSHIFT, %edx	/* calculate pte address */
andb	$0xfc, %dl
movl	_PTmap(%edx), %edx
andb	$7, %edx	/* if we are the one case that won't trap... */
cmpb	$5 , %edx
jne	1f
/* ..., then simulate the trap! */
	pushl	%edi
	call	_trapwrite	/* trapwrite(addr) */
	popl	%edx
movl	_curpcb, %ecx	# restore trashed registers
cmpl	$0, %eax	/* if not ok, return */
jne	fusufault
movl	8(%esp),%eax
1: movl	4(%esp),%edx
#endif
	.byte	0x65		# use gs
	movw	%ax,0(%edx)
	xorl	%eax,%eax
	movl	%eax,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 27
E 25
E 16
	ret
E 2

I 25
D 27

suword_breakup:
	/* crosses page boundary ... do each byte separately */
	pushl %ebp
	movl %esp, %ebp
	pushl %esi
	pushl %edi
	pushl %ebx

	movl %eax, %edi
	movl 12(%ebp), %ebx
	movl $4, %esi

suword_breakup_loop:
	pushl %ebx
	pushl %edi
	call _subyte
	addl $8, %esp

	cmpl $-1, %eax
	jz suword_breakup_error

	incl %edi
	shrl $8, %ebx
	decl %esi
	jnz suword_breakup_loop

	xorl %eax, %eax
	popl %ebx
	popl %edi
	popl %esi
	leave
	ret

suword_breakup_error:
	movl $-1, %eax
	popl %ebx
	popl %edi
	popl %esi
	leave
	ret

E 27
I 27
	ALIGN32
E 27
E 25
D 2
ENTRY(reset, 0)
	movl	4(ap),r0	# returned value
	movab	setsav,r1
	movq	(r1)+,r6
	movq	(r1)+,r8
	movq	(r1)+,r10
	movq	(r1)+,r12
	movl	(r1)+,sp
	jmp 	*(r1)
E 2
I 2
ALTENTRY(suibyte)
ENTRY(subyte)
D 16
	movl	$fusufault,_nofault	# in case we page/protection violate
E 16
I 16
D 25
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 16
	movl	4(%esp),%edx
	movl	8(%esp),%eax
D 4
	movl	%eax,0(%edx)
E 4
I 4
D 14
	.byte	0x65		# use gs
E 14
I 14
	# .byte	0x65		# use gs
E 14
	movb	%eax,0(%edx)
E 4
	xorl	%eax,%eax
D 16
	movl	%eax,_nofault
E 16
I 16
	movl	%eax,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 25
I 25
D 27
	movl 4(%esp), %eax /* address */

	cmpl $ USRSTACK, %eax
	jae return_minus_one

	/* make sure the page table is present */
	movl %eax, %ecx
	shrl $ PDRSHIFT, %ecx
	movl _PTD(,%ecx,4), %ecx
	andl $ PG_V, %ecx
	jnz subyte_fault

	/* now make sure the page is present with user write permission */
	movl %eax, %ecx
	shrl $ PGSHIFT, %ecx
	movl _PTmap(,%ecx,4), %ecx
	andl $ PG_V | PG_UW, %ecx
	cmpl $ PG_V | PG_UW, %ecx
	jnz subyte_fault

	movl 8(%esp), %ecx
	movb %cl, (%eax)
	xorl %eax, %eax
E 27
I 27
	movl	_curpcb,%ecx
	movl	$fusufault,PCB_ONFAULT(%ecx) #in case we page/protection violate
	movl	4(%esp),%edx
	movl	8(%esp),%eax
#ifdef notdef
shrl	$IDXSHIFT, %edx	/* calculate pte address */
andb	$0xfc, %dl
movl	_PTmap(%edx), %edx
andb	$7, %edx	/* if we are the one case that won't trap... */
cmpb	$5 , %edx
jne	1f
/* ..., then simulate the trap! */
	pushl	%edi
	call	_trapwrite	/* trapwrite(addr) */
	popl	%edx
movl	_curpcb, %ecx	# restore trashed registers
cmpl	$0, %eax	/* if not ok, return */
jne	fusufault
movl	8(%esp),%eax
1: movl	4(%esp),%edx
#endif
	.byte	0x65		# use gs
	movb	%eax,0(%edx)
	xorl	%eax,%eax
	movl	%eax,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 27
	ret

D 27
subyte_fault:
	pushl %ebp
	movl %esp, %ebp

	pushl %eax
	call _user_write_fault

	leave

	cmpl $0, %eax
	jnz return_minus_one

	movl 4(%esp), %eax
	movl 8(%esp), %ecx
	movb %cl, (%eax)
	xorl %eax, %eax
	ret

return_minus_one:
	movl $-1, %eax
E 25
E 16
	ret
E 2

E 27
I 27
	ALIGN32
E 27
D 2
	.data
	.align  2
setsav:	.space	10*4
	.text
#endif
E 2
I 2
D 15
	ALTENTRY(savectx)
E 15
	ENTRY(setjmp)
	movl	4(%esp),%eax
	movl	%ebx, 0(%eax)		# save ebx
	movl	%esp, 4(%eax)		# save esp
	movl	%ebp, 8(%eax)		# save ebp
	movl	%esi,12(%eax)		# save esi
	movl	%edi,16(%eax)		# save edi
	movl	(%esp),%edx		# get rta
	movl	%edx,20(%eax)		# save eip
D 6
	movl	$0,%edx			# return (0);
	movl	$0,%eax			# return (0);
E 6
I 6
	xorl	%eax,%eax		# return (0);
E 6
	ret
E 2

I 14
D 27
#ifdef notdef
E 27
I 27
	ALIGN32
E 27
E 14
D 2
	.globl	_whichqs
	.globl	_qs
	.globl	_cnt
E 2
I 2
D 4
	ENTRY(qsetjmp)
	movl	4(%esp),%eax
	movl	%esp, 4(%eax)		# save esp
	movl	%ebp, 8(%eax)		# save ebp
	movl	(%esp),%edx		# get rta
	movl	%edx,20(%eax)		# save eip
	xorl	%eax,%eax		# return (0);
	ret
E 2

E 4
D 2
	.globl	_noproc
	.comm	_noproc,4
	.globl	_runrun
	.comm	_runrun,4

E 2
I 2
	ENTRY(longjmp)
	movl	4(%esp),%eax
	movl	 0(%eax),%ebx		# restore ebx
	movl	 4(%eax),%esp		# restore esp
	movl	 8(%eax),%ebp		# restore ebp
	movl	12(%eax),%esi		# restore esi
	movl	16(%eax),%edi		# restore edi
	movl	20(%eax),%edx		# get rta
	movl	%edx,(%esp)		# put in return frame
	xorl	%eax,%eax		# return (1);
	incl	%eax
	ret
I 29

E 29
I 14
D 27
#endif
E 27
E 14
E 2
/*
D 2
 * The following primitives use the fancy VAX instructions
 * much like VMS does.  _whichqs tells which of the 32 queues _qs
E 2
I 2
D 29
 * The following primitives manipulate the run queues.
 * _whichqs tells which of the 32 queues _qs
E 2
 * have processes in them.  Setrq puts processes into queues, Remrq
 * removes them from queues.  The running process is on no queue,
 * other processes are on a queue related to p->p_pri, divided by 4
E 29
I 29
 * The following primitives manipulate the run queues.  _whichqs tells which
 * of the 32 queues _qs have processes in them.  Setrunqueue puts processes
 * into queues, Remrq removes them from queues.  The running process is on
D 30
 * no queue, other processes are on a queue related to p->p_pri, divided by 4
E 29
 * actually to shrink the 0-127 range of priorities into the 32 available
E 30
I 30
 * no queue, other processes are on a queue related to p->p_priority, divided
 * by 4 actually to shrink the 0-127 range of priorities into the 32 available
E 30
 * queues.
 */
D 29

E 29
I 2
D 4
	.globl	_whichqs,_qs,_cnt,_panic,_ctasksel
E 4
I 4
	.globl	_whichqs,_qs,_cnt,_panic
E 4
	.comm	_noproc,4
	.comm	_runrun,4
D 4
	.comm	_ctasksel,4
E 4

E 2
/*
D 2
 * Setrq(p), using fancy VAX instructions.
E 2
I 2
 * Setrq(p)
E 2
 *
D 2
 * Call should be made at splclock(), and p->p_stat should be SRUN
E 2
I 2
 * Call should be made at spl6(), and p->p_stat should be SRUN
E 2
 */
I 27
	ALIGN32
E 27
D 2
	.align	1
JSBENTRY(Setrq, R0)
	tstl	P_RLINK(r0)		## firewall: p->p_rlink must be 0
	beql	set1			##
	pushab	set3			##
	calls	$1,_panic		##
E 2
I 2
D 29
ENTRY(setrq)
E 29
I 29
ENTRY(setrunqueue)
E 29
	movl	4(%esp),%eax
D 30
	cmpl	$0,P_RLINK(%eax)	# should not be on q already
E 30
I 30
	cmpl	$0,P_BACK(%eax)		# should not be on q already
E 30
	je	set1
	pushl	$set2
	call	_panic
E 2
set1:
D 2
	movzbl	P_PRI(r0),r1		# put on queue which is p->p_pri / 4
	ashl	$-2,r1,r1
	movaq	_qs[r1],r2
	insque	(r0),*4(r2)		# at end of queue
	bbss	r1,_whichqs,set2	# mark queue non-empty
set2:
	rsb
E 2
I 2
D 30
	movzbl	P_PRI(%eax),%edx
E 30
I 30
	movzbl	P_PRIORITY(%eax),%edx
E 30
	shrl	$2,%edx
	btsl	%edx,_whichqs		# set q full bit
	shll	$3,%edx
	addl	$_qs,%edx		# locate q hdr
D 30
	movl	%edx,P_LINK(%eax)	# link process on tail of q
	movl	P_RLINK(%edx),%ecx
	movl	%ecx,P_RLINK(%eax)
	movl	%eax,P_RLINK(%edx)
	movl	%eax,P_LINK(%ecx)
E 30
I 30
	movl	%edx,P_FORW(%eax)	# link process on tail of q
	movl	P_BACK(%edx),%ecx
	movl	%ecx,P_BACK(%eax)
	movl	%eax,P_BACK(%edx)
	movl	%eax,P_FORW(%ecx)
E 30
	ret
E 2

D 2
set3:	.asciz	"setrq"
E 2
I 2
D 29
set2:	.asciz	"setrq"
E 29
I 29
set2:	.asciz	"setrunqueue"
E 29
E 2

/*
D 2
 * Remrq(p), using fancy VAX instructions
E 2
I 2
 * Remrq(p)
E 2
 *
D 2
 * Call should be made at splclock().
E 2
I 2
 * Call should be made at spl6().
E 2
 */
I 27
	ALIGN32
E 27
D 2
	.align	1
JSBENTRY(Remrq, R0)
	movzbl	P_PRI(r0),r1
	ashl	$-2,r1,r1
	bbsc	r1,_whichqs,rem1
	pushab	rem3			# it wasn t recorded to be on its q
	calls	$1,_panic
E 2
I 2
ENTRY(remrq)
	movl	4(%esp),%eax
D 30
	movzbl	P_PRI(%eax),%edx
E 30
I 30
	movzbl	P_PRIORITY(%eax),%edx
E 30
	shrl	$2,%edx
	btrl	%edx,_whichqs		# clear full bit, panic if clear already
	jb	rem1
	pushl	$rem3
	call	_panic
E 2
rem1:
D 2
	remque	(r0),r2
	beql	rem2
	bbss	r1,_whichqs,rem2
E 2
I 2
	pushl	%edx
D 30
	movl	P_LINK(%eax),%ecx	# unlink process
	movl	P_RLINK(%eax),%edx
	movl	%edx,P_RLINK(%ecx)
	movl	P_RLINK(%eax),%ecx
	movl	P_LINK(%eax),%edx
	movl	%edx,P_LINK(%ecx)
E 30
I 30
	movl	P_FORW(%eax),%ecx	# unlink process
	movl	P_BACK(%eax),%edx
	movl	%edx,P_BACK(%ecx)
	movl	P_BACK(%eax),%ecx
	movl	P_FORW(%eax),%edx
	movl	%edx,P_FORW(%ecx)
E 30
	popl	%edx
	movl	$_qs,%ecx
	shll	$3,%edx
	addl	%edx,%ecx
D 30
	cmpl	P_LINK(%ecx),%ecx	# q still has something?
E 30
I 30
	cmpl	P_FORW(%ecx),%ecx	# q still has something?
E 30
	je	rem2
	shrl	$3,%edx			# yes, set bit as still full
	btsl	%edx,_whichqs
E 2
rem2:
D 2
	clrl	P_RLINK(r0)		## for firewall checking
	rsb
E 2
I 2
D 30
	movl	$0,P_RLINK(%eax)	# zap reverse link to indicate off list
E 30
I 30
	movl	$0,P_BACK(%eax)		# zap reverse link to indicate off list
E 30
	ret
E 2

rem3:	.asciz	"remrq"
D 2

/*
 * Masterpaddr is the p->p_addr of the running process on the master
 * processor.  When a multiprocessor system, the slave processors will have
 * an array of slavepaddr s.
 */
	.globl	_masterpaddr
	.data
_masterpaddr:
	.long	0

	.text
E 2
D 30
sw0:	.asciz	"swtch"
E 30
I 30
sw0:	.asciz	"Xswitch"
E 30
I 2
D 13
sw01:	.asciz	"swtch1"
sw02:	.asciz	"swtch2"
E 13
E 2

/*
 * When no processes are on the runq, Swtch branches to idle
 * to wait for something to come ready.
 */
	.globl	Idle
I 27
	ALIGN32
E 27
D 2
Idle: idle:
	movl	$1,_noproc
	mtpr	$0,$IPL			# must allow interrupts here
1:
	tstl	_whichqs		# look for non-empty queue
	bneq	sw1
	brb	1b
E 2
I 2
Idle:
idle:
	call	_spl0
	cmpl	$0,_whichqs
D 15
	jne	sw1
E 15
I 15
D 16
	jne	2f
E 16
I 16
	jne	sw1
E 16
E 15
	hlt		# wait for interrupt
	jmp	idle
E 2

I 27
D 30
	.align 4 /* ..so that profiling doesn't lump Idle with swtch().. */
E 30
I 30
	.align 4 /* ..so that profiling doesn't lump Idle with Xswitch().. */
E 30
E 27
D 2
badsw:	pushab	sw0
	calls	$1,_panic
E 2
I 2
badsw:
	pushl	$sw0
	call	_panic
E 2
	/*NOTREACHED*/

/*
D 2
 * Swtch(), using fancy VAX instructions
E 2
I 2
 * Swtch()
E 2
 */
I 27
	ALIGN32
E 27
D 2
	.align	1
JSBENTRY(Swtch, 0)
E 2
I 2
D 30
ENTRY(swtch)
E 30
I 30
ENTRY(Xswitch)
E 30
I 7
D 11
	movl	_cpl,%eax
	movl	%eax,_u+PCB_IML
E 11
I 11
D 15
	movw	_cpl, %ax
	movw	%ax, _u+PCB_IML
E 11
E 7
	movl	$1,%eax
	movl	%eax,_noproc
E 15
I 15

E 15
E 2
	incl	_cnt+V_SWTCH
D 2
sw1:	ffs	$0,$32,_whichqs,r0	# look for non-empty queue
	beql	idle			# if none, idle
	mtpr	$0x18,$IPL		# lock out all so _whichqs==_qs
	bbcc	r0,_whichqs,sw1		# proc moved via interrupt
	movaq	_qs[r0],r1
	remque	*(r1),r2		# r2 = p = highest pri process
	bvs	badsw			# make sure something was there
	beql	sw2
	insv	$1,r0,$1,_whichqs	# still more procs in this queue
E 2
I 2
D 15
sw1:
I 7
	cli
E 7
	bsfl	_whichqs,%eax	# find a full q
	jz	idle		# if none, idle
swfnd:
D 6
	cli
E 6
I 6
D 7
	# cli
E 7
E 6
	btrl	%eax,_whichqs	# clear q full status
	jnb	sw1		# if it was clear, look for another
	pushl	%eax		# save which one we are using
	shll	$3,%eax
	addl	$_qs,%eax	# select q
	pushl	%eax
E 15

D 15
	cmpl	P_LINK(%eax),%eax	# linked to self? (e.g. not on list)
	je	badsw		# not possible
	movl	P_LINK(%eax),%ecx	# unlink from front of process q
	movl	P_LINK(%ecx),%edx
	movl	%edx,P_LINK(%eax)
	movl	P_RLINK(%ecx),%eax
	movl	%eax,P_RLINK(%edx)
E 15
I 15
	/* switch to new process. first, save context as needed */
E 15

D 15
	popl	%eax
	popl	%edx
	cmpl	P_LINK(%ecx),%eax	# q empty
	je	sw2
	btsl	%edx,_whichqs		# nope, indicate full
E 2
sw2:
D 2
	clrl	_noproc
	clrl	_runrun
#ifdef notdef
	tstl	P_WCHAN(r2)		## firewalls
	bneq	badsw			##
	cmpb	P_STAT(r2),$SRUN	##
	bneq	badsw			##
E 2
I 2
	movl	$0,%eax
	movl	%eax,_noproc
	movl	%eax,_runrun
	cmpl	$0,P_WCHAN(%ecx)
	jne	badsw
D 4
	cmpb	$SRUN,P_STAT(%ecx)
E 4
I 4
	cmpb	$ SRUN,P_STAT(%ecx)
E 4
	jne	badsw
	movl	%eax,P_RLINK(%ecx)
E 15
I 15
D 18
	movl	_curproc,%ecx
	movl	P_ADDR(%ecx),%ecx
E 18
I 18
D 19
	movl	_curpcb,%ecx
E 19
I 19
	movl	_curproc,%ecx
I 27

	/* if no process to save, don't bother */
	cmpl	$0,%ecx
	je	sw1

E 27
	movl	P_ADDR(%ecx),%ecx

E 19
E 18
E 15
D 7
	# movl	P_ADDR(%ecx),%edx
	movl	P_CR3(%ecx),%edx
E 7
D 4
/*pushal; pushl %edx; pushl $lc; call _printf; popl %eax ; popl %eax; popal ; .data ; lc: .asciz "swtch %x" ; .text*/
E 4

I 7
D 15
	movl	P_ADDR(%ecx),%edx
D 14
	movl	(%edx),%eax
	movl	%eax,_Swtchmap
D 11
	movl	4(%edx),%eax
	movl	%eax,_Swtchmap+4
E 11
I 11
D 13
	# movl	4(%edx),%eax
	# movl	%eax,_Swtchmap+4
E 11
D 9
	movl	%cr3,%eax
I 8
 	orl	$ I386_CR3PAT,%eax
E 8
	movl	%eax,%cr3
E 9
I 9
	# movl	%cr3,%eax
D 11
 	# orl	$ I386_CR3PAT,%eax
E 11
	# movl	%eax,%cr3
E 13
E 9
	movl	_Swtchbase+PCB_CR3,%edx
E 14
I 14
	movl	PCB_CR3(%edx),%edx
E 14

D 11
 # pushal; pushl %edx ; pushl P_CR3(%ecx); pushl $l2; call _pg; popl %eax ; popl %eax; popl %eax ; popal ; .data ; l2: .asciz "s %x %x " ; .text

E 11
E 7
/* switch to new process. first, save context as needed */
I 11

E 11
	movl	$_u,%ecx

E 15
	movl	(%esp),%eax		# Hardware registers
	movl	%eax, PCB_EIP(%ecx)
	movl	%ebx, PCB_EBX(%ecx)
	movl	%esp, PCB_ESP(%ecx)
	movl	%ebp, PCB_EBP(%ecx)
	movl	%esi, PCB_ESI(%ecx)
	movl	%edi, PCB_EDI(%ecx)

D 7
#ifdef FPUNOTYET
E 2
#endif
E 7
I 7
D 13
	fsave	PCB_SAVEFPU(%ecx)
E 13
I 13
D 20
#ifdef NPX
E 20
I 20
D 22
#ifdef NPXx
E 22
I 22
D 27
#if 0 && NNPX > 0
E 22
E 20
	movb	PCB_FLAGS(%ecx),%al
E 27
I 27
#ifdef NPX
E 27
	/* have we used fp, and need a save? */
D 27
	andb	$ FP_WASUSED|FP_NEEDSSAVE,%al
	cmpb	$ FP_WASUSED|FP_NEEDSSAVE,%al
E 27
I 27
	mov	_curproc,%eax
	cmp	%eax,_npxproc
E 27
	jne	1f
D 27
	movl	%cr0,%eax		/* insure fp is enabled */
	andb 	$0xfb,%al
	movl	%eax,%cr0
	fnsave	PCB_SAVEFPU(%ecx)
	orb 	$4,%al			/* disable it */
	movl	%eax,%cr0
	movb	PCB_FLAGS(%ecx),%al
	xorb	$ FP_NEEDSSAVE,%al	/* save processed */
	movb	%al,PCB_FLAGS(%ecx)
E 27
I 27
	pushl	%ecx			/* h/w bugs make saving complicated */
	leal	PCB_SAVEFPU(%ecx),%eax
	pushl	%eax
	call	_npxsave		/* do it in a big C function */
	popl	%eax
	popl	%ecx
E 27
1:
#endif
E 13
E 7
D 2
	clrl	P_RLINK(r2)		##
	movl	*P_ADDR(r2),r0
#ifdef notdef
	cmpl	r0,_masterpaddr		# resume of current proc is easy
	beql	res0
#endif
	movl	r0,_masterpaddr
	ashl	$PGSHIFT,r0,r0		# r0 = pcbb(p)
/* fall into... */
E 2

D 2
/*
 * Resume(pf)
 */
JSBENTRY(Resume, R0)
	mtpr	$HIGH,$IPL			# no interrupts, please
	movl	_CMAP2,_u+PCB_CMAP2	# yech
	svpctx
	mtpr	r0,$PCBB
	ldpctx
	movl	_u+PCB_CMAP2,_CMAP2	# yech
	mtpr	$_CADDR2,$TBIS
res0:
	tstl	_u+PCB_SSWAP
	bneq	res1
	rei
res1:
	movl	_u+PCB_SSWAP,r0			# longjmp to saved context
	clrl	_u+PCB_SSWAP
	movq	(r0)+,r6			# restore r6, r7
	movq	(r0)+,r8			# restore r8, r9
	movq	(r0)+,r10			# restore r10, r11
	movq	(r0)+,r12			# restore ap, fp
	movl	(r0)+,r1			# saved sp
	cmpl	r1,sp				# must be a pop
	bgequ	1f
	pushab	2f
	calls	$1,_panic
	/* NOTREACHED */
1:
	movl	r1,sp				# restore sp
	pushl	$PSL_PRVMOD			# return psl
	pushl	(r0)				# address to return to
	rei
E 2
I 2
	movl	_CMAP2,%eax		# save temporary map PTE
	movl	%eax,PCB_CMAP2(%ecx)	# in our context
I 27
	movl	$0,_curproc		#  out of process
E 27
E 2

I 14
D 15
#pushal ; pushl %edx ; pushl $LF ; call _pg ; popl %eax ; popl %edx ; popal
	movl	%esp,%ecx
	movl	$tmpstk,%esp
E 15
I 15
D 27
	movw	_cpl, %ax
	movw	%ax, PCB_IML(%ecx)	# save ipl
E 27
I 27
	# movw	_cpl, %ax
	# movw	%ax, PCB_IML(%ecx)	# save ipl
E 27
E 15

I 20
D 27
	movl	$tmpstk2,%edx
	movl	(%edx),%eax	# touch stack, fault if not there
	movl	%eax,(%edx)
	movl	%edx,%esp
	movl	$pcb2,_curpcb

E 27
E 20
E 14
I 8
D 15
 	orl	$ I386_CR3PAT,%edx
I 14
	inb	$0x84,%al	# check wristwatch
E 14
E 8
D 2
2:	.asciz	"ldctx"
E 2
D 7

I 4
 # orl $0x80000000,%edx
E 7
E 4
D 2
/*
 * {fu,su},{byte,word}, all massaged by asm.sed to jsb s
 */
	.align	1
JSBENTRY(Fuword, R0)
	prober	$3,$4,(r0)
	beql	fserr
	movl	(r0),r0
	rsb
fserr:
	mnegl	$1,r0
	rsb
E 2
I 2
D 13
	movl	%edx,%cr3	# context switch
E 13
I 13
	movl	%edx,%cr3	# context switch address space
E 15
I 15
	/* save is done, now choose a new process or idle */
I 16
sw1:
E 16
D 27
	cli				# XXX?
E 27
	movl	_whichqs,%edi
2:
I 27
	cli
E 27
	bsfl	%edi,%eax		# find a full q
	jz	idle			# if none, idle
D 16
	  # XX update whichqs?
E 16
I 16
	# XX update whichqs?
E 16
swfnd:
	btrl	%eax,%edi		# clear q full status
	jnb	2b		# if it was clear, look for another
	movl	%eax,%ebx		# save which one we are using
E 15
E 13
E 2

I 15
	shll	$3,%eax
	addl	$_qs,%eax		# select q
	movl	%eax,%esi

#ifdef	DIAGNOSTIC
D 30
	cmpl	P_LINK(%eax),%eax # linked to self? (e.g. not on list)
E 30
I 30
	cmpl	P_FORW(%eax),%eax # linked to self? (e.g. not on list)
E 30
	je	badsw			# not possible
#endif

D 30
	movl	P_LINK(%eax),%ecx	# unlink from front of process q
	movl	P_LINK(%ecx),%edx
	movl	%edx,P_LINK(%eax)
	movl	P_RLINK(%ecx),%eax
	movl	%eax,P_RLINK(%edx)
E 30
I 30
	movl	P_FORW(%eax),%ecx	# unlink from front of process q
	movl	P_FORW(%ecx),%edx
	movl	%edx,P_FORW(%eax)
	movl	P_BACK(%ecx),%eax
	movl	%eax,P_BACK(%edx)
E 30

D 16
#ifdef doubtful
E 16
D 30
	cmpl	P_LINK(%ecx),%esi	# q empty
E 30
I 30
	cmpl	P_FORW(%ecx),%esi	# q empty
E 30
	je	3f
D 16
	btsl	%edx,%edi		# nope, set to indicate full
E 16
I 16
	btsl	%ebx,%edi		# nope, set to indicate full
E 16
3:
D 16
	btsl	%edx,%edi		# nope, set to indicate full
E 16
	movl	%edi,_whichqs		# update q status
D 16
#else
	btsl	%edx,_whichqs		# nope, set to indicate full
#endif
E 16
I 16

E 16
	movl	$0,%eax
D 27
	movl	%ecx,_curproc
E 27
	movl	%eax,_want_resched

#ifdef	DIAGNOSTIC
	cmpl	%eax,P_WCHAN(%ecx)
	jne	badsw
	cmpb	$ SRUN,P_STAT(%ecx)
	jne	badsw
#endif

D 30
	movl	%eax,P_RLINK(%ecx) /* isolate process to run */
E 30
I 30
	movl	%eax,P_BACK(%ecx)	/* isolate process to run */
E 30
	movl	P_ADDR(%ecx),%edx
I 16
D 27
	movl	%edx,_curpcb
I 20
	inb	$0x84,%al	# flush write buffers
E 27
E 20
E 16
	movl	PCB_CR3(%edx),%ebx

	/* switch address space */
D 20
	movl	%esp,%ecx
	movl	$tmpstk,%esp
E 20
I 20
D 27
	cli
E 20
 	orl	$ I386_CR3PAT,%ebx
D 20
	inb	$0x84,%al	# flush write buffers
E 20
	movl	%ebx,%cr3	# context switch address space
E 27
I 27
	movl	%ebx,%cr3
E 27
I 20

D 27
	jmp	7f
	nop
 7:	inb	$0x84,%al	# flush write buffers
	movl	PCB_ESP(%edx), %ecx
E 20
E 15
I 14
	movl	(%ecx),%eax	# touch stack, fault if not there
	movl	%eax,(%ecx)
	movl	%ecx,%esp

E 27
E 14
D 2
	.align	1
JSBENTRY(Fubyte, R0)
	prober	$3,$1,(r0)
	beql	fserr
	movzbl	(r0),r0
	rsb
E 2
I 2
D 4
	movl	$_u,%edx
E 4
I 4
D 15
	movl	$_u,%ecx
D 7
	.globl	__gsel_tss
	movw	__gsel_tss,%ax
E 7
I 7
D 11
	# .globl	__gsel_tss
	# movw	__gsel_tss,%ax
E 7
	# ltr	%ax
E 11
E 4
E 2

D 2
	.align	1
JSBENTRY(Suword, R0|R1)
	probew	$3,$4,(r0)
	beql	fserr
	movl	r1,(r0)
	clrl	r0
	rsb
E 2
I 2
/* restore context */
	movl	PCB_EBX(%ecx), %ebx
	movl	PCB_ESP(%ecx), %esp
	movl	PCB_EBP(%ecx), %ebp
	movl	PCB_ESI(%ecx), %esi
	movl	PCB_EDI(%ecx), %edi
	movl	PCB_EIP(%ecx), %eax
E 15
I 15
	/* restore context */
	movl	PCB_EBX(%edx), %ebx
	movl	PCB_ESP(%edx), %esp
	movl	PCB_EBP(%edx), %ebp
	movl	PCB_ESI(%edx), %esi
	movl	PCB_EDI(%edx), %edi
	movl	PCB_EIP(%edx), %eax
E 15
	movl	%eax, (%esp)
E 2

D 2
	.align	1
JSBENTRY(Subyte, R0|R1)
	probew	$3,$1,(r0)
	beql	fserr
	movb	r1,(r0)
	clrl	r0
	rsb
E 2
I 2
D 7
#ifdef FPUNOTYET
#endif
E 7
I 7
D 13
	frstor	PCB_SAVEFPU(%ecx)
E 13
I 13
D 22
#ifdef NPX
E 22
I 22
D 27
#if NNPX > 0
E 22
I 20
#ifdef notdef
E 20
D 15
	movb	PCB_FLAGS(%ecx),%al
E 15
I 15
	movb	PCB_FLAGS(%edx),%al
E 15
	/* if fp could be used, a dna trap will do a restore */
	testb	$ FP_WASUSED,%al
	je	1f
D 15
	orb	$ FP_NEEDSRESTORE,%al
	movb	%al, PCB_FLAGS(%ecx)
E 15
I 15
	orb	$ FP_NEEDSRESTORE,PCB_FLAGS(%ecx)
E 15
1:
#endif
I 20
	movl	%cr0,%eax
	orb 	$4,%al			/* disable it */
	movl	%eax,%cr0
#endif
E 20
E 13
E 7
E 2

E 27
D 2
/*
 * Copy 1 relocation unit (NBPG bytes)
 * from user virtual address to physical address
 */
ENTRY(copyseg, 0)
	bisl3	$PG_V|PG_KW,8(ap),_CMAP2
	mtpr	$_CADDR2,$TBIS	# invalidate entry for copy 
	movc3	$NBPG,*4(ap),_CADDR2
E 2
I 2
D 4
	movl	PCB_CMAP2(%edx),%eax	# get temporary map
E 4
I 4
D 15
	movl	PCB_CMAP2(%ecx),%eax	# get temporary map
E 15
I 15
	movl	PCB_CMAP2(%edx),%eax	# get temporary map
E 15
E 4
	movl	%eax,_CMAP2		# reload temporary map PTE
D 13
#ifdef FPUNOTYET
#endif
E 13
D 4
	cmpl	$0,PCB_SSWAP(%edx)	# do an alternate return?
E 4
I 4
D 15
	cmpl	$0,PCB_SSWAP(%ecx)	# do an alternate return?
E 4
	jne	res3			# yes, go reload regs
E 15
D 6
	# call	_spl0
D 4
	cli
E 4
I 4
	sti
E 6
I 6
D 7
	call	_spl0
	# sti
E 7
I 7

D 11
	pushl	PCB_IML(%ecx)
	call	_splx
	popl	%eax
E 11
I 11
D 13
	# pushl	PCB_IML(%ecx)
	# call	_splx
	# popl	%eax
E 13
D 15
	call _spl0
E 11
	movl	$0,%eax
E 7
E 6
E 4
E 2
	ret
I 7

E 7
D 2

/*
 * zero out physical memory
 * specified in relocation units (NBPG bytes)
 */
ENTRY(clearseg, 0)
	bisl3	$PG_V|PG_KW,4(ap),_CMAP1
	mtpr	$_CADDR1,$TBIS
	movc5	$0,(sp),$0,$NBPG,_CADDR1
E 2
I 2
res3:
	xorl	%eax,%eax		# inline restore context
D 4
	xchgl	PCB_SSWAP(%edx),%eax	# addr of saved context, clear it
E 4
I 4
	xchgl	PCB_SSWAP(%ecx),%eax	# addr of saved context, clear it

D 11
 #pushal; pushl 20(%eax); pushl $l2; call _printf; popl %eax ; popl %eax; popal ; .data ; l2: .asciz "s %x\n" ; .text

E 11
E 4
	movl	 0(%eax),%ebx		# restore ebx
	movl	 4(%eax),%esp		# restore esp
	movl	 8(%eax),%ebp		# restore ebp
	movl	12(%eax),%esi		# restore esi
	movl	16(%eax),%edi		# restore edi
	movl	20(%eax),%edx		# get rta
	movl	%edx,(%esp)		# put in return frame
I 7
D 11
	call	_spl0
E 11
I 11

D 13
	# call	_spl0
E 13
	pushl	_u+PCB_IML
E 15
I 15
D 27
	pushl	PCB_IML(%edx)
E 27
I 27
	movl	%ecx,_curproc		# into next process
	movl	%edx,_curpcb

	/* pushl	PCB_IML(%edx)
E 27
E 15
	call	_splx
D 27
	popl	%eax
E 27
I 27
	popl	%eax*/
E 27

E 11
E 7
D 15
	xorl	%eax,%eax		# return (1);
	incl	%eax
E 15
I 15
	movl	%edx,%eax		# return (1);
E 15
D 7
	sti
E 7
E 2
	ret

I 27
	.globl	_mvesp
	ALIGN32
_mvesp:	movl	%esp,%eax
	ret
E 27
/*
D 2
 * Check address.
 * Given virtual address, byte count, and rw flag
 * returns 0 on no access.
E 2
I 2
D 15
 * Resume(p_addr)
 * current just used to fillout u. tss so fork can fake a return to swtch
E 15
I 15
D 30
 * struct proc *swtch_to_inactive(p) ; struct proc *p;
E 30
I 30
 * struct proc *switch_to_inactive(p) ; struct proc *p;
E 30
 *
 * At exit of a process, move off the address space of the
 * process and onto a "safe" one. Then, on a temporary stack
 * return and run code that disposes of the old state.
 * Since this code requires a parameter from the "old" stack,
 * pass it back as a return value.
E 15
D 13
 * [ all thats really needed is esp and eip ]
E 13
E 2
 */
I 27
	ALIGN32
E 27
D 2
ENTRY(useracc, 0)
	movl	4(ap),r0		# get va
	movl	8(ap),r1		# count
	tstl	12(ap)			# test for read access ?
	bneq	userar			# yes
	cmpl	$NBPG,r1			# can we do it in one probe ?
	bgeq	uaw2			# yes
uaw1:
	probew	$3,$NBPG,(r0)
	beql	uaerr			# no access
	addl2	$NBPG,r0
	acbl	$NBPG+1,$-NBPG,r1,uaw1
uaw2:
	probew	$3,r1,(r0)
	beql	uaerr
	movl	$1,r0
E 2
I 2
D 15
ENTRY(resume)
D 6
	movl	4(%esp),%ecx
E 6
I 6
D 14
	# movl	4(%esp),%ecx
	movl	$_u,%ecx
E 14
I 14
	movl	4(%esp),%ecx
	# movl	$_u,%ecx
E 15
I 15
D 30
ENTRY(swtch_to_inactive)
E 30
I 30
ENTRY(switch_to_inactive)
E 30
I 20
D 27

	movl	$tmpstk2-4,%ecx		# temporary stack, compensated for call
	movl	(%ecx),%eax		# touch stack, fault if not there
	movl	%eax,(%ecx)

E 27
E 20
	popl	%edx			# old pc
	popl	%eax			# arg, our return value
I 20
D 27
	inb	$0x84,%al	# flush write buffers

	movl	%ecx,%esp

E 27
E 20
	movl	_IdlePTD,%ecx
I 20
D 27

E 27
E 20
	movl	%ecx,%cr3		# good bye address space
I 20
D 27
	inb	$0x84,%al	# flush write buffers

E 27
E 20
 #write buffer?
D 20
	movl	$tmpstk-4,%esp		# temporary stack, compensated for call
E 20
I 20
D 27
	movl	$pcb2,_curpcb
E 27
I 27
	movl	$tmpstk-4,%esp		# temporary stack, compensated for call
E 27
E 20
D 16
	jmp	(%edx)			# return, execute remainder of cleanup
E 16
I 16
	jmp	%edx			# return, execute remainder of cleanup
E 16

/*
 * savectx(pcb, altreturn)
 * Update pcb, saving current processor state and arranging
D 30
 * for alternate return ala longjmp in swtch if altreturn is true.
E 30
I 30
 * for alternate return ala longjmp in Xswitch if altreturn is true.
E 30
 */
I 27
	ALIGN32
E 27
ENTRY(savectx)
	movl	4(%esp), %ecx
E 15
E 14
I 11
	movw	_cpl, %ax
	movw	%ax,  PCB_IML(%ecx)
E 11
E 6
D 15
	movl	(%esp),%eax	
E 15
I 15
	movl	(%esp), %eax	
E 15
	movl	%eax, PCB_EIP(%ecx)
	movl	%ebx, PCB_EBX(%ecx)
	movl	%esp, PCB_ESP(%ecx)
	movl	%ebp, PCB_EBP(%ecx)
	movl	%esi, PCB_ESI(%ecx)
	movl	%edi, PCB_EDI(%ecx)
D 13
#ifdef FPUNOTYET
E 13
I 13
D 20
#ifdef NPX
E 20
I 20
D 22
#ifdef NPXx
E 22
I 22
D 27
#if 0 && NNPX > 0
E 22
E 20
	/* have we ever used fp, and need to save? */
D 15
	testb	$ FP_WASUSED,PCB_FLAGS(%ecx)
E 15
I 15
	testb	$ FP_WASUSED, PCB_FLAGS(%ecx)
E 15
	je	1f
D 15
	movl	%cr0,%eax
	andb 	$0xfb,%al
	movl	%eax,%cr0
E 15
I 15
	movl	%cr0, %edx
	andb 	$0xfb, %dl
	movl	%edx, %cr0
E 15
	fnsave	PCB_SAVEFPU(%ecx)
D 15
	orb 	$4,%eax
	movl	%eax,%cr0
E 15
I 15
	orb 	$4, %edx
	movl	%edx, %cr0
E 27
I 27

#ifdef NPX
	/*
	 * If npxproc == NULL, then the npx h/w state is irrelevant and the
	 * state had better already be in the pcb.  This is true for forks
	 * but not for dumps (the old book-keeping with FP flags in the pcb
	 * always lost for dumps because the dump pcb has 0 flags).
	 *
	 * If npxproc != NULL, then we have to save the npx h/w state to
	 * npxproc's pcb and copy it to the requested pcb, or save to the
	 * requested pcb and reload.  Copying is easier because we would
	 * have to handle h/w bugs for reloading.  We used to lose the
	 * parent's npx state for forks by forgetting to reload.
	 */
	mov	_npxproc,%eax
	testl	%eax,%eax
  	je	1f

	pushl	%ecx
	movl	P_ADDR(%eax),%eax
	leal	PCB_SAVEFPU(%eax),%eax
	pushl	%eax
	pushl	%eax
	call	_npxsave
	popl	%eax
	popl	%eax
	popl	%ecx

	pushl	%ecx
	pushl	$108+8*2	/* XXX h/w state size + padding */
	leal	PCB_SAVEFPU(%ecx),%ecx
	pushl	%ecx
	pushl	%eax
	call	_bcopy
	addl	$12,%esp
	popl	%ecx
E 27
E 15
1:
E 13
#endif
I 27

E 27
I 7
D 13
	fsave	PCB_SAVEFPU(%ecx)
E 13
D 11
	movl	_cpl,%eax
	movl	%eax,PCB_IML(%ecx)
E 11
E 7
D 15
	movl	$0,%eax
E 15
I 15
	movl	_CMAP2, %edx		# save temporary map PTE
	movl	%edx, PCB_CMAP2(%ecx)	# in our context

	cmpl	$0, 8(%esp)
	je	1f
	movl	%esp, %edx		# relocate current sp relative to pcb
	subl	$_kstack, %edx		#   (sp is relative to kstack):
	addl	%edx, %ecx		#   pcb += sp - kstack;
	movl	%eax, (%ecx)		# write return pc at (relocated) sp@
I 16
	# this mess deals with replicating register state gcc hides
	movl	12(%esp),%eax
	movl	%eax,12(%ecx)
	movl	16(%esp),%eax
	movl	%eax,16(%ecx)
	movl	20(%esp),%eax
	movl	%eax,20(%ecx)
	movl	24(%esp),%eax
	movl	%eax,24(%ecx)
E 16
1:
	xorl	%eax, %eax		# return 0
I 20
	ret

D 27
	.globl	_mvesp
_mvesp:	movl	%esp,%eax
E 20
E 15
E 2
	ret
I 11

E 27
I 14
/*
D 27
 * update profiling information for the user
 * addupc(pc, up, ticks) struct uprof *up;
E 27
I 27
 * addupc(int pc, struct uprof *up, int ticks):
 * update profiling information for the user process.
E 27
 */

I 27
	ALIGN32
E 27
ENTRY(addupc)
D 27
	movl	4(%esp),%eax		/* pc */
	movl	8(%esp),%ecx		/* up */
E 27
I 27
	pushl %ebp
	movl %esp,%ebp
	movl 12(%ebp),%edx		/* up */
	movl 8(%ebp),%eax		/* pc */
E 27

D 27
	/* does sampled pc fall within bottom of profiling window? */
	subl	PR_OFF(%ecx),%eax 	/* pc -= up->pr_off; */
	jl	1f 			/* if (pc < 0) return; */
E 27
I 27
	subl PR_OFF(%edx),%eax		/* pc -= up->pr_off */
	jl L1				/* if (pc < 0) return */
E 27

D 27
	/* construct scaled index */
	shrl	$1,%eax			/* reduce pc to a short index */
	mull	PR_SCALE(%ecx)		/* pc*up->pr_scale */
	shrdl	$15,%edx,%eax 		/* praddr >> 15 */
	cmpl	$0,%edx			/* if overflow, ignore */
	jne	1f
	andb	$0xfe,%al		/* praddr &= ~1 */
E 27
I 27
	shrl $1,%eax			/* praddr = pc >> 1 */
	imull PR_SCALE(%edx),%eax	/* praddr *= up->pr_scale */
	shrl $15,%eax			/* praddr = praddr << 15 */
	andl $-2,%eax			/* praddr &= ~1 */
E 27

D 27
	/* within profiling buffer? if so, compute address */
	cmpl	%eax,PR_SIZE(%ecx)	/* if (praddr > up->pr_size) return; */
	jg	1f
	addl	PR_BASE(%ecx),%eax	/* praddr += up->pr_base; */
E 27
I 27
	cmpl PR_SIZE(%edx),%eax		/* if (praddr > up->pr_size) return */
	ja L1
E 27

D 27
	/* tally ticks to selected counter */
D 16
	movl	$proffault,_nofault
E 16
I 16
	movl	_curpcb,%ecx
	movl	$proffault,PCB_ONFAULT(%ecx) #in case we page/protection violate
E 16
	movl	12(%esp),%edx		/* ticks */
	addw	%dx,(%eax)
D 16
	movl	$0,_nofault
E 16
I 16
	movl	$0,PCB_ONFAULT(%ecx)
E 16
1:	ret
E 27
I 27
/*	addl %eax,%eax			/* praddr -> word offset */
	addl PR_BASE(%edx),%eax		/* praddr += up-> pr_base */
	movl 16(%ebp),%ecx		/* ticks */
E 27

I 27
	movl _curpcb,%edx
	movl $proffault,PCB_ONFAULT(%edx)
	addl %ecx,(%eax)		/* storage location += ticks */
	movl $0,PCB_ONFAULT(%edx)
L1:
	leave
	ret

	ALIGN32
E 27
proffault:
D 27
	/* disable profiling if we get a fault */
	movl	$0,PR_SCALE(%ecx) /*	up->pr_scale = 0; */
D 16
	movl	$0,_nofault
E 16
I 16
	movl	_curpcb,%ecx
	movl	$0,PCB_ONFAULT(%ecx)
E 27
I 27
	/* if we get a fault, then kill profiling all together */
	movl $0,PCB_ONFAULT(%edx)	/* squish the fault handler */
 	movl 12(%ebp),%ecx
	movl $0,PR_SCALE(%ecx)		/* up->pr_scale = 0 */
	leave
E 27
E 16
	ret

E 14
E 11
D 13

E 13
D 2
userar:
	cmpl	$NBPG,r1
	bgeq	uar2
uar1:
	prober	$3,$NBPG,(r0)
	beql	uaerr
	addl2	$NBPG,r0
	acbl	$NBPG+1,$-NBPG,r1,uar1
uar2:
	prober	$3,r1,(r0)
	beql	uaerr
	movl	$1,r0
E 2
I 2
.data
I 27
	ALIGN32
E 27
D 16
	.globl	_cyloffset
E 16
I 16
	.globl	_cyloffset, _curpcb
E 16
_cyloffset:	.long	0
D 16
	.globl	_nofault
_nofault:	.long	0
E 16
I 14
	.globl	_proc0paddr
_proc0paddr:	.long	0
D 30
LF:	.asciz "swtch %x"
E 30
I 30
LF:	.asciz "Xswitch %x"
E 30

E 14
.text
I 27
 # To be done:
E 27
D 23
 # To be done:
E 23
D 14
	.globl _addupc
E 14
	.globl _astoff
D 14
	.globl _doadump
D 13
	.globl _inittodr
D 6
	.globl _ovbcopy
E 6
	.globl _physaddr
_addupc:
E 13
I 13
_addupc:		# sorry, no profiling
E 13
	.byte 0xcc
E 14
_astoff:
I 23
D 27
	movl	$0,_astpending
E 27
E 23
E 2
	ret
D 2
uaerr:
	clrl	r0
E 2
I 2
D 14
_doadump:
D 6
	.byte 0xcc
_ovbcopy:
E 6
D 13
	.byte 0xcc
_physaddr:
	.byte 0xcc
E 13
I 13
	call _reset_cpu
E 14
E 13
I 4

D 9
/* Paranoiaa - never happens, right? */
E 4
	.globl	_svfpsp,_rsfpsp
_svfpsp:
	popl %eax
	movl	%esp,svesp
	movl	%ebp,svebp
	pushl %eax
E 2
	ret
E 9
I 9
#define	IDTVEC(name)	.align 4; .globl _X/**/name; _X/**/name:
D 16
/*#define	PANIC(msg)	xorl %eax,%eax; movl %eax,_waittime; pushl 1f; \
			call _panic; 1: .asciz msg*/
#define	PRINTF(n,msg)	pushal ; pushl 1f; call _printf; MSG(msg) ; popl %eax ; popal
E 16
I 16
#define	PANIC(msg)	xorl %eax,%eax; movl %eax,_waittime; pushl 1f; \
			call _panic; 1: .asciz msg
D 27
#define	PRINTF(n,msg)	pushal ; pushl 1f; call _printf; MSG(msg) ; \
E 27
I 27
#define	PRINTF(n,msg)	pushal ; nop ; pushl 1f; call _printf; MSG(msg) ; \
E 27
			 popl %eax ; popal
E 16
#define	MSG(msg)	.data; 1: .asciz msg; .text
E 9

D 2
/*
 * kernacc - check for kernel access privileges
 *
 * We can t use the probe instruction directly because
 * it ors together current and previous mode.
 */
 ENTRY(kernacc, 0)
	movl	4(ap),r0	# virtual address
	bbcc	$31,r0,kacc1
	bbs	$30,r0,kacerr
	mfpr	$SBR,r2		# address and length of page table (system)
	bbss	$31,r2,0f; 0:
	mfpr	$SLR,r3
	brb	kacc2
kacc1:
	bbsc	$30,r0,kacc3
	mfpr	$P0BR,r2	# user P0
	mfpr	$P0LR,r3
	brb	kacc2
kacc3:
	mfpr	$P1BR,r2	# user P1 (stack)
	mfpr	$P1LR,r3
kacc2:
	addl3	8(ap),r0,r1	# ending virtual address
	addl2	$NBPG-1,r1
	ashl	$-PGSHIFT,r0,r0
	ashl	$-PGSHIFT,r1,r1
	bbs	$31,4(ap),kacc6
	bbc	$30,4(ap),kacc6
	cmpl	r0,r3		# user stack
	blss	kacerr		# address too low
	brb	kacc4
kacc6:
	cmpl	r1,r3		# compare last page to P0LR or SLR
	bgtr	kacerr		# address too high
kacc4:	
	movl	(r2)[r0],r3
	bbc	$31,4(ap),kacc4a
	bbc	$31,r3,kacerr	# valid bit is off
kacc4a:
	cmpzv	$27,$4,r3,$1	# check protection code
	bleq	kacerr		# no access allowed
	tstb	12(ap)
	bneq	kacc5		# only check read access
	cmpzv	$27,$2,r3,$3	# check low 2 bits of prot code
	beql	kacerr		# no write access
kacc5:
	aoblss	r1,r0,kacc4	# next page
	movl	$1,r0		# no errors
E 2
I 2
D 9
_rsfpsp:
	popl %eax
	movl	svesp,%esp
	movl	svebp,%ebp
	pushl %eax
E 2
	ret
E 9
I 9
	.text
E 9
D 2
kacerr:
	clrl	r0		# error
	ret
/*
 * Extracted and unrolled most common case of pagein (hopefully):
 *	resident and not on free list (reclaim of page is purely
 *	for the purpose of simulating a reference bit)
 *
 * Built in constants:
 *	CLSIZE of 2, any bit fields in pte s
 */
	.text
	.globl	Fastreclaim
Fastreclaim:
	PUSHR
#ifdef GPROF
	movl	fp,-(sp)
	movab	12(sp),fp
	jsb	mcount
	movl	(sp)+,fp
#endif GPROF
	extzv	$9,$23,28(sp),r3	# virtual address
	bicl2	$1,r3			# v = clbase(btop(virtaddr)); 
	movl	_u+U_PROCP,r5		# p = u.u_procp 
					# from vtopte(p, v) ...
	movl	$1,r2			# type = CTEXT;
	cmpl	r3,P_TSIZE(r5)
	jlssu	1f			# if (isatsv(p, v)) {
	addl3	P_TSIZE(r5),P_DSIZE(r5),r0
	cmpl	r3,r0
	jgequ	2f
	clrl	r2			#	type = !CTEXT;
1:
	ashl	$2,r3,r4
	addl2	P_P0BR(r5),r4		#	tptopte(p, vtotp(p, v));
	jbr	3f
2:
	cvtwl	P_SZPT(r5),r4		# } else (isassv(p, v)) {
	ashl	$7,r4,r4
	subl2	$0x400000,r4
	addl2	r3,r4
	ashl	$2,r4,r4
	addl2	P_P0BR(r5),r4		#	sptopte(p, vtosp(p, v));
	clrl	r2			# 	type = !CTEXT;
3:					# }
	bitb	$0x82,3(r4)
	beql	2f			# if (pte->pg_v || pte->pg_fod)
	POPR; rsb			#	let pagein handle it
2:
	bicl3	$0xffe00000,(r4),r0
	jneq	2f			# if (pte->pg_pfnum == 0)
	POPR; rsb			# 	let pagein handle it 
2:
	subl2	_firstfree,r0
	ashl	$-1,r0,r0	
	incl	r0			# pgtocm(pte->pg_pfnum) 
	mull2	$SZ_CMAP,r0
	addl2	_cmap,r0		# &cmap[pgtocm(pte->pg_pfnum)] 
	tstl	r2
	jeql	2f			# if (type == CTEXT &&
	jbc	$C_INTRANS,(r0),2f	#     c_intrans)
	POPR; rsb			# 	let pagein handle it
2:
	jbc	$C_FREE,(r0),2f		# if (c_free)
	POPR; rsb			# 	let pagein handle it 
2:
	bisb2	$0x80,3(r4)		# pte->pg_v = 1;
	jbc	$26,4(r4),2f		# if (anycl(pte, pg_m) 
	bisb2	$0x04,3(r4)		#	pte->pg_m = 1;
2:
	bicw3	$0x7f,2(r4),r0
	bicw3	$0xff80,6(r4),r1
	bisw3	r0,r1,6(r4)		# distcl(pte);
	ashl	$PGSHIFT,r3,r0
	mtpr	r0,$TBIS
	addl2	$NBPG,r0
	mtpr	r0,$TBIS		# tbiscl(v); 
	tstl	r2
	jeql	2f			# if (type == CTEXT) 
	movl	P_TEXTP(r5),r0
	movl	X_CADDR(r0),r5		# for (p = p->p_textp->x_caddr; p; ) {
	jeql	2f
	ashl	$2,r3,r3
3:
	addl3	P_P0BR(r5),r3,r0	#	tpte = tptopte(p, tp);
	bisb2	$1,P_FLAG+3(r5)		#	p->p_flag |= SPTECHG;
	movl	(r4),(r0)+		#	for (i = 0; i < CLSIZE; i++)
	movl	4(r4),(r0)		#		tpte[i] = pte[i];
	movl	P_XLINK(r5),r5		#	p = p->p_xlink;
	jneq	3b			# }
2:					# collect a few statistics...
	incl	_u+U_RU+RU_MINFLT	# u.u_ru.ru_minflt++;
	moval	_cnt,r0
	incl	V_FAULTS(r0)		# cnt.v_faults++; 
	incl	V_PGREC(r0)		# cnt.v_pgrec++;
	incl	V_FASTPGREC(r0)		# cnt.v_fastpgrec++;
	incl	V_TRAP(r0)		# cnt.v_trap++;
	POPR
	addl2	$8,sp			# pop pc, code
	mtpr	$HIGH,$IPL		## dont go to a higher IPL (GROT)
	rei
#endif newway
E 2
I 2

D 9
svesp:	.long 0
svebp:	.long 0
E 9
I 9
/*
 * Trap and fault vector routines
 */ 
D 14
#define	TRAP(a)	pushl $ a; jmp alltraps
E 14
I 14
D 16
#define	TRAP(a)		pushl $ a; jmp alltraps
E 16
I 16
D 27
#define	TRAP(a)		pushl $a ; jmp alltraps
E 27
I 27
#define	TRAP(a)		pushl $(a) ; jmp alltraps
E 27
E 16
#ifdef KGDB
D 16
#define	BPTTRAP(a)	pushl $ a; jmp bpttraps
E 16
I 16
D 27
#define	BPTTRAP(a)	pushl $a ; jmp bpttraps
E 27
I 27
#define	BPTTRAP(a)	pushl $(a) ; jmp bpttraps
E 27
E 16
#else
#define	BPTTRAP(a)	TRAP(a)
#endif
E 14

IDTVEC(div)
	pushl $0; TRAP(T_DIVIDE)
IDTVEC(dbg)
D 14
	pushl $0; TRAP(T_TRCTRAP)
E 14
I 14
	pushl $0; BPTTRAP(T_TRCTRAP)
E 14
IDTVEC(nmi)
	pushl $0; TRAP(T_NMI)
IDTVEC(bpt)
D 14
	pushl $0; TRAP(T_BPTFLT)
E 14
I 14
	pushl $0; BPTTRAP(T_BPTFLT)
E 14
IDTVEC(ofl)
	pushl $0; TRAP(T_OFLOW)
IDTVEC(bnd)
	pushl $0; TRAP(T_BOUND)
IDTVEC(ill)
	pushl $0; TRAP(T_PRIVINFLT)
IDTVEC(dna)
	pushl $0; TRAP(T_DNA)
IDTVEC(dble)
	TRAP(T_DOUBLEFLT)
	/*PANIC("Double Fault");*/
IDTVEC(fpusegm)
	pushl $0; TRAP(T_FPOPFLT)
IDTVEC(tss)
	TRAP(T_TSSFLT)
	/*PANIC("TSS not valid");*/
IDTVEC(missing)
	TRAP(T_SEGNPFLT)
IDTVEC(stk)
	TRAP(T_STKFLT)
IDTVEC(prot)
	TRAP(T_PROTFLT)
IDTVEC(page)
	TRAP(T_PAGEFLT)
IDTVEC(rsvd)
	pushl $0; TRAP(T_RESERVED)
IDTVEC(fpu)
I 27
#ifdef NPX
	/*
	 * Handle like an interrupt so that we can call npxintr to clear the
	 * error.  It would be better to handle npx interrupts as traps but
	 * this is difficult for nested interrupts.
	 */
	pushl	$0		/* dummy error code */
	pushl	$T_ASTFLT
	pushal
	nop			/* silly, the bug is for popal and it only
				 * bites when the next instruction has a
				 * complicated address mode */
	pushl	%ds
	pushl	%es		/* now the stack frame is a trap frame */
	movl	$KDSEL,%eax
	movl	%ax,%ds
	movl	%ax,%es
	pushl	_cpl
	pushl	$0		/* dummy unit to finish building intr frame */
	incl	_cnt+V_TRAP
	call	_npxintr
	jmp	doreti
#else
E 27
	pushl $0; TRAP(T_ARITHTRAP)
I 27
#endif
E 27
	/* 17 - 31 reserved for future exp */
IDTVEC(rsvd0)
	pushl $0; TRAP(17)
IDTVEC(rsvd1)
	pushl $0; TRAP(18)
IDTVEC(rsvd2)
	pushl $0; TRAP(19)
IDTVEC(rsvd3)
	pushl $0; TRAP(20)
IDTVEC(rsvd4)
	pushl $0; TRAP(21)
IDTVEC(rsvd5)
	pushl $0; TRAP(22)
IDTVEC(rsvd6)
	pushl $0; TRAP(23)
IDTVEC(rsvd7)
	pushl $0; TRAP(24)
IDTVEC(rsvd8)
	pushl $0; TRAP(25)
IDTVEC(rsvd9)
	pushl $0; TRAP(26)
IDTVEC(rsvd10)
	pushl $0; TRAP(27)
IDTVEC(rsvd11)
	pushl $0; TRAP(28)
IDTVEC(rsvd12)
	pushl $0; TRAP(29)
IDTVEC(rsvd13)
	pushl $0; TRAP(30)
IDTVEC(rsvd14)
	pushl $0; TRAP(31)

I 27
	ALIGN32
E 27
alltraps:
	pushal
I 27
	nop
E 27
	push %ds
	push %es
I 27
	# movw	$KDSEL,%ax
E 27
	movw	$0x10,%ax
	movw	%ax,%ds
	movw	%ax,%es
I 14
calltrap:
E 14
	incl	_cnt+V_TRAP
	call	_trap
I 23
D 27

	cli

	/* this value may also be used in return_to_user_mode */
	movl	0x34(%esp),%esi /* previous cs */
	andl	$3,%esi
	jz	trap_return

	cmpl	$0,_astpending
	jnz	do_astflt

	cmpw	$0,_cpl
	jnz	return_to_user_mode /* in icu.s */

trap_return:
E 23
D 13

#ifdef junk
	cmpl	$0xfc000000,12*4(%esp)	# is it a user pc
	ja	1f 
	cmpw	$0x1f,13*4(%esp)	# is it a user cs
	je	1f 
	.data	; lx: .asciz "t user cs %x?" ; .text
2:
	movl	13*4(%esp),%eax
	pushl	%eax
	pushl	$lx
	call	_pg
	popl %eax ; popl %eax
	jmp	2b
1:
#endif junk

E 13
	pop %es
	pop %ds
	popal
I 13
	nop
E 13
	addl	$8,%esp			# pop type, code
	iret

I 23
do_astflt:
	/* pop off the old trap frame, then create a new one that
	 * will give trap() another chance
E 27
I 27
	/*
	 * Return through doreti to handle ASTs.  Have to change trap frame
	 * to interrupt frame.
E 27
	 */
D 27
	pop	%es
	pop	%ds
	popa
	addl	$8,%esp
E 27
I 27
	movl	$T_ASTFLT,4+4+32(%esp)	/* new trap type (err code not used) */
	pushl	_cpl
	pushl	$0			/* dummy unit */
	jmp	doreti
E 27

D 27
	pushl	$0
	TRAP (T_ASTFLT)
	/* NORETURN */
		


E 27
E 23
I 14
#ifdef KGDB
E 14
/*
I 14
 * This code checks for a kgdb trap, then falls through
 * to the regular trap code.
 */
I 27
	ALIGN32
E 27
bpttraps:
	pushal
I 27
	nop
E 27
	push	%es
	push	%ds
I 27
	# movw	$KDSEL,%ax
E 27
	movw	$0x10,%ax
	movw	%ax,%ds
	movw	%ax,%es
	movzwl	52(%esp),%eax
D 16
	test	$3,%eax			# make sure it's a kernel trap
E 16
I 16
	test	$3,%eax	
E 16
	jne	calltrap
D 16
	call	_kgdb_trap_glue		# won't return, if successful
E 16
I 16
	call	_kgdb_trap_glue		
E 16
	jmp	calltrap
#endif

/*
E 14
 * Call gate entry for syscall
 */

I 27
	ALIGN32
E 27
IDTVEC(syscall)
	pushfl	# only for stupid carry bit and more stupid wait3 cc kludge
	pushal	# only need eax,ecx,edx - trap resaves others
D 27
	movw	$0x10,%ax	# switch to kernel segments
	movw	%ax,%ds
	movw	%ax,%es
	call	_syscall
I 23

	cli

	cmpl	$0,_astpending
	jnz	syscall_ast

	cmpw	$0,_cpl
	jnz	syscall_fix_cpl

E 23
D 13

#ifdef notdef
	cmpw	$0x1f,10*4(%esp)	# is user cs what it should be?
	jz	1f
	.data	; lz: .asciz "s user cs %x?" ; .text
2:
	movl	10*4(%esp),%eax
	pushl	%eax
	pushl	$lz
	call	_pg
	jmp	2b
1:
#endif

E 13
	movw	__udatasel,%ax	# switch back to user segments
	movw	%ax,%ds
	movw	%ax,%es
	popal
E 27
I 13
	nop
E 13
D 27
	popfl
D 13
	lret			# back we go, we hope!
E 13
I 13
	lret
E 13

I 23
syscall_ast:
	movw	__udatasel,%ax
	movw	%ax,%ds
	movw	%ax,%es
	popal

	/* convert to trap frame
	 * stack is now ss, sp, cs,    ip, flags
	 * we want      ss, sp, flags, cs, ip   
 	 * offsets      16  12  8      4   0    
E 27
I 27
	movl	$KDSEL,%eax		# switch to kernel segments
	movl	%ax,%ds
	movl	%ax,%es
	incl	_cnt+V_SYSCALL  # kml 3/25/93
	call	_syscall
	/*
	 * Return through doreti to handle ASTs.  Have to change syscall frame
	 * to interrupt frame.
	 *
	 * XXX - we should have set up the frame earlier to avoid the
	 * following popal/pushal (not much can be done to avoid shuffling
	 * the flags).  Consistent frames would simplify things all over.
E 27
	 */
D 27
	xchgl	%eax,8(%esp) /* now eax has cs */
	xchgl	%eax,4(%esp) /* now eax has ip */
	xchgl	%eax,0(%esp) /* now eax has flags */
	xchgl	%eax,8(%esp) /* now eax has its original value */
	pushl $0
	TRAP (T_ASTFLT)
	/* NORETURN */

syscall_fix_cpl:
	movw	__udatasel,%ax
	movw	%ax,%ds
	movw	%ax,%es
E 27
I 27
	movl	32+0(%esp),%eax	/* old flags, shuffle to above cs:eip */
	movl	32+4(%esp),%ebx	/* `int' frame should have been ef, eip, cs */
	movl	32+8(%esp),%ecx
	movl	%ebx,32+0(%esp)
	movl	%ecx,32+4(%esp)
	movl	%eax,32+8(%esp)
E 27
	popal
D 27

	/* convert to trap frame
	 * stack is now ss, sp, cs,    ip, flags
	 * we want      ss, sp, flags, cs, ip   
 	 * offsets      16  12  8      4   0    
	 */
	xchgl	%eax,8(%esp) /* now eax has cs */
	xchgl	%eax,4(%esp) /* now eax has ip */
	xchgl	%eax,0(%esp) /* now eax has flags */
	xchgl	%eax,8(%esp) /* now eax has its original value */
	
	pushl $0
	pushl $ T_ASTFLT

E 27
I 27
	nop
	pushl	$0		/* dummy error code */
	pushl	$T_ASTFLT
E 27
	pushal
	nop
D 27
	push %ds
	push %es
	movw	$0x10,%ax
	movw	%ax,%ds
	movw	%ax,%es
E 27
I 27
	movl	__udatasel,%eax	/* switch back to user segments */
	push	%eax		/* XXX - better to preserve originals? */
	push	%eax
	pushl	_cpl
	pushl	$0
	jmp	doreti
E 27

D 27
	movl	$1, %esi /* non-zero to indicate return to user mode */
	jmp	return_to_user_mode /* in icu.s */

	
E 27
I 27
	ALIGN32
E 27
E 23
I 10
ENTRY(htonl)
ENTRY(ntohl)
	movl	4(%esp),%eax
	xchgb	%al,%ah
	roll	$16,%eax
	xchgb	%al,%ah
	ret

I 27
	ALIGN32
E 27
ENTRY(htons)
ENTRY(ntohs)
	movzwl	4(%esp),%eax
	xchgb	%al,%ah
	ret
I 14

I 24
D 27
/* DELAY(n)  delay about n microseconds */
ENTRY(DELAY)
	movl 4(%esp), %ecx
	incl %ecx /* make DELAY(0) go through the loop just once */

	/* 
	 * 0x80 is the manufacturing test port, which should be safe to
	 * write to on any motherboard.  The output instruction will
	 * be executed at bus speed, rather than processor speed, so
	 * it will be about 750ns on any ISA or EISA machine.
	 */
1:
	outb %al, $0x80
	loop 1b
	ret	

E 27
E 24
#include "vector.s"
D 26
#include "i386/isa/icu.s"
E 26
I 26
D 27
#include <i386/isa/icu.s>
E 27
I 27
#include "i386/isa/icu.s"
E 27
E 26
E 14
E 10
E 9
E 2
E 1
