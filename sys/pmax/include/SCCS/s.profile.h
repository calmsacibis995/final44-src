h38898
s 00002/00002/00049
d D 8.1 93/06/10 23:02:39 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00049
d D 7.5 93/05/09 16:05:25 ralph 5 4
c use non-profiled entry point for splhigh() and splx()
e
s 00002/00002/00049
d D 7.4 93/04/13 20:04:12 ralph 4 3
c fix kernel profiling
e
s 00025/00015/00026
d D 7.3 93/02/26 19:11:45 ralph 3 2
c fix profiling
e
s 00016/00002/00025
d D 7.2 93/02/21 13:57:34 ralph 2 1
c define MCOUNT properly. Still need to define kernel entry & exit.
e
s 00027/00000/00000
d D 7.1 92/07/27 09:25:26 bostic 1 0
c date and time created 92/07/27 09:25:26 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	_MCOUNT_DECL static inline void _mcount
E 2
I 2
D 3
#define	_MCOUNT_DECL static void _mcount
E 3
I 3
#define	_MCOUNT_DECL static void __mcount
E 3
E 2

D 2
#define	MCOUNT
E 2
I 2
#define	MCOUNT \
D 3
	asm(".globl mcount"); \
	asm("mcount:"); \
	asm(".set noreorder"); \
	asm(".set noat"); \
	asm("sw $31,4($29);"); \
	asm("jal _mcount"); \
	asm("sw $1,0($29);"); \
	asm("lw $31,4($29)"); \
	asm("lw $1,0($29)"); \
	asm("addu $29,$29,8"); \
	asm("j $31"); \
	asm("move $31,$1"); \
	asm(".set reorder"); \
	asm(".set at");
E 3
I 3
	asm(".globl _mcount;" \
	"_mcount:;" \
	".set noreorder;" \
	".set noat;" \
	"sw $4,8($29);" \
	"sw $5,12($29);" \
	"sw $6,16($29);" \
	"sw $7,20($29);" \
	"sw $1,0($29);" \
	"sw $31,4($29);" \
	"move $5,$31;" \
	"jal __mcount;" \
	"move $4,$1;" \
	"lw $4,8($29);" \
	"lw $5,12($29);" \
	"lw $6,16($29);" \
	"lw $7,20($29);" \
	"lw $31,4($29);" \
	"lw $1,0($29);" \
	"addu $29,$29,8;" \
	"j $31;" \
	"move $31,$1;" \
	".set reorder;" \
	".set at");
E 3
E 2

#ifdef KERNEL
/*
 * The following two macros do splhigh and splx respectively.
 * They have to be defined this way because these are real
 * functions on the PMAX, and we do not want to invoke mcount
 * recursively.
 */
D 4
#define	MCOUNT_ENTER
E 4
I 4
D 5
#define	MCOUNT_ENTER	s = splhigh()
E 5
I 5
#define	MCOUNT_ENTER	s = _splhigh()
E 5
E 4

D 4
#define	MCOUNT_EXIT
E 4
I 4
D 5
#define	MCOUNT_EXIT	splx(s)
E 5
I 5
#define	MCOUNT_EXIT	_splx(s)
E 5
E 4
#endif /* KERNEL */
E 1
