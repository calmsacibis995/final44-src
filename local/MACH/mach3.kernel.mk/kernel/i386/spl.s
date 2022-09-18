/* 
 * Mach Operating System
 * Copyright (c) 1993,1991,1990 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	spl.s,v $
 * Revision 2.10  93/11/17  16:39:44  dbg
 * 	Use PIC masks directly as SPL values.
 * 	[93/10/29            dbg]
 * 
 * 	Remove softclock checks.
 * 	[93/02/18            dbg]
 * 
 * Revision 2.9  93/02/04  07:58:11  danner
 * 	Convert asm comment "/" over to "/ *" "* /"
 * 	[93/01/27            rvb]
 * 
 * Revision 2.8  91/06/06  17:04:01  jsb
 * 	Added spldcm for i386ipsc.
 * 	[91/05/13  16:53:38  jsb]
 * 
 * Revision 2.7  91/05/14  16:16:41  mrt
 * 	Correcting copyright
 * 
 * Revision 2.6  91/05/08  12:42:29  dbg
 * 	Put parentheses around substituted immediate expressions, so
 * 	that they will pass through the GNU preprocessor.
 * 
 * 	Add set_spl_noi to reset PIC masks but leave interrupts disabled
 * 	(IF clear).
 * 	[91/04/26  14:38:31  dbg]
 * 
 * Revision 2.5  91/02/05  17:14:45  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:38:06  mrt]
 * 
 * Revision 2.4  90/12/20  16:36:50  jeffreyh
 * 	Changes for __STDC__
 * 	[90/12/07            jeffreyh]
 * 
 * Revision 2.3  90/11/26  14:48:50  rvb
 * 	Change Prime copyright as per Peter J. Weyman authorization.
 * 	[90/11/19            rvb]
 * 
 * Revision 2.2  90/05/03  15:37:36  dbg
 * 	Stole from Prime.
 * 	[90/02/14            dbg]
 * 
 */

/*
Copyright (c) 1988,1989 Prime Computer, Inc.  Natick, MA 01760
All Rights Reserved.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and
without fee is hereby granted, provided that the above
copyright notice appears in all copies and that both the
copyright notice and this permission notice appear in
supporting documentation, and that the name of Prime
Computer, Inc. not be used in advertising or publicity
pertaining to distribution of the software without
specific, written prior permission.

THIS SOFTWARE IS PROVIDED "AS IS", AND PRIME COMPUTER,
INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN
NO EVENT SHALL PRIME COMPUTER, INC.  BE LIABLE FOR ANY
SPECIAL, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN ACTION OF CONTRACT, NEGLIGENCE, OR
OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <i386/asm.h>
#include <i386/ipl.h>
#include <i386/pic.h>

/* *****************************************************************************
	SET_PIC_MASK : this routine is run to set the pic masks.  It is 
	implemented as a macro for efficiency reasons.
***************************************************************************** */

#define SET_PIC_MASK							\
	outb	%al, $(MASTER_OCW)		;			\
	movb	%ah, %al			;			\
	outb	%al, $(SLAVE_OCW)


/* *****************************************************************************
	SPLn : change interrupt priority level to that in %eax
	SPLOFF : disable all interrupts, saving interrupt flag
	SPLON: re-enable interrupt flag, undoes sploff()
	Warning: SPLn and SPLOFF aren`t nestable.  That is,
		a = sploff();
		...
		b = splmumble();
		...
		splx(b);
		...
		splon(a);
	is going to do the wrong thing.
***************************************************************************** */

/*
 *	The representation of the IPL is:
 *
 *	bits 0..15		PIC mask value
 *	bit  31			nonzero if all interrupts are blocked
 *				at CPU (IF set).
 *
 *	If interrupts are blocked at the CPU, the PIC mask may not
 *	need to be changed when the old IPL is restored.
 */

ENTRY(spl0)
	movw	_pic_mask+2*0, %ax
	jmp	EXT(set_spl_mask)

ENTRY(spl1)
ENTRY(splsoftclock)
	movw	_pic_mask+2*1, %ax
	jmp	EXT(set_spl_mask)

ENTRY(spl2)
	movw	_pic_mask+2*2, %ax
	jmp	EXT(set_spl_mask)

ENTRY(spl3)
	movw	_pic_mask+2*3, %ax
	jmp	EXT(set_spl_mask)

ENTRY(splnet)
ENTRY(splhdw)
ENTRY(spl4)
	movw	_pic_mask+2*4, %ax
	jmp	EXT(set_spl_mask)

ENTRY(splbio)
ENTRY(spldcm)
ENTRY(spl5)
	movw	_pic_mask+2*5, %ax
	jmp	EXT(set_spl_mask)

ENTRY(spltty)
ENTRY(spl6)
	movw	_pic_mask+2*6, %ax
	jmp	EXT(set_spl_mask)


ENTRY(set_spl)
	movw	_pic_mask(,%eax,2),%ax	/* enter with SPL number */

/*
 *	Set IPL for levels 0..6 (not blocking all interrupts).
 *	New pic mask is in %ax.
 *	Uses %edx.
 *	Returns old SPL in %eax.
 */
	.globl	_set_spl_mask
_set_spl_mask:
	andl	$0xffff,%eax		/* zero high bit (IF off) of new IPL */
	cli				/* disable interrupts */
	movl	_curr_ipl, %edx		/* get old IPL */
	movl	%eax, _curr_ipl		/* set new IPL */
	cmpw	%ax, %dx		/* if new PIC mask is different, */
	je	0f
	SET_PIC_MASK			/* set it. */
0:
	sti				/* enable processor interrupts */
	movl	%edx,%eax		/* return old level */
	ret

/*
 *	Block all interrupts.
 */
ENTRY(splclock)
ENTRY(splimp)
ENTRY(splvm)
ENTRY(splsched)
ENTRY(splhigh)
ENTRY(splhi)
ENTRY(spl7)

	cli				/*  3  disable interrupts */
	movl	_curr_ipl, %eax		/* return old IPL */
	movb	$0x80, _curr_ipl+3	/*  2  mark as disabled,*/
	ret				/* 10  preserve image of PIC mask */
/*					------ */
/*					  19 */

ENTRY(sploff)				/*  7  */
	pushf				/*  2  Flags reg NOT accessable */
	popl	%eax			/*  2  push onto stk, pop it into reg */
	cli				/*  3  DISABLE ALL INTERRUPTS */
	ret				/*  7  */
/*					------ */
/*					  21 */

ENTRY(splon)				/*  7 */
	pushl	4(%esp)			/*  4  Flags regs not directly settable. */
	popf				/*  4  push value, pop into flags reg */
					/*      IF ints were enabled before  */
					/*	then they are re-enabled now. */
	ret				/*  7  */
/*					------ */
/*					  22 */

/*
 *	void splx(spl_t)
 *
 *	Sets the IPL back to an old value that was gotten from
 *	spl<n> or pic_mask[] directly.
 *
 */
ENTRY(splx)
	movl	4(%esp),%eax		/* get new interrupt level from stack */
	cli				/* block interrupts */
	testl	%eax,%eax		/* all interrupts blocked? */
	js	splx_high		/* exit now if so, leaving
					   PIC mask unchanged. */

					/* we now know that IF will be set */
	movl	_curr_ipl,%edx		/* get current IPL */
	movl	%eax,_curr_ipl		/* set new IPL (clears 'IF-set') */
	cmpw	%ax,%dx			/* if PIC mask needs to be changed, */
	je	0f
	SET_PIC_MASK			/* do so */
0:
	sti				/* reenable processor interrupts */
	ret				/* and return */

splx_high:				/* leave interrupts disabled */
	movb	$0x80,_curr_ipl+3	/* at processor, and mark them so */
	ret

/*
 * Set SPL, but leave interrupts disabled.  Called when returning
 * from interrupt.  Interrupts are already disabled.
 * New interrupt level is in %ax;  since this is called from
 * an interrupt, we know that it cannot be SPLHIGH.
 */
	.globl	EXT(set_spl_noi)
LEXT(set_spl_noi)
	movl	_curr_ipl,%edx		/* get current IPL */
	movl	%eax,_curr_ipl		/* set new IPL (clears 'IF-set') */
	cmpw	%ax,%dx			/* if PIC mask needs to be changed, */
	je	0f
	SET_PIC_MASK			/* do so */
0:
	ret
