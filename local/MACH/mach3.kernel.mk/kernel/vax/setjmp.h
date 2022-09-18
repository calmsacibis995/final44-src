/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	setjmp.h,v $
 * Revision 2.2  90/08/27  22:14:14  dbg
 * 	Created.
 * 	[90/07/16            dbg]
 * 
 */

/*
 * Setjmp/longjmp buffer for VAX.
 */
#ifndef	_VAX_SETJMP_H_
#define	_VAX_SETJMP_H_

typedef	struct jmp_buf {
	int	jmp_buf[10];	/* r6..r11, ap, fp, sp, pc */
} jmp_buf_t;

#endif	/* _VAX_SETJMP_H_ */
