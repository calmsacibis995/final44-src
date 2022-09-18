/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	gfbreg.h,v $
 * Revision 2.3  89/03/09  22:15:13  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:19:17  gm0w
 * 	Changes for cleanup.
 * 
 * 17-Aug-84  Andy Gruss (gruss) at Carnegie-Mellon University
 *	Created.
 *
 */
/*
 * Definitions for use with Gruss frame buffer (GFB) device.
 */
#ifndef	LOCORE
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long doub;

/* Handy structures for picking apart words and longs */
union wpart {
  byte b[2];
  word w;
};
union qpart {
  byte b[4];
  word w[2];
  doub q;
};

struct gfb_reg {
	doub csr, auxd;
};
struct gfb_frame {			/* The frame particulars... */
	byte *addr;			/*    ...virtual address */
	unsigned size;			/*    ...size */
};
/* 
 * Ioctl commands.
 */
#define GFB_LOCFR	(0)		/* Get frame address & size */
#define GFBCSR_RD	(1)		/* Read CSR */
#define GFBCSR_WR	(2)		/* Write CSR */
#define GFBAUXD_RD	(3)		/* Read AUXD register */
#define GFBAUXD_WR	(4)		/* Write AUXD register */
#define CACHE_INV	(5)		/* Invalidate CPU cache */
#define GFBNEW_MAPS	(6)		/* Write in new color maps */

extern struct gfb_frame gfb_frame;
#ifdef	KERNEL
/*
 * Kernel definitions relating to the GFB
 */
extern int numgfb;
extern struct gfb_reg *gfb_preg;
extern struct pte GFBmap[];		/* Allocated in "../sys/locore.s" */
extern byte GFBmem[];			/* Ditto... */
#endif
#endif
#define GFBPLANE	(0x80000)	/* Frame memory plane size (bytes) */
#define GFBMPLANES	(8)		/* Max frame memory planes */
#define GFBMSIZE	(GFBPLANE*GFBMPLANES)
#define GFBMPAGES	(GFBMSIZE >> PGSHIFT)
#define GFBBASE		(0x800000)	/* Frame base address (physical) */

/* Control/status register bit assignments */
#define GFB_PERR	(0x80000000)	/* Parity error flag bit */
#define GFB_PEOVRN	(0x40000000)	/* Parity overrun error */
#define GFB_PECHK	(0x20000000)	/* Enable soft err int in PE */
#define GFB_DIAG	(0x10000000)	/* Diagnostic mode (no parity) */
#define GFB_EMASK	(0x0F000000)	/* Byte-in-word PE bits */
#define GFB_PEADDR	(0x00FFFFFF)	/* Word address of last PE */
/* Diagnostic register bit assignments */
#define GFB_AUXDI	(0xF0000000)
#define GFB_AUXDO	(0x0F000000)
/* Handy commands */
#define GFB_RCSR	(0x80000000)	/* Puts CSR in a 'cleared' state */
