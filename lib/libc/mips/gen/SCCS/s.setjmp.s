h58051
s 00002/00002/00090
d D 8.1 93/06/04 12:46:48 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00091
d D 5.6 92/07/26 21:36:54 ralph 6 5
c removed DEFS.h
e
s 00001/00001/00091
d D 5.5 92/05/28 18:23:14 mckusick 5 4
c struct for sigaltstack is one longword bigger
e
s 00004/00003/00088
d D 5.4 92/05/28 17:22:17 mckusick 4 3
c convert from sigstack to sigaltstack
e
s 00001/00000/00090
d D 5.3 92/03/07 09:25:53 ralph 3 2
c fix include files
e
s 00003/00003/00087
d D 5.2 92/02/29 12:58:57 bostic 2 1
c need DEFS.h for ASMSTR macro
e
s 00090/00000/00000
d D 5.1 92/02/29 12:41:00 bostic 1 0
c date and time created 92/02/29 12:41:00 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

I 2
#include <sys/syscall.h>
I 3
#include <machine/reg.h>
E 3
D 6
#include "DEFS.h"
E 6
I 6
#include <machine/machAsmDefs.h>
E 6

E 2
#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */
D 2

#include <sys/syscall.h>
#include "DEFS.h"
E 2

/*
 * C library -- setjmp, longjmp
 *
 *	longjmp(a,v)
 * will generate a "return(v)" from
 * the last call to
 *	setjmp(a)
 * by restoring registers from the stack,
 * and a struct sigcontext, see <signal.h>
 */

D 5
#define SETJMP_FRAME_SIZE	(STAND_FRAME_SIZE + 8)
E 5
I 5
#define SETJMP_FRAME_SIZE	(STAND_FRAME_SIZE + 12)
E 5

NON_LEAF(setjmp, SETJMP_FRAME_SIZE, ra)
	subu	sp, sp, SETJMP_FRAME_SIZE	# allocate stack frame
	.mask	0x80000000, (STAND_RA_OFFSET - STAND_FRAME_SIZE)
	sw	ra, STAND_RA_OFFSET(sp)		# save state
	sw	a0, SETJMP_FRAME_SIZE(sp)
	move	a0, zero			# get current signal mask
	jal	sigblock
	lw	v1, SETJMP_FRAME_SIZE(sp)	# v1 = jmpbuf
	sw	v0, (1 * 4)(v1)			# save sc_mask = sigblock(0)
	move	a0, zero
D 4
	addu	a1, sp, STAND_FRAME_SIZE	# pointer to struct sigstack
	jal	sigstack
E 4
I 4
	addu	a1, sp, STAND_FRAME_SIZE	# pointer to struct sigaltstack
	jal	sigaltstack
E 4
	lw	a0, SETJMP_FRAME_SIZE(sp)	# restore jmpbuf
D 4
	lw	v1, STAND_FRAME_SIZE+4(sp)	# get old ss_onstack
E 4
I 4
	lw	v1, STAND_FRAME_SIZE+8(sp)	# get old ss_onstack
	and	v1, v1, 1			# extract onstack flag
E 4
	sw	v1, 0(a0)			# save it in sc_onstack
	lw	ra, STAND_RA_OFFSET(sp)
	addu	sp, sp, SETJMP_FRAME_SIZE
	blt	v0, zero, botch			# check for sigstack() error
	sw	ra, (2 * 4)(a0)			# sc_pc = return address
	li	v0, 0xACEDBADE			# sigcontext magic number
	sw	v0, ((ZERO + 3) * 4)(a0)	#   saved in sc_regs[0]
	sw	s0, ((S0 + 3) * 4)(a0)
	sw	s1, ((S1 + 3) * 4)(a0)
	sw	s2, ((S2 + 3) * 4)(a0)
	sw	s3, ((S3 + 3) * 4)(a0)
	sw	s4, ((S4 + 3) * 4)(a0)
	sw	s5, ((S5 + 3) * 4)(a0)
	sw	s6, ((S6 + 3) * 4)(a0)
	sw	s7, ((S7 + 3) * 4)(a0)
	sw	gp, ((GP + 3) * 4)(a0)
	sw	sp, ((SP + 3) * 4)(a0)
	sw	s8, ((S8 + 3) * 4)(a0)
	li	v0, 1				# be nice if we could tell
	sw	v0, (37 * 4)(a0)		# sc_fpused = 1
	cfc1	v0, $31
	swc1	$f20, ((20 + 38) * 4)(a0)
	swc1	$f21, ((21 + 38) * 4)(a0)
	swc1	$f22, ((22 + 38) * 4)(a0)
	swc1	$f23, ((23 + 38) * 4)(a0)
	swc1	$f24, ((24 + 38) * 4)(a0)
	swc1	$f25, ((25 + 38) * 4)(a0)
	swc1	$f26, ((26 + 38) * 4)(a0)
	swc1	$f27, ((27 + 38) * 4)(a0)
	swc1	$f28, ((28 + 38) * 4)(a0)
	swc1	$f29, ((29 + 38) * 4)(a0)
	swc1	$f30, ((30 + 38) * 4)(a0)
	swc1	$f31, ((31 + 38) * 4)(a0)
	sw	v0, ((32 + 38) * 4)(a0)
	move	v0, zero
	j	ra
END(setjmp)

LEAF(longjmp)
	sw	a1, ((V0 + 3) * 4)(a0)	# save return value in sc_regs[V0]
	li	v0, SYS_sigreturn
	syscall
botch:
	jal	longjmperror
	jal	abort
END(longjmp)
E 1
