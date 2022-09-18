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
 * $Log:	gfbframe.h,v $
 * Revision 2.3  89/03/09  22:15:06  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:19:09  gm0w
 * 	Changes for cleanup.
 * 
 * 02-Jan-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Created (V3.07m).
 *
 */
/*
 * GFB frame buffer definitions.
 */

/* How many bytes do we fetch to Port 'A' at a time from the frame? */
#define FR_bpr		(8)		/* Bytes-Per-Reference */

/* Register addresses in the frame interface (address in high byte,
   data in low byte in word to the attached 16bit parallel interface */
#define FRbase		(0)
#define FRsize		(4)
#define FRmap		(8)

/* Constants for dealing with the maps */
#define FRmaps		(3)
#define FRred		(0)
#define FRgreen		(1)
#define FRblue		(2)
#define FRredmap	(0x01)
#define FRgrnmap	(0x02)
#define FRblumap	(0x04)
#define FRallmap	(FRredmap|FRgrnmap|FRblumap)
#define FRmap_wr	(0x08)

/* Data type for dealing with the color maps */
#define FRmapsize	(256)
typedef byte MAP[FRmaps][FRmapsize];

/* Macros used for setting frame data */
#define FRDataWr(v,s,e)	FRWrite(v,s,e,0)
#define FRCntlWr(v,s,e)	FRWrite(v,s,e,1)

/* Bit definitions within frame control bytes ('9th bit' set) */
#define FRsync		(0x01)
#define FRblank		(0x02)

#ifdef	KERNEL
#define GFB_DMF		(0)		/* Minor DMF-32 device GFB uses */
extern unsigned map_index;		/* Where in the map we are writing */
#endif
#ifndef	KERNEL
extern int drcdes, gfbdes;
#endif
