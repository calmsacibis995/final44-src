h57845
s 00001/00001/00100
d D 8.2 94/01/21 20:05:11 bostic 9 8
c copyright typo
e
s 00005/00003/00096
d D 8.1 93/06/10 23:32:25 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00005/00096
d D 7.7 93/04/05 21:45:17 ralph 7 6
c make boot work for either 3100 or 5000 and still fit in 15 sectors.
e
s 00007/00006/00094
d D 7.6 93/03/13 15:45:48 ralph 6 5
c don't clear callv with bzero!
e
s 00051/00015/00049
d D 7.5 93/02/15 11:22:41 ralph 5 4
c use old DS3100 style entry point for SCSI disk I/O
e
s 00002/00002/00062
d D 7.4 92/10/11 11:28:19 bostic 4 3
c make kernel includes standard
e
s 00025/00019/00039
d D 7.3 92/09/13 11:54:42 ralph 3 2
c added dummy __main for gcc2
e
s 00001/00001/00057
d D 7.2 92/06/06 07:03:57 ralph 2 1
c fix path for include file.
e
s 00058/00000/00000
d D 7.1 92/01/07 20:45:21 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
D 9
 *	Regents of the University of California.  All rights reserved.
E 9
I 9
 *	The Regents of the University of California.  All rights reserved.
E 9
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 8
 *
E 8
I 8
 */

/*
E 8
 * start.s -
 *
 *     Contains code that is the first executed at boot time.
 *
 *	Copyright (C) 1989 Digital Equipment Corporation.
 *	Permission to use, copy, modify, and distribute this software and
 *	its documentation for any purpose and without fee is hereby granted,
 *	provided that the above copyright notice appears in all copies.  
 *	Digital Equipment Corporation makes no representations about the
 *	suitability of this software for any purpose.  It is provided "as is"
 *	without express or implied warranty.
 *
 * from: $Header: /sprite/src/boot/decprom/ds3100.md/RCS/start.s,
 *	v 1.1 90/02/16 16:19:39 shirriff Exp $ SPRITE (DECWRL)
 */

D 2
#include <regdef.h>
E 2
I 2
D 4
#include "../include/regdef.h"
E 2
#include "../include/machConst.h"
E 4
I 4
#include <machine/regdef.h>
#include <machine/machConst.h>
I 5
#include <machine/machAsmDefs.h>
#include <pmax/stand/dec_prom.h>
E 5
E 4

/*
 * Amount to take off of the stack for the benefit of the debugger.
 */
#define START_FRAME	((4 * 4) + 4 + 4)
D 5
#define Init	0xbfc00018
E 5

D 3
    .globl	start
E 3
I 3
	.globl	start
E 3
start:
D 3
    .set noreorder
    mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
    li		sp, MACH_CODE_START - START_FRAME
    la		gp, _gp
    sw		zero, START_FRAME - 4(sp)	# Zero out old ra for debugger
    sw		zero, START_FRAME - 8(sp)	# Zero out old fp for debugger
    jal		main				# main(argc, argv, envp)
    nop
    li		a0, Init			# done, so call prom
    j		a0
E 3
I 3
	.set	noreorder
D 5
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
	li	sp, MACH_CODE_START - START_FRAME
	la	gp, _gp
E 5
I 5
D 6
	li	v0, MACH_SR_BOOT_EXC_VEC
	mtc0	v0, MACH_COP_0_STATUS_REG	# Disable interrupts
E 6
	la	sp, start - START_FRAME
E 5
	sw	zero, START_FRAME - 4(sp)	# Zero out old ra for debugger
	sw	zero, START_FRAME - 8(sp)	# Zero out old fp for debugger
D 5
	jal	main				# main(argc, argv, envp)
E 5
I 5
D 6
#ifdef DS3100
	la	a3, callvec			# init call vector
#endif
	sw	a3, callv			# save call vector
E 6
	move	s0, a0				# save argc
	move	s1, a1				# save argv
I 6
D 7
#ifdef DS5000
E 7
I 7
	beq	a3, 0x30464354, 1f		# jump if boot from DS5000
E 7
	move	s3, a3				# save call vector
D 7
#endif
E 7
I 7
	la	s3, callvec			# init call vector
1:
E 7
E 6
	la	a0, edata			# clear BSS
	la	a1, end
	jal	bzero				# bzero(edata, end - edata)
	subu	a1, a1, a0
I 6
D 7
#ifdef DS3100
	la	s3, callvec			# init call vector
#endif
E 7
	sw	s3, callv			# save call vector
E 6
	move	a0, s0				# restore argc
	jal	main				# main(argc, argv)
	move	a1, s1				# restore argv
	li	v0, DEC_PROM_RESTART		# done, so call prom
	j	v0
E 5
	nop
D 5
	li	a0, Init			# done, so call prom
	j	a0
E 5
E 3

D 3
    .globl	Boot_Transfer
E 3
I 3
/* dummy routine for gcc2 */
	.globl	__main
__main:
	j	ra
	nop

D 5
	.globl	Boot_Transfer
E 3
Boot_Transfer:
D 3
    mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
    li		sp, MACH_CODE_START - START_FRAME
    la		gp, _gp
    sw		zero, START_FRAME - 4(sp)	# Zero out old ra for debugger
    sw		zero, START_FRAME - 8(sp)	# Zero out old fp for debugger
    jal		a3				# Jump to routine
    nop
E 3
I 3
	mtc0	zero, MACH_COP_0_STATUS_REG	# Disable interrupts
	li	sp, MACH_CODE_START - START_FRAME
	la	gp, _gp
	sw	zero, START_FRAME - 4(sp)	# Zero out old ra for debugger
	sw	zero, START_FRAME - 8(sp)	# Zero out old fp for debugger
	jal	a3				# Jump to routine
E 5
I 5
LEAF(prom_restart)
	li	v0, DEC_PROM_RESTART
	j	v0
E 5
	nop
I 5
END(prom_restart)

LEAF(prom_open)
	li	v0, DEC_PROM_OPEN
	j	v0
	nop
END(prom_open)

LEAF(prom_lseek)
	li	v0, DEC_PROM_LSEEK
	j	v0
	nop
END(prom_lseek)

LEAF(prom_read)
	li	v0, DEC_PROM_READ
	j	v0
	nop
END(prom_read)

LEAF(printf)
	lw	v0, callv	# get pointer to call back vectors
	sw	a1, 4(sp)	# store args on stack for printf
	lw	v0, 48(v0)	# offset for callv->printf
	sw	a2, 8(sp)
	j	v0		# call PROM printf
	sw	a3, 12(sp)
END(printf)
E 5
E 3
E 1
