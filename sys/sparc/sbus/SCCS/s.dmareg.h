h13053
s 00002/00002/00106
d D 8.1 93/06/11 15:14:39 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00055/00032/00053
d D 7.4 93/04/27 07:40:06 torek 4 3
c update for dma chip rev 3, not that we have any yet
e
s 00002/00002/00083
d D 7.3 93/04/20 19:29:02 torek 3 2
c spelling
e
s 00005/00000/00080
d D 7.2 92/07/21 16:52:04 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00080/00000/00000
d D 7.1 92/07/13 00:44:04 torek 1 0
c date and time created 92/07/13 00:44:04 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
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
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: dmareg.h,v 1.4 92/06/17 06:59:33 torek Exp $ (LBL)
E 3
I 3
D 4
 * from: $Header: dmareg.h,v 1.5 92/11/26 02:28:08 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: dmareg.h,v 1.6 93/04/27 14:39:17 torek Exp $ (LBL)
E 4
E 3
 */

/*
 * Sun-4c Sbus slot 0 DMA registers.
I 4
 *
 * Note that the dma_addr on the rev 1 gate array cannot increment
 * across a 16 MB boundary (the counter is only 24 bits wide; the
 * top 8 bits are simply latched).
E 4
 */
struct dmareg {
	u_long	dma_csr;	/* control/status register */
	u_long	dma_addr;	/* address (virtual: is fed to MMU) */
	u_long	dma_bc;		/* byte count (not used) */
	u_long	dma_diag;	/* diagnostic register (not used) */
};

/*
 * Bits in dma_csr.
I 4
 * DMA chip revision numbers are confusing (rev 3 = `DMA2'?!).
 * Not my fault; we just live with what they give us....
E 4
 *
 * Notes in [brackets]:
D 4
 *	1: not self-clearing, must be reset after being set.
 *	2: `drain' is like Unibus `bdp purge', i.e., it tells
E 4
I 4
 *	1: used this way in rev 1 (`DMA') chips.
 *	2: used this way in rev 2 (`DMA+') chips.
 *	3: used this way in rev 3 (`DMA2') chips.
 *	R: not self-clearing, must be reset after being set.
 *	D: `drain' is like Unibus `bdp purge', i.e., it tells
E 4
 *	   the chip to finish up, because there is no more data
D 4
 *	   going into the buffer register.  Needed only in rev
 *	   1 dma chips.  Self-clearing (hence write-only).
 *	3: only in rev 1 dma chips.
 *	4: only in rev 2 dma chips.
 *	5: also enables scsi interrupts.
E 4
I 4
 *	   going into the buffer register.  Supposed to be needed
 *	   only in rev 1, but apparently needed or harmless in all
 *	   revs.  Self-clearing (hence write-only).
 *	I: also enables scsi interrupts.
E 4
 */
#define	DMA_REV(csr)	(((csr) >> 28) & 0xf)	/* device id field */
D 4
#define	DMAREV_1	0x8		/* device id = rev 1 DMA */
#define	DMAREV_2	0x9		/* device id = rev 2 DMA */
E 4
I 4
#define	DMAREV_1	0x8		/* rev 1 DMA gate array */
#define	DMAREV_2	0x9		/* rev 2 DMA gate array (`DMA+') */
#define	DMAREV_3	0xa		/* rev 3 DMA gate array (`DMA2') */
E 4

D 4
#define	DMA_1ZERO	0x0fff0000	/* unused; reads as zero [3] */
#define	DMA_NAL		0x08000000	/* next address loaded [4] (ro) */
#define	DMA_AL		0x04000000	/* address loaded [4] (ro) */
#define	DMA_ON		0x02000000	/* working [4] (ro) */
#define	DMA_NAE		0x01000000	/* next-address enable [4] (rw) */
#define	DMA_DTCI	0x00800000	/* disable DMA_TC intr [4] (rw) */
#define	DMA_TURBO	0x00400000	/* faster 53C90A mode [4] (rw) */
#define	DMA_LERR	0x00200000	/* LANCE error [4] (ro) */
#define	DMA_ALE		0x00100000	/* LANCE addr latch ena [4] (rw) */
#define	DMA_2ZERO	0x000f0000	/* unused; reads as zero [4] */
#define	DMA_ILACC	0x00008000	/* set for new AMD ethernet chip */
#define	DMA_TC		0x00004000	/* terminal count: dma_bc ran out */
E 4
I 4
#define	DMA_1ZERO	0x0fff0000	/* unused; reads as zero [1] */
#define	DMA_NAL		0x08000000	/* next address loaded [2] (ro) */
#define	DMA_AL		0x04000000	/* address loaded [2] (ro) */
#define	DMA_ON		0x02000000	/* working [2] (ro) */
#define	DMA_NAE		0x01000000	/* next-address enable [2] (rw) */
#define	DMA_DTCI	0x00800000	/* disable DMA_TC intr [2] (rw) */
#define	DMA_TURBO	0x00400000	/* faster 53C90A mode [2] (rw) */
#define	DMA_LERR	0x00200000	/* LANCE error [2] (ro) */
#define	DMA_TWOCYCLE	0x00200000	/* two cycle mode [3] (rw?) */
#define	DMA_ALE		0x00100000	/* LANCE addr latch ena [2] (rw) */
#define	DMA_2ZERO	0x000f0000	/* unused; reads as zero [2] */
#define	DMA_BURSTMASK	0x000c0000	/* burst mode mask [3] */
#define	DMA_BURST16	0x00000000		/* 16-byte bursts (default) */
#define	DMA_BURST32	0x00040000		/* 32-byte bursts */
#define	DMA_BURST0	0x00080000		/* no bursts */
#define	DMA_ILACC	0x00008000	/* for new AMD ethernet chip [1,2] */
#define	DMA_TC		0x00004000	/* terminal cnt: dma_bc ran out [1,2] */
E 4
#define	DMA_BCE		0x00002000	/* byte count enable (leave 0) */
D 4
#define	DMA_BO		0x00001800	/* byte offset (ro) */
#define	DMA_RP		0x00000400	/* request pending (ro) */
E 4
I 4
#define	DMA_BO		0x00001800	/* byte offset [1] (ro) */
#define	DMA_RP		0x00000400	/* busy, plz don't flush [1] (ro) */
E 4
#define	DMA_ENA		0x00000200	/* enable the dma chip */
#define	DMA_READ	0x00000100	/* set for dev=>mem, i.e., read() */
D 4
#define	DMA_RESET	0x00000080	/* reset dma chip [1] */
#define	DMA_DRAIN	0x00000040	/* drain buffered data [2,3] (wo) */
#define	DMA_ERR		0x00000040	/* slave error [4] (ro) */
#define	DMA_FLUSH	0x00000020	/* clear PC, EP, and TC [4] (wo) */
#define	DMA_IE		0x00000010	/* interrupt enable [4,5] */
#define	DMA_PC		0x0000000c	/* bytes in pack reg (ro) */
E 4
I 4
#define	DMA_RESET	0x00000080	/* reset dma chip [R] */
#define	DMA_DRAIN	0x00000040	/* drain buffered data [D,1] (wo) */
#define	DMA_SLAVEERR	0x00000040	/* slave error [2,3] (ro) */
#define	DMA_FLUSH	0x00000020	/* clear PC, EP, and TC [2,3] (wo) */
#define	DMA_IE		0x00000010	/* interrupt enable [2,3,I] */
#define	DMA_PC		0x0000000c	/* bytes in pack reg [1] (ro) */
#define	DMA_DRAINING	0x0000000c	/* nonzero => draining [2,3] (ro) */
E 4
#define	DMA_EP		0x00000002	/* error pending (ro) */
#define	DMA_IP		0x00000001	/* interrupt pending (ro) */

D 4
#define	DMA_BITS \
E 4
I 4
#define	DMA_REV1_BITS \
"\20\20ILACC\17TC\16BCE\13RP\12ENA\11READ\10RESET\7DRAIN\2EP\1IP"

/* Look ma, second system syndrome! */
#define	DMA_REV2_BITS \
E 4
"\20\34NAL\33AL\32ON\31NAE\30DTCI\27TURBO\26LERR\25ALE\
D 4
\20ILACC\17TC\16BCE\13RP\12ENA\11READ\10RESET\7DRAIN/ERR\6FLUSH\5IE\2EP\1IP"
E 4
I 4
\20ILACC\17TC\16BCE\12ENA\11READ\10RESET\7SLAVEERR\6FLUSH\5IE\2EP\1IP"

/* (Note how most of the crap has been discarded now.) */
#define	DMA_REV3_BITS \
"\20\26TWOCYCLE\16BCE\12ENA\11READ\10RESET\7SLAVEERR\6FLUSH\5IE\2EP\1IP"
E 4

/* DMA_BYTE turns the DMA_BO field into a byte index */
#define	DMA_BYTE(csr)	(((csr) >> 11) & 3)

/* DMA_NPACK turns the DMA_PC field into a byte count */
#define	DMA_NPACK(csr)	(((csr) >> 2) & 3)

/* DMA_INTR is true if the DMA chip says an ESP or DMA interrupt is pending */
#define	DMA_INTR(csr)	((csr) & (DMA_IP | DMA_EP))
E 1
