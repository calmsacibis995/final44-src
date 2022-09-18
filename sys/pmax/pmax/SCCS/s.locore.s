h53458
s 00030/00010/03098
d D 8.7 95/06/02 17:25:24 ralph 23 22
c final changes for pmax 4.4-Lite II release
e
s 00008/00000/03100
d D 8.6 94/07/03 14:51:20 mckusick 22 21
c minor debug checking code (from Ralph)
e
s 00048/00043/03052
d D 8.5 94/01/04 17:30:16 mckusick 21 20
c changes for 4.4BSD-Lite requested by USL
c NOT SEMANTIC SUGAR -- change to exec init, not hand-craft it
e
s 00031/00026/03064
d D 8.4 93/11/30 16:17:36 mckusick 20 19
c update from Ralph
e
s 00037/00037/03053
d D 8.3 93/09/23 16:38:38 bostic 19 18
c changes for 4.4BSD-Lite requested by USL
e
s 00008/00009/03082
d D 8.2 93/09/21 07:59:36 bostic 18 17
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/03089
d D 8.1 93/06/16 18:26:42 bostic 17 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/03089
d R 8.1 93/06/10 23:07:18 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00136/00126/02955
d D 7.15 93/05/09 17:46:36 ralph 15 14
c new improved pmap changes
e
s 00022/00000/03059
d D 7.14 93/04/05 21:39:59 ralph 14 13
c define stuff for vmstat. Probably need to fix this.
e
s 00121/00184/02938
d D 7.13 93/02/26 19:13:38 ralph 13 12
c use .set noreorder for better gas code.
e
s 00093/00054/03029
d D 7.12 93/02/04 19:54:38 ralph 12 11
c changes for a.out format and gas
e
s 00044/00000/03039
d D 7.11 92/11/15 16:30:32 ralph 11 10
c updates from Rick Macklem for maxine.
e
s 00015/00000/03024
d D 7.10 92/10/24 14:17:08 ralph 10 9
c changed sigreturn code to be on user's stack
e
s 00008/00007/03016
d D 7.9 92/10/11 11:23:12 bostic 9 8
c make kernel includes standard
e
s 00076/00054/02947
d D 7.8 92/07/27 21:28:12 ralph 8 7
c added susword fusword fusintrsword, etc.
e
s 00001/00001/03000
d D 7.7 92/06/20 11:58:22 ralph 7 6
c fix idle statistics.
e
s 00025/00003/02976
d D 7.6 92/05/28 14:40:20 mckusick 6 5
c speed cache lookups (from Macklem)
e
s 00002/00003/02977
d D 7.5 92/03/22 20:45:27 ralph 5 4
c don't save FP state more than once.
e
s 00006/00005/02974
d D 7.4 92/03/14 13:45:38 ralph 4 3
c don't need to block interrupts for FPU context switch
e
s 00331/00180/02648
d D 7.3 92/02/29 17:53:52 ralph 3 2
c added KADB support & DS5000 support
e
s 00017/00011/02811
d D 7.2 92/01/07 17:58:50 mckusick 2 1
c refinement in definitions of spl from Rick Macklem
e
s 02822/00000/00000
d D 7.1 92/01/07 17:39:37 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 17
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * This code is derived from software contributed to Berkeley by
 * Digital Equipment Corporation and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * Copyright (C) 1989 Digital Equipment Corporation.
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies.
 * Digital Equipment Corporation makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * from: $Header: /sprite/src/kernel/mach/ds3100.md/RCS/loMem.s,
 *	v 1.1 89/07/11 17:55:04 nelson Exp $ SPRITE (DECWRL)
 * from: $Header: /sprite/src/kernel/mach/ds3100.md/RCS/machAsm.s,
 *	v 9.2 90/01/29 18:00:39 shirriff Exp $ SPRITE (DECWRL)
 * from: $Header: /sprite/src/kernel/vm/ds3100.md/vmPmaxAsm.s,
 *	v 1.1 89/07/10 14:27:41 nelson Exp $ SPRITE (DECWRL)
 *
 *	%W% (Berkeley) %G%
 */

/*
 *	Contains code that is the first executed at boot time plus
 *	assembly language support routines.
 */

D 9
#include "errno.h"
E 9
I 9
#include <sys/errno.h>
I 10
#include <sys/syscall.h>
E 10
E 9

D 3
#include "machine/regdef.h"
E 3
D 9
#include "machine/param.h"
#include "machine/vmparam.h"
#include "machine/psl.h"
#include "machine/reg.h"
#include "machine/machAsmDefs.h"
D 3
#include "pte.h"
E 3
I 3
#include "machine/pte.h"
E 9
I 9
#include <machine/param.h>
D 12
#include <machine/vmparam.h>
E 12
#include <machine/psl.h>
#include <machine/reg.h>
#include <machine/machAsmDefs.h>
#include <machine/pte.h>

E 9
E 3
#include "assym.h"

I 13
	.set	noreorder

E 13
/*
 * Amount to take off of the stack for the benefit of the debugger.
 */
#define START_FRAME	((4 * 4) + 4 + 4)

	.globl	start
start:
D 13
	.set	noreorder
E 13
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
D 15
	li	t1, MACH_RESERVED_ADDR		# invalid address
E 15
I 15
	li	t1, MACH_CACHED_MEMORY_ADDR	# invalid address
E 15
	mtc0	t1, MACH_COP_0_TLB_HI		# Mark entry high as invalid
	mtc0	zero, MACH_COP_0_TLB_LOW	# Zero out low entry.
/*
 * Clear the TLB (just to be safe).
 * Align the starting value (t1), the increment (t2) and the upper bound (t3).
 */
	move	t1, zero
	li	t2, 1 << VMMACH_TLB_INDEX_SHIFT
	li	t3, VMMACH_NUM_TLB_ENTRIES << VMMACH_TLB_INDEX_SHIFT
1:
	mtc0	t1, MACH_COP_0_TLB_INDEX	# Set the index register.
	addu	t1, t1, t2			# Increment index.
	bne	t1, t3, 1b			# NB: always executes next
	tlbwi					# Write the TLB entry.

D 12
	li	sp, MACH_CODE_START - START_FRAME
	la	gp, _gp
E 12
I 12
	la	sp, start - START_FRAME
 #	la	gp, _gp
E 12
	sw	zero, START_FRAME - 4(sp)	# Zero out old ra for debugger
	jal	mach_init			# mach_init(argc, argv, envp)
	sw	zero, START_FRAME - 8(sp)	# Zero out old fp for debugger

	li	t0, MACH_SR_COP_1_BIT		# Disable interrupts and
	mtc0	t0, MACH_COP_0_STATUS_REG	#   enable the coprocessor
	li	sp, KERNELSTACK - START_FRAME	# switch to standard stack
	mfc0	t0, MACH_COP_0_PRID		# read processor ID register
	cfc1	t1, MACH_FPC_ID			# read FPU ID register
	sw	t0, cpu				# save PRID register
	sw	t1, fpu				# save FPU ID register
D 21
	jal	main				# main()
	nop

/* proc[1] == /etc/init now running here; run icode */
E 21
I 21
	jal	main				# main(regs)
	move	a0, zero
/*
 * proc[1] == /etc/init now running here.
 * Restore user registers and return.
 */
	.set	noat
E 21
	li	v0, PSL_USERSET
	mtc0	v0, MACH_COP_0_STATUS_REG	# switch to user mode
D 12
	j	zero				# icode is at address zero
E 12
I 12
D 21
	li	v0, VM_MIN_ADDRESS
	j	v0				# jump to icode
E 21
I 21
	lw	a0, UADDR+U_PCB_REGS+(SR * 4)
	lw	t0, UADDR+U_PCB_REGS+(MULLO * 4)
	lw	t1, UADDR+U_PCB_REGS+(MULHI * 4)
	mtlo	t0
	mthi	t1
	lw	k0, UADDR+U_PCB_REGS+(PC * 4)
	lw	AT, UADDR+U_PCB_REGS+(AST * 4)
	lw	v0, UADDR+U_PCB_REGS+(V0 * 4)
	lw	v1, UADDR+U_PCB_REGS+(V1 * 4)
	lw	a0, UADDR+U_PCB_REGS+(A0 * 4)
	lw	a1, UADDR+U_PCB_REGS+(A1 * 4)
	lw	a2, UADDR+U_PCB_REGS+(A2 * 4)
	lw	a3, UADDR+U_PCB_REGS+(A3 * 4)
	lw	t0, UADDR+U_PCB_REGS+(T0 * 4)
	lw	t1, UADDR+U_PCB_REGS+(T1 * 4)
	lw	t2, UADDR+U_PCB_REGS+(T2 * 4)
	lw	t3, UADDR+U_PCB_REGS+(T3 * 4)
	lw	t4, UADDR+U_PCB_REGS+(T4 * 4)
	lw	t5, UADDR+U_PCB_REGS+(T5 * 4)
	lw	t6, UADDR+U_PCB_REGS+(T6 * 4)
	lw	t7, UADDR+U_PCB_REGS+(T7 * 4)
	lw	s0, UADDR+U_PCB_REGS+(S0 * 4)
	lw	s1, UADDR+U_PCB_REGS+(S1 * 4)
	lw	s2, UADDR+U_PCB_REGS+(S2 * 4)
	lw	s3, UADDR+U_PCB_REGS+(S3 * 4)
	lw	s4, UADDR+U_PCB_REGS+(S4 * 4)
	lw	s5, UADDR+U_PCB_REGS+(S5 * 4)
	lw	s6, UADDR+U_PCB_REGS+(S6 * 4)
	lw	s7, UADDR+U_PCB_REGS+(S7 * 4)
	lw	t8, UADDR+U_PCB_REGS+(T8 * 4)
	lw	t9, UADDR+U_PCB_REGS+(T9 * 4)
	lw	gp, UADDR+U_PCB_REGS+(GP * 4)
	lw	sp, UADDR+U_PCB_REGS+(SP * 4)
	lw	s8, UADDR+U_PCB_REGS+(S8 * 4)
	lw	ra, UADDR+U_PCB_REGS+(RA * 4)
	j	k0
E 21
E 12
	rfe
I 21
	.set	at
E 21
D 13
	.set	reorder
E 13

/*
I 8
 * GCC2 seems to want to call __main in main() for some reason.
 */
LEAF(__main)
	j	ra
I 13
	nop
E 13
END(__main)

/*
E 8
D 21
 * This code is copied to user data space as the first program to run.
 * Basically, it just calls execve();
 */
	.globl	icode
icode:
D 13
	.set	noreorder
E 13
D 12
	li	a1, (9 * 4)		# address of 'icode_argv'
E 12
I 12
	li	a1, VM_MIN_ADDRESS + (9 * 4)	# address of 'icode_argv'
E 12
	addu	a0, a1, (3 * 4)		# address of 'icode_fname'
	move	a2, zero		# no environment
	li	v0, 59			# code for execve system call
	syscall
	li	v0, 1			# code for exit system call
	syscall				# execve failed: call exit()
1:	b	1b			# loop if exit returns
	nop
D 13
	.set	reorder
E 13
icode_argv:
D 12
	.word	(12 * 4)		# address of 'icode_fname'
	.word	(15 * 4)		# address of 'icodeEnd'
E 12
I 12
	.word	VM_MIN_ADDRESS + (12 * 4)	# address of 'icode_fname'
	.word	VM_MIN_ADDRESS + (15 * 4)	# address of 'icodeEnd'
E 12
	.word	0
icode_fname:
	.asciiz	"/sbin/init"		# occupies 3 words
	.align	2
	.globl	icodeEnd
icodeEnd:

D 12
	.sdata
E 12
I 12
	.data
E 12
	.align	2
	.globl	szicode
szicode:
	.word	(9 + 3 + 3) * 4		# compute icodeEnd - icode
	.text
I 10

/*
E 21
 * This code is copied the user's stack for returning from signal handlers
 * (see sendsig() and sigreturn()). We have to compute the address
 * of the sigcontext struct for the sigreturn call.
 */
	.globl	sigcode
sigcode:
D 12
	addu	a0, sp, 16		# address of sigcontext 
E 12
I 12
	addu	a0, sp, 16		# address of sigcontext
E 12
	li	v0, SYS_sigreturn	# sigreturn(scp)
	syscall
	break	0			# just in case sigreturn fails
	.globl	esigcode
esigcode:
E 10

/*
 * Primitives
 */

/*
 * This table is indexed by u.u_pcb.pcb_onfault in trap().
 * The reason for using this table rather than storing an address in
 * u.u_pcb.pcb_onfault is simply to make the code faster.
 */
	.globl	onfault_table
D 12
	.data	
E 12
I 12
	.data
E 12
	.align	2
onfault_table:
	.word	0		# invalid index number
#define BADERR		1
	.word	baderr
D 8
#define ADDUPCERR	2
	.word	addupcerr
#define COPYERR		3
E 8
I 8
#define COPYERR		2
E 8
	.word	copyerr
D 8
#define FSWBERR		4
E 8
I 8
#define FSWBERR		3
E 8
	.word	fswberr
I 8
#define FSWINTRBERR	4
	.word	fswintrberr
E 8
I 3
#ifdef KADB
#define KADBERR		5
	.word	kadberr
#endif
E 3
	.text

/*
 * See if access to addr with a len type instruction causes a machine check.
 * len is length of access (1=byte, 2=short, 4=long)
 *
 * badaddr(addr, len)
 *	char *addr;
 *	int len;
 */
LEAF(badaddr)
	li	v0, BADERR
D 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
	bne	a1, 1, 2f
D 13
	lbu	v0, (a0)
E 13
I 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
	b	5f
I 13
	lbu	v0, (a0)
E 13
2:
	bne	a1, 2, 4f
D 13
	lhu	v0, (a0)
E 13
I 13
	nop
E 13
	b	5f
I 13
	lhu	v0, (a0)
E 13
4:
	lw	v0, (a0)
5:
	sw	zero, UADDR+U_PCB_ONFAULT
D 13
	move	v0, zero		# made it w/o errors
E 13
	j	ra
I 13
	move	v0, zero		# made it w/o errors
E 13
baderr:
D 13
	li	v0, 1			# trap sends us here
E 13
	j	ra
I 13
	li	v0, 1			# trap sends us here
E 13
END(badaddr)

/*
D 8
 * update profiling information for the user
 * addupc(pc, pr, ticks)
 *	unsigned pc;
 *	struct uprof *pr;
 *	int ticks;
 */
LEAF(addupc)
	lw	v1, 8(a1)		# get pr->pr_off
	subu	a0, a0, v1		# pc -= pr->pr_off
	blt	a0, zero, 1f		# ignore if less than zero
	lw	v0, 12(a1)		# get pr->pr_scale
	multu	v0, a0			# compute index into count table
	mflo	v0
	srl	v0, v0, 16		# shift v1,v0 >> 16
	mfhi	v1
	sll	v1, v1, 16
	or	v0, v0, v1
	addu	v0, v0, 1		# round up and
	and	v0, v0, ~1		#   align to short boundary
	lw	v1, 4(a1)		# get pr->pr_size
	bgeu	v0, v1, 1f		# ignore if index >= size
	lw	v1, 0(a1)		# get pr->pr_base
	addu	v0, v0, v1		# add index and base
	li	v1, ADDUPCERR		# turn off profiling if fault
	bltz	v0, addupcerr		# can this happen?
	sw	v1, UADDR+U_PCB_ONFAULT
	lh	v1, 0(v0)		# get old count
	addu	v1, v1, a2		# add ticks
	sh	v1, 0(v0)		# save new count
	sw	zero, UADDR+U_PCB_ONFAULT
1:
	j	ra
addupcerr:
	sw	zero, 12(a1)		# pr->pr_scale = 0
	j	ra
END(addupc)

/*
E 8
 * netorder = htonl(hostorder)
 * hostorder = ntohl(netorder)
 */
LEAF(htonl)				# a0 = 0x11223344, return 0x44332211
ALEAF(ntohl)
	srl	v1, a0, 24		# v1 = 0x00000011
	sll	v0, a0, 24		# v0 = 0x44000000
	or	v0, v0, v1
	and	v1, a0, 0xff00
	sll	v1, v1, 8		# v1 = 0x00330000
	or	v0, v0, v1
	srl	v1, a0, 8
	and	v1, v1, 0xff00		# v1 = 0x00002200
D 13
	or	v0, v0, v1
E 13
	j	ra
I 13
	or	v0, v0, v1
E 13
END(htonl)

/*
 * netorder = htons(hostorder)
 * hostorder = ntohs(netorder)
 */
LEAF(htons)
ALEAF(ntohs)
	srl	v0, a0, 8
	and	v0, v0, 0xff
	sll	v1, a0, 8
	and	v1, v1, 0xff00
D 13
	or	v0, v0, v1
E 13
	j	ra
I 13
	or	v0, v0, v1
E 13
END(htons)

/*
 * bit = ffs(value)
 */
LEAF(ffs)
D 13
	move	v0, zero
E 13
	beq	a0, zero, 2f
I 13
	move	v0, zero
E 13
1:
	and	v1, a0, 1		# bit set?
	addu	v0, v0, 1
D 13
	srl	a0, a0, 1
E 13
	beq	v1, zero, 1b		# no, continue
I 13
	srl	a0, a0, 1
E 13
2:
	j	ra
I 13
	nop
E 13
END(ffs)

/*
 * strlen(str)
 */
LEAF(strlen)
	addu	v1, a0, 1
1:
	lb	v0, 0(a0)		# get byte from string
	addu	a0, a0, 1		# increment pointer
	bne	v0, zero, 1b		# continue if not end
D 13
	subu	v0, a0, v1		# compute length - 1 for '\0' char
E 13
I 13
	nop
E 13
	j	ra
I 13
	subu	v0, a0, v1		# compute length - 1 for '\0' char
E 13
END(strlen)

/*
I 3
 * NOTE: this version assumes unsigned chars in order to be "8 bit clean".
 */
LEAF(strcmp)
1:
	lbu	t0, 0(a0)		# get two bytes and compare them
	lbu	t1, 0(a1)
	beq	t0, zero, LessOrEq	# end of first string?
I 13
	nop
E 13
	bne	t0, t1, NotEq
I 13
	nop
E 13
	lbu	t0, 1(a0)		# unroll loop
	lbu	t1, 1(a1)
D 13
	add	a0, a0, 2
E 13
	beq	t0, zero, LessOrEq	# end of first string?
D 13
	add	a1, a1, 2
E 13
I 13
	addu	a0, a0, 2
E 13
	beq	t0, t1, 1b
I 13
	addu	a1, a1, 2
E 13
NotEq:
D 13
	subu	v0, t0, t1
E 13
	j	ra
I 13
	subu	v0, t0, t1
E 13
LessOrEq:
D 13
	subu	v0, zero, t1
E 13
	j	ra
I 13
	subu	v0, zero, t1
E 13
END(strcmp)

/*
E 3
 * bzero(s1, n)
 */
LEAF(bzero)
ALEAF(blkclr)
D 13
	.set	noreorder
E 13
	blt	a1, 12, smallclr	# small amount to clear?
	subu	a3, zero, a0		# compute # bytes to word align address
	and	a3, a3, 3
	beq	a3, zero, 1f		# skip if word aligned
	subu	a1, a1, a3		# subtract from remaining count
	swr	zero, 0(a0)		# clear 1, 2, or 3 bytes to align
	addu	a0, a0, a3
1:
	and	v0, a1, 3		# compute number of words left
	subu	a3, a1, v0
	move	a1, v0
	addu	a3, a3, a0		# compute ending address
2:
	addu	a0, a0, 4		# clear words
D 12
	bne	a0, a3, 2b		#   unrolling loop doesn't help
	sw	zero, -4(a0)		#   since we're limited by memory speed
E 12
I 12
	bne	a0, a3, 2b		#  unrolling loop does not help
	sw	zero, -4(a0)		#  since we are limited by memory speed
E 12
smallclr:
	ble	a1, zero, 2f
	addu	a3, a1, a0		# compute ending address
1:
	addu	a0, a0, 1		# clear bytes
	bne	a0, a3, 1b
	sb	zero, -1(a0)
2:
	j	ra
	nop
D 13
	.set	reorder
E 13
END(bzero)

/*
 * bcmp(s1, s2, n)
 */
LEAF(bcmp)
D 13
	.set	noreorder
E 13
	blt	a2, 16, smallcmp	# is it worth any trouble?
	xor	v0, a0, a1		# compare low two bits of addresses
	and	v0, v0, 3
	subu	a3, zero, a1		# compute # bytes to word align address
	bne	v0, zero, unalignedcmp	# not possible to align addresses
	and	a3, a3, 3

	beq	a3, zero, 1f
	subu	a2, a2, a3		# subtract from remaining count
	move	v0, v1			# init v0,v1 so unmodified bytes match
	lwr	v0, 0(a0)		# read 1, 2, or 3 bytes
	lwr	v1, 0(a1)
	addu	a1, a1, a3
	bne	v0, v1, nomatch
	addu	a0, a0, a3
1:
	and	a3, a2, ~3		# compute number of whole words left
	subu	a2, a2, a3		#   which has to be >= (16-3) & ~3
	addu	a3, a3, a0		# compute ending address
2:
	lw	v0, 0(a0)		# compare words
	lw	v1, 0(a1)
	addu	a0, a0, 4
	bne	v0, v1, nomatch
	addu	a1, a1, 4
	bne	a0, a3, 2b
	nop
	b	smallcmp		# finish remainder
	nop
unalignedcmp:
	beq	a3, zero, 2f
	subu	a2, a2, a3		# subtract from remaining count
	addu	a3, a3, a0		# compute ending address
1:
	lbu	v0, 0(a0)		# compare bytes until a1 word aligned
	lbu	v1, 0(a1)
	addu	a0, a0, 1
	bne	v0, v1, nomatch
	addu	a1, a1, 1
	bne	a0, a3, 1b
	nop
2:
	and	a3, a2, ~3		# compute number of whole words left
	subu	a2, a2, a3		#   which has to be >= (16-3) & ~3
	addu	a3, a3, a0		# compute ending address
3:
	lwr	v0, 0(a0)		# compare words a0 unaligned, a1 aligned
	lwl	v0, 3(a0)
	lw	v1, 0(a1)
	addu	a0, a0, 4
	bne	v0, v1, nomatch
	addu	a1, a1, 4
	bne	a0, a3, 3b
	nop
smallcmp:
	ble	a2, zero, match
	addu	a3, a2, a0		# compute ending address
1:
	lbu	v0, 0(a0)
	lbu	v1, 0(a1)
	addu	a0, a0, 1
	bne	v0, v1, nomatch
	addu	a1, a1, 1
	bne	a0, a3, 1b
	nop
match:
	j	ra
	move	v0, zero
nomatch:
	j	ra
	li	v0, 1
D 13
	.set	reorder
E 13
END(bcmp)

/*
I 20
 * memcpy(to, from, len)
E 20
 * {ov}bcopy(from, to, len)
 */
D 20
LEAF(bcopy)
E 20
I 20
LEAF(memcpy)
	move	v0, a0			# swap from and to
	move	a0, a1
	move	a1, v0
ALEAF(bcopy)
E 20
ALEAF(ovbcopy)
D 13
	.set	noreorder
E 13
	addu	t0, a0, a2		# t0 = end of s1 region
	sltu	t1, a1, t0
	sltu	t2, a0, a1
	and	t1, t1, t2		# t1 = true if from < to < (from+len)
	beq	t1, zero, forward	# non overlapping, do forward copy
	slt	t2, a2, 12		# check for small copy

	ble	a2, zero, 2f
	addu	t1, a1, a2		# t1 = end of to region
1:
D 20
	lb	v0, -1(t0)		# copy bytes backwards,
E 20
I 20
	lb	v1, -1(t0)		# copy bytes backwards,
E 20
D 12
	subu	t0, t0, 1		#   doesn't happen often so do slow way
E 12
I 12
	subu	t0, t0, 1		#   doesnt happen often so do slow way
E 12
	subu	t1, t1, 1
	bne	t0, a0, 1b
D 20
	sb	v0, 0(t1)
E 20
I 20
	sb	v1, 0(t1)
E 20
2:
	j	ra
	nop
forward:
	bne	t2, zero, smallcpy	# do a small bcopy
D 20
	xor	v0, a0, a1		# compare low two bits of addresses
	and	v0, v0, 3
E 20
I 20
	xor	v1, a0, a1		# compare low two bits of addresses
	and	v1, v1, 3
E 20
	subu	a3, zero, a1		# compute # bytes to word align address
D 20
	beq	v0, zero, aligned	# addresses can be word aligned
E 20
I 20
	beq	v1, zero, aligned	# addresses can be word aligned
E 20
	and	a3, a3, 3

	beq	a3, zero, 1f
	subu	a2, a2, a3		# subtract from remaining count
D 20
	lwr	v0, 0(a0)		# get next 4 bytes (unaligned)
	lwl	v0, 3(a0)
E 20
I 20
	lwr	v1, 0(a0)		# get next 4 bytes (unaligned)
	lwl	v1, 3(a0)
E 20
	addu	a0, a0, a3
D 20
	swr	v0, 0(a1)		# store 1, 2, or 3 bytes to align a1
E 20
I 20
	swr	v1, 0(a1)		# store 1, 2, or 3 bytes to align a1
E 20
	addu	a1, a1, a3
1:
D 20
	and	v0, a2, 3		# compute number of words left
	subu	a3, a2, v0
	move	a2, v0
E 20
I 20
	and	v1, a2, 3		# compute number of words left
	subu	a3, a2, v1
	move	a2, v1
E 20
	addu	a3, a3, a0		# compute ending address
2:
D 20
	lwr	v0, 0(a0)		# copy words a0 unaligned, a1 aligned
	lwl	v0, 3(a0)
E 20
I 20
	lwr	v1, 0(a0)		# copy words a0 unaligned, a1 aligned
	lwl	v1, 3(a0)
E 20
	addu	a0, a0, 4
	addu	a1, a1, 4
	bne	a0, a3, 2b
D 20
	sw	v0, -4(a1)
E 20
I 20
	sw	v1, -4(a1)
E 20
	b	smallcpy
	nop
aligned:
	beq	a3, zero, 1f
	subu	a2, a2, a3		# subtract from remaining count
D 20
	lwr	v0, 0(a0)		# copy 1, 2, or 3 bytes to align
E 20
I 20
	lwr	v1, 0(a0)		# copy 1, 2, or 3 bytes to align
E 20
	addu	a0, a0, a3
D 20
	swr	v0, 0(a1)
E 20
I 20
	swr	v1, 0(a1)
E 20
	addu	a1, a1, a3
1:
D 20
	and	v0, a2, 3		# compute number of whole words left
	subu	a3, a2, v0
	move	a2, v0
E 20
I 20
	and	v1, a2, 3		# compute number of whole words left
	subu	a3, a2, v1
	move	a2, v1
E 20
	addu	a3, a3, a0		# compute ending address
2:
D 20
	lw	v0, 0(a0)		# copy words
E 20
I 20
	lw	v1, 0(a0)		# copy words
E 20
	addu	a0, a0, 4
	addu	a1, a1, 4
	bne	a0, a3, 2b
D 20
	sw	v0, -4(a1)
E 20
I 20
	sw	v1, -4(a1)
E 20
smallcpy:
	ble	a2, zero, 2f
	addu	a3, a2, a0		# compute ending address
1:
D 20
	lbu	v0, 0(a0)		# copy bytes
E 20
I 20
	lbu	v1, 0(a0)		# copy bytes
E 20
	addu	a0, a0, 1
	addu	a1, a1, 1
	bne	a0, a3, 1b
D 20
	sb	v0, -1(a1)
E 20
I 20
	sb	v1, -1(a1)
E 20
2:
D 12
	sw	zero, UADDR+U_PCB_ONFAULT	# for copyin, copyout
E 12
	j	ra
D 20
	move	v0, zero
D 13
	.set	reorder
E 13
END(bcopy)
E 20
I 20
	nop
END(memcpy)
E 20

/*
 * Copy a null terminated string within the kernel address space.
 * Maxlength may be null if count not wanted.
 *	copystr(fromaddr, toaddr, maxlength, &lencopied)
 *		caddr_t fromaddr;
 *		caddr_t toaddr;
 *		u_int maxlength;
 *		u_int *lencopied;
 */
LEAF(copystr)
	move	t2, a2			# Save the number of bytes
1:
D 13
	lb	t0, 0(a0)
	sb	t0, 0(a1)
	sub	a2, a2, 1
E 13
I 13
	lbu	t0, 0(a0)
	subu	a2, a2, 1
E 13
	beq	t0, zero, 2f
D 13
	add	a0, a0, 1
	add	a1, a1, 1
E 13
I 13
	sb	t0, 0(a1)
	addu	a0, a0, 1
E 13
	bne	a2, zero, 1b
I 13
	addu	a1, a1, 1
E 13
2:
	beq	a3, zero, 3f
D 13
	sub	a2, t2, a2		# compute length copied
E 13
I 13
	subu	a2, t2, a2		# compute length copied
E 13
	sw	a2, 0(a3)
3:
D 12
	sw	zero, UADDR+U_PCB_ONFAULT	# for copyinstr, copyoutstr
E 12
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
END(copystr)

/*
 * Copy a null terminated string from the user address space into
 * the kernel address space.
 *
 *	copyinstr(fromaddr, toaddr, maxlength, &lencopied)
 *		caddr_t fromaddr;
 *		caddr_t toaddr;
 *		u_int maxlength;
 *		u_int *lencopied;
 */
D 12
LEAF(copyinstr)
E 12
I 12
NON_LEAF(copyinstr, STAND_FRAME_SIZE, ra)
	subu	sp, sp, STAND_FRAME_SIZE
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
	sw	ra, STAND_RA_OFFSET(sp)
E 12
D 13
	li	v0, COPYERR
E 13
	blt	a0, zero, copyerr	# make sure address is in user space
D 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
I 13
	li	v0, COPYERR
E 13
D 12
	b	copystr
E 12
I 12
	jal	copystr
I 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
	lw	ra, STAND_RA_OFFSET(sp)
	sw	zero, UADDR+U_PCB_ONFAULT
	addu	sp, sp, STAND_FRAME_SIZE
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
E 12
END(copyinstr)

/*
 * Copy a null terminated string from the kernel address space into
 * the user address space.
 *
 *	copyoutstr(fromaddr, toaddr, maxlength, &lencopied)
 *		caddr_t fromaddr;
 *		caddr_t toaddr;
 *		u_int maxlength;
 *		u_int *lencopied;
 */
D 12
LEAF(copyoutstr)
E 12
I 12
NON_LEAF(copyoutstr, STAND_FRAME_SIZE, ra)
	subu	sp, sp, STAND_FRAME_SIZE
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
	sw	ra, STAND_RA_OFFSET(sp)
E 12
D 13
	li	v0, COPYERR
E 13
	blt	a1, zero, copyerr	# make sure address is in user space
D 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
I 13
	li	v0, COPYERR
E 13
D 12
	b	copystr
E 12
I 12
	jal	copystr
I 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
	lw	ra, STAND_RA_OFFSET(sp)
	sw	zero, UADDR+U_PCB_ONFAULT
	addu	sp, sp, STAND_FRAME_SIZE
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
E 12
END(copyoutstr)

/*
 * Copy specified amount of data from user space into the kernel
 *	copyin(from, to, len)
 *		caddr_t *from;	(user source address)
 *		caddr_t *to;	(kernel destination address)
 *		unsigned len;
 */
D 12
LEAF(copyin)
E 12
I 12
NON_LEAF(copyin, STAND_FRAME_SIZE, ra)
	subu	sp, sp, STAND_FRAME_SIZE
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
	sw	ra, STAND_RA_OFFSET(sp)
E 12
D 13
	li	v0, COPYERR
E 13
	blt	a0, zero, copyerr	# make sure address is in user space
D 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
I 13
	li	v0, COPYERR
E 13
D 12
	b	bcopy
E 12
I 12
	jal	bcopy
I 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
	lw	ra, STAND_RA_OFFSET(sp)
	sw	zero, UADDR+U_PCB_ONFAULT
	addu	sp, sp, STAND_FRAME_SIZE
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
E 12
END(copyin)

/*
 * Copy specified amount of data from kernel to the user space
 *	copyout(from, to, len)
 *		caddr_t *from;	(kernel source address)
 *		caddr_t *to;	(user destination address)
 *		unsigned len;
 */
D 12
LEAF(copyout)
E 12
I 12
NON_LEAF(copyout, STAND_FRAME_SIZE, ra)
	subu	sp, sp, STAND_FRAME_SIZE
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
	sw	ra, STAND_RA_OFFSET(sp)
E 12
D 13
	li	v0, COPYERR
E 13
	blt	a1, zero, copyerr	# make sure address is in user space
D 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
I 13
	li	v0, COPYERR
E 13
D 12
	b	bcopy
E 12
I 12
	jal	bcopy
I 13
	sw	v0, UADDR+U_PCB_ONFAULT
E 13
	lw	ra, STAND_RA_OFFSET(sp)
	sw	zero, UADDR+U_PCB_ONFAULT
	addu	sp, sp, STAND_FRAME_SIZE
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
E 12
END(copyout)

LEAF(copyerr)
I 12
	lw	ra, STAND_RA_OFFSET(sp)
	sw	zero, UADDR+U_PCB_ONFAULT
	addu	sp, sp, STAND_FRAME_SIZE
E 12
D 13
	li	v0, EFAULT		# return error
E 13
	j	ra
I 13
	li	v0, EFAULT		# return error
E 13
END(copyerr)

/*
 * Copy data to the DMA buffer.
 * The DMA bufffer can only be written one short at a time
 * (and takes ~14 cycles).
 *
 *	CopyToBuffer(src, dst, length)
 *		u_short *src;	NOTE: must be short aligned
 *		u_short *dst;
 *		int length;
 */
LEAF(CopyToBuffer)
	blez	a2, 2f
I 13
	nop
E 13
1:
	lhu	t0, 0(a0)		# read 2 bytes of data
	subu	a2, a2, 2
	addu	a0, a0, 2
	addu	a1, a1, 4
D 13
	sh	t0, -4(a1)		# write 2 bytes of data to buffer
E 13
	bgtz	a2, 1b
I 13
	sh	t0, -4(a1)		# write 2 bytes of data to buffer
E 13
2:
	j	ra
I 13
	nop
E 13
END(CopyToBuffer)

/*
 * Copy data from the DMA buffer.
 * The DMA bufffer can only be read one short at a time
 * (and takes ~12 cycles).
 *
 *	CopyFromBuffer(src, dst, length)
 *		u_short *src;
 *		char *dst;
 *		int length;
 */
LEAF(CopyFromBuffer)
	and	t0, a1, 1		# test for aligned dst
	beq	t0, zero, 3f
I 13
	nop
E 13
	blt	a2, 2, 7f		# at least 2 bytes to copy?
I 13
	nop
E 13
1:
	lhu	t0, 0(a0)		# read 2 bytes of data from buffer
	addu	a0, a0, 4		# keep buffer pointer word aligned
	addu	a1, a1, 2
	subu	a2, a2, 2
	sb	t0, -2(a1)
	srl	t0, t0, 8
D 13
	sb	t0, -1(a1)
E 13
	bge	a2, 2, 1b
I 13
	sb	t0, -1(a1)
E 13
3:
	blt	a2, 2, 7f		# at least 2 bytes to copy?
I 13
	nop
E 13
6:
	lhu	t0, 0(a0)		# read 2 bytes of data from buffer
	addu	a0, a0, 4		# keep buffer pointer word aligned
	addu	a1, a1, 2
	subu	a2, a2, 2
D 13
	sh	t0, -2(a1)
E 13
	bge	a2, 2, 6b
I 13
	sh	t0, -2(a1)
E 13
7:
	ble	a2, zero, 9f		# done?
I 13
	nop
E 13
	lhu	t0, 0(a0)		# copy one more byte
I 13
	nop
E 13
	sb	t0, 0(a1)
9:
	j	ra
I 13
	nop
E 13
END(CopyFromBuffer)

/*
 * Copy the kernel stack to the new process and save the current context so
D 8
 * the new process will return nonzero when it is resumed by swtch().
E 8
I 8
D 19
 * the new process will return nonzero when it is resumed by cpu_swtch().
E 19
I 19
 * the new process will return nonzero when it is resumed by cpu_switch().
E 19
E 8
 *
 *	copykstack(up)
 *		struct user *up;
 */
LEAF(copykstack)
	subu	v0, sp, UADDR		# compute offset into stack
	addu	v0, v0, a0		# v0 = new stack address
	move	v1, sp			# v1 = old stack address
	li	t1, KERNELSTACK
1:
	lw	t0, 0(v1)		# copy stack data
	addu	v1, v1, 4
	sw	t0, 0(v0)
D 13
	addu	v0, v0, 4
E 13
	bne	v1, t1, 1b
I 13
	addu	v0, v0, 4
E 13
	/* FALLTHROUGH */
/*
 * Save registers and state so we can do a longjmp later.
 * Note: this only works if p != curproc since
D 8
 * swtch() will copy over pcb_context.
E 8
I 8
D 19
 * cpu_swtch() will copy over pcb_context.
E 19
I 19
 * cpu_switch() will copy over pcb_context.
E 19
E 8
 *
 *	savectx(up)
 *		struct user *up;
 */
ALEAF(savectx)
D 13
	.set	noreorder
E 13
	sw	s0, U_PCB_CONTEXT+0(a0)
	sw	s1, U_PCB_CONTEXT+4(a0)
	sw	s2, U_PCB_CONTEXT+8(a0)
	sw	s3, U_PCB_CONTEXT+12(a0)
	mfc0	v0, MACH_COP_0_STATUS_REG
	sw	s4, U_PCB_CONTEXT+16(a0)
	sw	s5, U_PCB_CONTEXT+20(a0)
	sw	s6, U_PCB_CONTEXT+24(a0)
	sw	s7, U_PCB_CONTEXT+28(a0)
	sw	sp, U_PCB_CONTEXT+32(a0)
	sw	s8, U_PCB_CONTEXT+36(a0)
	sw	ra, U_PCB_CONTEXT+40(a0)
	sw	v0, U_PCB_CONTEXT+44(a0)
	j	ra
	move	v0, zero
D 13
	.set	reorder
E 13
END(copykstack)

/*
D 18
 * _whichqs tells which of the 32 queues _qs
 * have processes in them.  Setrq puts processes into queues, Remrq
 * removes them from queues.  The running process is on no queue,
 * other processes are on a queue related to p->p_pri, divided by 4
E 18
I 18
 * The following primitives manipulate the run queues.  _whichqs tells which
 * of the 32 queues _qs have processes in them.  Setrunqueue puts processes
 * into queues, Remrq removes them from queues.  The running process is on
D 19
 * no queue, other processes are on a queue related to p->p_pri, divided by 4
E 18
 * actually to shrink the 0-127 range of priorities into the 32 available
E 19
I 19
 * no queue, other processes are on a queue related to p->p_priority, divided
 * by 4 actually to shrink the 0-127 range of priorities into the 32 available
E 19
 * queues.
 */
D 18

E 18
/*
D 18
 * setrq(p)
E 18
I 18
 * setrunqueue(p)
E 18
 *	proc *p;
 *
 * Call should be made at splclock(), and p->p_stat should be SRUN.
 */
D 18
NON_LEAF(setrq, STAND_FRAME_SIZE, ra)
E 18
I 18
NON_LEAF(setrunqueue, STAND_FRAME_SIZE, ra)
E 18
	subu	sp, sp, STAND_FRAME_SIZE
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
D 19
	lw	t0, P_RLINK(a0)		## firewall: p->p_rlink must be 0
E 19
I 19
	lw	t0, P_BACK(a0)		## firewall: p->p_back must be 0
E 19
D 3
	beq	t0, zero, 1f		##
E 3
	sw	ra, STAND_RA_OFFSET(sp)	##
I 3
	beq	t0, zero, 1f		##
I 13
D 19
	lbu	t0, P_PRI(a0)		# put on queue which is p->p_pri / 4
E 19
I 19
	lbu	t0, P_PRIORITY(a0)	# put on p->p_priority / 4 queue
E 19
E 13
E 3
D 18
	PANIC("setrq")			##
E 18
I 18
	PANIC("setrunqueue")		##
E 18
1:
D 13
	lbu	t0, P_PRI(a0)		# put on queue which is p->p_pri / 4
	srl	t0, t0, 2		# compute index into 'whichqs'
E 13
	li	t1, 1			# compute corresponding bit
I 13
	srl	t0, t0, 2		# compute index into 'whichqs'
E 13
	sll	t1, t1, t0
	lw	t2, whichqs		# set corresponding bit
I 13
	nop
E 13
	or	t2, t2, t1
	sw	t2, whichqs
	sll	t0, t0, 3		# compute index into 'qs'
	la	t1, qs
	addu	t0, t0, t1		# t0 = qp = &qs[pri >> 2]
D 19
	lw	t1, P_RLINK(t0)		# t1 = qp->ph_rlink
	sw	t0, P_LINK(a0)		# p->p_link = qp
	sw	t1, P_RLINK(a0)		# p->p_rlink = qp->ph_rlink
	sw	a0, P_LINK(t1)		# p->p_rlink->p_link = p;
	sw	a0, P_RLINK(t0)		# qp->ph_rlink = p
E 19
I 19
	lw	t1, P_BACK(t0)		# t1 = qp->ph_rlink
	sw	t0, P_FORW(a0)		# p->p_forw = qp
	sw	t1, P_BACK(a0)		# p->p_back = qp->ph_rlink
	sw	a0, P_FORW(t1)		# p->p_back->p_forw = p;
	sw	a0, P_BACK(t0)		# qp->ph_rlink = p
E 19
D 13
	addu	sp, sp, STAND_FRAME_SIZE
E 13
	j	ra
I 13
	addu	sp, sp, STAND_FRAME_SIZE
E 13
D 18
END(setrq)
E 18
I 18
END(setrunqueue)
E 18

/*
 * Remrq(p)
 *
 * Call should be made at splclock().
 */
NON_LEAF(remrq, STAND_FRAME_SIZE, ra)
	subu	sp, sp, STAND_FRAME_SIZE
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
D 19
	lbu	t0, P_PRI(a0)		# get from queue which is p->p_pri / 4
E 19
I 19
	lbu	t0, P_PRIORITY(a0)	# get from p->p_priority / 4 queue
E 19
D 13
	srl	t0, t0, 2		# compute index into 'whichqs'
E 13
	li	t1, 1			# compute corresponding bit
D 13
	sll	t1, t1, t0
E 13
I 13
	srl	t0, t0, 2		# compute index into 'whichqs'
E 13
	lw	t2, whichqs		# check corresponding bit
I 13
	sll	t1, t1, t0
E 13
	and	v0, t2, t1
D 3
	bne	v0, zero, 1f		##
E 3
	sw	ra, STAND_RA_OFFSET(sp)	##
I 3
	bne	v0, zero, 1f		##
I 13
D 19
	lw	v0, P_RLINK(a0)		# v0 = p->p_rlink
E 19
I 19
	lw	v0, P_BACK(a0)		# v0 = p->p_back
E 19
E 13
E 3
D 12
	PANIC("remrq")			## it wasn't recorded to be on its q
E 12
I 12
	PANIC("remrq")			## it wasnt recorded to be on its q
E 12
1:
D 13
	lw	v0, P_RLINK(a0)		# v0 = p->p_rlink
E 13
D 19
	lw	v1, P_LINK(a0)		# v1 = p->p_link
E 19
I 19
	lw	v1, P_FORW(a0)		# v1 = p->p_forw
E 19
I 13
	nop
E 13
D 19
	sw	v1, P_LINK(v0)		# p->p_rlink->p_link = p->p_link;
	sw	v0, P_RLINK(v1)		# p->p_link->p_rlink = p->r_rlink
E 19
I 19
	sw	v1, P_FORW(v0)		# p->p_back->p_forw = p->p_forw;
	sw	v0, P_BACK(v1)		# p->p_forw->p_back = p->r_rlink
E 19
	sll	t0, t0, 3		# compute index into 'qs'
	la	v0, qs
	addu	t0, t0, v0		# t0 = qp = &qs[pri >> 2]
D 19
	lw	v0, P_LINK(t0)		# check if queue empty
E 19
I 19
	lw	v0, P_FORW(t0)		# check if queue empty
E 19
I 13
	nop
E 13
	bne	v0, t0, 2f		# No. qp->ph_link != qp
I 13
	nop
E 13
	xor	t2, t2, t1		# clear corresponding bit in 'whichqs'
	sw	t2, whichqs
2:
D 19
	sw	zero, P_RLINK(a0)	## for firewall checking
E 19
I 19
	sw	zero, P_BACK(a0)	## for firewall checking
E 19
D 13
	addu	sp, sp, STAND_FRAME_SIZE
E 13
	j	ra
I 13
	addu	sp, sp, STAND_FRAME_SIZE
E 13
END(remrq)

/*
D 19
 * swtch_exit()
E 19
I 19
 * switch_exit()
E 19
 *
D 8
 * At exit of a process, do a swtch for the last time.
E 8
I 8
D 19
 * At exit of a process, do a cpu_swtch for the last time.
E 19
I 19
 * At exit of a process, do a cpu_switch for the last time.
E 19
E 8
 * The mapping of the pcb at p->p_addr has already been deleted,
 * and the memory for the pcb+stack has been freed.
 * All interrupts should be blocked at this point.
 */
D 19
LEAF(swtch_exit)
E 19
I 19
LEAF(switch_exit)
E 19
D 13
	.set	noreorder
E 13
D 15
	la	v0, nullproc			# save state into garbage proc
	lw	t0, P_UPTE+0(v0)		# t0 = first u. pte
	lw	t1, P_UPTE+4(v0)		# t1 = 2nd u. pte
E 15
I 15
	la	v1, nullproc			# save state into garbage proc
	lw	t0, P_UPTE+0(v1)		# t0 = first u. pte
	lw	t1, P_UPTE+4(v1)		# t1 = 2nd u. pte
E 15
	li	v0, UADDR			# v0 = first HI entry
	mtc0	zero, MACH_COP_0_TLB_INDEX	# set the index register
	mtc0	v0, MACH_COP_0_TLB_HI		# init high entry
	mtc0	t0, MACH_COP_0_TLB_LOW		# init low entry
	li	t0, 1 << VMMACH_TLB_INDEX_SHIFT
	tlbwi					# Write the TLB entry.
	addu	v0, v0, NBPG			# 2nd HI entry
	mtc0	t0, MACH_COP_0_TLB_INDEX	# set the index register
	mtc0	v0, MACH_COP_0_TLB_HI		# init high entry
	mtc0	t1, MACH_COP_0_TLB_LOW		# init low entry
D 15
	nop
E 15
I 15
	sw	zero, curproc
E 15
	tlbwi					# Write the TLB entry.
D 13
	.set	reorder
E 13
D 15
	li	sp, KERNELSTACK - START_FRAME	# switch to standard stack
E 15
D 8
	b	swtch
E 8
I 8
D 19
	b	cpu_swtch
E 19
I 19
	b	cpu_switch
E 19
I 13
D 15
	nop
E 15
I 15
	li	sp, KERNELSTACK - START_FRAME	# switch to standard stack
E 15
E 13
E 8
D 19
END(swtch_exit)
E 19
I 19
END(switch_exit)
E 19

/*
D 8
 * When no processes are on the runq, swtch branches to idle
E 8
I 8
D 19
 * When no processes are on the runq, cpu_swtch branches to idle
E 19
I 19
 * When no processes are on the runq, cpu_switch branches to idle
E 19
E 8
 * to wait for something to come ready.
D 8
 * Note: this is really a part of swtch() but defined here for kernel profiling.
E 8
I 8
D 19
 * Note: this is really a part of cpu_swtch() but defined here for kernel
E 19
I 19
 * Note: this is really a part of cpu_switch() but defined here for kernel
E 19
 * profiling.
E 8
 */
LEAF(idle)
D 13
	.set	noreorder
E 13
	li	t0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
	mtc0	t0, MACH_COP_0_STATUS_REG	# enable all interrupts
D 7
	nop
E 7
I 7
	sw	zero, curproc			# set curproc NULL for stats
E 7
D 3
	.set	reorder
E 3
1:
	lw	t0, whichqs			# look for non-empty queue
I 3
	nop
E 3
	beq	t0, zero, 1b
I 3
	nop
E 3
	b	sw1
I 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable all interrupts
D 13
	.set	reorder
E 13
E 3
END(idle)

/*
D 8
 * swtch()
E 8
I 8
D 19
 * cpu_swtch()
E 19
I 19
 * cpu_switch()
E 19
E 8
 * Find the highest priority process and resume it.
 */
D 8
NON_LEAF(swtch, STAND_FRAME_SIZE, ra)
E 8
I 8
D 19
NON_LEAF(cpu_swtch, STAND_FRAME_SIZE, ra)
E 19
I 19
NON_LEAF(cpu_switch, STAND_FRAME_SIZE, ra)
E 19
E 8
D 13
	.set	noreorder
E 13
	sw	sp, UADDR+U_PCB_CONTEXT+32	# save old sp
	subu	sp, sp, STAND_FRAME_SIZE
	sw	ra, STAND_RA_OFFSET(sp)
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
I 22
#ifdef DEBUG
	lw	a1, intr_level
	sw	a0, STAND_FRAME_SIZE(sp)
	beq	a1, zero, 1f
	nop
	PANIC("cpu_switch: intr_level %d")	# can't sleep in interrupt()
1:
#endif
E 22
	lw	t2, cnt+V_SWTCH			# for statistics
	lw	t1, whichqs			# look for non-empty queue
I 15
	sw	s0, UADDR+U_PCB_CONTEXT+0	# do a 'savectx()'
	sw	s1, UADDR+U_PCB_CONTEXT+4
	sw	s2, UADDR+U_PCB_CONTEXT+8
	sw	s3, UADDR+U_PCB_CONTEXT+12
E 15
	mfc0	t0, MACH_COP_0_STATUS_REG	# t0 = saved status register
I 15
	sw	s4, UADDR+U_PCB_CONTEXT+16
	sw	s5, UADDR+U_PCB_CONTEXT+20
	sw	s6, UADDR+U_PCB_CONTEXT+24
	sw	s7, UADDR+U_PCB_CONTEXT+28
	sw	s8, UADDR+U_PCB_CONTEXT+36
E 15
	sw	ra, UADDR+U_PCB_CONTEXT+40	# save return address
	sw	t0, UADDR+U_PCB_CONTEXT+44	# save status register
	addu	t2, t2, 1
D 15
	beq	t1, zero, idle			# if none, idle
E 15
	sw	t2, cnt+V_SWTCH
I 15
	beq	t1, zero, idle			# if none, idle
E 15
D 3
sw1:
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable all interrupts
I 3
sw1:
	nop					# wait for intrs disabled
E 3
	nop
	lw	t0, whichqs			# look for non-empty queue
	li	t2, -1				# t2 = lowest bit set
	beq	t0, zero, idle			# if none, idle
	move	t3, t0				# t3 = saved whichqs
1:
D 13
	add	t2, t2, 1
E 13
I 13
	addu	t2, t2, 1
E 13
	and	t1, t0, 1			# bit set?
	beq	t1, zero, 1b
	srl	t0, t0, 1			# try next bit
/*
 * Remove process from queue.
 */
	sll	t0, t2, 3
	la	t1, qs
	addu	t0, t0, t1			# t0 = qp = &qs[highbit]
D 19
	lw	a0, P_LINK(t0)			# a0 = p = highest pri process
E 19
I 19
	lw	a0, P_FORW(t0)			# a0 = p = highest pri process
E 19
	nop
D 19
	lw	v0, P_LINK(a0)			# v0 = p->p_link
E 19
I 19
	lw	v0, P_FORW(a0)			# v0 = p->p_forw
E 19
	bne	t0, a0, 2f			# make sure something in queue
D 19
	sw	v0, P_LINK(t0)			# qp->ph_link = p->p_link;
D 8
	PANIC("swtch")				# nothing in queue
E 8
I 8
	PANIC("cpu_swtch")			# nothing in queue
E 19
I 19
	sw	v0, P_FORW(t0)			# qp->ph_link = p->p_forw;
	PANIC("cpu_switch")			# nothing in queue
E 19
E 8
2:
D 19
	sw	t0, P_RLINK(v0)			# p->p_link->p_rlink = qp
E 19
I 19
	sw	t0, P_BACK(v0)			# p->p_forw->p_back = qp
E 19
	bne	v0, t0, 3f			# queue still not empty
D 19
	sw	zero, P_RLINK(a0)		## for firewall checking
E 19
I 19
	sw	zero, P_BACK(a0)		## for firewall checking
E 19
	li	v1, 1				# compute bit in 'whichqs'
	sll	v1, v1, t2
	xor	t3, t3, v1			# clear bit in 'whichqs'
	sw	t3, whichqs
3:
/*
D 15
 * Save old context and switch to new one.
E 15
I 15
 * Switch to new context.
E 15
 */
D 15
	sw	a0, curproc			# set curproc
E 15
	sw	zero, want_resched
	jal	pmap_alloc_tlbpid		# v0 = TLB PID
D 15
	sw	a0, STAND_FRAME_SIZE(sp)	# save p
	lw	a0, STAND_FRAME_SIZE(sp)	# restore p
E 15
I 15
D 21
	move	s0, a0				# save p
	move	a0, s0				# restore p
	sw	a0, curproc			# set curproc
E 21
I 21
	move	s0, a0				# BDSLOT: save p
	sw	s0, curproc			# set curproc
E 21
E 15
	sll	v0, v0, VMMACH_TLB_PID_SHIFT	# v0 = aligned PID
D 3
	or	v0, v0, UADDR			# v0 = first HI entry
E 3
D 21
	lw	t0, P_UPTE+0(a0)		# t0 = first u. pte
	lw	t1, P_UPTE+4(a0)		# t1 = 2nd u. pte
E 21
I 21
	lw	t0, P_UPTE+0(s0)		# t0 = first u. pte
	lw	t1, P_UPTE+4(s0)		# t1 = 2nd u. pte
E 21
D 15
	sw	s0, UADDR+U_PCB_CONTEXT+0	# do a 'savectx()'
	sw	s1, UADDR+U_PCB_CONTEXT+4	#  We save s0 to s8 here because
	sw	s2, UADDR+U_PCB_CONTEXT+8	#  the TLB trap code uses
	sw	s3, UADDR+U_PCB_CONTEXT+12	#  CONTEXT and there should be
	sw	s4, UADDR+U_PCB_CONTEXT+16	#  no faults at this point.
	sw	s5, UADDR+U_PCB_CONTEXT+20
	sw	s6, UADDR+U_PCB_CONTEXT+24
	sw	s7, UADDR+U_PCB_CONTEXT+28
	sw	s8, UADDR+U_PCB_CONTEXT+36
E 15
I 3
	or	v0, v0, UADDR			# v0 = first HI entry
E 3
/*
 * Resume process indicated by the pte's for its u struct
 * NOTE: This is hard coded to UPAGES == 2.
 * Also, there should be no TLB faults at this point.
 */
	mtc0	zero, MACH_COP_0_TLB_INDEX	# set the index register
	mtc0	v0, MACH_COP_0_TLB_HI		# init high entry
	mtc0	t0, MACH_COP_0_TLB_LOW		# init low entry
	li	t0, 1 << VMMACH_TLB_INDEX_SHIFT
	tlbwi					# Write the TLB entry.
	addu	v0, v0, NBPG			# 2nd HI entry
	mtc0	t0, MACH_COP_0_TLB_INDEX	# set the index register
	mtc0	v0, MACH_COP_0_TLB_HI		# init high entry
	mtc0	t1, MACH_COP_0_TLB_LOW		# init low entry
	nop
	tlbwi					# Write the TLB entry.
/*
 * Now running on new u struct.
 * Restore registers and return.
 */
	lw	v0, UADDR+U_PCB_CONTEXT+44	# restore kernel context
	lw	ra, UADDR+U_PCB_CONTEXT+40
	lw	s0, UADDR+U_PCB_CONTEXT+0
	lw	s1, UADDR+U_PCB_CONTEXT+4
	lw	s2, UADDR+U_PCB_CONTEXT+8
	lw	s3, UADDR+U_PCB_CONTEXT+12
	lw	s4, UADDR+U_PCB_CONTEXT+16
	lw	s5, UADDR+U_PCB_CONTEXT+20
	lw	s6, UADDR+U_PCB_CONTEXT+24
	lw	s7, UADDR+U_PCB_CONTEXT+28
	lw	sp, UADDR+U_PCB_CONTEXT+32
	lw	s8, UADDR+U_PCB_CONTEXT+36
	mtc0	v0, MACH_COP_0_STATUS_REG
	j	ra
	li	v0, 1				# possible return to 'savectx()'
D 13
	.set	reorder
E 13
D 8
END(swtch)
E 8
I 8
D 19
END(cpu_swtch)
E 19
I 19
END(cpu_switch)
E 19
E 8

/*
D 8
 * {fu,su},{ibyte,iword}, fetch or store a byte or word to user text space.
 * {fu,su},{byte,word}, fetch or store a byte or word to user data space.
E 8
I 8
 * {fu,su},{ibyte,isword,iword}, fetch or store a byte, short or word to
 * user text space.
 * {fu,su},{byte,sword,word}, fetch or store a byte, short or word to
 * user data space.
E 8
 */
LEAF(fuword)
ALEAF(fuiword)
D 13
	li	v0, FSWBERR
E 13
	blt	a0, zero, fswberr	# make sure address is in user space
I 13
	li	v0, FSWBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	lw	v0, 0(a0)		# fetch word
D 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
	j	ra
I 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
END(fuword)

I 8
LEAF(fusword)
ALEAF(fuisword)
D 13
	li	v0, FSWBERR
E 13
	blt	a0, zero, fswberr	# make sure address is in user space
I 13
	li	v0, FSWBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	lhu	v0, 0(a0)		# fetch short
D 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
	j	ra
I 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
END(fusword)

E 8
LEAF(fubyte)
ALEAF(fuibyte)
D 13
	li	v0, FSWBERR
E 13
	blt	a0, zero, fswberr	# make sure address is in user space
I 13
	li	v0, FSWBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	lbu	v0, 0(a0)		# fetch byte
D 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
	j	ra
I 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
END(fubyte)

LEAF(suword)
D 3
ALEAF(suiword)
E 3
D 13
	li	v0, FSWBERR
E 13
	blt	a0, zero, fswberr	# make sure address is in user space
I 13
	li	v0, FSWBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	sw	a1, 0(a0)		# store word
	sw	zero, UADDR+U_PCB_ONFAULT
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
END(suword)

I 3
/*
 * Have to flush instruction cache afterwards.
 */
LEAF(suiword)
D 13
	li	v0, FSWBERR
E 13
	blt	a0, zero, fswberr	# make sure address is in user space
I 13
	li	v0, FSWBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	sw	a1, 0(a0)		# store word
	sw	zero, UADDR+U_PCB_ONFAULT
	move	v0, zero
D 13
	li	a1, 4			# size of word
E 13
	b	MachFlushICache		# NOTE: this should not clobber v0!
I 13
	li	a1, 4			# size of word
E 13
END(suiword)

/*
 * Will have to flush the instruction cache if byte merging is done in hardware.
 */
I 8
LEAF(susword)
ALEAF(suisword)
D 13
	li	v0, FSWBERR
E 13
	blt	a0, zero, fswberr	# make sure address is in user space
I 13
	li	v0, FSWBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	sh	a1, 0(a0)		# store short
	sw	zero, UADDR+U_PCB_ONFAULT
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
END(susword)

E 8
E 3
LEAF(subyte)
ALEAF(suibyte)
D 13
	li	v0, FSWBERR
E 13
	blt	a0, zero, fswberr	# make sure address is in user space
I 13
	li	v0, FSWBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	sb	a1, 0(a0)		# store byte
	sw	zero, UADDR+U_PCB_ONFAULT
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
END(subyte)

LEAF(fswberr)
D 13
	li	v0, -1
E 13
	j	ra
I 13
	li	v0, -1
E 13
END(fswberr)
I 8

/*
 * fuswintr and suswintr are just like fusword and susword except that if
 * the page is not in memory or would cause a trap, then we return an error.
D 19
 * The important thing is to prevent sleep() and swtch().
E 19
I 19
 * The important thing is to prevent sleep() and switch().
E 19
 */
LEAF(fuswintr)
D 13
	li	v0, FSWINTRBERR
E 13
	blt	a0, zero, fswintrberr	# make sure address is in user space
I 13
	li	v0, FSWINTRBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	lhu	v0, 0(a0)		# fetch short
D 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
	j	ra
I 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
END(fuswintr)

LEAF(suswintr)
D 13
	li	v0, FSWINTRBERR
E 13
	blt	a0, zero, fswintrberr	# make sure address is in user space
I 13
	li	v0, FSWINTRBERR
E 13
	sw	v0, UADDR+U_PCB_ONFAULT
	sh	a1, 0(a0)		# store short
	sw	zero, UADDR+U_PCB_ONFAULT
D 13
	move	v0, zero
E 13
	j	ra
I 13
	move	v0, zero
E 13
END(suswintr)

LEAF(fswintrberr)
D 13
	li	v0, -1
E 13
	j	ra
I 13
	li	v0, -1
E 13
END(fswintrberr)
E 8

/*
 * Insert 'p' after 'q'.
 *	_insque(p, q)
 *		caddr_t p, q;
 */
LEAF(_insque)
	lw	v0, 0(a1)		# v0 = q->next
	sw	a1, 4(a0)		# p->prev = q
	sw	v0, 0(a0)		# p->next = q->next
	sw	a0, 4(v0)		# q->next->prev = p
D 13
	sw	a0, 0(a1)		# q->next = p
E 13
	j	ra
I 13
	sw	a0, 0(a1)		# q->next = p
E 13
END(_insque)

/*
 * Remove item 'p' from queue.
 *	_remque(p)
 *		caddr_t p;
 */
LEAF(_remque)
	lw	v0, 0(a0)		# v0 = p->next
	lw	v1, 4(a0)		# v1 = p->prev
I 13
	nop
E 13
	sw	v0, 0(v1)		# p->prev->next = p->next
D 13
	sw	v1, 4(v0)		# p->next->prev = p->prev
E 13
	j	ra
I 13
	sw	v1, 4(v0)		# p->next->prev = p->prev
E 13
END(_remque)

/*
 * This code is copied to the UTLB exception vector address to
 * handle user level TLB translation misses.
 * NOTE: This code must be relocatable!!!
 */
	.globl	MachUTLBMiss
MachUTLBMiss:
	.set	noat
D 13
	.set	noreorder
E 13
	mfc0	k0, MACH_COP_0_BAD_VADDR	# get the virtual address
I 15
	lw	k1, UADDR+U_PCB_SEGTAB		# get the current segment table
	bltz	k0, 1f				# R3000 chip bug
	srl	k0, k0, SEGSHIFT		# compute segment table index
	sll	k0, k0, 2
	addu	k1, k1, k0
	mfc0	k0, MACH_COP_0_BAD_VADDR	# get the virtual address
	lw	k1, 0(k1)			# get pointer to segment map
	srl	k0, k0, PGSHIFT - 2		# compute segment map index
	andi	k0, k0, (NPTEPG - 1) << 2
	beq	k1, zero, 2f			# invalid segment map
	addu	k1, k1, k0			# index into segment map
	lw	k0, 0(k1)			# get page PTE
E 15
	nop
D 15
	srl	k0, k0, PMAP_HASH_SHIFT1	# get page in low bits
	srl	k1, k0, PMAP_HASH_SHIFT2 - PMAP_HASH_SHIFT1
	and	k0, k0, PMAP_HASH_MASK1
	and	k1, k1, PMAP_HASH_MASK2
	or	k1, k1, k0
	sll	k1, k1, PMAP_HASH_SIZE_SHIFT	# compute index
	lw	k0, PMAP_HASH_LOW_OFFSET(k1)	# get cached low PTE entry
	lw	k1, PMAP_HASH_HIGH_OFFSET(k1)	# get cached high PTE entry
E 15
I 15
	beq	k0, zero, 2f			# dont load invalid entries
E 15
	mtc0	k0, MACH_COP_0_TLB_LOW
D 15
	mfc0	k0, MACH_COP_0_TLB_HI		# get actual high PTE entry
	nop
	bne	k0, k1, 1f			# non-matching PTE
	mfc0	k0, MACH_COP_0_EXC_PC		# get return address
E 15
I 15
	mfc0	k1, MACH_COP_0_EXC_PC		# get return address
E 15
	tlbwr					# update TLB
D 15
	j	k0
E 15
I 15
	j	k1
E 15
	rfe
1:
D 6
	j	SlowFault			# handle cache miss
E 6
I 6
D 15
	j	UtlbFault			# handle the rest
E 15
I 15
	mfc0	k1, MACH_COP_0_EXC_PC		# get return address
E 15
E 6
	nop
I 15
	j	k1
	rfe
2:
	j	SlowFault			# handle the rest
	nop
E 15
D 13
	.set	reorder
E 13
	.set	at
	.globl	MachUTLBMissEnd
MachUTLBMissEnd:

/*
 * This code is copied to the general exception vector address to
 * handle all execptions except RESET and UTLBMiss.
 * NOTE: This code must be relocatable!!!
 */
	.globl	MachException
MachException:
/*
 * Find out what mode we came from and jump to the proper handler.
 */
	.set	noat
D 13
	.set	noreorder
E 13
	mfc0	k0, MACH_COP_0_STATUS_REG	# Get the status register
	mfc0	k1, MACH_COP_0_CAUSE_REG	# Get the cause register value.
	and	k0, k0, MACH_SR_KU_PREV		# test for user mode
D 4
	beq	k0, zero, 1f			# handle kernel exception
E 4
I 4
	sll	k0, k0, 3			# shift user bit for cause index
E 4
	and	k1, k1, MACH_CR_EXC_CODE	# Mask out the cause bits.
D 4
	addu	k1, k1, 0x40			# change index to user table
E 4
I 4
	or	k1, k1, k0			# change index to user table
E 4
1:
	la	k0, machExceptionTable		# get base of the jump table
D 4
	add	k0, k0, k1			# Get the address of the
E 4
I 4
	addu	k0, k0, k1			# Get the address of the
E 4
						#  function entry.  Note that
						#  the cause is already
						#  shifted left by 2 bits so
D 12
						#  we don't have to shift.
E 12
I 12
						#  we dont have to shift.
E 12
	lw	k0, 0(k0)			# Get the function address
	nop
	j	k0				# Jump to the function.
	nop
D 13
	.set	reorder
E 13
	.set	at
	.globl	MachExceptionEnd
MachExceptionEnd:

/*
I 6
D 15
 * Handle the rest of the UTLB miss.
 */
UtlbFault:
D 13
	.set	noreorder
E 13
	.set	noat
	mfc0	k0, MACH_COP_0_BAD_VADDR	# get the virtual address
	nop
	srl	k0, k0, PMAP_HASH_SHIFT1	# get page in low bits
	srl	k1, k0, PMAP_HASH_SHIFT2 - PMAP_HASH_SHIFT1
	and	k0, k0, PMAP_HASH_MASK1
	and	k1, k1, PMAP_HASH_MASK2
	or	k1, k1, k0
	sll	k1, k1, PMAP_HASH_SIZE_SHIFT	# compute index
	lw	k0, PMAP_HASH_LOW_OFFSET+8(k1)	# get cached low PTE entry
	lw	k1, PMAP_HASH_HIGH_OFFSET+8(k1)	# get cached high PTE entry
	mtc0	k0, MACH_COP_0_TLB_LOW
	mfc0	k0, MACH_COP_0_TLB_HI		# get actual high PTE entry
	nop
	bne	k0, k1, SlowFault		# non-matching PTE
	mfc0	k0, MACH_COP_0_EXC_PC		# get return address
	tlbwr					# update TLB
	j	k0
	rfe
/*
E 15
E 6
 * We couldn't find a TLB entry.
 * Find out what mode we came from and call the appropriate handler.
 */
SlowFault:
I 15
	.set	noat
E 15
D 6
	.set	noat
	.set	noreorder
E 6
	mfc0	k0, MACH_COP_0_STATUS_REG
	nop
	and	k0, k0, MACH_SR_KU_PREV
	bne	k0, zero, MachUserGenException
	nop
D 13
	.set	reorder
E 13
	.set	at
/*
 * Fall though ...
 */

/*----------------------------------------------------------------------------
 *
 * MachKernGenException --
 *
 *	Handle an exception from kernel mode.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */

/*
 * The kernel exception stack contains 18 saved general registers,
 * the status register and the multiply lo and high registers.
 * In addition, we set this up for linkage conventions.
 */
#define KERN_REG_SIZE		(18 * 4)
#define KERN_REG_OFFSET		(STAND_FRAME_SIZE)
#define KERN_SR_OFFSET		(STAND_FRAME_SIZE + KERN_REG_SIZE)
#define KERN_MULT_LO_OFFSET	(STAND_FRAME_SIZE + KERN_REG_SIZE + 4)
#define KERN_MULT_HI_OFFSET	(STAND_FRAME_SIZE + KERN_REG_SIZE + 8)
#define	KERN_EXC_FRAME_SIZE	(STAND_FRAME_SIZE + KERN_REG_SIZE + 12)

D 15
NON_LEAF(MachKernGenException, KERN_EXC_FRAME_SIZE, ra)
E 15
I 15
NNON_LEAF(MachKernGenException, KERN_EXC_FRAME_SIZE, ra)
E 15
D 13
	.set	noreorder
E 13
	.set	noat
I 3
#ifdef KADB
	la	k0, kdbpcb			# save registers for kadb
	sw	s0, (S0 * 4)(k0)
	sw	s1, (S1 * 4)(k0)
	sw	s2, (S2 * 4)(k0)
	sw	s3, (S3 * 4)(k0)
	sw	s4, (S4 * 4)(k0)
	sw	s5, (S5 * 4)(k0)
	sw	s6, (S6 * 4)(k0)
	sw	s7, (S7 * 4)(k0)
	sw	s8, (S8 * 4)(k0)
	sw	gp, (GP * 4)(k0)
	sw	sp, (SP * 4)(k0)
#endif
E 3
	subu	sp, sp, KERN_EXC_FRAME_SIZE
	.mask	0x80000000, (STAND_RA_OFFSET - KERN_EXC_FRAME_SIZE)
/*
 * Save the relevant kernel registers onto the stack.
 * We don't need to save s0 - s8, sp and gp because
 * the compiler does it for us.
 */
	sw	AT, KERN_REG_OFFSET + 0(sp)
	sw	v0, KERN_REG_OFFSET + 4(sp)
	sw	v1, KERN_REG_OFFSET + 8(sp)
	sw	a0, KERN_REG_OFFSET + 12(sp)
	mflo	v0
	mfhi	v1
	sw	a1, KERN_REG_OFFSET + 16(sp)
	sw	a2, KERN_REG_OFFSET + 20(sp)
	sw	a3, KERN_REG_OFFSET + 24(sp)
	sw	t0, KERN_REG_OFFSET + 28(sp)
	mfc0	a0, MACH_COP_0_STATUS_REG	# First arg is the status reg.
	sw	t1, KERN_REG_OFFSET + 32(sp)
	sw	t2, KERN_REG_OFFSET + 36(sp)
	sw	t3, KERN_REG_OFFSET + 40(sp)
	sw	t4, KERN_REG_OFFSET + 44(sp)
	mfc0	a1, MACH_COP_0_CAUSE_REG	# Second arg is the cause reg.
	sw	t5, KERN_REG_OFFSET + 48(sp)
	sw	t6, KERN_REG_OFFSET + 52(sp)
	sw	t7, KERN_REG_OFFSET + 56(sp)
	sw	t8, KERN_REG_OFFSET + 60(sp)
	mfc0	a2, MACH_COP_0_BAD_VADDR	# Third arg is the fault addr.
	sw	t9, KERN_REG_OFFSET + 64(sp)
	sw	ra, KERN_REG_OFFSET + 68(sp)
	sw	v0, KERN_MULT_LO_OFFSET(sp)
	sw	v1, KERN_MULT_HI_OFFSET(sp)
	mfc0	a3, MACH_COP_0_EXC_PC		# Fourth arg is the pc.
	sw	a0, KERN_SR_OFFSET(sp)
/*
 * Call the exception handler.
 */
	jal	trap
	sw	a3, STAND_RA_OFFSET(sp)		# for debugging
/*
 * Restore registers and return from the exception.
 * v0 contains the return address.
 */
	lw	a0, KERN_SR_OFFSET(sp)
	lw	t0, KERN_MULT_LO_OFFSET(sp)
	lw	t1, KERN_MULT_HI_OFFSET(sp)
	mtc0	a0, MACH_COP_0_STATUS_REG	# Restore the SR, disable intrs
	mtlo	t0
	mthi	t1
	move	k0, v0
	lw	AT, KERN_REG_OFFSET + 0(sp)
	lw	v0, KERN_REG_OFFSET + 4(sp)
	lw	v1, KERN_REG_OFFSET + 8(sp)
	lw	a0, KERN_REG_OFFSET + 12(sp)
	lw	a1, KERN_REG_OFFSET + 16(sp)
	lw	a2, KERN_REG_OFFSET + 20(sp)
	lw	a3, KERN_REG_OFFSET + 24(sp)
	lw	t0, KERN_REG_OFFSET + 28(sp)
	lw	t1, KERN_REG_OFFSET + 32(sp)
	lw	t2, KERN_REG_OFFSET + 36(sp)
	lw	t3, KERN_REG_OFFSET + 40(sp)
	lw	t4, KERN_REG_OFFSET + 44(sp)
	lw	t5, KERN_REG_OFFSET + 48(sp)
	lw	t6, KERN_REG_OFFSET + 52(sp)
	lw	t7, KERN_REG_OFFSET + 56(sp)
	lw	t8, KERN_REG_OFFSET + 60(sp)
	lw	t9, KERN_REG_OFFSET + 64(sp)
	lw	ra, KERN_REG_OFFSET + 68(sp)
	addu	sp, sp, KERN_EXC_FRAME_SIZE
	j	k0				# Now return from the
	rfe					#  exception.
	.set	at
D 13
	.set	reorder
E 13
END(MachKernGenException)

/*----------------------------------------------------------------------------
 *
 * MachUserGenException --
 *
 *	Handle an exception from user mode.
 *
 * Results:
 * 	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
D 15
NON_LEAF(MachUserGenException, STAND_FRAME_SIZE, ra)
E 15
I 15
NNON_LEAF(MachUserGenException, STAND_FRAME_SIZE, ra)
E 15
D 13
	.set	noreorder
E 13
	.set	noat
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
/*
 * Save all of the registers except for the kernel temporaries in u.u_pcb.
 */
	sw	AT, UADDR+U_PCB_REGS+(AST * 4)
	sw	v0, UADDR+U_PCB_REGS+(V0 * 4)
	sw	v1, UADDR+U_PCB_REGS+(V1 * 4)
	sw	a0, UADDR+U_PCB_REGS+(A0 * 4)
	mflo	v0
	sw	a1, UADDR+U_PCB_REGS+(A1 * 4)
	sw	a2, UADDR+U_PCB_REGS+(A2 * 4)
	sw	a3, UADDR+U_PCB_REGS+(A3 * 4)
	sw	t0, UADDR+U_PCB_REGS+(T0 * 4)
	mfhi	v1
	sw	t1, UADDR+U_PCB_REGS+(T1 * 4)
	sw	t2, UADDR+U_PCB_REGS+(T2 * 4)
	sw	t3, UADDR+U_PCB_REGS+(T3 * 4)
	sw	t4, UADDR+U_PCB_REGS+(T4 * 4)
	mfc0	a0, MACH_COP_0_STATUS_REG	# First arg is the status reg.
	sw	t5, UADDR+U_PCB_REGS+(T5 * 4)
	sw	t6, UADDR+U_PCB_REGS+(T6 * 4)
	sw	t7, UADDR+U_PCB_REGS+(T7 * 4)
	sw	s0, UADDR+U_PCB_REGS+(S0 * 4)
	mfc0	a1, MACH_COP_0_CAUSE_REG	# Second arg is the cause reg.
	sw	s1, UADDR+U_PCB_REGS+(S1 * 4)
	sw	s2, UADDR+U_PCB_REGS+(S2 * 4)
	sw	s3, UADDR+U_PCB_REGS+(S3 * 4)
	sw	s4, UADDR+U_PCB_REGS+(S4 * 4)
	mfc0	a2, MACH_COP_0_BAD_VADDR	# Third arg is the fault addr
	sw	s5, UADDR+U_PCB_REGS+(S5 * 4)
	sw	s6, UADDR+U_PCB_REGS+(S6 * 4)
	sw	s7, UADDR+U_PCB_REGS+(S7 * 4)
	sw	t8, UADDR+U_PCB_REGS+(T8 * 4)
	mfc0	a3, MACH_COP_0_EXC_PC		# Fourth arg is the pc.
	sw	t9, UADDR+U_PCB_REGS+(T9 * 4)
	sw	gp, UADDR+U_PCB_REGS+(GP * 4)
	sw	sp, UADDR+U_PCB_REGS+(SP * 4)
	sw	s8, UADDR+U_PCB_REGS+(S8 * 4)
	li	sp, KERNELSTACK - STAND_FRAME_SIZE	# switch to kernel SP
	sw	ra, UADDR+U_PCB_REGS+(RA * 4)
	sw	v0, UADDR+U_PCB_REGS+(MULLO * 4)
	sw	v1, UADDR+U_PCB_REGS+(MULHI * 4)
	sw	a0, UADDR+U_PCB_REGS+(SR * 4)
D 12
	la	gp, _gp				# switch to kernel GP
E 12
I 12
 #	la	gp, _gp				# switch to kernel GP
E 12
	sw	a3, UADDR+U_PCB_REGS+(PC * 4)
	sw	a3, STAND_RA_OFFSET(sp)		# for debugging
I 12
	.set	at
E 12
	and	t0, a0, ~MACH_SR_COP_1_BIT	# Turn off the FPU.
I 12
	.set	noat
E 12
/*
 * Call the exception handler.
 */
	jal	trap
	mtc0	t0, MACH_COP_0_STATUS_REG
/*
 * Restore user registers and return. NOTE: interrupts are enabled.
 */
	lw	a0, UADDR+U_PCB_REGS+(SR * 4)
	lw	t0, UADDR+U_PCB_REGS+(MULLO * 4)
	lw	t1, UADDR+U_PCB_REGS+(MULHI * 4)
	mtc0	a0, MACH_COP_0_STATUS_REG	# this should disable interrupts
	mtlo	t0
	mthi	t1
	lw	k0, UADDR+U_PCB_REGS+(PC * 4)
	lw	AT, UADDR+U_PCB_REGS+(AST * 4)
	lw	v0, UADDR+U_PCB_REGS+(V0 * 4)
	lw	v1, UADDR+U_PCB_REGS+(V1 * 4)
	lw	a0, UADDR+U_PCB_REGS+(A0 * 4)
	lw	a1, UADDR+U_PCB_REGS+(A1 * 4)
	lw	a2, UADDR+U_PCB_REGS+(A2 * 4)
	lw	a3, UADDR+U_PCB_REGS+(A3 * 4)
	lw	t0, UADDR+U_PCB_REGS+(T0 * 4)
	lw	t1, UADDR+U_PCB_REGS+(T1 * 4)
	lw	t2, UADDR+U_PCB_REGS+(T2 * 4)
	lw	t3, UADDR+U_PCB_REGS+(T3 * 4)
	lw	t4, UADDR+U_PCB_REGS+(T4 * 4)
	lw	t5, UADDR+U_PCB_REGS+(T5 * 4)
	lw	t6, UADDR+U_PCB_REGS+(T6 * 4)
	lw	t7, UADDR+U_PCB_REGS+(T7 * 4)
	lw	s0, UADDR+U_PCB_REGS+(S0 * 4)
	lw	s1, UADDR+U_PCB_REGS+(S1 * 4)
	lw	s2, UADDR+U_PCB_REGS+(S2 * 4)
	lw	s3, UADDR+U_PCB_REGS+(S3 * 4)
	lw	s4, UADDR+U_PCB_REGS+(S4 * 4)
	lw	s5, UADDR+U_PCB_REGS+(S5 * 4)
	lw	s6, UADDR+U_PCB_REGS+(S6 * 4)
	lw	s7, UADDR+U_PCB_REGS+(S7 * 4)
	lw	t8, UADDR+U_PCB_REGS+(T8 * 4)
	lw	t9, UADDR+U_PCB_REGS+(T9 * 4)
	lw	gp, UADDR+U_PCB_REGS+(GP * 4)
	lw	sp, UADDR+U_PCB_REGS+(SP * 4)
	lw	s8, UADDR+U_PCB_REGS+(S8 * 4)
	lw	ra, UADDR+U_PCB_REGS+(RA * 4)
	j	k0
	rfe
	.set	at
D 13
	.set	reorder
E 13
END(MachUserGenException)

/*----------------------------------------------------------------------------
 *
 * MachKernIntr --
 *
 *	Handle an interrupt from kernel mode.
D 15
 *	Interrupts must use a separate stack since during exit()
 *	there is a window of time when there is no kernel stack.
E 15
I 15
 *	Interrupts use the standard kernel stack.
D 19
 *	swtch_exit sets up a kernel stack after exit so interrupts won't fail.
E 19
I 19
 *	switch_exit sets up a kernel stack after exit so interrupts won't fail.
E 19
E 15
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
#define KINTR_REG_OFFSET	(STAND_FRAME_SIZE)
#define KINTR_SR_OFFSET		(STAND_FRAME_SIZE + KERN_REG_SIZE)
D 15
#define KINTR_SP_OFFSET		(STAND_FRAME_SIZE + KERN_REG_SIZE + 4)
#define KINTR_MULT_LO_OFFSET	(STAND_FRAME_SIZE + KERN_REG_SIZE + 8)
#define KINTR_MULT_HI_OFFSET	(STAND_FRAME_SIZE + KERN_REG_SIZE + 12)
#define	KINTR_FRAME_SIZE	(STAND_FRAME_SIZE + KERN_REG_SIZE + 16)
E 15
I 15
#define KINTR_MULT_LO_OFFSET	(STAND_FRAME_SIZE + KERN_REG_SIZE + 4)
#define KINTR_MULT_HI_OFFSET	(STAND_FRAME_SIZE + KERN_REG_SIZE + 8)
#define	KINTR_FRAME_SIZE	(STAND_FRAME_SIZE + KERN_REG_SIZE + 12)
E 15

D 15
NON_LEAF(MachKernIntr, KINTR_FRAME_SIZE, ra)
E 15
I 15
NNON_LEAF(MachKernIntr, KINTR_FRAME_SIZE, ra)
E 15
D 13
	.set	noreorder
E 13
	.set	noat
I 15
	subu	sp, sp, KINTR_FRAME_SIZE	# allocate stack frame
E 15
	.mask	0x80000000, (STAND_RA_OFFSET - KINTR_FRAME_SIZE)
/*
D 15
 * Check to see if we are already on the interrupt stack.
 */
	li	k0, MACH_CODE_START		# interrupt stack below code
	sltu	k1, sp, k0
	beq	k1, zero, 1f			# no, init sp
	nop
	sw	sp, KINTR_SP_OFFSET - KINTR_FRAME_SIZE(sp)	# save old sp
	b	2f
	subu	sp, sp, KINTR_FRAME_SIZE	# allocate stack frame
1:
	sw	sp, KINTR_SP_OFFSET - KINTR_FRAME_SIZE(k0)	# save old sp
	subu	sp, k0, KINTR_FRAME_SIZE	# switch to interrupt stack
2:
/*
E 15
 * Save the relevant kernel registers onto the stack.
 * We don't need to save s0 - s8, sp and gp because
 * the compiler does it for us.
 */
	sw	AT, KINTR_REG_OFFSET + 0(sp)
	sw	v0, KINTR_REG_OFFSET + 4(sp)
	sw	v1, KINTR_REG_OFFSET + 8(sp)
	sw	a0, KINTR_REG_OFFSET + 12(sp)
	mflo	v0
	mfhi	v1
	sw	a1, KINTR_REG_OFFSET + 16(sp)
	sw	a2, KINTR_REG_OFFSET + 20(sp)
	sw	a3, KINTR_REG_OFFSET + 24(sp)
	sw	t0, KINTR_REG_OFFSET + 28(sp)
	mfc0	a0, MACH_COP_0_STATUS_REG	# First arg is the status reg.
	sw	t1, KINTR_REG_OFFSET + 32(sp)
	sw	t2, KINTR_REG_OFFSET + 36(sp)
	sw	t3, KINTR_REG_OFFSET + 40(sp)
	sw	t4, KINTR_REG_OFFSET + 44(sp)
	mfc0	a1, MACH_COP_0_CAUSE_REG	# Second arg is the cause reg.
	sw	t5, KINTR_REG_OFFSET + 48(sp)
	sw	t6, KINTR_REG_OFFSET + 52(sp)
	sw	t7, KINTR_REG_OFFSET + 56(sp)
	sw	t8, KINTR_REG_OFFSET + 60(sp)
	mfc0	a2, MACH_COP_0_EXC_PC		# Third arg is the pc.
	sw	t9, KINTR_REG_OFFSET + 64(sp)
	sw	ra, KINTR_REG_OFFSET + 68(sp)
	sw	v0, KINTR_MULT_LO_OFFSET(sp)
	sw	v1, KINTR_MULT_HI_OFFSET(sp)
	sw	a0, KINTR_SR_OFFSET(sp)
/*
 * Call the interrupt handler.
 */
	jal	interrupt
	sw	a2, STAND_RA_OFFSET(sp)		# for debugging
/*
 * Restore registers and return from the interrupt.
 */
	lw	a0, KINTR_SR_OFFSET(sp)
	lw	t0, KINTR_MULT_LO_OFFSET(sp)
	lw	t1, KINTR_MULT_HI_OFFSET(sp)
	mtc0	a0, MACH_COP_0_STATUS_REG	# Restore the SR, disable intrs
	mtlo	t0
	mthi	t1
	lw	k0, STAND_RA_OFFSET(sp)
	lw	AT, KINTR_REG_OFFSET + 0(sp)
	lw	v0, KINTR_REG_OFFSET + 4(sp)
	lw	v1, KINTR_REG_OFFSET + 8(sp)
	lw	a0, KINTR_REG_OFFSET + 12(sp)
	lw	a1, KINTR_REG_OFFSET + 16(sp)
	lw	a2, KINTR_REG_OFFSET + 20(sp)
	lw	a3, KINTR_REG_OFFSET + 24(sp)
	lw	t0, KINTR_REG_OFFSET + 28(sp)
	lw	t1, KINTR_REG_OFFSET + 32(sp)
	lw	t2, KINTR_REG_OFFSET + 36(sp)
	lw	t3, KINTR_REG_OFFSET + 40(sp)
	lw	t4, KINTR_REG_OFFSET + 44(sp)
	lw	t5, KINTR_REG_OFFSET + 48(sp)
	lw	t6, KINTR_REG_OFFSET + 52(sp)
	lw	t7, KINTR_REG_OFFSET + 56(sp)
	lw	t8, KINTR_REG_OFFSET + 60(sp)
	lw	t9, KINTR_REG_OFFSET + 64(sp)
	lw	ra, KINTR_REG_OFFSET + 68(sp)
D 15
	lw	sp, KINTR_SP_OFFSET(sp)		# restore orig sp
E 15
I 15
	addu	sp, sp, KINTR_FRAME_SIZE
E 15
	j	k0				# Now return from the
	rfe					#  interrupt.
	.set	at
D 13
	.set	reorder
E 13
END(MachKernIntr)

/*----------------------------------------------------------------------------
 *
 * MachUserIntr --
 *
 *	Handle an interrupt from user mode.
 *	Note: we save minimal state in the u.u_pcb struct and use the standard
 *	kernel stack since there has to be a u page if we came from user mode.
 *	If there is a pending software interrupt, then save the remaining state
D 19
 *	and call softintr(). This is all because if we call swtch() inside
E 19
I 19
 *	and call softintr(). This is all because if we call switch() inside
E 19
 *	interrupt(), not all the user registers have been saved in u.u_pcb.
 *
 * Results:
 * 	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
D 15
NON_LEAF(MachUserIntr, STAND_FRAME_SIZE, ra)
E 15
I 15
NNON_LEAF(MachUserIntr, STAND_FRAME_SIZE, ra)
E 15
D 13
	.set	noreorder
E 13
	.set	noat
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
/*
 * Save the relevant user registers into the u.u_pcb struct.
 * We don't need to save s0 - s8 because
 * the compiler does it for us.
 */
	sw	AT, UADDR+U_PCB_REGS+(AST * 4)
	sw	v0, UADDR+U_PCB_REGS+(V0 * 4)
	sw	v1, UADDR+U_PCB_REGS+(V1 * 4)
	sw	a0, UADDR+U_PCB_REGS+(A0 * 4)
	mflo	v0
	mfhi	v1
	sw	a1, UADDR+U_PCB_REGS+(A1 * 4)
	sw	a2, UADDR+U_PCB_REGS+(A2 * 4)
	sw	a3, UADDR+U_PCB_REGS+(A3 * 4)
	sw	t0, UADDR+U_PCB_REGS+(T0 * 4)
	mfc0	a0, MACH_COP_0_STATUS_REG	# First arg is the status reg.
	sw	t1, UADDR+U_PCB_REGS+(T1 * 4)
	sw	t2, UADDR+U_PCB_REGS+(T2 * 4)
	sw	t3, UADDR+U_PCB_REGS+(T3 * 4)
	sw	t4, UADDR+U_PCB_REGS+(T4 * 4)
	mfc0	a1, MACH_COP_0_CAUSE_REG	# Second arg is the cause reg.
	sw	t5, UADDR+U_PCB_REGS+(T5 * 4)
	sw	t6, UADDR+U_PCB_REGS+(T6 * 4)
	sw	t7, UADDR+U_PCB_REGS+(T7 * 4)
	sw	t8, UADDR+U_PCB_REGS+(T8 * 4)
	mfc0	a2, MACH_COP_0_EXC_PC		# Third arg is the pc.
	sw	t9, UADDR+U_PCB_REGS+(T9 * 4)
	sw	gp, UADDR+U_PCB_REGS+(GP * 4)
	sw	sp, UADDR+U_PCB_REGS+(SP * 4)
	sw	ra, UADDR+U_PCB_REGS+(RA * 4)
	li	sp, KERNELSTACK - STAND_FRAME_SIZE	# switch to kernel SP
	sw	v0, UADDR+U_PCB_REGS+(MULLO * 4)
	sw	v1, UADDR+U_PCB_REGS+(MULHI * 4)
	sw	a0, UADDR+U_PCB_REGS+(SR * 4)
	sw	a2, UADDR+U_PCB_REGS+(PC * 4)
D 12
	la	gp, _gp				# switch to kernel GP
E 12
I 12
 #	la	gp, _gp				# switch to kernel GP
	.set	at
E 12
	and	t0, a0, ~MACH_SR_COP_1_BIT	# Turn off the FPU.
I 12
	.set	noat
E 12
	mtc0	t0, MACH_COP_0_STATUS_REG
/*
 * Call the interrupt handler.
 */
	jal	interrupt
	sw	a2, STAND_RA_OFFSET(sp)		# for debugging
/*
 * Restore registers and return from the interrupt.
 */
	lw	a0, UADDR+U_PCB_REGS+(SR * 4)
	lw	v0, astpending			# any pending interrupts?
	mtc0	a0, MACH_COP_0_STATUS_REG	# Restore the SR, disable intrs
D 12
	bne	v0, zero, 1f			# don't restore, call softintr
E 12
I 12
	bne	v0, zero, 1f			# dont restore, call softintr
E 12
	lw	t0, UADDR+U_PCB_REGS+(MULLO * 4)
	lw	t1, UADDR+U_PCB_REGS+(MULHI * 4)
	lw	k0, UADDR+U_PCB_REGS+(PC * 4)
	lw	AT, UADDR+U_PCB_REGS+(AST * 4)
	lw	v0, UADDR+U_PCB_REGS+(V0 * 4)
	lw	v1, UADDR+U_PCB_REGS+(V1 * 4)
	lw	a0, UADDR+U_PCB_REGS+(A0 * 4)
	lw	a1, UADDR+U_PCB_REGS+(A1 * 4)
	lw	a2, UADDR+U_PCB_REGS+(A2 * 4)
	lw	a3, UADDR+U_PCB_REGS+(A3 * 4)
	mtlo	t0
	mthi	t1
	lw	t0, UADDR+U_PCB_REGS+(T0 * 4)
	lw	t1, UADDR+U_PCB_REGS+(T1 * 4)
	lw	t2, UADDR+U_PCB_REGS+(T2 * 4)
	lw	t3, UADDR+U_PCB_REGS+(T3 * 4)
	lw	t4, UADDR+U_PCB_REGS+(T4 * 4)
	lw	t5, UADDR+U_PCB_REGS+(T5 * 4)
	lw	t6, UADDR+U_PCB_REGS+(T6 * 4)
	lw	t7, UADDR+U_PCB_REGS+(T7 * 4)
	lw	t8, UADDR+U_PCB_REGS+(T8 * 4)
	lw	t9, UADDR+U_PCB_REGS+(T9 * 4)
	lw	gp, UADDR+U_PCB_REGS+(GP * 4)
	lw	sp, UADDR+U_PCB_REGS+(SP * 4)
	lw	ra, UADDR+U_PCB_REGS+(RA * 4)
	j	k0				# Now return from the
	rfe					#  interrupt.

1:
/*
 * We have pending software interrupts; save remaining user state in u.u_pcb.
 */
	sw	s0, UADDR+U_PCB_REGS+(S0 * 4)
	sw	s1, UADDR+U_PCB_REGS+(S1 * 4)
	sw	s2, UADDR+U_PCB_REGS+(S2 * 4)
	sw	s3, UADDR+U_PCB_REGS+(S3 * 4)
	sw	s4, UADDR+U_PCB_REGS+(S4 * 4)
	sw	s5, UADDR+U_PCB_REGS+(S5 * 4)
	sw	s6, UADDR+U_PCB_REGS+(S6 * 4)
	sw	s7, UADDR+U_PCB_REGS+(S7 * 4)
	sw	s8, UADDR+U_PCB_REGS+(S8 * 4)
	li	t0, MACH_HARD_INT_MASK | MACH_SR_INT_ENA_CUR
/*
 * Call the software interrupt handler.
 */
	jal	softintr
	mtc0	t0, MACH_COP_0_STATUS_REG	# enable interrupts (spl0)
/*
 * Restore user registers and return. NOTE: interrupts are enabled.
 */
	lw	a0, UADDR+U_PCB_REGS+(SR * 4)
	lw	t0, UADDR+U_PCB_REGS+(MULLO * 4)
	lw	t1, UADDR+U_PCB_REGS+(MULHI * 4)
	mtc0	a0, MACH_COP_0_STATUS_REG	# this should disable interrupts
	mtlo	t0
	mthi	t1
	lw	k0, UADDR+U_PCB_REGS+(PC * 4)
	lw	AT, UADDR+U_PCB_REGS+(AST * 4)
	lw	v0, UADDR+U_PCB_REGS+(V0 * 4)
	lw	v1, UADDR+U_PCB_REGS+(V1 * 4)
	lw	a0, UADDR+U_PCB_REGS+(A0 * 4)
	lw	a1, UADDR+U_PCB_REGS+(A1 * 4)
	lw	a2, UADDR+U_PCB_REGS+(A2 * 4)
	lw	a3, UADDR+U_PCB_REGS+(A3 * 4)
	lw	t0, UADDR+U_PCB_REGS+(T0 * 4)
	lw	t1, UADDR+U_PCB_REGS+(T1 * 4)
	lw	t2, UADDR+U_PCB_REGS+(T2 * 4)
	lw	t3, UADDR+U_PCB_REGS+(T3 * 4)
	lw	t4, UADDR+U_PCB_REGS+(T4 * 4)
	lw	t5, UADDR+U_PCB_REGS+(T5 * 4)
	lw	t6, UADDR+U_PCB_REGS+(T6 * 4)
	lw	t7, UADDR+U_PCB_REGS+(T7 * 4)
	lw	s0, UADDR+U_PCB_REGS+(S0 * 4)
	lw	s1, UADDR+U_PCB_REGS+(S1 * 4)
	lw	s2, UADDR+U_PCB_REGS+(S2 * 4)
	lw	s3, UADDR+U_PCB_REGS+(S3 * 4)
	lw	s4, UADDR+U_PCB_REGS+(S4 * 4)
	lw	s5, UADDR+U_PCB_REGS+(S5 * 4)
	lw	s6, UADDR+U_PCB_REGS+(S6 * 4)
	lw	s7, UADDR+U_PCB_REGS+(S7 * 4)
	lw	t8, UADDR+U_PCB_REGS+(T8 * 4)
	lw	t9, UADDR+U_PCB_REGS+(T9 * 4)
	lw	gp, UADDR+U_PCB_REGS+(GP * 4)
	lw	sp, UADDR+U_PCB_REGS+(SP * 4)
	lw	s8, UADDR+U_PCB_REGS+(S8 * 4)
	lw	ra, UADDR+U_PCB_REGS+(RA * 4)
	j	k0
	rfe
	.set	at
D 13
	.set	reorder
E 13
END(MachUserIntr)

I 3
#if 0
E 3
/*----------------------------------------------------------------------------
 *
 * MachTLBModException --
 *
 *	Handle a TLB modified exception.
 *	The BaddVAddr, Context, and EntryHi registers contain the failed
 *	virtual address.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
D 15
LEAF(MachTLBModException)
E 15
I 15
NLEAF(MachTLBModException)
E 15
D 3
#if 0
E 3
D 13
	.set	noreorder
E 13
	.set	noat
	tlbp					# find the TLB entry
	mfc0	k0, MACH_COP_0_TLB_LOW		# get the physical address
	mfc0	k1, MACH_COP_0_TLB_INDEX	# check to be sure its valid
	or	k0, k0, VMMACH_TLB_MOD_BIT	# update TLB
	blt	k1, zero, 4f			# not found!!!
	mtc0	k0, MACH_COP_0_TLB_LOW
	li	k1, MACH_CACHED_MEMORY_ADDR
	subu	k0, k0, k1
	srl	k0, k0, VMMACH_TLB_PHYS_PAGE_SHIFT
	la	k1, pmap_attributes
D 13
	add	k0, k0, k1
E 13
I 13
	addu	k0, k0, k1
E 13
	lbu	k1, 0(k0)			# fetch old value
	nop
	or	k1, k1, 1			# set modified bit
	sb	k1, 0(k0)			# save new value
	mfc0	k0, MACH_COP_0_EXC_PC		# get return address
	nop
	j	k0
	rfe
4:
	break	0				# panic
D 13
	.set	reorder
E 13
	.set	at
D 3
#endif
E 3
END(MachTLBModException)
I 3
#endif
E 3

/*----------------------------------------------------------------------------
 *
 * MachTLBMissException --
 *
 *	Handle a TLB miss exception from kernel mode.
 *	The BaddVAddr, Context, and EntryHi registers contain the failed
 *	virtual address.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
D 15
LEAF(MachTLBMissException)
E 15
I 15
NLEAF(MachTLBMissException)
E 15
D 13
	.set	noreorder
E 13
	.set	noat
	mfc0	k0, MACH_COP_0_BAD_VADDR	# get the fault address
D 15
	li	k1, MACH_KSEG2_ADDR		# compute index
E 15
I 15
	li	k1, VM_MIN_KERNEL_ADDRESS	# compute index
E 15
	subu	k0, k0, k1
I 15
	lw	k1, Sysmapsize			# index within range?
E 15
	srl	k0, k0, PGSHIFT
D 15
	li	k1, PMAP_HASH_KPAGES * NPTEPG	# index within range?
E 15
	sltu	k1, k0, k1
D 12
	beq	k1, zero, SlowFault		# No. do it the long way
E 12
I 12
D 15
	beq	k1, zero, MachKernGenException	# No. do it the long way
E 15
I 15
	beq	k1, zero, 1f			# No. check for valid stack
	nop
	lw	k1, Sysmap
E 15
E 12
	sll	k0, k0, 2			# compute offset from index
D 12
	lw	k0, PMAP_HASH_KADDR(k0)		# get PTE entry
E 12
I 12
D 15
	li	k1, PMAP_HASH_KADDR
	addu	k0, k0, k1
	lw	k0, 0(k0)			# get PTE entry
E 15
I 15
	addu	k1, k1, k0
	lw	k0, 0(k1)			# get PTE entry
E 15
E 12
	mfc0	k1, MACH_COP_0_EXC_PC		# get return address
	mtc0	k0, MACH_COP_0_TLB_LOW		# save PTE entry
D 12
	and	k0, k0, PG_V			# make sure it's valid
	beq	k0, zero, SlowFault		# No. do it the long way
E 12
I 12
D 15
	and	k0, k0, PG_V			# make sure its valid
	beq	k0, zero, MachKernGenException	# No. do it the long way
E 15
I 15
	and	k0, k0, PG_V			# check for valid entry
	beq	k0, zero, MachKernGenException	# PTE invalid
E 15
E 12
	nop
	tlbwr					# update TLB
	j	k1
	rfe
I 15

1:
	subu	k0, sp, UADDR + 0x200		# check to see if we have a
	sltiu	k0, UPAGES*NBPG - 0x200		#  valid kernel stack
	bne	k0, zero, MachKernGenException	# Go panic
	nop

	la	a0, start - START_FRAME - 8	# set sp to a valid place
	sw	sp, 24(a0)
	move	sp, a0
	la	a0, 1f
	mfc0	a2, MACH_COP_0_STATUS_REG
	mfc0	a3, MACH_COP_0_CAUSE_REG
	mfc0	a1, MACH_COP_0_EXC_PC
	sw	a2, 16(sp)
	sw	a3, 20(sp)
	sw	sp, 24(sp)
	move	a2, ra
	jal	printf
	mfc0	a3, MACH_COP_0_BAD_VADDR
	.data
1:
	.asciiz	"ktlbmiss: PC %x RA %x ADR %x\nSR %x CR %x SP %x\n"
	.text

	la	sp, start - START_FRAME		# set sp to a valid place
	PANIC("kernel stack overflow")
E 15
D 13
	.set	reorder
E 13
	.set	at
END(MachTLBMissException)

/*
 * Set/clear software interrupt routines.
 */

LEAF(setsoftclock)
I 23
	mfc0	v1, MACH_COP_0_STATUS_REG	# save status register
	mtc0	zero, MACH_COP_0_STATUS_REG	# disable interrupts (2 cycles)
	nop
	nop
E 23
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_CAUSE_REG	# read cause register
	nop
	or	v0, v0, MACH_SOFT_INT_MASK_0	# set soft clock interrupt
	mtc0	v0, MACH_COP_0_CAUSE_REG	# save it
I 23
	mtc0	v1, MACH_COP_0_STATUS_REG
E 23
	j	ra
	nop
D 13
	.set	reorder
E 13
END(setsoftclock)

LEAF(clearsoftclock)
I 23
	mfc0	v1, MACH_COP_0_STATUS_REG	# save status register
	mtc0	zero, MACH_COP_0_STATUS_REG	# disable interrupts (2 cycles)
	nop
	nop
E 23
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_CAUSE_REG	# read cause register
	nop
	and	v0, v0, ~MACH_SOFT_INT_MASK_0	# clear soft clock interrupt
	mtc0	v0, MACH_COP_0_CAUSE_REG	# save it
I 23
	mtc0	v1, MACH_COP_0_STATUS_REG
E 23
	j	ra
	nop
D 13
	.set	reorder
E 13
END(clearsoftclock)

LEAF(setsoftnet)
I 23
	mfc0	v1, MACH_COP_0_STATUS_REG	# save status register
	mtc0	zero, MACH_COP_0_STATUS_REG	# disable interrupts (2 cycles)
	nop
	nop
E 23
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_CAUSE_REG	# read cause register
	nop
	or	v0, v0, MACH_SOFT_INT_MASK_1	# set soft net interrupt
	mtc0	v0, MACH_COP_0_CAUSE_REG	# save it
I 23
	mtc0	v1, MACH_COP_0_STATUS_REG
E 23
	j	ra
	nop
D 13
	.set	reorder
E 13
END(setsoftnet)

LEAF(clearsoftnet)
I 23
	mfc0	v1, MACH_COP_0_STATUS_REG	# save status register
	mtc0	zero, MACH_COP_0_STATUS_REG	# disable interrupts (2 cycles)
	nop
	nop
E 23
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_CAUSE_REG	# read cause register
	nop
	and	v0, v0, ~MACH_SOFT_INT_MASK_1	# clear soft net interrupt
	mtc0	v0, MACH_COP_0_CAUSE_REG	# save it
I 23
	mtc0	v1, MACH_COP_0_STATUS_REG
E 23
	j	ra
	nop
D 13
	.set	reorder
E 13
END(clearsoftnet)

/*
 * Set/change interrupt priority routines.
 */

LEAF(MachEnableIntr)
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
	nop
	or	v0, v0, MACH_SR_INT_ENA_CUR
	mtc0	v0, MACH_COP_0_STATUS_REG	# enable all interrupts
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachEnableIntr)

LEAF(spl0)
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
	nop
	or	t0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
	mtc0	t0, MACH_COP_0_STATUS_REG	# enable all interrupts
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
D 13
	.set	reorder
E 13
END(spl0)

LEAF(splsoftclock)
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
D 2
	li	t0, ~MACH_SOFT_INT_MASK_1	# disable soft clock
E 2
I 2
	li	t0, ~MACH_SOFT_INT_MASK_0	# disable soft clock
E 2
	and	t0, t0, v0
	mtc0	t0, MACH_COP_0_STATUS_REG	# save it
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
D 13
	.set	reorder
E 13
END(splsoftclock)

I 2
D 3
LEAF(splnet)
E 3
I 3
LEAF(Mach_spl0)
E 3
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
D 3
	li	t0, ~(MACH_SOFT_INT_MASK_0 | MACH_SOFT_INT_MASK_1)
E 3
I 3
	li	t0, ~(MACH_INT_MASK_0|MACH_SOFT_INT_MASK_1|MACH_SOFT_INT_MASK_0)
E 3
	and	t0, t0, v0
	mtc0	t0, MACH_COP_0_STATUS_REG	# save it
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
D 13
	.set	reorder
E 13
D 3
END(splnet)
E 3
I 3
END(Mach_spl0)
E 3

E 2
D 3
LEAF(splbio)
E 3
I 3
LEAF(Mach_spl1)
E 3
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
D 2
	li	t0, ~MACH_INT_MASK_0		# disable SCSI interrupts
E 2
I 2
D 3
	li	t0, ~(MACH_INT_MASK_0 | MACH_SOFT_INT_MASK_0 | MACH_SOFT_INT_MASK_1)
E 3
I 3
	li	t0, ~(MACH_INT_MASK_1|MACH_SOFT_INT_MASK_0|MACH_SOFT_INT_MASK_1)
E 3
E 2
	and	t0, t0, v0
	mtc0	t0, MACH_COP_0_STATUS_REG	# save it
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
D 13
	.set	reorder
E 13
D 3
END(splbio)
E 3
I 3
END(Mach_spl1)
E 3

D 2
/*
 * Block interrupts for any device that could allocate memory at interrupt
 * time.
 */
LEAF(splnet)
ALEAF(splimp)
E 2
I 2
D 3
LEAF(splimp)
E 3
I 3
LEAF(Mach_spl2)
E 3
E 2
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
D 2
	li	t0, ~MACH_INT_MASK_1		# disable network interrupts
E 2
I 2
D 3
	li	t0, ~(MACH_INT_MASK_1 | MACH_SOFT_INT_MASK_1 | MACH_SOFT_INT_MASK_0)
E 3
I 3
	li	t0, ~(MACH_INT_MASK_2|MACH_SOFT_INT_MASK_1|MACH_SOFT_INT_MASK_0)
E 3
E 2
	and	t0, t0, v0
	mtc0	t0, MACH_COP_0_STATUS_REG	# save it
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
D 13
	.set	reorder
E 13
D 3
END(splnet)
E 3
I 3
END(Mach_spl2)
E 3

D 3
LEAF(spltty)
E 3
I 3
LEAF(Mach_spl3)
E 3
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
D 2
	li	t0, ~MACH_INT_MASK_2		# disable tty interrupts
E 2
I 2
D 3
	li	t0, ~(MACH_INT_MASK_2 | MACH_SOFT_INT_MASK_1 | MACH_SOFT_INT_MASK_0)
E 3
I 3
	li	t0, ~(MACH_INT_MASK_3|MACH_SOFT_INT_MASK_1|MACH_SOFT_INT_MASK_0)
E 3
E 2
	and	t0, t0, v0
	mtc0	t0, MACH_COP_0_STATUS_REG	# save it
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
D 13
	.set	reorder
E 13
D 3
END(spltty)
E 3
I 3
END(Mach_spl3)
E 3

I 15
/*
 * We define an alternate entry point after mcount is called so it
 * can be used in mcount without causeing a recursive loop.
 */
E 15
D 3
LEAF(splclock)
	.set	noreorder
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
D 2
	li	t0, ~MACH_INT_MASK_3		# disable clock interrupts
E 2
I 2
	li	t0, ~(MACH_INT_MASK_3 | MACH_SOFT_INT_MASK_1 | MACH_SOFT_INT_MASK_0)
E 2
	and	t0, t0, v0
	mtc0	t0, MACH_COP_0_STATUS_REG	# save it
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
	.set	reorder
END(splclock)

E 3
LEAF(splhigh)
I 15
ALEAF(_splhigh)
E 15
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG	# read status register
	li	t0, ~MACH_SR_INT_ENA_CUR	# disable all interrupts
	and	t0, t0, v0
	mtc0	t0, MACH_COP_0_STATUS_REG	# save it
	j	ra
	and	v0, v0, (MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
D 13
	.set	reorder
E 13
END(splhigh)

/*
 * Restore saved interrupt mask.
 */
LEAF(splx)
I 15
ALEAF(_splx)
E 15
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_STATUS_REG
	li	t0, ~(MACH_INT_MASK | MACH_SR_INT_ENA_CUR)
	and	t0, t0, v0
	or	t0, t0, a0
	mtc0	t0, MACH_COP_0_STATUS_REG
	j	ra
	nop
D 13
	.set	reorder
E 13
END(splx)

/*----------------------------------------------------------------------------
 *
 * MachEmptyWriteBuffer --
 *
 *	Return when the write buffer is empty.
 *
 *	MachEmptyWriteBuffer()
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
LEAF(MachEmptyWriteBuffer)
D 13
	.set	noreorder
E 13
	nop
	nop
	nop
	nop
1:	bc0f	1b
	nop
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachEmptyWriteBuffer)

/*--------------------------------------------------------------------------
 *
 * MachTLBWriteIndexed --
 *
 *	Write the given entry into the TLB at the given index.
 *
 *	MachTLBWriteIndexed(index, highEntry, lowEntry)
 *		int index;
 *		int highEntry;
 *		int lowEntry;
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	TLB entry set.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachTLBWriteIndexed)
D 13
	.set	noreorder
E 13
D 15
	mfc0	t1, MACH_COP_0_STATUS_REG	# Save the status register.
E 15
I 15
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
E 15
D 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save the current PID.
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
I 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save the current PID.
E 3

	sll	a0, a0, VMMACH_TLB_INDEX_SHIFT
	mtc0	a0, MACH_COP_0_TLB_INDEX	# Set the index.
	mtc0	a1, MACH_COP_0_TLB_HI		# Set up entry high.
	mtc0	a2, MACH_COP_0_TLB_LOW		# Set up entry low.
	nop
	tlbwi					# Write the TLB

	mtc0	t0, MACH_COP_0_TLB_HI		# Restore the PID.
	j	ra
D 15
	mtc0	t1, MACH_COP_0_STATUS_REG	# Restore the status register
E 15
I 15
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
E 15
D 13
	.set	reorder
E 13
END(MachTLBWriteIndexed)

I 15
#if 0
E 15
/*--------------------------------------------------------------------------
 *
 * MachTLBWriteRandom --
 *
 *	Write the given entry into the TLB at a random location.
 *
 *	MachTLBWriteRandom(highEntry, lowEntry)
 *		unsigned highEntry;
 *		unsigned lowEntry;
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	TLB entry set.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachTLBWriteRandom)
D 13
	.set	noreorder
E 13
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
D 3
	mfc0	v0, MACH_COP_0_TLB_HI		# Save the current PID.
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
I 3
	mfc0	v0, MACH_COP_0_TLB_HI		# Save the current PID.
I 15
	nop
E 15
E 3

	mtc0	a0, MACH_COP_0_TLB_HI		# Set up entry high.
	mtc0	a1, MACH_COP_0_TLB_LOW		# Set up entry low.
	nop
	tlbwr					# Write the TLB

	mtc0	v0, MACH_COP_0_TLB_HI		# Restore the PID.
	j	ra
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
D 13
	.set	reorder
E 13
END(MachTLBWriteRandom)
I 15
#endif
E 15

/*--------------------------------------------------------------------------
 *
 * MachSetPID --
 *
 *	Write the given pid into the TLB pid reg.
 *
 *	MachSetPID(pid)
 *		int pid;
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	PID set in the entry hi register.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachSetPID)
D 13
	.set	noreorder
E 13
	sll	a0, a0, VMMACH_TLB_PID_SHIFT	# put PID in right spot
	mtc0	a0, MACH_COP_0_TLB_HI		# Write the hi reg value
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachSetPID)

/*--------------------------------------------------------------------------
 *
 * MachTLBFlush --
 *
 *	Flush the "random" entries from the TLB.
 *
 *	MachTLBFlush()
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The TLB is flushed.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachTLBFlush)
D 13
	.set	noreorder
E 13
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
D 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save the PID
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
I 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save the PID
E 3
D 15
	li	t1, MACH_RESERVED_ADDR		# invalid address
E 15
I 15
	li	t1, MACH_CACHED_MEMORY_ADDR	# invalid address
E 15
	mtc0	t1, MACH_COP_0_TLB_HI		# Mark entry high as invalid
	mtc0	zero, MACH_COP_0_TLB_LOW	# Zero out low entry.
/*
D 3
 * Align the starting value (t1), the increment (t2) and the upper bound (t3).
E 3
I 3
 * Align the starting value (t1) and the upper bound (t2).
E 3
 */
	li	t1, VMMACH_FIRST_RAND_ENTRY << VMMACH_TLB_INDEX_SHIFT
D 3
	li	t2, 1 << VMMACH_TLB_INDEX_SHIFT
	li	t3, VMMACH_NUM_TLB_ENTRIES << VMMACH_TLB_INDEX_SHIFT
E 3
I 3
	li	t2, VMMACH_NUM_TLB_ENTRIES << VMMACH_TLB_INDEX_SHIFT
E 3
1:
	mtc0	t1, MACH_COP_0_TLB_INDEX	# Set the index register.
D 3
	addu	t1, t1, t2			# Increment index.
	bne	t1, t3, 1b			# NB: always executes next
E 3
I 3
	addu	t1, t1, 1 << VMMACH_TLB_INDEX_SHIFT	# Increment index.
D 15
	bne	t1, t2, 1b			# NB: always executes next
E 15
I 15
	bne	t1, t2, 1b
E 15
E 3
	tlbwi					# Write the TLB entry.

	mtc0	t0, MACH_COP_0_TLB_HI		# Restore the PID
	j	ra
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
D 13
	.set	reorder
E 13
END(MachTLBFlush)

I 15
#if 0
E 15
/*--------------------------------------------------------------------------
 *
 * MachTLBFlushPID --
 *
 *	Flush all entries with the given PID from the TLB.
 *
 *	MachTLBFlushPID(pid)
 *		int pid;
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	All entries corresponding to this PID are flushed.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachTLBFlushPID)
D 13
	.set	noreorder
E 13
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
D 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save the current PID
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
I 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save the current PID
E 3
	sll	a0, a0, VMMACH_TLB_PID_SHIFT	# Align the pid to flush.
/*
D 3
 * Align the starting value (t1), the increment (t2) and the upper bound (t3).
E 3
I 3
 * Align the starting value (t1) and the upper bound (t2).
E 3
 */
	li	t1, VMMACH_FIRST_RAND_ENTRY << VMMACH_TLB_INDEX_SHIFT
D 3
	li	t2, 1 << VMMACH_TLB_INDEX_SHIFT
	li	t3, VMMACH_NUM_TLB_ENTRIES << VMMACH_TLB_INDEX_SHIFT
E 3
I 3
	li	t2, VMMACH_NUM_TLB_ENTRIES << VMMACH_TLB_INDEX_SHIFT
E 3
	mtc0	t1, MACH_COP_0_TLB_INDEX	# Set the index register
1:
D 3
	addu	t1, t1, t2			# Increment index.
E 3
I 3
	addu	t1, t1, 1 << VMMACH_TLB_INDEX_SHIFT	# Increment index.
E 3
	tlbr					# Read from the TLB
	mfc0	t4, MACH_COP_0_TLB_HI		# Fetch the hi register.
	nop
D 12
	and	t4, t4, VMMACH_TLB_PID		# compare PID's
E 12
I 12
	and	t4, t4, VMMACH_TLB_PID		# compare PIDs
E 12
	bne	t4, a0, 2f
D 15
	li	v0, MACH_RESERVED_ADDR		# invalid address
E 15
I 15
	li	v0, MACH_CACHED_MEMORY_ADDR	# invalid address
E 15
	mtc0	v0, MACH_COP_0_TLB_HI		# Mark entry high as invalid
	mtc0	zero, MACH_COP_0_TLB_LOW	# Zero out low entry.
	nop
	tlbwi					# Write the entry.
2:
D 3
	bne	t1, t3, 1b
E 3
I 3
	bne	t1, t2, 1b
E 3
	mtc0	t1, MACH_COP_0_TLB_INDEX	# Set the index register

	mtc0	t0, MACH_COP_0_TLB_HI		# restore PID
	j	ra
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
D 13
	.set	reorder
E 13
END(MachTLBFlushPID)
I 15
#endif
E 15

/*--------------------------------------------------------------------------
 *
 * MachTLBFlushAddr --
 *
D 3
 *	Flush any TLB entries for the given address.
E 3
I 3
 *	Flush any TLB entries for the given address and TLB PID.
E 3
 *
D 3
 *	MachTLBFlushAddr(virtaddr)
 *		unsigned virtaddr;
E 3
I 3
 *	MachTLBFlushAddr(highreg)
 *		unsigned highreg;
E 3
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The process's page is flushed from the TLB.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachTLBFlushAddr)
D 13
	.set	noreorder
E 13
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
D 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Get current PID
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
I 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Get current PID
I 15
	nop
E 15

E 3
	mtc0	a0, MACH_COP_0_TLB_HI		# look for addr & PID
D 3
	mtc0	zero, MACH_COP_0_TLB_LOW	# look for matching PID
E 3
	nop
	tlbp					# Probe for the entry.
	mfc0	v0, MACH_COP_0_TLB_INDEX	# See what we got
D 15
	li	t1, MACH_RESERVED_ADDR		# Load invalid entry.
E 15
I 15
	li	t1, MACH_CACHED_MEMORY_ADDR	# Load invalid entry.
E 15
	bltz	v0, 1f				# index < 0 => !found
D 3
	mtc0	t1, MACH_COP_0_TLB_HI		# Prepare index hi.
E 3
I 3
	mtc0	t1, MACH_COP_0_TLB_HI		# Mark entry high as invalid
	mtc0	zero, MACH_COP_0_TLB_LOW	# Zero out low entry.
E 3
	nop
	tlbwi
1:
	mtc0	t0, MACH_COP_0_TLB_HI		# restore PID
	j	ra
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
D 13
	.set	reorder
E 13
END(MachTLBFlushAddr)

/*--------------------------------------------------------------------------
 *
 * MachTLBUpdate --
 *
D 15
 *	Update the TLB if highreg is found.
E 15
I 15
 *	Update the TLB if highreg is found; otherwise, enter the data.
E 15
 *
 *	MachTLBUpdate(highreg, lowreg)
 *		unsigned highreg, lowreg;
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachTLBUpdate)
D 13
	.set	noreorder
E 13
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
D 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save current PID
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
I 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Save current PID
D 15

E 15
I 15
	nop					# 2 cycles before intr disabled
E 15
E 3
	mtc0	a0, MACH_COP_0_TLB_HI		# init high reg.
D 15
	mtc0	a1, MACH_COP_0_TLB_LOW		# init low reg.
E 15
	nop
	tlbp					# Probe for the entry.
	mfc0	v0, MACH_COP_0_TLB_INDEX	# See what we got
D 15
	nop
E 15
I 15
	mtc0	a1, MACH_COP_0_TLB_LOW		# init low reg.
E 15
	bltz	v0, 1f				# index < 0 => !found
D 15
	nop
	tlbwi
E 15
I 15
	sra	v0, v0, VMMACH_TLB_INDEX_SHIFT	# convert index to regular num
	b	2f
	tlbwi					# update slot found
E 15
1:
I 15
	mtc0	a0, MACH_COP_0_TLB_HI		# init high reg.
	nop
	tlbwr					# enter into a random slot
2:
E 15
	mtc0	t0, MACH_COP_0_TLB_HI		# restore PID
	j	ra
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
D 13
	.set	reorder
E 13
END(MachTLBUpdate)

D 3
#ifdef DEBUG
E 3
I 3
D 15
#if defined(DEBUG) || defined(KADB)
E 15
I 15
#if defined(DEBUG)
E 15
E 3
/*--------------------------------------------------------------------------
 *
D 3
 * MachTLBDump --
E 3
I 3
 * MachTLBFind --
E 3
 *
D 3
 *	Print all entries in the TLB if 'all' is true; otherwise, just
 *	print valid entries.
E 3
I 3
 *	Search the TLB for the given entry.
E 3
 *
D 3
 *	MachTLBDump(all)
 *		int all;
E 3
I 3
 *	MachTLBFind(hi)
 *		unsigned hi;
E 3
 *
 * Results:
D 3
 *	None.
E 3
I 3
 *	Returns a value >= 0 if the entry was found (the index).
 *	Returns a value < 0 if the entry was not found.
E 3
 *
 * Side effects:
D 3
 *	None.
E 3
I 3
 *	tlbhi and tlblo will contain the TLB entry found.
E 3
 *
 *--------------------------------------------------------------------------
 */
D 3

#define DUMP_FRAME_SIZE	(STAND_FRAME_SIZE + 4*4)

NON_LEAF(MachTLBDump, DUMP_FRAME_SIZE, ra)
	.set	noreorder
	subu	sp, sp, DUMP_FRAME_SIZE
	sw	s0, STAND_RA_OFFSET(sp)
	sw	s1, STAND_RA_OFFSET+4(sp)
	sw	s2, STAND_RA_OFFSET+8(sp)
	sw	s3, STAND_RA_OFFSET+12(sp)
	sw	ra, STAND_RA_OFFSET+16(sp)
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)

	mfc0	s0, MACH_COP_0_TLB_HI		# Save the current PID
	sw	a0, DUMP_FRAME_SIZE(sp)		# Save 'all'
/*
 * Align the starting value (s1), the increment (s2) and the upper bound (s3).
 */
	move	s1, zero
	li	s2, 1 << VMMACH_TLB_INDEX_SHIFT
	li	s3, VMMACH_NUM_TLB_ENTRIES << VMMACH_TLB_INDEX_SHIFT
	mtc0	s1, MACH_COP_0_TLB_INDEX	# Set the index register
1:
	addu	s1, s1, s2			# Increment index.
	tlbr					# Read from the TLB
	bne	a0, zero, 2f			# skip valid check if 'all'
	mfc0	a3, MACH_COP_0_TLB_LOW		# Fetch the low register.
	nop
	and	t0, a3, PG_V			# is it valid?
	beq	t0, zero, 3f
	nop
2:
	mfc0	a2, MACH_COP_0_TLB_HI		# Fetch the hi register.
	PRINTF("%d: hi %x low %x\n")		# print entry
	srl	a1, s1, VMMACH_TLB_INDEX_SHIFT	# this is in the delay slot
	lw	a0, DUMP_FRAME_SIZE(sp)		# get 'all'
3:
	bne	s1, s3, 1b
	mtc0	s1, MACH_COP_0_TLB_INDEX	# Set the index register

	mtc0	s0, MACH_COP_0_TLB_HI		# restore PID
	nop
	lw	ra, STAND_RA_OFFSET+16(sp)
	lw	s0, STAND_RA_OFFSET(sp)
	lw	s1, STAND_RA_OFFSET+4(sp)
	lw	s2, STAND_RA_OFFSET+8(sp)
	lw	s3, STAND_RA_OFFSET+12(sp)
	j	ra
	addu	sp, sp, DUMP_FRAME_SIZE
	.set	reorder
END(MachTLBDump)

E 3
	.comm	tlbhi, 4
	.comm	tlblo, 4
LEAF(MachTLBFind)
D 13
	.set	noreorder
E 13
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
D 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Get current PID
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
I 3
	mfc0	t0, MACH_COP_0_TLB_HI		# Get current PID
	nop
E 3
	mtc0	a0, MACH_COP_0_TLB_HI		# Set up entry high.
D 3
	mtc0	a1, MACH_COP_0_TLB_LOW		# Set up entry low.
E 3
	nop
	tlbp					# Probe for the entry.
	mfc0	v0, MACH_COP_0_TLB_INDEX	# See what we got
I 3
	nop
	bltz	v0, 1f				# not found
	nop
	tlbr					# read TLB
E 3
	mfc0	t1, MACH_COP_0_TLB_HI		# See what we got
	mfc0	t2, MACH_COP_0_TLB_LOW		# See what we got
	sw	t1, tlbhi
	sw	t2, tlblo
I 15
	srl	v0, v0, VMMACH_TLB_INDEX_SHIFT	# convert index to regular num
E 15
D 3
	mtc0	t0, MACH_COP_0_TLB_HI		# Get current PID
E 3
I 3
1:
	mtc0	t0, MACH_COP_0_TLB_HI		# Restore current PID
E 3
	j	ra
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
D 13
	.set	reorder
E 13
END(MachTLBFind)

/*--------------------------------------------------------------------------
 *
D 3
 * MachGetPID --
E 3
I 3
 * MachTLBRead --
E 3
 *
D 3
 *	MachGetPID()
E 3
I 3
 *	Read the TLB entry.
E 3
 *
I 3
 *	MachTLBRead(entry)
 *		unsigned entry;
 *
E 3
 * Results:
I 3
 *	None.
 *
 * Side effects:
 *	tlbhi and tlblo will contain the TLB entry found.
 *
 *--------------------------------------------------------------------------
 */
LEAF(MachTLBRead)
D 13
	.set	noreorder
E 13
	mfc0	v1, MACH_COP_0_STATUS_REG	# Save the status register.
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
	mfc0	t0, MACH_COP_0_TLB_HI		# Get current PID

	sll	a0, a0, VMMACH_TLB_INDEX_SHIFT
	mtc0	a0, MACH_COP_0_TLB_INDEX	# Set the index register
	nop
	tlbr					# Read from the TLB
	mfc0	t3, MACH_COP_0_TLB_HI		# fetch the hi entry
	mfc0	t4, MACH_COP_0_TLB_LOW		# fetch the low entry
	sw	t3, tlbhi
	sw	t4, tlblo

	mtc0	t0, MACH_COP_0_TLB_HI		# restore PID
	j	ra
	mtc0	v1, MACH_COP_0_STATUS_REG	# Restore the status register
D 13
	.set	reorder
E 13
END(MachTLBRead)

/*--------------------------------------------------------------------------
 *
 * MachTLBGetPID --
 *
 *	MachTLBGetPID()
 *
 * Results:
E 3
 *	Returns the current TLB pid reg.
 *
 * Side effects:
 *	None.
 *
 *--------------------------------------------------------------------------
 */
D 3
LEAF(MachGetPID)
E 3
I 3
LEAF(MachTLBGetPID)
E 3
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_TLB_HI		# get PID
	nop
	and	v0, v0, VMMACH_TLB_PID		# mask off PID
	j	ra
	srl	v0, v0, VMMACH_TLB_PID_SHIFT	# put PID in right spot
D 13
	.set	reorder
E 13
D 3
END(MachGetPID)
E 3
I 3
END(MachTLBGetPID)

/*
 * Return the current value of the cause register.
 */
LEAF(MachGetCauseReg)
D 13
	.set	noreorder
E 13
	mfc0	v0, MACH_COP_0_CAUSE_REG
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachGetCauseReg)
E 3
#endif /* DEBUG */

/*----------------------------------------------------------------------------
 *
 * MachSwitchFPState --
 *
 *	Save the current state into 'from' and restore it from 'to'.
 *
 *	MachSwitchFPState(from, to)
 *		struct proc *from;
 *		struct user *to;
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
LEAF(MachSwitchFPState)
D 13
	.set	noreorder
E 13
	mfc0	t1, MACH_COP_0_STATUS_REG	# Save old SR
D 4
	li	t0, MACH_SR_COP_1_BIT		# Disable interrupts and
	mtc0	t0, MACH_COP_0_STATUS_REG	#  enable the coprocessor
E 4
I 4
	li	t0, MACH_SR_COP_1_BIT		# enable the coprocessor
D 5
	or	t0, t0, t1
E 5
	mtc0	t0, MACH_COP_0_STATUS_REG
E 4

	beq	a0, zero, 1f			# skip save if NULL pointer
	nop
/*
 * First read out the status register to make sure that all FP operations
 * have completed.
 */
	lw	a0, P_ADDR(a0)			# get pointer to pcb for proc
D 3
	cfc1	t0, MACH_FPC_CSR		# stall til FP done, get status
E 3
I 3
	cfc1	t0, MACH_FPC_CSR		# stall til FP done
	cfc1	t0, MACH_FPC_CSR		# now get status
E 3
	li	t3, ~MACH_SR_COP_1_BIT
	lw	t2, U_PCB_REGS+(PS * 4)(a0)	# get CPU status register
	sw	t0, U_PCB_FPREGS+(32 * 4)(a0)	# save FP status
	and	t2, t2, t3			# clear COP_1 enable bit
	sw	t2, U_PCB_REGS+(PS * 4)(a0)	# save new status register
/*
 * Save the floating point registers.
 */
	swc1	$f0, U_PCB_FPREGS+(0 * 4)(a0)
	swc1	$f1, U_PCB_FPREGS+(1 * 4)(a0)
	swc1	$f2, U_PCB_FPREGS+(2 * 4)(a0)
	swc1	$f3, U_PCB_FPREGS+(3 * 4)(a0)
	swc1	$f4, U_PCB_FPREGS+(4 * 4)(a0)
	swc1	$f5, U_PCB_FPREGS+(5 * 4)(a0)
	swc1	$f6, U_PCB_FPREGS+(6 * 4)(a0)
	swc1	$f7, U_PCB_FPREGS+(7 * 4)(a0)
	swc1	$f8, U_PCB_FPREGS+(8 * 4)(a0)
	swc1	$f9, U_PCB_FPREGS+(9 * 4)(a0)
	swc1	$f10, U_PCB_FPREGS+(10 * 4)(a0)
	swc1	$f11, U_PCB_FPREGS+(11 * 4)(a0)
	swc1	$f12, U_PCB_FPREGS+(12 * 4)(a0)
	swc1	$f13, U_PCB_FPREGS+(13 * 4)(a0)
	swc1	$f14, U_PCB_FPREGS+(14 * 4)(a0)
	swc1	$f15, U_PCB_FPREGS+(15 * 4)(a0)
	swc1	$f16, U_PCB_FPREGS+(16 * 4)(a0)
	swc1	$f17, U_PCB_FPREGS+(17 * 4)(a0)
	swc1	$f18, U_PCB_FPREGS+(18 * 4)(a0)
	swc1	$f19, U_PCB_FPREGS+(19 * 4)(a0)
	swc1	$f20, U_PCB_FPREGS+(20 * 4)(a0)
	swc1	$f21, U_PCB_FPREGS+(21 * 4)(a0)
	swc1	$f22, U_PCB_FPREGS+(22 * 4)(a0)
	swc1	$f23, U_PCB_FPREGS+(23 * 4)(a0)
	swc1	$f24, U_PCB_FPREGS+(24 * 4)(a0)
	swc1	$f25, U_PCB_FPREGS+(25 * 4)(a0)
	swc1	$f26, U_PCB_FPREGS+(26 * 4)(a0)
	swc1	$f27, U_PCB_FPREGS+(27 * 4)(a0)
	swc1	$f28, U_PCB_FPREGS+(28 * 4)(a0)
	swc1	$f29, U_PCB_FPREGS+(29 * 4)(a0)
	swc1	$f30, U_PCB_FPREGS+(30 * 4)(a0)
	swc1	$f31, U_PCB_FPREGS+(31 * 4)(a0)

1:
D 12
/* 
E 12
I 12
/*
E 12
 *  Restore the floating point registers.
 */
	lw	t0, U_PCB_FPREGS+(32 * 4)(a1)	# get status register
	lwc1	$f0, U_PCB_FPREGS+(0 * 4)(a1)
	lwc1	$f1, U_PCB_FPREGS+(1 * 4)(a1)
	lwc1	$f2, U_PCB_FPREGS+(2 * 4)(a1)
	lwc1	$f3, U_PCB_FPREGS+(3 * 4)(a1)
	lwc1	$f4, U_PCB_FPREGS+(4 * 4)(a1)
	lwc1	$f5, U_PCB_FPREGS+(5 * 4)(a1)
	lwc1	$f6, U_PCB_FPREGS+(6 * 4)(a1)
	lwc1	$f7, U_PCB_FPREGS+(7 * 4)(a1)
	lwc1	$f8, U_PCB_FPREGS+(8 * 4)(a1)
	lwc1	$f9, U_PCB_FPREGS+(9 * 4)(a1)
	lwc1	$f10, U_PCB_FPREGS+(10 * 4)(a1)
	lwc1	$f11, U_PCB_FPREGS+(11 * 4)(a1)
	lwc1	$f12, U_PCB_FPREGS+(12 * 4)(a1)
	lwc1	$f13, U_PCB_FPREGS+(13 * 4)(a1)
	lwc1	$f14, U_PCB_FPREGS+(14 * 4)(a1)
	lwc1	$f15, U_PCB_FPREGS+(15 * 4)(a1)
	lwc1	$f16, U_PCB_FPREGS+(16 * 4)(a1)
	lwc1	$f17, U_PCB_FPREGS+(17 * 4)(a1)
	lwc1	$f18, U_PCB_FPREGS+(18 * 4)(a1)
	lwc1	$f19, U_PCB_FPREGS+(19 * 4)(a1)
	lwc1	$f20, U_PCB_FPREGS+(20 * 4)(a1)
	lwc1	$f21, U_PCB_FPREGS+(21 * 4)(a1)
	lwc1	$f22, U_PCB_FPREGS+(22 * 4)(a1)
	lwc1	$f23, U_PCB_FPREGS+(23 * 4)(a1)
	lwc1	$f24, U_PCB_FPREGS+(24 * 4)(a1)
	lwc1	$f25, U_PCB_FPREGS+(25 * 4)(a1)
	lwc1	$f26, U_PCB_FPREGS+(26 * 4)(a1)
	lwc1	$f27, U_PCB_FPREGS+(27 * 4)(a1)
	lwc1	$f28, U_PCB_FPREGS+(28 * 4)(a1)
	lwc1	$f29, U_PCB_FPREGS+(29 * 4)(a1)
	lwc1	$f30, U_PCB_FPREGS+(30 * 4)(a1)
	lwc1	$f31, U_PCB_FPREGS+(31 * 4)(a1)

	and	t0, t0, ~MACH_FPC_EXCEPTION_BITS
	ctc1	t0, MACH_FPC_CSR
	nop

	mtc0	t1, MACH_COP_0_STATUS_REG	# Restore the status register.
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachSwitchFPState)

/*----------------------------------------------------------------------------
 *
 * MachSaveCurFPState --
 *
 *	Save the current floating point coprocessor state.
 *
 *	MachSaveCurFPState(p)
 *		struct proc *p;
 *
 * Results:
 *	None.
 *
 * Side effects:
D 5
 *	None.
E 5
I 5
 *	machFPCurProcPtr is cleared.
E 5
 *
 *----------------------------------------------------------------------------
 */
LEAF(MachSaveCurFPState)
D 13
	.set	noreorder
E 13
	lw	a0, P_ADDR(a0)			# get pointer to pcb for proc
	mfc0	t1, MACH_COP_0_STATUS_REG	# Disable interrupts and
	li	t0, MACH_SR_COP_1_BIT		#  enable the coprocessor
	mtc0	t0, MACH_COP_0_STATUS_REG
D 5
	nop
E 5
I 5
	sw	zero, machFPCurProcPtr		# indicate state has been saved
E 5
/*
 * First read out the status register to make sure that all FP operations
 * have completed.
 */
	lw	t2, U_PCB_REGS+(PS * 4)(a0)	# get CPU status register
	li	t3, ~MACH_SR_COP_1_BIT
	and	t2, t2, t3			# clear COP_1 enable bit
D 3
	cfc1	t0, MACH_FPC_CSR		# stall til FP done, get status
E 3
I 3
	cfc1	t0, MACH_FPC_CSR		# stall til FP done
	cfc1	t0, MACH_FPC_CSR		# now get status
E 3
	sw	t2, U_PCB_REGS+(PS * 4)(a0)	# save new status register
	sw	t0, U_PCB_FPREGS+(32 * 4)(a0)	# save FP status
/*
 * Save the floating point registers.
 */
	swc1	$f0, U_PCB_FPREGS+(0 * 4)(a0)
	swc1	$f1, U_PCB_FPREGS+(1 * 4)(a0)
	swc1	$f2, U_PCB_FPREGS+(2 * 4)(a0)
	swc1	$f3, U_PCB_FPREGS+(3 * 4)(a0)
	swc1	$f4, U_PCB_FPREGS+(4 * 4)(a0)
	swc1	$f5, U_PCB_FPREGS+(5 * 4)(a0)
	swc1	$f6, U_PCB_FPREGS+(6 * 4)(a0)
	swc1	$f7, U_PCB_FPREGS+(7 * 4)(a0)
	swc1	$f8, U_PCB_FPREGS+(8 * 4)(a0)
	swc1	$f9, U_PCB_FPREGS+(9 * 4)(a0)
	swc1	$f10, U_PCB_FPREGS+(10 * 4)(a0)
	swc1	$f11, U_PCB_FPREGS+(11 * 4)(a0)
	swc1	$f12, U_PCB_FPREGS+(12 * 4)(a0)
	swc1	$f13, U_PCB_FPREGS+(13 * 4)(a0)
	swc1	$f14, U_PCB_FPREGS+(14 * 4)(a0)
	swc1	$f15, U_PCB_FPREGS+(15 * 4)(a0)
	swc1	$f16, U_PCB_FPREGS+(16 * 4)(a0)
	swc1	$f17, U_PCB_FPREGS+(17 * 4)(a0)
	swc1	$f18, U_PCB_FPREGS+(18 * 4)(a0)
	swc1	$f19, U_PCB_FPREGS+(19 * 4)(a0)
	swc1	$f20, U_PCB_FPREGS+(20 * 4)(a0)
	swc1	$f21, U_PCB_FPREGS+(21 * 4)(a0)
	swc1	$f22, U_PCB_FPREGS+(22 * 4)(a0)
	swc1	$f23, U_PCB_FPREGS+(23 * 4)(a0)
	swc1	$f24, U_PCB_FPREGS+(24 * 4)(a0)
	swc1	$f25, U_PCB_FPREGS+(25 * 4)(a0)
	swc1	$f26, U_PCB_FPREGS+(26 * 4)(a0)
	swc1	$f27, U_PCB_FPREGS+(27 * 4)(a0)
	swc1	$f28, U_PCB_FPREGS+(28 * 4)(a0)
	swc1	$f29, U_PCB_FPREGS+(29 * 4)(a0)
	swc1	$f30, U_PCB_FPREGS+(30 * 4)(a0)
	swc1	$f31, U_PCB_FPREGS+(31 * 4)(a0)

	mtc0	t1, MACH_COP_0_STATUS_REG	# Restore the status register.
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachSaveCurFPState)

/*----------------------------------------------------------------------------
 *
 * MachFPInterrupt --
 *
 *	Handle a floating point interrupt.
 *
 *	MachFPInterrupt(statusReg, causeReg, pc)
 *		unsigned statusReg;
 *		unsigned causeReg;
 *		unsigned pc;
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
NON_LEAF(MachFPInterrupt, STAND_FRAME_SIZE, ra)
D 13
	.set	noreorder
E 13
	subu	sp, sp, STAND_FRAME_SIZE
	mfc0	t0, MACH_COP_0_STATUS_REG
	sw	ra, STAND_RA_OFFSET(sp)
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)

	or	t1, t0, MACH_SR_COP_1_BIT
	mtc0	t1, MACH_COP_0_STATUS_REG
	nop
	nop
D 3
	cfc1	t1, MACH_FPC_CSR	# stall til FP done, get status
E 3
I 3
	cfc1	t1, MACH_FPC_CSR	# stall til FP done
	cfc1	t1, MACH_FPC_CSR	# now get status
E 3
	nop
D 13
	.set	reorder
E 13
	sll	t2, t1, (31 - 17)	# unimplemented operation?
	bgez	t2, 3f			# no, normal trap
I 13
	nop
E 13
/*
 * We got an unimplemented operation trap so
 * fetch the instruction, compute the next PC and emulate the instruction.
 */
	bgez	a1, 1f			# Check the branch delay bit.
I 13
	nop
E 13
/*
 * The instruction is in the branch delay slot so the branch will have to
 * be emulated to get the resulting PC.
 */
	sw	a2, STAND_FRAME_SIZE + 8(sp)
	li	a0, UADDR+U_PCB_REGS	# first arg is ptr to CPU registers
	move	a1, a2			# second arg is instruction PC
	move	a2, t1			# third arg is floating point CSR
D 13
	move	a3, zero		# fourth arg is FALSE
E 13
	jal	MachEmulateBranch	# compute PC after branch
I 13
	move	a3, zero		# fourth arg is FALSE
E 13
/*
 * Now load the floating-point instruction in the branch delay slot
 * to be emulated.
 */
	lw	a2, STAND_FRAME_SIZE + 8(sp)	# restore EXC pc
D 13
	lw	a0, 4(a2)			# a0 = coproc instruction
E 13
	b	2f
I 13
	lw	a0, 4(a2)			# a0 = coproc instruction
E 13
/*
 * This is not in the branch delay slot so calculate the resulting
 * PC (epc + 4) into v0 and continue to MachEmulateFP().
 */
1:
	lw	a0, 0(a2)			# a0 = coproc instruction
	addu	v0, a2, 4			# v0 = next pc
2:
	sw	v0, UADDR+U_PCB_REGS+(PC * 4)	# save new pc
/*
 * Check to see if the instruction to be emulated is a floating-point
 * instruction.
 */
	srl	a3, a0, MACH_OPCODE_SHIFT
	beq	a3, MACH_OPCODE_C1, 4f		# this should never fail
/*
 * Send a floating point exception signal to the current process.
 */
3:
	lw	a0, curproc			# get current process
	cfc1	a2, MACH_FPC_CSR		# code = FP execptions
D 13
	li	a1, SIGFPE
E 13
	ctc1	zero, MACH_FPC_CSR		# Clear exceptions
	jal	trapsignal
I 13
	li	a1, SIGFPE
E 13
	b	FPReturn
I 13
	nop
E 13

/*
 * Finally, we can call MachEmulateFP() where a0 is the instruction to emulate.
 */
4:
	jal	MachEmulateFP
I 13
	nop
E 13

/*
 * Turn off the floating point coprocessor and return.
 */
FPReturn:
D 13
	.set	noreorder
E 13
	mfc0	t0, MACH_COP_0_STATUS_REG
	lw	ra, STAND_RA_OFFSET(sp)
	and	t0, t0, ~MACH_SR_COP_1_BIT
	mtc0	t0, MACH_COP_0_STATUS_REG
	j	ra
	addu	sp, sp, STAND_FRAME_SIZE
D 13
	.set	reorder
E 13
END(MachFPInterrupt)

/*----------------------------------------------------------------------------
 *
 * MachConfigCache --
 *
 *	Size the caches.
 *	NOTE: should only be called from mach_init().
 *
 * Results:
 *     	None.
 *
 * Side effects:
 *	The size of the data cache is stored into machDataCacheSize and the
 *	size of instruction cache is stored into machInstCacheSize.
 *
 *----------------------------------------------------------------------------
 */
NON_LEAF(MachConfigCache, STAND_FRAME_SIZE, ra)
D 13
	.set	noreorder
E 13
	subu	sp, sp, STAND_FRAME_SIZE
	sw	ra, STAND_RA_OFFSET(sp)		# Save return address.
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts.
	la	v0, 1f
	or	v0, MACH_UNCACHED_MEMORY_ADDR	# Run uncached.
	j	v0
	nop
1:
/*
 * This works because jal doesn't change pc[31..28] and the
 * linker still thinks SizeCache is in the cached region so it computes
 * the correct address without complaining.
 */
	jal	SizeCache			# Get the size of the d-cache.
	nop
	sw	v0, machDataCacheSize
	nop					# Make sure sw out of pipe
	nop
	nop
	nop
	li	v0, MACH_SR_SWAP_CACHES		# Swap caches
	mtc0	v0, MACH_COP_0_STATUS_REG
	nop					# Insure caches stable
	nop
	nop
	nop
	jal	SizeCache			# Get the size of the i-cache.
	nop
D 12
	sw	v0, machInstCacheSize		
	nop					# Make sure sw out of pipe
E 12
I 12
	mtc0	zero, MACH_COP_0_STATUS_REG	# Swap back caches and enable.
E 12
	nop
	nop
	nop
D 12
	mtc0	zero, MACH_COP_0_STATUS_REG	# Swap back caches. 
E 12
	nop
D 12
	nop
	nop
	nop
E 12
I 12
	sw	v0, machInstCacheSize
E 12
	la	t0, 1f
	j	t0				# Back to cached mode
	nop
1:
	lw	ra, STAND_RA_OFFSET(sp)		# Restore return addr
	addu	sp, sp, STAND_FRAME_SIZE	# Restore sp.
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachConfigCache)

/*----------------------------------------------------------------------------
 *
 * SizeCache --
 *
 *	Get the size of the cache.
 *
 * Results:
 *	The size of the cache.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------------
 */
LEAF(SizeCache)
D 13
	.set	noreorder
E 13
	mfc0	t0, MACH_COP_0_STATUS_REG	# Save the current status reg.
D 12
	nop				
E 12
I 12
	nop
E 12
	or	v0, t0, MACH_SR_ISOL_CACHES	# Isolate the caches.
	nop					# Make sure no stores in pipe
	mtc0	v0, MACH_COP_0_STATUS_REG
	nop					# Make sure isolated
	nop
	nop
/*
 * Clear cache size boundaries.
 */
	li	v0, MACH_MIN_CACHE_SIZE
I 12
	li	v1, MACH_CACHED_MEMORY_ADDR
	li	t2, MACH_MAX_CACHE_SIZE
E 12
1:
D 12
	sw	zero, MACH_CACHED_MEMORY_ADDR(v0)	# Clear cache memory
E 12
I 12
	addu	t1, v0, v1			# Compute address to clear
	sw	zero, 0(t1)			# Clear cache memory
	bne	v0, t2, 1b
E 12
	sll	v0, v0, 1
D 12
	bleu	v0, +MACH_MAX_CACHE_SIZE, 1b
	nop
E 12
I 12

E 12
	li	v0, -1
D 12
	sw	v0, MACH_CACHED_MEMORY_ADDR(zero)	# Store marker in cache
E 12
I 12
	sw	v0, 0(v1)			# Store marker in cache
E 12
	li	v0, MACH_MIN_CACHE_SIZE
2:
D 12
	lw	v1, MACH_CACHED_MEMORY_ADDR(v0)		# Look for marker
	nop			
	bne	v1, zero, 3f				# Found marker.
E 12
I 12
	addu	t1, v0, v1			# Compute address
	lw	t3, 0(t1)			# Look for marker
E 12
	nop
D 12
	sll	v0, v0, 1				# cache size * 2
	bleu	v0, +MACH_MAX_CACHE_SIZE, 2b		# keep looking
E 12
I 12
	bne	t3, zero, 3f			# Found marker.
E 12
	nop
D 12
	move	v0, zero				# must be no cache
E 12
I 12
	bne	v0, t2, 2b			# keep looking
	sll	v0, v0, 1			# cache size * 2

	move	v0, zero			# must be no cache
E 12
3:
	mtc0	t0, MACH_COP_0_STATUS_REG
D 12
	nop						# Make sure unisolated
E 12
I 12
	nop					# Make sure unisolated
E 12
	nop
	nop
	nop
	j	ra
	nop
D 13
	.set	reorder
E 13
END(SizeCache)

/*----------------------------------------------------------------------------
 *
 * MachFlushCache --
 *
 *	Flush the caches.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The contents of the caches is flushed.
 *
 *----------------------------------------------------------------------------
 */
LEAF(MachFlushCache)
D 13
	.set	noreorder
E 13
	lw	t1, machInstCacheSize		# Must load before isolating
	lw	t2, machDataCacheSize		# Must load before isolating
	mfc0	t3, MACH_COP_0_STATUS_REG 	# Save the status register.
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts.
	la	v0, 1f
	or	v0, MACH_UNCACHED_MEMORY_ADDR	# Run uncached.
D 12
	j	v0			
E 12
I 12
	j	v0
E 12
	nop
/*
 * Flush the instruction cache.
 */
1:
	li	v0, MACH_SR_ISOL_CACHES | MACH_SR_SWAP_CACHES
	mtc0	v0, MACH_COP_0_STATUS_REG	# Isolate and swap caches.
	li	t0, MACH_UNCACHED_MEMORY_ADDR
	subu	t0, t0, t1
	li	t1, MACH_UNCACHED_MEMORY_ADDR
	la	v0, 1f				# Run cached
	j	v0
	nop
1:
D 3
	sb	zero, 0(t0)
	sb	zero, 4(t0)
	sb	zero, 8(t0)
	sb	zero, 12(t0)
	sb	zero, 16(t0)
	sb	zero, 20(t0)
	sb	zero, 24(t0)
	addu	t0, t0, 32
E 3
I 3
	addu	t0, t0, 4
E 3
	bne	t0, t1, 1b
	sb	zero, -4(t0)

	la	v0, 1f
	or	v0, MACH_UNCACHED_MEMORY_ADDR
	j	v0				# Run uncached
	nop
/*
 * Flush the data cache.
 */
1:
	li	v0, MACH_SR_ISOL_CACHES
	mtc0	v0, MACH_COP_0_STATUS_REG	# Isolate and swap back caches
	li	t0, MACH_UNCACHED_MEMORY_ADDR
	subu	t0, t0, t2
	la	v0, 1f
	j	v0				# Back to cached mode
	nop
1:
D 3
	sb	zero, 0(t0)
	sb	zero, 4(t0)
	sb	zero, 8(t0)
	sb	zero, 12(t0)
	sb	zero, 16(t0)
	sb	zero, 20(t0)
	sb	zero, 24(t0)
	addu	t0, t0, 32
E 3
I 3
	addu	t0, t0, 4
E 3
	bne	t0, t1, 1b
	sb	zero, -4(t0)

D 12
	nop					# Insure isolated stores 
E 12
I 12
	nop					# Insure isolated stores
E 12
	nop					#   out of pipe.
	nop
	nop
	mtc0	t3, MACH_COP_0_STATUS_REG	# Restore status reg.
	nop					# Insure cache unisolated.
	nop
	nop
	nop
	j	ra
	nop
D 13
	.set	reorder
E 13
END(MachFlushCache)

/*----------------------------------------------------------------------------
 *
 * MachFlushICache --
 *
D 3
 *	MachFlushICache(addr, len)
E 3
I 3
 *	void MachFlushICache(addr, len)
 *		vm_offset_t addr, len;
E 3
 *
 *	Flush instruction cache for range of addr to addr + len - 1.
I 3
 *	The address can be any valid address so long as no TLB misses occur.
E 3
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The contents of the cache is flushed.
 *
 *----------------------------------------------------------------------------
 */
LEAF(MachFlushICache)
D 13
	.set	noreorder
E 13
D 3
	lw	t1, machInstCacheSize
	mfc0	t3, MACH_COP_0_STATUS_REG	# Save SR
	subu	t0, t1, 1			# t0 = size - 1
	and	a0, a0, t0			# mask off address bits
	addu	t0, t0, MACH_UNCACHED_MEMORY_ADDR
	subu	t0, t0, t1
E 3
I 3
	mfc0	t0, MACH_COP_0_STATUS_REG	# Save SR
E 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts.

D 3
	la	v0, 1f
	or	v0, MACH_UNCACHED_MEMORY_ADDR	# Run uncached.
	j	v0
E 3
I 3
	la	v1, 1f
	or	v1, MACH_UNCACHED_MEMORY_ADDR	# Run uncached.
	j	v1
E 3
	nop
1:
D 3
	li	v0, MACH_SR_ISOL_CACHES | MACH_SR_SWAP_CACHES
	mtc0	v0, MACH_COP_0_STATUS_REG
	bltu	t1, a1, 1f			# cache is smaller than region
E 3
I 3
	bc0f	1b				# make sure stores are complete
	li	v1, MACH_SR_ISOL_CACHES | MACH_SR_SWAP_CACHES
	mtc0	v1, MACH_COP_0_STATUS_REG
E 3
	nop
D 3
	move	t1, a1
E 3
I 3
	addu	a1, a1, a0			# compute ending address
E 3
1:
D 3
	addu	t1, t1, t0			# compute ending address
	la	v0, 1f				# run cached
	j	v0
	nop
1:
	sb	zero, 0(t0)
	sb	zero, 4(t0)
	sb	zero, 8(t0)
	sb	zero, 12(t0)
	sb	zero, 16(t0)
	sb	zero, 20(t0)
	sb	zero, 24(t0)
	addu	t0, t0, 32
	bltu	t0, t1, 1b
	sb	zero, -4(t0)
E 3
I 3
	addu	a0, a0, 4
	bne	a0, a1, 1b
	sb	zero, -4(a0)
E 3

D 3
	la	v0, 1f
	or	v0, MACH_UNCACHED_MEMORY_ADDR
	j	v0				# Run uncached
	nop
1:
	nop				# insure isolated stores out of pipe
	mtc0	zero, MACH_COP_0_STATUS_REG	# unisolate, unswap
	nop					# keep pipeline clean
	nop
	nop
	mtc0	t3, MACH_COP_0_STATUS_REG	# enable interrupts
E 3
I 3
	mtc0	t0, MACH_COP_0_STATUS_REG	# enable interrupts
E 3
	j	ra				# return and run cached
	nop
D 13
	.set	reorder
E 13
END(MachFlushICache)
I 3

I 11
/*----------------------------------------------------------------------------
 *
 * MachFlushDCache --
 *
 *	void MachFlushDCache(addr, len)
 *		vm_offset_t addr, len;
 *
 *	Flush data cache for range of addr to addr + len - 1.
 *	The address can be any valid address so long as no TLB misses occur.
 *	(Be sure to use cached K0SEG kernel addresses)
 * Results:
 *	None.
 *
 * Side effects:
 *	The contents of the cache is flushed.
 *
 *----------------------------------------------------------------------------
 */
LEAF(MachFlushDCache)
D 13
	.set	noreorder
E 13
	mfc0	t0, MACH_COP_0_STATUS_REG	# Save SR
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts.

	la	v1, 1f
	or	v1, MACH_UNCACHED_MEMORY_ADDR	# Run uncached.
	j	v1
	nop
1:
	bc0f	1b				# make sure stores are complete
	li	v1, MACH_SR_ISOL_CACHES
	mtc0	v1, MACH_COP_0_STATUS_REG
	nop
	addu	a1, a1, a0			# compute ending address
1:
	addu	a0, a0, 4
	bne	a0, a1, 1b
	sb	zero, -4(a0)

	mtc0	t0, MACH_COP_0_STATUS_REG	# enable interrupts
	j	ra				# return and run cached
	nop
D 13
	.set	reorder
E 13
END(MachFlushDCache)

E 11
#ifdef KADB
/*
 * Read a long and return it.
 * Note: addresses can be unaligned!
 *
 * long
L* kdbpeek(addr)
L*	caddt_t addr;
L* {
L*	return (*(long *)addr);
L* }
 */
LEAF(kdbpeek)
	li	v0, KADBERR
	sw	v0, UADDR+U_PCB_ONFAULT
	and	v0, a0, 3		# unaligned address?
	bne	v0, zero, 1f
D 13
	lw	v0, (a0)		# aligned access
E 13
I 13
	nop
E 13
	b	2f
I 13
	lw	v0, (a0)		# aligned access
E 13
1:
	lwr	v0, 0(a0)		# get next 4 bytes (unaligned)
	lwl	v0, 3(a0)
2:
D 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
	j	ra			# made it w/o errors
I 13
	sw	zero, UADDR+U_PCB_ONFAULT
E 13
kadberr:
	li	v0, 1			# trap sends us here
	sw	v0, kdbmkfault
	j	ra
I 13
	nop
E 13
END(kdbpeek)

/*
 * Write a long to 'addr'.
 * Note: addresses can be unaligned!
 *
L* void
L* kdbpoke(addr, value)
L*	caddt_t addr;
L*	long value;
L* {
L*	*(long *)addr = value;
L* }
 */
LEAF(kdbpoke)
	li	v0, KADBERR
	sw	v0, UADDR+U_PCB_ONFAULT
	and	v0, a0, 3		# unaligned address?
	bne	v0, zero, 1f
D 13
	sw	a1, (a0)		# aligned access
E 13
I 13
	nop
E 13
	b	2f
I 13
	sw	a1, (a0)		# aligned access
E 13
1:
	swr	a1, 0(a0)		# store next 4 bytes (unaligned)
	swl	a1, 3(a0)
	and	a0, a0, ~3		# align address for cache flush
2:
	sw	zero, UADDR+U_PCB_ONFAULT
D 13
	li	a1, 8
E 13
	b	MachFlushICache		# flush instruction cache
I 13
	li	a1, 8
E 13
END(kdbpoke)

/*
 * Save registers and state so we can do a 'kdbreset' (like longjmp) later.
 * Always returns zero.
 *
L* int kdb_savearea[11];
L*
L* int
L* kdbsetexit()
L* {
L*	kdb_savearea[0] = 0;
L*	return (0);
L* }
 */
	.comm	kdb_savearea, (11 * 4)

LEAF(kdbsetexit)
D 13
	.set	noreorder
E 13
	la	a0, kdb_savearea
	sw	s0, 0(a0)
	sw	s1, 4(a0)
	sw	s2, 8(a0)
	sw	s3, 12(a0)
	sw	s4, 16(a0)
	sw	s5, 20(a0)
	sw	s6, 24(a0)
	sw	s7, 28(a0)
	sw	sp, 32(a0)
	sw	s8, 36(a0)
	sw	ra, 40(a0)
	j	ra
	move	v0, zero
D 13
	.set	reorder
E 13
END(kdbsetexit)

/*
 * Restore registers and state (like longjmp) and return x.
 *
L* int
L* kdbreset(x)
L* {
L*	return (x);
L* }
 */
LEAF(kdbreset)
D 13
	.set	noreorder
E 13
	la	v0, kdb_savearea
	lw	ra, 40(v0)
	lw	s0, 0(v0)
	lw	s1, 4(v0)
	lw	s2, 8(v0)
	lw	s3, 12(v0)
	lw	s4, 16(v0)
	lw	s5, 20(v0)
	lw	s6, 24(v0)
	lw	s7, 28(v0)
	lw	sp, 32(v0)
	lw	s8, 36(v0)
	j	ra
	move	v0, a0
D 13
	.set	reorder
E 13
END(kdbreset)

/*
 * Trap into the debugger.
 *
L* void
L* kdbpanic()
L* {
L* }
 */
LEAF(kdbpanic)
	break	MACH_BREAK_KDB_VAL
	j	ra
I 13
	nop
E 13
END(kdbpanic)
#endif /* KADB */
I 13

#ifdef DEBUG
D 15
LEAF(cpu_getregs)	/* XXX */
E 15
I 15
LEAF(cpu_getregs)
E 15
	sw	sp, 0(a0)
D 15
	la	v0, cpu_getregs
	sw	v0, 4(a0)
	sw	ra, 8(a0)
	sw	a0, 12(a0)
	sw	a1, 16(a0)
	sw	a2, 20(a0)
	sw	a3, 24(a0)
E 15
I 15
	sw	ra, 4(a0)
E 15
	j	ra
D 15
	sw	s8, 28(a0)
E 15
I 15
	sw	s8, 8(a0)
E 15
END(cpu_getregs)
#endif /* DEBUG */
I 14

/*
D 15
 * Interrupt counters.
E 15
I 15
 * Interrupt counters for vmstat.
 * XXX These aren't used yet.
E 15
 */
	.data
	.globl	intrcnt, eintrcnt, intrnames, eintrnames
intrnames:
D 15
	.asciz	"spur"
	.asciz	"hil"
	.asciz	"lev2"
	.asciz	"lev3"
	.asciz	"lev4"
	.asciz	"lev5"
	.asciz	"dma"
	.asciz	"clock"
	.asciz  "statclock"
	.asciz	"nmi"
E 15
I 15
D 23
	.asciiz	"spur"
	.asciiz	"hil"
	.asciiz	"lev2"
	.asciiz	"lev3"
	.asciiz	"lev4"
	.asciiz	"lev5"
	.asciiz	"dma"
E 23
I 23
	.asciiz	"softclock"
	.asciiz	"softnet"
	.asciiz	"dc"
	.asciiz	"ether"
	.asciiz	"disk"
	.asciiz	"memory"
E 23
	.asciiz	"clock"
D 23
	.asciiz	"statclock"
	.asciiz	"nmi"
E 23
I 23
	.asciiz	"fp"
E 23
E 15
eintrnames:
	.align	2
intrcnt:
D 23
	.word	0,0,0,0,0,0,0,0,0,0
E 23
I 23
	.word	0,0,0,0,0,0,0,0
E 23
eintrcnt:
I 23
	.word	0	# This shouldn't be needed but the eintrcnt label
			# ends up in a different section otherwise.
E 23
E 14
E 13
E 3
E 1
