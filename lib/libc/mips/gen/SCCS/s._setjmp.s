h40500
s 00002/00002/00096
d D 8.1 93/06/04 12:46:24 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00097
d D 5.7 93/03/23 18:35:34 ralph 7 6
c fix bug in using v0 before the value is ready (load delay slot).
e
s 00007/00003/00091
d D 5.6 93/02/26 19:06:42 ralph 6 5
c use .set noreorder for better gas code.
e
s 00001/00001/00093
d D 5.5 93/02/04 18:51:56 ralph 5 4
c cpp can't handle ' in comments like ultrix assembler
e
s 00001/00001/00093
d D 5.4 92/07/26 21:36:52 ralph 4 3
c removed DEFS.h
e
s 00001/00000/00093
d D 5.3 92/03/07 09:24:45 ralph 3 2
c fix include files
e
s 00002/00003/00091
d D 5.2 92/02/29 12:58:54 bostic 2 1
c need DEFS.h for ASMSTR macro
e
s 00094/00000/00000
d D 5.1 92/02/29 12:40:57 bostic 1 0
c date and time created 92/02/29 12:40:57 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

I 3
#include <machine/reg.h>
E 3
I 2
D 4
#include "DEFS.h"
E 4
I 4
#include <machine/machAsmDefs.h>
E 4

E 2
#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */
D 2

#include <machine/reg.h>
#include "DEFS.h"
E 2

/*
 * C library -- _setjmp, _longjmp
 *
 *	_longjmp(a,v)
 * will generate a "return(v)" from
 * the last call to
 *	_setjmp(a)
 * by restoring registers from the stack,
 * The previous signal state is NOT restored.
 */

I 6
	.set	noreorder

E 6
LEAF(_setjmp)
	li	v0, 0xACEDBADE			# sigcontext magic number
	sw	ra, (2 * 4)(a0)			# sc_pc = return address
	sw	v0, (3 * 4)(a0)			#   saved in sc_regs[0]
	sw	s0, ((S0 + 3) * 4)(a0)
	sw	s1, ((S1 + 3) * 4)(a0)
	sw	s2, ((S2 + 3) * 4)(a0)
	sw	s3, ((S3 + 3) * 4)(a0)
	sw	s4, ((S4 + 3) * 4)(a0)
	sw	s5, ((S5 + 3) * 4)(a0)
	sw	s6, ((S6 + 3) * 4)(a0)
	sw	s7, ((S7 + 3) * 4)(a0)
	sw	sp, ((SP + 3) * 4)(a0)
	sw	s8, ((S8 + 3) * 4)(a0)
D 5
	cfc1	v0, $31				# too bad can't check if FP used
E 5
I 5
	cfc1	v0, $31				# too bad cant check if FP used
E 5
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
D 6
	move	v0, zero
E 6
	j	ra
I 6
	move	v0, zero
E 6
END(_setjmp)

LEAF(_longjmp)
	lw	v0, (3 * 4)(a0)			# get magic number
D 6
	bne	v0, 0xACEDBADE, botch		# jump if error
E 6
	lw	ra, (2 * 4)(a0)
I 6
	bne	v0, 0xACEDBADE, botch		# jump if error
E 6
	lw	s0, ((S0 + 3) * 4)(a0)
	lw	s1, ((S1 + 3) * 4)(a0)
	lw	s2, ((S2 + 3) * 4)(a0)
	lw	s3, ((S3 + 3) * 4)(a0)
	lw	s4, ((S4 + 3) * 4)(a0)
	lw	s5, ((S5 + 3) * 4)(a0)
	lw	s6, ((S6 + 3) * 4)(a0)
	lw	s7, ((S7 + 3) * 4)(a0)
I 7
	lw	v0, ((32 + 38) * 4)(a0)		# get fpu status
E 7
	lw	sp, ((SP + 3) * 4)(a0)
	lw	s8, ((S8 + 3) * 4)(a0)
D 7
	lw	v0, ((32 + 38) * 4)(a0)		# get fpu status
E 7
	ctc1	v0, $31
	lwc1	$f20, ((20 + 38) * 4)(a0)
	lwc1	$f21, ((21 + 38) * 4)(a0)
	lwc1	$f22, ((22 + 38) * 4)(a0)
	lwc1	$f23, ((23 + 38) * 4)(a0)
	lwc1	$f24, ((24 + 38) * 4)(a0)
	lwc1	$f25, ((25 + 38) * 4)(a0)
	lwc1	$f26, ((26 + 38) * 4)(a0)
	lwc1	$f27, ((27 + 38) * 4)(a0)
	lwc1	$f28, ((28 + 38) * 4)(a0)
	lwc1	$f29, ((29 + 38) * 4)(a0)
	lwc1	$f30, ((30 + 38) * 4)(a0)
	lwc1	$f31, ((31 + 38) * 4)(a0)
D 6
	move	v0, a1
E 6
	j	ra
I 6
	move	v0, a1
E 6
botch:
	jal	longjmperror
I 6
	nop
E 6
	jal	abort
I 6
	nop
E 6
END(_longjmp)
E 1
