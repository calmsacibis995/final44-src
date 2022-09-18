#ifndef PATCHES_DEFINED
#define PATCHES_DEFINED
/*	@(#)patches.h 1.1 84/01/11 SMI	*/

/*
 *	patches:	Sun Microsystems 1984
 *
 *		64 X 64 memory pixrects with useful patterns: white,
 *		simple 25% gray, root-window 25% gray, 50% gray, 75% gray,
 *		and black.
 */

#include <pixrect/pixrect_hs.h>

extern struct pixrect	black_patch;
extern struct pixrect	gray25_patch;
extern struct pixrect	gray50_patch;
extern struct pixrect	gray75_patch;
extern struct pixrect	root_gray_patch;
extern struct pixrect	white_patch;

#endif
