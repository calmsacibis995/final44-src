h24980
s 00002/00002/00179
d D 8.1 93/06/11 15:58:14 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00177
d D 7.2 92/10/11 10:22:58 bostic 2 1
c make kernel includes standard
e
s 00179/00000/00000
d D 7.1 91/04/28 17:39:24 william 1 0
c date and time created 91/04/28 17:39:24 by william
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * wdbootblk.s:
 *	Written 7/6/90 by William F. Jolitz
 *	Initial block boot for AT/386 with typical Western Digital
 *	WD 1002-WA2 (or upwards compatable). Works either as
 *	first and sole partition bootstrap, or as loaded by a
 *	earlier BIOS boot when on an inner partition of the disk.
 *
 *	Goal is to read in sucessive 7.5Kbytes of bootstrap to
 *	execute.
 *
 *	No attempt is made to handle disk errors.
 */
D 2
#include "i386/isa/isa.h"
#include "i386/isa/wdreg.h"
E 2
I 2

#include <i386/isa/isa.h>
#include <i386/isa/wdreg.h>

E 2
#define	NOP	jmp 1f ; nop ; 1:
#define BIOSRELOC	0x7c00
#define start		0x70400

	/* step 0 force descriptors to bottom of address space */

	.byte 0xfa,0xb8,0x30,0x00,0x8e,0xd0,0xbc,0x00,0x01 #ll fb

	xorl	%eax,%eax
	movl	%ax,%ds
	movl	%ax,%es

	/* step 1 load new descriptor table */

	.byte 0x2E,0x0F,1,0x16
	.word	BIOSRELOC+0x4a	#GDTptr
	# word aword cs lgdt GDTptr

	/* step 2 turn on protected mode */

	smsw	%ax
	orb	$1,%al
	lmsw	%ax
	jmp	1f
	nop

	/* step 3  reload segment descriptors */

1:
	xorl	%eax,%eax
	movb	$0x10,%al
	movl	%ax,%ds
	movl	%ax,%es
	movl	%ax,%ss
	word
	ljmp	$0x8,$ BIOSRELOC+0x50	/* would be nice if .-RELOC+0x7c00 worked */

 /* Global Descriptor Table contains three descriptors:
  * 0x00: Null: not used
  * 0x08: Code: code segment starts at 0 and extents for 4 gigabytes
  * 0x10: Data: data segment starts at 0 and extends for 4 gigabytes
  *		(overlays code)
  */
GDT:
NullDesc:	.word	0,0,0,0	# null descriptor - not used
CodeDesc:	.word	0xFFFF	# limit at maximum: (bits 15:0)
	.byte	0,0,0	# base at 0: (bits 23:0)
	.byte	0x9f	# present/priv level 0/code/conforming/readable
	.byte	0xcf	# page granular/default 32-bit/limit(bits 19:16)
	.byte	0	# base at 0: (bits 31:24)
DataDesc:	.word	0xFFFF	# limit at maximum: (bits 15:0)
	.byte	0,0,0	# base at 0: (bits 23:0)
	.byte	0x93	# present/priv level 0/data/expand-up/writeable
	.byte	0xcf	# page granular/default 32-bit/limit(bits 19:16)
	.byte	0	# base at 0: (bits 31:24)

/* Global Descriptor Table pointer
 *  contains 6-byte pointer information for LGDT
 */
GDTptr:	.word	0x17	# limit to three 8 byte selectors(null,code,data)
	.long 	BIOSRELOC+0x32	# GDT -- arrgh, gas again!

	/* step 4 relocate to final bootstrap address. */
reloc:
	movl	$ BIOSRELOC,%esi
	movl	$ RELOC,%edi
	movl	$512,%ecx
	rep
	movsb
 movl $0x60000,%esp
	pushl	$dodisk
	ret

	/* step 5 load remaining 15 sectors off disk */
dodisk:
	movl	$ IO_WD1+wd_seccnt,%edx
	movb	$ 15,%al
	outb	%al,%dx
	NOP
	movl	$ IO_WD1+wd_sector,%edx
	movb	$ 2,%al
	outb	%al,%dx
	NOP
	#outb(wdc+wd_cyl_lo, (cyloffset & 0xff));
	#outb(wdc+wd_cyl_hi, (cyloffset >> 8));
	#outb(wdc+wd_sdh, WDSD_IBM | (unit << 4));

	movl	$ IO_WD1+wd_command,%edx
	movb	$ WDCC_READ,%al
	outb	%al,%dx
	NOP
	cld

	/* check to make sure controller is not busy and we have data ready */
readblk:
	movl	$ IO_WD1+wd_status,%edx
	inb	%dx,%al
	NOP
	testb	$ WDCS_BUSY,%al
	jnz readblk
	testb	$ WDCS_DRQ,%al
	jz readblk

	/* read a block into final position in memory */

	movl	$ IO_WD1+wd_data,%edx
	movl	$ 256,%ecx
	.byte 0x66,0xf2,0x6d	# rep insw
	NOP

	/* need more blocks to be read in? */

	cmpl	$ RELOC+16*512-1,%edi
	jl	readblk

	/* for clever bootstrap, dig out boot unit and cylinder */
	
	movl	$ IO_WD1+wd_cyl_lo,%edx
	inb	%dx,%al
	NOP
	xorl	%ecx,%ecx
	movb	%al,%cl
	incl	%edx
	inb	%dx,%al		/* cyl_hi */
	NOP
	movb	%al,%ch
	pushl	%ecx		/* cyloffset */

	incl	%edx
	xorl	%eax,%eax
	inb	%dx,%al		/* sdh */
	andb	$0x10,%al	/* isolate unit # bit */
	shrb	$4,%al
	pushl	%eax		/* unit */

	/* wd controller is major device 0 */
	xorl	%eax,%eax
	pushl	%eax		/* bootdev */

	/* sorry, no flags at this point! */

	pushl	$ start
	ret	/* main (dev, unit, offset) */

ebootblkcode:

	/* remaining space usable for a disk label */
	
	.space	510-223		/* would be nice if .space 512-2-. worked */
	.word	0xaa55		/* signature -- used by BIOS ROM */

ebootblk: 			/* MUST BE EXACTLY 0x200 BIG FOR SURE */
E 1
