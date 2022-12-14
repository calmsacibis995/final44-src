/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	probe.s,v $
 * Revision 2.2  89/07/12  00:24:50  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *	.seg	"data"
 *	.asciz	"@(#)probe.s 1.4 88/02/08"
 *	Copyright (c) 1986 by Sun Microsystems, Inc.
 */
	.seg	"text"
	.align	4

#include <sun4/asm_linkage.h>
#define        TRAP_VECTOR_BASE        0xffe810d8

/*
 * set_handler, only called from this file for peek and poke
 * change trap-handler temporarily while probing
 * use of locals in this leaf routine is ok since they are used by the caller
 */
	.seg    "data"
lofault: .word  0
	.seg    "text"
	.align  4

set_handler:
	set     TRAP_VECTOR_BASE, %l0
	ld      [%l0], %l0
	ld      [%l0 + 0x24], %l1       ! save the current exception vector
	set     trap_handler, %o0
	retl			    ! done, leaf routine return
	st      %o0, [%l0 + 0x24]       ! write new vector

/*
 * The 4 instruction trap handler installed by set_handler for probes
 */
trap_handler:
	save    %sp, 0, %sp
	set     lofault, %l1
	mov     -1, %i0	 ! signify bad, -1 to i0 (contains addr above)
	st      %i0, [%l1]
	ret
	restore

/*
 * restore_trap, finshes all probe routines by restoring old trap vector
 */
restore_trap:
	st      %l1, [%l0 + 0x24]       ! restore old vector
	ret
	restore

/*
 * peek(addr)
 *
 * Temporarily re-routes Bus Errors, and then tries to
 * read a short from the specified address.  If a Bus Error occurs,
 * we return -1; otherwise, we return the unsigned short that we read.
 */
	ENTRY(peek)
	save	%sp, -SA(MINFRAME), %sp
	set	lofault, %l3
	st	%g0, [%l3]
	call	set_handler
	nop
	lduh	[%i0], %i0		! try to read short at addr
	nop				! we have -1 or return value now
	set	lofault, %l3
	ld	[%l3], %o0
	cmp	%o0, -1
	be,a	restore_trap
	mov	%o0, %i0
	b,a	restore_trap

/*
 * pokec(a,c)
 *  
 * This routine is the same, but uses a store instead of a read, due to
 * stupid I/O devices which do not respond to reads.
 *
 * if (pokec (charpointer, bytevalue)) itfailed;
 */

	ENTRY(pokec)
	save	%sp, -SA(MINFRAME), %sp
	set	lofault, %l3
	st	%g0, [%l3]
	call	set_handler
	nop
	clr	%o0
	stb	%i1, [%i0]		! try to write char at addr
	nop				! we get -1 if nothing there, (trap)
	set	lofault, %l3
	ld	[%l3], %o0
	cmp	%o0, -1			! was it there?
	be,a	restore_trap		! if not, return -1
	mov	%o0, %i0
	b	restore_trap		! otherwise
	mov	0, %o0			! it worked, return 0

/*
 * poke(a,c)
 *  
 * if (poke(pointer, value)) itfailed;
 */

	ENTRY(poke)
	save	%sp, -SA(MINFRAME), %sp
	set	lofault, %l3
	st	%g0, [%l3]
	call	set_handler
	nop
	st	%i1, [%i0]		! try to write int at addr
	nop				! we get -1 if nothing there, (trap)
	set	lofault, %l3
	ld	[%l3], %o0
	cmp	%o0, -1			! was it there?
	be,a	restore_trap		! if not, return -1
	mov	%o0, %i0
	b	restore_trap		! otherwise
	mov	0, %o0			! it worked, return 0
