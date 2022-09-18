/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mem_rop_impl_util.h,v $
 * Revision 2.4  89/03/09  20:56:28  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:11:43  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/* @(#)mem_rop_impl_util.h 1.2 86/10/08 SMI */

/*
 * Copyright 1986 by Sun Microsystems,  Inc.
 */

#ifndef	MEM_ROP_IMPL_UTIL_H_
#define MEM_ROP_IMPL_UTIL_H_

/*
 * Utility macros for memory pixrect code
 */

/*
 * Shifted pixrect op codes
 */
#define PIX_OPSRC	(12)
#define PIX_OPDST	(10)
#define PIX_OPNOT(op)	(~(op) & 15)
#define PIX_OPCLR	(0)
#define PIX_OPSET	(15)

/*
 * Identify 68000 family CPUs
 */
#ifndef	mc68000
#define mc68000	(defined(mc68010) || defined(mc68020))
#endif

#ifdef	mc68020
#undef	mc68010
#endif

/* 
 * lint doesn't believe in do { } while (0) 
 */
#ifdef	lint
int _ZERO_ = 0;
#else
#define _ZERO_ 0
#endif

/* 
 * Code selection macros 
 */
#define IFTRUE(a,b) a
#define IFFALSE(a,b) b
#define IFTRUET(t, a, b)	do { if (t) {a;} else {b;} } while (_ZERO_)
#define IFFALSET(t, a, b)	do { b; } while (_ZERO_)

/*
 * Option control macros
 */
#define ALWAYS(option,a,b)	IFTRUE(a,b)
#define NEVER(option,a,b)	IFFALSE(a,b)
#define OPTION(option,a,b)	option(a,b)

#define ALWAYST(option,t,a,b)	IFTRUET(t,a,b)
#define NEVERT(option,t,a,b)	IFFALSET(t,a,b)
#define OPTIONT(option,t,a,b)	option(t,a,b)

/*
 * Kernel code selection macro
 */
#ifdef	KERNEL
#define IFKERNEL IFTRUE
#else
#define IFKERNEL IFFALSE
#endif

/* 
 * CPU selection macro
 */
#if	mc68000
#define IF68000	IFTRUE
#else
#define IF68000	IFFALSE
#endif

/*
 * Speed choice macros
 *
 * The T form is used when the "never" half of the fast code
 * is the same as the slow code.
 *
 * Define NEVER_SLOW to get all fast code.
 * Define NEVER_FAST to get all slow code.
 */
 
#if	defined(NEVER_FAST) && !defined(NEVER_SLOW)
#define FAST	IFFALSE
#define FASTT	IFFALSET
#else
#define FAST	IFTRUE
#define FASTT	IFTRUET
#endif

#ifdef	NEVER_SLOW
#define SLOW	IFTRUE
#define SLOWT	IFTRUET
#else
#define SLOW	IFFALSE
#define SLOWT	IFFALSET
#endif

#endif	MEM_ROP_IMPL_UTIL_H_
