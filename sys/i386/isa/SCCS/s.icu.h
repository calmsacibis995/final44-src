h54370
s 00002/00002/00114
d D 8.1 93/06/11 15:53:45 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00006/00115
d D 5.9 92/05/11 16:58:29 bostic 9 8
c fix header
e
s 00015/00007/00106
d D 5.8 92/05/11 16:57:54 bostic 8 7
c Don't send an EOI to the slave interrupt controller if the interrupt
c came from the master; Insure that no hardware interrupts are allowed between
c deciding to return to user mode and the "iret".  This will be necessary for a
c future change that will fix floating point error reporting.  From Pace Willison
e
s 00011/00013/00102
d D 5.7 91/11/16 14:06:15 william 7 6
c partial fix of icu bugs.
e
s 00008/00032/00107
d D 5.6 91/05/09 21:34:01 william 6 5
c newer versions
e
s 00000/00000/00139
d D 5.5 91/01/08 19:13:19 william 5 4
c  npx.c wd.c wt.c
e
s 00091/00005/00048
d D 5.4 90/11/18 11:32:10 bill 4 3
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00020/00017/00033
d D 5.3 90/11/08 19:50:31 bill 3 2
c changes in the way interrupt code works
e
s 00007/00001/00043
d D 5.2 90/06/23 18:58:18 donahn 2 1
c improvements for interrupt latency by W. Jolitz
e
s 00044/00000/00000
d D 5.1 90/04/24 12:59:22 william 1 0
c date and time created 90/04/24 12:59:22 by william
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 6
 * %sccs.include.386.c%
E 6
I 6
D 7
 * %sccs.include.redist.c%
E 7
I 7
D 9
 * %sccs.include.386.c%
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
E 6
 *
 *	%W% (Berkeley) %G%
D 9
 */

/*
 * AT/386 Interrupt Control constants
 * W. Jolitz 8/89
E 9
 */

I 2
#ifndef	__ICU__
#define	__ICU__

E 2
#ifndef	LOCORE
I 4

/*
 * Interrupt "level" mechanism variables, masks, and macros
 */
E 4
extern	unsigned short	imen;	/* interrupt mask enable */
D 4
extern	unsigned short	cpl;	/* current priority level */
E 4
I 4
extern	unsigned short	cpl;	/* current priority level mask */
E 4

I 2
D 4
extern	unsigned short ttymask; /* things that get masked with spltty() */
extern	unsigned short biomask; /* things that get masked with splbio() */
I 3
extern	unsigned short netmask; /* things that get masked with splimp() */
E 4
I 4
extern	unsigned short highmask; /* group of interrupts masked with splhigh() */
extern	unsigned short ttymask; /* group of interrupts masked with spltty() */
extern	unsigned short biomask; /* group of interrupts masked with splbio() */
extern	unsigned short netmask; /* group of interrupts masked with splimp() */
E 4
E 3

E 2
#define	INTREN(s)	imen &= ~(s)
#define	INTRDIS(s)	imen |= (s)
I 3
#define	INTRMASK(msk,s)	msk |= (s)
I 4

#else

/*
 * Macro's for interrupt level priority masks (used in interrupt vector entry)
 */

D 6
/* Just mask this interrupt only */
#define	INTR(a)	\
	pushl	$0 ; \
	pushl	$ T_ASTFLT ; \
	pushal ; \
	push	%ds ; \
	push	%es ; \
	movw	$0x10, %ax ; \
	movw	%ax, %ds ; \
	movw	%ax,%es ; \
	incl	_cnt+V_INTR ; \
	movzwl	_cpl,%eax ; \
	pushl	%eax ; \
	pushl	$ a ; \
	orw	$ IRQ/**/a ,%ax ; \
	movw	%ax,_cpl ; \
	orw	_imen,%ax ; \
	NOP ; \
	outb	%al,$ IO_ICU1+1 ; \
	NOP ; \
	movb	%ah,%al ; \
	outb	%al,$ IO_ICU2+1	; \
	NOP	; \
	sti

E 6
/* Mask a group of interrupts atomically */
D 6
#define	INTRN(a,b) \
E 6
I 6
D 8
#define	INTR(unit,mask,offst) \
I 7
	cli ; \
E 7
E 6
	pushl	$0 ; \
I 7
	nop ; \
E 8
I 8
#define	INTR_HEAD(unit,mask,offst) \
	pushl	$ offst ; \
E 8
E 7
	pushl	$ T_ASTFLT ; \
I 7
D 8
	nop ; \
E 8
E 7
	pushal ; \
D 7
	push	%ds ; \
	push	%es ; \
E 7
I 7
D 8
	nop ; \
E 8
	movb	$0x20,%al ; \
I 8

#define INTR_TAIL(unit,mask,offst) \
E 8
	outb	%al,$ IO_ICU1 ; \
D 8
	outb	%al,$ IO_ICU2 ; \
E 8
	pushl	%ds ; \
	pushl	%es ; \
E 7
	movw	$0x10, %ax ; \
	movw	%ax, %ds ; \
	movw	%ax,%es ; \
	incl	_cnt+V_INTR ; \
I 6
	incl	_isa_intr + offst * 4 ; \
E 6
	movzwl	_cpl,%eax ; \
	pushl	%eax ; \
D 6
	pushl	$ a ; \
	orw	$ IRQ/**/a ,%ax ; \
	orw	b ,%ax ; \
E 6
I 6
	pushl	$ unit ; \
	orw	mask ,%ax ; \
E 6
	movw	%ax,_cpl ; \
	orw	_imen,%ax ; \
D 7
	NOP ; \
E 7
	outb	%al,$ IO_ICU1+1 ; \
D 7
	NOP ; \
E 7
	movb	%ah,%al ; \
	outb	%al,$ IO_ICU2+1	; \
D 7
	NOP	; \
I 6
	inb	$0x84,%al ; \
E 6
	sti
E 7
I 7
	sti ;
I 8

#define INTR1(unit,mask,offst) \
	INTR_HEAD(unit,mask,offst) \
	INTR_TAIL(unit,mask,offst)

#define INTR2(unit,mask,offst) \
	INTR_HEAD(unit,mask,offst) \
	outb	%al,$ IO_ICU2 ; \
	INTR_TAIL(unit,mask,offst)


E 8
E 7

/* Interrupt vector exit macros */

/* First eight interrupts (ICU1) */
D 6
#define	INTREXT1	\
E 6
I 6
#define	INTREXIT1	\
E 6
D 7
	movb	$0x20,%al ; \
	outb	%al,$ IO_ICU1 ; \
E 7
	jmp	doreti

/* Second eight interrupts (ICU2) */
D 6
#define	INTREXT2	\
E 6
I 6
#define	INTREXIT2	\
E 6
D 7
	movb	$0x20,%al ; \
	outb	%al,$ IO_ICU1 ; \
	outb	%al,$ IO_ICU2 ; \
E 7
	jmp	doreti

E 4
E 3
#endif

D 3
/* Interrupt enable bits */
#define	IRQ0	0x0001		/* highest priority - timer */
#define	IRQ1	0x0002
#define	IRQ8	0x0100
#define	IRQ9	0x0200
#define	IRQ2	IRQ9
#define	IRQ10	0x0400
#define	IRQ11	0x0800
#define	IRQ12	0x1000
#define	IRQ13	0x2000
#define	IRQ14	0x4000
#define	IRQ15	0x8000
#define	IRQ3	0x0008
#define	IRQ4	0x0010
#define	IRQ5	0x0020
#define	IRQ6	0x0040
#define	IRQ7	0x0080		/* lowest - parallel printer */
E 3
I 3
D 4
/* Interrupt enable bits -- in order of priority */
E 4
I 4
/*
 * Interrupt enable bits -- in order of priority
 */
E 4
#define	IRQ0		0x0001		/* highest priority - timer */
#define	IRQ1		0x0002
#define	IRQ_SLAVE	0x0004
#define	IRQ8		0x0100
#define	IRQ9		0x0200
#define	IRQ2		IRQ9
#define	IRQ10		0x0400
#define	IRQ11		0x0800
#define	IRQ12		0x1000
#define	IRQ13		0x2000
#define	IRQ14		0x4000
#define	IRQ15		0x8000
#define	IRQ3		0x0008
#define	IRQ4		0x0010
#define	IRQ5		0x0020
#define	IRQ6		0x0040
#define	IRQ7		0x0080		/* lowest - parallel printer */
I 4

/*
 * Interrupt Control offset into Interrupt descriptor table (IDT)
 */
#define	ICU_OFFSET	32		/* 0-31 are processor exceptions */
#define	ICU_LEN		16		/* 32-47 are ISA interrupts */
E 4
E 3

D 2

E 2
I 2
#endif	__ICU__
E 2
E 1
