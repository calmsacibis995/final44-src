/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cg4reg.h,v $
 * Revision 2.5  89/07/11  17:28:31  jjc
 * 	Picked up newer version.
 * 	[89/07/05  20:50:58  jjc]
 * 
 *
 * Revision 2.4  89/03/09  21:40:17  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:49:46  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/* @(#)cg4reg.h 1.5 87/06/11 SMI */

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

#ifndef	CG4REG_H_
#define CG4REG_H_

/*
 * Prism frame buffer hardware definitions.
 *
 * The cg4 device has an overlay plane, enable plane and eight planes
 * of color/grayscale pixel read/write memory.  There are no rasterop chips 
 * or planes register.  All memory is on board memory.
 *
 * There are two flavors of cg4.  The A type has AMD DACS in the I/O space
 * and a status register.  The B type has a Brooktree BT458 DAC in the
 * memory space.
 */

/* number of colormap entries */
#define CG4_CMAP_ENTRIES	256

#ifdef	sun3

/* number of known cg4 types */
#define CG4_NTYPES		2

/* A type (AMD DAC) definitions */
#define	CG4A			0

/* frame buffer and color map addresses */
#define CG4A_ADDR_OVERLAY	0xFF000000
#define CG4A_ADDR_ENABLE	0xFE400000
#define CG4A_ADDR_COLOR		0xFE800000
#define CG4A_ADDR_CMAP		0x000E0000

/* frame buffer and color map address spaces */
#define CG4A_PGT_FB		PGT_OBMEM
#define CG4A_PGT_CMAP		PGT_OBIO

/* colormap/status register structure */
struct cg4a_cmap {
	u_char red[CG4_CMAP_ENTRIES];
	u_char green[CG4_CMAP_ENTRIES];
	u_char blue[CG4_CMAP_ENTRIES];
	u_char status;
#define CG4A_STATUS_FIRSTHALF	0x80
#define CG4A_STATUS_TOOLATE	0x40
};

/* B type (Brooktree DAC) definitions */

/* frame buffer and color map addresses */
#define CG4B_ADDR_OVERLAY	0xFB400000
#define CG4B_ADDR_ENABLE	0xFB600000
#define CG4B_ADDR_COLOR		0xFB800000
#define CG4B_ADDR_CMAP		0xFB200000

/* frame buffer and color map address spaces */
#define CG4B_PGT_FB		PGT_OBMEM
#define CG4B_PGT_CMAP		PGT_OBMEM

#else sun3
/* number of known cg4 types */
#define	CG4_NTYPES		1

/* B type (Brooktree DAC) definitions */

/* frame buffer and color map addresses */
#define CG4B_ADDR_OVERLAY	0xFB400000
#define CG4B_ADDR_ENABLE	0xFB600000
#define CG4B_ADDR_COLOR		0xFB800000
#define CG4B_ADDR_CMAP		0xFB200000

/* frame buffer and color map address spaces */
#define CG4B_PGT_FB		PGT_OBIO
#define CG4B_PGT_CMAP		PGT_OBIO

#endif sun3


/* colormap structure */
struct cg4b_cmap {
	u_char	addr;		/* address register */
	char	fill0[3];
	u_char	cmap;		/* color map data register */
	char	fill1[3];
	u_char	ctrl;		/* control register */
	char	fill2[3];
	u_char	omap;		/* overlay map data register */
	char	fill3[3];
};

#endif	!CG4REG_H_
