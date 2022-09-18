h08077
s 00000/00004/00084
d D 8.2 94/03/21 12:31:28 bostic 9 8
c removed __main(). This will require libgcc.a to be installed
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00002/00002/00086
d D 8.1 93/06/01 23:57:44 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00084
d D 5.7 93/02/26 19:04:42 ralph 7 6
c fix profiling.
e
s 00004/00001/00084
d D 5.6 93/02/21 13:36:44 ralph 6 5
c fix mcount routine.
e
s 00048/00007/00037
d D 5.5 93/02/20 19:00:23 ralph 5 4
c added __progname support
e
s 00004/00003/00040
d D 5.4 93/02/04 18:45:00 ralph 4 3
c changes for a.out format with gcc
e
s 00002/00002/00041
d D 5.3 92/07/27 21:08:44 ralph 3 2
c removed DEFS.h
e
s 00011/00012/00032
d D 5.2 92/03/15 19:22:58 ralph 2 1
c use C style comments not # in column one
e
s 00044/00000/00000
d D 5.1 92/03/09 14:07:52 bostic 1 0
c date and time created 92/03/09 14:07:52 by bostic
e
u
U
t
T
I 1
D 2
#!/bin/sh -
#
# Copyright (c) 1991 The Regents of the University of California.
# All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# Ralph Campbell.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#
E 2
I 2
/*
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
D 3
 * %sccs.include.redist.sh%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */
E 2

#include <machine/regdef.h>
D 3
#include "../libc/mips/DEFS.h"
E 3
I 3
#include <machine/machAsmDefs.h>
E 3

	.comm	environ, 4
I 5
	.data
	.align	2
	.globl	__progname
__progname:
	.word	$L1
$L1:
	.word	0		# null string plus padding
	.text
E 5

D 7
NON_LEAF(__start, 24, ra)
E 7
I 7
NON_LEAF(start, 24, ra)
E 7
D 4
	li	v0, 45		# illegal ULTRIX system call to switch to BSD
	syscall			#   system call numbers.
E 4
D 5
	lw	a0, 0(sp)	# get argc from stack
D 4
	la	gp, _gp		# init gp pointer
E 4
	addu	a1, sp, 4	# get pointer to argv
	addu	a2, a1, 4	# skip null pointer on stack
	sll	v0, a0, 2	# add number of argv pointers
	addu	a2, a2, v0	# final pointer to environment list
	sw	a2, environ	# save environment pointer
E 5
I 5
	.set	noreorder
	lw	s0, 0(sp)	# get argc from stack
	addu	s1, sp, 4	# get pointer to argv
	addu	s2, s1, 4	# skip null pointer on stack
	sll	v0, s0, 2	# add number of argv pointers
	addu	s2, s2, v0	# final pointer to environment list
	sw	s2, environ	# save environment pointer
E 5
	subu	sp, sp, 24	# allocate standard frame
	.mask	0x80000000, -4
	sw	zero, 20(sp)	# clear return address for debugging
I 5
#ifdef MCRT0
eprol:
	la	a0, eprol
	la	a1, etext
	jal	monstartup	# monstartup(eprol, etext);
	nop
D 7
	la	a0, mcleanup
	jal	atexit		# atext(mcleanup);
E 7
I 7
	la	a0, _mcleanup
	jal	atexit		# atext(_mcleanup);
E 7
	nop
	sw	zero, errno
#endif
	lw	a0, 0(s1)	# a0 = argv[0];
	nop
	beq	a0, zero, 2f	# skip if a0 == NULL
	move	s3, a0		# save argv[0]
	jal	strrchr
	li	a1, 0x2f	# a1 = '/'
	bne	v0, zero, 1f	# if slash found
	addu	v0, v0, 1
	move	v0, s3		# v0 = argv[0];
1:
	sw	v0, __progname
2:
	move	a0, s0
	move	a1, s1
E 5
	jal	main		# v0 = main(argc, argv, env);
D 5
	move	a0, v0
E 5
I 5
	move	a2, s2
E 5
	jal	exit		# exit(v0);
I 5
	move	a0, v0
E 5
	break	0
I 5
	.set	reorder
E 5
D 7
END(__start)
E 7
I 7
END(start)
E 7
I 4

D 9
LEAF(__main)
	j	ra
END(__main)
E 4

E 9
I 5
#ifndef MCRT0
E 5
LEAF(moncontrol)
	j	ra
END(moncontrol)

LEAF(_mcount)
I 5
	.set	noreorder
E 5
D 6
	j	ra
E 6
I 6
	.set	noat
E 6
I 5
	addu	sp, sp, 8	# undo push
I 6
	j	ra
	move	ra, AT
	.set	at
E 6
	.set	reorder
E 5
END(_mcount)
I 5
#endif
E 5
E 1
