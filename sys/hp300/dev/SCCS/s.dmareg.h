h61708
s 00002/00002/00108
d D 8.1 93/06/10 21:32:15 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00005/00109
d D 7.5 92/10/11 09:23:44 bostic 5 4
c make kernel includes standard
e
s 00006/00005/00108
d D 7.4 92/06/05 15:31:54 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00112
d D 7.3 91/05/07 09:52:07 hibler 3 2
c 
e
s 00008/00008/00105
d D 7.2 90/11/04 19:21:09 mckusick 2 1
c update from Mike Hibler
e
s 00113/00000/00000
d D 7.1 90/05/08 22:06:35 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 5
#ifdef KERNEL
#include "hp/dev/iotypes.h"	/* XXX */
#else
#include <hp/dev/iotypes.h>	/* XXX */
#endif
E 5
I 5
#include <hp/dev/iotypes.h>		/* XXX */
E 5

E 4
/*
 * Hardware layout for the 98620[ABC]:
 *	98620A (old 320s?):	byte/word DMA in up to 64K chunks
 *	98620B (320s only):	98620A with programmable IPL
 *	98620C (all others):	byte/word/longword DMA in up to 4Gb chunks
 */
D 4
#define v_char		volatile char
#define	v_int		volatile int
#define vu_char		volatile u_char
#define vu_short	volatile u_short
#define vu_int		volatile u_int
E 4

struct	dmaBdevice {
	v_char		*dmaB_addr;
	vu_short	dmaB_count;
	vu_short	dmaB_cmd;
#define	dmaB_stat	dmaB_cmd
};

struct	dmadevice {
	v_char		*dma_addr;
	vu_int		dma_count;
	vu_short	dma_cmd;
	vu_short	dma_stat;
};

struct	dmareg {
	struct dmaBdevice dma_Bchan0;
	struct dmaBdevice dma_Bchan1;
/* the rest are 98620C specific */
	v_char		  dma_id[4];
	vu_char		  dma_cr;
	char		  dma_pad1[0xEB];
	struct dmadevice  dma_chan0;
	char		  dma_pad2[0xF4];
	struct dmadevice  dma_chan1;
};

#define	NDMA		2

/* intr level must be >= level of any device using dma.  i.e., splbio */
#define	DMAINTLVL	5

/* addresses */
D 3
#define	DMA_BASE	IOV(0x500000)
E 3
I 3
#define	DMA_BASE	IIOV(0x500000)
E 3

/* command bits */
#define	DMA_ENAB	0x0001
#define	DMA_WORD	0x0002
#define	DMA_WRT		0x0004
#define	DMA_PRI		0x0008
#define	DMA_IPL(x)	(((x) - 3) << 4)
#define DMA_LWORD	0x0100
#define DMA_START	0x8000

/* status bits */
#define	DMA_ARMED	0x01
#define	DMA_INTR	0x02
#define DMA_ACC		0x04
#define DMA_HALT	0x08
#define DMA_BERR	0x10
#define DMA_ALIGN	0x20
#define DMA_WRAP	0x40

#ifdef KERNEL
/*
 * Macros to attempt to hide the HW differences between the 98620B DMA
 * board and the 1TQ4-0401 DMA chip (68020C "board").  The latter
 * includes emulation registers for the former but you need to access
 * the "native-mode" registers directly in order to do 32-bit DMA.
 *
 * DMA_CLEAR:	Clear interrupt on DMA board.  We just use the
 *		emulation registers on the 98620C as that is easiest.
 * DMA_STAT:	Read status register.  Again, we always read the
 *		emulation register.  Someday we might want to
 *		look at the 98620C status to get the extended bits.
 * DMA_ARM:	Load address, count and kick-off DMA.
 */
#define	DMA_CLEAR(dc)	{ v_int dmaclr = (int)dc->sc_Bhwaddr->dmaB_addr; }
#define	DMA_STAT(dc)	dc->sc_Bhwaddr->dmaB_stat

#if defined(HP320)
D 2
#define	DMA_ARM(dc, ix)	\
E 2
I 2
#define	DMA_ARM(dc)	\
E 2
	if (dc->sc_type == DMA_B) { \
		register struct dmaBdevice *dma = dc->sc_Bhwaddr; \
D 2
		dma->dmaB_addr = dc->sc_addr[ix]; \
		dma->dmaB_count = dc->sc_count[ix] - 1; \
E 2
I 2
		dma->dmaB_addr = dc->sc_cur->dc_addr; \
		dma->dmaB_count = dc->sc_cur->dc_count - 1; \
E 2
		dma->dmaB_cmd = dc->sc_cmd; \
	} else { \
		register struct dmadevice *dma = dc->sc_hwaddr; \
D 2
		dma->dma_addr = dc->sc_addr[ix]; \
		dma->dma_count = dc->sc_count[ix] - 1; \
E 2
I 2
		dma->dma_addr = dc->sc_cur->dc_addr; \
		dma->dma_count = dc->sc_cur->dc_count - 1; \
E 2
		dma->dma_cmd = dc->sc_cmd; \
	}
#else
D 2
#define	DMA_ARM(dc, ix)	\
E 2
I 2
#define	DMA_ARM(dc)	\
E 2
	{ \
		register struct dmadevice *dma = dc->sc_hwaddr; \
D 2
		dma->dma_addr = dc->sc_addr[ix]; \
		dma->dma_count = dc->sc_count[ix] - 1; \
E 2
I 2
		dma->dma_addr = dc->sc_cur->dc_addr; \
		dma->dma_count = dc->sc_cur->dc_count - 1; \
E 2
		dma->dma_cmd = dc->sc_cmd; \
	}
#endif
#endif
E 1
