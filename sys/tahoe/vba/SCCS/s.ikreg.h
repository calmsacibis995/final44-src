h01116
s 00001/00011/00078
d D 7.3 90/06/28 22:27:30 bostic 5 4
c new copyright notice
e
s 00015/00000/00074
d D 7.2 88/09/16 09:37:27 bostic 4 3
c add appropriate copyright notices
e
s 00003/00001/00071
d D 7.1 88/05/21 18:33:02 karels 3 2
c bring up to revision 7 for tahoe release
e
s 00044/00047/00028
d D 1.2 86/12/11 08:28:19 sam 2 1
c put tacbs back; delete fixed interrupt vector base and address modifier definition
e
s 00075/00000/00000
d D 1.1 86/11/29 12:09:53 sam 1 0
c date and time created 86/11/29 12:09:53 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
I 4
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
D 5
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
E 4
 *	%W% (Berkeley) %G%
 */
E 3

/*
 * IKON DR-11W register definitions.
 */
D 2
struct  ikdevice {
        u_short ik_csr;         /* control status register */
        u_short ik_data;        /* data in/out register */
        u_char  ik_mod;         /* address modifier */
        u_char  ik_vec;         /* interrupt vector */
        u_short ik_pulse;       /* pulse commands (w) */
        u_short ik_fill[5];
        u_short ik_balo;        /* low word of dma beginning address (w) */
        u_short ik_wc;          /* dma word count */
        u_short ik_calo;        /* low word of dma current address (r) */
        u_short ik_fill1;
        u_short ik_bahi;        /* high word of dma beginning address (w) */
        u_short ik_fill2;
        u_short ik_cahi;        /* high word of dma current address (r) */
E 2
I 2
struct	ikdevice {
	u_short ik_csr;		/* control status register */
	u_short ik_data;	/* data in/out register */
	u_char	ik_mod;		/* address modifier */
	u_char	ik_vec;		/* interrupt vector */
	u_short ik_pulse;	/* pulse commands (w) */
	u_short ik_fill[5];
	u_short ik_balo;	/* low word of dma beginning address (w) */
	u_short ik_wc;		/* dma word count */
	u_short ik_calo;	/* low word of dma current address (r) */
	u_short ik_fill1;
	u_short ik_bahi;	/* high word of dma beginning address (w) */
	u_short ik_fill2;
	u_short ik_cahi;	/* high word of dma current address (r) */
E 2
};

/*
 * CSR control definitions (write-only).
 */
D 2
#define IKCSR_GO        0x0001          /* start dma */
#define IKCSR_FNC1      0x0002          /* function bit 1 */
#define IKCSR_FNC2      0x0004          /* function bit 2 */
#define IKCSR_FNC3      0x0008          /* function bit 3 */
E 2
I 2
#define IKCSR_GO	0x0001		/* start dma */
#define IKCSR_FNC1	0x0002		/* function bit 1 */
#define IKCSR_FNC2	0x0004		/* function bit 2 */
#define IKCSR_FNC3	0x0008		/* function bit 3 */
E 2
/* bits 4-5 are unused */
D 2
#define IKCSR_IENA      0x0040          /* enable/disable interrupts */
E 2
I 2
#define IKCSR_IENA	0x0040		/* enable/disable interrupts */
E 2
/* bit 7 is unused */
D 2
#define IKCSR_CYCLE     0x0100          /* force dma to cycle */
E 2
I 2
#define IKCSR_CYCLE	0x0100		/* force dma to cycle */
E 2
/* bits 9-11 are unused */
D 2
#define IKCSR_MCLR      0x1000          /* master clear board */
#define IKCSR_RPERR     0x2000          /* reset parity error */
#define IKCSR_RATTF     0x4000          /* reset attention */
#define IKCSR_RDMAF     0x8000          /* reset dma completion */
E 2
I 2
#define IKCSR_MCLR	0x1000		/* master clear board */
#define IKCSR_RPERR	0x2000		/* reset parity error */
#define IKCSR_RATTF	0x4000		/* reset attention */
#define IKCSR_RDMAF	0x8000		/* reset dma completion */
E 2

/*
 * CSR status definitions (read-only).
 */
D 2
#define IKCSR_DEV       0x0001          /* device flag (0 = 10083, 1 = 10077) */
E 2
I 2
#define IKCSR_DEV	0x0001		/* device flag (0 = 10083, 1 = 10077) */
E 2
/* bits 1-3 reflect the function latch state */
D 2
#define IKCSR_TIMO      0x0010          /* bus timeout during dma */
#define IKCSR_BERR      0x0020          /* bus error during dma */
E 2
I 2
#define IKCSR_TIMO	0x0010		/* bus timeout during dma */
#define IKCSR_BERR	0x0020		/* bus error during dma */
E 2
/* bit 6 reflects interrupt enable state */
D 2
#define IKCSR_READY     0x0080          /* device ready for next command */
E 2
I 2
#define IKCSR_READY	0x0080		/* device ready for next command */
E 2
/* bit 8 should be 0 */
D 2
#define IKCSR_STATC     0x0200          /* status bit C */
#define IKCSR_STATB     0x0400          /* status bit B */
#define IKCSR_STATA     0x0800          /* status bit A */
#define IKCSR_PERR      0x1000          /* parity error during pi/o or dma */
#define IKCSR_ATTN      0x2000          /* current state of attention bit */
#define IKCSR_ATTF      0x4000          /* latched attention t-f transition */
#define IKCSR_DMAF      0x8000          /* dma completed or terminated */
E 2
I 2
#define IKCSR_STATC	0x0200		/* status bit C */
#define IKCSR_STATB	0x0400		/* status bit B */
#define IKCSR_STATA	0x0800		/* status bit A */
#define IKCSR_PERR	0x1000		/* parity error during pi/o or dma */
#define IKCSR_ATTN	0x2000		/* current state of attention bit */
#define IKCSR_ATTF	0x4000		/* latched attention t-f transition */
#define IKCSR_DMAF	0x8000		/* dma completed or terminated */
E 2

#define IKCSR_BITS \
"\020\1DEV\2FNC1\3FNC2\4FNC3\5TIMO\6BERR\7IENA\10READY\12STATC\13STATB\14STATA\
\15PERR\16ATTN\17ATTF\20DMAF"

D 2
#define IKMOD_STD       0x1             /* std memory map address modifier */
#define IKVEC_BASE      0x9c            /* base of reserved interrupt vectors */

E 2
/*
 * Pulse command register definitions (write-only).
 */
D 2
#define IKPULSE_GO      0x0001          /* enable dma */
#define IKPULSE_FNC2    0x0004          /* pulse function bit 1 */
#define IKPULSE_RIENA   0x0020          /* reset IKCSR_IENA */
#define IKPULSE_SIENA   0x0040          /* set IKCSR_IENA */
#define IKPULSE_CYCL    0x0100          /* force dma to cycle */
#define IKPULSE_MCLR    0x1000          /* initialize interface */
#define IKPULSE_RPERR   0x2000          /* reset IKCSR_PERR */
#define IKPULSE_RATTF   0x4000          /* reset IKCSR_ATTF */
#define IKPULSE_RDMAF   0x8000          /* reset IKCSR_DMAF */
E 2
I 2
#define IKPULSE_GO	0x0001		/* enable dma */
#define IKPULSE_FNC2	0x0004		/* pulse function bit 1 */
#define IKPULSE_RIENA	0x0020		/* reset IKCSR_IENA */
#define IKPULSE_SIENA	0x0040		/* set IKCSR_IENA */
#define IKPULSE_CYCL	0x0100		/* force dma to cycle */
#define IKPULSE_MCLR	0x1000		/* initialize interface */
#define IKPULSE_RPERR	0x2000		/* reset IKCSR_PERR */
#define IKPULSE_RATTF	0x4000		/* reset IKCSR_ATTF */
#define IKPULSE_RDMAF	0x8000		/* reset IKCSR_DMAF */
E 2
E 1
