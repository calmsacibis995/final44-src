h12995
s 00002/00002/00303
d D 8.1 93/06/11 14:58:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00063/00298
d D 7.2 93/03/09 23:47:28 utashiro 2 1
c wrong number of f's!!
c removed needless lines
e
s 00361/00000/00000
d D 7.1 92/06/04 16:03:06 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell, and Kazumasa Utashiro of Software Research
 * Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * machConst.h --
 *
 *	Machine dependent constants.
 *
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 *
 * from: $Header: /sprite/src/kernel/mach/ds3100.md/RCS/machConst.h,
 *	v 9.2 89/10/21 15:55:22 jhh Exp $ SPRITE (DECWRL)
 * from: $Header: /sprite/src/kernel/mach/ds3100.md/RCS/machAddrs.h,
 *	v 1.2 89/08/15 18:28:21 rab Exp $ SPRITE (DECWRL)
 * from: $Header: /sprite/src/kernel/vm/ds3100.md/RCS/vmPmaxConst.h,
 *	v 9.1 89/09/18 17:33:00 shirriff Exp $ SPRITE (DECWRL)
 */

#ifndef _MACHCONST
#define _MACHCONST

#define MACH_KUSEG_ADDR			0x0
#define MACH_CACHED_MEMORY_ADDR		0x80000000
#define MACH_UNCACHED_MEMORY_ADDR	0xa0000000
#define MACH_KSEG2_ADDR			0xc0000000

#define	MACH_CACHED_TO_PHYS(x)		MACH_UNMAPPED_TO_PHYS(x)
#define	MACH_UNCACHED_TO_PHYS(x)	MACH_UNMAPPED_TO_PHYS(x)
#define	MACH_UNMAPPED_TO_PHYS(x)	((unsigned)(x) & 0x1fffffff)

#define	MACH_PHYS_TO_CACHED(x)	((unsigned)(x) | MACH_CACHED_MEMORY_ADDR)
#define	MACH_PHYS_TO_UNCACHED(x) ((unsigned)(x) | MACH_UNCACHED_MEMORY_ADDR)

#define	MACH_CACHED_TO_UNCACHED(x) ((unsigned)(x) | MACH_UNCACHED_MEMORY_ADDR)
D 2
#define	MACH_UNCACHED_TO_CACHED(x) ((unsigned)(x) & 0x9ffffffff)
E 2
I 2
#define	MACH_UNCACHED_TO_CACHED(x) ((unsigned)(x) & 0x9fffffff)
E 2

#define BETWEEN(x,a,b)	((unsigned)(x) >= (a) && (unsigned)(x) < (b))

#define	MACH_IS_UNMAPPED(x) \
	BETWEEN(x, MACH_CACHED_MEMORY_ADDR, MACH_KSEG2_ADDR)
#define	MACH_IS_CACHED(x) \
	BETWEEN(x, MACH_CACHED_MEMORY_ADDR, MACH_UNCACHED_MEMORY_ADDR)
#define	MACH_IS_UNCACHED(x) \
	BETWEEN(x, MACH_UNCACHED_MEMORY_ADDR, MACH_KSEG2_ADDR)
#define	MACH_IS_MAPPED(x) \
	BETWEEN(x, MACH_CACHED_MEMORY_ADDR, MACH_KSEG2_ADDR)
#define	MACH_IS_USPACE(x) \
	((unsigned)(x) < MACH_CACHED_MEMORY_ADDR)

D 2
#ifdef sony_news
E 2
#define MACH_CODE_START			0x80001000
#define MACH_RESERVED_ADDR		0xb3000000	/* KU:XXX need this? */
#define	MACH_KERNWORK_ADDR		0x800001c0
D 2
#define	MACH_MAXMEMSIZE_ADDR		MACH_KERNWORK_ADDR + 0 * 4
#define	MACH_BOOTSW_ADDR		MACH_KERNWORK_ADDR + 1 * 4
#define	MACH_BOOTDEV_ADDR		MACH_KERNWORK_ADDR + 2 * 4
#define	MACH_HOWTO_ADDR			MACH_KERNWORK_ADDR + 3 * 4
#endif
E 2
I 2
#define	MACH_MAXMEMSIZE_ADDR		(MACH_KERNWORK_ADDR + 0 * 4)
#define	MACH_BOOTSW_ADDR		(MACH_KERNWORK_ADDR + 1 * 4)
#define	MACH_BOOTDEV_ADDR		(MACH_KERNWORK_ADDR + 2 * 4)
#define	MACH_HOWTO_ADDR			(MACH_KERNWORK_ADDR + 3 * 4)
#define	MACH_BP_ADDR			(MACH_KERNWORK_ADDR + 4 * 4)
#define	MACH_MONARG_ADDR		(MACH_KERNWORK_ADDR + 5 * 4)
E 2

D 2
#ifdef DS3100
#define MACH_CODE_START			0x80030000
#define MACH_MAX_MEM_ADDR		0xa1800000
#define MACH_CACHED_FRAME_BUFFER_ADDR	0x8fc00000
#define MACH_UNCACHED_FRAME_BUFFER_ADDR	0xafc00000
#define MACH_PLANE_MASK_ADDR		0xb0000000
#define MACH_CURSOR_REG_ADDR		0xb1000000
#define MACH_COLOR_MAP_ADDR		0xb2000000
#define MACH_RESERVED_ADDR		0xb3000000
#define MACH_WRITE_ERROR_ADDR		0xb7000000
#define MACH_NETWORK_INTERFACE_ADDR	0xb8000000
#define MACH_NETWORK_BUFFER_ADDR	0xb9000000
#define MACH_SCSI_INTERFACE_ADDR	0xba000000
#define MACH_SCSI_BUFFER_ADDR		0xbb000000
#define MACH_SERIAL_INTERFACE_ADDR	0xbc000000
#define MACH_CLOCK_ADDR			0xbd000000
#define MACH_SYS_CSR_ADDR		0xbe000000
#endif

#ifdef DS5000
#define MACH_CODE_START			0x80030000
#define MACH_MAX_MEM_ADDR		0xbe000000
#define MACH_RESERVED_ADDR		0xbfc80000
#define MACH_CHKSYN_ADDR		0xbfd00000
#define MACH_ERROR_ADDR			0xbfd80000
#define MACH_SERIAL_INTERFACE_ADDR	0xbfe00000
#define MACH_CLOCK_ADDR			0xbfe80000
#define MACH_SYS_CSR_ADDR		0xbff00000
#endif

E 2
/*
 * The bits in the cause register.
 *
 *	MACH_CR_BR_DELAY	Exception happened in branch delay slot.
 *	MACH_CR_COP_ERR		Coprocessor error.
 *				Interrupt pending bits defined below.
 *	MACH_CR_EXC_CODE	The exception type (see exception codes below).
 */
#define MACH_CR_BR_DELAY	0x80000000
#define MACH_CR_COP_ERR		0x30000000
#define MACH_CR_EXC_CODE	0x0000003C
#define MACH_CR_EXC_CODE_SHIFT	2

/*
 * The bits in the status register.  All bits are active when set to 1.
 *
 *	MACH_SR_CO_USABILITY	Control the usability of the four coprocessors.
 *	MACH_SR_BOOT_EXC_VEC	Use alternate exception vectors.
 *	MACH_SR_TLB_SHUTDOWN	TLB disabled.
 *	MACH_SR_PARITY_ERR	Parity error.
 *	MACH_SR_CACHE_MISS	Most recent D-cache load resulted in a miss.
 *	MACH_SR_PARITY_ZERO	Zero replaces outgoing parity bits.
 *	MACH_SR_SWAP_CACHES	Swap I-cache and D-cache.
 *	MACH_SR_ISOL_CACHES	Isolate D-cache from main memory.
 *				Interrupt enable bits defined below.
 *	MACH_SR_KU_OLD		Old kernel/user mode bit. 1 => user mode.
 *	MACH_SR_INT_ENA_OLD	Old interrupt enable bit.
 *	MACH_SR_KU_PREV		Previous kernel/user mode bit. 1 => user mode.
 *	MACH_SR_INT_ENA_PREV	Previous interrupt enable bit.
 *	MACH_SR_KU_CUR		Current kernel/user mode bit. 1 => user mode.
 *	MACH_SR_INT_ENA_CUR	Current interrupt enable bit.
 */
#define MACH_SR_COP_USABILITY	0xf0000000
#define MACH_SR_COP_0_BIT	0x10000000
#define MACH_SR_COP_1_BIT	0x20000000
#define MACH_SR_BOOT_EXC_VEC	0x00400000
#define MACH_SR_TLB_SHUTDOWN	0x00200000
#define MACH_SR_PARITY_ERR	0x00100000
#define MACH_SR_CACHE_MISS	0x00080000
#define MACH_SR_PARITY_ZERO	0x00040000
#define MACH_SR_SWAP_CACHES	0x00020000
#define MACH_SR_ISOL_CACHES	0x00010000
#define MACH_SR_KU_OLD		0x00000020
#define MACH_SR_INT_ENA_OLD	0x00000010
#define MACH_SR_KU_PREV		0x00000008
#define MACH_SR_INT_ENA_PREV	0x00000004
#define MACH_SR_KU_CUR		0x00000002
#define MACH_SR_INT_ENA_CUR	0x00000001
#define MACH_SR_MBZ		0x0f8000c0

/*
 * The interrupt masks.
 * If a bit in the mask is 1 then the interrupt is enabled (or pending).
 */
#define MACH_INT_MASK		0xff00
#define MACH_INT_MASK_5		0x8000
#define MACH_INT_MASK_4		0x4000
#define MACH_INT_MASK_3		0x2000
#define MACH_INT_MASK_2		0x1000
#define MACH_INT_MASK_1		0x0800
#define MACH_INT_MASK_0		0x0400
#define MACH_HARD_INT_MASK	0xfc00
#define MACH_SOFT_INT_MASK	0x0300
#define MACH_SOFT_INT_MASK_1	0x0200
#define MACH_SOFT_INT_MASK_0	0x0100

D 2
#if defined(news3400) && !defined(PMAXSPL)
E 2
#define	MACH_SPL_MASK_8		0x0000
#define	MACH_SPL_MASK_7		MACH_SPL_MASK_8 | MACH_INT_MASK_5
#define	MACH_SPL_MASK_6		MACH_SPL_MASK_7 | MACH_INT_MASK_4
#define	MACH_SPL_MASK_5		MACH_SPL_MASK_6 | MACH_INT_MASK_3
#define	MACH_SPL_MASK_4		MACH_SPL_MASK_5 | MACH_INT_MASK_2
#define	MACH_SPL_MASK_3		MACH_SPL_MASK_4 | MACH_INT_MASK_1
#define	MACH_SPL_MASK_2		MACH_SPL_MASK_3 | MACH_INT_MASK_0
#define	MACH_SPL_MASK_1		MACH_SPL_MASK_2 | MACH_SOFT_INT_MASK_1
#define	MACH_SPL_MASK_0		MACH_SPL_MASK_1 | MACH_SOFT_INT_MASK_0
D 2
#endif
E 2

/*
 * The system control status register.
 */
D 2
#ifdef DS3100
#define MACH_CSR_MONO		0x0800
#define MACH_CSR_MEM_ERR	0x0400
#define	MACH_CSR_VINT		0x0200
#define	MACH_CSR_MBZ		0x9800
#endif

#ifdef DS5000
#define	MACH_CSR_IOINT_MASK	0x000000FF
#define MACH_CSR_BAUD38		0x00000100
#define MACH_CSR_DIAGDN		0x00000200
#define MACH_CSR_BNK32M		0x00000400
#define MACH_CSR_TXDIS		0x00000800
#define MACH_CSR_LEDIAG		0x00001000
#define MACH_CSR_CORRECT	0x00002000
#define MACH_CSR_ECCMD		0x0000C000
#define MACH_CSR_IOINTEN_MASK	0x00FF0000
#define	MACH_CSR_IOINTEN_SHIFT	16
#define MACH_CSR_NRMMOD		0x01000000
#define	MACH_CSR_REFEVEN	0x02000000
#define	MACH_CSR_PRSVNVR	0x04000000
#define	MACH_CSR_PSWARN		0x08000000
#define	MACH_CSR_MBZ		0xFF000000
#endif
E 2

/*
 * The bits in the context register.
 */
#define MACH_CNTXT_PTE_BASE	0xFFE00000
#define MACH_CNTXT_BAD_VPN	0x001FFFFC

/*
 * Location of exception vectors.
 */
#define MACH_RESET_EXC_VEC	0xBFC00000
#define MACH_UTLB_MISS_EXC_VEC	0x80000000
#define MACH_GEN_EXC_VEC	0x80000080

/*
 * Coprocessor 0 registers:
 *
 *	MACH_COP_0_TLB_INDEX	TLB index.
 *	MACH_COP_0_TLB_RANDOM	TLB random.
 *	MACH_COP_0_TLB_LOW	TLB entry low.
 *	MACH_COP_0_TLB_CONTEXT	TLB context.
 *	MACH_COP_0_BAD_VADDR	Bad virtual address.
 *	MACH_COP_0_TLB_HI	TLB entry high.
 *	MACH_COP_0_STATUS_REG	Status register.
 *	MACH_COP_0_CAUSE_REG	Exception cause register.
 *	MACH_COP_0_EXC_PC	Exception PC.
 *	MACH_COP_0_PRID		Processor revision identifier.
 */
#define MACH_COP_0_TLB_INDEX	$0
#define MACH_COP_0_TLB_RANDOM	$1
#define MACH_COP_0_TLB_LOW	$2
#define MACH_COP_0_TLB_CONTEXT	$4
#define MACH_COP_0_BAD_VADDR	$8
#define MACH_COP_0_TLB_HI	$10
#define MACH_COP_0_STATUS_REG	$12
#define MACH_COP_0_CAUSE_REG	$13
#define MACH_COP_0_EXC_PC	$14
#define MACH_COP_0_PRID		$15

/*
 * Values for the code field in a break instruction.
 */
#define MACH_BREAK_INSTR	0x0000000d
#define MACH_BREAK_VAL_MASK	0x03ff0000
#define MACH_BREAK_VAL_SHIFT	16
#define MACH_BREAK_KDB_VAL	512
#define MACH_BREAK_SSTEP_VAL	513
#define MACH_BREAK_BRKPT_VAL	514
#define MACH_BREAK_KDB		(MACH_BREAK_INSTR | \
				(MACH_BREAK_KDB_VAL << MACH_BREAK_VAL_SHIFT))
#define MACH_BREAK_SSTEP	(MACH_BREAK_INSTR | \
				(MACH_BREAK_SSTEP_VAL << MACH_BREAK_VAL_SHIFT))
#define MACH_BREAK_BRKPT	(MACH_BREAK_INSTR | \
				(MACH_BREAK_BRKPT_VAL << MACH_BREAK_VAL_SHIFT))

/*
 * Mininum and maximum cache sizes.
 */
#define MACH_MIN_CACHE_SIZE	(16 * 1024)
#define MACH_MAX_CACHE_SIZE	(256 * 1024)

/*
 * The floating point version and status registers.
 */
#define	MACH_FPC_ID	$0
#define	MACH_FPC_CSR	$31

/*
 * The floating point coprocessor status register bits.
 */
#define MACH_FPC_ROUNDING_BITS		0x00000003
#define MACH_FPC_ROUND_RN		0x00000000
#define MACH_FPC_ROUND_RZ		0x00000001
#define MACH_FPC_ROUND_RP		0x00000002
#define MACH_FPC_ROUND_RM		0x00000003
#define MACH_FPC_STICKY_BITS		0x0000007c
#define MACH_FPC_STICKY_INEXACT		0x00000004
#define MACH_FPC_STICKY_UNDERFLOW	0x00000008
#define MACH_FPC_STICKY_OVERFLOW	0x00000010
#define MACH_FPC_STICKY_DIV0		0x00000020
#define MACH_FPC_STICKY_INVALID		0x00000040
#define MACH_FPC_ENABLE_BITS		0x00000f80
#define MACH_FPC_ENABLE_INEXACT		0x00000080
#define MACH_FPC_ENABLE_UNDERFLOW	0x00000100
#define MACH_FPC_ENABLE_OVERFLOW	0x00000200
#define MACH_FPC_ENABLE_DIV0		0x00000400
#define MACH_FPC_ENABLE_INVALID		0x00000800
#define MACH_FPC_EXCEPTION_BITS		0x0003f000
#define MACH_FPC_EXCEPTION_INEXACT	0x00001000
#define MACH_FPC_EXCEPTION_UNDERFLOW	0x00002000
#define MACH_FPC_EXCEPTION_OVERFLOW	0x00004000
#define MACH_FPC_EXCEPTION_DIV0		0x00008000
#define MACH_FPC_EXCEPTION_INVALID	0x00010000
#define MACH_FPC_EXCEPTION_UNIMPL	0x00020000
#define MACH_FPC_COND_BIT		0x00800000
#define MACH_FPC_MBZ_BITS		0xff7c0000

/*
 * Constants to determine if have a floating point instruction.
 */
#define MACH_OPCODE_SHIFT	26
#define MACH_OPCODE_C1		0x11

/*
 * The low part of the TLB entry.
 */
#define VMMACH_TLB_PF_NUM		0xfffff000
#define VMMACH_TLB_NON_CACHEABLE_BIT	0x00000800
#define VMMACH_TLB_MOD_BIT		0x00000400
#define VMMACH_TLB_VALID_BIT		0x00000200
#define VMMACH_TLB_GLOBAL_BIT		0x00000100

#define VMMACH_TLB_PHYS_PAGE_SHIFT	12

/*
 * The high part of the TLB entry.
 */
#define VMMACH_TLB_VIRT_PAGE_NUM	0xfffff000
#define VMMACH_TLB_PID			0x00000fc0
#define VMMACH_TLB_PID_SHIFT		6
#define VMMACH_TLB_VIRT_PAGE_SHIFT	12

/*
 * The shift to put the index in the right spot.
 */
#define VMMACH_TLB_INDEX_SHIFT		8

/*
 * The number of TLB entries and the first one that write random hits.
 */
#define VMMACH_NUM_TLB_ENTRIES		64
#define VMMACH_FIRST_RAND_ENTRY 	8

/*
 * The number of process id entries.
 */
#define	VMMACH_NUM_PIDS			64

/*
 * TLB probe return codes.
 */
#define VMMACH_TLB_NOT_FOUND		0
#define VMMACH_TLB_FOUND		1
#define VMMACH_TLB_FOUND_WITH_PATCH	2
#define VMMACH_TLB_PROBE_ERROR		3

/*
 * Kernel virtual address for user page table entries
 * (i.e., the address for the context register).
 */
#define VMMACH_PTE_BASE		0xFFC00000

#endif /* _MACHCONST */
E 1
