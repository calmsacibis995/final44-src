h48607
s 00002/00002/00104
d D 8.1 93/06/11 15:54:17 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00025/00104
d D 5.9 93/06/10 21:59:24 cgd 9 8
c use inb and outb from locore
e
s 00029/00009/00100
d D 5.8 92/07/23 20:17:46 bostic 8 7
c Jolitz dropped this on the floor; I'm guessing by the dates that it's
c the latest one
e
s 00008/00006/00101
d D 5.7 91/05/09 20:35:53 william 7 6
c interim version, changes for net2 tape
e
s 00000/00000/00107
d D 5.6 91/01/08 19:13:27 william 6 5
c  npx.c wd.c wt.c
e
s 00020/00019/00087
d D 5.5 90/11/18 11:32:13 bill 5 4
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00002/00002/00104
d D 5.4 90/11/08 19:47:01 bill 4 3
c trvial
e
s 00080/00063/00026
d D 5.3 90/11/07 11:38:28 bill 3 2
c atio.h -> isa.h, complete revision
e
s 00009/00001/00080
d D 5.2 90/11/07 11:36:44 bill 2 1
c intermediate version
e
s 00081/00000/00000
d D 5.1 90/04/24 12:59:08 william 1 0
c date and time created 90/04/24 12:59:08 by william
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
D 7
 * %sccs.include.noredist.c%
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */

/*
D 3
 * AT bus specific definitions.
E 3
I 3
 * ISA Bus conventions
E 3
 */
I 3

E 3
I 2
D 8
#ifndef LOCORE
E 8
I 8
D 9
/*#ifndef LOCORE
E 9
I 9
#ifndef LOCORE
E 9
E 8
I 3
D 4
unsigned char inb() ;	/* XXX */
extern outb();
E 4
I 4
unsigned char inb(), rtcin();
void outb();
E 4
D 8
#endif
E 8
I 8
D 9
#endif*/
E 8
E 3
E 2

I 8
#ifndef LOCORE
unsigned char rtcin();
E 8
D 3
#define Rd(s) ({u_char rtn; u_short ioa; \
	ioa = (s); \
	asm volatile ("movw %1,%%dx; nop ; in %%dx,%%al ; nop ; movb %%al,%0" \
		: "=g" (rtn) \
		: "g" (ioa) \
		: "ax", "dx"); \
	rtn; \
})
E 3

I 8
#define inb(io) ({u_short iop; register u_char rtn; \
	iop = (io); \
	asm (" movl %1,%%edx; inb %%al,%%dx; movzbl %%al,%0 " \
		: "=r" (rtn) \
		: "g" (iop) \
		: "ax,dx"); \
	rtn; \
})

#define outb(io, v) ({u_short iop; u_char val; \
	iop = (io); \
	val = (v); \
	asm (" movl %1,%%edx; movl %0,%%eax; outb %%dx,%%al " \
		:  \
		: "g" (val) \
		: "g" (iop) \
		: "ax,dx"); \
})

E 9
#endif
I 9

E 9
E 8
D 3
#define Wr(s,n) ({u_char val; u_short ioa; \
	ioa = (s); \
	val = (n); \
	asm volatile ("movb %1,%%al; movw %0,%%dx; nop; out %%al,%%dx ; nop" \
		: /* nothing returned */ \
		: "g" (ioa), "g" (val) \
		: "ax", "dx"); \
})
E 3
I 3
/*
 * Input / Output Port Assignments
 */
E 3

I 3
#ifndef IO_BEGIN
#define	IO_ISABEGIN	0x000		/* 0x000 - Beginning of I/O Registers */
E 3

D 3
#define rdw(s) ({u_short rtn; u_short ioa; \
	ioa = (s); \
	asm volatile ("movw %1,%%dx; nop ; in %%dx,%%ax ; nop ; movw %%ax,%0" \
		: "=g" (rtn) \
		: "g" (ioa) \
		: "ax", "dx"); \
	rtn; \
})
E 3
I 3
		/* CPU Board */
D 5
#define IO_DMA0		0x000		/* 8237A DMA Controller #1 */
#define IO_ICU0		0x020		/* 8259A Interrupt Controller #1 */
#define IO_TIMER0	0x040		/* 8252 Timer #1 */
#define IO_TIMER1	0x048		/* 8252 Timer #2 */
E 5
I 5
#define IO_DMA1		0x000		/* 8237A DMA Controller #1 */
#define IO_ICU1		0x020		/* 8259A Interrupt Controller #1 */
#define IO_TIMER1	0x040		/* 8252 Timer #1 */
#define IO_TIMER2	0x048		/* 8252 Timer #2 */
E 5
#define IO_KBD		0x060		/* 8042 Keyboard */
#define IO_RTC		0x070		/* RTC */
#define IO_NMI		IO_RTC		/* NMI Control */
#define IO_DMAPG	0x080		/* DMA Page Registers */
D 5
#define IO_ICU1		0x0A0		/* 8259A Interrupt Controller #2 */
#define IO_DMA1		0x0C0		/* 8237A DMA Controller #2 */
E 5
I 5
#define IO_ICU2		0x0A0		/* 8259A Interrupt Controller #2 */
#define IO_DMA2		0x0C0		/* 8237A DMA Controller #2 */
E 5
#define IO_NPX		0x0F0		/* Numeric Coprocessor */
E 3

D 3
#define wrw(s,n) ({u_short val; u_short ioa; \
	ioa = (s); \
	val = (n); \
	asm volatile ("movw %1,%%ax; movw %0,%%dx; nop;  out %%ax,%%dx; nop" \
		: /* nothing returned */ \
		: "g" (ioa), "g" (val) \
		: "ax", "dx"); \
})
E 3
I 3
		/* Cards */
					/* 0x100 - 0x16F Open */
E 3

D 3
#define Outsw(s,a, n) ({short *addr; u_short ioa; int cnt,rtn; \
	ioa = (s); \
	addr = (a); \
	cnt = (n); \
	asm volatile ("movw %1,%%dx; movl %2,%%esi; movl %3,%%ecx; cld; nop; .byte 0x66,0xf2,0x6f; nop ; movl %%esi,%0" \
		: "=g" (rtn) \
		: "g" (ioa), "g" (addr), "g" (cnt) \
		: "si", "dx", "cx"); \
	rtn; \
})
#define Insw(s,a, n) ({short  *addr; u_short ioa; int cnt,rtn; \
	ioa = (s); \
	addr = (a); \
	cnt = (n); \
	asm volatile ("movw %1,%%dx; movl %2,%%edi; movl %3,%%ecx; cld; nop; .byte 0x66,0xf2,0x6d; nop ; movl %%edi,%0" \
		: "=g" (rtn) \
		: "g" (ioa), "g" (addr), "g" (cnt)  \
		: "di", "dx", "cx"); \
	rtn; \
})
E 3
I 3
D 5
#define IO_WD1		0x170		/* Secondary Fixed Disk Controller */
E 5
I 5
#define IO_WD2		0x170		/* Secondary Fixed Disk Controller */
E 5
E 3

D 3
unsigned char inb() ;
extern outb();
I 2
#endif
E 3
I 3
					/* 0x178 - 0x1EF Open */
E 3
E 2

D 2
#define IO_KBD1	0x60		/* keyboard */
E 2
I 2
D 3
#define IO_KBD	0x60			/* keyboard */
E 3
I 3
D 5
#define IO_WD0		0x1f0		/* Primary Fixed Disk Controller */
E 5
I 5
#define IO_WD1		0x1f0		/* Primary Fixed Disk Controller */
E 5
#define IO_GAME		0x200		/* Game Controller */
E 3
E 2

D 3
#define IO_WD0	0x1f0			/* primary base i/o address */
#define IO_WD1	0x170			/* secondary base i/o address */
E 3
I 3
					/* 0x208 - 0x277 Open */
E 3
I 2

D 3
#define IO_FD0	0x3f2			/* primary base i/o address */
#define IO_FD1	0x372			/* secondary base i/o address */
E 3
I 3
D 5
#define IO_LPT1		0x278		/* Parallel Port #2 */
E 5
I 5
#define IO_LPT2		0x278		/* Parallel Port #2 */
E 5
E 3

D 3
#define IO_COM0	0x3f8			/* COM1 i/o address */
#define IO_COM1	0x2f8			/* COM2 i/o address */
E 3
I 3
					/* 0x280 - 0x2F7 Open */

D 5
#define IO_COM1		0x2f8		/* COM2 i/o address */
E 5
I 5
#define IO_COM2		0x2f8		/* COM2 i/o address */
E 5

					/* 0x300 - 0x36F Open */

D 5
#define IO_FD1		0x370		/* secondary base i/o address */
#define IO_LPT0		0x378		/* Parallel Port #1 */
E 5
I 5
#define IO_FD2		0x370		/* secondary base i/o address */
#define IO_LPT1		0x378		/* Parallel Port #1 */
E 5

					/* 0x380 - 0x3AF Open */

#define IO_MDA		0x3B0		/* Monochome Adapter */
D 5
#define IO_LPT2		0x3BC		/* Monochome Adapter Printer Port */
E 5
I 5
#define IO_LPT3		0x3BC		/* Monochome Adapter Printer Port */
E 5
#define IO_VGA		0x3C0		/* E/VGA Ports */
#define IO_CGA		0x3D0		/* CGA Ports */

					/* 0x3E0 - 0x3EF Open */

D 5
#define IO_FD0		0x3f0		/* primary base i/o address */
#define IO_COM0		0x3f8		/* COM1 i/o address */
E 5
I 5
#define IO_FD1		0x3f0		/* primary base i/o address */
#define IO_COM1		0x3f8		/* COM1 i/o address */
E 5

#define	IO_ISAEND	0x3FF		/* - 0x3FF End of I/O Registers */
#endif	IO_ISABEGIN

/*
 * Input / Output Memory Physical Addresses
 */

D 5
#ifdef	IOM_BEGIN
E 5
I 5
#ifndef	IOM_BEGIN
E 5
D 7
#define	IOM_BEGIN	0xa0000		/* Start of I/O Memory "hole" */
#define	IOM_END		0xFFFFF		/* End of I/O Memory "hole" */
E 7
I 7
D 8
#define	IOM_BEGIN	0x0a0000		/* Start of I/O Memory "hole" */
#define	IOM_END		0x100000		/* End of I/O Memory "hole" */
#define	IOM_SIZE	(IOM_END - IOM_BEGIN)
E 8
I 8
#define	IOM_BEGIN	0xa0000		/* Start of I/O Memory "hole" */
#define	IOM_END		0xFFFFF		/* End of I/O Memory "hole" */
E 8
E 7
#endif	IOM_BEGIN

/*
 * RAM Physical Address Space (ignoring the above mentioned "hole")
 */

D 5
#ifdef	RAM_BEGIN
E 5
I 5
#ifndef	RAM_BEGIN
E 5
D 7
#define	RAM_BEGIN	0x000000	/* Start of RAM Memory */
D 5
#define	IOM_END		0xFFFFFF	/* End of RAM Memory */
E 5
I 5
#define	RAM_END		0xFFFFFF	/* End of RAM Memory */
E 5
#endif	IOM_BEGIN
E 7
I 7
D 8
#define	RAM_BEGIN	0x0000000	/* Start of RAM Memory */
#define	RAM_END		0x1000000	/* End of RAM Memory */
#define	RAM_SIZE	(RAM_END - RAM_BEGIN)
#endif	RAM_BEGIN
E 8
I 8
#define	RAM_BEGIN	0x000000	/* Start of RAM Memory */
#define	RAM_END		0xFFFFFF	/* End of RAM Memory */
#endif	IOM_BEGIN
E 8
E 7

/*
 * Oddball Physical Memory Addresses
 */
D 5

E 5
I 5
#ifndef	COMPAQ_RAMRELOC
E 5
#define	COMPAQ_RAMRELOC	0x80c00000	/* Compaq RAM relocation/diag */
#define	COMPAQ_RAMSETUP	0x80c00002	/* Compaq RAM setup */
#define	WEITEK_FPU	0xC0000000	/* WTL 2167 */
#define	CYRIX_EMC	0xC0000000	/* Cyrix EMC */
I 5
#endif	COMPAQ_RAMRELOC
E 5
E 3
E 2
E 1
