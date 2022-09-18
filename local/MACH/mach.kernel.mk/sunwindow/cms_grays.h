/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cms_grays.h,v $
 * Revision 2.4  89/03/09  21:56:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:04:12  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)cms_grays.h 1.2 86/10/08 SMI	*/

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Definition of the colormap segment CMS_GRAYS, a collection of grays.
 */

#define CMS_GRAYS	"grays"
#define CMS_GRAYSSIZE	8

#define WHITE	0
#define GRAY(i)	((BLACK)*(i)/100)
#define BLACK	7

#define cms_grayssetup(r,g,b) \
	{ unsigned char v = 0, vi; \
	  int	i, gi; \
	  vi = 255/BLACK; \
	  for (i=BLACK-1;i>WHITE;i--) { /* Dark (small v)->light (large v) */ \
		v += vi; \
		gi = GRAY(100/8*i); \
		(r)[gi] = v; (g)[gi] = v; (b)[gi] = v;  \
	  } \
	  (r)[WHITE] = 255;	(g)[WHITE] = 255;	(b)[WHITE] = 255; \
	  (r)[BLACK] = 0;	(g)[BLACK] = 0;		(b)[BLACK] = 0; \
	}

