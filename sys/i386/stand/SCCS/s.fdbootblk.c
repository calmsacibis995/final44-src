h01568
s 00002/00002/00223
d D 8.1 93/06/11 15:57:59 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00027/00197
d D 7.3 92/02/05 10:44:35 bostic 3 2
c commented, no functional changes; from Christos Zoulas
e
s 00000/00069/00224
d D 7.2 91/05/04 15:30:23 bostic 2 1
c fix from Bill -- remove #ifdef notdef sections
e
s 00293/00000/00000
d D 7.1 91/04/28 17:15:43 william 1 0
c date and time created 91/04/28 17:15:43 by william
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
D 3
 * fdbootblk.s:
 *	Written 10/6/90 by William F. Jolitz
 *	Initial block boot for AT/386 with typical stupid NEC controller
 *	Works only with 3.5 inch diskettes that have 16 or greater sectors/side
 *
 *	Goal is to read in sucessive 7.5Kbytes of bootstrap to
 *	execute.
 *
 *	No attempt is made to handle disk errors.
E 3
I 3
 * Initial block boot for AT/386 with typical stupid NEC controller.  Works
 * only with 3.5 inch diskettes that have 16 or greater sectors/side.  Goal
 * is to read in sucessive 7.5Kbytes of bootstrap to execute.  No attempt
 * is made to handle disk errors.
E 3
 */
D 3
/*#include "/sys/i386/isa/isa.h"
#include "/sys/i386/isa/fdreg.h"*/
#define	NOP	jmp 1f ; nop ; 1:
#define BIOSRELOC	0x7c00
#define	start	0x70400
E 3
I 3
#define	NOP		jmp 1f ; nop ; 1:
#define	BIOSRELOC	0x7c00
#define	start		0x70400
E 3

I 3
/* Gas does not know about 16 bit opcodes... */

E 3
	/* step 0 force descriptors to bottom of address space */

D 3
	.byte 0xfa,0xb8,0x30,0x00,0x8e,0xd0,0xbc,0x00,0x01 #ll fb
E 3
I 3
	.byte 	0xfa			# cli
	.byte 	0xb8, 0x30, 0x00	# mov $0x0030, %ax
	.byte 	0x8e, 0xd0 		# mov %ax, %ss
	.byte 	0xbc, 0x00, 0x01  	# mov $0x0100, %sp
E 3

	xorl	%eax,%eax
	movl	%ax,%ds
	movl	%ax,%es

	/* step 1 load new descriptor table */

D 3
	.byte 0x2E,0x0F,1,0x16
	.word	BIOSRELOC+0x4a	#GDTptr
	# word aword cs lgdt GDTptr
E 3
I 3
	.byte 	0x2e			# seg cs
	.byte 	0x0f, 0x01, 0x16	# lgdt DS:d16
	.word	BIOSRELOC + 0x4a	# [BIOSRELOC + GDTptr]
E 3

	/* step 2 turn on protected mode */

	smsw	%ax
	orb	$1,%al
	lmsw	%ax
	jmp	1f
	nop

I 3
 1:
E 3
	/* step 3  reload segment descriptors */

D 3
 1:
E 3
	xorl	%eax,%eax
	movb	$0x10,%al
	movl	%ax,%ds
	movl	%ax,%es
	movl	%ax,%ss
	word
D 3
	ljmp	$0x8,$ BIOSRELOC+0x59	/* would be nice if .-RELOC+0x7c00 worked */
E 3
I 3
	ljmp	$0x8, $ BIOSRELOC + 0x59 # [BIOSRELOC + reloc]
E 3

D 3
 /* Global Descriptor Table contains three descriptors:
E 3
I 3
 /* 
  * Global Descriptor Table contains three descriptors:
E 3
  * 0x00: Null: not used
  * 0x08: Code: code segment starts at 0 and extents for 4 gigabytes
  * 0x10: Data: data segment starts at 0 and extends for 4 gigabytes
  *		(overlays code)
  */
GDT:
D 3
NullDesc:	.word	0,0,0,0	# null descriptor - not used
CodeDesc:	.word	0xFFFF	# limit at maximum: (bits 15:0)
E 3
I 3
NullDsc:.word	0,0,0,0	# null descriptor - not used
CodeDsc:.word	0xFFFF	# limit at maximum: (bits 15:0)
E 3
	.byte	0,0,0	# base at 0: (bits 23:0)
	.byte	0x9f	# present/priv level 0/code/conforming/readable
	.byte	0xcf	# page granular/default 32-bit/limit(bits 19:16)
	.byte	0	# base at 0: (bits 31:24)
D 3
DataDesc:	.word	0xFFFF	# limit at maximum: (bits 15:0)
E 3
I 3
DataDsc:.word	0xFFFF	# limit at maximum: (bits 15:0)
E 3
	.byte	0,0,0	# base at 0: (bits 23:0)
	.byte	0x93	# present/priv level 0/data/expand-up/writeable
	.byte	0xcf	# page granular/default 32-bit/limit(bits 19:16)
	.byte	0	# base at 0: (bits 31:24)

D 3
/* Global Descriptor Table pointer
E 3
I 3
/* 
 * Global Descriptor Table pointer
E 3
 *  contains 6-byte pointer information for LGDT
 */
GDTptr:	.word	0x17	# limit to three 8 byte selectors(null,code,data)
D 3
	.long 	BIOSRELOC+0x32	# GDT -- arrgh, gas again!
readcmd: .byte 0xe6,0,0,0,0,2,18,0x1b,0xff
E 3
I 3
	.long 	BIOSRELOC + 0x32	# [BIOSRELOC + GDT]

readcmd: .byte 0xe6, 0x00, 0x00, 0x00, 0x00, 0x02, 18, 0x1b, 0xff
E 3

	/* step 4 relocate to final bootstrap address. */
reloc:
	movl	$ BIOSRELOC,%esi
	movl	$ RELOC,%edi
	movl	$512,%ecx
	rep
	movsb
	pushl	$dodisk
	ret

	/* step 5 load remaining 15 sectors off disk */
dodisk:
	movl	$0x70200,%edi
	xorl	%ebx,%ebx
	incb	%bl
	incb	%bl
D 2
#ifdef notdef
	movb	$0x11,%al
	outb	%al,$0x20
	NOP
	movb	$32,%al
	outb	%al,$0x21
	NOP
	movb	$4,%al
	outb	%al,$0x21
	NOP
	movb	$1,%al
	outb	%al,$0x21
	NOP
#endif
E 2
	movb	$0x20,%al	# do a eoi
	outb	%al,$0x20

	NOP
	movb	$0x07,%al
	outb	%al,$0x21
	NOP
 8:
	movb	%bl,readcmd+4
	movl	%edi,%ecx

	/* Set read/write bytes */
	xorl	%edx,%edx
	movb	$0x0c,%dl	# outb(0xC,0x46); outb(0xB,0x46);
	movb	$0x46,%al
	outb	%al,%dx
	NOP
	decb	%dx
	outb	%al,%dx

	/* Send start address */
	movb	$0x04,%dl	# outb(0x4, addr);
	movb	%cl,%al
	outb	%al,%dx
	NOP
	movb	%ch,%al		# outb(0x4, addr>>8);
	outb	%al,%dx
	NOP
	rorl	$8,%ecx		# outb(0x81, addr>>16);
	movb	%ch,%al
	outb	%al,$0x81
	NOP

	/* Send count */
	movb	$0x05,%dl	# outb(0x5, 0);
	xorl	%eax,%eax
	outb	%al,%dx
	NOP
	movb	$2,%al		# outb(0x5,2);
	outb	%al,%dx
	NOP

	/* set channel 2 */
	# movb	$2,%al		# outb(0x0A,2);
	outb	%al,$0x0A
	NOP

	/* issue read command to fdc */
	movw	$0x3f4,%dx
	movl	$readcmd,%esi
	xorl	%ecx,%ecx
	movb	$9,%cl

 2:	inb	%dx,%al
	NOP
	testb	$0x80,%al
	jz 2b

	incb	%dx
	movl	(%esi),%al
	outb	%al,%dx
	NOP
	incl	%esi
	decb	%dx
	loop	 2b

	/* watch the icu looking for an interrupt signalling completion */
	xorl	%edx,%edx
	movb	$0x20,%dl
 2:	movb	$0xc,%al
	outb	%al,%dx
	NOP
	inb	%dx,%al
	NOP
D 2
#ifdef notdef
	call	px
#endif
E 2
	andb	$0x7f,%al
	cmpb	$6,%al
	jne	2b
	movb	$0x20,%al	# do a eoi
	outb	%al,%dx
	NOP

	movl	$0x3f4,%edx
	xorl	%ecx,%ecx
	movb	$7,%cl
 2:	inb	%dx,%al
	NOP
	andb	$0xC0,%al
	cmpb	$0xc0,%al
	jne	2b
	incb	%dx
	inb	%dx,%al
	decb	%dx
	loop	2b

D 2
#ifdef notdef
	inb	$0x61,%al
	NOP
	orb	$3,%al
	outb	%al,$0x61
	NOP
#endif

E 2
	/* extract the status bytes after the read. must we do this? */
	addw	$0x200,%edi	# next addr to load to
	incb	%bl
D 2
#ifdef notdef
 movb %bl,%al
 call px
#endif
E 2
	cmpb	$16,%bl
	jle	8b
	
	/* for clever bootstrap, dig out boot unit and cylinder */
	pushl	$0
	pushl	$0
	
	/* fd controller is major device 2 */
	pushl	$2	/* dev */

	/* sorry, no flags at this point! */

	pushl $	start
	ret	/* main (dev, unit, off) */

D 2
#ifdef notdef
hextab:	.ascii	"0123456789abcdef"
curs:	.long	0xb8000
kbc:	.byte 0

px:
	pushal
	movl	curs,%edi
	movl	%eax,%ebx
	call	phd
	movl	%ebx,%eax
	shrl	$4,%eax
	call	phd
	movb	$0xe,%ah
	movb	$32,%al
	movw	%ax,(%edi)
	# movw	$(0xe<<8)+' ',(%edi)
	incl	%edi
	incl	%edi
	movl	%edi,curs

2:	inb	$0x60,%al
	NOP
	cmpb	%al,kbc
	je	2b
	movb	%al,kbc
	
	popal
	ret

phd:	
	andl	$0xf,%eax
	movb	hextab(%eax),%al
	movb	$0xe,%ah
	movw	%ax,(%edi)
	incl	%edi
	incl	%edi
	ret
#endif
	
E 2
ebootblkcode:

	/* remaining space usable for a disk label */
	
	.space	510-310		/* would be nice if .space 512-2-. worked */
	.word	0xaa55		/* signature -- used by BIOS ROM */

ebootblk: 			/* MUST BE EXACTLY 0x200 BIG FOR SURE */
E 1
