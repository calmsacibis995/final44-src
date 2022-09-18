/* 
 * Mach Operating System
 * Copyright (c) 1993,1991 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	vax_init.s,v $
 * Revision 2.8  93/02/01  09:53:50  danner
 * 	Changed '(r3)+' to 'OFFSET(r3)' to deal with boot_info block
 * 	changes.
 * 	[93/01/27            dbg]
 * 
 * Revision 2.7  93/01/24  14:14:46  danner
 * 	Fixed a few comments. The gcc preprossesor doesn't like
 * 	comments staring with # (. Thinks they are directives.
 * 	[93/01/17            mrt]
 * 
 * Revision 2.6  92/01/03  20:33:37  dbg
 * 	Move symbol table and bootstrap image out of BSS.
 * 	[91/08/02            dbg]
 * 
 * Revision 2.5  91/06/26  17:53:27  rpd
 * 	Fixed local-label bug so r2d2 works.
 * 	[91/06/26            rpd]
 * 
 * Revision 2.4  91/06/19  12:01:47  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:58:02  rvb]
 * 
 * 	VAX3100: Get device and mem_bitmap parameters from ultrix.
 * 	[91/06/11            rvb]
 * 	Support for VaxStation 3100: new processor number
 * 	[91/06/04            rvb]
 * 
 * Revision 2.3  91/05/14  17:46:29  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:28:20  dbg
 * 	Created.
 * 	[91/04/11            dbg]
 * 
 */

/*
 * Vax physical-mode initialization code in assembler.  GCC and
 * PCC differ on whether various C constructs generate PC-relative
 * addresses (physical) or absolute addresses (virtual).
 */

#include <cpus.h>
#include <platforms.h>
#include <emul.h>
#include <mach_kdb.h>
#include <mach_load.h>

#include <mach/vax/vm_param.h>

#include <sys/reboot.h>

#include <vax/asm.h>
#include <vax/cpu_data.h>
#include <vax/mtpr.h>
#include <vax/pmap.h>

#include <assym.s>

	.set	KERNELBASE,0x80000000		# kernel VA starts here

/*
 * CPU starts here.
 *
 *	ipl	0x1f	all blocked
 *	mapen	0	physical mode
 *			other processor registers not set.
 *
 * Registers contain:
 *	r11		boot flags
 *	r10		boot device
 *	r9		PA of end of loaded memory
 *			(if (r11 & 0x04))
 *	r8		bitmap pointer (650)
 *	r7		bitmap size (650)
 *			CCA address (6200)
 */

	.text

	.globl	start			# first CPU starts here
start:	.word	0			# loader expects a procedure entry mask
	mtpr	$0,$(ICCS)		# turn off interval timer
	.globl	jmp_start
jmp_start:				# other CPUs start here (?)

#if	NCPUS > 1
try:	bbssi	$1,_start_lock,wait
	brb	0f
wait:	bbs	$1,_start_lock,wait
	brb	try
0:	bbssi	$0,_start_lock,1f
	brb	2f
1:	jmp	slave_start
2:
	moval	cpu_number_zero,_Cpu_number_ptr	# set up for zero cpu number
#endif	/* NCPUS > 1 */

/*
 * Initialize machine
 */

	moval	_eintstack,sp		# get the boot-time stack
	moval	_scb,r0			# set up the SCB
	mtpr	r0,$(SCBB)
	moval	_intstack,r0		# set up the PCB
	mtpr	r0,$(PCBB)
	mtpr	$0,$(SSP)		# clear the current thread pointer
	mtpr	$0,$(ESP)		# clear the current stack pointer

/*
 * Move symbol table out of the way of BSS.
 *
 * When kernel is loaded, at the start of BSS we have:
 * _edata:
 *		.long	magic_number
 *		.long	kern_sym_size
 *		.long	boot_image_size
 *		.long	load_info_size
 * sym_start:
 *		kernel symbols
 *		.align	2
 * boot_start:
 *		bootstrap image
 *		.align	2
 * load_info_start:
 *		bootstrap load information
 *
 * all of which must be moved somewhere else, since it
 * is sitting in the kernel BSS.  In addition, the bootstrap
 * image must be moved to a machine page boundary, so that we get:
 *
 * _edata:
 *		BSS
 * _end:			<-	kern_sym_start (VA)
 *		kernel symbols		.
 *		.align 2		. (kern_sym_size)
 *					.
 *		.align VAX_PAGE_SIZE
 *				<-	boot_start (VA)
 *		bootstrap image
 *				<-	load_info_start (VA)
 *		load information
 *				<-	r9 (PA)
 *
 */
	movab	_edata,r3		# point to struct boot_info
	movl	BI_SYM_SIZE(r3),r6	# get symbol table size

	movab	_end+VAX_PGBYTES-1[r6],r5
					#  use indexing to keep PC-relative
					#  addressing, to get phys address
					# point after BSS, add symbol size,
					# and round up to
	bicl2	$(VAX_PGBYTES-1),r5	# machine page boundary
	movab	KERNELBASE(r5),_boot_start
					# save VA of start of bootstrap
	movl	BI_BOOT_SIZE(r3),r0	# get size of bootstrap
	movl	r0,_boot_size		# save size of bootstrap
	addl3	_boot_start,r0,_load_info_start
					# save VA of start of loader info
	movl	BI_LOAD_INFO_SIZE(r3),r1
					# get size of loader info
	movl	r1,_load_info_size	# save size of loader info
	addl2	r1,r0			# get total size to move

	movab	BI_SIZE(r3)[r6],r3	# point to start of boot image - source

	addl2	r0,r3			# point to end of source
	addl2	r0,r5			# point to end of destination
	movl	r5,r9			# save as first free PA

	ashl	$-2,r0,r0		# move bootstrap and loader info:
0:	movl	-(r3),-(r5)		# backwards, by longwords
	sobgtr	r0,0b

	movl	$_end,_kern_sym_start	# save VA of start of symbols
	movl	r6,_kern_sym_size	# save symbol table size
	beql	1f			# if there are symbols:

					# r3 already points to start of boot
					# equals end of symbol table (source)
	movab	_end[r6],r5		# point to end of dst (PA)

	ashl	$-2,r6,r0		# move symbols: backwards, by longwords
0:	movl	-(r3),-(r5)
	sobgtr	r0,0b
1:

/*
 * Zero BSS
 */

	moval	_edata,r1		# _edata PA
	moval	_end,r0			# _end PA
	subl2	r1,r0			# size of BSS
	ashl	$-2,r0,r0		# clear by longs
0:	clrl	(r1)+
	sobgtr	r0,0b

/*
 * Save boot parameters
 */

	movl	r11,_boothowto		# boot flags
	movl	r10,_bootdev		# boot device

	movl	r8,_boot_reg8		# reg 8
	movl	r7,_boot_reg7		# reg 7

/*
 * Get CPU type and size memory.
 */

#define	cpu		r6

#define	mem_high	r8
#define	avail_start	r9
					# left from boot

	mfpr	$(SID),cpu		# get CPU ID
	extzv	$24,$8,cpu,cpu		# get CPU number bits
#if	VAX650 || VAX6200 || VAX3100
	cmpl	cpu,$(VAX_650)		# if KA650:
	beql	1f
	brw	6f
1:	movl	*$(SYSTYPE),r0		# look at 'systype' for real type
	extzv	$24,$8,r0,r0
#if	VAX650
	cmpl	r0,$1			# 1 is VAX_650
	bneq	1f
	movl	r7,_mem_bitmap_size	# save bitmap size
	movl	r8,_mem_bitmap		# and pointer
					# bitmap is at end of memory
	jmp	9f
1:
#endif
#if	VAX6200
	cmpl	r0,$2			# 2 is VAX_6200
	bneq	1f
	movl	$(VAX_6200),cpu
	movl	r7,_ccap		# get CCA physical address
	movl	CCA_BITMAP_SZ(r7),_mem_bitmap_size
					# get bitmap size
	movl	CCA_BITMAP(r7),r8	# and pointer
	movl	r8,_mem_bitmap		# bitmap is at end of memory
	jmp	9f
1:
#endif
#if	VAX3100
	cmpl	r0,$3
	bneq	1f
	halt				# I wonder what got 3
1:
	cmpl	r0,$4
	beql	0f
	brw	1f
0:	movl	$(VAX_3100),cpu
/*			10	size
			14	extended rpb
			18	size
			1c	arg list to vmb
				1c R0	name desc
				20 R1	xxx
				24 R2	size
				28 R3	bitmap
				2c R4	xxx
				30 R5	flags
				34	iovec
					30	boot dev name
				64	 unit
*/
	movl	4(ap),r1	#vmb_info == arg0
	movl	0x14(r1),r1	#extended rpb

	movl	0x24(r1),r7
	movl	r7,_boot_reg7		# reg 7
	movl	r7,_mem_bitmap_size	# save bitmap size
	movl	0x28(r1),r8		# and pointer
	movl	r8,_boot_reg8		# reg 8
	movl	r8,_mem_bitmap

	movl	0x34(r1),r0		# iovector
	addl2	0x30(r0),r0		# boot dev name
	cmpw	(r0),$0x4b44		# == dk?
	beql	0f
8:	halt
	brb	8b

0:	movl	$0xa0000015,r10		# MAJOR 21 (dec) == scsi
	movw	0x1c+2(r1),r2
	cmpw	r2,$0x1fc		# 3fc is intr 0 == B
	bneq	0f
	 bisl2	$(1<<B_CONTROLLERSHIFT), r10
	 brb	7f
0:	cmpw	r2,$0x1f8		# 3f8 is intr 1 == A
	beql	0f
8:	halt
	brb	8b
0:	 bisl2	$(0<<B_CONTROLLERSHIFT), r10
7:	clrl	r3
	movw	0x64(r1),r3
	divl2	$100,r3			# disk unit -- ignore lun
	ashl	$(B_UNITSHIFT),r3,r3
	bisl3	r3,r10,_bootdev		# boot device
	brb	9f
1:
#endif
	halt				# others are invalid
#endif	/* VAX650 || VAX6200 || VAX3100 */
6:
#if	VAX820
	cmpl	cpu,$(VAX_820)		# for KA820:
	bneq	0f			# check whether correctly initialized

	bisl3	0x2008000c,0x20080010,r0 # check EINTRCSR | INTRDES
	beql	1f			# if not zero,
	pushab	2f			# reset the system
	calls	$1,_printf
	movl	$0x10000000,0x20088000	# (to port controller)
1:
	.data
2:	.ascii	"\n"
	.ascii	"You forgot to reset the system before you did a reboot.\n"
	.asciz	"No problem, I'll do it for you.\n"
	.text
0:
#endif
	bicl3	$0xffff,avail_start,mem_high
					# start at end of loaded memory,
					# on 64K boundary
	movl	cpu,_cpu		# set _cpu for badaddr
3:
	pushl	$4			# probe for a longword
	pushl	mem_high		# at mem_high
	calls	$2,_badaddr
	tstl	r0			# r0 == 0 if OK
	bneq	4f
	acbl	$(512*1024*1024)-1,$(64*1024),mem_high,3b
					# probe in 64K increments
					# up to 512Meg
4:
	cmpl	cpu,$(VAX_630)		# if a uVAX II,
	bneq	5f
	subl2	$4096,mem_high		# allow 4K for bitmap and console
	brb	9f
5:
9:	movl	cpu,_cpu		# save CPU ID

#if	MACH_LOAD

/*
 * Get load point if not loaded at physical 0
 */

#define	loadpt	r7

	moval	ZERO_PHYS,loadpt	# get physical start of kernel
	movl	loadpt,_loadpt		# save as loadpt
	subl	loadpt,_boot_start	# fix boot_start virtual address
#endif

/*
 * Allow patching mem_size to limit memory.
 */

	movl	_mem_size,r0		# desired memory size
	beql	0f			# use size found if not set
#if	MACH_LOAD
	addl2	loadpt,r0		# (get high memory address)
#endif
	cmpl	r0,mem_high		# too much?
	bleq	0f
	movl	r0,mem_high
0:
#if	MACH_LOAD
	subl3	loadpt,mem_high,_mem_size
#else
	movl	mem_high,_mem_size	# record size of memory
#endif

/*
 * initialize RPB
 */

#if	MACH_LOAD
	clrl	r0			# rpb in local memory
#else
	movab	_rpb,r0
#endif
	movl	r0,(r0)+		# p->rp_selfref = p
	movab	_doadump,r1
	movl	r1,(r0)+		# p->rp_dumprout = _doadump
	movl	$32,r2			# checksum doadump
	clrl	r3
0:	addl2	(r1)+,r3
	sobgtr	r2,0b
	movl	r3,(r0)+
	clrl	(r0)			# clear restart flag
	

/*
 * test for D float (uVax I only?)
 */

	calls	$0,_dfloat_test

/*
 * Fix up register masks for some routines
 */

	bisw2	$0x0fff,_panic

/*
 * Initialize kernel physical memory, mapping the region from
 * loadpt to avail_start.
 */

#define	sbr	r10
#define	slr	r11

	addl2	$(VAX_PGBYTES-1),avail_start
	bicl2	$(VAX_PGBYTES-1),avail_start
					# round up to VAX page boundary

/*
 * Available physical memory runs from avail_start to mem_high.
 *
 * Calculate size of system page table.  It must allow at least
 * min_virtual_size bytes to be mapped.
 */

	movl	avail_start,sbr		# set SBR
	ashl	$-2,_kernel_pmap_size,slr
					# kernel PMAP size set?
	bneq	0f			# use it if so
	subl3	avail_start,mem_high,r0	# get memory size
	ashl	$-7,r0,slr		# / 128
	ashl	$(VAX_PGSHIFT),slr,r0	# will map this much memory
	cmpl	r0,_min_virtual_size	# will it map enough?
	bgtr	0f			# if not:
	ashl	$(-VAX_PGSHIFT),_min_virtual_size,slr
					#    map min_virtual_size
0:

/*
 * Align end of system page table to VAX page boundary.
 * Save as start of available physical memory.
 */

	moval	(sbr)[slr],avail_start	# get physical end of page table
	addl2	$(VAX_PGBYTES-1),avail_start
	bicl2	$(VAX_PGBYTES-1),avail_start
					# align to VAX page boundary
	subl3	sbr,avail_start,slr	# and recalculate
	ashl	$-2,slr,slr		# slr

#define	pfn	r0
#define	ptx	r1
#define	lim	r2

#define	MAP_VA(prot) \
	extzv	$9,$21,lim,lim; \
0:	bisl3	$(VAX_PTE_VALID|prot),pfn,(sbr)[ptx]; \
	incl	pfn; \
	aoblss	lim,ptx,0b

#if	MACH_LOAD
	ashl	$(-VAX_PGSHIFT),_loadpt,pfn	# first PFN to be mapped
#else
	clrl	pfn
#endif
	clrl	ptx				# map starting at KERNELBASE

/*
 * Map VM_MIN_VIRTUAL_ADDRESS to start_text as KW
 */
	movl	$_start_text+VAX_PGBYTES-1, lim
	MAP_VA(VAX_PTE_KW)

#if	VAX650 || VAX6200 || VAX3100
#if	NEMUL > 0

/*
 * The Ultr*x instruction emulator is built contiguously, with page-size
 * padding at start and end.  We map only that part of the kernel to
 * user space.
 */
/*
 * Map start_text to beginning of emulation code as KR
 */
	movl	$vax$emul_begin,lim
	MAP_VA(VAX_PTE_KR)

/*
 * Map emulation code UR
 */
	movl	$vax$emul_end+VAX_PGBYTES-1,lim
	MAP_VA(VAX_PTE_UR)

/*
 * Map rest of kernel text KR
 */
	movl	$_etext,lim
	MAP_VA(VAX_PTE_KR)

#else	/* NEMUL > 0 */

/*
 * The Berkeley instruction emulator is who knows where.  Map the
 * entire kernel text to user space (BSD does that).
 */
	movl	$_etext,lim
	MAP_VA(VAX_PTE_UR)

#endif	/* NEMUL > 0 */

#else	/* VAX650 || VAX6200 || VAX3100*/

/*
 * Map kernel text KR (no emulator).
 */
	movl	$_etext,lim
	MAP_VA(VAX_PTE_KR)

#endif	/* VAX650 || VAX6200 || VAX3100 */

/*
 * map etext to end of system page table as KW
 */

	movab	KERNELBASE(avail_start),lim
#if	MACH_LOAD
	subl2	loadpt,lim
#endif
	MAP_VA(VAX_PTE_KW)

/*
 * Clear the rest of the system page table
 */

	cmpl	ptx,slr
	beql	1f
0:	clrl	(sbr)[ptx]
	aoblss	slr,ptx,0b
1:

/*
 * Set first,last PA and VA
 *
 * first PA = end of system page table
 */

	movl	avail_start,_avail_start

/*
 * last PA = mem_high
 */

	movl	mem_high,_avail_end

/*
 * first VA = end of system page table.
 */

	movab	KERNELBASE(avail_start),_virtual_avail
#if	MACH_LOAD
	subl2	loadpt,_virtual_avail
#endif

/*
 * last VA = last page mappable by system page table
 */

	ashl	$(VAX_PGSHIFT),slr,r0
	movab	KERNELBASE(r0),_virtual_end

/*
 * end of page-table initialization.
 * Map the kernel into system space.
 * Double-map the kernel into P0 space for the jump to virtual mode.
 */

	movl	sbr,_vax_sbr		# save SBR PA
	movl	slr,_vax_slr		# save SLR
	mtpr	sbr,$(SBR)
	mtpr	slr,$(SLR)

	movab	KERNELBASE(sbr),_vax_vsbr
#if	MACH_LOAD
	subl2	_loadpt,_vax_vsbr
#endif
					# save SBR VA
	mtpr	_vax_vsbr,$(P0BR)	# double-map kernel
	mtpr	slr,$(P0LR)

/*
 * Switch to virtual addresses
 */

	mtpr	$0,$(TBIA)
	mtpr	$1,$(MAPEN)
	jmp	*$0f
0:
#if	NCPUS > 1
	moval	cpu_number_zero,_Cpu_number_ptr	# set up for zero cpu number
#endif

#if	NEMUL > 0
#if	defined(VAX630) || defined(VAX650) || defined(VAX6200) || defined(VAX3100)
	/*
	 *	These two SCB vectors are reserved to DIGITAL and used by
	 *	the emulation code.
	 */
	movl	$vax$emulate,_scb+0xc8
	movl	$vax$emulate_fpd,_scb+0xcc
#endif	defined(VAX630) || defined(VAX650) || defined(VAX6200) || defined(VAX3100)
#endif	NEMUL > 0

	moval	_eintstack,sp		# switch to virtual stack
	clrl	fp			# clear traceback
	clrl	ap
	calls	$0,_machine_startup	# start up the system
	halt				# NOTREACHED

#if	NCPUS > 1
	.data
foo_stack:
	.space	512
efoo_stack:
	.text
slave_start:
	moval	_scb,r0				# set up SCB (physical address)
	mtpr	r0,$(SCBB)
	/* go into mapped mode */
	mtpr	_vax_sbr,$(SBR)
	mtpr	_vax_slr,$(SLR)
	mtpr	_vax_vsbr,$(P0BR)		# double map for jmp below
	mtpr	_vax_slr,$(P0LR)

	mtpr	$0,$(TBIA); mtpr $1,$(MAPEN); jmp *$0f; 0:

	moval	efoo_stack,sp
	CPU_NUMBER_R0				# get the cpu number
	movl	_interrupt_stack[r0],r0		# get its interrupt stack
	movab	INTSTACK_SIZE(r0),sp		# use top for stack
	extzv	$0,$30,r0,r0			# strip out high bits
	extzv	$9,$21,r0,r1			# get page number
	insv	*_vax_vsbr[r1],$9,$21,r0	# insert physical page number
						# in proper place
	mtpr	r0,$(PCBB)			# use bottom of stack as PCB
						# (for other stack pointers)
	mtpr	$0,$(SSP)			# clear current thread pointer
	mtpr	$0,$(ESP)			# clear current stack pointer
	bbcci	$1,_start_lock,1f		# release the lock
1:
	calls	$0,_slave_main
	halt
#endif	NCPUS > 1

