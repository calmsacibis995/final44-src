/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	subr.s,v $
 * Revision 2.2  89/07/12  00:25:16  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *	.seg    "data"
 *	.asciz  "@(#)subr.s 1.3 88/02/08"
 *	Copyright (c) 1986 by Sun Microsystems, Inc.
 */
	.seg    "text"
	.align  4

#include <machine/asm_linkage.h>
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/enable.h>
#define PSR_PIL_BIT 8
#define PG_S_BIT 29


#define RAISE(level) \
	mov     %psr, %o0; \
	and     %o0, PSR_PIL, %g1; \
	cmp     %g1, (level << PSR_PIL_BIT); \
	bl,a    1f; \
	andn    %o0, PSR_PIL, %g1; \
	retl; \
	nop; \
1:      or      %g1, (level << PSR_PIL_BIT), %g1; \
	mov     %g1, %psr; \
	nop; \
	retl; \
	nop;

#define SETPRI(level) \
	mov     %psr, %o0; \
	andn    %o0, PSR_PIL, %g1; \
	or      %g1, (level << PSR_PIL_BIT), %g1; \
	mov     %g1, %psr; \
	nop; \
	retl; \
	nop;

	ENTRY(splimp)
	RAISE(6)

	ENTRY(splnet)
	RAISE(1)

	ENTRY2(spl6,spl5)
	SETPRI(12)

	ENTRY(splx)
	and     %o0, PSR_PIL, %g1
	mov     %psr, %o0
	andn    %o0, PSR_PIL, %g2
	or      %g2, %g1, %g2
	mov     %g2, %psr
	nop
	retl
	nop

/*
 * insque(entryp, predp)
 *
 * Insert entryp after predp in a doubly linked list.
 */
	ENTRY(_insque)
	ld      [%o1], %g1              ! predp->forw
	st      %o1, [%o0 + 4]          ! entryp->back = predp
	st      %g1, [%o0]              ! entryp->forw = predp->forw
	st      %o0, [%o1]              ! predp->forw = entryp
	retl
	st      %o0, [%g1 + 4]          ! predp->forw->back = entryp

/*
 * remque(entryp)
 *
 * Remove entryp from a doubly linked list
 */
	ENTRY(_remque)
	ld      [%o0], %g1              ! entryp->forw
	ld      [%o0 + 4], %g2          ! entryp->back
	st      %g1, [%g2]              ! entryp->back = entryp->forw
	retl
	st      %g2, [%g1 + 4]          ! entryp->forw = entryp->back

