/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cache.s,v $
 * Revision 2.2  89/07/12  00:24:20  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *	.seg	"data"
 *	.asciz	"@(#)cache.s 1.7 88/02/08"
 *	Copyright (c) 1986 by Sun Microsystems, Inc.
 */
 	.seg	"text"
 	.align	4

#include <sun4/asm_linkage.h>
#include <sun4/param.h>
#include <sun4/pte.h>
#include <sun4/mmu.h>
#include <sun4/enable.h>
#define NSGVA	(1<<(32-PMGRPSHIFT))
/*
 * cache_prog(start, end)
 * change all of the text and data pages
 * that are used by prog to be cacheable
 */
	ENTRY(cache_prog)
	save	%sp, -WINDOWSIZE, %sp
	set	PG_NC, %l0		! the no cache bit
	set	NBPG, %l1		! pagesize increment
1:
	call	_getpgmap		! get pte
	mov	%i0, %o0		! address

	andn	%o0, %l0, %o1		! clear the nocache bit
	call	_setpgmap		! write the new pte
	mov	%i0, %o0		! address

	add	%i0, %l1, %i0		! add pagesize to get next pte
	cmp	%i0, %i1
	bleu	1b			! go do the next page
	nop

	ret
	restore

/*
 * turnon_cache
 *	write all the tags to zero
 *	turn on the cache via the system enable register
 */
	ENTRY(turnon_cache)
	set     CACHETAGSBASE, %o0      ! address of cache tags in CTL space
	set     VAC_NLINES, %o1         ! number of lines to initialize
	mov     (VAC_LINESIZE), %o2     ! offsets for by 4 loop unroll
	mov     (VAC_LINESIZE*2), %o3
	mov     (VAC_LINESIZE*3), %o4
1:
	sta     %g0, [%o0]ASI_CTL       ! write tags to zero
	sta     %g0, [%o0 + %o2]ASI_CTL ! offset 16
	sta     %g0, [%o0 + %o3]ASI_CTL ! offset 32
	sta     %g0, [%o0 + %o4]ASI_CTL ! offset 48
	subcc   %o1, 4, %o1             ! done yet?
	bg      1b
	add     %o0, VAC_LINESIZE*4, %o0 ! next cache tags address

	set     ENABLEREG, %o2          ! address of real version in hardware
	lduba    [%o2]ASI_CTL, %g1	! get current value
	bset	ENA_CACHE, %g1		! enable cache bit
	retl
	stba	%g1, [%o2]ASI_CTL	! write new value

/*
 * disable the cache, flush the cache completely (all of context 0)
 * We can't flush context 0 with a context flush, (a feature)
 * because we've been using context 0 in supervisor mode,
 * so we loop through segments.  Once flushed,  turn off the 
 * cache via the system enable register
 * NOTE: this assumes that standalones only use one context
 */
	ENTRY(turnoff_cache)
	save	%sp, -WINDOWSIZE, %sp
	mov	0, %l0			! address of first segment
	set	PMGRPSIZE, %l1		! number of bytes in a segment
	set	NPMGRPPERCTX_260/2, %l2	! number of segs to flush in 1st half
	mov	(VAC_LINESIZE), %l5
	mov	(VAC_LINESIZE*2), %l6
	mov	(VAC_LINESIZE*3), %l7
1:
	lduha	[%l0]ASI_SM, %g1	! get segment map
	cmp	%g1, SEGINV		! if invalid we don't have to flush
	be	3f
	.empty
	!
	! flush the segment
	!
	mov	%l0, %o0
	set	VAC_SEGFLUSH_COUNT, %o1	! set count
2:	
	sta	%g0, [%o0]ASI_FCS
	sta	%g0, [%o0 + %l5]ASI_FCS
	sta	%g0, [%o0 + %l6]ASI_FCS
	sta	%g0, [%o0 + %l7]ASI_FCS
	deccc	4, %o1			! dec count
	bg	2b			! done?
	add	%o0, (VAC_LINESIZE*4), %o0 ! next group of lines
3:
	deccc	%l2			! count down segments
	bnz	1b
	add	%l0, %l1, %l0		! next segment

	tst	%l0			! at end of 2nd half of addr space?
	set	(NSGVA - (NPMGRPPERCTX_260/2)) * PMGRPSIZE, %l0 ! start of 2nd half
	set	NPMGRPPERCTX_260/2, %l2	! number of segs to flush in 2nd half
	bnz	1b			! no, do 2nd half
	.empty

	set     ENABLEREG, %o0          ! address of enable reigster
	lduba    [%o0]ASI_CTL, %g1	! get current value
	bclr	ENA_CACHE, %g1		! clear enable cache bit
	stba	%g1, [%o0]ASI_CTL	! write new value
	ret				! cache is now off
	restore
