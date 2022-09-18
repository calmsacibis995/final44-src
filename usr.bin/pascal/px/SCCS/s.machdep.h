h14725
s 00002/00002/00087
d D 8.1 93/06/06 15:58:08 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00084
d D 5.4 91/04/16 15:48:17 bostic 8 7
c new copyright; att/bsd/shared
e
s 00053/00004/00035
d D 5.3 89/01/09 17:22:26 mckusick 7 6
c from John Gilmore for gcc
e
s 00023/00000/00016
d D 5.2 86/11/12 19:23:56 mckusick 6 5
c add machine specific macros for extracting inline data
e
s 00007/00003/00009
d D 5.1 85/06/05 13:59:57 dist 5 4
c Add copyright
e
s 00000/00000/00012
d D 2.1 84/02/08 20:29:09 aoki 4 3
c synchronize to version 2
e
s 00004/00003/00008
d D 1.3 83/01/10 19:52:56 mckusick 3 2
c ifdef VAX => ifdef ADDR32
e
s 00006/00002/00005
d D 1.2 81/03/06 23:01:15 mckusic 2 1
c add onyx code
e
s 00007/00000/00000
d D 1.1 81/01/07 16:55:37 mckusick 1 0
c date and time created 81/01/07 16:55:37 by mckusick
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */

D 2
/* static 	char sccsid[] = "%Z%%M% %I% %G%"; */
E 2
I 2
/* static char sccsid[] = "%Z%%M% %I% %G%"; */
E 5
I 5
D 8
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 9
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 5
E 2

I 2
D 3
#ifdef VAX
E 3
I 3
#ifdef ADDR32
E 3
E 2
D 7
#define pushaddr push4
#define popaddr (char *)pop4
E 7
I 7
#define pushaddr(x)	push4((long)(x))
#define popaddr()	(char *)pop4()
E 7
D 2
#define popargs(num) popsp(num * sizeof(int))
E 2
I 2
D 3
#else
E 3
I 3
#endif ADDR32
#ifdef ADDR16
E 3
D 7
#define pushaddr push2
#define popaddr (char *)pop2
E 7
I 7
#define pushaddr(x)	push2((short)(x))
#define popaddr()	(char *)pop2()
E 7
D 3
#endif VAX
E 3
I 3
#endif ADDR16
I 6

I 7
#define popfile()	(FILE *)(popaddr())

#if defined(pdp11)
#define	popint	pop2
#define	pushint	push2
#else
#define popint	pop4
#define pushint	push4
#endif

E 7
/*
 * Machine specific macros for reading quantities from the
 * interpreter instruction stream. Operands in the instruction
 * stream are aligned to short, but not long boundries. Blockmarks
 * are always long aligned. Stack alignment indicates whether the
 * stack is short or long aligned. Stack alignment is assumed to
 * be no more than long aligned for ADDR32 machines, short aligned
 * for ADDR16 machines.
 */
#if defined(vax) || defined(mc68000) || defined(pdp11)
#define PCLONGVAL(target) target = *pc.lp++
#define GETLONGVAL(target, srcptr) target = *(long *)(srcptr)
#define STACKALIGN(target, value) target = ((value) + 1) &~ 1
#endif vax || mc68000 || pdp11

#ifdef tahoe
#define PCLONGVAL(target) target = *pc.sp++ << 16, target += *pc.usp++
#define GETLONGVAL(target, srcptr) \
	tsp = (short *)(srcptr), \
	target = *tsp++ << 16, target += *(unsigned short *)tsp
#define STACKALIGN(target, value) target = ((value) + 3) &~ 3
#endif tahoe
I 7

/*
 * The following macros implement all accesses to the interpreter stack.
 *
 * They used to be hard-coded assembler stuff massaged into the compiler
 * output by sed scripts, but things are cleaner now.
 *
 * The STACKSIZE is an arbitrary value.  I picked 100K since it was unlikely
 * that anybody's program would run out of stack.  Automatic allocation
 * would be nice, maybe procedure call should check for enough space + slop
 * and expand it if necessary.  Expanding the stack will require
 * pointer relocation if it moves, though.  Probably better would be a
 * command line option to set the stack size.
 */
#define	STACKSIZE	100000
#define	setup()		{ \
	extern char *malloc(); \
	stack.cp = STACKSIZE + malloc((unsigned)STACKSIZE); \
	}
#ifndef tahoe
#define	push2(x)	(*--stack.sp) = (x)
#else
#define	push2(x)	(*--stack.lp) = (x) << 16
#endif
#define push4(x)	(*--stack.lp)  = (x)
#define push8(x)	(*--stack.dbp) = (x)
#define pushsze8(x)	(*--stack.s8p) = (x)
#define pushsp(x)	(stack.cp -= (x))
#ifndef tahoe
#define pop2()		(*stack.sp++)
#else
#define pop2()		(*stack.lp++) >> 16
#endif
#define pop4()		(*stack.lp++)
#define pop8()		(*stack.dbp++)
#define popsze8()	(*stack.s8p++)
#define popsp(x)	(void)(stack.cp += (x))
#define	enableovrflo()	/*nop*/
#define	disableovrflo()	/*nop*/
E 7
E 6
E 3
E 2
E 1
