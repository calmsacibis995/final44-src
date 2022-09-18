/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	bw2var.h,v $
 * Revision 2.4  89/03/09  20:55:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:10:33  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)bw2var.h 1.2 86/10/08 SMI	*/

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#ifndef	BW2VAR_H_
#define BW2VAR_H_

/*
 * bw2 -- monochrome frame buffer
 */

/* standard resolution */
#define BW2SIZEX 1152
#define BW2SIZEY 900
#define BW2BYTES (BW2SIZEX*BW2SIZEY/8)

#define BW2SQUARESIZEX 1024
#define BW2SQUARESIZEY 1024
#define BW2SQUAREBYTES (BW2SQUARESIZEX*BW2SQUARESIZEY/8)

/* high resolution (bw2h) */
#define BW2HSIZEX	1600
#define BW2HSIZEY	1280
#define BW2HBYTES	(BW2HSIZEX*BW2HSIZEY/8)

#define BW2HSQUARESIZEX 1440
#define BW2HSQUARESIZEY 1440
#define BW2HSQUAREBYTES (BW2HSQUARESIZEX*BW2HSQUARESIZEY/8)


extern	struct pixrectops bw2_ops;

#ifndef	KERNEL
struct	pixrect *bw2_make();
int	bw2_destroy();
#endif

#endif	BW2VAR_H_
