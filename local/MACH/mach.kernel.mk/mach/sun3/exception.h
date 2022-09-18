/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	exception.h,v $
 * Revision 2.4  89/03/09  20:23:26  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:40:34  gm0w
 * 	Changes for cleanup.
 * 
 * 28-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	Created.
 *
 */

/*
 *	Machine dependent exception definitions for the Sun3.
 */

#ifndef	_MACH_SUN3_EXCEPTION_H_
#define _MACH_SUN3_EXCEPTION_H_

/*
 *	EXC_BAD_INSTRUCTION
 */

#define EXC_SUN3_ILLEGAL_INSTRUCTION	0x10
#define EXC_SUN3_PRIVILEGE_VIOLATION	0x20
#define EXC_SUN3_COPROCESSOR		0x34
#define EXC_SUN3_TRAP1			0x84
#define EXC_SUN3_TRAP2			0x88
#define EXC_SUN3_TRAP3			0x8c
#define EXC_SUN3_TRAP4			0x90
#define EXC_SUN3_TRAP5			0x94
#define EXC_SUN3_TRAP6			0x98
#define EXC_SUN3_TRAP7			0x9c
#define EXC_SUN3_TRAP8			0xa0
#define EXC_SUN3_TRAP9			0xa4
#define EXC_SUN3_TRAP10			0xa8
#define EXC_SUN3_TRAP11			0xac
#define EXC_SUN3_TRAP12			0xb0
#define EXC_SUN3_TRAP13			0xb4
#define EXC_SUN3_TRAP14			0xb8
#define EXC_SUN3_FLT_BSUN		0xc0
#define EXC_SUN3_FLT_OPERAND_ERROR	0xd0

/*
 *	NOTE: TRAP0 is syscall, TRAP15 is breakpoint.
 */

/*
 *	EXC_ARITHMETIC
 */

#define EXC_SUN3_ZERO_DIVIDE		0x14
#define EXC_SUN3_FLT_INEXACT		0xc4
#define EXC_SUN3_FLT_ZERO_DIVIDE	0xc8
#define EXC_SUN3_FLT_UNDERFLOW		0xcc
#define EXC_SUN3_FLT_OVERFLOW		0xd4
#define EXC_SUN3_FLT_NOT_A_NUMBER	0xd8

/*
 *	EXC_EMULATION
 */

#define EXC_SUN3_LINE_1010		0x28
#define EXC_SUN3_LINE_1111		0x2c

/*
 *	EXC_SOFTWARE
 */

#define EXC_SUN3_CHK	0x18
#define EXC_SUN3_TRAPV	0x1c

/*
 *	EXC_BREAKPOINT
 */

#define EXC_SUN3_TRACE			0x24
#define EXC_SUN3_BREAKPOINT		0xbc

#endif	_MACH_SUN3_EXCEPTION_H_
