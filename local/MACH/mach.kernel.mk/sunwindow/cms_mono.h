/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cms_mono.h,v $
 * Revision 2.4  89/03/09  21:57:01  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:04:19  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)cms_mono.h 1.2 86/10/08 SMI	*/

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Definition of the colormap segment CMS_MONOCHROME,
 * a black and white color map segment.
 */

#define CMS_MONOCHROME		"monochrome"
#define CMS_MONOCHROMESIZE	2

#define WHITE	0
#define BLACK	1

#define cms_monochromeload(r,g,b) \
	(r)[WHITE] = -1;(g)[WHITE] = -1;(b)[WHITE] = -1; \
	(r)[BLACK] = 0;(g)[BLACK] = 0;(b)[BLACK] = 0; 
