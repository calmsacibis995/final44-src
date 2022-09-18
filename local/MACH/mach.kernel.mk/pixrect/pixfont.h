/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pixfont.h,v $
 * Revision 2.4  89/03/09  20:56:45  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:12:02  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)pixfont.h 1.3 87/01/08 SMI	*/

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#ifndef	PIXFONT_H_
#define PIXFONT_H_

/*
 * Definition of pixfonts for pixrect library.
 * Include <pixrect/pixrect.h> before this file.
 */

/*
 * A character descriptor contains the pixrect constituting the actual
 * character, the coordinates of the home (top left) of that pixrect
 * relative to the character origin (a point on the baseline near the left
 * of the character), and the distance by which to advance the origin after
 * printing this character.
 */
struct pixchar {
	Pixrect *pc_pr;	   /* pixrect for this char */
	struct pr_pos pc_home;	   /* home coords relative to left baseline */
	struct pr_pos pc_adv;	   /* distance to next char */
};

/*
 * A font descriptor contains the width of a space (intended to be used
 * in computing backspace and tab distances), the distance between consecutive
 * baselines in the absence of any superscripting, subscripting, or similar
 * vertical monkey business, and an array of 256 character descriptors.
 */
typedef struct pixfont {
	struct pr_size pf_defaultsize;	/* default character size */
	struct pixchar pf_char[256];
} Pixfont;

/* structured text macros */
#ifndef	lint
#define prs_text(prpos, op, pf, str) \
	pr_text((prpos).pr, (prpos).pos.x, (prpos).pos.y, pf, str)

#define prs_ttext(prpos, op, pf, str) \
	pr_ttext((prpos).pr, (prpos).pos.x, (prpos).pos.y, pf, str)
#endif	lint

Pixfont	*pf_open();
Pixfont	*pf_open_private();
Pixfont	*pf_default();
struct	pr_size pf_textbatch();
struct	pr_size pf_textwidth();

#define PIXFONT	Pixfont

#endif	PIXFONT_H_
