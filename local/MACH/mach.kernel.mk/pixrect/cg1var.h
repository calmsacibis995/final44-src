/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cg1var.h,v $
 * Revision 2.4  89/03/09  20:55:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:10:45  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)cg1var.h 1.2 86/10/08 SMI	*/

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

#define cg1_fbfrompr(pr) (((struct cg1pr *)(pr)->pr_data)->cgpr_va)
/*
 * Information pertaining to the Sun-1 color buffer but not to pixrects in
 * general is stored in the struct pointed to by the pr_data attribute of the
 * pixrect.
 * One property of the color buffer not shared with all pixrects is that
 * it has a color map.  The color map type and colormap contents are
 * specified by the putcolormap operation.
 */
struct	cg1pr {
	struct	cg1fb *cgpr_va;
	int	cgpr_fd;
	int	cgpr_planes;		/* color bit plane mask reg */
	struct	pr_pos cgpr_offset;
};

#define cg1_d(pr) ((struct cg1pr *)(pr)->pr_data)

extern	struct pixrectops cg1_ops;

int	cg1_rop();
int	cg1_putcolormap();
int	cg1_putattributes();

#ifndef	KERNEL
int	cg1_batchrop();
int	cg1_stencil();
struct	pixrect *cg1_make();
int	cg1_destroy();
int	cg1_get();
int	cg1_put();
int	cg1_vector();
struct	pixrect *cg1_region();
int	cg1_getcolormap();
int	cg1_getattributes();
#endif	!KERNEL
