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
 * $Log:	ptrace.h,v $
 * Revision 2.7  89/05/30  10:43:47  rvb
 * 	Cleaned up mips case: include separate file like everybody else.
 * 	[89/04/20            af]
 * 
 * Revision 2.6  89/03/09  22:06:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  17:55:36  gm0w
 * 	Changed MULTIMAX to multimax and removed include of cputypes.h
 * 	[89/02/14            mrt]
 * 
 * Revision 2.4  89/01/23  22:28:09  af
 * 	Added mips register offsets
 * 	[89/01/10            af]
 * 
 * Revision 2.3  89/01/18  01:18:29  jsb
 * 	Sun: include sun/ptrace.h.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.2  88/08/24  02:40:17  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:20:42  mwyoung]
 * 
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ptrace.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_PTRACE_H_
#define _SYS_PTRACE_H_

#define PT_TRACE_ME	0	/* child declares it's being traced */
#define PT_READ_I	1	/* read word in child's I space */
#define PT_READ_D	2	/* read word in child's D space */
#define PT_READ_U	3	/* read word in child's user structure */
#define PT_WRITE_I	4	/* write word in child's I space */
#define PT_WRITE_D	5	/* write word in child's D space */
#define PT_WRITE_U	6	/* write word in child's user structure */
#define PT_CONTINUE	7	/* continue the child */
#define PT_KILL		8	/* kill the child process */
#define PT_STEP		9	/* single step the child */

#ifdef mips
#include <mips/mips_ptrace.h>
#endif mips

#ifdef	multimax
#include <mmax/mmax_ptrace.h>
#endif	multimax

#ifdef	sun
#include <sun/ptrace.h>
#endif	sun

#endif	_SYS_PTRACE_H_
