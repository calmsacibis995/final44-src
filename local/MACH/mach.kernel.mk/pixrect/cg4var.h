/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cg4var.h,v $
 * Revision 2.4  89/03/09  20:55:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:11:03  gm0w
 * 	Changes for cleanup.
 * 
 * 13-Feb-89  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added new copyright and #ifndef <filename>_H_ around whole
 *	file as part of kernel cleanup.
 */
/* @(#)cg4var.h 1.4 87/02/23 SMI */

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

#ifndef	CG4VAR_H_
#define CG4VAR_H_

/*
 * cg4 -- color memory frame buffer
 */

/* FBIOSATTR device specific array indices */
#define FB_ATTR_CG4_SETOWNER_CMD	0	/* 1 indicates PID is valid */
#define FB_ATTR_CG4_SETOWNER_PID	1	/* new owner of device */

#ifdef	KERNEL
#include <pixrect/memvar.h>
#else
#include <pixrect/memvar.h>
#endif

#define CG4_NFBS	3	/* number of frame buffers in a cg4 */

/* description of single frame buffer */
struct cg4fb {
	short			group;		/* plane group implemented */
	short			depth;		/* depth, bits */
	struct mprp_data	mprp;		/* memory pixrect data */
};
	
/* pixrect private data */
struct cg4_data {
	struct mprp_data	mprp;		/* memory pixrect simulator */
	int			flags;		/* misc. flags */
#define CG4_PRIMARY		1		/* primary pixrect */
#define CG4_OVERLAY_CMAP	2		/* overlay has colormap */
	int			planes;		/* current group and mask */
	int			fd;		/* file descriptor */
	short			active;		/* active fb no. */
	struct cg4fb		fb[CG4_NFBS];	/* frame buffer info */
};

/* useful macros */
#define cg4_d(pr)	((struct cg4_data *) ((pr)->pr_data))

/* pixrect ops vector */
extern struct pixrectops cg4_ops;

int	cg4_putcolormap();
int	cg4_putattributes();

#ifndef	KERNEL
Pixrect	*cg4_make();
int	cg4_destroy();
Pixrect *cg4_region();
int	cg4_getcolormap();
int	cg4_getattributes();
#endif	!KERNEL

#endif	CG4VAR_H_
