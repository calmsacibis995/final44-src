h59944
s 00002/00002/00186
d D 8.1 93/06/11 15:16:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00014/00175
d D 7.4 93/04/20 21:18:18 torek 4 3
c update from elf: van's changes to avoid noise
e
s 00001/00001/00188
d D 7.3 92/10/11 12:57:05 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00184
d D 7.2 92/07/21 16:54:19 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00184/00000/00000
d D 7.1 92/07/13 00:44:29 torek 1 0
c date and time created 92/07/13 00:44:29 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: bsd_audiointr.s,v 1.4 92/07/03 23:24:17 mccanne Exp $ (LBL)
E 4
I 4
 * from: $Header: bsd_audiointr.s,v 1.6 93/04/20 21:15:08 torek Exp $ (LBL)
E 4
 */
D 4
	
E 4
I 4

E 4
#ifndef AUDIO_C_HANDLER
#ifndef LOCORE
#define LOCORE
#endif
#include "assym.s"
#if BSD < 199103
/* SunOS */
#include <machine/intreg.h>
#define IE_L4 IR_SOFT_INT4
#else
/* 4.4BSD */
D 3
#include "intreg.h"
E 3
I 3
#include <sparc/sparc/intreg.h>
E 3
/* XXX this goes in a header file -- currently, it's hidden in locore.s */
#define INTREG_ADDR 0xf8002000
#endif

#define R_amd	%l2
#define R_cb	%l3
#define R_h	%l4
#define R_t	%l5

#if AUCB_SIZE > 4096
#define MASK	%l1
#else
#define MASK	AUCB_SIZE - 1
#endif

	.seg	"data"
	.align	8
audio_savepc:
	.word	0
#if AUCB_SIZE > 4096
	.word	0
#endif
	.seg	"text"
	.align	4
	.global _audio_trap
	.global	_audio_au

_audio_trap:
#if AUCB_SIZE > 4096
	set	audio_savepc, %l7
	st	%l1, [%l7]
	st	%l2, [%l7 + 4]
	set	AUCB_SIZE - 1, %l1
#else
	sethi	%hi(audio_savepc), %l7
	st	%l2, [%l7 + %lo(audio_savepc)]
#endif
	sethi	%hi(_audio_au), %l7
	ld	[%l7 + %lo(_audio_au)], %l7
	ld	[%l7 + AU_AMD], R_amd
	add	%l7, AU_RB, R_cb		! set up read cb ptr
	ldsb    [R_amd + AMD_IR], %g0		! clear interrupt
	ld	[%l7 + AU_STAMP], %l6
	inc	%l6
	st	%l6, [%l7 + AU_STAMP]		! bump time stamp

	! receive incoming data
	ld	[R_cb + CB_HEAD], R_h
	ld	[R_cb + CB_TAIL], R_t
D 4
	add	R_t, 1, %l7			! compute next tail ptr
	and	%l7, MASK, %l7
	cmp	R_h, %l7
E 4
I 4
	inc	R_t
	and	R_t, MASK, R_t
	cmp	R_h, R_t
E 4
	bne	2f
	 nop
	ld	[R_cb + CB_DROPS], %l7
	inc	%l7
	ba	7f
	 st	%l7, [R_cb + CB_DROPS]
2:
	lduh	[R_cb + CB_PAUSE], %l6
	tst	%l6
	be	3f
	 nop
	ld	[R_cb + CB_PDROPS], %l7
	inc	%l7
	ba	7f
	 st	%l7, [R_cb + CB_PDROPS]
3:
	ldsb	[R_amd + AMD_BBRB], %l6		! get sample
D 4
	add	R_t, CB_DATA, R_t		! adjust for struct offset
	stb	%l6, [R_cb + R_t]		! store sample in buffer
	st	%l7, [R_cb + CB_TAIL]		! update tail
	mov	%l7, R_t			!   "     "
E 4
I 4
	add	R_t, CB_DATA, %l7
	stb	%l6, [R_cb + %l7]		! store sample in buffer
	st	R_t, [R_cb + CB_TAIL]		! update tail
E 4
7:
	ld	[R_cb + CB_THRESH], %l6
	sub	R_t, R_h, %l7			! enough data?
	and	%l7, MASK, %l7
	cmp	%l7, %l6
	bl	1f
	 nop
#if AUCB_SIZE >= 4096
	set	AUCB_SIZE, %l7
#else
	mov	AUCB_SIZE, %l7
#endif
	st	%l7, [R_cb + CB_THRESH]		! disable threshold
	mov	1, %l7
	sth	%l7, [R_cb + CB_WAKING]		! set waking

	sethi	%hi(INTREG_ADDR), %l7
	ldub	[%l7 + %lo(INTREG_ADDR)], %l6
	or	%l6, IE_L4, %l6
	stb	%l6, [%l7 + %lo(INTREG_ADDR)]	! set software interrupt
1:
	/* write */
	set	AU_WB - AU_RB, %l6		! avoid loading _audio_au ptr
	add	R_cb, %l6, R_cb			! set up write cb ptr

	ld	[R_cb + CB_HEAD], R_h
	ld	[R_cb + CB_TAIL], R_t
	cmp	R_h, R_t
	bne	2f
D 4
	 nop
E 4
I 4
	 mov	0x7f, %l6			! write zero if no new data
E 4
	ld	[R_cb + CB_DROPS], %l7
	inc	%l7
	ba	4f
	 st	%l7, [R_cb + CB_DROPS]
2:
	lduh	[R_cb + CB_PAUSE], %l7
	tst	%l7
	be	3f
	 nop
	ld	[R_cb + CB_PDROPS], %l7
	inc	%l7
	ba	4f
	 st	%l7, [R_cb + CB_PDROPS]
3:
	inc	R_h
	and	R_h, MASK, R_h			! compute new head ptr
	st	R_h, [R_cb + CB_HEAD]
D 4
	add	R_h, CB_DATA, R_h		! adjust for struct offset
	ldsb	[R_cb + R_h], %l6		! load sample from buffer
	stb	%l6, [R_amd + AMD_BBTB]		! output sample to device
E 4
I 4
	add	R_h, CB_DATA, %l7		! adjust for struct offset
	ldsb	[R_cb + %l7], %l6		! load sample from buffer
E 4
4:
I 4
	stb	%l6, [R_amd + AMD_BBTB]		! output sample to device
E 4
	ld	[R_cb + CB_THRESH], %l6
	sub	R_t, R_h, %l7			! test if below low water
	and	%l7, MASK, %l7
	cmp	%l7, %l6
	bg	5f
	! nop

	mov	-1, %l7
	st	%l7, [R_cb + CB_THRESH]		! disable threshold
	sth	%l7, [R_cb + CB_WAKING]		! set waking
	
	! set software interrupt
	sethi	%hi(INTREG_ADDR), %l7
	ldsb	[%l7 + %lo(INTREG_ADDR)], %l6
	or	%l6, IE_L4, %l6
	stb	%l6, [%l7 + %lo(INTREG_ADDR)]
5:
	/*
	 * Restore psr -- note: psr delay honored by pc restore loads.
	 */
	mov	%l0, %psr
#if AUCB_SIZE > 4096
	sethi	%hi(audio_savepc), %l7
	ldd	[%l7 + %lo(audio_savepc)], %l2
	jmp	%l2
	rett	%l3
#else
	sethi	%hi(audio_savepc), %l7
	ld	[%l7 + %lo(audio_savepc)], %l2
	jmp	%l1
	rett	%l2
#endif
#endif
E 1
