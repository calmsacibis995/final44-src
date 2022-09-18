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
 * $Log:	tmac.h,v $
 * Revision 2.2  89/02/26  10:48:39  gm0w
 * 	Changes for cleanup.
 * 
 * 20-Dec-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	use internal label 9 vs 1 in TIM() and TIM_PUSHR to avoid
 *	conflicts with code in locore.s
 *
 *  6-Dec-85  David L. Black (dlb) at Carnegie-Mellon University
 *	Modified to use indirect
 *	addressing of all timing routines to allow timing to be turned
 *	on and off at runtime.  Shortened TIM_PUSHR to enable cleanup
 *	of catcher code in locore.
 *
 * 30-Jul-85  David L. Black (dlb) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * This is a new file which defines the timing macros for kernel entry and 
 * exit.  Targets of jsb and jmp are in locore.s 
 */

/* for TIM and TIM_PUSHR macros the current mode of the old psl is
	being fetched and tested.  nop at end of TIM_PUSHR makes
	it exactly 20 bytes long. */

#define TIM_PUSHR(nump)	mfpr $ICR,-(sp) ; pushr $0x3f ; \
			cmpzv $24,$2,8+4*6+4*nump(sp),$3 ; \
			bneq 9f ; jsb *(upd_utimep) ; 9: nop

#define TIM(nump)	mfpr $ICR,-(sp) ; \
			cmpzv $24,$2,8+4*nump(sp),$3 ; \
			bneq 9f ; jsb *(upd_utime_rp) ; 9: addl2 $4,sp

#define TSREI_POPR	popr $0x3f ; addl2 $4,sp; jmp *(ts_exitp)

#define TSREI		jmp *(ts_exitp)

#define TS		jsb *(ts_p)

/* Warning: autoconf.c and locore.s know that TIM_PUSHR(0)
	takes exactly 20 bytes. */
