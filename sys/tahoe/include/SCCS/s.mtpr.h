h38729
s 00003/00001/00043
d D 7.3 92/02/20 15:18:13 sklower 4 3
c mtpr.h is vax and tahoe specific, have net files which need it for spl()
c include cpu.h instead.
e
s 00009/00002/00035
d D 7.2 91/05/08 14:23:27 bostic 3 2
c new copyright; att/bsd/shared
e
s 00004/00002/00033
d D 7.1 88/05/21 18:36:07 karels 2 1
c bring up to revision 7 for tahoe release
e
s 00035/00000/00000
d D 1.1 86/01/05 18:46:22 sam 1 0
c date and time created 86/01/05 18:46:22 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
/*	mtpr.h	4.5	82/11/05	*/
E 2
I 2
D 3
/*
E 3
I 3
/*-
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
 *
E 3
 *	%W% (Berkeley) %G%
D 3
 *	from mtpr.h	4.5	82/11/05
E 3
 */
E 2

I 4
#ifndef _MTPR_H__
#define _MTPR_H_
E 4
/*
 * TAHOE processor register numbers
 */
D 4

E 4
#define	SBR	0x0		/* system base register */
#define	SLR	0x1		/* system length register */
#define	P0BR	0x2		/* p0 base register */
#define	P0LR	0x3		/* p0 length register */
#define	P1BR	0x4		/* p1 base register */
#define	P1LR	0x5		/* p1 length register */
#define	P2BR	0x6		/* p2 base register */
#define	P2LR	0x7		/* p2 length register */
#define	IPL	0x8 		/* interrupt priority level */
#define	MME  	0x9		/* memory management enable */
#define	TBIA	0xa		/* translation buffer invalidate all */
#define	TBIS	0xb		/* translation buffer invalidate single */
#define DCK	0xc		/* data cache key */
#define CCK	0xd		/* code cache key */
#define	PCBB	0xe		/* process control block base */
#define	ISP	0xf		/* interrupt stack pointer */
#define	SIRR	0x10		/* software interrupt request */
#define	SISR	0x11		/* software interrupt summary */
#define	SCBB	0x12		/* system control block base */
#define	KSP	0x13		/* kernelack pointer */
#define	USP	0x14		/* user stack pointer */
#define CPMDCB	0x15		/* CP master DCM pointer */
#define PACC	0x17		/* purge all code cache */
#define P1DC	0x18		/* purge one data cache */
#define PADC	0x19		/* purge all data cache */
#define HISR	0x1a		/* hardware interrupt summery register */
#define DCR	0x1b		/* diagnostic control register */
#define PDCS	0x1c		/* purge data cache slot */
I 4
#endif /* !_MTPR_H_ */
E 4
E 1
