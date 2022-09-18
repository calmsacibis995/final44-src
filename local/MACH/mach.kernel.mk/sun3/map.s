/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	map.s,v $
 * Revision 2.4  89/03/09  21:36:36  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:45:05  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 *  3-Feb-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Created by dbg.   Finished and debugged by rvb.
 *	NB	{get,set}segmap take a context number as the first
 *		arg, while {get,set}sgmap use the current context
 *	NB	{get,set}pagemap take a context number as the first
 *		arg, while {get,set}pgmap use the current context
 *	??
 */
/*
 *	Rewrite sun3/map.s
 */

#include <cputypes.h>

#include <sun3/asm_linkage.h>
#include <sun3/mmu.h>

#if	SUN3_260
#define SUN_VAC 1
#endif	SUN3_260

/*
int	getcontext();
*/
ENTRY(getcontext)
	movsb	CONTEXTBASE,d0		| save context register
	andl	#CONTEXTMASK, d0	| in case we care
	rts				| done

/*
void	setcontext(int context);
*/
ENTRY(setcontext)
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	rts				| done

/*
int	getpagemap(int context, vm_offset_t va);
*/
ENTRY(getpagemap)
	movl	sp@(8),d0		| get address
	andl	#PAGEADDRBITS,d0	| mask out offset bits
	orl	#PAGEBASE,d0		| add in page map access base
	movl	d0,a0
	movsb	CONTEXTBASE,d1		| save context register
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	movsl	a0@,d0			| get page map entry
	movsb	d1,CONTEXTBASE		| restore context register
	rts				| done

/*
void	setpagemap(int context, vm_offset_t va, int pme);
*/
ENTRY(setpagemap)
	movl	sp@(8),d0		| get address
	andl	#PAGEADDRBITS,d0	| mask out offset bits
	orl	#PAGEBASE,d0		| add in page map access base
	movl	d0,a0
	movsb	CONTEXTBASE,d1		| save context register
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	movl	sp@(12),d0		| get pme to write
	movsl	d0,a0@			| set page map entry
	movsb	d1,CONTEXTBASE		| restore context register
	rts				| done

/*
void	changepagemap(int context, vm_offset_t va, and_complement_mask, or_mask)
*/
ENTRY(changepagemap)
	movl	sp@(8),d0		| get address
	andl	#PAGEADDRBITS,d0	| mask out offset bits
	orl	#PAGEBASE,d0		| add in page map access base
	movl	d0,a0
	movsb	CONTEXTBASE,d1		| save context register
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:
	movsl	a0@, d0			| get old pme
	movl	d0, a1			| save old pme for return
	andl	sp@(12), d0		| AND new stuff
	orl	sp@(16), d0		| OR new stuff
	movsl	d0,a0@			| set page map entry
	movsb	d1,CONTEXTBASE		| restore context register
	movl	a1, d0			| old pme
	rts				| done

/*
int	getpgmap(vm_offset_t va);
*/
ENTRY(getpgmap)
	movl	sp@(4),d0		| get address
	andl	#PAGEADDRBITS,d0	| mask out offset bits
	orl	#PAGEBASE,d0		| add in page map access base
	movl	d0,a0
	movsl	a0@,d0			| get page map entry
	rts				| done

/*
void	setpgmap(vm_offset_t va, int pme);
*/
ENTRY(setpgmap)
	movl	sp@(4),d0		| get address
	andl	#PAGEADDRBITS,d0	| mask out offset bits
	orl	#PAGEBASE,d0		| add in page map access base
	movl	d0,a0
	movl	sp@(8),d0		| get pme to write
	movsl	d0,a0@			| set page map entry
	rts				| done
/*
void	changepgmap(vm_offset_t va,  and_complement_mask, or_mask);
*/
ENTRY(changepgmap)
	movl	sp@(4),d0		| get address
	andl	#PAGEADDRBITS,d0	| mask out offset bits
	orl	#PAGEBASE,d0		| add in page map access base
	movl	d0,a0
	movsl	a0@, d0			| get old pme
	movl	d0, a1			| return old pme
	andl	sp@(8), d0		| AND new stuff
	orl	sp@(12), d0		| OR new stuff
	movsl	d0,a0@			| set page map entry
	movl	a1, d0
	rts

/*
int	getsegmap(int context, vm_offset_t va);
*/
ENTRY(getsegmap)
	movl	sp@(8),d0		| get address
	andl	#SEGMENTADDRBITS,d0	| mask out offset bits
	orl	#SEGMENTBASE,d0		| add in segment map access base
	movl	d0,a0
	movsb	CONTEXTBASE,d1		| save context register
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	clrl	d0
	movsb	a0@,d0			| get segment map entry
	movsb	d1,CONTEXTBASE		| restore context register
	rts				| done

/*
void	setsegmap(int context, vm_offset_t va, int seg);
*/
ENTRY(setsegmap)
	movl	sp@(8),d0		| get address
	andl	#SEGMENTADDRBITS,d0	| mask out offset bits
	orl	#SEGMENTBASE,d0		| add in segment map access base
	movl	d0,a0
	movsb	CONTEXTBASE,d1		| save context register
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	movl	sp@(12),d0		| get pme to write
	movsb	d0,a0@			| set segment map entry
	movsb	d1,CONTEXTBASE		| restore context register
	rts				| done

/*
int	getsgmap(vm_offset_t va);
*/
ENTRY(getsgmap)
	movl	sp@(4),d0		| get address
	andl	#SEGMENTADDRBITS,d0	| mask out offset bits
	orl	#SEGMENTBASE,d0		| add in segment map access base
	movl	d0,a0
	clrl	d0
	movsb	a0@,d0			| get segment map entry
	rts				| done

/*
void	setsgmap(vm_offset_t va, int seg);
*/
ENTRY(setsgmap)
	movl	sp@(4),d0		| get address
	andl	#SEGMENTADDRBITS,d0	| mask out offset bits
	orl	#SEGMENTBASE,d0		| add in segment map access base
	movl	d0,a0
	movl	sp@(8),d0		| get pme to write
	movsb	d0,a0@			| set segment map entry
	rts				| done

#if	SUN_VAC
/*
void	cache_flush_page(int context, vm_offset_t va);
*/
ENTRY(cache_flush_page)
	movl	sp@(8),d0		| get virtual address
	andl	#PAGEADDRBITS,d0	| mask out offset
	orl	#VAC_FLUSH_BASE,d0	| add in page flush base address
	movl	d0,a0
	movsb	CONTEXTBASE,d1		| save context
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	movl	d1,a1			| save old context
	
	movl	#VAC_PAGEFLUSH_COUNT-1,d0
	movb	#VAC_PAGEFLUSH,d1	| page flush command
0:
	movsb	d1,a0@			| flush part of a page
	addl	#VAC_FLUSH_INCRMNT,a0	| point to next flush unit
	dbra	d0,0b			| loop
	movl	a1,d1			| retrieve old context
	movsb	d1,CONTEXTBASE		| and restore it
	rts

/*
void	cache_flush_seg(int context, vm_offset_t va);
*/
ENTRY(cache_flush_seg)
	movl	sp@(8),d0		| get virtual address
	andl	#SEGMENTADDRBITS,d0	| mask out offset
	orl	#VAC_FLUSH_BASE,d0	| add in page flush base address
	movl	d0,a0
	movsb	CONTEXTBASE,d1		| save context
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	movl	d1,a1			| save old context
	
	movl	#VAC_SEGFLUSH_COUNT-1,d0
	movb	#VAC_SEGFLUSH,d1	| segment flush command
0:
	movsb	d1,a0@			| flush part of a segment
	addl	#VAC_FLUSH_INCRMNT,a0	| point to next flush unit
	dbra	d0,0b			| loop
	movl	a1,d1			| retrieve old context
	movsb	d1,CONTEXTBASE		| and restore it
	rts

/*
void	cache_flush_context(int context);
*/
ENTRY(cache_flush_context)
	movl	#VAC_FLUSH_BASE,a0	| get flush base address
	movsb	CONTEXTBASE,d1		| save context
	movl	sp@(4),d0		| get working context
	blts	0f			| ? CURRENTCONTEXT
	movsb	d0,CONTEXTBASE		| set it
0:	movl	d1,a1			| save old context
	
	movl	#VAC_CTXFLUSH_COUNT-1,d0
	movb	#VAC_CTXFLUSH,d1	| context flush command
0:
	movsb	d1,a0@			| flush part of a segment
	addl	#VAC_FLUSH_INCRMNT,a0	| point to next flush unit
	dbra	d0,0b			| loop
	movl	a1,d1			| retrieve old context
	movsb	d1,CONTEXTBASE		| and restore it
	rts

/* from sun for now */
	|
	| Init the VAC by invaliding all cache tags.
	| We loop through all 64KB to reset the valid bit of each line.
	| It DOESN'T turn on cache enable bit in the enable register.
	|
	| vac_init()
	ENTRY(vac_init)
	movl	#VAC_RWTAG_BASE,a0	| set base address to R/W VAC tags
	movl	#VAC_RWTAG_COUNT-1,d0	| loop through all lines
	clrl	d1			| reset valid bit of tags
0:	movsl	d1,a0@			| invalid the tag of this line
	addl	#VAC_RWTAG_INCRMNT,a0	| address to write to next line
	dbra	d0,0b			| invalid next tag until done
	rts
#endif	SUN_VAC
