/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	asm_linkage.h,v $
 * Revision 2.2  89/07/11  23:32:08  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)asm_linkage.h 1.4 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/* allow word aligned user stacks */
#define PARTIAL_ALIGN

/*
 * A stack frame looks like:
 *
 * %fp->|				|
 *	|-------------------------------|
 *	|  Locals, temps, saved floats	|
 *	|-------------------------------|
 *	|  outgoing parameters past 6	|
 *	|-------------------------------|-\
 *	|  6 words for callee to dump	| |
 *	|  register arguments		| |
 *	|-------------------------------|  > minimum stack frame
 *	|  One word struct-ret address	| |
 *	|-------------------------------| |
 *	|  16 words to save IN and	| |
 * %sp->|  LOCAL register on overflow	| |
 *	|-------------------------------|-/
 */

/*
 * Constants defining a stack frame.
 */
#define WINDOWSIZE	(16*4)		/* size of window save area */
#define ARGPUSHSIZE	(6*4)		/* size of arg dump area */
#define ARGPUSH		(WINDOWSIZE+4)	/* arg dump area offset */
#define MINFRAME	(WINDOWSIZE+ARGPUSHSIZE+4) /* min frame */

/*
 * Stack alignment macros.
 */
#define STACK_ALIGN	8
#define SA(X)	(((X)+(STACK_ALIGN-1)) & ~(STACK_ALIGN-1))


/*
 * profiling causes defintions of the MCOUNT and RTMCOUNT
 * particular to the type
 */
#ifdef GPROF

#define MCOUNT(x) \
	save	%sp, -SA(MINFRAME), %sp; \
	call	mcount; \
	nop ; \
	restore	;

#define RTMCOUNT(x) \
	save	%sp, -SA(MINFRAME), %sp; \
	call	mcount; \
	nop ; \
	restore	;

#endif GPROF


#ifdef PROF

#define MCOUNT(x) \
	save	%sp, -SA(MINFRAME), %sp; \
	sethi	%hi(L_/**/x/**/1), %o0; \
	call	mcount; \
        or      %o0, %lo(L_/**/x/**/1), %o0; \
        restore; \
        .reserve	L_/**/x/**/1, 4, "data", 4

#define RTMCOUNT(x) \
	save	%sp, -SA(MINFRAME), %sp; \
        sethi	%hi(L/**/x/**/1), %o0; \
        call	mcount; \
        or	%o0, %lo(L/**/x/**/1), %o0; \
        restore; \
        .reserve	L/**/x/**/1, 4, "data", 4

#endif PROF

/*
 * if we are not profiling,
 * MCOUNT and RTMCOUNT should be defined to nothing
 */
#if !defined(PROF) && !defined(GPROF)
#define MCOUNT(x)
#define RTMCOUNT(x)
#endif !PROF && !GPROF

/*
 * Entry macros for assembler subroutines.
 * NAME prefixes the underscore before a symbol.
 * ENTRY provides a way to insert the calls to mcount for profiling.
 * RTENTRY is similar to the above but provided for run-time routines
 *	whose names should not be prefixed with an underscore.
 */

#define	NAME(x) _/**/x

#define ENTRY(x) \
	.global	NAME(x); \
	NAME(x): MCOUNT(x)

#define ENTRY2(x,y) \
	.global	NAME(x), NAME(y); \
	NAME(x): ; \
	NAME(y): MCOUNT(x)

#define RTENTRY(x) \
	.global	x; x: RTMCOUNT(x)

/*
 * For additional entry points.
 */
#define ALTENTRY(x) \
	.global NAME(x); \
NAME(x):

#ifdef KERNEL
/*
 * Macros for saving/restoring registers.
 */

#define SAVE_GLOBALS(RP) \
	st	%g1, [RP + G1*4]; \
	std	%g2, [RP + G2*4]; \
	std	%g4, [RP + G4*4]; \
	std	%g6, [RP + G6*4]; \
	mov	%y, %g1; \
	st	%g1, [RP + Y*4]

#define RESTORE_GLOBALS(RP) \
	ld	[RP + Y*4], %g1; \
	mov	%g1, %y; \
	ld	[RP + G1*4], %g1; \
	ldd	[RP + G2*4], %g2; \
	ldd	[RP + G4*4], %g4; \
	ldd	[RP + G6*4], %g6;

#define SAVE_OUTS(RP) \
	std	%i0, [RP + O0*4]; \
	std	%i2, [RP + O2*4]; \
	std	%i4, [RP + O4*4]; \
	std	%i6, [RP + O6*4];

#define RESTORE_OUTS(RP) \
	ldd	[RP + O0*4], %i0; \
	ldd	[RP + O2*4], %i2; \
	ldd	[RP + O4*4], %i4; \
	ldd	[RP + O6*4], %i6;

#define SAVE_WINDOW(SBP) \
	std	%l0, [SBP + (0*4)]; \
	std	%l2, [SBP + (2*4)]; \
	std	%l4, [SBP + (4*4)]; \
	std	%l6, [SBP + (6*4)]; \
	std	%i0, [SBP + (8*4)]; \
	std	%i2, [SBP + (10*4)]; \
	std	%i4, [SBP + (12*4)]; \
	std	%i6, [SBP + (14*4)];

#define RESTORE_WINDOW(SBP) \
	ldd	[SBP + (0*4)], %l0; \
	ldd	[SBP + (2*4)], %l2; \
	ldd	[SBP + (4*4)], %l4; \
	ldd	[SBP + (6*4)], %l6; \
	ldd	[SBP + (8*4)], %i0; \
	ldd	[SBP + (10*4)], %i2; \
	ldd	[SBP + (12*4)], %i4; \
	ldd	[SBP + (14*4)], %i6;

#ifdef PARTIAL_ALIGN

#define SAVE_WINDOW_S(SBP) \
	st	%l0, [SBP + (0*4)]; \
	st	%l1, [SBP + (1*4)]; \
	st	%l2, [SBP + (2*4)]; \
	st	%l3, [SBP + (3*4)]; \
	st	%l4, [SBP + (4*4)]; \
	st	%l5, [SBP + (5*4)]; \
	st	%l6, [SBP + (6*4)]; \
	st	%l7, [SBP + (7*4)]; \
	st	%i0, [SBP + (8*4)]; \
	st	%i1, [SBP + (9*4)]; \
	st	%i2, [SBP + (10*4)]; \
	st	%i3, [SBP + (11*4)]; \
	st	%i4, [SBP + (12*4)]; \
	st	%i5, [SBP + (13*4)]; \
	st	%i6, [SBP + (14*4)]; \
	st	%i7, [SBP + (15*4)]

#define RESTORE_WINDOW_S(SBP) \
	ld	[SBP + (0*4)], %l0; \
	ld	[SBP + (1*4)], %l1; \
	ld	[SBP + (2*4)], %l2; \
	ld	[SBP + (3*4)], %l3; \
	ld	[SBP + (4*4)], %l4; \
	ld	[SBP + (5*4)], %l5; \
	ld	[SBP + (6*4)], %l6; \
	ld	[SBP + (7*4)], %l7; \
	ld	[SBP + (8*4)], %i0; \
	ld	[SBP + (9*4)], %i1; \
	ld	[SBP + (10*4)], %i2; \
	ld	[SBP + (11*4)], %i3; \
	ld	[SBP + (12*4)], %i4; \
	ld	[SBP + (13*4)], %i5; \
	ld	[SBP + (14*4)], %i6; \
	ld	[SBP + (15*4)], %i7

#endif PARTIAL_ALIGN

#endif KERNEL
