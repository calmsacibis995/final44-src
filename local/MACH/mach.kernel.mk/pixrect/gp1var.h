/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	gp1var.h,v $
 * Revision 2.4  89/03/09  20:56:14  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:11:29  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)gp1var.h 1.3 86/10/08 SMI	*/
 
/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * Information pertaining to the GP1/FB pair but not to pixrects in
 * general is stored in the struct pointed to by the pr_data attribute of the
 * pixrect.
 * One property of the GP1/FB pair not shared with all pixrects is that
 * it has a color map.  The color map type and colormap contents are
 * specified by the putcolormap operation.
 */

struct	gp1pr {
	struct	cg2fb *cgpr_va;		/* the color board va */
	caddr_t gp_shmem;		/* pointer to shared memory */
	int	cgpr_fd;
	int	cgpr_planes;		/* color bit plane mask reg */
	struct	pr_pos cgpr_offset;
	short	cg2_index;		/* cg2 board index */
	char	minordev;		/* true minor device to stuff into GP */
	int	gbufflag;		/* gbuffer flag */
	int	ioctl_fd;		/* the fd to talk to the driver with */
	int	ncmd;			/* length of cmdver array */
	u_char	*cmdver;		/* version #'s for each command */
};

#define gp1_d(pr) ((struct gp1pr *)(pr)->pr_data)
#define gp1_fbfrompr(pr) (((struct gp1pr *)(pr)->pr_data)->cgpr_va)


struct gp1_version {
	u_char majrel;
	u_char minrel;
	u_char serialnum;
	u_char flags;
};

extern	struct pixrectops gp1_ops;

int	gp1_rop();
int	gp1_putcolormap();
int	gp1_putattributes();

#ifndef	KERNEL
int	gp1_stencil();
int	gp1_batchrop();
struct	pixrect *gp1_make();
int	gp1_destroy();
int	gp1_get();
int	gp1_put();
int	gp1_vector();
struct	pixrect *gp1_region();
int	gp1_getcolormap();
int	gp1_getattributes();
#endif	!KERNEL
